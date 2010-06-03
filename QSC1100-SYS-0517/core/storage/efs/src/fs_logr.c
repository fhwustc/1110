/*===========================================================================

  fs_logr.c -  Log region handling.


  Copyright (c) 2003-2008 by QUALCOMM Incorporated. All Rights Reserved.

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


  $Header: //source/qcom/qct/core/storage/efs/main/latest/src/fs_logr.c#3 $ $DateTime: 2008/12/12 09:42:18 $ $Author: richardp $

when          who     what, where, why
--------      ---     ------------------------------------------------------
2008-11-03    rp      Introduce device abstraction.
2008-06-02    rp      Use unwritten super-page.
2008-05-08    rp      Handle write-failure in log-region.
2007-10-18    rp      Featurized QEFS2.
2007-08-31    yg      ERR_FATAL on init if log queue size is not sufficient.
2007-08-10    rp      Align buffers passed to flash on a 32-byte boundary.
2006-09-11    dlb     Use flash driver wrappers.
2005-12-09    sh      Terminate search for next good block after looping.
2005-05-26    sd      Compilation fixes for L4.
2005-01-04    dlb     Update copyright line.
2004-12-30    dlb     Remove excess infiltration of factory image code.
2004-10-15    dlb     Update copyright line.
2004-10-07    dlb     Whitespace cleanup.
2003-06-13     gr     Added support for recovery from erase failures.
2003-03-07    dlb     Added fs_logr_peek_alloc().
2003-02-28    dlb     Created.
===========================================================================*/

#include "fs_efs2_cust.h"
#include "fs_device.h"

#ifdef FEATURE_EFS_QEFS2
#if defined (FEATURE_EFS_EFS2_ON_NAND) ||   \
    defined (FEATURE_EFS_EFS2_ON_NOR)

#include <stdio.h>

#ifdef FEATURE_IG_EFS_EXT_SERVER
  #include "amssassert.h"
#else
  #include "assert.h"
#endif

#include "fs_logr.h"
#include "fs_pm_ptable.h"
#include "fs_err.h"
#include "fs_device.h"

#ifdef FS_UNIT_TEST
#error code not present
#endif

/* Check if a block is marked as bad in the bad block map.
 */
#define BLOCK_IS_BAD(logr,bl) \
  (((logr)->super->data->u.nand.logr_badmap & \
   (1 << ((bl) - (logr)->block_base))) != 0)

/* Record that a block is bad.
 */
#define RECORD_BAD_BLOCK(logr,bl) \
(logr)->super->data->u.nand.logr_badmap |= 1 << ((bl)-(logr)->block_base);

/* Increment a block value with proper wrapping. */
#define ADVANCE_BLOCK(logr, bl) \
  do { \
    (bl)++; \
    if ((bl) >= (logr)->stop) \
      (bl) = (logr)->start; \
  } while (0)

/* Increment a block value with proper wrapping. Will skip all bad-blocks
 * marked bad in flash only, Blocks marked bad in logr_badmap in super will
 * still be included. */
#define ADVANCE_TO_NEXT_GOOD_FLASH_BLOCK(logr, bl) \
  do { \
    fs_block_id starting_block = bl; \
    ADVANCE_BLOCK((logr), (bl)); \
    while (fs_device_bad_block_check ((logr->super->dev), (bl)) \
              == FS_DEVICE_BAD_BLOCK) { \
      if (bl == starting_block) { \
        FS_ERR_FATAL ("Too many bad blocks starting at %d", bl, 0, 0); \
      } \
      ADVANCE_BLOCK((logr), (bl)); \
    } \
  } while (0)


/* Increment a block value skipping bad blocks. */
#define ADVANCE_TO_NEXT_GOOD_BLOCK(logr, bl) \
  do { \
    fs_block_id starting_block = bl; \
    ADVANCE_BLOCK((logr), (bl)); \
    while (BLOCK_IS_BAD((logr), (bl))) { \
      if (bl == starting_block) { \
        FS_ERR_FATAL ("Too many bad blocks starting at %d", bl, 0, 0); \
      } \
      ADVANCE_BLOCK((logr), (bl)); \
    } \
  } while (0)

/* XXX: Initial assumption that this is only for NAND flash. Some day we
 * may want to use this on NOR as well.
 */

static void
fs_logr_init_logr_badmap (fs_logr_t logr)
{
  fs_block_id bl;

  /* Update logr_badmap by consulting all the blocks in flash. */
  bl = logr->start;
  do
  {
    if (fs_device_bad_block_check (logr->super->dev, bl) ==
          FS_DEVICE_BAD_BLOCK)
    {
      RECORD_BAD_BLOCK (logr, bl);
#ifdef FS_UNIT_TEST
#error code not present
#endif
    }

    ADVANCE_BLOCK (logr, bl);
  }while (bl != logr->start);
}

void
fs_logr_init (
    fs_logr_t   logr,
    fs_super_t  super,
    int         fresh_start)
{
  /* Only written to support nand. */
  ASSERT (FS_ISNAND (super));

  /* If our log queue size is smaller than the block size then, at some
   * point it would encounter the error of overflowing queue, that
   * depends on the log head and how much we wrote before power down.
   * So in the event of using huge block size devices, increase queue
   * size to greater than the block size. This applies to NAND only
   * since NAND block contains full block of logs less 1 page. */
  if (FS_LOG_QUEUE_SIZE < super->data->block_size)
    FS_ERR_FATAL ("Queue size is not sufficient...", 0, 0, 0);

  /* Assumes there are exactly 4 regions. */
  ASSERT (super->data->u.nand.num_regions == 4);

  /* There are 32 bits for the log region bad block map. */
  ASSERT (super->data->u.nand.regions[3] - super->data->u.nand.regions[2]
      <= 32);

  /* This define is limits the number of blocks as well. */
  ASSERT (super->data->u.nand.regions[3] - super->data->u.nand.regions[2]
      <= FS_LOGR_MAX_LOG_BLOCKS);

  logr->super = super;
  logr->block_base = super->data->u.nand.regions[2];

  logr->start = super->data->u.nand.regions[2];
  logr->stop = super->data->u.nand.regions[3];

  if (fresh_start)
  {
    /* Detect all the bad-blocks in the flash. */
    super->data->u.nand.logr_badmap = 0;
    fs_logr_init_logr_badmap (logr);

    logr->write_block = logr->start;
    logr->write_page = 0;
  }
  else
  {
    /* The log starts at where the superblock indicates. */
    ASSERT (super->data->log_head != FS_INVALID_PAGE_ID);
    ASSERT (super->latest_super_page != FS_INVALID_PAGE_ID);

    /* Our logr_badmap may have become out of sync, because when ever a
     * super-page write fails, we immediately mark the block as bad in the
     * flash, but we don't update the more recent logr_badmap onto the
     * super-block until the next super-block flush happens. Since we rely on
     * the logr_badmap to more accurately describe the bad-blocks, we need
     * to update the logr_badmap by consulting every block in the flash */
    fs_logr_init_logr_badmap (logr);

    logr->write_block = super->data->log_head >> super->block_shift;
    logr->write_page = super->data->log_head & (~super->block_mask);

    /* If the log head is in the block where failure happened,
     * we do not want to start re-allocating pages from this block.
     * So we shall skip to the next good block. */
    if (BLOCK_IS_BAD (logr, logr->write_block))
    {
      logr->write_page = 1; /* Skip the superblock. */
      ADVANCE_TO_NEXT_GOOD_BLOCK (logr, logr->write_block);
    }

    while (!fs_device_is_erased (
          super->dev,
          (logr->write_block << super->block_shift)
          + logr->write_page))
    {
      logr->write_page++;
      if (logr->write_page == super->data->block_size) {
        /* Assigning the page to super page is taken care in logr_alloc */
        logr->write_page = 0;
        ADVANCE_TO_NEXT_GOOD_BLOCK (logr, logr->write_block);
      }

      if (((logr->write_block << super->block_shift)
          + logr->write_page) == super->data->log_head)
      {
        FS_ERR_FATAL ("No space found in log", 0, 0, 0);
      }
    }

    /* If the write_page lands on the 2nd-page in the block, then we should
     * have had the latest-super-page in the 1st-page, If not so, then we
     * had a bad powerdown while writing super page and the write did not
     * complete, making it a bad powerdown. */
    if (logr->write_page == 1)
    {
      fs_page_id prev_pg;
      prev_pg = (logr->write_block << super->block_shift);
      if (super->latest_super_page != prev_pg)
      {
        /* Since our latest super block was not found in this block's first
         * page, and nothing is written in this block, assigning write_page
         * to first page in the block will make logr_alloc to erase this
         * block and reuse the block properly with super page.  */
        logr->write_page = 0;
      }
    }
  }
}

fs_page_id
fs_logr_alloc (fs_logr_t logr)
{
  int result;
  fs_page_id new_page;

  if (logr->write_page == 0) {
    /* Skip over any bad blocks. */
    while (1) {
      if (BLOCK_IS_BAD (logr, logr->write_block)) {
        ADVANCE_TO_NEXT_GOOD_BLOCK (logr, logr->write_block);
      }
      result = fs_device_erase_block (logr->super->dev,
          logr->write_block, FS_FOP_LOG);
      if (result != FS_DEVICE_OK) {
        RECORD_BAD_BLOCK (logr, logr->write_block);
        fs_device_mark_block_bad (logr->super->dev,
            logr->write_block);
#ifdef FS_UNIT_TEST
#error code not present
#endif
      } else {
        break;
      }
    }
#ifdef FS_UNIT_TEST
#error code not present
#endif
  }

  new_page = (logr->write_block << logr->super->block_shift)
    + logr->write_page;

  logr->write_page++;

  if (logr->write_page >= logr->super->data->block_size) {
    logr->write_page = 0;
    ADVANCE_TO_NEXT_GOOD_BLOCK (logr, logr->write_block);
  }

#ifdef FS_UNIT_TEST
#error code not present
#endif

  return new_page;
}

/* Where do we think we are going to alloc? */
fs_page_id
fs_logr_peek_alloc (fs_logr_t logr)
{
  fs_page_id page = logr->write_page;
  if (page == 0)
    page = 1;

  return (logr->write_block << logr->super->block_shift)
    + page;
}

/* Copy out the stopping block and page, and update those values as we
 * iterate.  The value is used by the iteration routines to replay journal
 * entries correctly. */
void
fs_logr_iterate (fs_logr_t logr, fs_log_t log,
    void (*visit) (void *priv, fs_log_code_t code, uint32 *args),
    void *priv)
{
  fs_block_id      block, stop_block;
  fs_page_id       page, stop_page;
  int result;
  fs_log_code_t code;
  uint32        args[3];
  int           done;

  block = logr->super->data->log_head >> logr->super->block_shift;
  page = logr->super->data->log_head & (~logr->super->block_mask);

  stop_block = logr->write_block;
  stop_page = logr->write_page;

  while (block != stop_block || page != stop_page) {

    /* Is this assignment really needed?? */
    logr->write_block = block;
    logr->write_page = page;

    if (page != 0) /* Skip the super-pages. */
    {
      result = fs_log_iter_set_page (log,
          (block << logr->super->block_shift) + page,
          NULL);

      if (result == FS_LOG_ITER_GOOD)
      {
        done = 0;
        while (!done)
        {
          fs_log_iter_step (log, &code, args);

          if (code == LOG_CODE_GROUP_END)
          {
            done = 1;
          }
          else
          {
            visit (priv, code, args);
          }
        }

        fs_log_add_written_page (log,
            (block << logr->super->block_shift) + page);
      }
      else
      {
        /* Do nothing if either corrupt, or just erased. */
      }
    }

    /* Advance to the next page. */
    page++;
    if (page == logr->super->data->block_size)
    {
      page = 0;

      /* While advancing to the next block, we want to skip the bad-blocks
       * that are marked bad only in the flash. We still have to read from
       * the bad-blocks that are marked bad in logr_badmap, these bad-blocks
       * will eventually be marked as bad in flash as well when the log_head
       * moves past this bad-block, but until then we still have to read from
       * these bad-blocks to replay our log-pages.
       */
      ADVANCE_TO_NEXT_GOOD_FLASH_BLOCK (logr, block);
    }
  }

  /* Is this assignment really needed?? If this is not modified in the
   * loop?? */
  /* Put these back so the next run will work correctly. */
  logr->write_block = stop_block;
  logr->write_page = stop_page;
}

void
fs_logr_handle_bad_block (fs_logr_t logr, fs_block_id bad_blk)
{
  RECORD_BAD_BLOCK (logr, bad_blk);
  if (logr->write_block == bad_blk)
  {
    logr->write_page = 0;
    ADVANCE_TO_NEXT_GOOD_BLOCK (logr, logr->write_block);
  }
}


void
fs_logr_mark_bad_blocks (fs_logr_t logr, fs_page_id super_page,
                         fs_page_id log_head)
{
  fs_block_id log_head_blk, super_blk;

  /* Make sure the super-page is the first page of the block. */
  ASSERT ((super_page & (~logr->super->block_mask)) == 0);

  /* Now we traverse from next block of [latest-super block] till [previous
   * block of log_head] and mark the blocks as bad if it is marked as bad in
   * the logr_badmap but not yet in the flash. This is to make sure that we are
   * not marking the blocks as bad if we still need to read the log pages from
   * these bad-blocks. When the log head moves out of this bad block, then we
   * are sure that we would never need the log pages from this block again, So
   * now would be the perfect time to mark these blocks as bad in the flash as
   * well. */
  super_blk = super_page >> logr->super->block_shift;
  log_head_blk = log_head >> logr->super->block_shift;
  ADVANCE_BLOCK (logr, super_blk);
  while (super_blk != log_head_blk)
  {
    if (BLOCK_IS_BAD (logr, super_blk))
    {
      if (fs_device_bad_block_check (logr->super->dev, super_blk)
            != FS_DEVICE_BAD_BLOCK)
      {
        fs_device_mark_block_bad (logr->super->dev, super_blk);
      }
    }
    ADVANCE_BLOCK (logr, super_blk);
  }

}

#endif /* defined (FEATURE_EFS_EFS2_ON_NAND) || (FEATURE_EFS_EFS2_ON_NOR) */
#endif /* FEATURE_EFS_QEFS2 */


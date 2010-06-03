#ifndef __EFS2_DIAG_I_H
#define __EFS2_DIAG_I_H
/*==========================================================================

                   Diagnostic Packet Definitions for EFS2

  Description: Definitions of EFS2 packets. These define the diagnostic
  interface between EFS2 and the external device.

  Copyright (c) 2002-2009 by QUALCOMM, Incorporated.
  All Rights Reserved.
===========================================================================*/

/* <EJECT> */
/*===========================================================================

                            Edit History

  $Header: //source/qcom/qct/core/storage/efs/main/latest/src/fs_diag_i.h#3 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/12/09   yog     Add support for hotplug_dev_get_device_info diag packet.
12/16/08    rp     Trigger a dummy check-in to fix the version in perforce.
12/12/08    yg     Moved fs_diag.h as EFS private internal header file.
12/04/08   yog     Add support for idle_device_event_duration diag packet.
09/10/08    np     Add support efs_shred diagnostic packet.
07/23/08   wek     Added support for hotplug format diagnostic packet.
05/23/08    rp     Temporary move to the /inc folder.
05/22/08    rp     Added back PACKED and PACKED_POST for void * arguments.
05/20/08    eb     Removed PACKED and PACKED_POST for void * arguments.
04/03/08    eb     Added PACKED_POST directive for GCC support.
01/11/08    eb     Added packet fs_diag_statvfs_v2.
02/18/08    np     Added support for efs_md5sum diagnostic packets.
08/30/07    np     Added support for efs_truncate diagnostic packets.
08/02/07    sh     Removed incorrect fnctl flag values (hex instead of octal)
12/14/06    sh     Replaced fs_diag_access.h include.
12/14/06    sh     Access Validation cleanup.
12/13/06   umr     Add sequence_number support to efs_deltree handler.
12/06/06   umr     Added diag interface for Sequential [In Order] put / get
12/08/06   umr     Deprecated put / get request handlers
10/19/06   umr     Added diag interface for efs_deltree ()
09/19/06    sh     Rename all instances of bare 'errno' members.
06/22/06   dlb     Fix comments on get request.
06/19/06   dlb     Add visible maximum length on read requests.
06/08/06    sh     Moved fs_diag_efs2_error_rsp here.
01/26/06    sh     Added packets for chown, and get/set reservation/quota
01/26/06    sh     Removed misleading errno list (comment) from this file
10/18/05    sh     Added fs_benchmark handlers
06/22/05   dlb     Add extended info query packet.
02/24/05   nrs     Added Generic EFS Diag error packet
02/15/05   nrs     Removed bytes written from put response packet.
                   Changed header to reflect proper implementation.
02/10/05   nrs     Added packet structures for put and get
10/15/04   dlb     Update copyright line.
10/07/04   dlb     Whitespace cleanup.
09/14/03   adm     Added support for efs_image_prepare function
07/28/03    gr     Featurized inclusion of fs_diag_access.h. Added the #defines
                   needed to allow this.
07/16/03    gr     Moved access validation support into its own file.
06/16/03   spf     Added factory image support.
06/12/03    gr     Added support for validating access to files and
                   directories.
10/20/02    gr     Created
===========================================================================*/

#include "comdef.h"
#include "customer.h"
#include "diagcmd.h"
#include "diagpkt.h"
#include "fs_benchmark.h"
#include "fs_lib.h"

/* -------------------------------------------------------------------------
 * Definitions of EFS2 diagnostic packets.
 * ------------------------------------------------------------------------- */

#ifdef FEATURE_EFS2

#if defined(T_WINNT)
#error code not present
#endif

/*
 * This is also defined in services/diag/fs_diag_access.h,
 * unfortunately.  That will generate a Lint warning until the
 * duplicate prototype is removed from there.
 */
PACKED void * PACKED_POST
fs_diag_efs2_error_rsp (int32, PACKED void * PACKED_POST, uint16);

/*
 * Permitted operations.
 */
#define EFS2_DIAG_HELLO     0 /* Parameter negotiation packet               */
#define EFS2_DIAG_QUERY     1 /* Send information about EFS2 params         */
#define EFS2_DIAG_OPEN      2 /* Open a file                                */
#define EFS2_DIAG_CLOSE     3 /* Close a file                               */
#define EFS2_DIAG_READ      4 /* Read a file                                */
#define EFS2_DIAG_WRITE     5 /* Write a file                               */
#define EFS2_DIAG_SYMLINK   6 /* Create a symbolic link                     */
#define EFS2_DIAG_READLINK  7 /* Read a symbolic link                       */
#define EFS2_DIAG_UNLINK    8 /* Remove a symbolic link or file             */
#define EFS2_DIAG_MKDIR     9 /* Create a directory                         */
#define EFS2_DIAG_RMDIR    10 /* Remove a directory                         */
#define EFS2_DIAG_OPENDIR  11 /* Open a directory for reading               */
#define EFS2_DIAG_READDIR  12 /* Read a directory                           */
#define EFS2_DIAG_CLOSEDIR 13 /* Close an open directory                    */
#define EFS2_DIAG_RENAME   14 /* Rename a file or directory                 */
#define EFS2_DIAG_STAT     15 /* Obtain information about a named file      */
#define EFS2_DIAG_LSTAT    16 /* Obtain information about a symbolic link   */
#define EFS2_DIAG_FSTAT    17 /* Obtain information about a file descriptor */
#define EFS2_DIAG_CHMOD    18 /* Change file permissions                    */
#define EFS2_DIAG_STATFS   19 /* Obtain file system information             */
#define EFS2_DIAG_ACCESS   20 /* Check a named file for accessibility       */
#define EFS2_DIAG_NAND_DEV_INFO    21 /* Get NAND device info               */
#define EFS2_DIAG_FACT_IMAGE_START 22 /* Start data output for Factory Image*/
#define EFS2_DIAG_FACT_IMAGE_READ  23 /* Get data for Factory Image         */
#define EFS2_DIAG_FACT_IMAGE_END   24 /* End data output for Factory Image  */
#define EFS2_DIAG_PREP_FACT_IMAGE  25 /* Prepare file system for image dump */
#define EFS2_DIAG_PUT_DEPRECATED   26 /* Write an EFS item file             */
#define EFS2_DIAG_GET_DEPRECATED   27 /* Read an EFS item file              */
#define EFS2_DIAG_ERROR    28 /* Semd an EFS Error Packet back through DIAG */
#define EFS2_DIAG_EXTENDED_INFO 29 /* Get Extra information.                */
#define EFS2_DIAG_CHOWN         30 /* Change ownership                      */
#define EFS2_DIAG_BENCHMARK_START_TEST  31 /* Start Benchmark               */
#define EFS2_DIAG_BENCHMARK_GET_RESULTS 32 /* Get Benchmark Report          */
#define EFS2_DIAG_BENCHMARK_INIT        33 /* Init/Reset Benchmark          */
#define EFS2_DIAG_SET_RESERVATION       34 /* Set group reservation         */
#define EFS2_DIAG_SET_QUOTA             35 /* Set group quota               */
#define EFS2_DIAG_GET_GROUP_INFO        36 /* Retrieve Q&R values           */
#define EFS2_DIAG_DELTREE               37 /* Delete a Directory Tree       */
#define EFS2_DIAG_PUT                   38 /* Write a EFS item file in order*/
#define EFS2_DIAG_GET                   39 /* Read a EFS item file in order */
#define EFS2_DIAG_TRUNCATE              40 /* Truncate a file by the name   */
#define EFS2_DIAG_FTRUNCATE           41 /* Truncate a file by a descriptor */
#define EFS2_DIAG_STATVFS_V2       42 /* Obtains extensive file system info */
#define EFS2_DIAG_MD5SUM              43 /* Calculate md5 hash of a file  */
#define EFS2_DIAG_HOTPLUG_FORMAT        44 /* Format a Connected device */
#define EFS2_DIAG_SHRED                 45 /* Shred obsolete file content. */
#define EFS2_DIAG_SET_IDLE_DEV_EVT_DUR  46 /* Idle_dev_evt_dur value in mins */
#define EFS2_DIAG_HOTPLUG_DEVICE_INFO   47 /* get the hotplug device info.  */

/*
 * Any error codes in fs_errno.h can be returned by the EFS2 Diag interface.
 * In addition, these additional diag-specific values are possible:
 *
 * Error codes generated by the EFS2 Diag interface. Note that we use values
 * about 0x40000000 to avoid clashing with the errno values used by EFS2.
 */
#define FS_DIAG_INCONSISTENT_STATE  0x40000001
#define FS_DIAG_INVALID_SEQ_NO      0x40000002
#define FS_DIAG_DIR_NOT_OPEN        0x40000003
#define FS_DIAG_DIRENT_NOT_FOUND    0x40000004
#define FS_DIAG_INVALID_PATH        0x40000005
#define FS_DIAG_PATH_TOO_LONG       0x40000006
#define FS_DIAG_TOO_MANY_OPEN_DIRS  0x40000007
#define FS_DIAG_INVALID_DIR_ENTRY   0x40000008
#define FS_DIAG_TOO_MANY_OPEN_FILES 0x40000009
#define FS_DIAG_UNKNOWN_FILETYPE    0x4000000a
#define FS_DIAG_NOT_NAND_FLASH      0x4000000b
#define FS_DIAG_UNAVAILABLE_INFO    0x4000000c

/* File types.
 */
#define FS_DIAG_FTYPE_REG     0x00   /* Regular file                        */
#define FS_DIAG_FTYPE_DIR     0x01   /* Directory                           */
#define FS_DIAG_FTYPE_LINK    0x02   /* Symbolic link                       */
#define FS_DIAG_FTYPE_IMVBL   0x03   /* Immovable file                      */
#define FS_DIAG_FTYPE_UNKNOWN 0x0f   /* Unknown file type                   */

/* Device Types
*/
#define FS_DIAG_NOR_DEV       0x00   /* NOR flash device                    */
#define FS_DIAG_NAND_DEV      0x01   /* NAND flash device                   */

/*
 * Default window sizes. Set to large numbers because the target can support
 * essentially unlimited windowing without doing any extra work.
 */
#define FS_TARG_PKT_WINDOW_DEFAULT  0x100000
#define FS_TARG_BYTE_WINDOW_DEFAULT 0x100000
#define FS_HOST_PKT_WINDOW_DEFAULT  0x100000
#define FS_HOST_BYTE_WINDOW_DEFAULT 0x100000
#define FS_ITER_PKT_WINDOW_DEFAULT  0x100000
#define FS_ITER_BYTE_WINDOW_DEFAULT 0x100000

/*
 * Protocol version information.
 */
#define FS_DIAG_VERSION     0x0001
#define FS_DIAG_MIN_VERSION 0x0001
#define FS_DIAG_MAX_VERSION 0x0001

/*
 * Feature Bits.
 */
#define FS_FEATURE_BITS 0x00000000

/* Maximum size of a read request. */
#define FS_DIAG_MAX_READ_REQ    1024

/* -------------------------------------------------------------------------
 *
 * ASSERT MACRO
 *
 *-------------------------------------------------------------------------*/
#define FS_DIAG_ASSERT(cond)

/* -------------------------------------------------------------------------
 * PACKET STRUCTURES
 *
 * General Note: Fields after the errno field in the response packet may not
 * exist if the errno value is not equal to zero. A non-zero errno value
 * indicates that an error occurred during the processing of the request.
 * If errno == 0, all fields exist. If errno != 0, errno is the last field
 * in the response packet that can be relied upon to exist.
 *
 * ------------------------------------------------------------------------- */

/*
 * Parameter Negotiation Packet
 *
 * Used by the tool and the target to negotiate parameter values. Typically
 * sent just once at the start of a session.
 *
 * Window size parameters: The tool and the target should both set their
 * internal window size parameters to the smaller of the sizes specified
 * in the request and response packets. For instance, if the tool's
 * value for the targ_pkt_window parameter is 8 and the target's value for
 * this parameter is 4, the tool will specify 8 as the value of this field
 * in the EFS2_DIAG_HELLO request packet. The target will respond with a
 * packet in which this field is set to 4. Once the request and response
 * packets have been exchanged, both the tool and the target will store a
 * value of 4 for the targ_pkt_window parameter.
 *
 * Version fields: The tool and the target use these fields to determine
 * whether their protocol version numbers are compatible.
 *
 * feature_bits parameter: At the end of the exchange, the tool and the
 * target should perform a logical and on the values of this parameter
 * specified in the request and response packets and use the resulting
 * value as the feature bit mask.
 *
 * NOTE: When the tool sends this packet, all open files and directories
 * are closed.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 targ_pkt_window;  /* Window size in packets for sends from phone  */
  uint32 targ_byte_window; /* Window size in bytes for sends from phone    */
  uint32 host_pkt_window;  /* Window size in packets for sends from host   */
  uint32 host_byte_window; /* Window size in bytes for sends from host     */
  uint32 iter_pkt_window;  /* Window size in packets for dir iteration     */
  uint32 iter_byte_window; /* Window size in bytes for dir iteration       */
  uint32 version;          /* Protocol version number                      */
  uint32 min_version;      /* Smallest supported protocol version number   */
  uint32 max_version;      /* Highest supported protocol version number    */
  uint32 feature_bits;     /* Feature bit mask; one bit per feature        */
} efs2_diag_hello_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 targ_pkt_window;  /* Window size in packets for sends from phone  */
  uint32 targ_byte_window; /* Window size in bytes for sends from phone    */
  uint32 host_pkt_window;  /* Window size in packets for sends from host   */
  uint32 host_byte_window; /* Window size in bytes for sends from host     */
  uint32 iter_pkt_window;  /* Window size in packets for dir iteration     */
  uint32 iter_byte_window; /* Window size in bytes for dir iteration       */
  uint32 version;          /* Protocol version number                      */
  uint32 min_version;      /* Smallest supported protocol version number   */
  uint32 max_version;      /* Highest supported protocol version number    */
  uint32 feature_bits;     /* Feature bit mask; one bit per feature        */
} efs2_diag_hello_rsp_type;

/*
 * Query Packet
 *
 * Used to return the values of EFS2 constants that might be of interest
 * to the tool.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
} efs2_diag_query_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 max_name;          /* Maximum filename length                      */
  int32 max_path;          /* Maximum pathname length                      */
  int32 max_link_depth;    /* Maximum number of symlinks followed          */
  int32 max_file_size;     /* Maximum size of a file in bytes              */
  int32 max_dir_entries;   /* Maximum number of entries in a directory     */
  int32 max_mounts;        /* Maximum number of filesystem mounts          */
} efs2_diag_query_rsp_type;

/*
 * Open File Packet
 *
 * Used to open a named file.
 *
 * The following oflag values are valid:
 * O_RDONLY (open for reading mode)
 * O_WRONLY (open for writing mode)
 * O_RDWR   (open for reading and writing)
 * O_TRUNC  (if successfully opened, truncate length to 0)
 * O_CREAT  (create file if it does not exist)
 *
 * The O_CREAT flag can be orred with the other flags.
 * The mode field is ignored unless the O_CREAT flag is specified.
 * If O_CREAT is specified, the mode is a three-digit octal number with
 * each octet representing read, write and execute permissions for owner,
 * group and other.
 *
 * Note: If a request is received to open an already open file, the file
 * is closed and reopened.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 oflag;             /* Open flags                                   */
  int32 mode;              /* Mode                                         */
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_open_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 fd;                /* File descriptor if successful, -1 otherwise  */
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_open_rsp_type;

/*
 * Close File Packet
 *
 * Used to close a file descriptor.
 *
 * Note: If a request is received to close an already closed file, nothing
 * is done but an error is not reported.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 fd;                /* File descriptor                              */
} efs2_diag_close_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_close_rsp_type;

/*
 * Read File Packet
 *
 * Used to read the contents of an open file. Note that the response packet
 * does not explicitly contain the number of bytes read, since this can be
 * computed from the packet size. The number of bytes actually read may be
 * less than the number specified in the request packet if EOF is encountered
 * (this is not an error).
 *
 * NOTE 1: The fd is part of the response packet because we want to allow for
 * the possibility of more than one file being open for reading. The fd
 * allows the tool to match a response with a request.
 *
 * NOTE 2: This is one of the packets that support windowing. Thus there can
 * be several requests outstanding before a response is sent.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32  fd;               /* File descriptor                              */
  uint32 nbyte;            /* Number of bytes to read                      */
  uint32 offset;           /* Offset in bytes from the origin              */
} efs2_diag_read_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32  fd;               /* File descriptor                              */
  uint32 offset;           /* Requested offset in bytes from the origin    */
  int32  bytes_read;       /* bytes read if successful, -1 otherwise       */
  int32  diag_errno;       /* Error code if error, 0 otherwise             */
  char   data[1];          /* The data read out                            */
} efs2_diag_read_rsp_type;

/*
 * Write File Packet
 *
 * Used to write data into a given offset in an open file. If the offset is
 * past the current end of the file, the file is zero-filled until the offset
 * and then the data is written to the file. Note that the request packet
 * does not explicitly contain the number of bytes to be written, since this
 * can be computed from the packet size. Unless an error occurs, all the
 * bytes specified in the data field of the request packet are written to
 * the file.
 *
 * NOTE 1: The fd is part of the response packet because we want to allow for
 * the possibility of more than one file being open for writing. The fd allows
 * the tool to match a response with a request.
 *
 * NOTE 2: This is one of the packets that support windowing. Thus there can
 * be several requests outstanding before a response is sent.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 fd;                /* File descriptor                              */
  uint32 offset;           /* Offset in bytes from the origin              */
  char  data[1];           /* The data to be written                       */
} efs2_diag_write_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 fd;                /* File descriptor                              */
  uint32 offset;           /* Requested offset in bytes from the origin    */
  int32 bytes_written;     /* The number of bytes written                  */
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_write_rsp_type;

/*
 * Create Link Packet
 *
 * Used to create a symbolic link.
 *
 * Note: If a request is received to create an already created link, nothing
 * is done but an error is not reported.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char oldpath[1];         /* Old pathname (null-terminated string)        */
  char newpath[1];         /* New pathname (null-terminated string)        */
} efs2_diag_symlink_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_symlink_rsp_type;

/*
 * Read Link Packet
 *
 * Used to read the name of a symbolic link. Note that the response packet
 * does not explicitly contain the number of bytes read, since this can be
 * computed from the packet size.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_readlink_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
  char  name[1];           /* The name of the link                         */
} efs2_diag_readlink_rsp_type;

/*
 * Unlink Packet
 *
 * Used to remove a file or a symbolic link. The file is physically deleted
 * only if there are no more links to it.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_unlink_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_unlink_rsp_type;

/*
 * Make Directory Packet
 *
 * Used to create a directory.
 *
 * Note: If request is received to create an existing directory, the
 * directory will be removed if possible and recreated. If directory
 * removal fails (because it is not empty, typically) then an error is
 * returned.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int16 mode;              /* The creation mode                            */
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_mkdir_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_mkdir_rsp_type;

/*
 * Remove Directory Packet
 *
 * Used to delete a directory. The deletion will fail if the directory is
 * not empty.
 *
 * Note: If a request is received to remove an already removed directory,
 * nothing is done but an error is not reported.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_rmdir_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_rmdir_rsp_type;

/*
 * Open Directory Packet
 *
 * Used to open a directory for reading. Returns a directory pointer that
 * can be used to read the contents of the directory.
 *
 * Note: If a request is received to open an already open directory, nothing
 * is done but the dirp from the previous open is returned.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_opendir_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 dirp;             /* Directory pointer. NULL if error             */
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_opendir_rsp_type;

/*
 * Read Directory Packet
 *
 * Used to read the next entry from an open directory. Returns the name
 * of the entry and some information about it. The directory pointer passed
 * in is returned in the response packet so that the tool can match it to
 * the request packet. The request packet contains a sequence number so that
 * the tool  can request to retrieve an entry again if the response packet
 * does not get through. If the iteration is complete, the entry_name field
 * in the response packet will contain an empty string (first character =
 * '\0'). Valid sequence numbers are positive integers, with a sequence
 * number of 1 indicating the first entry in the directory. "." and "..",
 * which are entries present in every directory, are not passed back.
 *
 * NOTE: This is one of the packets that support windowing. Thus there can
 * be several requests outstanding before a response is sent.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 dirp;             /* Directory pointer.                           */
  int32 seqno;             /* Sequence number of directory entry to read   */
} efs2_diag_readdir_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 dirp;             /* Directory pointer.                           */
  int32  seqno;            /* Sequence number of directory entry           */
  int32  diag_errno;       /* Error code if error, 0 otherwise             */
  int32  entry_type;       /* 0 if file, 1 if directory, 2 if symlink      */
  int32  mode;             /* File mode                                    */
  int32  size;             /* File size in bytes                           */
  int32  atime;            /* Time of last access                          */
  int32  mtime;            /* Time of last modification                    */
  int32  ctime;            /* Time of last status change                   */
  char   entry_name[1];    /* Name of directory entry (not full pathname)  */
} efs2_diag_readdir_rsp_type;

/*
 * Close Directory Packet
 *
 * Used to close an open directory.
 *
 * Note: If a request is received to close an already closed directory,
 * nothing is done but an error is not returned.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 dirp;              /* Directory pointer.                           */
} efs2_diag_closedir_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_closedir_rsp_type;

/*
 * Rename Packet
 *
 * Used to rename a file or directory. Note that duplicate requests to rename
 * a directory will lead to an error code being returned the second time if
 * the rename was successful the first time. If the duplicate request is due
 * to a missing response packet, the tool needs to check the error code to
 * make sure that the error is reasonable (ENOENT will be the error returned
 * in this case).
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char oldpath[1];         /* Old pathname (null-terminated string)        */
  char newpath[1];         /* New pathname (null-terminated string)        */
} efs2_diag_rename_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_rename_rsp_type;

/*
 * Stat Packet
 *
 * Used to retrieve information about a named file or directory.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char path[1];         /* Pathname (null-terminated string)               */
} efs2_diag_stat_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
  int32 mode;              /* File mode                                    */
  int32 size;              /* File size in bytes                           */
  int32 nlink;             /* Number of links                              */
  int32 atime;             /* Time of last access                          */
  int32 mtime;             /* Time of last modification                    */
  int32 ctime;             /* Time of last status change                   */
} efs2_diag_stat_rsp_type;

/*
 * Lstat Packet
 *
 * Used to retrieve information about a symbolic link.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char path[1];         /* Pathname (null-terminated string)               */
} efs2_diag_lstat_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
  int32 mode;              /* File mode                                    */
  int32 atime;             /* Time of last access                          */
  int32 mtime;             /* Time of last modification                    */
  int32 ctime;             /* Time of last status change                   */
} efs2_diag_lstat_rsp_type;

/*
 * Fstat Packet
 *
 * Used to retrieve information about a file descriptor.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 fd;                /* File descriptor                              */
} efs2_diag_fstat_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
  int32 mode;              /* File mode                                    */
  int32 size;              /* File size in bytes                           */
  int32 nlink;             /* Number of links                              */
  int32 atime;             /* Time of last access                          */
  int32 mtime;             /* Time of last modification                    */
  int32 ctime;             /* Time of last status change                   */
} efs2_diag_fstat_rsp_type;

/*
 * Chmod Packet
 *
 * Used to change the access permissions of a file or directory.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int16 mode;              /* The new mode                                 */
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_chmod_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_chmod_rsp_type;

/*
 * Statfs Packet
 *
 * Used to retrieve information about a filesystem. Note that the request
 * packet must specify a path to a file or directory. Information is returned
 * about the file system containing the named file or directory.
 */
#define EFS_FSTYPE_LEN 8

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char path[1];         /* Pathname (null-terminated string)               */
} efs2_diag_statfs_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
  int32 fs_id;             /* Filesystem ID                                */
  uint8 fs_type[EFS_FSTYPE_LEN];  /* Filesystem type                       */
  int32 block_size;        /* Filesystem block size                        */
  int32 total_blocks;      /* Filesystem size in blocks                    */
  int32 avail_blocks;      /* Blocks available in filesystem               */
  int32 free_blocks;       /* Blocks free in filesystem                    */
  int32 max_file_size;     /* Maximum size of a file in this filesystem    */
  int32 nfiles;            /* Current number of files in this filesystem   */
  int32 max_nfiles;        /* Maximum number of files in this filesystem   */
} efs2_diag_statfs_rsp_type;

/*
 * Access Packet
 *
 * Used to check access permissions for a file or directory.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  char perm_bits;       /* Permission bits                                */
  char path[1];         /* Pathname (null-terminated string)              */
} efs2_diag_access_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_access_rsp_type;

/*
 * Device Specification Packet
 *
 * Used to get the specifications of the flash device being used in the
 * phone.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
} efs2_diag_dev_info_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;            /* Error code if error, 0 otherwise  */
  int32 total_no_of_blocks;    /* Total number of blocks in the device */
  int32 no_of_pages_per_block; /* Number of pages in a block */
  int32 page_size;             /* Size of page data region in bytes */
  int32 total_page_size;       /* Size of total page_size */
  int32 maker_id;              /* Device maker ID */
  int32 device_id;             /* Device ID */
  uint8 device_type;           /* 0 indicates NOR device 1 NAND */
  uint8 device_name[1];        /* Name of the Nand device */
} efs2_diag_dev_info_rsp_type;

/*
 * Factory Image Start Packet
 *
 * Used to indicate to the file system to start output of
 * data for factory image
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
} efs2_diag_factimage_start_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32  diag_errno;           /* Error code if error, 0 otherwise */
} efs2_diag_factimage_start_rsp_type;

/*
 * Factory Image Data Packet
 *
 * Used to read the next page forming the EFS2 data for the factory image.
 * The initial request should have all parameters initialized to zero.
 * These parameters will be updated by the target and returned in the
 * response.  Each subsequent request should use these updated parameter
 * values.  The stream_state parameter in the response will indicate
 * whether or not there is more data to be read.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int8 stream_state;        /* Initialize to 0 */
  int8 info_cluster_sent;   /* Initialize to 0 */
  int16 cluster_map_seqno;  /* Initialize to 0 */
  int32 cluster_data_seqno; /* Initialize to 0 */
} efs2_diag_factimage_read_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;         /* Error code if error, 0 otherwise */
  int8 stream_state;        /* 1 = more data, 0 = all done      */
  int8 info_cluster_sent;   /* Info cluster sent indicator      */
  int16 cluster_map_seqno;  /* Cluster map sequence number      */
  int32 cluster_data_seqno; /* Cluster data sequence number     */
  char page[1];             /* Page data buffer */
} efs2_diag_factimage_read_rsp_type;

/*
 * Factory Image End Packet
 *
 * Used to indicate to the File system to end output of
 * EFS2 data for factory image
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
} efs2_diag_factimage_end_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32  diag_errno;      /* Error code if error, 0 otherwise */
} efs2_diag_factimage_end_rsp_type;


/*
 * Factory Image Prepare Packet
 *
 * Used to indicate to the File system to
 * prepare the file system for a factory image
 * dump.
*/

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
} efs2_diag_prep_factimage_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32  diag_errno;      /* Error code if error, 0 otherwise */
} efs2_diag_prep_factimage_rsp_type;

/*
 * Get Deprecated File Packet
 *
 * Old procedure used to read the contents of a named file. Note that the
 * response packet does not explicitly contain the number of bytes read, since
 * this can be computed from the packet size. The number of bytes actually read
 * may be less than the number specified in the request packet if EOF is
 * encountered (this is not an error).
 *
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 data_length;      /* Number of bytes to read                      */
  uint32 path_length;      /* Length of the path name (ignored)            */
  char path[1];            /* Pathname (null-terminated string)            */
} efs2_diag_get_deprecated_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32  num_bytes;        /* bytes read if successful, -1 otherwise       */
  int32  diag_errno;       /* Error code if error, 0 otherwise             */
  char   data[1];          /* The data read out                            */
} efs2_diag_get_deprecated_rsp_type;

/*
 * Put Deprecated File Packet
 *
 * Old procedure used to write data into an item file. Unless an error occurs,
 * all the bytes specified in the data field of the request packet are written
 * to the file. If there is an error, the error field will be non-zero.
 *
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 data_length;      /* Length of the data packet                    */
  uint32 flags;            /* Options for creating the item                */
  char  data[1];           /* The data to be written                       */
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_put_deprecated_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_put_deprecated_rsp_type;

/*
 * Get File Packet
 *
 * Used to read the contents of a named file. Note that the response packet
 * does not explicitly contain the number of bytes read, since this can be
 * computed from the packet size. The number of bytes actually read may be
 * less than the number specified in the request packet if EOF is encountered
 * (this is not an error).
 *
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 data_length;      /* Number of bytes to read                      */
  uint32 path_length;      /* Length of the path name (ignored)            */
  uint16 sequence_number;  /* Number for Synchronization / Correlation     */
  char path[1];            /* Pathname (null-terminated string)            */
} efs2_diag_get_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32  num_bytes;        /* bytes read if successful, -1 otherwise       */
  int32  diag_errno;       /* Error code if error, 0 otherwise             */
  uint16 sequence_number;  /* Acknowledge Synchronization / Correlation num */
  char   data[1];          /* The data read out                            */
} efs2_diag_get_rsp_type;

/*
 * Put File Packet
 *
 * Used to write data into an item file. Unless an error occurs, all the
 * bytes specified in the data field of the request packet are written to
 * the file. If there is an error, the error field will be non-zero.
 *
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 data_length;      /* Length of the data packet                    */
  uint32 flags;            /* Options for creating the item                */
  uint16 sequence_number;  /* Number for Synchronization / Correlation     */
  char  data[1];           /* The data to be written                       */
  char  path[1];           /* Pathname (null-terminated string)            */
} efs2_diag_put_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;  /* Acknowledge Synchronization / Correlation num */
  int32 diag_errno;        /* Error code if error, 0 otherwise             */
} efs2_diag_put_rsp_type;


/*
 * EFS2 Diag Error Packet
 *
 * To provide for better error handling response, this generic packet should
 * be returned in the case where EFS2 errors will occur, but can not be
 * passed back in the normal response packets of the handlers.
 *
 */

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;        /* Error code to be handled */
  byte pkt[32];
} efs2_diag_error_rsp_type;


/* EFS2 Benchmark Start_Test
 *
 * Begin a benchmark test operation.
 */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  fs_benchmark_test_cmd cmd;
} efs2_diag_benchmark_start_test_req_type;

typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  byte success;
  fs_benchmark_test_cmd cmd;
} efs2_diag_benchmark_start_test_rsp_type;

/* EFS2 Benchmark Results
 *
 * Fetch any pending results from a benchmark test operation.
 */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
} efs2_diag_benchmark_get_results_req_type;

typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  enum fs_benchmark_queue_status_t queue_status;
  fs_benchmark_report report;
} efs2_diag_benchmark_get_results_rsp_type;

/* EFS Benchmark initialize/reset */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
} efs2_diag_benchmark_init_req_type;

typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
} efs2_diag_benchmark_init_rsp_type;


/*
 * Quota and Reservation handling
 */

/* Many commands have a simple response */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;             /* Error code if error, 0 otherwise */
} efs2_diag_errno_rsp_type;

/* EFS2_DIAG_CHOWN */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  int32 uid_val;                  /* UID, or -1 */
  int32 gid_val;                  /* GID, or -1 */
  char path[1];                 /* Pathname (null-terminated) */
} efs2_diag_chown_req_type;

/* EFS2_DIAG_SET_RESERVATION */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  uint32 gid;                   /* GID */
  fs_size_t bytes;
  char path[1];                 /* Pathname (null-terminated) */
} efs2_diag_set_reservation_req_type;

/* EFS2_DIAG_SET_QUOTA */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  uint32 gid;                   /* GID */
  fs_size_t bytes;
  char path[1];                 /* Pathname (null-terminated) */
} efs2_diag_set_quota_req_type;


/* EFS2_DIAG_GET_GROUP_INFO */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  uint32 gid;                   /* GID */
  char path[1];                 /* Pathname (null-terminated) */
} efs2_diag_get_group_info_req_type;

/*
 * Deltree Packet
 *
 * Used to remove a directory and all its contents. The directory is completly
 * deleted only if there are no errors occured while performing the delete
 * operations.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number; /* Number for Synchronization / Correlation     */

/* Pathname (null-terminated string with "/public/" prepended). Deltree
 * operation from diag is performed only under the directory /public.
 */
  char  path[1];
} efs2_diag_deltree_req_type;

/* Simple response with a sequence number */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;   /* Acknowledge Synchronization / Correlation num */
  int32 diag_errno;         /* Error code if error, 0 otherwise             */
} efs2_diag_deltree_rsp_type;

/*
 * EFS2_DIAG_TRUNCATE: Truncate a file by pathname
 *
 * Truncate is the diagnostic packet for truncating a file with a filename
 * and a specified size.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number; /* Number for Synchronization / Correlation     */
  uint32 length; /* Truncated file length */
  char  path[1]; /* Pathname for the file to be truncated. */
} efs2_diag_truncate_req_type;

/* Simple response with a sequence number */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;   /* Acknowledge Synchronization / Correlation num */
  int32 diag_errno;         /* Error code if error, 0 otherwise             */
} efs2_diag_truncate_rsp_type;

/*
 * Ftruncate Packet
 *
 * Ftruncate is the diagnostic packet for truncating a file with a file
 * descriptor and a specified size.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number; /* Number for Synchronization / Correlation     */
  uint32 length; /* Truncated file length */
  int32 fildes; /* File descriptor for the file to be deleted. */
} efs2_diag_ftruncate_req_type;

/* Simple response with a sequence number */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;   /* Acknowledge Synchronization / Correlation num */
  int32 diag_errno;         /* Error code if error, 0 otherwise             */
} efs2_diag_ftruncate_rsp_type;

/* Statvfs_v2 packet
 *
 * Extended version of statfs packet. Contains additional filesystem
 * specific information.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number; /* Number for Synchronization / Correlation     */
  char path[1];         /* Pathname (null-terminated string)               */
} efs2_diag_statvfs_v2_req_type;

/* Statvfs response packet with addtional fields */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;    /* Synchronization / Correlation num           */
  int32  diag_errno;        /* Error code if error, 0 otherwise             */
  uint32 fs_id;             /* Filesystem ID                                */
  uint8  fs_type[EFS_FSTYPE_LEN];  /* Filesystem type                       */
  uint32 block_size;        /* Filesystem block size                        */
  uint32 total_blocks;      /* Filesystem size in blocks                    */
  uint32 avail_blocks;      /* Blocks available in filesystem               */
  uint32 free_blocks;       /* Blocks free in filesystem                    */
  uint32 max_file_size;     /* Maximum size of a file in this filesystem    */
  uint32 nfiles;            /* Current number of files in this filesystem   */
  uint32 max_nfiles;        /* Maximum number of files in this filesystem   */
  uint32 f_maxwrite;        /* Maximum number of bytes in a single write    */
  uint32 f_pathmax;         /* Maximum number of character symbols in path  */
  uint32 f_is_case_sensitive;  /* 1=> Path IS case sens. 0=> NOT case sens. */
  uint32 f_is_case_preserving; /* 1=> Path IS case pers. 0=> NOT case pers. */
  uint32 f_max_file_size;      /* Max file size in units f_max_file_size_unit*/
  uint32 f_max_file_size_unit; /* Units of max file size                    */
  uint32 f_max_open_files;      /* Maximum # open files at one time         */
  uint32 f_name_rule;          /* Pre-defined rules for naming files        */
  uint32 f_name_encoding;      /* File name encoding scheme                 */
} efs2_diag_statvfs_v2_rsp_type;


/* An exact clone of fs_group_info, but packed */
PACKED struct PACKED_POST efs2_diag_fs_group_info
{
  uint32 quota_size;
  uint32 reservation_size;
  uint32 space_used;
};

typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  int32 diag_errno;             /* Error code if error, 0 otherwise */
  struct efs2_diag_fs_group_info info;
} efs2_diag_get_group_info_rsp_type;

#if defined(T_WINNT)
#error code not present
#endif

/*
 * EFS2 Extended info packet.
 *
 * This request is used to query additional information about the
 * filesystem or underlying flash device.  The 'data', and 'path' fields
 * are determined by the particular query being made.
 */

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 query;
  uint32 data;
  char   path[1];
} efs2_diag_extended_info_req_type;

typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint32 kind;
  /*
   * Payload follows this packet directly, either a uin32 or a string.
   */
  /*
  union {
    uint32 int_val;
    char   string_val[1];
  } u;
  */
} efs2_diag_extended_info_rsp_type;

/*
 * md5sum Packet
 *
 * Used to calculate the md5 hash of a file content.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number; /* Number for Synchronization / Correlation     */

/* Pathname (null-terminated string). Md5hash operation from diag is performed
 * on the data with the filename path.
 */
  char  path[1];
} efs2_diag_md5sum_req_type;

/* Simple response with a sequence number */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;   /* Acknowledge Synchronization / Correlation num */
  int32 diag_errno;         /* Error code if error, 0 otherwise             */
  struct fs_md5sum hash_result; /* md5 hash result.*/
} efs2_diag_md5sum_rsp_type;

/*
 * Hotplug format diagnostics request packet.
 *
 * This packet contains the header type, sequence number and the
 * path to the media to be formatted (erased).
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number; /* Number for Synchronization / Correlation     */
  char  path[1];        /* Pathname (null-terminated string) to be erased. */
} efs2_diag_hotplug_format_req_type;

/*
 * Hotplug format diagnostics response packet.
 *
 * This packet contains the header type, sequence number and the
 * error number (efs_errno) indicating if the media was
 * successfully formatted.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;   /* Acknowledge Synchronization / Correlation num */
  int32 diag_errno;         /* Error code if error, 0 otherwise             */
} efs2_diag_hotplug_format_rsp_type;

/*
 * Shred packet
 *
 * Used to erase all the obsolete data (deleted file content) from the device.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number; /* Number for Synchronization / Correlation     */
  /* Path is a null-terminated string. It contains a valid file path for a file
   * or a directory in the file system on shich the shred is run.
   */
  char  path[1];
} efs2_diag_shred_req_type;

/* Shred response packet with a sequence number */
typedef PACKED struct PACKED_POST
{
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;    /* Acknowledge Synchronization/Correlation num  */
  int16 shred_result;
  int32 diag_errno;          /* Error code if error, 0 otherwise             */
} efs2_diag_shred_rsp_type;

/* Set idle device event duration diagnostics request packet.
 *
 * This packet contains the header type, sequence number and the
 * event duration in the minute value for the fs_hotplug_idle_device_timer.
 * This timer would generate an event after this duration value to check
 * whether to call the idle_dispatch () function or not.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;
  uint32 event_dur_minutes;
} efs2_diag_set_idle_dev_evt_dur_req_type;

/* Set idle device event duration diagnostics response packet.
 *
 * Simple response with a sequence number and diag_errno.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;
  int32  diag_errno;
} efs2_diag_set_idle_dev_evt_dur_rsp_type;

/* hotplug device info diagnostics request packet.
 *
 * This packet is used to get the device info maintained by the hotplug module
 * referred by the given path string.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;
  char path[1];
} efs2_diag_hotplug_device_info_req_type;

/* hotplug device info diagnostics request packet.
 */
typedef PACKED struct PACKED_POST {
  diagpkt_subsys_header_type hdr;
  uint16 sequence_number;
  int32  diag_errno;       /* errno if any error or 0 otherwise. */

  /* Device specific info. */
  uint32 manufacturer_id;       /* Manufacturer ID. */
  uint32 oem_id;                /* OEM ID. */
  uint32 prod_rev;              /* Product revision. */
  uint32 prod_serial_num;       /* Product serial number. */
  byte   product_name[16];      /* Product Name. */
  byte   manufactured_date[16]; /* Manufactured Date. */
} efs2_diag_hotplug_device_info_rsp_type;

/* The extended info queries can return multiple kinds of values, depending
 * on the request. */
#define FS_DIAG_EXT_KIND_INT    0
#define FS_DIAG_EXT_KIND_STRING 1

/* Currently defined queries.  Querying information that is not available
 * will return an efs2_diag_error_rsp_type packet with the error code set
 * to FS_DIAG_UNAVAILABLE_INFO.  All queries expect 'path' to be set to an
 * EFS2 path that determines which filesystem the query applies to.  The
 * path must be null terminated. */

#define FS_DIAG_EXT_QUERY_DEVICE_NAME   0
        /* Return the flash device name.  'data' is ignored Results in a
         * string. */

#define FS_DIAG_EXT_QUERY_DEVICE_ID     1
        /* Return a field of the device ID.  'data' indicates which ID
         * field to return.  '0' is always the Maker ID, and '1' begins the
         * device-specific ID.  The client should always request values
         * until the FS_DIAG_UNAVAILABLE_INFO is returned, indicating there
         * are no more ID values. */

#define FS_DIAG_EXT_QUERY_FILESYSTEM_BLOCKS   2
        /* Return the number of blocks in this EFS2 partition.  These are
         * FLASH blocks (called sectors for NOR).  'data' is ignored. */

#define FS_DIAG_EXT_QUERY_TOTAL_BLOCKS        3
        /* Return the total number of blocks in the flash device containing
         * this filesystem.  'data' is ignored. */

#define FS_DIAG_EXT_QUERY_PAGES_PER_BLOCK     4
        /* Return the number of pages per block for this device.  This
         * query is only valid for devices that have a fixed block size.
         * For devices with varying block sizes, the TBD request must be
         * used.  'data' is ignored. */

#define FS_DIAG_EXT_QUERY_PAGE_SIZE        5
        /* Return the number of bytes in a single page for this device.
         * 'data' is ignored'. */

#define FS_DIAG_EXT_QUERY_FLASH_BUS_WIDTH  6
        /* Return the bus width of the flash device used in this
         * filesystem.  'data' is ignored. */

/* Additional queries go here... */

#endif /* FEATURE_EFS2 */

#endif /* __EFS2_DIAG_I_H */


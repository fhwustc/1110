#ifndef QTV_FRUC_BROADCAST_H
#define QTV_FRUC_BROADCAST_H
/* =======================================================================

                          fruc_broadcast.h

DESCRIPTION
  Definition of the broadcast types generated by the video decoder.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None.

Copyright 2005 QUALCOMM Incorporated, All Rights Reserved
========================================================================== */
/* =======================================================================
                             Edit History

$Header: //source/qcom/qct/multimedia/qtv/renderer/main/latest/inc/fruc_broadcast.h#1 $
$DateTime: 2008/05/16 02:30:28 $
$Change: 660959 $

========================================================================== */

/* =======================================================================
**               Includes and Public Data Declarations
** ======================================================================= */

/* ==========================================================================

                     INCLUDE FILES FOR MODULE

========================================================================== */
/* Includes custmp4.h. The following 2 includes must be the first includes in this file! */
#include "customer.h"
#include "qtvInternalDefs.h"
#include "broadcast.h"
#include "vdecoder_types.h"
#include "qtv_utils.h"

/* ==========================================================================

                        DATA DECLARATIONS

========================================================================== */
/* -----------------------------------------------------------------------
** Constant / Define Declarations
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Type Declarations
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Global Constant Data Declarations
** ----------------------------------------------------------------------- */

/* -----------------------------------------------------------------------
** Global Data Declarations
** ----------------------------------------------------------------------- */

/* =======================================================================
**                        Macro Definitions
** ======================================================================= */

/* =======================================================================
**                        Class & Function Declarations
** ======================================================================= */
class qtv_FRUC_bcast_class : public QTV_Broadcast
{
public:
  typedef enum {
    FRUC_RESULT_SUCCESS        = 0,
    FRUC_RESULT_OUTLIER_ERROR  = 1,
    FRUC_RESULT_FATAL_ERROR    = 2,
    NUM_FRUC_RESULT            = 3
  } FRUCResult;

public:
  qtv_FRUC_bcast_class(FRUCResult result);
  virtual ~qtv_FRUC_bcast_class( void );

  #ifdef QTV_BROADCAST_VERBOSE_DIAG

  virtual int Describe( char* const pBuf, const int bufSiz );

  #endif /* QTV_BROADCAST_VERBOSE_DIAG */

  /* decode Status = Tells whether the decode was successful or not.
  */
  const FRUCResult m_result;
};

#endif // QTV_FRUC_BROADCAST_H

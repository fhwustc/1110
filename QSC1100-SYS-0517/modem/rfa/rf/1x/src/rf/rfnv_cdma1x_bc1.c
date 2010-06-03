/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

              1 X   B A N D  C L A S S - 1   R F   N V   M a n a g e r

DESCRIPTION
  This module provides the functions and data to retrieve the 1X BC1 mode RF NV items
  and store them in the local tables.

EXTERNALIZED FUNCTIONS

rfnv_cdma1x_bc1_list_size
  This function returns the size of the RF BC1 mode NV items identifier array.

rfnv_cdma1x_bc1_item_table
  Return a void pointer to the RF BC1 NV items table.

rfnv_cdma1x_bc1_copy_nv_items
  This function copies one RF data item, as specified by "item_code" into a
  local data structure.

Copyright (c) 1997 - 2002      by QUALCOMM, Incorporated.  All Rights Reserved.
Copyright (c) 2003, 2004, 2005 by QUALCOMM, Incorporated.  All Rights Reserved.
Copyright (c) 2006, 2007       by QUALCOMM, Incorporated.  All Rights Reserved.

*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

$Header: //source/qcom/qct/modem/rfa/rf/1x/main/qsc1100/src/rf/rfnv_cdma1x_bc1.c#7 $
$DateTime: 2008/10/01 18:07:35 $
$Author: vboda $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/30/08   vm/vb   Added Support for Band Class Sub Block Implementation
06/11/08   sl      Added support for  NV_BCx_EXP_HDET_VS_AGC_V2_I, NV_BCx_HDET_OFF_V2_I,
                   and NV_BCx_HDET_SPN_V2_I under feature RF_HAS_HDET_UINT16.
04/29/08   sl      ULC: Changed features with ZIF_LIBRARY_SUPPORTS to RF_HAS_SUPPORT_FOR.
04/23/08   sl      Added NV_C0_BCx_LO_CAL_I, NV_C0_BCx_IM2_CAL_I support.
10/27/07   ans     Changed FEATURE_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST name to 
                   RF_HAS_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST.
                   Changed FEATURE_HDR_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST name to 
                   RF_HAS_HDR_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST.
10/26/07   ans     Added FEATURE_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST for backoffs
                   for R2 and R3 PA states..
07/26/07   vm      Added the support for Tx Power Compensation NV based on
                   temperature and Frequency
07/22/07   dyc     Support for BC specific PA_R_MAP 
06/20/07   Vish    Added support for RFCONFIG Rx LNA data structures for
                   primary and secondary chains in digital NV items storage
                   on a per band class basis.
                   Added rfnv_cdma1x_bc1_get_rx_rfconfig_migration_tracker()
                   API for aiding migrating over of LNA switch point rise,
                   fall and IM level NV items to RFConfigDBase.
06/14/07   avi     Added support for selection of DRx switch settings through NV
04/30/07   vm      Added support for New Tx Cal for RF chips with 
                   Tx Compensation registers in RFT
04/23/07   adk     Updated NV read interface for Beta Scaling
03/28/07   adk     Updated NV read interface for Beta Scaling
03/23/07   bmg     Added PA timer hysteresis band config items
02/23/07   adk     Added support for FW TX AGC with Beta Scaling
01/25/07   jfc     Include high level rficap.h instead of rficap_mm_cdma1x.h
10/31/06   ycl     Include the correct rficap file.
11/15/05   sar     Removed incorrect cast from NV_BC1_GPS1_RF_DELAY_I case
                   in rfnv_cdma1x_bc1_copy_nv_items.Also updated for Lint.
10/10/05   dyc     Assign memcpy size for C1 VCO CT array.
07/12/05   bmg     Added NV_C0_BC1_INTELLICEIVER_DET_THRESH_I
07/01/05   sar     Eliminated revert back to legacy bands.
06/08/05   sar     Fixed Lint Error, Warning and Info messages.
06/03/05   dyc     Added RF_HDR_G0_IM_*_DEFAULT_V values.
05/26/05   sar     Mainlined Feature RF_HAS_ANT_SENS.
05/13/05   bmg     IntelliCeiver featurization for OLTA NV
05/12/05   sar     Added support for NV_BC1_ANT_QUALITY_I.
03/31/05   bmg     Added IntelliCeiver NV
                   Replaced redundant code loading RX frequency cal with
                   rfnv_load_dvga_offset_data() & rfnv_load_lna_offset_data()
                   Fixed some IntelliCeiver RFNV items to work with final
                   NV structure                     
02/15/05   dyc     Added support for NV_BC1_PA_DVS_VOLTAGE_I
01/17/05   sar     Added support for NV_BC1_HDR_P1_RISE_FALL_OFF_I.
12/09/04   bmg     Expanded VCO coarse tune 2 to support 16 frequency bins
12/08/04   bmg     Added RX cal channel least-recently-used list support
                   for enhanced automated calibration.
11/15/04   sar     Changed initial values so that hdr olta setting could be set by 
                   rfnv_set_defaults().
11/11/04   sar     Using filler values for olta items since the defaults are 
                   set by rfnv_set_defaults().
10/25/04   bmg     Added VCO coarse tune 2 item
10/14/04   bmg     Removed unused RX linearizer NV items from the RF NV
                   structure.  Converted to the new offset_vs_freq structure.
                   Added power mode support.
10/08/04   sar     Added back the support for RF Card specific items.
09/30/04   sar     Removed references to the RF Card specific items. Removed
                   rfnv_cdma1x_bc1_set_kpcs_defaults
09/16/04   jac     Added routine rfnv_cdma1x_bc1_set_kpcs_defaults() to change
                   the statically initialized structure for non-FEBC builds 
                   for KPCS band.
09/14/04   sar     Added Band Specific default for Tx limit versus temperature.
09/03/04   dbc     Added support for expected TX AGC versus HDET reading table
08/23/04   sar     Replacing references to FEATURE_ENHANCED_BAND_CLASS with
                   RF_HAS_ENHANCED_BAND_CLASS.
07/16/04   sar     Removed unused NV_BC1_RF_TUNE_RESERVED_I from items list.
06/21/04   sar     Added support for rf chain-1 vco coarse tune table.
06/07/04   sar     Updated algorithm for loading Interpolation Coefficients.
05/25/04   sar     added support for legacy cdma & pcs bands.
05/10/04   sar     Added default for HDR IM LEVEL. Added featurization to use
                   old vs. new NV items. Cleaned up some definitions and defaults.
04/26/04   sar     Added default for HDR IM FALL and HDR IM RISE.
                   Adjusted default values for Interpolation coeficients.
04/08/04   sar     Removed RF Tune reserved item.
03/19/04   et      added interpolation (frequency comp) support
03/19/04   sar     Updated file for new NV items.
02/18/04   sar     Added default value for GPS Chain Delay cal parameter.No NV
                   item has been allocated for this band yet.
01/29/04   SAR     Added support for 2nd chain lna rise/fall (1-4 states) and 
                   im_level 1-4. These 2nd chain items are set as: default values
                   if neither primary or secondary NV value is set; same as primary
                   chain NV values if they are defined and the 2nd chain values 
                   are not; their own NV value if they have been defined. 
01/29/04   SAR     Removed obsolete table rfnv_save_bc1_item_lst[];
01/26/03   SAR     Removed support for PA Range Offsets, LNA Bypass and Non-Bypass
                   0-3 timers, DACC I/Q Accumulators and Digital Mismatch Compensation.
12/18/03   SAR     Replaced numerical values with defined constants in the 
                   initializer list for rfnv_cdma1x_bc1_tbl.
12/17/03   SAR     Removed NV_LNA_RANGE_POL_I, NV_VCO_COARSE_TUNE_TABLE_I,
                   and NV_AGC_PHASE_OFFSET_I from the rfnv_cdma1x_bc1_nv_items_list.
11/26/03   SAR     Using a more meaningful name for range declaration in OLTA 
                   arrays in the digital items description. 
11/12/03   dyc     Added support for ch1 OLTA default values.
11/11/03   sar     Wrapped NV_PCS_OLTA_BACKOFF_I with RF_HAS_OLTA_BACKOFFS_IN_NV
                   in rfnv_cdma1x_bc1_nv_items_list.
11/05/03   SAR     Updated defaults per HW/SW Document.
11/05/03   dbc     Only retrieve OLTA backoffs from NV when RF_HAS_OLTA_BACKOFFS_IN_NV
                   is defined
11/03/03   SAR     Added support for OLTA items.
10/31/03   SAR     Fixed the assignment of value for NV_PCS_LNA_BYPASS_TIMER_0_I.
10/28/03   SAR     Added support for NV_PCS_IM_LEVEL3_I and NV_PCS_IM_LEVEL4_I.
                   Also updated the default values for the above items.
10/23/03   SAR     Added support for NV_PCS_LNA_BYPASS_TIMER_0_I.
10/23/03   SAR     Fixed a bug for NV_PCS_LNA_4_OFFSET_VS_FREQ_I, where 
                   indexes were transposed. Included header file rfi.h.
07/29/09   SAR     Initial Revision.
============================================================================*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/
#include "comdef.h"             /* General types and macros                 */
#include "target.h"             /* target configuration                     */
#include "rficap.h"             /* RF band/mode capabilitie                 */
#include "rfi.h"
#include "nv.h"                 /* NV item declarations                     */
#include "rfnv.h"               /* RF NV Manger                             */
#include "cagc.h"               /* CDMA Automatic Gain Control              */
#include "rfnv_cdma1x_bc1.h"    /* BC1 prototypes and definitions           */
#include "err.h"                /* Error handling services                  */
#ifdef RF_HAS_RFCONFIG_RX_LNA
#include "rfconfig_rx_lna.h"
#include "rfnv_rfconfig_migration_tracker.h"
#include "rfnv_rfconfig_migration_util.h"
#endif /* RF_HAS_RFCONFIG_RX_LNA */

#include <memory.h>             /* Memory manipulation                      */


/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=**=

                                 LOCAL DATA

=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=**/
    /* RF BC1 NV items table                                                */
rfnv_items_list_type rfnv_cdma1x_bc1_nv_items_list[] =
{
    /* 
    GPS Chain Delay cal parameter.                                   
    */
    { NV_BC1_GPS1_RF_DELAY_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Tx power limit vs temperature
    */
    { NV_BC1_TX_LIM_VS_TEMP_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },

    /*  
    Tx linearizer with internal PA=00
    */
    { NV_BC1_TX_LIN_MASTER0_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK }, 
    /* 
    Compensation for Tx linz. with internal PA=01
    */
    { NV_BC1_TX_LIN_MASTER1_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Tx linearizer with internal PA=10 
    */
    { NV_BC1_TX_LIN_MASTER2_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Tx linearizer with internal PA=11 
    */
    { NV_BC1_TX_LIN_MASTER3_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },

    /* 
    Compensation for Tx linz. with internal PA=00
    */
    { NV_BC1_TX_COMP0_I,                    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                            
    /*
    Compensation for Tx linz. with internal PA=01
    */
    { NV_BC1_TX_COMP1_I,                    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                            
    /* 
    Compensation for Tx linz 
    */
    { NV_BC1_TX_COMP2_I,                    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Compensation for Tx linz 
    */
    { NV_BC1_TX_COMP3_I,                    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Tx power limit vs frequency
    */
    { NV_BC1_TX_LIM_VS_FREQ_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                      
    /* 
    PA stepup threshold to state 1 
    */  
    { NV_BC1_PA_R1_RISE_I,                  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    PA stepdown threshold to state 0 
    */
    { NV_BC1_PA_R1_FALL_I,                  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    PA stepup threshold to state 2 
    */
    { NV_BC1_PA_R2_RISE_I,                  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    PA stepdown threshold to state 1 
    */
    { NV_BC1_PA_R2_FALL_I,                  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    PA stepup threshold to state 3 
    */
    { NV_BC1_PA_R3_RISE_I,                  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    PA stepdown threshold to state 2 
    */
    { NV_BC1_PA_R3_FALL_I,                  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },

#ifdef RF_HAS_HDET_UINT16
	/* 
    Expected HDET reading vs AGC PDM V2
    */
    { NV_BC1_EXP_HDET_VS_AGC_V2_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
	/*
	ADC HDET reading offset V2
    */
    { NV_BC1_HDET_OFF_V2_I,                    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                            
    /*  
    ADC HDET reading span V2                
    */
    { NV_BC1_HDET_SPN_V2_I,                    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
#else // HDET IS OF UINT8 NOT OF RF_HAS_HDET_UINT16
    /*
    ADC HDET reading offset
    */
    { NV_BC1_HDET_OFF_I,                    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                            
    /*  
    ADC HDET reading span                 
    */
    { NV_BC1_HDET_SPN_I,                    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                            
    /* 
    Expected HDET reading vs AGC PDM
    */
    { NV_BC1_EXP_HDET_VS_AGC_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
#endif // HDET IS OF UINT8

    /* 
    Chipx8 delay through Band Class 6 Tx path
    */
    { NV_BC1_ENC_BTF_I,                     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                             
    /*
    Table of VCO Coarse Tune Values.
    */
    { NV_BC1_VCO_COARSE_TUNE_TABLE_I,       NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_VCO_TUNE_2_I,                  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },

    #ifdef FEATURE_P1_DYNAMIC_PA_SWITCH_POINT_ADJUST    
    /* 
    P1 mode PA Rise/Fall offsets
    */
    { NV_BC1_P1_RISE_FALL_OFF_I,            NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    #endif
    #ifdef FEATURE_HDR_P1_DYNAMIC_PA_SWITCH_POINT_ADJUST
    /* 
    P1 mode PA Rise/Fall offsets
    */
    { NV_BC1_HDR_P1_RISE_FALL_OFF_I,        NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                    
    #endif

#ifdef RF_HAS_LINEAR_INTERPOLATION
    /* 
    Coefficients for Freq comp for Tx 
    */
    { NV_C0_BC1_TX_CAL_CHAN_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Coefficients for Freq comp for Rx 
    */
    { NV_C0_BC1_RX_CAL_CHAN_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },

#ifdef RF_HAS_FTM_V2_CAL_NV
    { NV_C0_BC1_RX_CAL_CHAN_LRU_I,          NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
#endif /* RF_HAS_FTM_V2_CAL_NV */

#endif /* RF_HAS_LINEAR_INTERPOLATION */
    /* 
    Rx chain-0: Offset Value subtracted from IF VGA linearizer table for state 1
    */
    { NV_C0_BC1_LNA_1_OFFSET_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /*  
    Rx chain-0: Offset Value subtracted from IF VGA linearizer table for state 2
    */
    { NV_C0_BC1_LNA_2_OFFSET_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /*  
    Rx chain-0: Offset Value subtracted from IF VGA linearizer table for state 3
    */
    { NV_C0_BC1_LNA_3_OFFSET_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /*  
    Rx chain-0: Offset Value subtracted from IF VGA linearizer table for state 4
    */
    { NV_C0_BC1_LNA_4_OFFSET_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /*
    LNA bypass offset vs. freq. Comp for state 1 
    */
    { NV_C0_BC1_LNA_1_OFFSET_VS_FREQ_I,     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA bypass offset vs. freq. Comp for state 2 
    */
    { NV_C0_BC1_LNA_2_OFFSET_VS_FREQ_I,     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Gain variations of the LNA
    */
    { NV_C0_BC1_LNA_3_OFFSET_VS_FREQ_I,     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /*  
    Gain variations of the LNA when in the 4th gain state.
    */
    { NV_C0_BC1_LNA_4_OFFSET_VS_FREQ_I,     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /*  
    IM2 cal items generated during RF Cal to be loaded into RFR6000
    */
    { NV_C0_BC1_IM2_I_VALUE_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM2 cal items generated during RF Cal to be loaded into RFR6000
    */
    { NV_C0_BC1_IM2_Q_VALUE_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                      
    /*  
    Chain 0 VGA gain offset
    */
    { NV_C0_BC1_VGA_GAIN_OFFSET_I,          NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                  
    /* 
    Chain 0 VGA gain offset variations over the frequencies
    */
    { NV_C0_BC1_VGA_GAIN_OFFSET_VS_FREQ_I,  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },          
    /* 
    Chain 0 IM2 transconductance values.
    */
    { NV_C0_BC1_IM2_TRANSCONDUCTOR_VALUE_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA rise 1 threshold 
    */
    { NV_C0_BC1_LNA_1_RISE_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA fall 1 threshold 
    */
    { NV_C0_BC1_LNA_1_FALL_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA rise 2 threshold 
    */
    { NV_C0_BC1_LNA_2_RISE_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA fall 2 threshold 
    */
    { NV_C0_BC1_LNA_2_FALL_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA rise 3 threshold 
    */
    { NV_C0_BC1_LNA_3_RISE_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA fall 3 threshold 
    */
    { NV_C0_BC1_LNA_3_FALL_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA rise 4 threshold 
    */
    { NV_C0_BC1_LNA_4_RISE_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA fall 4 threshold 
    */
    { NV_C0_BC1_LNA_4_FALL_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM threshold for 2nd stage 
    */
    { NV_C0_BC1_IM_LEVEL1_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM threshold for 3rd stage 
    */
    { NV_C0_BC1_IM_LEVEL2_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM threshold for 4th stage 
    */
    { NV_C0_BC1_IM_LEVEL3_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM threshold for 5th stage 
    */
    { NV_C0_BC1_IM_LEVEL4_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },

#ifdef RF_HAS_LINEAR_INTERPOLATION
    /* 
    Coefficients for Freq comp for Tx 
    */
    { NV_C1_BC1_TX_CAL_CHAN_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Coefficients for Freq comp for Rx 
    */
    { NV_C1_BC1_RX_CAL_CHAN_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },

#ifdef RF_HAS_FTM_V2_CAL_NV
    { NV_C1_BC1_RX_CAL_CHAN_LRU_I,          NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
#endif /* RF_HAS_FTM_V2_CAL_NV */

#endif /* RF_HAS_LINEAR_INTERPOLATION */
    /* 
    Rx chain-1: Offset Value subtracted from IF VGA linearizer table for state 1
    */
    { NV_C1_BC1_LNA_1_OFFSET_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /* 
    Rx chain-1: Offset Value subtracted from IF VGA linearizer table for state 2
    */
    { NV_C1_BC1_LNA_2_OFFSET_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /* 
    Rx chain-1: Offset Value subtracted from IF VGA linearizer table for state 3
    */
    { NV_C1_BC1_LNA_3_OFFSET_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /* 
    Rx chain-1: Offset Value subtracted from IF VGA linearizer table for state 4
    */
    { NV_C1_BC1_LNA_4_OFFSET_I,             NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /* 
    LNA bypass offset vs. freq. Comp for state 1 
    */
    { NV_C1_BC1_LNA_1_OFFSET_VS_FREQ_I,     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA bypass offset vs. freq. Comp for state 2 
    */
    { NV_C1_BC1_LNA_2_OFFSET_VS_FREQ_I,     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    Gain variations of the LNA
    */
    { NV_C1_BC1_LNA_3_OFFSET_VS_FREQ_I,     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /* 
    Gain variations of the LNA when in the 4th gain state.
    */
    { NV_C1_BC1_LNA_4_OFFSET_VS_FREQ_I,     NV_ITEM_ATTRIB_NON_CRTCL_BMSK },             
    /* 
    IM2 cal items generated during RF Cal to be loaded into RFR6000
    */
    { NV_C1_BC1_IM2_I_VALUE_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /*  
    IM2 cal items generated during RF Cal to be loaded into RFR6000
    */
    { NV_C1_BC1_IM2_Q_VALUE_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                      
    /*
    Chain 1 VGA gain offset
    */
    { NV_C1_BC1_VGA_GAIN_OFFSET_I,          NV_ITEM_ATTRIB_NON_CRTCL_BMSK },                  
    /* 
    Chain 1 VGA gain offset variations over the frequencies
    */
    { NV_C1_BC1_VGA_GAIN_OFFSET_VS_FREQ_I,  NV_ITEM_ATTRIB_NON_CRTCL_BMSK },          
    /* 
    Chain 1 IM2 transconductance values.
    */
    { NV_C1_BC1_IM2_TRANSCONDUCTOR_VALUE_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },         
    /* 
    LNA rise 1 threshold 
    */
    { NV_C1_BC1_LNA_1_RISE_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA fall 1 threshold 
    */
    { NV_C1_BC1_LNA_1_FALL_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA rise 2 threshold 
    */
    { NV_C1_BC1_LNA_2_RISE_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA fall 2 threshold 
    */
    { NV_C1_BC1_LNA_2_FALL_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA rise 3 threshold 
    */
    { NV_C1_BC1_LNA_3_RISE_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA fall 3 threshold 
    */
    { NV_C1_BC1_LNA_3_FALL_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA rise 4 threshold 
    */
    { NV_C1_BC1_LNA_4_RISE_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    LNA fall 4 threshold 
    */
    { NV_C1_BC1_LNA_4_FALL_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM threshold for 2nd stage 
    */
    { NV_C1_BC1_IM_LEVEL1_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM threshold for 3rd stage 
    */
    { NV_C1_BC1_IM_LEVEL2_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM threshold for 4th stage 
    */
    { NV_C1_BC1_IM_LEVEL3_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* 
    IM threshold for 5th stage 
    */
    { NV_C1_BC1_IM_LEVEL4_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /*
    Table of VCO Coarse Tune Values.
    */
    { NV_C1_BC1_VCO_COARSE_TUNE_TABLE_I,    NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    
    /*  Reletive Antenna Quality */
    { NV_BC1_ANT_QUALITY_I,                 NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
    
    #ifdef RF_HAS_PA_DVS_NV
    /*
    PA DVS voltage setting (mV) 0 = disabled
    */
    ,
    { NV_BC1_PA_DVS_VOLTAGE_I,              NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
    #endif

    #ifdef RF_HAS_POWER_MODE_LIB
    ,
    /* LNA switchpoints for IntelliCeiver low power modes */
    { NV_C0_BC1_LNA_SWITCHPOINTS_LPM_1_I,   NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_C0_BC1_LNA_SWITCHPOINTS_LPM_2_I,   NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* IM2 calibration for IntelliCeiver low power modes */
    { NV_C0_BC1_IM2_LPM_1_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_C0_BC1_IM2_LPM_2_I,                NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* RFR specific calibration for IntelliCeiver low power modes */
    { NV_C0_BC1_INTELLICEIVER_CAL_I,        NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    /* IntelliCeiver detector threshold adjustments from defaults */
    { NV_C0_BC1_INTELLICEIVER_DET_THRESH_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
    #endif /* RF_HAS_POWER_MODE_LIB */

    #if defined (RF_HAS_BETA_SCALING_TX_AGC) || defined(RF_HAS_PDM_VS_POWER_TX_CAL)    
    ,
    /* PDM values for TX calibration (for PA states 0,1,2,3) */
    { NV_BC1_TX_PDM_0_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_PDM_1_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_PDM_2_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_PDM_3_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },

    /* Measured TX power for above PDM values (for PA states 0,1,2,3) */
    { NV_BC1_TX_LIN_0_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_LIN_1_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_LIN_2_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_LIN_3_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
    #endif
    #ifdef RF_HAS_HW_DZRF6285
#error code not present
    #endif // RF_HAS_HW_DZRF6285 

    /* Band Specific PA_R_MAP value */
    ,
    {NV_BC1_PA_R_MAP_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
    #ifdef RF_HAS_TX_TEMP_FREQ_COMP_NV_BASED_ON_PWR
    ,
    { NV_BC1_TX_PWR_COMP0_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_PWR_COMP1_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_PWR_COMP2_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK },
    { NV_BC1_TX_PWR_COMP3_I, NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
    #endif
    #ifdef RF_HAS_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST    /*
    Adjustments to 1X PA rise and fall values during P2/P3 data calls in HDR mode.
    */
    ,
    { NV_BC1_P2_RISE_FALL_OFF_I,        NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
    ,
    { NV_BC1_P3_RISE_FALL_OFF_I,        NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
    #endif /* RF_HAS_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST */

    #ifdef RF_HAS_HDR_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST    
#error code not present
    #endif /* RF_HAS_HDR_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST */

#ifdef RF_HAS_SUPPORT_FOR_LO_PWC_CAL
    /* LO Cal Items.*/
    ,{ NV_C0_BC1_LO_CAL_I,                 	NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
#endif //RF_HAS_SUPPORT_FOR_LO_PWC_CAL

#ifdef RF_HAS_SUPPORT_FOR_LO_IM2_CAL
    /* IM2 Cal Items.*/
    ,{ NV_C0_BC1_IM2_CAL_I,                 NV_ITEM_ATTRIB_NON_CRTCL_BMSK }
#endif //RF_HAS_SUPPORT_FOR_LO_IM2_CAL

#ifdef RF_HAS_SUB_BLOCK_SUPPORT
/*
	Block Mask value for Parent Band class
    */
   ,{ NV_BC1_SUBCLASS_MASK_I,               NV_ITEM_ATTRIB_NON_CRTCL_BMSK }  
#endif

};/* RF BC1 NV items table */

/* -----------------------------------------------------------------------
** Mandatory NV items regardless of RF mode
** ----------------------------------------------------------------------- */


/* -----------------------------------------------------------------------
** Digital (CDMA/BC1) NV calibration tables.  Initially contains default
** values.  If these items are not read from NV, the default values are
** used.
** ----------------------------------------------------------------------- */
/* Initialise the BC1 table to the same values as that in the
** Cellular CDMA table.
*/

rfnv_digital_items_type rfnv_cdma1x_bc1_tbl =
{
    /* self id */
    #ifdef RF_HAS_BC1_NV_TABLE
    RF_BAND_CLASS_1,
    #else 
    RF_BAND_CLASS_MAX,
    #endif

    /* Holds either the base VREF value, or the difference between
     the base and switched values
    */
    RF_RX_AGC_VREF_VAL_V,
    
    /* Tx gain compensation versus frequency
    */
    RF_TX_COMP_VS_FREQ_V,

    #if defined (RF_HAS_BETA_SCALING_TX_AGC) || defined(RF_HAS_PDM_VS_POWER_TX_CAL)
    
    /* Here Beta Scaling is enabled */

    /* Default PDM values (for PA states 0,1,2,3) */
    RF_TX_CDMA_PDM_TBL_V,
    /* Default TX power for the PDM values (above) */
    RF_TX_CDMA_LIN_TBL_V,

    #endif    /* Here Beta Scaling is not enabled */
    
    /* CDMA Tx linearizer master offset 
    */
    RF_TX_LIN_MASTER_OFF_V,

    /* Tx linearizer with internal PA=00 
    */
    RF_TX_LIN_MASTER0_V,

    /* Tx linearizer with internal PA=01 
    */
    RF_TX_LIN_MASTER1_V,
  
    /* Tx linearizer with internal PA=10 
    */
    RF_TX_LIN_MASTER2_V,
  
    /* Tx linearizer with internal PA=11 
    */
    RF_TX_LIN_MASTER3_V,
    

    /* CDMA Tx linearizer versus temperature
    */
    RF_TX_LIN_VS_TEMP_V,
    
    /* CDMA Tx slope versus temperature
    */
    RF_TX_SLP_VS_TEMP_V,
    
    /* CDMA Tx limit versus temperature
    */
    RF_BC1_TX_LIM_VS_TEMP_V,
    
    /* CDMA Tx limit versus frequency
    */
    RF_TX_LIM_VS_FREQ_V,

#ifdef RF_HAS_HDET_UINT16

	/* CDMA expected HDET versus AGC V2
    */
    RF_EXP_HDET_VS_AGC_V2_V,

#else // HDET IS OF UINT8 NOT OF RF_HAS_HDET_UINT16

    /* CDMA expected HDET versus AGC
    */
    RF_EXP_HDET_VS_AGC_V,

#endif // HDET IS OF UINT8

    /* TX AGC VS HDET table */
    RF_EXP_TX_AGC_VS_HDET_V,

#ifdef RF_HAS_HDET_UINT16

    /* ADC HDET reading offset V2
    */
    RF_HDET_OFF_V2_V,

	/* ADC HDET reading span V2
    */
    RF_HDET_SPN_V2_V,
#else // HDET IS OF UINT8 NOT OF RF_HAS_HDET_UINT16

    /* ADC HDET reading offset
    */
    RF_HDET_OFF_V,
    
    /* ADC HDET reading span
    */
    RF_HDET_SPN_V,

#endif // HDET IS OF UINT8
   
    /* LNA range rise value
    */
    BC1_LNA_RANGE_1_RISE_V,
    
    /* LNA range fall value
    */
    BC1_LNA_RANGE_1_FALL_V,
    
    /* LNA range offset
    */
    BC1_LNA_RANGE_1_OFFSET_V,
    
    /* 2nd LNA range rise value
    */
    BC1_LNA_RANGE_2_RISE_V,    /* 0xE1 */
    
    /* 2nd LNA range fall value
    */
    BC1_LNA_RANGE_2_FALL_V,    /* 0xDE */
    
    /* 2nd LNA range offset
    */
    BC1_LNA_RANGE_2_OFFSET_V,
    
    /* 3rd LNA range rise value
    */
    BC1_LNA_RANGE_3_RISE_V,  /* 0x2A */
    
    /* 3rd LNA range fall value
    */
    BC1_LNA_RANGE_3_FALL_V,   /* 0x20 */
    
    /* 3rd LNA range offset
    */
    BC1_LNA_RANGE_3_OFFSET_V,
    
    /* 4th LNA range rise value
    */
    BC1_LNA_RANGE_4_RISE_V,  /* 0x39 */
    
    /* 4th LNA range fall value
    */
    BC1_LNA_RANGE_4_FALL_V,  /* 0x2F */
    
    /* 4th LNA bypass range offset
    */
    BC1_LNA_RANGE_4_OFFSET_V,
    
    /* Intermod Level 1
    */
    BC1_IM_LEVEL1_V,
    
    /* Intermod Level 2
    */
    BC1_IM_LEVEL2_V,
    
    /* Intermod Level 3
    */
    BC1_IM_LEVEL3_V,
    
    /* Intermod Level 4
    */
    BC1_IM_LEVEL4_V,
    
    /* LNA non-bypass hold timer - 7:5 register mapping
    */
    BC1_NONBYPASS_TIMER_V,
    
    /* LNA bypass hold timer - 4:0 register mapping
    */
    BC1_BYPASS_TIMER_V,
    
    /* 1st LNA bypass range offset vs. frequency compensation
    */
    RF_LNA_1_OFFSET_VS_FREQ_V,
    
    /* 2nd LNA bypass range offset vs. frequency compensation
    */
    RF_LNA_2_OFFSET_VS_FREQ_V,
    
    /* 3rd LNA bypass range offset vs. frequency compensation
    */
    RF_LNA_3_OFFSET_VS_FREQ_V,
    
    /* 4th LNA bypass range offset vs. frequency compensation
    */
    RF_LNA_4_OFFSET_VS_FREQ_V,
    
    /* Phase rotation settings
    */
    RF_AGC_PHASE_OFFSET_V,
    
    /* LNA range polarity
    */
    RF_LNA_RANGE_POL_V,
    
    /* Mixer range polarity
    */
    RF_MIXER_RANGE_POL_V, 
    
    /* LNA range delay time from CAGC to RX Front
    */
    RF_LNA_RANGE_DELAY_V,
    
    /* CDMA Tx limiter loop gain, scaled by RF_CDMA_TX_LIM_ADJ_SCALE.
    */
    RF_TX_LIM_ADJ_GAIN_V,
    
    /* PA_R1 rise value
    **   decimal value = 255 - (desired power + 52)*3
    */
    RF_R1_RISE_V,    /* approximately 11dBm */
    
    /* PA_R1 fall value
    */
    RF_R1_FALL_V,    /* approximately 6dBm */
    
    /* PA_R2 rise value
    */
    RF_R2_RISE_V,    /* disabled             */
    
    /* PA_R2 fall value
    */
    RF_R2_FALL_V,    /* disabled             */
    
    /* PA_R3 rise value
    */
    RF_R3_RISE_V,    /* disabled             */
    
    /* PA_R3 fall value
    */
    RF_R3_FALL_V     /* disabled             */
    
    #ifdef FEATURE_P1_DYNAMIC_PA_SWITCH_POINT_ADJUST
    ,RF_P1_PA_RISE_FALL_OFF_V
    #endif
    #ifdef FEATURE_HDR_P1_DYNAMIC_PA_SWITCH_POINT_ADJUST
    ,RF_HDR_P1_PA_RISE_FALL_OFF_V
    #endif
    
    , BC1_ENC_BTF_DLY_V
    
    #ifdef FEATURE_TX_POWER_BACK_OFF
    // NV_PWR_BACKOFF_VS_VOLT_MED_I
    /********************************************************************************
    *                                                                               *
    *  N.B. BEGINNING OF EXPLANATORY COMMENT:                                       *
    *                                                                               *
    *    From this comment to the comment containing the phrase,                    *
    *                                                                               *
    *        "N.B. END OF EXPLANATORY COMMENT."                                     *
    *                                                                               *
    *    are tables that will map bijectively to case statements in RF_PA_BACKOFF.C.*
    *    These tables specify the backoff in the maximum power for a specific       *
    *    CELLULAR BAND channel configuration.                                       *
    *                                                                               *
    *    The structure of these tables tracks enumeration type                      *
    *                                                                               *
    *        rfnv_backoff_chan_config_type                                          *
    *                                                                               *
    *    and contains backoff values in dB, scaled 3.                               *
    *                                                                               *
    *    The values here are for reference only and DO NOT necessarily refer        *
    *    to any valid channel configuration!                                        *
    *                                                                               *
    *    Please see the sections in RF_PA_BACKOFF.C preceded by the phrase          *
    *                                                                               *
    *        "N.B. BEGINNING OF EXPLANATORY COMMENT:"                               *
    *                                                                               *
    *    for the case statements corresponding to these data.                       *
    *                                                                               *
    *     *********************************************************************     *
    *     *   Please be aware that these data do not necessarily correspond to*     *
    *     *   any real backoff values!                                        *     *
    *     *                                                                   *     *
    *     *   Each phone manufacturer must generate its own calibration values*     *
    *     *   and store them in non-volatile memory!                          *     *
    *     *********************************************************************     *
    *                                                                               *
    *********************************************************************************/
    
    #define ONE_PT_0         (1<<3)
    #define ZERO_PT_5        (4)
    #define ONE_PT_5         (ONE_PT_0 + ZERO_PT_5   )
    #define TWO_PT_0         (ONE_PT_0 + ONE_PT_0    )
    #define THREE_PT_0       (ONE_PT_0 + TWO_PT_0    )
    #define MAX_PA_BACKOFF   (THREE_PT_0             )
    ,{
     0        ,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5,
     ZERO_PT_5
    },
    //NV_PWR_BACKOFF_VS_VOLT_LOW_I
    {
      0       ,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5,
      ONE_PT_5
    },
    
    /*********************************************************************************
    *                                                                                 *
    *  N.B. END OF EXPLANATORY COMMENT.                                               *
    *                                                                                 *
    *                                                                                 *
    **********************************************************************************/
    
    // NV_PA_BACKOFF_VOLTS_I
    // Units = volts*10
    RF_PA_BACKOFF_CAL_VOLTS_V,
    // NV_VBATT_MIN_MAX_I
    // Units = volts*10
    // Range must be >= NV_PA_BACKOFF_VOLTS_I
    // Lower must be <= NV_PA_BACKOFF_VOLTS_I  low
    // Higher must be >= NV_PA_BACKOFF_VOLTS_I  higher
    BC1_VBATT_CAL_VOLTS_V
    #endif
    ,
    /* RxFront Digital items */
    
    /* rfnv_grp_delay_adj    */
    RF_GRP_DELAY_ADJ_V,
    
    /*  vga_gain_offset
    */
    RF_VGA_GAIN_OFFSET_V,
    
    /*  vga_gain_offset_vs_freq
    */
    RF_VGA_GAIN_OFFSET_VS_FREQ_V,
    
    /*  vga_gain_offset_vs_temp
    */
    RF_VGA_GAIN_OFFSET_VS_TEMP_V,
    
    /*  dacc_iaccum0
    */
    RF_DACC_IACCUM0_V,
    
    /*  dacc_iaccum1
    */
    RF_DACC_IACCUM1_V,
    
    /*  dacc_iaccum2
    */
    RF_DACC_IACCUM2_V,
    
    /*  dacc_iaccum3
    */
    RF_DACC_IACCUM3_V,
    
    /*  dacc_iaccum4
    */
    RF_DACC_IACCUM4_V,
    
    /*  dacc_qaccum0
    */
    RF_DACC_QACCUM0_V,
    
    /*  dacc_qaccum1
    */
    RF_DACC_QACCUM1_V,
    
    /*  dacc_qaccum2
    */
    RF_DACC_QACCUM2_V,
    
    /*  dacc_qaccum3
    */
    RF_DACC_QACCUM3_V,
    
    /*  dacc_qaccum4
    */
    RF_DACC_QACCUM4_V,
    
    /*  im2_i_value
    */
    RF_IM2_I_VALUE_V,
    
    /*  im2_q_value
    */
    RF_IM2_Q_VALUE_V,
    
    /*  im2_transconductor_value
    */
    RF_IM2_TRANSCONDUCTOR_VALUE_V,
    
#ifndef RF_HAS_RFCONFIG_RX_LNA
    /* cell olta_backoff */
    RF_OLTA_FILLER_V,
    
    /* hdr olta_backoff  */
    RF_OLTA_FILLER_V,
#endif /* !RF_HAS_RFCONFIG_RX_LNA */
    
    /* Coefficients used in interpolation of Frequency Compensation 
     Values for Rx and Tx 
     */
#ifdef RF_HAS_LINEAR_INTERPOLATION
    RF_CAL_CHAN_FILLER_V,
    RF_CAL_CHAN_FILLER_V,
    
    /* RX Cal channel least recently used list */
    RF_RX_CAL_CHAN_LRU_V,
#endif    

    /* The GPS Chain Delay cal. parameter. */
    RF_GPS_CHAIN_DELAY_V,
        
    /* Adjustment factor */
    RF_ADJ_FACTOR_V,

    /* default VCO coarse tune table 
    */
    RF_DEFAULT_VCO_COARSE_TUNE_TABLE,

    RF_DEFAULT_VCO_COARSE_TUNE_2,

    /*
    Fall setting for HDR IM 
    */
    RF_BC1_HDR_IM_FALL,

    /* 
    Rise settings for HDR IM
    */
    RF_BC1_HDR_IM_RISE,

    /*
    Im level for HDR
    */
    RF_BC1_HDR_IM_LEVEL,

    /* HDR G0 IM Fall, Rise and Level settings 
    *  Band specific settings can be assigned 
    *  with band specific definitions
    */
    RF_HDR_G0_IM_FALL_DEFAULT_V,
    RF_HDR_G0_IM_RISE_DEFAULT_V,
    RF_HDR_G0_IM_LEVEL_DEFAULT_V,

#ifdef RF_HAS_PA_DVS_NV
    /*
    PA DVS Voltage setting (mV)  0 = PA DVS disabled 
    */
    PA_DVS_DISABLE_V,
#endif

    /* Intelliceiver Calibration values */
    RF_INTELLICEIVER_CAL_V,

    /*
    RF Antenna Sensitivity
    */
    RF_BC1_ANT_QUALITY_TBL,

    /* IntelliCeiver detector threshold adjustment */
    RF_INTELLICEIVER_DETECTOR_ADJUST_V,

    /* Default 1x PA hysteresis timer */
    RF_1X_PA_R_TIMER_V,

    /* Default 1xEV-DO PA hysteresis timer */
    RF_1XEV_DO_PA_R_TIMER_V,

    #ifdef RF_HAS_RFCONFIG_RX_LNA
       #ifdef RF_HAS_MULTI_RX_CHAIN
    /* default RFCONFIG RX_LNA_CONFIG data structures for primary and secondary LNAs */
    { RFCONFIG_RX_LNA_RESET_VAL, RFCONFIG_RX_LNA_RESET_VAL },
       #else /* RF_HAS_MULTI_RX_CHAIN */
    /* default RFCONFIG RX_LNA_CONFIG data structures for the only (primary) LNA */
    { RFCONFIG_RX_LNA_RESET_VAL },
       #endif /* RF_HAS_MULTI_RX_CHAIN */
    #endif /* RF_HAS_RFCONFIG_RX_LNA */

	#ifdef RF_HAS_HW_DZRF6285
#error code not present
	#endif // RF_HAS_HW_DZRF6285 

    /* Band class specific PA_R_MAP */
    RF_BC_PA_R_MAP_V
    #ifdef RF_HAS_TX_TEMP_FREQ_COMP_NV_BASED_ON_PWR
    /*Tx Power Compensation based on frequency and temperature*/
    ,RF_TEMP_FREQ_BASED_TX_PWR_COMP_V
    #endif      
    #ifdef RF_HAS_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST
    , RF_P2_PA_RISE_FALL_OFF_V
    , RF_P3_PA_RISE_FALL_OFF_V
    #endif

    #ifdef RF_HAS_HDR_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST    
#error code not present
    #endif

#ifdef RF_HAS_SUPPORT_FOR_LO_PWC_CAL
    /* LO Cal Items.*/
    ,RF_LO_CAL_DEFAULT_V
#endif //RF_HAS_SUPPORT_FOR_LO_PWC_CAL

#ifdef RF_HAS_SUPPORT_FOR_LO_IM2_CAL
    /* IM2 Cal Items.*/
    ,RF_IM2_CAL_DEFAULT_V
#endif //RF_HAS_SUPPORT_FOR_LO_IM2_CAL
#ifdef RF_HAS_SUB_BLOCK_SUPPORT
    , RF_BLOCK_MASK_DEFAULT_VALUE
    , NULL//RF_BLOCK_DIGITAL_ITEM_PTR_DEFAULT_VALUE
#endif
};/* rfnv_cdma1x_bcx_tbl defaults */

#ifdef RF_HAS_RFCONFIG_RX_LNA
static rfnv_rfconfig_migration_tracker_type  rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_NUM]
 = {
      RFNV_RFCONFIG_MIGRATION_TRACKER_RESET_VAL_INITIALIZER,
      RFNV_RFCONFIG_MIGRATION_TRACKER_RESET_VAL_INITIALIZER
};
static rfnv_rfconfig_migration_util_map_type  rfnv_cdma1x_bc1_rfconfig_migration_util_map_array[]
 = {
      // Primary Rx chain items
      { NV_C0_BC1_LNA_1_RISE_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA1_RISE,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_LNA_2_RISE_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA2_RISE,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_LNA_3_RISE_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA3_RISE,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_LNA_4_RISE_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA4_RISE,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_LNA_1_FALL_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA1_FALL,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_LNA_2_FALL_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA2_FALL,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_LNA_3_FALL_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA3_FALL,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_LNA_4_FALL_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA4_FALL,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_IM_LEVEL1_I,               RFNV_RFCONFIG_MIGRATION_ITEM__LNA1_IM_LEVEL,           &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_IM_LEVEL2_I,               RFNV_RFCONFIG_MIGRATION_ITEM__LNA2_IM_LEVEL,           &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_IM_LEVEL3_I,               RFNV_RFCONFIG_MIGRATION_ITEM__LNA3_IM_LEVEL,           &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_IM_LEVEL4_I,               RFNV_RFCONFIG_MIGRATION_ITEM__LNA4_IM_LEVEL,           &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
#ifdef RF_HAS_POWER_MODE_LIB
      { NV_C0_BC1_LNA_SWITCHPOINTS_LPM_1_I,  RFNV_RFCONFIG_MIGRATION_ITEM__LNA_SWITCH_POINTS_LPM_1, &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
      { NV_C0_BC1_LNA_SWITCHPOINTS_LPM_2_I,  RFNV_RFCONFIG_MIGRATION_ITEM__LNA_SWITCH_POINTS_LPM_2, &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_0] },
#endif /* RF_HAS_POWER_MODE_LIB */

      // Secondary Rx chain items
      { NV_C1_BC1_LNA_1_RISE_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA1_RISE,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_LNA_2_RISE_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA2_RISE,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_LNA_3_RISE_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA3_RISE,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_LNA_4_RISE_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA4_RISE,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_LNA_1_FALL_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA1_FALL,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_LNA_2_FALL_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA2_FALL,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_LNA_3_FALL_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA3_FALL,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_LNA_4_FALL_I,              RFNV_RFCONFIG_MIGRATION_ITEM__LNA4_FALL,               &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_IM_LEVEL1_I,               RFNV_RFCONFIG_MIGRATION_ITEM__LNA1_IM_LEVEL,           &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_IM_LEVEL2_I,               RFNV_RFCONFIG_MIGRATION_ITEM__LNA2_IM_LEVEL,           &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_IM_LEVEL3_I,               RFNV_RFCONFIG_MIGRATION_ITEM__LNA3_IM_LEVEL,           &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },
      { NV_C1_BC1_IM_LEVEL4_I,               RFNV_RFCONFIG_MIGRATION_ITEM__LNA4_IM_LEVEL,           &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[RF_PATH_1] },

      // ensure at least one element is present
      { NV_MAX_I,                            RFNV_RFCONFIG_MIGRATION_ITEM__COUNT,                   NULL }
   };
#endif /* RF_HAS_RFCONFIG_RX_LNA */


/* -----------------------------------------------------------------------

                               FUNCTIONS

** ----------------------------------------------------------------------- */

/*===========================================================================

FUNCTION RFNV_CDMA1X_BC1_COPY_NV_ITEM              EXTERNALIZED FUNCTION

DESCRIPTION
  This function copies one RF data item, as specified by "item_code" into a
  local data structure.  This function must be called during initialization
  for each and every RF NV item.

DEPENDENCIES
  Note that there must NOT be a dependency on the read order of the NV
  calibration items.

RETURN VALUE
  None

SIDE EFFECTS
  None

===========================================================================*/
void rfnv_cdma1x_bc1_copy_nv_items
(
  nv_items_enum_type  item_code,    /* Item to put */
  nv_item_type        *item_ptr     /* Pointer where to get the item */
)
{
  word loop_ctr;                    /* Loop Counter */
  int rx_freq_offset_array_length;
  uint32 ct_table_size;             /* These variables used to determine */
  uint32 nv_table_size;             /*  array size of VCO CT table.      */
  uint32 rfnv_vco_array_size;       /*                                   */

#ifdef RF_HAS_POWER_MODE_LIB
  rx_freq_offset_array_length = NV_RF_POWER_MODE_SIZ * NV_FREQ_TABLE_SIZ;
#else
  rx_freq_offset_array_length = NV_FREQ_TABLE_SIZ;
#endif /* RF_HAS_POWER_MODE_LIB */

  /* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
  /* Make sure the NULL pointer condition does not exist */
  RF_ASSERT(item_ptr!=NULL);

  /*lint -save -e613 */

  switch (item_code) {

  case NV_BC1_GPS1_RF_DELAY_I:              
      rfnv_cdma1x_bc1_tbl.rfnv_gps1_rf_delay = item_ptr->bc1_gps1_rf_delay;
      break;
  
  case  NV_BC1_TX_LIM_VS_TEMP_I:             
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lim_vs_temp[loop_ctr]
          = (int2)item_ptr->bc1_tx_lim_vs_temp[loop_ctr]
            + RF_BC1_TX_LIM_OFFSET;
      }
      break;


  case  NV_BC1_TX_LIN_MASTER0_I:             
      rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[0][0]
        = (int2)item_ptr->bc1_tx_lin_master0.offset;

      for (loop_ctr=0; loop_ctr < (NV_CDMA_TX_LIN_MASTER_SIZ-1); loop_ctr++)
         {
          rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[0][loop_ctr+1]
            = rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[0][loop_ctr]
              + (word)item_ptr->bc1_tx_lin_master0.slope[loop_ctr];
         }
      break;

  case  NV_BC1_TX_LIN_MASTER1_I:             
      rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[1][0]
        = (int2)item_ptr->bc1_tx_lin_master1.offset;

      for (loop_ctr=0; loop_ctr < (NV_CDMA_TX_LIN_MASTER_SIZ-1); loop_ctr++)
         {
          rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[1][loop_ctr+1]
            = rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[1][loop_ctr]
              + (word)item_ptr->bc1_tx_lin_master1.slope[loop_ctr];
         }
      break;

  case  NV_BC1_TX_LIN_MASTER2_I:             
      rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[2][0]
        = (int2)item_ptr->bc1_tx_lin_master2.offset;

      for (loop_ctr=0; loop_ctr < (NV_CDMA_TX_LIN_MASTER_SIZ-1); loop_ctr++)
         {
          rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[2][loop_ctr+1]
            = rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[2][loop_ctr]
              + (word)item_ptr->bc1_tx_lin_master2.slope[loop_ctr];
         }
      break;

  case  NV_BC1_TX_LIN_MASTER3_I:             
      rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[3][0]
        = (int2)item_ptr->bc1_tx_lin_master3.offset;

      for (loop_ctr=0; loop_ctr < (NV_CDMA_TX_LIN_MASTER_SIZ-1); loop_ctr++)
         {
          rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[3][loop_ctr+1]
            = rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_master_off[3][loop_ctr]
              + (word)item_ptr->bc1_tx_lin_master3.slope[loop_ctr];
         }
      break;


#if defined (RF_HAS_BETA_SCALING_TX_AGC) || defined(RF_HAS_PDM_VS_POWER_TX_CAL)
/* Here Beta Scaling is enabled */

    case NV_BC1_TX_PDM_0_I:
      for (loop_ctr = 0; loop_ctr < NV_CDMA_TX_PDM_LIN_TYPE; loop_ctr++)
      {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_pdm_tbl[0][loop_ctr] =
                                         item_ptr->bc1_tx_pdm_0 [loop_ctr];
      }
      break;

    case NV_BC1_TX_PDM_1_I:
      for (loop_ctr = 0; loop_ctr < NV_CDMA_TX_PDM_LIN_TYPE; loop_ctr++)
      {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_pdm_tbl[1][loop_ctr] =
                                         item_ptr->bc1_tx_pdm_1 [loop_ctr];
      }
      break;

    case NV_BC1_TX_PDM_2_I:
      for (loop_ctr = 0; loop_ctr < NV_CDMA_TX_PDM_LIN_TYPE; loop_ctr++)
      {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_pdm_tbl[2][loop_ctr] =
                                         item_ptr->bc1_tx_pdm_2 [loop_ctr];
      }
      break;

    case NV_BC1_TX_PDM_3_I:
      for (loop_ctr = 0; loop_ctr < NV_CDMA_TX_PDM_LIN_TYPE; loop_ctr++)
      {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_pdm_tbl[3][loop_ctr] =
                                         item_ptr->bc1_tx_pdm_3 [loop_ctr];
      }
      break;

    case NV_BC1_TX_LIN_0_I:
      for (loop_ctr = 0; loop_ctr < NV_CDMA_TX_PDM_LIN_TYPE; loop_ctr++)
      {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_tbl[0][loop_ctr] =
                                         item_ptr->bc1_tx_lin_0 [loop_ctr];
      }
      break;

    case NV_BC1_TX_LIN_1_I:
      for (loop_ctr = 0; loop_ctr < NV_CDMA_TX_PDM_LIN_TYPE; loop_ctr++)
      {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_tbl[1][loop_ctr] =
                                         item_ptr->bc1_tx_lin_1 [loop_ctr];
      }
      break;

    case NV_BC1_TX_LIN_2_I:
      for (loop_ctr = 0; loop_ctr < NV_CDMA_TX_PDM_LIN_TYPE; loop_ctr++)
      {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_tbl[2][loop_ctr] =
                                         item_ptr->bc1_tx_lin_2 [loop_ctr];
      }
      break;

    case NV_BC1_TX_LIN_3_I:
      for (loop_ctr = 0; loop_ctr < NV_CDMA_TX_PDM_LIN_TYPE; loop_ctr++)
      {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_tbl[3][loop_ctr] =
                                         item_ptr->bc1_tx_lin_3 [loop_ctr];
      }
      break;

#endif  /* RF_HAS_BETA_SCALING_TX_AGC */

#ifdef RF_HAS_TX_TEMP_FREQ_COMP_NV_BASED_ON_PWR
    case  NV_BC1_TX_PWR_COMP0_I:
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[0].rfnv_tx_comp_lin_vs_temp[loop_ctr]
          = (int2)( item_ptr->bc1_tx_pwr_comp0.nv_tx_pwr_comp_lin_vs_temp[loop_ctr] );
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[0].rfnv_tx_comp_slp_vs_temp[loop_ctr]
          = (int2)( item_ptr->bc1_tx_pwr_comp0.nv_tx_pwr_comp_slp_vs_temp[loop_ctr] );
      }
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[0].rfnv_tx_pwr_comp_vs_freq[loop_ctr]
          = item_ptr->bc1_tx_pwr_comp0.nv_tx_pwr_comp_vs_freq[loop_ctr];
      }
      break;

    case  NV_BC1_TX_PWR_COMP1_I:
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[1].rfnv_tx_comp_lin_vs_temp[loop_ctr]
          = (int2)( item_ptr->bc1_tx_pwr_comp1.nv_tx_pwr_comp_lin_vs_temp[loop_ctr] );
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[1].rfnv_tx_comp_slp_vs_temp[loop_ctr]
          = (int2)( item_ptr->bc1_tx_pwr_comp1.nv_tx_pwr_comp_slp_vs_temp[loop_ctr] );
      }
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[1].rfnv_tx_pwr_comp_vs_freq[loop_ctr]
          = item_ptr->bc1_tx_pwr_comp1.nv_tx_pwr_comp_vs_freq[loop_ctr];
      }
      break;

    case  NV_BC1_TX_PWR_COMP2_I:
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[2].rfnv_tx_comp_lin_vs_temp[loop_ctr]
          = (int2)( item_ptr->bc1_tx_pwr_comp2.nv_tx_pwr_comp_lin_vs_temp[loop_ctr] );
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[2].rfnv_tx_comp_slp_vs_temp[loop_ctr]
          = (int2)( item_ptr->bc1_tx_pwr_comp2.nv_tx_pwr_comp_slp_vs_temp[loop_ctr] );
      }
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[2].rfnv_tx_pwr_comp_vs_freq[loop_ctr]
          = item_ptr->bc1_tx_pwr_comp2.nv_tx_pwr_comp_vs_freq[loop_ctr];
      }
      break;

    case  NV_BC1_TX_PWR_COMP3_I:
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[3].rfnv_tx_comp_lin_vs_temp[loop_ctr]
          = (int2)( item_ptr->bc1_tx_pwr_comp3.nv_tx_pwr_comp_lin_vs_temp[loop_ctr] );
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[3].rfnv_tx_comp_slp_vs_temp[loop_ctr]
          = (int2)( item_ptr->bc1_tx_pwr_comp3.nv_tx_pwr_comp_slp_vs_temp[loop_ctr] );
      }
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_power_comp[3].rfnv_tx_pwr_comp_vs_freq[loop_ctr]
          = item_ptr->bc1_tx_pwr_comp3.nv_tx_pwr_comp_vs_freq[loop_ctr];
      }
      break;
#endif

  case  NV_BC1_TX_COMP0_I:                   
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_vs_temp[0][loop_ctr]
          = (int2)( item_ptr->bc1_tx_comp0.nv_cdma_tx_lin_vs_temp[loop_ctr] );
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_slp_vs_temp[0][loop_ctr]
          = (int2)( item_ptr->bc1_tx_comp0.nv_cdma_tx_slp_vs_temp[loop_ctr] );
      }
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_comp_vs_freq[0][loop_ctr]
          = item_ptr->bc1_tx_comp0.nv_cdma_tx_comp_vs_freq[loop_ctr];
      }
      break;

  case  NV_BC1_TX_COMP1_I:                   
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_vs_temp[1][loop_ctr]
          = (int2)( item_ptr->bc1_tx_comp1.nv_cdma_tx_lin_vs_temp[loop_ctr] );
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_slp_vs_temp[1][loop_ctr]
          = (int2)( item_ptr->bc1_tx_comp1.nv_cdma_tx_slp_vs_temp[loop_ctr] );
      }
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_comp_vs_freq[1][loop_ctr]
          = item_ptr->bc1_tx_comp1.nv_cdma_tx_comp_vs_freq[loop_ctr];
      }
      break;

  case NV_BC1_TX_COMP2_I:
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_vs_temp[2][loop_ctr]
          = (int2)( item_ptr->bc1_tx_comp2.nv_cdma_tx_lin_vs_temp[loop_ctr] );
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_slp_vs_temp[2][loop_ctr]
          = (int2)( item_ptr->bc1_tx_comp2.nv_cdma_tx_slp_vs_temp[loop_ctr] );
      }
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_comp_vs_freq[2][loop_ctr]
          = item_ptr->bc1_tx_comp2.nv_cdma_tx_comp_vs_freq[loop_ctr];
      }
      break;

  case NV_BC1_TX_COMP3_I:
      for (loop_ctr=0; loop_ctr < NV_TEMP_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lin_vs_temp[3][loop_ctr]
          = (int2)( item_ptr->bc1_tx_comp3.nv_cdma_tx_lin_vs_temp[loop_ctr] );
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_slp_vs_temp[3][loop_ctr]
          = (int2)( item_ptr->bc1_tx_comp3.nv_cdma_tx_slp_vs_temp[loop_ctr] );
      }
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_comp_vs_freq[3][loop_ctr]
          = item_ptr->bc1_tx_comp3.nv_cdma_tx_comp_vs_freq[loop_ctr];
      }
      break;

  case  NV_BC1_TX_LIM_VS_FREQ_I:             
      (void)memcpy( rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lim_vs_freq,
                    (void *)item_ptr->bc1_tx_lim_vs_freq,
                    sizeof(rfnv_cdma1x_bc1_tbl.rfnv_cdma_tx_lim_vs_freq) );
      break;
  
  case  NV_BC1_PA_R1_RISE_I:                    
      rfnv_cdma1x_bc1_tbl.rfnv_r1_rise = item_ptr->bc1_pa_r1_rise;
      break;

  case  NV_BC1_PA_R1_FALL_I:                    
      rfnv_cdma1x_bc1_tbl.rfnv_r1_fall = item_ptr->bc1_pa_r1_fall;
      break;

  case NV_BC1_PA_R2_RISE_I:
      rfnv_cdma1x_bc1_tbl.rfnv_r2_rise = item_ptr->bc1_pa_r2_rise;
      break;

  case NV_BC1_PA_R2_FALL_I:
      rfnv_cdma1x_bc1_tbl.rfnv_r2_fall = item_ptr->bc1_pa_r2_fall;
    break;

  case NV_BC1_PA_R3_RISE_I:
      rfnv_cdma1x_bc1_tbl.rfnv_r3_rise = item_ptr->bc1_pa_r3_rise;
    break;

  case NV_BC1_PA_R3_FALL_I:
      rfnv_cdma1x_bc1_tbl.rfnv_r3_fall = item_ptr->bc1_pa_r3_fall;
    break;

#ifdef RF_HAS_HDET_UINT16
	  case  NV_BC1_EXP_HDET_VS_AGC_V2_I:            
      (void)memcpy( rfnv_cdma1x_bc1_tbl.rfnv_cdma_exp_hdet_vs_agc,
                    (void *)item_ptr->bc1_exp_hdet_vs_agc_v2,
                    sizeof(rfnv_cdma1x_bc1_tbl.rfnv_cdma_exp_hdet_vs_agc) - 2 );
      break;

	  case  NV_BC1_HDET_OFF_V2_I:                   
      rfnv_cdma1x_bc1_tbl.rfnv_hdet_off = item_ptr->bc1_hdet_off_v2;
      break;
    
    case  NV_BC1_HDET_SPN_V2_I:                   
      rfnv_cdma1x_bc1_tbl.rfnv_hdet_spn = item_ptr->bc1_hdet_spn_v2;
      break;

#else // HDET IS OF UINT8 NOT OF RF_HAS_HDET_UINT16

  case  NV_BC1_HDET_OFF_I:                   
      rfnv_cdma1x_bc1_tbl.rfnv_hdet_off = item_ptr->bc1_hdet_off;
      break;

  case  NV_BC1_HDET_SPN_I:                   
      rfnv_cdma1x_bc1_tbl.rfnv_hdet_spn = item_ptr->bc1_hdet_spn;
      break;

  case  NV_BC1_EXP_HDET_VS_AGC_I:            
      (void)memcpy( rfnv_cdma1x_bc1_tbl.rfnv_cdma_exp_hdet_vs_agc,
                    (void *)item_ptr->bc1_exp_hdet_vs_agc,
                    sizeof(rfnv_cdma1x_bc1_tbl.rfnv_cdma_exp_hdet_vs_agc) - 1 );
      break;

#endif // HDET IS OF UINT8

  case  NV_BC1_ENC_BTF_I:                    
      rfnv_cdma1x_bc1_tbl.rfnv_enc_btf_dly = item_ptr->bc1_enc_btf;
      break;

  case NV_BC1_VCO_COARSE_TUNE_TABLE_I:
    (void)memcpy( rfnv_cdma1x_bc1_tbl.rfnv_vco_coarse_tune_table[0],
                  (void*) item_ptr->bc1_vco_coarse_tune_table,
                  sizeof( rfnv_cdma1x_bc1_tbl.rfnv_vco_coarse_tune_table[0] ) );
      break;

  case NV_BC1_VCO_TUNE_2_I:
    (void)memcpy( rfnv_cdma1x_bc1_tbl.rfnv_vco_coarse_tune_2[0],
                  (void*) item_ptr->bc1_vco_tune_2,
                  sizeof( rfnv_cdma1x_bc1_tbl.rfnv_vco_coarse_tune_2[0] ) );
    break;

#ifdef RF_HAS_LINEAR_INTERPOLATION

  case  NV_C0_BC1_TX_CAL_CHAN_I:
      for( loop_ctr=0; loop_ctr<16; loop_ctr++ )
      {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_cal_chan[0][loop_ctr] =
          (word) item_ptr->c0_bc1_tx_cal_chan[loop_ctr] ;
      }
      break;

  case  NV_C0_BC1_RX_CAL_CHAN_I:                   
      for (loop_ctr=0; loop_ctr < NV_FREQ_TABLE_SIZ; loop_ctr++) {
        rfnv_cdma1x_bc1_tbl.rfnv_rx_cal_chan[0][loop_ctr] =
          (word) item_ptr->c0_bc1_rx_cal_chan[loop_ctr];        
      }
      break;

#ifdef RF_HAS_FTM_V2_CAL_NV
  case NV_C0_BC1_RX_CAL_CHAN_LRU_I:
     for( loop_ctr=0; loop_ctr<NV_MAX_NUM_CAL_CHAN; loop_ctr++ )
     {
          rfnv_cdma1x_bc1_tbl.rfnv_rx_cal_chan_lru[0][loop_ctr] =
           item_ptr->c0_bc1_rx_cal_chan_lru[loop_ctr];
     }
    break;
#endif /* RF_HAS_FTM_V2_CAL_NV */

#endif /* RF_HAS_LINEAR_INTERPOLATION */

  case  NV_C0_BC1_LNA_1_OFFSET_VS_FREQ_I:   
      rfnv_load_lna_offset_data( item_ptr->c0_bc1_lna_1_offset_vs_freq,
                                 (int2*)rfnv_cdma1x_bc1_tbl.rfnv_cdma_lna_1_offset_vs_freq[0],/*lint !e740 */
                                 rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_offset[0],
                                 rx_freq_offset_array_length );
      break;

  case  NV_C0_BC1_LNA_2_OFFSET_VS_FREQ_I:   
      rfnv_load_lna_offset_data( item_ptr->c0_bc1_lna_2_offset_vs_freq,
                                 (int2*)rfnv_cdma1x_bc1_tbl.rfnv_cdma_lna_2_offset_vs_freq[0],/*lint !e740 */
                                 rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_offset[0],
                                 rx_freq_offset_array_length );
      break;

  case  NV_C0_BC1_LNA_3_OFFSET_VS_FREQ_I:   
      rfnv_load_lna_offset_data( item_ptr->c0_bc1_lna_3_offset_vs_freq,
                                 (int2*)rfnv_cdma1x_bc1_tbl.rfnv_cdma_lna_3_offset_vs_freq[0],/*lint !e740 */
                                 rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_offset[0],
                                 rx_freq_offset_array_length );
      break;

  case  NV_C0_BC1_LNA_4_OFFSET_VS_FREQ_I:   
      rfnv_load_lna_offset_data( item_ptr->c0_bc1_lna_4_offset_vs_freq,
                                 (int2*)rfnv_cdma1x_bc1_tbl.rfnv_cdma_lna_4_offset_vs_freq[0],/*lint !e740 */
                                 rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_offset[0],
                                 rx_freq_offset_array_length );
      break;
    
  case  NV_C0_BC1_LNA_1_OFFSET_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_offset[0] = (int2) item_ptr->c0_bc1_lna_1_offset;
      break;

  case  NV_C0_BC1_LNA_2_OFFSET_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_offset[0] = (int2) item_ptr->c0_bc1_lna_2_offset;
      break;

  case  NV_C0_BC1_LNA_3_OFFSET_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_offset[0] = (int2) item_ptr->c0_bc1_lna_3_offset;
      break;

  case  NV_C0_BC1_LNA_4_OFFSET_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_offset[0] = (int2) item_ptr->c0_bc1_lna_4_offset;
      break;

  case  NV_C0_BC1_IM2_I_VALUE_I:                     
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_im2_i_value[0][0] = item_ptr->c0_bc1_im2_i_value;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_im2_i_value[0] = item_ptr->c0_bc1_im2_i_value;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_IM2_Q_VALUE_I:             
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_im2_q_value[0][0] = item_ptr->c0_bc1_im2_q_value;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_im2_q_value[0] = item_ptr->c0_bc1_im2_q_value;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_VGA_GAIN_OFFSET_I:         
      rfnv_cdma1x_bc1_tbl.rfnv_vga_gain_offset[0] =
        (int2) item_ptr->c0_bc1_vga_gain_offset;
      break;

  case  NV_C0_BC1_VGA_GAIN_OFFSET_VS_FREQ_I: 
      rfnv_load_dvga_offset_data( item_ptr->c0_bc1_vga_gain_offset_vs_freq,
                                  (int2*)rfnv_cdma1x_bc1_tbl.rfnv_vga_gain_offset_vs_freq[0],/*lint !e740 */
                                  rfnv_cdma1x_bc1_tbl.rfnv_vga_gain_offset[0],
                                  rx_freq_offset_array_length );
      break;

  case  NV_C0_BC1_IM2_TRANSCONDUCTOR_VALUE_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_im2_transconductor_value[0][0] = item_ptr->c0_bc1_im2_transconductor_value;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_im2_transconductor_value[0] = item_ptr->c0_bc1_im2_transconductor_value;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_LNA_1_RISE_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_rise[0][0] = item_ptr->c0_bc1_lna_1_rise;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_rise[0] = item_ptr->c0_bc1_lna_1_rise;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_LNA_1_FALL_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_fall[0][0] = item_ptr->c0_bc1_lna_1_fall;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_fall[0] = item_ptr->c0_bc1_lna_1_fall;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_LNA_2_RISE_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_rise[0][0] = item_ptr->c0_bc1_lna_2_rise;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_rise[0] = item_ptr->c0_bc1_lna_2_rise;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_LNA_2_FALL_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_fall[0][0] = item_ptr->c0_bc1_lna_2_fall;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_fall[0] = item_ptr->c0_bc1_lna_2_fall;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_LNA_3_RISE_I:                 
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_rise[0][0] = item_ptr->c0_bc1_lna_3_rise;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_rise[0] = item_ptr->c0_bc1_lna_3_rise;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_LNA_3_FALL_I:                 
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_fall[0][0] = item_ptr->c0_bc1_lna_3_fall;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_fall[0] = item_ptr->c0_bc1_lna_3_fall;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_LNA_4_RISE_I:                 
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_rise[0][0] = item_ptr->c0_bc1_lna_4_rise;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_rise[0] = item_ptr->c0_bc1_lna_4_rise;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_LNA_4_FALL_I:                 
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_fall[0][0] = item_ptr->c0_bc1_lna_4_fall;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_fall[0] = item_ptr->c0_bc1_lna_4_fall;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C0_BC1_IM_LEVEL1_I:                  
      rfnv_cdma1x_bc1_tbl.rfnv_im_level1[0] = (int1) item_ptr->c0_bc1_im_level1;
      break;

  case  NV_C0_BC1_IM_LEVEL2_I:                  
      rfnv_cdma1x_bc1_tbl.rfnv_im_level2[0] = (int1) item_ptr->c0_bc1_im_level2;
      break;

  case  NV_C0_BC1_IM_LEVEL3_I:                  
      rfnv_cdma1x_bc1_tbl.rfnv_im_level3[0] = (int1) item_ptr->c0_bc1_im_level3;
      break;

  case  NV_C0_BC1_IM_LEVEL4_I:                  
      rfnv_cdma1x_bc1_tbl.rfnv_im_level4[0] = (int1) item_ptr->c0_bc1_im_level4;
      break;

#ifdef RF_HAS_LINEAR_INTERPOLATION

  case  NV_C1_BC1_TX_CAL_CHAN_I:
      for( loop_ctr=0; loop_ctr<16; loop_ctr++ )
      {
        rfnv_cdma1x_bc1_tbl.rfnv_tx_cal_chan[1][loop_ctr] =
          (word) item_ptr->c1_bc1_tx_cal_chan[loop_ctr] ;
      }
      break;

  case  NV_C1_BC1_RX_CAL_CHAN_I:
      for( loop_ctr=0; loop_ctr<16; loop_ctr++ )
      {
        rfnv_cdma1x_bc1_tbl.rfnv_rx_cal_chan[1][loop_ctr] =
          (word) item_ptr->c1_bc1_rx_cal_chan[loop_ctr] ;
      }
      break;

#ifdef RF_HAS_FTM_V2_CAL_NV
  case NV_C1_BC1_RX_CAL_CHAN_LRU_I:
     for( loop_ctr=0; loop_ctr<NV_MAX_NUM_CAL_CHAN; loop_ctr++ )
     {
          rfnv_cdma1x_bc1_tbl.rfnv_rx_cal_chan_lru[1][loop_ctr] =
           item_ptr->c1_bc1_rx_cal_chan_lru[loop_ctr];
     }
    break;
#endif /* RF_HAS_FTM_V2_CAL_NV */

#endif /* RF_HAS_LINEAR_INTERPOLATION */

  case  NV_C1_BC1_LNA_1_OFFSET_VS_FREQ_I:   
      rfnv_load_lna_offset_data( item_ptr->c1_bc1_lna_1_offset_vs_freq,
                                 (int2*)rfnv_cdma1x_bc1_tbl.rfnv_cdma_lna_1_offset_vs_freq[1],/*lint !e740 */
                                 rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_offset[1],
                                 NV_FREQ_TABLE_SIZ );
      break;

  case  NV_C1_BC1_LNA_2_OFFSET_VS_FREQ_I:   
      rfnv_load_lna_offset_data( item_ptr->c1_bc1_lna_2_offset_vs_freq,
                                 (int2*)rfnv_cdma1x_bc1_tbl.rfnv_cdma_lna_2_offset_vs_freq[1],/*lint !e740 */
                                 rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_offset[1],
                                 NV_FREQ_TABLE_SIZ );
      break;

  case  NV_C1_BC1_LNA_3_OFFSET_VS_FREQ_I:   
      rfnv_load_lna_offset_data( item_ptr->c1_bc1_lna_3_offset_vs_freq,
                                 (int2*)rfnv_cdma1x_bc1_tbl.rfnv_cdma_lna_3_offset_vs_freq[1],/*lint !e740 */
                                 rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_offset[1],
                                 NV_FREQ_TABLE_SIZ );
      break;

  case  NV_C1_BC1_LNA_4_OFFSET_VS_FREQ_I:   
      rfnv_load_lna_offset_data( item_ptr->c1_bc1_lna_4_offset_vs_freq,
                                 (int2*)rfnv_cdma1x_bc1_tbl.rfnv_cdma_lna_4_offset_vs_freq[1],/*lint !e740 */
                                 rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_offset[1],
                                 NV_FREQ_TABLE_SIZ );
      break;
    
  case  NV_C1_BC1_LNA_1_OFFSET_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_offset[1] = (int2) item_ptr->c1_bc1_lna_1_offset;
      break;

  case  NV_C1_BC1_LNA_2_OFFSET_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_offset[1] = (int2) item_ptr->c1_bc1_lna_2_offset;
      break;

  case  NV_C1_BC1_LNA_3_OFFSET_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_offset[1] = (int2) item_ptr->c1_bc1_lna_3_offset;
      break;

  case  NV_C1_BC1_LNA_4_OFFSET_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_offset[1] = (int2) item_ptr->c1_bc1_lna_4_offset;
      break;

  case  NV_C1_BC1_IM2_I_VALUE_I:                     
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_im2_i_value[1][0] = item_ptr->c1_bc1_im2_i_value;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_im2_i_value[1] = item_ptr->c1_bc1_im2_i_value;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_IM2_Q_VALUE_I:             
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_im2_q_value[1][0] = item_ptr->c1_bc1_im2_q_value;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_im2_q_value[1] = item_ptr->c1_bc1_im2_q_value;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_VGA_GAIN_OFFSET_I:         
      rfnv_cdma1x_bc1_tbl.rfnv_vga_gain_offset[1] =
        (int2) item_ptr->c1_bc1_vga_gain_offset;
      break;

  case  NV_C1_BC1_VGA_GAIN_OFFSET_VS_FREQ_I: 
      rfnv_load_dvga_offset_data( item_ptr->c1_bc1_vga_gain_offset_vs_freq,
                                  (int2*)rfnv_cdma1x_bc1_tbl.rfnv_vga_gain_offset_vs_freq[1],/*lint !e740 */
                                  rfnv_cdma1x_bc1_tbl.rfnv_vga_gain_offset[1],
                                  NV_FREQ_TABLE_SIZ );
      break;

  case  NV_C1_BC1_IM2_TRANSCONDUCTOR_VALUE_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_im2_transconductor_value[1][0] = item_ptr->c1_bc1_im2_transconductor_value;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_im2_transconductor_value[1] = item_ptr->c1_bc1_im2_transconductor_value;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_LNA_1_RISE_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_rise[1][0] = item_ptr->c1_bc1_lna_1_rise;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_rise[1] = item_ptr->c1_bc1_lna_1_rise;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_LNA_1_FALL_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_fall[1][0] = item_ptr->c1_bc1_lna_1_fall;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_fall[1] = item_ptr->c1_bc1_lna_1_fall;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_LNA_2_RISE_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_rise[1][0] = item_ptr->c1_bc1_lna_2_rise;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_rise[1] = item_ptr->c1_bc1_lna_2_rise;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_LNA_2_FALL_I:
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_fall[1][0] = item_ptr->c1_bc1_lna_2_fall;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_fall[1] = item_ptr->c1_bc1_lna_2_fall;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_LNA_3_RISE_I:                 
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_rise[1][0] = item_ptr->c1_bc1_lna_3_rise;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_rise[1] = item_ptr->c1_bc1_lna_3_rise;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_LNA_3_FALL_I:                 
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_fall[1][0] = item_ptr->c1_bc1_lna_3_fall;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_fall[1] = item_ptr->c1_bc1_lna_3_fall;
#endif /* RF_HAS_POWER_MODE_LIB */
    break;

  case  NV_C1_BC1_LNA_4_RISE_I:                 
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_rise[1][0] = item_ptr->c1_bc1_lna_4_rise;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_rise[1] = item_ptr->c1_bc1_lna_4_rise;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_LNA_4_FALL_I:                 
#ifdef RF_HAS_POWER_MODE_LIB
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_fall[1][0] = item_ptr->c1_bc1_lna_4_fall;
#else
      rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_fall[1] = item_ptr->c1_bc1_lna_4_fall;
#endif /* RF_HAS_POWER_MODE_LIB */
      break;

  case  NV_C1_BC1_IM_LEVEL1_I:                  
      rfnv_cdma1x_bc1_tbl.rfnv_im_level1[1] = (int1) item_ptr->c1_bc1_im_level1;
      break;

  case  NV_C1_BC1_IM_LEVEL2_I:                  
      rfnv_cdma1x_bc1_tbl.rfnv_im_level2[1] = (int1) item_ptr->c1_bc1_im_level2;
      break;

  case  NV_C1_BC1_IM_LEVEL3_I:                  
      rfnv_cdma1x_bc1_tbl.rfnv_im_level3[1] = (int1) item_ptr->c1_bc1_im_level3;
      break;

  case  NV_C1_BC1_IM_LEVEL4_I:                  
      rfnv_cdma1x_bc1_tbl.rfnv_im_level4[1] = (int1) item_ptr->c1_bc1_im_level4;
      break;

  case NV_C1_BC1_VCO_COARSE_TUNE_TABLE_I:
      ct_table_size = sizeof(rfnv_cdma1x_bc1_tbl.rfnv_vco_coarse_tune_table[1]);
      nv_table_size = sizeof(item_ptr->c1_bc1_vco_coarse_tune_table);
      rfnv_vco_array_size = MIN(ct_table_size, nv_table_size);       
      (void)memcpy( rfnv_cdma1x_bc1_tbl.rfnv_vco_coarse_tune_table[1],
                    (void*) item_ptr->c1_bc1_vco_coarse_tune_table,
                    rfnv_vco_array_size );
      break;
#ifdef FEATURE_P1_DYNAMIC_PA_SWITCH_POINT_ADJUST
    case NV_BC1_P1_RISE_FALL_OFF_I:
        for( loop_ctr=0; loop_ctr<NV_PA_SP_OFFSET_TABLE_SIZ; loop_ctr++ )
        {
            rfnv_cdma1x_bc1_tbl.rfnv_p1_pa_rise_fall_off[0][loop_ctr] =
            rfnv_cdma1x_bc1_tbl.rfnv_p1_pa_rise_fall_off[1][loop_ctr] =
                (byte) item_ptr->bc1_p1_rise_fall_off[loop_ctr] ;
        }
        break;
#endif
#ifdef FEATURE_HDR_P1_DYNAMIC_PA_SWITCH_POINT_ADJUST
    
    case NV_BC1_HDR_P1_RISE_FALL_OFF_I:
        for( loop_ctr=0; loop_ctr<NV_HDR_PA_SP_OFFSET_TABLE_SIZ; loop_ctr++ )
        {
            rfnv_cdma1x_bc1_tbl.rfnv_hdr_p1_pa_rise_fall_off[loop_ctr] =
                (byte) item_ptr->bc1_hdr_p1_rise_fall_off[loop_ctr] ;
        }
        break;
#endif

#ifdef RF_HAS_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST
    
    case NV_BC1_P2_RISE_FALL_OFF_I:
        for( loop_ctr=0; loop_ctr<NV_PA_SP_OFFSET_TABLE_SIZ; loop_ctr++ )
        {
            rfnv_cdma1x_bc1_tbl.rfnv_p2_pa_rise_fall_off[0][loop_ctr] =
            rfnv_cdma1x_bc1_tbl.rfnv_p2_pa_rise_fall_off[1][loop_ctr] =
                (byte) item_ptr->bc1_p2_rise_fall_off[loop_ctr] ;
        }
        break;

    case NV_BC1_P3_RISE_FALL_OFF_I:
        for( loop_ctr=0; loop_ctr<NV_PA_SP_OFFSET_TABLE_SIZ; loop_ctr++ )
        {
            rfnv_cdma1x_bc1_tbl.rfnv_p3_pa_rise_fall_off[0][loop_ctr] =
            rfnv_cdma1x_bc1_tbl.rfnv_p3_pa_rise_fall_off[1][loop_ctr] =
                (byte) item_ptr->bc1_p3_rise_fall_off[loop_ctr] ;
        }
        break;
#endif /* RF_HAS_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST */

#ifdef RF_HAS_HDR_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST
#error code not present
#endif /* RF_HAS_HDR_P2_P3_DYNAMIC_PA_SWITCH_POINT_ADJUST */

#ifdef RF_HAS_PA_DVS_NV
    case NV_BC1_PA_DVS_VOLTAGE_I:
        rfnv_cdma1x_bc1_tbl.rfnv_pa_dvs_voltage = (uint16) item_ptr->bc1_pa_dvs_voltage;
        break;
#endif
 
#ifdef RF_HAS_POWER_MODE_LIB
    case NV_C0_BC1_LNA_SWITCHPOINTS_LPM_1_I:
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_rise[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_1.rf_rx_agc_lpm_rise[0];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_rise[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_1.rf_rx_agc_lpm_rise[1];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_rise[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_1.rf_rx_agc_lpm_rise[2];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_rise[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_1.rf_rx_agc_lpm_rise[3];
  
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_fall[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_1.rf_rx_agc_lpm_fall[0];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_fall[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_1.rf_rx_agc_lpm_fall[1];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_fall[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_1.rf_rx_agc_lpm_fall[2];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_fall[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_1.rf_rx_agc_lpm_fall[3];
        break;

    case NV_C0_BC1_IM2_LPM_1_I:
        rfnv_cdma1x_bc1_tbl.rfnv_im2_i_value[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_im2_lpm_1.i;
        rfnv_cdma1x_bc1_tbl.rfnv_im2_q_value[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_im2_lpm_1.q;
        rfnv_cdma1x_bc1_tbl.rfnv_im2_transconductor_value[0][RFLIB_LOW_POWER_MODE_1]
          = item_ptr->c0_bc1_im2_lpm_1.transconductor;
        break;

    case NV_C0_BC1_LNA_SWITCHPOINTS_LPM_2_I:
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_rise[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_2.rf_rx_agc_lpm_rise[0];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_rise[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_2.rf_rx_agc_lpm_rise[1];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_rise[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_2.rf_rx_agc_lpm_rise[2];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_rise[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_2.rf_rx_agc_lpm_rise[3];

        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_1_fall[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_2.rf_rx_agc_lpm_fall[0];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_2_fall[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_2.rf_rx_agc_lpm_fall[1];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_3_fall[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_2.rf_rx_agc_lpm_fall[2];
        rfnv_cdma1x_bc1_tbl.rfnv_lna_range_4_fall[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_lna_switchpoints_lpm_2.rf_rx_agc_lpm_fall[3];
        break;

    case NV_C0_BC1_IM2_LPM_2_I:
        rfnv_cdma1x_bc1_tbl.rfnv_im2_i_value[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_im2_lpm_2.i;
        rfnv_cdma1x_bc1_tbl.rfnv_im2_q_value[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_im2_lpm_2.q;
        rfnv_cdma1x_bc1_tbl.rfnv_im2_transconductor_value[0][RFLIB_LOW_POWER_MODE_2]
          = item_ptr->c0_bc1_im2_lpm_2.transconductor;
        break;

    case NV_C0_BC1_INTELLICEIVER_CAL_I:
        memcpy( rfnv_cdma1x_bc1_tbl.rfnv_intelliceiver_cal[0],
                (void*)item_ptr->c0_bc1_intelliceiver_cal,
                NV_INTELLICEIVER_CAL_LENGTH );
        break;
    
    case NV_C0_BC1_INTELLICEIVER_DET_THRESH_I:
        memcpy( rfnv_cdma1x_bc1_tbl.rfnv_intelliceiver_detector_adjust[0],
                (void*)item_ptr->c0_bc1_intelliceiver_det_thresh,
                sizeof(item_ptr->c0_bc1_intelliceiver_det_thresh) );
        break;
#endif /* RF_HAS_POWER_MODE_LIB */
    
    case NV_BC1_ANT_QUALITY_I:
        memcpy( rfnv_cdma1x_bc1_tbl.rfnv_ant_quality,
                (void*)item_ptr->bc1_ant_quality, 
                sizeof(rfnv_cdma1x_bc1_tbl.rfnv_ant_quality) );
        break;
#ifdef RF_HAS_HW_DZRF6285
#error code not present
#endif

    case NV_BC1_PA_R_MAP_I:
        rfnv_cdma1x_bc1_tbl.rfnv_bc_pa_r_map.value = item_ptr->bc1_pa_r_map;
        rfnv_cdma1x_bc1_tbl.rfnv_bc_pa_r_map.nv_initialized = TRUE;
        break;

#ifdef RF_HAS_SUPPORT_FOR_LO_PWC_CAL
    case NV_C0_BC1_LO_CAL_I:
      rfnv_cdma1x_bc1_tbl.rfnv_lo_cal[ RF_PATH_0 ] = item_ptr->c0_bc1_lo_cal;
      break;
#endif //RF_HAS_SUPPORT_FOR_LO_PWC_CAL

#ifdef RF_HAS_SUPPORT_FOR_LO_IM2_CAL
    case NV_C0_BC1_IM2_CAL_I:
      rfnv_cdma1x_bc1_tbl.rfnv_im2_cal[ RF_PATH_0 ] = item_ptr->c0_bc1_im2_cal;
      break;
#endif //RF_HAS_SUPPORT_FOR_LO_IM2_CAL

#ifdef RF_HAS_SUB_BLOCK_SUPPORT
    case NV_BC1_SUBCLASS_MASK_I:
      rfnv_cdma1x_bc1_tbl.rfnv_block_mask = item_ptr->bc1_subclass_mask;
      break;
#endif //RF_HAS_SUB_BLOCK_SUPPORT

    default:
      ERR( "RF NV item not accounted for: %d", item_code, 0,0 );
      break;
  }

#ifdef RF_HAS_RFCONFIG_RX_LNA
    rfnv_rfconfig_migration_util_enable_tracking_for_nv(
       item_code,  // NV item ID
       rfnv_cdma1x_bc1_rfconfig_migration_util_map_array,
       ARR_SIZE(rfnv_cdma1x_bc1_rfconfig_migration_util_map_array));
#endif /* RF_HAS_RFCONFIG_RX_LNA */

  /*lint -restore */

}/* end of rfnv_cdma1x_bc1_copy_nv_item */


/*===========================================================================

FUNCTION RFNV_CDMA1X_BC1_LIST_SIZE                      EXTERNALIZED FUNCTION

DESCRIPTION
  This function returns the number of items in the BC1 NV list.

DEPENDENCIES
  None

RETURN VALUE
  Number of item in the BC1 NV list.

SIDE EFFECTS
  None

===========================================================================*/
word rfnv_cdma1x_bc1_list_size( void )
{
  return ( ARR_SIZE( rfnv_cdma1x_bc1_nv_items_list ) );
} /* end of rfnv_cdma1x_bc1_list_size */

/*===========================================================================

FUNCTION RFNV_CDMA1X_BC1_ITEM_TABLE                  EXTERNALIZED FUNCTION

DESCRIPTION
  This function returns a void pointer to the bc1 nv table.

DEPENDENCIES
  None

RETURN VALUE
  void pointer the bc1 nv table.

SIDE EFFECTS
  None

===========================================================================*/
void *rfnv_cdma1x_bc1_item_table(void)
{
    return ((void *) &rfnv_cdma1x_bc1_tbl);
}


#ifdef RF_HAS_RFCONFIG_RX_LNA
/*===========================================================================
FUNCTION  RFNV_CDMA1X_BC1_GET_RX_RFCONFIG_MIGRATION_TRACKER  EXTERNALIZED FUNCTION

DESCRIPTION
  This function returns pointer to the RFNV->RFConfigDBase migration tracker
  object for the specified Rx path.

DEPENDENCIES
  None

RETURN VALUE
  RFNV->RFConfigDBase migration tracker pointer for a given Rx path

SIDE EFFECTS
  None
===========================================================================*/
const rfnv_rfconfig_migration_tracker_type* rfnv_cdma1x_bc1_get_rx_rfconfig_migration_tracker(
   rf_path_enum_type which_rx_chain)
{
   const rfnv_rfconfig_migration_tracker_type *tracker_ptr = NULL;

   RF_ASSERT(which_rx_chain < RF_PATH_NUM);

   if (which_rx_chain < RF_PATH_NUM)
   {
      tracker_ptr = &rfnv_cdma1x_bc1_rx_rfconfig_migration_tracker[which_rx_chain];
   }
   return tracker_ptr;
}
#endif /* RF_HAS_RFCONFIG_RX_LNA */


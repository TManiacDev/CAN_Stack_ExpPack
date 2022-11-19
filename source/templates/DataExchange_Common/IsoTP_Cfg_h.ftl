[#ftl]
/**
  ******************************************************************************
  * @section CanIsoTP_CFG_H Code generation 
  * File Name          : ${name}
  * Description        : This file provides code for the configuration
  *                      of the ${name} instances.
  *
  [#assign aDateTime = .now]
  [#assign aDate = aDateTime?date]
  [#assign aTime = aDateTime?time]
  * Last updated       : ${aDate}  ${aTime}
  *
  ******************************************************************************
[@common.optinclude name=mxTmpFolder+"/license.tmp"/][#--include License text --]
  ******************************************************************************
  */
[#assign s = name]
[#assign to = s?replace(".","__")]
[#assign toto = to?replace("/","__")]
[#assign dashReplace = toto?replace("-","_")]
[#assign inclusion_protection = dashReplace?upper_case]
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __${inclusion_protection}__
#define __${inclusion_protection}__

/* Imported types */
#include "TM_Std_types.h"
#include "CanIf.h"

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN CanIsoTP_Cfg_h 0 */

/* USER CODE END CanIsoTP_Cfg_h 0 */

/** @addtogroup TM_IsoTP_CfgGeneral
 *  @{ */
 
 /** @brief Development Error Detection On/OFF
  *  @details
  *  activates the calling of CAN_DET_REPORTERROR() */
// #define ISOTP_DEV_ERROR_DETECT  STD_ON 
 #define ISOTP_DEV_ERROR_DETECT  STD_OFF 
 /** @} */ // end of grouping TM_IsoTP_CfgGeneral
 
 /** @addtogroup TM_IsoTP_Cfg
 *  @{ */

/** @brief define the decode level 
 * 
 *  @value DECODE_ON_INTERRUPT 
 *  @value DECODE_ON_TASK */ 
#define ISOTP_DECODE_LEVEL DECODE_ON_INTERRUPT 

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN CanIsoTP_Enum_h 1 */

/* USER CODE END CanIsoTP_Enum_h 1 */
/** @} */ // end of grouping TM_IsoTP_Cfg

/** @addtogroup TM_IsoTP_Cfg
 *  @{ */

/** the structure type to hold the configuration */ 
typedef struct
{
  /** BS */ 
  uint32_t maxBlockSize; 
  /** STmin */ 
  uint32_t minSeparartionTime; 
  /** max response time in milliseconds */ 
  uint32_t maxResponseTimeout; 
  /** the maximal number of accepted wait frames */ 
  uint32_t maxWaitForTransmitCylcles; 
  /** just a dummy */ 
  uint32_t Just_a_Dummy; 
}IsoTP_ConfigType; 
 
/** this holds the default values defined by the protocol it self */ 
extern const IsoTP_ConfigType IsoTP_DefaultConfig; 

/** @} */ // end of grouping TM_IsoTP_Cfg

#endif /* __ ${inclusion_protection}__ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
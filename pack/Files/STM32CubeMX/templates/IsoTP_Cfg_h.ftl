[#ftl]
[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 1]
[#list SWIPdatas as SWIP]  
[#assign instName = SWIP.ipName]   
[#assign fileName = SWIP.fileName]   
[#assign version = SWIP.version]   
[#assign myInstName = instName]
[#assign SubPatch = myInstName?keep_after_last(".")]
[#assign myInstName = myInstName?keep_before_last(".")]
[#assign PatchLevel = myInstName?keep_after_last(".")]
[#assign myInstName = myInstName?keep_before_last(".")]
[#assign VersionLevel = myInstName?keep_after_last(".")]
/* ******************************************************************************
 * File Name          : ${fileName}
 * Description        : This file provides code for the configuration
 *                      of the ${name} instances.
 *
 * MiddleWare name    : ${instName}
 * MiddleWare version : ${version} / ${VersionLevel}.${PatchLevel}.${SubPatch}
 * Last updated       : ${aDate}  ${aTime}
 *
 ******************************************************************************
 [@common.optinclude name=mxTmpFolder+"/license.tmp"/][#--include License text --]
 ******************************************************************************
 */
[/#list] [#-- end of SWIPdatas as SWIP --]
[#assign s = name]
[#assign dashedFileNamed = s?replace(".","__")]
[#assign toto = dashedFileNamed?replace("/","__")]
[#assign dashReplace = toto?replace("-","_")]
[#assign inclusion_protection = dashReplace?upper_case]

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __${inclusion_protection}__
#define __${inclusion_protection}__

[#assign UserCodeCounter = 0]

/* Imported types */

/* the IsoTP_Cfg.h shouldn't have an include itself, it should extending the IsoTP.h file*/

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/** @addtogroup TM_IsoTP
 *  @version ${VersionLevel}.${PatchLevel}.${SubPatch}
 *  @{ */
/** @brief  my ID */
#define ISOTP_VENDOR_ID           TM_VENDOR_ID
/** @brief  module id to see where the error is come from */
#define ISOTP_MODULE_ID           (*(uint16_t*)"TP")
/** @brief To see the version and patch level we save it on ASCII: ${VersionLevel}.${PatchLevel} */ 
#define ISOTP_VERSION             (*(uint16_t*)"${VersionLevel}${PatchLevel}")
/** @brief To see the sub patch level we save it on ASCII 
 *  @details There are two signs available(0-99):${SubPatch} */
#define ISOTP_PATCH_VERSION       (*(uint16_t*)"${SubPatch}")

/** @} */ // end of TM_IsoTP grouping

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
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]
  
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
}IsoTP_FlowConfigType; 

/** this holds the default values defined by the protocol it self */ 
extern const IsoTP_ConfigType IsoTP_DefaultConfig; 

/** @} */ // end of grouping TM_IsoTP_Cfg

#endif /* __ ${inclusion_protection}__ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
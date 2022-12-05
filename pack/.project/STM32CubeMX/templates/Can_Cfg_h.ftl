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
/**
  ******************************************************************************
  * @section Can_CFG_H Code generation 
  * File Name          : ${fileName}
  * Description        : This file provides code for the configuration
  *                      of the ${name} instances.
  *
  * MiddleWare name    : ${instName}
  * MiddleWare version : ${version}
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

/* Define to prevent recursive inclusion ------------------------------------- */
#ifndef __${inclusion_protection}__
#define __${inclusion_protection}__

  [#assign UserCodeCounter = 0]
  
#include "TM_ComStack_Types.h"
#include "Can_Compiler_Cfg.h"

/* private Includes ----------------------------------------------------------- */
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/** @addtogroup TM_Can_Driver
 *  @{ */
/** @brief  my ID */
#define CAN_VENDOR_ID           TM_VENDOR_ID
/** @brief  module id to see where the error is come from */
#define CAN_MODULE_ID           (*(uint16_t*)"CA")
/** @brief To see the version and patch level we save it on ASCII */ 
#define CAN_VERSION             (*(uint16_t*)"${VersionLevel}${PatchLevel}")
/** @brief To see the sub patch level we save it on ASCII 
 *  @details There are two signs available: 0-99 */
#define CAN_PATCH_VERSION       (*(uint16_t*)"${SubPatch}")
/** @} */ // end of grouping TM_Can_Driver

/*******************************/
[#-- SWIPdatas is a list of SWIPconfigModel --]  
[#list SWIPdatas as SWIP]  
[#assign instName = SWIP.ipName]   
[#assign fileName = SWIP.fileName]   
[#assign version = SWIP.version]   
[#-- Global variables --]
[#if SWIP.variables??]
	[#list SWIP.variables as variable]
extern ${variable.value} ${variable.name};
	[/#list]
[/#if]

[#-- Global variables --]


/** @addtogroup TM_CanCfg_General
 *  @brief    General behavior of the CAN Module
 *  @details  Some elements are hold as \#define and other in the configuration structure<br>
 *            \#defines are used to switch on or off code segments
 *  @{ */

/** @brief Development Error Detection On/OFF
 *  @details
 *  activates the calling of CAN_DET_REPORTERROR() */
// #define CAN_DEV_ERROR_DETECT  STD_ON
#define CAN_DEV_ERROR_DETECT_NO  STD_OFF

[#if SWIP.defines??]
	[#list SWIP.defines as definition]	
  
  [#switch definition.name ]
    [#case "CAN_BITRATES"]
      [#-- extract Bitrate list --]
      [#assign BitrateList = definition.value]
      [#assign _BitrateList_ = BitrateList?replace(","," ")]
      [#assign _List_ = _BitrateList_?word_list]
      [#-- extract Bitrate list --]
      [#break]
  [#default]
  [#if definition.comments??]
/** ----------  ${definition.comments} -----------*/
  [#else]
/** -------- generated Value  -----------*/ 
  [/#if]
#define ${definition.name} #t#t ${definition.value} 
[#if definition.description??]${definition.description} [/#if]
  [/#switch]
	[/#list]
[/#if]
[/#list]

/** @brief this is just to catch un used configuration */
#define UNKNOWN 0

/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]
/** @} */ // end of grouping TM_CanCfg_General

/** @addtogroup TM_CanCfg_BaudCfg
 *  @{ */

/** @brief This ID is used by SetBaudrate API and uniquely identifies a specific baud rate configuration within a controller configuration.
 */
typedef enum
{
  [#list _List_ as word] 
    [#assign Bitnumber = word?number]
  /** @brief symbolic name for ${Bitnumber}kb/s baudrate */
  CanBaudrate_${Bitnumber}kbs,
    [/#list]
  /** @brief symbolic name to end the list and for error handling */
  CanBaudrate_unknown
}CanControllerBaudRateConfigID;

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]
/** @} */ // end of grouping TM_CanCfg_BaudCfg

#endif /*__ ${inclusion_protection}_H */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

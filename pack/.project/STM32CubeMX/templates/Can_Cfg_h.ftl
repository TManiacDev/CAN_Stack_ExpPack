[#ftl]
[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 1]
[#list SWIPdatas as SWIP]  
[#assign instName = SWIP.ipName]   
[#assign fileName = SWIP.fileName]   
[#assign version = SWIP.version]   
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __${inclusion_protection}__
#define __${inclusion_protection}__

  [#assign UserCodeCounter = 0]
  
#include "main.h"
#include "TM_ComStack_Types.h" 

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

#ifdef __cplusplus
 extern "C" {
#endif

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
#define CAN_DEV_ERROR_DETECT  STD_ON
// #define CAN_DEV_ERROR_DETECT_NO  STD_OFF

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

/** @brief Names for the hardware CAN controller */
typedef enum
{
  CanMasterController,    ///< ST named the first controller Master because of the "Master configuration"
  CanSlaveController,     ///< ST named the second controller Slave because of fewer configuration
  NBROF_CanController     ///< for error handling we create a name at last
}ECU_CanController;

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]
/** @} */ // end of grouping TM_CanCfg_BaudCfg

#ifdef __cplusplus
}
#endif
#endif /*__ ${inclusion_protection}_H */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

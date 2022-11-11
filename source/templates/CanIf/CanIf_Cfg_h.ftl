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
  * @section CanIF_CFG_H Code generation
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
  
#include "main.h"
#include "TM_Std_types.h"

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/** @addtogroup TM_CanIf_Main
 *  @{ */
 
#ifdef __cplusplus
#include "TMEVersionInfo.h"
#endif
 
/** @brief  my ID */
#define CANIF_VENDOR_ID           TM_VENDOR_ID
/** @brief  module id to see where the error is come from */
#define CANIF_MODULE_ID           (0x60)
/** @brief we have only one version at start 
 *  todo use a generated value */
#define CANIF_VERSION             (${VersionLevel})
/** @brief no patching until now 
 *  todo use a generated value */
#define CANIF_PATCH_VERSION       (${PatchLevel})
/** @} */ // end of grouping TM_CanIf_Main

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

/** @addtogroup TM_CanIf_BufferCfg
 *  @{ */
[#if SWIP.defines??]
	[#list SWIP.defines as definition]	
  
      [#assign List = definition.value]
      [#assign _ListC = List?replace(","," ")]  
      [#assign _List_ = _ListC?replace("|"," ")]  
      
  [#switch definition.name ]
      [#-- extract IF Upper Layer list --]
    [#case "CANIF_RXUL_LIST"]
      [#assign RxUpperLayerList = _List_?word_list]
      /* extract RxUpperLayerList ${definition.value} /./ ${List} /./ ${_List_} */
      [#break]
    [#case "CANIF_TXUL_LIST"] 
      [#assign TxUpperLayerList = _List_?word_list]
      /* extract TxUpperLayerList ${definition.value} /./ ${List} /./ ${_List_} */
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

/** @} */ // end of grouping TM_CanIf_BufferCfg

[#if RxUpperLayerList??]
  [#assign SortList = RxUpperLayerList?sort]
  [#assign DoneList = ["Start", "Second"] ]
  [#list SortList as RxUpperLayer]
    [#if (DoneList?seq_contains(RxUpperLayer) ) || (RxUpperLayer?starts_with("u") )]
    
    [#-- nothing to do --]
    
    [#else]
    
/** @brief activate receive code for the ${RxUpperLayer} */ 
#define _CanIfUL_${RxUpperLayer}_RX_USED_ 

    [#assign DoneList += [RxUpperLayer] ]
    [/#if] [#-- end of check already done --]
  [/#list] [#-- end of RxUpperLayer --] 
[/#if] [#-- end of RxUpperLayerList?? --]

[#if TxUpperLayerList??]
  [#assign SortList = TxUpperLayerList?sort]
  [#assign DoneList = ["Start", "Second"] ]
  [#list SortList as TxUpperLayer]
    [#if (DoneList?seq_contains(TxUpperLayer) ) || (TxUpperLayer?starts_with("u") )]
    [#else]
    
/** @brief activate transmit code for the ${TxUpperLayer} */ 
#define _CanIfUL_${TxUpperLayer}_TX_USED_ 

    [#assign DoneList += [TxUpperLayer] ]
    [/#if] [#-- end of check already done --]
  [/#list] [#-- end of TxUpperLayer --] 
[/#if] [#-- end of TxUpperLayerList?? --]

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/** use of the development error detection */
#define CANIF_DEV_ERROR_DETECT STD_OFF

/** use of the pre compile configuration */
#define CANIF_LOAD_STATIC_CONFIG STD_ON

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]


#ifdef __cplusplus
}
#endif
#endif /*__ ${inclusion_protection}__ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
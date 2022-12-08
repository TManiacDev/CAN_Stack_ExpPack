[#ftl]
[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 0]
[#assign fileName = ""]
[#list SWIPdatas as SWIP]  
[#assign instName = SWIP.ipName]   
[#assign fileName = SWIP.fileName]   
[#assign version = SWIP.version]   
/**
  ******************************************************************************
  * @section EcuNames_CFG_H Code generation 
  * File Name          : ${fileName}
  * Description        : This file provides code for the configuration
  *                      of the instances.
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

[#assign s = fileName]
[#if s?contains("/")]
  [#assign s = s?keep_after_last("/")]
[/#if]
[#assign dashReplace = s?replace(".","_")]
[#assign dashedFileNamed = dashReplace?replace("-","_")]
[#assign inclusion_protection = dashedFileNamed?upper_case]
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __${inclusion_protection}__
#define __${inclusion_protection}__

  [#assign UserCodeCounter = 0]
  
#include "main.h"
#include "TM_Std_types.h"

/* private Includes -----------------------------------------------------------*/

/** @brief this enum shows the naming conventions of used PDU names */
 typedef enum 
 {  
   N_PDU_Dummy_for_Test = 0x80, 
   L_PDU_Dummy_for_Test, 
   CanUndefUl_Rx_Target1, 
   CanUndefUl_Rx_Target2, 
   CanUndefUl_Tx_Target1,
   CanUndefUl_Tx_Target2   
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]
 }CanUL_PDU_for_Test; 
 
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */
 
/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/* ***************************** */

/** @brief Names for the hardware CAN controller 
  * @todo we need a generic way for this */
typedef enum
{
  CanMasterController,    ///< ST named the first controller Master because of the "Master configuration"
  CanSlaveController,     ///< ST named the second controller Slave because of fewer configuration
  NBROF_CanController     ///< for error handling we create a name at last
}ECU_CanController;

/* ***************************** */
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
[#assign CanIf_Prefix = "CanIf"]
[#assign IsoTp_Prefix = "IsoTP"]
[#assign FTCAN2p0_Prefix = "CanFT"]
[#assign CanNM_Prefix = "CanNM"]
[#assign CanTSync_Prefix = "CanTSync"]
[#assign Xcp_Prefix = "CanXcp"]
[#assign strPduIdType = "PduIdType" ]

[#assign FTEcuUse = "-"]
[#assign FTPanelUse = "-"]
[#assign FTDeviceUse = "-"]
[#assign FTConfigOk = "NOk"]
[#assign FT_RxList = [] ] [#-- we create an empty list --]
[#assign FT_TxList = [] ]

[#if SWIP.defines??]
	[#list SWIP.defines as definition]	
  
  [#switch definition.name ]
    [#case "CANIF_PDU_LIST"]
    /* you used a old configuration !!! */
      [#break]    
    [#case "CANIF_RXPDU_LIST"]
      [#-- extract IF PDU list --]
      [#assign NameList = definition.value]
      [#assign _NameList_ = NameList?replace(","," ")]
      
      [#assign CanIfRxPduNameList = _NameList_?word_list]
      [#-- extract IF PDU list --]

      [#break]
    [#case "CANIF_TXPDU_LIST"]
      [#-- extract IF PDU list --]
      [#assign NameList = definition.value]
      [#assign _NameList_ = NameList?replace(","," ")]
      
      [#assign CanIfTxPduNameList = _NameList_?word_list]
      [#-- extract IF PDU list --]

      [#break]
    [#case "ISOTP_PDU_RX_LIST"]
    
/** @addtogroup TM_IsoTP_Cfg
 *  @{ */
      [#-- extract IF PDU list --]
      [#assign NameList = definition.value]
      [#assign _NameList_ = NameList?replace(","," ")]
      
      [#assign IsoTp_RxPduNameList = _NameList_?word_list]
      [#-- extract IF PDU list --]
/** @brief to use generic names for the PDUs */
enum class ${IsoTp_Prefix}_Rx${strPduIdType}
{
  [#list IsoTp_RxPduNameList as word] 
    [#assign PduName = word]
    [#assign CanIfRxPduNameList += ["MyTest" + "_" + PduName] ]
  /** @brief symbolic name for ${PduName} */
  ${IsoTp_Prefix}_Rx_${PduName},
  [/#list]
/* USER CODE BEGIN ${IsoTp_Prefix}_User_RxPDUs 0 */

/* USER CODE END ${IsoTp_Prefix}_User_RxPDUs 0 */
  ${IsoTp_Prefix}_Rx_unknownPdu
};

/* USER CODE BEGIN ${IsoTp_Prefix}_User_RxPDUs 1 */

/** @brief number of user defined RxPdu-Names 
    @details This define must be edit if added User_RxPDUs to the enum ${IsoTp_Prefix}_${strPduIdType} */
#define ${IsoTp_Prefix?upper_case}_RXPDU_USERCOUNT  0

/* USER CODE END ${IsoTp_Prefix}_User_RxPDUs 1 */

/** @brief number of all RxPdu-Names 
 *  @details this will be used to define the used memory to handle the RxPdus */
#define ${IsoTp_Prefix?upper_case}_RXPDU_COUNT ( ${IsoTp_RxPduNameList?size} + ${IsoTp_Prefix?upper_case}_RXPDU_USERCOUNT )

/** @} */ // end of grouping TM_IsoTP_Cfg

      [#break]
    [#case "ISOTP_PDU_TX_LIST"]
    
/** @addtogroup TM_IsoTP_Cfg
 *  @{ */
      [#-- extract IF PDU list --]
      [#assign NameList = definition.value]
      [#assign _NameList_ = NameList?replace(","," ")]
      
      [#assign IsoTp_TxPduNameList = _NameList_?word_list]
      [#-- extract IF PDU list --]
/** @brief to use generic names for the PDUs */
enum class ${IsoTp_Prefix}_Tx${strPduIdType}
{
  [#list IsoTp_TxPduNameList as word] 
    [#assign PduName = word]
    [#assign CanIfTxPduNameList += ["MyTest" + "_" + PduName] ]
  /** @brief symbolic name for ${PduName} */
  ${IsoTp_Prefix}_Tx_${PduName},
  [/#list]
/* USER CODE BEGIN ${IsoTp_Prefix}_User_TxPDUs 0 */

/* USER CODE END ${IsoTp_Prefix}_User_TxPDUs 0 */
  ${IsoTp_Prefix}_Tx_unknownPdu
};

/* USER CODE BEGIN ${IsoTp_Prefix}_User_TxPDUs 1 */

/** @brief number of user defined RxPdu-Names
    @details This define must be edit if added User_TxPDUs to the enum ${IsoTp_Prefix}_${strPduIdType} */
#define ${IsoTp_Prefix?upper_case}_TXPDU_USERCOUNT  0

/* USER CODE END ${IsoTp_Prefix}_User_TxPDUs 1 */

/** @brief number of all TxPdu-Names 
 *  @details this will be used to define the used memory to handle the TxPdus */
#define ${IsoTp_Prefix?upper_case}_TXPDU_COUNT ( ${IsoTp_TxPduNameList?size} + ${IsoTp_Prefix?upper_case}_TXPDU_USERCOUNT )

/** @} */ // end of grouping TM_IsoTP_Cfg

      [#break]
      
[#-- handle the Fueltech FTCAN2.0 configuration --]      
      [#case "FT_Ecu"]
          [#if extractDebug_FTL > 0]
        /* we need 
        >> ${definition.name} #t#t ${definition.value}  */
          [/#if] [#-- end of extractDebug_FTL --]
        [#if definition.value != "unused" ]
          [#assign FT_EcuType = definition.value]
        [/#if] [#-- end of check for unsed device --]
      [#break]
      [#case "FT_ECU_StreamList"]
        [#-- this is the first parameter and will be the last read so we use it to generate a trigger for output the collected configuration --]
        [#assign FTConfigOk = "Ok"]
          [#if extractDebug_FTL > 0]
        /* we need 
        >> ${definition.name} #t#t ${definition.value}  */
          [/#if] [#-- end of extractDebug_FTL --]
          [#assign _FT_EcuStreamListC = definition.value?replace(","," ")]  
          [#assign _FT_EcuStreamList_ = _FT_EcuStreamListC?replace("|"," ")]  
          [#assign FT_EcuStreamList = _FT_EcuStreamList_?word_list ]
      [#break]
      [#case "FT_SwitchPanel"]
          [#if extractDebug_FTL > 0]
        /* we need 
        >> ${definition.name} #t#t ${definition.value} #t#t ${FTPanelUse} */
          [/#if] [#-- end of extractDebug_FTL --]
        [#if definition.value != "unused" ]
          [#assign FT_SwPType = definition.value]
        [/#if] [#-- end of check for unsed device --]
      [#break]
      [#case "FT_Nano"]
      [#case "FT_Device"]
          [#if extractDebug_FTL > 0]
        /* we need 
        >> ${definition.name} #t#t ${definition.value} */
          [/#if] [#-- end of extractDebug_FTL --]          
          [#if definition.value != "unused" ]
          /* there is a config for FT Device ${definition.value} */
            [#assign FT_DeviceType = definition.value]
            [#assign FT_DeviceId = "Why"]
          [/#if] [#-- end of check for unsed device --]
      [#break]
      [#case "FT_SwitchPanel_RW"]
          [#if extractDebug_FTL > 0]
        /* we need 
        >> ${definition.name} #t#t ${definition.value}  */
          [/#if] [#-- end of extractDebug_FTL --]
        [#assign FTPanelUse = definition.value]
      [#break]
      [#case "FT_Nano_RW"]
      [#case "FT_Device_RW"]
          [#if extractDebug_FTL > 0]
        /* we need 
        >> ${definition.name} #t#t ${definition.value}  */
          [/#if] [#-- end of extractDebug_FTL --]
        [#assign FTDeviceUse = definition.value]
      [#break]
[#-- end of handle the Fueltech FTCAN2.0 configuration --]  

  [#default]
  [#if definition.comments??]
/** ----------  ${definition.comments} -----------*/
  [#else]
/** -------- generated Value  -----------*/ 
  [/#if]
#define ${definition.name} #t#t ${definition.value} 
[#if definition.description??]${definition.description} [/#if]
  [/#switch] [#-- end of definition.name --]
	[/#list] [#-- end of  SWIP.defines as definition --]
[/#if] [#-- end of  SWIP.defines?? --]
[/#list] [#-- end of  SWIPdatas as SWIP --]

[#-- add fueltech pdu --]
[#if FT_DeviceType?? && FTDeviceUse??]
  [#if FTDeviceUse == "UseDevice"]
    [#if extractDebug_FTL > 0]
  /* we add it to CanFT_RxPduType*/
    [/#if] [#-- end of extractDebug_FTL --]
    [#assign FT_RxList += [FT_DeviceType] ]
    [#-- assign FT_TxList += [FT_DeviceType+"_Responce"] --]
  [#else]
    [#if extractDebug_FTL > 0]
    /* we add it to CanFT_TxPduType*/
    [/#if] [#-- end of extractDebug_FTL --]
    [#assign FT_TxList += [FT_DeviceType] ]
    [#assign FT_RxList += [FT_DeviceType+"_Responce"] ]
  [/#if]
[/#if] [#-- end of FT_DeviceType?? && FT_Device_Use?? --]

[#if FT_SwPType?? && FTPanelUse??]
  [#if FTPanelUse == "UseDevice" ]
    [#if extractDebug_FTL > 0]
      /* we add it to CanFT_RxPduType*/
    [/#if] [#-- end of extractDebug_FTL --]
    [#assign FT_RxList += [ "SwitchPanel_" + FT_SwPType ] ]
    [#assign FT_TxList += [ "SwitchPanel_" + FT_SwPType + "_Ctrl" ] ]
  [#else]
    [#if extractDebug_FTL > 0]
    /* we add it to CanFT_TxPduType*/
    [/#if] [#-- end of extractDebug_FTL --]
    [#assign FT_TxList += [ "SwitchPanel_" + FT_SwPType ] ]
    [#assign FT_RxList += [ "SwitchPanel_" + FT_SwPType + "_Ctrl" ] ]
  [/#if] [#-- end of check for unsed device --]
[/#if] [#-- end of FT_SwPType?? --]
[#-- end of add fueltech pdu --]

[#if FTConfigOk = "Ok"]
[#-- we generate the code for the FTCAN outside because of multiple dependencies --] 
[#if extractDebug_FTL > 0]
/* we have a valid FT configuration */
[/#if] [#-- end of extractDebug_FTL --]

  [#if FT_EcuType?? && FT_EcuStreamList??] [#-- -we have an ecu config to add --]
  [#if extractDebug_FTL > 0]
  /* we have a FT Ecu configuration */
  [/#if] [#-- end of extractDebug_FTL --]
  
    [#list FT_EcuStreamList as FT_EcuStreamName]
      [#assign FT_RxList += [FT_EcuType + "_" + FT_EcuStreamName?keep_after_last("x") ] ]
    [/#list] [#-- end of FT_EcuStreamList as FT_EcuStreamName --]
  [/#if] [#-- end of adding FT Ecu config --]

/** @addtogroup CanFT_Cfg
 *  @{ */
/** @brief to use generic names for the PDUs */
typedef enum
{
  [#list FT_RxList as FT_RxPdu]
  [#assign CanIfRxPduNameList += [FT_RxPdu] ]
  /** @brief symbolic name for ${FT_RxPdu} */
  ${FTCAN2p0_Prefix}_Rx_${FT_RxPdu},
  [/#list]
/* USER CODE BEGIN ${FTCAN2p0_Prefix}_User_RxPDUs 0 */

/* USER CODE END ${FTCAN2p0_Prefix}_User_RxPDUs 0 */
  [#assign UserCodeCounter++]
  ${FTCAN2p0_Prefix}_Rx_unknownPdu
}${FTCAN2p0_Prefix}_Rx${strPduIdType};

/* USER CODE BEGIN ${FTCAN2p0_Prefix}_User_RxPDUs 1 */

/** @brief number of user defined RxPdu-Names 
    @details This define must be edit if added User_RxPDUs to the enum ${FTCAN2p0_Prefix}_RxPduIdType */
#define ${FTCAN2p0_Prefix?upper_case}_RXPDU_USERCOUNT  0

/* USER CODE END ${FTCAN2p0_Prefix}_User_RxPDUs 1 */

/** @brief number of all RxPdu-Names 
 *  @details this will be used to define the used memory to handle the RxPdus */
#define ${FTCAN2p0_Prefix?upper_case}_RXPDU_COUNT ( ${FT_RxList?size} + ${FTCAN2p0_Prefix?upper_case}_RXPDU_USERCOUNT )

/** @} */ // end of grouping CanFT_Cfg

/** @addtogroup CanFT_Cfg
 *  @{ */
/** @brief to use generic names for the PDUs */
typedef enum
{
  [#list FT_TxList as FT_TxPdu]
  [#assign CanIfTxPduNameList += [FT_TxPdu] ]
  /** @brief symbolic name for ${FT_TxPdu} */
  ${FTCAN2p0_Prefix}_Tx_${FT_TxPdu},
  [/#list]
/* USER CODE BEGIN ${FTCAN2p0_Prefix}_User_TxPDUs 0 */

/* USER CODE END ${FTCAN2p0_Prefix}_User_TxPDUs 0 */
  [#assign UserCodeCounter++]
  ${FTCAN2p0_Prefix}_Tx_unknownPdu
}${FTCAN2p0_Prefix}_Tx${strPduIdType};

/* USER CODE BEGIN ${FTCAN2p0_Prefix}_User_TxPDUs 1 */

/** @brief number of user defined TxPdu-Names 
    @details This define must be edit if added User_RxPDUs to the enum ${FTCAN2p0_Prefix}_TxPduIdType */
#define ${FTCAN2p0_Prefix?upper_case}_TXPDU_USERCOUNT  0

/* USER CODE END ${FTCAN2p0_Prefix}_User_TxPDUs 1 */

/** @brief number of all TxPdu-Names 
 *  @details this will be used to define the used memory to handle the TxPdus */
#define ${FTCAN2p0_Prefix?upper_case}_TXPDU_COUNT ( ${FT_TxList?size} + ${FTCAN2p0_Prefix?upper_case}_TXPDU_USERCOUNT )

/** @} */ // end of grouping CanFT2p0_Cfg

[#else]
[#if extractDebug_FTL > 0]
/* we haven#t a valid FT configuration */
[/#if] [#-- end of extractDebug_FTL --]
[/#if] [#-- end of FTConfigOk = "Ok" --]

[#if CanIfRxPduNameList?? ]
/** @addtogroup TM_CanIfCfg
 *  @{ */
 
/** @brief to use generic names for the PDUs */
enum class ${CanIf_Prefix}_Rx${strPduIdType}
{
  [#list CanIfRxPduNameList as word] 
    [#assign PduName = word]
  /** @brief symbolic name for ${PduName} */
  ${CanIf_Prefix}_Rx_${PduName},
  [/#list]
/* USER CODE BEGIN ${CanIf_Prefix}_User_RxPDUs 0 */

/* USER CODE END ${CanIf_Prefix}_User_RxPDUs 0 */
  ${CanIf_Prefix}_Rx_unknownPdu
};

/* USER CODE BEGIN ${CanIf_Prefix}_User_RxPDUs 1 */

/** @brief number of user defined RxPdu-Names 
    @details This define must be edit if added User_RxPDUs to the enum ${CanIf_Prefix}_RxPduIdType */
#define ${CanIf_Prefix?upper_case}_RXPDU_USERCOUNT  0

/* USER CODE END ${CanIf_Prefix}_User_RxPDUs 1 */

/** @brief number of all RxPdu-Names 
 *  @details this will be used to define the used memory to handle the RxPdus */
#define ${CanIf_Prefix?upper_case}_RXPDU_COUNT ( ${CanIfRxPduNameList?size} + ${CanIf_Prefix?upper_case}_RXPDU_USERCOUNT )

/** @} */ // end of grouping TM_CanIfCfg
[/#if] [#-- end of CanIfRxPduNameList?? --]

[#if CanIfTxPduNameList??]
/** @addtogroup TM_CanIfCfg
 *  @{ */
/** @brief to use generic names for the PDUs */
enum class ${CanIf_Prefix}_Tx${strPduIdType}
{
  [#list CanIfTxPduNameList as word] 
    [#assign PduName = word]
  /** @brief symbolic name for ${PduName} */
  ${CanIf_Prefix}_Tx_${PduName},
  [/#list]
/* USER CODE BEGIN ${CanIf_Prefix}_User_TxPDUs 0 */

/* USER CODE END ${CanIf_Prefix}_User_TxPDUs 0 */
  ${CanIf_Prefix}_Tx_unknownPdu
};

/* USER CODE BEGIN ${CanIf_Prefix}_User_TxPDUs 1 */

/** @brief number of user defined RxPdu-Names
    @details This define must be edit if added User_TxPDUs to the enum ${CanIf_Prefix}_TxPduIdType */
#define ${CanIf_Prefix?upper_case}_TXPDU_USERCOUNT  0

/* USER CODE END ${CanIf_Prefix}_User_TxPDUs 1 */

/** @brief number of all TxPdu-Names 
 *  @details this will be used to define the used memory to handle the TxPdus */
#define ${CanIf_Prefix?upper_case}_TXPDU_COUNT ( ${CanIfTxPduNameList?size} + ${CanIf_Prefix?upper_case}_TXPDU_USERCOUNT )

/** @} */ // end of grouping TM_CanIfCfg
[/#if] [#-- end of CanIfTxPduNameList?? --]

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

#endif /*__ ${inclusion_protection}__ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
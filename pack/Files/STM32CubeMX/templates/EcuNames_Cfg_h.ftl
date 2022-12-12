[#ftl]
[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 0]
[#-- disableUserCode: a whitespace will enable --]
[#assign disableUserCode = " " ]
[#-- #assign disableUserCode = "disable" --]
[#-- Warning: this will erase all user code !!! --]
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

[#assign pduMember = {"preFix" : "", "rxList": [], "txList" : [] }]
[#assign pduMemberList = [] ]
[#assign protocolMemberList =[]]
[#assign protocolFiles_List = [ "MXTmpFiles/IsoTP_PduList.tmp",  "MXTmpFiles/CanFT_PduList.tmp" ]]
[#list protocolFiles_List as protocolTemplate ] 
  [#attempt]
    [#-- add Iso TP pdu --]
    [#import protocolTemplate as TPSnippet ]    
/* import ${TPSnippet.GetPrefix()} : ${TPSnippet.lastGenerated} */
    [#assign protocolImport = { "preFix" : TPSnippet.GetPrefix(), 
                                "rxList": TPSnippet.GetRxList(), 
                                "txList" : TPSnippet.GetTxList() }]
    [#assign protocolMemberList += [protocolImport] ]
  [#recover]
/* can't find ${protocolTemplate} */
  [/#attempt]
[/#list]

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

[#-- ########################## --]
[#-- end of extract definitions --]
[#-- ########################## --]

[#list protocolMemberList as myMember ]
[#assign myRxList = myMember.rxList ]
[#assign rxItemCounter = 0]
#t
[#compress]
/** @addtogroup TM_${myMember.preFix}_Cfg 
#t#t@{ */
/** @brief to use generic names for the PDUs */
enum class ${myMember.preFix}_Rx${strPduIdType}
{
  [#list myRxList as rxItem ]
  [#assign rxItemCounter += 1]
[#attempt]
#t/** @brief symbolic name for ${rxItem.name} */
#t${myMember.preFix}_Rx_${rxItem.name},
[#recover]
/* ##################################### */
/** there is an unsupported member config */
#t#t#t${myMember.preFix}_Rx_Dummy_${rxItemCounter},
/* ##################################### */
[/#attempt]
  [/#list]
/* USER${disableUserCode}CODE BEGIN ${myMember.preFix}_User_RxPDUs 0 */
#t
/* USER${disableUserCode}CODE END ${myMember.preFix}_User_RxPDUs 0 */
    
#t/** @brief symbolic name for unknownPdu */
#t${myMember.preFix}_Rx_unknownPdu
};
#t
/* USER${disableUserCode}CODE BEGIN ${myMember.preFix}_User_RxPDUs 1 */
#t
/** @brief number of user defined RxPdu-Names 
#t#t@details This define must be edit if added User_RxPDUs to the enum ${myMember.preFix}_${strPduIdType} */
#define ${myMember.preFix?upper_case}_RXPDU_USERCOUNT  0
#t
/* USER${disableUserCode}CODE END ${myMember.preFix}_User_RxPDUs 1 */
#t
/** @brief number of all RxPdu-Names 
#t#t@details this will be used to define the used memory to handle the RxPdus */
#define ${myMember.preFix?upper_case}_RXPDU_COUNT ( ${myRxList?size } + ${myMember.preFix?upper_case}_RXPDU_USERCOUNT )
#t
/** @} */ // end of grouping TM_${myMember.preFix}_Cfg
#t
[/#compress]
#t
[#assign myTxList = myMember.txList ]
[#assign txItemCounter = 0]
[#compress]
/** @addtogroup TM_${myMember.preFix}_Cfg 
#t#t@{ */
/** @brief to use generic names for the PDUs */
enum class ${myMember.preFix}_Tx${strPduIdType}
{
  [#list myTxList as txItem]
  [#assign txItemCounter += 1]
[#attempt]
#t/** @brief symbolic name for ${txItem.name} */
#t${myMember.preFix}_Tx_${txItem.name},
[#recover]
/* ##################################### */
/** there is an unsupported member config */
#t#t#t${myMember.preFix}_Tx_Dummy_${txItemCounter},
/* ##################################### */
[/#attempt]
  [/#list]
/* USER${disableUserCode}CODE BEGIN ${myMember.preFix}_User_RxPDUs 0 */
#t
/* USER${disableUserCode}CODE END ${myMember.preFix}_User_RxPDUs 0 */
    
#t/** @brief symbolic name for unknownPdu */
#t${myMember.preFix}_Tx_unknownPdu 
};
#t
/* USER${disableUserCode}CODE BEGIN ${myMember.preFix}_User_TxPDUs 1 */
#t
/** @brief number of user defined RxPdu-Names
#t* @details This define must be edit if added User_TxPDUs to the enum ${myMember.preFix}_${strPduIdType} */
#define ${myMember.preFix?upper_case}_TXPDU_USERCOUNT  0
#t
/* USER${disableUserCode}CODE END ${myMember.preFix}_User_TxPDUs 1 */
#t
/** @brief number of all TxPdu-Names 
#t* @details this will be used to define the used memory to handle the TxPdus */
#define ${myMember.preFix?upper_case}_TXPDU_COUNT ( ${myTxList?size } + ${myMember.preFix?upper_case}_TXPDU_USERCOUNT )
#t
/** @} */ // end of grouping TM_${myMember.preFix}_Cfg
#t
[/#compress]
[/#list] [#-- end of protocolMemberList as myMember --]

[#if CanIfRxPduNameList?? ][#compress]
/** @addtogroup TM_CanIfCfg
#t#t@{ */
 
/** @brief to use generic names for the PDUs */
enum class ${CanIf_Prefix}_Rx${strPduIdType}
{
  [#list CanIfRxPduNameList as word] 
    [#assign PduName = word]
#t/** @brief symbolic name for ${PduName} */
#t${CanIf_Prefix}_Rx_${PduName},
  [/#list]
#t/* V-----V----V----V-----V */
#t/* add imported list items */
  [#assign pduMemberCounter = 0]
  [#if protocolMemberList?? ]
    [#list protocolMemberList as protocolMember]
      [#assign protocolRxList = protocolMember.rxList]
      [#list protocolRxList as rxPdu]
        [#assign pduMemberCounter += 1]
[#attempt]
#t/** @brief symbolic name for ${rxPdu.name}} */
#t${CanIf_Prefix}_Rx_${rxPdu.name},
[#recover]
/* ##################################### */
/* there is an unsupported member config */
#t#t#tL_PDU_${protocolMember.preFix}_Rx_Dummy_${pduMemberCounter},
/* ##################################### */
[/#attempt]
      [/#list] [#-- end of protocolRxList as rxPdu --]
    [/#list] [#-- end of protocolMemberList as protocolMember--]
  [/#if] [#-- end of protocolMemberList?? -> imported list items --]
/* USER${disableUserCode}CODE BEGIN ${CanIf_Prefix}_User_RxPDUs 0 */
#t
/* USER${disableUserCode}CODE END ${CanIf_Prefix}_User_RxPDUs 0 */
#t${CanIf_Prefix}_Rx_unknownPdu
};
#t
/* USER${disableUserCode}CODE BEGIN ${CanIf_Prefix}_User_RxPDUs 1 */
#t
/** @brief number of user defined RxPdu-Names 
#t#t@details This define must be edit if added User_RxPDUs to the enum ${CanIf_Prefix}_RxPduIdType */
#define ${CanIf_Prefix?upper_case}_RXPDU_USERCOUNT  0
#t
/* USER${disableUserCode}CODE END ${CanIf_Prefix}_User_RxPDUs 1 */
#t
/** @brief number of all RxPdu-Names 
#t#t@details this will be used to define the used memory to handle the RxPdus */
#define ${CanIf_Prefix?upper_case}_RXPDU_COUNT ( ${CanIfRxPduNameList?size + pduMemberCounter} + ${CanIf_Prefix?upper_case}_RXPDU_USERCOUNT )
#t
/** @} */ // end of grouping TM_CanIfCfg
[/#compress][/#if] [#-- end of CanIfRxPduNameList?? --]

[#if CanIfTxPduNameList??][#compress]
/** @addtogroup TM_CanIfCfg
#t#t@{ */
/** @brief to use generic names for the PDUs */
enum class ${CanIf_Prefix}_Tx${strPduIdType}
{
  [#list CanIfTxPduNameList as word] 
    [#assign PduName = word]
#t/** @brief symbolic name for ${PduName} */
#t${CanIf_Prefix}_Tx_${PduName},
  [/#list]
#t/* V-----V----V----V-----V */
#t/* add imported list items */
  [#assign pduMemberCounter = 0]
  [#if protocolMemberList?? ]
    [#list protocolMemberList as protocolMember]
      [#assign protocolTxList = protocolMember.txList]
      [#list protocolTxList as txPdu]
        [#assign pduMemberCounter += 1]
[#attempt]
#t/** @brief symbolic name for ${txPdu.name}} */
#t${CanIf_Prefix}_Tx_${txPdu.name},
[#recover]
/* ##################################### */
/* there is an unsupported member config */
#t#t#tL_PDU_${protocolMember.preFix}_Tx_Dummy_${pduMemberCounter},
/* ##################################### */
[/#attempt]
      [/#list] [#-- end of protocolRxList as txPdu --]
    [/#list] [#-- end of protocolMemberList as protocolMember--]
  [/#if] [#-- end of protocolMemberList?? -> imported list items --]
/* USER${disableUserCode}CODE BEGIN ${CanIf_Prefix}_User_TxPDUs 0 */
#t
/* USER${disableUserCode}CODE END ${CanIf_Prefix}_User_TxPDUs 0 */
#t${CanIf_Prefix}_Tx_unknownPdu
};

#t
/* USER${disableUserCode}CODE BEGIN ${CanIf_Prefix}_User_TxPDUs 1 */
#t
/** @brief number of user defined RxPdu-Names
#t#t@details This define must be edit if added User_TxPDUs to the enum ${CanIf_Prefix}_TxPduIdType */
#define ${CanIf_Prefix?upper_case}_TXPDU_USERCOUNT  0
#t
/* USER${disableUserCode}CODE END ${CanIf_Prefix}_User_TxPDUs 1 */
#t
/** @brief number of all TxPdu-Names 
#t#t@details this will be used to define the used memory to handle the TxPdus */
#define ${CanIf_Prefix?upper_case}_TXPDU_COUNT ( ${CanIfTxPduNameList?size + pduMemberCounter} + ${CanIf_Prefix?upper_case}_TXPDU_USERCOUNT )
#t
/** @} */ // end of grouping TM_CanIfCfg
[/#compress][/#if] [#-- end of CanIfTxPduNameList?? --]

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

#endif /*__ ${inclusion_protection}__ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
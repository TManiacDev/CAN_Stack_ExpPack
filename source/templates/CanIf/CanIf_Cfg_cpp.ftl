[#ftl]
[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 0]
[#list SWIPdatas as SWIP]  
[#assign instName = SWIP.ipName]   
[#assign fileName = SWIP.fileName]   
[#assign version = SWIP.version]   
/**
  ******************************************************************************
  * @section CanIF_CFG_C Code generation
  * File Name          : ${fileName}
  * Description        : This file provides code for the configuration
  *                      of the ${name} instances.
  *
  * MiddleWare name    : ${instName}
  * MiddleWare version : ${version}
  * Last updated       : ${aDate}  ${aTime}
  *
  ******************************************************************************
[@common.optinclude name=mxTmpFolder+"/license.tmp"/][#-- include License text --]
  ******************************************************************************
  */
[/#list] [#-- end of SWIPdatas as SWIP --] 
  
[#assign s = fileName]
[#if s?contains("/")]
  [#assign s = s?keep_after_last("/")]
[/#if]
[#assign dashReplace = s?replace(".","_")]
[#assign dashedFileNamed = dashReplace?replace("-","_")]
[#assign UserCodeCounter = 0]

[#-- to handle linked PDU names we import this listes --] 
[#assign pduMember = {"preFix" : "", "rxList": [], "txList" : [] }]
[#assign pduMemberList = [] ]
[#assign protocolFiles_List = [ "MXTmpFiles/IsoTP_PduList.tmp",  "MXTmpFiles/CanFT_PduList.tmp" ]]
[#list protocolFiles_List as protocolTemplate ] 
  [#attempt]
    [#-- add from template --]
    [#import protocolTemplate as TPSnippet ]
/* import ${TPSnippet.GetPrefix()} : ${TPSnippet.lastGenerated} */    
  [#recover]
/* can't find ${protocolTemplate} */
  [/#attempt]
  [#if TPSnippet??] [#-- we have a TPSnippet on successful template open --]
    [#assign pduTp = {"preFix"    : TPSnippet.GetPrefix(),
                      "rxList"    : TPSnippet.GetRxList(), 
                      "txList"    : TPSnippet.GetTxList() }]
    [#assign pduMemberList += [pduTp] ]
  [/#if] [#-- TPSnippet?? --]
[/#list]
/* ${pduMemberList?size} */
[#-- end of to handle linked PDU names we import this listes --] 

[#-- Global variables --]
[#assign CanIf_Prefix = "CanIf"]
[#assign IsoTp_Prefix = "IsoTP"]
[#assign FTCAN2p0_Prefix = "CanFT"]
[#assign CanNM_Prefix = "CanNM"]
[#assign CanTSync_Prefix = "CanTSync"]
[#assign Xcp_Prefix = "CanXcp"]
[#assign strPduIdType = "PduIdType" ]

[#-- SWIPdatas is a list of SWIPconfigModel --]  
[#list SWIPdatas as SWIP]
  [#if includes??]
/* Includes ------------------------------------------------------------------*/
    [#list includes as include]
#include "${include}"
    [/#list] [#-- end of list includes as include --]
  [/#if] [#-- if end of includes?? --]

/* Includes ------------------------------------------------------------------*/
#include <CanIf.h>

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

[#if extractDebug_FTL > 0]
/* ########################################################################## */
[/#if] [#-- end of extractDebug_FTL --]
[#if SWIP.defines??]
	[#list SWIP.defines as definition]	
  
      [#assign List = definition.value]
      [#assign _ListC = List?replace(","," ")]  
      [#assign _List_ = _ListC?replace("|"," ")]  
      
  [#switch definition.name ]  
      [#-- extract IF PDU list --]    
    [#case "CANIF_RXPDU_LIST"]   
      [#assign RxPduNameList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxPduNameList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]  
    [#case "CANIF_TXPDU_LIST"]
      [#assign TxPduNameList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract TxPduNameList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract IF CAN ID list --]
    [#case "CANIF_RXID_LIST"]
      [#assign RxIdList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxIdList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
    [#case "CANIF_TXID_LIST"] 
      [#assign TxIdList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract TxIdList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract IF ID Mask list --]
    [#case "CANIF_RXMASK_LIST"]
      [#assign RxMaskList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxMaskList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
    [#case "CANIF_TXMASK_LIST"] 
      [#assign TxMaskList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract TxMaskList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract IF Message Lengt list --]
    [#case "CANIF_RXMSGLENGTH_LIST"]
      [#assign RxLengthList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxLengthList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
    [#case "CANIF_TXMSGLENGTH_LIST"] 
      [#assign TxLengthList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract TxLengthList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract IF Controller list --]
    [#case "CANIF_RX_CONTROLLER_LIST"]
      [#assign RxControllerList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxControllerList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
    [#case "CANIF_TX_CONTROLLER_LIST"] 
      [#assign TxControllerList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract TxControllerList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract IF PDU list --]    
    [#case "CANIF_RX_TARGETPDU_LIST"]   
      [#assign RxTargetPduNameList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxTargetPduNameList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]  
    [#case "CANIF_TX_TARGETPDU_LIST"]
      [#assign TxTargetPduNameList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract TxTargetPduNameList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract IF Upper Layer list --]
    [#case "CANIF_RXUL_LIST"]
      [#assign RxUpperLayerList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxUpperLayerList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
    [#case "CANIF_TXUL_LIST"] 
      [#assign TxUpperLayerList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract TxUpperLayerList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      
[#-- handle the IsoTp configuration --]  
      [#case "ISOTP_PDU_RX_LIST"]
[#if extractDebug_FTL > 0]
        [#assign _IsoTp_RxPduListC = definition.value?replace(","," ")]
/* ISOTP_PDU_RX_LIST is ${_IsoTp_RxPduListC} */
        [#assign _IsoTp_RxPduList_ = _IsoTp_RxPduListC?replace("|"," ")]
        [#assign IsoTp_RxPduList = _IsoTp_RxPduList_?word_list ]
[/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#case "ISOTP_PDU_TX_LIST"]
[#if extractDebug_FTL > 0]
        [#assign _IsoTp_txPduListC = definition.value?replace(","," ")]
/* ISOTP_PDU_TX_LIST is ${_IsoTp_txPduListC} */
        [#assign _IsoTp_txPduList_ = _IsoTp_txPduListC?replace("|"," ")]
        [#assign IsoTp_TxPduList = _IsoTp_txPduList_?word_list ]
[/#if] [#-- end of extractDebug_FTL --]
      [#break]
[#-- end of handle the IsoTp configuration --]  

    [#default]
      [#-- notthing to do --]
      [#break]
  [/#switch] [#-- end of definition.name --]
  
	[/#list] [#-- end of  SWIP.defines as definition --]
[/#if] [#-- end of  SWIP.defines?? --]
[/#list] [#-- end of  SWIPdatas as SWIP --]
[#if extractDebug_FTL > 0]
/* ########################################################################## */
[/#if] [#-- end of extractDebug_FTL --]

[#-- add fueltech pdu --]
[#if FT_DeviceType?? && FT_Device_Use??]
// we have a FT Device config 
  [#switch FT_Device_Use]
    [#case "BeDevise"]
      /* there is a config to simulate FT ${FT_DeviceType} */
      [#assign RxPduNameList += [FT_DeviceType] ]  
      [#assign RxIdList += ["E:" + FT_DeviceCanId + "000"] ]
      [#assign RxMaskList += ["E:" + FT_DeviceCanId + "000" + " /** @todo check this masking */"] ]
      [#assign RxLengthList += ["8"] ]
      [#assign RxControllerList += ["M"] ]
      [#assign RxTargetPduNameList += [FT_DeviceType] ]
      [#assign RxUpperLayerList += ["FT2p0"] ]
      
      [#assign TxPduNameList += [FT_DeviceType] ]  
      [#assign TxIdList += ["E:" + FT_DeviceCanId + "0FF"] ]
      [#assign TxMaskList += ["E:0x0"] ]
      [#assign TxLengthList += ["8"] ]
      [#assign TxControllerList += ["M"] ]
      [#assign TxTargetPduNameList += [FT_DeviceType] ]
      [#assign TxUpperLayerList += ["FT2p0"] ]
    [#break]
    [#case "UseDevice"]
      /* there is a config to read FT ${FT_DeviceType} */
      [#assign RxPduNameList += [FT_DeviceType] ]  
      [#assign RxIdList += ["E:" + FT_DeviceCanId + "0FF"] ]
      [#assign RxMaskList += ["E:0x0"] ]
      [#assign RxLengthList += ["8"] ]
      [#assign RxControllerList += ["M"] ]
      [#assign RxTargetPduNameList += [FT_DeviceType] ]
      [#assign RxUpperLayerList += ["FT2p0"] ]
      
      [#-- no tx needed --]
    [#break]
    [#default]
  [/#switch] [#-- end of definition.value (Nano read or write ) --]
[/#if] [#-- end of FT_DeviceType?? && FT_Device_Use?? --]

[#if FT_SwPType?? && FT_Swp_Use??]
  [#switch FT_Swp_Use]
    [#case "BeDevice"]
      /* there is a config to simulate FT Panel */
      [#assign RxPduNameList += ["SwitchPanel_"+ FT_SwPType + "_Ctrl"] ]  
      [#assign RxIdList += ["E:" + FT_SwPId + "321"] ]
      [#assign RxMaskList += ["E:0x0"] ]
      [#assign RxLengthList += ["8"] ]
      [#assign RxControllerList += ["M"] ]
      [#assign RxTargetPduNameList += ["SwitchPanel_"+ FT_SwPType + "_Ctrl"] ]
      [#assign RxUpperLayerList += ["FT2p0"] ]
      
      [#assign TxPduNameList += ["SwitchPanel_"+ FT_SwPType] ]  
      [#assign TxIdList += ["E:" + FT_SwPId + "320"] ]
      [#assign TxMaskList += ["E:0x0"] ]
      [#assign TxLengthList += ["8"] ]
      [#assign TxControllerList += ["M"] ]
      [#assign TxTargetPduNameList += ["SwitchPanel_"+ FT_SwPType] ]
      [#assign TxUpperLayerList += ["FT2p0"] ]
    [#break]
    [#case "UseDevice"]
      /* there is a config to read FT Panel */
      [#assign RxPduNameList += ["SwitchPanel_"+ FT_SwPType] ]  
      [#assign RxIdList += ["E:" + FT_SwPId + "320"] ]
      [#assign RxMaskList += ["E:0x0"] ]
      [#assign RxLengthList += ["8"] ]
      [#assign RxControllerList += ["M"] ]
      [#assign RxTargetPduNameList += ["SwitchPanel_"+ FT_SwPType] ]
      [#assign RxUpperLayerList += ["FT2p0"] ]
      
      [#assign TxPduNameList += ["SwitchPanel_"+ FT_SwPType + "_Ctrl"] ]  
      [#assign TxIdList += ["E:" + FT_SwPId + "321"] ]
      [#assign TxMaskList += ["E:0x0"] ]
      [#assign TxLengthList += ["8"] ]
      [#assign TxControllerList += ["M"] ]
      [#assign TxTargetPduNameList += ["SwitchPanel_"+ FT_SwPType + "_Ctrl"] ]
      [#assign TxUpperLayerList += ["FT2p0"] ]
    [#break]
    [#default]
  [/#switch] [#-- end of definition.value (SwitchPanel read or write ) --]
[/#if] [#-- end of FT_SwPType?? && FT_Device_Use?? --]

[#if FT_EcuType?? && FT_EcuStreamList?? ]
  [#list FT_EcuStreamList as FT_EcuStreamName]
    [#assign RxPduNameList += [FT_EcuType + "_" + FT_EcuStreamName?keep_after_last("x") ] ]
    [#assign RxIdList += ["E:" + FT_EcuId + FT_EcuStreamName?keep_after_last("x")] ]
    [#assign RxMaskList += ["E:0x0"] ]
    [#assign RxLengthList += ["8"] ]
    [#assign RxControllerList += ["M"] ]
    [#assign RxTargetPduNameList += [FT_EcuType + "_" + FT_EcuStreamName?keep_after_last("x") ] ]
    [#assign RxUpperLayerList += ["FT2p0"] ]
  [/#list] [#-- end of FT_EcuStreamList as FT_EcuStreamName --]
[/#if] [#-- end of FT_EcuType?? && FT_EcuStreamList?? --]
[#-- end of add fueltech pdu --]

[#if RxPduNameList?? && (RxPduNameList?size > 0)]
[#-- test for all RX lists have the same length --]
[#if extractDebug_FTL > 0]
// FTL Debug: test the Rx PDU Lists 
[/#if] [#-- end of extractDebug_FTL --]
    [#if RxIdList??] 
[#if extractDebug_FTL > 0]
/* RxPduNameList has ${RxPduNameList?size} elements */
[/#if] [#-- end of extractDebug_FTL --]
      [#if RxIdList?size != RxPduNameList?size] 
    /* >>> @attention Rx ID List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing Rx ID List */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxMaskList??] 
      [#if RxMaskList?size != RxPduNameList?size] 
    /* >>> @attention Rx Mask List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing Rx Mask List */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxLengthList??] 
      [#if RxLengthList?size != RxPduNameList?size] 
    /* >>> @attention Rx Length List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing Rx Length List */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxControllerList??] 
      [#if RxControllerList?size != RxPduNameList?size] 
    /* >>> @attention Rx Controller List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing Rx Controller List */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxTargetPduNameList??] 
      [#if RxTargetPduNameList?size != RxPduNameList?size] 
    /* >>> @attention Rx Target PDU List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing Rx Target PDU List */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxUpperLayerList??] 
      [#if RxUpperLayerList?size != RxPduNameList?size] 
    /* >>> @attention Rx Upper Layer List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing Rx Upper Layer List */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
[#-- end of test for all lists hav the same length --]
[#else]
/* there is no Rx PDU List */
    [#assign RxPduTestReturn = "failed" ]
[/#if] [#--  end of PduNameList?? --]

[#if TxPduNameList?? && (TxPduNameList?size > 0)]
[#-- test for all TX lists have the same length --]
[#if extractDebug_FTL > 0]
// FTL Debug: test the Tx PDU Lists 
[/#if] [#-- end of extractDebug_FTL --]
    [#if TxIdList??] 
[#if extractDebug_FTL > 0]
/* TxPduNameList has ${TxPduNameList?size} elements */
[/#if] [#-- end of extractDebug_FTL --]
      [#if TxIdList?size != TxPduNameList?size] 
    /* >>> @attention Tx ID List with wrong count of members */ 
        [#assign TxPduTestReturn = "failed"]
      [#else] 
        [#if !TxPduTestReturn??][#assign TxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing Tx ID List */ 
        [#assign TxPduTestReturn = "failed"]
    [/#if]
    
    [#if TxMaskList??] 
      [#if TxMaskList?size != TxPduNameList?size] 
    /* >>> @attention Tx Mask List with wrong count of members */ 
        [#assign TxPduTestReturn = "failed"]
      [#else] 
        [#if !TxPduTestReturn??][#assign TxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing Tx Mask List */ 
        [#assign TxPduTestReturn = "failed"]
    [/#if]
    
    [#if TxLengthList??] 
      [#if TxLengthList?size != TxPduNameList?size] 
    /* >>> @attention Tx Length List with wrong count of members */ 
        [#assign TxPduTestReturn = "failed"]
      [#else] 
        [#if !TxPduTestReturn??][#assign TxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing Tx Length List */ 
        [#assign TxPduTestReturn = "failed"]
    [/#if]
    
    [#if TxControllerList??] 
      [#if TxControllerList?size != TxPduNameList?size] 
    /* >>> @attention Tx Controller List with wrong count of members */ 
        [#assign TxPduTestReturn = "failed"]
      [#else] 
        [#if !TxPduTestReturn??][#assign TxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing Tx Controller List */ 
        [#assign TxPduTestReturn = "failed"]
    [/#if]
    
    [#if TxTargetPduNameList??] 
      [#if TxTargetPduNameList?size != TxPduNameList?size] 
    /* >>> @attention Tx Target PDU List with wrong count of members */ 
        [#assign TxPduTestReturn = "failed"]
      [#else] 
        [#if !TxPduTestReturn??][#assign TxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing Tx Target PDU List */ 
        [#assign TxPduTestReturn = "failed"]
    [/#if]
    
    [#if TxUpperLayerList??] 
      [#if TxUpperLayerList?size != TxPduNameList?size] 
    /* >>> @attention Tx Upper Layer List with wrong count of members */ 
        [#assign TxPduTestReturn = "failed"]
      [#else] 
        [#if !TxPduTestReturn??][#assign TxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing Tx Upper Layer List */ 
        [#assign TxPduTestReturn = "failed"]
    [/#if]
[#-- end of test for all lists hav the same length --]
[#else]
/* there is no Tx PDU List */
    [#assign TxPduTestReturn = "failed" ]
[/#if] [#--  end of PduNameList?? --]
[#if extractDebug_FTL > 0]
/* ########################################################################## */
[/#if] [#-- end of extractDebug_FTL --]

[#-- function to separate CAN ID, Extend Bit --]
[#function GetMessageType MsgIdString ]
  [#if MsgIdString?starts_with("E") ] [#return "CANIF_EXTID"]
  [#else] [#return "CANIF_STDID"]
  [/#if]
[/#function]

[#function GetMessageId MsgIdString ]
  [#assign IdSperator = MsgIdString[0]+MsgIdString[1] ] 
  [#return MsgIdString?keep_after(IdSperator)]
[/#function]
[#-- end of function to separate CAN ID, Extend Bit, RTR Bit --]

[#-- function to extend the CAN controller name --]
[#function GetControllerName NameString]
  [#if NameString?starts_with("C") == true ]
    [#-- we must do a extraction of the channel number from name --]
    [#return "CanMasterController"]
  [#else]
  [#if NameString?starts_with("M") != true ]
    [#return "CanSlaveController"]
  [#else]
    [#return "CanMasterController"]
  [/#if]
  [/#if]
[/#function]
[#-- end of function to extend the CAN controller name --]

[#-- function to create the PDU enum used in source code --]
[#function GetNPduName N_PduString N_PduUlString RxTx]
  [#switch N_PduUlString]
    [#case CanIf_Prefix]
      [#assign RetName = CanIf_Prefix + "_" + RxTx + strPduIdType + "::" + CanIf_Prefix + "_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "CanNM"]
      [#assign RetName = CanNM_Prefix + "_" + RxTx + strPduIdType + "::" + CanNM_Prefix + "_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "CanTP"] [#-- this is the AUTOSAR name --]
      [#assign RetName = IsoTp_Prefix + "_" + RxTx + strPduIdType + "::" + IsoTp_Prefix + "_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "IsoTP"] [#-- maybe we use the international name --]
      [#assign RetName = IsoTp_Prefix + "_" + RxTx + strPduIdType + "::" + IsoTp_Prefix + "_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "CanTSync"]
      [#assign RetName = CanTSync_Prefix + "_" + RxTx + strPduIdType + "::" + CanTSync_Prefix + "_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "XCP"]
      [#assign RetName = Xcp_Prefix + "_" + RxTx + strPduIdType + "::" + Xcp_Prefix + "_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "FT2p0"]
      [#assign RetName = FTCAN2p0_Prefix + "_" + RxTx + strPduIdType + "::" + FTCAN2p0_Prefix + "_" + RxTx + "_" + N_PduString ]
      [#break]
    [#default]
      [#assign RetName = "CanUndefUl_" + RxTx + "_" + N_PduString ]
      [#break]
  [/#switch] [#-- end of N_PduUlString --]
  [#return RetName]
[/#function]
[#-- end of function to create the PDU enum used in source code --]

/* ########################################################################## */
/*          CAN Interface / Abstraction configuration                         */

/** @addtogroup TM_CanIf_RxPduCfg
 *  @{ */

/** @brief This is a test configuration for RxPdu
 *  @details
 *  - PDU Name (enum)
 *  - CanId (ID, (unusedBit), RTR, EXT)
 *  - IdMask (ID, (unusedBit), RTR, EXT)
 *  - MsgLength
 *  - Name for Instance
 *  - Name of the upper layer N-PDU
 *  - name of upper layer
 *
 *  @warning the struct must have the same order like CanIf_RxPduIdType */
[#if RxPduTestReturn?? && RxPduTestReturn == "passed" ]
/* ->->-> we have a valid Rx Pdu List */
EXTERN_CONST( CanIf_RxPduCfgType, TM_CANIF_CONFIG_DATA ) MyTest_RxPduConfig[] =
{
  [#list RxPduNameList as RxPDU ]
  [#assign RxIndex = RxPduNameList?seq_index_of(RxPDU)]
  {  /* ${RxIndex} */
    .L_PDU_Name = ${GetNPduName(RxPDU, CanIf_Prefix, "Rx")}, /* ${CanIf_Prefix}_Rx_${RxPDU} */
    .CanId = { ${GetMessageId(RxIdList[RxIndex])}, _UNUSED_VAR_, CANIF_NO_RTR, ${GetMessageType(RxIdList[RxIndex])} },
    .IdMask = { ${GetMessageId(RxMaskList[RxIndex])}, _UNUSED_VAR_, CANIF_NO_RTR, ${GetMessageType(RxMaskList[RxIndex])} },
    .MsgLength = ${RxLengthList[RxIndex]},
    .InstanceName = ${GetControllerName(RxControllerList[RxIndex])},
    .N_PDU_Name = (ComStack_PduType)${GetNPduName(RxTargetPduNameList[RxIndex], RxUpperLayerList[RxIndex], "Rx")},
    [#if RxUpperLayerList[RxIndex]?starts_with("u")]
    .ULName = CanIfUL_undefined
    [#else]
    .ULName = CanIfUL_${RxUpperLayerList[RxIndex]}
    [/#if]
  },
  [/#list][#-- end of RxPduNameList as PDU --]
#t/* V-----V----V----V-----V */
#t/* add imported list items */
  [#if pduMemberList?? ][#compress]
    [#assign pduMemberCounter = 0]
    [#list pduMemberList as pduMember]
      [#assign RxList = pduMember.rxList]
      [#list RxList as rxPdu]
        [#assign pduMemberCounter += 1]
#t{#t/* ${RxIndex+pduMemberCounter} */
[#attempt]
#t#t.L_PDU_Name = ${GetNPduName(rxPdu.name, CanIf_Prefix, "Rx")}, /* ${CanIf_Prefix}_Rx_${rxPdu.name} */
#t#t.CanId = { ${GetMessageId(rxPdu.canId)}, _UNUSED_VAR_, CANIF_NO_RTR, ${GetMessageType(rxPdu.canId)} },
#t#t.IdMask = { ${GetMessageId(rxPdu.maskId)}, _UNUSED_VAR_, CANIF_NO_RTR, ${GetMessageType(rxPdu.maskId)} },
#t#t.MsgLength = ${rxPdu.length},
#t#t.InstanceName = ${GetControllerName(rxPdu.controller)}, 
#t#t.N_PDU_Name = (ComStack_PduType)${rxPdu.nPduName},
    [#if pduMember.preFix?starts_with("u")]
#t#t.ULName = CanIfUL_undefined
    [#else]
#t#t.ULName = CanIfUL_${pduMember.preFix}
    [/#if]
[#recover]
/* ##################################### */
/* there is an unsupported member config */
[#if rxPdu.name??]
#t#t.L_PDU_Name = (ComStack_PduType)${GetNPduName(rxPdu.name, CanIf_Prefix, "Rx")}, /* ${CanIf_Prefix}_Rx_${rxPdu.name} */
[#else]
[#assign genericUnkown = "L_PDU_" + pduMember.preFix + "_Rx_Dummy_" + (pduMemberCounter)]
#t#t.L_PDU_Name = (ComStack_PduType)CanIf_RxPduIdType::${genericUnkown}
[/#if]
#t#t/* .InstanceName = we should disable the controller */
/* ##################################### */
[/#attempt]
#t},
      [/#list] [#-- end of RxList as rxPdu --]
    [/#list]
  [/#compress][/#if] [#-- pduMemberList?? -> imported list items --]
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */
  {
    .L_PDU_Name = (CanIf_RxPduIdType)L_PDU_Dummy_for_Test,
    .CanId = { 0x123456, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_EXTID },
    .IdMask = { 0x0, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_EXTID },
    .MsgLength = 8,
    .InstanceName = CanMasterController,
    .N_PDU_Name = N_PDU_Dummy_for_Test,
    .ULName = CanIfUL_CDD
  }
/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
[#assign UserCodeCounter++]
};
/** @} */ // end of grouping TM_CanIf_RxPduCfg
[#else]
/* #+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+ */
/* There is a problem on configuration of the Rx PDU List */
/* #+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+ */
[/#if]

/** @brief This is a test configuration for TxPdu
 *  @details
 *  - PDU Name (enum)
 *  - CanId (ID, (unusedBit), RTR, EXT)
 *  - IdMask (ID, (unusedBit), RTR, EXT)
 *  - MsgLength
 *  - Name for Instance
 *  - Name of the upper layer N-PDU
 *  - name of upper layer
 *
 *  @warning the struct must have the same order like CanIf_TxPduIdType */
[#if TxPduTestReturn?? && TxPduTestReturn == "passed" ]
/* ->->-> we have a valid Tx Pdu List */
EXTERN_CONST( CanIf_TxPduCfgType, TM_CANIF_CONFIG_DATA ) MyTest_TxPduConfig[] =
{
  [#list TxPduNameList as TxPDU ]
  [#assign TxIndex = TxPduNameList?seq_index_of(TxPDU)]  
  { /* ${TxIndex} */
    .L_PDU_Name = ${GetNPduName(TxPDU, CanIf_Prefix, "Tx")}, /* ${CanIf_Prefix}_Tx_${TxPDU} */
    .CanId = { ${GetMessageId(TxIdList[TxIndex])}, _UNUSED_VAR_, CANIF_NO_RTR, ${GetMessageType(TxIdList[TxIndex])} },
    .IdMask = { ${GetMessageId(TxMaskList[TxIndex])}, _UNUSED_VAR_, CANIF_NO_RTR, ${GetMessageType(TxMaskList[TxIndex])} },
    .MsgLength = ${TxLengthList[TxIndex]},
    .InstanceName = ${GetControllerName(TxControllerList[TxIndex])}, 
    .N_PDU_Name = (ComStack_PduType)${GetNPduName(TxTargetPduNameList[TxIndex], TxUpperLayerList[TxIndex], "Tx")},
    [#if TxUpperLayerList[TxIndex]?starts_with("u")]
    .ULName = CanIfUL_undefined
    [#else]
    .ULName = CanIfUL_${TxUpperLayerList[TxIndex]}
    [/#if]
  },
  [/#list][#-- end of TxPduNameList as PDU --]
#t/* V-----V----V----V-----V */
#t/* add imported list items */
  [#if pduMemberList?? ][#compress]
    [#assign pduMemberCounter = 0]
    [#list pduMemberList as pduMember]
      [#assign TxList = pduMember.txList]
      [#list TxList as txPdu]
        [#assign pduMemberCounter += 1]
#t{#t/* ${TxIndex+pduMemberCounter} */
[#attempt]
#t#t.L_PDU_Name = ${GetNPduName(txPdu.name, CanIf_Prefix, "Tx")}, /* ${CanIf_Prefix}_Tx_${txPdu.name} */
#t#t.CanId = { ${GetMessageId(txPdu.canId)}, _UNUSED_VAR_, CANIF_NO_RTR, ${GetMessageType(txPdu.canId)} },
#t#t.IdMask = { ${GetMessageId(txPdu.maskId)}, _UNUSED_VAR_, CANIF_NO_RTR, ${GetMessageType(txPdu.maskId)} },
#t#t.MsgLength = ${txPdu.length},
#t#t.InstanceName = ${GetControllerName(txPdu.controller)}, 
#t#t.N_PDU_Name = (ComStack_PduType)${txPdu.nPduName},
    [#if pduMember.preFix?starts_with("u")]
#t#t.ULName = CanIfUL_undefined
    [#else]
#t#t.ULName = CanIfUL_${pduMember.preFix}
    [/#if]
[#recover]
/* ##################################### */
/* there is an unsupported member config */
[#if txPdu.name??]
#t#t.L_PDU_Name = ${GetNPduName(txPdu.name, CanIf_Prefix, "Tx")}, /* ${CanIf_Prefix}_Tx_${txPdu.name} */
[#else]
[#assign genericUnkown = "L_PDU_" + pduMember.preFix + "_Tx_Dummy_" + (pduMemberCounter)]
#t#t.L_PDU_Name = (ComStack_PduType)CanIf_TxPduIdType::${genericUnkown}
[/#if]
/* ##################################### */
[/#attempt]
#t},
      [/#list]
    [/#list]
  [/#compress][/#if] [#-- pduMemberList?? -> imported list items --]
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */
  {
    .L_PDU_Name = (CanIf_TxPduIdType)L_PDU_Dummy_for_Test,
    .CanId = { 0x0, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_STDID },
    .IdMask = { 0x0, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_STDID },
    .MsgLength = 8,
    .InstanceName = CanMasterController,
    .N_PDU_Name = N_PDU_Dummy_for_Test,
    .ULName = CanIfUL_CDD
  }
/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
[#assign UserCodeCounter++]
};
[#else]
/* #+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+ */
/* There is a problem on configuration of the Tx PDU List */
/* #+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+ */
[/#if]

/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
[#assign UserCodeCounter++]

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
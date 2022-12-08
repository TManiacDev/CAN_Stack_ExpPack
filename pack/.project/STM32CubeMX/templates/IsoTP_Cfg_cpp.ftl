[#ftl]
[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 1]
[#-- SWIPdatas is a list of SWIPconfigModel --]  
[#list SWIPdatas as SWIP]
  [#assign instName = SWIP.ipName]
  [#assign fileName = SWIP.fileName]
  [#assign version = SWIP.version]
/**
  ******************************************************************************
  * @section CanIsoTP_CFG_C Code generation
  * File Name          : ${fileName}
  * Description        : This file provides code for the configuration
  *                      of the ${name} instances.
  *
  * Last updated       : ${aDate}  ${aTime}
  *
  ******************************************************************************
  [@common.optinclude name=mxTmpFolder+"/license.tmp"/][#-- include License text --]
  ******************************************************************************
  *
  * MiddleWare name : ${instName}
  * MiddleWare fileName : ${fileName}
  * MiddleWare version : ${version}
  *
  */
[/#list] [#-- end of  SWIPdatas as SWIP --]

[#assign s = fileName]
[#if s?contains("/")]
  [#assign s = s?keep_after_last("/")]
[/#if]
[#assign dashReplace = s?replace(".","_")]
[#assign dashedFileNamed = dashReplace?replace("-","_")]
[#assign inclusion_protection = dashedFileNamed?upper_case]
  [#assign UserCodeCounter = 0]

[#-- SWIPdatas is a list of SWIPconfigModel --]
[#list SWIPdatas as SWIP]
/* Includes ------------------------------------------------------------------*/
  [#if includes??]
    [#list includes as include]
#include "${include}"
    [/#list] [#-- end of list includes as include --]
  [/#if] [#-- if end of includes?? --]

#include "CanIf.h"

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
    [#case "ISOTP_PDU_RX_LIST"]   
      [#assign RxPduNameList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxPduNameList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]  
    [#case "ISOTP_PDU_TX_LIST"]
      [#assign TxPduNameList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract TxPduNameList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract Bs list --]
    [#case "ISOTP_BS_LIST"]
      [#assign RxBsList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxBsList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract N_Ar list --]
    [#case "ISOTP_NAR_LIST"]
      [#assign RxNArList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxNArList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract N_Br list --]
    [#case "ISOTP_NBR_LIST"]
      [#assign RxNBrList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxNBrList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract N_Cr list --]
    [#case "ISOTP_NCR_LIST"]
      [#assign RxNCrList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxNCrList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract Padding list --]    
    [#case "ISOTP_PADDING_LIST"]   
      [#assign RxPaddingList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxPaddingList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]  
      [#-- extract TA Type list --]
    [#case "ISOTP_TATYPE_LIST"]
      [#assign RxTATypeList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxTATypeList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract Wft list --]
    [#case "ISOTP_WFT_LIST"]
      [#assign RxWftList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxWftList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
      [#-- extract STmin list --]
    [#case "ISOTP_STMIN_LIST"]
      [#assign RxSTminList = _List_?word_list]
      [#if extractDebug_FTL > 0]
      /* extract RxSTminList ${definition.value} /./ ${List} /./ ${_List_} */
      [/#if] [#-- end of extractDebug_FTL --]
      [#break]
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

[#if RxPduNameList?? && (RxPduNameList?size > 0)]
[#-- test for all RX lists have the same length --]
[#if extractDebug_FTL > 0]
// FTL Debug: test the Rx PDU Lists 
[/#if] [#-- end of extractDebug_FTL --]
    [#if RxBsList??] 
      [#if RxBsList?size != RxPduNameList?size] 
    /* >>> @attention RxBsList with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing RxBsList */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxNArList??] 
      [#if RxNArList?size != RxPduNameList?size] 
    /* >>> @attention RxNArList List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing RxNArList */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxNBrList??] 
      [#if RxNBrList?size != RxPduNameList?size] 
    /* >>> @attention RxNBrList with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing RxNBrList */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxNCrList??] 
      [#if RxNCrList?size != RxPduNameList?size] 
    /* >>> @attention RxNCrList with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]  
      [/#if]
    [#else]
    /* >>> @attention missing RxNCrList */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxPaddingList??] 
      [#if RxPaddingList?size != RxPduNameList?size] 
    /* >>> @attention RxPaddingList List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing RxPaddingList */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxTATypeList??] 
      [#if RxTATypeList?size != RxPduNameList?size] 
    /* >>> @attention RxTATypeList List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing RxTATypeList */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxWftList??] 
      [#if RxWftList?size != RxPduNameList?size] 
    /* >>> @attention RxWftList List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing RxWftList */ 
        [#assign RxPduTestReturn = "failed"]
    [/#if]
    
    [#if RxSTminList??] 
      [#if RxSTminList?size != RxPduNameList?size] 
    /* >>> @attention RxSTminList List with wrong count of members */ 
        [#assign RxPduTestReturn = "failed"]
      [#else] 
        [#if !RxPduTestReturn??][#assign RxPduTestReturn = "passed"] [/#if]   
      [/#if]
    [#else]
    /* >>> @attention missing RxSTminList */ 
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
  [#if MsgIdString?starts_with("E") ] [#return "EXTID"]
  [#else] [#return "STDID"]
  [/#if]
[/#function]

[#function GetMessageId MsgIdString ]
  [#assign IdSperator = MsgIdString[0]+MsgIdString[1] ] 
  [#return MsgIdString?keep_after(IdSperator)]
[/#function]
[#-- end of function to separate CAN ID, Extend Bit, RTR Bit --]

[#-- function to extend the CAN controller name --]
[#function GetControllerName NameString]
  [#if NameString?starts_with("M") != true ]
    [#return "CanSlaveController"]
  [#else]
    [#return "CanMasterController"]
  [/#if]
[/#function]
[#-- end of function to extend the CAN controller name --]

[#-- function to create the PDU enum used in source code --]
[#function GetNPduName N_PduString N_PduUlString RxTx]
  [#switch N_PduUlString]
    [#case "CanNM"]
      [#assign RetName = "CanNM_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "CanTP"]
      [#assign RetName = "CanIsoTP_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "CanTSync"]
      [#assign RetName = "CanTSync_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "XCP"]
      [#assign RetName = "CanXcp_" + RxTx + "_" + N_PduString ]
      [#break]
    [#case "FT2p0"]
      [#assign RetName = "CanFT2p0_" + RxTx + "_" + N_PduString ]
      [#break]
    [#default]
      [#assign RetName = "CanUndefUl_" + RxTx + "_" + N_PduString ]
      [#break]
  [/#switch] [#-- end of N_PduUlString --]
  [#return RetName]
[/#function]
[#-- end of function to create the PDU enum used in source code --]

/* ########################################################################## */
/*          CAN ISO TP configuration                         */

/** @addtogroup TM_IsoTP_Cfg
 *  @{ */

/* * @brief This is a test configuration for RxPdu
 *  @details
 *  - PDU Name (enum)
 * */
[#if RxPduTestReturn?? && RxPduTestReturn == "passed" ]
/* ->->-> we have a valid Rx Pdu List */
/* const CanIf_RxPduCfgType MyTest_RxPduConfig[] = */
//      {
        [#list RxPduNameList as RxPDU ]
        [#assign RxIndex = RxPduNameList?seq_index_of(RxPDU)]
//        {  /* ${RxIndex} */
//          CanIf_Rx_${RxPDU},
//          
//          /* to be done */
//          
        [/#list] [#-- end of RxPduNameList as PDU --]
//        {
//          L_PDU_Dummy_for_Test,
//          { 0x0, _UNUSED_VAR_, NO_RTR, STDID },
//          { 0x0, _UNUSED_VAR_, NO_RTR, STDID },
//          8,
//          CanMasterController,
//          N_PDU_Dummy_for_Test,
//          CanIfUL_CDD
//        }
//      };
/** @} */ // end of grouping TM_IsoTP_Cfg
[#else]
/* #+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+ */
/* There is a problem on configuration of the Rx PDU List */
/* #+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+#+ */
[/#if]

/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
[#assign UserCodeCounter++]

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
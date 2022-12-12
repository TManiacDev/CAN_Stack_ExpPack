[#ftl]
 Line 1
[#assign open ="<" ]
[#assign close =">" ]

[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 0]
[#assign fileName = ""]
[#list SWIPdatas as SWIP]  
[#assign instName = SWIP.ipName]   
[#assign fileName = SWIP.fileName]   
[#assign version = SWIP.version]  
[/#list] [#-- end of SWIPdatas as SWIP --] 

[#assign IsoTp_Prefix = "IsoTP"]
[#assign strPduIdType = "PduIdType" ]

[#list SWIPdatas as SWIP]  
[#if SWIP.defines??]
	[#list SWIP.defines as definition]	
  
  [#switch definition.name ]
    [#case "ISOTP_PDU_RX_LIST"]
          [#-- extract IF PDU list --]
      [#assign NameList = definition.value]
      [#assign _NameList_ = NameList?replace(","," ")]
      
      [#assign RxPduNameList = _NameList_?word_list]
      [#-- extract IF PDU list --]
      [#break]
    [#case "ISOTP_PDU_TX_LIST"]
      [#-- extract IF PDU list --]
      [#assign NameList = definition.value]
      [#assign _NameList_ = NameList?replace(","," ")]
      
      [#assign TxPduNameList = _NameList_?word_list]
      [#-- extract IF PDU list --]
      [#break]
    [#case "ISOTP_FUNC_REQU"]
 ${definition.name} : ${definition.value} 
      [#break]
    [#case "ISOTP_FUNC_REQU_EXT"]
 ${definition.name} : ${definition.value} 
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

[#assign rxIsoTpList = []]
[#assign txIsoTpList = []]

[#list RxPduNameList as rxTempName]
  [#assign rxIsoTpChannel = { "name" : rxTempName }]
  [#assign rxIsoTpChannel += { "canId" : "S:0x7EF" }]
  [#assign rxIsoTpChannel += { "maskId" : "S:0x0" }]
  [#assign rxIsoTpChannel += { "length" : "8" }]
  [#assign rxIsoTpChannel += { "controller" : "M" }]
  
  [#assign rxIsoTpList += [rxIsoTpChannel]]
[/#list]

[#list TxPduNameList as txTempName]
  [#assign txIsoTpChannel = { "name" : txTempName }]
  [#assign txIsoTpChannel += { "canId" : "S:0x7EF" }]
  [#assign txIsoTpChannel += { "maskId" : "S:0x0" }]
  [#assign txIsoTpChannel += { "length" : "8" }]
  [#assign txIsoTpChannel += { "controller" : "M" }]
  
  [#assign txIsoTpList += [txIsoTpChannel]]
[/#list]


[#-- function to create the PDU enum used in source code --]
[#function GetNPduName N_PduString RxTx]
  [#assign RetName = IsoTp_Prefix + "_" + RxTx + strPduIdType + "::" + IsoTp_Prefix + "_" + RxTx + "_" + N_PduString ]
  [#return RetName]
[/#function]

${open}#assign lastGenerated = "${aDate}  ${aTime} | RxListSize: ${RxPduNameList?size} " ${close}

${open}#assign MyPrefix = "${IsoTp_Prefix}" ${close}

${open}#assign RxIfList =  [[#list rxIsoTpList as rxMember]
{ "name": "${rxMember.name}",
  "canId" : "${rxMember.canId}", 
  "maskId" : "${rxMember.maskId}",
  "length" : "${rxMember.length}",
  "controller" : "${rxMember.controller}",
  "nPduName" : "${GetNPduName(rxMember.name,"Rx")}"
}[#if rxMember.name != (rxIsoTpList?last).name],[/#if][/#list] ] ${close}

${open}#assign TxIfList =  [[#list txIsoTpList as txMember]
{ "name": "${txMember.name}",
  "canId" : "${txMember.canId}", 
  "maskId" : "${txMember.maskId}",
  "length" : "${txMember.length}",
  "controller" : "${txMember.controller}",
  "nPduName" : "${GetNPduName(txMember.name,"Tx")}"
}[#if txMember.name != (txIsoTpList?last).name],[/#if][/#list] ] ${close}

${open}#function HasComInterfaceCfg ${close}
${open}#return true${close}
${open}/#function${close}

${open}#function GetPrefix ${close}
${open}#return MyPrefix${close}
${open}/#function${close}

${open}#function GetRxPduList ${close}
${open}#if RxPduList??${close}
${open}#return RxPduList ${close}
${open}#else ${close}
${open}#return ["NoPdu"] ${close}
${open}/#if${close}
${open}/#function${close}

${open}#function GetTxPduList ${close}
${open}#if TxPduList??${close}
${open}#return TxPduList ${close}
${open}#else ${close}
${open}#return ["NoPdu"] ${close}
${open}/#if${close}
${open}/#function${close}

${open}#function GetRxList ${close}
${open}#if RxIfList??${close}
${open}#return RxIfList ${close}
${open}#else ${close}
${open}#return [] ${close}
${open}/#if${close}
${open}/#function${close}

${open}#function GetTxList ${close}
${open}#if TxIfList??${close}
${open}#return TxIfList ${close}
${open}#else ${close}
${open}#return [] ${close}
${open}/#if${close}
${open}/#function${close}

${open}#function GetMessageType MsgIdString ${close}
  ${open}#if MsgIdString?starts_with("E") ${close} ${open}#return "CANIF_EXTID"${close}
  ${open}#else${close} ${open}#return "CANIF_STDID"${close}
  ${open}/#if${close}
${open}/#function${close}

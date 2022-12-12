[#ftl]
[#compress][#-- this is all without real output --]
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

[#assign Name_Prefix = "FT2p0"]
[#assign strPduIdType = "PduIdType" ]

[#assign FT_Ecu_Cfg = {} ]
[#assign FT_Switchpanel_Cfg = {} ]
[#assign FT_Device_Cfg = {} ]

[#list SWIPdatas as SWIP]  
[#if SWIP.defines??]
	[#list SWIP.defines as definition]	
  
  [#switch definition.name ]
[#-- handle the Fueltech FTCAN2.0 configuration --]      
[#-- ECU config --]
      [#case "FT_Ecu"]
        [#if definition.value != "unused" ]
          [#assign FT_EcuType = definition.value]
          [#assign FT_Ecu_Cfg += { "type" : definition.value }]
          [#assign FT_Ecu_Cfg += { "baseId" : "0x14001" }]
          
          [#assign FT_EcuId = "0x14001"]
          [#-- (today) ECU is only readable --]
          [#assign FT_Ecu_Cfg += { "useCase" : "beDevice" } ]  
        [/#if] [#-- end of check for unsed device --]
      [#break]
      [#case "FT_ECU_StreamList"]
        [#assign _FT_EcuStreamListC = definition.value?replace(","," ")]  
        [#assign _FT_EcuStreamList_ = _FT_EcuStreamListC?replace("|"," ")]  
        [#assign FT_EcuStreamList = _FT_EcuStreamList_?word_list ]
        [#assign FT_Ecu_Cfg += { "rxId" : FT_EcuStreamList } ]
      [#break]
      [#case "FT_ECU_HW_Channel"]
          [#assign FT_Ecu_Cfg += { "channel" : definition.value } ]        
      [#break]
      
[#-- Switchpanel config --]
      [#case "FT_SwitchPanel"]
        [#if definition.value != "unused" ]
          [#assign FT_Switchpanel_Cfg += { "type" : definition.value} ]
          [#switch FT_Switchpanel_Cfg.type]
            [#case "Mini4"]
              [#assign FT_Switchpanel_Cfg += { "baseId" : "0x12208" }]
            [#break]
            [#case "Mini5"]
              [#assign FT_Switchpanel_Cfg += { "baseId" : "0x12210" }]
            [#break]
            [#case "Mini8"]
              [#assign FT_Switchpanel_Cfg += { "baseId" : "0x12218" }]
            [#break]
            [#default]
              [#assign FT_Switchpanel_Cfg += { "baseId" : "0x12200" }]
          [/#switch] [#-- end of FT_SwPType --]
        [/#if] [#-- end of check for unsed device --]
      [#break]
      [#case "FT_SwitchPanel_RW"]
        [#assign FT_Swp_Use = definition.value]
        [#assign FT_Switchpanel_Cfg += { "useCase" : definition.value } ]  
      [#break]
      [#case "FT_SwitchPanel_HW_Channel"]
          [#assign FT_Switchpanel_Cfg += { "channel" : definition.value } ]        
      [#break]
      
[#-- FT_Device / FT_Nano /Gear Controller config --]
      [#case "FT_Nano"]
      [#case "FT_Device"]
        [#if definition.value != "unused" ]
          [#assign FT_Device_Cfg += { "type" : definition.value} ]
          [#assign FT_Device_Cfg += { "baseId" : "0x12000" }]
        [/#if] [#-- end of check for unsed device --]
      [#break]
      [#case "FT_Nano_RW"]
      [#case "FT_Device_RW"]
        [#assign FT_Device_Cfg += { "useCase" : definition.value } ]  
        [#assign FT_Device_Cfg += { "baseId" : "0x12200" }]
      [#break]
      [#case "FT_DEVICE_HW_Channel"]
        [#assign FT_Device_Cfg += { "channel" : definition.value } ]        
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

[#-- ########################## --]
[#-- end of extract definitions --]
[#-- ########################## --]

[#assign RxPduTempList = []]
[#assign TxPduTempList = []]

[#-- add fueltech pdu --]
[#if FT_Device_Cfg.type?? && FT_Device_Cfg.useCase??]
  [#if FT_Device_Cfg.channel??]
    [#assign FT_Channel = FT_Device_Cfg.channel]
  [#else]
    [#assign FT_Channel = "M"]
  [/#if]
  [#if FT_Device_Cfg.useCase == "UseDevice"]
  we use device
  [#-- Rx PDU --]
    [#assign RxPdu  = { "name" : FT_Device_Cfg.type} ]
    [#assign RxPdu += { "canId" : "E:" + FT_Device_Cfg.baseId + "0FF"} ]
    [#assign RxPdu += { "maskId" : "E:0x0" } ]
    [#assign RxPdu += { "length" : "8" }]
    [#assign RxPdu += { "controller" : FT_Channel } ]
    [#assign RxPduTempList += [RxPdu]]
  [#-- Tx Pdu (not needed --]
    [#-- assign TxPduNameList += [FT_DeviceType+"_Responce"] --]
  [#else] [#-- we are "BeDevice" --]
  we are device
  [#-- Rx PDU --]
    [#assign RxPdu = {"name" : FT_Device_Cfg.type+"_Responce"} ]
    [#assign RxPdu += { "canId" : "E:" + FT_Device_Cfg.baseId + "000"} ]
    [#assign RxPdu += { "maskId" : "E:0x0" } ]
    [#assign RxPdu += { "length" : "8" }]    
    [#assign RxPdu += { "controller" : FT_Channel } ]
    [#assign RxPduTempList += [RxPdu]]
  [#--Tx PDU --]
    [#assign TxPdu = {"name" :FT_Device_Cfg.type} ]
    [#assign TxPdu += { "canId" : "E:" + FT_Device_Cfg.baseId + "0FF"} ]
    [#assign TxPdu += { "maskId" : "E:0x0" } ]
    [#assign TxPdu += { "length" : "8" }]
    [#assign TxPdu += { "controller" : FT_Channel } ]
    [#assign TxPduTempList += [TxPdu]]
  [/#if] [#-- end of FT_Device_Cfg.useCase == "UseDevice" --]
[/#if] [#-- end of FT_DeviceType?? && FT_Device_Use?? --]

[#if FT_Switchpanel_Cfg.type?? && FT_Switchpanel_Cfg.useCase??]
  [#if FT_Switchpanel_Cfg.channel??]
    [#assign FT_Channel = FT_Switchpanel_Cfg.channel]
  [#else]
    [#assign FT_Channel = "M"]
  [/#if]
  [#if FT_Switchpanel_Cfg.useCase == "UseDevice"]
  we use a SwitchPanel
  [#-- Rx Pdu --]
    [#assign RxPdu = {"name" : "SwitchPanel_" + FT_Switchpanel_Cfg.type} ]
    [#assign RxPdu += { "canId" : "E:" + FT_Switchpanel_Cfg.baseId + "320"} ]
    [#assign RxPdu += { "maskId" : "E:0x0" } ]
    [#assign RxPdu += { "length" : "8" }]
    [#assign RxPdu += { "controller" : FT_Channel } ]
    [#assign RxPduTempList += [RxPdu]]   
  [#-- Tx PDU --]
    [#-- assign TxPduNameList += [FT_DeviceType+"_Responce"] --]
  [#else]
  [#-- Rx PDU --]
  we are the Switchpanel
    [#assign RxPdu = {"name" : "SwitchPanel_" + FT_Switchpanel_Cfg.type + "_Ctrl" } ]
    [#-- assign TxPduNameList += [FT_DeviceType+"_Responce"] --]
    [#assign RxPdu += { "canId" : "E:" + FT_Switchpanel_Cfg.baseId + "321"} ]
    [#assign RxPdu += { "maskId" : "E:0x0" } ]
    [#assign RxPdu += { "length" : "8" }]
    [#assign RxPdu += { "controller" : FT_Channel } ]
    [#assign RxPduTempList += [RxPdu]]   
  [#-- Tx Pdu --]
    [#assign TxPdu = {"name" : "SwitchPanel_" + FT_Switchpanel_Cfg.type} ]
    [#assign TxPdu += { "canId" : "E:" + FT_Switchpanel_Cfg.baseId + "320"} ]
    [#assign TxPdu += { "maskId" : "E:0x0" } ]
    [#assign TxPdu += { "length" : "8" }]
    [#assign TxPdu += { "controller" : FT_Channel } ] 
  [#if TxPdu??][#assign TxPduTempList += [TxPdu]][/#if]
  [/#if] [#-- end of check for unsed device --]
[/#if] [#-- end of FT_Switchpanel_Cfg.type?? --]

[#if FT_Ecu_Cfg.type?? && FT_Ecu_Cfg.useCase??]
test ECU
  [#if FT_Ecu_Cfg.channel??]
    [#assign FT_Channel = FT_Ecu_Cfg.channel]
  [#else]
    [#assign FT_Channel = "M"]
  [/#if]
  [#list FT_Ecu_Cfg.rxId as FT_EcuStreamName]
    [#assign RxPduName = FT_EcuType + "_" + FT_EcuStreamName?keep_after_last("x") ]
    [#assign RxPdu = {"name" : RxPduName } ]
    [#-- assign TxPduNameList += [FT_DeviceType+"_Responce"] --]
    [#assign RxPdu += { "canId" : "E:" + FT_EcuId + FT_EcuStreamName?keep_after_last("x")} ]
    [#assign RxPdu += { "maskId" : "E:0x0" } ]
    [#assign RxPdu += { "length" : "8" }]
    [#assign RxPdu += { "controller" : FT_Channel } ]
    [#assign RxPduTempList += [RxPdu]]  
  [/#list] [#-- end of FT_EcuStreamList as FT_EcuStreamName --]
[/#if] [#-- end of adding FT Ecu config --]
[/#compress]

[#-- function to create the PDU enum used in source code --]
[#function GetNPduName N_PduString RxTx]
  [#assign RetName = Name_Prefix + "_" + RxTx + strPduIdType + "::" + Name_Prefix + "_" + RxTx + "_" + N_PduString ]
  [#return RetName]
[/#function]

[#function GetLPduName RxTx]
  [#assign RetName = Name_Prefix + "_" + RxTx + strPduIdType ]
  [#return RetName]
[/#function]


[#-- we start to create the generic template --]
${open}#assign lastGenerated = "${aDate}  ${aTime}" ${close}

${open}#assign MyPrefix = "${Name_Prefix}" ${close}

${open}#assign RxIfList =  [[#list RxPduTempList as RxTempPdu]
{ "name": "${RxTempPdu.name}",
  "canId" : "${RxTempPdu.canId}", 
  "maskId" : "${RxTempPdu.maskId}",
  "length" : "${RxTempPdu.length}",
  "controller" : "${RxTempPdu.controller}",
  "nPduName" : "${GetNPduName(RxTempPdu.name,"Rx")}"
}[#if RxTempPdu.name != (RxPduTempList?last).name],[/#if][/#list] ] ${close}

${open}#assign TxIfList =  [[#list TxPduTempList as TxTempPdu]
{ "name": "${TxTempPdu.name}",
  "canId" : "${TxTempPdu.canId}", 
  "maskId" : "${TxTempPdu.maskId}",
  "length" : "${TxTempPdu.length}",
  "controller" : "${TxTempPdu.controller}",
  "nPduName" : "${GetNPduName(TxTempPdu.name,"Tx")}"
}[#if TxTempPdu.name != (TxPduTempList?last).name],[/#if][/#list] ] ${close}

${open}#function HasComInterfaceCfg ${close}
${open}#return true${close}
${open}/#function${close}

${open}#function GetPrefix ${close}
${open}#return MyPrefix${close}
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

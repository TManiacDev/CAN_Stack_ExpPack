[#ftl]
[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 1]

[#list SWIPdatas as SWIP]  
[#assign instName = SWIP.ipName]   
[#assign fileName = SWIP.fileName]  
[#assign moduleName = fileName?keep_before_last("_")]   
[#assign version = SWIP.version]   
/**
  ******************************************************************************
  * @section FT2p0TL_CFG_C Code generation
  * File Name          : ${fileName}
  * Description        : This file provides code for the configuration
  *                      of the ${moduleName} instances.
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
  
[#assign dashedFileNamed = fileName?replace(".","_")]
[#assign UserCodeCounter = 0]

[#-- SWIPdatas is a list of SWIPconfigModel --]
[#list SWIPdatas as SWIP]
  [#if includes??]
    [#list includes as include]
#include "${include}"
    [/#list] [#-- end of list includes as include --]
  [/#if] [#-- if end of includes?? --]
[/#list] [#-- end of SWIPdatas as SWIP --]

/* Includes -----------------------------------------------------------*/
#include <CanFT2p0_Cfg.h>

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/* ************************************************************** */
[#-- SWIPdatas is a list of SWIPconfigModel --]  
[#list SWIPdatas as SWIP]  
[#-- Global variables --]
[#if SWIP.variables??]
	[#list SWIP.variables as variable]
extern ${variable.value} ${variable.name};
	[/#list]
[/#if]
[#-- Global variables --]
[#assign CanIf_Prefix = "CanIf"]
[#assign IsoTp_Prefix = "CanIsoTP"]
[#assign FTCAN2p0_Prefix = "CanFT"]
[#assign CanNM_Prefix = "CanNM"]
[#assign CanTSync_Prefix = "CanTSync"]
[#assign Xcp_Prefix = "CanXcp"]

[#assign FTPanelUse = "-"]
[#assign FTDeviceUse = "-"]
[#assign FTConfigOk = "NOk"]
 [#-- we create an empty lists --]
[#assign FT_SwB_Def = {} ]
[#assign FT_Nano_Def = {} ]
[#assign FT_ObjNameList = [] ]
[#assign FT_RxList = [] ]
[#assign FT_TxList = [] ]

[#if SWIP.defines??]
	[#list SWIP.defines as definition]	
  
  [#switch definition.name ]
[#-- handle the Fueltech FTCAN2.0 configuration --]      
      [#case "FT_SwitchPanel"]        
        [#assign FT_SwB_Def += {"Name":definition.name} ]
        [#assign FT_SwB_Def += {"UniqueId":definition.value} ]
        [#break]
      [#case "FT_SwitchPanel_RW"]
        [#assign FT_SwB_Def += {"UseCase":definition.value} ]
        [#break]
[#-- Nano values to the Nano_list --]     
      [#case "FT_Nano"] 
      [#case "FT_Device"]
        [#assign FT_Nano_Def += {"Name":definition.name} ]
        [#assign FT_Nano_Def += {"UniqueId":definition.value} ]
        [#break]
      [#case "FT_Nano_RW"]
      [#case "FT_Device_RW"]
        [#assign FT_Nano_Def += {"UseCase":definition.value} ]
        [#break]
      [#case "FT_Nano_FW_Version"]
      [#case "FT_Device_FW_Version"]
        [#assign FT_Nano_Def += {"FW_Version":definition.value} ]
        [#break]
      [#case "FT_Nano_SerialNumber"]
      [#case "FT_Device_SerialNumber"]
        [#assign FT_Nano_Def += {"SerialVersion":definition.value} ]
        [#break]
      [#case "FT_Nano_HW_Version"]
      [#case "FT_Device_HW_Version"]
        [#assign FT_Nano_Def += {"HW_Version":definition.value} ]
        [#break]
[#-- handle the command line style input --]        
      [#case "FT_CommandLine"]  
        // CommandLine Options:
        // ${definition.value}
        // I will add an interpreter for this later
        // syntax will be:
        // { { Para1, Para2, ... }, { ... }, ... }
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

[#-- build my Object List --]
[#assign FT_ObjList = [] ]
  [#if FT_SwB_Def.UseCase == "NoDevice" ]
    // there is no configuration for the SwitchPanel
  [#else]
    [#assign FT_ObjList += [FT_SwB_Def] ]
  [/#if]
  [#if FT_Nano_Def.UseCase == "NoDevice" ]
    // there is no configuration for the FT Nano
  [#else]
    [#assign FT_ObjList += [FT_Nano_Def] ]
  [/#if]
  
  
[#-- function to version string --]
[#function GetVersionString NameString]
  [#assign NameStartSymbol = NameString[0] ]
  [#switch NameStartSymbol]
    [#case "0"]
      [#assign ReturnString = "Byte Array"]
        [#assign ByteString = ""]
        [#assign StringList = NameString?word_list]
        [#list StringList as ByteValue]
        [#assign ByteString += "0x" + ByteValue + " " ]
        [/#list]
      [#assign ReturnString = ByteString]
      [#break]
    [#case "A"]
      [#assign ReturnString = "ASCII Format. We need a handling for. - "+ NameString?keep_after_last(":") +" -"]
      [#break]
    [#default]
      [#assign ReturnString = "unbekanntes Format"]
      [#break]
  [/#switch] [#-- end of NameStartSymbol --]
    [#return ReturnString]
[/#function]
[#-- end of function to version string --]

/** @brief Configuration of the used Fueltech products
 *  @details
 *  das ist die Object Configuration aus dem Code Generator */
CONST(CanFT2p0_ObjectCfgType, AUTOMATIC) MX_Fueltech_Objects[] =
{
[#list FT_ObjList as FT_ObjFromList]
  {
    /* do we need this counter/enum/name ??? */
    // [#if FT_ObjFromList.UseCase??] ${FT_ObjFromList.UseCase}[#else] "na" [/#if]
    // [#if FT_ObjFromList.Name??] ${FT_ObjFromList.Name}[#else] "na" [/#if]
    // [#if FT_ObjFromList.UniqueId??] ${FT_ObjFromList.UniqueId}[#else] "na" [/#if]
    // [#if FT_ObjFromList.SerialVersion??] ${GetVersionString(FT_ObjFromList.SerialVersion)}[#else] "na" [/#if]
    // [#if FT_ObjFromList.HW_Version??] ${GetVersionString(FT_ObjFromList.HW_Version)}[#else] "na" [/#if]
    // [#if FT_ObjFromList.FW_Version??] ${GetVersionString(FT_ObjFromList.FW_Version)}[#else] "na" [/#if]
  },
[/#list]
};

// #define CANFT_OBJECT_COUNT ${FT_ObjList?size} // das hier muss in die Cfg.h es ist die gleiche Anzahl wie es CanFT2p0_ObjectCfgType Elemente gibt
/** @} */ // end of grouping CanFT_Cfg

/* ########################## */
/* old stuff */
/* ########################## */

/* USER CODE BEGIN ${FTCAN2p0_Prefix}_Test_Area 1 */

/** @addtogroup CanFT_Cfg 
 *  @{ */ 
/** @brief this is a test channel */ 
//CONST (CanFT2p0_ChannelConfigType, AUTOMATIC) JustAChannel[] =
//{
//    {
//      1, 2, { CanFT_Rx_SwitchPanel_Mini8, CanFT_Rx_unknownPdu, CanFT_Rx_unknownPdu }
//    },
//    {
//      1, 3, { CanFT_Tx_SwitchPanel_Mini8_Ctrl, CanFT_Rx_unknownPdu, CanFT_Tx_unknownPdu }
//    },
//    {
//      1, 1, { CanFT_Rx_WbO2_Nano_0_Responce, CanFT_Rx_unknownPdu }
//    },
//    {
//      0, 0, { CanFT_Rx_unknownPdu, CanFT_Rx_unknownPdu, CanFT_Rx_unknownPdu }
//    },
//    {
//      3, 8, { CanFT_Rx_FT500_1FF, CanFT_Rx_FT500_2FF,  CanFT_Rx_FT500_3FF }
//    },
//    {
//      0, 0, { CanFT_Tx_unknownPdu, CanFT_Tx_unknownPdu, CanFT_Tx_unknownPdu }
//    }
//};

/** @brief Configuration of the used Fueltech products
 *  @details
 *  ich brauche noch eine Konfiguration wieviele "Messwerte" verlinkt werden müssen */
//CONST(CanFT2p0_ObjectCfgType, AUTOMATIC) RS601_Fueltech_Objects[] =
//{
//  {
//    1,
//    Fueltech_SwitchPanel,
//    CanFT2p0_UniqueId_Mini8,
//    CANFT_TX_OBJ,
//    {"NoSerial"},
//    &JustAChannel[0],
//    &JustAChannel[1]
//  },
//  {
//    2,
//    FuelTech_O2Nano,
//    0,
//    CANFT_RX_OBJ,
//    {"38420074063037"},
//    &JustAChannel[2],
//    &JustAChannel[3]
//  },
//  {
//    3,
//    FuelTech_ECU_FT500,
//    0,
//    CANFT_RX_OBJ,
//    {"NoSerial"},
//    &JustAChannel[4],
//    &JustAChannel[5]
//  }
//};

/** @} */ // end of grouping CanFT_Cfg

/* USER CODE END ${FTCAN2p0_Prefix}_Test_Area 1 */

//extern CONST(CanFT2p0_CfgType, AUTOMATIC) CanFT2p0_Default_Config =
//{
//  RS601_Fueltech_DB,
//  RS601_Fueltech_Objects
//};

/* private -----------------------------------------------------------*/
/* USER CODE BEGIN CanFT2p0_Cfg_c 1 */

/* USER CODE END CanFT2p0_Cfg_c 1 */


/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
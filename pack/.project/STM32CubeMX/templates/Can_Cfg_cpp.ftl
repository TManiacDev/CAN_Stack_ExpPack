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
  * @section Can_CFG_C Code generation 
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
  
  [#assign s = name]
  [#assign to = s?keep_after_last("/")]
  [#assign dashedFileNamed = to?replace(".","_")]
  [#assign UserCodeCounter = 0]
  
[#-- SWIPdatas is a list of SWIPconfigModel --]  
[#list SWIPdatas as SWIP]
  [#if includes??]
/* Includes ------------------------------------------------------------------*/
    [#list includes as include]
#include "${include}"
    [/#list] [#-- end of list includes as include --]
  [/#if] [#-- if end of includes?? --]

/* Includes ------------------------------------------------------------------*/
#include <vector>
#include "Can.h"

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/* ########################################################################## */
/*               CAN Hardware / Module configuration                          */
/** @addtogroup TM_CanCfg_ConfigSet
    @{ */ 
/* ########################################################################## */   
/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/* private constances -----------------------------------------------------------*/
[#-- Global variables --]
  [#if SWIP.variables??]
    [#list SWIP.variables as variable]
extern ${variable.value} ${variable.name};
    [/#list] [#-- end of list SWIP.variables as variable --]
  [/#if] [#-- end of if SWIP.variables?? --]

[#-- Global variables --]

[#-- bxCAN slave (pre) defines --]
        [#assign bxCAN2_Speed       = 0]
        [#assign bxCAN2_Mode        = "DISABLE"]
        [#assign bxCAN2_TTMode      = "DISABLE"]
        [#assign bxCAN2_AutoBusOff  = "DISABLE"]
        [#assign bxCAN2_AutoWakeup  = "DISABLE"]
        [#assign bxCAN2_AutoRetrans = "DISABLE"]
        [#assign bxCAN2_RxFifoLock  = "DISABLE"]
        [#assign bxCAN2_TxFifoPrio  = "DISABLE"]

[#if SWIP.defines??]
	[#list SWIP.defines as definition]
    [#switch definition.name]
[#-- bxCAN Master defines --]
      [#case "CAN1_STARTUP_MODE"]
        [#assign bxCAN1_Mode = definition.value]
        [#break]
      [#case "CAN1_STARTUP_BITRATE"]
        [#-- extract Bitrate --]
        [#assign bxCAN1_Speed = definition.value?number]
        [#-- extract Bitrate --]
        [#break]
      [#case "CAN1_STARTUP_TTMODE"]
        [#if definition.value=="true"]
          [#assign bxCAN1_TTMode = "ENABLE"]
        [#else]
          [#assign bxCAN1_TTMode = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN1_STARTUP_AUTOBUSOFF"]
        [#if definition.value=="true"]
          [#assign bxCAN1_AutoBusOff = "ENABLE"]
        [#else]
          [#assign bxCAN1_AutoBusOff = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN1_STARTUP_AUTOWAKEUP"]
        [#if definition.value=="true"]
          [#assign bxCAN1_AutoWakeup = "ENABLE"]
        [#else]
          [#assign bxCAN1_AutoWakeup = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN1_STARTUP_AUTO_RETRANSMISSION"]
        [#if definition.value=="true"]
          [#assign bxCAN1_AutoRetrans = "ENABLE"]
        [#else]
          [#assign bxCAN1_AutoRetrans = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN1_STARTUP_RXFIFO_LOCKED"]
        [#if definition.value=="true"]
          [#assign bxCAN1_RxFifoLock = "ENABLE"]
        [#else]
          [#assign bxCAN1_RxFifoLock = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN1_STARTUP_TXFIFO_PRIO"]
        [#if definition.value=="true"]
          [#assign bxCAN1_TxFifoPrio = "ENABLE"]
        [#else]
          [#assign bxCAN1_TxFifoPrio = "DISABLE"]
        [/#if]
        [#break]
        
[#-- bxCAN slave defines --]
      [#case "CAN2_STARTUP_MODE"]
        [#assign bxCAN2_Mode = definition.value]
        [#break]
      [#case "CAN2_STARTUP_BITRATE"]
        [#-- extract Bitrate --]
        [#assign bxCAN2_Speed = definition.value?number]
        [#-- extract Bitrate --]
        [#break]
      [#case "CAN2_STARTUP_TTMODE"]
        [#if definition.value=="true"]
          [#assign bxCAN2_TTMode = "ENABLE"]
        [#else]
          [#assign bxCAN2_TTMode = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN2_STARTUP_AUTOBUSOFF"]
        [#if definition.value=="true"]
          [#assign bxCAN2_AutoBusOff = "ENABLE"]
        [#else]
          [#assign bxCAN2_AutoBusOff = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN2_STARTUP_AUTOWAKEUP"]
        [#if definition.value=="true"]
          [#assign bxCAN2_AutoWakeup = "ENABLE"]
        [#else]
          [#assign bxCAN2_AutoWakeup = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN2_STARTUP_AUTO_RETRANSMISSION"]
        [#if definition.value=="true"]
          [#assign bxCAN2_AutoRetrans = "ENABLE"]
        [#else]
          [#assign bxCAN2_AutoRetrans = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN2_STARTUP_RXFIFO_LOCKED"]
        [#if definition.value=="true"]
          [#assign bxCAN2_RxFifoLock = "ENABLE"]
        [#else]
          [#assign bxCAN2_RxFifoLock = "DISABLE"]
        [/#if]
        [#break]
      [#case "CAN2_STARTUP_TXFIFO_PRIO"]
        [#if definition.value=="true"]
          [#assign bxCAN2_TxFifoPrio = "ENABLE"]
        [#else]
          [#assign bxCAN2_TxFifoPrio = "DISABLE"]
        [/#if]
        [#break]
        
[#-- Values for bit time calculation --]
      [#case "CAN_BITRATES"]
        [#-- extract Bitrate list --]
        [#assign BitrateList = definition.value]
        [#assign _BitrateList_ = BitrateList?replace(","," ")]
        [#assign _List_ = _BitrateList_?word_list]
        [#-- extract Bitrate list --]
        [#break]
      [#case "CAN_SAMPLE_POINT"]
        [#-- extract Sample point --]
        [#assign SamplePoint = definition.value?number]
        [#if SamplePoint < 1 ]
          [#if SamplePoint > 0.5]
            [#-- the Sample point comes as we want --]
            [#-- nothing to do for reformating --]
          [#else]
          /** *******************************************
           * @todo
           * SamplePoint: {SamplePoint?string["0.000"]} 
           * The Sample point can not be smaller then 50 %
           * You should use value formated like 0.xx      
           * We use 0.75 (75%) as default 
           * ******************************************* */
            [#assign SamplePoint = 0.75]
          [/#if]      
        [#else]
          [#-- Maybe the Sample point comes as percent value --]
          [#if SamplePoint > 50]
            [#assign SamplePoint = SamplePoint/100]
          [#else]
          /** *******************************************
           * @todo
           * SamplePoint: {SamplePoint?string["0.000"]} 
           * The Sample point can not be smaller then 50 %
           * You should use value formated like 0.xx      
           * We use 0.75 (75%) as default 
           * ******************************************* */
            [#assign SamplePoint = 0.75]
          [/#if]
        [/#if]
        [#-- extract Sample point --]
        [#break]
        
      [#default]
        /*  unkown definition from pack   
         *  [#if definition.description??]${definition.description} [/#if]
         *   -  name:   ${definition.name} 
         *   -  value:  ${definition.value}      */
    [/#switch]
    
	[/#list]
  
/** @brief the list of configured CAN controllers
 * 
 *  @details this vector is used to load the configuration for all listed CAN controller 
 * 
 *  @todo evaluiere was besser zu nutzen ist. Die Vector-Liste hier oder das enum im EcuNames_cfg.h 
 *  vielleicht wäre eine EcuNames_cfg.cpp mit solchen Listen auch der Weg */ 
extern const std::vector<ECU_CanController> controllerList
{
  ECU_CanController::CanMasterController,
      [#if bxCAN2_Speed != 0]
  ECU_CanController::CanSlaveController
      [/#if]
};

/** @brief parameter setup for the bxCAN module of the Nucleo board */
CONST( CanControllerParaType,TM_CAN_CONFIG_DATA) CanNucleoParaSet[] =
{
  {
      CAN1,
      ${bxCAN1_Mode},         // Mode
      ${bxCAN1_TTMode},       //TTMode
      ${bxCAN1_AutoBusOff},   //AutoBusoff
      ${bxCAN1_AutoWakeup},   //AutoWakeup
      ${bxCAN1_AutoRetrans},  //AutoRetransmission
      ${bxCAN1_RxFifoLock},   //RxFifoLock
      ${bxCAN1_TxFifoPrio},    //TxFifoPrio
      CanBaudrate_${bxCAN1_Speed}kbs
    },
    {
      CAN2,
      ${bxCAN2_Mode},         // Mode
      ${bxCAN2_TTMode},       //TTMode
      ${bxCAN2_AutoBusOff},   //AutoBusoff
      ${bxCAN2_AutoWakeup},   //AutoWakeup
      ${bxCAN2_AutoRetrans},  //AutoRetransmission
      ${bxCAN2_RxFifoLock},   //RxFifoLock
      ${bxCAN2_TxFifoPrio},    //TxFifoPrio
      [#if bxCAN2_Speed != 0]
      CanBaudrate_${bxCAN2_Speed}kbs
      [#else]
      CanBaudrate_unknown
      [/#if]
    },
};
[/#if]

[/#list]

[#list configs as dt]
[#assign data = dt]
[#assign peripheralParams =dt.peripheralParams]
[#assign peripheralGPIOParams =dt.peripheralGPIOParams]
[#assign peripheralDMAParams =dt.peripheralDMAParams]
[#assign peripheralNVICParams =dt.peripheralNVICParams]

[#assign usedIPs =dt.usedIPs]

/*  We read the CanClock speed from the RCC configuration
   APB1 Frequence Value   :   ${peripheralParams.get("RCC").get("APB1Freq_Value")}  Hz
   */
   [#assign APB1FreqValue = (peripheralParams.get("RCC").get("APB1Freq_Value"))?number]
   
[/#list]

    [#assign CanClock = APB1FreqValue/1000]
    [#assign CanClockCycle = 1000/CanClock]
    [#assign PrescalerList = [1, 2, 3, 4, 5, 6, 7, 8, 9]]
    [#assign BS1_List = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]]

/** @brief a set of configurations to generate baudrates
 *  @details  Beschreibung für den STM32 (Seite 1106 im Manual)
 *            Der Clock kommt von t_PCLK von der RCC APB1
 *            der Baud rate prescaler definiert die Zeit für ein Sync Quanta.
 *            Die Summe aus phase segment 1 und phase segment 2 quantas ergibt eine Bit Timing Länge
 *
 * This values will be used to generate the bittiming register values 
 * BitrateList :  ${_BitrateList_} kbs
 * CanClock    :  ${CanClock} kHz
 * SamplePoint :  ${SamplePoint?string.percent} 
 */
CONST( CanControllerBaudrateConfigType,TM_CAN_CONFIG_DATA) NucleoBaudrateConfig[] =
{
  [#list _List_ as word] 
  {
    [#assign Bitnumber = word?number]
    CanBaudrate_${Bitnumber}kbs, /* we save the ID also in the configuration so we can check it */
    ${Bitnumber},  /* Specifies the baudrate of the controller in kbps, maybe we save the register value here */
    [#list PrescalerList as Prescal]
      [#list BS1_List as BS_Value]
        [#assign Bittime = 1000/(Bitnumber)]
        [#assign TimeQuanta = CanClockCycle*Prescal]
        [#assign SWJ_Time = TimeQuanta ]
        [#assign BS1_Time = TimeQuanta*BS_Value]
        [#assign BS2_Time_down =  TimeQuanta*(BS_Value*SamplePoint)?floor]
        [#assign BS2_Time_up =  TimeQuanta*(BS_Value*SamplePoint)?ceiling]
        [#if (BS_Value*SamplePoint)?floor > 8]
          [#break]
        [/#if]
        [#if (BS_Value*SamplePoint)?ceiling > 8]
          [#break]
        [/#if]
        [#if (SWJ_Time+BS1_Time+BS2_Time_down) < Bittime ]
          [#if (SWJ_Time+BS1_Time+BS2_Time_up) < Bittime ]
            [#assign BS_ESQ = false]
          [#else] 
    /*  ----- ${Prescal} > SJW_1TQ (${SWJ_Time?string["0.000"]}) + CAN_BS1_${BS_Value}TQ (${BS1_Time?string["0.000"]}) +  CAN_BS2_${(BS_Value*SamplePoint)?ceiling}TQ (${BS2_Time_up?string["0.000"]}) = ${(SWJ_Time+BS1_Time+BS2_Time_up)?string["0.000"]} */
    ${Prescal},  /* Specifies scaling factor for CAN controller clock */
    0,   // Specifies propagation delay in time quantas. not supported by the STM32 CAN modul
    CAN_BS1_${BS_Value}TQ, /* Specifies phase segment 1 in time quantas */
    CAN_BS2_${(BS_Value*SamplePoint)?ceiling}TQ,  /* Specifies phase segment 2 in time quantas. */
    CAN_SJW_1TQ   // Specifies the synchronization jump width for the controller in time quantas
            [#assign BS_ESQ = true]
          [/#if]
        [#else] 
    /*  ----- ${Prescal} > SJW_1TQ (${SWJ_Time?string["0.000"]}) + CAN_BS1_${BS_Value}TQ (${BS1_Time?string["0.000"]}) +  CAN_BS2_${(BS_Value*SamplePoint)?floor}TQ (${BS2_Time_down?string["0.000"]}) = ${(SWJ_Time+BS1_Time+BS2_Time_down)?string["0.000"]} */
    ${Prescal},  /* Specifies scaling factor for CAN controller clock */
    0,   // Specifies propagation delay in time quantas. not supported by the STM32 CAN modul
    CAN_BS1_${BS_Value}TQ, /* Specifies phase segment 1 in time quantas */
    CAN_BS2_${(BS_Value*SamplePoint)?floor}TQ,  /* Specifies phase segment 2 in time quantas. */
    CAN_SJW_1TQ   // Specifies the synchronization jump width for the controller in time quantas
        [#assign BS_ESQ = true]
        [/#if]
        [#if BS_ESQ == true ]
        [#break][/#if]
      [/#list]
      [#if BS_ESQ == true ][#break][/#if]
    [/#list]
  },
    [/#list]
};

/*

*/


/** @brief filter configuration
 *  @details
 *  we have this order:
 *  - FilterIdHigh
 *  - FilterIdLow
 *  - FilterMaskIdHigh
 *  - FilterMaskIdLow
 *  - FilterFIFOAssignment
 *  - FilterBank
 *  - FilterMode
 *  - FilterScale
 *  - FilterActivation
 *  - SlaveStartFilterBank
 *  @todo we need a nice generic way */
CONST( CAN_FilterTypeDef, TM_CAN_CONFIG_DATA) CanNucleoFilterSet[] =
{
    {
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        CAN_RX_FIFO0,
        13,
        CAN_FILTERMODE_IDMASK,
        CAN_FILTERSCALE_32BIT,
        ENABLE,
        14
    }
};

/** @brief This is the configuration for the STM Nulceo144 board 
 *  @todo we need a generic way */
EXTERN_CONST( CanConfigType, TM_CAN_CONFIG_DATA) Can_DefaultConfig =
{
  NucleoBaudrateConfig,
  CanNucleoParaSet,
  CanNucleoFilterSet
};

/** @} */ // end of grouping TM_CanCfg_ConfigSet
/* ########################################################################## */


/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
[#assign UserCodeCounter++]

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
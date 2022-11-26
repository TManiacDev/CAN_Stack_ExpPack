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
  * @section CanIf_HAL_C Code generation 
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
  *
  ******************************************************************************
  * This file should be fully generated
  ******************************************************************************
  * 
  */
[/#list] [#-- end of SWIPdatas as SWIP --]

[#assign s = name]
[#assign to = s?keep_after_last("/")]
[#assign dashedFileNamed = to?replace(".","_")]
[#assign UserCodeCounter = 0]

[#-- SWIPdatas is a list of SWIPconfigModel --]  
[#list SWIPdatas as SWIP]
  [#if includes??]
    [#list includes as include]
#include "${include}"
    [/#list] [#-- end of list includes as include --]
  [/#if] [#-- if end of includes?? --]

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "TM_Std_Types.h"

/* private Includes ----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
[#assign UserCodeCounter++]

/* ---- external Can handle names needed ---------  */

/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
[#assign UserCodeCounter++]

/* @brief to use the generic name coming from the template 
 * @details this pointer will be redirected on CanIf::Init() function */ 
CAN_HandleTypeDef* ptr2Can1Hdl = NULL_PTR; 
 
/* @brief to use the generic name coming from the template 
 * @details this pointer will be redirected on CanIf::Init() function */ 
CAN_HandleTypeDef* ptr2Can2Hdl = NULL_PTR; 

[#list configs as dt]
  [#assign data = dt]
  [#assign peripheralParams =dt.peripheralParams]
  [#assign peripheralGPIOParams =dt.peripheralGPIOParams]
  [#assign peripheralDMAParams =dt.peripheralDMAParams]
  [#assign peripheralNVICParams =dt.peripheralNVICParams]

  [#assign usedIPs =dt.usedIPs]
  
  [#list usedIPs as ip ] [#-- For each used ip, list all configuration data --]
    [#if peripheralParams.get(ip).entrySet()?size>0]
      [#if ip?contains("CAN")]
      
        [#if peripheralNVICParams.get(ip)?? && peripheralNVICParams.get(ip).entrySet()?size>0]
          [#list peripheralNVICParams.get(ip).entrySet() as nvicParamEntry]
            [#assign irqName = nvicParamEntry.key?remove_ending("n")]
/**
  * @brief This function handles ${irqName} interrupts.
  */
void ${irqName}Handler(void)
{
  /* USER CODE BEGIN ${nvicParamEntry.key} 0 */

  /* USER CODE END ${nvicParamEntry.key} 0 */
  HAL_CAN_IRQHandler(ptr2${ip?capitalize}Hdl);
  /* USER CODE BEGIN ${nvicParamEntry.key} 1 */

  /* USER CODE END ${nvicParamEntry.key} 1 */
}

          [/#list] [#-- end of list peripheralNVICParams.get(ip).entrySet() as nvicParamEntry --]
        [/#if] [#-- end of if peripheralNVICParams.get(ip)?? && peripheralNVICParams.get(ip).entrySet()?size>0 --]
      [/#if] [#-- end of  if ip?contains("CAN") --]
    [/#if] [#--  end of if peripheralParams.get(ip).entrySet()?size>0 --]
  [/#list] [#-- end of  list usedIPs as ip --]
  
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/**
* @brief CAN MSP Initialization
* This function configures the hardware resources used in this example
* @param hcan: CAN handle pointer
* @retval None
*/
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{  
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  [#list usedIPs as ip ] [#-- For each used ip, list all configuration data --]
    [#if peripheralParams.get(ip).entrySet()?size>0]
      [#if ip?contains("CAN")]
        [#assign rxName = "_IP_RX"]
        [#assign rxName = rxName?replace("_IP", ip)]
        [#assign txName = rxName?replace("RX", "TX")]
        [#if peripheralGPIOParams.get(ip)?? && peripheralGPIOParams.get(ip).entrySet()?size>0]
  if(hcan->Instance == ${ip})
  {
/* USER CODE BEGIN ${ip}_MspInit 0 */

/* USER CODE END ${ip}_MspInit 0 */
  
    /* Peripheral clock enable */
    __HAL_RCC_${ip}_CLK_ENABLE();

    __HAL_RCC_${peripheralGPIOParams.get(ip).get(rxName).get("GPIOx")}_CLK_ENABLE(); 
        
    /**  ${ip} GPIO Configuration
        - Pin Name    Rx -> ${peripheralGPIOParams.get(ip).get(rxName).get("Pin")} | Tx -> ${peripheralGPIOParams.get(ip).get(txName).get("Pin")}
        - Port        ${peripheralGPIOParams.get(ip).get(rxName).get("GPIOx")}
      */
    GPIO_InitStruct.Pin = ${peripheralGPIOParams.get(ip).get(rxName).get("GPIO_Pin")} | ${peripheralGPIOParams.get(ip).get(txName).get("GPIO_Pin")};
    GPIO_InitStruct.Mode = ${peripheralGPIOParams.get(ip).get(rxName).get("GPIO_Mode")};
    GPIO_InitStruct.Pull = ${peripheralGPIOParams.get(ip).get(rxName).get("GPIO_PuPd")};
    GPIO_InitStruct.Speed = ${peripheralGPIOParams.get(ip).get(rxName).get("GPIO_Speed")};
    GPIO_InitStruct.Alternate = ${peripheralGPIOParams.get(ip).get(rxName).get("GPIO_AF")};
    
    /* use the GPIO HAL function */
    HAL_GPIO_Init(${peripheralGPIOParams.get(ip).get(rxName).get("GPIOx")}, &GPIO_InitStruct);
        [/#if] [#-- if peripheralGPIOParams.get(ip)?? && peripheralGPIOParams.get(ip).entrySet()?size>0 --]
         
        [#if peripheralNVICParams.get(ip)?? && peripheralNVICParams.get(ip).entrySet()?size>0]
    /* ${ip} interrupt Init */
          [#list peripheralNVICParams.get(ip).entrySet() as nvicParamEntry]
     //   - ${nvicParamEntry.key} :  
            [#list nvicParamEntry.value.entrySet() as nvicParam]
     //       - ${nvicParam.key} : ${nvicParam.value}      #t [peripheralNVICParams.get("${ip}").get("${nvicParamEntry.key}").get("${nvicParam.key}")]
            [/#list]
    HAL_NVIC_SetPriority(${nvicParamEntry.key}, ${nvicParamEntry.value.get("interruptPremptionPriority")}, ${nvicParamEntry.value.get("Subriority")});
    HAL_NVIC_EnableIRQ(${nvicParamEntry.key});  
    /* --- */
    
          [/#list]
        [/#if] [#--  end of if peripheralNVICParams.get(ip)?? && peripheralNVICParams.get(ip).entrySet()?size>0 --]
  /* USER CODE BEGIN ${ip}_MspInit 1 */

  /* USER CODE END ${ip}_MspInit 1 */
  }
      [/#if] [#-- end of  if ip?contains("CAN") --] 
    [/#if] [#--  end of if peripheralParams.get(ip).entrySet()?size>0 --]
  [/#list] [#-- end of  list usedIPs as ip --]
[/#list] [#-- end of list configs as dt --]
}

[/#list] [#-- end of  SWIPdatas as SWIP --]

/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
[#assign UserCodeCounter++]

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/


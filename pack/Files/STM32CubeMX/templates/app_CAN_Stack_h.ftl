[#ftl]
/**
  ******************************************************************************
  * File Name          : ${name}
  * Description        : This file provides code for the configuration
  *                      of the ${name} instances.
  *
  [#assign aDateTime = .now]
  [#assign aDate = aDateTime?date]
  [#assign aTime = aDateTime?time]
  * Last updated       : ${aDate}  ${aTime}
  *
  ******************************************************************************
[@common.optinclude name=mxTmpFolder+"/license.tmp"/][#--include License text --]
  ******************************************************************************
  */

[#assign s = fctProcessName?keep_before_last("_")]
[#assign dashedFileNamed = s?replace("-","_")]
[#assign inclusion_protection = dashedFileNamed?upper_case]
[#assign UserCodeCounter = 0]
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __${inclusion_protection}__
#define __${inclusion_protection}__

#ifdef __cplusplus
extern "C" {
#endif

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

#define LED_GREEN_TOGGLE   HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin)
#define LED_BLUE_TOGGLE    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin)
#define LED_RED_TOGGLE     HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin)

/* Exported Functions --------------------------------------------------------*/
void ${fctName}(void);
void ${fctProcessName}(void);

[#assign MX_secFctName = fctName?keep_before_last("_")]
[#if MX_secFctName?contains("Sandbox")]
void ${MX_secFctName + "_Task2"}(void);
[/#if]
/* private function -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

#ifdef __cplusplus
}
#endif
#endif /*__ ${inclusion_protection} */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

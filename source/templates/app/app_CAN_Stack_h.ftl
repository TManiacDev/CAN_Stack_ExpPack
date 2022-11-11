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


[#assign s = name]
[#assign to = s?replace(".","__")]
[#assign toto = to?replace("/","__")]
[#assign dashReplace = toto?replace("-","_")]
[#assign inclusion_protection = dashReplace?upper_case]
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __${inclusion_protection}__
#define __${inclusion_protection}__

#ifdef __cplusplus
extern "C" {
#endif

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN app_include 0 */

/* USER CODE END app_include 0 */

#define LED_GREEN_TOGGLE   HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin)
#define LED_BLUE_TOGGLE    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin)
#define LED_RED_TOGGLE     HAL_GPIO_TogglePin(LD3_GPIO_Port,LD3_Pin)

/* Exported Functions --------------------------------------------------------*/
void ${fctName}(void);
void ${fctProcessName}(void);

[#assign secFctName = fctName?keep_before_last("_")]
[#if secFctName == "FT500_Read"]
void ${fctName + "_Task2"}(void);
[/#if]
/* private function -----------------------------------------------------------*/
/* USER CODE BEGIN app_func 0 */

/* USER CODE END app_func 0 */

#ifdef __cplusplus
}
#endif
#endif /*__ ${inclusion_protection} */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

/**
  ******************************************************************************
  * File Name          : TM_Engineering.CAN_Stack.0.2.1
  * Description        : This file provides code for the configuration
  *                      of the TM_Engineering.CAN_Stack.0.2.1 instances.
  *
  * Last updated       : Dec 5, 2022  12:48:08 PM
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TM_ENGINEERING__CAN_STACK__0__2__1__
#define __TM_ENGINEERING__CAN_STACK__0__2__1__

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
void MX_CanIf_AppDemo_Init(void);
void MX_CanIf_AppDemo_Process(void);

/* private function -----------------------------------------------------------*/
/* USER CODE BEGIN app_func 0 */

/* USER CODE END app_func 0 */

#ifdef __cplusplus
}
#endif
#endif /*__ TM_ENGINEERING__CAN_STACK__0__2__1 */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

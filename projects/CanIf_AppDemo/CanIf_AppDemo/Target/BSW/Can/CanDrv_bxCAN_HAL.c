/**
  ******************************************************************************
  * @section CanIf_HAL_C Code generation
  * File Name          : CanDrv_bxCAN_HAL.c
  * Description        : This file provides code for the configuration
  *                      of the CanDrv_bxCAN_HAL.c instances.
  *
  * MiddleWare name    : TM_Engineering.CAN_Stack.0.2.1
  * MiddleWare version :
  * Last updated       : Dec 5, 2022  12:48:10 PM
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
  *
  ******************************************************************************
  * This file should be fully generated
  ******************************************************************************
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "TM_Std_Types.h"

/* private Includes ----------------------------------------------------------*/
/* USER CODE BEGIN  0 */

/* USER CODE END  0 */

/* ---- external Can handle names needed ---------  */

/* USER CODE BEGIN  1 */

/* USER CODE END  1 */

/* @brief to use the generic name coming from the template
 * @details this pointer will be redirected on CanIf::Init() function */
CAN_HandleTypeDef* ptr2Can1Hdl = NULL_PTR;

/* @brief to use the generic name coming from the template
 * @details this pointer will be redirected on CanIf::Init() function */
CAN_HandleTypeDef* ptr2Can2Hdl = NULL_PTR;

/* USER CODE BEGIN  2 */

/* USER CODE END  2 */

/**
* @brief CAN MSP Initialization
* This function configures the hardware resources used in this example
* @param hcan: CAN handle pointer
* @retval None
*/
void HAL_CAN_MspInit(CAN_HandleTypeDef* hcan)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  if(hcan->Instance == CAN1)
  {
/* USER CODE BEGIN CAN1_MspInit 0 */

/* USER CODE END CAN1_MspInit 0 */

    /* Peripheral clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();

    /**  CAN1 GPIO Configuration
        - Pin Name    Rx -> PB8 | Tx -> PB9
        - Port        GPIOB
      */
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;

    /* use the GPIO HAL function */
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }

}

/* USER CODE BEGIN  3 */

/* USER CODE END  3 */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/


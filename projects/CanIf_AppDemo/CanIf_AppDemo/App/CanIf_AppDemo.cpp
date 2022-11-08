/**
  ******************************************************************************
  * File Name          : App/CanIf_AppDemo.cpp
  * Description        : This file provides code for the configuration
  *                      of the App/CanIf_AppDemo.cpp instances.
  *
  * Last updated       : Nov 8, 2022  6:56:51 PM
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

/* Private includes ----------------------------------------------------------*/

/* we need generic include */
#include "app_canif_appdemo.h"
#include "CanIf.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/** to have the CAN interface object */
CanIf canInterface;

/* USER CODE BEGIN PV */
uint32_t processTick = 0;
uint32_t processUsage = 0;

ComStack_CanMsgHeader msgHeader = {{0x1ff, 0, 0, 0}, 8, 0 , 0x0 };
uint8_t data[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x04, 0x80};
CanIf_PduInfoType myTestPdu = { data, 8 };

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

void MX_CanIf_AppDemo_Init(void)
{

/* USER CODE BEGIN MX_CanIf_AppDemo_Init 0 */

/* USER CODE END MX_CanIf_AppDemo_Init 0 */

  if ( canInterface.Init() == E_NOT_OK )
  {
    // report error ;
  }

  if ( canInterface.Start() == E_NOT_OK )
  {
    // try it later
  }

/* USER CODE BEGIN MX_CanIf_AppDemo_Init 1 */

/* USER CODE END MX_CanIf_AppDemo_Init 1 */

}

/* USER CODE BEGIN Header_Process_Task */
/**
  * @brief  Function implementing the baseTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Process_Task */
void MX_CanIf_AppDemo_Process(void)
{

/* USER CODE BEGIN MX_CanIf_AppDemo_Process 0 */

  processTick = HAL_GetTick()%1000;

  if ( ( processTick == 100 ) && ( processUsage == 0 ) )
  {
    LED_RED_TOGGLE;

    // send via known CAN message header:
    canInterface.Transmit( msgHeader,data);

    // to lock against multiple call
    processUsage++;
  }

  if ( ( processTick == 600 ) && ( processUsage == 1 ) )
  {
    // send with known PDU name (better way):
    canInterface.Transmit(CanIf_Tx_Name2, &myTestPdu);

    // to lock against multiple call
    processUsage++;
  }

  // release the lock
  if ( ( processTick > 950 ) )
  {
    processUsage = 0;
  }

  // call the TxTask to write to CAN controller
  canInterface.TxTask();

/* USER CODE END MX_CanIf_AppDemo_Process 0 */
}

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

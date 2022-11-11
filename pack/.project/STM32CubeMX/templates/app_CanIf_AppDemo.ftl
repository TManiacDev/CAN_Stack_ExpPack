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
  [#assign to = s?keep_after_last("/")]
  [#assign dashedFileNamed = to?replace(".","_")]
  [#assign UserCodeCounter = 0]
  
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

void ${fctName}(void)
{

/* USER CODE BEGIN ${fctName} 0 */

/* USER CODE END ${fctName} 0 */
  [#assign UserCodeCounter++]

  if ( canInterface.Init() == E_NOT_OK )
  {
    // report error ;
  }

  if ( canInterface.Start() == E_NOT_OK )
  {
    // try it later
  }
  
/* USER CODE BEGIN ${fctName} 1 */

/* USER CODE END ${fctName} 1 */
  [#assign UserCodeCounter++]
  
}


/* USER CODE BEGIN Header_Process_Task */
/**
  * @brief  Function implementing the baseTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Process_Task */
void ${fctProcessName}(void)
{
  
/* USER CODE BEGIN ${fctProcessName} 0 */

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
    canInterface.Transmit(CanIf_Tx_Name1, &myTestPdu);
    
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
  
/* USER CODE END ${fctProcessName} 0 */
}

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

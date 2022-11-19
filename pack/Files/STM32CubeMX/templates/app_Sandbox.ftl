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
  
[#assign MX_secFctName = fctName?keep_before_last("_")]
/* Private includes ----------------------------------------------------------*/
#include "app_sandbox.h"
#include "CanIf.h"
#include "FTSwitchPanel.h" 
#include "FuelTechEcu.h"

/* we need generic include */

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

/* USER CODE BEGIN PV */

/** @addtogroup TM_CanIf_Main 
 *  @{ */ 
 
/** to have the CAN interface object */ 
CanIf canInterface; 
/** @} */ 
FT_SwitchPanel externFtPanel = FT_SwitchPanel(); 

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

/* USER CODE BEGIN ${MX_secFctName + "_Task2"} 0 */ 
/** 
  * @brief  Function implementing the baseTask thread. 
  * @param  argument: Not used 
  * @retval None 
  */ 
/* USER CODE END ${MX_secFctName + "_Task2"} 0 */ 
void ${MX_secFctName + "_Task2"}(void) 
{ 
 
/* USER CODE BEGIN ${MX_secFctName + "_Task2"} 1 */ 
 
/* USER CODE END ${MX_secFctName + "_Task2"} 1 */ 
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
//  CanIsoTP_ScheduledFunc();
  
/* USER CODE BEGIN ${fctProcessName} 0 */

/* USER CODE END ${fctProcessName} 0 */
}

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */


/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

/**
  ******************************************************************************
  * @section Can_CFG_H Code generation
  * File Name          : ./Can_Cfg.h
  * Description        : This file provides code for the configuration
  *                      of the Can_Cfg.h instances.
  *
  * MiddleWare name    : TM_Engineering.CAN_Stack.0.1.0
  * MiddleWare version :
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_CFG__H__
#define __CAN_CFG__H__

#include "main.h"
#include "TM_ComStack_Types.h"

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN Can_Cfg__h 0 */

/* USER CODE END Can_Cfg__h 0 */

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************/

/** @addtogroup TM_CanCfg_General
 *  @brief    General behavior of the CAN Module
 *  @details  Some elements are hold as \#define and other in the configuration structure<br>
 *            \#defines are used to switch on or off code segments
 *  @{ */

/** @brief Development Error Detection On/OFF
 *  @details
 *  activates the calling of CAN_DET_REPORTERROR() */
#define CAN_DEV_ERROR_DETECT  STD_ON
// #define CAN_DEV_ERROR_DETECT_NO  STD_OFF

/** ----------  Number of used HW filter for bxCAN Master -----------*/
#define CAN1_USED_RX_HW_FILTER      16

/** ----------  the used sample point for bitrate generator -----------*/
#define CAN_SAMPLE_POINT      0.63

/** @brief this is just to catch un used configuration */
#define UNKNOWN 0

/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Can_Cfg__h 1 */

/* USER CODE END Can_Cfg__h 1 */
/** @} */ // end of grouping TM_CanCfg_General

/** @addtogroup TM_CanCfg_BaudCfg
 *  @{ */

/** @brief This ID is used by SetBaudrate API and uniquely identifies a specific baud rate configuration within a controller configuration.
 */
typedef enum
{
  /** @brief symbolic name for 250kb/s baudrate */
  CanBaudrate_250kbs,
  /** @brief symbolic name for 500kb/s baudrate */
  CanBaudrate_500kbs,
  /** @brief symbolic name for 1000kb/s baudrate */
  CanBaudrate_1000kbs,
  /** @brief symbolic name to end the list and for error handling */
  CanBaudrate_unknown
}CanControllerBaudRateConfigID;

/** @brief Names for the hardware CAN controller */
typedef enum
{
  CanMasterController,    ///< ST named the first controller Master because of the "Master configuration"
  CanSlaveController,     ///< ST named the second controller Slave because of fewer configuration
  NBROF_CanController     ///< for error handling we create a name at last
}ECU_CanController;

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN Can_Cfg__h 2 */

/* USER CODE END Can_Cfg__h 2 */
/** @} */ // end of grouping TM_CanCfg_BaudCfg

#ifdef __cplusplus
}
#endif
#endif /*__ CAN_CFG__H_H */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

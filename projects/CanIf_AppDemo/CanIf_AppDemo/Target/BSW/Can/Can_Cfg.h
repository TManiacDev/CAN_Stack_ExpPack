/**
  ******************************************************************************
  * @section Can_CFG_H Code generation
  * File Name          : Can_Cfg.h
  * Description        : This file provides code for the configuration
  *                      of the Can_Cfg.h instances.
  *
  * MiddleWare name    : TM_Engineering.CAN_Stack.0.2.1
  * MiddleWare version :
  * Last updated       : Dec 5, 2022  12:48:09 PM
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

/* Define to prevent recursive inclusion ------------------------------------- */
#ifndef __CAN_CFG__H__
#define __CAN_CFG__H__

#include "TM_ComStack_Types.h"
#include "Can_Compiler_Cfg.h"

/* private Includes ----------------------------------------------------------- */
/* USER CODE BEGIN Can_Cfg__h 0 */

/* USER CODE END Can_Cfg__h 0 */

/** @addtogroup TM_Can_Driver
 *  @{ */
/** @brief  my ID */
#define CAN_VENDOR_ID           TM_VENDOR_ID
/** @brief  module id to see where the error is come from */
#define CAN_MODULE_ID           (*(uint16_t*)"CA")
/** @brief To see the version and patch level we save it on ASCII */
#define CAN_VERSION             (*(uint16_t*)"02")
/** @brief To see the sub patch level we save it on ASCII
 *  @details There are two signs available: 0-99 */
#define CAN_PATCH_VERSION       (*(uint16_t*)"1")
/** @} */ // end of grouping TM_Can_Driver

/*******************************/

/** @addtogroup TM_CanCfg_General
 *  @brief    General behavior of the CAN Module
 *  @details  Some elements are hold as \#define and other in the configuration structure<br>
 *            \#defines are used to switch on or off code segments
 *  @{ */

/** @brief Development Error Detection On/OFF
 *  @details
 *  activates the calling of CAN_DET_REPORTERROR() */
// #define CAN_DEV_ERROR_DETECT  STD_ON
#define CAN_DEV_ERROR_DETECT_NO  STD_OFF

/** ----------   -----------*/
#define CAN1_USED_RX_HW_FILTER      16

/** ----------   -----------*/
#define CAN_SAMPLE_POINT      0.63

/** ----------   -----------*/
#define CAN_TX_SW_BUFFER_SIZE      16

/** ----------   -----------*/
#define CAN_RX_SW_BUFFER_SIZE      16

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

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN Can_Cfg__h 2 */

/* USER CODE END Can_Cfg__h 2 */
/** @} */ // end of grouping TM_CanCfg_BaudCfg

#endif /*__ CAN_CFG__H_H */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

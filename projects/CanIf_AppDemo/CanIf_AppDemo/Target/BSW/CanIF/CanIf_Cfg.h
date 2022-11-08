/**
  ******************************************************************************
  * @section CanIF_CFG_H Code generation
  * File Name          : ./CanIf_Cfg.h
  * Description        : This file provides code for the configuration
  *                      of the CanIf_Cfg.h instances.
  *
  * MiddleWare name    : TM_Engineering.CAN_Stack.0.1.0
  * MiddleWare version :  / 0.1.0
  * Last updated       : Nov 8, 2022  6:56:52 PM
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
#ifndef __CANIF_CFG__H__
#define __CANIF_CFG__H__

#include "main.h"
#include "TM_Std_types.h"

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN CanIf_Cfg__h 0 */

/* USER CODE END CanIf_Cfg__h 0 */

/** @addtogroup TM_CanIf_Main
 *  @{ */

#ifdef __cplusplus
#include "TMEVersionInfo.h"
#endif

/** @brief  my ID */
#define CANIF_VENDOR_ID           TM_VENDOR_ID
/** @brief  module id to see where the error is come from */
#define CANIF_MODULE_ID           (0x60)
/** @brief we have only one version at start
 *  todo use a generated value */
#define CANIF_VERSION             (0)
/** @brief no patching until now
 *  todo use a generated value */
#define CANIF_PATCH_VERSION       (1)
/** @} */ // end of grouping TM_CanIf_Main

#ifdef __cplusplus
 extern "C" {
#endif

/*******************************/

/** @addtogroup TM_CanIf_BufferCfg
 *  @{ */

      /* extract RxUpperLayerList undef,undef /./ undef,undef /./ undef undef */

/** ----------  Size of TX buffer -----------*/
#define CANIF_TX_BUFFER_SIZE      16

/** ----------  Size of RX buffer -----------*/
#define CANIF_RX_BUFFER_SIZE      16

      /* extract TxUpperLayerList undef,undef /./ undef,undef /./ undef undef */

/** @} */ // end of grouping TM_CanIf_BufferCfg

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN CanIf_Cfg__h 1 */

/** use of the development error detection */
#define CANIF_DEV_ERROR_DETECT STD_OFF

/** use of the pre compile configuration */
#define CANIF_LOAD_STATIC_CONFIG STD_ON

/* USER CODE END CanIf_Cfg__h 1 */

#ifdef __cplusplus
}
#endif
#endif /*__ CANIF_CFG__H__ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

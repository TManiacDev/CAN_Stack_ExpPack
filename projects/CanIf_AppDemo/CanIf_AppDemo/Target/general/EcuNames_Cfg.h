/**
  ******************************************************************************
  * @section EcuNames_CFG_H Code generation
  * File Name          : ./EcuNames_Cfg.h
  * Description        : This file provides code for the configuration
  *                      of the instances.
  *
  * MiddleWare name    : TM_Engineering.CAN_Stack.0.1.0
  * MiddleWare version :
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
#ifndef ______ECUNAMES_CFG__H__
#define ______ECUNAMES_CFG__H__

#include "main.h"
#include "TM_Std_types.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN __/EcuNames_Cfg__h 0 */

/** @brief this enum shows the naming conventions of used PDU names */
 typedef enum
 {
   N_PDU_Dummy_for_Test,
   L_PDU_Dummy_for_Test,
   CanUndefUl_Rx_Target1,
   CanUndefUl_Rx_Target2,
   CanUndefUl_Tx_Target1,
   CanUndefUl_Tx_Target2
 }CanUL_PDU_for_Test;

/* USER CODE END __/EcuNames_Cfg__h 0 */

/*******************************/

/** @addtogroup TM_CanIfCfg
 *  @{ */

/** @brief to use generic names for the PDUs */
typedef enum
{
  /** @brief symbolic name for Name1 */
  CanIf_Rx_Name1,
  /** @brief symbolic name for Name2 */
  CanIf_Rx_Name2,
/* USER CODE BEGIN CanIf_User_RxPDUs 0 */

/* USER CODE END CanIf_User_RxPDUs 0 */
  CanIf_Rx_unknownPdu
}CanIf_RxPduIdType;

/* USER CODE BEGIN CanIf_User_RxPDUs 1 */

/** @brief number of user defined RxPdu-Names
    @details This define must be edit if added User_RxPDUs to the enum CanIf_RxPduIdType */
#define CANIF_RXPDU_USERCOUNT  0

/* USER CODE END CanIf_User_RxPDUs 1 */

/** @brief number of all RxPdu-Names
 *  @details this will be used to define the used memory to handle the RxPdus */
#define CANIF_RXPDU_COUNT ( 2 + CANIF_RXPDU_USERCOUNT )

/** @} */ // end of grouping TM_CanIfCfg

/** @addtogroup TM_CanIfCfg
 *  @{ */
/** @brief to use generic names for the PDUs */
typedef enum
{
  /** @brief symbolic name for Name1 */
  CanIf_Tx_Name1,
  /** @brief symbolic name for Name2 */
  CanIf_Tx_Name2,
/* USER CODE BEGIN CanIf_User_TxPDUs 0 */

/* USER CODE END CanIf_User_TxPDUs 0 */
  CanIf_Tx_unknownPdu
}CanIf_TxPduIdType;

/* USER CODE BEGIN CanIf_User_TxPDUs 1 */

/** @brief number of user defined RxPdu-Names
    @details This define must be edit if added User_TxPDUs to the enum CanIf_TxPduIdType */
#define CANIF_TXPDU_USERCOUNT  0

/* USER CODE END CanIf_User_TxPDUs 1 */

/** @brief number of all TxPdu-Names
 *  @details this will be used to define the used memory to handle the TxPdus */
#define CANIF_TXPDU_COUNT ( 2 + CANIF_TXPDU_USERCOUNT )

/** @} */ // end of grouping TM_CanIfCfg

/* private names -----------------------------------------------------------*/
/* USER CODE BEGIN __/EcuNames_Cfg__h 1 */

/* USER CODE END __/EcuNames_Cfg__h 1 */

#ifdef __cplusplus
}
#endif
#endif /*__ ____ECUNAMES_CFG__H__ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

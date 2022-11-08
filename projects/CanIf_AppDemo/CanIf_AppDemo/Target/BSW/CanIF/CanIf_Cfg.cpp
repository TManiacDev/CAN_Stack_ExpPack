/**
  ******************************************************************************
  * @section CanIF_CFG_C Code generation
  * File Name          : ./CanIf_Cfg.cpp
  * Description        : This file provides code for the configuration
  *                      of the CanIf_Cfg.cpp instances.
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

/* Includes ------------------------------------------------------------------*/
#include <CanIf.h>

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN  0 */

/* USER CODE END  0 */

/* ########################################################################## */
/*          CAN Interface / Abstraction configuration                         */

/** @addtogroup TM_CanIf_RxPduCfg
 *  @{ */

/** @brief This is a test configuration for RxPdu
 *  @details
 *  - PDU Name (enum)
 *  - CanId (ID, (unusedBit), RTR, EXT)
 *  - IdMask (ID, (unusedBit), RTR, EXT)
 *  - MsgLength
 *  - Name for Instance
 *  - Name of the upper layer N-PDU
 *  - name of upper layer
 *
 *  @sa CanIf_PduIdType */
/* ->->-> we have a valid Rx Pdu List */
EXTERN_CONST( CanIf_RxPduCfgType, TM_CANIF_CONFIG_DATA ) MyTest_RxPduConfig[] =
{
  {  /* 0 */
    .L_PDU_Name = CanIf_Rx_Name1,
    .CanId = { 123, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_STDID },
    .IdMask = { 0, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_STDID },
    .MsgLength = 8,
    .InstanceName = CanMasterController,
    .N_PDU_Name = CanUndefUl_Rx_Target1,
    .ULName = CanIfUL_undefined
  },
    {  /* 1 */
    .L_PDU_Name = CanIf_Rx_Name2,
    .CanId = { 0xAFFE, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_EXTID },
    .IdMask = { 0, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_EXTID },
    .MsgLength = 8,
    .InstanceName = CanMasterController,
    .N_PDU_Name = CanUndefUl_Rx_Target2,
    .ULName = CanIfUL_undefined
  },

/* USER CODE BEGIN  1 */
  {
    .L_PDU_Name = L_PDU_Dummy_for_Test,
    .CanId = { 0x123456, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_EXTID },
    .IdMask = { 0x0, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_EXTID },
    .MsgLength = 8,
    .InstanceName = CanMasterController,
    .N_PDU_Name = N_PDU_Dummy_for_Test,
    .ULName = CanIfUL_CDD
  }
/* USER CODE END  1 */
};
/** @} */ // end of grouping TM_CanIf_RxPduCfg

/** @brief This is a test configuration for TxPdu
 *  @details
 *  - PDU Name (enum)
 *  - CanId (ID, (unusedBit), RTR, EXT)
 *  - IdMask (ID, (unusedBit), RTR, EXT)
 *  - MsgLength
 *  - Name for Instance
 *  - Name of the upper layer N-PDU
 *  - name of upper layer
 *
 *  @sa CanIf_PduIdType */
/* ->->-> we have a valid Tx Pdu List */
EXTERN_CONST( CanIf_RxPduCfgType, TM_CANIF_CONFIG_DATA ) MyTest_TxPduConfig[] =
{
  { /* 0 */
    .L_PDU_Name = CanIf_Tx_Name1,
    .CanId = { 0x7FF, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_STDID },
    .IdMask = { 0x7FF, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_STDID },
    .MsgLength = 8,
    .InstanceName = CanMasterController,
    .N_PDU_Name = CanUndefUl_Tx_Target1,
    .ULName = CanIfUL_undefined
  },
    { /* 1 */
    .L_PDU_Name = CanIf_Tx_Name2,
    .CanId = { 0x1F2F3F4F, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_EXTID },
    .IdMask = { 0x1F2F3F4F, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_EXTID },
    .MsgLength = 8,
    .InstanceName = CanSlaveController,
    .N_PDU_Name = CanUndefUl_Tx_Target2,
    .ULName = CanIfUL_undefined
  },

/* USER CODE BEGIN  2 */
  {
    .L_PDU_Name = L_PDU_Dummy_for_Test,
    .CanId = { 0x0, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_STDID },
    .IdMask = { 0x0, _UNUSED_VAR_, CANIF_NO_RTR, CANIF_STDID },
    .MsgLength = 8,
    .InstanceName = CanMasterController,
    .N_PDU_Name = N_PDU_Dummy_for_Test,
    .ULName = CanIfUL_CDD
  }
/* USER CODE END  2 */
};

/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN  3 */

/* USER CODE END  3 */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

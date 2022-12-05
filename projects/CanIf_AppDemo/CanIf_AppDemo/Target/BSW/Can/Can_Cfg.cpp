/**
  ******************************************************************************
  * @section Can_CFG_C Code generation
  * File Name          : Can_Cfg.cpp
  * Description        : This file provides code for the configuration
  *                      of the Can_Cfg.cpp instances.
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

/* Includes ------------------------------------------------------------------*/
#include <vector>
#include "Can.h"

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN  0 */

/* USER CODE END  0 */

/* ########################################################################## */
/*               CAN Hardware / Module configuration                          */
/** @addtogroup TM_CanCfg_ConfigSet
    @{ */
/* ########################################################################## */
/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN  1 */

/* USER CODE END  1 */

/* private constances -----------------------------------------------------------*/

        /*  unkown definition from pack
         *
         *   -  name:   CAN_TX_SW_BUFFER_SIZE
         *   -  value:  16      */

        /*  unkown definition from pack
         *
         *   -  name:   CAN1_USED_RX_HW_FILTER
         *   -  value:  16      */

        /*  unkown definition from pack
         *
         *   -  name:   CAN_RX_SW_BUFFER_SIZE
         *   -  value:  16      */

/** @brief the list of configured CAN controllers
 *
 *  @details this vector is used to load the configuration for all listed CAN controller
 *
 *  @todo evaluiere was besser zu nutzen ist. Die Vector-Liste hier oder das enum im EcuNames_cfg.h
 *  vielleicht wäre eine EcuNames_cfg.cpp mit solchen Listen auch der Weg */
extern const std::vector<ECU_CanController> controllerList
{
  ECU_CanController::CanMasterController,
};

/** @brief parameter setup for the bxCAN module of the Nucleo board */
CONST( CanControllerParaType,TM_CAN_CONFIG_DATA) CanNucleoParaSet[] =
{
  {
      CAN1,
      CAN_MODE_NORMAL,         // Mode
      DISABLE,       //TTMode
      DISABLE,   //AutoBusoff
      DISABLE,   //AutoWakeup
      ENABLE,  //AutoRetransmission
      DISABLE,   //RxFifoLock
      DISABLE,    //TxFifoPrio
      CanBaudrate_1000kbs
    },
    {
      CAN2,
      DISABLE,         // Mode
      DISABLE,       //TTMode
      DISABLE,   //AutoBusoff
      DISABLE,   //AutoWakeup
      DISABLE,  //AutoRetransmission
      DISABLE,   //RxFifoLock
      DISABLE,    //TxFifoPrio
      CanBaudrate_unknown
    },
};

/*  We read the CanClock speed from the RCC configuration
   APB1 Frequence Value   :   42000000  Hz
   */

/** @brief a set of configurations to generate baudrates
 *  @details  Beschreibung für den STM32 (Seite 1106 im Manual)
 *            Der Clock kommt von t_PCLK von der RCC APB1
 *            der Baud rate prescaler definiert die Zeit für ein Sync Quanta.
 *            Die Summe aus phase segment 1 und phase segment 2 quantas ergibt eine Bit Timing Länge
 *
 * This values will be used to generate the bittiming register values
 * BitrateList :  250 500 1000 kbs
 * CanClock    :  42000 kHz
 * SamplePoint :  63%
 */
CONST( CanControllerBaudrateConfigType,TM_CAN_CONFIG_DATA) NucleoBaudrateConfig[] =
{
  {
    CanBaudrate_250kbs, /* we save the ID also in the configuration so we can check it */
    250,  /* Specifies the baudrate of the controller in kbps, maybe we save the register value here */
    /*  ----- 8 > SJW_1TQ (0.190) + CAN_BS1_12TQ (2.286) +  CAN_BS2_8TQ (1.524) = 4.000 */
    8,  /* Specifies scaling factor for CAN controller clock */
    0,   // Specifies propagation delay in time quantas. not supported by the STM32 CAN modul
    CAN_BS1_12TQ, /* Specifies phase segment 1 in time quantas */
    CAN_BS2_8TQ,  /* Specifies phase segment 2 in time quantas. */
    CAN_SJW_1TQ   // Specifies the synchronization jump width for the controller in time quantas
  },
  {
    CanBaudrate_500kbs, /* we save the ID also in the configuration so we can check it */
    500,  /* Specifies the baudrate of the controller in kbps, maybe we save the register value here */
    /*  ----- 4 > SJW_1TQ (0.095) + CAN_BS1_12TQ (1.143) +  CAN_BS2_8TQ (0.762) = 2.000 */
    4,  /* Specifies scaling factor for CAN controller clock */
    0,   // Specifies propagation delay in time quantas. not supported by the STM32 CAN modul
    CAN_BS1_12TQ, /* Specifies phase segment 1 in time quantas */
    CAN_BS2_8TQ,  /* Specifies phase segment 2 in time quantas. */
    CAN_SJW_1TQ   // Specifies the synchronization jump width for the controller in time quantas
  },
  {
    CanBaudrate_1000kbs, /* we save the ID also in the configuration so we can check it */
    1000,  /* Specifies the baudrate of the controller in kbps, maybe we save the register value here */
    /*  ----- 2 > SJW_1TQ (0.048) + CAN_BS1_12TQ (0.571) +  CAN_BS2_8TQ (0.381) = 1.000 */
    2,  /* Specifies scaling factor for CAN controller clock */
    0,   // Specifies propagation delay in time quantas. not supported by the STM32 CAN modul
    CAN_BS1_12TQ, /* Specifies phase segment 1 in time quantas */
    CAN_BS2_8TQ,  /* Specifies phase segment 2 in time quantas. */
    CAN_SJW_1TQ   // Specifies the synchronization jump width for the controller in time quantas
  },
};

/*

*/

/** @brief filter configuration
 *  @details
 *  we have this order:
 *  - FilterIdHigh
 *  - FilterIdLow
 *  - FilterMaskIdHigh
 *  - FilterMaskIdLow
 *  - FilterFIFOAssignment
 *  - FilterBank
 *  - FilterMode
 *  - FilterScale
 *  - FilterActivation
 *  - SlaveStartFilterBank
 *  @todo we need a nice generic way */
CONST( CAN_FilterTypeDef, TM_CAN_CONFIG_DATA) CanNucleoFilterSet[] =
{
    {
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        CAN_RX_FIFO0,
        13,
        CAN_FILTERMODE_IDMASK,
        CAN_FILTERSCALE_32BIT,
        ENABLE,
        14
    }
};

/** @brief This is the configuration for the STM Nulceo144 board
 *  @todo we need a generic way */
EXTERN_CONST( CanConfigType, TM_CAN_CONFIG_DATA) Can_DefaultConfig =
{
  NucleoBaudrateConfig,
  CanNucleoParaSet,
  CanNucleoFilterSet
};

/** @} */ // end of grouping TM_CanCfg_ConfigSet
/* ########################################################################## */

/* private defines -----------------------------------------------------------*/
/* USER CODE BEGIN  2 */

/* USER CODE END  2 */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

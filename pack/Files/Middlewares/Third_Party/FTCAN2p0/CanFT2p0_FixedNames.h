/**
  ******************************************************************************
  * File Name          : CanFT2p0TL_FixedNames.h
  * Description        : This file provides code for the configuration
  *                      of the CanFT2p0TL_FixedNames.h instances.
  *
  * Last updated       : Feb 12, 2022  10:58:15 AM
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
#ifndef __CANFT2P0TL_FIXEDNAMES__H__
#define __CANFT2P0TL_FIXEDNAMES__H__

#ifdef __cplusplus
 extern "C" {
#endif

/** @addtogroup CanFT2p0_DataIDs
 *   @{ */

/** @brief this are the DataIds corresponding to the Fueltech Protocol description
 *  @details we use the DataID not the MeasureId
 *  The Data will be mapped to it's MeasureID and Data according to it's type (@todo we need a way to do this)
 *
 *  In addition we use DataIds to handle buttons and lights on the Switchpanel */
typedef enum
{
  Unknown,
  TPS,
  MAP,
  AirTemp,
  EngineTemp,
  Cyl1_O2,
  Cyl2_O2,
  LeftBank_O2,
  RightBank_O2,
  General_O2,
  SW_Button_State,
  SW_Button_Color,  
/* USER CODE BEGIN CanFT2p0_DataName 0 */

/* USER CODE END CanFT2p0_DataName 0 */
  DataName_ListEnd
}CanFT2p0_DataName;

/** @brief this enum defines the order of the data array to describe a Fueltech SwitchPanel*/
typedef enum
{
  Button_01_State,
  Button_01_Color,
  Button_02_State,
  Button_02_Color,
  Button_03_State,
  Button_03_Color,
  Button_04_State,
  Button_04_Color
}CanFT2P0_SwitchPanelDataIds;

/* USER CODE BEGIN CanFT2P0_SwitchPanelDataIds 0 */

/* USER CODE END CanFT2P0_SwitchPanelDataIds 0 */

/** Unique ID for the older switch panel 8 */
#define CanFT2p0_UniqueId_Big8         0x0
/** Unique ID for the switch panel 4 (old and mini) */
#define CanFT2p0_UniqueId_Mini4        0x2
/** Unique ID for the switch panel 5 (old and mini) */
#define CanFT2p0_UniqueId_Mini5        0x4
/** Unique ID for the switch panel 8 mini */
#define CanFT2p0_UniqueId_Mini8        0x6

/** @brief product ID of the Switchpanel(s) */
#define CanFT2p0_SwitchPanelId 0x0244
/** @brief product ID of the FT500 ECU */
#define CanFT2p0_FT500Id       0x0280
/** @brief product ID of the FT600 ECU */
#define CanFT2p0_FT600Id       0x0281
/** @brief product ID of the WB O2 Nano */
#define CanFT2p0_WBo2Nano     0x0240

/** @brief product ID of the EGT-8 model A
 *  @note
 *  - Channel 1 - 4 on message ID 0x0080
 *  - Channel 5 - 8 on message ID 0x0100
 *  @note using fix point data with low nibble for 0.1-0.9 (0.2 and 0.8 not supported) */
#define CanFT2p0_EGT_8AId      (0x0800)
/** @brief product ID of the EGT-8 model B
 *  @note
 *  - Channel 1 - 4 on message ID 0x0080
 *  - Channel 5 - 8 on message ID 0x0100
 *  @note using fix point data with low nibble for 0.1-0.9 (0.2 and 0.8 not supported) */
#define CanFT2p0_EGT_8BId      (0x0880)

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN CanFT2p0_DataId 0 */

/* USER CODE END CanFT2p0_DataId 0 */

/** @} */ // end of grouping CanFT2p0_DataIDs

/** @addtogroup CanFT2p0_DataFieldIDs
 *   @{ */

/** @brief to have spec like name for DataFieldID
 *  @details It  describes how the data is packed  */
typedef enum
{
  /** @brief  Standard CAN data field */
  CanFT2p0_Standard  = 0b000,
  /** @brief Standard CAN data field coming from/going to a bus converter */
  CanFT2p0_StandardConv = 0b001,
  /** @brief FTCAN 2.0 data field */
  CanFT2p0_FTCAN20 = 0b010,
  /** @brief FTCAN 2.0 data field coming from/going to a bus converter. */
  CanFT2p0_FTCAN20Conv = 0b011,

  /** @brief the button data isn't defined inside the spec. it will transported as CanFT2p0_Standard*/
  CanFT2p0_FT_Button = CanFT2p0_Standard + 0b100,
  /** @brief the button data isn't defined inside the spec. it will transported as CanFT2p0_Standard*/
  CanFT2p0_FT_ButtonConv = CanFT2p0_StandardConv + 0b100,

  /** (--- missing ---) */
  Para_invalid,
}CanFT2p0_DataFieldId;
/** @} */ // end of grouping CanFT2p0_DataFieldIDs

/** @brief to have spec like name for ProductTypeID
 *  @todo maybe we change this to a enum with the IDs sorted to the type
 *  enum { CanFT2p0_SwitchPanelId = 0x0244, CanFT2p0_FT500Id = 0x0280, ... }*/
typedef uint32_t CanFT2p0_ProductTypeId;

/** @brief to have spec like name for ProductID */
typedef uint32_t CanFT2p0_ProductId;

/** @brief to have spec like name for UniqueID */
typedef uint32_t CanFT2p0_UniqueId;

/** @brief to have spec like name for MessageID */
typedef uint32_t CanFT2p0_MessageId;

#ifdef __cplusplus
}
#endif
#endif /*__CANFT2P0TL_CFGNAMES__H__ */

/**
  * @}
  */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

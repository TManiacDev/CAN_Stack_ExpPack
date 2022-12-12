[#ftl]
[#assign aDateTime = .now]
[#assign aDate = aDateTime?date]
[#assign aTime = aDateTime?time]
[#assign extractDebug_FTL = 1]

[#list SWIPdatas as SWIP]  
[#assign instName = SWIP.ipName]   
[#assign fileName = SWIP.fileName]   
[#assign version = SWIP.version]   
/**
  ******************************************************************************
  * @section FT2p0TL_CFG_H Code generation 
  * File Name          : ${fileName}
  * Description        : This file provides code for the configuration
  *                      of the ${name} instances.
  *
  * MiddleWare name    : ${instName}
  * MiddleWare version : ${version}
  * Last updated       : ${aDate}  ${aTime}
  *
  ******************************************************************************
[@common.optinclude name=mxTmpFolder+"/license.tmp"/][#--include License text --]
  ******************************************************************************
  */
[/#list] [#-- end of SWIPdatas as SWIP --]

[#assign Name_Prefix = "FT2p0"]
[#assign s = fileName]
[#if s?contains("/")]
  [#assign s = s?keep_after_last("/")]
[/#if]
[#assign dashReplace = s?replace(".","_")]
[#assign dashedFileNamed = dashReplace?replace("-","_")]
[#assign inclusion_protection = dashedFileNamed?upper_case]
[#assign UserCodeCounter = 0]
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __${inclusion_protection}__
#define __${inclusion_protection}__

/* Imported types */
#include "TM_ComStack_Types.h" 
#include "EcuNames_Cfg.h"
#include "CanFT2p0_DatabaseCfg.h" 
#include "CanFT2p0_FixedNames.h"

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/** @addtogroup CanFT2p0_Cfg
 *  @{ */

#define CANFT_OBJECT_COUNT 3 // das hier muss in die Cfg.h es ist die gleiche Anzahl wie es CanFT2p0_ObjectCfgType Elemente gibt
#define CANFT_HOW_MANY_BYTES_WE_NEED 64 
/**
States type to handle behavior.
*/
typedef enum
{
  /** we don't know who we are. maybe there is a problem */
  CANFT_USE_UNKOWN,
  /** We are the Fueltech product */
  CANFT_RX_OBJ,
  /** we use the Fueltech product */
  CANFT_TX_OBJ,
  /** CAN FT module is ready to work as cross (rx/tx) object*/
  CANFT_RXTX_OBJ
}CanFT2p0_ObjectStatesType;

/** @brief to name all measure values for access from application */
typedef enum
{
  CanFT_SwitchPanel_States, 
  CanFT_SwitchPanel_Ctrl, 
  CanFT_SwitchPanel_RedLight, 
  CanFT_SwitchPanel_GreenLight, 
  CanFT_SwitchPanel_BlueLight, 
  CanFT_Nano_Value, 

  /* USER CODE BEGIN CanFT2p0_NameType 0 */

  /* USER CODE END CanFT2p0_NameType 0 */
  CanFT_undefined_Measure
}CanFT2p0_MeasureNameType;

/** @brief to create enough space for measure values */
#define CANFT2P0_MEASURE_NAME_COUNT  16 // CodeGenreration need, same as CanFT_undefined_Measure, maybe round to 4 or 2

/** @brief configuration of a rx channel */
typedef struct
{
  // Anzahl
  // genutzte PDU
  VAR(uint32_t, AUTOMATIC) PduCount;
  /** Die Anzahl zu reservierender DatenPackete */ 
  VAR(uint32_t, AUTOMATIC) DataCount; 
  /// @todo ich brauch ein passendes define für die maximale Anzahl
  VAR(ComStack_PduType, AUTOMATIC) Pdu[${Name_Prefix?upper_case}_RXPDU_COUNT];
}CanFT2p0_ChannelConfigType;

/** @brief Configuration of the Fueltech communication object
 *  @details
 *  a single configuration holds all data to one object like a SwitchPanel or a ECU
 *  */
typedef struct
{
  // hier muss die Verknüpfung zwischen Database und PDU-Handling passieren
  /** @brief The config object should know his name */
  VAR(uint16_t, AUTOMATIC) ConfigName;
  /** @brief we must know which product it is */
  VAR(CanFT2p0_NameType, AUTOMATIC) ProductName;
  /** @brief the UniqueId is a config element */
  VAR(CanFT2p0_UniqueId, AUTOMATIC) UniqueId;
  /// @brief to handle the direction of de-/coding from/to CAN
  VAR(CanFT2p0_ObjectStatesType, AUTOMATIC) ObjectState;
  /// @brief to save a serial number 
  /// @hint we need a "new line" character at the end for C++ 
  VAR(uint8_t, AUTOMATIC) SerialNo[15]; 
  // was brauchen wir alles um einen Rx oder Tx Kanal zu beschreiben?
  P2CONST(CanFT2p0_ChannelConfigType,AUTOMATIC, AUTOMATIC) ptr2RxChannel;
  P2CONST(CanFT2p0_ChannelConfigType,AUTOMATIC, AUTOMATIC) ptr2TxChannel;

}CanFT2p0_ObjectCfgType;

/** @addtogroup CanFT2p0_Spec_DataBase
 *  @{ */


typedef struct
{
  /** @brief The channel needs a name */
  CONST(CanFT2p0_DB_ChannelNameType, AUTOMATIC) ChannelName;
  /** @brief The channel uses a specific message ID */
  CONST(CanFT2p0_MessageId, AUTOMATIC) MessageId;
  /** @brief The channel as a data field coding described in the spec */
  CONST(CanFT2p0_DataFieldId, AUTOMATIC) DataFieldId;
}CanFT2p0_DBChannelType;

/** @brief this are static information defined by the protocol
 *  @details
 *  We don't need all Fueltech products every time so we can use a reduced database.
 *  @hint Rx and Tx in the database is in the direction of the product it self.
 *        If you want to read a product it must be switched */
typedef struct
{
  /** @brief The enum name is to find the product in the data base */
  CONST(CanFT2p0_NameType, AUTOMATIC) ProductName;
  /** @brief The ProductTypeID defined on the FTCAN 2.0 spec */
  CONST(CanFT2p0_ProductTypeId, AUTOMATIC) ProductTypeId;
  /** @brief Describes the data that will be send from this product */
  P2CONST(CanFT2p0_DB_ChannelNameType, AUTOMATIC, AUTOMATIC) TransmitChannels;
  /** @brief Describes the data that will be received at this product */
  P2CONST(CanFT2p0_DB_ChannelNameType, AUTOMATIC, AUTOMATIC) ReceiveChannels;
}CanFT2p0_DataBaseType;
/** @} */ // end of grouping CanFT2p0_Spec_DataBase

/** @brief this is the overall config container of this communication module */
typedef struct
{
  /** @brief pointer to the spec database */
  P2CONST(CanFT2p0_DataBaseType, AUTOMATIC, AUTOMATIC) ptr2DataBase;
  /** @brief pointer to the configuration of the software modules */
  P2CONST(CanFT2p0_ObjectCfgType, AUTOMATIC, AUTOMATIC) ptr2ObjConfig;
}CanFT2p0_CfgType;

/** @} */ // end of grouping CanFT2p0_Cfg

/** @addtogroup CanFT2p0_Cfg
 *  @{ */
/** @brief the major configuration of the FTCAN 2.0 module */
extern const CanFT2p0_CfgType RS601_FT_Config;
/** @} */

/** @addtogroup CanFT2p0_DataBase
 *  @{ */
/** @brief We save the Fueltech stuff in this data base ready to use it on init function */
//extern CONST(CanFT2p0_DataBaseType, AUTOMATIC) CanFT2p0_Default_Config[];
#define CanFT2p0_Default_Config  nullptr
/** @} */

/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN ${dashedFileNamed} ${UserCodeCounter} */

/* USER CODE END ${dashedFileNamed} ${UserCodeCounter} */
  [#assign UserCodeCounter++]

/** @} */ // end of grouping CanFT2p0_Cfg

#endif /* __ ${inclusion_protection}__ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/
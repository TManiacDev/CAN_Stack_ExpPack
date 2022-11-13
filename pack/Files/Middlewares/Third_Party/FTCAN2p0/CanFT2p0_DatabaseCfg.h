/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanFT2p0_DatabaseCfg.h

 * @author TManiac
 * @date 19.06.2022
 * @version 
 *
 */
#ifndef _CANFT2P0_DATABASECFG_H_
#define _CANFT2P0_DATABASECFG_H_


/** @addtogroup CanFT2p0_Spec_DataBase
 *  @{ */

/** we use a symbolic name to select the handling
 *  Das sind die Namen welche für CanFT2p0_DataBaseType RS601_Fueltech_DB[] genutzt werden */
typedef enum
{
  /// @brief it is a Switch Panel
  Fueltech_SwitchPanel,
  /// @brief it is a FT500 ECU
  FuelTech_ECU_FT500,
  /// @brief it is a O2 Nano
  FuelTech_O2Nano,

/* USER CODE BEGIN CanFT2p0_NameType 0 */

/* USER CODE END CanFT2p0_NameType 0 */

  /// @brief for searching and error handling
  CanFT2p0_ObjectName_unknown
}CanFT2p0_NameType;

/** @brief Uses the MeasureIDs in an enum style */
typedef enum
{
  CanFt2p0_unknown_MeasureID = 0x0000,
  TPS_MeasureID = 0x0002,
  MAP_MeasureID = 0x0004,
  AirTemp_MeasureID = 0x0006,
  EngineTemp_MeasureID = 0x0008,
  Cyl1_O2_MeasureID =  0x0026,  // oder 0x0027
  Cyl2_O2_MeasureID =  0x0028,  // oder 0x0029
  LeftBank_O2_MeasureID = 0x004A,  // oder 0x0027
  RightBank_O2_MeasureID = 0x004C,  // oder 0x0029
  General_O2_MeasureID = 0x004E,  // oder 0x004F

  SwitchPanel_ButtonStates_MeasureID = 0xF000,
  SwitchPanel_DimCtrl_MeasureID = 0xF002,
  SwitchPanel_RedCtrl_MeasureID = 0xF004,
  SwitchPanel_GreenCtrl_MeasureID = 0xF006,
  SwitchPanel_BlueCtrl_MeasureID = 0xF008

}CanFT2p0_MeasureID;

/** @brief this is the name list of known communication channels */
typedef enum
{
  /** @brief Describes the channel transmitted from a Fueltech Switchpanel
   *  @details the Switchpanel has only on "TX Channel" that deliveres the button states.*/
  FT_Switchpanel_Data,
  /** @brief Describes the channel to control a Fueltech Switchpanel
   *  @details the Switchpanel has only on "RX Channel" that controls the lighting.*/
  FT_Switchpanel_Ctrl,
  /** @brief The data sended from the wideband O2 Nano
   *  @details
   *  0x120003FF (301.990911)): 00.4E.27.0F     -> Exhaust O2: 9.999 */
  FT_WbO2Nano_Data,
  /** @brief a complete version info message
   *  @details
   *
Antwort auf 0x140002EA<br>
0x120016EA / Multiplex

| Data  | Decode | ASCII | Anm. |
| ----- | ------ | ----- | ---- |
| 0x00.00.27.06.02.40.00.00   | (0) 0.39.6.2.64.0.0       |             |   |
| 0x01 0E 00 00 32 C8 30 30   | (1) 14.0.0.50.200.48.48   |             |   |
| 0x02 33 38 34 32 30 30 37   | (2)                       | 3842007     | SerialNo |
| 0x03 37 30 36 33 30 33 37   | (3)                       | 4063037     | ^ |
| 0x04 F3 30 35 39 35 30 39   | (4) 243 48 53 57 53 48 57 | ?.059509    | [ASCII] |
| 0x05 39 32 01 00 00 27 --   | (5) 57 50 1 0 0 39        | 9 2 ^1 ^@ ' | |
   */
  FT_WbO2Nano_VersionInfo,
  /** @brief short version info
   *  @details
   *
Antwort auf 0x14000AF5<br>
0x12001EF5 | Multiplex

| Data  | Decode | ASCII | Anm. |
| ----- | ------ | ----- | ---- |
| 0x00.00.1B.06.02.40.00.00 | (0) 0.27.6.2.64.0.0      | | |
| 0x01 0E 00 00 32 C8 30 30 | (1) 14.0.0.50.200.48.48  | | |
| 0x02 33 38 34 32 30 30 37 | (2)                      | 3842007 | SerialNo |
| 0x03 37 30 36 33 30 33 37 | (3)                      | 4063037 | ^ |
| 0x04 F3                   | (4) 243                  | | |
   */
  FT_WbO2Nano_ShortInfo,
  /** @brief I don't know what is for
   *  @details
   *
Antwort auf 0x1400AE9 [48.00.00.00]
0x12000EE9
0x06.01.01
   *  */
  FT_WbO2Nano_VeryShortMsg,
  /** @brief the ECU request for FT_WbO2Nano_VersionInfo */
  FT_VersionInfoRequest,
  /** @brief the ECU request for FT_WbO2Nano_ShortInfo */
  FT_ShortInfoRequest,
  /** @brief the ECU request for FT_WbO2Nano_VeryShortMsg */
  FT_VeryShortInfoRequest,
  /** just to handle unknown messages */
  ChannelName_unknown
}CanFT2p0_DB_ChannelNameType;

/** @} */ // end of grouping CanFT2p0_Spec_DataBase

#endif /* _CANFT2P0_DATABASECFG_H_ */

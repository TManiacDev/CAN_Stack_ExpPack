/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * This file holdes the information coming from the FTCAN 2.0 spec
 *
 * The file has a "Cfg" name, because of adding new information should be done here
 *
 * $Author: jens.raethe $
 * $Source: CanFT2p0_DatabaseCfg.c $
 * $Date: 2022/06/19 $
 * $Revision: 0.1 $
 *
 */

/* Includes ------------------------------------------------------------------*/

#include <CanFT2p0_Cfg.h>

/** @addtogroup CanFT2p0_Spec_DataBase
 *  @{ */

/** @brief Describes the channels
 *  @details

*/
CONST(CanFT2p0_DBChannelType, AUTOMATIC) Fueltech_DB_Channels[] =
{
  {
    FT_Switchpanel_Data,
    0x320,
    CanFT2p0_Standard
  },
  {
    FT_Switchpanel_Ctrl,
    0x321,
    CanFT2p0_Standard
  },
  {
    FT_WbO2Nano_Data,
    0x3FF,
    CanFT2p0_Standard
  },
  {
    FT_WbO2Nano_VersionInfo,
    0x2EA, // plus gesetztes Response bit
    CanFT2p0_FTCAN20
  },
  {
    FT_WbO2Nano_ShortInfo,
    0xEF5,  // plus gesetztes Response bit
    CanFT2p0_FTCAN20
  },
  {
    FT_WbO2Nano_VeryShortMsg,
    0xEE9, // plus gesetztes Response bit
    CanFT2p0_Standard
  },
  {
    FT_VersionInfoRequest,
    0x2EA,
    CanFT2p0_Standard
  },
  {
    FT_ShortInfoRequest,
    0xAF5,
    CanFT2p0_Standard
  },
  {
    FT_VeryShortInfoRequest,
    0xAE9,
    CanFT2p0_Standard
  }
};

/** @brief Describes the channel to control a Fueltech Switchpanel
 *  @details the Switchpanel has only on "RX Channel" that controls the lighting.*/
CONST(CanFT2p0_DB_ChannelNameType, AUTOMATIC) Fueltech_SwitchPanel_RxChannel[] =
{
    FT_Switchpanel_Ctrl
};
/** @brief Describes the channel transmitted from a Fueltech Switchpanel
 *  @details the Switchpanel has only on "TX Channel" that deliveres the button states.*/
CONST(CanFT2p0_DB_ChannelNameType, AUTOMATIC) Fueltech_SwitchPanel_TxChannel[] =
{
    FT_Switchpanel_Data
};

/** @brief Describes the channel to control a Fueltech Wideband O2 Nano
 *  @details Es ist die Frage wie geht man mit den Filtern um?
 *  - ausmaskieren des "Senders" aka ProductID und so
 *  - festen Empfänger vorsehen*/
CONST(CanFT2p0_DB_ChannelNameType, AUTOMATIC) Fueltech_WbO2Nano_RxChannel[] =
{
    FT_VersionInfoRequest,
    FT_ShortInfoRequest,
    FT_VeryShortInfoRequest
};
/** @brief Describes the channel transmitted from a Fueltech Wideband O2 Nano
 *  @details*/
CONST(CanFT2p0_DB_ChannelNameType, AUTOMATIC) Fueltech_WbO2Nano_TxChannel[] =
{
    FT_WbO2Nano_Data,
    FT_WbO2Nano_VersionInfo,
    FT_WbO2Nano_ShortInfo,
    FT_WbO2Nano_VeryShortMsg
};

/** @brief known Fueltech product specifications
 *
 *  @details
 *
 *  @todo the specification of the ECU (today the FT500) is not ready to use */
CONST(CanFT2p0_DataBaseType, AUTOMATIC)  RS601_Fueltech_DB[] =
{
  {
    Fueltech_SwitchPanel,
    CanFT2p0_SwitchPanelId,
    Fueltech_SwitchPanel_TxChannel,
    Fueltech_SwitchPanel_RxChannel
  },
  {
    FuelTech_O2Nano,
    CanFT2p0_WBo2Nano,
    Fueltech_WbO2Nano_TxChannel,
    Fueltech_WbO2Nano_RxChannel
  },
  {
    FuelTech_ECU_FT500,
    CanFT2p0_FT500Id,
    NULL_PTR,
    NULL_PTR
  }
};
/** @} */ // end of CanFT2p0_Spec_DataBase

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

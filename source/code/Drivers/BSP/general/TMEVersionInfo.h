/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * TMEVersionInfo.h

 * @author TManiac
 * @date 14.08.2022
 * @version 
 *
 */
#ifndef TMANIACENGINEERING__GENERAL_TMEVERSIONINFO_H_
#define TMANIACENGINEERING__GENERAL_TMEVERSIONINFO_H_

#include "TM_Std_Types.h"

/** @brief to hold the version info
 *  @details
 *  maybe we should add a copy constructor */

class TME_VersionInfo {
public:
  TME_VersionInfo();
  /** @brief constructor to set version Ids */
  TME_VersionInfo(uint8_t Module, uint8_t Version, uint8_t Patch);
  /** @brief constructor to set version Ids including the vendor */
  TME_VersionInfo(uint8_t Vendor, uint8_t Module, uint8_t Version, uint8_t Patch);
  /** @brief copy constructor */
  TME_VersionInfo(const TME_VersionInfo &other);

  virtual ~TME_VersionInfo();

//  TME_VersionInfo(TME_VersionInfo &&other);
//  TME_VersionInfo& operator=(const TME_VersionInfo &other);
//  TME_VersionInfo& operator=(TME_VersionInfo &&other);


private:
  /** @brief  my ID */
  CONST(uint8_t, AUTOMATIC) Vendor_ID       =  TM_VENDOR_ID;
  /** @brief  module id to see where the error is come from */
  CONST(uint8_t, AUTOMATIC) Module_ID      =  (0x00);
  /** @brief we have only one version at start */
  CONST(uint8_t, AUTOMATIC) Version_ID        =   (0x00);
  /** @brief no patching until now */
  CONST(uint8_t, AUTOMATIC) PatchVersion_ID  =    (0x00);
};

#endif /* TMANIACENGINEERING__GENERAL_TMEVERSIONINFO_H_ */

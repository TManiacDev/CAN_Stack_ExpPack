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
  TME_VersionInfo(uint16_t Module, uint16_t Version, uint16_t Patch);
  /** @brief constructor to set version Ids including the vendor */
  TME_VersionInfo(uint16_t Vendor, uint16_t Module, uint16_t Version, uint16_t Patch);
  /** @brief copy constructor */
  TME_VersionInfo(const TME_VersionInfo &other);

  virtual ~TME_VersionInfo();

  /** @brief Copies the VersionIinfo to a 8byte buffer
   *  @param[in] BufferLength should be 8 at minimum
   *  @param[out] pointer where the VersionInfo should be
   *  @return E_NOT_OK if buffer is to small */
  Std_ReturnType GetVersionInfo(CONST(uint32_t,AUTOMATIC) BufferLength, P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) Ptr2Buffer );

//  TME_VersionInfo(TME_VersionInfo &&other);
//  TME_VersionInfo& operator=(const TME_VersionInfo &other);
//  TME_VersionInfo& operator=(TME_VersionInfo &&other);


private:
  /** @brief  my ID */
  CONST(uint16_t, AUTOMATIC) Vendor_ID       =  TM_VENDOR_ID;
  /** @brief  module id to see where the error is come from */
  CONST(uint16_t, AUTOMATIC) Module_ID      =  (0x00);
  /** @brief we have only one version at start */
  CONST(uint16_t, AUTOMATIC) Version_ID        =   (0x00);
  /** @brief no patching until now */
  CONST(uint16_t, AUTOMATIC) PatchVersion_ID  =    (0x00);
};

#endif /* TMANIACENGINEERING__GENERAL_TMEVERSIONINFO_H_ */

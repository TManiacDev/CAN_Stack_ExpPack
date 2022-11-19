/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * TMEVersionInfo.cpp

 * @author TManiac
 * @date 14.08.2022
 * @version 
 *
 */
#include <TMEVersionInfo.h>

TME_VersionInfo::TME_VersionInfo() {
  // TODO Auto-generated constructor stub

}

TME_VersionInfo::TME_VersionInfo(uint8_t Module, uint8_t Version, uint8_t Patch) :
    Module_ID { Module },
    Version_ID { Version },
    PatchVersion_ID { Patch }
{
}

TME_VersionInfo::TME_VersionInfo(uint8_t Vendor, uint8_t Module, uint8_t Version, uint8_t Patch) :
    Vendor_ID { Vendor },
    Module_ID { Module },
    Version_ID { Version },
    PatchVersion_ID { Patch }
{
}

TME_VersionInfo::~TME_VersionInfo() {
  // TODO Auto-generated destructor stub
}

TME_VersionInfo::TME_VersionInfo(const TME_VersionInfo &other) :
        Vendor_ID { other.Vendor_ID },
        Module_ID { other.Module_ID },
        Version_ID { other.Version_ID },
        PatchVersion_ID { other.PatchVersion_ID }
{
  // TODO Auto-generated copy constructor stub

}

//TME_VersionInfo::TME_VersionInfo(TME_VersionInfo &&other) {
//  // TODO Auto-generated move constructor stub
//
//}

//TME_VersionInfo& TME_VersionInfo::operator=(const TME_VersionInfo &other) {
//  // TODO Auto-generated method stub (copy assignment operator)
//  Vendor_ID = other.Vendor_ID;
//  Module_ID = other.Module_ID;
//  Version_ID = other.Version_ID;
//  PatchVersion_ID = other.PatchVersion_ID;
//
//}
//
//TME_VersionInfo& TME_VersionInfo::operator=(TME_VersionInfo &&other) {
//  // TODO Auto-generated method stub (move assignment operator)
//  other.Vendor_ID = Vendor_ID;
//  other.Module_ID = Module_ID;
//  other.Version_ID = Version_ID;
//  other.PatchVersion_ID = PatchVersion_ID;
//
//}


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

TME_VersionInfo::TME_VersionInfo(uint16_t Module, uint16_t Version, uint16_t Patch) :
    Module_ID { Module },
    Version_ID { Version },
    PatchVersion_ID { Patch }
{
}

TME_VersionInfo::TME_VersionInfo(uint16_t Vendor, uint16_t Module, uint16_t Version, uint16_t Patch) :
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

Std_ReturnType TME_VersionInfo::GetVersionInfo( CONST(uint32_t,AUTOMATIC) BufferLength, P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) Ptr2Buffer )
{
  if (BufferLength >= 4*sizeof(uint16_t) )
  {
    Ptr2Buffer[0] = (uint8_t)(Vendor_ID >> 8);
    Ptr2Buffer[1] = (uint8_t)(Vendor_ID );
    Ptr2Buffer[2] = (uint8_t)(Module_ID >> 8);
    Ptr2Buffer[3] = (uint8_t)(Module_ID );
    Ptr2Buffer[4] = (uint8_t)(Version_ID >> 8);
    Ptr2Buffer[5] = (uint8_t)(Version_ID);
    Ptr2Buffer[6] = (uint8_t)(PatchVersion_ID >> 8);
    Ptr2Buffer[7] = (uint8_t)(PatchVersion_ID );
    return E_OK;
  }
  else return E_NOT_OK;
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


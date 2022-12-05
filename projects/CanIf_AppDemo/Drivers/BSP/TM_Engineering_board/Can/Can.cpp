/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Can.cpp

 * @author TManiac
 * @date Nov 19, 2022
 * @version 
 *
 */
#include "Can.h"

/** To hold the callback function pointers of the CanIf module */
P2VAR(ComIf, TM_CAN_VAR, AUTOMATIC) ptr2ComIf = NULL_PTR;

Can::Can() : TME_VersionInfo{CAN_MODULE_ID, CAN_VERSION, CAN_PATCH_VERSION}
{
  // TODO Auto-generated constructor stub

}

Can::~Can() {
  // TODO Auto-generated destructor stub
}


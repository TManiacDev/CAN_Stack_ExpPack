
/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanIfUpperLayer.cpp

 * @author TManiac
 * @date 19.08.2022
 * @version 
 *
 */
#include <CanIfUpperLayer.h>

CanIfUpperLayer::CanIfUpperLayer() {
  // TODO Auto-generated constructor stub

}

CanIfUpperLayer::~CanIfUpperLayer() {
  // TODO Auto-generated destructor stub
}

FUNC(Std_ReturnType, AUTOMATIC) CanIfUpperLayer::RxIndication(
    CONST(ComStack_PduType, AUTOMATIC) rxPduId,
    REF2CONST( ComStack_CanMsgHeader, AUTOMATIC) CanMsgHeader,
    REF2CONST( ComStack_PduInfoType, AUTOMATIC) PduInfo )
{
  Std_ReturnType returnValue = E_NOT_OK;

  VAR(ComStack_CanMessageType, AUTOMATIC) tempSdu;
  tempSdu.CanMsgHeader = CanMsgHeader;
  tempSdu.ptr2Data = PduInfo.SduDataPtr;

  returnValue = RxIndication(rxPduId, &tempSdu);
  return returnValue;
}

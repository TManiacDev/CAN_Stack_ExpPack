/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * FuelTechEcu.cpp

 * @author TManiac
 * @date Sep 25, 2022
 * @version 
 *
 */
#include "FuelTechEcu.h"

FuelTechEcu::FuelTechEcu() {
  // TODO Auto-generated constructor stub

}

FuelTechEcu::FuelTechEcu(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2ControllerInterface) :
      p2ControllerIf { p2ControllerInterface }
{

 // Init();

}

FuelTechEcu::~FuelTechEcu() {
  // TODO Auto-generated destructor stub
}


Std_ReturnType FuelTechEcu::Init(void)
{
  Std_ReturnType returnValue = E_NOT_OK;

  for (uint8_t streamIndex = 0; streamIndex < USED_RX_STREAMS; streamIndex++ )
  {
    if ( p2ControllerIf->ConnectUpperLayerIndication( rxStream[streamIndex].GetRxPduName(), &rxStream[streamIndex] ) == E_OK )
    {
      // do some thing on success
      rxStream[streamIndex].Init();
    }

  }
//  for ( auto& rxInitStream : rxStreamList )
//  {
//    if ( p2ControllerIf->ConnectUpperLayerIndication( (rxInitStream.GetRxPduName()), &rxInitStream ) == E_OK )
//    {
//      // do some thing on success
//      rxInitStream.Init();
//    }
//  }

  returnValue = E_OK;
  return returnValue;
}

void FuelTechEcu::Task(void)
{
  // coming soon

}

FUNC(CanFT2p_MeasureValueType, AUTOMATIC) FuelTechEcu::GetMeasureValue (CanFT2p0_MeasureID MeasureId)
{

  CanFT2p_MeasureValueType MeasureValue;
  // search meassure in stream

  for (uint8_t streamIndex = 0; streamIndex < USED_RX_STREAMS; streamIndex++ )
  {
    if ( rxStream[streamIndex].GetMeasureValue(MeasureId, MeasureValue) == E_OK )
    {
      break;
    }
  }
  return MeasureValue;
}

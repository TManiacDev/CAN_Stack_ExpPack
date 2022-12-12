/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanFT2p0Stream.cpp

 * @author TManiac
 * @date 04.10.2022
 * @version 
 *
 */
#include <CanFT2p0Stream.h>

#include <CanFT2p0_Compiler_Cfg.h>


CanFT2p0Stream::CanFT2p0Stream()
{
  // TODO Auto-generated constructor stub

}

CanFT2p0Stream::CanFT2p0Stream(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface)
  : CanFT2p0{ p2CanInterface }
{
  // TODO Auto-generated constructor stub

}

CanFT2p0Stream::CanFT2p0Stream(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface, CONST(CanIf_RxPduIdType, AUTOMATIC) rxPduName)
  : CanFT2p0{ p2CanInterface, rxPduName }
{
  // TODO Auto-generated constructor stub

}

CanFT2p0Stream::~CanFT2p0Stream()
{
  // TODO Auto-generated destructor stub
}

/** @attention
 *  - this function will be called in interrupt context
 *  - we need a secure to avoid buffer overflow */
FUNC(Std_ReturnType, TM_CANFT_CODE) CanFT2p0Stream::RxIndication(
    CONST(ComStack_PduType, AUTOMATIC) rxPduId,
    P2VAR(ComStack_CanMessageType, AUTOMATIC, AUTOMATIC) ptr2Sdu)
{
  Std_ReturnType returnValue = E_NOT_OK;

  if ( GetState() != CanFT2p0_StatesType::CANFT_ON )
  {
#if ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
    CANISOTP_CANFT2P0_DET_REPORTERRORDET_REPORTERROR(CANFT2P0_E_UNINIT, CANFT2P0_SCHEDULED_FUNC_ID);
#endif // ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
  }
  else
  {
    if ( ( ptr2Sdu != NULL_PTR ) &&
         (rxPduId < (ComStack_PduType)FT2p0_RxPduIdType::FT2p0_Rx_unknownPdu ) )
    {
      // first segmented message, we need a hard reset of segment counter:
      if ( ptr2Sdu->ptr2Data[0] == 0x0 )
      {
        // start new reading of segmented message
        dataCount = (ptr2Sdu->ptr2Data[1] << 8) + ptr2Sdu->ptr2Data[2];
        readCount = 0;
        for ( uint8_t byteCount = 3; byteCount < ptr2Sdu->CanMsgHeader.DLC; byteCount++ )
        {
          ((uint8_t*)dataList)[(dataCount-1)-readCount] = ptr2Sdu->ptr2Data[byteCount];
          readCount++;
        }
        segmCount = 1;
      }

      // all other segmented messages
      if ( ptr2Sdu->ptr2Data[0] == segmCount )
      {
        for ( uint8_t byteCount = 1; byteCount < ptr2Sdu->CanMsgHeader.DLC; byteCount++ )
        {
          ((uint8_t*)dataList)[(dataCount-1)-readCount] = ptr2Sdu->ptr2Data[byteCount];
          readCount++;
        }
        segmCount++;
      }

      // we have read all data bytes
      if ( readCount == dataCount )
      {
        // set data as valid read (maybe swap the mirror)
        //
        size = readCount / sizeof(CanFT2p0_DataHdlType);
        segmCount = 0;
      }
        returnValue = E_OK;


    }
#if ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
    else
    {
      CANFT2P0_DET_REPORTERROR(CANFT2P0_E_PARAM_POINTER, CANFT2P0_RXINDICATION_ID);
    }
#endif // ( CANISOTP_DEV_ERROR_DETECT == STD_ON )
  }
  return returnValue;
}

FUNC(CanFT2p_MeasureValueType, TM_CANFT_CODE) CanFT2p0Stream::GetMeasureValue (CONST(CanFT2p0_MeasureID, AUTOMATIC) MeasureId)
{

  CanFT2p_MeasureValueType MeasureValue = 0;
  // search meassure in stream

  for (uint8_t meassureIndex = 0; meassureIndex < 24; meassureIndex++ )
  {
    if ( dataList[meassureIndex].as.measure.MeasureId == MeasureId )
    {
      MeasureValue = dataList[meassureIndex].as.measure.MeasureValue;
    }
  }
  return MeasureValue;
}

FUNC(Std_ReturnType, TM_CANFT_CODE) CanFT2p0Stream::GetMeasureValue (CONST(CanFT2p0_MeasureID, AUTOMATIC) MeasureId, REF2VAR(CanFT2p_MeasureValueType, AUTOMATIC) MeasureValue)
{
  Std_ReturnType returnValue = E_NOT_OK;
  // search meassure in stream

  for (uint8_t meassureIndex = 0; meassureIndex < 24; meassureIndex++ )
  {
    if ( dataList[meassureIndex].as.measure.MeasureId == MeasureId )
    {
      MeasureValue = dataList[meassureIndex].as.measure.MeasureValue;
      returnValue = E_OK;
    }
  }
  return returnValue;
}

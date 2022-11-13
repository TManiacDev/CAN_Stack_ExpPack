/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanFT2p0Stream.h

 * @author TManiac
 * @date 04.10.2022
 * @version 
 *
 */
#ifndef THIRD_PARTY_TM_ENGINEERING_DATAEXCHANGE_FUELTECH_FTCAN2P0_CANFT2P0STREAM_H_
#define THIRD_PARTY_TM_ENGINEERING_DATAEXCHANGE_FUELTECH_FTCAN2P0_CANFT2P0STREAM_H_

#include <CanFT2p0.h>

#define maxSegment  24

class CanFT2p0Stream: public CanFT2p0 {
public:
  CanFT2p0Stream();
  CanFT2p0Stream(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface);
  CanFT2p0Stream(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface, CONST(CanIf_RxPduIdType, AUTOMATIC) rxPduName);
  virtual ~CanFT2p0Stream();

  /** @brief overwrite the function prototype supported by the CanIfUpperLayer class
   *
   *  @param[in] rxPduId  naming the incoming message
   *  @param[in] ptr2Sdu  pointer to the data unit */
  FUNC(Std_ReturnType, AUTOMATIC) RxIndication(
      CONST(ComStack_PduType, AUTOMATIC) rxPduId,
      P2VAR(ComStack_CanMessageType, AUTOMATIC, AUTOMATIC) ptr2Sdu);

  FUNC(CanFT2p_MeasureValueType, AUTOMATIC)  GetMeasureValue( CONST(CanFT2p0_MeasureID, AUTOMATIC) MeasureId );
  FUNC(Std_ReturnType, AUTOMATIC) GetMeasureValue( CONST(CanFT2p0_MeasureID, AUTOMATIC) MeasureId, REF2VAR(CanFT2p_MeasureValueType, AUTOMATIC) MeasureValue );

private:
  enum class CanMessageState
  {
    WaitForFirstMsg
  };
  uint16_t size = 0;
  uint16_t segmCount = 0;
  uint16_t dataCount = 0;
  uint16_t readCount = 0;
  CanFT2p0_DataHdlType dataList[maxSegment];
};

#endif /* THIRD_PARTY_TM_ENGINEERING_DATAEXCHANGE_FUELTECH_FTCAN2P0_CANFT2P0STREAM_H_ */

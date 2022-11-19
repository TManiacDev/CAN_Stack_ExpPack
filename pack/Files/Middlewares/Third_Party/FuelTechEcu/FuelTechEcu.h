/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * FuelTechEcu.h

 * @author TManiac
 * @date Sep 25, 2022
 * @version 
 *
 */
#ifndef THIRD_PARTY_TME_DATAEXCHANGE_FUELTECH_FT_ECU_FUELTECHECU_H_
#define THIRD_PARTY_TME_DATAEXCHANGE_FUELTECH_FT_ECU_FUELTECHECU_H_

#include "CanFT2p0Stream.h"
#include <vector>

#define USED_RX_STREAMS 4

typedef uint8_t pduDataType[8];
struct testStreamType
{
  uint16_t size;
  CanFT2p0_MeasureType* ptr2Data;
};

class FuelTechEcu
{
public:
  /** @brief standard constructor */
  FuelTechEcu();
  /** @brief constructor with link to the controller interface class
   * @param[in] p2ControllerInterface  pointer to a controller interface object */
  FuelTechEcu(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2ControllerInterface);
  virtual ~FuelTechEcu();

  /** @brief initialise the internal work */
  Std_ReturnType Init(void);

  /** @brief the scheduled task work */
  void Task(void);

  uint16_t GetMeasureValue (CanFT2p0_MeasureID MeasureId);
private:
  /**
   * @brief to hold the connection to the used communication controller interface
   * @details today we have only a CanIf. Later this will be a derived class from a virtual ControllerIf class */
  P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2ControllerIf  = nullptr;

  /* we need this here to config */
  CanFT2p0Stream rxStream[USED_RX_STREAMS] = {
      CanFT2p0Stream(p2ControllerIf, CanIf_Rx_CanFT_FT500_0FF),
      CanFT2p0Stream(p2ControllerIf, CanIf_Rx_CanFT_FT500_1FF),
      CanFT2p0Stream(p2ControllerIf, CanIf_Rx_CanFT_FT500_2FF),
      CanFT2p0Stream(p2ControllerIf, CanIf_Rx_CanFT_FT500_3FF) };

  // das hier funktioniert nicht. Warum???
  //std::vector<CanFT2p0Stream> rxStreamList
  //{
  //  CanFT2p0Stream(p2ControllerIf, CanIf_Rx_CanFT_FT500_0FF),
  //  CanFT2p0Stream(p2ControllerIf, CanIf_Rx_CanFT_FT500_1FF),
  //  CanFT2p0Stream(p2ControllerIf, CanIf_Rx_CanFT_FT500_2FF),
  //  CanFT2p0Stream(p2ControllerIf, CanIf_Rx_CanFT_FT500_3FF)
  //};

};

#endif /* THIRD_PARTY_TME_DATAEXCHANGE_FUELTECH_FT_ECU_FUELTECHECU_H_ */

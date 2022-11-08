/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanIfUpperLayer.h
 *
 * @author TManiac
 * @date 19.08.2022
 * @version 
 *
 */
#ifndef _CANIF_UPPERLAYER_CLASS_H_
#define _CANIF_UPPERLAYER_CLASS_H_

#include "TM_ComStack_Types.h"

#include "EcuNames_Cfg.h"
/** @addtogroup TM_OsiLayer3LowerInterface
 * @{ */

/** @brief to address the upper layer */
typedef enum
{
  /** @brief No upper layer is defined */
  CanIfUL_undefined,
  /** @brief CAN Networkmanagment Layer */
  CanIfUL_CanNM,
  /** @brief CAN TransportLayer module */
  CanIfUL_CanTP,
  /** @brief Global time Sync over CAN */
  CanIfUL_CanTSync,
  /** @brief Complex Device Driver */
  CanIfUL_CDD,
  /** @brief J1939 NM */
  CanIfUL_J1939NM,
  /** @brief J1939 TP */
  CanIfUL_J1939TP,
  /** @brief PDU Router module */
  CanIfUL_PduR,
  /** @brief Extended Calibration Protocol */
  CanIfUL_XCP,
  /** @brief Fueltech FT2.0 protocol */
  CanIfUL_FT2p0
}CanIf_UpperLayerType;

/**
 * @details
 * a class with the standard interface of the upper transport layer classes
 *
 * @todo maybe we should bring this to a template
 * */
class CanIfUpperLayer {
public:
  CanIfUpperLayer();
  virtual ~CanIfUpperLayer();

  /** @brief virtual function declaration to have an indication function in all upper layer classes
   *  @param[in] rxPduId  naming the incoming message
   *  @param[in] ptr2Sdu  pointer to the data unit */
  virtual  FUNC(Std_ReturnType, AUTOMATIC) RxIndication(
      CONST(ComStack_PduType, AUTOMATIC) rxPduId,
      P2VAR(ComStack_CanMessageType, AUTOMATIC, AUTOMATIC) ptr2Sdu) { return E_NOT_OK; } ;
};

/** @} */ // end of grouping TM_OsiLayer3LowerInterface
#endif /* _CANIF_UPPERLAYER_CLASS_H_ */

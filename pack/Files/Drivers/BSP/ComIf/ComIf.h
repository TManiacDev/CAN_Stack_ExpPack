/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * ComIf.h

 * @author TManiac
 * @date 08.10.2022
 * @version 
 *
 */
#ifndef BSP_COMIF_H_
#define BSP_COMIF_H_

/* includes only documentation : */
//#include "ComIf_Doxy.h"

/* imported types */
#include <CanIfUpperLayer.h>

#include <ComIf_Compiler_Cfg.h>


/* ===================== Development Error Tracer (DET)  ========== */
/** @addtogroup TM_DET_NAMES
 *  @{ */
/** @defgroup TM_DET_COMIF_NAMES Dev. Errors from Com interface base class */
/** @defgroup TM_DEM_COMIF_NAMES Runtime Errors from Com interface base class */
/** @} */ // end of grouping TM_DET_NAMES

//#include "DevErrorTraver.h"

/** @addtogroup TM_DET_COMIF_NAMES
 *  @{ */

/** @brief Development errors known by the Com interface module */
enum class ComIf_DevError
{
  /** @brief Module initialization has failed */
  E_INIT_FAILED = 0x04,
};
/** @} */ // end of grouping TM_DET_CANIF_NAMES

/** @addtogroup TM_DET_REPORT
 *  @{ */
/** @brief Macro to report dev errors from CAN interface module
 *  @details We use an expansion macro for development error reporting */
#if ( COMIF_DEV_ERROR_DETECT == STD_ON )
  #define COMIF_DET_REPORTERROR(ErrorId, ApiId) Det_ReportError(COMIF_MODULE_ID, 0, (ApiId), (ErrorId))
#else
#define COMIF_DET_REPORTERROR(ErrorId, ApiId) Error_Handler()
#endif // ( COMIF_DEV_ERROR_DETECT == STD_ON )
/** @} */ // end of grouping TM_DET_REPORT

/* ===================== Can Interface definition  ========== */

/** @addtogroup TM_ComIf_Main
*  @{ */

/** @brief the base class to hold a unique interface to all communication controller interface types
 *
 *  @details This class declares functions that must be known by the controller objects (if exists) and the first level of protocol objects */
class ComIf
{
public:
  /** @brief naming the known interface classes */
  enum class ComInterfaceType
  {
    /** unknown interface type */
    ComIfUnknown = 0,
    /** Controller area network (CAN) interface */
    CanIf,
    /** two wire interface, maybe I2C (until now just to old the place) */
    TwiIf,
    /** FlexRay interface */
    FlexRayIf
  };
  ComIf();
  /** @brief constructor to initialize the interface type value */
  ComIf( CONST(ComInterfaceType, AUTOMATIC) ComIfType );
  virtual ~ComIf();

  /** @brief get the type of communication controller interface */
  ComInterfaceType GetComIfType(void) { return connectedComInterface; };

  /** @brief Requests transmission of a PDU using the Tx software Buffer.
  @details
  returns E_NOT_OK if SW buffer full<br>
  this function is the AUTOSAR like transmit function

  @param[in] txPduId          name the Pdu to transmit
  @param[in] ptr2PduInfo      pointer to the data to transmit

  @return Std_ReturnType

  @todo we should rework to select the CAN Channel by using PDU IDs
  */
  virtual Std_ReturnType Transmit(
      CONST(ComStack_PduType,AUTOMATIC) txPduId,
      P2CONST(ComStack_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo) = 0;

  /** @brief poll the RxBuffer for a message
   *  @details This function looks if there is an message inside the buffer by checking the PDU name
   *
   *  This is the AUTOSAR like function  ReadRxPduData
   *
   *  @param[in]  rxPduId       search for the PDU by using the CanIf_RxPduIdType
   *  @param[out] ptr2PduInfo      to return the data */
  virtual Std_ReturnType Receive(
      CONST(ComStack_PduType,AUTOMATIC) rxPduId,
      P2VAR(ComStack_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo) = 0;

  virtual ComStack_PduType GetIfRxPduName(
      CONST(CanIf_UpperLayerType, AUTOMATIC) upperLayerName,
      CONST(ComStack_PduType, AUTOMATIC) rxPduId ) = 0;

  virtual ComStack_PduType GetIfTxPduName(
      CONST(CanIf_UpperLayerType, AUTOMATIC) upperLayerName,
      CONST(ComStack_PduType, AUTOMATIC) txPduId ) = 0;


  /** @brief we need to know the connected upper layer object for rx indication
   *
   *  @details maybe we solve this in a static way on code generation later
   *  @param[in] rxPduId to name the rx pdu
   *  @param[in] p2UpperLayerObject   to give the pointer to the object */
  virtual Std_ReturnType ConnectUpperLayerIndication(
      CONST(ComStack_PduType,AUTOMATIC) rxPduId,
      P2VAR(CanIfUpperLayer,AUTOMATIC,AUTOMATIC) p2UpperLayerObject) = 0;

  /** @brief There is a RxIndication function on every ComIf class
   *  @details The service CanIf_RxIndication() is implemented in CanIf and called by CanDrv after a CAN L-PDU has been received. */
  virtual void RxIndication(
      CONST( ECU_CanController, AUTOMATIC) Controller,
      REF2CONST( ComStack_CanMsgHeader, AUTOMATIC) CanMsgHeader,
      REF2CONST( ComStack_PduInfoType, AUTOMATIC) PduInfo ) = 0;

private:
  /** @brief to hold the interface type value */
  const ComInterfaceType connectedComInterface = ComInterfaceType::ComIfUnknown;
};
/** @} */ // end of TM_ComIf_Main
#endif /* BSP_COMIF_H_ */

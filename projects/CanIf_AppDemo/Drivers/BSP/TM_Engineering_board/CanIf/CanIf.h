/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanIf.h

 * @author TManiac
 * @date 20.08.2022
 * @version 
 *
 */
#ifndef CANIF_H_
#define CANIF_H_

/* includes only documentation : */
#include "CanIf_Doxy.h"

/** @addtogroup TM_CanIf_Main
 *  @{
 *  TM_CanIf.h */

/* imported types */
#include "EcuNames_Cfg.h"
#include "Can.h"
#include "CanIf_Cfg.h"
#include "ComIf.h"

#include <CanIf_Compiler_Cfg.h>

/** @} */ // end of grouping TM_CanIf_Main

/* ===================== Development Error Tracer (DET)  ========== */
/** @addtogroup TM_DET_NAMES
 *  @{ */
/** @defgroup TM_DET_CANIF_NAMES Dev. Errors from CAN interface module */
/** @defgroup TM_DEM_CANIF_NAMES Runtime Errors from CAN interface module */
/** @} */ // end of grouping TM_DET_NAMES

//#include "DevErrorTraver.h"

/** @addtogroup TM_DET_CANIF_NAMES
 *  @{ */

/** @brief Development errors known by the Can interface module */
enum class CanIf_DevError
{
  /** @brief Module initialization has failed */
  E_INIT_FAILED = 0x04,
  /** @brief need some more error codes */
  E_SETUP_FAILED
};
/** @} */ // end of grouping TM_DET_CANIF_NAMES

/** @addtogroup TM_DET_REPORT
 *  @{ */
/** @brief Macro to report dev errors from CAN interface module
 *  @details We use an expansion macro for development error reporting */
#if ( CANIF_DEV_ERROR_DETECT == STD_ON )
  #define CANIF_DET_REPORTERROR(ErrorId, ApiId) Det_ReportError(CANIF_MODULE_ID, 0, (ApiId), (ErrorId))
#else
#define CANIF_DET_REPORTERROR(ErrorId, ApiId) Error_Handler()
#endif // ( CANIF_DEV_ERROR_DETECT == STD_ON )
/** @} */ // end of grouping TM_DET_REPORT

//#include "CanIf_Switch.h"

 /* ===================== Can Interface definition  ========== */

/** @addtogroup TM_CanIf_Main
 *  @{ */

/** working states of the CanIf class
 *
 *  @image html CanIf_StateMachine.svg "CanIf State Machine"
 *  */
enum class CanIfStates
{
  /** on construction we will be in */
  PreInit,
  /** for hardware init we will be in */
  HwInit,
  /** for filter init we will be in */
  FilterInit,
  /** the module is in working state */
  Ready,
  /** we can do a stop on it */
  Stopped,
  /** we should never come to */
  ErrorState,
  /** the object will be cleaned */
  ShutDown
};


/** @class CanIf */

/** @} */ // end of grouping TM_CanIf_Main

/* ****** struct defines ************ */
/** @addtogroup TM_CanIf_Types
 *  @{ */
/** The type to handle PDUs on the CanIf  */
typedef struct
{
  /** CanIf can handle only byte like data */
  P2VAR(uint8_t,AUTOMATIC,AUTOSAR_COMSTACKDATA) SduDataPtr;
  /** count of the data bytes.
   *
   *  This will be max 8 on normal CAN and 64 on CAN-FD */
  PduLengthType SduLength;
}CanIf_PduInfoType;
/** @} */ // end of grouping TM_CanIf_Types

/** @addtogroup TM_CanIf_RxPduCfg
 *  @{ */

/** @brief to hold the configuration of a RxPdu */
typedef struct
{
  /** @brief name of this L-PDU */
  VAR(uint32_t, AUTOMATIC) L_PDU_Name;
  /** @brief The base Id */
  VAR(ComStack_CanIdType, AUTOMATIC) CanId;
  /** @brief Mask to select dynamic Id bits */
  VAR(ComStack_CanIdType, AUTOMATIC) IdMask;
  /** @brief ??? */
  VAR(uint32_t, AUTOMATIC) MsgLength;
  /** @brief name the used hardware */
  VAR(ECU_CanController, AUTOMATIC ) InstanceName;
  /** @brief name of the upper layer N-PDU */
  VAR(tm_PduIDType, AUTOMATIC) N_PDU_Name;
  /** @brief name the upper layer */
  VAR(CanIf_UpperLayerType, AUTOMATIC ) ULName;

}CanIf_RxPduCfgType;
/** @} */ // end of grouping TM_CanIf_RxPduCfg

/** @brief the class to work on the CAN controller interface
 *  @details
 *  Gemäß dem AUTOSAR Gedanken abstrahiert das CAN Interface die gesamte CAN Hardware.
 *  Es wird also später auch nur ein CanIf Objekt geben.
 *
 *  Genauso wird diese CanIf Objekt global angelegt sein.
 *
 *  @todo es braucht eine Absicherung auf nur ein Objekt */
class CanIf
    : public TME_VersionInfo,
      public ComIf
{
public:
  /** Standard constructor will do a connection to the precompile configuration */
  CanIf();

  /** Destructor shouldn't called on an embedded system */
  ~CanIf();

/** @addtogroup TM_CanIf_Func
 *  @{ */

  /** @brief init of the CanIf module
   *  @details
   *  This will start the hardware modules
   *  @sa CANIF_INIT_ID */
  Std_ReturnType Init(void);
  /** @brief service ID of CanIf::Init() */
  #define CANIF_INIT_ID          (0x01)

  /** @brief all init of the CanIf module is done
   *  @details
   *  This will start the interface modules */
  Std_ReturnType Start(void);

  /** @brief Requests transmission of a PDU using the Tx software Buffer.
  @details
  returns E_NOT_OK if SW buffer full<br>
  this function is the AUTOSAR like transmit function

  @param[in] txPduId          name the Pdu to transmit
  @param[in] ptr2PduInfo      pointer to the data to transmit

  @return Std_ReturnType

  @todo we should rework to select the CAN Channel by using PDU IDs
  */
  Std_ReturnType Transmit(
      CONST(CanIf_TxPduIdType,AUTOMATIC) txPduId,
      P2CONST(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo);

  /** @brief Requests transmission of a PDU using the Tx software Buffer.
  @details
  returns E_NOT_OK if SW buffer full<br>
  This function remaps the pure virtual function coming from the ComIf class

  @param[in] txPduId          name the Pdu to transmit
  @param[in] ptr2PduInfo      pointer to the data to transmit

  @return Std_ReturnType

  @todo we should rework to select the CAN Channel by using PDU IDs
  */
  Std_ReturnType Transmit(
      CONST(ComStack_PduType,AUTOMATIC) txPduId,
      P2CONST(ComStack_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo);

  /** @brief Requests transmission of a PDU using the Tx software Buffer.
  @details
  this function is we send messages without a transport protocol, maybe for test messages

  returns E_NOT_OK if SW buffer full

  @param[in] msgHeader      Header for the CAN message handling
  @param[in] ptr2Data       pointer to the data to transmit

  @return Std_ReturnType
  */
  Std_ReturnType Transmit(
      VAR(ComStack_CanMsgHeader, AUTOMATIC) msgHeader,
      P2CONST(uint8_t, AUTOMATIC, AUTOMATIC) ptr2Data);

  /** @brief poll the RxBuffer for a message
   *  @details This function looks if there is an message inside the buffer by checking the PDU name
   *
   *  This is the AUTOSAR like function  CanIf_ReadRxPduData
   *
   *  @param[in]  rxPduId       search for the PDU by using the CanIf_RxPduIdType
   *  @param[out] ptr2PduInfo      to return the data */
  Std_ReturnType Receive(
      CONST(CanIf_RxPduIdType,AUTOMATIC) rxPduId,
      P2VAR(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo);

  /** @brief poll the RxBuffer for a message
   *  @details This function remaps the pure virtual function coming from the ComIf class
   *
   *  This is the AUTOSAR like function  CanIf_ReadRxPduData
   *
   *  @param[in]  rxPduId       search for the PDU by using the CanIf_RxPduIdType
   *  @param[out] ptr2PduInfo      to return the data */
  Std_ReturnType Receive(
      CONST(ComStack_PduType,AUTOMATIC) rxPduId,
      P2VAR(ComStack_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo);

  /** @brief poll the RxBuffer for a message
   *
   *  @details This function looks if there is an message inside the buffer with the requested CAN ID (including IDE & RTR)
   *  @param[in,out]  msgHeader   we need the CanId to look for the message
   *  @param[out]     ptr2Data   pointer to return the data -> we need a C++ save way */
  Std_ReturnType Receive(
      REF2VAR(ComStack_CanMsgHeader, AUTOMATIC ) msgHeader,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2Data );

  /** @brief we need to know the connected upper layer object for rx indication
   *
   *  @details maybe we solve this in a static way on code generation later
   *  @param[in] rxPduId to name the rx pdu
   *  @param[in] p2UpperLayerObject   to give the pointer to the object */
  Std_ReturnType ConnectUpperLayerIndication(
      CONST(ComStack_PduType,AUTOMATIC) rxPduId,
      P2VAR(CanIfUpperLayer,AUTOMATIC,AUTOMATIC) p2UpperLayerObject);

  /** @brief to get the CanIf_RxPduIdType name */
  ComStack_PduType GetIfRxPduName(
      CONST(CanIf_UpperLayerType, AUTOMATIC) upperLayerName,
      CONST(ComStack_PduType, AUTOMATIC) rxPduId );

  /** @brief to get the CanIf_TxPduIdType name */
  ComStack_PduType GetIfTxPduName(
      CONST(CanIf_UpperLayerType, AUTOMATIC) upperLayerName,
      CONST(ComStack_PduType, AUTOMATIC) txPduId );

/** @} */ // end of grouping TM_CanIf_Func

  /** @brief task function to push the tx message from software buffer to tx mailbox */
  void TxTask(void);

  /** The service CanIf_RxIndication() is implemented in CanIf and called by CanDrv after a CAN L-PDU has been received. */
  void RxIndication(
      CONST( ECU_CanController, AUTOMATIC) Controller,
      REF2CONST( ComStack_CanMsgHeader, AUTOMATIC) CanMsgHeader,
      REF2CONST( ComStack_PduInfoType, AUTOMATIC) PduInfo );

private:

  /** we have a simple state machine inside */
  CanIfStates state = CanIfStates::PreInit;

  /** @brief we need a handle to hold the information for the bxCAN controller
   *  @todo there are STM controller with three CAN controller too!!! */
  //CAN_HandleTypeDef bxCanHdl[2];


  /** @brief We create a list with CAN message headers for fast access sorted by the CanIf_txPduIdType
   *
   *  @details we use the STM-CAN-Message-Headers for fast copy during tx. Maybe we change this later
   * on pre compiled linking that could be on FLASH */
  VAR(STM_HAL_TxHeaderTypeDef, AUTOMATIC) txHeaderList[CANIF_TXPDU_COUNT];

  /** @brief We create a list with CAN message headers for fast access sorted by the CanIf_rxPduIdType
   *
   *  @details on rx we can use the the ComStack type (in contrast to STM HAL type)
   * on pre compiled linking that could be on FLASH */
  VAR(ComStack_CanMsgHeader, AUTOMATIC) rxHeaderList[CANIF_RXPDU_COUNT];

  /** @brief to hold the CanDrv(s)*/
  CONSTP2VAR(Can, AUTOMATIC,AUTOMATIC) ptr2CanDriver;

  /** @brief this list will hold the pointer to the upper layers in same order like the rxHeaderList */
  P2VAR(CanIfUpperLayer, AUTOMATIC,AUTOMATIC) p2UpperLayerList[CANIF_RXPDU_COUNT];
};
#endif /* CANIF_H_ */

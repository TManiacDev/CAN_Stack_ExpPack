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
#include "Can_Cfg.h"
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

#include "CanIf_Switch.h"

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

/** @brief remapping of the HAL CAN Header to the Header used inside this implementation
 *  @remark this function should be used only and immediately on received message
 *
 *  @param[in] rev2HAL_Header  reference to the HAL header with data inside
 *  @param[out] rev2CanIfHeader reference where the data should be copied
 *  @return    E_NOT_OK if one pointer is NULL_PTR*/
Std_ReturnType HalHeaderToCanIfHeader(
    REF2CONST(CAN_RxHeaderTypeDef,AUTOMATIC)  rev2HAL_Header,
    REF2VAR(ComStack_CanMsgHeader, AUTOMATIC)  rev2CanIfHeader );

/** @brief remapping of the CAN Header to the HAL Header used by the STM HAL
 *  @remark this function should be used only and immediately before transmit a message
 *
 *  @param[in] rev2CanIfHeader  pointer to the header with data inside
 *  @param[out] rev2HAL_Header pointer where the data should be copied
 *  @return    E_NOT_OK if one pointer is NULL_PTR*/
Std_ReturnType CanIfHeaderToHalHeader(
    REF2CONST(ComStack_CanMsgHeader, AUTOMATIC)  rev2CanIfHeader,
    REF2VAR(CAN_RxHeaderTypeDef,AUTOMATIC)  rev2HAL_Header );

/** @brief the class to work on the CAN controller interface
 *  @details
 *  Gemäß dem AUTOSAR Gedanken abstrahiert das CAN Interface die gesamte CAN Hardware.
 *  Es wird also später auch nur ein CanIf Objekt geben.
 *
 *  Genauso wird diese CanIf Objekt global angelegt sein.
 *
 *  @todo es braucht eine Absicherung auf nur ein Objekt */
class CanIf
    : TME_VersionInfo,
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


 // CAN_HandleTypeDef* GetHardwareHandle(uint8_t Channel)
  //{
  //  return &bxCanHdl[Channel];
  //};

private:

  /** @brief to find a free CAN hardware filter
   *  @details STM hasn't a function like this in the HAL.<br>
   *  We find a free hardware filter and returns the filter bank to use the filter.<br>
   *  We returns the filter number to use it on fast selection in IRQ routine.<br>
   *  The filter mode is used to search for mask or identifier filter.
   *  If searching for identifier filter we returns also if there is a FR2 is empty
   *
   *  @param[out] ptr2FilterBankNumber returns the number of the first free filter bank
   *  @param[out] ptr2FilterNumber     returns the filter number according to the previous filter configuration
   *  @param[in,out] ptr2FilterMode    selects the search for Mask filter (aka deactivated filter) or Identifier Filter.
   *                                   on Identifier Filter search it returns if the FR1 register is already in use
   *  @returns
   *  - E_OK      ...........  we found an unused filter
   *  - E_NOT_OK  ...........  we can't find an unused filter */
  Std_ReturnType FindFreeFilter(
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterBankNumber,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterNumber,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterMode);

  /** @brief configure a free hardware filter using bit masking
   *  @details set hardware filter
   *
   *  @attention
   *  This isn't the same like inside STM register access.
   *  But the function manages the correct use for STM HAL
   *  - bit 31 is IDE
   *  - bit 30 is RTR
   *
   *  @param[in] Controller   select the controller where the filter should be applied
   *  @param[in] FilterId     the selected filter bits
   *  @param[in] FilterMask   the filter mask to select valid filter bits
   *  @return                 E_OK if the filter is applied, E_NOT_OK no hardware filter free */
  Std_ReturnType SetFilterByBitmask(
      VAR(ECU_CanController, AUTOMATIC) Controller,
      VAR(ComStack_CanIdType, AUTOMATIC) FilterId,
      VAR(ComStack_CanIdType, AUTOMATIC) FilterMask);

  /** @brief configure a free hardware filter using single CAN Id filtering
   *  @details set hardware filter
   *
   *  @param[in] Controller   select the controller where the filter should be applied
   *  @param[in] FilterId     the selected filter bits
   *  @return                 E_OK if the filter is applied, E_NOT_OK no hardware filter free */
  int SetFilterByCanId(
     VAR(ECU_CanController, AUTOMATIC) Controller,
     VAR(ComStack_CanIdType, AUTOMATIC) FilterId );

  /** @brief change the 32bit format to use with STM Registers
   *  @details we use the unified CanIf_CanIdSelectType for easy remapping
   *
   *  this function or the union can be changed to match register on other controller
   *
   *  @param[in] CanId should be a CanIf formated CanId
   *  @return CanId in STM Register format */
  uint32_t CanIdToHalFormat(
      VAR(ComStack_CanIdType, AUTOMATIC) CanId);

  /** we have a simple state machine inside */
  CanIfStates state = CanIfStates::PreInit;

  /** @brief we need a handle to hold the information for the bxCAN controller
   *  @todo there are STM controller with three CAN controller too!!! */
  CAN_HandleTypeDef bxCanHdl[2];

  /** a semi static place to bring messages from buffer to hardware */
  CAN_TxMessage canTxBufferMirror;

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
};
#endif /* CANIF_H_ */

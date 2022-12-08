/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanDrv_bxCAN.h

 * @author TManiac
 * @date Nov 19, 2022
 * @version 
 *
 */
#ifndef _CANDRV_BXCAN_H_
#define _CANDRV_BXCAN_H_

#include "Can.h"

/* ************* Types ********** */
/** @addtogroup TM_Can_Types
 *  @{ */

/** @brief the handling of rx buffer needs some states of the buffered message */
enum class bxCan_RxMessageStateType
{
  /** @brief the Rx Message is free for use */
  RxMessage_free,
  /** @brief the Rx Message is blocked to write */
  RxMessage_write,
  /** @brief the Rx Message is ready for transmit */
  RxMessage_rdy2rd,
  /** @brief the Rx Message is blocked for transmit */
  RxMessage_read,
  /** @brief if the upper layer needs a callback we can handle a ok transmit */
  RxMessage_rxok,
  /** @brief if the upper layer needs a callback we can handle a failed transmit */
  RxMessage_rxerr,
  /** @brief maybe we handle internal errors */
  RxMessage_unkown
};

/** @brief the handling of tx buffer needs some states of the buffered message */
enum class bxCan_TxMessageStateType
{
  /** @brief the Tx Message is free for use */
  TxMessage_free,
  /** @brief the Tx Message is blocked to write */
  TxMessage_write,
  /** @brief the Tx Message is ready for transmit */
  TxMessage_rdy2tx,
  /** @brief the Tx Message is blocked for transmit */
  TxMessage_transmit,
  /** @brief if the upper layer needs a callback we can handle a ok transmit */
  TxMessage_txok,
  /** @brief if the upper layer needs a callback we can handle a failed transmit */
  TxMessage_txerr,
  /** @brief maybe we handle internal errors */
  TxMessage_unkown
};

/** @brief bxCAN specific standard CanId type
 *  @details
 *  to use the 32bit for standard CAN Id on STM registers */
typedef struct
{
  /** @brief Transmit request (only used inside the Tx mailbox register) */
  uint32_t TXRQ:1;
  /** @brief Remote transmission request */
  uint32_t RTR:1;
  /** @brief identifier extension */
  uint32_t IDE:1;
  /** @brief unused bits */
  uint32_t unused:18;
  /** @brief Standard Id */
  uint32_t Id11bit:11;
}bxCan_StdCanIdType;

/** @brief bxCAN specific extended CanId type
 *  @details
 *  to use the 32bit for extended CAN Id on STM registers */
typedef struct
{
  /** @brief Transmit request (only used inside the Tx mailbox register) */
  uint32_t TXRQ:1;
  /** @brief Remote transmission request */
  uint32_t RTR:1;
  /** @brief identifier extension */
  uint32_t IDE:1;
  /** @brief extended Id */
  uint32_t Id29bit:29;
}bxCan_ExtCanIdType;

/** @brief to unify to handle the CAN Id formats */
typedef union
{
  /** @brief to use it like uint32 */
  uint32_t        common;
  /** @brief to use it on standard Ids from STM Registers */
  bxCan_StdCanIdType stm_StdId;
  /** @brief to use it on extended Ids from STM Registers */
  bxCan_ExtCanIdType stm_ExtId;
  /** @brief to use it on extended Ids how we use it inside the CanIf */
  ComStack_CanIdType  can_Id;
}bxCan_IdSelectType;


/** @brief this is a test structure to hold data and header for a rx message
 *  @details because of the filtermatch element inside the rx header we need two different buffer types :-( */
typedef struct
{
  /** @brief current state of this RxMessage */
  bxCan_RxMessageStateType State;
  /** @brief The header of the CAN message
   *  @details this is the public header used by inside my implementation */
  VAR(ComStack_CanMsgHeader, AUTOMATIC)       CanMsgHeader;
  /** @brief DON'T USE: The Header used by STM inside the HAL
   *  @details This header is only used by call of HAL functions. <br>
   *           There must be remapping before/after the HAL function.
   *  @todo  it will be at the end of the struct, maybe we hide this with a casted type */
  STM_HAL_RxHeaderTypeDef   HAL_Header;
  /// hold the data
  uint8_t               Data[8];
}bxCan_RxMessageType;

/** @brief this is a test structure to hold data and header for a tx message
 * @todo ich muss mich noch entscheiden wie ich den notwendigen CAN Controller auswähle
 *       - entweder zwei Buffer
 *       - oder die Message weiß wohin sie muss
 *       - was ist wenn eine Nachricht auf beide Controller muss
 *
 * @todo nur das CAN Module (aka HAL) darf CAN Message bedienen, aber mein State gehört in das Interface */
typedef struct
{
  /// @brief current state of this TxMessage
  bxCan_TxMessageStateType State;
  /// @brief to select the controller master or slave
  ECU_CanController Controller;
  /// @brief hold the header info
  STM_HAL_TxHeaderTypeDef   Header;
  /// @brief the transmit function returns the HW mailbox if we need it
  uint32_t Mailbox;
  /// hold the data
  uint8_t               Data[8];
}bxCan_TxMessageType;

/** @brief a simple structure to handle a software rx fifo */
typedef struct
{
  /// Position to write next Message
  uint8_t BufWrPos;
  /// position to read last Message
  uint8_t BufRdPos;
  /// to hold the pointer to the Message buffer
  bxCan_RxMessageType* ptr2MsgBuffer;
}bxCan_RxSwBufferType;
/** @} */ // end of grouping TM_Can_Types

/** @brief remapping of the HAL CAN Header to the Header used inside this implementation
 *  @remark this function should be used only and immediately on received message
 *
 *  @param[in] rev2HAL_Header  reference to the HAL header with data inside
 *  @param[out] rev2CanIfHeader reference where the data should be copied
 *  @return    E_NOT_OK if one pointer is NULL_PTR*/
Std_ReturnType HalHeaderToCanStackHeader(
    REF2CONST(CAN_RxHeaderTypeDef,AUTOMATIC)  rev2HAL_Header,
    REF2VAR(ComStack_CanMsgHeader, AUTOMATIC)  rev2CanStackHeader );

/** @brief remapping of the CAN Header to the HAL Header used by the STM HAL
 *  @remark this function should be used only and immediately before transmit a message
 *
 *  @param[in] rev2CanIfHeader  pointer to the header with data inside
 *  @param[out] rev2HAL_Header pointer where the data should be copied
 *  @return    E_NOT_OK if one pointer is NULL_PTR*/
Std_ReturnType CanIfHeaderToHalHeader(
    REF2CONST(ComStack_CanMsgHeader, AUTOMATIC)  rev2CanIfHeader,
    REF2VAR(CAN_RxHeaderTypeDef,AUTOMATIC)  rev2HAL_Header );

/** @addtogroup TM_Can_Driver
 *  @{ */

/** @brief driver class to work with the STM32 bxCAN controller module */
class CanDrv_bxCAN: public Can {
public:
  /** @brief standard constructor for a bxCAN controller object */
  CanDrv_bxCAN();
  /** @brief standard destructor for a bxCAN controller object */
  virtual ~CanDrv_bxCAN();

  /** @brief task function to push the tx message from software buffer to tx mailbox */
  void TxTask(void);

  /** @brief Init function for the bxCAN */
  Std_ReturnType Init(
      P2CONST(CanConfigType, AUTOMATIC, AUTOMATIC) ptr2Config = NULL_PTR,
      P2VAR(ComIf, TM_CAN_VAR, AUTOMATIC) ptr2ComIfObject = NULL_PTR  );

  /** @brief The API to set a controller mode
   *  @param[in] Controller    selects the controller
   *  @param[in] Transition    selects the transition per name/id
   *  @sa CAN_SET_CONTROLLER_MODE_ID */
  Std_ReturnType SetControllerMode ( ECU_CanController Controller, CanControllerStates Transition );

  /** @brief The API to write a message to tx FIFO
   *  @param[in] Controller   select the controller for tx
   *  @param[in] PduInfo      the CAN message to send */
  Std_ReturnType Write(
      ECU_CanController Controller,
      P2CONST(ComStack_CanMessageType, AUTOMATIC,AUTOMATIC) ptr2PduInfo );

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
  Std_ReturnType SetFilterByCanId(
     VAR(ECU_CanController, AUTOMATIC) Controller,
     VAR(ComStack_CanIdType, AUTOMATIC) FilterId );

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
      VAR(ECU_CanController, AUTOMATIC) Controller,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterBankNumber,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterNumber,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterMode);

  /** @brief change the 32bit format to use with STM Registers
   *  @details
   *
   *  @param[in] CanId should be a CanIf formated CanId
   *  @return CanId in STM bxCAN Register format */
  FUNC(uint32_t, TM_CAN_CODE) CanIdToStmRegisterFormat(
      VAR(ComStack_CanIdType, AUTOMATIC) CanId);


  /** @brief we need a handle to hold the information for the bxCAN controller */
  CAN_HandleTypeDef bxCanHdl[2];

  /** @brief we want a Tx software buffer
   *
   *  we start with a fix size. Later it would be go to the IDE
   * @todo bring the buffers to save class */
  bxCan_TxMessageType     canTxBuffer[CAN_TX_SW_BUFFER_SIZE];
};

/** @} */ // end of grouping TM_Can_Driver

#endif /* _CANDRV_BXCAN_H_ */

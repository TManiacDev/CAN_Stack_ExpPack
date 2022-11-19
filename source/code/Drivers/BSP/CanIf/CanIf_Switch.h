/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanIf_Switch.h

 * @author TManiac
 * @date 20.08.2022
 * @version 
 *
 */
#ifndef BSP_TME_BOARD_CANIF_CANIF_SWITCH_H_
#define BSP_TME_BOARD_CANIF_CANIF_SWITCH_H_

/************ CAN Module = hardware specific ***********/
#define CANIF_IS_CANID_EQUAL(RequestCanId, TestCanId)  ((RequestCanId.Id29bit==TestCanId.Id29bit)&&(RequestCanId.IDE==TestCanId.IDE)&&(RequestCanId.RTR==TestCanId.RTR))

/** @addtogroup TM_Can_Types
 *  @{ */

/** @brief no RTR bit set */
#define CANIF_NO_RTR 0

 /** @brief RTR bit set */
 #define CANIF_USE_RTR 1

/** @brief use standard CAN ID */
#define CANIF_STDID 0

/** @brief use extended CAN ID */
#define CANIF_EXTID 1

/** @brief structure to hold the timing configuration of the bitrates */
typedef struct tCAN_BitrateConfig
{
  /** @brief clock prescaler */
  uint32_t Prescaler;
  /** @brief jump width for resync */
  uint32_t SyncJumpWidth;
  /** @brief time segment length before Abtastpunkt */
  uint32_t TimeSeg1;
  /** @brief time segment length after Abtastpunkt */
  uint32_t TimeSeg2;
}CAN_BitrateConfig;

/** @} */ // end of grouping TM_Can_Types

/** @addtogroup TM_CanCfg_ParaCfg
 * @{ */

/** @brief to hold the handling parameters */
typedef struct
{
  /// hold the pointer to the hardware instance registers
  P2VAR(CAN_TypeDef, AUTOMATIC, AUTOMATIC ) Instance;
  /// setup the mode
  VAR(uint32_t, AUTOMATIC )     Mode;
  /// use time triggered mode
  VAR(FunctionalState, AUTOMATIC )     TTMode;
  /// use auto bus off function
  VAR(FunctionalState, AUTOMATIC )     AutoBusOff;
  /// use auto wake up function
  VAR(FunctionalState, AUTOMATIC )     AutoWakeUp;
  /// use auto retransmission
  VAR(FunctionalState, AUTOMATIC )     AutoRetransmission;
  /// will be the full fifo locked
  VAR(FunctionalState, AUTOMATIC )     ReceiveFifoLocked;
  /// switch internal time based transmission priority on
  VAR(FunctionalState, AUTOMATIC )     TransmitFifoPriority;
  /// initial Baudrate
  VAR(CanControllerBaudRateConfigID, AUTOMATIC )  InitBaudrate;
}CanControllerParaType;
/** @} */ // end of grouping TM_CanCfg_ParaCfg

/** @addtogroup TM_CanCfg_BaudCfg
 * @{ */

/** @brief Configuration parameters for a baudrate setting
 *
 *  @todo we should add a picture to explain the bit segments */
typedef struct
{
    /** @brief
     * we save the ID also in the configuration so we can check it */
    VAR(CanControllerBaudRateConfigID, AUTOMATIC )  CanControllerBaudrateID;
    /** @brief
     * Specifies the baudrate of the controller in kbps */
    VAR(uint16_t, AUTOMATIC )    CanControllerBaudRate;
    /** @brief
     * Specifies propagation delay in time quantas. */
    VAR(uint32_t, AUTOMATIC )    CanControllerPrescaler;
    /** @brief
     * Specifies scaling factor for CAN controller clock.
     * @details not used on STM32 bxCAN Controller */
    VAR(uint32_t, AUTOMATIC )    CanControllerPropSeg;
    /** @brief
     * Specifies phase segment 1 in time quantas */
    VAR(uint32_t, AUTOMATIC )    CanControllerSeg1;
    /** @brief
     * Specifies phase segment 2 in time quantas. */
    VAR(uint32_t, AUTOMATIC )    CanControllerSeg2;
    /** @brief
     * Specifies the synchronization jump width for the controller in time quantas  */
    VAR(uint32_t, AUTOMATIC )    CanControllerSyncJumpWidth;
}CanControllerBaudrateConfigType;
/** @} */ // end of grouping TM_CanCfg_BaudCfg

/** @addtogroup TM_CanCfg_HwFilter
 *  @brief parameters to ...
 *  @{ */

/** @brief This container is only valid for HRHs and contains the configuration (parameters) of one hardware filter. */
typedef struct
{
    /** @brief
     * Specifies (together with the filter mask) the identifiers range that passes the hardware filter. */
  VAR(uint32_t, AUTOMATIC ) CanHwFilterCode;
    /** @brief
     * Describes a mask for hardware-based filtering of CAN identifiers. */
  VAR(uint32_t, AUTOMATIC ) CanHwFilterMaskType;
}CanHwFilterType;

/** @} */ // end of grouping TM_CanCfg_HwFilter

/** @addtogroup TM_CanCfg_ConfigSet
    @{ */

/** @brief The structure of the overall configuration for the CAN */
typedef struct
{
  /** @brief Pointer to the baudrate configuration
   *
   *  we should use P2CONST macro */
  const CanControllerBaudrateConfigType * ptr2CanBaudrateConfigSet;
  /** @brief Pointer to the parameter configuration
   *
   *  we should use P2CONST macro */
  const CanControllerParaType * ptr2CanParaConfigSet;
  /** @brief pointer to filter configruation
   *
   *  we use the STM filter structure
   *  we should use P2CONST macro */
  const CAN_FilterTypeDef * ptr2CanFilterConfigSet;
}CanConfigType;

/** @} */ // end of grouping TM_CanCfg_ConfigSet

/********** CAN Interface Hardware abstraction ************/
/** @addtogroup TM_CanIf_Types
 *  @{ */

/****** fix enumerations / symbolic names ******/

/** @brief the handling of tx buffer needs some states of the buffered message */
typedef enum
{
  /** @brief the Tx Message is free for use */
  CanIf_TxMessage_free,
  /** @brief the Tx Message is blocked to write */
  CanIf_TxMessage_write,
  /** @brief the Tx Message is ready for transmit */
  CanIf_TxMessage_rdy2tx,
  /** @brief the Tx Message is blocked for transmit */
  CanIf_TxMessage_transmit,
  /** @brief if the upper layer needs a callback we can handle a ok transmit */
  CanIf_TxMessage_txok,
  /** @brief if the upper layer needs a callback we can handle a failed transmit */
  CanIf_TxMessage_txerr,
  /** @brief maybe we handle internal errors */
  CanIf_TxMessage_unkown
}CanIf_TxMessageStateType;

/** @brief the handling of rx buffer needs some states of the buffered message */
typedef enum
{
  /** @brief the Rx Message is free for use */
  CanIf_RxMessage_free,
  /** @brief the Rx Message is blocked to write */
  CanIf_RxMessage_write,
  /** @brief the Rx Message is ready for transmit */
  CanIf_RxMessage_rdy2rd,
  /** @brief the Rx Message is blocked for transmit */
  CanIf_RxMessage_read,
  /** @brief if the upper layer needs a callback we can handle a ok transmit */
  CanIf_RxMessage_rxok,
  /** @brief if the upper layer needs a callback we can handle a failed transmit */
  CanIf_RxMessage_rxerr,
  /** @brief maybe we handle internal errors */
  CanIf_RxMessage_unkown
}CanIf_RxMessageStateType;


/** @} */ // end of grouping TM_CanIf_Types

/******* simple typedefs ************/

/******* struct defines *************/
/** @addtogroup TM_CanIf_Types
 *  @{ */
/** @brief this is a test structure to hold data and header for a tx message
 * @todo ich muss mich noch entscheiden wie ich den notwendigen CAN Controller auswähle
 *       - entweder zwei Buffer
 *       - oder die Message weiß wohin sie muss
 *       - was ist wenn eine Nachricht auf beide Controller muss
 *
 * @todo nur das CAN Module (aka HAL) darf CAN Message bedienen, aber mein State gehört in das Interface */
typedef struct tCAN_TxMessage
{
  /// @brief current state of this TxMessage
  CanIf_TxMessageStateType State;
  /// @brief hold the header info
  STM_HAL_TxHeaderTypeDef   Header;
  /// @brief the transmit function returns the HW mailbox if we need it
  uint32_t Mailbox;
  /// hold the data
  uint8_t               Data[8];
}CAN_TxMessage;

typedef struct
{
  /// @brief hold the header info
  STM_HAL_RxHeaderTypeDef   Header;
  /// hold the data
  uint8_t               Data[8];
}CanIf_RxMessageType;


/** @brief to use the 32bit for standard CAN Id on STM registers */
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
}CanIf_STM_StdCanIdType;

/** @brief to use the 32bit for extended CAN Id on STM registers */
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
}CanIf_STM_ExtCanIdType;

/** @brief to use the 32bit for standard CAN Id */
typedef struct
{
  /** @brief Standard Id */
  uint32_t Id11bit:11;
  /** @brief unused bits */
  uint32_t unused:19;
  /** @brief Remote transmission request */
  uint32_t RTR:1;
  /** @brief identifier extension */
  uint32_t IDE:1;
}CanIf_StdCanIdType;

/** @brief to use the 32bit for extended CAN Id */
typedef struct
{
  /** @brief extended Id */
  uint32_t Id29bit:29;
  /** @brief unused bits */
  uint32_t unused:1;
  /** @brief Remote transmission request */
  uint32_t RTR:1;
  /** @brief identifier extension */
  uint32_t IDE:1;
}CanIf_CanIdType;

/** @brief to unify to handle the CAN Id formats */
typedef union
{
  /** @brief to use it like uint32 */
  uint32_t        common;
  /** @brief to use it on standard Ids from STM Registers */
  CanIf_STM_StdCanIdType stm_StdId;
  /** @brief to use it on extended Ids from STM Registers */
  CanIf_STM_ExtCanIdType stm_ExtId;
  /** @brief to use it on standard Ids how we use it inside the CanIf */
  CanIf_StdCanIdType  canif_StdId;
  /** @brief to use it on extended Ids how we use it inside the CanIf */
  ComStack_CanIdType  canif_ExdId;
}CanIf_CanIdSelectType;

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

/** @brief this is a test structure to hold data and header for a rx message
 *  @details because of the filtermatch element inside the rx header we need two different buffer types :-( */
typedef struct tCAN_RxMessage
{
  /** @brief current state of this RxMessage */
  CanIf_RxMessageStateType State;
  /** @brief The header of the CAN message
   *  @details this is the public header used by inside my implementation */
  ComStack_CanMessageType       CanIf_Message;
  /** @brief DON'T USE: The Header used by STM inside the HAL
   *  @details This header is only used by call of HAL functions. <br>
   *           There must be remapping before/after the HAL function.
   *  @todo  it will be at the end of the struct, maybe we hide this with a casted type */
  STM_HAL_RxHeaderTypeDef   HAL_Header;
}CanIf_MessageType;

/** @brief a simple structure to handle a software rx fifo */
typedef struct
{
  /// Position to write next Message
  uint8_t BufWrPos;
  /// position to read last Message
  uint8_t BufRdPos;
  /// to hold the pointer to the Message buffer
  CanIf_MessageType* ptr2MsgBuffer;
}CanIf_RxBufferType;


#endif /* BSP_TME_BOARD_CANIF_CANIF_SWITCH_H_ */

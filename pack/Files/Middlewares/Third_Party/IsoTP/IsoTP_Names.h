/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanIsoTP.h

 * @author TManiac
 * @date 30.03.2022
 * @version
 *
 */
#ifndef TMANIACENGINEERING_CAN_TM_CANISOTP_NAMES_H_
#define TMANIACENGINEERING_CAN_TM_CANISOTP_NAMES_H_

/** @addtogroup TM_IsoTP_Types
 *   @{ */

/**************************************************************
 * internal used defines
 *************************************************************/

/** name the return errors*/
enum class IsoTp_ReturnErrorType
{
  /** Today we return that the data will copied later */
  RET_CALL_OF_COPY = 2,
  /** return with a undefined error */
  RET_ERROR         = E_NOT_OK,
  /** return with an ok */
  RET_OK            = E_OK,
  /** last accepted frame before overflow */
  RET_LAST_OK       = -1,
  /** return while the function is already in progress */
  RET_E_INPROGRESS  = -2,
  /** return in case of a overrun */
  RET_E_OVERFLOW    = -3,
  /** return in case of a wrong sequence number */
  RET_E_WRONG_SN    = -4,
  /** no data to do the work */
  RET_E_NO_DATA     = -5,
  /** there is a timeout */
  RET_E_TIMEOUT     = -6,
  /** there was a data length that isn't defined for this job */
  RET_E_LENGTH      = -7
};

/* return logic true if 'a' is after 'b' */
#define IsoTpTimeAfter(a,b) ((int32_t)((int32_t)(b) - (int32_t)(a)) < 0)

/*  invalid bs */
#define ISOTP_INVALID_BS       0xFFFF

#define ISOTP_IDLE           0
#define ISOTP_WAIT_FIRST_FC  1
#define ISOTP_WAIT_FC        2
#define ISOTP_WAIT_DATA      3
#define ISOTP_SENDING        4

// Events
#define ISOTP_RX_EVENT       0x01

#define ISOTP_TX_TIMEOUT_SET 0x01
#define ISOTP_TX_CANCEL      0x02

// Flags
#define CAN_ISOTP_29BIT_ID      1
#define CAN_ISOTP_EXTEND_ADDR   2
#define CAN_ISOTP_TX_PADDING    4
#define CAN_ISOTP_LISTEN_MODE   8

/* USER CODE BEGIN CanIsoTP_Defines 0 */

/* USER CODE END CanIsoTP_Defines 0 */

/**
@brief States type to handle behavior.

@todo maybe we bring a standard type to Std_types.h
*/
enum class IsoTP_StatesType
{
  /** CAN TP module isn't initialized */
  IsoTP_OFF,
  /** CAN TP module is ready to work */
  IsoTP_ON
};

/** @brief we can have only one of this states */
enum class IsoTP_RxTxStatus
{
  IsoTP_Init,

  IsoTP_SendIdle,
  IsoTP_SendInProgress,
  IsoTP_SendError,

  IsoTP_ReceiveIdle,
  IsoTP_ReceiveInProgress,
  IsoTP_ReceiveFull
};

/**
@brief Messages types defined by ISO 1576-3.
*/
enum class IsoTP_FrameType
{
  /** @brief CAN TP handling a single frame message = 0x0 */
  IsoTP_SingleFrame,
  /** @brief CAN TP handling the first frame on segmented messages = 0x1 */
  IsoTP_FirstFrame,
  /** @brief CAN TP handling consecutive frame of a segmented message = 0x2 */
  IsoTP_ConsecutiveFrame,
  /** @brief CAN TP handling control messages = 0x3 */
  IsoTP_FlowControl
};

/** @brief Private: network layer result code.
 */
enum class IsoTP_ProtocolResultType
{
  RESULT_OK           =   0,
  RESULT_TIMEOUT_A    =  -1,
  RESULT_TIMEOUT_BS   =  -2,
  RESULT_TIMEOUT_CR   =  -3,
  RESULT_WRONG_SN     =  -4,
  RESULT_INVALID_FS   =  -5,
  RESULT_UNEXP_PDU    =  -6,
  RESULT_WFT_OVRN     =  -7,
  RESULT_BUFFER_OVFLW =  -8,
  RESULT_ERROR        =  -9
};

/* can fram defination */

/** @brief to select the type without knowing the kind of type
 *  @details
 *     */
typedef struct
{
  uint8_t reserve_1:4;
  IsoTP_FrameType type:4;
  uint8_t reserve_2[7];
} IsoTP_PciType;

/** @brief we are a Single Frame
 *  @details
* single frame
*
*  | byte #0                  || ...  |
*  | :---------: | :---------: | :--- |
*  | nibble #0   | nibble #1   | ...  |
*  | PCIType = 0 | SF_DL       | ...  |
*/
typedef struct
{
  uint8_t SF_DL:4;
  IsoTP_FrameType type:4;
  uint8_t data[7];
} IsoTP_SingleFrameType;

/** @brief we are the first frame of segmented transfer
 *  @details
* first frame
*
* | byte #0                || byte #1              || ... |
* | :---------: | :-------: | :-------: | :-------: | :-- |
* | nibble #0   | nibble #1 | nibble #2 | nibble #3 | ... |
* | PCIType = 1 | FF_DL                           ||| ... |
*/
typedef struct
{
  uint8_t FF_DL_high:4;
  IsoTP_FrameType type:4;
  uint8_t FF_DL_low;
  uint8_t data[6];
} IsoTP_FirstFrameType;

/** @brief we are a consecutive frame of segmented transfer
 *  @details
* consecutive frame
*
*  | byte #0                  || ...  |
*  | :---------: | :---------: | :--- |
*  | nibble #0   | nibble #1   | ...  |
*  | PCIType = 0 | SN          | ...  |
*/
typedef struct
{
  uint8_t SN:4;
  IsoTP_FrameType type:4;
  uint8_t data[7];
} IsoTP_ConsecutiveFrameType;

/** @brief Private: Protocol Control Information (PCI) flow control identifiers.
 */
enum class IsoTP_FlowStatus
{
    CONTINUE = 0x0,
    WAIT     = 0x1,
    OVERFLOW = 0x2
};

/** @brief the flow control message
 *  @details
* flow control frame
*
* | byte #0                || byte #1              || byte #2              || ... |
* | :---------: | :-------: | :-------: | :-------: | :-------: | :-------: | :-- |
* | nibble #0   | nibble #1 | nibble #2 | nibble #3 | nibble #4 | nibble #5 | ... |
* | PCIType = 1 | FS        | BS                   || STmin                || ... |
*/
typedef struct
{
  IsoTP_FlowStatus FS:4;
  IsoTP_FrameType type:4;
  uint8_t BS;
  uint8_t STmin;
  uint8_t reserve[5];
} IsoTP_FlowControlType;

/** @brief to handle the data array as it is
 *  @details maybe to copy to or from buffer */
typedef struct
{
  uint8_t ptr[8];
} IsoTP_DataArrayType;

/** @brief to use the 8 data bytes in an union type */
typedef struct
{
  union {
    IsoTP_PciType              common;
    IsoTP_SingleFrameType      single_frame;
    IsoTP_FirstFrameType       first_frame;
    IsoTP_ConsecutiveFrameType consecutive_frame;
    IsoTP_FlowControlType      flow_control;
    IsoTP_DataArrayType        data_array;
  } as;
} CanIsoTP_8ByteData;

/**************************************************************
 * protocol specific defines
 *************************************************************/




/** @} */ // end of grouping TM_IsoTP_Types

#endif /* TMANIACENGINEERING_CAN_TM_CANISOTP_H_ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

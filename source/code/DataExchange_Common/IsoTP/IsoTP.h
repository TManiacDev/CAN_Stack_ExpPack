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
#ifndef TMANIACENGINEERING_COMMON_ISOTP_H_
#define TMANIACENGINEERING_COMMON_ISOTP_H_

 /** includes only documentation : */
#include "IsoTP_Doxy.h"

/** @addtogroup TM_IsoTP
 *  @{
 *  CanIsoTP.h */

/* Imported types */
#include "IsoTP_Names.h"
#include "IsoTP_Cfg.h"
#include "TMEVersionInfo.h"
#include "ComIf.h"

/** @brief  my ID */
#define ISOTP_VENDOR_ID           TM_VENDOR_ID
/** @brief  module id to see where the error is come from */
#define ISOTP_MODULE_ID           (0xF2)
/** @brief we have only one version at start */
#define ISOTP_VERSION             (0x01)
/** @brief no patching until now */
#define ISOTP_PATCH_VERSION       (0x01)

/** @} */ // end of TM_IsoTP grouping

/* ===================== Development Error Tracer (DET)  ========== */

/** @addtogroup TM_DET_NAMES
 *  @{ */
/** @defgroup TM_DET_ISOTP_NAMES Dev. Errors from CAN ISO TP */
/** @defgroup TM_DEM_ISOTP_NAMES Runtime Errors from CAN ISO TP */
/** @} */

//#include "DevErrorTraver.h"
/** @addtogroup TM_DET_ISOTP_NAMES
 *  @{ */

/** @brief to name the development errors
 *
 *  @details numbers greater then 0xc0 aren't like AUTOSAR */
enum class IsoTp_DevError
{
  /** @brief API service called with invalid config
   *  @details When CanTp_Transmit is called for a none configured PDU identifier
   *           or with an identifier for a received PDU.*/
  ISOTP_E_PARAM_CONFIG = 0x01,
  /** @brief API service called with invalid Pdu ID
   *  @details When CanTp_Transmit is called for a none configured PDU identifier
   *           or with an identifier for a received PDU. */
  ISOTP_E_PARAM_ID   = 0x02,
  /** @brief API service called with NULL pointer
   *  @details  In case of this error, the API service shall return immediately
   *            without any further action, besides reporting this development error. */
  ISOTP_E_PARAM_POINTER  = 0x03,
  /** @brief Module initialization has failed */
  ISOTP_E_INIT_FAILED = 0x04,
  /** @brief API service used without initialization
   *  @details On any API call except CanTp_Init(), CanTp_GetVersionInfo()
   *           and CanTp_MainFunction() if CanTp is in state CANTP_OFF */
  ISOTP_E_UNINIT = 0x20,
  /** @brief Invalid Transmit Pdu Id used */
  ISOTP_E_INVALID_TX_ID = 0x30,
  /** @brief Invalid Receive Pdu Id used */
  ISOTP_E_INVALID_RX_ID = 0x40,

  /* private error types */
  ISOTP_E_BUFFER_OVERRUN = 0xF0,

  /** error on decode a frame */
  ISOTP_E_INVALID_FRAME = 0xF1,
  /** error on decode a frame */
  ISOTP_E_INVALID_FRAMELENGTH = 0xF2,

  /** @brief this is just a place holder */
  ISOTP_E_UNDEFINED = 0xFF
};
/** @} */ // end of grouping TM_DET_CANISOTP_NAMES

/** @addtogroup TM_DET_REPORT
 *  @{ */
/** @brief Macro to report dev errors from CAN IsoTP transport layer module
 *  @details We use an expansion macro for development error reporting */
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
  #define ISOTP_DET_REPORTERROR(ErrorId, ApiId) Det_ReportError(ISOTP_MODULE_ID, 0, (ApiId), (ErrorId))

#else
  #define ISOTP_DET_REPORTERROR(ErrorId, ApiId) Error_Handler()
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
/** @} */ // end of grouping TM_DET_REPORT


/* ==================End Development Error Tracer (DET)  ==========*/

/** @addtogroup TM_IsoTP_Types
 *  @{ */

/** @to hold the static data of the object */
struct IsoTp_ObjectConfig
{
  /** @brief to know the rx PDU name */
  VAR(IsoTP_RxPduType, AUTOMATIC) rxPduName;
  /** @brief to know the tx PDU name */
  VAR(IsoTP_TxPduType, AUTOMATIC) txPduName;
  /** @brief to hold the config to use
   *  @details the config defines timing and flow control */
  P2CONST(IsoTP_ConfigType, AUTOMATIC, AUTOMATIC) ptr2Config;
  /** hold the connection to the communication controller interface */
  P2VAR(ComIf, AUTOMATIC, AUTOMATIC) p2ControllerInterface;
};

/**
 * @brief to control the flow
 */
typedef struct
{
  /** extends the state machine */
  VAR(IsoTP_RxTxStatus, AUTOMATIC) ProtocolStatus;
  /** */
  VAR(IsoTP_ProtocolResultType, AUTOMATIC)  ProtocolResult;
  /** number of accepted bytes in the next block */
  VAR(uint32_t, AUTOMATIC)    RemainingBlockSize;
  /** Separation Time between consecutive frames, unit milliseconds */
  VAR(uint32_t, AUTOMATIC)    MinSeparationTime;
  /** counts the wait for transmit messages */
  VAR(uint32_t, AUTOMATIC) WaitForTransmitCounter;
  /** current sequence number during transmit or receive */
  VAR(uint16_t, AUTOMATIC) SeqNumber;
  /** current offset during transmit or receive */
  VAR(uint16_t, AUTOMATIC) DataOffset;
  /** */
  VAR(uint32_t, AUTOMATIC) bsTimer;
  VAR(uint32_t, AUTOMATIC) stTimer;
  VAR(uint32_t, AUTOMATIC) crTimer;
  /** @brief to know the rx PDU name used by the ComIf*/
  VAR(ComStack_PduType, AUTOMATIC) rxIfPduName;
  /** @brief to know the tx PDU name used by the ComIf */
  VAR(ComStack_PduType, AUTOMATIC) txIfPduName;
}IsoTP_ControlType;

/** struct to hold a const size number and a pointer to writable memory */
typedef struct
{
  VAR(uint32_t, AUTOMATIC) DataReceivedSize;
  /** to know the size of the linked buffer */
  CONST(uint32_t,AUTOMATIC) DataBufferSize;
  /** the rx data need write access */
  CONSTP2VAR(uint8_t, AUTOMATIC, AUTOMATIC) p2RxData;
}IsoTp_RxBufferType;

/** struct to hold a const size number and a pointer to readable memory */
typedef struct
{
  /** to know the size of the linked buffer */
  CONST(uint32_t,AUTOMATIC) DataBufferSize;
  /** the rx data need write access */
  CONSTP2CONST(uint8_t, AUTOMATIC, AUTOMATIC) p2TxData;
}IsoTp_TxBufferType;

/** @brief we need a type to manage the work of the protocol using object
 *  @details
 *  was wir brauchen:
 *  - ist es ein tx (wollen wir die Daten senden) oder ein rx (wollen wir die Daten verarbeiten) objekt?
 *  - some objects are responce objects they need rx & tx
 *
 *  das Can Interface braucht:
 *  - Can ID
 *  - wir haben immer Extended Mode
 *  - DLC wird im Protokol bestimmt und ist abhängig von der Nachricht
 *  - den Datenstrom
 *  - bei mehr als 8 Datenbytes muss das Streaming im Protokoll erfolgen
 *
 *  die Applikation braucht:
 *  - den Namen, bzw die Id des Objektes
 *  - Zugriff auf die entsprechenden Daten
 *  */
typedef struct
{
  /** @brief to handle the init */
  VAR(IsoTP_StatesType, AUTOMATIC) ModuleState;
  /** @brief Task tick */
  VAR(uint32_t, AUTOMATIC) TaskTicks;
  /** @brief to hold the values needed on flow control */
  VAR(IsoTP_ControlType, AUTOMATIC) FlowControl;
  /** the tx data pointer is pointing to const data, so we don't change the content */
  P2CONST(IsoTp_TxBufferType, AUTOMATIC, AUTOMATIC) p2TxBuffer;
  /** the rx data need write access */
  P2VAR(IsoTp_RxBufferType, AUTOMATIC, AUTOMATIC) p2RxBuffer;
}IsoTP_HandlingType;
/** @} */ // end of grouping TM_IsoTP_Types


/** @addtogroup TM_IsoTP
 *  @{ */
/**
 *  @brief a class to handle the IsoTp protocol
 *
 *  @details
 *  - We start to implement the ECU/slave side of communication
 *  - we must response on functional (0x7DF/0x18DB33F1) and physical addressing (0x7E0, 0x7E1... / 0x18DAXXF1 )
 *  - every time response is on physical addressing (*/
class IsoTp
    : TME_VersionInfo,
      public CanIfUpperLayer
{

public:
  IsoTp();
  /** @brief constructor with connection to a communication controller interface */
  IsoTp(CONST(IsoTp_ObjectConfig, AUTOMATIC) initConfig);
  virtual ~IsoTp();

  /** @brief This function initializes the object according the background configuration.
  @details
  returns E_NOT_OK if there is a problem on the config

  @sa TM_ISOTP_INIT_ID
  @param[in]   ptr2Config     pointer to hold configuration
  @return Std_ReturnType

  @version 04.2022
  */
  FUNC(Std_ReturnType, AUTOMATIC) Init( P2CONST(IsoTP_ConfigType, AUTOMATIC, AUTOMATIC) ptr2Config );
  FUNC(Std_ReturnType, AUTOMATIC) Init( CONST(IsoTP_RxTxStatus, AUTOMATIC) SendOrReceive = IsoTP_RxTxStatus::IsoTP_SendIdle );
  /** @brief service ID of IsoTP::Init() */
  #define TM_ISOTP_INIT_ID          (0x01)

  /** @brief Get the name of the linked rx PDU
   *  @todo we should add a virtual function to the CanIfUpperLayer class */
  FUNC(IsoTP_RxPduType, AUTOMATIC) GetRxPduName(void);

  /** @brief Get the name of the linked rx PDU
   *  @todo we should add a virtual function to the CanIfUpperLayer class */
  FUNC(IsoTP_TxPduType, AUTOMATIC) GetTxPduName(void);

  /** @brief to get the module state */
  FUNC(IsoTP_StatesType, AUTOMATIC) GetState( void );
/** @brief the transmit function
   *  @param[in] ptr2TxBuffer    pointer to the data array structure including the size */
  FUNC(Std_ReturnType, AUTOMATIC) Transmit( P2CONST(IsoTp_TxBufferType, AUTOMATIC, AUTOMATIC) ptr2TxBuffer );

  /** @brief the transmit function
   *  @param[in] payload    pointer to the data array
   *  @param[in] size       byte count */
  FUNC(Std_ReturnType, AUTOMATIC) Transmit( CONST(uint8_t, AUTOMATIC) payload[], CONST(uint16_t, AUTOMATIC) size );

  /** @brief overwrite the function prototype supported by the CanIfUpperLayer class
   *
   *  @param[in] rxPduId  naming the incoming message
   *  @param[in] ptr2Sdu  pointer to the data unit */
  FUNC(Std_ReturnType, AUTOMATIC) RxIndication(
      CONST(ComStack_PduType, AUTOMATIC) rxPduId,
      P2VAR(ComStack_CanMessageType, AUTOMATIC, AUTOMATIC) ptr2Sdu);
  #define TM_ISOTP_RXINDICATION_ID      (0xF2)

  /**
  @brief to handle the protocol
  @sa TM_ISOTP_SCHEDULED_FUNC_ID
  @return Std_ReturnType
  */
  FUNC(Std_ReturnType, AUTOMATIC) Task( void );
  /** @brief service ID of IsoTP::Task() */
  #define TM_ISOTP_SCHEDULED_FUNC_ID          (0xF1)
private:

  /* #### init functions #### */

  /** @brief initialize the object handle*/
  FUNC(Std_ReturnType, AUTOMATIC) InitHandle( void );
#define TM_ISOTP_INITHANDLE_ID          (0x5401)

  /* #### send functions #### */

  /** @brief the flow controll message will be send */
  FUNC(Std_ReturnType, AUTOMATIC) SendFlowControl( CONST(IsoTP_FlowStatus, AUTOMATIC ) FlowStatus );
#define TM_ISOTP_SEND_FLOWCONTROL_ID      (0x5410)

  /** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
  FUNC(Std_ReturnType, AUTOMATIC) SendSingleFrame( void );
#define TM_ISOTP_SEND_SINGLEFRAME_ID      (0x5411)

  /** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
  FUNC(Std_ReturnType, AUTOMATIC) SendFirstFrame( void );
#define TM_ISOTP_SEND_FIRSTFRAME_ID      (0x5412)

  /** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
  FUNC(Std_ReturnType, AUTOMATIC) SendConsecutiveFrame( void );
#define TM_ISOTP_SEND_CONSECUTIVE_ID      (0x5413)

  /* #### receive functions #### */

  /** @brief do the work on a flow control message */
  FUNC(Std_ReturnType, AUTOMATIC) ReceiveFlowControl( P2CONST(CanIsoTP_8ByteData ,AUTOMATIC, AUTOMATIC) ptr2FlowControlFrame );
#define TM_ISOTP_RECEIVE_FLOWCONTROL_ID      (0x5420)

  /** @brief do the work on a received single frame message */
  FUNC(Std_ReturnType, AUTOMATIC) ReceiveSingleFrame( P2CONST(CanIsoTP_8ByteData ,AUTOMATIC, AUTOMATIC) ptr2SingleFrame );
#define TM_ISOTP_RECEIVE_SINGLEFRAME_ID      (0x5421)

  /** @brief do the work on a received first frame message */
  FUNC(Std_ReturnType, AUTOMATIC) ReceiveFirstFrame( P2CONST(CanIsoTP_8ByteData ,AUTOMATIC, AUTOMATIC) ptr2FirstFrame );
#define TM_ISOTP_RECEIVE_FIRSTFRAME      (0x5422)

  /** @brief do the work on a received consecutive frame message */
  FUNC(Std_ReturnType, AUTOMATIC) ReceiveConsecutiveFrame( P2CONST(CanIsoTP_8ByteData ,AUTOMATIC, AUTOMATIC) ptr2ConsFrame, CONST(uint8_t, AUTOMATIC) len );
#define TM_ISOTP_RECEIVE_CONSECUTIVE_ID      (0x5423)

  /* #### other functions #### */

  /** convert millisecond to STmin value */
  FUNC(uint8_t, AUTOMATIC) ms_to_st_min(uint8_t ms);

  /** convert STmin value to millisecond */
  FUNC(uint8_t, AUTOMATIC) st_min_to_ms(uint8_t st_min);

  /** To get the actual millisecond of the system */
  FUNC(uint32_t, AUTOMATIC) GetMillisecond( void );

  /* ############### member data #################################### */

  /** @brief to handle the object lifetime */
  VAR(IsoTP_HandlingType, AUTOMATIC) objectHandle = { .ModuleState = IsoTP_StatesType::IsoTP_OFF } ;
  /** @brief to hold the object configuration */
  CONST(IsoTp_ObjectConfig, AUTOMATIC) objectConfig = { .rxPduName = IsoTP_Rx_unknownPdu,
                                                        .txPduName = IsoTP_Tx_unknownPdu,
                                                        .ptr2Config = &IsoTP_DefaultConfig,
                                                        .p2ControllerInterface = NULL_PTR,
                                                      };
};
/** @} */ // end of TM_IsoTP grouping

#endif /* TMANIACENGINEERING_COMMON_ISOTP_H_ */

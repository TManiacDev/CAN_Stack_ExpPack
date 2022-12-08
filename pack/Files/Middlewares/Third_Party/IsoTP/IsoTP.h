/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * IsoTP.h

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
 *  IsoTP.h */

/** @} */ // end of TM_IsoTP grouping

/* Imported types */
#include "TMEVersionInfo.h"
#include "IsoTP_Names.h"
#include "IsoTP_Cfg.h"
#include "ComIf.h"

#include "Uds.h"

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
  /** we have a buffer overrun inside the IsoTp */
  ISOTP_E_BUFFER_OVERRUN = 0xF0,

  /** error on decode a frame */
  ISOTP_E_INVALID_FRAME = 0xF1,
  /** error on decode a frame */
  ISOTP_E_INVALID_FRAMELENGTH = 0xF2,

  /** @brief this is just a place holder */
  ISOTP_E_UNDEFINED = 0xFF
};
/** @} */ // end of grouping TM_DET_ISOTP_NAMES

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

/** @addtogroup TM_IsoTP_CfgTypes
 *  @{ */

/** @brief This are addressing format types defined by the ISO
 *
 *  I need them to understand the work */
enum class IsoTp_AddressingFormatTypes
{
  /** A unique CAN identifier is assigned to each combination of N_SA, N_TA, N_TAtype and Mtype.
   *  N_PCI and N_Data are filed in the CAN frame data field. */
  NormalAddressing,
  /** This should be like normal but what is extended? CanID or addressing style like in mixed? */
  ExtendedAddressing,
  /** A unique CAN identifier is assigned to each combination of N_SA, N_TA, N_TAtype.
   *  N_AE is placed in the first data byte of the CAN frame data field.
   *  N_PCI and N_Data are placed in the remaining bytes of the CAN frame data field. */
  Mixed11bitAddressing,
  /**   */
  NormalFixedAddressing,
  /** This should be the same like with 11bit CanID */
  Mixed29bitAddressing
};

/** @brief There are two types of addressing */
enum class IsoTp_AddressingType
{
  /** In the transport layer, functional addressing refers to N-SDU, of which parameter
      N_TAtype (which is an extension to the N_TA parameter [14] used to encode the
      communication model) has the value functional.
      This means the N-SDU is used in 1 to n communications. Thus with the CAN
      protocol, functional addressing will only be supported for Single Frame
      communication.
      In terms of application, functional addressing is used by the external (or internal)
      tester if it does not know the physical address of an ECU that should respond to a
      service request or if the functionality of the ECU is implemented as a distributed
      server over several ECUs. When functional addressing is used, the communication
      is a communication broadcast from the external tester to one or more ECUs (1 to n
      communication).
      Use cases are (for example) broadcasting messages, such as “ECUReset” or
      “CommunicationControl”
      OBD communication will always be performed as part of functional addressing.
   */
  FunctionalAddressing,
  /** In the transport layer, physical addressing refers to N-SDU, of which parameter
      N_TAtype (which is an extension of the N_TA parameter [14] used to encode the
      communication model) has the value physical.
      This means the N-SDU is used in 1 to 1 communication, thus physical addressing
      will be supported for all types of network layer messages.
      In terms of application, physical addressing is used by the external (or internal)
      tester if it knows the physical address of an ECU that should respond to a service
      request. When physical addressing is used, a point to point communication takes
      place (1 to 1 communication).
      Use cases are (for example) messages, such as “ReadDataByIdentifier” or
      “InputOutputControlByIdentifier”
   */
  PhysicalAddressing
};

/** @} */ // end of grouping TM_IsoTP_CfgTypes

/** @addtogroup TM_IsoTP_Types
 *  @{ */

/** @brief to hold the static data of the object */
struct IsoTp_ObjectConfig
{
  /** @brief to know the rx PDU name */
  VAR(IsoTP_RxPduIdType, AUTOMATIC) rxPduName;
  /** @brief to know the tx PDU name */
  VAR(IsoTP_TxPduIdType, AUTOMATIC) txPduName;
  /** @brief to hold the config to use
   *  @details the config defines timing and flow control */
  P2CONST(IsoTP_ConfigType, AUTOMATIC, AUTOMATIC) ptr2Config;
  /** hold the connection to the communication controller interface
   *  @todo we should move this to Reference style */
  P2VAR(ComIf, AUTOMATIC, AUTOMATIC) p2ControllerInterface;
  /** we will link to a UDS object
   *  @todo we should move this to Reference style */
  P2VAR(UnifiedDiagnosticService, AUTOMATIC, AUTOMATIC) p2PduReceiver;
};
/**
 *
 * @brief to control the flow
 */
typedef struct
{
  /** extends the state machine */
  VAR(IsoTP_RxTxStatus, AUTOMATIC) ProtocolStatus;
  /** result */
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
  /** Block ssize timer */
  VAR(uint32_t, AUTOMATIC) bsTimer;
  /** segmentation timeout timer */
  VAR(uint32_t, AUTOMATIC) stTimer;
  /** timer for consecutive receive timeout */
  VAR(uint32_t, AUTOMATIC) crTimer;
  /** @brief to know the rx PDU name used by the ComIf*/
  VAR(ComStack_PduType, AUTOMATIC) rxIfPduName;
  /** @brief to know the tx PDU name used by the ComIf */
  VAR(ComStack_PduType, AUTOMATIC) txIfPduName;
}IsoTP_ControlType;

/** struct to hold a const size number and a pointer to writable memory */
typedef struct
{
  /** received number of bytes */
  VAR(uint32_t, AUTOMATIC) DataReceivedSize;
  /** to know the remaining number of bytes of the linked buffer */
  VAR(uint32_t,AUTOMATIC) RemainingBufferSize;
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
    : public TME_VersionInfo,
      public CanIfUpperLayer
{

public:
  /** Standard constructor */
  IsoTp();
  /** @brief constructor with connection to a communication controller interface */
  IsoTp(CONST(IsoTp_ObjectConfig, AUTOMATIC) initConfig);
  /** Standard destructor */
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
  FUNC(IsoTP_RxPduIdType, AUTOMATIC) GetRxPduName(void);

  /** @brief Get the name of the linked rx PDU
   *  @todo we should add a virtual function to the CanIfUpperLayer class */
  FUNC(IsoTP_TxPduIdType, AUTOMATIC) GetTxPduName(void);

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
   *  @param[in] ref2Pdu  reference to the data unit */
  FUNC(Std_ReturnType, AUTOMATIC) RxIndication(
      CONST(ComStack_PduType, AUTOMATIC) rxPduId,
      REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2Pdu);
  /** @brief service ID of IsoTP::RxIndication() */
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
  /** @brief service ID of IsoTP::InitHandle() */
#define TM_ISOTP_INITHANDLE_ID          (0x5401)

  /* #### send functions #### */

  /** @brief the flow controll message will be send */
  FUNC(Std_ReturnType, AUTOMATIC) SendFlowControl( CONST(IsoTP_FlowStatus, AUTOMATIC ) FlowStatus );
  /** @brief service ID of IsoTP::SendFlowControl() */
#define TM_ISOTP_SEND_FLOWCONTROL_ID      (0x5410)

  /** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
  FUNC(Std_ReturnType, AUTOMATIC) SendSingleFrame( void );
  /** @brief service ID of IsoTP::SendSingleFrame() */
#define TM_ISOTP_SEND_SINGLEFRAME_ID      (0x5411)

  /** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
  FUNC(Std_ReturnType, AUTOMATIC) SendFirstFrame( void );
  /** @brief service ID of IsoTP::SendFirstFrame() */
#define TM_ISOTP_SEND_FIRSTFRAME_ID      (0x5412)

  /** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
  FUNC(Std_ReturnType, AUTOMATIC) SendConsecutiveFrame( void );
  /** @brief service ID of IsoTP::SendConsecutiveFrame() */
#define TM_ISOTP_SEND_CONSECUTIVE_ID      (0x5413)

  /* #### receive functions #### */

  /** @brief do the work on a flow control message
   *  @param[in] rxPduId  naming the incoming message
   *  @param[in] ref2Pdu  reference to the data unit (this is the full CAN data including the protocol information) */
  FUNC(Std_ReturnType, AUTOMATIC) ReceiveFlowControl(
      CONST(IsoTP_RxPduIdType, AUTOMATIC) rxPduId,
      REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2Pdu);
  /** @brief service ID of IsoTP::ReceiveFlowControl() */
#define TM_ISOTP_RECEIVE_FLOWCONTROL_ID      (0x5420)

  /** @brief do the extended work on a received single frame message
   *
   *  This is to call the PDU router in the AUTOSAR style
   *  @param[in] rxPduId  naming the incoming message
   *  @param[in] ref2Pdu  reference to the data unit (this is the full CAN data including the protocol information) */
  FUNC(Std_ReturnType, AUTOMATIC) ReceiveSingleFrame(
      CONST(IsoTP_RxPduIdType, AUTOMATIC) rxPduId,
      REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2Pdu);
  /** @brief service ID of IsoTP::ReceiveSingleFrame() */
#define TM_ISOTP_RECEIVE_SINGLEFRAME_ID      (0x5421)

  /** @brief do the work on a received first frame message
   *  @param[in] rxPduId  naming the incoming message
   *  @param[in] ref2Pdu  reference to the data unit (this is the full CAN data including the protocol information) */
  FUNC(Std_ReturnType, AUTOMATIC) ReceiveFirstFrame(
      CONST(IsoTP_RxPduIdType, AUTOMATIC) rxPduId,
      REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2Pdu);
  /** @brief service ID of IsoTP::ReceiveFirstFrame() */
#define TM_ISOTP_RECEIVE_FIRSTFRAME      (0x5422)

  /** @brief do the work on a received consecutive frame message
   *  @param[in] rxPduId  naming the incoming message
   *  @param[in] ref2Pdu  reference to the data unit (this is the full CAN data including the protocol information) */
  FUNC(Std_ReturnType, AUTOMATIC) ReceiveConsecutiveFrame(
      CONST(IsoTP_RxPduIdType, AUTOMATIC) rxPduId,
      REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2Pdu);
  /** @brief service ID of IsoTP::ReceiveConsecutiveFrame() */
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
  CONST(IsoTp_ObjectConfig, AUTOMATIC) objectConfig = { .rxPduName = IsoTP_RxPduIdType::IsoTP_Rx_unknownPdu,
                                                        .txPduName = IsoTP_TxPduIdType::IsoTP_Tx_unknownPdu,
                                                        .ptr2Config = &IsoTP_DefaultConfig,
                                                        .p2ControllerInterface = NULL_PTR,
                                                        .p2PduReceiver = NULL_PTR,
                                                      };
};
/** @} */ // end of TM_IsoTP grouping

#endif /* TMANIACENGINEERING_COMMON_ISOTP_H_ */

/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanFT2p0.h

 * @author TManiac
 * @date 14.08.2022
 * @version 
 *
 */
#ifndef TMANIACENGINEERING__FUELTECH_FTCAN2P0_H_
#define TMANIACENGINEERING__FUELTECH_FTCAN2P0_H_

/** @addtogroup CanFT2p0_group
 * @{
 * TM_CanFT2p0TL.h */
 /** includes only documentation : */
#include <CanFT2p0_Cfg.h>
#include <CanFT2p0_Doxy.h>
#include <CanFT2p0_FixedNames.h>
#include "TMEVersionInfo.h"
#include "CanIfUpperLayer.h"

#include "CanIf.h"

/** @brief  my ID */
#define CANFT2P0_VENDOR_ID           TM_VENDOR_ID
/** @brief  module id to see where the error is come from */
#define CANFT2P0_MODULE_ID           (0xF1)
/** @brief we have only one version at start */
#define CANFT2P0_VERSION             (0x01)
/** @brief no patching until now */
#define CANFT2P0_PATCH_VERSION       (0x01)

/** @} */ // end of CanFT2p0 grouping

/* ===================== Development Error Tracer (DET)  ========== */

#if ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
/** @addtogroup TM_DET_NAMES
 *  @{ */
/** @defgroup TM_DET_CANFT2P0_NAMES Dev. Errors from CAN FT2.0 */
/** @defgroup TM_DEM_CANFT2P0_NAMES Runtime Errors from CAN FT2.0 */
/** @} */ // end of grouping TM_DET_NAMES

//#include "DevErrorTraver.h"

/** @addtogroup TM_DET_CANFT2P0_NAMES
 *  @{ */

/** @brief Development errors known by the CanFT2P0 module */
enum class CanFT2P0_DevError
{
  /** @brief API service called with invalid config
   *  @details When CanFT2p0_Transmit is called for a none configured PDU identifier
   *           or with an identifier for a received PDU.*/
  E_PARAM_CONFIG = 0x01,
  /** @brief API service called with invalid Pdu ID
   *  @details When CanFT2p0_Transmit is called for a none configured PDU identifier
   *           or with an identifier for a received PDU. */
  E_PARAM_ID  = 0x02,
  /** @brief API service called with NULL pointer
   *  @details  In case of this error, the API service shall return immediately
   *            without any further action, besides reporting this development error. */
  E_PARAM_POINTER  = 0x03,
  /** @brief Module initialization has failed */
  E_INIT_FAILED = 0x04,
  /** @brief API service used without initialization
   *  @details On any API call except CanFT2p0_Init(), CanFT2p0_GetVersionInfo()
   *           and CanFT2p0_MainFunction() if CanFT2p0 is in state CANFT_OFF */
  E_UNINIT = 0x20,
  /** @brief Invalid Transmit Pdu Id used */
  E_INVALID_TX_ID = 0x30,
  /** @brief Invalid Receive Pdu Id used */
  E_INVALID_RX_ID = 0x40

};
/** @} */ // end of grouping TM_DET_CANFT2P0_NAMES

/** @addtogroup TM_DET_REPORT
 *  @{ */
/** @brief Macro to report dev errors from CAN FT2.0 transport layer module
 *  @details We use an expansion macro for development error reporting */
  #define CANFT2P0_DET_REPORTERROR(ErrorId, ApiId) Det_ReportError(CANFT2P0_MODULE_ID, 0, (ApiId), (ErrorId))
/** @} */ // end of grouping TM_DET_REPORT

#endif // ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )

/* ==================End Development Error Tracer (DET)  ==========*/

/** @addtogroup CanFT2p0_Types
 *   @{ */

/** @brief use some event flags
 * @sa CanIsoTP_Link
 */
#define CANFT2P0_RXINDICATION  (0x1)
#define CANFT2P0_RXDATACOPY    ((0x1) << 16 )
#define CANFT2P0_TXINDICATION  ((0x1) << 1  )

/** @defgroup CanFT2p0_ID_Types Handling of CAN IDs as Spec-defined Ids */
/** @} */ // end of grouping CanFT2p0_Types

/** @addtogroup CanFT2p0_ID_Types
 *  @todo we should change this defines to a union struct handling
 *   @{ */
/** @brief macro to read the message Id from CAN ID */
#define CANFT2P0_GET_MESSAGE_ID(CanId) (CanId & 0x3FF)

/** @brief macro to read the package type from CAN ID */
#define CANFT2P0_GET_PACKAGE_TYPE(CanId)  ((CanId >> 11) & 0x3)

/** @brief macro to read the product id from CAN ID */
#define CANFT2P0_GET_PRODUCT_ID(CanId)  ((CanId >> 14) & 0x7FFF)

/** @brief to set the ProductTypeId in the CanId */
#define CANFT_PRODUCT_TYPE_ID(ProductTypeId)  ( (ProductTypeId & 0x3FF ) << 19)

/** @brief to mask the ProductTypeId in the CanId */
#define CANFT_PRODUCT_TYPE_MASK  ( 0x3FF << 19)

/** @brief to set the ProductUniqueId in the CanId */
#define CANFT_PRODUCT_UNIQUE_ID(ProductUniqueId)  ( (ProductUniqueId & 0x1F ) << 14)

/** @brief to mask the ProductUniqueId in the CanId */
#define CANFT_PRODUCT_UNIQUE_MASK  ( 0x1F << 14)

/** @brief to set the DataFieldId in the CanId
 *  @details you can use the CanFt2p0T_PackageType */
#define CANFT_DATAFIELD(DataField)   ( (DataField & 0x7) << 11 )

/** @brief to set the MessageId in the CanId */
#define CANFT_MESSAGE_ID(MessageId)    (MessageId & 0x03FF)
/** @} */ // end of grouping CanFT2p0_ID_Types

/** @addtogroup CanFT2p0_Types
 *  @{ */
#define CANFT_SW_BUTTON_RED(Data)   (( (Data) &0x0100)>>8)
#define CANFT_SW_BUTTON_GREEN(Data)   (( (Data) &0x0010)>>4)
#define CANFT_SW_BUTTON_BLUE(Data)   ( (Data) &0x0001)

/* USER CODE BEGIN CanFT2p0_Defines 0 */

/* USER CODE END CanFT2p0_Defines 0 */


/**
States type to handle behavior.
*/
enum class CanFT2p0_StatesType
{
  /** CAN TP module isn't initialized */
  CANFT_OFF,
  /** CAN TP module is initialized */
  CANFT_ON,
  /** CAN TP module is ready to work as rx object*/
  CANFT_RX_ON,
  /** CAN TP module is ready to work as tx object*/
  CANFT_TX_ON,
  /** CAN TP module is ready to work as cross (rx/tx) object*/
  CANFT_RXTX_ON
};

/* USER CODE BEGIN CanFT2p0_Enums 0 */

/* USER CODE END CanFT2p0_Enums 0 */

typedef uint16_t CanFT2p_MeasureValueType;

/** @brief to have a good way to handle the button states and color states */
typedef struct
{
  /* byte 2 or 4 or 6 */
  uint8_t   ButtonState_1:1;
  uint8_t   ButtonState_2:1;
  uint8_t   ButtonState_3:1;
  uint8_t   ButtonState_4:1;
  uint8_t   ButtonState_unused:4;
  /* byte 3 or 5 or 7 */
  uint8_t   ButtonState_5:1;
  uint8_t   ButtonState_6:1;
  uint8_t   ButtonState_7:1;
  uint8_t   ButtonState_8:1;
  uint8_t   ButtonState_unused_:4;
  CanFT2p0_MeasureID MeasureId;
}CanFT2p0_ButtonStateType;

/** @brief to dim or switch the button lightning */
typedef struct
{
  /* byte 0  */
  uint8_t   Diming_Row_1:7;
  uint8_t   State_Row_1:1;
  /* byte 1 */
  uint8_t   Diming_Row_2:7;
  uint8_t   State_Row_2:1;
  CanFT2p0_MeasureID MeasureId;
}CanFT2p0_ButtonCtrlType;
typedef struct
{
  uint32_t Content;
}CanFT20p_ContentType;

typedef struct
{
  CanFT2p_MeasureValueType MeasureValue;
  CanFT2p0_MeasureID MeasureId;
}CanFT2p0_MeasureType;

typedef struct
{
  uint8_t ptr[4];
}CanFT2p0_DataArrayType;

typedef struct
{
  union {
    CanFT20p_ContentType      common;
    CanFT2p0_MeasureType      measure;
    CanFT2p0_ButtonStateType  buttons;
    CanFT2p0_ButtonCtrlType   buttonsCtrl;
    CanFT2p0_DataArrayType    data_array;
  } as;
}CanFT2p0_DataHdlType;

/** @brief we use a simple data type who knows his name */
typedef struct
{
  /** @brief know the type of data for remaping or recalculation */
  VAR(CanFT2p0_DataName, AUTOMATIC) DataName;
  /** @brief The MeasureID extends the Base Id to the CAN Id*/
  VAR(uint32_t, AUTOMATIC) MeasureID;
  /** @brief the data */
  VAR(uint32_t, AUTOMATIC) DataValue;
}CanFT2p0_DataType;

typedef struct
{
  uint32_t MessageId:10;
  uint32_t ResponceBit:1;
  uint32_t DataFieldId:3;
  uint32_t UniqueId:5;
  uint32_t ProductTypeId:11;
  uint32_t unused:3;
}CanFT2p0_CanIdCodingType;

typedef struct
{
  union {
    uint32_t                  common;
    ComStack_CanIdType        interface;
    CanFT2p0_CanIdCodingType  elements;
  } as;

}CanFT2p0_CanIdType;

typedef struct
{
  VAR(uint16_t, AUTOMATIC) SizeOfStream;
  P2VAR(uint8_t, AUTOMATIC, AUTOMATIC)  ptr2Data;
}CanFT2p0_MailboxType;

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
  /// @brief we must known who we are
  VAR( CanFT2p0_NameType, AUTOMATIC) ObjectType;
  /// @brief to handle the init and tx or rx
  VAR(CanFT2p0_StatesType, AUTOMATIC) ObjectState;
  /// @brief To hold the fixed bits of the CAN Id
  VAR(CanFT2p0_CanIdType, AUTOMATIC) BaseId;
  /// @brief To add a counter to the UniqueID
  VAR(uint32_t, AUTOMATIC) UnifyId;
  /** @brief connection to the const configuration data */
  P2CONST(CanFT2p0_ObjectCfgType, AUTOMATIC, AUTOMATIC) ObjectCfgPtr;
  /** @brief connection to the const database info */
  P2CONST(CanFT2p0_DataBaseType, AUTOMATIC, AUTOMATIC) DB_CfgPtr;
  /// @brief Number of data values, it counts 32bit data elements
  VAR(uint32_t, AUTOMATIC) DataCount;
  /// @brief Number of data values
  VAR(uint32_t, AUTOMATIC) DataOffset;
  /// @brief pointer to the data of the object
  P2VAR(CanFT2p0_DataHdlType, AUTOMATIC, AUTOMATIC) Datas;

  VAR(CanFT2p0_MailboxType, AUTOMATIC) ptr2TxData;
  /// @brief if we get data feedback we must know the maximum amount
  VAR(uint32_t, AUTOMATIC) FeedbackDataCount;
  /// @brief pointer to the feedback data of the object
  P2VAR(CanFT2p0_DataType, AUTOMATIC, AUTOMATIC) FeedbackDatas;
  /// @brief Number of data values
  VAR(uint32_t, AUTOMATIC) VersionCount;
  /// @brief pointer to the data of the object
  P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) VersionDatas;
  /** @brief to hold the names of the rx PDUs of this object
   *  @details Die maximale Anzahl ist gerade genauso wie es überhaupt mögliche RX PDUs geben kann. */
 // VAR(CanFT_RxPduIdType, AUTOMATIC) rxPdu[CANFT_RXPDU_COUNT];
  /** @brief to hold the names of the tx PDUs of this object
   *  @details Die maximale Anzahl ist gerade genauso wie es überhaupt mögliche RX PDUs geben kann. */
//  VAR(CanFT_TxPduIdType, AUTOMATIC) txPdu[CANFT_TXPDU_COUNT];
  // wir brauchen:
  // RxPduList (ist über den CfgPtr eingehängt)
  // TxPduList (ist über den CfgPtr eingehängt)
  // Irgend etwas was die Daten beschreibt, auf das ich von außen zu greifen kann
}CanFT2p0_ObjectHdlType;

typedef struct
{
  /** @brief to handle the init */
  VAR(CanFT2p0_StatesType, AUTOMATIC) ModuleState;
  /** @brief Task tick */
  VAR(uint32_t, AUTOMATIC) TaskTicks;
  /** @brief count the active jobs */
  VAR(uint32_t, AUTOMATIC) ActiveJobs;
  /** @brief to hold the config to use */
  P2CONST(CanFT2p0_CfgType, AUTOMATIC, AUTOMATIC) ptr2Config;
}CanFT2p0_HandlingType;

/**
 * @brief Struct containing the data for linking an application to a CAN instance.
 * The data stored in this struct is used internally and may be used by software programs
 * using this library.
 */
typedef struct
{
  VAR(FT2p0_TxPduIdType, AUTOMATIC) txPdu;
  //TMhsQueue *RxQueue; @todo we should use a OS-Queue
  //TMhsEvent *Event;   @todo check of use the OS-Event
  uint32_t EventFlags;
  //TMhsThread *Thread;
  uint32_t TimeoutSet;
  uint32_t Flags;
  uint32_t TxId;
  uint32_t RxId;
  uint8_t ExtAddress;
  uint8_t ExtRxAddress;
  uint8_t TxPadContent;
  P2VAR(CanFT2p0_MailboxType, AUTOMATIC, AUTOMATIC) ptr2StreamBuffer;
}CanFT2p0_TxPduType;

/**
 * @brief Struct containing the data for linking an application to a CAN instance.
 * The data stored in this struct is used internally and may be used by software programs
 * using this library.
 */
typedef struct
{
  VAR(FT2p0_RxPduIdType, AUTOMATIC) rxPdu;
  //TMhsQueue *RxQueue; @todo we should use a OS-Queue
  //TMhsEvent *Event;   @todo check of use the OS-Event
  uint32_t EventFlags;
  //TMhsThread *Thread;

  uint8_t RxIndicationCounter;
  uint16_t RxMaxCounter;
  uint16_t ByteCounter;
  P2VAR(ComStack_CanMessageType, AUTOMATIC, AUTOMATIC)    ptr2Message;
  P2VAR(CanFT2p0_MailboxType, AUTOMATIC, AUTOMATIC) ptr2StreamBuffer;
}CanFT2p0_RxPduType;

/* USER CODE BEGIN CanFT2p0_Types 0 */

/* USER CODE END CanFT2p0_Types 0 */

/** @} */ // end of grouping CanFT2p0_Types

/** @addtogroup CanFT2p0_group
 * @{
 * TM_CanFT2p0.h */

/**
 *  @brief a class to handle the Fueltech CAN FT2.0 protocol */
class CanFT2p0
    : TME_VersionInfo,
      public CanIfUpperLayer
{

public:
  CanFT2p0();
  /** @brief constructor to connect to communication controller interface */
  CanFT2p0(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface);
  /** @brief constructor to connect to communication controller interface and naming the PDUs */
  CanFT2p0(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface, CONST(CanIf_RxPduIdType, AUTOMATIC) rxPduName);
  virtual ~CanFT2p0();

  /** @brief to get the module state */
  FUNC(CanFT2p0_StatesType, AUTOMATIC) GetState( void ) { return Handle.ModuleState; };

  /**
  This function initializes the object according the background configuration.

  @sa CANFT2P0_INIT_ID
  @param[in]  ptr2Config   Name the Type we want to be
  @return Std_ReturnType   success or failed init

  @version 02.2021
  */
  FUNC(Std_ReturnType, AUTOMATIC) Init( P2CONST(CanFT2p0_CfgType, AUTOMATIC, AUTOMATIC) ptr2Config = nullptr);
  /** @brief service ID of CanFT2p0::Init() */
  #define CANFT2P0_INIT_ID          (0x01)

  /** @brief get the handle to the connected communication controller interface */
  FUNC( CanIf*, AUTOMATIC) GetHwInterface(void);

  /** @brief Get the name of the linked rx PDU
   *  @todo we should add a virtual function to the CanIfUpperLayer class */
  FUNC( CanIf_RxPduIdType, AUTOMATIC ) GetRxPduName(void) { return rxPduName; } ;

  /** @brief overwrite the function prototype supported by the CanIfUpperLayer class
   *
   *  @param[in] rxPduId  naming the incoming message
   *  @param[in] ptr2Sdu  pointer to the data unit */
  FUNC(Std_ReturnType, AUTOMATIC) RxIndication(
      CONST(ComStack_PduType, AUTOMATIC) rxPduId,
      P2VAR(ComStack_CanMessageType, AUTOMATIC, AUTOMATIC) ptr2Sdu);


  /** @brief overwrite the function prototype supported by the CanIfUpperLayer class
   *
*/
  FUNC(Std_ReturnType, AUTOMATIC) TxIndication(
      //CONST(ComStack_PduType, AUTOMATIC) txPduId,
      CONST(CanIf_TxPduIdType, AUTOMATIC) txPduId,
      P2CONST(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) p2TxPdu );



private:
  /** @brief byte wise copy
   *  @details
   *  the size of the destination array must be the same as it be on the source array */
  FUNC(Std_ReturnType, AUTOMATIC) DataCopy(
      CONST(uint8_t, AUTOMATIC) DataLength,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) DestPtr,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) SourcePtr);
  /** @brief byte wise copy in reversed order
   *  @details
   *  the size of the destination array must be the same as it be on the source array <br>
   *  The first byte of the source will be the last byte of the destination */
  FUNC(Std_ReturnType, AUTOMATIC) DataReverseCopy(
      CONST(uint8_t, AUTOMATIC) DataLength,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) DestPtr,
      P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) SourcePtr);


  VAR(CanFT2p0_HandlingType, AUTOMATIC) Handle;
  VAR(CanFT2p0_ObjectHdlType, AUTOMATIC) ObjectHandle[CANFT_OBJECT_COUNT];
  VAR(CanFT2p0_RxPduType, AUTOMATIC) RxPduInfo[FT2P0_RXPDU_COUNT];
  VAR(CanFT2p0_TxPduType, AUTOMATIC) TxPduInfo[FT2P0_TXPDU_COUNT];

  P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanIf  = nullptr;
  CONST(CanIf_RxPduIdType, AUTOMATIC) rxPduName = CanIf_RxPduIdType::CanIf_Rx_unknownPdu;
};

/** @} */ // end of CanFT2p0 grouping

#endif /* TMANIACENGINEERING__FUELTECH_FTCAN2P0_H_ */

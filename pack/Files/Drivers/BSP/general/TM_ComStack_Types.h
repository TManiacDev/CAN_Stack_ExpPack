/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * TM_ComStack_Types.h

 * @author TManiac
 * @date 19.08.2022
 * @version 
 *
 */
#ifndef _TM_COMSTACK_TYPES_H_
#define _TM_COMSTACK_TYPES_H_

#include "TM_Std_Types.h"

/** the unified type to use PduNames as numbers */
typedef uint32_t ComStack_PduType;

/** @brief generic value for a invalid PDU name */
#define ComStack_InvalidPdu   0xFCCFFCCF

/** @brief to see it is a HAL name */
typedef CAN_TxHeaderTypeDef STM_HAL_TxHeaderTypeDef;

/** @brief to see it is a HAL name */
typedef CAN_RxHeaderTypeDef STM_HAL_RxHeaderTypeDef;

/** @brief to use the 32bit for extended CAN Id */
struct ComStack_CanIdType
{
  /** @brief extended Id */
  uint32_t Id29bit:29;
  /** @brief unused bits */
  uint32_t unused:1;
  /** @brief Remote transmission request */
  uint32_t RTR:1;
  /** @brief identifier extension */
  uint32_t IDE:1;

  /** the  operator is used only inside the CanIf */
  friend bool operator==(const ComStack_CanIdType& lCanId, const ComStack_CanIdType& rCanId )
  {
    if ( (lCanId.RTR == rCanId.RTR ) &&
         (lCanId.IDE == rCanId.IDE ) &&
         (lCanId.Id29bit == rCanId.Id29bit) )
      return true;
    else return false;
  };
};

/** @brief upper layer can use a smaller CAN message header */
typedef struct
{
  /// @brief The one and only CanId
  ComStack_CanIdType    CanId;
  uint32_t    DLC;      /*!< Specifies the length of the frame that will be transmitted.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 8. */
  uint32_t    Timestamp; /*!< Specifies the timestamp counter value captured on start of frame reception.
                          @note: Time Triggered Communication Mode must be enabled.
                          This parameter must be a number between Min_Data = 0 and Max_Data = 0xFFFF. */
  /** @brief identifies the HW filter which opens for the message */
  uint32_t FilterMatchIndex;

}ComStack_CanMsgHeader;

/** @brief this is a test structure to hold data and header for a rx message
 *  @details because of the filtermatch element inside the rx header we need two different buffer types :-( */
typedef struct
{
  /** @brief The header of the CAN message
   *  @details this is the public header used by inside my implementation */
  VAR(ComStack_CanMsgHeader, AUTOMATIC)       CanMsgHeader;
  /** @brief CAN has 8 data bytes. */
  P2CONST(uint8_t, AUTOMATIC, AUTOMATIC)               ptr2Data;
}ComStack_CanMessageType;

/** @brief The length type for PDU Data */
typedef uint32_t   PduLengthType;

/** @brief The type to handle PDUs on the ComStack
 *  @details this is the pure PDU type that holds the pointer to the data array. <br>
 *           The data array may be casted to a usable type */
typedef struct
{
  /** CanIf can handle only byte like data */
  P2VAR(uint8_t,AUTOMATIC,AUTOSAR_COMSTACKDATA) SduDataPtr;
  /** count of the data bytes.
   *
   *  This will be max 8 on normal CAN and 64 on CAN-FD */
  PduLengthType SduLength;
}ComStack_PduInfoType;
#endif /* _TM_COMSTACK_TYPES_H_ */

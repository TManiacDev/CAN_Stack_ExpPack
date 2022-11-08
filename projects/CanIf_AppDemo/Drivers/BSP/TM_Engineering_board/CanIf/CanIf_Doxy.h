/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanIf_Doxy.h

 * @author TManiac
 * @date 03.04.2022
 * @version 
 *
 */
#ifndef _CANIF_DOXY_H_
#define _CANIF_DOXY_H_

/*
 * das hier ist das Link Layer
 * also nutzen wir die L-PDU Namen
 *
 * --------
 * I-PDU Interaction Layer PDU for Communication Services Layer
 * L-PDU Data Link Layer PDU for Communication Abstraction and Micro controller Abstraction Layer
 * N-PDU Network Layer PDU for Transport Protocol
 *
 * PDU Protocol Data Unit
 * SDU Service Data Unit -> Payload of the PDU
 */

/***************************************/
/******** Development Error Module **********/
/** @defgroup TM_DET Development Error Manager
 *  @brief to handle errors during development
 *  */
/** @addtogroup TM_DET
 *  @{ */
/** @defgroup TM_DET_NAMES Naming of DET Errors */
/** @defgroup TM_DET_REPORT Report function macros for the modules */
/** @} */ // end of grouping TM_DET

/***************************************/
/******** CAN Hardware Module **********/
/** @defgroup TM_Can CAN Module
 *  @brief to work with the STM HAL
 *  */

/** @addtogroup TM_Can
 *  @{ */
/** @defgroup TM_CanCfg Configuration for CAN Hardware Module
 *  @brief  configuration for hardware dependencies */
/** @defgroup TM_Can_Types Type definitions for CAN Module
 *  @brief to handle hardware module access */
/** @} */ // end of grouping TM_CAN
/********* CAN Module Config **************/
/** @addtogroup TM_CanCfg
 *  @{ */
/** @defgroup TM_CanCfg_General general behavior */
/** @defgroup TM_CanCfg_ConfigSet Hardware configuration container */

/** @} */ // end of grouping TM_CanCfg

/** @addtogroup TM_CanCfg_ConfigSet
 *  @brief  Collection of the configuration parameters of hardware relevant elements.<br>
 *            Access via pointer
 * @{ */
/** @defgroup TM_CanCfg_ParaCfg  the parameter for the CAN hardware configuration
 *  @brief This container contains configuration parameters of the CAN controller(s) that will be needed at start */
/** @defgroup TM_CanCfg_BaudCfg Baudrate configuration
 *  @brief This container contains bit timing related configuration parameters of the CAN controller(s) */
/** @defgroup TM_CanCfg_HwFilter Hardware Rx Filter configuration
 *  @brief This container contains configuration parameters for the hardware filter */
/** @} */ // end of grouping TM_CanCfg_ConfigSet

/******************************************/


/***************************************/
/******** CAN Interface Module *********/
/** @defgroup TM_CanIf_Main CAN Interface Module
 *  @brief Interfacing dependencies
 *  */

/** @addtogroup TM_CanIf_Main
 *  @{ */
     /** @defgroup TM_CanIfCfg Configuration for CAN Interface Module
      *  @brief    configuration to connect hardware to upper layers */

    /** @defgroup TM_CanIf_Types API type definitions for CAN Interface Module
     *  @brief    Extended variable types used on the API */

    /** @defgroup TM_CanIf_Func API function definitions for CAN Interface Module
     *  @brief    Functions used in the API */
    /** @defgroup TM_CanIf_InternFunc Functions that will not be on public interface
     *  @brief    Internal functions not public */
/** @} */ // end of grouping TM_CanIf_Main

/**** CAN Interface Module Config ********/

/** @addtogroup TM_CanIfCfg
 *  @details
 *  This Configuration describes the parameters like AUTOSAR.
 *  Not all are used.
 *  @{ */
    /** @defgroup TM_CanIf_InitCfg Configuration to handle communication messages */
    /** @defgroup TM_CanIf_PrivateCfg Configuration of internal behavior (only as sketch)*/
    /** @defgroup TM_CanIf_PublicCfg Configuration on network wide level (only as sketch) */
    /** @defgroup TM_CanIf_TrcvCfg Transceiver handling (only as sketch) */
    /** @defgroup TM_CanIf_DrvCfg  Configuration for extern driver (only as sketch) */
    /** @defgroup TM_CanIf_DispatchCfg Callback functions for driver and transceiver (only as sketch) */
/** @} */ // end of grouping TMCanIfCfg

/** @addtogroup TM_CanIf_InitCfg
 *  @details
 *  - InitCfgSet (enum name the Init)
 *  - MaxBufferSize (int)
 *  - MaxRxPduCfg (int) -> maximum number of Rx Pdu
 *  - MaxTxPduCfg (int) -> maximum number of Tx Pdu
 *  @{ */
    /**  @defgroup TM_CanIf_BufferCfg Buffer configuration */
    /**  @defgroup TM_CanIf_InitHohCfg references to the hardware/driver */
    /**  @defgroup TM_CanIf_RxPduCfg PDU configuration for receiving */
    /**  @defgroup TM_CanIf_TxPduCfg PDU configuration for transmit */
/** @} */ // end of grouping TM_CanIf_InitCfg

/** @addtogroup TM_CanIf_PrivateCfg
 *  @details
 *  - FixedBuffer (bool)
 *  - DataLengthCheck (bool)
 *  - SoftwareFilterType (Binary/Index)Linear/Table)
 *  - TTCan Support (bool/Container)
 *  */

/** @addtogroup TM_CanIf_PublicCfg
 *  @details
 *  - BusMirroringSupport (bool)
 *  - DevErrorDetection (bool)
 *  - SecurityEventReporting (bool)
 *  - MetaDataSupport (bool) -> support of dynamic CAN Id handling, we need it for Fueltech FT2.0
 *  - CDD Support (link to headerfiles)
 *  - CAN Hardware Handle Type -> name the TYPE, not the Handle it self
 *  - MultipleDrvSupport (bool)
 *  - PartialNetworkSupport (bool)
 *  - ReadRxPduDataApi (bool)
 *  - ReadRxPduNotifyStatusApi (bool)
 *  - ReadTxPduNotifyStatusApi (bool)
 *  - SetDynamicTxIdApi (bool)
 *  - TxBuffering (bool)
 *  - TxConfirmPollingSupport (bool)
 *  - WakeupCheckValidByNM (bool)
 *  - WakeupCheckValidSupport (bool)
 *  - SetBaudrateApi (bool)
 *  - TriggerTransmitSupport (bool)
 *  - TxOfflineActiveSupport (bool)
 *  - VersionInfoApi (bool)
 *  - WakeupSupport (bool)
 *  - SecurityEventsRef (List)
 *  */

/** @addtogroup TM_CanIf_RxPduCfg
 *  @details
 *
 *  @section AUTOSAR_INFO  Needs on AUTOSAR
 *  - CAN Id
 *  - Id Mask
 *  - IdType (Ext/Ext_FD/Std/Std_FD)
 *  - DataLength (normal 0-8 / FD CAN 0-64)
 *  - DataLengthCheck (bool)
 *  - PduId (Enum) -> ECU wide unique, symbolic handle for receive CAN L-SDU. It shall fulfill ANSI/AUTOSAR definitions for constant defines.
 *  - ReadData (bool) -> Enables and disables the Rx buffering for reading of received L-SDU data.
 *  - ReadNotifyStatus (bool)
 *  - RxIndicationName (enum)
 *  - RxIndicationUL (enum: NM/TP_TSYN/CDD/J1939...)
 *  - HrhIdRef (Hardware handle name of CAN Module)
 *  - PduRef -> Reference to the "global" Pdu structure to allow harmonization of handle IDs in the COM-Stack.
 *  - CanIdRange (Container)
 *  - TTTxFrameTrigger (ref to container)
 *  @{ */

/** @} */ // end of grouping TM_CanIf_RxPduCfg

/** @addtogroup TM_CanIf_TxPduCfg
 *  @details
 *  - CAN Id (32bit)
 *  - Id Mask (32bit)
 *  - IdType (Ext/Ext_FD/Std/Std_FD)
 *  - PduId (Enum)
 *  - PartialNetworkFilter (bool)
 *  - ReadNotifyStatus (bool)
 *  - TriggerTransmit (bool)
 *  - Truncation (bool) -> Enables/disables truncation of PDUs that exceed the configured size
 *  - PduType (dynamic/static)
 *  - UserTriggerTransmitName (see SWS -> ECUC_CanIf_00842)
 *  - UserTxConfirmationName (see SWS ECUC_CanIf_00528)
 *  - UserTxConfirmationUL (enum: NM/TP_TSYN/CDD/J1939...)
 *  - @link TM_CanIf_BufferCfg BufferRef @endlink
 *  - TTTxFrameTrigger (ref to container)
 *  @{ */

/** @} */ // end of grouping TM_CanIf_TxPduCfg

/******************************************/


/***************************************/
/******** Unified interface OSI Layer 2 to Layer 3 *********/
/** @defgroup TM_OsiLayer3LowerInterface Unified interface OSI Layer 2 to Layer 3
 *  @brief Interfacing dependencies
 *  @details this interface will be used between TM_CanIf and its upper layer
 *  */
#endif /* _CANIF_DOXY_H_ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

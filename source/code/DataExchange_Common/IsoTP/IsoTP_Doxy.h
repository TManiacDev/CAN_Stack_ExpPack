/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * IsoTP_Doxy.h

 * @author TManiac
 * @date Apr 3, 2022
 * @version 
 *
 */
#ifndef _ISOTP_DOXY_H_
#define _ISOTP_DOXY_H_

/*
 * das hier ist das Network Layer
 * also nutzen wir die N-PDU Namen
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
/*********** ISO TP module **********/
/** @defgroup TM_IsoTP ISO Transport Protocol Transport Layer
 *  @brief configuration of the CAN ISO TP module
 *  @details
 *
 *  | Abkürzung | Beschreibung | Übersetzung |
 *  | --------- | ------------ | ----------- |
 *  | N_AI | Network Address Information (see ISO 15765-2) | - |
 *  | N_Ar | Time for transmission of the CAN frame (any N-PDU) on the receiver side (see ISO 15765-2) | - |
 *  | N_As | Time for transmission of the CAN frame (any N-PDU) on the sender side (seeISO 15765-2) | - |
 *  | N_Br | Time until transmission of the next flow control N-PDU (see ISO 15765-2) | - |
 *  | N_Bs | Time until reception of the next flow control N-PDU (see ISO 15765-2) | - |
 *  | N_Cr | Time until reception of the next consecutive frame N-PDU (see ISO 15765-2) | - |
 *  | N_Cs | Time until transmission of the next consecutive frame N-PDU (see ISO 15765-2) | - |
 *  | N_Data | Data information of the transport layer | - |
 *  | N_PCI | Protocol Control Information of the transport layer | - |
 *  | N_SA | Network Source Address (see ISO 15765-2) | - |
 *  | N_TA | Network Target Address (see ISO 15765-2). It might already contain the N_TAtype(physical/function) in case of ExtendedAddressing  | - |
 *  | N_TAtype | Network Target Address type (see ISO 15765-2)| - |
 *  |  @link abrev Standardabkürzungen @endlink |||
 *
 *  | N_PDU name                    | CAN<br>2.0 | CAN<br>FD | N_PCI bytes |||||||||
 *  | ----------                    | :----: | :----: | ----- | ----- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
 *  | Byte usage                    | ...... ......  || Byte #0      || Byte #1       | Byte #2       | Byte #3       | Byte #4       | Byte #5       | Byte #6       | Byte #7 ... |
 *  | Bit usage                     | ^      | ^      | 7 - 4 | 3 - 1 | ^             | ^             | ^             | ^             | ^             | ^             | ^ |
 *  | ++++++++++                    | ++++++++++     || +++++++++++++|| +++++++++++++ | +++++++++++++ | +++++++++++++ | +++++++++++++ | +++++++++++++ | +++++++++++++ | +++++++++++++ |
 *  | SingleFrame (SF)<br>DL <= 8   | yes | yes       | 0x0   | SF_DL | [unused/padding]      |||||||
 *  | SingleFrame (SF)<br>DL > 8    | no  | yes       | 0x00         || SF_DL         | [unused]      ||||||
 *  | FirstFrame (FF)<br>DL <= 4095 | yes | yes       | 0x1   | FF_DL                || [data]        | [data]      | [data]      | [data]      | [data]      | [data]      |
 *  | FirstFrame (FF)<br>DL >  4095 | yes | yes       | 0x1   | 0x000                || FF_DL         ||||| [data] |
 *  | ConsecutiveFrame (CF)         | yes | yes       | 0x2   | SN   | [data]         | [data]        | [data]      | [data]      | [data]      | [data]      | [data]      |
 *  | FlowControl (FC)              | yes | yes       | 0x3   | FS   | BS             | STmin         | [unused/padding] |||||
 */

/** @addtogroup TM_IsoTP
 * @{ */
    /** @defgroup TM_IsoTP_Cfg ISO TP configuration
     *  @brief This container holds the configuration of the ISO TP module */

    /** @defgroup TM_IsoTP_Types Type definitions for ISO TP Layer Module
     *  @brief there are no special public types then the configuration
     *         all types defined in the COM stack */

    /** @defgroup TM_IsoTP_CfgTypes Type definitions for configuration of the ISO TP Layer Module
     *  @brief This types hold the configuration parameters
     *         see also all types defined in the COM stack */

    /** @defgroup TM_IsoTP_Func Function definitions for CAN ISO TP Layer Module */

    /** @defgroup TM_IsoTP_Task Task definitions for CAN ISO TP Layer Module */
/** @} */ // end of grouping IsoTP

/** @addtogroup TM_IsoTP_Cfg
 *  @{ */
    /** @defgroup TM_IsoTP_CfgGeneral General configuration */
    /** @defgroup TM_IsoTP_Cfg_Config Parameter configuration */
/** @} */ // end of grouping TM_IsoTP_Cfg

/** @addtogroup TM_IsoTP_CfgGeneral
 *  - ChangeParameterApi (bool)
 *  - DevErrorDetect (bool)
 *  - DynIdSupport (bool)
 *  - GenericConnectionSupport (bool) -> Enable support for the handling of generic connections using N-SDUs with MetaData. Requires CanTpDynIdSupport.
 *  - PaddingByte (byte/uint8)
 *  - ReadParameterApi (bool)
 *  - VersionInfoApi (bool)
 *  - FlexibleDataRateSupport / CAN FD Support (bool)
 *  @{ */
/** @} */ // end of grouping TM_IsoTP_CfgGeneral

/** @addtogroup TM_IsoTP_Cfg_Config
 *  @details
 *  - MainFunctionPeriod (float in sec)
 *  - MaxChannelCount (int)
 *  - @link TM_IsoTP_Cfg_Channel ChannelConfig (Container) @endlink
 *  @{ */
    /** @defgroup TM_IsoTP_Cfg_Channel Channel configuration */
/** @} */ // end of grouping TM_IsoTP_Cfg_Config

/** @addtogroup TM_IsoTP_Cfg_Channel
 *  @details
 *  - @link TM_IsoTP_Cfg_RxNSdu RxNSdu (Container) @endlink
 *  - @link TM_IsoTP_Cfg_TxNSdu TxNSdu (container) @endlink
 *  @{ */
    /** @defgroup TM_IsoTP_Cfg_RxNSdu Rx Channel configuration */
    /** @defgroup TM_IsoTP_Cfg_TxNSdu Tx Channel configuration */
/** @} */ // end of grouping TM_CanIsoTP_Cfg_Channel

/** @addtogroup TM_IsoTP_Cfg_RxNSdu
 *  @details
 *  - Bs (uint8)
 *  - Nar (sec in float)
 *  - Nbr (sec in float)
 *  - Ncr (sec in float)
 *  - AddressingFormat (Std/Ext/Mixed/NormalFixed/Mixed29Bit)
 *  - NSduId (enum) -> for use with upper layer
 *  - PaddingActivation (bool)
 *  - TaType (functional/physical)
 *  - WftMax (int) ???
 *  - STmin (sec in float)
 *  - NSduRef (Ref to Pdu) -> Reference to a Pdu in the COM-Stack.
 *  - NAe (Container) -> optional one
 *  - NSa (Container) -> optional one
 *  - NTa (Container) -> optional one
 *  - RxNPdu (Container) -> must have one
 *  - TxFcNPdu (Container) -> optional one
 *
 *  RxNPdu:
 *  - PduId (symbolic name /enum)
 *  - PduRef (Ref to Pdu) -> Reference to a Pdu in the COM-Stack.
 *
 *  TxFcNPdu:
 *  - FcNPduConfirmationPduId (symbolic name /enum)
 *  - PduRef (Ref to Pdu) -> Reference to a Pdu in the COM-Stack.
 *  @{ */
/** @} */ // end of grouping TM_IsoTP_Cfg_RxNSdu

/** @addtogroup TM_IsoTP_Cfg_TxNSdu
 *  @{ */
/** @} */ // end of grouping TM_IsoTP_Cfg_TxNSdu

#endif /* _ISOTP_DOXY_H_ */

/*******************  (C) TManiac Engineering  *******************/
/*******************         END OF FILE       *******************/

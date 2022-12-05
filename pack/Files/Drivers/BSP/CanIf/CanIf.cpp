/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanIf.cpp

 * @author TManiac
 * @date 20.08.2022
 * @version 
 *
 */
#include <CanIf.h>
#include <vector>

#ifndef HAL_CAN_MODULE_ENABLED
/*
 * @todo
 * we need the STM HAL CAN module.
 * */
 #error "The CanIf needs the STM CAN HAL module"
#endif

/** @brief to access the configuration */
EXTERN_CONST( CanIf_RxPduCfgType, AUTOMATIC) MyTest_RxPduConfig[];
/** @brief to access the configuration */
EXTERN_CONST( CanIf_RxPduCfgType, AUTOMATIC) MyTest_TxPduConfig[];

/* mein Testobjekt zum CanDrv */
#include "CanDrv_bxCAN.h"
CanDrv_bxCAN myCanDrv_bxCan;

#define LINK_TO_CANDRV &myCanDrv_bxCan

/** the enum switching operator is used only inside the CanIf */
SYS_FUNC( TM_CANIF_CODE ) CanIfStates& operator++(CanIfStates& state)
{
  switch (state)
  {
    case CanIfStates::PreInit : return state= CanIfStates::HwInit;
    case CanIfStates::HwInit  : return state= CanIfStates::FilterInit;
    case CanIfStates::FilterInit  : return state= CanIfStates::Ready;
    case CanIfStates::Stopped  : return state= CanIfStates::Ready;
    case CanIfStates::Ready  : return state= CanIfStates::Ready;
    default: return state= CanIfStates::ErrorState;
  }
};
/** the enum switching operator is used only inside the CanIf */
SYS_FUNC( TM_CANIF_CODE ) CanIfStates& operator--(CanIfStates& state)
{
  switch (state)
  {
    case CanIfStates::FilterInit : return state= CanIfStates::HwInit;
    case CanIfStates::Ready  : return state= CanIfStates::FilterInit;
    case CanIfStates::HwInit  : return state= CanIfStates::HwInit;
    case CanIfStates::Stopped  : return state= CanIfStates::FilterInit;
    default: return state= CanIfStates::ErrorState;
  }
};


SYS_FUNC( TM_CANIF_CODE ) CanIf::CanIf()
    : TME_VersionInfo{CANIF_MODULE_ID, CANIF_VERSION, CANIF_PATCH_VERSION},
      ComIf{ComInterfaceType::CanIf},
      ptr2CanDriver{LINK_TO_CANDRV}
{
  // TODO Auto-generated constructor stub

  // we leave the constructor with increment the state machine
  ++state;
}

SYS_FUNC( TM_CANIF_CODE ) CanIf::~CanIf() {
  // TODO Auto-generated destructor stub

  // this should never be seen outside
  state = CanIfStates::ShutDown;
}


FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Init(void)
{
  Std_ReturnType returnValue = E_NOT_OK;

  if (state == CanIfStates::HwInit )
  {
    if ( ptr2CanDriver->Init(NULL_PTR, this) != E_OK )
    {
      CANIF_DET_REPORTERROR(CanIf_DevError::E_INIT_FAILED, CANIF_INIT_ID);
    }
    if ( ptr2CanDriver->SetControllerMode(CanMasterController, CanControllerStates::CS_Started) != E_OK )
    {
      CANIF_DET_REPORTERROR(CanIf_DevError::E_SETUP_FAILED, CANIF_INIT_ID);
    }
    ++state;
    returnValue = E_OK;
  }
  else
  {
    --state;
    returnValue = E_OK;
  }

  /*###############################################
   * init the real interface
   ################################################*/

#if ( CANIF_LOAD_STATIC_CONFIG == STD_ON )

  if ( returnValue == E_OK ) // CanDrv start was successful
  {
    returnValue = E_NOT_OK;
    // init the Tx-Path
/*  @warning the struct hasn't the same order like CanIf_TxPduIdType */
    for (ComStack_PduType InitPdu = 0; InitPdu < CanIf_Tx_unknownPdu; InitPdu++ )
    {
      if ( MyTest_TxPduConfig[InitPdu].CanId.IDE == CANIF_EXTID )
      {
        txHeaderList[InitPdu].ExtId = MyTest_TxPduConfig[InitPdu].CanId.Id29bit;
        txHeaderList[InitPdu].IDE = CAN_ID_EXT;
      }
      else
      {
        txHeaderList[InitPdu].StdId = MyTest_TxPduConfig[InitPdu].CanId.Id29bit;
        txHeaderList[InitPdu].IDE = CAN_ID_STD;
      }
      txHeaderList[InitPdu].DLC = MyTest_TxPduConfig[InitPdu].MsgLength;
      txHeaderList[InitPdu].RTR = MyTest_TxPduConfig[InitPdu].CanId.RTR;
    }

    // init rx path
    /*  @warning the struct hasn't the same order like CanIf_TxPduIdType */
    for (ComStack_PduType InitPdu = 0; InitPdu < CanIf_Rx_unknownPdu; InitPdu++ )
    {
      if ( MyTest_RxPduConfig[InitPdu].IdMask.Id29bit > 0x0 )
      {
        /** try to setup HW filter */
        if ( ptr2CanDriver->SetFilterByBitmask(
                                    MyTest_RxPduConfig[InitPdu].InstanceName,
                                    MyTest_RxPduConfig[InitPdu].CanId,
                                    MyTest_RxPduConfig[InitPdu].IdMask) >= 0 )
        {
          // do something on success
          // we should remember the filter number for work on RxIndication
        }
      }
      else
      {
        /** try to setup HW filter*/
        if ( ptr2CanDriver->SetFilterByCanId(
                                    MyTest_RxPduConfig[InitPdu].InstanceName,
                                    MyTest_RxPduConfig[InitPdu].CanId) >= 0 )
        {
          // do something on success
          // we should remember the filter number for work on RxIndication
        }
      }

      /// @todo MyTest_RxPduConfig[InitPdu].N_PDU_Name  -->> muss noch zu geordnet werden !!!
    }
  }

#endif // ( CANIF_LOAD_STATIC_CONFIG == STD_ON )
  return returnValue;
}

FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Start(void)
{
  Std_ReturnType returnValue = E_NOT_OK;

  ++state;
  if (state == CanIfStates::Ready )
  {
    returnValue = E_OK;
  }
  else
  {
    // we keep the old state if we aren't ready
    --state;
    // so we return to state before increment above
  }

  return returnValue;
}

FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Transmit(
    CONST(ComStack_PduType,AUTOMATIC) txPduId,
    P2CONST(ComStack_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo)
{
  return Transmit((CanIf_TxPduIdType) txPduId, (CanIf_PduInfoType*) ptr2PduInfo);
}

/* Requests transmission of a CAN message via message header and data array */
FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Transmit(
    VAR(ComStack_CanMsgHeader, AUTOMATIC) msgHeader,
    P2CONST(uint8_t, AUTOMATIC, AUTOMATIC) ptr2Data)
{
  Std_ReturnType returnValue = E_NOT_OK;

  if (state == CanIfStates::Ready )
  {
    ComStack_CanMessageType CanMsg{msgHeader, ptr2Data};
    returnValue = ptr2CanDriver->Write(CanMasterController, &CanMsg);
  }
  return returnValue;
}
/* Requests transmission of a CAN message with PDU info. */
FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Transmit(
    CONST(CanIf_TxPduIdType,AUTOMATIC) txPduId,
    P2CONST(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo)
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint8_t* ptr2Data = ptr2PduInfo->SduDataPtr;

  if ( txPduId < CanIf_Tx_unknownPdu )
  {
    if (state == CanIfStates::Ready )
    {
      ComStack_CanMessageType CanMsg;
      CanMsg.CanMsgHeader.CanId = MyTest_TxPduConfig[txPduId].CanId;
      CanMsg.CanMsgHeader.DLC = ptr2PduInfo->SduLength;
      CanMsg.ptr2Data = ptr2Data;
      returnValue = ptr2CanDriver->Write(CanMasterController, &CanMsg);
    }
  }
  return returnValue;
}

/* The service CanIf_RxIndication() is implemented in CanIf and called by CanDrv after a CAN L-PDU has been received. */
FUNC(void, TM_CANIF_CODE) CanIf::RxIndication(
    CONST( ECU_CanController, AUTOMATIC) Controller,
    REF2CONST( ComStack_CanMsgHeader, AUTOMATIC) CanMsgHeader,
    REF2CONST( ComStack_PduInfoType, AUTOMATIC) PduInfo )
{
  uint32_t filterIndex = CanMsgHeader.FilterMatchIndex;
  /* On L-PDU reception, the Can module shall call the RX indication callback function CanIf_RxIndication
   * with ID, Hoh,
   * abstract CanIf ControllerId in parameter Mailbox,
   * and the Data Length and pointer to the L-SDU buffer in parameter PduInfoPtr.*/
  /* Ziel ist es dass die Filternummer unmittelbar die RxIndication Funktion des dazu gehörigen Empfängers aufruft */
  /* Implentation goal is this way: the filter number coming with the HAL_CAN_GetRxMessage inside the HAL_Header.FilterMatchIndex should be select the needed RxIndication function */

  if ( ( p2UpperLayerList[filterIndex] != nullptr ) )
  {
    p2UpperLayerList[filterIndex]->RxIndication(MyTest_RxPduConfig[filterIndex].N_PDU_Name, CanMsgHeader, PduInfo);
  }
}

FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Receive(
    CONST(ComStack_PduType,AUTOMATIC) rxPduId,
    P2VAR(ComStack_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo)
{
  return Receive( (CanIf_RxPduIdType) rxPduId, (CanIf_PduInfoType*) ptr2PduInfo);
}

/* read a received message from buffer via CAN message header */
/**  @todo this is a fix not save implementation */
FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Receive(
    REF2VAR(ComStack_CanMsgHeader, AUTOMATIC ) msgHeader,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2Data )
{
  Std_ReturnType returnValue = E_NOT_OK;

  /** @todo we need some work here -> CanIf::Receive(
    REF2VAR(ComStack_CanMsgHeader, AUTOMATIC ) msgHeader,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2Data )  */

  return returnValue;
}

/* read a received message from buffer via PDU naming */
/**  @todo this is a fix not save implementation */
FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Receive(
    CONST(CanIf_RxPduIdType,AUTOMATIC) rxPduId,
    P2VAR(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo)
{
  Std_ReturnType returnValue = E_NOT_OK;

  /** @todo we need some work here -> CanIf::Receive(
    CONST(CanIf_RxPduIdType,AUTOMATIC) rxPduId,
    P2VAR(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo)*/

  return returnValue;
}

/* to get the CanIf_RxPduIdType name */
FUNC(ComStack_PduType, TM_CANIF_CODE) CanIf::GetIfRxPduName(
    CONST(CanIf_UpperLayerType, AUTOMATIC) upperLayerName,
    CONST(ComStack_PduType, AUTOMATIC) rxPduId )
{
  ComStack_PduType ifRxPduId = ComStack_InvalidPdu;
  for (ComStack_PduType InitPdu = 0; InitPdu < CanIf_Rx_unknownPdu; InitPdu++ )
  {
    if ( (MyTest_RxPduConfig[InitPdu].N_PDU_Name == rxPduId ) && (MyTest_RxPduConfig[InitPdu].ULName == upperLayerName ) )
    {
      ifRxPduId = MyTest_RxPduConfig[InitPdu].L_PDU_Name;
    }
  }
  return ifRxPduId;
}

/* to get the CanIf_TxPduIdType name */
FUNC(ComStack_PduType, TM_CANIF_CODE) CanIf::GetIfTxPduName(
    CONST(CanIf_UpperLayerType, AUTOMATIC) upperLayerName,
    CONST(ComStack_PduType, AUTOMATIC) txPduId )
{
  ComStack_PduType ifTxPduId = ComStack_InvalidPdu;
  for (ComStack_PduType InitPdu = 0; InitPdu < CanIf_Tx_unknownPdu; InitPdu++ )
  {
    if ( (MyTest_TxPduConfig[InitPdu].N_PDU_Name == txPduId ) && (MyTest_TxPduConfig[InitPdu].ULName == upperLayerName ) )
    {
      ifTxPduId = MyTest_TxPduConfig[InitPdu].L_PDU_Name;
    }
  }
  return ifTxPduId;
}

FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::ConnectUpperLayerIndication(
    CONST(ComStack_PduType,AUTOMATIC) rxPduId,
    P2VAR(CanIfUpperLayer,AUTOMATIC,AUTOMATIC) p2UpperLayerObject)
{
  Std_ReturnType returnValue = E_NOT_OK;

  // maybe we should test the pointer
  // but a null-ptr is ok, because it will be used for disconnect the UpperLayerIndication
  if ( ( p2UpperLayerList[rxPduId] == NULL_PTR ) || ( p2UpperLayerObject == NULL_PTR ) )
  {
    p2UpperLayerList[rxPduId] = p2UpperLayerObject;
    returnValue = E_OK;
  }

  return returnValue;
}

/** @brief task function to push the tx message from software buffer to tx mailbox */
FUNC(void, TM_CANIF_CODE) CanIf::TxTask(void)
{
  if (state == CanIfStates::Ready )
  {
    ptr2CanDriver->TxTask();
  }
}


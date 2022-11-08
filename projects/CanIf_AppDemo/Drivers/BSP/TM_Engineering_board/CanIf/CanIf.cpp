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

/** @brief This is the configuration for the STM Nulceo144 board */
extern  const CanConfigType Can_NucleoConfig;

/* * @brief to use the generic name coming from the template */
extern CAN_HandleTypeDef* ptr2Can1Hdl;

/* * @brief to use the generic name coming from the template */
extern CAN_HandleTypeDef* ptr2Can2Hdl;

/** names of the CAN controller configurations
 *
 * @todo das sollte auch extern sein: extern const ECU_CanController controllerList[];*/
extern const std::vector<ECU_CanController> controllerList;
//const ECU_CanController controllerList[] = {ECU_CanController::CanMasterController,ECU_CanController::CanSlaveController};

/** @brief to access the configuration */
EXTERN_CONST( CanIf_RxPduCfgType, AUTOMATIC) MyTest_RxPduConfig[];
/** @brief to access the configuration */
EXTERN_CONST( CanIf_RxPduCfgType, AUTOMATIC) MyTest_TxPduConfig[];

/** @brief we want a Tx software buffer
 *
 *  we start with a fix size. Later it would be go to the IDE
 * @todo bring the buffers to save class */
static CAN_TxMessage     canTxBuffer[CANIF_TX_BUFFER_SIZE];

uint32_t testFilter = 3;

/** @brief we use a clean message */
CONST(CAN_TxMessage, AUTOMATIC)  cleanMessage =
{
    CanIf_TxMessage_free,
    {
        /* StdID = */ 0x0,
        /* ExtID = */ 0,
        /* IDE = */   CAN_ID_EXT,
        /* RTR = */   CAN_RTR_DATA,
        /* DLC = */   0,
        /* TT_CAN */  FunctionalState::DISABLE
    },
    0,
    { 0x00,0x00, 0xAF,0xFE, 0x00,0x00, 0x00,0x00}
};

/** @brief we want a Rx software buffer
 *
 *  we start with a fix size. Later it would be go to the IDE */
CanIf_MessageType     rxMsgBuffer[CANIF_RX_BUFFER_SIZE];

/** @brief the object to handle the RxBuffer
 *
 * @todo bring the buffers to save class */
CanIf_RxBufferType canRxBuffer =
{
    0,
    0,
    rxMsgBuffer
};


/** @brief this list will hold the pointer to the upper layers in same order like the rxHeaderList */
P2VAR(CanIfUpperLayer,AUTOMATIC,AUTOMATIC) p2UpperLayerList[CANIF_RXPDU_COUNT];

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


SYS_FUNC( TM_CANIF_CODE ) CanIf::CanIf() : TME_VersionInfo{CANIF_MODULE_ID, CANIF_VERSION, CANIF_PATCH_VERSION}, ComIf{ComInterfaceType::CanIf}
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
    /*###############################################
     * start the HAL hardware driver
     ################################################*/

      /*## -1- Configure the CAN peripheral #######################################*/
    //for ( C_ECU_CanController initController = C_CanMasterController ; initController < C_NBROF_CanController; ++initController )
    for (auto& initController : controllerList )
    {
      const CanControllerParaType * ptr2CanParaConfigSet = &Can_NucleoConfig.ptr2CanParaConfigSet[initController];
      const CanControllerBaudrateConfigType* ptr2BaudConfig = &Can_NucleoConfig.ptr2CanBaudrateConfigSet[ptr2CanParaConfigSet->InitBaudrate];

      if (ptr2CanParaConfigSet->InitBaudrate < CanBaudrate_unknown  )
      {
        bxCanHdl[initController].Instance                    = ptr2CanParaConfigSet->Instance;
        bxCanHdl[initController].Init.Mode                   = ptr2CanParaConfigSet->Mode;
        bxCanHdl[initController].Init.TimeTriggeredMode      = ptr2CanParaConfigSet->TTMode;
        bxCanHdl[initController].Init.AutoBusOff             = ptr2CanParaConfigSet->AutoBusOff;
        bxCanHdl[initController].Init.AutoWakeUp             = ptr2CanParaConfigSet->AutoWakeUp;
        bxCanHdl[initController].Init.AutoRetransmission     = ptr2CanParaConfigSet->AutoRetransmission;
        bxCanHdl[initController].Init.ReceiveFifoLocked      = ptr2CanParaConfigSet->ReceiveFifoLocked;
        bxCanHdl[initController].Init.TransmitFifoPriority   = ptr2CanParaConfigSet->TransmitFifoPriority;

        bxCanHdl[initController].Init.Prescaler              = ptr2BaudConfig->CanControllerPrescaler;
        bxCanHdl[initController].Init.SyncJumpWidth          = ptr2BaudConfig->CanControllerSyncJumpWidth;
        bxCanHdl[initController].Init.TimeSeg1               = ptr2BaudConfig->CanControllerSeg1;
        bxCanHdl[initController].Init.TimeSeg2               = ptr2BaudConfig->CanControllerSeg2;
        if (HAL_CAN_Init(&bxCanHdl[initController]) != HAL_OK)
        {
          state = CanIfStates::ErrorState;
          CANIF_DET_REPORTERROR(E_INIT_FAILED, CANIF_INIT_ID);
        }
      }
      else
      {
        // do error handling
          state = CanIfStates::ErrorState;
          CANIF_DET_REPORTERROR(E_INIT_FAILED, CANIF_INIT_ID);
      }
    }

    /*## -2- Start the CAN peripheral ###########################################*/
    /* this must be changed on controllers with other CAN modules */
    if (HAL_CAN_Start(&bxCanHdl[CanMasterController]) != HAL_OK)
    {
      /* Start Error */
      state = CanIfStates::ErrorState;
      CANIF_DET_REPORTERROR(E_INIT_FAILED, CANIF_INIT_ID);
    }
    if (bxCanHdl[CanSlaveController].Instance != NULL )
    {
      if (HAL_CAN_Start(&bxCanHdl[CanSlaveController]) != HAL_OK)
      {
        /* Start Error */
        state = CanIfStates::ErrorState;
        CANIF_DET_REPORTERROR(E_INIT_FAILED, CANIF_INIT_ID);
      }
    }
    /** @warning here will be done the unique connection to the interrupt handles 
     *  we need a good C++ way for this */
    ptr2Can1Hdl = &bxCanHdl[0];
    ptr2Can2Hdl = &bxCanHdl[1];

    /*## -3- Activate CAN RX notification #######################################*/
    /** @todo we need a generic mode for IRQ activation */
    if (HAL_CAN_ActivateNotification(&bxCanHdl[CanMasterController], CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
      /* Notification Error */
      CANIF_DET_REPORTERROR(E_INIT_FAILED, CANIF_INIT_ID);
    }
    else
    {
      ++state;
      returnValue = E_OK;
    }
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

  if ( returnValue == E_OK ) // HAL start was successful
  {
    returnValue = E_NOT_OK;
    // init the Tx-Path

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
//    VAR(CanIf_UpperLayerConnectType, AUTOMATIC) UL_Config;
    for (ComStack_PduType InitPdu = 0; InitPdu < CanIf_Rx_unknownPdu; InitPdu++ )
    {
//        UL_Config.PduId = MyTest_RxPduConfig[InitPdu].N_PDU_Name;
//        UL_Config.UpperLayer = MyTest_RxPduConfig[InitPdu].ULName;
//        UL_Config.ptr2Storage = NULL_PTR;
      if ( MyTest_RxPduConfig[InitPdu].IdMask.Id29bit > 0x0 )
      {
//        CanIf_SetFilterByBitmask(
//            MyTest_RxPduConfig[InitPdu].InstanceName,
//            MyTest_RxPduConfig[InitPdu].CanId,
//            MyTest_RxPduConfig[InitPdu].IdMask,
//            &UL_Config);
        if ( SetFilterByBitmask(
              MyTest_RxPduConfig[InitPdu].InstanceName,
              MyTest_RxPduConfig[InitPdu].CanId,
              MyTest_RxPduConfig[InitPdu].IdMask) >= 0 )
        {
          // do something on success
        }

      }
      else
      {
//        CanIf_SetFilterByCanId(
//            MyTest_RxPduConfig[InitPdu].InstanceName,
//            MyTest_RxPduConfig[InitPdu].CanId,
//            &UL_Config);
        if ( SetFilterByCanId(
              MyTest_RxPduConfig[InitPdu].InstanceName,
              MyTest_RxPduConfig[InitPdu].CanId) >= 0 )
        {
          // do something on success
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
  uint32_t txBufferpos = 0;
  Std_ReturnType returnValue = E_NOT_OK;

  if (state == CanIfStates::Ready )
  {
    // we need a empty message buffer box
    for (txBufferpos = 0; txBufferpos < CANIF_TX_BUFFER_SIZE; txBufferpos++ )
    {
      if ( canTxBuffer[txBufferpos].State == CanIf_TxMessage_free )
      {
        canTxBuffer[txBufferpos].State = CanIf_TxMessage_write;
        if ( msgHeader.CanId.IDE == CANIF_EXTID )
        {
          canTxBuffer[txBufferpos].Header.ExtId = msgHeader.CanId.Id29bit;
          canTxBuffer[txBufferpos].Header.IDE = CAN_ID_EXT;
        }
        else
        {
          canTxBuffer[txBufferpos].Header.StdId = msgHeader.CanId.Id29bit;
          canTxBuffer[txBufferpos].Header.IDE = CAN_ID_STD;
        }

        canTxBuffer[txBufferpos].Header.DLC = msgHeader.DLC;
        canTxBuffer[txBufferpos].Header.RTR = msgHeader.CanId.RTR;

        for (uint8_t bPos = 0; bPos < 8; bPos++)
          {canTxBuffer[txBufferpos].Data[bPos] = ptr2Data[bPos];}

        canTxBuffer[txBufferpos].State = CanIf_TxMessage_rdy2tx;
        txBufferpos = CANIF_TX_BUFFER_SIZE + 1; // -> this breaks the search on the buffer
        returnValue = E_OK;
      }
    }
  }
  return returnValue;
}
/* Requests transmission of a CAN message with PDU info. */
FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Transmit(
    CONST(CanIf_TxPduIdType,AUTOMATIC) txPduId,
    P2CONST(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo)
{
  uint32_t TxBufferpos = 0;
  Std_ReturnType ReturnValue = E_NOT_OK;
  //  CAN_TxHeaderTypeDef   StmHeader;
  uint8_t* ptr2Data = ptr2PduInfo->SduDataPtr;

  if ( txPduId < CanIf_Tx_unknownPdu )
  {
    if (state == CanIfStates::Ready )
    {
      // we need a empty message buffer box
      for (TxBufferpos = 0; TxBufferpos < CANIF_TX_BUFFER_SIZE; TxBufferpos++ )
      {
        if ( canTxBuffer[TxBufferpos].State == CanIf_TxMessage_free )
        {
          canTxBuffer[TxBufferpos].State = CanIf_TxMessage_write;
          canTxBuffer[TxBufferpos].Header = txHeaderList[txPduId];
          canTxBuffer[TxBufferpos].Header.DLC = ptr2PduInfo->SduLength;

          /* copy data bytes to tx buffer */
          for (uint8_t bPos = 0; bPos < 8; bPos++)
            {canTxBuffer[TxBufferpos].Data[bPos] = ptr2Data[bPos];}

          canTxBuffer[TxBufferpos].State = CanIf_TxMessage_rdy2tx;
          TxBufferpos = CANIF_TX_BUFFER_SIZE + 1; // -> this breaks the search on the buffer
          ReturnValue = E_OK;
        }
      }
    }
  }
  return ReturnValue;
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

/* USER CODE BEGIN CanIf_Receive 0 */

/* USER CODE END CanIf_Receive 0 */

  for (uint32_t rxBufferpos = 0; (rxBufferpos < CANIF_RX_BUFFER_SIZE) && (returnValue == E_NOT_OK); rxBufferpos++ )
  {
/* USER CODE BEGIN CanIf_Receive 1 */

/* USER CODE END CanIf_Receive 1 */
    if ( canRxBuffer.ptr2MsgBuffer[rxBufferpos].State == CanIf_RxMessage_rdy2rd )
    {
/* USER CODE BEGIN CanIf_Receive 2 */

/* USER CODE END CanIf_Receive 2 */
      ComStack_CanIdType requestCanId = msgHeader.CanId;
      ComStack_CanIdType testCanId = canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Message.CanIf_Header.CanId;

      if ( CANIF_IS_CANID_EQUAL(requestCanId, testCanId) )
      {
        canRxBuffer.ptr2MsgBuffer[rxBufferpos].State = CanIf_RxMessage_read;
        msgHeader.DLC = canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Message.CanIf_Header.DLC;
        msgHeader.Timestamp = canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Message.CanIf_Header.Timestamp;
        for ( uint8_t ByteCounter = 0; ByteCounter < msgHeader.DLC; ByteCounter++)
        {
          ptr2Data[ByteCounter] =  canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Message.Data[ByteCounter];
        }
        returnValue = E_OK;  // -> this breaks the search on the buffer
        canRxBuffer.ptr2MsgBuffer[rxBufferpos].State = CanIf_RxMessage_rxok;
      }

/* USER CODE BEGIN CanIf_Receive 3 */

/* USER CODE END CanIf_Receive 3 */
    }

/* USER CODE BEGIN CanIf_Receive 4 */

/* USER CODE END CanIf_Receive 4 */
  }

/* USER CODE BEGIN CanIf_Receive 5 */

/* USER CODE END CanIf_Receive 5 */
  return returnValue;
}

/* read a received message from buffer via PDU naming */
/**  @todo this is a fix not save implementation */
FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::Receive(
    CONST(CanIf_RxPduIdType,AUTOMATIC) rxPduId,
    P2VAR(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) ptr2PduInfo)
{
  Std_ReturnType returnValue = E_NOT_OK;
/* USER CODE BEGIN CanIf_Receive 0 */

/* USER CODE END CanIf_Receive 0 */

  for (uint32_t rxBufferpos = 0; (rxBufferpos < CANIF_RX_BUFFER_SIZE) && (returnValue == E_NOT_OK); rxBufferpos++ )
  {
/* USER CODE BEGIN CanIf_Receive 1 */

/* USER CODE END CanIf_Receive 1 */
    if ( canRxBuffer.ptr2MsgBuffer[rxBufferpos].State == CanIf_RxMessage_rdy2rd )
    {
/* USER CODE BEGIN CanIf_Receive 2 */

/* USER CODE END CanIf_Receive 2 */
      //ComStack_CanIdType requestCanId = rxHeaderList[rxPduId].CanId;
      ComStack_CanIdType requestCanId = MyTest_RxPduConfig[rxPduId].CanId;
      ComStack_CanIdType testCanId = canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Message.CanIf_Header.CanId;

      //if ( CANIF_IS_CANID_EQUAL(requestCanId, testCanId) )
      if ( requestCanId == testCanId ) // we can use the "new" operator :-)
      {
        canRxBuffer.ptr2MsgBuffer[rxBufferpos].State = CanIf_RxMessage_read;
        if ( ptr2PduInfo->SduLength > canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Message.CanIf_Header.DLC)
        {
          // der kleinere Wert bestimmt die Anzahl der zu lesenden Bytes
          // vielleicht sollten wir auch mit rxHeaderList[rxPduId].DLC überprüfen
          ptr2PduInfo->SduLength = canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Message.CanIf_Header.DLC;
        }
        /* todo vielleicht notwendig bei TT CAN
        ptr2PduInfo->Timestamp = canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Header.Timestamp;
        */

        for ( uint8_t ByteCounter = 0; ByteCounter < ptr2PduInfo->SduLength; ByteCounter++)
        {
          ptr2PduInfo->SduDataPtr[ByteCounter] =  canRxBuffer.ptr2MsgBuffer[rxBufferpos].CanIf_Message.Data[ByteCounter];
        }
        returnValue = E_OK;  // -> this breaks the search on the buffer
        //canRxBuffer.ptr2MsgBuffer[rxBufferpos].State = CanIf_RxMessage_rxok;
        canRxBuffer.ptr2MsgBuffer[rxBufferpos].State = CanIf_RxMessage_free;
      }

/* USER CODE BEGIN CanIf_Receive 3 */

/* USER CODE END CanIf_Receive 3 */
    }

/* USER CODE BEGIN CanIf_Receive 4 */

/* USER CODE END CanIf_Receive 4 */
  }

/* USER CODE BEGIN CanIf_Receive 5 */

/* USER CODE END CanIf_Receive 5 */
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
  uint32_t txBufferpos = 0;

  if (state == CanIfStates::Ready )
  {
    for (txBufferpos = 0; txBufferpos < CANIF_TX_BUFFER_SIZE; txBufferpos++ )
    {
      /** @todo the Tx Task need handling to transmit to other CAN controller then the bxCanMaster */
      if ( HAL_CAN_GetTxMailboxesFreeLevel(&bxCanHdl[CanMasterController]) > 0 )
      {
        switch ( canTxBuffer[txBufferpos].State)
        {
          case CanIf_TxMessage_rdy2tx:
            // we block for transmit
            canTxBuffer[txBufferpos].State = CanIf_TxMessage_transmit;

            // give the message via HAL to the CAN Controller
            canTxBufferMirror = canTxBuffer[txBufferpos];
            //if ( HAL_CAN_AddTxMessage(&bxCanHdl[CanMasterController], &CanTxBuffer[TxBufferpos].Header, CanTxBuffer[TxBufferpos].Data, &CanTxBuffer[TxBufferpos].Mailbox) != HAL_OK)
            if ( HAL_CAN_AddTxMessage(&bxCanHdl[CanMasterController], &canTxBufferMirror.Header, canTxBuffer[txBufferpos].Data, &canTxBuffer[txBufferpos].Mailbox) != HAL_OK)
            {
              canTxBuffer[txBufferpos].State = CanIf_TxMessage_txerr;
              Error_Handler();
            }
            break;
          case CanIf_TxMessage_transmit:
            if ( !(HAL_CAN_IsTxMessagePending(&bxCanHdl[CanMasterController], canTxBuffer[txBufferpos].Mailbox)) )
            {
              canTxBuffer[txBufferpos].State = CanIf_TxMessage_txok;
            }
            break;
          case CanIf_TxMessage_txok:
            if ( 1  ) // maybe we want to wait until clear up the mailbox
            {
              canTxBuffer[txBufferpos] = cleanMessage;
            }
            break;
          default:
            // nothing to do
            break;
        }
      }
    }
  }
}

/* to find a free CAN hardware filter */
FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::FindFreeFilter(
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterBankNumber,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterNumber,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2FilterMode)
{
  P2VAR(CAN_TypeDef, AUTOMATIC, AUTOMATIC) ptr2Instance = bxCanHdl[CanMasterController].Instance;
  Std_ReturnType returnValue = E_NOT_OK;
  uint32_t filterBankRegValue = ptr2Instance->FA1R;
  uint32_t filterModeRegValue = ptr2Instance->FM1R;

  /* the STM HAL library has no function to find a free hardware filter
   * we test only for active filter */
  uint8_t testBank = 0;
  uint8_t foundBank = FALSE;
  uint8_t filterCounter = 0;
  uint8_t filterIncrement = 0;

  /** @todo we need to clean up the filter number CAN1_USED_RX_HW_FILTER */
  while ((filterCounter < CAN1_USED_RX_HW_FILTER) && (foundBank == FALSE ))
  {
    foundBank = 0x1 & ~(filterBankRegValue>>testBank);
    if ( (0x1 & (filterModeRegValue>>testBank)) == CAN_FILTERMODE_IDLIST)
    {
      filterIncrement = 2;
      // second filter inside a filter bank used as ID filter is free
      if ( (*ptr2FilterMode == CAN_FILTERMODE_IDLIST ) &&
           (ptr2Instance->sFilterRegister[testBank].FR2 == 0xFFFFFFFF) )
      {
        foundBank = TRUE;
        filterCounter++; // single step when select a second filter
        /** @todo
         *  we need a readable implementation for the "second identifier filter bit" inside ptr2FilterMode */
        *ptr2FilterMode |= 0x80;
      }

    }
    else
    {
      filterIncrement = 1;
    }

    if (foundBank == FALSE )
    {
      testBank++;
      filterCounter += filterIncrement;
    }
    else /* we have found a free filter */
    {
      *ptr2FilterBankNumber = testBank;
      *ptr2FilterNumber = filterCounter;
      returnValue = E_OK;
    }
  }

  return returnValue;
}


/* configure a free hardware filter using bit masking */
FUNC(Std_ReturnType, TM_CANIF_CODE) CanIf::SetFilterByBitmask(
    VAR(ECU_CanController, AUTOMATIC) Controller,
    VAR(ComStack_CanIdType, AUTOMATIC) FilterId,
    VAR(ComStack_CanIdType, AUTOMATIC) FilterMask) //,
    //P2VAR(CanIf_UpperLayerConnectType, AUTOMATIC, AUTOMATIC) UL_Link )
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  CAN_FilterTypeDef  sFilterConfig;

  uint32_t StmFilterId = CanIdToHalFormat(FilterId);
  uint32_t StmMaskId = CanIdToHalFormat(FilterMask);
  uint8_t TempBank = 0;
  uint8_t TempNumber = 0;
  uint8_t TempMode = CAN_FILTERMODE_IDMASK;
  if ( FindFreeFilter(&TempBank, &TempNumber, &TempMode) == E_OK )
  {
    sFilterConfig.FilterBank = TempBank;

    if ( (TempMode & 0x80) == 0x80 )
    {
      /* this shouldn't happen here*/
      Error_Handler();
    }

    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = ( 0xFFFF0000U & StmFilterId) >> 16;
    sFilterConfig.FilterIdLow = (0x0000FFFFU & StmFilterId);
    sFilterConfig.FilterMaskIdHigh = ( 0xFFFF0000U & StmMaskId) >> 16;
    sFilterConfig.FilterMaskIdLow = ( 0x0000FFFFU & StmMaskId);
  /** @todo we need a handling to select different Rx Fifo */
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    if (HAL_CAN_ConfigFilter(&bxCanHdl[CanMasterController], &sFilterConfig) != HAL_OK)
    {
      /* Filter configuration Error */
      Error_Handler();
    }
    /* we save the pointer according to the Filter Number to fast access in the IRQ routine
     * the IRQ must test against the NULL_PTR */
  //  ptr2FilterMailbox[TempNumber] = UL_Link->ptr2Storage;

    // connect ptr2Data and UpperLayer-Name with Filter number
    //CanIfUpperLayer[TempNumber] = *UL_Link;

  }

  return ReturnValue;
}

/* configure a free hardware filter using single CAN Id filtering */
FUNC(int, TM_CANIF_CODE) CanIf::SetFilterByCanId(
   VAR(ECU_CanController, AUTOMATIC) Controller,
   VAR(ComStack_CanIdType, AUTOMATIC) FilterId)//,
   //P2VAR(CanIf_UpperLayerConnectType, AUTOMATIC, AUTOMATIC) UL_Link )
{
  int returnValue = -E_NOT_OK;
  CAN_FilterTypeDef  sFilterConfig;
  uint32_t SaveFilterbank = 0;

  uint32_t StmFilterId = CanIdToHalFormat(FilterId);
  uint8_t TempBank = 0;
  uint8_t TempNumber = 0;
  uint8_t TempMode = CAN_FILTERMODE_IDLIST;
  if ( FindFreeFilter(&TempBank, &TempNumber, &TempMode) == E_OK )
  {
    sFilterConfig.FilterBank = TempBank;
//    FilterId = CanIf_CanIdToHalFormat( FilterId) ;
    if ( (TempMode & 0x80) == 0x80 ) // the FindFreeFilter() func sets this bit to show second filter on bank
    {
      SaveFilterbank  = bxCanHdl[CanMasterController].Instance->sFilterRegister[TempBank].FR1;
      sFilterConfig.FilterMaskIdHigh = ( 0xFFFF0000U & StmFilterId) >> 16;
      sFilterConfig.FilterMaskIdLow = ( 0x0000FFFFU & StmFilterId);
      sFilterConfig.FilterIdHigh = ( 0xFFFF0000U & SaveFilterbank) >> 16;
      sFilterConfig.FilterIdLow = (0x0000FFFFU & SaveFilterbank);
    }
    else
    {
      sFilterConfig.FilterIdHigh = ( 0xFFFF0000U & StmFilterId) >> 16;
      sFilterConfig.FilterIdLow = (0x0000FFFFU & StmFilterId);
      sFilterConfig.FilterMaskIdHigh = 0xFFFF; // we prepare the mask register to reuse it with a second identifier
      sFilterConfig.FilterMaskIdLow = 0xFFFF;  // see above
    }
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    /** @todo we need a handling to select different Rx Fifo */
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 20;
    if (HAL_CAN_ConfigFilter(&bxCanHdl[CanMasterController], &sFilterConfig) != HAL_OK)
    {
      /* Filter configuration Error */
      Error_Handler();
    }
    /* we save the pointer according to the Filter Number to fast access in the IRQ routine
     * the IRQ must test against the NULL_PTR */
 //   ptr2FilterMailbox[TempNumber] = UL_Link->ptr2Storage;
    // connect ptr2Data and UpperLayer-Name with Filter number
//    CanIfUpperLayer[TempNumber].UpperLayer = UL_Link->UpperLayer;
//    CanIfUpperLayer[TempNumber].ptr2Storage = UL_Link->ptr2Storage;
//    CanIfUpperLayer[TempNumber].PduId = UL_Link->PduId;
    //CanIfUpperLayer[TempNumber] = *UL_Link;
    returnValue = TempNumber;
  }

  return returnValue;
}

/* change the 32bit format to use with STM Registers */
FUNC(uint32_t, TM_CANIF_CODE) CanIf::CanIdToHalFormat(
    VAR(ComStack_CanIdType, AUTOMATIC) CanId)
{
  CanIf_CanIdSelectType CatchBits;
  CatchBits.stm_ExtId.IDE = CanId.IDE;
  CatchBits.stm_ExtId.RTR = CanId.RTR;
  if (CanId.IDE == TRUE )
  {
    CatchBits.stm_ExtId.Id29bit = CanId.Id29bit;
  }
  else
  {
    CatchBits.stm_StdId.Id11bit = (0x7FF & CanId.Id29bit);
  }
  return CatchBits.common;
}

FUNC(Std_ReturnType, TM_CANIF_CODE) HalHeaderToCanIfHeader(
    REF2CONST(CAN_RxHeaderTypeDef,AUTOMATIC)  rev2HAL_Header,
    REF2VAR(ComStack_CanMsgHeader, AUTOMATIC)  rev2CanIfHeader )
{
  Std_ReturnType returnValue = E_NOT_OK;
  /* remapping the CAN header */
  if ( rev2HAL_Header.IDE == CAN_ID_EXT )
  {
    rev2CanIfHeader.CanId.Id29bit  = rev2HAL_Header.ExtId;
    rev2CanIfHeader.CanId.IDE = CANIF_EXTID;
  }
  else
  {
    rev2CanIfHeader.CanId.Id29bit  = rev2HAL_Header.StdId;
  }
  rev2CanIfHeader.CanId.RTR = rev2HAL_Header.RTR;
  rev2CanIfHeader.DLC = rev2HAL_Header.DLC;
  rev2CanIfHeader.Timestamp = rev2HAL_Header.Timestamp;
  rev2CanIfHeader.FilterMatchIndex = rev2HAL_Header.FilterMatchIndex;
  /* end of remapping */
  returnValue = E_OK;
  return returnValue;
}

FUNC(Std_ReturnType, TM_CANIF_CODE) CanIfHeaderToHalHeader(
    REF2CONST(ComStack_CanMsgHeader, AUTOMATIC)  rev2CanIfHeader,
    REF2VAR(CAN_RxHeaderTypeDef,AUTOMATIC)  rev2HAL_Header )
{
  Std_ReturnType returnValue = E_NOT_OK;
  /* remapping the CAN header */
  if ( rev2CanIfHeader.CanId.IDE == CANIF_EXTID )
  {
    rev2HAL_Header.ExtId = rev2CanIfHeader.CanId.Id29bit;
    rev2HAL_Header.IDE = CAN_ID_EXT;
  }
  else
  {
    rev2HAL_Header.StdId = rev2CanIfHeader.CanId.Id29bit;
  }
  rev2HAL_Header.RTR = rev2CanIfHeader.CanId.RTR;
  rev2HAL_Header.DLC = rev2CanIfHeader.DLC;
  rev2HAL_Header.Timestamp = rev2CanIfHeader.Timestamp;
  rev2HAL_Header.FilterMatchIndex = rev2CanIfHeader.FilterMatchIndex;
  /* end of remapping */
  returnValue = E_OK;
  return returnValue;
}


/* #########################  interrupt callback function ############## */

/** this overwrites the weak HAL function */
ISR_FUNC( TM_CANIF_ISR_CODE) HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  canRxBuffer.BufWrPos = 0;

//  uint8_t* ptr2buf = NULL_PTR;
//  tm_PduIDType pduId = INVALID_PDUID;
//  CanIf_UpperLayerType CallUpperLayer = CanIfUL_undefined;

  /* find free rx buffer place or take the last */
  while ( (canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].State != CanIf_RxMessage_free ) && (canRxBuffer.BufWrPos< (CANIF_RX_BUFFER_SIZE-1) ))
  {
    canRxBuffer.BufWrPos++;
  }
  canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].State = CanIf_RxMessage_rdy2rd;

  /* Get RX message */
  if ( HAL_CAN_GetRxMessage( hcan,
                             CAN_RX_FIFO0,
                            &canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].HAL_Header,
                             canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].CanIf_Message.Data )        == HAL_OK )
  {
    //LED_BLUE_TOGGLE;
    /* remapping the CAN header */
    HalHeaderToCanIfHeader(canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].HAL_Header, canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].CanIf_Message.CanIf_Header);

    /* Ziel ist es dass die Filternummer unmittelbar die RxIndication Funktion des dazu gehörigen Empfängers aufruft */
    /* Impelentation goal is this way: the filter number coming with the HAL_CAN_GetRxMessage inside the HAL_Header.FilterMatchIndex should be select the needed RxIndication function */
    uint32_t filterIndex = canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].HAL_Header.FilterMatchIndex;
    if ( filterIndex == testFilter )
  {
    //  LED_BLUE_TOGGLE;
  }
    if ( ( p2UpperLayerList[filterIndex] != nullptr ) )
    {
      p2UpperLayerList[filterIndex]->RxIndication(MyTest_RxPduConfig[filterIndex].N_PDU_Name, &canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].CanIf_Message);
    }

//    for (ComStack_PduType searchPdu = 0; searchPdu < CanIf_Rx_unknownPdu; searchPdu++ )
//    {
//      if ( (MyTest_RxPduConfig[searchPdu].CanId == canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].CanIf_Message.CanIf_Header.CanId ) &&
//          ( p2UpperLayerList[searchPdu] != nullptr ) )
//      {
//        p2UpperLayerList[searchPdu]->RxIndication(MyTest_RxPduConfig[searchPdu].L_PDU_Name, &canRxBuffer.ptr2MsgBuffer[canRxBuffer.BufWrPos].CanIf_Message);
//      }
//    }
  }
}

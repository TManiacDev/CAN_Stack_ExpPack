/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanDrv_bxCAN.cpp

 * @author TManiac
 * @date Nov 19, 2022
 * @version 
 *
 */
#include "CanDrv_bxCAN.h"
#include <vector>

#ifndef HAL_CAN_MODULE_ENABLED
/*
 * @todo
 * we need the STM HAL CAN module.
 * */
 #error "The CanIf needs the STM CAN HAL module"
#endif

/** @brief This is the configuration for the STM Nulceo144 board */
EXTERN_CONST( CanConfigType, AUTOMATIC) Can_DefaultConfig;

/** names of the CAN controller configurations
 *
 * @todo das sollte auch extern sein: extern const ECU_CanController controllerList[];*/
EXTERN_CONST( std::vector<ECU_CanController>, AUTOMATIC) controllerList;

/* * @brief to use the generic name coming from the template */
extern CAN_HandleTypeDef* ptr2Can1Hdl;

/* * @brief to use the generic name coming from the template */
extern CAN_HandleTypeDef* ptr2Can2Hdl;

/** @brief we want a Rx software buffer
 *
 *  we start with a fix size. Later it would be go to the IDE */
bxCan_RxMessageType     bxCan_rxMsgBuffer[CAN_RX_SW_BUFFER_SIZE];

/** @brief the object to handle the RxBuffer
 *
 * @todo bring the buffers to save class */
bxCan_RxSwBufferType bxCan_canRxBuffer =
{
    0,
    0,
    bxCan_rxMsgBuffer
};

SYS_FUNC( TM_CAN_CODE ) CanDrv_bxCAN::CanDrv_bxCAN() {
  // TODO Auto-generated constructor stub

}

SYS_FUNC( TM_CAN_CODE ) CanDrv_bxCAN::~CanDrv_bxCAN() {
  // TODO Auto-generated destructor stub
}


FUNC(Std_ReturnType, TM_CAN_CODE) CanDrv_bxCAN::Init(
    P2CONST(CanConfigType, AUTOMATIC, AUTOMATIC) ptr2Config,
    P2VAR(ComIf, TM_CAN_VAR, AUTOMATIC) ptr2ComIfObject  )
{
  Std_ReturnType returnValue = E_NOT_OK;

  if ( GetDrvState() != CanDrvStates::Uninit )
  {
    CAN_DET_REPORTERROR(Can_DevError::E_TRANSITION, CAN_INIT_ID);
  }
  else
  {

    ptr2ComIf = ptr2ComIfObject;

    /*###############################################
     * start the HAL hardware driver
     ################################################*/

      /*## -1- Configure the CAN peripheral #######################################*/
    for (auto& initController : controllerList )
    {
      P2CONST( CanControllerParaType,           AUTOMATIC, AUTOMATIC ) ptr2CanParaConfigSet = &ptr2Config->ptr2CanParaConfigSet[initController];
      P2CONST( CanControllerBaudrateConfigType, AUTOMATIC, AUTOMATIC ) ptr2BaudConfig       = &ptr2Config->ptr2CanBaudrateConfigSet[ptr2CanParaConfigSet->InitBaudrate];

      if ( ptr2Config == NULL_PTR )
      {
        ptr2CanParaConfigSet = &Can_DefaultConfig.ptr2CanParaConfigSet[initController];
        ptr2BaudConfig       = &Can_DefaultConfig.ptr2CanBaudrateConfigSet[ptr2CanParaConfigSet->InitBaudrate];
      }

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
          CAN_DET_REPORTERROR(Can_DevError::E_INIT_FAILED, CAN_INIT_ID);
        }


        /*## -2- Activate CAN RX notification #######################################*/
        /** @todo we need a generic mode for IRQ activation */
        if (HAL_CAN_ActivateNotification(&bxCanHdl[CanMasterController], CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
        {
          /* Notification Error */
          CAN_DET_REPORTERROR(E_INIT_FAILED, CAN_INIT_ID);
        }

        /** @warning here will be done the unique connection to the interrupt handles
         *  we need a good C++ way for this
         *  we will switch to function pointer inside the Init-structure later */
        ptr2Can1Hdl = &bxCanHdl[0];
        ptr2Can2Hdl = &bxCanHdl[1];
        Can::SetDrvStateReady();
        returnValue = E_OK;
      }
      else
      {
        // do error handling
        CAN_DET_REPORTERROR(Can_DevError::E_INIT_FAILED, CAN_INIT_ID);
      }
    }
  }
  return returnValue;
}


Std_ReturnType CanDrv_bxCAN::SetControllerMode ( ECU_CanController Controller, CanControllerStates Transition )
{
  Std_ReturnType returnValue = E_NOT_OK;
  /// @todo maybe we add the possibility to call the function with Controller == ECU_CanController::NBROF_CanController
//  uint32_t CountOfController;
//  if ( Controller == ECU_CanController::NBROF_CanController )
//  {
//    CountOfController = Controller;
//    //Controller
//  }
//
//  for (auto& initController : controllerList )
//  {
//
//  }
  if ( Controller < ECU_CanController::NBROF_CanController )
  {
    switch (Transition)
    {
      case (CanControllerStates::CS_Started):
      {
        if (HAL_CAN_Start(&bxCanHdl[Controller]) != HAL_OK)
        {
          /* Start Error */
          CAN_DET_REPORTERROR(E_TRANSITION, CAN_SET_CONTROLLER_MODE_ID);
        }
        returnValue = E_OK;
        break;
      }
      default:
        break;
    }
  }
  else
  {
    CAN_DET_REPORTERROR(E_TRANSITION, CAN_SET_CONTROLLER_MODE_ID);
  }

  return returnValue;
}

Std_ReturnType CanDrv_bxCAN::Write(
      ECU_CanController Controller,
      P2CONST(ComStack_CanMessageType, AUTOMATIC,AUTOMATIC) ptr2PduInfo )
{
  Std_ReturnType returnValue = E_NOT_OK;
  uint32_t TxBufferpos = 0;

  if (Can::GetDrvState() != CanDrvStates::Ready )
  {
    CAN_DET_REPORTERROR(E_UNINIT, CAN_WRITE_ID);
  }
  else
  {
    // we need a empty message buffer box
    for (TxBufferpos = 0; TxBufferpos < CAN_TX_SW_BUFFER_SIZE; TxBufferpos++ )
    {
      if ( canTxBuffer[TxBufferpos].State == bxCan_TxMessageStateType::TxMessage_free )
      {
        canTxBuffer[TxBufferpos].State = bxCan_TxMessageStateType::TxMessage_write;
        canTxBuffer[TxBufferpos].Controller = Controller;
        if (ptr2PduInfo->CanMsgHeader.CanId.IDE == TRUE )
        {
          canTxBuffer[TxBufferpos].Header.IDE = CAN_ID_EXT;
          canTxBuffer[TxBufferpos].Header.ExtId = ptr2PduInfo->CanMsgHeader.CanId.Id29bit;
        }
        else
        {
          canTxBuffer[TxBufferpos].Header.StdId = ptr2PduInfo->CanMsgHeader.CanId.Id29bit;

        }
        canTxBuffer[TxBufferpos].Header.DLC = ptr2PduInfo->CanMsgHeader.DLC;

        /* copy data bytes to tx buffer */
        for (uint8_t bPos = 0; bPos < 8; bPos++)
          {canTxBuffer[TxBufferpos].Data[bPos] = ptr2PduInfo->ptr2Data[bPos];}

        canTxBuffer[TxBufferpos].State = bxCan_TxMessageStateType::TxMessage_rdy2tx;
        TxBufferpos = CAN_TX_SW_BUFFER_SIZE + 1; // -> this breaks the search on the buffer
        returnValue = E_OK;
      }
    }
  }

  return returnValue;
}

/** @brief task function to push the tx message from software buffer to tx mailbox */
FUNC(void, TM_CAN_CODE) CanDrv_bxCAN::TxTask(void)
{
  uint32_t txBufferpos = 0;

  if ( Can::GetDrvState() == CanDrvStates::Ready )
  {
    for (txBufferpos = 0; txBufferpos < CAN_TX_SW_BUFFER_SIZE; txBufferpos++ )
    {
      /** @todo the Tx Task need handling to transmit to other CAN controller then the bxCanMaster */
      if ( HAL_CAN_GetTxMailboxesFreeLevel(&bxCanHdl[CanMasterController]) > 0 )
      {
        switch ( canTxBuffer[txBufferpos].State)
        {
          case bxCan_TxMessageStateType::TxMessage_rdy2tx:
            // we block for transmit
            canTxBuffer[txBufferpos].State = bxCan_TxMessageStateType::TxMessage_transmit;

            // give the message via HAL to the CAN Controller
            if ( HAL_CAN_AddTxMessage(&bxCanHdl[CanMasterController], &canTxBuffer[txBufferpos].Header, canTxBuffer[txBufferpos].Data, &canTxBuffer[txBufferpos].Mailbox) != HAL_OK)
            {
              canTxBuffer[txBufferpos].State = bxCan_TxMessageStateType::TxMessage_txerr;
              Error_Handler();
            }
            break;
          case bxCan_TxMessageStateType::TxMessage_transmit:
            if ( !(HAL_CAN_IsTxMessagePending(&bxCanHdl[CanMasterController], canTxBuffer[txBufferpos].Mailbox)) )
            {
              canTxBuffer[txBufferpos].State = bxCan_TxMessageStateType::TxMessage_txok;
            }
            break;
          case bxCan_TxMessageStateType::TxMessage_txok:
            if ( 1  ) // maybe we want to wait until clear up the mailbox
            {
              canTxBuffer[txBufferpos].Mailbox = 0;
              canTxBuffer[txBufferpos].Header = {0};
              canTxBuffer[txBufferpos].State = bxCan_TxMessageStateType::TxMessage_free;
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
FUNC(Std_ReturnType, TM_CAN_CODE) CanDrv_bxCAN::FindFreeFilter(
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
FUNC(Std_ReturnType, TM_CAN_CODE) CanDrv_bxCAN::SetFilterByBitmask(
    VAR(ECU_CanController, AUTOMATIC) Controller,
    VAR(ComStack_CanIdType, AUTOMATIC) FilterId,
    VAR(ComStack_CanIdType, AUTOMATIC) FilterMask) //,
    //P2VAR(CanIf_UpperLayerConnectType, AUTOMATIC, AUTOMATIC) UL_Link )
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  CAN_FilterTypeDef  sFilterConfig;

  uint32_t StmFilterId = CanIdToStmRegisterFormat(FilterId);
  uint32_t StmMaskId = CanIdToStmRegisterFormat(FilterMask);
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
  }

  return ReturnValue;
}

/* configure a free hardware filter using single CAN Id filtering */
FUNC(Std_ReturnType, TM_CAN_CODE) CanDrv_bxCAN::SetFilterByCanId(
   VAR(ECU_CanController, AUTOMATIC) Controller,
   VAR(ComStack_CanIdType, AUTOMATIC) FilterId)//,
   //P2VAR(CanIf_UpperLayerConnectType, AUTOMATIC, AUTOMATIC) UL_Link )
{
  Std_ReturnType returnValue = -E_NOT_OK;
  CAN_FilterTypeDef  sFilterConfig;
  uint32_t SaveFilterbank = 0;

  uint32_t StmFilterId = CanIdToStmRegisterFormat(FilterId);
  uint8_t TempBank = 0;
  uint8_t TempNumber = 0;
  uint8_t TempMode = CAN_FILTERMODE_IDLIST;
  if ( FindFreeFilter(&TempBank, &TempNumber, &TempMode) == E_OK )
  {
    sFilterConfig.FilterBank = TempBank;
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
    returnValue = TempNumber;
  }

  return returnValue;
}

/* change the 32bit format to use with STM Registers */
FUNC(uint32_t, TM_CAN_CODE) CanDrv_bxCAN::CanIdToStmRegisterFormat(
    VAR(ComStack_CanIdType, AUTOMATIC) CanId)
{
  bxCan_IdSelectType CatchBits;
  if (CanId.IDE == TRUE )
  {
    CatchBits.stm_ExtId.Id29bit = CanId.Id29bit;
    CatchBits.stm_ExtId.IDE = TRUE;
    CatchBits.stm_ExtId.RTR = CanId.RTR;
  }
  else
  {
    CatchBits.stm_StdId.Id11bit = (0x7FF & CanId.Id29bit);
    CatchBits.stm_StdId.RTR = CanId.RTR;
  }
  return CatchBits.common;
}

FUNC(Std_ReturnType, TM_CAN_CODE) HalHeaderToCanStackHeader(
    REF2CONST(CAN_RxHeaderTypeDef,AUTOMATIC)  rev2HAL_Header,
    REF2VAR(ComStack_CanMsgHeader, AUTOMATIC)  rev2CanStackHeader )
{
  Std_ReturnType returnValue = E_NOT_OK;
  /* remapping the CAN header */
  if ( rev2HAL_Header.IDE == CAN_ID_EXT )
  {
    rev2CanStackHeader.CanId.Id29bit  = rev2HAL_Header.ExtId;
    rev2CanStackHeader.CanId.IDE = CANIF_EXTID;
  }
  else
  {
    rev2CanStackHeader.CanId.Id29bit  = rev2HAL_Header.StdId;
  }
  rev2CanStackHeader.CanId.RTR = rev2HAL_Header.RTR;
  rev2CanStackHeader.DLC = rev2HAL_Header.DLC;
  rev2CanStackHeader.Timestamp = rev2HAL_Header.Timestamp;
  rev2CanStackHeader.FilterMatchIndex = rev2HAL_Header.FilterMatchIndex;
  /* end of remapping */
  returnValue = E_OK;
  return returnValue;
}

/** this overwrites the weak HAL function */
ISR_FUNC( TM_CAN_ISR_CODE) HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  /* find free rx buffer place or take the last */
  while ( (bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].State != bxCan_RxMessageStateType::RxMessage_free ) && (bxCan_canRxBuffer.BufWrPos< (CAN_RX_SW_BUFFER_SIZE-1) ))
  {
    bxCan_canRxBuffer.BufWrPos++;
  }
  bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].State = bxCan_RxMessageStateType::RxMessage_rdy2rd;

  /* Get RX message */
  if ( HAL_CAN_GetRxMessage( hcan,
                             CAN_RX_FIFO0,
                            &bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].HAL_Header,
                            bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].Data )        == HAL_OK )
  {
    /* remapping the CAN header */
    HalHeaderToCanStackHeader(bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].HAL_Header, bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].CanMsgHeader);


    if ( ptr2ComIf != NULL_PTR )
    {
      ComStack_PduInfoType PduInfo{ bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].Data, bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].CanMsgHeader.DLC };
      if ( hcan->Instance == CAN1 )
      {
        ptr2ComIf->RxIndication(ECU_CanController::CanMasterController, bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].CanMsgHeader, PduInfo);
      }
      if ( hcan->Instance == CAN2 )
      {
        ptr2ComIf->RxIndication(ECU_CanController::CanSlaveController, bxCan_canRxBuffer.ptr2MsgBuffer[bxCan_canRxBuffer.BufWrPos].CanMsgHeader, PduInfo);
      }
    }
  }
}

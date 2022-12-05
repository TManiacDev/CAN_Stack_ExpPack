/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanIsoTP.c

 * @author TManiac
 * @date 31.03.2022
 * @version 
 *
 */
#include "CanIf.h"
#include "IsoTP.h"
#include "string.h"

#include <IsoTP_Compiler_cfg.h>
/* private Includes -----------------------------------------------------------*/
/* USER CODE BEGIN CanFT2p0TL_include 0 */

/* USER CODE END CanFT2p0TL_include 0 */

#if ( CANISOTP_DEV_ERROR_DETECT == STD_ON )

#endif // ( CANFT2P0TL_DEV_ERROR_DETECT == STD_ON )

#define CANISOTP_RXINDICATION  (0x1)
#define CANISOTP_RXDATACOPY    ((0x1) << 16 )

CONST(IsoTP_ConfigType, TM_ISOTP_CONST) IsoTP_DefaultConfig =
{
  /** BS */
  .maxBlockSize = 8,
  /** STmin */
  .minSeparartionTime = 0,
  /** */
  .maxResponseTimeout = 100,
  .maxWaitForTransmitCylcles = 1,
  .Just_a_Dummy = 0xFF00FF00
};

SYS_FUNC( TM_ISOTP_CODE ) IsoTp::IsoTp() : TME_VersionInfo{ISOTP_MODULE_ID, ISOTP_VERSION, ISOTP_PATCH_VERSION}
{
  InitHandle();
}

SYS_FUNC( TM_ISOTP_CODE ) IsoTp::IsoTp(CONST(IsoTp_ObjectConfig, AUTOMATIC) initConfig)
  : TME_VersionInfo{ISOTP_MODULE_ID, ISOTP_VERSION, ISOTP_PATCH_VERSION},
    objectConfig{ initConfig }
{
  InitHandle();
}

SYS_FUNC( TM_ISOTP_CODE ) IsoTp::~IsoTp()
{
  // TODO Auto-generated destructor stub
}


FUNC(Std_ReturnType, AUTOMATIC) IsoTp::Init( CONST(IsoTP_RxTxStatus, AUTOMATIC) SendOrReceive )
{
  Std_ReturnType returnValue = E_NOT_OK;
  if ( objectHandle.ModuleState == IsoTP_StatesType::IsoTP_OFF )
  {
    objectHandle.FlowControl.rxIfPduName = objectConfig.p2ControllerInterface->GetIfRxPduName(CanIfUL_CanTP, objectConfig.rxPduName);
    objectHandle.FlowControl.txIfPduName = objectConfig.p2ControllerInterface->GetIfTxPduName(CanIfUL_CanTP, objectConfig.txPduName);
    if ( ( objectHandle.FlowControl.rxIfPduName != ComStack_InvalidPdu ) &&
        ( objectHandle.FlowControl.txIfPduName != ComStack_InvalidPdu ) )
    {
      if ( objectConfig.p2ControllerInterface->ConnectUpperLayerIndication( objectHandle.FlowControl.rxIfPduName, this ) == E_OK )
      {
        objectHandle.FlowControl.ProtocolStatus = SendOrReceive;
        objectHandle.ModuleState = IsoTP_StatesType::IsoTP_ON;
      }
      returnValue = E_OK;

    }
  }
  return returnValue;
}

FUNC(IsoTP_StatesType, TM_ISOTP_CODE) IsoTp::GetState( void ) { return objectHandle.ModuleState; }

/*  @brief Get the name of the linked rx PDU */
/** @todo we should add a virtual function to the CanIfUpperLayer class */
FUNC( IsoTP_RxPduType, TM_ISOTP_CODE ) IsoTp::GetRxPduName(void) { return objectConfig.rxPduName; }

/*  @brief Get the name of the linked rx PDU */
/** @todo we should add a virtual function to the CanIfUpperLayer class */
FUNC( IsoTP_TxPduType, TM_ISOTP_CODE ) IsoTp::GetTxPduName(void) { return objectConfig.txPduName; }

FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::InitHandle( void )
{
  Std_ReturnType returnValue = E_NOT_OK;
  if ( objectHandle.ModuleState == IsoTP_StatesType::IsoTP_OFF )
  {
    // objectHandle.ModuleState = IsoTP_StatesType::IsoTP_OFF;
    objectHandle.TaskTicks = 0;

    objectHandle.p2RxBuffer = NULL_PTR;
    objectHandle.p2TxBuffer = NULL_PTR;
    returnValue = E_OK;
  }
  else
  {
    ISOTP_DET_REPORTERROR(ISOTP_E_UNINIT, TM_ISOTP_INIT_ID);
  }
  return returnValue;
}

FUNC(Std_ReturnType, AUTOMATIC) IsoTp::Init(
    P2CONST(IsoTP_ConfigType, AUTOMATIC, AUTOMATIC) ptr2Config )
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue = E_NOT_OK;

  // #1 search config
  if ( ptr2Config == NULL_PTR )
  {
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
  ISOTP_DET_REPORTERROR(CANISOTP_E_PARAM_POINTER, CANISOTP_INIT_ID);
#else // ( CANISOTP_DEV_ERROR_DETECT == STD_ON )

#endif // #else !!! ( CANISOTP_DEV_ERROR_DETECT == STD_ON )
    // we select the precompile configuration
    //CanIsoTP_Handle.ptr2Config = &WeNeedGenericNameConfig;
  }
  else
  {
//    CanIsoTP_Handle.ptr2Config = ptr2Config;
//    for (CanIsoTP_RxPduType InitPduId = 0 ;InitPduId< CanIsoTP_Rx_unknownPdu;InitPduId++)
//    {
//
//    }

  }
  objectHandle.ModuleState = IsoTP_StatesType::IsoTP_ON;
  returnValue = E_OK;

/* USER CODE BEGIN CanFT2p0TL_Init 2 */

/* USER CODE END CanFT2p0TL_Init 2 */
//
return returnValue;
}

FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::Transmit( P2CONST(IsoTp_TxBufferType, AUTOMATIC, AUTOMATIC) ptr2TxBuffer )
{
  Std_ReturnType returnValue = E_NOT_OK;

  if (objectHandle.FlowControl.ProtocolStatus == IsoTP_RxTxStatus::IsoTP_SendIdle)
  {
    if ( (ptr2TxBuffer != NULL_PTR ) &&
         (ptr2TxBuffer->DataBufferSize > 1 ) &&
         (ptr2TxBuffer->p2TxData != NULL_PTR ) )
    {
      objectHandle.FlowControl.DataOffset = 0;
      objectHandle.p2TxBuffer = ptr2TxBuffer;

      if (objectHandle.p2TxBuffer->DataBufferSize < 8) {
          /* send single frame */
        returnValue = SendSingleFrame();
      }
      else
      {
        /* send multi-frame */
        returnValue = SendFirstFrame();

        /* init multi-frame control flags */
        if ( returnValue == E_OK )
        {
          objectHandle.FlowControl.RemainingBlockSize = 0;
          objectHandle.FlowControl.MinSeparationTime = 0;
          objectHandle.FlowControl.WaitForTransmitCounter = 0;
          objectHandle.FlowControl.stTimer = GetMillisecond();
          objectHandle.FlowControl.bsTimer = GetMillisecond() + objectConfig.ptr2Config->maxResponseTimeout;
          objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_OK;
          objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_SendInProgress;
        }
      } // end of buffer size test
    }
  }


  return returnValue;
}

/* ##### send functions ##### */

FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::SendFlowControl( CONST(IsoTP_FlowStatus, AUTOMATIC ) FlowStatus )
{

  Std_ReturnType returnValue = E_NOT_OK;

  if ( GetState() != IsoTP_StatesType::IsoTP_ON )
  {
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
    ISOTP_DET_REPORTERROR(ISOTP_E_UNINIT, TM_ISOTP_SEND_FLOWCONTROL_ID);
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
  }
  else
  {
    CanIsoTP_8ByteData TxData; // -> entspricht 8 byte
    ComStack_PduInfoType isoTpData = { .SduDataPtr = TxData.as.data_array.ptr, .SduLength = 3 };


    TxData.as.flow_control.type = IsoTP_FrameType::IsoTP_FlowControl;
    TxData.as.flow_control.FS = FlowStatus;
    TxData.as.flow_control.BS = objectConfig.ptr2Config->maxBlockSize;
    TxData.as.flow_control.STmin = objectConfig.ptr2Config->minSeparartionTime;

    objectHandle.FlowControl.RemainingBlockSize = objectConfig.ptr2Config->maxBlockSize;

    returnValue =((CanIf*)objectConfig.p2ControllerInterface)->Transmit(objectHandle.FlowControl.txIfPduName, &isoTpData);
  }

  return returnValue;
}


/** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
FUNC(Std_ReturnType, TM_ISOTP_CODE)  IsoTp::SendSingleFrame( void )
{
  Std_ReturnType returnValue = E_NOT_OK;
    if ( objectHandle.p2TxBuffer->p2TxData != NULL_PTR )
    {
      uint16_t dataSize = objectHandle.p2TxBuffer->DataBufferSize;
      if ( dataSize <= 7 )
      {
        ComStack_PduType txPduId = objectHandle.FlowControl.txIfPduName;

        CanIsoTP_8ByteData TxData; // -> entspricht 8 byte
        TxData.as.single_frame.type = IsoTP_FrameType::IsoTP_SingleFrame;
        TxData.as.single_frame.SF_DL = (uint8_t) dataSize;
          (void) memcpy(TxData.as.single_frame.data, objectHandle.p2TxBuffer->p2TxData, dataSize );
        uint16_t msgSize = objectHandle.p2TxBuffer->DataBufferSize + 1;
        ComStack_PduInfoType isoTpData = { .SduDataPtr = TxData.as.data_array.ptr, .SduLength = msgSize };
#ifdef ISO_TP_FRAME_PADDING

#endif
        returnValue = ((CanIf*)objectConfig.p2ControllerInterface)->Transmit(txPduId, &isoTpData);
        objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_SendIdle;
      }
      else
      {
        // handle error
      }
    }
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
    else
    {
      ISOTP_DET_REPORTERROR(ISOTP_E_PARAM_POINTER, TM_ISOTP_SEND_FLOWCONTROL_ID);
    }
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
  return returnValue;
}

/** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
FUNC(Std_ReturnType, TM_ISOTP_CODE)  IsoTp::SendFirstFrame( void )
{
  Std_ReturnType returnValue = E_NOT_OK;
  if ( objectHandle.p2TxBuffer->p2TxData != NULL_PTR )
  {
    CanIsoTP_8ByteData TxData; // -> entspricht 8 byte
    uint16_t dataSize = objectHandle.p2TxBuffer->DataBufferSize;
    if ( dataSize > 7 )
    {

      TxData.as.first_frame.type = IsoTP_FrameType::IsoTP_FirstFrame;
      TxData.as.first_frame.FF_DL_low = (uint8_t) dataSize;
      TxData.as.first_frame.FF_DL_high = (uint8_t) (0x0F & (dataSize >> 8));
      (void) memcpy(TxData.as.first_frame.data, objectHandle.p2TxBuffer->p2TxData, sizeof(TxData.as.first_frame.data) );
      uint16_t msgSize = sizeof(TxData);
      ComStack_PduInfoType isoTpData = { .SduDataPtr = TxData.as.data_array.ptr, .SduLength = msgSize };

    #ifdef ISO_TP_FRAME_PADDING

    #endif
      //returnValue = ((CanIf*)objectConfig.p2ControllerInterface)->Transmit(txPduId, &isoTpData);
      returnValue = ((CanIf*)objectConfig.p2ControllerInterface)->Transmit(objectHandle.FlowControl.txIfPduName, &isoTpData);
      if ( returnValue == E_OK)
      {
        objectHandle.FlowControl.DataOffset += sizeof(TxData.as.first_frame.data);
        objectHandle.FlowControl.SeqNumber = 1;
      }
    }
    else
    {
      // handle error
    }
  }
  return returnValue;
}

/** @brief this function gives the data stored inside the IsoTp object to the communication controller interface */
FUNC(Std_ReturnType, AUTOMATIC)  IsoTp::SendConsecutiveFrame( void )
{
  Std_ReturnType returnValue = E_NOT_OK;
  if ( objectHandle.p2TxBuffer->p2TxData != NULL_PTR )
  {
    uint16_t dataSize = objectHandle.p2TxBuffer->DataBufferSize;
    if ( dataSize < objectHandle.FlowControl.DataOffset )
    {
      /* here it is an error. This case should managed before calling SendConsecutiveFrame() */
      objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_SendError;
      objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_BUFFER_OVFLW;
      returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_OVERFLOW);
    }
    else
    {
      if ( dataSize > 7 )
      {
        ComStack_PduType txPduId = objectHandle.FlowControl.txIfPduName;

        CanIsoTP_8ByteData TxData; // -> entspricht 8 byte
        TxData.as.consecutive_frame.type = IsoTP_FrameType::IsoTP_ConsecutiveFrame;
        TxData.as.consecutive_frame.SN = objectHandle.FlowControl.SeqNumber;
        uint16_t data_length = dataSize - objectHandle.FlowControl.DataOffset;
        if (data_length > sizeof(TxData.as.consecutive_frame.data))
        {
          data_length = sizeof(TxData.as.consecutive_frame.data);
        }
        (void) memcpy(TxData.as.consecutive_frame.data, objectHandle.p2TxBuffer->p2TxData + objectHandle.FlowControl.DataOffset, data_length );

        uint16_t msgSize = data_length + 1;
        ComStack_PduInfoType isoTpData = { .SduDataPtr = TxData.as.data_array.ptr, .SduLength = msgSize };

#ifdef ISO_TP_FRAME_PADDING

#endif
        returnValue = ((CanIf*)objectConfig.p2ControllerInterface)->Transmit(txPduId, &isoTpData);
        if ( returnValue == E_OK)
        {
          objectHandle.FlowControl.DataOffset += data_length;
          if ( ++(objectHandle.FlowControl.SeqNumber) > 0x0F )
          {
            objectHandle.FlowControl.SeqNumber = 0;
          }
        }
      }
      else
      {

      }

    }
  }
  return returnValue;
}

/* ##### receive functions ##### */

FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::ReceiveFlowControl( P2CONST(CanIsoTP_8ByteData, AUTOMATIC, AUTOMATIC) ptr2FlowControlFrame )
{
  Std_ReturnType returnValue = E_NOT_OK;

  /* handle fc frame only when sending in progress  */
  if ( objectHandle.FlowControl.ProtocolStatus == IsoTP_RxTxStatus::IsoTP_SendInProgress)
  {
  /* refresh bs timer */
  //link->send_timer_bs = isotp_user_get_ms() + ISO_TP_DEFAULT_RESPONSE_TIMEOUT;
    switch (ptr2FlowControlFrame->as.flow_control.FS)
    {
      case ( IsoTP_FlowStatus::OVERFLOW ):
      {
        /* overflow */
        objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_SendError;
        objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_BUFFER_OVFLW;
        returnValue = E_OK;
        break;
      }
      case ( IsoTP_FlowStatus::WAIT ):
      {
        /* wait */
        objectHandle.FlowControl.WaitForTransmitCounter += 1;
        /* wait exceed allowed count */
        //if ( objectHandle.waitForTransmitCounter > objectConfig.ptr2Config->maxWaitForTransmitCylcles )
        if ( objectHandle.FlowControl.WaitForTransmitCounter > objectConfig.ptr2Config->maxWaitForTransmitCylcles )
        {
          objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_SendError;
          objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_WFT_OVRN;
        }
        returnValue = E_OK;
        break;
      }
      case ( IsoTP_FlowStatus::CONTINUE ):
      {
        /* permit send */
        if ( ptr2FlowControlFrame->as.flow_control.BS == 0)
        {
          objectHandle.FlowControl.RemainingBlockSize = ISOTP_INVALID_BS;
        }
        else
        {
          objectHandle.FlowControl.RemainingBlockSize = ptr2FlowControlFrame->as.flow_control.BS;
        }
        objectHandle.FlowControl.WaitForTransmitCounter = 0;
        objectHandle.FlowControl.MinSeparationTime = st_min_to_ms(ptr2FlowControlFrame->as.flow_control.STmin);
        returnValue = E_OK;
        break;
      }
      default:
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
        // should not happen
        ISOTP_DET_REPORTERROR(ISOTP_E_UNDEFINED, TM_ISOTP_RECEIVE_FLOWCONTROL_ID);
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
        break;
    }
  }
  else
  {
    returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_INPROGRESS);
  }
  return returnValue;
}

FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::ReceiveSingleFrame( P2CONST(CanIsoTP_8ByteData ,AUTOMATIC, AUTOMATIC) ptr2SingleFrame )
{
  Std_ReturnType returnValue = E_NOT_OK;
  if ( objectHandle.FlowControl.ProtocolStatus == IsoTP_RxTxStatus::IsoTP_ReceiveInProgress)
  {
    objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_UNEXP_PDU;
    returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_INPROGRESS);
  }
  else
  {
    objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_OK;

    if ( objectHandle.p2RxBuffer != NULL_PTR )
    {
      if ( ( ptr2SingleFrame->as.single_frame.SF_DL > 0) )
      {
        objectHandle.p2RxBuffer->DataReceivedSize = ptr2SingleFrame->as.single_frame.SF_DL;
        (void) memcpy(objectHandle.p2RxBuffer->p2RxData, ptr2SingleFrame->as.single_frame.data, objectHandle.p2RxBuffer->DataReceivedSize );
        returnValue = E_OK;
        objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_ReceiveFull; // why to full and not Idle ???
      }
      else
      {
        returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_LENGTH);
      }
    }
  }
  return returnValue;
}

FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::ReceiveFirstFrame( P2CONST(CanIsoTP_8ByteData ,AUTOMATIC, AUTOMATIC) ptr2FirstFrame )
{
  Std_ReturnType returnValue = E_NOT_OK;
  if ( objectHandle.FlowControl.ProtocolStatus == IsoTP_RxTxStatus::IsoTP_ReceiveInProgress)
  {
    objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_UNEXP_PDU;
    returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_INPROGRESS);
  }
  else
  {
    objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_OK;

    if ( objectHandle.p2RxBuffer != NULL_PTR )
    {
      uint16_t payloadSize = ptr2FirstFrame->as.first_frame.FF_DL_low;
      payloadSize += ( ptr2FirstFrame->as.first_frame.FF_DL_high<<8 );
      if ( payloadSize > objectHandle.p2RxBuffer->DataBufferSize )
      {
        objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_ReceiveIdle;
        objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_BUFFER_OVFLW;
        returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_OVERFLOW);
  #if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
        ISOTP_DET_REPORTERROR(ISOTP_E_BUFFER_OVERRUN, TM_ISOTP_SEND_FIRSTFRAME_ID);
  #endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
      }
      else
      {
        if ( payloadSize <= 7 )
        {
          returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_LENGTH);
        }
        else
        {
          (void) memcpy(objectHandle.p2RxBuffer->p2RxData, ptr2FirstFrame->as.first_frame.data, sizeof( ptr2FirstFrame->as.first_frame.data ) );
          objectHandle.p2RxBuffer->DataReceivedSize = payloadSize;
          objectHandle.FlowControl.DataOffset = sizeof(ptr2FirstFrame->as.first_frame.data);
          objectHandle.FlowControl.SeqNumber = 1;
          objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_ReceiveInProgress;
          /* refresh timer cs */
          objectHandle.FlowControl.crTimer = GetMillisecond() + objectConfig.ptr2Config->maxResponseTimeout;

          returnValue = E_OK;
        }
      }

    }

  }
  return returnValue;
}

FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::ReceiveConsecutiveFrame( P2CONST(CanIsoTP_8ByteData ,AUTOMATIC, AUTOMATIC) ptr2ConsFrame, CONST(uint8_t, AUTOMATIC) len )
{
  Std_ReturnType returnValue = E_NOT_OK;
  /* handle consecutive frame only when receiving in progress  */
  if ( objectHandle.FlowControl.ProtocolStatus != IsoTP_RxTxStatus::IsoTP_ReceiveInProgress)
  {
    objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_UNEXP_PDU;
    returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_INPROGRESS);
  }
  else if ( ptr2ConsFrame->as.consecutive_frame.SN != objectHandle.FlowControl.SeqNumber )
  {
    objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_WRONG_SN;
    objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_ReceiveIdle;
    returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_WRONG_SN);
  }
  else
  {
    if ( objectHandle.p2RxBuffer != NULL_PTR )
    {
      uint16_t remaining_bytes = objectHandle.p2RxBuffer->DataReceivedSize - objectHandle.FlowControl.DataOffset;

      if ( remaining_bytes > sizeof(ptr2ConsFrame->as.consecutive_frame.data) )
      {
        remaining_bytes = sizeof(ptr2ConsFrame->as.consecutive_frame.data);
      }

      // @todo we need a detection of padding

      //if ( remaining_bytes != len )
      if ( remaining_bytes > len )
      {
        returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_LENGTH);
      }
      else
      {
        (void) memcpy(objectHandle.p2RxBuffer->p2RxData + objectHandle.FlowControl.DataOffset, ptr2ConsFrame->as.consecutive_frame.data, remaining_bytes );

        objectHandle.FlowControl.DataOffset += remaining_bytes;
        if ( ++(objectHandle.FlowControl.SeqNumber) > 0x0F )
        {
          objectHandle.FlowControl.SeqNumber = 0;
        }

        /* refresh timer cs */
        objectHandle.FlowControl.crTimer = GetMillisecond() + objectConfig.ptr2Config->maxResponseTimeout;

        /* all segments are here */
        if (objectHandle.FlowControl.DataOffset >= objectHandle.p2RxBuffer->DataReceivedSize )
        {
          objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_ReceiveFull;
        }
        else
        {
          if ( --objectHandle.FlowControl.RemainingBlockSize == 0)
            {
            returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_LAST_OK);
            }
        }
        returnValue = E_OK;
      }
    }

  }


  return returnValue;
}

FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::Task( void )
{
  Std_ReturnType returnValue = E_NOT_OK;
  objectHandle.TaskTicks++;

  if ( objectHandle.ModuleState != IsoTP_StatesType::IsoTP_ON )
  {
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
    ISOTP_DET_REPORTERROR(ISOTP_E_UNINIT, CANISOTP_SCHEDULED_FUNC_ID);
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
  }
  else
  {
    if ( objectHandle.FlowControl.ProtocolStatus == IsoTP_RxTxStatus::IsoTP_SendInProgress )
    {
      /* send data if bs_remain is invalid or bs_remain large than zero */
      if ( ( ISOTP_INVALID_BS == objectHandle.FlowControl.RemainingBlockSize || objectHandle.FlowControl.RemainingBlockSize > 0) )
      {
        /* and if st_min is zero or go beyond interval time */
        if ( objectHandle.FlowControl.MinSeparationTime == 0 ||
            ( (objectHandle.FlowControl.MinSeparationTime != 0) && (IsoTpTimeAfter(GetMillisecond(), objectHandle.FlowControl.stTimer) ) )
            )
        {
          if ( SendConsecutiveFrame() == E_OK )
          {
            if (  ISOTP_INVALID_BS != objectHandle.FlowControl.RemainingBlockSize )
            {
              objectHandle.FlowControl.RemainingBlockSize -= 1;
            }
            objectHandle.FlowControl.bsTimer = GetMillisecond() + objectConfig.ptr2Config->maxResponseTimeout;
            objectHandle.FlowControl.stTimer = GetMillisecond() + objectHandle.FlowControl.MinSeparationTime;
            /* check if send finish */
            if ( objectHandle.p2TxBuffer->DataBufferSize <= objectHandle.FlowControl.DataOffset )
            {
              objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_SendIdle;
              objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_OK;
            }
          }
          else
          {
            objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_SendError;
          }
        } // end of test the separation time
      } // end of test the block size

      /* check timeout */
      if (IsoTpTimeAfter(GetMillisecond(), objectHandle.FlowControl.bsTimer))
      {
        objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_SendError;
        objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_TIMEOUT_BS;
      }
    }

    if ( objectHandle.FlowControl.ProtocolStatus == IsoTP_RxTxStatus::IsoTP_ReceiveInProgress )
    {
      /* check timeout */
      if (IsoTpTimeAfter(GetMillisecond(), objectHandle.FlowControl.bsTimer))
      {
        objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_ReceiveIdle;
        objectHandle.FlowControl.ProtocolResult = IsoTP_ProtocolResultType::RESULT_TIMEOUT_CR;
      }

    }


  returnValue = E_OK;
  }
return returnValue;
}

/* this function does the decoding on interrupt level */
FUNC(Std_ReturnType, TM_ISOTP_CODE) IsoTp::RxIndication(
    CONST(ComStack_PduType, AUTOMATIC) rxPduId,
    P2VAR(ComStack_CanMessageType, AUTOMATIC, AUTOMATIC) ptr2Sdu)
{
  Std_ReturnType returnValue = E_NOT_OK;

  if ( GetState() != IsoTP_StatesType::IsoTP_ON )
  {
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
    ISOTP_DET_REPORTERROR(ISOTP_E_UNINIT, TM_ISOTP_RXINDICATION_ID);
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
  }
  else
  {
    if ( ( ptr2Sdu != NULL_PTR ) &&
         (rxPduId < IsoTP_Rx_unknownPdu ) )
    {
      if ( ( ptr2Sdu->CanMsgHeader.DLC <2 ) ||
           ( ptr2Sdu->CanMsgHeader.DLC >8 ) )
      {
        //returnValue = NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_LENGTH);
        returnValue = E_NOT_OK;
      }
      else
      {
#if ( ISOTP_DECODE_LEVEL == DECODE_ON_INTERRUPT )
        CanIsoTP_8ByteData * msg = (CanIsoTP_8ByteData *)ptr2Sdu->ptr2Data;
        switch (msg->as.common.type)
        {
/* ####### Flow Control Frame ##### */
          case (IsoTP_FrameType::IsoTP_FlowControl):
          {
            if ( ptr2Sdu->CanMsgHeader.DLC >= 3 )
            {
              returnValue = ReceiveFlowControl((CanIsoTP_8ByteData*)ptr2Sdu->ptr2Data);
              // may be do error handling on development
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
              if ( returnValue != E_OK ) ISOTP_DET_REPORTERROR(ISOTP_E_INVALID_FRAME, TM_ISOTP_RXINDICATION_ID);
#else
              returnValue = E_OK; // report ok to clear the buffer
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
            }
            else
            {
            // may be do error handling on development
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
            ISOTP_DET_REPORTERROR(ISOTP_E_INVALID_FRAMELENGTH, TM_ISOTP_RXINDICATION_ID);
#else
            returnValue = E_OK; // report ok to clear the buffer
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
            }
            break;
          }
/* ####### Single Frame ##### */
          case (IsoTP_FrameType::IsoTP_SingleFrame):
          {
            returnValue = ReceiveSingleFrame((CanIsoTP_8ByteData*)ptr2Sdu->ptr2Data);
            if ( returnValue == E_OK )
            {
              objectHandle.FlowControl.ProtocolStatus = IsoTP_RxTxStatus::IsoTP_ReceiveFull;
            }
            break;
          }
/* ####### First Segment Frame ##### */
          case (IsoTP_FrameType::IsoTP_FirstFrame):
          {
            returnValue = ReceiveFirstFrame((CanIsoTP_8ByteData*)ptr2Sdu->ptr2Data);
            if ( returnValue == E_OK )
            {
              /** @warning this should removed from CAN Rx Interrupt !!!!
               * - call the SendFlowControl() */
              SendFlowControl(IsoTP_FlowStatus::CONTINUE);
            }
            else if ( returnValue == NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_E_OVERFLOW) )
            {
              /** @warning this should removed from CAN Rx Interrupt !!!!
               * - call the SendFlowControl() */
              SendFlowControl(IsoTP_FlowStatus::OVERFLOW);
              returnValue = E_OK; // report ok to clear the buffer
            }
            break;
          }
/* ####### Consecutive Segment Frame ##### */
          case (IsoTP_FrameType::IsoTP_ConsecutiveFrame):
          {
            returnValue = ReceiveConsecutiveFrame((CanIsoTP_8ByteData*)ptr2Sdu->ptr2Data, ptr2Sdu->CanMsgHeader.DLC - 1);
            if ( returnValue == NON_STD_RET_VALUE(IsoTp_ReturnErrorType::RET_LAST_OK) )
            {
              /** @warning this should removed from CAN Rx Interrupt !!!!
               * - call the SendFlowControl() */
              SendFlowControl(IsoTP_FlowStatus::CONTINUE);
            }
            // may be do error handling on development
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
            if ( returnValue != E_OK ) ISOTP_DET_REPORTERROR(ISOTP_E_INVALID_FRAME, TM_ISOTP_RXINDICATION_ID);
#else
            returnValue = E_OK; // report ok to clear the buffer
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
            break;
          }
          default:
/* ####### Unknown Frame ##### */
#if ( ISOTP_DEV_ERROR_DETECT == STD_ON )
            // should not happen
            ISOTP_DET_REPORTERROR(ISOTP_E_UNDEFINED, TM_ISOTP_RXINDICATION_ID);
#endif // ( ISOTP_DEV_ERROR_DETECT == STD_ON )
            break; // nothing to do

        }
/* ####### End Of Switch Frame Type ##### */
      }
#else

#endif // ( ISOTP_DECODE_LEVEL == DECODE_ON_INTERRUPT )
    }
  }
  return returnValue;
}

/* #### helper functions #### */

/* st_min to microsecond */
FUNC(uint8_t, AUTOMATIC) IsoTp::ms_to_st_min(uint8_t ms)
{
  uint8_t st_min;

  st_min = ms;
  if (st_min > 0x7F) {
      st_min = 0x7F;
  }

  return st_min;
}

/* st_min to msec  */
FUNC(uint8_t, AUTOMATIC) IsoTp::st_min_to_ms(uint8_t st_min)
{
  uint8_t ms;

  if (st_min >= 0xF1 && st_min <= 0xF9) {
      ms = 1;
  } else if (st_min <= 0x7F) {
      ms = st_min;
  } else {
      ms = 0;
  }

  return ms;
}

FUNC(uint32_t, AUTOMATIC) IsoTp::GetMillisecond( void )
{
  return objectHandle.TaskTicks;
}


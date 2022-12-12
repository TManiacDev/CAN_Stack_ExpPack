/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanFT2p0.cpp

 * @author TManiac
 * @date 14.08.2022
 * @version 
 *
 */
#include <CanFT2p0.h>

#include <CanFT2p0_Compiler_Cfg.h>

CanFT2p0::CanFT2p0() : TME_VersionInfo{CANFT2P0_MODULE_ID, CANFT2P0_VERSION, CANFT2P0_PATCH_VERSION}
{

}

CanFT2p0::CanFT2p0(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface) : TME_VersionInfo{CANFT2P0_MODULE_ID, CANFT2P0_VERSION, CANFT2P0_PATCH_VERSION}
{
  p2CanIf = p2CanInterface;
}

CanFT2p0::CanFT2p0(P2VAR(CanIf, AUTOMATIC, AUTOMATIC) p2CanInterface, CONST(CanIf_RxPduIdType, AUTOMATIC) rxPduName)
  : TME_VersionInfo{CANFT2P0_MODULE_ID, CANFT2P0_VERSION, CANFT2P0_PATCH_VERSION},
    rxPduName {rxPduName}
{
  p2CanIf = p2CanInterface;
}

CanFT2p0::~CanFT2p0()
{
  // TODO Auto-generated destructor stub
}


FUNC(Std_ReturnType, TM_CANFT_CODE) CanFT2p0::Init( P2CONST(CanFT2p0_CfgType, AUTOMATIC, AUTOMATIC) ptr2Config)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue = E_NOT_OK;

  if ( Handle.ModuleState != CanFT2p0_StatesType::CANFT_OFF )
  {
#if ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
    CANFT2P0_DET_REPORTERROR(CANFT2P0_E_UNINIT, CANFT2P0_INIT_ID);
#endif // ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
  }
  else
  {
    if (ptr2Config == NULL_PTR)
    {
#if ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
    CANFT2P0_DET_REPORTERROR(CANFT2P0_E_PARAM_CONFIG, CANFT2P0_INIT_ID);
#endif // ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
      ptr2Config = CanFT2p0_Default_Config;
    }
    Handle.ptr2Config = ptr2Config;
  /* USER CODE BEGIN CanFT2p0_Init 1 */
    Handle.ModuleState = CanFT2p0_StatesType::CANFT_ON;
    returnValue = E_OK;
  /* USER CODE END CanFT2p0_Init 1 */
  }
  /* USER CODE BEGIN CanFT2p0_Init 2 */

  /* USER CODE END CanFT2p0_Init 2 */
    //
    return returnValue;
}

FUNC( CanIf*, TM_CANFT_CODE) CanFT2p0::GetHwInterface(void)
{
  return p2CanIf;
}

FUNC(Std_ReturnType, TM_CANFT_CODE) CanFT2p0::RxIndication(
    CONST(ComStack_PduType, AUTOMATIC) rxPduId,
    P2VAR(ComStack_CanMessageType, AUTOMATIC, AUTOMATIC) ptr2Sdu)
{
  Std_ReturnType returnValue = E_NOT_OK;

  if ( GetState() != CanFT2p0_StatesType::CANFT_ON )
  {
#if ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
    CANISOTP_CANFT2P0_DET_REPORTERRORDET_REPORTERROR(CANFT2P0_E_UNINIT, CANFT2P0_SCHEDULED_FUNC_ID);
#endif // ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
  }
  else
  {
    if ( ( ptr2Sdu != NULL_PTR ) &&
         (rxPduId < (ComStack_PduType)FT2p0_RxPduIdType::FT2p0_Rx_unknownPdu ) )
    {
      if ( READ_FLAG(RxPduInfo[rxPduId].EventFlags,CANFT2P0_RXDATACOPY) != CANFT2P0_RXDATACOPY)
      {
        // we clear the flag before in case of interrupting this function
        // we should test the other flags
        CLEAR_FLAG(RxPduInfo[rxPduId].EventFlags, CANFT2P0_RXINDICATION);

        // we need to offset the destination buffer pointer [CanFt_RxPduInfo[RxPduId].RxIndicationCounter]
//        RxPduInfo[RxPduId].ptr2Message = MessagePtr;
//        CanFt_RxPduInfo[RxPduId].RxIndicationCounter++;
//        if (CanFt_RxPduInfo[RxPduId].RxIndicationCounter > CanFt_RxPduInfo[RxPduId].RxMaxCounter )
//        {
//          // Rücksetzen oder blockieren ist hier die Frage?
//        }

        returnValue = E_OK;

        SET_FLAG(RxPduInfo[rxPduId].EventFlags, CANFT2P0_RXINDICATION);

      }
    }
#if ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
    else
    {
      CANFT2P0_DET_REPORTERROR(CANFT2P0_E_PARAM_POINTER, CANFT2P0_RXINDICATION_ID);
    }
#endif // ( CANISOTP_DEV_ERROR_DETECT == STD_ON )
  }
  return returnValue;
}

FUNC(Std_ReturnType, TM_CANFT_CODE) CanFT2p0::TxIndication(
    //CONST(ComStack_PduType, AUTOMATIC) txPduId,
    CONST(CanIf_TxPduIdType, AUTOMATIC) txPduId,
    P2CONST(CanIf_PduInfoType, AUTOMATIC, AUTOMATIC) p2TxPdu )
{
  Std_ReturnType returnValue = E_NOT_OK;

  if ( Handle.ModuleState != CanFT2p0_StatesType::CANFT_ON )
  {
#if ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
    CANISOTP_CANFT2P0_DET_REPORTERRORDET_REPORTERROR(CANFT2P0_E_UNINIT, CANFT2P0_SCHEDULED_FUNC_ID);
#endif // ( CANFT2P0_DEV_ERROR_DETECT == STD_ON )
  }
  else
  {
    p2CanIf->Transmit(txPduId, p2TxPdu);
  }

  return returnValue;
}

FUNC(Std_ReturnType, TM_CANFT_CODE) CanFT2p0::DataCopy(
    CONST(uint8_t, AUTOMATIC) DataLength,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) DestPtr,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) SourcePtr)
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  if ( (DestPtr != NULL_PTR ) &&
       (SourcePtr != NULL_PTR) &&
       DataLength > 0 )
  {
    for ( uint8_t Byte = 0; Byte < DataLength; Byte++ )
    {
      // we should test this:  memmove(msg->payload, RxMessage.Data, 8);
      DestPtr[Byte] = SourcePtr[Byte];
    }
    ReturnValue = E_OK;
  }

  return ReturnValue;
}

FUNC(Std_ReturnType, TM_CANFT_CODE) CanFT2p0::DataReverseCopy(
    CONST(uint8_t, AUTOMATIC) DataLength,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) DestPtr,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) SourcePtr)
{
  Std_ReturnType ReturnValue = E_NOT_OK;
  if ( (DestPtr != NULL_PTR ) &&
       (SourcePtr != NULL_PTR) &&
       DataLength > 0 )
  {
    for ( uint8_t Byte = 0; Byte < DataLength; Byte++ )
    {
      // we should test this:  memmove(msg->payload, RxMessage.Data, 8);
      DestPtr[Byte] = SourcePtr[(DataLength-1) - Byte];
    }
    ReturnValue = E_OK;
  }

  return ReturnValue;
}

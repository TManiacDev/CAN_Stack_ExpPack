/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Uds.cpp

 * @author TManiac
 * @date 05.12.2022
 * @version 
 *
 */
 
#include "Uds.h"

#include <Uds_Compiler_cfg.h>


FUNC(BufReq_ReturnType, AUTOMATIC) UnifiedDiagnosticService::StartOfReception(
              CONST(Uds_RxPduType, AUTOMATIC) PduId,
              REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2PduInfo,
              CONST(PduLengthType,AUTOMATIC) TpSduLength,
              P2VAR(uint32_t, AUTOMATIC, AUTOMATIC) bufferSizePtr )
{
  BufReq_ReturnType returnValue = BufReq_ReturnType::BUFREQ_E_NOT_OK;


  return returnValue;
}

FUNC(BufReq_ReturnType, AUTOMATIC) UnifiedDiagnosticService::CopyRxData(
              CONST(Uds_RxPduType, AUTOMATIC) PduId,
              REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2PduInfo,
              P2VAR(uint32_t, AUTOMATIC, AUTOMATIC) bufferSizePtr )
{
  BufReq_ReturnType returnValue = BufReq_ReturnType::BUFREQ_E_NOT_OK;


  return returnValue;
}

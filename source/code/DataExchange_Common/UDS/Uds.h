/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Uds.h

 * @author TManiac
 * @date 05.12.2022
 * @version 
 *
 */
#ifndef TMANIACENGINEERING_COMMON_UDS_H_
#define TMANIACENGINEERING_COMMON_UDS_H_

 /** includes only documentation : */
#include "Uds_Doxy.h"

/** @addtogroup TM_Uds
 *  @{
 *  Uds.h */

/* Imported types */
//#include "Uds_Cfg.h"
#include "TMEVersionInfo.h" // sollte mit dem IsoTp kommen
#include "ComIf.h"

/** Indicates the the success on a call with request for buffer */
enum class BufReq_ReturnType
{
  /** Connection has been accepted.
   *  bufferSizePtr indicates the available receive buffer and reception is continued.
   *  If no buffer of the requested size is available, a receive buffer size of 0 shall be indicated by bufferSizePtr */
  BUFREQ_OK = E_OK,
  /** Connection has been rejected and reception is aborted.
   *  bufferSizePtr remains unchanged */
  BUFREQ_E_NOT_OK = E_NOT_OK,
  /** No buffer of the required length can be provided and reception is aborted.
   * bufferSizePtr remains unchanged. */
  BUFREQ_E_OVL
};

/** to give the info of a I-PDU
 * Pointer to a PduInfoType structure containing the payload data
   (without protocol information) and payload length of the first
   frame or single frame of a transport protocol I-PDU reception, and
   the MetaData related to this PDU. If neither first/single frame data
   nor MetaData are available, this parameter is set to NULL_PTR.
 * */
typedef struct
{
  /** payload data */
  P2VAR(uint8_t, AUTOMATIC, AUTOMATIC) ptr2Data;
  /** payload length of the first frame or single frame of a transport protocol I-PDU reception*/
  VAR(uint32_t, AUTOMATIC) DataLength;
  /** MetaData related to this PDU */
}Uds_PduInfoType;

/** @brief a class to serve unified diagnostic services
 *
 *  AUTOSAR includes this behavior to the Diagnostic Communication Manager (DCM)
 *  There is a PDU router between IsoTp and the DCM
 *  I start with a direct linkage of the UDS to the IsoTp */
class UnifiedDiagnosticService
    : public TME_VersionInfo
{
public:
  /** Standard constructor */
  UnifiedDiagnosticService();
  /** Standard destructor */
  virtual ~UnifiedDiagnosticService();

  /** @brief this is the callback on receiving a PDU
   *  @param[in] PduId This is the PDU-name inside the UDS module (I-PDU name)
   *  @param[in] ref2PduInfo Reference to the PduInfoType structure
   *  @param[in] TpSduLength Total length of the N-SDU (IsoTp-SDU) to be received
   *  @param[out] bufferSizePtr returns the available buffer size. This is be used to calculate the IsoTp BlockSize
   *  @return (see return type) */
  FUNC(BufReq_ReturnType, AUTOMATIC) StartOfReception(
                CONST(Uds_RxPduType, AUTOMATIC) PduId,
                REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2PduInfo,
                CONST(PduLengthType,AUTOMATIC) TpSduLength,
                P2VAR(uint32_t, AUTOMATIC, AUTOMATIC) bufferSizePtr );

  /** @brief this is the callback to copy received PDU
   *  @param[in] PduId This is the PDU-name inside the UDS module (I-PDU name)
   *  @param[in] ref2PduInfo Reference to the PduInfoType structure
   *  @param[out] bufferSizePtr returns the available buffer size. This is be used to calculate the IsoTp BlockSize
   *  @return (see return type) */
  FUNC(BufReq_ReturnType, AUTOMATIC) CopyRxData(
      CONST(Uds_RxPduType, AUTOMATIC) PduId,
      REF2CONST(ComStack_PduInfoType, AUTOMATIC) ref2PduInfo,
      P2VAR(uint32_t, AUTOMATIC, AUTOMATIC) bufferSizePtr);
};
/** @} */ // end of TM_Uds grouping

#endif /* TMANIACENGINEERING_COMMON_UDS_H_ */

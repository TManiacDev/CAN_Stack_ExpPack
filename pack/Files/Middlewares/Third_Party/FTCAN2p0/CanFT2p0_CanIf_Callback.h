/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * CanFT2p0_Callback.h

 * @author TManiac
 * @date 31.03.2022
 * @version 
 *
 */
#ifndef TARGET_CANFT2P0TL_CALLBACK_H_
#define TARGET_CANFT2P0TL_CALLBACK_H_

#include "CanFT2p0TL.h"

/** @brief Callback function to indicate on Rx interrupt
 *  @param[in] RxPduId   Name of the received message. It must be used the CanFT-Pdu-Name
 *  @param[in] MessagePtr   Pointer to the received data
 *  @return Std_ReturnType   success or failed
 *
 *  @sa CANFT2P0_RXINDICATION_ID*/
FUNC(Std_ReturnType, TM_CANFT_CODE) CanFT2p0_RxIndication(
    CONST(CanFT_RxPduIdType, AUTOMATIC) RxPduId,
    P2VAR(CanIf_MessageType, AUTOMATIC, AUTOMATIC) MessagePtr);

/** @brief service ID of the CanFT2p0_RxIndication() */
#define CANFT2P0_RXINDICATION_ID          (0x42)

FUNC(Std_ReturnType, TM_CANTP_CODE) CanFT2p0_DataCopy(
    CONST(uint8_t, AUTOMATIC) DataLength,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) DestPtr,
    P2VAR(uint8_t, AUTOMATIC, AUTOMATIC ) SourcePtr);

#endif /* TARGET_CANFT2P0TL_CALLBACK_H_ */

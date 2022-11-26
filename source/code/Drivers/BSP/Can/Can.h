/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Can.h

 * @author TManiac
 * @date Nov 19, 2022
 * @version 
 *
 */
#ifndef _CAN_H_
#define _CAN_H_

/* includes documentation : */
#include "Can_Doxy.h"

#include "Can_Cfg.h"

#include "ComIf.h"

/* ===================== Development Error Tracer (DET)  ========== */
/** @addtogroup TM_DET_NAMES
 *  @{ */
/** @defgroup TM_DET_CAN_NAMES Dev. Errors from CAN interface module */
/** @defgroup TM_DEM_CAN_NAMES Runtime Errors from CAN interface module */
/** @} */ // end of grouping TM_DET_NAMES

//#include "DevErrorTraver.h"

/** @addtogroup TM_DET_CAN_NAMES
 *  @{ */

/** @brief Development errors known by the Can interface module */
enum class Can_DevError
{
  /** @brief invalid pointer on API call */
  E_PARAM_POINTER = 0x01,
  /** @brief invalid handle on API call */
  E_PARAM_HANDLE = 0x02,
  /** @brief invalid length value on API call*/
  E_PARAM_DATA_LENGTH = 0x03,
  /** @brief invalid controller selected on API call */
  E_PARAM_CONTROLLER = 0x04,
  /** @brief API call without initialization */
  E_UNINIT = 0x05,
  /** @brief Transition isn't supported */
  E_TRANSITION = 0x06,
  /** @brief invalid baudrate value */
  E_PARAM_BAUDRATE = 0x07,
  /** @brief Module initialization has failed */
  E_INIT_FAILED = 0x09
};
/** @} */ // end of grouping TM_DET_CAN_NAMES

/** @addtogroup TM_DET_REPORT
 *  @{ */
/** @brief Macro to report dev errors from CAN interface module
 *  @details We use an expansion macro for development error reporting */
#if ( CAN_DEV_ERROR_DETECT == STD_ON )
  #define CAN_DET_REPORTERROR(ErrorId, ApiId) Det_ReportError(CAN_MODULE_ID, 0, (ApiId), (ErrorId))
#else
#include "main.h"
#define CAN_DET_REPORTERROR(ErrorId, ApiId) Error_Handler()
#endif // ( CAN_DEV_ERROR_DETECT == STD_ON )
/** @} */ // end of grouping TM_DET_REPORT

/* ************* Types ********** */
/** @addtogroup TM_Can_Types
 *  @{ */

/** @brief no RTR bit set
 *  @todo need refactor from CANIF_xx to CAN_xx */
#define CANIF_NO_RTR 0

/** @brief RTR bit set
 *  @todo need refactor from CANIF_xx to CAN_xx */
#define CANIF_USE_RTR 1

/** @brief use standard CAN ID
 *  @todo need refactor from CANIF_xx to CAN_xx */
#define CANIF_STDID 0

/** @brief use extended CAN ID
 *  @todo need refactor from CANIF_xx to CAN_xx */
#define CANIF_EXTID 1

/** @brief structure to hold the timing configuration of the bitrates */
typedef struct tCAN_BitrateConfig
{
  /** @brief clock prescaler */
  VAR(uint32_t, AUTOMATIC) Prescaler;
  /** @brief jump width for resync */
  VAR(uint32_t, AUTOMATIC) SyncJumpWidth;
  /** @brief time segment length before Abtastpunkt */
  VAR(uint32_t, AUTOMATIC) TimeSeg1;
  /** @brief time segment length after Abtastpunkt */
  VAR(uint32_t, AUTOMATIC) TimeSeg2;
}CAN_BitrateConfig;

typedef struct
{
  /** The service CanIf_RxIndication() is implemented in CanIf and called by CanDrv after a CAN L-PDU has been received. */
  void (* CanIf_RxIndication)(
      const ECU_CanController Controller,
      const ComStack_CanMsgHeader CanMsgHeader,
      const ComStack_PduInfoType* PduInfoPtr);
  /** The service CanIf_TxConfirmation() is implemented in CanIf and called
      by the CanDrv after the CAN L-PDU has been transmitted on the CAN network. */
  void (* CanIf_TxConfirmation) (
      ComStack_PduType CanTxPduId );
}CanIfCallbackType;

/** @} */ // end of grouping TM_Can_Types

/** @addtogroup TM_CanCfg_ParaCfg
 * @{ */

/** @brief to hold the handling parameters */
typedef struct
{
  /// hold the pointer to the hardware instance registers
  P2VAR(CAN_TypeDef, AUTOMATIC, AUTOMATIC ) Instance;
  /// setup the mode
  VAR(uint32_t, AUTOMATIC )     Mode;
  /// use time triggered mode
  VAR(FunctionalState, AUTOMATIC )     TTMode;
  /// use auto bus off function
  VAR(FunctionalState, AUTOMATIC )     AutoBusOff;
  /// use auto wake up function
  VAR(FunctionalState, AUTOMATIC )     AutoWakeUp;
  /// use auto retransmission
  VAR(FunctionalState, AUTOMATIC )     AutoRetransmission;
  /// will be the full fifo locked
  VAR(FunctionalState, AUTOMATIC )     ReceiveFifoLocked;
  /// switch internal time based transmission priority on
  VAR(FunctionalState, AUTOMATIC )     TransmitFifoPriority;
  /// initial Baudrate
  VAR(CanControllerBaudRateConfigID, AUTOMATIC )  InitBaudrate;
}CanControllerParaType;
/** @} */ // end of grouping TM_CanCfg_ParaCfg

/** @addtogroup TM_CanCfg_BaudCfg
 * @{ */

/** @brief Configuration parameters for a baudrate setting
 *
 *  @todo we should add a picture to explain the bit segments */
typedef struct
{
    /** @brief
     * we save the ID also in the configuration so we can check it */
    VAR(CanControllerBaudRateConfigID, AUTOMATIC )  CanControllerBaudrateID;
    /** @brief
     * Specifies the baudrate of the controller in kbps */
    VAR(uint16_t, AUTOMATIC )    CanControllerBaudRate;
    /** @brief
     * Specifies propagation delay in time quantas. */
    VAR(uint32_t, AUTOMATIC )    CanControllerPrescaler;
    /** @brief
     * Specifies scaling factor for CAN controller clock.
     * @details not used on STM32 bxCAN Controller */
    VAR(uint32_t, AUTOMATIC )    CanControllerPropSeg;
    /** @brief
     * Specifies phase segment 1 in time quantas */
    VAR(uint32_t, AUTOMATIC )    CanControllerSeg1;
    /** @brief
     * Specifies phase segment 2 in time quantas. */
    VAR(uint32_t, AUTOMATIC )    CanControllerSeg2;
    /** @brief
     * Specifies the synchronization jump width for the controller in time quantas  */
    VAR(uint32_t, AUTOMATIC )    CanControllerSyncJumpWidth;
}CanControllerBaudrateConfigType;
/** @} */ // end of grouping TM_CanCfg_BaudCfg

/** @addtogroup TM_CanCfg_HwFilter
 *  @brief parameters to ...
 *  @{ */

/** @brief This container is only valid for HRHs and contains the configuration (parameters) of one hardware filter. */
typedef struct
{
    /** @brief
     * Specifies (together with the filter mask) the identifiers range that passes the hardware filter. */
  VAR(uint32_t, AUTOMATIC ) CanHwFilterCode;
    /** @brief
     * Describes a mask for hardware-based filtering of CAN identifiers. */
  VAR(uint32_t, AUTOMATIC ) CanHwFilterMaskType;
}CanHwFilterType;

/** @} */ // end of grouping TM_CanCfg_HwFilter

/** @addtogroup TM_CanCfg_ConfigSet
    @{ */

/** @brief The structure of the overall configuration for the CAN */
typedef struct
{
  /** @brief Pointer to the baudrate configuration
   *
   *  we should use P2CONST macro */
  const CanControllerBaudrateConfigType * ptr2CanBaudrateConfigSet;
  /** @brief Pointer to the parameter configuration
   *
   *  we should use P2CONST macro */
  const CanControllerParaType * ptr2CanParaConfigSet;
  /** @brief pointer to filter configruation
   *
   *  we use the STM filter structure
   *  we should use P2CONST macro */
  const CAN_FilterTypeDef * ptr2CanFilterConfigSet;
}CanConfigType;

/** @} */ // end of grouping TM_CanCfg_ConfigSet

/* ********* API ************* */
/** @addtogroup TM_Can_Driver
 *  @{ */

/** @brief CAN module state machine is very simple
 *
 *  @details the controller holds there own state machine with CanControllerStates */
enum class CanDrvStates
{
  /** @brief the module is without configuration */
  Uninit,
  /** @brief the configuration is loaded */
  Ready
};

/** CAN Controller State Machine */
enum class CanControllerStates
{
  /** for hardware init we will be in */
  CS_Uninit = 0x00,
  /** This is the working state */
  CS_Started = 0x01,
  /** the CAN controller is ready to work, but does not participate on the bus */
  CS_Stopped = 0x02,
  /** the CAN controller is in sleep mode */
  CS_Sleep = 0x03
};

/** To hold the callback function pointers of the CanIf module
 *  @todo we should bring this inside the CanDrv object, we need it outside because of use in ISR  */
extern P2VAR(ComIf, TM_CAN_VAR, AUTOMATIC) ptr2ComIf;

/** @brief This pure virtual class holds the interface to work with derived driver classes.
 *
 * It will be managed like the AUTOSAR CAN-module  */
class Can
    : TME_VersionInfo
{
public:
  /** @brief Standard Constructor */
  Can();
  /** @brief basic destructor */
  virtual ~Can();

  /** @brief To get the the software module state */
  CanDrvStates GetDrvState(void) { return state; };

  /** @brief Switch driver state to ready */
  void SetDrvStateReady(void) { state = CanDrvStates::Ready; };
  /** @brief Switch driver state to uninit */
  void SetDrvStateUninit(void) { state = CanDrvStates::Uninit; };

  /** @brief The API for Init
   *  @sa CAN_INIT_ID */
  virtual Std_ReturnType Init(
      P2CONST(CanConfigType, AUTOMATIC, AUTOMATIC) ptr2Config = NULL_PTR,
      P2VAR(ComIf, TM_CAN_VAR, AUTOMATIC) ptr2ComIfObject = NULL_PTR ) = 0;
  /** @brief service ID of Can::Init() */
  #define CAN_INIT_ID 0x00

  /** @brief The API function for Deinit
   *  @sa CAN_DEINIT_ID */
  virtual void Deinit(void){};
  /** @brief service ID of CAN::Deinit()*/
  #define CAN_DEINIT_ID 0x10

  /** @brief The API to set baudrate on a controller
   *  @param[in] Controller    selects the controller
   *  @param[in] BaudrateId    selects the baudrate per name/id
   *  @sa CAN_SET_BAUDRATE_ID */
  virtual Std_ReturnType SetBaudrate(
      ECU_CanController Controller,
      CanControllerBaudRateConfigID BaudrateId )
        { return E_NOT_OK; };
  /** @brief service ID of Can::SetBaudrate() */
  #define CAN_SET_BAUDRATE_ID 0x0f

  /** @brief The API to set a controller mode
   *  @param[in] Controller    selects the controller
   *  @param[in] Transition    selects the transition per name/id
   *  @sa CAN_SET_CONTROLLER_MODE_ID */
  virtual Std_ReturnType SetControllerMode (
      ECU_CanController Controller,
      CanControllerStates Transition ) = 0;
  /** @brief service ID of SetControllerMode*/
  #define CAN_SET_CONTROLLER_MODE_ID 0x03

  /** @brief The API to disable all interrupts of a controller
   *  @sa CAN_DISABLE_CTRL_INT_ID */
  virtual void DisableControllerInterrupts(
      ECU_CanController Controller )
        {};
  /** @brief service ID of Can::DisableControllerInterrupts() */
  #define CAN_DISABLE_CTRL_INT_ID 0x04

  /** @brief The API to enable all interrupts of a controller
   *  @sa CAN_ENABLE_CTRL_INT_ID */
  virtual void EnableControllerInterrupts(
      ECU_CanController Controller)
        {};
  /** @brief service ID of Can::EnableControllerInterrupts() */
  #define CAN_ENABLE_CTRL_INT_ID 0x05

  /** @brief The API checks the controller for wakeup events
   *  @sa CAN_CHECK_WAKEUP_ID */
  virtual Std_ReturnType CheckWakeup(
      ECU_CanController Controller)
        { return E_NOT_OK; };
  /** @brief service ID of Can::CheckWakeup() */
  #define CAN_CHECK_WAKEUP_ID 0x0b

  /** @brief The API returns the error state of the CAN controller
   *  @param[in] Controller    selects the controller
   *  @param[out] ErrorStatePtr   gives a buffer where the error state should be stored
   *  @sa CAN_GET_CTRL_ERROR_STATE_ID */
  virtual Std_ReturnType GetControllerErrorState (
      ECU_CanController Controller,
      /*Can_ErrorStateType*/uint8_t* ErrorStatePtr )
        { return E_NOT_OK; };
  /** @brief service ID of Can::GetControllerErrorState() */
  #define CAN_GET_CTRL_ERROR_STATE_ID 0x11

  /** @brief The API returns the error state of the CAN controller
   *  @param[in] Controller    selects the controller
   *  @param[out] ControllerModePtr   gives a buffer where the controller mode should be stored
   *  @sa CAN_GET_CTRL_MODE_ID */
  virtual Std_ReturnType GetControllerMode (
      ECU_CanController Controller,
      CanControllerStates* ControllerModePtr )
        { return E_NOT_OK; };
  /** @brief service ID of Can::GetControllerMode() */
  #define CAN_GET_CTRL_MODE_ID 0x12

  /** @brief The API to write a message to tx FIFO
   *  @param[in] Controller   select the controller for tx
   *  @param[in] PduInfo      the CAN message to send */
  virtual Std_ReturnType Write(
      ECU_CanController Controller,
      P2CONST(ComStack_CanMessageType, AUTOMATIC,AUTOMATIC) ptr2PduInfo )
        { return E_NOT_OK; };
  /** @brief service ID of Can::Write() */
  #define CAN_WRITE_ID 0x06

  /** @brief configure a free hardware filter using bit masking
   *  @details set hardware filter
   *
   *  @attention
   *  This isn't the same like inside STM register access.
   *  But the function manages the correct use for STM HAL
   *  - bit 31 is IDE
   *  - bit 30 is RTR
   *
   *  @param[in] Controller   select the controller where the filter should be applied
   *  @param[in] FilterId     the selected filter bits
   *  @param[in] FilterMask   the filter mask to select valid filter bits
   *  @return                 E_OK if the filter is applied, E_NOT_OK no hardware filter free */
  virtual Std_ReturnType SetFilterByBitmask(
      VAR(ECU_CanController, AUTOMATIC) Controller,
      VAR(ComStack_CanIdType, AUTOMATIC) FilterId,
      VAR(ComStack_CanIdType, AUTOMATIC) FilterMask)
        { return E_NOT_OK; };

  /** @brief configure a free hardware filter using single CAN Id filtering
   *  @details set hardware filter
   *
   *  @param[in] Controller   select the controller where the filter should be applied
   *  @param[in] FilterId     the selected filter bits
   *  @return                 E_OK if the filter is applied, E_NOT_OK no hardware filter free */
  virtual Std_ReturnType SetFilterByCanId(
     VAR(ECU_CanController, AUTOMATIC) Controller,
     VAR(ComStack_CanIdType, AUTOMATIC) FilterId )
      { return E_NOT_OK; };

  /** @brief a task function to do something cycling */
  virtual void TxTask(void) {};

private:
  /** @brief the sate of the software module */
  CanDrvStates state = CanDrvStates::Uninit;
};

/** @} */ // end of grouping TM_Can_Driver

#endif /* _CAN_H_ */

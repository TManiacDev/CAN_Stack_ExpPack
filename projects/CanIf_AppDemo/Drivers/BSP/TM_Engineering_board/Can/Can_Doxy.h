/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Can_Doxy.h

 * @author TManiac
 * @date 20.11.2022
 * @version 
 *
 */
#ifndef _CAN_DOXY_H_
#define _CAN_DOXY_H_


/***************************************/
/******** CAN Hardware Module **********/
/** @defgroup TM_Can_Module CAN Module
 *  @brief to work with the STM HAL
 *  */

/** @addtogroup TM_Can_Module
 *  @{ */

/** @defgroup TM_CanCfg Configuration for CAN Hardware Module
 *  @brief  configuration for hardware dependencies */

/** @defgroup TM_Can_Types Type definitions for CAN Module
 *  @brief to handle hardware module access */

/** @defgroup TM_Can_Driver CAN driver
 *  @brief Driver classes to handle a specific CAN controller module */

/** @} */ // end of grouping TM_CAN

/********* CAN Module Config **************/
/** @addtogroup TM_CanCfg
 *  @{ */
/** @defgroup TM_CanCfg_General general behavior */
/** @defgroup TM_CanCfg_ConfigSet Hardware configuration container */

/** @} */ // end of grouping TM_CanCfg

/** @addtogroup TM_CanCfg_ConfigSet
 *  @brief  Collection of the configuration parameters of hardware relevant elements.<br>
 *            Access via pointer
 * @{ */
/** @defgroup TM_CanCfg_ParaCfg  the parameter for the CAN hardware configuration
 *  @brief This container contains configuration parameters of the CAN controller(s) that will be needed at start */
/** @defgroup TM_CanCfg_BaudCfg Baudrate configuration
 *  @brief This container contains bit timing related configuration parameters of the CAN controller(s) */
/** @defgroup TM_CanCfg_HwFilter Hardware Rx Filter configuration
 *  @brief This container contains configuration parameters for the hardware filter */
/** @} */ // end of grouping TM_CanCfg_ConfigSet

/******************************************/





#endif /* _CAN_DOXY_H_ */

/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Can_Compiler_Cfg.h

 * @author TManiac
 * @date 20.11.2022
 * @version 
 *
 */
#ifndef _CAN_COMPILER_CFG_H_
#define _CANIF_COMPILER_CFG_H_


/** to place the runtime variables of the CAN on memory */
#define TM_CAN_USER_VAR     __attribute__((section(".tm_data_can_var_preinit")))
/** to place the configuration data of the CAN on memory */
#define TM_CAN_CONFIG_DATA  __attribute__((section(".tm_driver_config_can")))
/** to place the code of the CAN on memory */
#define TM_CAN_CODE         __attribute__((section(".tm_driver_code_can")))



/** @file
This area musst be extended with implementiation of every new modul
*/


/** Standard memory class for low level code */
#define TM_CAN_CODE	     __attribute__((section(".tm_driver_code_can")))

#define TM_CAN_ISR_CODE      __attribute__((section(".tm_driver_isr_can")))

/** standard memory class for global or static constants */
#define TM_CAN_CONFIG_DATA	    __attribute__((section(".tm_driver_config_can")))

/** Standard memory class for low level variables initialized on every reset */
#define TM_CAN_VAR	          __attribute__((section(".tm_data_can_var_preinit")))

/** Standard memory class for never intialized low level variables */
#define CAN_VAR_NOINIT	STD_VAR_NOINIT /* empty */

/** standard memory class for power on reset initialized low level variables */
#define CAN_VAR_POWERON_INIT	STD_VAR_POWERON_INIT /* empty */

/** standard memory class for special handling variables, like bitwise access, frequently used, high number of use points in code (only allowed for BSW) */
#define CAN_VAR_FAST	STD_VAR_FAST /* empty */

/** Standard memory class for application code*/
#define CAN_APPL_CODE	STD_APPL_CODE /* empty */

/**  Standard memory class for application constants */
#define CAN_APPL_CONST	STD_APPL_CONST /* empty */

/**  Standard memory class for application variables */
#define CAN_APPL_DATA	STD_APPL_DATA /* empty */


#endif /* _CANIF_COMPILER_CFG_H_ */

/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * ComIf_Compiler_Cfg.h

 * @author TManiac
 * @date 15.10.2022
 * @version 
 *
 */
#ifndef BSP_TM_ENGINEERING_BOARD_COMIF_COMIF_COMPILER_CFG_H_
#define BSP_TM_ENGINEERING_BOARD_COMIF_COMIF_COMPILER_CFG_H_


/** Standard memory class for low level code */
#define TM_COMIF_CODE      __attribute__((section(".tm_driver_code_comif")))


#endif /* BSP_TM_ENGINEERING_BOARD_COMIF_COMIF_COMPILER_CFG_H_ */

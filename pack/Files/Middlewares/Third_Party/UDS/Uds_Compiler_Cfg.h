/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * Uds_Compiler_Cfg.h

 * @author TManiac
 * @date 05.12.2022
 * @version 
 *
 */
#ifndef TMANIACENGINEERING_COMMON_UDS_COMPILER_CFG_H_
#define TMANIACENGINEERING_COMMON_UDS_COMPILER_CFG_H_


/** Standard memory class for low level code */
#define TM_UDS_CODE_SECTION      __attribute__((section(".tm_code_isotp")))

/** standard memory class for global or static constants */
#define TM_UDS_CONST_SECTION    __attribute__((section(".tm_config_isotp")))


#endif /* TMANIACENGINEERING_COMMON_UDS_COMPILER_CFG_H_ */

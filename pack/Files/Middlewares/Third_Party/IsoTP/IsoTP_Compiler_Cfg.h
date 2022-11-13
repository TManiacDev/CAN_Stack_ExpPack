/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * IsoTP_Compiler_Cfg.h

 * @author TManiac
 * @date 15.10.2022
 * @version 
 *
 */
#ifndef THIRD_PARTY_TM_ENGINEERING_DATAEXCHANGE_COMMON_ISOTP_ISOTP_COMPILER_CFG_H_
#define THIRD_PARTY_TM_ENGINEERING_DATAEXCHANGE_COMMON_ISOTP_ISOTP_COMPILER_CFG_H_


/** Standard memory class for low level code */
#define TM_ISOTP_CODE      __attribute__((section(".tm_code_isotp")))

/** standard memory class for global or static constants */
#define TM_ISOTP_CONST    __attribute__((section(".tm_config_isotp")))


#endif /* THIRD_PARTY_TM_ENGINEERING_DATAEXCHANGE_COMMON_ISOTP_ISOTP_COMPILER_CFG_H_ */

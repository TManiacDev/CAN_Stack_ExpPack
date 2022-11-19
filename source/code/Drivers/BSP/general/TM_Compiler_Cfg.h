/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * AUTOSAR Compiler specific configurable definitions <br/>
 * based on AUTOSAR_SWS_CompilerAbstraction.pdf V2.0.2 .
 * 
 * $Author: jens.raethe $
 * $Source: [HAL]/general/Compiler_Cfg.h $
 * $Date: 2009/09/16 13:09:03 $
 * $Revision: 1.1 $
 * 
 */
  
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/* module dependend memory classes */

/*  <MSN_MemoryAndPointerClasses> [each per module] */ 
/*    <MSN_CODE> [1] (define eg. near, far) */
/*    <MSN_VAR_NOINIT> [1] (define eg. near, far) */
/*    <MSN_VAR_POWERON_INIT> [1] (define eg. near, far) */
/*    <MSN_VAR_FAST> [1] (define eg. near, far) */
/*    <MSN_VAR> [1] (define eg. near, far) */
/*    <MSN_CONST> [1] (define eg. page, section) */
/*    <MSN_APPL_DATA> [1] (define eg. page, section) */
/*    <MSN_APPL_CONST> [1] (define eg. page, section) */
/*    <MSN_APPL_CODE> [1] (define eg. page, section) */

/** to place the code of the DET on memory */
#define DET_CODE __attribute__((section(".det_code")))
/** to place the data of the DET on memory */
#define DET_DATA __attribute__((section(".det_data")))

/** Standard memory class for low level code */
#define STD_CODE /* empty */

/** standard memory class for global or static constants */
#define STD_CONST /* empty */

/** Standard memory class for low level variables initialized on every reset */
#define STD_VAR /* empty */

/** Standard memory class for never intialized low level variables */
#define STD_VAR_NOINIT /* empty */

/** standard memory class for power on reset initialized low level variables */
#define STD_VAR_POWERON_INIT /* empty */

/** standard memory class for special handling variables, like bitwise access, frequently used, high number of use points in code (only allowed for BSW) */
#define STD_VAR_FAST /* empty */

/** Standard memory class for application code*/
#define STD_APPL_CODE /* empty */

/**  Standard memory class for application constants */
#define STD_APPL_CONST /* empty */

/**  Standard memory class for application variables */
#define STD_APPL_DATA /* empty */


/** to place the test routine code of the CAN on memory */
#define TM_TEST_CODE __attribute__((section(".test_code")))


#endif /* COMPILER_CFG_H */

/*-------------------------------------------------------------------------*/
/* END OF FILE                                                             */
/*-------------------------------------------------------------------------*/

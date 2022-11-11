/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * AUTOSAR Compiler specific definitions <br/>
 * based on AUTOSAR_SWS_CompilerAbstraction.pdf V2.0.2 .
 * includes the AUTOSAR Compiler Configuration header file
 * 
 * $Author: jens.raethe $
 * $Source: [HAL]/general/Compiler.h $
 * $Date: 2009/09/16 13:09:03 $
 * $Revision: 1.1 $
 * 
 */

#ifndef COMPILER_H
#define COMPILER_H
 
#include "TM_Compiler_Cfg.h"

/* If necessary, compiler-specific definitions can be made here */
/* Right now this is just a dummy */

/* definitions (chapter 9.1)*/
/** refers to COMPILER046. */
#define AUTOMATIC  /*!< empty */

/** not in AUTOSAR, only to use as empty space */
#define NO_LOCATION /*!< empty */

/** refers to COMPILER059. */
#define TYPEDEF /*!< empty */

/** refers to COMPILER049. */
#define STATIC /*!< empty for Tasking Compiler */

#ifdef __cplusplus
/** refers to COMPILER051. */
#define NULL_PTR  (nullptr) //!<@todo check NULL_PTR definition
#else
/** refers to COMPILER051. */
#define NULL_PTR  ((void*) 0) //!<@todo check NULL_PTR definition
#endif

/** refers to COMPILER057. */
#define INLINE inline

/* macros for functions (chapter 9.2) */

/** refers to COMPILER001 and COMPILER058. */
#define FUNC(rettype, memclass)  memclass rettype
//#define FUNC(rettype, memclass)   rettype  memclass

#define ISR_FUNC( memclass)  memclass void

#define SYS_FUNC(memclass) memclass

/* macros for pointers (chapter 9.3) */

/** refers to COMPILER006.
    use &lt;MSN&gt;_APPL_DATA and &lt;MSN&gt;_VAR_FAST definition */
#define P2VAR(ptrtype, memclass, ptrclass)   ptrtype *

/** on c++ we can use reference pointers */
#define REF2VAR(reftype, memclass)  reftype &

/** on c++ we can use reference pointers */
#define REF2CONST(reftype, memclass)  const reftype &

/** refers to COMPILER013.
    use &lt;MSN&gt;_APPL_CONST and &lt;MSN&gt;_VAR definition */
#define P2CONST(ptrtype, memclass, ptrclass)  const ptrtype *

/** refers to COMPILER031.
    use &lt;MSN&gt;_APPL_DATA and &lt;MSN&gt;_VAR definition */
#define CONSTP2VAR(ptrtype, memclass, ptrclass) ptrtype * const

/** refers to COMPILER032.
    use &lt;MSN&gt;_APPL_DATA and &lt;MSN&gt;_CONST definition */
#define CONSTP2CONST(ptrtype, memclass, ptrclass)  const ptrtype * const

/** refers to COMPILER039.
    use &lt;MSN&gt;_APPL_CODE */
#define P2FUNC(rettype, ptrclass, fctname)  rettype (* fctname)

/* Keywords for constants */

/** refers to COMPILER023.
    use &lt;MSN&gt;_CONST */
#define CONST(consttype, memclass)   const consttype memclass

#define EXTERN_CONST(consttype, memclass)  extern const consttype memclass

/** refers to COMPILER026.
    use &lt;MSN&gt;_VAR_FAST definition */
#define VAR(vartype, memclass)   vartype memclass

/** macro to map a 32bit value to 4 CAN bytes [00.00.00.FF] */
#define ui32ToByte0(ui32) (tm_uint8)ui32&0x000000FF
/** macro to map a 32bit value to 4 CAN bytes [00.00.FF.00] */
#define ui32ToByte1(ui32) (tm_uint8)(ui32>>8)
/** macro to map a 32bit value to 4 CAN bytes [00.FF.00.00] */
#define ui32ToByte2(ui32) (tm_uint8)(ui32>>16)
/** macro to map a 32bit value to 4 CAN bytes [FF.00.00.00] */
#define ui32ToByte3(ui32) (tm_uint8)(ui32>>24)

/** macro to map a 16bit value to 2 CAN bytes [00.FF] */
#define ui16ToByte0(ui16) (tm_uint8)ui16&0x00FF
/** macro to map a 16bit value to 2 CAN bytes [FF.00] */
#define ui16ToByte1(ui16) (tm_uint8)(ui16>>8)

/** macro to set a flag or bit inside a var */
#define SET_FLAG(REG, FLAG)     ((REG) |= (FLAG))

/** macro to clear a flag or bit inside a var */
#define CLEAR_FLAG(REG, FLAG)   ((REG) &= ~(FLAG))

/** macro to read a flag or bit inside a var */
#define READ_FLAG(REG, FLAG)    ((REG) & (FLAG))

#endif /* COMPILER_H */

/*-------------------------------------------------------------------------*/
/* END OF FILE                                                             */
/*-------------------------------------------------------------------------*/

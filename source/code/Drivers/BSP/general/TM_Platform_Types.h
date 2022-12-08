/*--------------------------------------------------------------------------*/
/*                    TManiac Software Architecture                         */
/*                              Jens Raethe                                 */
/*                             www.tmaniac.de                               */
/*--------------------------------------------------------------------------*/

/**
 * @file
 * TMSA platform types
 * highest level header file
 * defining bit- and byte order for a certain platform
 * as well as basic types like uint8
 * 
 * $Author: jens.raethe $
 * $Source: [HAL]/general/Platform_Types.h $
 * $Date: 2008/05/16 13:09:03 $
 * $Revision: 1.1 $
 * $Hint:   This is no AUTOSAR architecture. 
 *          There are many ideas from it, because I had worked with it before.
 *
 */

#ifndef TMSA_PLATFORM_TYPES_H
#define TMSA_PLATFORM_TYPES_H

/* to use compiler specific names */
// #include <stdbool.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"

/** @brief 8bit CPU */
#define CPU_TYPE_8	8
/** @brief 16bit CPU */
#define CPU_TYPE_16	16
/** @brief 32bit CPU */
#define CPU_TYPE_32	32
/** @brief 64bit CPU */
#define CPU_TYPE_64	64

/** @brief MSB first on CPU registers */
#define MSB_FIRST	0
/** @brief LSB first on CPU registers */
#define LSB_FIRST	1

/** @brief high byte first on CPU registers */
#define HIGH_BYTE_FIRST	0
/** @brief low byte first on CPU registers */
#define LOW_BYTE_FIRST	1


/** @brief used CPU */
#define CPU_TYPE CPU_TYPE_32	/* 32-bit-uC */

/** @brief used CPU */
#define CPU_BIT_ORDER	  LSB_FIRST       /* ? MSB_FIRST or LSB_FIRST */
/** @brief used CPU */
#define CPU_BYTE_ORDER	LOW_BYTE_FIRST /* ? HIGH_BYTE_FIRST or LOW_BYTE_FIRST */

/** @todo there is a boolean definition, AUTOSAR need pointer access*/
typedef unsigned char tm_boolean;
#ifndef TRUE	/* in case the compiler has built in support of booleans */
/** used TRUE */
	#define TRUE	(tm_boolean)1 /* Better: ((boolean) 1), but for some reason this does not work */
#endif
	
#ifndef FALSE	/* in case the compiler has built in support of booleans */
/** used FALSE */
	#define FALSE	(tm_boolean)0
#endif

/** used unsigned 8bit value */
typedef unsigned 	char 		  tm_uint8;	  
/** used unsigned 16bit value */
typedef unsigned 	short  		tm_uint16;
/** used unsigned 32bit value */
typedef unsigned 	long 		  tm_uint32;
/** used unsigned 64bit value */
typedef unsigned 	long long tm_uint64;
/** used signed 8bit value */
typedef signed 	  char      tm_sint8;
/** used signed 16bit value */
typedef signed 	  short     tm_sint16;
/** used signed 32bit value */
typedef signed 	  long      tm_sint32;
/** used signed 64bit value */
typedef signed    long long tm_sint64;

/** used unsigned 8bit optimized value */
typedef unsigned 	short     tm_uint8_least;
/** used unsigned 16bit optimized value */
typedef unsigned 	short     tm_uint16_least;
/** used unsigned 32bit optimized value */
typedef unsigned 	long      tm_uint32_least;
/** used signed 8bit optimized value */
typedef signed 	  short     tm_sint8_least;
/** used signed 16bit optimized value */
typedef signed 	  short     tm_sint16_least;
/** used signed 32bit optimized value */
typedef signed    long      tm_sint32_least;

/** used 32bit float */
typedef float               tm_float32;
/** used 64bit float */
typedef double              tm_float64;

/** used void pointer */
typedef void*               tm_VoidPtr;
/** used const void pointer */
typedef const void*         tm_ConstVoidPtr;

/** just to use it on init */
#define INVALID_PDUID       (0xF0F0F0F0)

#endif /* TMSA_PLATFORM_TYPES_H */
/*-------------------------------------------------------------------------*/
/* END OF FILE                                                             */
/*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * AUTOSAR standard types <br/>
 * based on AUTOSAR_SWS_StandardTypes.pdf V1.2.1 .
 * includes the AUTOSAR platform types header file <br/>
 * includes the compiler specific header file

 * $Author: jens.raethe $
 * $Source: [HAL]/general/Std_Types.h $
 * $Date: 2008/05/16 13:09:03 $
 * $Revision: 1.1 $
 *
 */
  
#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "TM_Platform_Types.h"
#include "TM_Compiler.h"

/** @brief we us the 'T' for the vendor Id ;-) */
#define TM_VENDOR_ID           (*(uint16_t*)"TM")    /* hex: 'TM' */

/** Standard return type for functions */
typedef tm_sint16 Std_ReturnType; /* E_OK and E_NOT_OK */

/** we do a automatic casting */
#define NON_STD_RET_VALUE(retValue)   (tm_sint16)retValue

#ifndef STATUSTYPEDEFINED
/** to avoid name clashes and redefinition problems with OSEK */
	#define STATUSTYPEDEFINED
/** @brief function could do the shop */
	#define E_OK	0
/** for OSEK compliance */
	typedef unsigned char StatusType;
#endif

/** @brief function failed */
#define E_NOT_OK	1

/** @brief Physical state 5V or 3.3 V */
#define STD_HIGH	1
/** @brief Physical state 0V */
#define STD_LOW		0

/** @brief Logical state active */
#define STD_ACTIVE	1
/** @brief Logical State idle */
#define STD_IDLE	0

/** @brief to switch a API support on */
#define STD_ON	1
/** @brief to switch a API support off */
#define STD_OFF	0


/** @brief to hide unused parts in unions, structs and so on */
#define _UNUSED_VAR_  0

#ifdef __cplusplus
#include "TMEVersionInfo.h"
#else

/** @brief structure for access on version info on runtime */
typedef struct
{
  /** @brief the vendor Id of the used module */
	tm_uint16	vendorID;
	/** @brief the Id of the used module */
	tm_uint16	moduleID;
	/** @brief we use the instance to distinguish between development and runtime */
	tm_uint8	instanceID;
	/** @brief version Id */
	tm_uint8	sw_major_version;
	/** @brief patch version */
	tm_uint8	sw_patch_version;
} TM_VersionInfoType;

#endif // end of __cplusplus

#endif /* STD_TYPES_H */

/*-------------------------------------------------------------------------*/
/* END OF FILE                                                             */
/*-------------------------------------------------------------------------*/


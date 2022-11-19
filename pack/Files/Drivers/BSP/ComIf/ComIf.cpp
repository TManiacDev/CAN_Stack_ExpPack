/*-------------------------------------------------------------------------*/
/*                              Jens Raethe                                */
/*                             www.tmaniac.de                              */
/*-------------------------------------------------------------------------*/

/**
 * @file
 * ComIf.cpp

 * @author TManiac
 * @date 08.10.2022
 * @version 
 *
 */
#include "ComIf.h"

SYS_FUNC( TM_COMIF_CODE ) ComIf::ComIf()
{
  // TODO Auto-generated constructor stub

}

SYS_FUNC( TM_COMIF_CODE ) ComIf::ComIf( VAR(ComInterfaceType, AUTOMATIC) ComIfType ) : connectedComInterface {ComIfType}
{
  // TODO Auto-generated constructor stub

}

SYS_FUNC( TM_COMIF_CODE ) ComIf::~ComIf() {
  // TODO Auto-generated destructor stub
}


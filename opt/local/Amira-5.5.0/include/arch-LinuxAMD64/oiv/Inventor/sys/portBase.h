/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _INVENTOR_PORT_BASE_H
#define  _INVENTOR_PORT_BASE_H

#ifdef _WIN32
#  if defined(_DEBUG)
#    define __INVENTORBASEDLL "InventorBaseD.dll"
#    define __INVENTORBASELIB "InventorBaseD.lib"
#  else
#    define __INVENTORBASEDLL "InventorBase.dll"
#    define __INVENTORBASELIB "InventorBase.lib"
#  endif
#endif

#endif // _INVENTOR_PORT_BASE_H

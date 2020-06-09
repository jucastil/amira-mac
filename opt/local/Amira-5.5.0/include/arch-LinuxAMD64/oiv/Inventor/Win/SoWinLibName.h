/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef __SO_WIN_LIB_NAME_H
#define __SO_WIN_LIB_NAME_H
// Name of Inventor Windows library

#if defined(_WIN32)
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    ifndef INV_COMPONENT_LIB
#      define INV_COMPONENT_LIB "InventorWinD"
#    endif
#    define __INVWDLL "InventorWinD.dll"
#    define __INVWLIB "InventorWinD.lib"
#    define __INVRDLL "InventorRD.dll"
#  else
#    ifndef INV_COMPONENT_LIB
#      define INV_COMPONENT_LIB "InventorWin"
#    endif
#    define __INVWDLL "InventorWin.dll"
#    define __INVWLIB "InventorWin.lib"
#    define __INVRDLL "InventorR.dll"
#  endif
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoInventorWin, __INVWDLL)

#endif

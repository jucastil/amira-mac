/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef __SO_QT_LIB_NAME_H
#define __SO_QT_LIB_NAME_H

// Name of Inventor QT library

#if defined(_WIN32)
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    ifndef INV_COMPONENT_LIB
#      define INV_COMPONENT_LIB "InventorQtD"
#    endif
#    define __INVQTDLL "InventorQt4D.dll"
#    define __INVQTLIB "InventorQt4D.lib"
#    define __INVRDLL "InventorRD.dll"
#  else
#    ifndef INV_COMPONENT_LIB
#      define INV_COMPONENT_LIB "InventorQt"
#    endif
#    define __INVQTDLL "InventorQt4.dll"
#    define __INVQTLIB "InventorQt4.lib"
#    define __INVRDLL "InventorR.dll"
#  endif
#else
#  define __INVQTDLL "libInventorQt4"
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoInventorQt4, __INVQTDLL)

#endif

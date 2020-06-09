/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _INVENTOR_PORT_IMAGE_H
#define  _INVENTOR_PORT_IMAGE_H

#ifdef _WIN32
#  if defined(_DEBUG)
#    define __INVENTORIMAGEDLL "InventorImageD.dll"
#    define __INVENTORIMAGELIB "InventorImageD.lib"
#  else
#    define __INVENTORIMAGEDLL "InventorImage.dll"
#    define __INVENTORIMAGELIB "InventorImage.lib"
#  endif
#endif

#endif // _INVENTOR_PORT_IMAGE_H

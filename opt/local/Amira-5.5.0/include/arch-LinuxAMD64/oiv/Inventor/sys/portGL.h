/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _INVENTOR_GL_
#define  _INVENTOR_GL_

#ifdef _WIN32
#  if defined(_DEBUG)
#    define __INVENTORGLDLL "InventorGLD.dll"
#    define __INVENTORGLLIB "InventorGLD.lib"
#  else
#    define __INVENTORGLDLL "InventorGL.dll"
#    define __INVENTORGLLIB "InventorGL.lib"
#  endif
#else
#define __INVENTORGLDLL "libInventorGL"
#endif


#endif // _INVENTOR_GL_

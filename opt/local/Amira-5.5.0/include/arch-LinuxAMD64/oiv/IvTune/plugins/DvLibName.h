/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2010)
**=======================================================================*/
#ifndef DV_LIB_NAME_H
#define DV_LIB_NAME_H

// Name of Demo Viewer library

#if defined(_WIN32)
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __DEMOVDLL "DemoViewerAPID.dll"
#    define __DEMOVLIB "DemoViewerAPID.lib"
#  else
#    define __DEMOVDLL "DemoViewerAPI.dll"
#    define __DEMOVLIB "DemoViewerAPI.lib"
#  endif
#else
#  define __DEMOVDLL "libDemoViewerAPI"
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoDemoViewer, __DEMOVDLL)

#endif // DV_LIB_NAME_H

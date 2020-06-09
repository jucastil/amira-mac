/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#include <SoVersion.h>

#ifdef _WIN32
# ifdef SOQT
#  if defined(_DEBUG)
#    ifndef MESHVIZ_COMPONENT_LIB
#      define MESHVIZ_COMPONENT_LIB "MeshVizQtD"
#    endif
#    define __MESHVIZWDLL "MeshVizQtD.dll"
#    define __MESHVIZWLIB "MeshVizQtD.lib"
#  else
#    ifndef MESHVIZ_COMPONENT_LIB
#      define MESHVIZ_COMPONENT_LIB "MeshVizQt"
#    endif
#    define __MESHVIZWDLL "MeshVizQt.dll"
#    define __MESHVIZWLIB "MeshVizQt.lib"
#  endif
# elif defined(SOWX)
#  if defined(_DEBUG)
#    ifndef MESHVIZ_COMPONENT_LIB
#      define MESHVIZ_COMPONENT_LIB "MeshVizWxD"
#    endif
#    define __MESHVIZWDLL "MeshVizWxD.dll"
#    define __MESHVIZWLIB "MeshVizWxD.lib"
#  else
#    ifndef MESHVIZ_COMPONENT_LIB
#      define MESHVIZ_COMPONENT_LIB "MeshVizWx"
#    endif
#    define __MESHVIZWDLL "MeshVizWx.dll"
#    define __MESHVIZWLIB "MeshVizWx.lib"
#  endif
# else
#  if defined(_DEBUG)
#    ifndef MESHVIZ_COMPONENT_LIB
#      define MESHVIZ_COMPONENT_LIB "MeshVizWinD"
#    endif
#    define __MESHVIZWDLL "MeshVizWinD.dll"
#    define __MESHVIZWLIB "MeshVizWinD.lib"
#  else
#    ifndef MESHVIZ_COMPONENT_LIB
#      define MESHVIZ_COMPONENT_LIB "MeshVizWin"
#    endif
#    define __MESHVIZWDLL "MeshVizWin.dll"
#    define __MESHVIZWLIB "MeshVizWin.lib"
#  endif
# endif

# ifndef MeshVizWin_EXPORTS
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__MESHVIZWLIB)
#  endif
# endif
# ifndef PoDataVizW
#  define PoDataVizW PoMeshVizW
# endif
#else
# ifdef SOQT
#  define __MESHVIZWDLL "libMeshVizXt"
# else
#  define __MESHVIZWDLL "libMeshVizQt"
# endif
#endif /* _WIN32 */

#include <Inventor/SoModule.h>
#ifdef SOQT
SO_MODULE_HEADER(SoMeshVizQt, __MESHVIZWDLL)
#elif defined(SOWX)
SO_MODULE_HEADER(SoMeshVizWx, __MESHVIZWDLL)
#elif defined(_WIN32)
SO_MODULE_HEADER(SoMeshVizWin, __MESHVIZWDLL)
#else
SO_MODULE_HEADER(SoMeshVizXt, __MESHVIZWDLL)
#endif

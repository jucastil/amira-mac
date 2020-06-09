/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _INVENTOR_PORT_H
#define _INVENTOR_PORT_H

# include <inttypes.h>

// kept for compatibility but no more used
#define __IvStaticImport

#ifdef _WIN32

#include <Inventor/Win/SoWinBeginStrict.h>

#  include <windows.h>
#  include <winsock.h>
#  include <math.h>
#  include <string.h>
#ifdef LIBRARYBUILD
//Don't force customers to use this definition
#  define strcasecmp _stricmp
#endif

#  ifdef _WIN64
#    define _USE_MATH_DEFINES
#  endif
#  include <math.h>

#ifndef _USE_MATH_DEFINES
#ifndef M_E
#  define M_E            2.7182818284590452354
#endif
#ifndef M_LOG2E
#  define M_LOG2E        1.4426950408889634074
#endif
#ifndef M_LOG10E
#  define M_LOG10E       0.43429448190325182765
#endif
#ifndef M_LN2
#  define M_LN2          0.69314718055994530942
#endif
#ifndef M_LN10
#  define M_LN10         2.30258509299404568402
#endif
#ifndef M_PI
#  define M_PI           3.14159265358979323846
#endif
#ifndef M_PI_2
#  define M_PI_2         1.57079632679489661923
#endif
#ifndef M_PI_4
#  define M_PI_4         0.78539816339744830962
#endif
#ifndef M_1_PI
#  define M_1_PI         0.31830988618379067154
#endif
#ifndef M_2_PI
#  define M_2_PI         0.63661977236758134308
#endif
#ifndef M_2_SQRTPI
#  define M_2_SQRTPI     1.12837916709551257390
#endif
#ifndef M_SQRT2
#  define M_SQRT2        1.41421356237309504880
#endif
#ifndef M_SQRT1_2
#  define M_SQRT1_2      0.70710678118654752440
#endif
#ifndef MAXFLOAT
#  define MAXFLOAT     ((float)3.40282346638528860e+38)
#endif
#endif


#if defined(_MSC_VER) && (_MSC_VER < 1300)
#  define __FUNCTION__ "NO__FUNCTION__FOR_VC6"
#endif

#ifdef bcopy
#  undef bcopy
#endif
#define bcopy(from,to,len) memcpy((to),(from),(len))

#include <SoVersion.h>

#if defined(_DEBUG)
#  define SO_DLL_SUFFIX SO_FULL_VERSION_STRING"D.DLL"
#  define SO_LIB_SUFFIX SO_FULL_VERSION_STRING"D.LIB"
#  define __INVDLL "INV"SO_FULL_VERSION_STRING"D.DLL"
#  define __INVLIB "INV"SO_FULL_VERSION_STRING"D.LIB"
#else
#  define SO_DLL_SUFFIX SO_FULL_VERSION_STRING".DLL"
#  define SO_LIB_SUFFIX SO_FULL_VERSION_STRING".LIB"
#  define __INVDLL "INV"SO_FULL_VERSION_STRING".DLL"
#  define __INVLIB "INV"SO_FULL_VERSION_STRING".LIB"
#endif

#define VC_DLL_EXPORT __declspec(dllexport)
#define VC_DLL_IMPORT __declspec(dllimport)

// Defines by default USE_DEF_FILE_AT_LINK to link Inv.dll using .def file
// on VC6, VC7, VC7.1
#if defined(_WIN32) && _MSC_VER < 1400
//#  define USE_DEF_FILE_AT_LINK // Should be set when we build or use Inventor lib linked with a def file
#endif

#ifdef USE_DEF_FILE_AT_LINK
#  pragma warning(disable: 4275)
#  pragma warning(disable: 4251)
#endif

#ifndef INVENTOR_EXPORT // When lib Inventor is not built
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__INVLIB)
#endif
#endif

#include <Inventor/Win/SoWinEndStrict.h>

// DIRECTVIZ_EXPORT is defined only when building DirectViz dll
#ifdef DIRECTVIZ_EXPORT
#  define DIRECTVIZ_API VC_DLL_EXPORT
#else
#  define DIRECTVIZ_API VC_DLL_IMPORT
#endif

// DIRECTVIZQ_EXPORT is defined only when building DirectVizQT dll
#ifdef DIRECTVIZQ_EXPORT
#  define DIRECTVIZQ_API VC_DLL_EXPORT
#else
#  define DIRECTVIZQ_API VC_DLL_IMPORT
#endif

// DIRECTVIZW_EXPORT is defined only when building DirectVizQT dll
#ifdef DIRECTVIZW_EXPORT
#  define DIRECTVIZW_API VC_DLL_EXPORT
#else
#  define DIRECTVIZW_API VC_DLL_IMPORT
#endif

// DIALOGVIZ_EXPORT is defined only when building DialogViz dll
#ifdef DIALOGVIZ_EXPORT
#  define DIALOGVIZ_API VC_DLL_EXPORT
#else
#  define DIALOGVIZ_API VC_DLL_IMPORT
#endif

// DIALOGVIZQ_EXPORT is defined only when building DialogVizQT dll
#ifdef DIALOGVIZQ_EXPORT
#  define DIALOGVIZQ_API VC_DLL_EXPORT
#else
#  define DIALOGVIZQ_API VC_DLL_IMPORT
#endif

// FXVIZ_EXPORT is defined only when building FxViz dll
#ifdef FXVIZ_EXPORT
#  define FXVIZ_API VC_DLL_EXPORT
#else
#  define FXVIZ_API VC_DLL_IMPORT
#endif

// HARDCOPY_EXPORT is defined only when building HardCopy dll
#ifdef HARDCOPY_EXPORT
#  define HARDCOPY_API VC_DLL_EXPORT
#else
#  define HARDCOPY_API VC_DLL_IMPORT
#endif

// HARDCOPYW_EXPORT is defined only when building HardCopyW dll
#ifdef HARDCOPYW_EXPORT
#  define HARDCOPYW_API VC_DLL_EXPORT
#else
#  define HARDCOPYW_API VC_DLL_IMPORT
#endif

// MESHVIZ_EXPORT is defined only when building MeshViz dll
#ifdef MESHVIZ_EXPORT
#  define MESHVIZ_API VC_DLL_EXPORT
#else
#  define MESHVIZ_API VC_DLL_IMPORT
#endif

// MESHVIZW_EXPORT is defined only when building MeshVizw dll
#ifdef MESHVIZW_EXPORT
#  define MESHVIZW_API VC_DLL_EXPORT
#else
#  define MESHVIZW_API VC_DLL_IMPORT
#endif

// INVENTOR_EXPORT is defined only when building Inv dll
#ifdef USE_DEF_FILE_AT_LINK
#  ifdef INVENTOR_EXPORT
#    define INVENTOR_API
#  else
#    define INVENTOR_API
#  endif
#else
#  ifdef INVENTOR_EXPORT
#    define INVENTOR_API VC_DLL_EXPORT
#  else
#    define INVENTOR_API VC_DLL_IMPORT
#  endif
#endif

// INVENTORW_EXPORT is defined only when building Invw dll
#ifdef INVENTORW_EXPORT
#  define INVENTORW_API VC_DLL_EXPORT
#else
#  define INVENTORW_API VC_DLL_IMPORT
#endif

// INVENTORQT_EXPORT is defined only when building InvQt dll
#ifdef INVENTORQT_EXPORT
#  define INVENTORQT_API VC_DLL_EXPORT
#else
#  define INVENTORQT_API VC_DLL_IMPORT
#endif

// INVENTORWX_EXPORT is defined only when building InvWx dll
#ifdef INVENTORWX_EXPORT
#  define INVENTORWX_API VC_DLL_EXPORT
#else
#  define INVENTORWX_API VC_DLL_IMPORT
#endif

// INVENTORGUI_EXPORT is defined only when building InvGui dll
#ifdef INVENTORGUI_EXPORT
#  define INVENTORGUI_API VC_DLL_EXPORT
#else
#  define INVENTORGUI_API VC_DLL_IMPORT
#endif

// IVDLACIS_EXPORT is defined only when building IvDllAcis dll
#ifdef IVDLACIS_EXPORT
#  define IVDLACIS_API VC_DLL_EXPORT
#else
#  define IVDLACIS_API VC_DLL_IMPORT
#endif

// IVF_EXPORT is defined only when building Ivf dll
#ifdef IVF_EXPORT
#  define IVF_API VC_DLL_EXPORT
#else
#  define IVF_API VC_DLL_IMPORT
#endif

// IVTUNE_EXPORT is defined only when building IvTune dll
#ifdef IVTUNE_EXPORT
#  define IVTUNE_API VC_DLL_EXPORT
#else
#  define IVTUNE_API VC_DLL_IMPORT
#endif

// SCALEVIZ_EXPORT is defined only when building Inv dll
#ifdef SCALEVIZ_EXPORT
#  define SCALEVIZ_API VC_DLL_EXPORT
#else
#  define SCALEVIZ_API VC_DLL_IMPORT
#endif

// SOLIDVIZ_EXPORT is defined only when building SolidViz dll
#ifdef SOLIDVIZ_EXPORT
#  define SOLIDVIZ_API VC_DLL_EXPORT
#else
#  define SOLIDVIZ_API VC_DLL_IMPORT
#endif

// TERRAINVIZ_EXPORT is defined only when building MeshViz dll
#ifdef TERRAINVIZ_EXPORT
#  define TERRAINVIZ_API VC_DLL_EXPORT
#else
#  define TERRAINVIZ_API VC_DLL_IMPORT
#endif

// TERRAINVIZW_EXPORT is defined only when building MeshVizw dll
#ifdef TERRAINVIZW_EXPORT
#  define TERRAINVIZW_API VC_DLL_EXPORT
#else
#  define TERRAINVIZW_API VC_DLL_IMPORT
#endif

// VOLUMEVIZ_EXPORT is defined only when building VolumeViz dll
#ifdef VOLUMEVIZ_EXPORT
#  define VOLUMEVIZ_API VC_DLL_EXPORT
#else
#  define VOLUMEVIZ_API VC_DLL_IMPORT
#endif

// LDM_EXPORT is defined only when building LDM dll
#ifdef LDM_EXPORT
#  define LDM_API VC_DLL_EXPORT
#else
#  define LDM_API VC_DLL_IMPORT
#endif

// RESERVOIRVIZ_EXPORT is defined only when building RerervoirViz dll
#ifdef RESERVOIRVIZ_EXPORT
#  define RESERVOIRVIZ_API VC_DLL_EXPORT
#else
#  define RESERVOIRVIZ_API VC_DLL_IMPORT
#endif

#else /********************************************** UNIX **********************************************/

#  include <strings.h>

#  ifndef APIENTRY
#    define APIENTRY
#  endif
#  ifndef CALLBACK
#    define CALLBACK
#  endif
#  ifndef WINGDIAPI
#    define WINGDIAPI
#  endif
#  ifndef HDC
#    define HDC void *
#  endif
#  if defined(_HP_NAMESPACE_STD)
#    include <limits>
#  endif
#  ifndef UINT
#    define UINT unsigned int
#  endif

#  define DIRECTVIZ_API
#  define DIRECTVIZQ_API
#  define DIALOGVIZ_API
#  define DIALOGVIZQ_API
#  define FXVIZ_API
#  define HARDCOPY_API
#  define HARDCOPYW_API
#  define MESHVIZ_API
#  define MESHVIZW_API
#  define INVENTOR_API
#  define INVENTORW_API
#  define INVENTORQT_API
#  define INVENTORWX_API
#  define INVENTORGUI_API
#  define IVDLACIS_API
#  define IVF_API
#  define IVTUNE_API
#  define SCALEVIZ_API
#  define SOLIDVIZ_API
#  define TERRAINVIZ_API
#  define TERRAINVIZW_API
#  define VOLUMEVIZ_API
#  define LDM_API
#  define RESERVOIRVIZ_API
#  define _API

#ifndef __FUNCTION__
#  if defined(sgi)
#    define __FUNCTION__ "NO__FUNCTION__FOR_IRIX"
#  elif defined(sun)
#    define __FUNCTION__ "NO__FUNCTION__FOR_SOLARIS"
#  endif
#endif

#endif /* UNIX */

#ifndef __APPLE__
typedef void* WindowPtr;
#endif

#endif /* _INVENTOR_PORT_H */


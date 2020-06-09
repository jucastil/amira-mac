/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _INVENTOR_PORT_H
#define _INVENTOR_PORT_H

#include <inttypes.h>

// kept for compatibility but no more used
#define __IvStaticImport

#ifdef _WIN32


#  pragma warning( disable: 4800)
#  pragma warning( disable: 4251)

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
#  define __INVDLL "InventorD.dll"
#  define __INVLIB "InventorD.lib"
#else
#  define __INVDLL "Inventor.dll"
#  define __INVLIB "Inventor.lib"
#endif

#define VC_DLL_EXPORT __declspec(dllexport)
#define VC_DLL_IMPORT __declspec(dllimport)

#include <Inventor/Win/SoWinEndStrict.h>

#include <Inventor/sys/portBase.h>
#include <Inventor/sys/portGL.h>
#include <Inventor/sys/portImage.h>

// DemoViewerAPI_EXPORTS is defined only when building DemoViewer dll
#ifdef DemoViewerAPI_EXPORTS
#  define DEMOVIEWER_API VC_DLL_EXPORT
#else
#  define DEMOVIEWER_API VC_DLL_IMPORT
#endif

// DirectViz_EXPORTS is defined only when building DirectViz dll
#ifdef DirectViz_EXPORTS
#  define DIRECTVIZ_API VC_DLL_EXPORT
#else
#  define DIRECTVIZ_API VC_DLL_IMPORT
#endif

// DirectVizQt_EXPORTS is defined only when building DirectVizQt dll
#ifdef DirectVizQt_EXPORTS
#  define DIRECTVIZQ_API VC_DLL_EXPORT
#else
#  define DIRECTVIZQ_API VC_DLL_IMPORT
#endif

// DirectVizWin_EXPORTS is defined only when building DirectVizWin dll
#ifdef DirectVizWin_EXPORTS
#  define DIRECTVIZW_API VC_DLL_EXPORT
#else
#  define DIRECTVIZW_API VC_DLL_IMPORT
#endif

// DialogViz_EXPORTS is defined only when building DialogViz dll
#if defined(DialogVizXt_EXPORTS) || defined(DialogVizWin_EXPORTS) || defined(DialogVizQt_EXPORTS)
#  define DIALOGVIZ_API VC_DLL_EXPORT
#else
#  define DIALOGVIZ_API VC_DLL_IMPORT
#endif

// DialogVizQt_EXPORTS is defined only when building DialogVizQt dll
#ifdef DialogVizQt_EXPORTS
#  define DIALOGVIZQ_API VC_DLL_EXPORT
#else
#  define DIALOGVIZQ_API VC_DLL_IMPORT
#endif

// FXViz_EXPORTS is defined only when building FxViz dll
#ifdef FXViz_EXPORTS
#  define FXVIZ_API VC_DLL_EXPORT
#else
#  define FXVIZ_API VC_DLL_IMPORT
#endif

// HardCopy_EXPORTS is defined only when building HardCopy dll
#ifdef HardCopy_EXPORTS
#  define HARDCOPY_API VC_DLL_EXPORT
#else
#  define HARDCOPY_API VC_DLL_IMPORT
#endif

// HardCopyWin_EXPORTS is defined only when building HardCopyW dll
#ifdef HardCopyWin_EXPORTS
#  define HARDCOPYW_API VC_DLL_EXPORT
#else
#  define HARDCOPYW_API VC_DLL_IMPORT
#endif

// MeshViz_EXPORTS is defined only when building MeshViz dll
#ifdef MeshViz_EXPORTS
#  define MESHVIZ_API VC_DLL_EXPORT
#else
#  define MESHVIZ_API VC_DLL_IMPORT
#endif

// MeshVizWin_EXPORTS is defined only when building MeshVizWin dll
#ifdef MeshVizWin_EXPORTS
#  define MESHVIZW_API VC_DLL_EXPORT
#else
#  define MESHVIZW_API VC_DLL_IMPORT
#endif

// Inventor_EXPORTS is defined only when building Inventor dll
#ifdef Inventor_EXPORTS
#  define INVENTOR_API VC_DLL_EXPORT
#else
#  define INVENTOR_API VC_DLL_IMPORT
#endif

// InventorBase_EXPORTS is defined only when building InventorBase dll
#ifdef InventorBase_EXPORTS
#  define INVENTORBASE_API VC_DLL_EXPORT
#else
#  define INVENTORBASE_API VC_DLL_IMPORT
#endif

// InventorGL_EXPORTS is defined only when building InventorBase dll
#ifdef InventorGL_EXPORTS
#  define INVENTORGL_API VC_DLL_EXPORT
#else
#  define INVENTORGL_API VC_DLL_IMPORT
#endif

// InventorGL_EXPORTS is defined only when building InventorBase dll
#ifdef InventorImage_EXPORTS
#  define INVENTORIMAGE_API VC_DLL_EXPORT
#else
#  define INVENTORIMAGE_API VC_DLL_IMPORT
#endif

// InventorWin_EXPORTS is defined only when building InventorWin dll
#ifdef InventorWin_EXPORTS
#  define INVENTORW_API VC_DLL_EXPORT
#else
#  define INVENTORW_API VC_DLL_IMPORT
#endif
#define INVENTORXT_API INVENTORW_API

// InventorQt_EXPORTS is defined only when building InventorQt dll
#ifdef InventorQt_EXPORTS
#  define INVENTORQT_API VC_DLL_EXPORT
#elif defined(InventorQt4_EXPORTS)
#  define INVENTORQT_API VC_DLL_EXPORT
#else
#  define INVENTORQT_API VC_DLL_IMPORT
#endif

// InventorWx_EXPORTS is defined only when building InventorWx dll
#ifdef InventorWx_EXPORTS
#  define INVENTORWX_API VC_DLL_EXPORT
#else
#  define INVENTORWX_API VC_DLL_IMPORT
#endif

// InventorGui_EXPORTS is defined only when building InventorGui dll
#ifdef InventorGui_EXPORTS
#  define INVENTORGUI_API VC_DLL_EXPORT
#else
#  define INVENTORGUI_API VC_DLL_IMPORT
#endif

// IvDLDxf_EXPORTS is defined only when building IvDLDxf dll
#ifdef IvDLDxf_EXPORTS
#  define IVDLDXF_API VC_DLL_EXPORT
#else
#  define IVDLDXF_API VC_DLL_IMPORT
#endif

// IvDLFlt_EXPORTS is defined only when building IvDLFlt dll
#ifdef IvDLFlt_EXPORTS
#  define IVDLFLT_API VC_DLL_EXPORT
#else
#  define IVDLFLT_API VC_DLL_IMPORT
#endif

// IvDLCSG_EXPORTS is defined only when building IvDLCSG dll
#ifdef IvDLCSG_EXPORTS
#  define IVDLCSG_API VC_DLL_EXPORT
#else
#  define IVDLCSG_API VC_DLL_IMPORT
#endif

// IvDLAcis_EXPORTS is defined only when building IvDllAcis dll
#ifdef IvDLAcis_EXPORTS
#  define IVDLACIS_API VC_DLL_EXPORT
#else
#  define IVDLACIS_API VC_DLL_IMPORT
#endif

// Ivf_EXPORTS is defined only when building Ivf dll
#ifdef Ivf_EXPORTS
#  define IVF_API VC_DLL_EXPORT
#else
#  define IVF_API VC_DLL_IMPORT
#endif

// IvTune_EXPORTS is defined only when building IvTune dll
#ifdef IvTune_EXPORTS
#  define IVTUNE_API VC_DLL_EXPORT
#else
#  define IVTUNE_API VC_DLL_IMPORT
#endif

// IvTunePlg_EXPORTS is defined only when building IvTune plugins
#ifdef IvTunePlg_EXPORTS
#  define IVTUNEPLG_API VC_DLL_EXPORT
#else
#  define IVTUNEPLG_API VC_DLL_IMPORT
#endif

// ScaleViz_EXPORTS is defined only when building Inv dll
#ifdef RemoteViz_EXPORTS
#  define REMOTEVIZ_API VC_DLL_EXPORT
#else
#  define REMOTEVIZ_API VC_DLL_IMPORT
#endif

// ScaleViz_EXPORTS is defined only when building Inv dll
#ifdef ScaleViz_EXPORTS
#  define SCALEVIZ_API VC_DLL_EXPORT
#else
#  define SCALEVIZ_API VC_DLL_IMPORT
#endif

// SolidViz_EXPORTS is defined only when building SolidViz dll
#ifdef SolidViz_EXPORTS
#  define SOLIDVIZ_API VC_DLL_EXPORT
#else
#  define SOLIDVIZ_API VC_DLL_IMPORT
#endif

// TerrainViz_EXPORTS is defined only when building TerrainViz dll
#ifdef TerrainViz_EXPORTS
#  define TERRAINVIZ_API VC_DLL_EXPORT
#else
#  define TERRAINVIZ_API VC_DLL_IMPORT
#endif

// TerrainVizWin_EXPORTS is defined only when building TerrainVizWin dll
#ifdef TerrainVizWin_EXPORTS
#  define TERRAINVIZW_API VC_DLL_EXPORT
#else
#  define TERRAINVIZW_API VC_DLL_IMPORT
#endif

// VolumeViz_EXPORTS is defined only when building VolumeViz dll
#ifdef VolumeViz_EXPORTS
#  define VOLUMEVIZ_API VC_DLL_EXPORT
#else
#  define VOLUMEVIZ_API VC_DLL_IMPORT
#endif

// LDM_EXPORTS is defined only when building LDM dll
#ifdef LDM_EXPORTS
#  define LDM_API VC_DLL_EXPORT
#else
#  define LDM_API VC_DLL_IMPORT
#endif

// ReservoirViz_EXPORTS is defined only when building RerervoirViz dll
#ifdef ReservoirViz_EXPORTS
#  define RESERVOIRVIZ_API VC_DLL_EXPORT
#else
#  define RESERVOIRVIZ_API VC_DLL_IMPORT
#endif

#ifdef OIV_ENABLE_LEAKDETECTOR
#include <vld.h>
#endif

#else /********************************************** UNIX **********************************************/

#include <Inventor/sys/portGL.h>
#define __INVDLL "libInventor"

#if __GNUC__ > 3
 #define GCC_DLLEXPORT __attribute__ ((visibility("default")))
#else
 #define GCC_DLLEXPORT
#endif

//always set the attribute with GCC
#define VC_DLL_IMPORT GCC_DLLEXPORT
#define VC_DLL_EXPORT GCC_DLLEXPORT

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

#  define DEMOVIEWER_API GCC_DLLEXPORT
#  define DIRECTVIZ_API GCC_DLLEXPORT
#  define DIRECTVIZQ_API GCC_DLLEXPORT
#  define DIALOGVIZ_API GCC_DLLEXPORT
#  define DIALOGVIZQ_API GCC_DLLEXPORT
#  define FXVIZ_API GCC_DLLEXPORT
#  define HARDCOPY_API GCC_DLLEXPORT
#  define HARDCOPYW_API GCC_DLLEXPORT
#  define MESHVIZ_API GCC_DLLEXPORT
#  define MESHVIZW_API GCC_DLLEXPORT
#  define INVENTOR_API GCC_DLLEXPORT
#  define INVENTORW_API GCC_DLLEXPORT
#  define INVENTORXT_API GCC_DLLEXPORT
#  define INVENTORQT_API GCC_DLLEXPORT
#  define INVENTORWX_API GCC_DLLEXPORT
#  define INVENTORGUI_API GCC_DLLEXPORT
#  define INVENTORGL_API GCC_DLLEXPORT
#  define INVENTORIMAGE_API GCC_DLLEXPORT
#  define INVENTORBASE_API GCC_DLLEXPORT
#  define IVDLDXF_API GCC_DLLEXPORT
#  define IVDLFLT_API GCC_DLLEXPORT
#  define IVDLCSG_API GCC_DLLEXPORT
#  define IVDLACIS_API GCC_DLLEXPORT
#  define IVF_API GCC_DLLEXPORT
#  define IVTUNE_API GCC_DLLEXPORT
#  define IVTUNEPLG_API GCC_DLLEXPORT
#  define REMOTEVIZ_API GCC_DLLEXPORT
#  define SCALEVIZ_API GCC_DLLEXPORT
#  define SOLIDVIZ_API GCC_DLLEXPORT
#  define TERRAINVIZ_API GCC_DLLEXPORT
#  define TERRAINVIZW_API GCC_DLLEXPORT
#  define VOLUMEVIZ_API GCC_DLLEXPORT
#  define LDM_API GCC_DLLEXPORT
#  define RESERVOIRVIZ_API GCC_DLLEXPORT
#  define _API

#ifndef __FUNCTION__
#  if defined(sgi)
#    define __FUNCTION__ "NO__FUNCTION__FOR_IRIX"
#  elif defined(sun)
#    define __FUNCTION__ "NO__FUNCTION__FOR_SOLARIS"
#  endif
#endif

#  define SO_DLL_SUFFIX ""
#  define SO_LIB_SUFFIX ""

#endif /* UNIX */

#ifndef __APPLE__
typedef void* WindowPtr;
#endif

#endif /* _INVENTOR_PORT_H */

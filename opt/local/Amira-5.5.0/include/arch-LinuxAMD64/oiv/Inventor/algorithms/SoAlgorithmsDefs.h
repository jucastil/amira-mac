/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOALGORITHMSDEFS_H
#define SOALGORITHMSDEFS_H

#if defined(_WIN32)

#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __INVALGORITHMSDLL "InventorAlgorithmsD.dll"
#    define __INVALGORITHMSLIB "InventorAlgorithmsD.lib"
#  else
#    define __INVALGORITHMSDLL "InventorAlgorithms.dll"
#    define __INVALGORITHMSLIB "InventorAlgorithms.lib"
#  endif
#  ifndef InventorAlgorithms_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVALGORITHMSLIB)
#    endif
#  endif
#else
#  define __INVALGORITHMSDLL "libInventorAlgorithms"
#endif //win

// InventorAlgorithms_EXPORTS is defined only when building InventorAlgorithms dll
#ifdef InventorAlgorithms_EXPORTS
#  define INVENTORALGORITHMS_API VC_DLL_EXPORT
#else
#  define INVENTORALGORITHMS_API VC_DLL_IMPORT
#endif



#endif //SOALGORITHMSDEFS_H

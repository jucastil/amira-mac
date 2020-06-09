/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDADEFS_H
#define SOCUDADEFS_H

/**
* @VSGEXT CUDA module defines for OpenInventor
*
* @ingroup CudaDevice
*
* @DESCRIPTION
*
* Examples:
*
*
*
*
* [OIVJAVA-WRAPPER-NO-WRAP]
* 
*/

#if defined(_WIN32)

#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __INVCUDADLL "InventorCudaD.dll"
#    define __INVCUDALIB "InventorCudaD.lib"
#  else
#    define __INVCUDADLL "InventorCuda.dll"
#    define __INVCUDALIB "InventorCuda.lib"
#  endif

// InventorCuda_EXPORTS is defined only when building InventorCuda dll
#  ifdef InventorCuda_EXPORTS
#    define INVENTORCUDA_API VC_DLL_EXPORT
#  else
#    define INVENTORCUDA_API VC_DLL_IMPORT
#  endif

#  ifndef InventorCuda_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVCUDALIB)
#    endif
#  endif

#else //win

#  define INVENTORCUDA_API GCC_DLLEXPORT
#  define __INVCUDADLL "libInventorCuda"
#endif

#endif //SOCUDADEFS_H

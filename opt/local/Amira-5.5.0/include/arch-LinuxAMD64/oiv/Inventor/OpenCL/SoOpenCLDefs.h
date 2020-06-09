/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOOPENCLDEFS_H
#define SOOPENCLDEFS_H

/**
* @VSGEXT OpenCL module defines for OpenInventor
*
* @ingroup OpenCLDevice
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
#    define __INVOPENCLDLL "InventorCLD.dll"
#    define __INVOPENCLLIB "InventorCLD.lib"
#  else
#    define __INVOPENCLDLL "InventorCL.dll"
#    define __INVOPENCLLIB "InventorCL.lib"
#  endif

// InventorCL_EXPORTS is defined only when building InventorCL dll
#  ifdef InventorCL_EXPORTS
#    define INVENTOROPENCL_API VC_DLL_EXPORT
#  else
#    define INVENTOROPENCL_API VC_DLL_IMPORT
#  endif

#  ifndef InventorCL_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVOPENCLLIB)
#    endif
#  endif

#else //win

#  define INVENTOROPENCL_API GCC_DLLEXPORT
#  define __INVOPENCLDLL "libInventorCL"
#endif

#endif //SOOPENCLDEFS_H

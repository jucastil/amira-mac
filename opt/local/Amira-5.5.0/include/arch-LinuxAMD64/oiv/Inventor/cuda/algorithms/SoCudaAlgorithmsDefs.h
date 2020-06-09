/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDAALGORITHMSDEFS_H
#define SOCUDAALGORITHMSDEFS_H

/**
* @VSGEXT Cuda module defines for OpenInventor
*
* @ingroup Cuda
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
#    define __INVCUDAALGORITHMSDLL "InventorCudaAlgorithmsD.dll"
#    define __INVCUDAALGORITHMSLIB "InventorCudaAlgorithmsD.lib"
#  else
#    define __INVCUDAALGORITHMSDLL "InventorCudaAlgorithms.dll"
#    define __INVCUDAALGORITHMSLIB "InventorCudaAlgorithms.lib"
#  endif

// This project is just a DLL, the functions are not supposed to be used from the outside.

#  ifndef InventorCudaAlgorithms_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVCUDAALGORITHMSLIB)
#    endif
#  endif

#else
#    define __INVCUDAALGORITHMSDLL "libInventorCudaAlgorithms"

#endif //win

// InventorCudaAlgorithms_EXPORTS is defined only when building InventorCudaAlgorithms dll
#ifdef InventorCudaAlgorithms_EXPORTS
#  define INVENTORCUDAALGORITHMS_API VC_DLL_EXPORT
#else
#  define INVENTORCUDAALGORITHMS_API VC_DLL_IMPORT
#endif


#endif //SOCUDAALGORITHMSDEFS_H

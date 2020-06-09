/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOOPENCLALGORITHMSDEFS_H
#define SOOPENCLALGORITHMSDEFS_H

/**
* @VSGEXT OpenCL module defines for OpenInventor
*
* @ingroup OpenCL
*
* @DESCRIPTION
*
* Examples:
*
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
#    define __INVOPENCLALGORITHMSDLL "InventorCLAlgorithmsD.dll"
#    define __INVOPENCLALGORITHMSLIB "InventorCLAlgorithmsD.lib"
#  else
#    define __INVOPENCLALGORITHMSDLL "InventorCLAlgorithms.dll"
#    define __INVOPENCLALGORITHMSLIB "InventorCLAlgorithms.lib"
#  endif

// This project is just a DLL, the functions are not supposed to be used from the outside.

#  ifndef InventorCLAlgorithms_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVOPENCLALGORITHMSLIB)
#    endif
#  endif

#else
#    define __INVOPENCLALGORITHMSDLL "libInventorCLAlgorithms"

#endif //win

// InventorOpenCLAlgorithms_EXPORTS is defined only when building InventorOpenCLAlgorithms dll
#ifdef InventorCLAlgorithms_EXPORTS
#  define INVENTOROPENCLALGORITHMS_API VC_DLL_EXPORT
#else
#  define INVENTOROPENCLALGORITHMS_API VC_DLL_IMPORT
#endif


#endif //SOOPENCLALGORITHMSDEFS_H

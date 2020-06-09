/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_BASIC_
#define _SB_BASIC_

#ifndef HIDDEN_FROM_DOC

#include <Inventor/SbBase.h>

// Internal check
#if defined(InventorBase_EXPORTS)
#error "libInventorBase should not depends on libInventor"
#endif

#ifdef _WIN32

#if !defined(InventorImage_EXPORTS) && !defined(InventorGL_EXPORTS) && !defined(InventorCL_EXPORTS) && !defined(InventorCuda_EXPORTS)
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__INVENTORGLLIB)
#endif
#endif

#if !defined(InventorImage_EXPORTS) && !defined(InventorGL_EXPORTS) && !defined(InventorCL_EXPORTS) && !defined(InventorCuda_EXPORTS)
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__INVENTORIMAGELIB)
#endif
#endif

#if !defined(Inventor_EXPORTS) && !defined(InventorImage_EXPORTS) && !defined(InventorGL_EXPORTS) && !defined(InventorCL_EXPORTS) && !defined(InventorCuda_EXPORTS)
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__INVLIB)
#endif
#endif

#endif // _WIN32

#endif // HIDDEN_FROM_DOC

#endif // _SB_BASIC_

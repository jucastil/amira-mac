/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/




#ifndef _SO_HARDCOPY_
#define _SO_HARDCOPY_

#include <SoVersion.h>

#ifdef _WIN32
#  if defined(_DEBUG)
#    define __HARDCOPYDLL "HardCopyD.dll"
#    define __HARDCOPYLIB "HardCopyD.lib"
#  else
#    define __HARDCOPYDLL "HardCopy.dll"
#    define __HARDCOPYLIB "HardCopy.lib"
#  endif
#  ifndef HardCopy_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__HARDCOPYLIB)
#    endif
#  endif
#else
#  define __HARDCOPYDLL "libHardCopy"
#endif

#include <Inventor/SbBasic.h>

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoHardCopy, __HARDCOPYDLL)

/**
 * @HCEXT Class to initialize HardCopy.
 * 
 * @ingroup DataViz
 * 
 * @DESCRIPTION
 *   This class allows the user to initialize the HardCopy module. The module
 *   must be initialized before using any other classes of the module.
 * 
 * @SEE_ALSO
 *    HardCopy Overview,
 * 
 * 
 */ 

class HARDCOPY_API SoHardCopy {

 public:

  /**
   * Initializes all classes of HardCopy by registering them
   * in the database. This function needs to be called before any 
   * other class of HardCopy may be constructed or accessed. 
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init();

  /** 
   * Frees Open Inventor's internal static memory 
   * allocations. This avoids false positives from memory
   * leak checking software. We recommend calling this method
   * and it should be the last Open Inventor method called by
   * the application.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();

  /**
   * Returns a character string identifying the name of the extension.
   */
  static const char *getProductName();

  /**
   * Returns a character string identifying the version of extension.
   */
  static const char *getVersion();

 SoINTERNAL public:

  static SbBool internalInit();

  // reference counter on the lib.
  static int s_initRefCount;

  static const char *s_versionString;

};
/*---------------------------------------------------------------------------*/

#endif // _SO_HARDCOPY_


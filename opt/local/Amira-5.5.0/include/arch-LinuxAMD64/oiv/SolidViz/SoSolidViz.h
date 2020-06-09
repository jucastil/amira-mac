/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Rodolphe ALBOU (May 2001)
**=======================================================================*/


#ifndef _SO_SOLID_VIZ_
#define _SO_SOLID_VIZ_

#include <Inventor/SbBasic.h>

#ifdef _WIN32
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __INVSVDLL "SolidVizD.dll"
#    define __INVSVLIB "SolidVizD.lib"
#  else
#    define __INVSVDLL "SolidViz.dll"
#    define __INVSVLIB "SolidViz.lib"
#  endif
#  ifndef SolidViz_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVSVLIB)
#    endif
#  endif
#else
#  define __INVSVDLL "libSolidViz"
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoSolidViz, __INVSVDLL)

/*----------------------------------------------------------------------------*/

/**
 * @SVEXT Class to initialize SolidViz.
 * 
 * @ingroup SolidViz
 * 
 * @DESCRIPTION
 *   This class allows the user to initialize the SolidViz module. The module must be
 *   initialized before using any other classes of the module.
 * 
 * @SEE_ALSO
 *    SolidViz  Overview,
 *    SoCSGGroup
 * 
 * 
 */ 

class SOLIDVIZ_API SoSolidViz {

public:
  /**
   * Initializes the SolidViz extension.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init() ;

  /**
   * Finalize the SolidViz module.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
   * Returns a character string identifying the name of the extension (SolidViz).
   */
  static const char *getProductName() ;
  /**
   * Returns a character string identifying the version of SolidViz.
   */
  static const char *getVersion() ;

 SoINTERNAL public:
  static void internalInit();
  static int s_initRefCount;
  static const char *s_versionString;
}; /*---------------------------------------------------------------------------*/

#endif // _SO_SOLID_VIZ_









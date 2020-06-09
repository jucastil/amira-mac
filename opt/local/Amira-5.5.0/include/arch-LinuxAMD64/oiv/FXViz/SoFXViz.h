/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Rodolphe ALBOU (Dec 2001)
**=======================================================================*/


#ifndef _SO_FXVIZ_
#define _SO_FXVIZ_


#include <SoVersion.h>
#include <Inventor/SbBasic.h>


#ifdef _WIN32
#  if defined(_DEBUG)   
#    define __INVFXVizDLL "FXVizD.dll"
#    define __INVFXVizLIB "FXVizD.lib"
#  else
#    define __INVFXVizDLL "FXViz.dll"
#    define __INVFXVizLIB "FXViz.lib"
#  endif
#  ifndef FXViz_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVFXVizLIB)
#    endif
#  endif
#else
#  define __INVFXVizDLL "libFXViz"
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoFXViz, __INVFXVizDLL)

/*----------------------------------------------------------------------------*/

/**
 * @FXEXT Class to initialize FXViz.
 * 
 * @ingroup FXViz
 * 
 * @DESCRIPTION
 *   This class allows the user to initialize the FXViz module. The module must be
 *   initialized before using any other classes of the module.
 * 
 * @SEE_ALSO
 *    FXViz, SoParticleAnimation, SoParticleChemicalFlame, 
 *    SoParticleExplosion, SoParticleFlame, SoParticleLightRay,
 *    SoParticleSmoke, SoParticleSnow, SoShadowGroup
 * 
 * 
 */ 

class FXVIZ_API SoFXViz {

public:
  /**
   * Initializes the FXViz extension.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init() ;

  /** 
   * Shuts down the FXViz module, which includes freeing any
   * internal static memory that it allocated. 
   * Finish methods must be called in the reverse order of the init method calls: 
   * <PRE>    SoFXViz::finish(); 
   *    SoXt::finish(); 
   *    ... </PRE>
   * [OIV-WRAPPER-NO-WRAP]
   */

  static void finish() ;

  /**
   * Returns TRUE if module is currently initialized.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
   * Returns a character string identifying the name of the extension (FXViz).
   */
  static const char *getProductName() ;
  /**
   * Returns a character string identifying the version of FXViz.
   */
  static const char *getVersion() ;

private:
  static int s_initRefCount;

  static const char *s_versionString;

}; /*---------------------------------------------------------------------------*/

#endif // _SO_FXVIZ_









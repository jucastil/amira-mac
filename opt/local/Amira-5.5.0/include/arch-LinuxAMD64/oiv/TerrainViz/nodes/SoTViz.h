/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : C. OGNIER (Feb 2001)
**=======================================================================*/

#ifndef SOTVIZ_H
#define SOTVIZ_H

#ifdef _WIN32
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __INVTVIZDLL "TerrainVizD.dll"
#    define __INVTVIZLIB "TerrainVizD.lib"
#  else
#    define __INVTVIZDLL "TerrainViz.dll"
#    define __INVTVIZLIB "TerrainViz.lib"
#  endif
#  ifndef TerrainViz_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVTVIZLIB)
#    endif
#  endif
#else
#  define __INVTVIZDLL "libTerrainViz"
#endif


#include <Inventor/SbBasic.h> 
#include <Inventor/sys/SoGLType.h>

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoTerrainViz, __INVTVIZDLL)

/**
 * @TVEXT Static class used to initialize the TerrainViz extension.
 * 
 * @ingroup TerrainViz
 * 
 * @DESCRIPTION
 *   This class allows the user to initialize the TerrainViz extension. The extension
 *   must be initialized before using any other classes of the extension.
 * 
 * @SEE_ALSO
 *    SbTVizData,
 *    SbTVizRegularGridData,
 *    SbTVizTexture,
 *    SbTVizTextureList,
 *    SoTVizRender
 * 
 * 
 */ 

class TERRAINVIZ_API SoTViz {
        

  public :
  /**
   * Initializes the TerrainViz extension and checks the license.
   */
  static void init();
  static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   */
  static bool isInitialized();

  /**
   * Returns a character string identifying the name of the extension ("TerrainViz").
   */
  static const char* getProductName();

  /**
   * Returns a character string identifying the version of TerrainViz.
   */
  static const char* getVersion();

 SoINTERNAL public:
  static int getGLMaxTextureSize();

 private:
  SoTViz();
  virtual ~SoTViz();

  static SbBool getGLInfo();
  static GLint  m_glMaxTexSize;
  static int s_initRefCount;
  static const char *s_versionString;
};

#endif


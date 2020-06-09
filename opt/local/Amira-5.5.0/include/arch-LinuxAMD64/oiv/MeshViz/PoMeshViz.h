/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _PO_MESHVIZ_
#define  _PO_MESHVIZ_

#define PoDataViz PoMeshViz

#include <SoVersion.h>

#ifdef _WIN32
# if defined(_DEBUG)   
#    define __MESHVIZLIB  "MeshVizD.lib"
#    define __MESHVIZDLL  "MeshVizD.dll"
# else
#    define __MESHVIZLIB  "MeshViz.lib"
#    define __MESHVIZDLL  "MeshViz.dll"
# endif

# ifndef MeshViz_EXPORTS
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__MESHVIZLIB)
#  endif
# endif

#else
#    define __MESHVIZDLL  "libMeshViz"
#endif

#include <MeshViz/PbBasic.h>

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(MoMeshViz, __MESHVIZDLL)

/**
 * @DTEXT Class to initialize MeshViz.
 * 
 * @ingroup MeshViz
 * 
 * @DESCRIPTION
 *   This class allows the user to initialize the MeshViz module. The module
 *   must be initialized before using any other classes of the module.
 * 
 * @SEE_ALSO
 *    MeshViz Overview,
 *    PoBase
 * 
 * 
 */ 

class MESHVIZ_API PoMeshViz {

 public:

  /**
   * Initializes all nodekit classes of MeshViz by registering them
   * in the database. This function needs to be called before any 
   * other nodekit class of MeshViz may be constructed or accessed. 
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void init();

	/**
   * Finishes all nodekit classes of MeshViz by unregistering them
   * in the database. This function needs to be called after any 
   * other nodekit class of MeshViz may be destroyed.
   * [OIV-WRAPPER-NO-WRAP]
   */
	static void finish();

  /**
   * Returns TRUE if module is currently initialized.
   * [OIV-WRAPPER-NO-WRAP]
   */
  static bool isInitialized();

  /**
   * Returns a character string identifying the name of the extension.
   */
  static const char *getProductName();

  /**
   * Returns a character string identifying the version of extension.
   */
  static const char *getVersion();
private:
  static const char *s_versionString;
} ;
/*---------------------------------------------------------------------------*/

#endif /* _PO_MESHVIZ_ */


/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MO_MESHVIZ_
#define  _MO_MESHVIZ_

#include <MeshVizInterface/mapping/MoMeshVizDataMapping.h>

/**
 * @DTEXT Class to initialize all MeshViz Interface nodes.
 * 
 * @ingroup MeshIViz_Mapping
 * 
 * @DESCRIPTION
 *   This class initializes both the Mesh Extraction and Data Mapping modules
 *   of MeshViz Interface (it is not necessary to initialize #MiMeshViz if
 *   using this class). Initialization must be done before creating or
 *   using any other MeshViz Interface classes.
 * 
 * 
 */ 

class MESHIVIZDM_API MoMeshViz {

 public:

  /**
   * Initializes all classes in the Mesh Extraction and Data Mapping modules
   * (automatically calls the MiMeshViz::init method).
   * This function must be called before creating or using any 
   * other MeshViz Interface classes.
   */
  static void init();

	/**
   * Finishs all classes in the Mesh Extraction and Data Mapping modules
   * (automatically calls the MiMeshViz::finish method).
   * This function should be called after all MeshViz Interface objects
   * have been destroyed, to ensure that any static memory allocations
   * are freed.
   */
	static void finish();

  /**
   * Returns TRUE if module is currently initialized.
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

 SoINTERNAL public:

  // Init/finish ref counter status
  static int s_initRefCount;

  static const char *s_versionString;
} ;
/*---------------------------------------------------------------------------*/

#endif /* _MO_MESHVIZ_ */


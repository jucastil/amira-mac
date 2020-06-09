/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIMESHVIZ_H
#define _MIMESHVIZ_H

#include <MeshVizInterface/MxMeshIViz.h>

/**
 * @DTEXT Class to initialize the MeshViz Mesh Extraction module.
 * 
 * @ingroup MeshIViz_MeshIViz
 * 
 * @DESCRIPTION
 *   This class is used to initialize and finish the Mesh Extraction module.
 *   The init() method must be called before using any other Mesh Extraction classes.
 *
 *   This class is provided for stand-alone use of Mesh Extraction (separate
 *   from Open Inventor). If using MeshViz Data Mapping, it is not necessary to
 *   explicitly initalize Mesh Extraction because this is done automatically
 *   by the MoMeshViz class.
 *
 * @SEE_ALSO
 *    MoMeshViz
 * 
 * 
 */ 

class MESHIVIZ_API MiMeshViz {

 public:

  /**
   * Initializes all Mesh Extraction classes.
   * This function must be called before any 
   * other Mesh Extraction class may be constructed or used. 
   */
  static void init(const char *internalUse = NULL);

	/**
   * Finishes all classes of MeshViz extraction.
   * This function should be called after all Mesh Extraction objects
   * have been destroyed, to ensure that any static memory allocations
   * are freed.
   */
	static void finish();

  /**
  * Returns a character string identifying the name of the extension.
  */
  const char* getProductName();

  /**
  * Returns a character string identifying the version of extension.
  */
  const char* getVersion();

  /**
  * Returns true if MeshViz Interface is initialized
  */
  static bool isInitialized();

 private:

  // Init/finish ref counter status
  static int s_initRefCount;

} ;



#endif

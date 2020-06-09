/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Pascal DOUX (May 1998)
**=======================================================================*/


#ifndef _SO_REORGANIZE_ACTION_
#define _SO_REORGANIZE_ACTION_


//------------------------------------------------------------------------------
// Includes

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoSimplifyAction.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/fields/SoMFFloat.h>

#include <Inventor/SoType.h>

class SoSimplifier;

/**
 * @VSGEXT Reorganizes the scene graph by grouping shapes with common properties, then
 * groups these shapes in a single shape and runs the simplifier on it.
 * 
 * @ingroup actions LMV
 * 
 * @DESCRIPTION
 *   This class reorganizes the scene graph by grouping shapes with common properties,
 *   then groups these shapes in a single shape and runs the simplifier on it. If a
 *   simplifier is not provided, it creates an indexed triangle strip set from this
 *   shape. 
 *
 *   In order for shapes to be grouped together, they must:
 *    - Be indexed shapes (e.g., SoIndexedFaceSet)
 *    - Have the same material properties
 *    - Have a material binding of PER_VERTEX_INDEXED.
 *
 * 
 * @SEE_ALSO
 *    SoAction,
 *    SoIndexedTriangleStripSet
 * 
 * 
 */ 

class INVENTOR_API SoReorganizeAction : public SoSimplifyAction
{
  SO_ACTION_HEADER(SoReorganizeAction);

public:

  /**
   * Constructor.
   */
  SoReorganizeAction (SoSimplifier *_simplifier = NULL) ;

  /**
   * Destructor.
   */
  ~SoReorganizeAction();

  /**
   * Returns result of reorganization as new scene graph.
   */
  SoSeparator *getSimplifiedSceneGraph() const { return simplifiedRoot; }
  /**
   * Sets whether normals should be generated during reorganization. @BR
   * Default is TRUE.
   */
  void generateNormals(SbBool g) { generateNormal = g;}
  /**
   * Gets whether normals should be generated during reorganization.
   */
  SbBool areNormalGenerated() const { return generateNormal ;}
  /**
   * Sets whether triangle strips should be generated. @BR
   * Default is TRUE.  If false, IndexedFaceSets are generated.
   */
  void generateTriangleStrips(SbBool g) { generateTriangleStrip = g;}
  /**
   * Gets whether triangle strips should be generated; if false, IndexedFaceSets
   * are generated.
   */
  SbBool areTriangleStripGenerated() const { return generateTriangleStrip ;}
  /** 
   * Sets whether texture coordinates should be generated during 
   * reorganization. @BR
   * Default is TRUE.
   */
  void generateTexCoords(SbBool g) { generateTexCoord = g;}
  /**
   * Gets whether texture coordinates should be generated during 
   * reorganization.
   */
  SbBool areTexCoordsGenerated() const { return generateTexCoord ;}
  /**
   * Sets whether vertex property nodes should be generated during 
   * reorganization. @BR
   * Default is TRUE.
   */
  void generateVPNodes(SbBool g) { generateVPNode = g;}
  /**
   * Gets whether vertex property nodes should be generated during 
   * reorganization.
   */
  SbBool areVPNodesGenerated() const { return generateVPNode ;}
  /**
   * Sets whether to try to match index arrays during reorganization. @BR
   * Default is TRUE.
   */
  void matchIndexArrays(SbBool g) { matchIndexArray = g;}
  /**
   * Gets whether to try to match index arrays during reorganization.
   */
  SbBool areIndexArraysMatched() const { return matchIndexArray ;}

  /**
   * Returns the simplifier being used, may be NULL.
   */
  SoSimplifier *getSimplifier() const { return simplifier ;}

  /**
   * Starts a report. The specified message is sent to the console window. 
   * @UNICODE_WARNING
   */
   SoNONUNICODE static void   startReport(const char* msg);

  /**
   * Starts a report. The specified message is sent to the console window. 
   */
   static void   startReport(const SbString& msg);

   /**
   * Ends a report. "Done" is sent to the console window.
   */
   static void   finishReport();

protected:
  virtual void beginTraversal(SoNode *) { beginTraversal();}
  virtual void endTraversal  (SoNode *) { endTraversal()  ;}

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  // Not necessary to document these - interface is same as SoAction
  virtual void apply(SoNode *node);
  virtual void apply(SoPath *path);
  virtual void apply(const SoPathList &path_list, SbBool obeys_rules=FALSE);

private: 

  virtual void beginTraversal();
  virtual void endTraversal  ();

  // new scene graph
  SoSeparator   *simplifiedRoot; 

  // generate per-vertex normals
  SbBool         generateNormal;

  // generate Triangle Strips 
  // only used if a not using a simplifier. Otherwise ignored.
  // FALSE by default
  SbBool         generateTriangleStrip;

  // generate Texture Coordinates
  SbBool         generateTexCoord;

  // generate Vertex Property Nodes 
  SbBool         generateVPNode;

  // match Index Arrays 
  SbBool         matchIndexArray;

  void simplifySingleLevel();
  void simplifyMultiLevelsWithInline();
  void simplifyMultiLevels();
  void simplify();

};


#endif // _SO_REORGANIZE_ACTION_










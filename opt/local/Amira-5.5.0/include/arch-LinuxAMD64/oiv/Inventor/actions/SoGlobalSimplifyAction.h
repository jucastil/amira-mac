/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Pascal DOUX (Jan 1998)
**=======================================================================*/


#ifndef _SO_GLOBAL_SIMPLIFY_ACTION_
#define _SO_GLOBAL_SIMPLIFY_ACTION_


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
 * @VSGEXT Traverses the scene graph and collects all the triangles in a single list. This
 * list is then simplified and the result is stored in a new scene graph.
 * 
 * @ingroup actions LMV
 * 
 * @DESCRIPTION
 *   This class traverses the scene graph and collects all the triangles in a single
 *   list. This list is then simplified and the result is stored in a new scene
 *   graph.
 *   
 *   The SoGlobalSimplifyAction provides two simplification strategies:
 *   
 *   - SIMPLIFY_GLOBALLY: all the triangles found in the scene graph are collected in
 *   a single object. Then this object is simplified.
 *   
 *   - SIMPLIFY_BY_SUBGROUP: triangles are collected until a material change or a
 *   separator is found. 
 *   
 *   The generateNormals flag can be used to force per-vertex normal computation
 *   during an SoGlobalSimplifyAction. When not set, objects may appear faceted
 *   instead of appearing smooth. Setting the @B addShapeHints @b flag to TRUE tells
 *   Open Inventor to build normals at run-time.
 *   
 *   By default the SoGlobalSimplifyAction collects all the triangles even if they are
 *   part of a simple shape (cube, cone, sphere, text3...). Setting the
 *   setCatchAllShapesFlag() flag to FALSE tells the action to collect triangles
 *   only if they belong to a complex shape.
 *   
 *   The getSimplifiedSceneGraph() method returns the root of the new scene
 *   graph after applying the SoGlobalSimplifyAction.
 *   
 *   Typically you will pass an instance of SoDecimator to the constructor. Please see
 *   SoDecimator for info about which geometry objects can be simplified.
 * 
 * @SEE_ALSO
 *    SoAction,
 *    SoLevelOfSimplification,
 *    SoShapeSimplifyAction,
 *    SoSimplifyAction
 * 
 * 
 */ 

class INVENTOR_API SoGlobalSimplifyAction : public SoSimplifyAction
{
  SO_ACTION_HEADER(SoGlobalSimplifyAction);

public:

  /**
   * Constructor. The algorithm used for simplifying is defined by the
   * SoSimplifier class that is passed in the constructor.
   */
  SoGlobalSimplifyAction (SoSimplifier *_simplifier) ;

  /**
   * Destructor.
   */
  ~SoGlobalSimplifyAction();

  /** Strategy */
  enum Strategy {
    /** All triangles are stored in a single list and decimated globally. */
    SIMPLIFY_GLOBALLY, 
    /** Triangles are stored between each material (or separator) to be decimated. */
    SIMPLIFY_BY_SUBGROUP
  };
    
  virtual void apply(SoNode *node);
  virtual void apply(SoPath *path);
  virtual void apply(const SoPathList &path_list, SbBool obeys_rules = FALSE);

  /**
   * Sets the strategy used to determine how to group triangles into the
   * simplified shapes. The choices are SIMPLIFY_GLOBALLY and SIMPLIFY_BY_SUBGROUP.
   */
  void setSimplificationStrategy(Strategy st) { simplificationStrategy = st;}
  /**
   * Gets the strategy used to determine how to group triangles into the
   * simplified shapes.
   */
  Strategy getSimplificationStrategy() const { return simplificationStrategy ;}

  /**
   * This returns the new scene graph which contains the simplified result.
   */
  SoSeparator *getSimplifiedSceneGraph() const { return simplifiedRoot; }
  
  /**
   * Sets the normal generation flag.
   * If true, per-vertex normals are calculated while simplifying.
   */
  void generateNormals(SbBool g) { generateNormal = g;}
  /**
   * Gets the normal generation flag.
   * If true, per-vertex normals are calculated while simplifying.
   */
  SbBool areNormalGenerated() const { return generateNormal ;}

  /**
   * Sets the flag that specifies whether simple shapes are simplified.
   * If true, simple shapes such as SoSphere, SoCone, etc, are faceted and simplified
   * also. If false, then they are ignored.
   */
  void setCatchAllShapesFlag(SbBool c) { catchAllShapes = c;}
  /**
   * Gets the flag that specifies whether simple shapes are simplified.
   */
  SbBool areAllShapesCatched() const { return catchAllShapes ;}

  /**
   * Sets whether a shape hints node is added.
   * If true, a @B shapeHints @b node is added to force smooth normals if they were
   * not generated, and to turn on two-sided lighting.
   */
  void addShapeHintsNode(SbBool a) { addShapeHints = a;}
  /**
   * Gets whether a shape hints node will be added.
   */
  SbBool isShapeHintAdded() const { return addShapeHints ;}

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

protected:
  virtual void beginTraversal(SoNode *) { beginTraversal();}
  virtual void endTraversal  (SoNode *) { endTraversal()  ;}

private: 

  virtual void prepareAction (SoCallbackAction &action);

  virtual void beginTraversal();
  virtual void endTraversal  ();
  
  SbBool         collectTriangles;

  // how to handle decimation
  Strategy       simplificationStrategy;

  // new scene graph
  SoSeparator   *simplifiedRoot; 

  // generate per-vertex normals
  SbBool         generateNormal;

  // catch all shapes flag: TRUE by default.
  // if FALSE, only complex shapes are catched, others are ignored
  SbBool         catchAllShapes;

  // if TRUE, adds a ShapeHint node with two sided lighting on.
  // when generateNormals is FALSE, the shape hints crease angle is
  // set to 0.55 thus objects will appear smooth even witouh normals.
  // This should be used carefully since it may slow down drawing but
  // it can improve rendering aspect when normals are not computed
  // default FALSE
  SbBool         addShapeHints;

  SoMaterial    *material;
  SbBool         materialChanged;

  static SoCallbackAction::Response
  catchShapeCB    ( void* object, SoCallbackAction* action, const SoNode* node) 
  { return ((SoGlobalSimplifyAction*) object)->catchShape (action, node); }

  SoCallbackAction::Response
  catchShape      ( SoCallbackAction* action, const SoNode* node) ;

  static SoCallbackAction::Response
  catchEndShapeCB    ( void* object, SoCallbackAction* action, const SoNode* node) 
  { return ((SoGlobalSimplifyAction*) object)->catchEndShape (action, node); }

  SoCallbackAction::Response
  catchEndShape      ( SoCallbackAction* action, const SoNode* node) ;

  static SoCallbackAction::Response
  catchShapeAttrCB( void* object, SoCallbackAction* action, const SoNode* node)
  { return ((SoGlobalSimplifyAction*) object)->catchShapeAttr (action, node); }

  SoCallbackAction::Response
  catchShapeAttr  ( SoCallbackAction* action, const SoNode* node) ;

  static SoCallbackAction::Response
  catchGroupNodesCB ( void* object, SoCallbackAction* action, const SoNode* node)
  { return ((SoGlobalSimplifyAction*) object)->catchGroupNodes (action, node); }

  SoCallbackAction::Response
  catchGroupNodes   ( SoCallbackAction* action, const SoNode* node) ;

  void addTriangle (SoCallbackAction *action,
                    const SoPrimitiveVertex *vertex1,
                    const SoPrimitiveVertex *vertex2,
                    const SoPrimitiveVertex *vertex3);

  static void addTriangleCB (void *userData,
                             SoCallbackAction *action,
                             const SoPrimitiveVertex *vertex1,
                             const SoPrimitiveVertex *vertex2,
                             const SoPrimitiveVertex *vertex3)
  { ((SoGlobalSimplifyAction*) userData)->addTriangle (action, vertex1, vertex2, vertex3); }


};


#endif // _SO_GLOBAL_SIMPLIFY_ACTION_










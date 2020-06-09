/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Pascal DOUX (Jan 1998)
**=======================================================================*/


#ifndef _SO_SHAPE_SIMPLIFY_ACTION_
#define _SO_SHAPE_SIMPLIFY_ACTION_


//------------------------------------------------------------------------------
// Includes

#include <Inventor/actions/SoAction.h>
#include <Inventor/actions/SoSubAction.h>
#include <Inventor/actions/SoCallbackAction.h>
#include <Inventor/actions/SoSimplifyAction.h>
#include <Inventor/nodes/SoLevelOfSimplification.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/VRMLnodes/SoVRMLIndexedFaceSet.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/SoLists.h>

#include <Inventor/SoType.h>

class SoSimplifier;

/**
 * @VSGEXT Simplify action that replaces shapes within a scene graph with versions that
 * contain fewer triangles.
 * 
 * @ingroup actions LMV
 * 
 * @DESCRIPTION
 *   This class traverses a scene graph and replaces every complex shape with a
 *   simplified version.
 * 
 * @SEE_ALSO
 *    SoAction,
 *    SoLevelOfSimplification,
 *    SoSimplifyAction,
 *    SoGlobalSimplifyAction
 * 
 * 
 */ 

class INVENTOR_API SoShapeSimplifyAction : public SoSimplifyAction
{
  SO_ACTION_HEADER(SoShapeSimplifyAction);

public:

  /**
   * Constructor. The algorithm used for simplifying is defined by the
   * SoSimplifier class that is passed in the constructor.
   * 
   * Typically you will pass an instance of SoDecimator to the constructor. Please see
   * SoDecimator for info about which geometry objects can be simplified.
   */
  SoShapeSimplifyAction (SoSimplifier *_simplifier) ;

  /**
   * Destructor.
   */
  ~SoShapeSimplifyAction();
    
  /**
   * Initiates an action on the graph defined by a node.
   */
  virtual void apply(SoNode *node);
  /**
   * Initiates an action on the graph defined by a path.
   */
  virtual void apply(SoPath *path);
  /**
   * Initiates an action on the graph defined by a list of
   * paths. TRUE can be passed for the @B obeysRules @b flag if the given path list
   * has the following 4 properties:
   *   -# All paths have the same head node.
   *   -# Paths are sorted in traversal order.
   *   -# If one path ends at node @B A@b, no other path continues through @B A@b.
   *   -# No two paths are the same.
   *
   * These rules will be obeyed by path lists returned by picking and by searches for
   * non-group nodes.
   */
  virtual void apply(const SoPathList &path_list, SbBool obeys_rules=FALSE);

 SoINTERNAL public:

  static void initClass();
  static void exitClass();
  SbBool isDecimated() { return wasDecimated; }

protected:

  virtual void beginTraversal(SoNode *) { beginTraversal();}
  virtual void endTraversal  (SoNode *) { endTraversal()  ;}

private: 

  // Holds enabled-elements counter when state is created; used to
  // determine whether list of enabled elements is up to date.
  int enabledElementsCounter;

  SbBool wasDecimated;
  virtual void prepareAction (SoCallbackAction &action);

  virtual void beginTraversal();
  virtual void endTraversal  ();

  SoNodeList groupStack;
  SoNodeList deletedNodes;
  SoNodeList multInstNodes;
  SoNodeList newNodes;
  
  SbBool     collectTriangles;
  SbBool     hasNormals;
  SbBool     hasColors;

  void    pushGroup(const SoNode *node){ groupStack.append((SoNode *)node);}
  void    popGroup ()                  { groupStack.remove(groupStack.getLength()-1);}
  SoNode *getGroup () const            { return groupStack[groupStack.getLength()-1];}

  static SoCallbackAction::Response
  catchShapeCB    ( void* object, SoCallbackAction* action, const SoNode* node) 
  { return ((SoShapeSimplifyAction*) object)->catchShape (action, node); }

  SoCallbackAction::Response
  catchShape      ( SoCallbackAction* action, const SoNode* node) ;

  static SoCallbackAction::Response
  catchEndShapeCB    ( void* object, SoCallbackAction* action, const SoNode* node) 
  { return ((SoShapeSimplifyAction*) object)->catchEndShape (action, node); }

  SoCallbackAction::Response
  catchEndShape      ( SoCallbackAction* action, const SoNode* node) ;

  static SoCallbackAction::Response
  catchGroupNodesCB ( void* object, SoCallbackAction* action, const SoNode* node)
  { return ((SoShapeSimplifyAction*) object)->catchGroupNodes (action, node); }

  SoCallbackAction::Response
  catchGroupNodes   ( SoCallbackAction* action, const SoNode* node) ;

  static SoCallbackAction::Response
  catchEndGroupNodesCB ( void* object, SoCallbackAction* action, const SoNode* node)
  { return (static_cast<SoShapeSimplifyAction*>(object))->catchEndGroupNodes (action, node); }

  SoCallbackAction::Response
  catchEndGroupNodes   ( SoCallbackAction* action, const SoNode* node) ;

  void addTriangle (SoCallbackAction *action,
                    const SoPrimitiveVertex *vertex1,
                    const SoPrimitiveVertex *vertex2,
                    const SoPrimitiveVertex *vertex3);

  static void addTriangleCB (void *userData,
                             SoCallbackAction *action,
                             const SoPrimitiveVertex *vertex1,
                             const SoPrimitiveVertex *vertex2,
                             const SoPrimitiveVertex *vertex3) {
    (static_cast<SoShapeSimplifyAction*>(userData))->addTriangle (action, vertex1, vertex2, vertex3); 
  }

  SoVRMLIndexedFaceSet *convertToVRML2Form(const SoVRMLIndexedFaceSet * node, 
                                           SoIndexedFaceSet * newNode);

};

#endif // _SO_SHAPE_SIMPLIFY_ACTION_










/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul Isaacs (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_SURROUND_SCALE_
#define  _SO_SURROUND_SCALE_

#include <Inventor/fields/SoFieldData.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoTransformation.h>
#include <Inventor/fields/SoSFInt32.h>

class SoFullPath;
class SoGetBoundingBoxAction;
class SbThreadMutex;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoSurroundScale
//
//  Appends a transform to the localMatrix so that a default size  cube will 
//  surround the objects specified by its fields.
//
//  To determine what to surround, the node looks at the current path in
//  the action.  An SoGetBoundingBoxAction is applied to the node that is
//  'numNodesUpToContainer' nodes above this node in the path.
//  The action will be told to reset the bounding box upon traversal of the
//  node that is 'numNodesUpToReset' nodes above this node in the path.
//
//  For example, when a trackballManip wants to surround the objects it
//  is going to move, the scene graph will look something like this:
//                      Separator
//                         |
//            -------------------------
//            |                       |
//          trackballManip       subGraphOfObjectsThatWilMove
//            |
//           trackballDragger
//            |
//           topSeparator(top part within of the dragger)
//            |
//           -----------------------------------
//           |            |                    |
//         motionMatrix  surroundScale     parts of the dragger.
//  The manip will set the fields on the surround scale node to be:
//  numNodesUpToContainer = 4;
//  numNodesUpToReset = 3;
//
//  The action will therefore be applied to the Separator, and will be
//  reset after traversing the trackballManip.
//  So the surroundScale will surround the objects below 'separator' and
//  not including 'trackballManip,' producing the desired effect.
//
//  Note that, therefore, designers of draggers and manipulators which use
//  this node should base their models on default size cubes (2 by 2 by 2).
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Transformation node that adjusts the current matrix so a default cube will
 * surround other objects.
 * 
 * @ingroup TransformNodes
 * 
 * @DESCRIPTION
 *   When traversed by an action, this node appends a transformation to the current
 *   transformation matrix so that a default size cube will surround the objects
 *   specified by its fields. Transform manipulators, such as SoHandleBoxManip, use
 *   these nodes to make themselves surround other objects.
 *   
 *   This node only recalculates after the invalidate() method has been called.
 *   Otherwise it uses a saved scale and translation.
 *   
 *   When calculating what to surround, the SoSurroundScale looks at the current path
 *   in the action and at its own field values. Then SoSurroundScale applies an
 *   SoGetBoundingBoxAction to the node that is #numNodesUpToContainer nodes
 *   above it on the path. SoSurroundScale also tells the action to reset the
 *   bounding box upon traversal of the node located #numNodesUpToReset nodes
 *   above it in the path. The SoSurroundScale then appends a translation and scale
 *   to the current transformation so that a default size SoCube will translate and
 *   scale to fit this bounding box.
 *   
 *   For example, when an SoHandleBoxManip wants to surround the objects it is going
 *   to move, the scene graph will look something like this:
 *   
 *   <PRE>
 *                    RootNode
 *          -------------------------
 *          |                       |
 *        handleBoxManip       movingStuff
 *          |
 *        handleBoxDragger
 *          |
 *        separator
 *        -----------------------------------
 *        |                 |               |
 *     motionMatrix    surroundScale     cubeGeom
 *    </PRE>
 *    The SoHandleBoxDragger wants to transform the @B cubeGeom @b so that it
 *   surrounds the @B movingStuff @b. So it sets the @B surroundScale @b fields
 *   to:
 *   
 *   <PRE> 
 *    numNodesUpToContainer = 4;
 *    numNodesUpToReset = 3;
 *    </PRE>
 *   The SoBoundingBoxAction will then be applied to @B RootNode @b, with a
 *   reset after traversing the SoHandleBoxManip. So the SoSurroundScale will
 *   surround the objects below @B separator @b, and to the right of
 *   @B handleBoxManip @b, producing the desired effect.
 * 
 * @FILE_FORMAT_DEFAULT
 *    SurroundScale {
 *    @TABLE_FILE_FORMAT
 *       @TR numNodesUpToContainer   @TD 0
 *       @TR numNodesUpToReset       @TD 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Accumulates scaling and translation transformations into the current
 *        transformation.
 * 
 *    SoGetMatrixAction @BR
 *        Returns the matrix corresponding to the scaling and translation.
 * 
 * 
 * @SEE_ALSO
 *    SoTransformation,
 *    SoTransformManip,
 *    SoCenterballDragger,
 *    SoCenterballManip,
 *    SoHandleBoxDragger,
 *    SoHandleBoxManip,
 *    SoJackDragger,
 *    SoJackManip,
 *    SoTabBoxDragger,
 *    SoTabBoxManip,
 *    SoTrackballDragger,
 *    SoTrackballManip,
 *    SoTransformBoxDragger,
 *    SoTransformBoxManip
 * 
 * 
 */ 

class INVENTOR_API SoSurroundScale : public SoTransformation {

  SO_NODE_HEADER(SoSurroundScale);

 public:

  /**
   * Creates a surround scale node with default settings.
   */
  SoSurroundScale();

  // Fields
  /**
   * When traversed by an action, if surroundScale needs to calculate a new box,
   * surroundScale looks at the current path in the action. It travels up this path a
   * distance of #numNodesUpToContainer and applies an SoGetBoundingBoxAction
   * to the node that it finds there.
   * 
   */
  SoSFInt32           numNodesUpToContainer;
  /**
   * Before applying the SoGetBoundingBoxAction (see the #numNodesUpToContainer
   * field above) the surroundScale node travels up the path a distance of
   * #numNodesUpToReset and tells the action to reset the bounding box upon
   * traversal of that node.
   * 
   */
  SoSFInt32           numNodesUpToReset;

  /**
   * If you call this, then next time an action is applied the node will re-calculate
   * its cached translation and scale values.
   */
  void invalidate();

 SoEXTENDER public:
  // Called by actions that need to change the state with a new matrix.
  void                doAction(SoAction *action);

  void setDoingTranslations( SbBool doEm ) { doTranslations = doEm; }
  SbBool isDoingTranslations() { return doTranslations; }

  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        pick(SoPickAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SB_THREAD_TLS_HEADER();

  const SbVec3f&      getScale()        { return cachedScale; }
  const SbVec3f&      getTranslation()  { return cachedTranslation; }

 protected:

  void updateMySurroundParams( SoAction *action, const SbMatrix &inv);

  void setIgnoreInBbox( SbBool newVal ) { ignoreInBbox = newVal; }
  SbBool isIgnoreInBbox() { return ignoreInBbox; }

  SbVec3f    cachedScale;
  SbVec3f    cachedInvScale;
  SbVec3f    cachedTranslation;
  SbBool     cacheOK;

  SbBool doTranslations;

  virtual ~SoSurroundScale();

  // Class static thread local storage
  struct MTstruct {
    SoGetBoundingBoxAction *bboxAction;
  };

  // Mutex to protect during updateMySurroundParams
  SbThreadMutex *m_mutex;

 private:
  SbBool ignoreInBbox;
};

#endif /* _SO_SURROUND_SCALE_ */


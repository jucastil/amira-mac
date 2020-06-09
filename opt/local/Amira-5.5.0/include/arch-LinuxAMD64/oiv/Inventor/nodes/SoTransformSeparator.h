/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_TRANSFORM_SEPARATOR_
#define  _SO_TRANSFORM_SEPARATOR_

#include <Inventor/nodes/SoGroup.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoTransformSeparator
//
//  TransformSeparator group node: isolates any transformations under
//  the node from the rest of the graph. In effect, this node acts as
//  a separator for just modeling transformations; it saves the model
//  matrix before traversing children and restores it afterwards.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Group node that saves and restores transformation state.
 * 
 * @ingroup GroupNodes
 * 
 * @DESCRIPTION
 *   This group node is similar to the SoSeparator node in that it saves state before
 *   traversing its children and restores it afterwards. However, it saves only the
 *   current transformation; all other state is left as is. This node can be useful
 *   for positioning a camera, since the transformations to the camera will not
 *   affect the rest of the scene, even though the camera will view the scene.
 *   Similarly, this node can be used to isolate transformations to light sources or
 *   other objects.
 * 
 * @FILE_FORMAT_DEFAULT
 *    TransformSeparator {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoGetMatrixAction,  SoRayPickAction @BR
 *        Saves the current transformation state, traverses all children, and restores
 *        the previous transformation state.
 *        Sets: SoModelMatrixElement, SoBBoxModelMatrixElement.
 * 
 * 
 * @SEE_ALSO
 *    SoResetTransform,
 *    SoTransformation
 * 
 * 
 */ 

class INVENTOR_API SoTransformSeparator : public SoGroup {

  SO_NODE_HEADER(SoTransformSeparator);

 public:
  // No fields

  /**
   * Creates a transform separator node with default settings.
   */
  SoTransformSeparator();

  /**
   * Constructor that takes approximate number of children.
   */
  SoTransformSeparator(int nChildren);

 SoEXTENDER public:
  // Implement actions
  virtual void        doAction(SoAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        getMatrix(SoGetMatrixAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoTransformSeparator();
};

#endif /* _SO_TRANSFORM_SEPARATOR_ */


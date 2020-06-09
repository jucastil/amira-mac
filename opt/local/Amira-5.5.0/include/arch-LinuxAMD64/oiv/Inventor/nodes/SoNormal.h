/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_NORMAL_
#define  _SO_NORMAL_

#include <Inventor/nodes/SoNode.h>
#include <Inventor/fields/SoMFVec3f.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNormal
//
//  Normal vector node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that defines surface normals for shapes.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines a set of 3D surface normal vectors to be used by vertex-based
 *   shape nodes that follow it in the scene graph. This node does not produce a
 *   visible result during rendering; it simply replaces the current normals in the
 *   rendering state for subsequent nodes to use. This node contains one
 *   multiple-valued field that contains the normal vectors.
 *   
 *   Surface normals are needed to compute lighting when the Phong lighting model is
 *   used. Most vertex-based shapes that use normals can compute default normals if
 *   none are specified, depending on the current normal binding.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Normal {
 *    @TABLE_FILE_FORMAT
 *       @TR vector   @TD [ ]
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction @BR
 *        Sets the current normals in the traversal state. Sets: SoNormalElement
 * 
 * 
 * @SEE_ALSO
 *    SoCoordinate3,
 *    SoLightModel,
 *    SoNormalBinding,
 *    SoVertexShape,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoNormal : public SoNode {

  SO_NODE_HEADER(SoNormal);

 public:
  // Fields
  /**
   * Surface normal vectors.
   * 
   */
  SoMFVec3f           vector;

  /**
   * Creates a surface normal node with default settings.
   */
  SoNormal();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoNormal();
};

#endif /* _SO_NORMAL_ */


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


#ifndef  _SO_COORDINATE3_
#define  _SO_COORDINATE3_

#include <Inventor/fields/SoMFVec3f.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCoordinate3
//
//  3-vector coordinate point node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Coordinate point node.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines a set of 3D coordinates to be used by subsequent vertex-based
 *   shape nodes (those derived from SoVertexShape) or shape nodes that use them as
 *   control points (such as NURBS curves and surfaces). This node does not produce a
 *   visible result during rendering; it simply replaces the current coordinates in
 *   the rendering state for subsequent nodes to use.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Coordinate3 {
 *    @TABLE_FILE_FORMAT
 *       @TR point   @TD 0 0 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoGetBoundingBoxAction,  SoRayPickAction @BR
 *        Sets coordinates in current traversal state.
 *        Sets: SoCoordinateElement
 * 
 * @SEE_ALSO
 *    SoCoordinate4,
 *    SoVertexShape,
 *    SoVertexProperty
 * 
 * 
 */ 

class INVENTOR_API SoCoordinate3 : public SoNode {

  SO_NODE_HEADER(SoCoordinate3);

 public:
  // Fields
  /**
   * Coordinate point(s).
   * 
   */
  SoMFVec3f point;

  /**
   * Creates a coordinate node with default settings.
   */
  SoCoordinate3();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoCoordinate3();
};

#endif /* _SO_COORDINATE3_ */


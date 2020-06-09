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


#ifndef  _SO_COORDINATE4_
#define  _SO_COORDINATE4_

#include <Inventor/fields/SoMFVec4f.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoCoordinate4
//
//  4-vector coordinate point node.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Rational coordinate point node.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   This node defines a set of 3D coordinates to be used by subsequent vertex-based
 *   shape nodes (those derived from SoVertexShape) or shape nodes that use them as
 *   control points (such as NURBS curves and surfaces). Coordinates are specifed as
 *   rational 4-vectors; the corresponding 3D point is computed by dividing the first
 *   three components by the fourth. This node does not produce a visible result
 *   during rendering; it simply replaces the current coordinates in the rendering
 *   state for subsequent nodes to use.
 *   
 *   This node exists primarily for use with NURBS curves and surfaces. However, it
 *   can be used to define coordinates for any vertex-based shape.
 * 
 * @FILE_FORMAT_DEFAULT
 *    Coordinate4 {
 *    @TABLE_FILE_FORMAT
 *       @TR point   @TD 0 0 0 1
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
 *    SoIndexedNurbsCurve,
 *    SoIndexedNurbsSurface,
 *    SoNurbsCurve,
 *    SoNurbsProfile,
 *    SoNurbsSurface,
 *    SoVertexShape
 * 
 * 
 */ 

class INVENTOR_API SoCoordinate4 : public SoNode {

  SO_NODE_HEADER(SoCoordinate4);

 public:
  // Fields
  /**
   * Coordinate point(s).
   * 
   */
  SoMFVec4f           point;

  /**
   * Creates a coordinate node with default settings.
   */
  SoCoordinate4();

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getPrimitiveCount(SoGetPrimitiveCountAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

 protected:
  virtual ~SoCoordinate4();
};

#endif /* _SO_COORDINATE4_ */


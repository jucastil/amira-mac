/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Dave Immel (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_INDEXED_NURBS_CURVE_
#define  _SO_INDEXED_NURBS_CURVE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoMFInt32.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/threads/SbThreadRWMutex.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoIndexedNurbsCurve
//
//  NURBS curve using an indexed list for the control points.
//
//////////////////////////////////////////////////////////////////////////////

class SoState;
class SoPrimitiveVertex;
class SoIndexedNurbsCurveCache;
class _SoNurbsNurbsTessellator;

/**
 * Indexed NURBS curve shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This class represents a NURBS curve based on the knot vector and the control
 *   points that you specify. The #knotVector field specifies a floating-point
 *   array of values; the values are the coordinates of the knot points in the curve,
 *   and you must enter them in non-decreasing order. The #numControlPoints
 *   field specifies the number of control points the curve will have and will use
 *   the current coordinates that are indexed from the #coordIndex field.
 *   
 *   You can get a curve of minimum order (2) by specifying two more knots than
 *   control points and having at least two control points. This curve would be a set
 *   of line segments connecting the control points together.
 *   
 *   You can get a curve of maximum order (8) by specifying 8 more knots than control
 *   points and having at least 8 control points. In this curve, each control point
 *   would have influence on a larger portion of the curve than with curves of lesser
 *   order.
 *   
 *   The control points of the curve are transformed by the current transformation
 *   matrix. The curve is drawn with the current lighting model and drawing style
 *   (drawing style FILLED is treated as LINES). The coordinates, normals, and
 *   texture coordinates of a NURBS curve are generated, so you cannot bind explicit
 *   normals or texture coordinates to a NURBS curve.
 *   
 *   The approximation of the curve by line segments is affected by the current
 *   complexity value.
 *
 *   Shape Antialiasing type is SoShape::LINES.
 * 
 * @FILE_FORMAT_DEFAULT
 *    IndexedNurbsCurve {
 *    @TABLE_FILE_FORMAT
 *       @TR numControlPoints   @TD 0
 *       @TR coordIndex         @TD 0
 *       @TR knotVector         @TD 0
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction @BR
 *        Draws the curve based on the current coordinates, material, and so on.
 * 
 *    SoRayPickAction @BR
 *        Picks the curve based on the current coordinates and transformation.
 * 
 *    SoGetBoundingBoxAction @BR
 *        Computes the bounding box that encloses all control points of the curve with
 *        the current transformation applied to them. Sets the center to the average of
 *        the control points.
 * 
 *    SoCallbackAction @BR
 *        If any line segment callbacks are registered with the action, they will be
 *        invoked for each successive segment approximating the curve.
 * 
 * 
 * @SEE_ALSO
 *    SoFullSceneAntialiasing,
 *    SoNurbsCurve,
 *    SoIndexedNurbsSurface
 * 
 * 
 */ 

class INVENTOR_API SoIndexedNurbsCurve : public SoShape {
  
  SO_NODE_HEADER(SoIndexedNurbsCurve);
  
 public:
  /**
   * Number of control points for the curve.
   */

  SoSFInt32 numControlPoints;
  /**
   * Coordinate indices for the control points.
   */
  SoMFInt32 coordIndex;

  /**
   * The knot vector for the curve. Values must be in non-decreasing order.
   */
  SoMFFloat knotVector;

  /**
   * Creates an indexed NURBS curve node with default settings.
   */
  SoIndexedNurbsCurve();

 SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  
  // Redefine this to tell open caches that they contain lines
  virtual void  getBoundingBox(SoGetBoundingBoxAction *action);
  
  // Computes bounding box of curve
  virtual void computeBBox(SoAction *action, SbBox3f &box,
                           SbVec3f &center);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  void sendPrimitive(SoAction *, SoPrimitiveVertex *);
  
 protected:
  // Generates triangles representing curve
  virtual void generatePrimitives(SoAction *action);
  
  ~SoIndexedNurbsCurve();
  
 private:
  SoIndexedNurbsCurveCache *nurbsCache;
  SbThreadRWMutex       *nurbsCacheMutex;
  int isValid(SoState *state);
  
  // Tessellate the surface
  void tesselateNURBS_G5G(SoAction *action, int32_t steps);
  // Render the surface
  void drawNURBS_G5G(SoAction *action, int32_t steps);
  
  void drawNURBS(_SoNurbsNurbsTessellator *render, SoState *state);
  void calcTotalMatrix(SoState *state, SbMatrix &totalMat);
  void multMatrix4d(SbMatrix &n, SbMatrix left, SbMatrix right);
  
  // This callback gets details from the NURBS library
  static void primCB(SoAction *, SoPrimitiveVertex *, void *);
  
  // Functions to compute complexity from Complexity
  // and decimation elements
  int computeSteps(SoState *state);
  int computePixelTolerance(SoState *state);
  
  void createNurbsCache(SoState *state);
};

#endif /* _SO_INDEXED_NURBS_CURVE_ */


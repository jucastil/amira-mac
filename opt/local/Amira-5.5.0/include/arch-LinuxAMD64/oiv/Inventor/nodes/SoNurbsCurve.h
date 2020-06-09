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


#ifndef  _SO_NURBS_CURVE_
#define  _SO_NURBS_CURVE_

#include <Inventor/SbLinear.h>
#include <Inventor/fields/SoMFFloat.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/nodes/SoShape.h>
#include <Inventor/threads/SbThreadRWMutex.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoNurbsCurve
//
//  NURBS curve. The curve consists of a knot vector and order for
//  the U parametric directions.  The control points for the curve
//  are obtained from the current coordinates.
//
//////////////////////////////////////////////////////////////////////////////

class SoState;
class SoPrimitiveVertex;
class SoNurbsCurveCache;
class _SoNurbsNurbsTessellator;

/**
 * NURBS curve shape node.
 * 
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This class represents a NURBS curve, based on the knot vector and the control
 *   points that you specify. The #knotVector field specifies a floating-point
 *   array of values; the values are the coordinates of the knot points in the curve,
 *   and you must enter them in non-decreasing order. The curve will use the first
 *   #numControlPoints values in the current coordinates as control points.
 *   
 *   If you specify @B n @b knots, you can specify up to @B n-8 @b control points.
 *   The number of knots minus the number of control points is known as the order of
 *   the curve. A NURBS curve can have an order of up to 8.
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
 *    NurbsCurve {
 *    @TABLE_FILE_FORMAT
 *       @TR numControlPoints   @TD 0
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
 *    SoIndexedNurbsCurve,
 *    SoNurbsSurface
 * 
 * 
 */ 

class INVENTOR_API SoNurbsCurve : public SoShape {
  
  SO_NODE_HEADER(SoNurbsCurve);
  
 public:
  /**
   * Number of control points.
   */
  SoSFInt32 numControlPoints;

  /**
   * The knot vector.
   */
  SoMFFloat knotVector;

  /**
   * Creates a NURBS curve node with default settings.
   */
  SoNurbsCurve();

 SoEXTENDER public:
  virtual void GLRender(SoGLRenderAction *action);
  virtual void rayPick(SoRayPickAction *action);
  virtual void getPrimitiveCount(SoGetPrimitiveCountAction *action);
  
  // Redefine this to tell open caches that they contain lines
  virtual void getBoundingBox(SoGetBoundingBoxAction *action);

  // Computes bounding box of curve
  virtual void computeBBox(SoAction *action, SbBox3f &box,
                           SbVec3f &center);
  
 SoINTERNAL public:
  static void initClass();
  static void exitClass();
  void sendPrimitive(SoAction *, SoPrimitiveVertex *);
  
 protected:
  // Generates triangles representing a sphere
  virtual void generatePrimitives(SoAction *action);
  
  ~SoNurbsCurve();
  
 private:
  SoNurbsCurveCache *nurbsCache;
  SbThreadRWMutex       *nurbsCacheMutex;
  int isValid(SoState *state);
  
  // Tesselate the surface
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

#endif /* _SO_NURBS_CURVE_ */


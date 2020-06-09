/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Thibaut Andrieu (Jan 2011)
**=======================================================================*/

#if !defined _SO_CSG_SHAPE_H_
#define _SO_CSG_SHAPE_H_

#include <Inventor/nodes/SoShape.h>
#include <Inventor/fields/SoSFNode.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <Inventor/threads/SbThreadMutex.h>

class SoFaceSet;
class SoCallbackAction;

//@TOBEWRAPPED
/**
 * @VSGEXT Shape defined by a binary boolean operation on two sub scene graphs.
 *
 * @ingroup ShapeNodes
 * 
 * @DESCRIPTION
 *   This shape represents the result of a Constructive Solid Geometry (CSG)
 *   operation applied on the two scene graphs #leftOperand and #rightOperand.
 *   Constructive solid geometry allows the application to create a (potentially)
 *   complex object by using Boolean operators to combine (relatively) simple objects.
 *
 *   The left and right operands can be any scene graph, including other SoCSGShape
 *   nodes. You can define a complex CSG geometry by creating a tree using multiple
 *   SoCSGShape nodes. The specified scene graph's shapes must be closed (no holes)
 *   and CCW-orientated (all triangles composing shapes must be counter-clockwise).
 *
 *   Each time an operand is modified, a CSG Operation is performed.
 *   Keep this in mind if you create a CSGTree (SoCSGShape which contains other
 *   SoCSGShapes), especially if you use associative and commutative operations 
 *   (only additions or only intersections) because the result of such operations 
 *   does not depend on the tree ( (A + B) + C = A + (B + C) ).
 *   In this case, try to build your tree by putting the most often modified 
 *   nodes at the top of the tree. 
 *
 *   For example, a tree optimized for modification on first node (@B N1 @b) will 
 *   look like this:
 *
 * <PRE>
 *     S
 *   __|__S
 *  |   __|__S
 * N1  |   __|__S
 *    N2  |   __|__
 *       N3  |     |
 *          N4    N5
 * </PRE>
 *
 *   Where S are SoCSGShape and N1, N2, ... are ordinary nodes. In this case, 
 *   a modification on N1 will need only 1 csgOperation, whereas a modificaion 
 *   on N5 will need 4 csgOperations to regenerate the resulting shape.
 *
 *   A tree optimized for random modification will try to minimize its depth:
 *
 * <PRE>
 *                   S
 *           ________|_________
 *          |                  |
 *      ____S____          ____S____
 *     |         |        |         |
 *   __S__       N3       N4        N5
 *  |     |
 *  N1    N2 
 * </PRE>
 *
 * In this case, any modification will require at most 3 CSG Operations.
 *
 * @NODE_SINCE_OIV 8.6
 * 
 * @FILE_FORMAT_DEFAULT
 *    CSGShape {
 *    @TABLE_FILE_FORMAT
 *       @TR leftOperand  @TD NULL
 *       @TR rightOperand @TD NULL
 *       @TR csgOperation @TD ADD
 *    @TABLE_END
 *    }
 *
 * @NOTES
 *   - CSG means Constructive Solid Geometry.
 *   - Some operations are not commutative (A - B) != (B - A).
 *
 * @B LIMITATIONS @b
 *   Only vertices are handled in the generated shape, none of the normal, color,
 *   texCoord properties of the left or right operands are taken into account.
 *
 * @SEE_ALSO
 *   SoShape
 *   
 *
 */
class INVENTOR_API SoCSGShape : public SoShape
{
  SO_NODE_HEADER( SoCSGShape );

public:

  /** Constructor */
  SoCSGShape();

  /** CSG operation to be used. */
  enum CsgOperationType
  {
    /** leftOperand union rightOperand. Remove useless faces and create edges if necessary. */
    ADD,
    /** LeftOperand - rightOperand. Remove useless faces and create edges if necessary. */
    SUB,  
    /** LeftOperand intersect rightOperand. Remove useless faces and create edges if necessary. */
    INTERSECTION,
    /** Keep only leftOperand. */
    LEFT_ONLY, 
    /** Keep only rightOperand. */
    RIGHT_ONLY,
    /** Keep nothing (result will be empty). May be useful for debugging. */
    NOTHING,
    /** Keep left and right primitives (concatenate all resulting faces). May be useful for debugging. */
    ALL
  };

  /** Geometry scene graph to be used as left operand for the Boolean operation. */ 
  SoSFNode leftOperand;
  
  /** Geometry scene graph to be used as right operand for the Boolean operation. */ 
  SoSFNode rightOperand;

  /** CSG boolean operation to apply.
   *  Use enum #CsgOperationType. Default is ADD. 
   */
  SoSFEnum csgOperation;

SoEXTENDER public:

  // Implement actions

  /** @copydoc SoShape::doAction */
  virtual void doAction( SoAction *action );

  /** @copydoc SoShape::callback */
  virtual void callback( SoCallbackAction *action );

  /** @copydoc SoShape::GLRender */
  virtual void GLRender( SoGLRenderAction *action );

  /** @copydoc SoShape::rayPick */
  virtual void rayPick( SoRayPickAction *action );

  /** @copydoc SoShape::computeBBox */
  virtual void computeBBox( SoAction *action, SbBox3f &box, SbVec3f &center );

  /** @copydoc SoShape::computeBBox */
  virtual void computeBBox(SoAction *action, SbXfBox3d &box, SbVec3d &center);

  /** @copydoc SoShape::getPrimitiveCount */
  virtual void getPrimitiveCount( SoGetPrimitiveCountAction *action );

  /** 
   * Set operation to use in case of CSG operation failed or CSGLib is not available. Default is NOTHING.
   * Must be one of LEFT_ONLY, RIGHT_ONLY, NOTHING or ALL. 
   */
  static void setRescueOperation( CsgOperationType op );

SoINTERNAL public:

  /** Register in database */
  static void initClass();

  /** Unregister from database */
  static void exitClass();


protected:
  /** Destructor */
  virtual ~SoCSGShape();

  /** catch some fields changes */
  virtual void notify( SoNotList *list );

  /** sentinel check */
  virtual void generatePrimitives ( SoAction *action );

private:

  /** Update m_shape if needed and return it. */
  SoFaceSet* getShape();

  /** Update m_trianglesLeft with leftOperand using a triangleClabback. */
  void updateLeftTriangles();

  /** Update m_trianglesRight with rightOperand using a triangleClabback. */
  void updateRightTriangles();

  /** 
   * Update m_triangles and m_shape using csgOperation between  m_trianglesLeft 
   * and m_trianglesRight. Of course, m_trianglesLeft and m_trianglesRight must
   * be up to date.
   */
  void updateResult();

  /** Callback used by triangleCallbackAction. */
  static void pushTriangleCallback(void* vec, 
                            SoCallbackAction* cb, 
                            const SoPrimitiveVertex* v1, 
                            const SoPrimitiveVertex* v2, 
                            const SoPrimitiveVertex* v3);

  /** 
   * Compute operation between trianglesLeft and triangleRight. Result is in trianglesResult. 
   * return success.
   */
  static bool computeCSG(const std::vector<SoPrimitiveVertex>& trianglesLeft, 
                        const std::vector<SoPrimitiveVertex>& trianglesRight, 
                        const CsgOperationType& operation, 
                        std::vector<SoPrimitiveVertex>& trianglesResult);

  /** Does m_trianglesLeft needs to be updated ? */
  bool m_needUpdateLeftTriangles;

  /** Triangles of left operand. Updated when leftOperand has changed. */
  std::vector<SoPrimitiveVertex> m_trianglesLeft;

  /** Does m_trianglesRight needs to be updated ? */
  bool m_needUpdateRightTriangles;

  /** Triangles of right operand. Updated when rightOperand has changed. */
  std::vector<SoPrimitiveVertex> m_trianglesRight;

  /** Does m_triangles needs to be updated ? */
  bool m_needUpdateResultTriangles;

  /** 
   * Triangles of result. This correspond to m_shape triangles.
   * m_shape must be updated every time m_triangles is updated.
   * Updated when one of operand, or operator has changed. 
   */
  std::vector<SoPrimitiveVertex> m_triangles;

  /**
   * Shape representing result of CSG operation. It will be updated when needed
   * And all actions will be redirected on it.
   * Don't call directly m_shape. Use the getShape() method instead.
   */
  SoFaceSet* m_shape;

  /** Mutex to protect access to m_shape */
  SbThreadMutex m_mutex;

  /** Operation used in case of CSG operation failed. See #setRescueOperation. */
  static CsgOperationType s_rescueOp;

};

#endif // _SO_CSG_SHAPE_H_

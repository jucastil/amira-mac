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


#ifndef  _SO_SHAPE_HINTS_
#define  _SO_SHAPE_HINTS_

#include <Inventor/elements/SoGLShapeHintsElement.h>
#include <Inventor/fields/SoSFEnum.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFBool.h>
#include <Inventor/nodes/SoNode.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoShapeHints
//
//  This node is used to give hints about subsequent shapes defined in
//  a scene graph. It allows Inventor to provide or optimize certain
//  features (such as back-face culling and two-sided lighting) based
//  on information about shapes. The vertexOrdering, faceType, and
//  shapeType fields hold this information. There is also a crease
//  angle field, which is used when default normals are generated for
//  a polyhedral shape. It defines the smallest edge angle that will
//  be shaded as a crease (faceted), rather than as smooth.
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node that provides hints about shapes.
 * 
 * @ingroup PropertyNodes
 * 
 * @DESCRIPTION
 *   By default, Open Inventor assumes very little about the shapes it renders. You
 *   can use the SoShapeHints node to indicate that vertex-based shapes (those
 *   derived from SoVertexShape) are solid, contain ordered vertices, or contain
 *   convex faces. For fastest rendering, specify SOLID, COUNTERCLOCKWISE, CONVEX
 *   shapes.
 *   
 *   These hints allow Open Inventor to optimize certain rendering features.
 *   Optimizations that may be performed include enabling back-face culling and
 *   disabling two-sided lighting. For example, if an object is solid and has ordered
 *   vertices, Open Inventor turns on backface culling and turns off two-sided
 *   lighting. If the object is not solid but has ordered vertices, it turns off
 *   backface culling and turns on two-sided lighting. In all other cases, both
 *   backface culling and two-sided lighting are off.
 *   
 *   This node allows the creation of polygons with holes. 
 *   See the #windingType field description, SoIndexedFaceSet, and 
 *   SoFaceSet for details.
 *
 *   This node also allows subsequent indexed shapes to use 
 *   Vertex Buffer Objects to speed up
 *   rendering under certain circumstances. See the #useVBO field
 *   description for details.
 *
 *   The SoShapeHints node also affects how default normals are generated. When a node
 *   derived from SoVertexShape has to generate default normals, it uses the
 *   #creaseAngle field to determine which edges should be smooth-shaded and
 *   which ones should have a sharp crease. The crease angle is the angle between
 *   surface normals on adjacent polygons. For example, a crease angle of .5 radians
 *   means that an edge between two adjacent polygonal faces will be smooth shaded if
 *   the normals to the two faces form an angle that is less than .5 radians (about
 *   30 degrees). Otherwise, it will be faceted. Normal generation is fastest when
 *   the #creaseAngle is 0 (the default), producing one normal per facet. A
 *   #creaseAngle of pi produces one averaged normal per vertex.
 * 
 * @FILE_FORMAT_DEFAULT
 *    ShapeHints {
 *    @TABLE_FILE_FORMAT
 *       @TR vertexOrdering   @TD UNKNOWN_ORDERING
 *       @TR shapeType        @TD UNKNOWN_SHAPE_TYPE
 *       @TR faceType         @TD CONVEX
 *       @TR windingType      @TD NO_WINDING_TYPE
 *       @TR creaseAngle      @TD 0
 *       @TR neighboorTolerance @TD 10000
 *       @TR useVBO           @TD TRUE
 *    @TABLE_END
 *    }
 * 
 * @ACTION_BEHAVIOR
 *    SoGLRenderAction,  SoCallbackAction,  SoRayPickAction,  SoGetBoundingBoxAction @BR
 *        Sets the state to contain the hints; sets up optimizations based on the
 *        hints. Sets: SoShapeHintsElement, SoCreaseAngleElement, SoNeighborToleranceElement
 * 
 * 
 * @SEE_ALSO
 *    SoVertexShape SoIndexedFaceSet SoFaceSet
 * 
 * 
 */ 

class INVENTOR_API SoShapeHints : public SoNode {

  SO_NODE_HEADER(SoShapeHints);

 public:
  /**
   * Hints about ordering of face vertices: if ordering of all
   * vertices of all faces is known to be consistent when viewed
   * from "outside" shape or not.
   */
  enum VertexOrdering {
    /**
     *  Ordering of vertices is unknown 
     */
    UNKNOWN_ORDERING = SoShapeHintsElement::UNKNOWN_ORDERING,
    /**
     *  Face vertices are ordered clockwise (from the outside) 
     */
    CLOCKWISE        = SoShapeHintsElement::CLOCKWISE,
    /**
     *  Face vertices are ordered counterclockwise (from the outside) 
     */
    COUNTERCLOCKWISE = SoShapeHintsElement::COUNTERCLOCKWISE
  };

  /**
   * Hints about entire shape: if shape is known to be a solid
   * object, as opposed to a surface.
   */
  enum ShapeType {
    /**
     *  Nothing is known about the shape 
     */
    UNKNOWN_SHAPE_TYPE = SoShapeHintsElement::UNKNOWN_SHAPE_TYPE,
    /**
     *  The shape encloses a volume 
     */
    SOLID              = SoShapeHintsElement::SOLID
  };

  /** Hints about faces of shape: if all faces are known to be convex or not. */
  enum FaceType {
    /**
     *  Nothing is known about faces 
     */
    UNKNOWN_FACE_TYPE = SoShapeHintsElement::UNKNOWN_FACE_TYPE,
    /**
     *  All faces are convex 
     */
    CONVEX            = SoShapeHintsElement::CONVEX
  };
    
  /** Winding type possible values. */
  enum WindingType {
    /**
     *
     * Draw without holes (default).
     */
    NO_WINDING_TYPE = SoShapeHintsElement::NO_WINDING_TYPE,
    /**
     * 
     * Regions with odd winding numbers are filled.
     * This is the most commonly used winding rule.
     */
    ODD_TYPE = SoShapeHintsElement::ODD_TYPE,
    /**
     * 
     * Regions with non-zero winding numbers are filled.   
     */
    NON_ZERO_TYPE = SoShapeHintsElement::NON_ZERO_TYPE,
    /**
     * 
     * Regions with positive winding numbers are filled.
     */
    POSITIVE_TYPE = SoShapeHintsElement::POSITIVE_TYPE,
    /**
     * 
     * Regions with negative winding numbers are filled.
     */
    NEGATIVE_TYPE = SoShapeHintsElement::NEGATIVE_TYPE,
    /**
     * 
     * Regions with winding numbers whose absolute value is
     * greater than or equal to two are filled.
     */
    ABS_GEQ_TWO_TYPE = SoShapeHintsElement::ABS_GEQ_TWO_TYPE
  };

  /**
   * Indicates how the vertices of faces are ordered. CLOCKWISE ordering means that
   * the vertices of each face form a clockwise loop around the face, when viewed
   * from the outside (the side toward which the normal points).
   * Use enum #VertexOrdering. Default is UNKNOWN_ORDERING.
   */
  SoSFEnum vertexOrdering;
  /**
   * Indicates whether the shape is known to enclose a volume (SOLID) or not. If the
   * inside (the side away from the surface normal) of any part of the shape is
   * visible, the shape is not solid.
   * Use enum #ShapeType. Default is UNKNOWN_SHAPE_TYPE.
   */
  SoSFEnum shapeType;
  /**
   * Indicates whether each face is convex. Because the penalty for non-convex faces
   * is very steep (faces must be triangulated expensively), the default assumes all
   * faces are convex. Therefore, shapes with concave faces may not be displayed
   * correctly unless this hint is set to UNKNOWN_FACE_TYPE.
   * Use enum #FaceType. Default is CONVEX.
   */
  SoSFEnum faceType;

  /**
   * Indicates the winding rule used to define holes in a polygon. It is used by 
   * SoIndexedFaceSet and SoFaceSet to determine which parts of the polygon
   * are on the interior and which are on the exterior and should not be filled.
   * By default this field value is NO_WINDING_TYPE, that is, no winding rules
   * are used, so there are no holes. Use enum #WindingType.
   *  
   * For a single contour, the winding number of a point is the signed number of 
   * revolutions we make around that point while traveling once around the contour
   * (where a counterclockwise revolution is positive and a clockwise revolution is
   * negative). When there are several contours, the individual winding numbers are summed. 
   * This procedure associates a signed integer value with each point in the plane. Note 
   * that the winding number is the same for all points in a single region. 

   * The following figure
   * shows three sets of contours and winding numbers for points inside those contours. In 
   * the left set, all three contours are counterclockwise, so each nested interior region 
   * adds one to the winding number. For the middle set, the two interior contours are drawn 
   * clockwise, so the winding number decreases and actually becomes negative. 
   * @TABLE_0B
   *         @TR @IMAGE windingRules1.jpg  
   * @TABLE_END
   * The winding rule classifies a region as inside if its winding number belongs 
   * to the chosen category (odd, nonzero, positive, negative, or "absolute value 
   * of greater than or equal to two"). The odd and nonzero rules are common ways 
   * to define the interior. The positive, negative, and "absolute value>=2" winding 
   * rules have some limited use for polygon CSG (computational solid geometry) operations.
   * The four sets of contours shown in the following figure are used with different
   * winding rule properties to see their effects. For each winding rule, the dark areas
   * represent interiors. Note the effect of clockwise and counterclockwise winding.
   *
   * @TABLE_0B
   *         @TR @IMAGE windingRules2.jpg  
   * @TABLE_END
   *
   * NOTE: In LINES drawing style (see SoDrawStyle), if #windingType is not 
   * NO_WINDING_TYPE, or if
   * #faceType is UNKNOWN_FACE_TYPE, the edges of the tessellated triangles will be drawn.
   *
   * @FIELD_SINCE_OIV 4.0
   */
  SoSFEnum windingType;

  /**
   * Setting this field to TRUE allows subsequent indexed or non-indexed shapes (any shape
   * that inherit SoShape) to use Vertex Buffer Objects (VBO) to speed up rendering.
   * Vertex Buffer Object (ARB_vertex_buffer_object) is a standard feature of 
   * OpenGL since version 1.5 and an extension feature in
   * previous OpenGL versions. VBO provides a mechanism to store
   * vertices and other data in high performance memory on the graphics board.
   * Open Inventor shapes will use these buffers only in the case of Vertex Array usage 
   * (see these classes for details).
   *
   * Vertex Buffer Objects should be used only for non cached shapes (i.e., shapes which are
   * not in a display list) because:
   *    1) There is no performance gain for cached shapes, and
   *    2) Vertex Buffer Objects consume graphics board memory.
   *
   * Using Vertex Buffer Objects can significantly improve rendering performance for shapes that
   * are frequently modified. It also avoids building display lists which can reduce the latency 
   * of first frame rendering and reduce host memory usage.
   *
   * If this OpenGL feature (ARB_vertex_buffer_object) is not available, 
   * setting this field to TRUE has no effect.
   *
   * Default value is TRUE since Open Inventor 8.1.
   * The default field value can be set using the OIV_FORCE_USE_VBO environment variable
   * (see SoPreferences).
   *
   * @FIELD_SINCE_OIV 5.0
   */
  SoSFBool useVBO ;

  /**
   * Indicates the minimum angle (in radians) between two adjacent face normals
   * required to form a sharp crease at the edge when normal vectors are computed
   * automatically by Open Inventor.  It has no effect when normal vectors are
   * explicitly provided by the application.
   */
  SoSFFloat creaseAngle;

  /** 
   * Specifies the tolerance value to use when default normals are computed. 
   * Specifically it determines which (other) points in the shape are close 
   * enough to influence the normal at each vertex.  
   * Setting a smaller tolerance value will select a smaller number of points
   * and can reduce the time required for computing normals on very large,
   * very dense geometry.
   * 
   * The default is 10e-5.
   *
   * If the OIV_NORMGEN_TOLERANCE environment variable is set, the default is
   * 1/OIV_NORMGEN_TOLERANCE.
   *
   * @FIELD_SINCE_OIV 8.0
   */
  SoSFFloat neighborTolerance;

  /**
   * Creates a shape hints node with default settings.
   */
  SoShapeHints();

  /**
   * Indicates if Vertex Buffer Object (VBO) is supported by your graphics board.
   */
  static SbBool isVBOSupported() ;

  /**
   * Set the state of the override field.
   * see SoNode::setOverride doc.
   */
  inline virtual void setOverride(const SbBool state)
  { override.setValue(state); }

  /**
   * Returns the state of the override field.
   */
  inline virtual SbBool isOverride() const
  { return override.getValue(); }

 SoEXTENDER public:
  virtual void        doAction(SoAction *action);
  virtual void        GLRender(SoGLRenderAction *action);
  virtual void        callback(SoCallbackAction *action);
  virtual void        pick(SoPickAction *action);
  virtual void        getBoundingBox(SoGetBoundingBoxAction *action);

 SoINTERNAL public:
  static void         initClass();
  static void         exitClass();

  SoSFBool override;

 protected:
  virtual ~SoShapeHints();

 private:
  // Does regular doAction stuff, also sets shapehints element
  void                doAction2(SoAction *action);
};

#endif /* _SO_SHAPE_HINTS_ */


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


#ifndef  _SO_SHAPE_HINTS_ELEMENT
#define  _SO_SHAPE_HINTS_ELEMENT

#include <Inventor/elements/SoReplacedElement.h>

/**
*   Stores the current shape hints.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores current shape hints.
*   All hints must be set at the same time; to
*   leave any hint as is, use the "AS_IS" enum value.
*
*   @SEE_ALSO
*   SoShapeHints
*/

SoEXTENDER_Documented class INVENTOR_API SoShapeHintsElement : public SoElement {

  SO_ELEMENT_HEADER(SoShapeHintsElement);

 public:
 /**
 *  Hints about ordering of face vertices.
 */
 enum VertexOrdering {
 /**
 *  No ordering info is known.
 */
 UNKNOWN_ORDERING,
 /**
 *  Vertices are ordered CW around faces.
 */
 CLOCKWISE,
 /**
 *  Vertices are ordered CCW around faces.
 */
 COUNTERCLOCKWISE,
 /**
 *  Indicates to set() to leave as is.
 */
 ORDERING_AS_IS
  };
 /**
 *  Hints about entire shape.
 */
 enum ShapeType {
 /**
 *  Nothing is known about shape.
 */
 UNKNOWN_SHAPE_TYPE,
 /**
 *  Shape is known to be solid.
 */
 SOLID,
 /**
 *  Indicates to set() to leave as is.
 */
 SHAPE_TYPE_AS_IS  };

 /**
 *  Hints about faces of shape.
 */
 enum FaceType {
 /**
 *  Nothing is known about faces.
 */
 UNKNOWN_FACE_TYPE,
 /**
 *  Faces are all convex.
 */
 CONVEX,
 /**
 *  Indicates to set() to leave as is.
 */
 FACE_TYPE_AS_IS
  };

 /**
 *  Hints about winding type
 */
 enum WindingType {
 /**
 *  No hole.
 */
    NO_WINDING_TYPE,
    ODD_TYPE,
    NON_ZERO_TYPE,
    POSITIVE_TYPE,
    NEGATIVE_TYPE,
    ABS_GEQ_TWO_TYPE
  };

  /**
  *  Sets the current shape hints in the state. Calls virtual
  *  method that subclasses can override.
  */
  static void         set(SoState *state, VertexOrdering vertexOrdering,
                          ShapeType shapeType, FaceType faceType);

  /**
  *  Sets the current shape hints in the state. Only for the winding type.
  *  Call virtual method that subclasses can override.
  */
  static void         set(SoState *state, WindingType windingType);

  /**
  *  Sets the current shape hints in the state. Only for VBO usage.
  */
  static void         set(SoState *state, SbBool useVBO) ;

#ifndef IV_STRICT
  /**
  *  Sets the current shape hints in the state.
  */
  static void         set(SoState *state, SoNode *,
                          VertexOrdering vertexOrdering,
                          ShapeType shapeType, FaceType faceType)
    { set(state, vertexOrdering, shapeType, faceType); }

  /**
  *
  */
  static void         set(SoState *state, SoNode *,WindingType windingType)
    { set(state,windingType); }

  /**
  *  Indicates if VBO is used from the state.
  */
  static void         set(SoState *state, SoNode *, SbBool useVBO)
    { set(state,useVBO); }
#endif

  /**
  *  Returns current shape hints from the state.
  */
  static void         get(SoState *state,
                          VertexOrdering &vertexOrdering,
                          ShapeType &shapeType, FaceType &faceType);

  /**
  *  Return current shape winding type from the state.
  */
  static void         get(SoState *state, WindingType &windingType );

  /**
  *  Indicates if VBO is used from the state.
  */
  static SbBool       isVBOUsed(SoState *state) ;

  /**
  *  Returns default hint.
  */
  static VertexOrdering getDefaultVertexOrdering();
  /**
  *  Returns default hint.
  */
  static ShapeType      getDefaultShapeType();
  /**
  *  Returns default hint.
  */
  static FaceType       getDefaultFaceType();
  /**
  *  Returns default hint.
  */
  static WindingType    getDefaultWindingType();
  /**
  *  Returns default hint.
  */
  static SbBool         getDefaultVBOUsage() ;

  /**
  *  Push copies the values from the previous element, so set
  *  doesn't have to set them if they are set AS_IS.
  */
  virtual void        push(SoState *state);

  /**
  *  Returns TRUE if the hints match in both elements.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoShapeHintsElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

  static bool isTwoSidedLighting(SoState *state);

 protected:
  // Virtual set methods that subclasses can override.
  virtual void        setElt(SoState *state, VertexOrdering vertexOrdering,
                             ShapeType shapeType, FaceType faceType);

  virtual void        setElt(SoState *state, WindingType windingType);

  VertexOrdering      vertexOrdering;
  ShapeType           shapeType;
  FaceType            faceType;
  WindingType         windingType;
  SbBool              useVBO ;

  virtual ~SoShapeHintsElement();
};

#endif /* _SO_SHAPE_HINTS_ELEMENT */


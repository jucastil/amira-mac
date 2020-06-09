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


#ifndef  _SO_LOCAL_BBOX_MATRIX_ELEMENT
#define  _SO_LOCAL_BBOX_MATRIX_ELEMENT

#include <Inventor/elements/SoModelMatrixElement.h>

/**
*   Stores the transformation matrix from object space to
*   some local coordinate space during application of an
*   SoGetBoundingBoxAction.
* 
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the transformation matrix from object space to
*   some local coordinate space during application of an
*   SoGetBoundingBoxAction. This element is needed to allow separators
*   (and other caching nodes) to store cached bounding boxes in their
*   own local space. Shapes that extend the current bounding box
*   computed by the action use this matrix to transform the bounding
*   box into local space. Separators cache this box, then transform it
*   into the next local space up the hierarchy.
* 
*   Because this element is set to identity by separators before
*   traversing their children, it can never have an affect on any
*   caching separator that it is not under. Therefore, it should
*   never be tested for cache invalidation, so its matches() method
*   prints an error message and returns FALSE. It also means that it
*   does not have to save node id's so there are no nodes passed in to
*   any of the methods.
* 
*   @SEE_ALSO
*/

SoEXTENDER_Documented class INVENTOR_API SoLocalBBoxMatrixElement : public SoElement {

  SO_ELEMENT_HEADER(SoLocalBBoxMatrixElement);

 public:
  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void        push(SoState *state);

  /**
  *  Sets the local matrix to the identity matrix.
  */
  static void         makeIdentity(SoState *state);

  /**
  *  Sets the local matrix to the given matrix.
  */
  static void         set(SoState *state, const SbMatrix &matrix);

  /**
  *  Multiplies the given matrix into the local matrix.
  */
  static void         mult(SoState *state, const SbMatrix &matrix);

  /**
  *  Multiplies a matrix that performs the specified
  *  transformation into the local matrix.
  */
  static void         translateBy(SoState *state,const SbVec3f &translation);
  /**
  *  Multiplies a matrix that performs the specified
  *  transformation into the local matrix.
  */
  static void         rotateBy(SoState *state, const SbRotation &rotation);
  /**
  *  Multiplies a matrix that performs the specified
  *  transformation into the local matrix.
  */
  static void         scaleBy(SoState *state, const SbVec3f &scaleFactor);

  /**
  *  This method is used by the TransformSeparator node.
  */
  static SbMatrix     pushMatrix(SoState *state);
  /**
  *  This method is used by the TransformSeparator node.
  */
  static void         popMatrix(SoState *state, const SbMatrix &m);

  /**
  *  Resets all current instances in the state to identity.
  */
  static void         resetAll(SoState *state);

  /**
  *  Returns current matrix from the state.
  */
  static const SbMatrix &     get(SoState *state);

  /**
  *  Prints error message and returns FALSE (see class header comment).
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
  // Initializes the SoLocalBBoxMatrixElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbMatrix            localMatrix;

  virtual ~SoLocalBBoxMatrixElement();

 private:
  // This stores the inverse of the current model matrix at the time
  // the element is created. It is needed in case the element is set
  // to contain a new matrix, since we want to factor out the
  // effects of the non-local part of the matrix.
  SbMatrix            modelInverseMatrix;
};

#endif /* _SO_LOCAL_BBOX_MATRIX_ELEMENT */

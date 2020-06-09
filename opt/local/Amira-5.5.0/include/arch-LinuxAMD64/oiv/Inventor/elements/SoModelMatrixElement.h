/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MODEL_MATRIX_ELEMENT
#define  _SO_MODEL_MATRIX_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>

/**
*   Stores the current model matrix.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current model matrix - the cumulative
*   transformation applied to subsequent shapes. Because the matrix is
*   cumulative, this class is derived from SoAccumulatedElement. The
*   set() method replaces the current matrix, while all the others
*   (mult(), translateBy(), etc.) multiply into it. Node id's of the
*   nodes that affect the element are accumulated properly.
*
*   This element also stores the current view-volume culling
*   transformation, which is normally the view*projection matrices
*   (set by cameras), but which may be modified by sophisticated
*   culling schemes.
*
*   @SEE_ALSO
*   SoMatrixTransform, SoRotation, SoRotationXYZ, SoScale,
*   SoTransform, SoTranslation, SoUnits, SoVRMLTransform
*/

SoEXTENDER_Documented class INVENTOR_API SoModelMatrixElement : public SoAccumulatedElement {

  SO_ELEMENT_HEADER(SoModelMatrixElement);

 public:
  /**
  *  Override standard matches to invalidate on cull-test.
  */
  virtual SbBool      matches(const SoElement *elt) const;


  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void        push(SoState *state);

  /**
  *  Sets the model matrix to the identity matrix.
  */
  static void         makeIdentity(SoState *state, SoNode *node);

  /**
  *  Sets the model matrix to the given matrix.
  *  This method will (indirectly) call glLoadMatrix with the
  *  new matrix unless the 'sendToGL' parameter is explicitly FALSE.
  */
  static void         set(SoState *state, SoNode *node,
                          const SbMatrix &matrix, SbBool sendToGL = TRUE);

  /**
  *  Multiplies the given matrix into the model matrix.
  */
  static void         mult(SoState *state, SoNode *node,
                           const SbMatrix &matrix);

  /**
  *  This multiplies a matrix that performs the specified
  *  transformation into the model matrix.
  */
  static void         translateBy(SoState *state, SoNode *node,
                                  const SbVec3f &translation);
  /**
  *  This multiplies a matrix that performs the specified
  *  transformation into the model matrix.
  */
  static void         rotateBy(SoState *state, SoNode *node,
                               const SbRotation &rotation);
  /**
  *  This multiplies a matrix that performs the specified
  *  transformation into the model matrix.
  */
  static void         scaleBy(SoState *state, SoNode *node,
                              const SbVec3f &scaleFactor);

  /**
  *  This method is used by the TransformSeparator node.
  *  WARNING!  For proper caching behavior, the matrix returned by
  *  ::pushMatrix() must be used ONLY as a later argument to
  *  ::popMatrix(), and you must NOT modify the matrix between the
  *  push and the pop.  If you need the matrix for any other reason,
  *  you MUST use the ::get() routine.
  */
  static SbMatrix     pushMatrix(SoState *state);
  /**
  *  This method is used by the TransformSeparator node.
  *  WARNING!  For proper caching behavior, the matrix returned by
  *  ::pushMatrix() must be used ONLY as a later argument to
  *  ::popMatrix(), and you must NOT modify the matrix between the
  *  push and the pop.  If you need the matrix for any other reason,
  *  you MUST use the ::get() routine.
  */
  static void         popMatrix(SoState *state, const SbMatrix &m);

  /**
  *  Sets the transformation that defines the volume that
  *  view-volume culling should be tested against.
  */
  static void         setCullMatrix(SoState *state, SoNode *node,
                                    const SbMatrix &matrix);

  /**
  *  This method gets the model*cullMatrix combined matrix (which is
  *  cached by this element).
  */
  static const SbMatrix &     getCombinedCullMatrix(SoState *state);

  /**
  *  Returns current model matrix from the state.
  */
  static const SbMatrix &     get(SoState *state);

  /**
  *  Returns current model matrix from the state, sets given flag to TRUE
  *  if matrix is known to be identity.
  */
  static const SbMatrix &     get(SoState *state, SbBool &isIdent);

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoModelMatrixElement class
  static void         initClass();
  static void         exitClass();
  SbMatrix            getModelMatrix() { return modelMatrix; }
  SbBool              isIdent() { return flags.isModelIdentity; }
  // Initializes element
  virtual void        init(SoState *state);

 protected:
  // Sets the matrix in an instance to identity
  virtual void        makeEltIdentity();

  // Sets the matrix in an instance to given matrix
  virtual void        setElt(const SbMatrix &matrix, SbBool sendToGL = TRUE);

  // Multiplies into the matrix in an instance
  virtual void        multElt(const SbMatrix &matrix);

  // Each of these performs the appropriate operation on the matrix
  // in an instance
  virtual void        translateEltBy(const SbVec3f &translation);
  virtual void        rotateEltBy(const SbRotation &translation);
  virtual void        scaleEltBy(const SbVec3f &scaleFactor);

  // virtual methods for push/pop so GL element can Do The Right Thing:
  virtual SbMatrix    pushMatrixElt();
  virtual void        popMatrixElt(const SbMatrix &m);

  // Update the shader state matrix
  virtual void updateShaderStateMatrix(SoState *state);

  virtual ~SoModelMatrixElement();

  // Copy method, copies flags
  virtual SoElement   *copyMatchInfo() const;

  SbMatrix            modelMatrix;
 private:
  SbMatrix            cullMatrix;
  SbMatrix            modelCullMatrix;
  struct Flags {
    unsigned int    isModelIdentity : 1;
    unsigned int    haveCullMatrix  : 1; // TRUE if cullMatrix set
    unsigned int    haveModelCull   : 1; // TRUE if model*cull computed
  };
  Flags flags;

  friend class SoLocalBBoxMatrixElement;
};

inline void
SoModelMatrixElement::updateShaderStateMatrix(SoState *)
{}

#endif /* _SO_MODEL_MATRIX_ELEMENT */

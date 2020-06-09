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


#ifndef  _SO_BBOX_MODEL_MATRIX_ELEMENT
#define  _SO_BBOX_MODEL_MATRIX_ELEMENT

#include <Inventor/SbBasic.h>
#include <Inventor/elements/SoModelMatrixElement.h>

/**
* Stores the current model matrix for use with the
*   SoGetBoundingBoxAction.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current model matrix for use with the
*   SoGetBoundingBoxAction. Overrides the virtual methods on
*   SoModelMatrixElement to also set the current
*   SoLocalBBoxMatrixElement.
* 
*   This class relies on SoModelMatrixElement to store the matrix in
*   the instance, and inherits most of its methods from it.
*   @SEE_ALSO
*   SoTransformSeparator, SoResetTransform
* 
*/

SoEXTENDER_Documented class INVENTOR_API SoBBoxModelMatrixElement : public SoModelMatrixElement {

  SO_ELEMENT_HEADER(SoBBoxModelMatrixElement);

 public:

  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
  virtual void        push(SoState *state);

  /**
  *  Allows the SoGetBoundingBoxAction to reset the current model
  *  matrix to identity and all currently-open local matrices to
  *  identity.
  */
  static void         reset(SoState *state, SoNode *node);

  /**
  *  Because two model matrices are kept track of during the
  *  getBoundingBoxAction (the local model matrix, used by
  *  separators to calculate their bbox caches, and the real model
  *  matrix), replacement routines for pushMatrix/popMatrix must be
  *  given; SoTransformSeparator::getBoundingBox uses these methods to
  *  correctly keep both matrices up-to-date.
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  static void         pushMatrix(SoState *state,
                                 SbMatrix &matrix,
                                 SbMatrix &localmatrix);
  /**
  * See description for pushMatrix().
  */
  static void         popMatrix(SoState *state,
                                const SbMatrix &matrix,
                                const SbMatrix &localmatrix);

 SoINTERNAL public:
  // Initializes the SoBBoxModelMatrixElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  // These all override the methods on SoModelMatrixElement to also
  // set the SoLocalBBoxMatrixElement
  virtual void        makeEltIdentity();
  virtual void        setElt(const SbMatrix &matrix);
  virtual void        setElt(const SbMatrix &matrix, SbBool sendToGL);
  virtual void        multElt(const SbMatrix &matrix);
  virtual void        translateEltBy(const SbVec3f &translation);
  virtual void        rotateEltBy(const SbRotation &translation);
  virtual void        scaleEltBy(const SbVec3f &scaleFactor);

  // These must never be called; they print debug errors if called:
  virtual SbMatrix    pushMatrixElt();
  virtual void        popMatrixElt(const SbMatrix &m);

  virtual ~SoBBoxModelMatrixElement();

 private:
  // Stores pointer to state so we can access the SoLocalBBoxMatrixElement
  SoState             *state;

  // This is used to make sure the pushMatrix/popMatrix methods are
  // called correctly.
  static SbBool      pushPopCallOK;
};

inline void
SoBBoxModelMatrixElement::setElt(const SbMatrix &matrix, SbBool )
{
  setElt(matrix);
}

#endif /* _SO_BBOX_MODEL_MATRIX_ELEMENT */

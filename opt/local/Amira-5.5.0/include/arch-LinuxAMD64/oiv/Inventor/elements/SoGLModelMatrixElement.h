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


#ifndef  _SO_GL_MODEL_MATRIX_ELEMENT
#define  _SO_GL_MODEL_MATRIX_ELEMENT

#include <Inventor/elements/SoModelMatrixElement.h>

/**
*   Stores the current model matrix in GL.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current model matrix in GL. Overrides the
*   virtual methods on SoModelMatrixElement to send the matrix to GL
*   when necessary.
*
*   Note that this class relies on SoModelMatrixElement to store the
*   matrix in the instance. This is less expensive in the long run
*   than asking GL for the matrix when it is needed.
*
*   Because GL stores the model and view matrices in one matrix, this
*   has to do a little extra work when setting the model matrix to
*   identity or another matrix. (It has to set the GL model-view
*   matrix correctly.)
*
*   @SEE_ALSO
*   SoModelMatrixElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLModelMatrixElement : public SoModelMatrixElement {

  SO_ELEMENT_HEADER(SoGLModelMatrixElement);

 public:
  /**
  *  Overrides push() method so side effects can occur in GL.
  */
  virtual void        push(SoState *state);
  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLModelMatrixElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  // Overrides SoModelMatrixElement::makeEltIdentity() to print an
  // error message
  virtual void        makeEltIdentity();

  // Sets the matrix in an instance to the given matrix. Assumes
  // that the passed matrix contains the correct combination of view
  // and model matrices.  This method will call glLoadMatrix with the
  // new matrix unless the 'sendToGL' parameter is explicitly FALSE.
  virtual void        setElt(const SbMatrix &matrix, SbBool sendToGL = TRUE);

  // Multiplies into the matrix in an instance
  virtual void        multElt(const SbMatrix &matrix);

  // Each of these performs the appropriate operation on the matrix
  // in an instance
  virtual void        translateEltBy(const SbVec3f &translation);
  virtual void        rotateEltBy(const SbRotation &translation);
  virtual void        scaleEltBy(const SbVec3f &scaleFactor);
  virtual SbMatrix    pushMatrixElt();
  virtual void        popMatrixElt(const SbMatrix &m);

  // Update the shader state matrix
  virtual void updateShaderStateMatrix(SoState *state) ;

  virtual ~SoGLModelMatrixElement();

 private:
  /** Update OivModelMatrix uniform */
  void setShaderModelMatrix(SoState *state);

  // We need to save the state to access the viewing matrix
  SoState             *m_state;

  // And we need to remember the nodeId of the viewing matrix
  // element to see if it changes between pushMatrixElt() and
  // popMatrixElt().
  uint64_t viewEltNodeId;
};

#endif /* _SO_GL_MODEL_MATRIX_ELEMENT */

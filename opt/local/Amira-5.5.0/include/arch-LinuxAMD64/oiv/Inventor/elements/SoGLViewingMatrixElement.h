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


#ifndef  _SO_GL_VIEWING_MATRIX_ELEMENT
#define  _SO_GL_VIEWING_MATRIX_ELEMENT

#include <Inventor/elements/SoViewingMatrixElement.h>

/**
*  Stores the current viewing matrix in GL.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current viewing matrix in GL. Overrides
*   the virtual methods on SoViewingMatrixElement to send the matrix
*   to GL when necessary.
*
*   Note that this class relies on SoViewingMatrixElement to store the
*   matrix in the instance.
*
*   @SEE_ALSO
*   SoViewingMatrixElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLViewingMatrixElement : public SoViewingMatrixElement {

  SO_ELEMENT_HEADER(SoGLViewingMatrixElement);

 public:
  /**
  *  Override push() to copy state pointer.
  */
  virtual void        push(SoState *state);

  /**
  *  Override pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLViewingMatrixElement class
  static void         initClass();
  static void         exitClass();

  // Override init() to copy state pointer
  virtual void        init(SoState *state);

  // Used by SoGLModelMatrixElement when it need to figure out if
  // this element has changed between a glPushMatrix() and a
  // glPopMatrix():
  static uint64_t     getNodeId(SoState *state);

 protected:
  // Sets the matrix in an instance. Has GL side effects.
  // This method will (indirectly) call glLoadMatrix with the
  // new matrix unless the 'sendToGL' parameter is explicitly FALSE.
  virtual void        setElt(const SbMatrix &matrix, SbBool sendToGL = TRUE);

  virtual ~SoGLViewingMatrixElement();

 private:
  /** Update OivViewMatrix and OivViewMatrixIT matrix*/
  void setShaderViewMatrix(SoState *state);

  // We need to store the state so we can get the model matrix element
  SoState             *state;

  // Sends matrix in element to GL
  void                send();
};

#endif /* _SO_GL_VIEWING_MATRIX_ELEMENT */

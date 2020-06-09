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


#ifndef  _SO_GL_PROJECTION_MATRIX_ELEMENT
#define  _SO_GL_PROJECTION_MATRIX_ELEMENT

#include <Inventor/elements/SoProjectionMatrixElement.h>

/**
*  Stores the current projection matrix in GL.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current projection matrix in GL. Overrides
*   the virtual methods on SoProjectionMatrixElement to send the matrix
*   to GL when necessary.
* 
*   Note that this class relies on SoProjectionMatrixElement to store the
*   matrix in the instance.
* 
*   @SEE_ALSO
*   SoProjectionMatrixElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLProjectionMatrixElement :
public SoProjectionMatrixElement {

  SO_ELEMENT_HEADER(SoGLProjectionMatrixElement);

 public:
  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLProjectionMatrixElement class
  static void         initClass();
  static void         exitClass();

 protected:
  // Sets the matrix in an instance. Has GL side effects.
  // This method will call glLoadMatrix with the new matrix unless the
  // 'sendToGL' parameter is explicitly FALSE.
  virtual void        setElt(const SbMatrix &matrix, SbBool sendToGL = TRUE);

  virtual ~SoGLProjectionMatrixElement();

 private:
  // Sends matrix in element to GL
  void                send();
};

#endif /* _SO_GL_PROJECTION_MATRIX_ELEMENT */

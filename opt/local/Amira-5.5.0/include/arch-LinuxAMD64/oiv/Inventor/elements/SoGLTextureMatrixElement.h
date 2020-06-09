/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_GL_TEXTURE_MATRIX_ELEMENT
#define  _SO_GL_TEXTURE_MATRIX_ELEMENT

#include <Inventor/elements/SoTextureMatrixElement.h>

/**
*  Stores the current texture matrix in GL.
* 
*  @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current texture matrix in GL. Overrides the
*   virtual methods on SoTextureMatrixElement to send the matrix to GL
*   when necessary.
* 
*   @SEE_ALSO
*   SoTextureMatrixElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTextureMatrixElement : public SoTextureMatrixElement {
  
  SO_ELEMENT_HEADER(SoGLTextureMatrixElement);
  
 public:
  /**
  *  Override pop() methods so side effects can occur in GL.
  */
  virtual void  pop(SoState *state, const SoElement *prevTopElement);
    
 SoINTERNAL public:
  // Initializes the SoGLTextureMatrixElement class
  static void initClass();
  static void exitClass();
  static void setEltIdentity();

 protected:
  // Sets the matrix to the identity matrix.
  virtual void  makeEltIdentity(int unit=0);
    
  // Multiplies into the matrix in an instance
  virtual void  multElt(const SbMatrix &matrix, int unit=0);
    
  // Each of these performs the appropriate operation on the matrix
  // in an instance
  virtual void  translateEltBy(const SbVec3f &translation, int unit=0);
  virtual void  rotateEltBy(const SbRotation &translation, int unit=0);
  virtual void  scaleEltBy(const SbVec3f &scaleFactor, int unit=0);
    
  virtual ~SoGLTextureMatrixElement();
};

#endif /* _SO_GL_TEXTURE_MATRIX_ELEMENT */

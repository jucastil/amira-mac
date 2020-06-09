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


#ifndef  _SO_TEXTURE_MATRIX_ELEMENT
#define  _SO_TEXTURE_MATRIX_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoAccumulatedElement.h>
#include <Inventor/STL/vector>

/**
*  Stores the current texture matrix.
* 
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current texture matrix - the cumulative
*   transformation applied to subsequent shapes. Because the matrix is
*   cumulative, this class is derived from SoAccumulatedElement. The
*   set() method replaces the current matrix, while all the others
*   (mult(), translateBy(), etc.) multiply into it. Node id's of the
*   nodes that affect the element are accumulated properly.
* 
*   @SEE_ALSO
*   SoTexture2Transform, SoTexture3Transform, SoTextureMatrix, SoVRMLTextureTransform
*/

SoEXTENDER_Documented class INVENTOR_API SoTextureMatrixElement : public SoAccumulatedElement {
  
  SO_ELEMENT_HEADER(SoTextureMatrixElement);
  
 public:
  /**
  *  Overrides push() method to copy values from next instance in the stack.
  */
 virtual void        push(SoState *state);
    
  /**
  *  Sets the texture matrix to the identity matrix.
  */
  static void         makeIdentity(SoState *state, SoNode *node);
    
  /**
  *  Multiplies the given matrix into the texture matrix.
  */
  static void         mult(SoState *state, SoNode *node,
                           const SbMatrix &matrix);
    
  /**
  *  Multiplies a matrix that performs the specified
  *  transformation into the texture matrix.
  */
  static void         translateBy(SoState *state, SoNode *node,
                                  const SbVec3f &translation);

  /**
  *  Multiplies a matrix that performs the specified
  *  transformation into the texture matrix.
  */
  static void         rotateBy(SoState *state, SoNode *node,
                               const SbRotation &rotation);

  /**
  *  Multiplies a matrix that performs the specified
  *  transformation into the texture matrix.
  */
  static void         scaleBy(SoState *state, SoNode *node,
                              const SbVec3f &scaleFactor);
    
  /**
  *  Returns current matrix from the state.
  */
  static const SbMatrix &     get(SoState *state, int unit=0);
    
  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;
    
 SoINTERNAL public:
  // Initializes the SoTextureMatrixElement class
  static void initClass();
  static void exitClass();
  static void emptyMatrix(SoState *state);

  // Initializes element
  virtual void        init(SoState *state);

  // Common Initialization. Directly called by the constructor.
  virtual void commonInit() ;
    
 protected:
  // Sets the matrix in an instance to identity
  virtual void        makeEltIdentity(int unit=0);
    
  // Multiplies into the matrix in an instance
  virtual void        multElt(const SbMatrix &matrix, int unit=0);
    
  // Each of these performs the appropriate operation on the matrix
  // in an instance
  virtual void        translateEltBy(const SbVec3f &translation, int unit=0);
  virtual void        rotateEltBy(const SbRotation &translation, int unit=0);
  virtual void        scaleEltBy(const SbVec3f &scaleFactor, int unit=0);
    
  // Gets the matrix from an instance
  virtual const SbMatrix &    getElt(int unit=0) const;
    
  virtual ~SoTextureMatrixElement();

  // return texture matrix for the given texture unit
  SbMatrix& getTexMatrix(const int unit) const;

private:
  // This stores the list of node id's as pointers associated to
  // each texture unit.
  typedef std::vector<SbMatrix> SbMatrixList;
  mutable SbMatrixList m_textureMatrixList;
};

#endif /* _SO_TEXTURE_MATRIX_ELEMENT */

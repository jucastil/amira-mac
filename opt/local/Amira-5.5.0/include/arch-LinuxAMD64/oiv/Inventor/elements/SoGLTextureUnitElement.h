/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Sep 2003)
**=======================================================================*/

#ifndef  _SO_GL_TEXTURE_UNIT_ELEMENT_
#define  _SO_GL_TEXTURE_UNIT_ELEMENT_

/* include files */
#include <Inventor/elements/SoTextureUnitElement.h>

/**
*  @VSGEXT Stores the current texture unit in GL.
* 
*  @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current texture unit in GL. 
* 
*   @SEE_ALSO
*   SoTextureUnitElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLTextureUnitElement : public SoTextureUnitElement {
  SO_ELEMENT_HEADER(SoGLTextureUnitElement) ;
  
 public:

  /**
  *  Pop method
  */
  virtual void pop(SoState *, const SoElement *prevTopElement) ;

 SoINTERNAL public:
  
  // Initializes the SoGLTextureUnitElement class
  static void initClass() ;
  static void exitClass() ;

  // Initializes element.
  virtual void init(SoState *state);
    
  
 protected:  
  virtual ~SoGLTextureUnitElement() ;

  // Sets the element
  virtual void setElt(SoState* state, SoNode *node, const int unit, MappingMethod mappingMethod) ;

  virtual void setUnit(SoState* state, const int unit) ;

} ;
/*----------------------------------------------------------------------------*/

#endif // _SO_GL_TEXTURE_UNIT_ELEMENT_

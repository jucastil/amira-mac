/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : P. ESTRADE (Nov 1999)
**=======================================================================*/

#ifndef  _SO_GL_PATTERN_ELEMENT_
#define  _SO_GL_PATTERN_ELEMENT_

#include <Inventor/sys/port.h>
#include <Inventor/elements/SoPatternElement.h>
/**
* @VSGEXT Stores the current pattern in GL.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element.stores the current pattern in GL.
*
*   @SEE_ALSO
*   SoPatternElement
*/
SoEXTENDER_Documented class INVENTOR_API SoGLPatternElement : public SoPatternElement {
  SO_ELEMENT_HEADER( SoGLPatternElement );

 public:
  /**
  *  Overrides push() method to remember previous element's state so
  *  we can sometimes generate more efficient GL calls.
  */
  virtual void push( SoState* state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState* state, const SoElement* prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLPatternElement class
  static void initClass() ;
  static void exitClass() ;

    // Initializes element
  virtual void init( SoState* state );

  //  typedef void (*GlPolygonOffsetPtr)(GLfloat factor, GLfloat units)

 protected:
  // Sets the pattern attributes in an instance. Has GL side effects.
  virtual void setElt( SbString category, SbString name, unsigned char* pattern );
  virtual ~SoGLPatternElement();

  // static GLPatternPtr m_glPatternPtr;

 private:
  // We save the state to figure out if the hints were
  // copied from a parent element; if they were, then caches will have
  // to depend on that element because if it changes we have to have
  // a chance to change our decision about what GL calls to make.
  // If this is NULL, then there are no cache dependencies.
  SoState *copiedFromParent ;

  // To know if stipple is activated.
  SbBool m_isStippleOn;
};
#endif // SO_GL_PATTERN_ELEMENT_

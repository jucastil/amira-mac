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


#ifndef _SO_GL_LINE_PATTERN_ELEMENT
#define _SO_GL_LINE_PATTERN_ELEMENT

#include <Inventor/elements/SoLinePatternElement.h>

/**
*  Stores the current line pattern in GL.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current line pattern in GL. Overrides the
*   virtual methods on SoLinePatternElement to send the line pattern
*   to GL when necessary.
* 
*   Note that this class relies on SoLinePatternElement to store the
*   pattern in the instance.
* 
*   @SEE_ALSO
*   SoLinePatternElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLLinePatternElement : public SoLinePatternElement {
  
  SO_ELEMENT_HEADER(SoGLLinePatternElement);
  
 public:
  /**
  *  Overrides push() so we can remember what line pattern the
  *  previous element set, and not send it again if it is the same.
  */
  virtual void push(SoState *state);
  
  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);
  
 SoINTERNAL public:
  // Initializes the SoGLLinePatternElement class
  static void initClass();
  static void exitClass();
 
  // Initializes element
  virtual void init(SoState *state);
  
 protected:
  // Sets the line pattern in an instance. Has GL side effects.
  virtual void setElt(u_short pattern, int factor);
  
  virtual ~SoGLLinePatternElement();
  
 private:
  // We save the state to figure out if the lastPattern variable was
  // copied from a parent element; if it was, then caches will have
  // to depend on that element because if it changes we have to have
  // a chance to change our decision about what GL calls to make.
  // If this is NULL, then there are no cache dependencies.
  SoState *copiedFromParent;
  
  // Sends line pattern in element to GL
  void send();
};

#endif /* _SO_GL_LINE_PATTERN_ELEMENT */

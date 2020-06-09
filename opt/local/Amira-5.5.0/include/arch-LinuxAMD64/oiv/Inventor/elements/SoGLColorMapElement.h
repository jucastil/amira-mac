/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_GL_COLOR_MAP_ELEMENT_
#define  _SO_GL_COLOR_MAP_ELEMENT_

#include <Inventor/elements/SoColorMapElement.h>

/**
* @VSGEXT Stores color map attributes.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores color map attributes.
*
*   @SEE_ALSO
*   SoColorMapElement
*/
SoEXTENDER_Documented class INVENTOR_API SoGLColorMapElement : public SoColorMapElement {

  SO_ELEMENT_HEADER(SoGLColorMapElement);
  
public:
  /**
  *  Overrides push() method so side effects can occur in GL.
  */
  virtual void push(SoState *state);
  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);
  
  SoINTERNAL public:
  // Initializes the classes.
  static void initClass();
  static void exitClass();

  // Initializes element.
  virtual void init(SoState *state);
   
  static SoGLColorMapElement * getCurrentElement(SoState *);

private:
  // Destructor
  virtual ~SoGLColorMapElement();
  
};
#endif /* _SO_GL_COLOR_MAP_ELEMENT_ */

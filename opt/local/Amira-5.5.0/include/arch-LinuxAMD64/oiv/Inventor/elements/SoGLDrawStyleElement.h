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


#ifndef  _SO_GL_DRAW_STYLE_ELEMENT
#define  _SO_GL_DRAW_STYLE_ELEMENT

#include <Inventor/elements/SoDrawStyleElement.h>

/**
*  Changes the current draw style in GL.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element changes the current draw style in GL. Overrides the
*   virtual methods on SoDrawStyleElement to send the draw style to GL
*   when necessary.
* 
*   Note that this class relies on SoDrawStyleElement to store the
*   style in the instance.
* 
*   Also note that this tells GL only how to draw polygons. Shapes
*   that contain lines still have to check for POINTS draw styles and
*   act accordingly.
* 
*   @SEE_ALSO
*   SoDrawStyleElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLDrawStyleElement : public SoDrawStyleElement {

  SO_ELEMENT_HEADER(SoGLDrawStyleElement);

 public:
  /**
  *  Overrides push() so we can remember the previous element's draw
  *  style, and perhaps avoid sending unnecessary GL calls if this
  *  element is the same.
  */
  virtual void        push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLDrawStyleElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  // Sets the draw style in an instance. Has GL side effects.
  virtual void        setElt(int32_t style);

  virtual ~SoGLDrawStyleElement();

 private:
  // We save the state to figure out if the lastPattern variable was
  // copied from a parent element; if it was, then caches will have
  // to depend on that element because if it changes we have to have
  // a chance to change our decision about what GL calls to make.
  // If this is NULL, then there are no cache dependencies.
  SoState *           copiedFromParent;

  // Sends draw style in element to GL
  void                send();
};

#endif /* _SO_GL_DRAW_STYLE_ELEMENT */

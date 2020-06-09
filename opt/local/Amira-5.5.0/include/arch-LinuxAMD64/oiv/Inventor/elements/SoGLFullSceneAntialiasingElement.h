/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (Nov 2003)
**=======================================================================*/

#ifndef  _SO_GL_FULL_SCENE_ANTIALIASING_ELEMENT_
#define  _SO_GL_FULL_SCENE_ANTIALIASING_ELEMENT_

#include <Inventor/sys/port.h>
#include <Inventor/elements/SoFullSceneAntialiasingElement.h>

/**
* @VSGEXT Stores full-scene antialiasing properties.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores full-scene antialiasing properties.
*   @SEE_ALSO
*   SoFullSceneAntialiasingElement
*/
SoEXTENDER_Documented class INVENTOR_API SoGLFullSceneAntialiasingElement : public SoFullSceneAntialiasingElement {
  SO_ELEMENT_HEADER(SoGLFullSceneAntialiasingElement);

 public:
  /**
  *  Overrides push() method to remember previous element's state so
  *  we can sometimes generate more efficient GL calls.
  */
  virtual void push(SoState *state);

  /**
  *  Overrides pop() method so side effects can occur in GL.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLFullSceneAntialiasingElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  // Sets the polygon offset attributes in an instance. Has GL side effects.
  virtual void setElt(SbBool on, SbBool currOn, int filter);

  virtual ~SoGLFullSceneAntialiasingElement();
  
 private:
  // We save the state to figure out if the hints were
  // copied from a parent element; if they were, then caches will have
  // to depend on that element because if it changes we have to have
  // a chance to change our decision about what GL calls to make.
  // If this is NULL, then there are no cache dependencies.
  SoState *copiedFromParent;

  // Send full scene antialiasing state to OpenGL
  void send(SoState *state);
};

#endif /* _SO_GL_FULL_SCENE_ANTIALIASING_ELEMENT_ */

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas Daguise (Dec 2003)
**=======================================================================*/

#ifndef  _SO_GL_TRANSPARENCY_TYPE_ELEMENT_
#define  _SO_GL_TRANSPARENCY_TYPE_ELEMENT_

#include <Inventor/elements/SoTransparencyTypeElement.h>

/**
 * @VSGEXT Stores the current transparency type in GL.
 *
 * @ingroup elements
 *
 * @DESCRIPTION
 * Stores the current transparency type in GL.
 *
 * @SEE_ALSO
 * SoTransparencyTypeElement
 *
 */

SoEXTENDER_Documented class INVENTOR_API SoGLTransparencyTypeElement : public SoTransparencyTypeElement {

  SO_ELEMENT_HEADER(SoGLTransparencyTypeElement);

 public:
  /**
   * Initializes element
   */
  virtual void init(SoState *state);

#ifdef OIV_NET_DOC
  /**
  * Override push() method to copy state reference and value of
  * previous element, to avoid sending GL commands if the elements
  * are the same.
  */

#else
  /**
  * Override push() method to copy state pointer and value of
  * previous element, to avoid sending GL commands if the elements
  * are the same.
  */

#endif //OIV_NET_DOC
  virtual void push(SoState *state);

  /**
   * Override pop() method so side effects can occur in GL
   */
  virtual void pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  /**
   * Initializes the SoGLTransparencyTypeElement class
   */
  static void initClass();
  static void exitClass();

 protected:
  /**
   * Sets the point size in an instance. Has GL side effects.
   */
  virtual void setElt(int type);

  virtual ~SoGLTransparencyTypeElement();

 private:
  /**
   * This variable is TRUE if the value in this element was copied
   * from our parent.  If set is called with the same value, no GL
   * commands have to be done-- it is as if this element doesn't
   * exist, and the parent's value is used.  Of course, a cache
   * dependency will have to be added in this case (if the parent
   * changes, the cache is not valid).  Set sets this flag to false.
   */
  SbBool copiedFromParent;

  // We need to store the state so we can get the viewport region element
  SoState *state;

  /**
   * Sends blend func in element to GL
   */
  void send(SoState* state);
};

#endif  // _SO_GL_TRANSPARENCY_TYPE_ELEMENT_

/**/

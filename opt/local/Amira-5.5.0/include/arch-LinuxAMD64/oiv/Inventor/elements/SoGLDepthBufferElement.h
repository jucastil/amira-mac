/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (Apr 2009)
**=======================================================================*/

#ifndef _SO_GL_DEPTH_BUFFER_ELEMENT_
#define _SO_GL_DEPTH_BUFFER_ELEMENT_

#include <Inventor/elements/SoDepthBufferElement.h>

/**
 * @VSGEXT Stores the current OpenGL depth buffer parameters.
 *
 * @ingroup elements
 *
 * @DESCRIPTION
 * This element stores the current depth buffer parameters used for rendering,
 * including:
 * - Depth buffer test enabled,
 * - Depth buffer writing enabled,
 * - Depth buffer range, and
 * - Depth comparison function.
 *
 * @SEE_ALSO
 *   SoDepthBufferElement
 */
SoEXTENDER_Documented class INVENTOR_API SoGLDepthBufferElement : public SoDepthBufferElement
{
  SO_ELEMENT_HEADER(SoGLDepthBufferElement);

public:
  /**
  *  Override push() method to keep GL up to date.
  */
  virtual void push(SoState *state);

  /**
  *  Override pop() method to keep GL up to date.
  */
  virtual void pop(SoState *state, const SoElement *prevTopElement);

SoINTERNAL public:

  /** register in database */
  static void initClass();

  /** unregister from database */
  static void exitClass();

  /** Initializes element */
  virtual void init(SoState *state);

protected:

  /** Destructor */
  virtual ~SoGLDepthBufferElement();

  /**
   * Sets the depth buffer parameter in an instance. Has GL side effects.
   * This method will enable or not GL_DEPTH_TEST mode and call glDepthRange/glDepthMask/glDepthFunc
   * with the new values.
   */
  virtual void setElt(SoDepthBuffer* depthBuffer, const SbBool enable, const SbBool write, const DepthWriteFunction function, const SbVec2f range);

private:
  /** send parameters to GL */
  void send() const;

};

#endif /* _SO_GL_DEPTH_BUFFER_ELEMENT_ */

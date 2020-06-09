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


#ifndef  _SO_GL_RENDER_PASS_ELEMENT
#define  _SO_GL_RENDER_PASS_ELEMENT

#include <Inventor/elements/SoSubElement.h>

/**
*  Stores the current rendering pass.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current rendering pass, a non-negative
*   integer that can be used during multi-pass rendering to implement
*   special effects such as motion blur or anti-aliasing.
* 
*   @SEE_ALSO
*   SoGLRenderAction
*/

SoEXTENDER_Documented class INVENTOR_API SoGLRenderPassElement : public SoElement {

  SO_ELEMENT_HEADER(SoGLRenderPassElement);

 public:
  /**
  *  Sets the current rendering pass in the state.
  */
  static void         set(SoState *state, int pass);

  /**
  *  Returns current rendering pass from the state.
  */
  static int          get(SoState *state);

  /**
  *  Returns TRUE if the passes match in both elements.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Creates and returns a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoGLRenderPassElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  int                 GLRenderPass;

  virtual ~SoGLRenderPassElement();
};

#endif /* _SO_GL_RENDER_PASS_ELEMENT */

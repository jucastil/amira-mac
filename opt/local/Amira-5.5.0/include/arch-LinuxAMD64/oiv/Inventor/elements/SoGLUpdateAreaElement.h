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


#ifndef  _SO_UPDATE_AREA_ELEMENT
#define  _SO_UPDATE_AREA_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoSubElement.h>

/**
* Stores the rectangular area within the current viewport region that 
* needs to be updated when rendering.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the rectangular area within the current
*   viewport region that needs to be updated when rendering. It can be
*   used for partial rendering updates when applications know that
*   only a portion of the objects need to be rerendered. Cameras can
*   use the info in this element to set up a view volume against which
*   culling can be performed. This element also sets up the GL scissor
*   box to limit drawing.
* 
*   The update area is specified in normalized viewport coordinates,
*   where (0,0) is the lower left corner of the viewport and (1,1) is
*   the upper right corner. The area is given as an origin and a size.
* 
*   @SEE_ALSO
*   PoBaseView, SoGLRenderAction
*/

SoEXTENDER_Documented class INVENTOR_API SoGLUpdateAreaElement : public SoElement {

  SO_ELEMENT_HEADER(SoGLUpdateAreaElement);

 public:
  /**
  *  Sets the current update area in the state. May have GL side effects.
  */
  static void         set(SoState *state,
                          const SbVec2f &origin, const SbVec2f &size);

  /**
  *  Returns current update area from the state. Returns TRUE if the
  *  update area is the default, namely, the entire viewport.
  */
  static SbBool       get(SoState *state, SbVec2f &origin, SbVec2f &size);

  /**
  *  Returns the default update area origin.
  */
  static SbVec2f      getDefaultOrigin()      { return SbVec2f(0.0, 0.0); }
  /**
  *  Returns the default update area size.
  */
  static SbVec2f      getDefaultSize()        { return SbVec2f(1.0, 1.0); }

  /**
  *  Override push() method to keep GL up to date.
  */
  virtual void        push(SoState *state);
  /**
  *  Override pop() method to keep GL up to date.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

  /**
  *  Returns TRUE if the update areas match in both elements.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoGLUpdateAreaElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbVec2f             origin, size;
  SbBool          m_sissor_enabled;

  virtual ~SoGLUpdateAreaElement();

 private:
  // This flag lets us know if the element is set to its initial
  // default value, which is not sent to GL. This is so we can tell
  // whether the GL value is up to date.
  SbBool              isDefault;

  // Sends region in element to GL
  void                send(SoState *state);
};

#endif /* _SO_UPDATE_AREA_ELEMENT */

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


#ifndef  _SO_GL_VIEWPORT_REGION_ELEMENT
#define  _SO_GL_VIEWPORT_REGION_ELEMENT

#include <Inventor/elements/SoViewportRegionElement.h>

/**
*  Stores the current viewport region in GL.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current viewport region in GL. Overrides
*   the virtual methods on SoViewportRegionElement to send the region
*   to GL when necessary.
* 
*   Note that this class relies on SoViewportRegionElement to store the
*   region in the instance.
* 
*   @SEE_ALSO
*   SoViewportRegionElement
*/

SoEXTENDER_Documented class INVENTOR_API SoGLViewportRegionElement : public SoViewportRegionElement {

  SO_ELEMENT_HEADER(SoGLViewportRegionElement);

 public:
  /**
  *  Override push() method to keep GL up to date.
  */
  virtual void        push(SoState *state);
  /**
  *  Override pop() method to keep GL up to date.
  */
  virtual void        pop(SoState *state, const SoElement *prevTopElement);

 SoINTERNAL public:
  // Initializes the SoGLViewportRegionElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  // Sets the region in an instance. Has GL side effects.
  // This method will call glViewport with the new values
  // unless the 'sendToGL' parameter is explicitly FALSE.
  virtual void        setElt(const SbViewportRegion &vpReg, SbBool sendToGL = TRUE);

  virtual ~SoGLViewportRegionElement();

 private:
  // This flag lets us know if the element is set to its initial
  // (usually bogus) value, which is not sent to GL. This is so we
  // can tell whether the GL value is up to date.
  SbBool              isDefault;

  // Sends region in element to GL
  void                send();
};

#endif /* _SO_GL_VIEWPORT_REGION_ELEMENT */

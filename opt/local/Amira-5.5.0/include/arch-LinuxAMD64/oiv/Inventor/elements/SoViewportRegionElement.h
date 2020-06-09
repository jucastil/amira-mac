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


#ifndef  _SO_VIEWPORT_REGION_ELEMENT
#define  _SO_VIEWPORT_REGION_ELEMENT

#include <Inventor/SbBasic.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/elements/SoSubElement.h>

/**
*   Stores the current viewport region.
* 
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current viewport region, which indicates
*   which part of the window is being rendered into. This information
*   is also needed during picking and bounding box computation to
*   determine sizes/locations of screen-space objects.
* 
*   @SEE_ALSO
*   PoBaseView, SoGetBoundingBoxAction, SoGetMatrixAction, SoGLRenderAction,
*   SoHandleEventAction, SoRayPickAction, SoCamera
*/

SoEXTENDER_Documented class INVENTOR_API SoViewportRegionElement : public SoElement {

  SO_ELEMENT_HEADER(SoViewportRegionElement);

 public:
  /**
  *  Sets the viewport region.
  *  This method will (indirectly) call glViewport with the new values
  *  unless the 'sendToGL' parameter is explicitly FALSE.
  */
  static void         set(SoState *state,
                          const SbViewportRegion &vpReg, SbBool sendToGL = TRUE);

  /**
  *  Returns current viewport region from the state.
  */
  static const SbViewportRegion & get(SoState *state);

  /**
  *  Returns TRUE if the viewports match.
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
  // Initializes the SoViewportRegionElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbViewportRegion    viewportRegion;

  // Sets the region in an instance
  virtual void        setElt(const SbViewportRegion &vpReg, SbBool sendToGL = TRUE);

  virtual ~SoViewportRegionElement();

 private:
  static SbViewportRegion *emptyViewportRegion;
};

#endif /* _SO_VIEWPORT_REGION_ELEMENT */

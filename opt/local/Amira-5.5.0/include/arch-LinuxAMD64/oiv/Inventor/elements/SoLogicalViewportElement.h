/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Pierre Stefani (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_LOGICAL_VIEW_PORT_ELEMENT
#define  _SO_LOGICAL_VIEW_PORT_ELEMENT

#include <Inventor/SbViewportRegion.h>
#include <Inventor/elements/SoSubElement.h>

/**
*   @VSGEXT Stores the logical viewport region.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the logical viewport region, which indicates
*   to the camera(s) the whole size of the window which is being rendered
*   into. This information is needed when the viewport region has been
*   split, so that the camera doesn't adjust its parameters on only
*   a part of the whole window.
* 
*   LogicalViewportElement is used for "tiled" rendering -- in this case
*   it contains the size (and aspect ratio) of the complete large image,
*   while ViewportRegionElement contains the size of the tile (subimage)
*   we are currently rendering. SoCamera::computeView uses the logical
*   viewport's aspect ratio for ADJUST_CAMERA mode, so we render all the
*   tiles with the same adjustment (but only if the LogicalViewportElement
*   was actually set during traversal -- see SoOffscreenRenderer).
* 
*   @SEE_ALSO
*   PoBaseView, SoOffscreenRenderer, SoGLRenderAction
*/

SoEXTENDER_Documented class INVENTOR_API SoLogicalViewportElement : public SoElement {
  
  SO_ELEMENT_HEADER(SoLogicalViewportElement);
  
 public:
  /**
  *  Sets the viewport region.
  */
  static void set(SoState *state, const SbViewportRegion &vp);
  
  /**
  *  Returns the current viewport region from the state.
  */
  static const SbViewportRegion &get(SoState *state);

  /**
  *  Returns the default viewport region.
  */
  static SbViewportRegion getDefaultViewport()
    { return SbViewportRegion(SbVec2s(100, 100)); }

  /**
  *  Return the top (current) instance of the element in the state.
  *  Note it does NOT cause cache dependency!
  *  It also casts away the const.
  */
  static SoLogicalViewportElement *getInstance(const SoState *state, 
                                               SbBool &elemIsSet);

  /**
  *  Returns TRUE if the passes match in both elements.
  */
  virtual SbBool matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement *copyMatchInfo() const;

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:
    // Initializes the SoLogicalViewportElement class
  static void initClass();
  static void exitClass();
  
  // Initializes element
  virtual void init(SoState *state);
  
 protected:
  SbViewportRegion viewport;
  SbBool isSet;

  virtual ~SoLogicalViewportElement();

private:
  uint64_t nodeId;
};
#endif /* _SO_LOGICAL_VIEW_PORT_ELEMENT */


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


#ifndef  _SO_PICK_RAY_ELEMENT
#define  _SO_PICK_RAY_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoSubElement.h>

/**
*   Stores the current ray to use for picking.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current ray to use for picking. It
*   contains the world space ray information in terms of an
*   SbViewVolume. The projection point and view direction of the
*   volume represent the ray itself. The width (which equals the
*   height) represents the diameter of the picking circle in the near
*   plane. The near and far planes represent the distances to the near
*   and far planes between which valid intersections must lie.
* 
*   @SEE_ALSO
*   SoRayPickAction
*/

SoEXTENDER_Documented class INVENTOR_API SoPickRayElement : public SoElement {

  SO_ELEMENT_HEADER(SoPickRayElement);

 public:
  /**
  *  Always returns FALSE, since this element should never be a
  *  criterion for cache invalidation.
  */
  virtual SbBool      matches(const SoElement *elt) const;

  /**
  *  Create and return a copy of this element.
  */
  virtual SoElement   *copyMatchInfo() const;

  /**
  *  Sets the picking ray.
  */
  static void         set(SoState *state, const SbViewVolume &volume);

  /**
  *  Returns the current picking ray view volume from the state.
  */
  static const SbViewVolume & get(SoState *state);

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoPickRayElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbViewVolume        volume;         // Ray as view volume

  virtual ~SoPickRayElement();
};

#endif /* _SO_PICK_RAY_ELEMENT */

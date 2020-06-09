/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Julien Chaplier (MMM yyyy)
** Modified by : Olivier Fedkiw (MMM yyyy)
**=======================================================================*/

#ifndef _SO_MODIFY_VIEW_VOLUME_ELEMENT
#define _SO_MODIFY_VIEW_VOLUME_ELEMENT

#include <Inventor/elements/SoSubElement.h>
#include <Inventor/SbBox.h>

/**
* @VSGEXT Stores a view volume subset.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores a view volume subset.
*   This element is used for "tiled" rendering, where we create a large
*   image by rendering one tile (subimage) at a time.  In this case we
*   must "narrow" the view volume for each tile, without modifying the
*   camera nodes in the scene graph. SoCamera::computeView uses this
*   element to modify the view volume after other adjustments have been
*   made. See also SoOffscreenRenderer.
*
*   @SEE_ALSO
*   PoBaseView, SoOffscreenRenderer
*/

SoEXTENDER_Documented class INVENTOR_API SoModifyViewVolumeElement : public SoElement {

  SO_ELEMENT_HEADER(SoModifyViewVolumeElement);

 public:
  /**
  *  Sets the current portion in the state to the given
  *  portion (left, bottom, right, top).
  */
  static void set(SoState *state, const SbVec4f &portion);
  /**
  *  Sets the current portion in the state to the given
  *  portion (left, bottom, right, top).
  */
  static void set(SoState *state, const SbBox3f &portion);

  /**
  *  Sets an integer info.
  */
  static void setInfo(SoState *state, int info);
  /**
  *  Gets an integer info.
  */
  static int getInfo(SoState *state);

  /**
  *  Returns the current portion of the view volume from the state.
  */
  static const SbVec4f &get(SoState *state);
  /**
  *  Returns the current portion of the view volume from the state.
  */
  static const SbBox3f &getBox(SoState *state);

  /**
  *  Returns the current coordinates of the virtual window in the real world.
  *  MP: coordinates of the projection wall/window in real world i.e., relative
  *  to the tracking system base or reference frame.
  */
  static void getWallCoordinates(SoState *state,
                                 SbVec3f &lowerLeft,
                                 SbVec3f &lowerRight,
                                 SbVec3f &upperLeft);
  /**
  *  Sets the current coordinates of the virtual window in the real world.
  *  MP: coordinates of the projection wall/window in real world i.e., relative
  *  to the tracking system base or reference frame.
  */
  static void setWallCoordinates(SoState *state,
                                 SbVec3f lowerLeft,
                                 SbVec3f lowerRight,
                                 SbVec3f upperLeft);

  /**
  *  Returns a boolean telling the Camera to compute
  *  a view volume using the wall coordinates.
  */
  static SbBool useWallCoordinates(SoState *state);

  /**
  *  Returns the default screen portion.
  */
  static SbVec4f getDefault()
    { return SbVec4f(0., 0., 1., 1.); }
  /**
  *  Returns the default screen portion.
  */
  static SbBox3f getDefaultBox()
    { return SbBox3f(0., 0., 0., 1., 1., 1.); }

  /**
  *  Return the top (current) instance of the element in the state
  *  Note it does NOT cause cache dependency!
  *  It also casts away the const.
  */
  static SoModifyViewVolumeElement *getInstance(const SoState *state,
                                                SbBool &elemIsSet);

  /**
  *  Push copies the values from the previous element.
  */
  virtual void  push(SoState *state);

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
  // Initializes the SubViewVolumeElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  virtual ~SoModifyViewVolumeElement();

  int info;
  SbBool isSet;
  SbBox3f screenPortionBox;
  SbVec4f screenPortion;
  SbVec3f _lowerLeft, _lowerRight, _upperLeft;
  SbBool _useWall;

private:
  uint64_t nodeId;
};
#endif /* _SO_MODIFY_VIEW_VOLUME_ELEMENT */

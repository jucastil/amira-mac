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


#ifndef  _SO_VIEW_VOLUME_ELEMENT
#define  _SO_VIEW_VOLUME_ELEMENT

#include <Inventor/SbLinear.h>
#include <Inventor/elements/SoReplacedElement.h>

/**
*   Stores the current viewing volume.
*
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current viewing volume.
*
*   @SEE_ALSO
*   SoCamera, SoOrthographicCamera, SoPerspectiveCamera
*/

SoEXTENDER_Documented class INVENTOR_API SoViewVolumeElement : public SoReplacedElement {

  SO_ELEMENT_HEADER(SoViewVolumeElement);

 public:
  /**
  *  Sets the view volume in the state.
  */
  static void set(SoState *state, SoNode *node, const SbViewVolume &viewVolume);

  /**
  *  Returns the current view volume from the state.
  */
  static const SbViewVolume & get(SoState *state);

  /**
  *  Returns TRUE if the view volume has been set in the state.
  */
  static SbBool isSet(SoState *state);

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:
  /** Return the eye position in object space */
  static SbVec3f getEyePosObjectSpace(SoState* state);

  // Initializes the SoViewVolumeElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  SbBool              volumeWasSet;
  SbViewVolume        viewVolume;

  virtual ~SoViewVolumeElement();
};

#endif /* _SO_VIEW_VOLUME_ELEMENT */

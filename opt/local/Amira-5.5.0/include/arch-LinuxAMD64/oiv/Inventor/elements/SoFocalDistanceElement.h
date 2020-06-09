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


#ifndef  _SO_FOCAL_DISTANCE_ELEMENT
#define  _SO_FOCAL_DISTANCE_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

/**
*   Stores the current focal distance of the camera.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current focal distance of the camera. This
*   can be used to determine the center of attention of the camera.
*
*   @SEE_ALSO
*   SoCamera, SoOrthographicCamera, SoPerspectiveCamera
*/

SoEXTENDER_Documented class INVENTOR_API SoFocalDistanceElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoFocalDistanceElement);

 public:

  /**
  *  Sets the current focal distance in the state.
  */
  static void         set(SoState *state, float distance)
    { SoFloatElement::set(getClassTypeId(), getClassStackIndex(), state, distance); }

#ifndef IV_STRICT
  /**
  *  Sets the current focal distance in the state.
  */
  static void         set(SoState *state, SoNode *, float distance)
    { set(state, distance); }
#endif

  /**
  *  Returns current focal distance from the state.
  */
  static float        get(SoState *state)
    { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default focal distance.
  */
  static float        getDefault()                    { return 5.0; }

 SoINTERNAL public:
  // Initializes the SoFocalDistanceElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoFocalDistanceElement();
};

#endif /* _SO_FOCAL_DISTANCE_ELEMENT */

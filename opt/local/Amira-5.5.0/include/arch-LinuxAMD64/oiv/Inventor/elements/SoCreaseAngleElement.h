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


#ifndef  _SO_CREASE_ANGLE_ELEMENT
#define  _SO_CREASE_ANGLE_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

/**
*  Stores the current crease angle
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current crease angle that is used to
*   determine whether default normals should be computed to create a
*   sharp edge or a smooth surface.
*   @SEE_ALSO
*   SoShapeHints
*/

SoEXTENDER_Documented class INVENTOR_API SoCreaseAngleElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoCreaseAngleElement);

 public:
   /**
   *  Sets the current crease angle in the state.
   */
    static void         set(SoState *state, float angle);
#ifndef IV_STRICT
   /**
   *  Sets the current crease angle in the state.
   */
    static void         set(SoState *state, SoNode *, float angle)
    { set(state, angle); }
#endif

  /**
  *  Returns current crease angle from the state.
  */
  static float        get(SoState *state)
    { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default crease angle.
  */
  static float        getDefault()                    { return 0.0; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoCreaseAngleElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoCreaseAngleElement();
};

#endif /* _SO_CREASE_ANGLE_ELEMENT */

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Nov 2004)
**=======================================================================*/

#ifndef  _SO_TEXT_ORIENTATION_ELEMENT_
#define  _SO_TEXT_ORIENTATION_ELEMENT_

#include <Inventor/elements/SoInt32Element.h>

/**
*  @VSGEXT Stores the current text orientation attributes.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current text orientation attributes.
*
*   @SEE_ALSO
*   SoTextProperty
*/
SoEXTENDER_Documented class INVENTOR_API SoTextOrientationElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoTextOrientationElement);

 public:

    /** Orientation */
   enum Orientation {
    /** LEFT_TO_RIGHT */
    LEFT_TO_RIGHT = 0x01,
    /** RIGHT_TO_LEFT */
    RIGHT_TO_LEFT = 0x02,
    /** TOP_TO_BOTTOM */
    TOP_TO_BOTTOM = 0x03,
    /** BOTTOM_TO_TOP */
    BOTTOM_TO_TOP = 0x04
  };

  /**
  *  Sets the current font orientation in the state.
  */
  static void set(SoState *state, Orientation style);

#ifndef IV_STRICT
  /**
  *  Sets the current font orientation in the state.
  */
  static void set(SoState *state, SoNode *, Orientation style) { set(state, style); }
#endif

  /**
  *  Returns current draw style from the state.
  */
  static Orientation get(SoState *state) { return (Orientation)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default draw style.
  */
  static Orientation getDefault();

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoTextOrientationElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  virtual ~SoTextOrientationElement();
};

#endif // _SO_TEXT_ORIENTATION_ELEMENT_

/**/

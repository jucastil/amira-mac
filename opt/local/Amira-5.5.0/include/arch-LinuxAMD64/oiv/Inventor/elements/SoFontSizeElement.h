/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Thad Beier (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FONT_SIZE_ELEMENT
#define  _SO_FONT_SIZE_ELEMENT

#include <Inventor/SbString.h>
#include <Inventor/elements/SoFloatElement.h>

/**
*   Stores the current font size.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current font size.
*
*   @SEE_ALSO
*   SoFont, SoFontStyle, SoVRMLFontStyle
*/

SoEXTENDER_Documented class INVENTOR_API SoFontSizeElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoFontSizeElement);

 public:
  /**
  *  Sets the current font size.
  */
  static void         set(SoState *state, float size)
    { SoFloatElement::set(getClassTypeId(), getClassStackIndex(), state, size); }

#ifndef IV_STRICT
  /**
  *  Sets the current font size.
  */
  static void         set(SoState *state, SoNode *, float size)
    { set(state, size); }
#endif

  /**
  *  Returns the current font size from the state.
  */
  static float        get(SoState *state)
    { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default font size.
  */
  static float  getDefault();

 SoINTERNAL public:
  // Initializes class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoFontSizeElement();

 private:
  static float s_defaultFontSize;
  static bool s_isSet;
};

#endif /* _SO_FONT_SIZE_ELEMENT */

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Aug 2009)
**=======================================================================*/

#ifndef  SO_TEXT_EFFECTS_ELEMENT
#define  SO_TEXT_EFFECTS_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
* @VSGEXT Stores the current text effect settings.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current text effects settings.
*
*   @SEE_ALSO
*   SoTextProperty
*/

SoEXTENDER_Documented class INVENTOR_API SoTextStyleElement : public SoInt32Element
{

  SO_ELEMENT_HEADER(SoTextStyleElement);

 public:
    /**
    *  Available styles (may be combined):
    */
    enum Style
    {
      /** No effects. */
      NONE                  = 1 << 0,
      /** UNDERLINE */
      UNDERLINE             = 1 << 1,
      /** STRIKETHROUGH */
      STRIKETHROUGH         = 1 << 2,
      /** DOUBLE_STRIKETHROUGH */
      DOUBLE_STRIKETHROUGH  = 1 << 3,
      /** BACK_FRAME */
      BACK_FRAME            = 1 << 4,
      /** BACK_FRAME_LINE */
      BACK_FRAME_LINE       = 1 << 5
    };

    /**
     *  Sets the current style type in the state.
     */
     static void set(SoState *state, Style style);

#ifndef IV_STRICT
    /**
     *  Sets the current style type in the state.
     */
  static void set(SoState *state, SoNode *, Style style)
    { set(state, style); }
#endif

  /**
  *  Returns current style from the state.
  */
  static Style get(SoState *state)
    { return (Style)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default style.
  */
  static Style getDefault();

 SoINTERNAL public:
  // Initializes the SoComplexityTypeElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  virtual ~SoTextStyleElement();
};

#endif // SO_TEXT_EFFECTS_ELEMENT

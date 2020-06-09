/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Feb 2010)
**=======================================================================*/

#ifndef  _SO_TEXT_MARGIN_ELEMENT_
#define  _SO_TEXT_MARGIN_ELEMENT_

#include <Inventor/elements/SoFloatElement.h>

/**
*  @VSGEXT Stores the current textured text anti-aliasing factor.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current textured text anti-aliasing factor.
*
*   @SEE_ALSO
*   SoTextProperty
*/
SoEXTENDER_Documented class INVENTOR_API SoTextMarginElement : public SoFloatElement
{

  SO_ELEMENT_HEADER(SoTextMarginElement);

 public:

   /**
   *  Sets the current horizontal text alignment in the state.
   */
   static void set(SoState *state, float factor);

#ifndef IV_STRICT
   /**
   *  Sets the current horizontal text alignment in the state.
   */
  static void set(SoState* state, SoNode*, float style) { set(state, style); }
#endif

  /**
  *  Returns current draw style from the state.
  */
  static float get(SoState* state) { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default draw style.
  */
  static float getDefault();

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:

  // Initializes the SoTextMarginElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  virtual ~SoTextMarginElement();

 private:
  static float s_defaultMarginFactor;
  static bool s_isSet;
};

#endif // _SO_TEXT_MARGIN_ELEMENT_

/**/

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Aug 2009)
**=======================================================================*/

#ifndef  _SO_TEXT_ALIASING_FACTOR_ELEMENT_
#define  _SO_TEXT_ALIASING_FACTOR_ELEMENT_

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
SoEXTENDER_Documented class INVENTOR_API SoTextAliasingFactorElement : public SoFloatElement
{

  SO_ELEMENT_HEADER(SoTextAliasingFactorElement);

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

  // Initializes the SoTextAliasingFactorElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  virtual ~SoTextAliasingFactorElement();

 private:
  static float s_defaultAliasingFactor;
  static bool s_isSet;
};

#endif // _SO_TEXT_ALIASING_FACTOR_ELEMENT_

/**/

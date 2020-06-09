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

#ifdef  IV_STRICT
#error SoEmissiveColorElement is obsolete.  See SoLazyElement instead.
#endif /*IV_STRICT*/
#ifndef  _SO_EMISSIVE_COLOR_ELEMENT
#define  _SO_EMISSIVE_COLOR_ELEMENT


#include <Inventor/SbColor.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/errors/SoDebugError.h>

/**
*   Stores emissive color of current material (superseded by SoLazyElement).
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This class is superseded by the SoLazyElement class.
*   All methods are converted inline to SoLazyElement methods for
*   compatibility.  This only uses the first emissive color, not an
*   array of them.
* 
*   @SEE_ALSO
*
* [OIV-WRAPPER-NO-WRAP]
*/

SoEXTENDER_Documented class SoEmissiveColorElement {


 public:

  /**
   * Sets the current emissive color(s).
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(colors != NULL? colors->Length: 0)},ARRAY]
   */
  static void set(SoState *state, SoNode *,
                          int32_t numColors, const SbColor *colors);

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoEmissiveColorElement * getInstance(SoState *state);

  /**
  *  Returns the number of emissive colors in any instance.
  */
  int32_t getNum() const
  { return 1; }

  /**
  *  Returns the current emissive color.
  */
  const SbColor& get(int index) const;

  /**
  *  Returns the default emissive color.
  */
  static SbColor getDefault()         
  { return SoLazyElement::getDefaultEmissive(); }
    
 private:
  SoState* saveState;
};



inline void
#if defined(_DEBUG)
SoEmissiveColorElement::set(SoState *state, SoNode *,int32_t numColors, const SbColor *colors)
#else
SoEmissiveColorElement::set(SoState *state, SoNode *,int32_t , const SbColor *colors)
#endif
{
  SoLazyElement::setEmissive(state,*colors);
#if defined(_DEBUG)
  if(numColors>1){
    SoDebugError::post("SoEmissiveColorElement::set",
                       "multiple emissive colors not supported");
  }
#endif
}


inline const SoEmissiveColorElement * 
SoEmissiveColorElement::getInstance(SoState *state)
{
  SoEmissiveColorElement* ece = new SoEmissiveColorElement;
  ece->saveState = state;
  return(ece);
}


inline const SbColor&
#if defined(_DEBUG)
SoEmissiveColorElement::get(int index) const
#else
SoEmissiveColorElement::get(int) const
#endif
{
#if defined(_DEBUG)
  if(index >1)
    SoDebugError::post("SoEmissiveColorElement::get",
                       "multiple emissive colors not supported");
#endif
  return(SoLazyElement::getEmissive(saveState));
}


#endif /* _SO_EMISSIVE_COLOR_ELEMENT */

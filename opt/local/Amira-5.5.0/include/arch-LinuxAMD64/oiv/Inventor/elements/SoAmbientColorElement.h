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

#ifdef IV_STRICT
#error SoAmbientColorElement is obsolete.  See SoLazyElement.h instead.
#endif /*IV_STRICT*/
#ifndef  _SO_AMBIENT_COLOR_ELEMENT
#define  _SO_AMBIENT_COLOR_ELEMENT


#include <Inventor/SbColor.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/errors/SoDebugError.h>
/**
*   Stores ambient color of current material (superseded by SoLazyElement).
* 
* @ingroup elements
*
*   @DESCRIPTION
*   This class is superseded by the SoLazyElement class.
*   All methods are converted inline to SoLazyElement methods for
*   compatibility. This only uses the first ambient color, not an
*   array of them.
*   @SEE_ALSO
* 
* [OIV-WRAPPER-NO-WRAP]
*/

SoEXTENDER_Documented class SoAmbientColorElement {

 public:

  /**
   * Sets the current ambient color(s).
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(colors != NULL? colors->Length: 0)},ARRAY]
   */
  static void set(SoState *state, SoNode *, int32_t numColors, const SbColor *colors);

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoAmbientColorElement * getInstance(SoState *state);

  /**
  *  Returns the number of ambient colors in any instance.
  */
  int32_t getNum() const
  { return 1; }

  /**
  *  Returns the current ambient color.
  */
  const SbColor& get(int index) const;

  /**
  *  Returns the default ambient color.
  */
  static SbColor getDefault()         
  { return SoLazyElement::getDefaultAmbient(); }
    
 private:
  SoState* saveState;
};


inline void
#if defined(_DEBUG)
SoAmbientColorElement::set(SoState *state, SoNode *, int32_t numColors, const SbColor *colors)
#else
SoAmbientColorElement::set(SoState *state, SoNode *, int32_t, const SbColor *colors)
#endif
{
  SoLazyElement::setAmbient(state,*colors);
#if defined(_DEBUG)
  if(numColors>1){
    SoDebugError::post("SoAmbientColorElement::set",
                       "multiple ambient colors not supported");
  }
#endif
}


inline const SoAmbientColorElement * 
SoAmbientColorElement::getInstance(SoState *state)
{
  SoAmbientColorElement* ace = new SoAmbientColorElement;
  ace->saveState = state;
  return(ace);
}

inline const SbColor &
#if defined(_DEBUG)
SoAmbientColorElement::get(int index) const
#else
SoAmbientColorElement::get(int) const
#endif
{
#if defined(_DEBUG)
  if(index >1)
    SoDebugError::post("SoAmbientColorElement::get",
                       "multiple ambient colors not supported");
#endif
  return(SoLazyElement::getAmbient(saveState));
}

#endif /* _SO_AMBIENT_COLOR_ELEMENT */


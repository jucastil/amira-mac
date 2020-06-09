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
#error SoSpecularColorElement is obsolete. See SoLazyElement.h instead.
#endif /*IV_STRICT*/
#ifndef  _SO_SPECULAR_COLOR_ELEMENT
#define  _SO_SPECULAR_COLOR_ELEMENT


#include <Inventor/SbColor.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/errors/SoDebugError.h>

/**
*   Stores specular color of current material (superseded by SoLazyElement).
* 
*   @ingroup elements
*
*   @DESCRIPTION
*   This class is superseded by the SoLazyElement class.
*   All methods are converted inline to SoLazyElement methods for
*   compatibility. This only uses the first specular color, not an
*   array of them.
* 
*   @SEE_ALSO
*
* [OIV-WRAPPER-NO-WRAP]
*/

SoEXTENDER_Documented class SoSpecularColorElement {


 public:

  /**
   * Sets the current specular color(s).
   * [OIV-WRAPPER-ARG IN,IN,NO_WRAP{(colors != NULL? colors->Length: 0)},ARRAY]
   */
  static void         set(SoState *state, SoNode *,
                          int32_t numColors, const SbColor *colors);

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoSpecularColorElement * getInstance(SoState *state);

  /**
  *  Returns the number of specular colors in any instance.
  */
  int32_t getNum() const
  { return 1; }

  /**
  *  Returns the current specular color.
  */
  const SbColor &  get(int index) const;

  /**
  *  Returns the default specular color.
  */
  static SbColor getDefault()         
  { return SoLazyElement::getDefaultSpecular(); }
    
 private:
  SoState* saveState;
};

inline void
#if defined(_DEBUG)
SoSpecularColorElement::set(SoState *state, SoNode *, int32_t numColors, const SbColor *colors)
#else
SoSpecularColorElement::set(SoState *state, SoNode *, int32_t, const SbColor *colors)
#endif
{
  SoLazyElement::setSpecular(state,*colors);
#if defined(_DEBUG)
  if(numColors>1){
    SoDebugError::post("SoSpecularColorElement::set",
                       "multiple specular colors not supported");
  }
#endif
}


inline const SoSpecularColorElement * 
SoSpecularColorElement::getInstance(SoState *state)
{
  SoSpecularColorElement* sce = new SoSpecularColorElement;
  sce->saveState = state;
  return(sce);
}

inline const SbColor &
#if defined(_DEBUG)
SoSpecularColorElement::get(int index) const
#else
SoSpecularColorElement::get(int ) const
#endif
{
#if defined(_DEBUG)
  if(index >1)
    SoDebugError::post("SoSpecularColorElement::get",
                       "multiple specular colors not supported");
#endif
  return(SoLazyElement::getSpecular(saveState));
}

#endif /* _SO_SPECULAR_COLOR_ELEMENT */


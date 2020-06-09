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
#error SoShininessElement is obsolete. See SoLazyElement.h instead.
#endif /*IV_STRICT*/
#ifndef  _SO_SHININESS_ELEMENT
#define  _SO_SHININESS_ELEMENT


#include <Inventor/elements/SoLazyElement.h>
#include <Inventor/misc/SoState.h>
#include <Inventor/errors/SoDebugError.h>

/**
*   Stores shininess of current material (mostly superseded by SoLazyElement).
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   Mostly superseded by SoLazyElement.
*   get() and set() methods retained for compatibility
* 
*   @SEE_ALSO
*
* [OIV-WRAPPER-NO-WRAP]
*/

SoEXTENDER_Documented class SoShininessElement {


 public:

  /**
  *  Sets the current shininess(es).
  */
  static void set(SoState *state, SoNode *,
                          int32_t numShininesses, const float *shininesses);

  /**
  *  Returns the top (current) instance of the element in the state.
  */
  static const SoShininessElement * getInstance(SoState *state);

  /**
  *  Returns the number of shininess values in an instance.
  */
  int32_t getNum() const
  { return 1; }

  /**
  *  Returns the indexed shininess from an element.
  */
  float get(int index) const;

  /**
  *  Returns the default shininess.
  */
  static float        getDefault()            
    { return SoLazyElement::getDefaultShininess(); }


 private:
  SoState * saveState;
};


inline void 
#if defined(_DEBUG)
SoShininessElement::set(SoState *state, SoNode *, int32_t numShininesses, const float *shininesses)
#else
SoShininessElement::set(SoState *state, SoNode *, int32_t, const float *shininesses)
#endif
{
  SoLazyElement::setShininess(state, *shininesses);
#if defined(_DEBUG)
  if(numShininesses>1){
    SoDebugError::post("SoShininessElement::set",
                       "multiple shininess not supported");
  }
#endif
}


inline const SoShininessElement *
SoShininessElement::getInstance(SoState *state)
{
  SoShininessElement* se = new SoShininessElement;
  se->saveState = state;
  return(se);
}

inline float
#if defined(_DEBUG)
SoShininessElement::get(int index) const
#else
SoShininessElement::get(int) const
#endif
{
#if defined(_DEBUG)
  if(index >1)
    SoDebugError::post("SoShininessElement::get",
                       "multiple shininess values not supported");
#endif
  return(SoLazyElement::getShininess(saveState));
}


#endif /* _SO_SHININESS_ELEMENT */


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


#ifndef  _SO_COMPLEXITY_ELEMENT
#define  _SO_COMPLEXITY_ELEMENT

#include <Inventor/elements/SoFloatElement.h>
#include <Inventor/SoPreferences.h>

/**
*   Stores the current shape complexity.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current shape complexity.
*   @SEE_ALSO
*   SoComplexity
*/

SoEXTENDER_Documented class INVENTOR_API SoComplexityElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoComplexityElement);

 public:
    /**
    *  Sets the current complexity in the state.
    */
    static void         set(SoState *state, float comp)
    { SoFloatElement::set(getClassTypeId(), getClassStackIndex(), state, comp); }

#ifndef IV_STRICT
    /**
    *  Sets the current complexity in the state.
    */
  static void         set(SoState *state, SoNode *, float comp)
    { set(state, comp); }
#endif

  /**
  *  Returns current complexity from the state.
  */
  static float        get(SoState *state)
  { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default complexity.
  */
  static float        getDefault()                    { return SoPreferences::getFloat ("OIV_COMPLEXITY", 0.5); }

 SoINTERNAL public:
  // Initializes the SoComplexityElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoComplexityElement();
};

#endif /* _SO_COMPLEXITY_ELEMENT */

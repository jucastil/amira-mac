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


#ifndef  _SO_POINT_SIZE_ELEMENT
#define  _SO_POINT_SIZE_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

/**
*   Stores the current point size.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current point size.
*
*   @SEE_ALSO
*   SoDrawStyle
*/

SoEXTENDER_Documented class INVENTOR_API SoPointSizeElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoPointSizeElement);

 public:
  /**
  *  Sets the current point size in the state.
  */
  static void         set(SoState *state, float size)
    { SoFloatElement::set(getClassTypeId(), getClassStackIndex(), state, size); }

#ifndef IV_STRICT
  /**
  *  Sets the current point size in the state.
  */
  static void         set(SoState *state, SoNode *, float size)
    { set(state, size); }
#endif

  /**
  *  Returns current point size from the state.
  */
  static float        get(SoState *state)
    { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default point size.
  */
  static float        getDefault()                    { return 0; }

 SoINTERNAL public:
  // Initializes the SoPointSizeElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoPointSizeElement();
};

#endif /* _SO_POINT_SIZE_ELEMENT */

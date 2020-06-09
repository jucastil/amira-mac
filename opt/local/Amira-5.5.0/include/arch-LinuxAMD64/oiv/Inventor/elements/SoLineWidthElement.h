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


#ifndef  _SO_LINE_WIDTH_ELEMENT
#define  _SO_LINE_WIDTH_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

/**
*   Stores the current line width.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current line width.
*
*   @SEE_ALSO
*   SoDrawStyle,
*   SoVRMLLineProperties
*/

SoEXTENDER_Documented class INVENTOR_API SoLineWidthElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoLineWidthElement);

 public:
  /**
  *  Sets the current line width in the state.
  */
  static void         set(SoState *state, float width)
    { SoFloatElement::set(getClassTypeId(), getClassStackIndex(), state, width); }

#ifndef IV_STRICT
  /**
  *  Sets the current line width in the state.
  */
  static void         set(SoState *state, SoNode *, float width)
    { set(state, width); }
#endif

  /**
  *  Returns current line width from the state.
  */
  static float        get(SoState *state)
    { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default line width.
  */
  static float        getDefault()                    { return 0; }

 SoINTERNAL public:
  // Initializes the SoLineWidthElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoLineWidthElement();
};

#endif /* _SO_LINE_WIDTH_ELEMENT */

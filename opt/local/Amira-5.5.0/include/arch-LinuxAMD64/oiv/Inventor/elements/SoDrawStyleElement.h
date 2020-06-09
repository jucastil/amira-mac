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


#ifndef  _SO_DRAW_STYLE_ELEMENT
#define  _SO_DRAW_STYLE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
*   Stores the current draw style.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current draw style.
*   @SEE_ALSO
*   SoDrawStyle
*/

SoEXTENDER_Documented class INVENTOR_API SoDrawStyleElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoDrawStyleElement);

 public:
/**
*  These are the available draw styles.
*/
  enum Style {
                            /** Filled regions */
    FILLED,                 /** Outlined regions */
    LINES,                  /** Points */
    POINTS,                 /** Nothing */
    INVISIBLE,              /** Markers */
    MARKERS
  };

  /**
  *  Sets the current draw style in the state.
  */
  static void         set(SoState *state, Style style);

#ifndef IV_STRICT
  /**
  *  Sets the current draw style in the state.
  */
  static void         set(SoState *state, SoNode *, Style style)
    { set(state, style); }
#endif

  /**
  *  Returns current draw style from the state.
  */
  static Style        get(SoState *state)
    { return (Style)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default draw style.
  */
  static Style        getDefault()            { return FILLED; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoDrawStyleElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

protected:
  virtual ~SoDrawStyleElement();
};

#endif /* _SO_DRAW_STYLE_ELEMENT */

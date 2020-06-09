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


#ifndef  _SO_PICK_STYLE_ELEMENT
#define  _SO_PICK_STYLE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
*   Stores the current pick style.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current pick style.
*
*   @SEE_ALSO
*   SoPickStyle
*/

SoEXTENDER_Documented class INVENTOR_API SoPickStyleElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoPickStyleElement);

 public:
 /**
 *  These are the available pick styles.
 */
 enum Style {
 /**
 *  Points on surface of shape may be picked.
 */
 SHAPE,
 /**
 *  Points on bounding boxes may be picked.
 */
 BOUNDING_BOX,
 /**
 *  Picks go through objects.
 */
 UNPICKABLE
  };

  /**
  *  Sets the current pick style in the state.
  */
  static void         set(SoState *state, Style style)
    { SoInt32Element::set(getClassTypeId(), getClassStackIndex(), state, (int32_t)style); }

#ifndef IV_STRICT
  /**
  *  Sets the current pick style in the state.
  */
  static void         set(SoState *state, SoNode *, Style style)
    { set(state, style); }
#endif

  /**
  *  Returns current pick style from the state.
  */
  static Style        get(SoState *state)
  { return (Style)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default pick style.
  */
  static Style        getDefault()            { return SHAPE; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoPickStyleElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);
 protected:
  virtual ~SoPickStyleElement();
};

#endif /* _SO_PICK_STYLE_ELEMENT */

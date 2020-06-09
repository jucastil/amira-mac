/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Nov 2004)
**=======================================================================*/

#ifndef  _SO_TEXT_ALIGNMENTV_ELEMENT_
#define  _SO_TEXT_ALIGNMENTV_ELEMENT_

#include <Inventor/elements/SoInt32Element.h>

/**
*  @VSGEXT  Stores the current vertical text alignment.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current vertical text alignment.
*
*   @SEE_ALSO
*   SoTextProperty
*/
SoEXTENDER_Documented class INVENTOR_API SoTextAlignmentVElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoTextAlignmentVElement);

 public:

    /** AlignmentV */
   enum AlignmentV {
    /** TOP */
    TOP    = 0x01,
    /** HALF */
    HALF   = 0x03,
    /** BASE */
    BASE   = 0x04,
    /** BOTTOM */
    BOTTOM = 0x05
  };

  /**
  *  Sets the current vertical text alignment in the state.
  */
  static void set(SoState *state, AlignmentV style);

#ifndef IV_STRICT
  /**
  *  Sets the current vertical text alignment in the state.
  */
  static void set(SoState *state, SoNode *, AlignmentV style) { set(state, style); }
#endif

  /**
  *  Returns current draw style from the state.
  */
  static AlignmentV get(SoState *state) { return (AlignmentV)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default draw style.
  */
  static AlignmentV getDefault();

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoTextAlignmentVElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  virtual ~SoTextAlignmentVElement();
};

#endif // _SO_TEXT_ALIGNMENTV_ELEMENT_

/**/

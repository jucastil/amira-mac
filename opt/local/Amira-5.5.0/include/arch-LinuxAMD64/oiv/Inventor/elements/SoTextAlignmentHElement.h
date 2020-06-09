/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Nov 2004)
**=======================================================================*/

#ifndef  _SO_TEXT_ALIGNMENTH_ELEMENT_
#define  _SO_TEXT_ALIGNMENTH_ELEMENT_

#include <Inventor/elements/SoInt32Element.h>

/**
*  @VSGEXT Stores the current horizontal text alignment.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current horizontal text alignment.
*
*   @SEE_ALSO
*   SoTextProperty
*/
SoEXTENDER_Documented class INVENTOR_API SoTextAlignmentHElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoTextAlignmentHElement);

 public:

    /** AlignmentH */
   enum AlignmentH {
    /** LEFT */
    LEFT   = 0x01,
    /** CENTER */
    CENTER = 0x03,
    /** RIGHT */
    RIGHT  = 0x02
  };

   /**
   *  Sets the current horizontal text alignment in the state.
   */
   static void set(SoState *state, AlignmentH style);

#ifndef IV_STRICT
   /**
   *  Sets the current horizontal text alignment in the state.
   */
  static void set(SoState *state, SoNode *, AlignmentH style) { set(state, style); }
#endif

  /**
  *  Returns current draw style from the state.
  */
  static AlignmentH get(SoState *state) { return (AlignmentH)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default draw style.
  */
  static AlignmentH getDefault();

  /**
  *  Prints element (for debugging).
  */
  virtual void print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoTextAlignmentHElement class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);

 protected:
  virtual ~SoTextAlignmentHElement();
};

#endif // _SO_TEXT_ALIGNMENTH_ELEMENT_

/**/

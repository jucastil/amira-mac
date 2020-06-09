/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jul 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_ANNOT_TEXT3_FONT_SIZE_HINT_ELEMENT_
#define  _SO_ANNOT_TEXT3_FONT_SIZE_HINT_ELEMENT_

#include <Inventor/elements/SoInt32Element.h>

/*----------------------------------------------------------------------------*/
/**
* @VSGEXT Stores the current font size hint of an SoAnnoText3Property node.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current font size hint of an SoAnnoText3Property node.
*   @SEE_ALSO
*   SoAnnoText3Property
*/

SoEXTENDER_Documented class INVENTOR_API SoAnnoText3FontSizeHintElement : public SoInt32Element {
  
  SO_ELEMENT_HEADER(SoAnnoText3FontSizeHintElement);
  
 public:

   /** Font size hint */
  enum FontSizeHint {
    /** Annotation */
    ANNOTATION,
    /** Fit text vector */
    FIT_TEXT_VECTOR
  };
 
  /**
  *  Sets the value in the state.
  */
  static void set(SoState *state, FontSizeHint hint);
  
  /**
  *  Returns the current value from the state.
  */
  static FontSizeHint get(SoState *state);
  
  /**
  *  Returns the default value.
  */
  static FontSizeHint getDefault();

 SoINTERNAL public:
  // Initializes the class
  static void initClass();
  static void exitClass();

  // Initializes element
  virtual void init(SoState *state);
  
 protected:
  virtual ~SoAnnoText3FontSizeHintElement();
};

/*----------------------------------------------------------------------------*/

#endif /* _SO_ANNOT_TEXT3_FONT_SIZE_HINT_ELEMENT_  */

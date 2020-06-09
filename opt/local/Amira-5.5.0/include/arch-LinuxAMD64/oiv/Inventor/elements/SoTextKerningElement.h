/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Nov 2004)
**=======================================================================*/


#ifndef  _SO_TEXT_KERNING_ENABLED_ELEMENT_
#define  _SO_TEXT_KERNING_ENABLED_ELEMENT_

#include <Inventor/elements/SoInt32Element.h>

/**
*  @VSGEXT  Stores the current kerning value.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current kerning value defined through the SoTextProperty node.
*
*   @SEE_ALSO
*   SoTextProperty
*/
SoEXTENDER_Documented class INVENTOR_API SoTextKerningElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoTextKerningElement);

 public:
  
  /** Initializes element */
  virtual void init(SoState *state);

  /** Sets element in state */
  static void set(SoState *state, SbBool isKernedText);

  /** Returns the current element value */
  static SbBool get(SoState *state);

  /** Returns the default element value */
  static SbBool getDefault() { return FALSE; }

 SoINTERNAL public:
  // Initializes the  class
  static void initClass();
  static void exitClass();

 protected:
  virtual ~SoTextKerningElement();
};

#endif // _SO_TEXT_OUTLINE_ENABLED_ELEMENT_

/**/

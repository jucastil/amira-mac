/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Jul 1997)
**=======================================================================*/

                                                             /* include files */
#ifndef  _SO_ANNOT_TEXT3_CHAR_ORIENT_ELEMENT_
#define  _SO_ANNOT_TEXT3_CHAR_ORIENT_ELEMENT_

#include <Inventor/elements/SoInt32Element.h>

/*----------------------------------------------------------------------------*/
/**
* @VSGEXT Stores the current character orientation flag of an SoAnnoText3Property node.
*
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current character orientation flag of an SoAnnoText3Property node.
*   @SEE_ALSO
*   SoAnnoText3Property
*/

SoEXTENDER_Documented class INVENTOR_API SoAnnoText3CharOrientElement : public SoInt32Element {
  
  SO_ELEMENT_HEADER(SoAnnoText3CharOrientElement);
  
 public:

  /**
  *  Sets the value in the state.
  */
  static void set(SoState *state, SbBool isOriented);
  
  /**
  *  Returns the current value from the state.
  */
  static SbBool get(SoState *state);
  
  /**
  *  Returns the default value.
  */
  static SbBool getDefault();

 SoINTERNAL public:
//  Initializes the class
  static void initClass();
  static void exitClass();

//Initializes element
  virtual void init(SoState *state);
  
 protected:
  virtual ~SoAnnoText3CharOrientElement();
} ;

/*----------------------------------------------------------------------------*/

#endif /* _SO_ANNOT_TEXT3_CHAR_ORIENT_ELEMENT_  */

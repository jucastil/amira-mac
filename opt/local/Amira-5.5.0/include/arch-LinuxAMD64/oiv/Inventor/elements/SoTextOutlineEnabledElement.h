/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Feb 1997)
**=======================================================================*/

#ifndef  _SO_TEXT_OUTLINE_ENABLED_ELEMENT_
#define  _SO_TEXT_OUTLINE_ENABLED_ELEMENT_
/* include files */
#include <Inventor/elements/SoInt32Element.h>

/*----------------------------------------------------------------------------*/

/**
*  @VSGEXT Stores the current 3D text outline flag.
* 
*  @ingroup elements
*
*  @DESCRIPTION
*  This element stores the current 3D text outline flag.
* 
*  @SEE_ALSO
*  SoFont
*/
SoEXTENDER_Documented class INVENTOR_API SoTextOutlineEnabledElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoTextOutlineEnabledElement);

 public:
  /**
  *  Set the current element value.
  */
  static void    set(SoState *state, SbBool isOutlineText);

  /**
  *  Returns the current element value.
  */
  static SbBool  get(SoState *state);

  /**
  *  Returns the default element value.
  */
  static SbBool   getDefault()         { return FALSE; }

 SoINTERNAL public:
  // Initializes the  class
  static void    initClass();
  static void    exitClass();

  // Initializes element
  virtual void   init(SoState *state);

 protected:
  virtual ~SoTextOutlineEnabledElement();
};

/*----------------------------------------------------------------------------*/

#endif /* _SO_TEXT_OUTLINE_ENABLED_ELEMENT_ */

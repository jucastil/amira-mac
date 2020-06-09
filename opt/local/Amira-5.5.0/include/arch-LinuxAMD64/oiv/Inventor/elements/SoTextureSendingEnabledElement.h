/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : R. ALBOU (Nov 2001)
**=======================================================================*/

#ifndef  _SO_TEXTURE_SENDING_ENABLED_ELEMENT_
#define  _SO_TEXTURE_SENDING_ENABLED_ELEMENT_
/* include files */
#include <Inventor/elements/SoInt32Element.h>

/*----------------------------------------------------------------------------*/

/**
*  @VSGEXT Stores the information that indicates if texture calls must be sent.
* 
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores information that indicates if texture calls must be sent.
* 
*   @SEE_ALSO
*/
SoEXTENDER_Documented class INVENTOR_API SoTextureSendingEnabledElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoTextureSendingEnabledElement);

 public:
  /**
  *  Sets the current element value.
  */
  static void    set(SoState *state, SbBool flag);

  /**
  *  Returns the current element value.
  */
  static SbBool  get(SoState *state);

  /**
  *  Returns the default element value.
  */
  static SbBool   getDefault()         { return TRUE; }

 SoINTERNAL public:
  // Initializes the  class
  static void    initClass();
  static void    exitClass();

  // Initializes element
  virtual void   init(SoState *state);

 protected:
  virtual ~SoTextureSendingEnabledElement();
};

/*----------------------------------------------------------------------------*/

#endif /* _SO_TEXTURE_SENDING_ENABLED_ELEMENT_ */

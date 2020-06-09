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


#ifndef IV_STRICT
#ifndef _SO_LIGHT_MODEL_ELEMENT
#define _SO_LIGHT_MODEL_ELEMENT

#include <Inventor/elements/SoGLLazyElement.h>

/**
*   Stores the current lighting model (superseded by SoLazyElement).
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current lighting model.
*   This element has been superseded by SoLazyElement. Methods are included for
*   compatibility.
* 
*   @SEE_ALSO
*/

SoEXTENDER_Documented class INVENTOR_API SoLightModelElement {
  
 public:
 /**
 *  These are the available lighting models.
 */
 enum Model {
 /**
 *  No lighting; just use base color.
 */
 BASE_COLOR,
 /**
 *  Phong lighting.
 */
 PHONG 
  };
  
  /**
  *  Sets the current lighting model in the state.
  */
  static void set(SoState *state, Model model)
    { SoLazyElement::setLightModel(state, model); }
  
  /**
  *  Sets the current lighting model in the state.
  */
  static void set(SoState *state, SoNode *, Model model)
    { set(state, model); }
  
  /**
  *  Returns current lighting model from the state.
  */
  static Model get(SoState *state)
    { return (Model)(SoLazyElement::getLightModel(state)); }
  
  /**
  *  Returns the default lighting model.
  */
  static Model getDefault()
    { return (Model)SoLazyElement::getDefaultLightModel(); }
};

#endif /* _SO_LIGHT_MODEL_ELEMENT */
#endif /*IV_STRICT*/

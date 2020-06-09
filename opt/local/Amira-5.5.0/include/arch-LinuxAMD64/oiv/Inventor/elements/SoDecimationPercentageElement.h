/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_DECIMATION_PERCENTAGE_ELEMENT
#define  _SO_DECIMATION_PERCENTAGE_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

/**
* @VSGEXT Stores the current shape decimation percentage.
* 
* @ingroup elements
* 
*   @DESCRIPTION
*   This element stores the current shape decimation percentage.
*   If the SoDecimationTypeElement is set to "PERCENTAGE",
*   shapes should use this element to determine the desired
*   percentage of the total amount of triangles.
*
*   @SEE_ALSO
*   SoGLRenderAction, SoGetPrimitiveCountAction
*/

SoEXTENDER_Documented class INVENTOR_API SoDecimationPercentageElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoDecimationPercentageElement);

 public:
  /**
  *  Sets the current decimation in the state.
  */
  static void         set(SoState *state, float comp);

#ifndef IV_STRICT
  /**
  *  Sets the current decimation in the state.
  */
   static void         set(SoState *state, SoNode *, float comp);
#endif

  /**
  *  Returns current decimation percentage from the state.
  */
  static float        get(SoState *state);

  /**
  *  Returns the default decimation percentage.
  */
  static float        getDefault();

 SoINTERNAL public:
  // Initializes the SoDecimationPercentageElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoDecimationPercentageElement();
};

#endif /* _SO_DECIMATION_PERCENTAGE_ELEMENT */

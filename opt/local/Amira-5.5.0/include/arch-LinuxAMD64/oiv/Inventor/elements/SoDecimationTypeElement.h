/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_DECIMATION_TYPE_ELEMENT
#define  _SO_DECIMATION_TYPE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
*  @VSGEXT Stores the current decimation type.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current decimation type.
*
*   @SEE_ALSO
*   SoGLRenderAction, SoGetPrimitiveCountAction
*/

SoEXTENDER_Documented class INVENTOR_API SoDecimationTypeElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoDecimationTypeElement);

 public:
  /**
  *  These are the available decimation types.
  */
  enum Type {               /** Nodes are allowed to choose themselves. */
    AUTOMATIC,              /** Nodes must use highest level. */
    HIGHEST,                /** Nodes must use lowest level (non-empty). */
    LOWEST,                 /** Nodes should try to reach percentage from DecimationPercentageElement. */
    PERCENTAGE
  };

  /**
  *  Sets the current decimation type in the state.
  */
  static void         set(SoState *state, Type type);

#ifndef IV_STRICT
  /**
  *  Sets the current decimation type in the state.
  */
  static void         set(SoState *state, SoNode *, Type type)
    { set(state, type); }
#endif

  /**
  *  Returns current decimation type from the state.
  */
  static Type         get(SoState *state)
    { return (Type)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default decimation type.
  */
  static Type         getDefault()            { return AUTOMATIC; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoDecimationTypeElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoDecimationTypeElement();
};

#endif /* _SO_DECIMATION_TYPE_ELEMENT */

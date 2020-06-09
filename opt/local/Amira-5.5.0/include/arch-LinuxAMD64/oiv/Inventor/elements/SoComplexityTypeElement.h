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


#ifndef  _SO_COMPLEXITY_TYPE_ELEMENT
#define  _SO_COMPLEXITY_TYPE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
*   Stores the current complexity type.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current complexity type.
*   @SEE_ALSO
*   SoComplexity
*/

SoEXTENDER_Documented class INVENTOR_API SoComplexityTypeElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoComplexityTypeElement);

 public:
    /**
    *  These are the available complexity types:
    */
    enum Type {
    OBJECT_SPACE,           // Complexity computed in object space
    SCREEN_SPACE,           // Complexity computed in screen space
    BOUNDING_BOX            // Bounding box used to represent object
  };

    /**
     *  Sets the current complexity type in the state.
     */
     static void         set(SoState *state, Type type);

#ifndef IV_STRICT
    /**
     *  Sets the current complexity type in the state.
     */
  static void         set(SoState *state, SoNode *, Type type)
    { set(state, type); }
#endif

  /**
  *  Returns current complexity type from the state.
  */
  static Type         get(SoState *state)
    { return (Type)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default complexity type.
  */
  static Type         getDefault(); //                { return OBJECT_SPACE; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoComplexityTypeElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoComplexityTypeElement();
};

#endif /* _SO_COMPLEXITY_TYPE_ELEMENT */

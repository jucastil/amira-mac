/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _SO_BBox_TYPE_ELEMENT
#define  _SO_BBox_TYPE_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
* @VSGEXT Stores the current BBox type.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current BBox type.
*
*   @SEE_ALSO
*   SoComplexity
*/
SoEXTENDER_Documented class INVENTOR_API SoBBoxTypeElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoBBoxTypeElement);

public:
  /**
  *  Available BBox types:
  */
  enum Type {
    // Axis aligned (default)
    BBOX_AABB,
    // Object oriented
    BBOX_OOB
  };

  /**
  *  Sets the current BBox type in the state.
  */
  static void set(SoState *state, Type type);

#ifndef IV_STRICT
  /**
  *  Sets the current BBox type in the state.
  */
  static void         set(SoState *state, SoNode *, Type type)
  { set(state, type); }
#endif

  /**
  *  Returns current BBox type from the state.
  */
  static Type         get(SoState *state)
  { return (Type)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default BBox type.
  */
  static Type         getDefault();

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

  SoINTERNAL public:
  // Initializes the SoBBoxTypeElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

protected:
  virtual ~SoBBoxTypeElement();
};

#endif /* _SO_BBox_TYPE_ELEMENT */

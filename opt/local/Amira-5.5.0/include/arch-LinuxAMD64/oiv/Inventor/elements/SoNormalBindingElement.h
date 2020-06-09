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


#ifndef  _SO_NORMAL_BINDING_ELEMENT
#define  _SO_NORMAL_BINDING_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
*   Stores current normal binding.
*
*   @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current normal binding.
*
*   @SEE_ALSO
*   SoNormalBinding, SoVertexProperty
*/

SoEXTENDER_Documented class INVENTOR_API SoNormalBindingElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoNormalBindingElement);

 public:
 /**
 *  The choice of values is for compatibility
 *  with Open Inventor 2.0 binary format files:
 */
 enum Binding {
 /**
 *  Whole object has same normal.
 */
 OVERALL = 2,
/**
*  One normal for each part of object.
*/
PER_PART = 3,
/**
*  One normal for each part, indexed.
*/
PER_PART_INDEXED = 4,
/**
*  One normal for each face of object.
*/
PER_FACE = 5,
/**
*  One normal for each face, indexed.
*/
PER_FACE_INDEXED = 6,
/**
*  One normal for each vertex.
*/
PER_VERTEX = 7,
/**
*  One normal for each vertex, indexed.
*/
PER_VERTEX_INDEXED = 8
#ifndef IV_STRICT
    // Obsolete bindings:
    ,                       // Comma to continue list
    DEFAULT = PER_VERTEX_INDEXED,
    NONE = OVERALL
#endif

  };

  /**
  *  Sets the current normal binding in the state.
  */
  static void         set(SoState *state, Binding binding)
    { SoInt32Element::set(getClassTypeId(), classStackIndex, state, (int32_t)binding); }

#ifndef IV_STRICT
  /**
  *  Sets the current normal binding in the state.
  */
  static void         set(SoState *state, SoNode *, Binding binding)
    { set(state, binding); }
#endif

  /**
  *  Returns current normal binding from the state.
  */
  static Binding      get(SoState *state)
    { return (Binding)SoInt32Element::get(getClassTypeId(), classStackIndex, state); }

  /**
  *  Returns the default normal binding.
  */
  static Binding      getDefault()            { return PER_VERTEX_INDEXED; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoNormalBindingElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoNormalBindingElement();
};

#endif /* _SO_NORMAL_BINDING_ELEMENT */

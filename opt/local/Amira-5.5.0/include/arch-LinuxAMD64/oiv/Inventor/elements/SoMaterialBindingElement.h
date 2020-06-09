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


#ifndef  _SO_MATERIAL_BINDING_ELEMENT
#define  _SO_MATERIAL_BINDING_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
*   Stores the current material binding.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current material binding.
*
*   @SEE_ALSO
*   SoMaterialBinding, SoVertexProperty
*/

SoEXTENDER_Documented class INVENTOR_API SoMaterialBindingElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoMaterialBindingElement);

 public:
 /**
 *  The choice of values is for compatibility
 *  with Open Inventor 2.0 binary format files.
 */
 enum Binding {
 /**
 *  Whole object has same material.
 */
 OVERALL = 2,
 /**
 *  One material for each part of object.
 */
 PER_PART = 3,
/**
*  One material for each part, indexed.
*/
PER_PART_INDEXED = 4,
/**
*  One material for each face of object.
*/
PER_FACE = 5,
/**
*  One material for each face, indexed.
*/
PER_FACE_INDEXED = 6,
/**
*  One material for each vertex.
*/
PER_VERTEX = 7,
/**
*  One material for each vertex, indexed.
*/
PER_VERTEX_INDEXED = 8
#ifndef IV_STRICT
    // Obsolete bindings:
    ,                       // Comma to continue list
    DEFAULT = OVERALL,
    NONE = OVERALL
#endif

  };

  /**
  *  Sets the current material binding in the state.
  */
  static void         set(SoState *state, Binding binding)
  { SoInt32Element::set(getClassTypeId(), classStackIndex, state, (int32_t)binding); }

#ifndef IV_STRICT
  /**
  *  Sets the current material binding in the state.
  */
  static void         set(SoState *state, SoNode *, Binding binding)
    { set(state, binding); }
#endif

  /**
  *  Returns current material binding from the state.
  */
  static Binding      get(SoState *state)
  { return (Binding)SoInt32Element::get(getClassTypeId(), classStackIndex, state); }

  /**
  *  Returns the default material binding.
  */
  static Binding      getDefault()            { return OVERALL; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoMaterialBindingElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoMaterialBindingElement();
};

#endif /* _SO_MATERIAL_BINDING_ELEMENT */

/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_FLOAT_ELEMENT
#define  _SO_FLOAT_ELEMENT


/**
*   Element's subclasses store a single float, int, or enum value.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element's subclasses store a single float, int, or enum value. This class
*   defines generic matches() and copy() methods.
*
*   @SEE_ALSO
*/

#include <Inventor/elements/SoSubElement.h>

SoEXTENDER_Documented class INVENTOR_API SoFloatElement : public SoElement {

  SO_ELEMENT_ABSTRACT_HEADER(SoFloatElement);

 public:

  /**
  *  Comparison based on value of floats
  */
  virtual SbBool      matches(const SoElement *elt) const;

 SoINTERNAL public:
  // Initializes the SoFloatElement class
  static void         initClass();
  static void         exitClass();

  // Copy method, takes care copying the data.
  virtual SoElement   *copyMatchInfo() const;

  // Set value.  Derived classes have static inline methods
  // that pass in the stack index and cast their type into a float.
  // This just gets an appropriate instance and calls the virtual
  // set.
  //static void         set(int stackIndex, SoState *state, float value);
  static void         set(SoType type, int stackIndex, SoState *state, float value);

  // Virtual set that subclasses can override to implement
  // side-effect behaviors.
  virtual void        setElt(float value);

  // Get value.  Derived classes have static inline methods to pass
  // in the stackIndex and cast the returned value to the right type.

  static float        get(SoType type, int stackIndex, SoState *state)
  {return ((SoFloatElement*)getConstElement(state, type, stackIndex))->data;}

  // Prints element (for debugging)
  virtual void        print(FILE *fp) const;

 protected:
  // Storage for data.
  float data;

  // Destructor
  virtual ~SoFloatElement();
};

#endif /* _SO_FLOAT_ELEMENT */

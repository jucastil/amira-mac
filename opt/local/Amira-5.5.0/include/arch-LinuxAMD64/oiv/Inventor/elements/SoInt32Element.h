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


#ifndef  _SO_INT32_ELEMENT
#define  _SO_INT32_ELEMENT

/**
*  Stores a single int32_t, int, or enum value.
*
* @ingroup elements
*
*   @DESCRIPTION
*   Subclasses store a single int32_t, int, or enum value. This class
*   defines generic matches() and copy() methods.
*
*   @SEE_ALSO
*/

#include <Inventor/elements/SoSubElement.h>

SoEXTENDER_Documented class INVENTOR_API SoInt32Element : public SoElement {

  SO_ELEMENT_ABSTRACT_HEADER(SoInt32Element);

 public:
 /**
 *  Comparison based on value of int32_ts.
 */
	virtual SbBool      matches(const SoElement *elt) const;

 SoINTERNAL public:
  // Initializes the SoInt32Element class
  static void         initClass();
  static void         exitClass();

  // Copy method, takes care copying the data.
  virtual SoElement   *copyMatchInfo() const;

  // Set value.  Derived classes have static inline methods
  // that pass in the stack index and cast their type into a int32_t.
  // This just gets an appropriate instance and calls the virtual
  // set.
  //static void         set(int stackIndex, SoState *state, int32_t value);
  static void         set(SoType type, int stackIndex, SoState *state, int32_t value);

#ifndef IV_STRICT
  static void         set(SoType type, int stackIndex,
                          SoState *state, SoNode *, int32_t value)
  { set(type, stackIndex, state, value); }
#ifndef __NUTC__
  static void         set(SoType type, int stackIndex,
                          SoState *state, SoNode *,
                          long value)     // System long
  { set(type, stackIndex, state, (int32_t)value); }
#endif
#endif

  // Virtual set that subclasses can override to implement
  // side-effect behaviors.
  virtual void        setElt(int32_t value);

  // Get value.  Derived classes have static inline methods to pass
  // in the stackIndex and cast the returned value to the right type.
  // static int32_t              get(int stackIndex, SoState *state)
  // {return getConstElement(state, stackIndex)->data;}

  static int32_t              get(SoType type, int stackIndex, SoState *state)
  {return ((SoInt32Element*)getConstElement(state, type, stackIndex))->data;}

  // Prints element (for debugging)
  virtual void        print(FILE *fp) const;

 protected:
  // Storage for data.
  int32_t data;

  virtual ~SoInt32Element();
};

#endif /* _SO_INT32_ELEMENT */

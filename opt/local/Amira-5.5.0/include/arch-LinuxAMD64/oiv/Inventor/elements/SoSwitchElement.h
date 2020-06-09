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


#ifndef  _SO_SWITCH_ELEMENT
#define  _SO_SWITCH_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
*   Stores the current switch index.
*
*  @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current switch index. This is set by
*   several nodes and is used to allow SoSwitch nodes to inherit the
*   index.
*
*   @SEE_ALSO
*   SoArray, SoMultipleCopy, SoSwitch, SoVRMLSwitch
*/

SoEXTENDER_Documented class INVENTOR_API SoSwitchElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoSwitchElement);

 public:
  /**
  *  Sets the current switch index in the state.
  */
  static void         set(SoState *state, int32_t index)
    { SoInt32Element::set(getClassTypeId(), getClassStackIndex(), state, index); }

#ifndef IV_STRICT
  /**
  *  Sets the current switch index in the state.
  */
  static void         set(SoState *state, SoNode *, int32_t index)
    { set(state, index); }
#endif

  /**
  *  Returns current switch index from the state.
  */
  static int32_t              get(SoState *state)
    { return SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default switch index.
  */
  static int32_t              getDefault()            { return -1; }

 SoINTERNAL public:
  // Initializes the SoSwitchElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoSwitchElement();
};

#endif /* _SO_SWITCH_ELEMENT */

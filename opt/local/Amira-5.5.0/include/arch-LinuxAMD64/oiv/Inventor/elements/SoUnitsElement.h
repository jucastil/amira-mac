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


#ifndef  _SO_UNITS_ELEMENT
#define  _SO_UNITS_ELEMENT

#include <Inventor/elements/SoInt32Element.h>

/**
*   Stores the current units type.
*
* @ingroup elements
*
*   @DESCRIPTION
*   This element stores the current units type.
*
*   @SEE_ALSO
*   SoUnits
*/

SoEXTENDER_Documented class INVENTOR_API SoUnitsElement : public SoInt32Element {

  SO_ELEMENT_HEADER(SoUnitsElement);

 public:
  /**
  *  These are the available types of units.
  */
  enum Units {
    METERS,
    CENTIMETERS,
    MILLIMETERS,
    MICROMETERS,
    MICRONS,
    NANOMETERS,
    ANGSTROMS,
    KILOMETERS,
    FEET,
    INCHES,
    POINTS,
    YARDS,
    MILES,
    NAUTICAL_MILES
  };

  /**
  *  Sets the current units in the state.
  */
  static void         set(SoState *state, Units units)
    { SoInt32Element::set(getClassTypeId(), getClassStackIndex(), state, (int32_t)units); }

#ifndef IV_STRICT
  /**
  *  Sets the current units in the state.
  */
  static void         set(SoState *state, SoNode *, Units units)
    { set(state, units); }
#endif

  /**
  *  Returns current units from the state.
  */
  static Units        get(SoState *state)
    { return (Units)SoInt32Element::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  *  Returns the default units.
  */
  static Units        getDefault()            { return METERS; }

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  // Initializes the SoUnitsElement class
  static void         initClass();
  static void         exitClass();

  // Initializes element
  virtual void        init(SoState *state);

 protected:
  virtual ~SoUnitsElement();
};

#endif /* _SO_UNITS_ELEMENT */

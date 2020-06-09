/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Beilloin (Jan 2009)
**=======================================================================*/

#ifndef  _SO_NEIGHBOR_TOLERANCE_ELEMENT
#define  _SO_NEIGHBOR_TOLERANCE_ELEMENT

#include <Inventor/elements/SoFloatElement.h>

/**
* @VSGEXT Stores the current neighbor tolerance factor.
*
* @ingroup elements
*
* @DESCRIPTION
* Specifies the tolerance value to use when default normals are computed.
* Specifically it determines which (other) points in the shape are close
* enough to influence the normal at each vertex.
* Setting a smaller tolerance value will select a smaller number of points
* and can reduce the time required for computing normals on very large,
* very dense geometry.
*
* The default is 10e-5.
*
* If the OIV_NORMGEN_TOLERANCE environment variable is set, the default is
* 1/OIV_NORMGEN_TOLERANCE.
*
* @SEE_ALSO SoShapeHints, SoPreferences.
*/

SoEXTENDER_Documented class INVENTOR_API SoNeighborToleranceElement : public SoFloatElement {

  SO_ELEMENT_HEADER(SoNeighborToleranceElement);

 public:
   /**
   *  Sets the current tolerance factor in the state.
   */
    static void         set(SoState *state, float tolerance);

  /**
  *  Returns current tolerance factor from the state.
  */
  static float        get(SoState *state)
    { return SoFloatElement::get(getClassTypeId(), getClassStackIndex(), state); }

  /**
  * Returns the default tolerance factor value.
  */
  static inline float getDefault()
  { return s_defaultTolerance; }

  /**
  * set the default tolerance factor value.
  */
  static void setDefault(const float tolerance);

  /**
  *  Prints element (for debugging).
  */
  virtual void        print(FILE *fp) const;

 SoINTERNAL public:
  /** Register SoNeighborToleranceElement in database. */
  static void         initClass();
  /** Unregister SoNeighborToleranceElement in database. */
  static void         exitClass();

  /** Initializes element in the state. */
  virtual void        init(SoState *state);

 protected:
  /** Destructor. */
  virtual ~SoNeighborToleranceElement();

private:
  /** default tolerance factor value */
  static float s_defaultTolerance;
};

#endif /* _SO_NEIGHBOR_TOLERANCE_ELEMENT */

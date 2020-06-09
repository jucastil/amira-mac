/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_CYLINDER_
#define _SB_CYLINDER_

#include <Inventor/SbBase.h>
#include <Inventor/SbLine.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbCylinder
//
//  Represents a cylinder in 3D space.
//
//////////////////////////////////////////////////////////////////////////////


/**
* Class for representing a cylinder.
*
* @ingroup Basics
*
* @DESCRIPTION
*   This class defines a simple cylinder datatype. It is used by the Open Inventor
*   toolkit for arguments or return values.
*
* @SEE_ALSO
*    SbVec3f,
*    SbLine,
*    SbPlane,
*    SbSphere,
*    SoCylinder
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,7}]
*/

class INVENTORBASE_API SbCylinder {
public:
  /**
  * Default constructor.  The cylinder is oriented along the Y axis
  * and has a radius of 1.
  */
  SbCylinder();

  /**
  * Constructor that takes an axis and radius.
  */
  SbCylinder(const SbLine &a, float r);

  /**
  * Change the axis and radius.
  */
  void   setValue(const SbLine &a, float r);

  /**
  * Set the axis.
  */
  void  setAxis(const SbLine &a);
  /**
  * Set the radius.
  */
  void  setRadius(float r);

  /**
  * Return the axis.
  */
  const SbLine &getAxis() const  { return axis; }
  /**
  * Return the radius.
  */
  float    getRadius() const    { return radius; }

  /**
  * Intersect line and cylinder, returning TRUE if there is an intersection.
  * [OIVJAVA-WRAPPER NAME{intersectFirst}]
  */
  SbBool  intersect(const SbLine &l, SbVec3f &intersection) const;
  /**
  * Intersect line and cylinder, returning TRUE if there is an intersection.
  */
  SbBool  intersect(const SbLine &l,
    SbVec3f &enter, SbVec3f &exit) const;

private:
  SbLine  axis;
  float  radius;

  static SbBool unitCylinderIntersect(const SbLine &l,
    SbVec3f &in, SbVec3f &out);

};


#endif /* _SB_CYLINDER_ */

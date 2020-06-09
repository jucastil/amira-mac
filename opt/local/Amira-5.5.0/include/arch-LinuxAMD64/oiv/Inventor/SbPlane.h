/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_PLANE_
#define _SB_PLANE_

#include <Inventor/SbVec.h>

class SbLine;
class SbMatrix;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbPlane
//
//  Represents an oriented plane in 3D space. The plane is defined by
//  a plane normal and a distance from the origin along that normal.
//  SbPlanes may be used to represent either planes or half-spaces. In
//  the latter case (as for the isInHalfSpace() method), the
//  half-space is defined to be all points on the plane or on the side
//  of the plane in the direction of the plane normal.
//
//  The 4 coefficients of the plane equation of an SbPlane can be
//  obtained easily as the 3 coordinates of the plane normal and the
//  distance, in that order.
//
//////////////////////////////////////////////////////////////////////////////


/**
* Oriented plane in 3D.
*
* @ingroup Basics
*
* @DESCRIPTION
*   Represents an oriented plane in 3D. This is a lightweight class/datatype that is
*   used for arguments to some Open Inventor objects.
*
* @SEE_ALSO
*    SbVec3f,
*    SbLine
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,4}]
*/

class INVENTORBASE_API SbPlane {
public:
  /**
  * Default constructor.  The plane is not initialized.
  */
  SbPlane()  {}

  /**
  * Constructor. @B p0@b, @B p1@b, and @B p2@b represent three points in the
  * plane.
  */
  SbPlane(const SbVec3f &p0, const SbVec3f &p1, const SbVec3f &p2);

  /**
  * Constructor. @B normal@b is a normal vector and @B distance @b is distance
  * from origin to
  * plane along normal vector.
  */
  SbPlane(const SbVec3f &normal, float distance);

  /**
  * Constructor. @B normal@b is a normal vector and @B point @b is a point
  * in 3-space for the plane
  * to pass through.
  */
  SbPlane(const SbVec3f &normal, const SbVec3f &point);

  /**
  * Offset a plane by a given distance.
  */
  void    offset(float d);

  /**
  * Intersect line and plane, returning TRUE if there is an intersection, FALSE if
  * line is parallel to plane.
  */
  SbBool intersect(const SbLine &l,
    SbVec3f &intersection) const;

  /**
  * Transforms the plane by the given matrix.
  */
  void    transform(const SbMatrix &matrix);

  /**
  * Returns TRUE if the given point is within the half-space defined by the plane.
  */
  SbBool    isInHalfSpace(const SbVec3f &point) const;


  /**
  * Returns normal vector to plane.
  */
  const SbVec3f &getNormal() const    { return normalVec; }
  /**
  * Returns distance from origin to plane.
  */
  float    getDistanceFromOrigin() const  { return distance; }

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbPlane &p1, const SbPlane &p2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbPlane &p1, const SbPlane &p2)
  { return !(p1 == p2); }

  /**
   * Returns the distance from a point to plane. Positive distance means the point is in the plane's half space.
   */
  float getDistance(const SbVec3f &point) const;

private:
  // Plane is all p such that normalVec . p - distance = 0

  // Normal to the plane
  SbVec3f  normalVec;

  // Distance from origin to plane: distance * normalVec is on the plane
  float  distance;

};


#endif /* _SB_PLANE_ */

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_SPHERE_
#define _SB_SPHERE_

#include <Inventor/SbVec.h>

class SbLine;
class SbBox3f;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbSphere
//
//  Represents a sphere in 3D space.
//
//////////////////////////////////////////////////////////////////////////////


/**
* Class for representing a sphere.
*
* @ingroup Basics
*
* @DESCRIPTION
*   Represents a sphere in 3D. This is a lightweight datatype that is used for
*   arguments or return values in the Open Inventor toolkit. See SoSphere for a
*   database sphere (used for rendering, picking, etc.).
*
* @SEE_ALSO
*    SbVec3f,
*    SbLine,
*    SoSphere
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,4}]
*/

class INVENTORBASE_API SbSphere {
public:

  /**
  * Default constructor.  The sphere is not initialized.
  */
  SbSphere()  {}

  /**
  * Constructor that takes a center and a radius.
  */
  SbSphere(const SbVec3f &c, float r);

  /**
  * Change the center and radius.
  */
  void   setValue(const SbVec3f &c, float r);

  /**
  * Set the center.
  */
  void  setCenter(const SbVec3f &c);
  /**
  * Set the radius.
  */
  void  setRadius(float r);

  /**
  * Return the center.
  */
  const SbVec3f &getCenter() const    { return center; }
  /**
  * Return the radius.
  */
  float    getRadius() const    { return radius; }

  /**
  * Return a sphere containing a given box.
  */
  void  circumscribe(const SbBox3f &box);

  /**
  * Intersect line and sphere, returning TRUE if there is an intersection. The line
  * is treated as a ray.
  * [OIVJAVA-WRAPPER NAME{intersectFirst}]
  */
  SbBool  intersect(const SbLine &l, SbVec3f &intersection) const;
  /**
  * Intersect line and sphere, returning TRUE if there is an intersection. The line
  * is treated as a ray.
  */
  SbBool  intersect(const SbLine &l, SbVec3f &enter, SbVec3f &exit) const;

private:
  SbVec3f  center;
  float  radius;

};

#endif /* _SB_SPHERE_ */

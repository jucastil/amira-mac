#ifndef MC_SPHERE_H
#define MC_SPHERE_H

#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>
#include <mclib/McLine.h>

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
 * @MODIFICATIONS_ENHANCEMENTS @I Copyright (C) 1997-2002 TGS ALL RIGHTS RESERVED @i
 * 
 */ 

class McSphere {
 public:

  /**
   * Constructor.
   */
  McSphere()  {}

  /**
   * Constructor that takes a center and a radius.
   */
  McSphere(const McVec3f &c, float r);

  /**
   * Change the center and radius.
   */
  void   setValue(const McVec3f &c, float r);

  /**
   * Set the center.
   */
  void  setCenter(const McVec3f &c);
  /**
   * Set the radius.
   */
  void  setRadius(float r);

  /**
   * Return the center.
   */
  const McVec3f &getCenter() const    { return center; }
  /**
   * Return the radius.
   */
  float    getRadius() const    { return radius; }

  /**
   * Return a sphere containing a given box.
   */
  void  circumscribe(const McBox3f &box);

  /**
   * Intersect line and sphere, returning TRUE if there is an intersection. The line
   * is treated as a ray.
   */
  bool  intersect(const McLine &l, McVec3f &intersection) const;
  /**
   * Intersect line and sphere, returning TRUE if there is an intersection. The line
   * is treated as a ray.
   */
  bool  intersect(const McLine &l, McVec3f &enter, McVec3f &exit) const;

 private:
  McVec3f  center;
  float  radius;
};

#endif

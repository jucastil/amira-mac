/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup mclib mclib
/// @{
#ifndef MC_ROTATION_H
#define MC_ROTATION_H

#include <math.h>
#include <assert.h>
#include "McVec3f.h"
#include "McWinDLLApi.h"

/* Define the variable MC_ROTATION_NO_MULT in order to hide the declaration of the
   multiplication operators *= and * in McRotation. This allows you to detect code
   which has to be changed in order to work with the new-style McRotation class.
   In all versions of Amira <= 3.1.1 the order of multiplication was different for
   McRotation and SbRotation. McRotation now has been changed so that it is fully
   compatible with SbRotation. However, this requires that old code has to be
   changed. Instead of
      McRotation a,b,c;
      c = a*b;
   you now have to write
      McRotation a,b,c;
      c = b*a;
   If MC_ROTATION_NO_MULT is defined, you get a compiler error when one of the two
   multiplication operators is used. This allows you to identify and fix such code.
*/
// #define MC_ROTATION_NO_MULT

class McMat4f;
class McMat3f;
/** This class stores a rotation. There are several ways to specify a rotation:
    quaternion (4 floats, in the order x, y, z, w), 4x4 rotation matrix, or axis and
    angle. All angles are in radians and all rotations are right-handed. */

class MCLIB_API McRotation {
 public:

  /**
   * Constructor for rotation.
   *
   * WARNING: This contructor leaves the instance uninitialized.
   */
  McRotation()
    {}

  /// Copy constructor.
  McRotation( const McRotation& other ) { *this = other; }

  /**
   * Constructor for rotation. The constructors that take four floats
   * create a quaternion from those floats (careful, this differs from the four
   * numbers in an axis/radian definition).
   */
  McRotation(const float v[4])
    { setValue(v); }

  /**
   * Constructor for rotation. The constructors that take four floats
   * create a quaternion from those floats (careful, this differs from the four
   * numbers in an axis/radian definition).
   */
  McRotation(float q0, float q1, float q2, float q3)
    { setValue(q0, q1, q2, q3); }

  /**
   * Constructor for rotation. The matrix constructor requires a valid
   * rotation matrix.
   */
  McRotation(const McMat4f &m)
    { setValue(m); }

  /**
   * Constructor for rotation. The axis/radians constructor creates a rotation of
   * angle radians about the given axis.
   */
  McRotation(const McVec3f &axis, float radians)
    { setValue(axis, radians); }

  /**
   * Constructors for rotation. The rotateFrom/To constructor defines rotation
   * that rotates
   * from one vector into another. The @B rotateFrom and @B rotateTo vectors
   * are normalized by the constructor before calculating the rotation.
   */
  McRotation(const McVec3f &rotateFrom, const McVec3f &rotateTo)
    { setValue(rotateFrom, rotateTo); }

  /// Constructor that rotates one frame to another
  McRotation(const McVec3f &fromX, const McVec3f& fromY,
             const McVec3f& toX, const McVec3f &toY)
    { setValue(fromX, fromY, toX, toY); }

  /// Assignment operator.
  McRotation& operator=(const McRotation &other) {
      quat[0]=other.quat[0]; quat[1]=other.quat[1];
      quat[2]=other.quat[2]; quat[3]=other.quat[3]; return *this;
  }

  /**
   * Returns pointer to array of 4 components defining quaternion.
   */
  const float  *  getValue() const
    { return (quat); }

  /**
   * Returns 4 individual components of rotation quaternion.
   */
  void    getValue(float &q0, float &q1,
                   float &q2, float &q3) const;

  /**
   * Returns corresponding 3D rotation axis vector and angle in radians.
   */
  void    getValue(McVec3f &axis, float &radians) const;

  /**
   * Returns corresponding 4x4 rotation matrix.
   */
  void    getValue(McMat4f &matrix) const;

  /**
   * Returns corresponding 3x3 rotation matrix.
   */
  void    getValue(McMat3f &matrix) const;

  /// Index operator. Gets access to the @c ith component of the quaternion.
  float& operator[] (int i) { return quat[i]; }

  /** Const version of index operator. Gets const access to the @c ith
      component of the quaternion. */
  const float& operator[] (int i) const { return quat[i]; }

  /**
   * Changes a rotation to be its inverse.
   */
  McRotation &invert();

  /**
   * Returns the inverse of a rotation.
   */
  McRotation    inverse() const
    { McRotation q = *this; return q.invert(); }

  /**
   * Sets value of rotation from array of 4 components of a quaternion.
   */
  McRotation &setValue(const float q[4]);

  /**
   * Sets value of rotation from 4 individual components of a quaternion.
   */
  McRotation &setValue(float q0, float q1, float q2, float q3);

  /**
   * Sets value of rotation from a rotation matrix.
   */
  McRotation &setValue(const McMat4f &m);

  /**
   * Sets value of vector from 3D rotation axis vector and angle in radians.
   */
  McRotation &setValue(const McVec3f &axis, float radians);

  /**
   * Sets rotation to rotate one direction vector to another. The @B rotateFrom 
   * and @B rotateTo arguments are normalized before the rotation is calculated.
   */
  McRotation &setValue(const McVec3f &rotateFrom,
                       const McVec3f &rotateTo);

  /// Rotates one orthogonal frame to another.
  McRotation&	setValue(const McVec3f &fromX, const McVec3f &fromY,
	const McVec3f &toX, const McVec3f &toY);

#ifndef MC_ROTATION_NO_MULT
  /**
   * Multiplies by another rotation; results in product of rotations.
   */
  McRotation & operator *=(const McRotation &q);
#endif

  /**
   * Equality comparison operator.
   */
  friend MCLIB_API int operator ==(const McRotation &q1, const McRotation &q2);

  /**
   * Inequality comparison operator.
   */
  friend MCLIB_API int operator !=(const McRotation &q1, const McRotation &q2)
  { return !(q1 == q2); }

  /**
   * Equality comparison within given tolerance - the square of the length of the
   * maximum distance between the two quaternion vectors.
   */
  bool equals(const McRotation &r, float tolerance) const;

#ifndef MC_ROTATION_NO_MULT
  /**
   * Multiplication of two rotations; results in product of rotations.
   */
  friend MCLIB_API McRotation operator *(const McRotation &q1, const McRotation &q2);
#endif

  /**
   * Multiplies the given vector by the matrix of this rotation.
   */
  void  multVec(const McVec3f &src, McVec3f &dst) const;

  /**
   * Keep the axis the same. Multiply the angle of rotation by the amount
   * @B scaleFactor.
   */
  void scaleAngle( float scaleFactor );

  /**
   * Spherical linear interpolation: as @B t goes from 0 to 1, returned
   * value goes from @B rot0 to @B rot1.
   */
  static McRotation  slerp(const McRotation &rot0,
                           const McRotation &rot1, float t);

  /**
   * Returns a null rotation.
   */
  static McRotation  identity()
    { return McRotation(0.0, 0.0, 0.0, 1.0); }

 private:
  float  quat[4];  // Storage for quaternion components

  // Returns the norm (square of the 4D length) of a rotation's quaterion
  float  norm() const;

  // Normalizes a rotation quaternion to unit 4D length
  void  normalize();
};

#endif

/// @}

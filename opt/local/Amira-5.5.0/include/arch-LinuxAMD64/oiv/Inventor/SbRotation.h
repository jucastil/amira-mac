/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_ROTATION_
#define _SB_ROTATION_

#include <Inventor/SbVec.h>

class SbRotationd;
class SbMatrix;
class SbMatrix3;
class SbMatrixd;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbRotation
//
//  Rotation specfication. It is stored internally as a quaternion,
//  which has 4 floating-point components.
//
//////////////////////////////////////////////////////////////////////////////



/**
* Class for representing a rotation.
*
* @ingroup Basics
*
* @DESCRIPTION
*   Object that stores a rotation. There are several ways to specify a rotation:
*   quaternion (4 floats, in the order x, y, z, w), 4x4 rotation matrix, or axis and
*   angle. All angles are in radians and all rotations are right-handed.
*
*   The rotation value is stored internally as a @I quaternion. @i
*   Quaternion representation is more compact, faster to compute and more
*   numerically stable than rotation matrices.  Quaternion representation
*   allows smooth rotation (spherical linear interpolation) and avoids the
*   problem of "gimbal lock" associated with Euler angles.  It is not necessary
*   to deal directly with quaternions.  Many convenience methods are provided
*   to set and get rotations using matrix and axis/angle representations.
*
*   Rotations are most commonly specified using an axis and an angle
*   in radians.  A common mistake is to use the constructor or setValue method
*   that takes four float values, when intending to set an axis and angle.
*   The methods that take four float values directly specify the quaternion
*   value, which is probably not the intended result.  For example:
*   <PRE>
*     // Create a rotation of PI/2 radians around the Z axis:
*
*     // Incorrect.
*     // (Compiles, but actually sets the quaternion value directly!)
*     SbRotation rotation(0, 0, 1, 1.5707963f);
*
*     // This is the correct rotation.
*     SbRotation rotation( SbVec3f(0, 0, 1), 1.5707963f);
*   </PRE>
*
* @SEE_ALSO
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
*    SbVec3f,
*    SbVec3i32,
*    SbVec3s,
*    SbVec4b,
*    SbVec4d,
*    SbVec4f,
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,4}]
*/

class INVENTORBASE_API SbRotation {
public:

  /**
  * Default constructor.  The initial value is no rotation.
  */
  SbRotation()
  { setValue(0.0f, 0.0f, 0.0f, 1.0f);}

  /**
  * Constructor. The quaternion constructor takes four floats
  * that define a quaternion. @BR
  * Note this is NOT the same as an axis/radian definition.
  */
  SbRotation(const float v[4])
  { setValue(v); }

  /**
  * Constructor. The quaternion constructor takes four floats
  * that define a quaternion. @BR
  * Note this is NOT the same as an axis/radian definition.
  */
  SbRotation(float q0, float q1, float q2, float q3)
  { setValue(q0, q1, q2, q3); }

  /**
  * Constructor. The matrix constructor takes a valid
  * rotation matrix.
  */
  SbRotation(const SbMatrix &m)
  { setValue(m); }

  /**
  * Constructor. The axis/radians constructor creates a rotation of
  * angle radians about the given axis.
  */
  SbRotation(const SbVec3f &axis, float radians)
  { setValue(axis, radians); }

  /**
  * Constructor. The rotateFrom/To constructor defines a rotation
  * that rotates
  * from one vector into another. The @B rotateFrom @b and @B rotateTo @b vectors
  * are normalized by the constructor before calculating the rotation.
  */
  SbRotation(const SbVec3f &rotateFrom, const SbVec3f &rotateTo)
  { setValue(rotateFrom, rotateTo); }

  /**
  * Returns pointer to array of 4 components defining quaternion.
  */
  const float  *  getValue() const
  { return (quat); }

  /**
  * Returns 4 individual components of rotation quaternion.
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  void    getValue(float &q0, float &q1,
    float &q2, float &q3) const;

  /**
  * Returns corresponding 3D rotation axis vector and angle in radians.
  * [OIVJAVA-WRAPPER NAME{decompose},PACK{AxisAngle}]
  */
  void    getValue(SbVec3f &axis, float &radians) const;

  /**
  * Returns corresponding 4x4 rotation matrix.
  * [OIVJAVA-WRAPPER NAME{getMatrix}]
  */
  void    getValue(SbMatrix &matrix) const;

  /**
  * Returns corresponding 3x3 rotation matrix.
  * [OIVJAVA-WRAPPER NAME{getMatrix3}]
  */
  void    getValue(SbMatrix3 &matrix) const;

  /**
  * Returns corresponding 4x4 rotation matrix.
  * [OIVJAVA-WRAPPER NAME{getMatrixd}]
  */
  void    getValue(SbMatrixd &matrix) const;

  /**
  * Changes a rotation to be its inverse.
  */
  SbRotation &invert();

  /**
  * Returns the inverse of a rotation.
  */
  SbRotation    inverse() const
  { SbRotation q = *this; return q.invert(); }

  /**
  * Sets value of rotation from array of 4 components of a quaternion.
  */
  SbRotation &setValue(const float q[4]);

  /**
  * Sets value of rotation from 4 individual components of a quaternion.
  */
  SbRotation &setValue(float q0, float q1, float q2, float q3);

  /**
  * Sets value of rotation from a rotation matrix.
  */
  SbRotation &setValue(const SbMatrix &m);

  /**
  * Sets value of vector from 3D rotation axis vector and angle in radians.
  */
  SbRotation &setValue(const SbVec3f &axis, float radians);

  /**
  * Sets rotation to rotate one direction vector to another. The @B rotateFrom @b
  * and @B rotateTo @b arguments are normalized before the rotation is calculated.
  */
  SbRotation &setValue(const SbVec3f &rotateFrom,
    const SbVec3f &rotateTo);

  /**
  * Sets rotation from a double precision rotation.
  */
  SbRotation &setValue(const SbRotationd &rotated) ;

  /**
  * Sets rotation from a double precision rotation matrix.
  */
  SbRotation &setValue(const SbMatrixd &md) ;

  /**
  * Multiplies by another rotation; results in product of rotations.
  */
  SbRotation & operator *=(const SbRotation &q);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbRotation &q1, const SbRotation &q2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbRotation &q1, const SbRotation &q2)
  { return !(q1 == q2); }

  /**
  * Equality comparison within given tolerance - the square of the length of the
  * maximum distance between the two quaternion vectors.
  */
  SbBool    equals(const SbRotation &r, float tolerance) const;

  /**
  * Multiplication of two rotations; results in product of rotations.
  */
  INVENTORBASE_API friend SbRotation operator *(const SbRotation &q1, const SbRotation &q2);

  /**
  * Multiplies the given vector by the matrix of this rotation.
  */
  void  multVec(const SbVec3f &src, SbVec3f &dst) const;

  /**
  * Keep the axis the same. Multiply the angle of rotation by the amount
  * @B scaleFactor@b.
  */
  void scaleAngle( float scaleFactor );

  /**
  * Spherical linear interpolation: as @B t @b goes from 0 to 1, returned
  * value goes from @B rot0 @b to @B rot1@b.
  */
  static SbRotation  slerp(const SbRotation &rot0,
    const SbRotation &rot1, float t);

  /**
  * Returns a null rotation.
  */
  static SbRotation  identity()
  { return SbRotation(0.0f, 0.0f, 0.0f, 1.0f); }

private:
  float  quat[4];  // Storage for quaternion components

  // Returns the norm (square of the 4D length) of a rotation's quaterion
  float  norm() const;

  // Normalizes a rotation quaternion to unit 4D length
  void  normalize();

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbRotationd
//
//  Rotation specfication. It is stored internally as a quaternion,
//  which has 4 double precision floating-point components.
//
//////////////////////////////////////////////////////////////////////////////

/**
* @VSGEXT Class for representing a rotation (double precision).
*
* @ingroup Basics
*
* @DESCRIPTION
*   Object that stores a rotation using double precision values. Although Open
*   Inventor fields still store only single precision values, for certain
*   applications it is useful and convenient to be able to store and manipulate
*   double precision values, for example, double precision coordinate data or values
*   that will be used for further computation.
*
*   The rotation value is stored internally as a @I quaternion. @i
*   Quaternion representation is more compact, faster to compute and more
*   numerically stable than rotation matrices.  Quaternion representation
*   allows smooth rotation (spherical linear interpolation) and avoids the
*   problem of "gimbal lock" associated with Euler angles.  It is not necessary
*   to deal directly with quaternions.  Many convenience methods are provided
*   to set and get rotations using matrix and axis/angle representations.
*
*   Rotations are most commonly specified using an axis and an angle
*   in radians.  A common mistake is to use the constructor or setValue method
*   that takes four double values, when intending to set an axis and angle.
*   The methods that take four double values directly specify the quaternion
*   value, which is probably not the intended result.  For example:
*   <PRE>
*     // Create a rotation of PI/2 radians around the Z axis:
*
*     // Incorrect.
*     // (Compiles, but actually sets the quaternion value directly!)
*     SbRotationd rotation( 0, 0, 1, 1.5707963 );
*
*     // This is the correct rotation.
*     SbRotation rotationd( SbVec3f(0, 0, 1), 1.5707963 );
*   </PRE>
*
* @SEE_ALSO
*    SbRotation,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
*    SbVec3f,
*    SbVec3i32,
*    SbVec3s,
*    SbVec4b,
*    SbVec4d,
*    SbVec4f,
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,4}]
*/

class INVENTORBASE_API SbRotationd {
public:

  /**
  * Constructor for rotation.  The initial value is no rotation.
  */
  SbRotationd()
  { setValue(0.0, 0.0, 0.0, 1.0); }

  /**
  * Constructor.  The constructors that take four doubles
  * create a quaternion from those doubles (careful, this differs from the four
  * numbers in an axis/radian definition).
  */
  SbRotationd(const double v[4])
  { setValue(v); }

  /**
  * Constructor. The constructors that take four doubles
  * create a quaternion from those doubles (careful, this differs from the four
  * numbers in an axis/radian definition).
  */
  SbRotationd(double q0, double q1, double q2, double q3)
  { setValue(q0, q1, q2, q3); }

  /**
  * Constructor. The matrix constructor requires a valid
  * rotation matrix.
  */
  SbRotationd(const SbMatrixd &m)
  { setValue(m); }

  /**
  * Constructor. The axis/radians constructor creates a rotation of
  * angle radians about the given axis.
  */
  SbRotationd(const SbVec3d &axis, double radians)
  { setValue(axis, radians); }

  /**
  * Constructor. The rotateFrom/To constructor defines
  * rotation that rotates
  * from one vector into another. The @B rotateFrom @b and @B rotateTo @b vectors
  * are normalized by the constructor before calculating the rotation.
  */
  SbRotationd(const SbVec3d &rotateFrom, const SbVec3d &rotateTo)
  { setValue(rotateFrom, rotateTo); }

  /**
  * Returns pointer to array of 4 components defining quaternion.
  */
  const double *getValue() const
  { return (quat); }

  /**
  * Returns 4 individual components of rotation quaternion.
  * [OIVJAVA-WRAPPER NO_WRAP]
  */
  void getValue(double &q0, double &q1,
    double &q2, double &q3) const;

  /**
  * Returns corresponding 3D rotation axis vector and angle in radians.
  * [OIVJAVA-WRAPPER NAME{decompose},PACK{AxisAngle}]
  */
  void    getValue(SbVec3d &axis, double &radians) const;

  /**
  * Returns corresponding 4x4 rotation matrix.
  * [OIVJAVA-WRAPPER NAME{getMatrixd}]
  */
  void    getValue(SbMatrixd &matrix) const;

  /**
  * Returns corresponding 4x4 rotation matrix.
  * [OIVJAVA-WRAPPER NAME{getMatrix}]
  */
  void    getValue(SbMatrix &matrix) const;

  /**
  * Changes a rotation to be its inverse.
  */
  SbRotationd &invert();

  /**
  * Returns the inverse of a rotation.
  */
  SbRotationd    inverse() const
  { SbRotationd q = *this; return q.invert(); }

  /**
  * Sets value of rotation from array of 4 components of a quaternion.
  */
  SbRotationd &setValue(const double q[4]);

  /**
  * Sets value of rotation from 4 individual components of a quaternion.
  */
  SbRotationd &setValue(double q0, double q1, double q2, double q3);

  /**
  * Sets value of rotation from a rotation matrix.
  */
  SbRotationd &setValue(const SbMatrixd &m);

  /**
  * Sets value of vector from 3D rotation axis vector and angle in radians.
  */
  SbRotationd &setValue(const SbVec3d &axis, double radians);

  /**
  * Sets rotation to rotate one direction vector to another. The @B rotateFrom @b
  * and @B rotateTo @b arguments are normalized before the rotation is calculated.
  */
  SbRotationd &setValue(const SbVec3d &rotateFrom,
    const SbVec3d &rotateTo);

  /**
  * Sets rotation from a single precision rotation.
  */
  SbRotationd &setValue(const SbRotation &rotate) ;

  /**
  * Sets rotation from a single precision rotation matrix.
  */
  SbRotationd &setValue(const SbMatrix &m) ;

  /**
  * Multiplies by another rotation; results in product of rotations.
  */
  SbRotationd & operator *=(const SbRotationd &q);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbRotationd &q1, const SbRotationd &q2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbRotationd &q1, const SbRotationd &q2)
  { return !(q1 == q2); }

  /**
  * Equality comparison within given tolerance - the square of the length of the
  * maximum distance between the two quaternion vectors.
  */
  SbBool    equals(const SbRotationd &r, double tolerance) const;

  /**
  * Multiplication of two rotations; results in product of rotations.
  */
  INVENTORBASE_API friend SbRotationd operator *(const SbRotationd &q1, const SbRotationd &q2);

  /**
  * Multiplies the given vector by the matrix of this rotation.
  */
  void  multVec(const SbVec3d &src, SbVec3d &dst) const;

  /**
  * Keep the axis the same. Multiply the angle of rotation by the amount
  * @B scaleFactor@b.
  */
  void scaleAngle( double scaleFactor );

  /**
  * Spherical linear interpolation: as @B t @b goes from 0 to 1, returned value goes from
  * @B rot0 @b to @B rot1@b.
  */
  static SbRotationd  slerp(const SbRotationd &rot0,
    const SbRotationd &rot1, double t);

  /**
  * Returns a null rotation.
  */
  static SbRotationd  identity()
  { return SbRotationd(0.0, 0.0, 0.0, 1.0); }

private:
  double  quat[4];  // Storage for quaternion components

  // Returns the norm (square of the 4D length) of a rotation's quaterion
  double  norm() const;

  // Normalizes a rotation quaternion to unit 4D length
  void  normalize();

};

#endif /* _SB_ROTATION_ */

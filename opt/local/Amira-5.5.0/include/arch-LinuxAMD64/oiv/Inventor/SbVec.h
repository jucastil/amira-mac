/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _SB_VEC_
#define _SB_VEC_

#include <Inventor/SbBase.h>
#include <Inventor/SbMathHelper.h>
#include <Inventor/STL/iostream>

class SbVec2d;
class SbVec3d;
class SbVec3s;
class SbVec4d;
class SbPlane;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec2f
//
//  2D vector used to represent points or directions. Each component of
//  the vector is a float.
//
//////////////////////////////////////////////////////////////////////////////

/**
* 2D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   2D vector class used to store 2D vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
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
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,2}]
*/

class INVENTORBASE_API SbVec2f {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec2f()    { }

  /**
  * Constructor given vector components.
  */
  SbVec2f(const float v[2])    { setValue(v); }

  /**
  * Constructor given vector components.
  */
  SbVec2f(float x, float y)    { setValue(x, y); }

  /**
  * Constructor that sets all components to the same value.
  */
  SbVec2f(float val)    { setValue(val,val); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  float  dot(const SbVec2f &v) const;

  /**
  * Returns vector components.
  */
  const float  *getValue() const  { return vec; }

  /**
  * Returns vector components.
  */
  void  getValue(float &x, float &y) const;

  /**
  * Returns geometric length of vector.
  */
  float  length() const;

  /**
  * Negates each component of vector in place.
  */
  void  negate();

  /**
  * Changes vector to be unit length.
  */
  float  normalize();

  /**
  * Sets the vector components.
  */
  SbVec2f &setValue(const float v[2]);

  /**
  * Sets the vector components.
  */
  SbVec2f &setValue(float x, float y);

  /**
  * Sets value of vector from a double precision vector.
  *
  * If the values stored in the double precision argument(s) are too large to be
  * stored in single precision variables, some loss of data will occur during the
  * data transfer. The loss of data is defined by the standard C type conversion
  * from double to float. It is the application's responsibility to handle this
  * potential loss of data appropriately.
  *
  * NOTE: Open Inventor fields still store only single precision values, not double
  * precision values.
  */
  SbVec2f &setValue(const SbVec2d &vec2d);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  float & operator [](int i) { return (vec[i]); }
  const float & operator [](int i) const   { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec2f & operator *=(float d);

  /**
   * Component-wise vector multiplication operator.
   */
  inline SbVec2f operator *(const SbVec2f &v) const
  {
    return SbVec2f(vec[0]*v.vec[0],
                   vec[1]*v.vec[1]);
  }

  /**
   * Component-wise vector multiplication operator.
   */
  inline SbVec2f& operator *=(const SbVec2f &v)
  {
    *this = (*this)*v;
    return *this;
  }

  /**
  * Component-wise scalar division operator.
  */
  SbVec2f & operator /=(float d);

  /**
  * Component-wise vector addition operator.
  */
  SbVec2f & operator +=(const SbVec2f &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec2f & operator -=(const SbVec2f &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec2f operator -() const;

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2f operator *(const SbVec2f &v, float d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2f operator *(float d, const SbVec2f &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec2f operator /(const SbVec2f &v, float d);

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec2f operator +(const SbVec2f &v1, const SbVec2f &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec2f operator -(const SbVec2f &v1, const SbVec2f &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec2f &v1, const SbVec2f &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec2f &v1, const SbVec2f &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec2f& v);

  /**
  * Equality comparison within given tolerance - the square of the length of the
  * maximum distance between the two vectors.
  */
  SbBool equals(const SbVec2f v, float tolerance) const;

  /**
  * Constructor that converts an arbitrary SbVec2 to an SbVec2f.
  */
  template<typename T>
  explicit SbVec2f(const T& v)
  {
    // Uses operator[](int) to get the required field and float() to convert it.
    vec[0] = float(v[0]);
    vec[1] = float(v[1]);
  }

protected:
  float  vec[2];    // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec2d
//
//  2D vector used to represet points or directions. Each component of
//  the vector is a double float.
//
//////////////////////////////////////////////////////////////////////////////

/**
* @VSGEXT 2D vector class (double precision).
*
* @ingroup Basics
*
* @DESCRIPTION
*   2D vector class used to store 2D vectors and points using double precision
*   values. Although Open Inventor fields still store only single precision values,
*   for certain applications it is useful and convenient to be able to store and
*   manipulate double precision values, for example, double precision coordinate
*   data or values that will be used for further computation.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
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
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,2}]
*/

class INVENTORBASE_API SbVec2d {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec2d()    { }

  /**
  * Constructor given vector components.
  */
  SbVec2d(const double v[2])    { setValue(v); }

  /**
  * Constructor given vector components.
  */
  SbVec2d(double x, double y)    { setValue(x, y); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  double  dot(const SbVec2d &v) const;

  /**
  * Returns vector components.
  */
  const double  *getValue() const  { return vec; }

  /**
  * Returns vector components.
  */
  void  getValue(double &x, double &y) const;

  /**
  * Returns geometric length of vector.
  */
  double  length() const;

  /**
  * Negates each component of vector in place.
  */
  void  negate();

  /**
  * Changes vector to be unit length.
  */
  double  normalize();

  /**
  * Sets the vector components.
  */
  SbVec2d &setValue(const double v[2]);

  /**
  * Sets the vector components.
  */
  SbVec2d &setValue(double x, double y);

  /**
  * Sets value of vector from a single precision vector.
  */
  SbVec2d &setValue(const SbVec2f &vec2f)
  { vec[0] = vec2f[0] ; vec[1] = vec2f[1] ; return (*this) ; }

  //@{
  /**
  * Accesses indexed component of vector.
  */
  double & operator [](int i) { return (vec[i]); }
  const double & operator [](int i) const { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec2d & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec2d & operator /=(double d);

  /**
  * Component-wise vector addition operator.
  */
  SbVec2d & operator +=(const SbVec2d &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec2d & operator -=(const SbVec2d &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec2d operator -() const;

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2d operator *(const SbVec2d &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2d operator *(double d, const SbVec2d &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec2d operator /(const SbVec2d &v, double d);

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec2d operator +(const SbVec2d &v1, const SbVec2d &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec2d operator -(const SbVec2d &v1, const SbVec2d &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec2d &v1, const SbVec2d &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec2d &v1, const SbVec2d &v2)
  { return !(v1 == v2); }

  /**
  * Equality comparison within given tolerance - the square of the length of the
  * maximum distance between the two vectors.
  */
  SbBool equals(const SbVec2d v, double tolerance) const;

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec2d& v);

  /**
  * Constructor that converts an arbitrary SbVec2 to an SbVec2d.
  */
  template<typename T>
  explicit SbVec2d(const T& v)
  {
   // Uses operator[](int) to get the required field and double() to convert it.
   vec[0] = double(v[0]);
   vec[1] = double(v[1]);
  }

protected:
  double  vec[2];    // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec2i32
//
//  2D vector used to represent points or directions. Each component of
//  the vector is a (int32_t) integer.
//
//////////////////////////////////////////////////////////////////////////////
/**
* 2D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   2D vector class used to store 2D vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
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
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{int,2}]
*/
class INVENTORBASE_API SbVec2i32 {
public:
  /**
  *  Default constructor.  The vector is not initialized.
  */
  SbVec2i32()    { }
  /**
  *  Constructor given an array of 2 components.
  */
  SbVec2i32(const int32_t v[2]) { setValue(v); }
  /**
  *  Constructor given 2 individual components.
  */
  SbVec2i32(int32_t x, int32_t y) { setValue(x, y); }
  /**
  *  Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec2i32 &v) const;
  /**
  *  Returns pointer to array of 2 components.
  */
  const int32_t *getValue() const { return vec; }
  /**
  *  Returns 2 individual components.
  */
  void getValue(int32_t &x, int32_t &y) const;
  /**
  *  Negates each component of vector in place.
  */
  void negate();
  /**
  *  Sets value of vector from array of 2 components.
  */
  SbVec2i32 &setValue(const int32_t v[2]);
  /**
  *  Sets value of vector from 2 individual components.
  */
  SbVec2i32 &setValue(int32_t x, int32_t y);
  /**
  *  Accesses indexed component of vector.
  */
  int32_t & operator [](int i) { return (vec[i]); }
  /**
  *  Accesses indexed component of vector.
  */
  const int32_t & operator [](int i) const { return (vec[i]); }
  /**
  *  Component-wise scalar multiplication operator.
  */
  SbVec2i32 & operator *=(int d);
  /**
  *  Component-wise scalar multiplication operator.
  */
  SbVec2i32 & operator *=(double d);

  /**
  *  Component-wise scalar division operator.
  */
  SbVec2i32 & operator /=(int d);
  /**
  *  Component-wise scalar division operator.
  */
  SbVec2i32 & operator /=(double d)
  { return *this *= (1.0 / d); }
  /**
  *   Component-wise vector addition operator.
  */
  SbVec2i32 & operator +=(const SbVec2i32 &u);
  /**
  *   Component-wise vector subtraction operator.
  */
  SbVec2i32 & operator -=(const SbVec2i32 &u);
  /**
  *  Nondestructive unary negation - returns a new vector.
  */
  SbVec2i32 operator -() const;
  /**
  *   Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2i32 operator *(const SbVec2i32 &v, int d);
  /**
  *   Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2i32 operator *(const SbVec2i32 &v, double d);
  /**
  *   Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2i32 operator *(int d, const SbVec2i32 &v)
  { return v * d; }
  /**
  *   Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2i32 operator *(double d, const SbVec2i32 &v)
  { return v * d; }
  /**
  *   Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec2i32 operator /(const SbVec2i32 &v, int d);
  /**
  *   Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec2i32 operator /(const SbVec2i32 &v, double d)
  { return v * (1.0 / d); }
  /**
  *  Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec2i32 operator +(const SbVec2i32 &v1, const SbVec2i32 &v2);
  /**
  *  Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec2i32 operator -(const SbVec2i32 &v1, const SbVec2i32 &v2);
  /**
  *   Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec2i32 &v1, const SbVec2i32 &v2);
  /**
  *   Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec2i32 &v1, const SbVec2i32 &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec2i32& v);

  /**
  * Constructor that converts an arbitrary SbVec2 to an SbVec2i32.
  */
  template<typename T>
  explicit SbVec2i32(const T& v)
  {
    // Uses operator[](int) to get the required field and int32_t() to convert it.
    vec[0] = int32_t(v[0]);
    vec[1] = int32_t(v[1]);
  }



protected:
  int32_t  vec[2];    // Storage for vector components
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec2s
//
//  2D vector used to represet points or directions. Each component of
//  the vector is a (short) integer.
//
//////////////////////////////////////////////////////////////////////////////

/**
* 2D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   2D vector class used to store 2D integer vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
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
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{short,2}]
*/

class INVENTORBASE_API SbVec2s {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec2s()    { }

  /**
  * Constructor given 2 components.
  */
  SbVec2s(const short v[2]) { setValue(v); }

  /**
  * Constructor given 2 components.
  */
  SbVec2s(short x, short y) { setValue(x, y); }

  /**
  * Constructor given an SbVec2i32.
  */
#ifndef OIV_DO_NOT_ALLOW_I32_TO_I16_AUTO_CAST
  SbVec2s(const SbVec2i32 &v);
#endif

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec2s &v) const;

  /**
  * Returns vector components.
  */
  const short *getValue() const { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(short &x, short &y) const;

  /**
  * Negates each component of vector in place.
  */
  void negate();

  /**
  * Sets vector components.
  */
  SbVec2s &setValue(const short v[2]);

  /**
  * Sets vector components.
  */
  SbVec2s &setValue(short x, short y);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  short & operator [](int i) { return (vec[i]); }
  const short & operator [](int i) const { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec2s & operator *=(int d);
  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec2s & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec2s & operator /=(int d);
  /**
  * Component-wise scalar division operator.
  */
  SbVec2s & operator /=(double d)
  { return *this *= (1.0 / d); }

  /**
  * Component-wise vector addition operator.
  */
  SbVec2s & operator +=(const SbVec2s &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec2s & operator -=(const SbVec2s &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec2s operator -() const;

  /**
  * Component-wise set operator.
  */
#ifndef OIV_DO_NOT_ALLOW_I32_TO_I16_AUTO_CAST
  SbVec2s operator = (const SbVec2i32 &v);
#endif

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2s operator *(const SbVec2s &v, int d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2s operator *(const SbVec2s &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2s operator *(int d, const SbVec2s &v)
  { return v * d; }
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec2s operator *(double d, const SbVec2s &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec2s operator /(const SbVec2s &v, int d);
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec2s operator /(const SbVec2s &v, double d)
  { return v * (1.0 / d); }

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec2s operator +(const SbVec2s &v1, const SbVec2s &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec2s operator -(const SbVec2s &v1, const SbVec2s &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec2s &v1, const SbVec2s &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec2s &v1, const SbVec2s &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec2s& v);

  /**
  * Constructor that converts an arbitrary SbVec2 to an SbVec2s.
  */
  template<typename T>
  explicit SbVec2s(const T& v)
  {
    // Uses operator[](int) to get the required field and short() to convert it.
    vec[0] = short(v[0]);
    vec[1] = short(v[1]);
  }

protected:
  short  vec[2];    // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec3f
//
//  3D vector used to represent points or directions. Each component of
//  the vector is a floating-point number.
//
//  WARNING!!!!!  Transcription of arrays of this class assume that the
//    only data stored in this class are three consecutive values.
//    Do not add any extra data members!!!
//
// Internal note:
// It would be convenient to have a conversion constructor that takes an SbVec3d
// (instead of having to create an SbVec3d and then call setValue).  But...
// This is not possible because given an expression like: "aVec3d * 1.2f"
// The compiler can't decide if it should convert the vector to SbVec3f or
// convert the constant to double.
//
//////////////////////////////////////////////////////////////////////////////

/**
* 3D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   3D vector class used to store 3D vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
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
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,3}]
*/

class INVENTORBASE_API SbVec3f {
public:
  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec3f() { }

  /**
  * Constructor given vector components.
  */
  SbVec3f(const float v[3])
  { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; }

  /**
  * Constructor given vector components.
  */
  SbVec3f(float x, float y, float z)
  { vec[0] = x; vec[1] = y; vec[2] = z; }

  /**
  * Constructor given 3 planes.
  */
  SbVec3f(SbPlane &p0, SbPlane &p1, SbPlane &p2);

  /**
  * Returns right-handed cross product of vector and another vector.
  */
  SbVec3f  cross(const SbVec3f &v) const;

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  float  dot(const SbVec3f &v) const {
    return (vec[0] * v.vec[0] + vec[1] * v.vec[1] + vec[2] * v.vec[2]);
  }

  /**
  * Returns vector components.
  */
  const float *getValue() const { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(float &x, float &y, float &z) const;

  /**
  * Returns geometric length of vector.
  */
  float length() const;

  /**
  * Changes vector to be unit length, returning the length before normalization.
  */
  float  normalize();

  /**
  * Negates each component of vector in place.
  */
  void  negate();

  /**
  * Sets the vector components.
  */
  inline SbVec3f &setValue(const float v[3])
  { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; return *this; }

  /**
  * Sets the vector components.
  */
  inline  SbVec3f &setValue(float x, float y, float z)
  { vec[0] = x; vec[1] = y; vec[2] = z; return *this; }

  /**
  * Sets value of vector as the weighted average of 3 other vectors.
  */
  SbVec3f &setValue(const SbVec3f &barycentic,
    const SbVec3f &v0,
    const SbVec3f &v1,
    const SbVec3f &v2);

  /**
  * Sets value of vector from a double precision vector.
  */
  SbVec3f &setValue(const SbVec3d &vec3d);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  float & operator [](int i) { return (vec[i]); }
  const float & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec3f & operator *=(float d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec3f & operator /=(float d);

  /**
  * Component-wise vector addition operator.
  */
  inline SbVec3f & operator +=(const SbVec3f &v)
  {
    vec[0] += v.vec[0];
    vec[1] += v.vec[1];
    vec[2] += v.vec[2];

    return *this;
  }

  /**
  * Component-wise vector subtraction operator.
  */
  SbVec3f & operator -=(const SbVec3f &v);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec3f operator -() const;

  /**
  * Component-wise vector multiplication operator.
  */
  inline SbVec3f operator *(const SbVec3f &v) const
  {
    return SbVec3f(vec[0]*v.vec[0],
                   vec[1]*v.vec[1],
                   vec[2]*v.vec[2]);
  }

  /**
  * Component-wise vector multiplication operator.
  */
  inline SbVec3f& operator *=(const SbVec3f &v)
  {
    *this = (*this)*v;
    return *this;
  }

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend inline SbVec3f operator *(const SbVec3f &v, float d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend inline SbVec3f operator *(float d, const SbVec3f &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend inline SbVec3f operator /(const SbVec3f &v, float d);

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend inline SbVec3f operator +(const SbVec3f &v1, const SbVec3f &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend inline SbVec3f operator -(const SbVec3f &v1, const SbVec3f &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend inline int operator ==(const SbVec3f &v1, const SbVec3f &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend inline int operator !=(const SbVec3f &v1, const SbVec3f &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec3f& v);

  /**
  * Equality comparison within given tolerance - the square of the length of the
  * maximum distance between the two vectors.
  */
  SbBool    equals(const SbVec3f v, float tolerance) const;

  /**
  * Returns principal axis that is closest (based on maximum dot product) to this
  * vector.
  */
  SbVec3f    getClosestAxis() const;

  /**
  * Constructor that converts an arbitrary SbVec3 to an SbVec3f.
  */
  template<typename T>
  explicit SbVec3f(const T& v)
  {
    // Uses operator[](int) to get the required field and float() to convert it.
    vec[0] = float(v[0]);
    vec[1] = float(v[1]);
    vec[2] = float(v[2]);
  }

protected:
  float vec[3];    // Storage for vector components

};

/*******************************************************************************/
inline int
operator ==(const SbVec3f &v1, const SbVec3f &v2)
{
    return (v1.vec[0] == v2.vec[0] &&
	    v1.vec[1] == v2.vec[1] &&
	    v1.vec[2] == v2.vec[2]);
}

/*******************************************************************************/
inline SbVec3f
operator *(const SbVec3f &v, float d)
{
    return SbVec3f(v.vec[0] * d,
		  v.vec[1] * d,
		  v.vec[2] * d);
}

/*******************************************************************************/
inline SbVec3f
operator /(const SbVec3f &v, float d)
{
    return SbVec3f(v.vec[0] / d,
		  v.vec[1] / d,
		  v.vec[2] / d);
}

/*******************************************************************************/
inline SbVec3f
operator +(const SbVec3f &v1, const SbVec3f &v2)
{
    return SbVec3f(v1.vec[0] + v2.vec[0],
		  v1.vec[1] + v2.vec[1],
		  v1.vec[2] + v2.vec[2]);
}

/*******************************************************************************/
inline SbVec3f
operator -(const SbVec3f &v1, const SbVec3f &v2)
{
    return SbVec3f(v1.vec[0] - v2.vec[0],
		   v1.vec[1] - v2.vec[1],
		   v1.vec[2] - v2.vec[2]);
}


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec3d
//
//  3D vector used to represent points or directions. Each component of
//  the vector is a double precision floating-point number.
//
//  WARNING!!!!!  Transcription of arrays of this class assume that the
//    only data stored in this class are three consecutive values.
//    Do not add any extra data members!!!
//
// Internal note:
// It would be convenient to have a conversion constructor that takes an SbVec3d
// (instead of having to create an SbVec3d and then call setValue).  But...
// This is not possible because given an expression like: "aVec3d * 1.2f"
// The compiler can't decide if it should convert the vector to SbVec3f or
// convert the constant to double.
//
//////////////////////////////////////////////////////////////////////////////

/**
* @VSGEXT 3D vector class (double precision).
*
* @ingroup Basics
*
* @DESCRIPTION
*   3D vector class used to store 3D vectors and points. Although Open Inventor
*   fields still store only single precision values, for certain applications it is
*   useful and convenient to be able to store and manipulate double precision
*   values, for example, double precision coordinate data or values that will be
*   used for further computation.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
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
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,3}]
*/

class INVENTORBASE_API SbVec3d {
public:
  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec3d()    { }

  /**
  * Constructor given vector components.
  */
  SbVec3d(const double v[3])
  { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; }

  /**
  * Constructor given vector components.
  */
  inline SbVec3d(double x, double y, double z)
  { vec[0] = x; vec[1] = y; vec[2] = z; }

  /**
  * Constructor given 3 planes.
  */
  SbVec3d(SbPlane &p0, SbPlane &p1, SbPlane &p2);

  /**
  * Returns right-handed cross product of vector and another vector.
  */
  SbVec3d  cross(const SbVec3d &v) const;

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  double  dot(const SbVec3d &v) const;

  /**
  * Returns vector components.
  */
  const double  *getValue() const  { return vec; }

  /**
  * Returns vector components.
  */
  void  getValue(double &x, double &y, double &z) const;

  /**
  * Returns geometric length of vector.
  */
  double  length() const;

  /**
  * Changes vector to be unit length, returning the length before normalization.
  */
  double  normalize();

  /**
  * Negates each component of vector in place.
  */
  void  negate();

  /**
  * Sets the vector components.
  */
  SbVec3d &setValue(const double v[3])
  { vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; return *this; }

  /**
  * Sets the vector components.
  */
  SbVec3d &setValue(double x, double y, double z)
  { vec[0] = x; vec[1] = y; vec[2] = z; return *this; }

  /**
  * Sets value of vector as the weighted average of 3 other vectors.
  */
  SbVec3d &setValue(const SbVec3d &barycentic,
    const SbVec3d &v0,
    const SbVec3d &v1,
    const SbVec3d &v2);

  /**
  * Sets value of vector from a single precision vector.
  */
  inline SbVec3d &setValue(const SbVec3f &vec3f)
  { vec[0] = vec3f[0] ; vec[1] = vec3f[1] ; vec[2] = vec3f[2] ; return (*this) ; }

  //@{
  /**
  * Accesses indexed component of vector.
  */
  double & operator [](int i) { return (vec[i]); }
  const double & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  inline SbVec3d & operator *=(double d)
  {
    vec[0] *= d;
    vec[1] *= d;
    vec[2] *= d;

    return *this;
  }

  /**
  * Component-wise scalar division operator.
  */
  inline SbVec3d & operator /=(double d)
  {
    vec[0] /= d;
    vec[1] /= d;
    vec[2] /= d;

    return *this;
  }

  /**
  * Component-wise vector addition operator.
  */
  inline SbVec3d & operator +=(const SbVec3d &v)
  {
    vec[0] += v.vec[0];
    vec[1] += v.vec[1];
    vec[2] += v.vec[2];

    return *this;
  }

  /**
  * Component-wise vector subtraction operator.
  */
  inline SbVec3d & operator -=(const SbVec3d &v)
  {
    vec[0] -= v.vec[0];
    vec[1] -= v.vec[1];
    vec[2] -= v.vec[2];

    return *this;
  }


  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec3d operator -() const;

  /**
  * Component-wise vector multiplication operator.
  */
  inline SbVec3d operator *(const SbVec3d &v) const
  {
    return SbVec3d(vec[0]*v.vec[0],
                   vec[1]*v.vec[1],
                   vec[2]*v.vec[2]);
  }

  /**
  * Component-wise vector multiplication operator.
  */
  inline SbVec3d& operator *=(const SbVec3d &v)
  {
    *this = (*this)*v;
    return *this;
  }

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3d operator *(const SbVec3d &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3d operator *(double d, const SbVec3d &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec3d operator /(const SbVec3d &v, double d);

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec3d operator +(const SbVec3d &v1, const SbVec3d &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec3d operator -(const SbVec3d &v1, const SbVec3d &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec3d &v1, const SbVec3d &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec3d &v1, const SbVec3d &v2)
  { return !(v1 == v2); }

  /**
  * Equality comparison within given tolerance - the square of the length of the
  * maximum distance between the two vectors.
  */
  SbBool    equals(const SbVec3d v, double tolerance) const;

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec3d& v);

  /**
  * Returns principal axis that is closest (based on maximum dot product) to this
  * vector.
  */
  SbVec3d    getClosestAxis() const;

  /**
  * Constructor that converts an arbitrary SbVec3 to an SbVec3d.
  */
  template<typename T>
  explicit SbVec3d(const T& v)
  {
    // Uses operator[](int) to get the required field and double() to convert it.
    vec[0] = double(v[0]);
    vec[1] = double(v[1]);
    vec[2] = double(v[2]);
  }

protected:
  double vec[3];    // Storage for vector components

};

// Note: This implementation must appear after the declaration of SbVec3d!

inline SbVec3f &SbVec3f::setValue(const SbVec3d &vec3d)
{
  vec[0] = static_cast<float>(vec3d[0]);
  vec[1] = static_cast<float>(vec3d[1]);
  vec[2] = static_cast<float>(vec3d[2]);
  return (*this);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec3i32
//
//  3D vector used to represet points or directions or dimensions. Each
//  component of the vector is a (int32_t) integer.
//
//////////////////////////////////////////////////////////////////////////////
/**
* 3D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   3D vector class used to store 3D vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
*    SbVec3f,
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
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{int,3}]
*/
class INVENTORBASE_API SbVec3i32 {
public:
  /**
  *  Default constructor.  The vector is not initialized.
  */
  SbVec3i32()           { }
  /**
  *  Constructor given an array of 3 components.
  */
  SbVec3i32(const int32_t v[3])       { setValue(v); }
  /**
  * Constructor given 3 individual components.
  */
  SbVec3i32(int32_t x, int32_t y, int32_t z)  { setValue(x, y, z); }
  /**
  * Constructor given an SbVec3s (adapter).
  */
  SbVec3i32( const SbVec3s &vec );
  /**
  *  Returns dot (inner) product of vector and another vector.
  */
  inline int32_t dot(const SbVec3i32 &v) const
  {
    return vec[0] * v.vec[0] + vec[1] * v.vec[1] + vec[2] * v.vec[2];
  }

  /**
  * Returns pointer to array of 3 components.
  */
  const int32_t *getValue() const       { return vec; }
  /**
  *  Returns 3 individual components.
  */
  void getValue(int32_t &x, int32_t &y, int32_t &z) const;
  /**
  *  Negates each component of vector in place.
  */
  void    negate();
  /**
  * Sets value of vector from array of 3 components.
  */
  inline SbVec3i32 &setValue(const int32_t v[3])
  {
    vec[0] = v[0];
    vec[1] = v[1];
    vec[2] = v[2];

    return (*this);
  }

  /**
  * Sets value of vector from 3 individual components.
  */
  inline SbVec3i32 &setValue(int32_t x, int32_t y, int32_t z)
  {
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;

    return (*this);
  }

  /**
  * Sets value of vector from an SbVec3s (adapter).
  */
  SbVec3i32 &setValue(const SbVec3s &v);
  /**
  * Assignment operator given an SbVec3s (adapter).
  */
  SbVec3i32 operator = (const SbVec3s &v);
  /**
  *  Accesses indexed component of vector.
  */
  int32_t & operator [](int i)    { return (vec[i]); }
  /**
  *  Accesses indexed component of vector.
  */
  const int32_t & operator [](int i) const  { return (vec[i]); }
  /**
  *  Component-wise scalar multiplication operator.
  */
  SbVec3i32 & operator *=(int d);
  /**
  *  Component-wise scalar multiplication operator.
  */
  SbVec3i32 & operator *=(double d);

  /**
  *  Component-wise scalar division operator.
  */
  SbVec3i32 & operator /=(int d);
  /**
  *  Component-wise scalar division operator.
  */
  SbVec3i32 & operator /=(double d)
  { return *this *= (1.0 / d); }
  /**
  *  Component-wise vector addition operator.
  */
  inline SbVec3i32 & operator +=(const SbVec3i32 &u)
  {
    vec[0] += u.vec[0];
    vec[1] += u.vec[1];
    vec[2] += u.vec[2];

    return *this;
  }

  /**
  *  Component-wise vector subtraction operator.
  */
  SbVec3i32 & operator -=(const SbVec3i32 &u);
  /**
  *  Nondestructive unary negation - returns a new vector
  */
  SbVec3i32 operator -() const;
  /**
  *  Component-wise binary scalar multiplication operator.
  */
  inline SbVec3i32 operator *(int d) const
  {
    return SbVec3i32(vec[0] * d, vec[1] * d, vec[2] * d);
  }

  /**
  *  Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3i32 operator *(const SbVec3i32 &v, double d);
  /**
  *  Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3i32 operator *(int d, const SbVec3i32 &v)
  { return v * d; }
  /**
  *  Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3i32 operator *(double d, const SbVec3i32 &v)
  { return v * d; }
  /**
  *  Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec3i32 operator /(const SbVec3i32 &v, int d);
  /**
  *  Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec3i32 operator /(const SbVec3i32 &v, double d)
  { return v * (1.0 / d); }
  /**
  *  Component-wise binary vector addition operator.
  */
  inline SbVec3i32 operator +(const SbVec3i32 &v) const
  {
    return SbVec3i32(vec[0] + v.vec[0],
                     vec[1] + v.vec[1],
                     vec[2] + v.vec[2]);
  }

  /**
  *  Component-wise binary vector subtraction operator.
  */

  INVENTORBASE_API friend SbVec3i32 operator -(const SbVec3i32 &v1, const SbVec3i32 &v2)
  {
    return SbVec3i32(v1.vec[0] - v2.vec[0],
                     v1.vec[1] - v2.vec[1],
                     v1.vec[2] - v2.vec[2]);
  }

  /**
  *  Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec3i32 &v1, const SbVec3i32 &v2);
  /**
  *  Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec3i32 &v1, const SbVec3i32 &v2)
  { return !(v1 == v2); }

  /**
   * Writes the vector to the specified output stream.
   */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec3i32& v);

  /**
  * Constructor that converts an arbitrary SbVec3 to an SbVec3i32.
  */
  template<typename T>
  explicit SbVec3i32(const T& v)
  {
    // Uses operator[](int) to get the required field and int32_t() to convert it.
    vec[0] = int32_t(v[0]);
    vec[1] = int32_t(v[1]);
    vec[2] = int32_t(v[2]);
  }

  /**
  * Returns max(x, y, z)
  */
  inline int32_t getMaxComponent() const;

protected:
  int32_t   vec[3];     // Storage for vector components
};

int32_t
SbVec3i32::getMaxComponent() const
{
  return SbMathHelper::Max(SbMathHelper::Max(vec[0], vec[1]), vec[2]);
}

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec3s
//
//  3D vector used to represet points or directions or dimensions. Each
//  component of the vector is a (short) integer.
//
//////////////////////////////////////////////////////////////////////////////



/**
* @VSGEXT 3D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   3D vector class used to store 3D integer vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
*    SbVec3f,
*    SbVec3i32,
*    SbVec4b,
*    SbVec4d,
*    SbVec4f,
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{short,3}]
*/

class INVENTORBASE_API SbVec3s {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec3s()           { }

  /**
  * Constructor given 3 components.
  */
  SbVec3s(const short v[3])       { setValue(v); }

  /**
  * Constructor given 3 components.
  */
  SbVec3s(short x, short y, short z)  { setValue(x, y, z); }

  /**
  * Constructor given an SbVec3i32 (adapter).
  * Note possible loss of data.
  */
#ifndef OIV_DO_NOT_ALLOW_I32_TO_I16_AUTO_CAST
  SbVec3s(const SbVec3i32 &v);
#endif

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec3s &v) const;

  /**
  * Returns vector components.
  */
  const short *getValue() const       { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(short &x, short &y, short &z) const;

  /**
  * Negates each component of vector in place.
  */
  void    negate();

  /**
  * Sets vector components.
  */
  SbVec3s &setValue(const short v[3]);

  /**
  * Sets vector components.
  */
  SbVec3s &setValue(short x, short y, short z);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  short & operator [](int i)    { return (vec[i]); }
  const short & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec3s & operator *=(int d);
  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec3s & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec3s & operator /=(int d);
  /**
  * Component-wise scalar division operator.
  */
  SbVec3s & operator /=(double d)
  { return *this *= (1.0 / d); }

  /**
  * Component-wise vector addition operator.
  */
  SbVec3s & operator +=(const SbVec3s &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec3s & operator -=(const SbVec3s &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec3s operator -() const;

  /**
  * Assignment operator given SbVec3i32 (adapter).
  * Note possible loss of data.
  */
#ifndef OIV_DO_NOT_ALLOW_I32_TO_I16_AUTO_CAST
  SbVec3s operator = (const SbVec3i32 &v);
#endif

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3s operator *(const SbVec3s &v, int d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3s operator *(const SbVec3s &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3s operator *(int d, const SbVec3s &v)
  { return v * d; }
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec3s operator *(double d, const SbVec3s &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec3s operator /(const SbVec3s &v, int d);
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec3s operator /(const SbVec3s &v, double d)
  { return v * (1.0 / d); }

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec3s operator +(const SbVec3s &v1, const SbVec3s &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec3s operator -(const SbVec3s &v1, const SbVec3s &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec3s &v1, const SbVec3s &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec3s &v1, const SbVec3s &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec3s& v);

  /**
  * Constructor that converts an arbitrary SbVec3 to an SbVec3s.
  */
  template<typename T>
  explicit SbVec3s(const T& v)
  {
    // Uses operator[](int) to get the required field and short() to convert it.
    vec[0] = short(v[0]);
    vec[1] = short(v[1]);
    vec[2] = short(v[2]);
  }


protected:
  short   vec[3];     // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec4b
//
//  4D vector. Each component of the vector is a (byte) integer.
//
//////////////////////////////////////////////////////////////////////////////



/**
* @VSGEXT 4D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   4D vector class used to store 4D integer vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
*    SbRotationd,
*    SbVec2d,
*    SbVec2f,
*    SbVec2i32,
*    SbVec2s,
*    SbVec3d,
*    SbVec3f,
*    SbVec3i32,
*    SbVec3s,
*    SbVec4d,
*    SbVec4f,
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{char,4}]
*/

class INVENTORBASE_API SbVec4b {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec4b()           { }

  /**
  * Constructor given 4 components.
  */
  SbVec4b(const char v[4])       { setValue(v); }

  /**
  * Constructor given 4 components.
  */
  SbVec4b(char x, char y, char z, char w)  { setValue(x, y, z, w); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec4b &v) const;

  /**
  * Returns vector components.
  * [OIVJAVA-WRAPPER NAME{getString}]
  */
  const char *getValue() const       { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(char &x, char &y, char &z, char &w) const;

  /**
  * Negates each component of vector in place.
  */
  void    negate();

  /**
  * Sets vector components.
  */
  SbVec4b &setValue(const char v[4]);

  /**
  * Sets vector components.
  */
  SbVec4b &setValue(char x, char y, char z, char w);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  char & operator [](int i)    { return (vec[i]); }
  const char & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4b & operator *=(int d);
  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4b & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec4b & operator /=(int d);
  /**
  * Component-wise scalar division operator.
  */
  SbVec4b & operator /=(double d)
  { return *this *= (1.0 / d); }

  /**
  * Component-wise vector addition operator.
  */
  SbVec4b & operator +=(const SbVec4b &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec4b & operator -=(const SbVec4b &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec4b operator -() const;

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4b operator *(const SbVec4b &v, int d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4b operator *(const SbVec4b &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4b operator *(int d, const SbVec4b &v)
  { return v * d; }
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4b operator *(double d, const SbVec4b &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4b operator /(const SbVec4b &v, int d);
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4b operator /(const SbVec4b &v, double d)
  { return v * (1.0 / d); }

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec4b operator +(const SbVec4b &v1, const SbVec4b &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec4b operator -(const SbVec4b &v1, const SbVec4b &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec4b &v1, const SbVec4b &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec4b &v1, const SbVec4b &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec4b& v);

  /**
  * Constructor that converts an arbitrary SbVec4 to an SbVec4b.
  */
  template<typename T>
  explicit SbVec4b(const T& v)
  {
    // Uses operator[](int) to get the required field and char() to convert it.
    vec[0] = char(v[0]);
    vec[1] = char(v[1]);
    vec[2] = char(v[2]);
    vec[3] = char(v[3]);
  }
protected:
  char   vec[4];     // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec4f
//
//  4D vector used to represet rational points or directions. Each component of
//  the vector is a float.
//
//////////////////////////////////////////////////////////////////////////////

/**
* 4D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   4D vector class used to store homogeneous coordinates. This class is used in
*   Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
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
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{float,4}]
*/

class INVENTORBASE_API SbVec4f {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec4f()    { }

  /**
  * Constructor given vector components.
  */
  SbVec4f(const float v[4])    { setValue(v); }

  /**
  * Constructor given vector components.
  */
  SbVec4f(float x, float y, float z, float w)    { setValue(x, y, z, w); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  float  dot(const SbVec4f &v) const;

  /**
  * Returns the real portion of the vector by dividing by the fourth value.
  */
  void  getReal(SbVec3f &v) const;

  /**
  * Returns vector components.
  */
  const float  *getValue() const  { return vec; }

  /**
  * Returns vector components.
  */
  void  getValue(float &x, float &y, float &z, float &w) const;

  /**
  * Returns geometric length of vector.
  */
  float  length() const;

  /**
  * Negates each component of vector in place.
  */
  void  negate();

  /**
  * Changes vector to be unit length.
  */
  float  normalize();

  /**
  * Sets the vector components.
  */
  SbVec4f &setValue(const float v[4]);

  /**
  * Sets the vector components.
  */
  SbVec4f &setValue(float x, float y, float z, float w);

  /**
  * Sets value of vector from a double precision vector.
  */
  SbVec4f &setValue(const SbVec4d &vec4d);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  float & operator [](int i) { return (vec[i]); }
  const float & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4f & operator *=(float d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec4f & operator /=(float d);

  /**
  * Component-wise vector addition operator.
  */
  SbVec4f & operator +=(const SbVec4f &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec4f & operator -=(const SbVec4f &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec4f operator -() const;

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4f operator *(const SbVec4f &v, float d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4f operator *(float d, const SbVec4f &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4f operator /(const SbVec4f &v, float d);

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec4f operator +(const SbVec4f &v1, const SbVec4f &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec4f operator -(const SbVec4f &v1, const SbVec4f &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec4f &v1, const SbVec4f &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec4f &v1, const SbVec4f &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec4f& v);

  /**
  * Equality comparison within given tolerance - the square of the length of the
  * maximum distance between the two vectors.
  */
  SbBool    equals(const SbVec4f v, float tolerance) const;

  /**
  * Constructor that converts an arbitrary SbVec4 to an SbVec4f.
  */
  template<typename T>
  explicit SbVec4f(const T& v)
  {
    // Uses operator[](int) to get the required field and float() to convert it.
    vec[0] = float(v[0]);
    vec[1] = float(v[1]);
    vec[2] = float(v[2]);
    vec[3] = float(v[3]);
  }

protected:
  float  vec[4];    // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec4d
//
//  4D vector used to represet rational points or directions. Each component of
//  the vector is a double float.
//
//////////////////////////////////////////////////////////////////////////////

/**
* @VSGEXT 4D vector class (double precision).
*
* @ingroup Basics
*
* @DESCRIPTION
*   4D vector class used to store homogeneous coordinates. Although Open Inventor
*   fields still store only single precision values, for certain applications it is
*   useful and convenient to be able to store and manipulate double precision
*   values, for example, double precision coordinate data or values that will be
*   used for further computation.
*
* @SEE_ALSO
*    SbRotation,
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
*    SbVec4f,
*    SbVec4i32,
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{double,4}]
*/

class INVENTORBASE_API SbVec4d {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec4d()    { }

  /**
  * Constructor given vector components.
  */
  SbVec4d(const double v[4])    { setValue(v); }

  /**
  * Constructor given vector components.
  */
  SbVec4d(double x, double y, double z, double w)    { setValue(x, y, z, w); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  double  dot(const SbVec4d &v) const;

  /**
  * Returns the real portion of the vector by dividing by the fourth value.
  */
  void  getReal(SbVec3d &v) const;

  /**
  * Returns vector components.
  */
  const double  *getValue() const  { return vec; }

  /**
  * Returns vector components.
  */
  void  getValue(double &x, double &y, double &z, double &w) const;

  /**
  * Returns geometric length of vector.
  */
  double  length() const;

  /**
  * Negates each component of vector in place.
  */
  void  negate();

  /**
  * Changes vector to be unit length.
  */
  double  normalize();

  /**
  * Sets the vector components.
  */
  SbVec4d &setValue(const double v[4]);

  /**
  * Sets the vector components.
  */
  SbVec4d &setValue(double x, double y, double z, double w);

  /**
  * Sets value of vector from a single precision vector.
  */
  SbVec4d &setValue(const SbVec4f &vec4f)
  { vec[0] = vec4f[0] ; vec[1] = vec4f[1] ; vec[2] = vec4f[2] ;
  vec[3] = vec4f[3] ; return (*this) ;}

  //@{
  /**
  * Accesses indexed component of vector.
  */
  double & operator [](int i) { return (vec[i]); }
  const double & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4d & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec4d & operator /=(double d);

  /**
  * Component-wise vector addition operator.
  */
  SbVec4d & operator +=(const SbVec4d &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec4d & operator -=(const SbVec4d &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec4d operator -() const;

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4d operator *(const SbVec4d &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4d operator *(double d, const SbVec4d &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4d operator /(const SbVec4d &v, double d);

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec4d operator +(const SbVec4d &v1, const SbVec4d &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec4d operator -(const SbVec4d &v1, const SbVec4d &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec4d &v1, const SbVec4d &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec4d &v1, const SbVec4d &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec4d& v);

  /**
  * Equality comparison within given tolerance - the square of the length of the
  * maximum distance between the two vectors.
  */
  SbBool    equals(const SbVec4d v, double tolerance) const;

  /**
  * Constructor that converts an arbitrary SbVec4 to an SbVec4d.
  */
  template<typename T>
  explicit SbVec4d(const T& v)
  {
    // Uses operator[](int) to get the required field and double() to convert it.
    vec[0] = double(v[0]);
    vec[1] = double(v[1]);
    vec[2] = double(v[2]);
    vec[3] = double(v[3]);
  }


protected:
  double  vec[4];    // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec4i32
//
//  4D vector used to represet rational points or directions. Each
//  component of the vector is a (int32_t) integer.
//
//////////////////////////////////////////////////////////////////////////////
/**
* 4D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   4D vector class used to store 4D vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
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
*    SbVec4s,
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{int,4}]
*/
class INVENTORBASE_API SbVec4i32 {
public:
  /**
  *  Default constructor.  The vector is not initialized.
  */
  SbVec4i32()           { }
  /**
  *  Constructor given an array of 4 components.
  */
  SbVec4i32(const int32_t v[4])       { setValue(v); }
  /**
  * Constructor given 4 individual components.
  */
  SbVec4i32(int32_t x, int32_t y, int32_t z, int32_t w)  { setValue(x, y, z, w); }
  /**
  *  Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec4i32 &v) const;
  /**
  * Returns pointer to array of 4 components.
  */
  const int32_t *getValue() const       { return vec; }
  /**
  *  Returns 4 individual components.
  */
  void getValue(int32_t &x, int32_t &y, int32_t &z, int32_t &w) const;
  /**
  *  Negates each component of vector in place.
  */
  void    negate();
  /**
  * Sets value of vector from array of 4 components.
  */
  SbVec4i32 &setValue(const int32_t v[4]);
  /**
  * Sets value of vector from 4 individual components.
  */
  SbVec4i32 &setValue(int32_t x, int32_t y, int32_t z, int32_t w);
  /**
  *  Accesses indexed component of vector.
  */
  int32_t & operator [](int i)    { return (vec[i]); }
  /**
  *  Accesses indexed component of vector.
  */
  const int32_t & operator [](int i) const  { return (vec[i]); }
  /**
  *  Component-wise scalar multiplication operator.
  */
  SbVec4i32 & operator *=(int d);
  /**
  *  Component-wise scalar multiplication operator.
  */
  SbVec4i32 & operator *=(double d);

  /**
  *  Component-wise scalar division operator.
  */
  SbVec4i32 & operator /=(int d);
  /**
  *  Component-wise scalar division operator.
  */
  SbVec4i32 & operator /=(double d)
  { return *this *= (1.0 / d); }
  /**
  *  Component-wise vector addition operator.
  */
  SbVec4i32 & operator +=(const SbVec4i32 &u);
  /**
  *  Component-wise vector subtraction operator.
  */
  SbVec4i32 & operator -=(const SbVec4i32 &u);
  /**
  *  Nondestructive unary negation - returns a new vector
  */
  SbVec4i32 operator -() const;
  /**
  *  Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4i32 operator *(const SbVec4i32 &v, int d);
  /**
  *  Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4i32 operator *(const SbVec4i32 &v, double d);
  /**
  *  Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4i32 operator *(int d, const SbVec4i32 &v)
  { return v * d; }
  /**
  *  Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4i32 operator *(double d, const SbVec4i32 &v)
  { return v * d; }
  /**
  *  Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4i32 operator /(const SbVec4i32 &v, int d);
  /**
  *  Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4i32 operator /(const SbVec4i32 &v, double d)
  { return v * (1.0 / d); }
  /**
  *  Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec4i32 operator +(const SbVec4i32 &v1, const SbVec4i32 &v2);
  /**
  *  Component-wise binary vector subtraction operator.
  */

  INVENTORBASE_API friend SbVec4i32 operator -(const SbVec4i32 &v1, const SbVec4i32 &v2);
  /**
  *  Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec4i32 &v1, const SbVec4i32 &v2);
  /**
  *  Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec4i32 &v1, const SbVec4i32 &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec4i32& v);

  /**
  *  Constructor that converts an arbitrary SbVec4 to an SbVec4i32.
  */
  template<typename T>
  explicit SbVec4i32(const T& v)
  {
    // Uses operator[](int) to get the required field and int32_t() to convert it.
    vec[0] = int32_t(v[0]);
    vec[1] = int32_t(v[1]);
    vec[2] = int32_t(v[2]);
    vec[3] = int32_t(v[3]);
  }

protected:
  int32_t   vec[4];     // Storage for vector components
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec4s
//
//  4D vector. Each component of the vector is a (short) integer.
//
//////////////////////////////////////////////////////////////////////////////



/**
* @VSGEXT 4D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   4D vector class used to store 4D integer vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
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
*    SbVec4ub,
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{short,4}]
*/

class INVENTORBASE_API SbVec4s {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec4s()           { }

  /**
  * Constructor given 4 components.
  */
  SbVec4s(const short v[4])       { setValue(v); }

  /**
  * Constructor given 4 components.
  */
  SbVec4s(short x, short y, short z, short w)  { setValue(x, y, z, w); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec4s &v) const;

  /**
  * Returns vector components.
  */
  const short *getValue() const       { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(short &x, short &y, short &z, short &w) const;

  /**
  * Negates each component of vector in place.
  */
  void    negate();

  /**
  * Sets vector components.
  */
  SbVec4s &setValue(const short v[4]);

  /**
  * Sets vector components.
  */
  SbVec4s &setValue(short x, short y, short z, short w);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  short & operator [](int i)    { return (vec[i]); }
  const short & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4s & operator *=(int d);
  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4s & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec4s & operator /=(int d);
  /**
  * Component-wise scalar division operator.
  */
  SbVec4s & operator /=(double d)
  { return *this *= (1.0 / d); }

  /**
  * Component-wise vector addition operator.
  */
  SbVec4s & operator +=(const SbVec4s &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec4s & operator -=(const SbVec4s &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec4s operator -() const;

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4s operator *(const SbVec4s &v, int d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4s operator *(const SbVec4s &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4s operator *(int d, const SbVec4s &v)
  { return v * d; }
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4s operator *(double d, const SbVec4s &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4s operator /(const SbVec4s &v, int d);
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4s operator /(const SbVec4s &v, double d)
  { return v * (1.0 / d); }

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec4s operator +(const SbVec4s &v1, const SbVec4s &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec4s operator -(const SbVec4s &v1, const SbVec4s &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec4s &v1, const SbVec4s &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec4s &v1, const SbVec4s &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec4s& v);

  /**
  * Constructor that converts an arbitrary SbVec4 to an SbVec4s.
  */
  template<typename T>
  explicit SbVec4s(const T& v)
  {
    // Uses operator[](int) to get the required field and short() to convert it.
    vec[0] = short(v[0]);
    vec[1] = short(v[1]);
    vec[2] = short(v[2]);
    vec[3] = short(v[3]);
  }



protected:
  short   vec[4];     // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec4ui32
//
//  4D vector. Each component of the vector is an (uint32_t) integer.
//
//////////////////////////////////////////////////////////////////////////////



/**
* @VSGEXT 4D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   4D vector class used to store 4D integer vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
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
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{int,4}]
*/

class INVENTORBASE_API SbVec4ui32 {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec4ui32()           { }

  /**
  * Constructor given 4 components.
  */
  SbVec4ui32(const uint32_t v[4])       { setValue(v); }

  /**
  * Constructor given 4 components.
  */
  SbVec4ui32(uint32_t x, uint32_t y, uint32_t z, uint32_t w)
  { setValue(x, y, z, w); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec4ui32 &v) const;

  /**
  * Returns vector components.
  */
  const uint32_t *getValue() const       { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(uint32_t &x, uint32_t &y,
    uint32_t &z, uint32_t &w) const;

  /**
  * Sets vector components.
  */
  SbVec4ui32 &setValue(const uint32_t v[4]);

  /**
  * Sets vector components.
  */
  SbVec4ui32 &setValue(uint32_t x, uint32_t y,
    uint32_t z, uint32_t w);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  uint32_t & operator [](int i)    { return (vec[i]); }
  const uint32_t & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4ui32 & operator *=(int d);
  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4ui32 & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec4ui32 & operator /=(int d);
  /**
  * Component-wise scalar division operator.
  */
  SbVec4ui32 & operator /=(double d)
  { return *this *= (1.0 / d); }

  /**
  * Component-wise vector addition operator.
  */
  SbVec4ui32 & operator +=(const SbVec4ui32 &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec4ui32 & operator -=(const SbVec4ui32 &u);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4ui32 operator *(const SbVec4ui32 &v, int d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4ui32 operator *(const SbVec4ui32 &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4ui32 operator *(int d, const SbVec4ui32 &v)
  { return v * d; }
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4ui32 operator *(double d, const SbVec4ui32 &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4ui32 operator /(const SbVec4ui32 &v, int d);
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4ui32 operator /(const SbVec4ui32 &v, double d)
  { return v * (1.0 / d); }

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec4ui32 operator +(const SbVec4ui32 &v1, const SbVec4ui32 &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec4ui32 operator -(const SbVec4ui32 &v1, const SbVec4ui32 &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec4ui32 &v1, const SbVec4ui32 &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec4ui32 &v1, const SbVec4ui32 &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec4ui32& v);

  /**
  * Constructor that converts an arbitrary SbVec4 to an SbVec4ui32.
  */
  template<typename T>
  explicit SbVec4ui32(const T& v)
  {
    // Uses operator[](int) to get the required field and uint32_t() to convert it.
    vec[0] = uint32_t(v[0]);
    vec[1] = uint32_t(v[1]);
    vec[2] = uint32_t(v[2]);
    vec[3] = uint32_t(v[3]);
  }
protected:
  uint32_t   vec[4];     // Storage for vector components

};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec4us
//
//  4D vector. Each component of the vector is an (unsigned short) integer.
//
//////////////////////////////////////////////////////////////////////////////



/**
* @VSGEXT 4D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   4D vector class used to store 4D integer vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
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
*    SbVec4ui32
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{short,4}]
*/

class INVENTORBASE_API SbVec4us {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec4us()           { }

  /**
  * Constructor given 4 components.
  */
  SbVec4us(const unsigned short v[4])       { setValue(v); }

  /**
  * Constructor given 4 components.
  */
  SbVec4us(unsigned short x, unsigned short y, unsigned short z, unsigned short w)
  { setValue(x, y, z, w); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec4us &v) const;

  /**
  * Returns vector components.
  */
  const unsigned short *getValue() const       { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(unsigned short &x, unsigned short &y, unsigned short &z, unsigned short &w) const;

  /**
  * Negates each component of vector in place.
  */
  void    negate();

  /**
  * Sets vector components.
  */
  SbVec4us &setValue(const unsigned short v[4]);

  /**
  * Sets vector components.
  */
  SbVec4us &setValue(unsigned short x, unsigned short y, unsigned short z, unsigned short w);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  unsigned short & operator [](int i)    { return (vec[i]); }
  const unsigned short & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4us & operator *=(int d);
  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4us & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec4us & operator /=(int d);
  /**
  * Component-wise scalar division operator.
  */
  SbVec4us & operator /=(double d)
  { return *this *= (1.0 / d); }

  /**
  * Component-wise vector addition operator.
  */
  SbVec4us & operator +=(const SbVec4us &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec4us & operator -=(const SbVec4us &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec4us operator -() const;

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4us operator *(const SbVec4us &v, int d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4us operator *(const SbVec4us &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4us operator *(int d, const SbVec4us &v)
  { return v * d; }
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4us operator *(double d, const SbVec4us &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4us operator /(const SbVec4us &v, int d);
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4us operator /(const SbVec4us &v, double d)
  { return v * (1.0 / d); }

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec4us operator +(const SbVec4us &v1, const SbVec4us &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec4us operator -(const SbVec4us &v1, const SbVec4us &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec4us &v1, const SbVec4us &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec4us &v1, const SbVec4us &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec4us& v);

  /**
  * Constructor that converts an arbitrary SbVec4 to an SbVec4us.
  */
  template<typename T>
  explicit SbVec4us(const T& v)
  {
    // Uses operator[](int) to get the required field and unsigned short() to convert it.
    vec[0] = static_cast<unsigned short>(v[0]);
    vec[1] = static_cast<unsigned short>(v[1]);
    vec[2] = static_cast<unsigned short>(v[2]);
    vec[3] = static_cast<unsigned short>(v[3]);
  }
protected:
  unsigned short   vec[4];     // Storage for vector components

};


//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec4ub
//
//  4D vector. Each component of the vector is an (unsigned byte) integer.
//
//////////////////////////////////////////////////////////////////////////////



/**
* @VSGEXT 4D vector class.
*
* @ingroup Basics
*
* @DESCRIPTION
*   4D vector class used to store 4D integer vectors and points. This class is used
*   throughout Open Inventor for arguments and return values.
*
* @SEE_ALSO
*    SbRotation,
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
*    SbVec4ui32,
*    SbVec4us
*
* [OIVJAVA-WRAPPER-CLASS BASIC_TYPE{true},LAYOUTED_ARRAY_TYPE{char,4}]
*/

class INVENTORBASE_API SbVec4ub {
public:

  /**
  * Default constructor.  The vector is not initialized.
  */
  SbVec4ub()           { }

  /**
  * Constructor given 4 components.
  */
  SbVec4ub(const unsigned char v[4])       { setValue(v); }

  /**
  * Constructor given 4 components.
  */
  SbVec4ub(unsigned char x, unsigned char y, unsigned char z, unsigned char w)
  { setValue(x, y, z, w); }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  int32_t dot(const SbVec4ub &v) const;

  /**
  * Returns vector components.
  */
  const unsigned char *getValue() const       { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(unsigned char &x, unsigned char &y, unsigned char &z, unsigned char &w) const;

  /**
  * Negates each component of vector in place.
  */
  void    negate();

  /**
  * Sets vector components.
  */
  SbVec4ub &setValue(const unsigned char v[4]);

  /**
  * Sets vector components.
  */
  SbVec4ub &setValue(unsigned char x, unsigned char y, unsigned char z, unsigned char w);

  //@{
  /**
  * Accesses indexed component of vector.
  */
  unsigned char & operator [](int i)    { return (vec[i]); }
  const unsigned char & operator [](int i) const  { return (vec[i]); }
  //@}

  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4ub & operator *=(int d);
  /**
  * Component-wise scalar multiplication operator.
  */
  SbVec4ub & operator *=(double d);

  /**
  * Component-wise scalar division operator.
  */
  SbVec4ub & operator /=(int d);
  /**
  * Component-wise scalar division operator.
  */
  SbVec4ub & operator /=(double d)
  { return *this *= (1.0 / d); }

  /**
  * Component-wise vector addition operator.
  */
  SbVec4ub & operator +=(const SbVec4ub &u);
  /**
  * Component-wise vector subtraction operator.
  */
  SbVec4ub & operator -=(const SbVec4ub &u);

  /**
  * Nondestructive unary negation - returns a new vector.
  */
  SbVec4ub operator -() const;

  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4ub operator *(const SbVec4ub &v, int d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4ub operator *(const SbVec4ub &v, double d);
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4ub operator *(int d, const SbVec4ub &v)
  { return v * d; }
  /**
  * Component-wise binary scalar multiplication operator.
  */
  INVENTORBASE_API friend SbVec4ub operator *(double d, const SbVec4ub &v)
  { return v * d; }
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4ub operator /(const SbVec4ub &v, int d);
  /**
  * Component-wise binary scalar division operator.
  */
  INVENTORBASE_API friend SbVec4ub operator /(const SbVec4ub &v, double d)
  { return v * (1.0 / d); }

  /**
  * Component-wise binary vector addition operator.
  */
  INVENTORBASE_API friend SbVec4ub operator +(const SbVec4ub &v1, const SbVec4ub &v2);

  /**
  * Component-wise binary vector subtraction operator.
  */
  INVENTORBASE_API friend SbVec4ub operator -(const SbVec4ub &v1, const SbVec4ub &v2);

  /**
  * Equality comparison operator.
  */
  INVENTORBASE_API friend int operator ==(const SbVec4ub &v1, const SbVec4ub &v2);
  /**
  * Inequality comparison operator.
  */
  INVENTORBASE_API friend int operator !=(const SbVec4ub &v1, const SbVec4ub &v2)
  { return !(v1 == v2); }

  /**
  * Writes the vector to the specified output stream.
  */
  INVENTORBASE_API friend inline std::ostream& operator << (std::ostream& os, const SbVec4ub& v);

  /**
  * Constructor that converts an arbitrary SbVec4 to an SbVec4ub.
  */
  template<typename T>
  explicit SbVec4ub(const T& v)
  {
    // Uses operator[](int) to get the required field and unsigned char() to convert it.
    vec[0] = static_cast<unsigned char>(v[0]);
    vec[1] = static_cast<unsigned char>(v[1]);
    vec[2] = static_cast<unsigned char>(v[2]);
    vec[3] = static_cast<unsigned char>(v[3]);
  }

  /**
   * Clamp each component between a and b
   */
  inline void clamp(unsigned char a, unsigned char b)
  {
    vec[0] = SbMathHelper::Clamp(vec[0], a, b);
    vec[1] = SbMathHelper::Clamp(vec[1], a, b);
    vec[2] = SbMathHelper::Clamp(vec[2], a, b);
    vec[3] = SbMathHelper::Clamp(vec[3], a, b);
  }
protected:
  unsigned char   vec[4];     // Storage for vector components

};

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec2s& v)
{
  return os << "(" << v[0] << ", " << v[1] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec2i32& v)
{
  return os << "(" << v[0] << ", " << v[1] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec2f& v)
{
  return os << "(" << v[0] << ", " << v[1] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec2d& v)
{
  return os << "(" << v[0] << ", " << v[1] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec3s& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec3i32& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec3d& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec3f& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}


/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec4b& v)
{
  return os << "(" << static_cast<int>(v[0]) << ", " << static_cast<int>(v[1]) << ", " << static_cast<int>(v[2]) << ", " << static_cast<int>(v[3]) << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec4d& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec4f& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec4i32& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec4s& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec4ub& v)
{
  return os << "(" << static_cast<unsigned int>(v[0]) << ", " << static_cast<unsigned int>(v[1]) << ", " << static_cast<unsigned int>(v[2]) << ", " << static_cast<unsigned int>(v[3]) << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec4ui32& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}

/**
* Writes the vector to the specified output stream.
*/
inline std::ostream& operator << (std::ostream& os, const SbVec4us& v)
{
  return os << "(" << v[0] << ", " << v[1] << ", " << v[2] << ", " << v[3] << ")";
}


#endif /* _SB_VEC_ */

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef  _MBVEC3_H
#define  _MBVEC3_H

#ifdef _WIN32
#  pragma warning( push )
#  pragma warning(disable:4250)
#endif


#include <Inventor/STL/iostream>
#include <Inventor/STL/limits>

#include <cmath>

/**
 * @DTEXT Class defining a vector or a point of 3 coordinates.
 * 
 * @ingroup MeshIViz
 * 
 * @DESCRIPTION
 * 3D vector class used to store 3D vectors and points.
 * This class is similar to the standard Open Inventor SbVec3 classes,
 * but exists to allow MeshViz Extraction to be used independently of
 * Open Inventor.
 * 
 */
template <typename _T>
class MbVec3
{
public:
  /** Returns the maximum value for a vector */
  static MbVec3 numeric_limit_max()
  {
    return MbVec3<_T>(std::numeric_limits<_T>::max());
  }

  /** Constructor (vector is initialized to zero values) */
  MbVec3() 
  { 
    vec[0] = vec[1] = vec[2] = 0; 
  }
  /** Constructor */
  MbVec3(const _T v[3])
  { 
    vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; 
  }

  /** Constructor */
  MbVec3(_T x, _T y, _T z)
  { 
    vec[0] = x; vec[1] = y; vec[2] = z; 
  }

  /** Constructor */
  explicit MbVec3(char v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  explicit MbVec3(unsigned char v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  explicit MbVec3(short v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  explicit MbVec3(unsigned short v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  explicit MbVec3(int v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  explicit MbVec3(size_t v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  explicit MbVec3(long v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

#if defined(_WIN32)
  /** Constructor */
  explicit MbVec3(unsigned long v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }
#endif

  /** Constructor */
  explicit MbVec3(float v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  explicit MbVec3(double v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  explicit MbVec3(long double v)
  { 
    vec[0] = (_T)v; vec[1] = (_T)v; vec[2] = (_T)v; 
  }

  /** Constructor */
  template<typename _MbVec3T>
  explicit MbVec3(const _MbVec3T& v)
  {
    vec[0] = _T(v[0]);
    vec[1] = _T(v[1]);
    vec[2] = _T(v[2]);
  }

  /**
  * Returns right-handed cross product of vector and another vector.
  */
  MbVec3  cross(const MbVec3<_T> &v) const
  {
    return MbVec3<_T>(vec[1] * v.vec[2] - vec[2] * v.vec[1],
      vec[2] * v.vec[0] - vec[0] * v.vec[2],
      vec[0] * v.vec[1] - vec[1] * v.vec[0]);
  }

  /**
  * Returns dot (inner) product of vector and another vector.
  */
  _T  dot(const MbVec3<_T> &v) const 
  {
    return (vec[0] * v.vec[0] + vec[1] * v.vec[1] + vec[2] * v.vec[2]);
  }

  /**
  * Returns pointer to vector components.
  */
  const _T *getValue() const { return vec; }

  /**
  * Returns vector components.
  */
  void getValue(_T &x, _T &y, _T &z) const
  {
    x = vec[0]; y = vec[1]; z = vec[2];
  }

  /**
  * Returns geometric length of vector.
  */
  _T length() const
  {
    return _T(sqrt(double(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2])));
  }

  /**
  * Changes vector to be unit length, returning the length before normalization.
  */
  _T  normalize();

  /**
  * Negates each component of vector in place.
  */
  void  negate()
  {
    vec[0] = -vec[0]; vec[1] = -vec[1]; vec[2] = -vec[2];
  }

  /**
  * Component-wise vector multiplication.
  */
  MbVec3 mult(const MbVec3<_T> &v) const 
  {
    return MbVec3<_T>(vec[0] * v.vec[0], vec[1] * v.vec[1],vec[2] * v.vec[2]) ;
  }

    /**
  * Component-wise vector division.
  */
  MbVec3 div(const MbVec3<_T> &v) const 
  {
    return MbVec3<_T>(vec[0] / v.vec[0], vec[1] / v.vec[1],vec[2] / v.vec[2]) ;
  }


  /**
  * Sets the vector components.
  */
  MbVec3<_T>& setValue(const _T v[3])
  { 
    vec[0] = v[0]; vec[1] = v[1]; vec[2] = v[2]; return *this; 
  }

  /**
  * Sets the vector components.
  */
  MbVec3<_T> &setValue(_T x, _T y, _T z)
  { 
    vec[0] = x; vec[1] = y; vec[2] = z; return *this; 
  }

  //@{
  /**
  * Accesses indexed component of vector.
  */
  _T& operator [](int i) { return (vec[i]); }
  const _T & operator [](int i) const  { return (vec[i]); }
  _T& operator [](size_t i) { return (vec[i]); }
  const _T & operator [](size_t i) const  { return (vec[i]); }
//@}

  /**
  * Component-wise setting. All components are set to d.
  */
  MbVec3 & operator =(_T d)
  {
    vec[0] = vec[1] = vec[2] = d;
    return *this;
  }

  /**
  * Component-wise scalar multiplication operator.
  */
  MbVec3 & operator *=(_T d)
  {
    vec[0] *= d;
    vec[1] *= d;
    vec[2] *= d;
    return *this;
  }

  /**
  * Component-wise scalar division operator.
  */
  MbVec3 & operator /=(_T d)
  { 
    vec[0] /= d;
    vec[1] /= d;
    vec[2] /= d;
    return *this; 
  }

  /**
  * Component-wise vector addition operator.
  */
  MbVec3 & operator +=(const MbVec3 &v)
  {
    vec[0] += v.vec[0];
    vec[1] += v.vec[1];
    vec[2] += v.vec[2];
    return *this;
  }

  /**
  * Component-wise vector subtraction operator.
  */
  MbVec3 & operator -=(const MbVec3 &v)
  {
    vec[0] -= v.vec[0];
    vec[1] -= v.vec[1];
    vec[2] -= v.vec[2];
    return *this;
  }


  /**
  * Nondestructive unary negation - returns a new vector.
  */
  MbVec3 operator -() const
  {
    return MbVec3<_T>(-vec[0],-vec[1],-vec[2]);
  }

  /**
  * Component-wise vector multiplication operator.
  */
  friend MbVec3 operator *(const MbVec3 &v1, const MbVec3 &v2)
  {
    return MbVec3(v1.vec[0] * v2.vec[0], v1.vec[1] * v2.vec[1], v1.vec[2] * v2.vec[2]);
  }

  /**
  * Component-wise binary scalar multiplication operator.
  */
  friend MbVec3 operator *(const MbVec3 &v, _T d)
  {
    return MbVec3<_T>(v.vec[0] * d, v.vec[1] * d, v.vec[2] * d);
  }

  /**
  * Component-wise binary scalar multiplication operator.
  */
  friend MbVec3 operator *(_T d, const MbVec3 &v)
  { return v * d; }

  /**
  * Component-wise binary scalar division operator.
  */
  friend MbVec3 operator /(const MbVec3 &v, _T d)
  { 
    return MbVec3<_T>(v.vec[0] / d, v.vec[1] / d, v.vec[2] / d);
  }

  /**
  * Component-wise vector division operator.
  */
  friend MbVec3 operator /(const MbVec3 &v1, const MbVec3 &v2)
  {
    return MbVec3(v1.vec[0] / v2.vec[0], v1.vec[1] / v2.vec[1], v1.vec[2] / v2.vec[2]);
  }

  /**
  * Component-wise binary vector addition operator.
  */
  friend MbVec3 operator +(const MbVec3 &v1, const MbVec3 &v2)
  {
    return MbVec3(v1.vec[0] + v2.vec[0], v1.vec[1] + v2.vec[1], v1.vec[2] + v2.vec[2]);
  }

  /**
  * Component-wise binary scalar addition operator.
  */
  friend MbVec3 operator +(const MbVec3 &v, _T d)
  {
    return MbVec3(v.vec[0] + d, v.vec[1] + d, v.vec[2] + d);
  }

  /**
  * Component-wise binary scalar addition operator.
  */
  friend MbVec3 operator +(_T d, const MbVec3 &v)
  {
    return MbVec3(v.vec[0] + d, v.vec[1] + d, v.vec[2] + d);
  }

  /**
  * Component-wise binary vector subtraction operator.
  */
  friend MbVec3 operator -(const MbVec3 &v1, const MbVec3 &v2)
  {
    return MbVec3(v1.vec[0] - v2.vec[0], v1.vec[1] - v2.vec[1], v1.vec[2] - v2.vec[2]);
  }

  /**
  * Component-wise binary scalar subtraction operator.
  */
  friend MbVec3 operator -(const MbVec3 &v, _T d)
  {
    return MbVec3(v.vec[0] - d, v.vec[1] - d, v.vec[2] - d);
  }

  /**
  * Equality comparison operator.
  */
  friend bool operator ==(const MbVec3 &v1, const MbVec3 &v2)
  {
    return (v1.vec[0] == v2.vec[0] && v1.vec[1] == v2.vec[1] && v1.vec[2] == v2.vec[2]);
  }

  /**
  * Inequality comparison operator.
  */
  friend bool operator !=(const MbVec3 &v1, const MbVec3 &v2)
  { 
    return !(v1 == v2); 
  }

  /**
  * Length comparison operator.
  */
  friend bool operator <(const MbVec3 &v1, const MbVec3 &v2)
  { 
    return v1.length() < v2.length(); 
  }

  /**
  * Length comparison operator.
  */
  friend bool operator <=(const MbVec3 &v1, const MbVec3 &v2)
  { 
    return v1.length() <= v2.length(); 
  }

  /**
  * Length comparison operator.
  */
  friend bool operator >(const MbVec3 &v1, const MbVec3 &v2)
  { 
    return v1.length() > v2.length(); 
  }

  /**
  * Length comparison operator.
  */
  friend bool operator >=(const MbVec3 &v1, const MbVec3 &v2)
  { 
    return v1.length() >= v2.length(); 
  }

  /**
  * Writes the vector to the specified output stream.
  */
  friend inline std::ostream& operator << (std::ostream& os, const MbVec3& v)
  {
    return os << "(" << v.vec[0] << "," << v.vec[1] << "," << v.vec[2] << ")";
  }


protected:
  _T vec[3];
};

template <typename _T>
_T  
MbVec3<_T>::normalize()
{
  _T len = length();

  if (len != 0)
    (*this) /= len;
  else
    setValue(0,0,0);
  return len;
}

/**
* Vector of 3 float coordinates.
* @ingroup MeshIViz
* @see MbVec3
*/ 
typedef MbVec3<float> MbVec3f;
/**
* Vector of 3 double coordinates.
* @ingroup MeshIViz
* @see MbVec3
*/ 
typedef MbVec3<double> MbVec3d;

#ifdef _WIN32
#  pragma warning( pop )
#endif

#endif 








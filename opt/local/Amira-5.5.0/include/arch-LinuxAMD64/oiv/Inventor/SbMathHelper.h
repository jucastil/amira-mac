#ifndef SB_MATH_HELPER_H
#define SB_MATH_HELPER_H

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#include <Inventor/SbBase.h>
#include <float.h>
#include <math.h>

#ifdef __APPLE__
#  include <cmath>
#endif

namespace SbMathHelper
{
  /**
  * Maximum value returned by SbMathHelper::rand()
  */
  static const int OIV_RAND_MAX = 32767;
  /**
  * Default epsilon value for coincidence and interval checking 
  */
  static const float OIV_DEF_MATH_HELPER_EPS = 1.e-6f;

  /**
   * Return true if A and B are equal. @B numFloat@b is the number of allowed
   * representable IEEE float between A and B. For example, there is no
   * number between 10000 and 10000.000977. So if numFloat=1 it will return true
   * for these two numbers.
   */
  INVENTORBASE_API SbBool floatIsEqual(float A, float B, unsigned int numFloat);
  template <typename T> inline T Max(T a, T b) { return (a>b)?a:b; }
  template <typename T> inline T Min(T a, T b) { return (a<b)?a:b; }

  /** 
  * Clamps value to given range [minV, maxV]
  */
  template <typename T> inline T Clamp(T a, T minV, T maxV) { return Min(Max(minV, a), maxV); }

  /**
   * Return an integer multiple of 2^shift greater or equals to n
   */
  template <typename T> inline T alignToNextPowerOf2(T n, size_t shift)
  {
    if ( n &  ((T(1)<<shift)-1) )
      n = (n + (T(1)<<shift)) & ~((T(1)<<shift)-1);
    return n;
  }

  /**
   * Return the next power of 2 greater or equal to a
   */
  template <typename T> inline T getNextPow2(T a)
  {
    T pow = 1;
    while ( pow < a )
      pow *= 2;
    return pow;
  }

  /**
   * Convert degrees to radians
   */
  inline float deg2Rad(float a)
  {
    return (a*float(M_PI))/180.f;
  }

  /**
   * Convert radians to degrees
   */
  inline float rad2Deg(float a)
  {
    return (a*180.f)/float(M_PI);
  }

  /**
   * Returns true if the specified value is NaN.
   */
  INVENTORBASE_API inline bool isNaN(double a)
  {
#ifdef _WIN32
    return _isnan(a) != 0;
#elif defined(__APPLE__)
	return std::isnan(a);
#else
    return isnan(a);
#endif
  }

  /**
   * Returns a pseudo-random integer between 0 and OIV_RAND_MAX.
   * The returned sequence will be the same on all machines.
   */
  INVENTORBASE_API int rand();

  /**
   * Set seed for a new sequence of pseudo-random integers to be returned by rand()
   */
  INVENTORBASE_API void srand(unsigned seed);

  /** 
  * Coincidence test using given tolerance
  */
  template<typename T>
  inline bool isCoinc( T x, T y, T tol = (T)OIV_DEF_MATH_HELPER_EPS )
  {
    return ( fabs( x - y ) <= tol );
  }

  /** 
  * Less than test (x < y) using given tolerance
  */
  template<typename T>
  inline bool isLessThan( T x, T y, T tol = (T)OIV_DEF_MATH_HELPER_EPS )
  {
    return ( x < y ) && !isCoinc( x, y, tol );
  }

  /** 
  * Greater than test (x > y) using given tolerance
  */
  template<typename T>
  inline bool isGreaterThan( T x, T y, T tol = (T)OIV_DEF_MATH_HELPER_EPS )
  {
    return ( x > y ) && !isCoinc( x, y, tol );
  }

  /**  
  * Less or equal than test (x <= y) using given tolerance
  */
  template<typename T>
  inline bool isLessOrEqualThan( T x, T y, T tol = (T)OIV_DEF_MATH_HELPER_EPS )
  {
    return ( x < y ) || isCoinc( x, y, tol );
  }

  /**  
  * Greater or equal than test (x >= y) using given tolerance
  */
  template<typename T>
  inline bool isGreaterOrEqualThan( T x, T y, T tol = (T)OIV_DEF_MATH_HELPER_EPS )
  {
    return ( x > y ) || isCoinc( x, y, tol );
  }

  /** 
  * Inside closed interval (including endpoints) using given tolerance test
  */
  template<typename T>
  inline bool checkRangeI( T x, T min, T max, T tol = (T)OIV_DEF_MATH_HELPER_EPS )
  {
    return ( isLessOrEqualThan( x, max, tol ) &&
             isGreaterOrEqualThan( x, min, tol ) );
  }

  /** 
  * Inside open interval (excluding endpoints) using given tolerance test
  */
  template<typename T>
  inline bool checkRangeE( T x, T min, T max, T tol = (T)OIV_DEF_MATH_HELPER_EPS )
  {
    return ( isLessThan( x, max, tol ) &&
             isGreaterThan( x, min, tol ) ) ;
  }

}

#endif

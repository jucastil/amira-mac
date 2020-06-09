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
#ifndef MCMATH_H
#define MCMATH_H

#define MC_MIN2(a,b)     ((b)<(a)?(b):(a))
#define MC_MIN3(a,b,c)   (MC_MIN2(MC_MIN2(a,b),c))
#define MC_MIN4(a,b,c,d) (MC_MIN2(MC_MIN3(a,b,c),d))

#define MC_MAX2(a,b)     ((b)>(a)?(b):(a))
#define MC_MAX3(a,b,c)   (MC_MAX2(MC_MAX2(a,b),c))
#define MC_MAX4(a,b,c,d) (MC_MAX2(MC_MAX3(a,b,c),d))

#define MC_CLAMP(x,min,max)      (MC_MIN2(MC_MAX2(min,x),max))
#define MC_CLAMP_SAFE(x,min,max) ((max)>(min)?MC_CLAMP(x,min,max):MC_CLAMP(x,max,min))

#define MC_IN_RANGE(x,min,max) ((x)>=(min)&&(x)<=(max))

#define MC_ARRAY_LENGTH(x) (sizeof(x)/sizeof(*x))

#include "McPrimType.h"
#include "McStdlib.h"

#ifdef _MSC_VER
    #include <intrin.h>
    #ifdef EXPLICIT
        #undef EXPLICIT
    #endif
    
    #pragma intrinsic(_BitScanForward)
    #pragma intrinsic(_BitScanReverse)
#else
    #ifdef __SSE2__
        #include <emmintrin.h> // SSE2 intrinsics
    #endif
    #ifdef __SSE__
        #include <xmmintrin.h> // SSE intrinsics
    #endif
#endif

#include <limits>

#ifdef HX_OS_WIN
    // Make defines like M_PI etc. available.
    #define _USE_MATH_DEFINES
#endif
#include <math.h>

#ifndef HX_OS_WIN
    #include <limits.h>
#endif

// Clamps \a a of type \c A to the numeric range of type \c B if \a a is
// out of the numeric range of \c B, or casts \a a to type \c B if \a a 
// is within the numeric range of \c B.
template<typename A,typename B>
void McClampCastToType(A const& a,B& b) {
    B const& min_value=(std::numeric_limits<B>::is_integer)
                      ?(std::numeric_limits<B>::min()):(-std::numeric_limits<B>::max());
    B const& max_value=std::numeric_limits<B>::max();

    if (a<min_value) {
        b=min_value;
    }
    else if (a>max_value) {
        b=max_value;
    }
    else {
        b=static_cast<B>(a);
    }
}

// Exchange values stored at A and B
template<typename T>
inline void McSwap(T & A, T & B)
{
    T Tmp = A; A = B; B = Tmp;
}

// Converts degrees to radians.
template<typename T>
inline T McDegToRad(T angle) {
    static T const PI=static_cast<T>(M_PI);
    return (angle*PI)/180;
}

// Converts radians to degrees.
template<typename T>
inline T McRadToDeg(T angle) {
    static T const PI=static_cast<T>(M_PI);
    return (angle*180)/PI;
}

/**
    Compares two floating point numbers for equality w.r.t. to a
    tolerance relative to max(@c a,@c b).  If @c a and @c b are both
    NaN, the numbers are considered equal.
*/
inline bool McEqualsRelative(float a, float b, float tolerance=1e-6)
{
    // Special handling, because (NaN == NaN) yields false
    if (MC_isnan(a) && MC_isnan(b))
        return true;

    // Exact equivalence also covers (+Infinity == +Infinity) and
    // (-Infinity == -Infinity)
    if (a==b) return true;

    // Every other number compared to Infinity is not equal
    if (MC_isinf(a) || MC_isinf(b))
        return false;

    return fabs(a-b) <= tolerance*MC_MAX2(fabs(a),fabs(b));
}

// Returns true if the integer is an exact power of two.
inline bool McIsPowerOf2(mculong x) {
    if (x==0)
        return false;
    return (x&(x-1))==0;
}

// Returns the number of bits set in an integer.
inline mcuint32 McBitCount(mcuint32 x) {
    x = ((x & 0xaaaaaaaa) >>  1) + (x & 0x55555555);
    x = ((x & 0xcccccccc) >>  2) + (x & 0x33333333);
    x = ((x & 0xf0f0f0f0) >>  4) + (x & 0x0f0f0f0f);
    x = ((x & 0xff00ff00) >>  8) + (x & 0x00ff00ff);
    x = ((x & 0xffff0000) >> 16) + (x & 0x0000ffff);
    return x;
}

// Returns the number of bits set in an 64bit integer
inline mcuint32 McBitCount(mcuint64 x) {
    x = (x & 0x5555555555555555ULL) + (x>>1 & 0x5555555555555555ULL);
    x = (x & 0x3333333333333333ULL) + (x>>2 & 0x3333333333333333ULL);
    x = (x & 0x0F0F0F0F0F0F0F0FULL) + (x>>4 & 0x0F0F0F0F0F0F0F0FULL);
    return mcuint32((x * 0x0101010101010101ULL) >> 56);
}

// Returns the position of the least significant bit set in an integer.
inline mcint32 McGetLSBSet(mcuint32 x) {
#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
    unsigned long index;
    if (_BitScanForward(&index,x)) {
        return static_cast<mcint32>(index);
    }
    return -1;
#elif defined(__GNUC__) && (defined(__i386__) || defined(__amd64__) || defined(__x86_64__))
    if (x==0) {
        return -1;
    }

    return __builtin_ctz(x);
#else
    if (x==0) {
        return -1;
    }

    mcint32 index=0;
    while ((x&1)==0) {
        ++index;
        x>>=1UL;
    }
    return index;
#endif
}

// Returns the position of the most significant bit set in an integer.
inline mcint32 McGetMSBSet(mcuint32 x) {
    mcuint32 const MSB=sizeof(x)*8-1;

#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
    unsigned long index;
    if (_BitScanReverse(&index,x)) {
        return static_cast<mcint32>(index);
    }
    return -1;
#elif defined(__GNUC__) && (defined(__i386__) || defined(__amd64__) || defined(__x86_64__))
    if (x==0) {
        return -1;
    }

    return static_cast<mcint32>(MSB)-__builtin_clz(x);
#else
    if (x==0) {
        return -1;
    }

    mcint32 index=static_cast<mcint32>(MSB);
    mcuint32 mask=1UL<<MSB;
    while ((x&mask)==0) {
        --index;
        x<<=1UL;
    }
    return index;
#endif
}

// Returns the largest power of 2 that is smaller than or equal to x, except
// for x=0 which returns 0.
inline mcuint32 McFloorPow2(mcuint32 x) {
    mcint32 i=McGetMSBSet(x);
    if (i<0)
        return 0;
    return mcuint32(1)<<mcuint32(i);
}

// Returns the smallest power of 2 that is greater than or equal to x,
// except for x=0 and x>2147483648 which returns 0.
inline mcuint32 McCeilPow2(mcuint32 x) {
    if (x==0)
        return 0;
    mcint32 i=McGetMSBSet(x-1)+1;
    return mcuint32(1)<<mcuint32(i);
}

// Round a float to the nearest integer (to the even one in case of ambiguity).
inline mcint64 McRoundEven(float f) {
#if defined(_MSC_VER) || defined(__SSE__)
    // Use SSE intrinsics rather than FPU assembly here for speed & portability.
  #ifdef AMIRA64
    return _mm_cvtss_si64x(_mm_load_ss(&f));
  #else
    return static_cast<mcint64>(_mm_cvtss_si32(_mm_load_ss(&f)));
  #endif
#else
    mcint64 result;
    if (f>=0) {
        result=static_cast<mcint64>(f+0.5f);
        if ((result&1==1) && (result-f==0.5f)) {
            --result;
        }
    }
    else {
        result=static_cast<mcint64>(f-0.5f);
        if ((result&1==1) && (f-result==0.5f)) {
            ++result;
        }
    }
    return result;
#endif
}

// Round a double to the nearest integer (to the even one in case of ambiguity).
inline mcint64 McRoundEven(double d) {
#if defined(_MSC_VER) || defined(__SSE2__)
    // Use SSE2 intrinsics rather than FPU assembly here for speed & portability.
  #ifdef AMIRA64
    return _mm_cvtsd_si64x(_mm_load_sd(&d));
  #else
    return static_cast<mcint64>(_mm_cvtsd_si32(_mm_load_sd(&d)));
  #endif
#else
    mcint64 result;
    if (d>=0) {
        result=static_cast<mcint64>(d+0.5);
        if ((result&1==1) && (result-d==0.5)) {
            --result;
        }
    }
    else {
        result=static_cast<mcint64>(d-0.5);
        if ((result&1==1) && (d-result==0.5)) {
            ++result;
        }
    }
    return result;
#endif
}

// Round a float by choosing the nearest integer towards zero.
inline mcint64 McTruncZero(float f) {
#if defined(_MSC_VER) || defined(__SSE__)
    // Use SSE intrinsics rather than FPU assembly here for speed & portability.
  #ifdef AMIRA64
    return _mm_cvttss_si64x(_mm_load_ss(&f));
  #else
    return static_cast<mcint64>(_mm_cvttss_si32(_mm_load_ss(&f)));
  #endif
#else
    return static_cast<mcint64>(f);
#endif
}

// Round a double by choosing the nearest integer towards zero.
inline mcint64 McTruncZero(double d) {
#if defined(_MSC_VER) || defined(__SSE2__)
    // Use SSE2 intrinsics rather than FPU assembly here for speed & portability.
  #ifdef AMIRA64
    return _mm_cvttsd_si64x(_mm_load_sd(&d));
  #else
    return static_cast<mcint64>(_mm_cvttsd_si32(_mm_load_sd(&d)));
  #endif
#else
    return static_cast<mcint64>(d);
#endif
}

// Returns n factorial (n!). The result type is double because integer types,
// e.g. mculong, will quickly overflow even for moderate values of n.
inline double McFactorial(mculong n) {
    double total=1.0;
    while (n>0) {
        total*=n;
        --n;
    }
    return total;
}

// Returns the cube root of value a.
inline double McCbrt(double a) {
#ifdef HX_OS_WIN // function cbrt is not defined on Windows 
    if ( a >= 0.0 )
        return pow(a, 1.0/3.0);
    else 
        return - pow(fabs(a), 1.0/3.0);
#else
    return cbrt(a);
#endif
}

// Returns the cube root of value a.
inline float McCbrt(float a) {
#ifdef HX_OS_WIN // function cbrt is not defined on Windows 
    if ( a >= 0.0 )
        return pow((double)a, 1.0/3.0);
    else 
        return - pow(fabs((double)a), 1.0/3.0);
#else
    return cbrt(a);
#endif
}

#endif // MCMATH_H

/// @}

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
#ifndef MC_STDLIB_H
#define MC_STDLIB_H

#include <float.h>

#include <mclib/McStdio.h>

#ifdef HX_HAS_STDIOSTREAM
    #define MC_ostream std::ostream
    #define MC_cerr std::cerr
    #define MC_endl std::endl
    #define MC_cout std::cout
#else
    #define MC_ostream ::ostream
    #define MC_cerr ::cerr
    #define MC_endl ::endl
    #define MC_cout ::cout
#endif

// for convenience use #include "McMalloc.h" to use MC_alloca
#if defined(_WIN32) || defined(_WIN64)
    #define MC_alloca _alloca
#else
    #define MC_alloca alloca
#endif

// Tests for Visual Studio .NET 2005 (and newer). Under this compiler several functions are deprecated.
#if defined(_WIN32) && defined(_MSC_VER) && _MSC_VER >= 1400
    #define MC_putenv _putenv
    #define MC_tempnam _tempnam
#else
    #define MC_putenv putenv
    #define MC_tempnam tempnam
#endif

#if HX_HAS_STDCOMPLEX
    #define MC_complex std::complex
    #define MC_conj std::conj
    #define MC_real std::real
    #define MC_imag std::imag
    #define MC_abs std::abs
    #define MC_exp std::exp
    #define MC_log std::log
#else
    #define MC_complex ::complex
    #define MC_conj ::conj
    #define MC_real ::real
    #define MC_imag ::imag
    #define MC_abs ::abs
    #define MC_exp ::exp
    #define MC_log ::log
#endif

#if HX_NO_MATHF
    #define MC_ffloor(a)   ((float) floor((float)(a)))
    #define MC_floorf(a)   ((float) floor((float)(a)))
    #define MC_fceil(a)    ((float) ceil((float)(a)))
    #define MC_ceilf(a)    ((float) ceil((float)(a)))
    #define MC_facos(a)    ((float) acos((float)(a)))
    #define MC_acosf(a)    ((float) acos((float)(a)))
    #define MC_fasin(a)    ((float) asin((float)(a)))
    #define MC_asinf(a)    ((float) asin((float)(a)))
    #define MC_fcos(a)     ((float) cos((float)(a)))
    #define MC_cosf(a)     ((float) cos((float)(a)))
    #define MC_fsin(a)     ((float) sin((float)(a)))
    #define MC_sinf(a)     ((float) sin((float)(a)))
// Tests for Visual Studio .NET 2005 (and newer). On this compiler hypot() is deprecated.
#if defined(_WIN32) && defined(_MSC_VER) && _MSC_VER >= 1400
    #define MC_fhypot(a,b) ((float)_hypot((float)(a), float(b)))
    #define MC_hypotf(a,b) ((float)_hypot((float)(a), float(b)))
    #define MC_hypot(a,b)  ((double)_hypot((double)(a), double(b)))
#else
    #define MC_fhypot(a,b) ((float)hypot((float)(a), float(b)))
    #define MC_hypotf(a,b) ((float)hypot((float)(a), float(b)))
    #define MC_hypot(a,b)  ((double)hypot((double)(a), double(b)))
#endif
    #define MC_fsqrt(a)    ((float)sqrt((float)(a)))
    #define MC_sqrtf(a)    ((float)sqrt((float)(a)))
    #define MC_fatan2(a,b) ((float)atan2((float)(a), (float)(b)))
    #define MC_atan2f(a,b) ((float)atan2((float)(a), (float)(b)))
    #define MC_fatan(a)    ((float)atan((float)(a)))
    #define MC_atanf(a)    ((float)atan((float)(a)))
    #define MC_fpow(a,b)   ((float)pow((float)(a), (float)(b)))
    #define MC_powf(a,b)   ((float)pow((float)(a), (float)(b)))
    #define MC_flog10(a)   ((float)log10((float)(a)))
    #define MC_log10f(a)   ((float)log10((float)(a)))
#else
    #define MC_ffloor ffloor
    #define MC_floorf floorf
    #define MC_fceil  fceil
    #define MC_ceilf  ceilf
    #define MC_facos  facos
    #define MC_acosf  acosf
    #define MC_fasin  fasin
    #define MC_asin   asinf
    #define MC_fcos   fcos
    #define MC_cosf   cosf
    #define MC_fhypot fhypot
    #define MC_hypotf hypotf
    #define MC_fsin   fsin
    #define MC_sinf   fsinf
    #define MC_fsqrt  fsqrt
    #define MC_sqrtf  sqrtf
    #define MC_fatan2 fatan2
    #define MC_atan2f atan2f
    #define MC_fatan  fatan
    #define MC_atanf  atanf
    #define MC_fpow   fpow
    #define MC_powf   powf
    #define MC_flog10 flog10
    #define MC_log10f log10f
#endif

#ifdef HX_OS_WIN
    #define MC_isnan(x) _isnan(x)
    #define MC_isfinite(x) _finite(x)
    #define MC_isinf(x) (!_finite(x) && !_isnan(x))
#elif defined(HX_OS_HPUX)
    #define MC_isnan(x) isnan(x)
    #define MC_isfinite(x) isfinite(x)
    #define MC_isinf(x) isinf(x)
#elif defined(HX_OS_LINUX)
    #define MC_isnan(x) isnan(x)
    #define MC_isfinite(x) finite(x)
    #define MC_isinf(x) isinf(x)
#elif defined(HX_OS_AIX)
    #define MC_isnan(x) isnan(x)
    #define MC_isfinite(x) finite(x)
    #define MC_isinf(x) isinf(x)
#elif defined(HX_OS_SUNOS)
    #include <ieeefp.h>
    #define MC_isnan(x) isnan(x)
    #define MC_isfinite(x) finite(x)
    #define MC_isinf(x) isinf(x)
#elif defined(HX_OS_IRIX)
    #include <ieeefp.h>
    #define MC_isnan(x) isnan(x)
    #define MC_isfinite(x) finite(x)
    #define MC_isinf(x) isinf(x)
#elif defined(HX_OS_MACX)
    #include <cmath>
inline long MC_isnan(double d) { return std::isnan(d); }
inline long MC_isnan(float d) { return std::isnan(d); }
inline long MC_isfinite(double d) { return std::isfinite(d); }
inline long MC_isfinite(float d) { return std::isfinite(d); }
inline long MC_isinf(double d) { return std::isinf(d); }
inline long MC_isinf(float d) { return std::isinf(d); }
#else
    // The whole mclib may be shipped with other Windows-only products.
    // As customers do not use our build system which defines HX_OS_*, 
    // we fall back to Windows if no OS has been defined so far. Later, 
    // this scheme should be replaced by some global configuration
    // header file which defines all HX_* at compile time.
    #if defined(_WIN32) || defined(_WIN64)
        #define HX_OS_WIN
    #else
        #error "Architecture not properly configured !"
    #endif
#endif

#if !defined(M_PI) && !defined(_USE_MATH_DEFINES)
    #define _USE_MATH_DEFINES
#endif
#include <math.h>
#undef _USE_MATH_DEFINES

/// Indicates to the compiler that the parameter with the specified name is not used in the body of a function.
/// This can be used to suppress compiler warnings.
#ifndef MC_UNREFERENCED_PARAMETER
    #define MC_UNREFERENCED_PARAMETER(p) (void)p
#endif

#endif // MC_STDLIB_H

/// @}

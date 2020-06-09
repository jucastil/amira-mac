/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
/*
 * Module: inttypes.h
 */

#ifndef __oiv_inttypes_h__
#define __oiv_inttypes_h__

#ifdef _WIN32 /* Microsoft WINxx */
#  if !defined(_WIN32)
#    define WIN32
#  endif
#  ifdef _WIN64
#    ifndef _WIN64
#      define WIN64
#    endif
#  endif
#endif

#ifdef _WIN32 /* Microsoft WINxx */
typedef signed   __int8  int8_t;
typedef unsigned __int8  uint8_t;
typedef signed   __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef signed   __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef signed   __int64 int64_t;
typedef unsigned __int64 uint64_t;

#define SO_WCHAR_T unsigned short
# define INT64FMT "%I64d"

#elif defined(__NUTC__) /* NuTCRACKER */
typedef unsigned char uint8_t;
typedef unsigned long uint32_t;
typedef long int32_t;
#elif defined (__linux__) || defined(__APPLE__) /* Linux or Mac */
/*typedef unsigned int uint32_t; already defined in /usr/include/stdint.h */
#  include <stdint.h>
#elif defined(sun) /* SGI */
#  include <sys/types.h>
#elif defined(__sgi) /* SGI */
#  include <sys/types.h>
#elif defined(_AIX) /* IBM AIX */
#  include <sys/types.h>
#elif defined(__osf__) /* OSF1 5.x (Digital) */
#  include "/usr/include/inttypes.h"
#elif defined(__hpux) /* HPUX 11.x */
#  include <sys/unistd.h> /* for int32_t and uint32_t */
#elif defined(__OPENNT) /* Interix */
typedef unsigned char uint8_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
#endif

#ifndef _WIN32 /* UNIX */
#define SO_WCHAR_T wchar_t

#if defined(__GNUC__) && defined(__LP64__) && (__LP64__ == 1)
# define INT64FMT "%ld"
#else
# define INT64FMT "%lld"
#endif
#endif

#if defined(_WIN64) || _MSC_VER >= 1300
/* nothing */
#elif defined(__NUTC__) /* MKS Toolkit 8.5 (NutCracker) */
#include <nutc/pragma.h>
#include <nutc/intptr_t.h>
#elif defined(_WIN32) && !defined(_WIN64) && _MSC_VER < 1300 /* Visual C++ 6.0 */
typedef unsigned uintptr_t;
typedef unsigned long DWORD_PTR;
typedef signed int intptr_t;
#elif defined(sun) && (MIPS_SZPTR <= 32) /* SOLARIS 32 */
/* nothing */
#elif (defined(__sgi) && (_MIPS_SZPTR == 64))/*SGI64*/ || (MIPS_SZPTR == 64) || defined(__sparcv9)/*sun64*/ || defined(__osf__)
typedef unsigned long uintptr_t;
typedef unsigned long DWORD_PTR;
#elif defined(__linux__) || defined(__hpux) || (defined(_ABIO32) && (_MIPS_SIM==_ABIO32)) || defined(_AIX)
/* Linux || HPUX 11.x || SGI O32 || AIX 32 */
typedef unsigned long DWORD_PTR;
#else
typedef unsigned long uintptr_t;
typedef unsigned long DWORD_PTR;
typedef signed long int intptr_t;
#endif

#if defined(_WIN32) && !defined(_WIN64) && _MSC_VER < 1300
#  ifndef SetWindowLongPtr
#    define SetWindowLongPtr SetWindowLong
#  endif
#  ifndef GetWindowLongPtr
#    define GetWindowLongPtr GetWindowLong
#  endif
#  ifndef LONG_PTR
#    define LONG_PTR LONG
#  endif
#  ifndef GWLP_HINSTANCE
#    define GWLP_HINSTANCE GWL_HINSTANCE
#  endif
#  ifndef GWLP_WNDPROC
#    define GWLP_WNDPROC GWL_WNDPROC
#  endif
#  ifndef GWLP_USERDATA
#    define GWLP_USERDATA GWL_USERDATA
#  endif
#  ifndef DWLP_USER
#    define DWLP_USER DWL_USER
#  endif
#endif

#endif /* __oiv_inttypes_h__ */


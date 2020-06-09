/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_BASE_
#define _SB_BASE_

#ifndef HIDDEN_FROM_DOC

#if defined(_WIN32)
#pragma warning(disable:4251)
#endif

#include <SoVersion.h>

#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>

#if defined(__sgi)
#  include <sgidefs.h>
#endif

#include <stdio.h>

#include <Inventor/non_winsys.h>

#if defined(_AIX)
#  include <sys/select.h>
#endif

#endif //HIDDEN_FROM_DOC

#ifndef FALSE
/** Possible value of SbBool */
#  define FALSE 0
/** Possible value of SbBool */
#  define TRUE 1
#endif

/**
 * Boolean type.
 *
 * This typedef is used to represent the Boolean values #TRUE and #FALSE. SbBool is
 * not a class and does not have any methods or variables.
 * @ingroup Basics
 */
typedef int SbBool;

typedef void *SbHandle;

#ifndef HIDDEN_FROM_DOC
#define _SBHANDLE_ 1

#include <Inventor/sys/port.h>

#ifdef _WIN32
typedef unsigned int SbThreadId_t;
#else
#include <pthread.h>                //for defn of pthread_t
typedef pthread_t SbThreadId_t;
#endif

/**
* This symbol is used in Open Inventor header files to distinguish
* between varying levels of use of classes and members.
*
*      "SoEXTENDER class" indicates a class that is used only by
*              people extending the set of Open Inventor classes.
*      "SoEXTENDER public:" members are used when extending Inventor.
*      "protected:" members are for people extending Inventor
*              classes. (The "SoEXTENDER" is implied.)
*/
#define SoEXTENDER

/**
* This symbol is used in Open Inventor header files to distinguish
* between varying levels of use of classes and members.
*
*      "SoEXTENDER class" indicates a class that is used only by
*              people extending the set of Open Inventor classes.
*      "SoEXTENDER public:" members are used when extending Inventor.
*      "protected:" members are for people extending Inventor
*              classes. (The "SoEXTENDER" is implied.)
*/
#define SoEXTENDER_Documented

/**
* This symbol is used in Open Inventor header files to distinguish
* between varying levels of use of classes and members.
*
*      "SoINTERNAL class" means that the class is used only by VSG developers.
*
*      "SoINTERNAL public:" members are for VSG Inventor developers only.
*
*      "SoINTERNAL protected:" members are for VSG use only.
*/
#define SoINTERNAL

/**
 * This uses the preprocessor to quote a string
 */
#if defined(__STDC__) || defined(__ANSI_CPP__) || defined(__hpux) || defined(__osf__) || defined(_WIN32)
/* ANSI C */
#  define SO__QUOTE(str)        #str
#else
/* Non-ANSI C */
#  define SO__QUOTE(str)        "str"
#endif

/**
 * This uses the preprocessor to concatenate two strings
 */
#if defined(__STDC__) || defined(__ANSI_CPP__) || defined (__hpux) || defined(__osf__) || defined(_WIN32)
/* ANSI C */
#   define SO__CONCAT(str1, str2)       str1##str2
#else
/* Non-ANSI C */
#   define SO__CONCAT(str1, str2)       str1/**/str2
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Map the single-precision math functions to the regular ones on
// machines that don't support them.
//
/////////////////////////////////////////////////////////////////////////////
#if (defined(__sgi) && (_MIPS_SZPTR == 64)) || \
    (MIPS_SZPTR == 64) || \
    defined(__osf__) || \
    defined(__sparcv9) || \
    (defined(__hpux) && defined(__LP64__)) || \
    defined(__x86_64__)
#  define OIV_PTR_SIZE 64
#  define OIV_LONG_SIZE 64
#else
#  define OIV_PTR_SIZE 32
#  define OIV_LONG_SIZE 32
#endif

#if  defined(_WIN32) && (_MSC_VER >= 1300)
# define SoDEPRECATED __declspec(deprecated)
#elif defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ >= 3) && (__GNUC_MINOR__ >= 4)))
# define SoDEPRECATED __attribute__ ((deprecated))
#else
# define SoDEPRECATED
#endif

#if defined(_WIN32) && (_MSC_VER >=1300)

// We define SoNONUNICODE only in the internal build
#ifdef OIV_UNICODE_CHECK
# define SoNONUNICODE \
   __declspec(deprecated( "!!! This function is not unicode! IT SHOULD NOT BE USED !!!" ) )
#else
# define SoNONUNICODE
#endif // OIV_UNICODE_CHECK

#else // defined(_WIN32) && (_MSC_VER >=1300)

# define SoNONUNICODE

#endif // defined(_WIN32) && (_MSC_VER >=1300)

#if (defined(__GNUC__) && (__GNUC__ >= 4))
#define SoPRINTFPREFIX(stringIndex, firstToCheck) __attribute__((format(printf, stringIndex, firstToCheck)))
#define SoPRINTF  __attribute__((format(printf, 1, 2)))
#else
#define SoPRINTFPREFIX(stringIndex, firstToCheck)
#define SoPRINTF
#endif


#if  (defined(_WIN32) && (_MSC_VER < 1400)) || defined (__sgi)
// no VA_ARGS support in macro
#ifdef DEBUG_PRINTF
static inline void SODEBUGPRINTF(const char *format, ...){
  va_list ap;
  va_start(ap, format);
  vfprintf(stderr,format,ap);
  va_end(ap);
}
#else
static inline void SODEBUGPRINTF(...) {}
#endif

#else
// support VA_ARGS in macro

#ifdef DEBUG_PRINTF
#define SODEBUGPRINTF(format, ...) fprintf (stderr, format, __VA_ARGS__)
#else
#ifdef _WIN32
#pragma managed(push, off)
#endif
inline static void SODEBUGPRINTF(const char *, ...) {}
#ifdef _WIN32
#pragma managed(pop)
#endif
#endif

#endif // VA_ARGS support

#ifdef _WIN32

#if !defined(InventorBase_EXPORTS)
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__INVENTORBASELIB)
#endif
#endif

#endif // _WIN32

#endif //HIDDEN_FROM_DOC

#endif // _SB_BASE_

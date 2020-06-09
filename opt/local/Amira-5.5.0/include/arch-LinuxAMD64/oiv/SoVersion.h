/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _INVENTOR_VERSION_H_
#define _INVENTOR_VERSION_H_

#ifndef HIDDEN_FROM_DOC

/**
 * These symbols can be used to determine what version of Inventor
 * your application is compiling against.  These symbols were first
 * added with Inventor 7.1.0 (SO_VERSION==7, SO_VERSION_REVISION==1);
 * they were undefined in previous revisions of Inventor. The new
 * one is SO_INVENTOR_VERSION which is the total including the internal
 * sub_version.
 */

/* 8.6.3 */
#define SO_VERSION                      8
#define SO_VERSION_REVISION             6
#define SO_VERSION_PATCH                3
#define SO_VERSION_BUILD                0
#define SO_INVENTOR_VERSION             8630
#define TGS_VERSION                     SO_INVENTOR_VERSION

/* 8.6.3.0 */
#define SO_VERSION_STRING               "8"
#define SO_VERSION_REVISION_STRING      "6"
#define SO_PATCH_STRING                 "3"
#define SO_BUILD_STRING                 "0"

/* "8.6" */
#define SO_COMPACT_VERSION_DOTTED_STRING SO_VERSION_STRING"."SO_VERSION_REVISION_STRING
/* "8.6.3.0" */
#define SO_FULL_VERSION_DOTTED_STRING    SO_COMPACT_VERSION_DOTTED_STRING"."SO_PATCH_STRING"."SO_BUILD_STRING

/* "86" */
#define SO_COMPACT_VERSION_STRING        SO_VERSION_STRING""SO_VERSION_REVISION_STRING
/* "8630" */
#define SO_FULL_VERSION_STRING           SO_COMPACT_VERSION_STRING""SO_PATCH_STRING""SO_BUILD_STRING

/* used in licensing : "8.6" */
#define SO_PRODUCT_VERSION_FOR_LICENSING SO_VERSION_STRING"."SO_VERSION_REVISION_STRING

/* used in resources file */
#define SO_COMPANY_NAME     "Visualization Sciences Group"
#define SO_LEGAL_COPYRIGHT  "© 1996-2012 VSG"
#define SO_PRODUCT_VERSION  "8.6.3.0"
#define SO_FILE_VERSION     "8630"

/* RemoteViz version: 2.0 */
#define SO_REMOTE_VERSION                   2
#define SO_REMOTE_VERSION_REVISION          0
#define SO_REMOTE_VERSION_PATCH             0
#define SO_REMOTE_VERSION_STRING            "2"
#define SO_REMOTE_VERSION_REVISION_STRING   "0"
#define SO_REMOTE_PATCH_STRING              "0"
#define SO_REMOTE_VERSION_FOR_LICENSING SO_REMOTE_VERSION_STRING"."SO_REMOTE_VERSION_REVISION_STRING

#if defined(_DEBUG)
#define SO_FILE_VERSION_TAG     "D"
#else
#define SO_FILE_VERSION_TAG     ""
#endif

/* Used for internal string version notice (subject to changes)*/
#if defined(_WIN64) || defined(WIN64)
#define SO_PRODUCT_STRING_PLATFORM "64 bits"
#elif defined(_WIN32) || defined(WIN32)
#define SO_PRODUCT_STRING_PLATFORM "32 bits"
#elif defined(__hpux)
#if (__cplusplus >= 199707L)
#define SO_PRODUCT_STRING_PLATFORM "HP aCC"
#else
#define SO_PRODUCT_STRING_PLATFORM "HP C++"
#endif
#elif defined(__osf__)
#define SO_PRODUCT_STRING_PLATFORM "DIGITAL"
#elif defined(sun)
#define SO_PRODUCT_STRING_PLATFORM "SUN"
#elif defined(_AIX)
#define SO_PRODUCT_STRING_PLATFORM "IBM"
#elif defined(__linux__)
#define SO_PRODUCT_STRING_PLATFORM "LINUX"
#elif defined(__OPENNT)
#define SO_PRODUCT_STRING_PLATFORM "Interix"
#elif defined(__NUTC__)
#define SO_PRODUCT_STRING_PLATFORM "NuTCRACKER"
#elif defined(__sgi)
#define SO_PRODUCT_STRING_PLATFORM "SGI"
#else
#define SO_PRODUCT_STRING_PLATFORM ""
#endif

#endif /* HIDDEN_FROM_DOC */

#endif /* _INVENTOR_VERSION_H_ */


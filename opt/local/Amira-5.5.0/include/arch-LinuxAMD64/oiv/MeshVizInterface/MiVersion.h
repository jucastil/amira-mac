/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _MIVERSION_H_
#define _MIVERSION_H_

#include <SoVersion.h>


#define MI_VERSION                      SO_VERSION
#define MI_VERSION_REVISION             SO_VERSION_REVISION
#define MI_VERSION_PATCH                SO_VERSION_PATCH
#define MI_MESHIVIZ_VERSION             SO_INVENTOR_VERSION


#define MI_VERSION_STRING               SO_VERSION_STRING
#define MI_VERSION_REVISION_STRING      SO_VERSION_REVISION_STRING
#define MI_PATCH_STRING                 SO_PATCH_STRING


#define MI_COMPACT_VERSION_DOTTED_STRING SO_COMPACT_VERSION_DOTTED_STRING

#define MI_FULL_VERSION_DOTTED_STRING    SO_FULL_VERSION_DOTTED_STRING


#define MI_COMPACT_VERSION_STRING        SO_COMPACT_VERSION_STRING

#define MI_FULL_VERSION_STRING           SO_FULL_VERSION_STRING

#define MI_PRODUCT_VERSION_FOR_LICENSING SO_PRODUCT_VERSION_FOR_LICENSING


#define MI_COMPANY_NAME     SO_COMPANY_NAME
#define MI_LEGAL_COPYRIGHT  SO_LEGAL_COPYRIGHT
#define MI_PRODUCT_VERSION  SO_PRODUCT_VERSION
#define MI_FILE_VERSION     SO_FILE_VERSION

#if defined(_DEBUG)
#define MI_FILE_VERSION_TAG     SO_FILE_VERSION_TAG
#else
#define MI_FILE_VERSION_TAG     SO_FILE_VERSION_TAG
#endif

#endif /* _MIVERSION_H_ */

/*=========================================================================
                                                                                
  Program:   gdcm
  Module:    $RCSfile: gdcmConfigure.h.in,v $
  Language:  C++
  Date:      $Date: 2008-05-19 06:58:31 $
  Version:   $Revision: 1.14 $
                                                                                
  Copyright (c) CREATIS (Centre de Recherche et d'Applications en Traitement de
  l'Image). All rights reserved. See Doc/License.txt or
  http://www.creatis.insa-lyon.fr/Public/Gdcm/License.html for details.
                                                                                
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.
                                                                                
=========================================================================*/

#ifndef __gdcmConfigure_h
#define __gdcmConfigure_h

/* This header is configured by GDCM's build process.  */

/*--------------------------------------------------------------------------*/
/* Platform Features                                                        */

/* Byte order.  */
/* All compilers that support Mac OS X define either __BIG_ENDIAN__ or
   __LITTLE_ENDIAN__ to match the endianness of the architecture being
   compiled for. This is not necessarily the same as the architecture of
   the machine doing the building. In order to support Universal Binaries on
   Mac OS X, we prefer those defines to decide the endianness.
   On other platform, we use the result of the TRY_RUN. */
#if !defined(__APPLE__)
/* #undef GDCM_WORDS_BIGENDIAN */
#elif defined(__BIG_ENDIAN__)
  #define GDCM_WORDS_BIGENDIAN
#endif

/* Allow access to UINT32_MAX , cf gdcmCommon.h */
#define __STDC_LIMIT_MACROS

/* Hard code the path to the public dictionary */
#define PUB_DICT_PATH "install/share/gdcm/"

/* Hardcode the path to GDCM_DATA_ROOT */
#define GDCM_DATA_ROOT ""

/* Usefull in particular for loadshared where the full path
 * to the lib is needed */
#define GDCM_EXECUTABLE_OUTPUT_PATH "/home/indeed/itk/InsightToolkit-3.20.0/build/Debug/bin"
#define GDCM_LIBRARY_OUTPUT_PATH    "/home/indeed/itk/InsightToolkit-3.20.0/build/Debug/bin"

/* For older gcc / broken platform */
/* #undef GDCM_NO_ANSI_STRING_STREAM */

/* I guess something important */
#define CMAKE_HAVE_STDINT_H
#define CMAKE_HAVE_INTTYPES_H

/* This variable allows you to have helpful debug statement */
/* That are in between #ifdef / endif in the gdcm code */
/* That means if GDCM_DEBUG is OFF there shouldn't be any 'cout' at all ! */
/* only cerr, for instance 'invalid file' will be allowed */
/* #undef GDCM_DEBUG */

/* Whether we are building shared libraries.  */
/* This was important as long as GDCM is LGPL */
#define BUILD_SHARED_LIBS

/* GDCM uses __FUNCTION__ which is not ANSI C89, but is in ANSI C99 */
#define GDCM_COMPILER_HAS_FUNCTION

#define GDCM_SYSTEM_UUID_FOUND


/* GetMacAddress require a lot of include file to access low level API */
#define CMAKE_HAVE_UNISTD_H
#define CMAKE_HAVE_STDLIB_H
#define CMAKE_HAVE_SYS_IOCTL_H
#define CMAKE_HAVE_SYS_SOCKET_H
/* #undef CMAKE_HAVE_SYS_SOCKIO_H */
#define CMAKE_HAVE_NET_IF_H
#define CMAKE_HAVE_NETINET_IN_H
/* #undef CMAKE_HAVE_NET_IF_DL_H */
#define CMAKE_HAVE_NET_IF_ARP_H
/* #undef HAVE_SA_LEN */

/* #undef GDCM_FORCE_BIGENDIAN_EMULATION */

/* For OpenJPEG */
/* #undef OPJ_EXPORTS */
/* #undef OPJ_STATIC */

/*--------------------------------------------------------------------------*/
/* GDCM Versioning                                                          */

/* Version number.  */
#define GDCM_MAJOR_VERSION 1
#define GDCM_MINOR_VERSION 2
#define GDCM_BUILD_VERSION 4
#define GDCM_VERSION "1.2.4"

/*--------------------------------------------------------------------------*/
/* GDCM deprecation mechanism                                               */
/* #undef GDCM_LEGACY_REMOVE */
/* #undef GDCM_LEGACY_SILENT */


#endif

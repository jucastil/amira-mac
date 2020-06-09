/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkConfigure.h.in,v $
  Language:  C++
  Date:      $Date: 2010-01-13 14:19:07 $
  Version:   $Revision: 1.41 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

/* 
 * here is where system computed values get stored these values should only
 * change when the target compile platform changes 
 */

/* what byte order */
/* All compilers that support Mac OS X define either __BIG_ENDIAN__ or
   __LITTLE_ENDIAN__ to match the endianness of the architecture being
   compiled for. This is not necessarily the same as the architecture of
   the machine doing the building. In order to support Universal Binaries on
   Mac OS X, we prefer those defines to decide the endianness.
   On other platform, we use the result of the TRY_RUN. */
#if !defined(__APPLE__)
/* #undef CMAKE_WORDS_BIGENDIAN */
  #ifdef CMAKE_WORDS_BIGENDIAN
    #define ITK_WORDS_BIGENDIAN 
  #endif
#elif defined(__BIG_ENDIAN__)
  #define CMAKE_WORDS_BIGENDIAN
  #define ITK_WORDS_BIGENDIAN
#endif

/* what threading system are we using */
#define CMAKE_USE_PTHREADS
#ifdef CMAKE_USE_PTHREADS
#define ITK_USE_PTHREADS
#endif

/* #undef CMAKE_USE_SPROC */
#ifdef CMAKE_USE_SPROC
#define ITK_USE_SPROC
#endif

/* #undef CMAKE_HP_PTHREADS */
#ifdef CMAKE_HP_PTHREADS
#define ITK_HP_PTHREADS
#endif

/* #undef CMAKE_USE_WIN32_THREADS */
#ifdef CMAKE_USE_WIN32_THREADS
#define ITK_USE_WIN32_THREADS
#endif

#define ITK_BUILD_SHARED_LIBS
#ifdef ITK_BUILD_SHARED_LIBS
#define ITKDLL
#else
#define ITKSTATIC
#endif

/* #undef CMAKE_NO_STD_NAMESPACE */
/* #undef CMAKE_NO_ANSI_STREAM_HEADERS */
/* #undef CMAKE_NO_ANSI_STRING_STREAM */
/* #undef CMAKE_NO_ANSI_FOR_SCOPE */
#define ITK_CPP_FUNCTION
/* #undef ITK_LEGACY_REMOVE */
/* #undef ITK_LEGACY_SILENT */
#define ITK_USE_CONCEPT_CHECKING
/* #undef ITK_USE_STRICT_CONCEPT_CHECKING */
/* #undef ITK_EXPLICIT_INSTANTIATION */
/* #undef USE_FFTWF */
/* #undef USE_FFTWD */
/* #undef ITK_USE_MINC2 */
/* #undef ITK_USE_OPTIMIZED_REGISTRATION_METHODS */
/* #undef ITK_USE_REVIEW_STATISTICS */
/* #undef ITK_USE_CONSOLIDATED_MORPHOLOGY */
/* #undef ITK_USE_TRANSFORM_IO_FACTORIES */
#define ITK_USE_ORIENTED_IMAGE_DIRECTION
#define ITK_IMAGE_BEHAVES_AS_ORIENTED_IMAGE
#define ITK_USE_CENTERED_PIXEL_COORDINATES_CONSISTENTLY
#define ITK_USE_REGION_VALIDATION_IN_ITERATORS
#define ITK_USE_TEMPLATE_META_PROGRAMMING_LOOP_UNROLLING
/* #undef ITK_USE_DEPRECATED_LEVELSET_INTERPOLATION */
/* #undef ITK_USE_DEPRECATED_FAST_MARCHING */
#define ITK_USE_REVIEW
/* #undef ITK_SUPPORTS_TEMPLATED_FRIEND_FUNCTION_WITH_TEMPLATE_ARGUMENTS */
#define ITK_SUPPORTS_TEMPLATED_FRIEND_FUNCTION_WITH_EMPTY_BRACKETS
/* #undef ITK_SUPPORTS_TEMPLATED_FRIEND_FUNCTION_WITH_NULL_STRING */
/* #undef ITK_SUPPORTS_WCHAR_T_FILENAME_CSTYLEIO */
/* #undef ITK_SUPPORTS_WCHAR_T_FILENAME_IOSTREAMS_CONSTRUCTORS */
/* #undef ITK_SUPPORTS_FDSTREAM_HPP */

/* 
 * TODO: this should be changed to a compile time test for the needed
 * feature and then defined as a cmake variable
 */
#if !(defined( _MSC_VER ) && ( _MSC_VER < 1310 ))
#define ITK_USE_NUMERIC_TRAITS_PARTIAL_SPECIALIZATION
#endif

/*
 * The  gets replaced with "1" or "", this define is
 * to remap these values to 0 and 1
 */
#define ITK_CMAKEDEFINE_VAR_1 1
#define ITK_CMAKEDEFINE_VAR_ 0

/*
 * Check Include files defines. We use the CMake standard names in the
 * cmake files to reduce extra calls for checking header, but then
 * conditionally defined them here with an ITK_ prefix to prevent
 * collisions and re defined warnings.
 */
#if ITK_CMAKEDEFINE_VAR_1
# define ITK_HAVE_FENV_H
#endif /* HAVE_FENV_H */
#if ITK_CMAKEDEFINE_VAR_1
# define ITK_HAVE_SYS_TYPES_H
#endif  /* HAVE_SYS_TYPES_H */
#if ITK_CMAKEDEFINE_VAR_1
# define ITK_HAVE_STDINT_H
#endif  /* HAVE_STDINT_H */
#if ITK_CMAKEDEFINE_VAR_1
# define ITK_HAVE_STDDEF_H
#endif /* HAVE_STDDEF_H */
#if ITK_CMAKEDEFINE_VAR_1
# define ITK_HAVE_UNISTD_H
#endif /* HAVE_UNISTD_H */

#undef ITK_CMAKEDEFINE_VAR_1 
#undef ITK_CMAKEDEFINE_VAR_ 


/*
 * Enable ITK usage of and long long 
 */
#define ITK_TYPE_USE_LONG_LONG

#define ITK_VERSION_MAJOR 3
#define ITK_VERSION_MINOR 20
#define ITK_VERSION_PATCH 0
#define ITK_VERSION_STRING "3.20"


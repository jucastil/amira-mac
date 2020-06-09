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
#ifndef MC_PRIMTYPE_H
#define MC_PRIMTYPE_H

#include <sys/types.h>
#include "McWinDLLApi.h"

#ifdef __linux
#undef uint8_t
typedef unsigned char uint8_t;
#endif

/// Convenience definition to refer to \c mc_int8.
#define MC_INT8 McPrimType(McPrimType::mc_int8)
/// Convenience definition to refer to \c mc_uint8.
#define MC_UINT8 McPrimType(McPrimType::mc_uint8)
/// Convenience definition to refer to \c mc_int16.
#define MC_INT16 McPrimType(McPrimType::mc_int16)
/// Convenience definition to refer to \c mc_uint16.
#define MC_UINT16 McPrimType(McPrimType::mc_uint16)
/// Convenience definition to refer to \c mc_int32.
#define MC_INT32 McPrimType(McPrimType::mc_int32)
/// Convenience definition to refer to \c mc_int64.
#define MC_INT64 McPrimType(McPrimType::mc_int64)
/// Convenience definition to refer to \c mc_uint32.
#define MC_UINT32 McPrimType(McPrimType::mc_uint32)
/// Convenience definition to refer to \c mc_float.
#define MC_FLOAT McPrimType(McPrimType::mc_float)
/// Convenience definition to refer to \c mc_double.
#define MC_DOUBLE McPrimType(McPrimType::mc_double)
/// Convenience definition to refer to \c mc_complex.
#define MC_COMPLEX McPrimType(McPrimType::mc_complex)
/// Convenience definition to refer to \c mc_string.
#define MC_STRING McPrimType(McPrimType::mc_string)

/** @file McPrimType.h
    @brief Contains typedefs for primitive data types.
  */

/// This class describes primitive data types.
class MCLIB_API McPrimType
{
  public:
    /// Enumeration type.
    enum Type {
        /// Unsigned char (1 byte)
        mc_uint8 = 0,
        /// Signed short (2 bytes)
        mc_int16,
        /// Signed integer (4 bytes)
        mc_int32,
        /// Single precision real number (4 bytes)
        mc_float,
        /// Double precision real number (8 bytes)
        mc_double,
        /// Complex number (2 floats, 8 bytes)
        mc_complex,
        // Generic pointer type (obsolete)
        mc_string,
        /// Unsigned integer (2 bytes)
        mc_uint16,
        /// Unsigned integer (4 bytes)
        mc_uint32,
        /// Unsigned char (1 byte)
        mc_int8,
        // Signed integer (8 bytes)
        mc_int64

    };

    /// Default constructor, sets the type to McPrimType::mc_uint8.
    McPrimType() {
        type = mc_uint8;
    }

    /// Sets the type to McPrimType::mc_int8.
    McPrimType(signed char*) {
        type = mc_int8;
    }

    /// Sets the type to McPrimType::mc_uint8.
    McPrimType(unsigned char*) {
        type = mc_uint8;
    }

    /// Sets the type to McPrimType::mc_int16.
    McPrimType(short*) {
        type = mc_int16;
    }

    /// Sets the type to McPrimType::mc_uint16.
    McPrimType(unsigned short*) {
        type = mc_uint16;
    }

    /// Sets the type to McPrimType::mc_int32.
    McPrimType(int*) {
        type = mc_int32;
    }

    /// Sets the type to McPrimType::mc_int32.
    McPrimType(unsigned int*) {
        type = mc_uint32;
    }

    /// Sets the type to McPrimType::mc_float.
    McPrimType(float*) {
        type = mc_float;
    }

    /// Sets the type to McPrimType::mc_double.
    McPrimType(double*) {
        type = mc_double;
    }

    /// Sets the type to McPrimType::mc_int64.
    McPrimType(long long*) {
        type = mc_int64;
    }

    /** Sets the type to McPrimType::mc_int8
    Note: The implementation of this primitive type
    may differs among compilers and according to compiler options
    between the types of unsigned char or signed char */

    McPrimType(char*) {
        type = mc_int8;
    }

    /// Constructor, sets type from an integer value.
    McPrimType(int enumtype) {
        type = enumtype;
    }

    /// Assignment operator.
    McPrimType& operator=(const McPrimType& other) {
        type = other.type;
        return *this;
    }

    /// This allows assignments like type=McPrimType::mc_uint8.
    int operator=(Type other) {
        type = other;
        return type;
    }

    /// This allows assignments from integer values.
    int operator=(int other) {
        type = other;
        return type;
    }

    /// This allows comparisons like primType==McPrimType::mc_uint8.
    int operator==(Type other) const {
        return type==other;
    }

    /// This allows comparisons with integer values.
    int operator==(int other) const {
        return type==other;
    }

    /// This allows comparisons like primType!=McPrimType::mc_uint8.
    int operator!=(Type other) const {
        return type!=other;
    }

    /// This allows comparisons with integer values.
    int operator!=(int other) const {
        return type!=other;
    }

    /// Cast to int.
    operator int() const {
        return type;
    }

    /// Returns the size of the primitive data type in bytes.
    int size() const {
        return primTypeSize[type];
    }

    /// Returns type as integer (useful in switch() statements).
    int getType() const {
        return type;
    }

    /// Returns the name of the primitive data type.
    const char* getName() const {
        return primTypeName[type];
    }

    /// Returns true if this is an integer type.
    bool isInteger () const {
        if (type == mc_int8  || type == mc_uint8 ||
            type == mc_int16 || type == mc_uint16 ||
            type == mc_int32 || type == mc_uint32 ||
            type == mc_int64) {
            return true;
        }
        return false;
    }

    /// Returns true if this is a floating point type.
    bool isFloat () const {
        if (type == mc_float || type == mc_double || type == mc_complex) {
            return true;
        }
        return false;
    }

    /** converts type name as returned by getName() into Type
        returns whether such a typename could be found */
    static bool nameToType(const char*, Type& t);

  protected:
      /// Contains the enumerated primitive data type casted to an integer.
      int type;
      /// Stores the sizes of the primitive data types in bytes.
      static const int primTypeSize[];
      /// Stores the names of the primitive data types as strings.
      static const char* primTypeName[];
};

#ifdef _WIN32 // This is also defined on Windows x64!
    typedef __int8                  mcint8;
    typedef unsigned __int8         mcuint8;
    typedef __int16                 mcint16;
    typedef unsigned __int16        mcuint16;
    typedef __int32                 mcint32;
    typedef unsigned __int32        mcuint32;
    typedef __int64                 mcint64;
    typedef unsigned __int64        mcuint64;
    #ifdef _WIN64
    typedef __int64                 mclong;
    typedef unsigned __int64        mculong;
    #else
    typedef long                    mclong;
    typedef unsigned long           mculong;
    #endif
#else
    typedef char                    mcint8;
    typedef unsigned char           mcuint8;
    typedef short                   mcint16;
    typedef unsigned short          mcuint16;
    typedef int                     mcint32;
    typedef unsigned int            mcuint32;
    typedef long long               mcint64;
    typedef unsigned long long      mcuint64;
    typedef long                    mclong;
    typedef unsigned long           mculong;
#endif

/** Checks if the integral data types have the expected sizes in bytes on this
    platform. */
inline int McPrimTypeSizedIntegersAreValid()
{
    return      sizeof(mcint8 )==1 && sizeof(mcuint8 )==1
            &&  sizeof(mcint16)==2 && sizeof(mcuint16)==2
            &&  sizeof(mcint32)==4 && sizeof(mcuint32)==4
            &&  sizeof(mcint64)==8 && sizeof(mcuint64)==8;
}

/** @name Typedefs for primitive data types
    In this file typedefs for certain primitive data types are provided.
    Perhaps the most important ones are mclong and mculong. These types
    are 32-bit on 32-bit systems and 64-bit on 64-bit systems. You should
    use mclong instead of int in any for-loop or in any index operator
    at places where the number of items to be processed might exceed the
    32-bit limit. */

//@{
/** \var typedef char mcint8;
    \brief 8-bit integer data type (on Windows __int8)
  */
/** \var typedef unsigned char mcuint8;
    \brief 8-bit unsigend integer data type (on Windows __uint8)
  */
/** \var typedef short mcint16;
    \brief 16-bit integer data type (on Windows __int16)
  */
/** \var typedef unsigned short mcuint16;
    \brief 16-bit unsigned integer data type (on Windows __uint16)
  */
/** \var typedef int mcint32;
    \brief 32-bit integer data type (on Windows __int32)
  */
/** \var typedef unsigned int mcuint32;
    \brief 32-bit unsigned integer data type (on Windows __uint32)
  */
/** \var typedef long long mcint64;
    \brief 64-bit integer data type (on Windows __int64)
  */
/** \var typedef unsigned long long mcuint64;
    \brief 64-bit unsigned integer data type (on Windows __uint64)
  */
/** \var typedef long mclong;
    \brief Unix-style long integer data type.

     mclong is 64-bit on 64-bit systems and 32-bit on 32-bit systems.
     It is exactly as large as a pointer. On 32-bit Windows this is also
     defined as long. On 64-bit Windows this is defined as __int64.
  */
/** \var typedef unsigned long mculong;
    \brief Unix-style unsigned long integer data type.

     mculong is 64-bit on 64-bit systems and 32-bit on 32-bit systems.
     It is exactly as large as a pointer. On 32-bit Windows this is also
     defined as unsigned long. On 64-bit Windows this is defined as __uint64.
  */
//@}

#endif

/// @}

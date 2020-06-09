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
#ifndef MC_DATA_TYPE_H
#define MC_DATA_TYPE_H

#include "McWinDLLApi.h"
#include "McAssert.h"
#include "McPrimType.h"

#include <string.h>

template <class A, class B> class McHashTable;

/** This namespace is used for all the constants
    which describe a datatype. In addition
    to the namespace the constants also start with mc_
    to avoid clashed with some common defines in C source, e.g. uint8
 */
namespace mcdatatypes {
    /// mimic the McPrimTypes
    //@{
    extern MCLIB_API const char* mc_int8;
    extern MCLIB_API const char* mc_uint8;
    extern MCLIB_API const char* mc_int16;
    extern MCLIB_API const char* mc_uint16;
    extern MCLIB_API const char* mc_int32;
    extern MCLIB_API const char* mc_uint32;
    extern MCLIB_API const char* mc_float;
    extern MCLIB_API const char* mc_double;
    //@}

    // a type for all unknown types
    extern MCLIB_API const char* mc_unknown;
}

/** \brief This is a lightweight class describing data types.
           Datatypes can be registered during run time.
           Compatibility with McPrimType is guaranteed.

    In prinziple, the class would be able to support non primary types.
    This feature is not currently not supported. It is most likely
    that it will not be supported in the future.

    What is a primary type?
        - A primary type is a type which is natively supported by a CPU.
        - A primary type can be converted from little to big endian,
            just by knowing its size in bytes (-> complex is not a primary type).
        - The size of the type defines how many bytes of memory must be copied
            to copy one instance of the type (-> const char* == string is not a
            primary type)

    I think McPrimType should be cleaned up (removing complex and string).
    Casting McPrimType to int must be avoided. McDataType and McPrimType
    would be essentially the same and should be merged.

    The case against non primary types:
        - vector and array types can be implemented using nDataVar
        - compound types built of different types (== structs) are
           very hard to handle. Padding might be needed to achieve alignment.
           We don't want to deal with this issue.
  */
class MCLIB_API McDataType {
    public:
        class PrimTypeDescription;

        /// Default constructor, sets the type to mcdatatype::mc_unknown.
        McDataType() {
            init (mcdatatypes::mc_unknown);
        }

        /** Type from name.
         */
        explicit McDataType(const char* name) {
            init (name);
        }

        /** copy from string */
        const McDataType& operator= (const char* other) {
            init (other);
            return *this;
        }


        /* Default copy and assignment is fine
         */
        // McDataType (const McDataType& other);
        // const McDataType& operator= (const McDataType&);

        /// Sets the type to mcdatatypes::mc_int8
        static McDataType ofPointer(char*) {
            return McDataType (mcdatatypes::mc_int8);
        }

        /// Sets the type to mcdatatypes::mc_int8
        static McDataType ofPointer(signed char*) {
            return McDataType (mcdatatypes::mc_int8);
        }

        /// Sets the type to mcdatatypes::mc_uint8.
        static McDataType ofPointer(unsigned char*) {
            return McDataType (mcdatatypes::mc_uint8);
        }

        /// Sets the type to mcdatatypes::mc_int16.
        static McDataType ofPointer(short*) {
            return McDataType (mcdatatypes::mc_int16);
        }

        /// Sets the type to mcdatatypes::mc_uint16.
        static McDataType ofPointer(unsigned short*) {
            return McDataType (mcdatatypes::mc_uint16);
        }

        /// Sets the type to McDataType::mc_int32.
        static McDataType ofPointer(int*) {
            return McDataType (mcdatatypes::mc_int32);
        }

        /// Sets the type to McDataType::mc_uint32.
        static McDataType ofPointer(unsigned int*) {
            return McDataType (mcdatatypes::mc_uint32);
        }

        /// Sets the type to mcdatatypes::mc_float.
        static McDataType ofPointer(float*) {
            return McDataType (mcdatatypes::mc_float);
        }

        /// Sets the type to mcdatatypes::mc_double.
        static McDataType ofPointer(double*) {
            return McDataType (mcdatatypes::mc_double);
        }

        /// Sets the type to mcdatatypes::mc_int8.
        static McDataType ofPointer(const char*) {
            return McDataType (mcdatatypes::mc_int8);
        }

        /// Sets the type to mcdatatypes::mc_int8.
        static McDataType ofPointer(const signed char*) {
            return McDataType (mcdatatypes::mc_int8);
        }

        /// Sets the type to mcdatatypes::mc_uint8.
        static McDataType ofPointer(const unsigned char*) {
            return McDataType (mcdatatypes::mc_uint8);
        }

        /// Sets the type to mcdatatypes::mc_int16.
        static McDataType ofPointer(const short*) {
            return McDataType (mcdatatypes::mc_int16);
        }

        /// Sets the type to mcdatatypes::mc_uint16.
        static McDataType ofPointer(const unsigned short*) {
            return McDataType (mcdatatypes::mc_uint16);
        }

        /// Sets the type to mcdatatypes::mc_int32.
        static McDataType ofPointer(const int*) {
            return McDataType (mcdatatypes::mc_int32);
        }

        /// Sets the type to mcdatatypes::mc_uint32.
        static McDataType ofPointer(const unsigned int*) {
            return McDataType (mcdatatypes::mc_int32);
        }

        /// Sets the type to mcdatatypes::mc_float.
        static McDataType ofPointer(const float*) {
            return McDataType (mcdatatypes::mc_float);
        }

        /// Sets the type to mcdatatypes::mc_double.
        static McDataType ofPointer(const double*) {
            return McDataType (mcdatatypes::mc_double);
        }


        /** check if the type name is known. */
        static bool isKnown (const char* name);

        McDataType(McPrimType ptype);

        ///
        bool operator==(const McDataType& other) const {
            return mName == other.mName || strcmp (mName, other.mName) == 0;
        }

        ///
        bool operator==(const char* other) const {
            return mName == other || strcmp (mName, other) == 0;
        }

        ///
        bool operator!=(const McDataType& other) const {
            return strcmp (mName, other.mName) != 0;
        }

        ///
        bool operator!=(const char* other) const {
            return strcmp (mName, other) != 0;
        }

        /** \brief [DEPRECATED] Returns the size of the data type in bytes.
                    Use memsize() as a more readable substitute.
          */
        int size() const {
            return memsize ();
        }

        /** Returns the size of the data type in bytes.
         *  A memsize of zero indicates an type of unknown size.
         */
        int memsize() const;

        /// Returns the name of the data type.
        const char* getName() const {
            return mName;
        }

        ///
        const char* fullName () const {
            return getName ();
        }

        /// Return the common name of the datatype.
        const char* getCommonName () const {
            mcenter ("McDataType::getCommonName");
            mcdebug (MCDL_CRIT, "TODO");
            return getName();
        }

        ///
        const char* commonName () const {
            mcenter ("McDataType::commonName");
            mcdebug (MCDL_CRIT, "TODO");
            return getCommonName ();
        }

        /// check if datatype is an old style McPrimType
        bool isMcPrimType() const;

        McPrimType asMcPrimType () const;

        /// Returns true if this is one of the basic integer types.
        bool isInteger () const {
            if (*this == mcdatatypes::mc_uint8
                || *this == mcdatatypes::mc_int8
                    || *this == mcdatatypes::mc_int16
                    || *this == mcdatatypes::mc_int32
                    || *this == mcdatatypes::mc_uint32
                    || *this == mcdatatypes::mc_uint16) {
                return true;
            }
            return false;
        }

        /// Returns true if this is one of the basic floating point types.
        bool isFloat () const {
            if (*this == mcdatatypes::mc_float
                    || *this == mcdatatypes::mc_double) {
                return true;
            }
            return false;
        }

        /// Returns true if the type is based on a single type.
        bool isBasedOn (const McDataType& ty) const;

        bool isBasedOn (const char* ty) const {
            return isBasedOn (McDataType (ty));
        }

        /** register a basic type

            @param name fully qualified name of type, e.g. http://amira.zib.de/types#mc_uint8
            @param memsize size in bytes
         */
        static void registerType (const char* name, int memsize);

    private:
        void init (const char* name);

        static McHashTable<const char*, McPrimType>& toMcPrimTypeMap ();
        static McHashTable<const char*, PrimTypeDescription*>& descriptionMap ();
        static McHashTable<const char*, const char*>& toPersistentMap ();

        const char* mName;
};

#endif

/// @}

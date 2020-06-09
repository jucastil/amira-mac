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
#ifndef MC_DATA_POINTER_H
#define MC_DATA_POINTER_H

#include "McWinDLLApi.h"
#include "McDataType.h"
#include "McMalloc.h"

/** A Pointer with additional type information.

    This class is used to pass void pointers together with additional information
    to allow type checking during runtime. Constructors and cast operators
    allow to work with instances similar to raw pointers.

    Additional information might be:
        - The data type of the memory
        - nDataVar of basic elements grouped together
        - The allowed access type (read only = A_CONST, read write = A_NONCONST)

    You can get access to the raw mem by using methods like uint8Ptr() or uint8constPtr().
    To allow casting in template methods cast operators are also provided. Handle
    them with greatest care to avoid segfaults.
        
    e.g. 
\code
    char c[100];
    // knows about the type (char)
    McDataPointer typed(c);
    char* c1 = typed.uint8Ptr();

    float v[100][3];
    // knows about the type (float) and the number of floats grouped together (3)
    McDataPointer typedvectors1 (v, 3);
    // same memory as simple floats 
    McDataPointer typed1 (v); 

    McDataPointer typed1const ((const float*)(v));
    float* f1 = typed1const.floatPtr(); // runtime error, typed1const was forced to be const 
    const float* f2 = typed1const.floatconstPtr(); // ok
\endcode
  */
class MCLIB_API McDataPointer {
    public: 
        enum AccessType {
              A_NONCONST = 0
            , A_CONST = 1
        };
    
        /** Provide a default constructor. 
         */ 
        McDataPointer () : data (0), type (mcdatatypes::mc_unknown), ndv(0), readonly(1) {};
        
        /* char constructors */
        /// 
        explicit McDataPointer(char* d) : data(d), type(McDataType::ofPointer(d)), ndv(1), readonly(0) {}

        /// 
        McDataPointer(char* d, int ndatavar) : data(d), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (0) {}

        /// 
        explicit McDataPointer(const char* d) : data(const_cast<char*>(d)), type(McDataType::ofPointer(d)), ndv(1), readonly(1) {}

        /// 
        McDataPointer(const char* d, int ndatavar) : data(const_cast<char*>(d)), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly(1) {}


        /* unsigned char constructors */
        /// 
        explicit McDataPointer(unsigned char* d) : data(d), type(McDataType::ofPointer(d)), ndv(1), readonly(0) {}

        /// 
        McDataPointer(unsigned char* d, int ndatavar) : data(d), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (0) {}

        /// 
        explicit McDataPointer(const unsigned char* d) : data(const_cast<unsigned char*>(d)), type(McDataType::ofPointer(d)), ndv(1), readonly(1) {}

        /// 
        McDataPointer(const unsigned char* d, int ndatavar) : data(const_cast<unsigned char*>(d)), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly(1) {}


        /* short constructors */
        /// 
        explicit McDataPointer(short* d) : data(d), type(McDataType::ofPointer(d)), ndv(1), readonly (0) {}

        /// 
        McDataPointer(short* d, int ndatavar) : data(d), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (0) {}

        /// 
        explicit McDataPointer(const short* d) : data(const_cast<short*>(d)), type(McDataType::ofPointer(d)), ndv(1), readonly (1) {}

        /// 
        McDataPointer(const short* d, int ndatavar) : data(const_cast<short*>(d)), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (1) {}


        /* unsigned short constructors */
        /// 
        explicit McDataPointer(unsigned short* d) : data(d), type(McDataType::ofPointer(d)), ndv(1), readonly (0) {}

        /// 
        McDataPointer(unsigned short* d, int ndatavar) : data(d), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (0) {}

        /// 
        explicit McDataPointer(const unsigned short* d) : data(const_cast<unsigned short*>(d)), type(McDataType::ofPointer(d)), ndv(1), readonly (1) {}

        /// 
        McDataPointer(const unsigned short* d, int ndatavar) : data(const_cast<unsigned short*>(d)), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (1) {}


        /* int constructors */
        /// 
        explicit McDataPointer(int* d) : data(d), type(McDataType::ofPointer(d)), ndv(1), readonly (0) {}

        /// 
        McDataPointer(int* d, int ndatavar) : data(d), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (0) {}

        /// 
        explicit McDataPointer(const int* d) : data(const_cast<int*>(d)), type(McDataType::ofPointer(d)), ndv(1), readonly (1) {}

        /// 
        McDataPointer(const int* d, int ndatavar) : data(const_cast<int*>(d)), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (1) {}


        /* float constructors */
        /// 
        explicit McDataPointer(float* d) : data(d), type(McDataType::ofPointer(d)), ndv(1), readonly (0) {}

        /// 
        McDataPointer(float* d, int ndatavar) : data(d), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (0) {}

        /// 
        explicit McDataPointer(const float* d) : data(const_cast<float*>(d)), type(McDataType::ofPointer(d)), ndv(1), readonly (1) {}

        /// 
        McDataPointer(const float* d, int ndatavar) : data(const_cast<float*>(d)), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (1) {}


        /* double constructors */
        /// 
        explicit McDataPointer(double* d) : data(d), type(McDataType::ofPointer(d)), ndv(1), readonly (0) {}

        /// 
        McDataPointer(double* d, int ndatavar) : data(d), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (0) {}

        /// 
        explicit McDataPointer(const double* d) : data(const_cast<double*>(d)), type(McDataType::ofPointer(d)), ndv(1), readonly (1) {}

        /// 
        McDataPointer(const double* d, int ndatavar) : data(const_cast<double*>(d)), type(McDataType::ofPointer(d)), ndv(ndatavar), readonly (1) {}


        /// 
        McDataPointer(void* d, McDataType ty) : data(d), type(ty), ndv(1), readonly (0) { }

        /// 
        McDataPointer(void* d, McDataType ty, int ndatavar) : data(d), type(ty), ndv(ndatavar), readonly (0) { }

        /// 
        McDataPointer(const void* d, McDataType ty) : data(const_cast<void*>(d)), type(ty), ndv(1), readonly (1) { }

        /// 
        McDataPointer(const void* d, McDataType ty, int ndatavar) : data(const_cast<void*>(d)), type(ty), ndv(ndatavar), readonly (1) { }

       
        /* 'copy' constructors */ 
        /// 
        McDataPointer (const McDataPointer& other) : data (other.data), type (other.type), ndv(other.ndv), readonly (other.readonly) {};


        /// Returns data pointer.
        void* dataPtr() const {
            mcrequire (!readonly);
            return data;
        }

        /// Returns data pointer.
        const void* constdataPtr() const {
            return data;
        }

        /// return pointer after typechecking.
        char* charPtr () const {
            mcrequire (!readonly);
            mcrequire (type.isBasedOn (mcdatatypes::mc_int8));
            return (char*)data;
        }

        // return pointer after typechecking 
        const char* charconstPtr () const {
            mcrequire (type.isBasedOn (mcdatatypes::mc_int8));
            return (const char*)data;
        }

        /// return pointer after typechecking.
        unsigned char* uint8Ptr () const {
            mcrequire (!readonly);
            mcrequire (type.isBasedOn (mcdatatypes::mc_uint8));
            return (unsigned char*)data;
        }

        // return pointer after typechecking 
        const unsigned char* uint8constPtr () const {
            mcrequire (type.isBasedOn (mcdatatypes::mc_uint8));
            return (const unsigned char*)data;
        }

        /// return pointer after typechecking.
        short* int16Ptr() const {
            mcrequire (!readonly);
            mcrequire (type.isBasedOn (mcdatatypes::mc_int16));
            return (short*)data;
        }

        /// return pointer after typechecking.
        const short* int16constPtr() const {
            mcrequire (type.isBasedOn (mcdatatypes::mc_int16));
            return (const short*)data;
        }

        /// return pointer after typechecking.
        unsigned short* uint16Ptr() const {
            mcrequire (!readonly);
            mcrequire (type.isBasedOn (mcdatatypes::mc_uint16));
            return (unsigned short*)data;
        }

        /// return pointer after typechecking.
        const unsigned short* uint16constPtr() const {
            mcrequire (type.isBasedOn (mcdatatypes::mc_uint16));
            return (const unsigned short*)data;
        }

        /// return pointer after typechecking.
        int* int32Ptr() const {
            mcrequire (!readonly);
            mcrequire (type.isBasedOn (mcdatatypes::mc_int32));
            return (int*)data;
        }

        /// return pointer after typechecking.
        const int* int32constPtr() const {
            mcrequire (type.isBasedOn (mcdatatypes::mc_int32));
            return (const int*)data;
        }

        /// return pointer after typechecking.
        float* floatPtr() const {
            mcrequire (!readonly);
            mcrequire (type.isBasedOn (mcdatatypes::mc_float));
            return (float*)data;
        }

        /// return pointer after typechecking.
        const float* floatconstPtr() const {
            mcrequire (type.isBasedOn (mcdatatypes::mc_float));
            return (const float*)data;
        }

        /// return pointer after typechecking.
        double* doublePtr() const {
            mcrequire (!readonly);
            mcrequire (type.isBasedOn (mcdatatypes::mc_double));
            return (double*)data;
        }

        /// return pointer after typechecking.
        const double* doubleconstPtr() const {
            mcrequire (type.isBasedOn (mcdatatypes::mc_double));
            return (const double*)data;
        }

        /* The cast operators may be useful toghether with templates */

        /// Returns data pointer, dataPtr() is the preferred method.
        operator void*() const {
            return dataPtr();
        }

        /// Returns data pointer, constdataPtr() is the preferred method.
        operator const void*() const {
            return constdataPtr();
        }

        /// return pointer after typechecking, uint8Ptr() is the preferred method.
        operator char* () const {
            return charPtr();
        }

        /// return pointer after typechecking, uint8constPtr() is the preferred method.
        operator const char* () const {
            return charconstPtr(); 
        }

        /// return pointer after typechecking, uint8Ptr() is the preferred method.
        operator unsigned char* () const {
            return uint8Ptr();
        }

        /// return pointer after typechecking, uint8constPtr() is the preferred method.
        operator const unsigned char* () const {
            return uint8constPtr(); 
        }

        /// return pointer after typechecking, int16Ptr() is the preferred method.
        operator short* () const {
            return int16Ptr();
        }

        /// return pointer after typechecking, int16constPtr() is the preferred method.
        operator const short* () const {
            return int16constPtr();
        }

        /// return pointer after typechecking, uint16Ptr() is the preferred method.
        operator unsigned short* () const {
            return uint16Ptr();
        }

        /// return pointer after typeckecking,  is the preferred method.
        operator const unsigned short* () const {
            return uint16constPtr();
        }

        /// return pointer after typeckecking, int32Ptr() is the preferred method.
        operator int* () const {
            return int32Ptr();
        }

        /// return pointer after typeckecking, int32constPtr() is the preferred method.
        operator const int* () const {
            return int32constPtr();
        }

        /// return pointer after typeckecking, floatPtr() is the preferred method.
        operator float* () const {
            return floatPtr();
        }

        /// return pointer after typeckecking, floatconstPtr() is the preferred method.
        operator const float* () const {
            return floatconstPtr();
        }

        /// return pointer after typeckecking, doublePtr() is the preferred method.
        operator double* () const {
            return doublePtr();
        }

        /// return pointer after typeckecking, doubleconstPtr() is the preferred method.
        operator const double* () const {
            return doubleconstPtr();
        }

        //
        McDataType dataType () const {
            return type;
        }

        //
        int nDataVar () const {
            return ndv;
        }

        //
        int dataElemSize () const {
            return type.size () * ndv;
        }

        //
        bool isConst () const {
            return readonly == 1;
        }

        /** Return a McDataPointer which is of defined const type.
          */
        McDataPointer constCast (AccessType access = A_NONCONST) const {
            return McDataPointer (*this, access);
        }

        /** Change type of memory to be const.
          */
        void forceConst () {
            readonly = 1;
        }

        /** Change type of memory to be non const.
          */
        void forceNonConst () {
            readonly = 0;
        }

        /** Returns new McDataPointer which references 
            a duplicate of the referenced memory */
        McDataPointer duplicateData() {
            McDataPointer p = *this;
            void * ptr = mcmalloc(dataElemSize());
            p.changeDataPtr(ptr);
            memcpy(ptr,rawmemory(),dataElemSize());
            return p;
        }

    protected:
        // get access to the memory 
        char* rawmemory () const {
            return (char*)data;
        }

        // 
        void changeDataPtr (void* d) {
            data = d;
        }
     
        /// 
        void changeDataPtr (const void* d) {
            data = const_cast<void*>(d);
        }

    private:
        /// Pointer to the data
        void* data;

        /// The type of the data
        McDataType type;

        /** NDataVar, the number of elements of basic type grouped together to form an basic element. 
          */
        int ndv;

        /** Set if the memory should be treated as read only.
          */
        unsigned int readonly:1;


        /// copy constructor which overrides const.
        McDataPointer (const McDataPointer& other, AccessType access) : data(other.data), type(other.type), ndv(other.ndv), readonly (access)  { }
};

#endif


/// @}

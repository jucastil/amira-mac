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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_DATA_ACCESS_H_
#define _VS_DATA_ACCESS_H_


#include "Vs.h"

#include "VsInterface.h"

#include <mclib/McPrimType.h>
#include <mclib/McBox3i.h>
#include "McVec3l.h"


/** VsDataAccess provides direct access to a 3D data array stored in memory.
    You get a pointer to a VsDataAccess instance when mapping parts of a
    VsData object into memory using VsData::lock() or related methods.
    
    The elements of the 3D data array may be stored in a non-contiguous or
    even non-linear way in memory. Non-contiguous means that the offset
    between subsequent elements of the 3D data array is larger than the size
    of an individual element, i.e., the elements are stored in an interlaced
    way. In order to obtain the address of the element (i,j,k) within the
    current region-of-interest you should use the following code:
\code
    if ( data->primType() == McPrimType::mc_uint16 ) 
    {
        const VsDataAccess * a = data->lock( roi, VsData::P_READONLY );
        if ( a )
        {
            char * ptr = a->dataPtr(k) + j*a->strides()[1] + i*a->strides()[0];
            unsigned short value = *(unsigned short*)ptr;
            data->unlock(a);
        }
        else
        {
            Vs::lastError().notify();
        }
    }
\endcode
    Note that the strides returned by VsDataAccess::strides() are in bytes.
    Thus you should perform any pointer arithmetic with the char* pointer
    returned by VsDataAccess::dataPtr(). Once you have computed the address
    of an element you may cast the char* pointer to the actual primitive
    data type of the element, e.g. unsigned short as in the example above.

    Also note that each slice of the 3D data array may be stored at its own
    memory position. This is refered to as a non-linear memory layout. Thus
    you should call VsDataAccess::dataPtr() in order to obtain the base
    address for each slice of the array (compare example code above). 

    After construction the VsDataAccess object describes an empty array of size 
    0x0x0. You can initialize the object by calling setImageVolume() or setImageSlices().

    VsDataAccess does not manage any memory on its own. Consequently, also no memory 
    is freed on its destruction. 
*/
class VSVOLREN_API VsDataAccess : public VsInterface
{
    VS_DECL_INTERFACE        ( VsDataAccess )
    VS_DECL_INTERFACE_IMPL   ( VsDataAccess )
//    VS_DECL_INTERFACE_FACTORY( VsDataAccess )
//    VS_DECL_INTERFACE_RELAY  ( VsDataAccess )

public:

    /** Returns the primitive data type of the values of the 3D array.
        For example, unsigned 16-bit data values are specified by
        McPrimType::mc_uint16. 
        \return 
                The primitive data type.
    */
    McPrimType primType() const;

    /** Returns the number of components of the data elements.
        \return 
                The number of components per data element.
    */
    int nDataVar() const;

    /** Returns the size of the 3D array. dims()[0] is the number of voxels in
        x-direction (running fastest), dims()[1] is the number of voxels in
        y-direction, and dims()[2] is the number of voxels in z-direction. 
        \return 
                A vector holding the x-, y- and z-dimension.
    */
    const McVec3l dims() const;

    /** Returns the offset in bytes between subsequent elements in x- and
        y-direction, given by strides()[0] and strides()[1], respectively.
        If the data is stored in linear order in memory, strides()[2]
        denotes the offset between subsequent elements in z-direction.
        Otherwise, strides()[2] will be 0. 
        \return 
                A vector holding the x-, y- and z-stride value.
    */
    const McVec3l strides() const;

    /** Returns the address of the first element of slice \c inSliceIndex. The address
        is returned as a char* pointer in order to simplify pointer arithmetic
        with the byte offsets returned by strides(). You need to explicitly
        check the primitive data type of the elements as returned by primType()
        and cast the address to a matching pointer type. 
        \param  inSliceIndex
                Index of the requested slice.
        \return 
                Address of the first element of slice \c inSliceIndex.
    */
    char * dataPtr( mclong inSliceIndex = 0 ) const;

    /** Returns the address of the element with indices x, y, and z
        The address is returned as a char* pointer in order to simplify pointer arithmetic
        with the byte offsets returned by strides(). You need to explicitly
        check the primitive data type of the elements as returned by primType()
        and cast the address to a matching pointer type. 
        \param  inX, inY, inZ
                Index of the requested data element.
        \return 
                Address of the element at position x, y, z.
    */
    char * dataPtr( mclong inX, mclong inY, mclong inZ ) const;

    /** Takes a region-of-interest in index space and initializes the
        VsDataAccess object referenced by \c outAccess so that it describes this
        region-of-interest. No data is allocated or copied. 
        \param  outAccess
                Access object that gets initialized.
        \param  inROI
                Boxed region of interest that will be addressed by \c outAccess.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT subBox( VsDataAccess & outAccess, const McBox3i & inROI ) const;

    /** Initializes the VsDataAccess object with one linear block of
        memory. The memory will not be copied and it will not be deleted
        by the VsDataAccess object. If \c inStrides[2] is zero a contiguous
        (non-interlaced) memory layout will be assumed and the internal
        strides() array will be initialized automatically. 
        \param  inDims
                The dimensions of the data. Must be non-zero.
        \param  inStrides
                The vector of stride values which is copied to the access
                object. If inStrides[2] is zero a contiguous memory 
                layout will be assumed and the internal strides() array will be 
                initialized automatically.
        \param  inVolumeData
                Non-zero pointer to the actual data array.
        \param  inPrimType
                The primitive type of the data.
        \param  inNDataVar
                The number of channels per data element.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT setImageVolume( const McVec3l & inDims, const McVec3l & inStrides, void * inVolumeData, McPrimType inPrimType, int inNDataVar=1 );

    /** Initializes the VsDataAccess object with multiple slices each
        stored at an arbitrary position in memory. The memory will not be
        copied and it will not be deleted by the VsDataAccess object.
        However, the pointers indicated by \c inSliceData will be copied.
        If \c inStrides is zero a contiguous (non-interlaced) memory layout
        will be assumed for each slice and the internal strides() array
        will be initialized automatically.
        \param  inDims
                The dimensions of the data. Must be non-zero.
        \param  inStrides
                The vector of stride values which is copied to the access
                object. If \c inStrides[2] is zero a contiguous 
                memory layout will be assumed and the internal strides() array 
                will be initialized automatically with strides()[2] set to 0 which 
                indicates a non-linear layout.
        \param  inSliceData
                Array of pointers to each slice of the 3D data. Must be non-zero. The array must have at least \c inDims[2] entries.
        \param  inPrimType
                The primitive type of the data.
        \param  inNDataVar
                The number of channels per data element.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT setImageSlices( const McVec3l & inDims, const McVec3l & inStrides, void ** inSliceData, McPrimType inPrimType, int inNDataVar=1 );

    /** Returns \c True if the data is stored in one chunk of memory. If this
        is not the case each slice might be stored at an arbitrary position
        in memory. The base address of a slice can be obtained by calling
        VsDataAccess::dataPtr(). 
        \return 
                \c True if data memory layout is linear, \c False if non-linear.
    */
    bool isLinear() const;

    /** Returns \c True if the data is stored in contiguous form without interlacing
        between subsequent voxels. This is the case if strides()[0] equals
        nDataVar()*primType().size(), strides()[1] equals strides()[0]*dims()[0],
        and strides()[2] equals strides()[1]*dims()[1]. 
        \return 
                \c True if data memory layout is contiguous, \c False if non-contiguous.
    */
    bool isContiguous() const;

    /** This method extracts a row from the 3D data array. One of the three
        indices \c inX, \c inY, \c inZ must be -1. This index determines the direction of
        the row. All results are casted to float. \c outRow must point to a
        sufficiently large memory location. 
        \param  inX
                Coordinate of the row in X direction. -1 indicates that the row is taken in X direction.
        \param  inY
                Coordinate of the row in Y direction. -1 indicates that the row is taken in Y direction.
        \param  inZ
                Coordinate of the row in Z direction. -1 indicates that the row is taken in Z direction.
        \param  outRow
                Non-zero pointer to the application-provided destination memory of sufficient size.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT row( mclong inX, mclong inY, mclong inZ, float * outRow ) const;

    /** This method saves a row into the lattice. One of the three
        indices @c inX, @c inY, @c inZ must be -1. This index determines the direction of
        the row. The input values will be casted and clipped to the range
        of the primitive data type of the array elements. 
        \param  inX
                Coordinate of the row in X direction. -1 indicates that the row is written in X direction.
        \param  inY
                Coordinate of the row in Y direction. -1 indicates that the row is written in Y direction.
        \param  inZ
                Coordinate of the row in Z direction. -1 indicates that the row is written in Z direction.
        \param  inRow
                Non-zero pointer to the application-provided source memory of sufficient size.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT putRow( mclong inX, mclong inY, mclong inZ, const float * inRow ) const;

    /** Resets this object so that it describes an empty array of size 0x0x0.
        All data pointers, the strides, and the number of data variables per
        voxel are set to 0. 
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT clear();

#ifndef HIDDEN_FROM_DOC
    /** Depricated: The method will be removed.

        Sets all data pointers to 0. In contrast to clear() the size of the
        3D array, the strides, and the number of data variables per voxel are
        not reset. 
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT zeroDataPtrs();
#endif

    /** Returns \c True if this object stores non-zero memory pointers. For example,
        this is not the case after calling clear(). 
        \return 
                \c True if there are non-zero data pointers, \c False if not.
    */
    bool hasData() const;
};

#endif

/// @}

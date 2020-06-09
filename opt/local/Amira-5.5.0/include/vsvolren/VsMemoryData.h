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
#ifndef _VS_MEMORY_DATA_H_
#define _VS_MEMORY_DATA_H_

#include "Vs.h"

#include "VsInterface.h"
#include "VsData.h"

#include <mclib/McPrimType.h>
#include <mclib/McBox3i.h>


// VS_RELAY_CLASS VsMemoryData VsDataRelay


/** The VsMemoryData class describes a 3D data array which is completely
    stored in memory. The data may be stored in one single chunk of memory
    containing all slices of the data or in multiple smaller chunks
    each containing a smaller number of slices. This is mentioned here as
    data splitting. Data splitting is intended to store datasets that are 
    bigger than the biggest allocatable memory chunk.
*/
class VSVOLREN_API VsMemoryData : public VsData
{
    VS_DECL_INTERFACE        ( VsMemoryData )
    VS_DECL_INTERFACE_IMPL   ( VsMemoryData )
    VS_DECL_INTERFACE_FACTORY( VsMemoryData )
    VS_DECL_INTERFACE_RELAY  ( VsMemoryData )

public:

    ////////////////////////////////////////
    // virtuals from VsData
    ////////////////////////////////////////

    /// Checks whether actual data is contained (overloaded from VsData).
    virtual bool hasData() const; // LOCAL_GET
    /// Checks whether actual data is contained (overloaded from VsData).
    virtual bool hasDataLocal() const; // LOCAL_GET
    /// Returns the primitive data type of the data elements (overloaded from VsData).
    virtual McPrimType primType() const; // LOCAL_GET
    /// Returns the number of components of the data elements (overloaded from VsData).
    virtual int nDataVar() const; // LOCAL_GET
    /// Returns the dimensions of the 3D data array (overloaded from VsData).
    virtual const McVec3l dims() const; // LOCAL_GET

protected:
    // Maps data elements into main memory (overloaded from VsData).
    virtual VSRESULT mapDataToMemory( McBox3i inROI, VsDataAccess & outAccess ); // FORBIDDEN_ON_CLIENT
    // Un-maps data elements (overloaded from VsData).
    virtual VSRESULT unMapDataFromMemory( VsDataAccess & inAccess, bool inTouched ); // FORBIDDEN_ON_CLIENT

public:
    ////////////////////////////////////////
    // new methods
    ////////////////////////////////////////

    /** Initialize the object. New memory will be allocated and the auto deletion
        flag is set to true, meaning that the memory chunk will be released upon object
        deletion.

        \param  inDims
                Target dimensions of the data.
        \param  inPrimType
                Primitive type of the data components.
        \param  inNumDataVar
                Number of components per data element.
        \param  inForceLinear
                If set to \c False and the memory could not be allocated in one piece, the method also tries to allocate
                the memory in multiple smaller pieces.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT init( const McVec3l & inDims, McPrimType inPrimType, int inNumDataVar=1, bool inForceLinear=true ); // VS_SYNC_CALL

    /** Initializes the object with a volume provided as contigous memory chunk.
        No copy of the volume is made, instead the VsMemoryData object reuses
        the provided memory. The auto deletion flag is initialized to false. 
        The responsibility for deletion remains with the caller to init(). However, 
        VsMemoryData assumes that the data pointer remains valid until it is destroyed 
        or a new data pointer is provided.
        Note that it is possible, to pass the responsibility for the provided memory 
        to the VsMemoryData object by manually setting the auto deletion flag 
        (setAutoDelete()). This might be useful, e.g., if the data object is
        created by an external initialization method.
        
        \param  inDims
                Target dimensions of the data.
        \param  inStrides
                The stride values which are copied to the data object. 
                (refer to VsDataAccess for details about stride()).
        \param  inVolumeData
                Pointer to the volume data memory. Must be non-zero.
        \param  inPrimType
                Primitive type of the data components.
        \param  inNDataVar
                Number of components per data element.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT init( const McVec3l & inDims, const McVec3l & inStrides, void * inVolumeData, McPrimType inPrimType, int inNDataVar=1 ); // VS_RELAY

    /** Initializes the object with a volume provided as set of individual slices.
        No copy of the slice data is made, instead the VsMemoryData object reuses
        the provided memory. The auto deletion flag is initialized to false.
        The responsibility for deletion remains with the caller to init(). However,
        VsMemoryData assumes that the data pointers remain valid until it is destroyed
        or new data pointers are provided.
        Note that it is possible, to pass the responsibility for the provided memory 
        to the VsMemoryData object by manually setting the auto deletion flag 
        (setAutoDelete()). This might be useful, e.g., if the data objects are
        created by an external initialization method.

        \param  inDims
                Target dimensions of the data.
        \param  inStrides
                The stride values which are copied to the access object.
                Setting \c inStrides[2] to zero indicates a non-linear layout.
                If \c inStrides[0] is set to zero, the \c inStrides parameter is ignored and 
                a contiguous and linear memory layout is assumed.
                (refer to VsDataAccess for details about stride()).
        \param  inSliceData
                Array of pointers to each slice of the 3D data. Must be non-zero. 
                The array must have at least \c inDims[2] entries.
        \param  inPrimType
                Primitive type of the data components.
        \param  inNDataVar
                Number of components per data element.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT init( const McVec3l & inDims, const McVec3l & inStrides, void ** inSliceData, McPrimType inPrimType, int inNDataVar=1 );

    /** Set to zero volume.
        If auto deletion is turned on, \c free() is called on all memory chunks. Thus, make sure 
        memory provided for deletion by VsMemoryData is allocated with \c malloc() - NOT with
        the \c new operator.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT clear(); // VS_RELAY

    /** Convert data. The offsetted value is multiplied by scale and then type converted:
        i.e., the equation for converting each data element is: \c outVal = (\c inVal + \c inOffset)*\c inScale
        and type conversion is performed on the result value \c outVal.
        \param  inDestinationType
                Target primitive data type.
        \param  inOffset
                Offset.
        \param  inScale
                Scale factor.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT mapLinear( McPrimType inDestinationType, double inOffset=0.0, double inScale=1.0 ); // VS_SYNC_CALL

    /** Set the flag for automatic deletion. Default value is true, unless pointers to the
        data have been provided by an appropriate init() method.
        \param  inFlag
                If \c True the pieces of memory used to store the data values are freed when clear() gets invoked.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT setAutoDelete( bool inFlag ); // VS_RELAY
    
    /** Returns the status of the automatic deletion flag.
        \return 
                \c True if the pieces of memory used to store the data values are automatically freed when clear() gets invoked.
    */
    bool autoDelete() const; // LOCAL_GET

    /** Conveniance method, that converts a memory data object with signed short data values
        (common in medical applications) into an object storing unsigned short values. 
        This is useful for dealing with this kind of signed data, since VsVolren only
        supports unsigned data. The conversion is performed by substracting the most negative
        value within the data field from each data value, effectively shifting the data range
        to positive values.
        
        Note that you have to consider this data shift in your application, for the VsMemoryData
        and, thus, a VsVolume object that stores this object reports raw data (aka. shifted values)
        This can be compensated for by using VsVolume::rescaleIntercept() and the appropriate
        scale/rescale methods. 
        
        Note that this function does not perform any operation if the McPrimType is not
        McPrimType::mc_int16. The method will just leave the object untouched.

        \return 
                The method returns the applied bias, i.e. usually the previous data minimum.
                0 is returned if no conversion has been performed, either due to unsupported
                data type or already positiv data values.
    */
    int mapSignedToUnsigned(); // VS_SYNC_CALL
};

#endif

/// @}

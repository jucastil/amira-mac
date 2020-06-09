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
#ifndef _VS_DATA_H_
#define _VS_DATA_H_

#include "Vs.h"


#include <mclib/McHandle.h>
#include <mclib/McPrimType.h>
#include <mclib/McBox3i.h>
#include <mclib/McBox3f.h>
#include <mclib/McDArray.h>
#include <mclib/McMath.h>
#include <amiramesh/HxParamBundle.h>

#include "VsInterface.h"
#include "VsHandable.h"
#include "McVec3l.h"
#include "VsRelay.h"


class VsJobControl;
class VsDataAccess;
class VsEvaluator;
class VsMsg;

class McBox3f;
class McMat4f;

// VS_RELAY_CLASS VsData VsRelay


/** The VsData class describes a 3D data array in an abstract way.
    Each voxel of the 3D array consists of a pre-defined number
    of variables - indicated by nDataVar() - of a particular primitive
    data type, as indicated by primType(). In order to get access to the
    actual data elements you need to lock a particular region of
    the whole 3D data array using lock(). See VsDataAccess for an example. 
    Multiple regions of the data set can be locked at the same time as long 
    as there are no read/write conflicts.

    This abstract class hides the actual storage of the data. The 
    data array might reside in main memory or it might be stored 
    on disk (out-of-core) with only the currently accessed parts  
    mapped to main memory. In order to enable this behaviour a 
    derived class must implement the pure virtual method mapDataToMemory(),
    which is called whenever the user locks a region of the data for
    access. A lock() might therefore not only fail because of read/write
    conflicts but also if the region to be mapped cannot reside in main
    memory. Required cleanup operations can be performed by overloading
    unMapDataFromMemory().
*/
class VSVOLREN_API  VsData 
:   public          VsInterface
,   public virtual  VsHandable
{
    VS_DECL_INTERFACE        ( VsData )
    VS_DECL_INTERFACE_IMPL   ( VsData )
//  VS_DECL_INTERFACE_FACTORY( VsData )
    VS_DECL_INTERFACE_RELAY  ( VsData )

public:

    /// Data type for histograms.
    typedef McDArray<mcuint64> HistogramType;
    
    /// Constants for various filter methods.
    enum Filter 
    {
        /// Box filter - simple averaging of scalar values with constant weights
        FILT_BOX,
        /// Triangle filter - hat-like filter kernel
        FILT_TRIANGLE,
        /// Bell filter
        FILT_BELL,
        /// B-Spline filter
        FILT_BSPLINE,
        /// Mitchell filter
        FILT_MITCHELL,
        /// Lanzcos filter - approximates a sinc(x) function
        FILT_LANZCOS,
        /// Max filer - useful for down-sampling, preserves tiny bright features on a dark background
        FILT_MAX,
        /// Min filter - useful for down-sampling, preserves tiny dark features on a bright background 
        FILT_MIN
    };

    /// Permission flags for the various lock() methods.
    enum Permission
    {
        /// lock for reading only
        P_READONLY  = 1,
        /// lock for reading and writing
        P_READWRITE = 3
    };

    /// Interpolation methods to be used in createEvaluator()
    enum InterpolationMethod
    {
        /// Nearest-neighbour interpolation
        EVAL_NEAREST_NEIGHBOUR,
        /// Tri-linear interpolation
        EVAL_TRI_LINEAR
    };

protected:
    /** Maps data elements that are inside a given axis aligned box into main memory.

        Derived classes should implement this method. It will be called when the data
        set or parts of it are locked via lock().

        \param  inROI
                Box that defines the region of interest.
        \param  outAccess
                The implementation of this method has to initialize this VsDataAccess
                object so that it represents the requested data region.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT mapDataToMemory( McBox3i inROI, VsDataAccess & outAccess ) = 0; // FORBIDDEN_ON_CLIENT

    /** Un-maps data elements associated with a VsDataAccess object from main memory.
        
        Derived classes should implement this method. It will be called when a locked
        region of a data set is unlocked via unlock().
        
        \param  inAccess
                VsDataAccess object previously initialized in the corresponding 
                call to mapDataToMemory().
        \param  inTouched
                If \c True, the data was locked with write permission, i.e., the
                data may have changed and file-i/o operations may be necessary.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT unMapDataFromMemory( VsDataAccess & inAccess, bool inTouched ) = 0; // FORBIDDEN_ON_CLIENT

public:
    /** Checks whether actual data is contained. After calling any init() method
        data should be available.
        \return 
                \c True if there is data available, \c False if not.
    */
    virtual bool hasData() const = 0; // LOCAL_GET

    /** Checks whether actual data is contained. After calling any init() method
        data should be available.
        \return 
                \c True if there is data available, \c False if not.
    */
    virtual bool hasDataLocal() const = 0; // LOCAL_GET

    /** Returns the primitive data type of the data elements.
        \return 
                The primitive data type.
    */
    virtual McPrimType primType() const = 0; // LOCAL_GET

    /** Returns the number of components of the data elements.
        \return 
                The number of components per data element.
    */
    virtual int nDataVar() const = 0; // LOCAL_GET

    /** Returns the dimensions of the 3D data array.
        \return 
                Vector holding the X-, Y- and Z-dimension.
    */
    virtual const McVec3l dims() const = 0; // LOCAL_GET

    /** Returns the voxel spacing - which is the bounding box range that
        corresponds to the distance between two neighboring voxels.
        
        \return
                Vector containing the voxel spacing
    */
    McVec3f voxelSpacing() const; // LOCAL_GET

    /** Returns the voxel indices corresponding to a specified position.
        \param  inPosition
                Position at which the voxel should be set.
        \param  outVoxel
                integer array indicating the x, y, and z index
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT voxelIndex( const McVec3f & inPosition, int * outVoxel ) const; // LOCAL_GET

    /** Returns the voxel position corresponding to a specified indices.
        \param  inIndices
                Indices at which the position should be determined.
        \param  outPosition
                Position coresponding to provided inIndices.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT voxelPosition( const McVec3l &inIndices, McVec3f & outPosition ) const; // LOCAL_GET


    /* Retrieve the value at a given spacial position.
        \param  inPosition
                Position at which the sample has to be taken.
        \param  outResult
                Data value at position \c inPosition. Note that \c outResult.mPointer
                must point to a memory block of size float[nDataVar()].
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual bool sample( const McVec3f & inPosition, int inNumberOfResults, float * outResults ); // VS_SYNC_CALL

    /* Retrieve the value for a given voxel index.
        \param  inVoxel
                Voxel indices where the sample has to be taken.
        \param  outResult
                Data value at position \c inVoxel. Note that \c outResult.mPointer
                must point to a memory block of size float[nDataVar()].
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual bool sample( const McVec3l & inVoxel, int inNumberOfResults, float * outResults ); // VS_SYNC_CALL

    /* Retrieve the values for the given voxels. Which voxel has to be taken is
                defined by the polygon. The polygon is define by a set of points and
                the path of the polygon dedicate which voxels are contained in the result.
        \param  inPoint
                A set of Points which defines the polygon.
        \param  inLast
                the ending postion were the voxels has to be taken.
        \param  inNumberOfResults
                the number of voxels were should return \c outResult.
        \param  outResult
                The data values at positions between \c inFirst and \c inLast.
                Note that \c outResult.mPointer must point to a memory block of
                size float[nDataVar()] * \c inNumberOfResults.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual bool sampleLine( const McDArray<McVec3f> & inPoints, int inNumberOfResults, float * outResults ); // VS_SYNC_CALL

    /** Fils the whole data volume with a particular value.
        \param inValue
               This value will be stored in every voxel in every component.
               The value will be casted to the native data type of the
               data object.
        \return If the method succeeds, the return value is #VS_OK.
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT fill( float inValue ); // VS_RELAY

    /** This method copies the data values from another data object to	the
        memory this object points to. This is especially useful to copy
        contiguous memory to non-contiguous memory. The other object must
        have same dimensions and primtype size.
        \param  inSrcData
                The data object to copy the data from.
        \param  inFlipY
                If set to \c True, the image data will be flipped about
                the y-axis meaning that the last row in the input image
                will become the first row of the output image.
        \return If the method succeeds, the return value is #VS_OK.
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT copyData(VsData * inSrcData, bool inFlipY = false); // VS_RELAY

    /** Returns whether the data object is valid, i.e. the data in this
        object can be accessed. Even if the object has data (hasData() returns
        \c True), the status might be set to invalid, e.g., if some reading 
        thread is still initializing the data values.
        \return 
                \c True if there is data accessible, \c False if not.
    */
    bool isValid() const; // LOCAL_GET

    /** Set validity status.
        \param  inFlag 
                The value that gets returned on the following calls to isValid().
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setValid( bool inFlag ); // VS_RELAY

    /** Set data range.
        \param  inMin
                Minimum data value.
        \param  inMax
                Maximum data value.
        \return 
                If the method succeeds, the return value is #VS_OK. To get extended error information, call Vs::lastError().
    */
    VSRESULT setRange( float inMin, float inMax ); // VS_RELAY

    /** Returns the data range of the 3D data elements.
        \param  outMin
                Minimum value of all data elements.
        \param  outMax
                Maximum value of all data elements.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT range( float & outMin, float & outMax ); // VS_SYNC_CALL (might return cached values if they exist)


    // ////////////////////////////////////////
    //  parameters
    // ////////////////////////////////////////

    /** Returns a read-only reference to the associated parameter bundle.
        While you hold the reference, ensure by using appropriate locking
        mechanisms that the parameter bundle is not modified by other threads.
        \return 
                Read-only reference to the object's parameter bundle.
    */
    const HxParamBundle & parameters() const; // LOCAL_GET

    /** Returns a writable reference to the associated parameter bundle.
        While you hold the reference, ensure by using appropriate locking
        mechanisms that the parameter bundle is not modified by other threads.
        \return 
                Reference to the object's parameter bundle.
    */
    HxParamBundle & parameters(); // VS_FORBIDDEN_ON_SERVER (parameters on server should be read-only)

    /** Sets a parameter bundle.
        \param  inBundle 
                The parameter bundle object is set to a copy of this parameter object.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setParameters( HxParamBundle & inBundle ); // VS_RELAY


    // ////////////////////////////////////////
    //  bounding box
    // ////////////////////////////////////////

    /** Returns the bounding box of the 3D data array.
        \param  outBox
                The current bounding box gets stored in the box object 
                referenced by this parameter.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
    */
    virtual VSRESULT boundingBox( McBox3f & outBox ) const; // LOCAL_GET

    /** Sets the bounding box of the 3D data array.
        \param  inBox 
                The object's bounding box to be set.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT setBoundingBox( const McBox3f& inBox ); // VS_RELAY

    /** Computes the bounding box of a subregion of the 3D data array.
        \param  outBox
                The computed bounding box gets stored in the box object 
                referenced by this parameter.
        \param  inROI
                The subregion in voxel coordinates.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT boundingBox( McBox3f & outBox, const McBox3i & inROI ) const; // LOCAL_GET


    // ////////////////////////////////////////
    //  transformation matrix
    // ////////////////////////////////////////

    /** Set the transformation matrix that transforms from
        object local coordinates to world coordinates.
        With this matrix sheared volumes can be can implemented.
        \param  inMatrix
                The transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT setTransformationMatrix( const McMat4f & inMatrix ); // VS_RELAY

    /** Get the transformation matrix.
        \param  outMatrix
                Receives the current transformation matrix.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT transformationMatrix( McMat4f & outMatrix ) const; // LOCAL_GET

    /** Returns true if the transformation matrix was explicitly set via
        setTransformationMatrix(). */
    virtual bool transformationMatrixDefined() const; // LOCAL_GET

    // ////////////////////////////////////////
    //  Locking
    // ////////////////////////////////////////

    /** Locks the whole 3D data array. If the lock could not be obtained zero is returned.
        \param  inPermission
                Permission that the requested lock has to provide.
        \return 
                If the lock could be obtained, a pointer to the access object is 
                returned; zero otherwise. To get extended error information, call 
                Vs::lastError(). The returned VsDataAccess object remains under 
                control of the library and must be specified as parameter of the
                unlock() method.
    */
    const VsDataAccess * lock( VsData::Permission inPermission = P_READONLY ); // FORBIDDEN_ON_CLIENT

    /** Locks a single slice of the 3D data. Slices are considered to be perpendicular to
        the local z-axis of the data array. If the lock could not be obtained zero is returned.
        \param  inSliceIndex
                Z-index of the slice that gets to be accessed.
        \param  inPermission
                Permission that the requested lock has to provide.
        \return 
                Pointer to the access object if the lock could be obtained. Zero,
                if no lock could be obtained. To get extended error information,
                call Vs::lastError(). The returned VsDataAccess object remains 
                under control of the library and must be specified as parameter
                of the unlock() method.
    */
    const VsDataAccess * lock( int inSliceIndex, VsData::Permission inPermission = P_READONLY ); // FORBIDDEN_ON_CLIENT

    /** Locks a sub-box of the 3D data. If the lock could not be obtained zero is returned.
        \param  inROI
                Sub box that gets to be accessed.
        \param  inPermission
                Permission that the requested lock has to provide.
        \return 
                Pointer to the access object if the lock could be obtained. Zero,
                if no lock could be obtained. To get extended error information, 
                call Vs::lastError(). The returned VsDataAccess object remains 
                under control of the library and must be specified as parameter
                of the unlock() method.
    */
    const VsDataAccess * lock( const McBox3i & inROI, VsData::Permission inPermission = P_READONLY ); // FORBIDDEN_ON_CLIENT

    /** Releases the lock on the 3D data.
        \param  inAccess
                Pointer to the access object returned by a previous call to lock().
                Once the method returns, this pointer is not longer valid.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT unlock( VsDataAccess const * & inAccess ); // FORBIDDEN_ON_CLIENT


    // ////////////////////////////////////////
    // Histogram 
    // ////////////////////////////////////////

    /** Set the histogram.
        \param  inHistogram
                New histogram.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT setHistogram( HistogramType & inHistogram ); // VS_RELAY

    /** Returns the histogram of the 3D data array. This method will
        automatically call computeHistogram(), if the histogram has not
        yet been generated.
        \param  outMin
                Minimum value of all data elements.
        \param  outMax
                Maximum value of all data elements.
        \param  outHistogram
                Current histogram.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT histogram( float & outMin, float & outMax, HistogramType & outHistogram ); // LOCAL_GET

    /** Method for computing the histogram.
        \param  inNumBins
                Number of intervals the data elements are sorted in,
                i.e, the size of the desired histogram.
        \param  outMin
                Minimum value of all data elements.
        \param  outMax
                Maximum value of all data elements.
        \param  outHistogram
                Current histogram with \c inNumBins elements.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT computeHistogram( int inNumBins, float & outMin, float & outMax, HistogramType & outHistogram ); // VS_SYNC_CALL


    // ////////////////////////////////////////
    // File-IO / Post-processing
    // ////////////////////////////////////////

    /** Create a data object from an AmiraMesh file.
        \param  inFileName
                File name of the AmiraMesh file to read in.
        \return 
                The VsData object filled with the data read from the file. 
                If zero call Vs::lastError() to get extended error information.
    */
    static VsData * readAmiraMesh( const char * inFileName );

    /** Write the data to an AmiraMesh file.
        \param  inFileName
                File name of the AmiraMesh file into which the data has to be written.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT writeAmiraMesh( const char * inFileName ); // VS_SYNC_CALL

    /** Allocates and computes a resampled version of the 3D data array.
        \param  inNewDims
                Dimensions of the resampled volume data.
        \param  inFilter
                Specifies the filter that is used for resampling. 
                VsData::Filter for possible values.
        \param  inControl
                Optional VsJobControl-object that allows to interrupt
                the resampling and that reports the computation progress.
        \return 
                The VsData object filled with the resampled data. 
                If zero, call Vs::lastError() to get extended error information.
    */
    VsData * resample( const McVec3l& inNewDims, VsData::Filter inFilter = FILT_BOX, VsJobControl * inControl = 0); // VS_SYNC_CALL

    /** Creates an evaluator for sampling data values. The evaluator holds a
        read-lock on the data. The lock will be released when the evaluator
        is deleted. Evaluators should be used as follows:
        
        \code
            VsEvaluator* e = data->createEvaluator(VsData::EVAL_TRI_LINEAR);
            float value;
            e->set(pos);
            e->eval(&result);
            delete e;
        \endcode

        \param method
                Interpolation method to be used by the evaluator.
                Can be VsData::EVAL_NEAREST_NEIGHBOUR or VsData::EVAL_TRI_LINEAR
        \return
                Pointer to the newly created evaluator object. The evaluator
                should be deleted as soon as it is not used anymore.
    */
    VsEvaluator* createEvaluator(InterpolationMethod method=EVAL_TRI_LINEAR); // FORBIDDEN_ON_CLIENT

    VsEvaluator* createEvaluator(InterpolationMethod method, VsData* labels, int numLabels, bool labelClipped[]); // FORBIDDEN_ON_CLIENT
};

class VsEvaluator
{
public:
    virtual ~VsEvaluator() { }

    virtual bool set(const McVec3f& pos) = 0;

    virtual void eval(float* result) = 0;

    void getVoxelIndex(McVec3i& idx) const {
        idx.i = McRoundEven(mPos.x);
        idx.j = McRoundEven(mPos.y);
        idx.k = McRoundEven(mPos.z);
    }

    const McVec3f& voxelIndexf() const { return mPos; }

protected:
    VsEvaluator() { }

    McVec3f mPos;
};

VsMsg & operator << ( VsMsg & ioMsg, VsData::HistogramType const & inValue  );
VsMsg & operator >> ( VsMsg & ioMsg, VsData::HistogramType       & outValue );

#endif

/// @}

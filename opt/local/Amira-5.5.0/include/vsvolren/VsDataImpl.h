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
#ifndef _VS_DATA_IMPL_H
#define _VS_DATA_IMPL_H


#include "VsData.h"

#include "VsInterfaceImpl.h"
#include "VsDataAccess.h"

#include <mclib/McBox3f.h>
#include <mclib/McBox3i.h>
#include <mclib/McMat4f.h>
#include <amiramesh/AmiraMesh.h>
#include <amiramesh/HxParamBundle.h>
#include <mclibthreaded/McMutex.h>
#include <mclibthreaded/McWaitCondition.h>


//////////////////////////////////////////////////////////
class VsDataImpl : public VsInterfaceImpl
{
    VS_IMPLEMENTATION( VsDataImpl, VsInterfaceImpl, VsData )

public:

    class VsDataAccessPrivate 
    :   public VsDataAccess
    {
        friend class VsDataImpl;
    };


    static int              mInstanceCount;

    // Bounding box of the data
    McBox3f                 mBoundingBox;

    // Range of the voxel component values
    float                   mDataRange[2];

    // Statistical parameters of the data elements
    VsData::HistogramType   mHistogram;
    mcuint64 *              mDataDistArray; // The data distribution array - an acceleration structure for the histogram computation

    // Transformation of the data domain
    McMat4f                 mTransformationMatrix;
    McMat4f                 mTransformationMatrixInverse;
    bool                    mTransformationMatrixDefined;
    // Parameter associated with this data object
    HxParamBundle           mParameters;

    // Flag indicating whether the data associated with this object 
    // is available (or might be in the process of asynchronous read)
    bool                    mValidFlag;

    // for each lock() a new VsDataAccess object gets stored in this array and removed from on unlock()
    McDArray<VsDataAccess*> mLocks;
    McMutex                 mLocksMutex;
    McWaitCondition         mLocksWait;

    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////
    static bool writeRawData( FILE * inTargetFile, bool inSwapBytes, AmiraMesh::Data * unused, void * inUserData );
    
    /** Downsample 3D array of size dimsx*dimsy*dimsz by averaging
        nx*ny*nz values.  All calculations will be done with integer
        arithmetic if src and dst both are integer data types (like
        i.e. shorts). Currently dst and src are to be of the same data
        type. !*/
    VSRESULT downSample( VsData * ioTarget, bool inLabels = false, VsJobControl * control = 0 );
    VSRESULT downSample( const VsDataAccess * ioTarget, bool inLabels = false, VsJobControl * control = 0, McBox3i *bbox = 0 ); 

    VsData * resample2( const McVec3l& newDims, bool inLabels, VsJobControl * control = 0 );

    /** This method is intended for incremental processing of the VsData object.
        You may update some statistical information like data range or histogram
        data whenever additional data, that can be identified by \c inAcc is written
        into the VsData object. */
    void updateData( const VsDataAccess * inAcc );

public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    McVec3f voxelSpacing() const;
    VSRESULT voxelIndex( const McVec3f & inPosition, int * outVoxel ) const;
    VSRESULT voxelPosition( const McVec3l &inIndices, McVec3f & outPosition ) const;
    bool isValid() const;
    VSRESULT setValid( bool inFlag );
    VSRESULT setRange( float inMin, float inMax );
    VSRESULT range( float & outMin, float & outMax );
    const HxParamBundle & parameters() const;
    HxParamBundle & parameters();
    VSRESULT setParameters( HxParamBundle & inBundle );
    const VsDataAccess * lock( VsData::Permission inPermission = VsData::P_READONLY );
    const VsDataAccess * lock( int inSliceIndex, VsData::Permission inPermission = VsData::P_READONLY );
    const VsDataAccess * lock( const McBox3i & inROI, VsData::Permission inPermission = VsData::P_READONLY, bool inNoDataAccess = false );
    VSRESULT unlock( VsDataAccess const * & inAccess );
    VSRESULT setHistogram( VsData::HistogramType & inHistogram );
    VSRESULT histogram( float & outMin, float & outMax, VsData::HistogramType & outHistogram );
    VSRESULT computeHistogram( int inNumBins, float & outMin, float & outMax, VsData::HistogramType & outHistogram );
    static VsData * readAmiraMesh( const char * inFileName );
    VSRESULT writeAmiraMesh( const char * inFileName );
    VsData * resample( const McVec3l& inNewDims, VsData::Filter inFilter = VsData::FILT_BOX, VsJobControl * control = 0 );
    VsEvaluator* createEvaluator(VsData::InterpolationMethod method=VsData::EVAL_TRI_LINEAR);
    VsEvaluator* createEvaluator(VsData::InterpolationMethod method, VsData* labels, int numLabels, bool labelClipped[]);

private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VSRESULT vimpl_boundingBox( McBox3f & outBox ) const;
    VSRESULT vimpl_setBoundingBox( const McBox3f& inBox );
    VSRESULT vimpl_setTransformationMatrix( const McMat4f & inMatrix );
    VSRESULT vimpl_transformationMatrix( McMat4f & outMatrix ) const;
    bool vimpl_transformationMatrixDefined() const;

    virtual bool vimpl_sample( const McVec3f & inPosition, int inNumberOfResults, float * outResults );
    virtual bool vimpl_sample( const McVec3l & inVoxel,    int inNumberOfResults, float * outResults );
    virtual bool vimpl_sampleLine( const McDArray<McVec3f> & inPoints, int inNumberOfResults, float * outResults );
    virtual VSRESULT vimpl_fill( float value );
            VSRESULT vimpl_copyData(VsData * inSrcData, bool inFlipY = false);
};   


#endif

/// @}

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
#ifndef _VS_SLICE_DATA_H
#define _VS_SLICE_DATA_H

#include "VsObject.h"
#include "VsData.h"
#include "VsVolume.h"
#include "VsHeadUpDisplay.h"
#include "VsSlice.h"
#include "VsMesh.h"
#include "VsThickSliceImpl.h" // This is an internal object, so it's ok to have this internal header here

#include <mclib/McVec2f.h>
#include <mclib/McVec3f.h>
#include <mclib/McMat4f.h>

class McMat3f;

class VsSliceData
{
public:

    enum Type
    {
        T_RGBA      = 0
    ,   T_DENSITY   = 1
    ,   T_LABEL     = 2
    };

protected:
    // ----------------------------------
    //   General parameters
    // ----------------------------------
    /// The volume object to visualize
    VsVolume *                  mVolume;
    /// The level 0 data for reference
    VsData *                    mLevel0Data;
    /// The index of the data field within the volume
    int                         mIndex;
    /// Volume index
    int                         mVolumeIndex;
    /// 
    Type                        mType;

    // ----------------------------------

    /// Flag indicating whether the slice data needs resampling
    bool                        mDataDirty;
    /// Flag indicating whether the slice polygon needs update
    bool                        mGeometryDirty;

    /// The actual data object from which the slice is extracted
    // RGBA or Density
    VsData *                    mPresentedData;
    
    /// optional label data object
    VsData *                    mPresentedLabel;

    /// An optional array for omitting voxels belonging to a specific label
    McDArray<bool>              mClipLabels;

    /// A transformation matrix that can be used for registering two volumes
    McMat4f                     mTransformationMatrix;
    McMat4f                     mTransformationMatrixInverse;

    // ----------------------------------
    //   Quality parameters
    // ----------------------------------
    /// The resolution level that is actually beeing presented
    int                         mLevel;
    /** In low quality mode this variable can be set to values larger 1
        to skip every n-th slice during sampling */
    int                         mThickStride;
    // ----------------------------------

    /// filter used for slice extraction
    VsSlice::Filter             mFilter;

    /// the thickness and mode for thick slice mode
    float                       mThickness;
    VsSlice::MipMode            mThickMode;

    /// The actual raw data
    McHandle<VsMemoryData>      mSliceImage;
    int                         mTexDims[2];

    /// (Over-) sampling factor for slice extraction - increases the output image if set to > 1.f
    float                       mSamplingFactor;

    bool                        mLabelsEnabled;

public:

    /** Constructor
        \param volume   the volume object
        \param idx      the data element within the volume object
                        (e.g. density values or label data) */
    VsSliceData(VsVolume * volume, VsData * data);

    /// Destructor
    virtual ~VsSliceData();

    /** Set a new volume and new data objects - if the same objects are already
        in use, this method does nothing.
    */
    void setData(VsVolume * volume, VsData * data, VsData * labelData);

    /**  Set index of volume
        \param inIndex 0 = primary and 1 = overlay
    */
    void setVolumeIndex( int inIndex );
    int volumeIndex();
    
    /** Set type of slice data
        \param inType slice data type
    */
    void setType(Type t);
    Type type();
    
    /// Reallocate slice memory if neccessary
    void resize(int dimsX, int dimsY);

    /** FIXME:
        Validates the slice data object - should be called every time
        the volume changed. However, this method just provides a workaround
        for dealing with inconsistent internal data structures. It will
        not fix this inconsistency but just disable rendering.
    */
    void validate();

    /// Set a transformation matrix
    virtual VSRESULT setTransformationMatrix( const McMat4f & inMatrix );
    /// Returns the transformation matrix
    VSRESULT transformationMatrix( McMat4f & outMatrix ) const;

    /// Allows to adjust the quality for the slice extraction
    virtual void setQuality(int level, int stride = 1, float samplingFactor = 1.f, bool force = false);
    /// Returns the projected compute time for that slice in milliseconds
    virtual float computeTime(float setupTimePerPixelNS, int level, int stride) = 0;

    /// Extracts the slice data
    virtual VSRESULT compute(bool & needReload, VsObject &object) = 0;
    /// Returns whether the slice was extracted with full quality
    virtual bool isHighQuality() const { return mPresentedData == mLevel0Data && mThickStride == 1 && mSamplingFactor >= 1.f; };

    /// Returns the pointer to the associated volume
    VsVolume * volume() const { return mVolume; };
    /// Returns the index of the managed data object inside the volume
    int index() const { return mIndex; };

    /// Returns the finest available resolution level
    virtual int finestLevel() const { return 0; };
    /// Returns the coarsest available resolution level
    virtual int coarsestLevel() const { return 1; };
    /// Returns the level that was actually used for extraction
    int level() const { return mLevel; };

    /// Set the thickness for the slice
    virtual VSRESULT setThickness(float thickness);
    /// Get the current thickness.
    float thickness() const { return mThickMode ? mThickness : 0.0f; };
    /// Returns the actual number of thick slices.
    virtual int numThickSlices() const { return (int) mThickness; };
    /// Set filter for slice extraction
    virtual VSRESULT setFilter( VsSlice::Filter inFilter );
    /// Returns the current filter for slice extraction
    virtual VsSlice::Filter filter() const { return mFilter; };
    /// Set the reconstruction mode for thick-MPR
    virtual VSRESULT setThickMIPMode( VsSlice::MipMode inMode );
    /// Returns the current thick-MPR reconstruction mode
    VsSlice::MipMode thickMIPMode( ) const { return mThickMode; };
    /// Set the array for clipped labels
    virtual VSRESULT setLabelClipped(McDArray<bool> * clipLabels);

    // -------------------------------------------------------------
    // The interface to access the slice and associated parameters
    // -------------------------------------------------------------

    /// Functions for accessing the acutal slice data
    virtual VsData * sliceImage() const { return mSliceImage; };
    virtual const McVec3l sliceDims() const { return mSliceImage->dims(); };

    /// Functions for accessing the texture to hold the slice
    virtual const int * texDims() const { return mTexDims; };
    virtual void swizzle(int outSwizzle[3]) const;

#if 0
    //!! TODO: not used any more - remove occationally
    /** Maps a 3D position to corresponding texture coordinates, returns false if
        transformation is not possible */
    virtual bool mapToTextureCoord(McVec3f & inPosition, int &x, int &y) const = 0;
    /** Calculate transform between object space and texture space, returns
        false if the matrix could not be computed, e.g. in case of curved slices */
    virtual bool calcTextureTransform(McMat3f & outTransform) const { return false; };
#endif

    /// Access the geometry, that was used for sampling the volume data
    virtual const VsMesh * sampleGeometry() const = 0;
    /// Access the geometry, that should be used for displaying the sampled data
    virtual const VsMesh * renderGeometry() const = 0;

    /// Dumps additional object information into a head-up display
    virtual void dump(VsHeadUpDisplay & hud, VsHeadUpDisplay::Placement placement) = 0;
    /// Set data dirty flag
    void setDataDirty(bool status) { mDataDirty = status; };
    /// Retrun the data dirty flag
    bool dataDirty() { return mDataDirty; };

    void setLabelsEnabled(bool setting) { mLabelsEnabled = setting; }
    bool labelsEnabled() const { return mLabelsEnabled; }

  protected:
    /// Utility method for creating appropriate functors
    ThickFunctor * createFunctor(const int * texDims, void * texData, McPrimType primType, int nDataVar);
    /// Attribute method defining, when label clipping should be applied
    bool useLabelClipping() const;
};

#endif

/// @}

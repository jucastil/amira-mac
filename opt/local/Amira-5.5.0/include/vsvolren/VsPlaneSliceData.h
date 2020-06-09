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
#ifndef _VS_PLANE_SLICE_DATA_H
#define _VS_PLANE_SLICE_DATA_H

#include "VsSliceData.h"
#include "VsSlice.h"
#include "VsMesh.h"
#include "VsPolygon.h"

class VsObject;
class VsSliceHighResData;
class ThickFunctor;

////////////////////////////////////////////////////////////////////////////////
class VsPlaneSliceData : public VsSliceData, VsMesh
{
public:

    /// struct for scanline callback
    struct SampleAux
    {
        int         dimx;
        int         dimy;
        int         dimz;
        int         nDataVar;
        int         pitch;
        int         dstOffset;
        void      * dst;
        int         thickness;
        int         stride;
        int         samples;
        bool        interpolate;
        int       * rasterLine;
        int       * ptrOffset;
        int       * labelPtrOffset;
        VsObject  * object;
        bool        canceled;
        ThickFunctor * functor;
    };

#if 1
    /// TODO: get rid of this stuff!!

    /* Dimensions of the OpenGL texture (power-of two). Usually this is identical
       to mTexDims, but the dimensions may get larger if high-res data is available. */
    int myTexDims[2];

    /* Pointer to the actual slice image. Usually this is identical to mSliceImage.
       If high-res data is used, it may point to somewhere else. */
    McHandle<VsData> mySliceImage;

    /* Texture coordinates used to render the texture. Usually this is identical
       to mTexCoords, but it may be different if high-res data is available. */
    McVec2f myTexCoords[6];

    McHandle<VsMemoryData> mHighResSlice;
#endif

private:

    /// Helper struct for scanline callback
    SampleAux              mAux;

    /// Number of slices extracted
    int                    mSliceCounter;

    /// Parameters describing the plane to be extracted
    McPlane                mPlane;           // the plane equation
    VsSlice::Orientation   mOrientation;     // the plane orientation
    float                  mSliceNumber;     // the slice number to be extracted (with respect to level-0)
    bool                   mIllegalPlane;    // The plane is illegal, e.g. referes to a slice outside the data field

    /// Some auxiliary variables for internal use
    int                    mPermutation[3];  // the index swizzeling for the extracted plane
    int                    mThickSliceStart; // the first slice to extract in thick slice mode
    int                    mThickSliceStop;  // the last slice to extract in thick slice mode
    int                    mSliceBaseDims[2];// slices dimensions with respect to level 0 data

    /// The polygon for slice extraction
    int                    mNumTransformedVertices;
    McVec3f                mTransformedCoords[6];

    /// The polygon for rendering the slice data
    int                    mNumVertices;
    McVec3f                mCoords[6];
    McVec2f                mTexCoords[6];

    /// The polygon object for returning the render polygon
    VsGenericPolygon       mPolygon;
    bool                   mPolygonValid;

    /* Pointer to helper classes managing the retrievel of high data in each of
       the main axis directions. */
    VsSliceHighResData* mHighResData[3];

    /// Timing statistics for slice extraction - used for computing projectd compute time
    float mExtractionTimePerVoxelNS[4][3];

public:

    VsPlaneSliceData(VsVolume * vol, VsData * data);
    virtual ~VsPlaneSliceData();

    // --------------------------------------
    // Overloaded from VsSliceData
    // --------------------------------------
    virtual float computeTime(float setupTimePerPixelNS, int level, int stride);

    virtual VSRESULT compute(bool & needReload, VsObject &object);
    virtual VSRESULT computeGeometry();
    virtual bool isHighQuality() const;
    virtual int finestLevel() const { return hasHighResData() ? -1 : 0; };
    virtual VSRESULT setThickness(float thickness);
    virtual int numThickSlices() const;
    virtual VSRESULT setThickMIPMode( VsSlice::MipMode inMode );
    virtual VSRESULT setFilter( VsSlice::Filter inFilter );

    virtual VsData * sliceImage() const { return mySliceImage; };
    virtual const McVec3l sliceDims() const { return mySliceImage ? mySliceImage->dims() : McVec3l(0); };
    virtual const int * texDims() const { return myTexDims; };
    virtual void swizzle(int outSwizzle[3]) const { memcpy(outSwizzle, mPermutation, 3*sizeof(int)); };

#if 0
    //!! TODO: not used any more - remove occationally
    virtual bool mapToTextureCoord(McVec3f & inPosition, int &x, int &y) const;
    virtual bool calcTextureTransform(McMat3f & outTransform) const;
#endif

    virtual const VsMesh * sampleGeometry() const { return this; };
    virtual const VsMesh * renderGeometry() const { return this; };

    // Interface of VsMesh
    // virtual int numPolygons() const { return mNumVertices > 2 ? 1 : 0; };
    virtual int numPolygons() const { return mPolygonValid ? (int)(mNumVertices > 2) : 0; };
    virtual const VsPolygon * polygon(unsigned int idx) const;
    virtual int numContours() const { return numPolygons(); };
    virtual const VsPolygon * contour(unsigned int idx) const { return polygon(idx); };
    virtual VSRESULT boundingBox( McBox3f & outBox ) const;

    // --------------------------------------
    // New methods
    // --------------------------------------
    VSRESULT setPlane(const McPlane& plane);
    VsSlice::Orientation orientation() const { return mOrientation; }

private:

    /// Access for timing statistics for a given orientation and level
    float & extractionTime(int orientation, int level);
    /// Update the timing statistics for the current level
    void updateTimings(float extractionTimeMS);

    /// Returns the number of voxels for a specific resolution level.
    int computeVoxels(int level) const;

    /// The methods computes the first and last slice to be extracted
    bool computeThickSliceStartStop();

    /// The methods return the number of actually extracted slices
    bool extractSliceXY(VsObject & object);
    bool extractSliceXZ(VsObject & object);
    bool extractSliceYZ(VsObject & object);
    bool extractSliceOblique(VsObject & object);
    bool extractHighResData(VsObject & object);

#if 1
    /// TODO: get rid of this stuff!!

    /// Set the appropriate rendering parameters for normal resolution rendering.
    void setLowResParameters();
    /// Set the appropriate rendering parameters for high resolution rendering.
    void setHighResParameters();

    /// Returns if the node has additionaly attached high-resolution data
    bool hasHighResData() const;

public:
    /// Returns the actual number of considered thick slices
    virtual int computedThickSlices() const;

    const int * sliceBaseDims() const { return mSliceBaseDims; };

#endif

    /// Dumps additional object information into a head-up display
    virtual void dump(VsHeadUpDisplay & hud, VsHeadUpDisplay::Placement placement);
};

#endif

/// @}

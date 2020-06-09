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
#ifndef _VS_SLICE_IMPL_H
#define _VS_SLICE_IMPL_H

#define USE_EXTRACTION_FILTER

#include "VsSlice.h"
#include "VsNodeImpl.h"
#include "VsVolume.h"
#include "VsCropRegion.h"
#include "VsColorMap.h"

#include <mclib/McColor.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McLine.h>
#include <mclib/McMat3f.h>
#include <mclib/McPlane.h>
#include <mclib/McBox3f.h>

#include <mclibthreaded/McMutex.h>

#include "VsHeadUpDisplay.h"
#include "VsSliceData.h"
#include "VsQuadMesh.h"
#include "VsTexturedPolygon.h"


class VsData;
class McMat3f;


////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_API VsSliceImpl : public VsNodeImpl
{

    VS_IMPLEMENTATION( VsSliceImpl, VsNodeImpl, VsSlice )

protected:

    /// The maximum number of supported volumes
    enum { MAX_VOLUMES = 2,
           MAX_LABELS  = 256 };

    VsSlice::RenderMode         mRenderMode;
    McHandle<VsVolume>          mVolume[MAX_VOLUMES];
    int                         mPrimaryVolume;
    int                         mLevel;         // the level the application requested
    float                       mDataWindowMin[MAX_VOLUMES];
    float                       mDataWindowMax[MAX_VOLUMES];
    float                       mDataWindowHighlightMin[MAX_VOLUMES];
    float                       mDataWindowHighlightMax[MAX_VOLUMES];
    McDArray<bool>              mClipLabel[MAX_VOLUMES];
    bool                        mLabelClipping[MAX_VOLUMES];
    bool                        mInverseTF;
    McPlane                     mPlane;         // 
    bool                        mPlaneIllegal;
    McVec3f                     mFocus;         // 
    VsSlice::Orientation        mOrientation;   // 
    float                       mSliceNumber;   // this is always with respect to level-0
    float                       mThickness;
    McHandle<VsQuadMesh>        mRenderMesh;
    McHandle<VsQuadMesh>        mSampleMesh;

    McColor                     mFrameColor[2];
    unsigned int                mFrameColorIndexBound; // index of the frame color used when redering the slice bound
    unsigned int                mFrameColorIndexScout; // index of the frame color used when redering the slice scout line
    
    McVec4f                     mSelectionColor;

    McDArray<VsSlice*>          mScouts;
    McHandle<VsCropRegion>      mCropRegion[4];   
    VsSlice::Filter             mFilter;
    VsSlice::MipMode            mMipMode;
    int                         mHighResDims[3];
    McMat4f                     mRegistrationTransform;

    /// Head up display for additional informations
    int                         mHudStatsShow;
    McHandle<VsHeadUpDisplay>   mHudStats;
    VsHeadUpDisplay::Placement  mHudStatsPlacement;

    McLine                      mPickLine;
    bool                        mPickLineValid;

    /// Decoration used for rendering
    unsigned int                mDecoration;
    /// Decorations which should be always turned on/off
    static const unsigned int   mDecorationAlwaysOff;
    static const unsigned int   mDecorationAlwaysOn;

    /// Blending factor for two fused volumes.
    float                       mFusionWeight;                     

    /// Color maps used for slice rendering
    McHandle< VsColorMap >      mColorMap[MAX_VOLUMES];

    /// Colors of the material labels
    unsigned char               mLabelColors[4*MAX_LABELS];
    /// Set if the material labels have been changed
    bool                        mLabelColorsDirty;

    bool                        mIsInTouch;

    /// The extracted slice data objects
    mutable VsSliceData       * mPrimaryData[MAX_VOLUMES];
    mutable VsSliceData       * mLabelData  [MAX_VOLUMES];

    McHandle<VsSliceSelector>   mSliceSelector;
    
    /// The objects responsible for rendering slice polygons with large textures
    McHandle<VsTexturedPolygon> mTexPolygon [MAX_VOLUMES];

    /// Polygons that need to be cleant up
    McDArray<McHandle<VsTexturedPolygon> > mCleanupPolygons;

    /// Allow automatic level switching for improved interactiviy
    bool                        mLevelAutoSelect;
    /// Allow increased thick slice sampling distance for improved interactivty
    bool                        mThickStrideEnabled;
    /// Allow reduced resolution of the extracted slice for improved interactivty
    bool                        mDownsamplingEnabled;
    /// Specifies the amount of downsampling during interaction
    float                       mDownsamplingFactor;
    /// If slices should be clamped in orthographic setPlane() method
    bool                        mClampOrtho;
    /// Interrupt lowres jobs if granted time has elapsed (see Vs::OPT_INTERRUPT_LOWRES)
    bool                        mInterruptLowRes;

    /// Flags used for indicating certain dirty states
    bool                        mTexturesDirty;
    bool                        mDecorationDirty;
    bool                        mRenderModeDirty;
    bool                        mColormapDirty;
    bool                        mSliceDataDirty;

    /// Flags used to trigger a once-only initialization
    bool                        mInitOnce[MAX_VOLUMES];
    
    /// Clip fusion rendering with repect to the boundingbox of the primary volume     
    bool                        mClipFusion;

#ifdef USE_EXTRACTION_FILTER
    /// Filter used for slice extraction
    VsSlice::Filter             mExtractionFilter;
#endif
    

    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////

private:

    VSRESULT vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );
    VSRESULT vimpl_boundingBox( McBox3f & box ) const;
    virtual bool vimpl_hasHighResData() const;

public:
    virtual VSRESULT vimpl_setPlane( const McPlane & plane, const McVec3f * focus=0 );

protected:

    virtual VSRESULT vimpl_setOptioni( int inOption, int inValue );
    virtual VSRESULT vimpl_optioni( int inOption, int & outValue ) const;
    virtual VSRESULT vimpl_setOptiond( int inOption, double inValue );
    virtual VSRESULT vimpl_optiond( int inOption, double & outValue ) const;

    virtual VSRESULT vimpl_pickValue( float & outDensity, int inIndex, bool inLabel=false ) const;    
    virtual VSRESULT vimpl_pickValueLine( const McDArray<McLine>& inLineStrip, int inNumberOfResults, float * outDensities, int inIndex = 0 ) const;
    virtual VsRenderResult vimpl_render();
    virtual VSRESULT vimpl_cleanup() { assert(0); return VS_OK; };
    virtual VSRESULT vimpl_setPlane( float sliceNumber, VsSlice::Orientation ori, bool & needTouch );
    virtual VSRESULT vimpl_touch( unsigned int mask );

    void * vimpl_extension( int inEnum, void * inData);


public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    bool hasData() const;
    VSRESULT setPrimaryVolume(int inIndex = 0);
    int primaryVolume() const;
    int secondaryVolume() const;
    VSRESULT setVolume( VsVolume * volume, bool updateLabelColors = true, int inIdex = 0 );
    VsVolume * volume( int inIndex = 0 ) const;
    VSRESULT setData( VsData * data );
    VSRESULT setLevel( int level );
    int level() const;
    VSRESULT setRenderMode( VsSlice::RenderMode iMode );
    VsSlice::RenderMode renderMode() const;
    bool isRenderModeSupported( VsSlice::RenderMode iMode ) const;
    VSRESULT setDecoration( unsigned int inMask );
    unsigned int decoration() const;
    VsColorMap * transferFunction(unsigned int inTableIndex) const;
    VSRESULT setTransferFunction( VsColorMap * map, int inTableIndex );
    VSRESULT setDataWindow( float min = FLT_MIN, float max = FLT_MAX, int inIndex = 0 );
    float dataWindowMin( int inIndex = 0 ) const;
    float dataWindowMax( int inIndex = 0 ) const;
    VSRESULT setDataWindowHighlight( float min, float max, int inIndex = 0 );
    float dataWindowHighlightMin( int inIndex = 0 ) const;
    float dataWindowHighlightMax( int inIndex = 0 ) const;
    VSRESULT setLabelClippingEnabled( bool inOn, int inIndex = -1 );
    bool labelClippingEnabled( int inIndex ) const;
    VSRESULT setLabelClipped( int inLabelIndex, bool inDoClip, int inVolumeIndex = 0 );
    bool labelClipped( int inLabelIndex, int inVolumeIndex = 0 ) const;
    VSRESULT setInverseTF(bool inEnable);
    bool inverseTF() const;
    float sliceNumber() const;
    float sliceIncrement() const;
    int numSlices() const;
    int numBaseSlices() const;
    VsSlice::Orientation orientation() const;
    McPlane plane() const;
    VSRESULT swizzle( int outSwizzle[3] ) const;
    VSRESULT setFusionWeight( float inWeight );
    float fusionWeight() const;
    VSRESULT setFrameColor( const McColor & inColor );
    McColor frameColor() const;
    VSRESULT setThickness(float thickness);
    float thickness() const;
    int numScoutLines() const;
    VsSlice * scoutLine(int k) const;
    VSRESULT addScoutLine( VsSlice * slice );
    VSRESULT removeScoutLine( VsSlice * slice );
    VSRESULT clearScoutLines();
    VSRESULT setCropRegion(VsCropRegion* cropRegion, int idx=0);
    VsCropRegion * cropRegion(int idx=0) const;
    VsSlice::Filter filter() const;
    VSRESULT setFilter( VsSlice::Filter inFilter );
    VSRESULT setPickLine( const McLine& inLine );
    VSRESULT pickPoint( McVec3f & outPoint, int inIndex = 0, McVec2f * outTex = 0 ) const;
    VsData * sliceImage( int inIndex, bool extractSliceIfNecessary ) const;
    VsData * labelImage( int inIndex ) const;
    VSRESULT setThickMIPMode( VsSlice::MipMode inMode );
    VsSlice::MipMode thickMIPMode() const;
    VSRESULT setLabelColor(int inLabel, int inNumberOfColor, unsigned char * inColor);
    VSRESULT labelColor(int label, unsigned char outColor[4]) const;
    float voxelArea() const;
    VSRESULT setSampleGeometry(int inM, int inN, int inNumberOfVertices, const McVec3f* inVertices);
    VSRESULT setRenderGeometry(int inM, int inN, int inNumberOfVertices, const McVec3f* inVertices);
    VSRESULT setCurvedSlice(int inM, int inN, const McVec3f* inVertices);

#ifdef USE_EXTRACTION_FILTER
    // TODO: temporary used for testing (MWL 2007-Jan-23)
    VSRESULT setExtractionFilter( VsSlice::Filter inFilter );
    VsSlice::Filter extractionFilter() const;
#endif

    // TODO: introduced for DTI ... to be moved to VsSlice.h later
    enum Mapping {
        M_RAW            = 0, // Render slice data as is
        M_DENSITY_SCALED = 1, // Interpret slice data as density and render scaled and biased by means of the data window
        M_DENSITY_TF     = 2  // Interpret slice data as density and apply transfer function for mapping
        // ... more to come
    };

    /** Returns the chosen mapping that should be applied on the extracted slice data 
        \param  inIndex
                Index of the volume for which the slice image is to be retrieved.
        \return 
                Mapping that should be applied on the slice data of volume with 
                index \c inIndex.
    */
    Mapping mapping(int inIndex) const;

    // TODO: to be moved to VsSlice.h again - later


    VSRESULT setRegistrationTransform( const McMat4f & inMatrix );
    VSRESULT registrationTransform( McMat4f & outMatrix ) const;
    
    void setSliceSelector(VsSliceSelector* sliceSelector); 
    void setSelectionColor(const McColor &color);
    McColor selectionColor() const;

    int      renderGeometryNumPolygons( int inVolumeIndex );
//    VSRESULT renderGeometryPolygon( McDArray<McVec3f> & outPolygon, int inPolyIndex, int inVolumeIndex );
    VSRESULT renderGeometryPolygonPlanes( McDArray<McPlane> & outPlanes, McBox3f & outBoundingBox, int inPolyIndex = 0, int inVolumeIndex = 0 );


    ////////////////////////////////////////
    // internal methods
    ////////////////////////////////////////

    bool computeScoutLine( const McPlane &, McVec3f & a, McVec3f & b, int thickMode=0, float thickness=0 );
    /// Initialize label colors
    void initLabelColors();
    /// Returns orientation of PlaneSliceData for volume 0 or 1
    VsSlice::Orientation orientation(int volumeIdx) const;

    /// Update the slice data objects. 
    void updateSliceData();

protected:

    VsTexturedPolygon * findTexPolygon( VsSliceData * sData )
    {
        if ( sData==0 )
            return 0;

        int volumeIndex = sData->volumeIndex();

        if ( mTexPolygon[volumeIndex] == 0 )
        {
            VsMeta meta;
            meta.mRemotify = false;
            mTexPolygon[volumeIndex] = new VsTexturedPolygon( & meta );
        }

        return mTexPolygon[volumeIndex]; 
    }
};

#endif

/// @}

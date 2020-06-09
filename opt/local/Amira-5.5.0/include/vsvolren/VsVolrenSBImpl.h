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
#ifndef _VS_VOLREN_SB_IMPL_H
#define _VS_VOLREN_SB_IMPL_H

#include "VsVolrenImpl.h"

#include <mcgl/mcgl.h>

#include <mclib/McString.h>
#include <mclib/McDArray.h>
#include <mclib/McMat4f.h>
#include <mclib/McHandle.h>
#include <mclib/McResult.h>
#include <mclib/McVec4f.h>
#include <mclib/McVec3f.h>

#include "VsTechnique2.h"
#include "VsHeadUpDisplay.h"
#include "VsBSPImpl.h"
#include "VsResourceManager.h"


class VsCropRegion;


#define COLORMAP_TEX_WIDTH 256


////////////////////////////////////////////////////////////////////////////////
class VsVolrenSBImpl : public VsVolrenImpl
{
    VS_IMPLEMENTATION( VsVolrenSBImpl, VsVolrenImpl, VsVolren )

public:

    
    class Stats
    {
    public:
        Stats();

        void reset();
        void dump( McString & out );

        mcuint64        mFragmentsAll;      // number of drawn fragments
        mcuint64        mFragments[2][2];   // number of drawn fragments [cachemissed][resident]
        float           mTime;
        unsigned int    mFrames;
        float           mTimeFrameMin;
        float           mTimeFrameMax;
        unsigned int    mTexDim[4][3];      // dimensions of the textures
        unsigned int    mTexBits[4];        // bytes per texel
        unsigned int    mVolDim[3];         // dimensions of the volume
        mcuint64        mBytesPreloaded;
        mcuint64        mBytesUploaded;
        McString        mGLVersion;
        McString        mGLVendor;
        McString        mGLRenderer;
        int             mPreswizzled;
    };


public:
    ////////////////////////////////////////
    // members
    ////////////////////////////////////////

    /// Statistics
    Stats                       mStats;


    ////////////////////////////////////////
    // matricies
    ////////////////////////////////////////

    McMat4f                     mMatView;
    McMat4f                     mMatViewInv;
    McMat4f                     mMatProjection;
    McMat4f                     mMatViewProj;
    McMat4f                     mMatViewProjLast;
    McMat4f                     mMatViewProjInv;

    ////////////////////////////////////////
    // technique stuff
    ////////////////////////////////////////

    Vs::TechniqueAPI            mTechniqueAPI;
    bool                        mTechniqueReset;
    McHandle<VsTechnique2>      mTechnique3D   [4];
    McHandle<VsTechnique2>      mTechnique3DCap[4];
    McHandle<VsTechnique2>      mTechnique2D;

    McHandle<VsTechnique2::Params2> mParams;

    VsResourceManager::TextureInfo3d    mTexInfo[16];
    int                                 mTexInfoNum;

    int                         mTecVol2Slot[4][2]; // mapping from volume index to shader slot index (for all 4 volume combinations)

    bool                        mUsingStencil;

    ////////////////////////////////////////
    // technique uniform parameter identifiers
    ////////////////////////////////////////

    // sampler
    int mId_DENSITY;
    int mId_RGBA;
    int mId_LABEL;
    int mId_LOOKUP1D;
    int mId_LOOKUP2D;
    int mId_JITTER;
    int mId_RESULT;

    // matricies
    int mId_OBJ_TO_TEX;
    int mId_VIEW_PROJ;
    int mId_VIEW_PROJ_INV;

    // vectors
    int mId_HALFWAY_O;  // halfway vector in object space
    int mId_HALFWAY_W;  // halfway vector in world space
    int mId_LIGHT_O;    // light vector in object space
    int mId_LIGHT_W;    // light vector in world space
    int mId_DELTA_POS;
    int mId_DELTA_POS_X;
    int mId_DELTA_POS_Y;
    int mId_DELTA_POS_Z;
    int mId_PLANE_DELTA;
    int mId_LUT_SCALE_OFF;
    int mId_ALPHA_CORRECTION;
    int mId_SPECULAR;
    int mId_AMBIENT;
    int mId_THRESHOLD;
    int mId_SELECTION_COLOR;
    int mId_ISO_COLOR;
    int mId_MIN_CLIP_TEX_COORD;
    int mId_MAX_CLIP_TEX_COORD;
    int mId_MIN_TEX_COORD;
    int mId_MAX_TEX_COORD;
    int mId_GAMMA;
    int mId_DRR_SCALE;
    int mId_CAP_PLANE;
    int mId_DELTA_POS_A;
    int mId_DELTA_POS_B;
    int mId_DELTA_POS_C;
    int mId_VOXEL_SIZE_O;
    int mId_NO_JITTER;

    ////////////////////////////////////////
    //
    ////////////////////////////////////////

    int                         mNeedOffscreenRT;
    bool                        mAutoNormals;
    float                       mSliceDistanceScaleFactor[2]; // scale factor for level 0 and 1
    /**
     * When true, use mSliceDistance instead of calculating it dynamically or using
     * an implementation defined sample count.
     */
    bool                        mSliceDistanceFixed;
    float                       mSliceDistance;
    McDArray<float>             mNormalClipWidth;
    float                       mViewPortScaleFactor;
    float                       mViewPortAutoScaleRange[2];
    int                         mZBufUse;

    bool                        mTryUsePBuffer;
    bool                        mTryCopyZBuffer;
    bool                        mAutoViewScaleEnable;
    bool                        mAdaptPBufferFmt; // if true the pbuffer forced to have the same colordepth as the main context
    bool                        mTargetFloat; // true if the pbuffer has float components

    /// render target
    int                         mViewPort[4];
    mcuint32                    mTargetSizeInUse[2];  // currently used size
    mcuint32                    mTargetSizeAlloc[2];  // current size of the render target

    /// headup displays
    bool                        mHudChunksShow;
    McHandle<VsHeadUpDisplay>   mHudChunks;
    VsHeadUpDisplay::Placement  mHudChunksPlacement;
    bool                        mHudColorMapsShow;
    McHandle<VsHeadUpDisplay>   mHudColorMaps;

    
    ////////////////////////////////////////
    // statistics of the last frame
    ////////////////////////////////////////

    mcint64                     mTexMemUsedInLastHighRes; // sum number of bytes of all textures used (always full texture, even if partially filled)


    ////////////////////////////////////////
    // overload handling
    ////////////////////////////////////////

    int                         mLastLevel;
    int                         mLastUploadCount; // number of textures uploaded in the last frame
    float                       mNextViewScale;
    float                       mTargetFPS;

    ////////////////////////////////////////
    //
    ////////////////////////////////////////

    McDArray< McVec4f >         mClipPlanes;

    McDArray< int >             mPolyOff[3]; // 0,1 is ping pong. 3 are base polys
    McDArray< int >             mPolyLen[3];
    McDArray< McVec3f >         mPolyPos[3];
    int                         mPolyIdxSrc;

    McDArray< int >             mPPOff[2];
    McDArray< int >             mPPLen[2];
    McDArray< McVec3f >         mPPV[2];
    int                         mPPsrc;



    bool                        mDoJitter; // smart sampling
    bool                        mAlwaysUseLevel0; // always use level 0 if it fits into texture memory

    // id of the compute method
    int                         mWhichCompute;

    // sum of products of global clipping planes (DNF in german)
    McDArray< McDArray< McPlane > > mClipSOP;
    McDArray< McDArray< McPlane > > mClipSOPWorld;

    
    ////////////////////////////////////////
    // local information about the current volumes
    ////////////////////////////////////////

    class VsVolumeState
    {
    public:
         VsVolumeState();
        ~VsVolumeState();
        
        // material stuff
        int                     mUpdateFrameID;
        float                   mLastMinMax[2];     // extrema of all labels data windows used on last computation
        unsigned short        * mTex2d;             // 2d image containing the transfer functions for each label
        bool                    mMultiMaterial;     // true, if multiple transfer functions need to be used
        float                   mLastExposure;
        int                     mLastPlaneNum;

        enum LookupSource { S_NONE, S_CMAP, S_DRR, S_CLIP };
        LookupSource            mLastSource; // -1:unknown

        // level using for rendering
        McHandle<VsVolumeLevel> mLevel;
        int                     mLevelCurr;
        int                     mLevelSemantics;

        // brick size
        int                     mBrickSize[3];

        // transformations
        McMat4f                 mTransObj2World;
        McMat4f                 mTransWorld2Obj;
        McMat4f                 mTransWorld2Tex;

        // sum of products of clipping planes (DNF in german)
        McDArray< McDArray< McPlane > > mClipSOP;
        McDArray< McDArray< McPlane > > mClipSOPWorld;


        // temporary
        bool                    mClipMask[256];
    };

    VsVolumeState       mVolState[2];


public:

    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////

    virtual McResult renderClear( McVec4f & inRGBA ) { return McOK; }

    virtual McResult renderSlices( McDArray<int> & inOffsets, McDArray<int> & inLengths, McDArray<McVec3f> * inAttribs1, McDArray<McVec3f> * inAttribs2, McDArray<McVec3f> * inAttribs3 )  { return McOK; }
    virtual McResult renderSlices( McDArray<float> & inGeometry )  { return McOK; }

    virtual McResult renderApiAttach()          { return McOK; }

    virtual McResult renderApiDetach()          { return McOK; }

    virtual bool     renderApiIsAttached()      { return McOK; }

    virtual McResult renderTargetAvailable()    { return McOK; }

    virtual McResult renderTargetCreate()       { return McOK; }

    virtual McResult renderTargetRelease()      { return McOK; }

    virtual bool     renderTargetSupportsZBuffer()  { return false; }

    virtual McResult renderTargetResultTexture( GLuint & outTex, float outMaxUV[2] )    { outTex=0; return McOK; }

    virtual McResult colorMapSet( int inVolumeIndex, int inUnit, int * inDims, int inNumChans, int inNumBytesPerChan, int inFilter )  { return McOK; }

    virtual McResult colorMapBind(int inVolumeIndex, int inUnit, int inNumDims ) { return McOK; }

    virtual McResult jitterMapBind(int inUnit)  { return McOK; }

    virtual McResult renderPresent()            { return McOK; }

    virtual McResult renderInit()               { return McOK; }

    virtual McResult renderBegin()              { return McOK; }

    virtual McResult renderEnd()                { return McOK; }

    virtual McResult renderBrickBegin()         { return McOK; }

    virtual McResult renderSubBoxBegin()        { return McOK; }

    virtual McResult renderSubBoxEnd()          { return McOK; }

    virtual McResult clipPlanesAdd( McDArray< McVec4f > & inClipPlanesO, McDArray< McVec4f > & inClipPlanesW, McDArray< McVec4f > & inClipPlanesC ) { return McOK; }

    virtual McResult clipPlanesAdd( McHandle<VsCropRegion> inCrop ) { return McOK; }

    virtual McResult clipPlanesDisable()         { return McOK; }


    ////////////////////////////////////////
    // additional internal interface
    ////////////////////////////////////////
private:
    // void computeNumSlices();
    void classify();
    void computeDeltaV( const McVec3f & p, const McVec3f & d, McVec3f & res );
    void statsInit();
    void statsDump( McString & out );
    VSRESULT updateMaterials( int inVolumeIndex, int inUnit );


    static VSRESULT bspMergeLevel( VsBSP & ioBSP, VsVolumeLevel & inLevel, McMat4f & inObject2World, int inVolumeIndex );
    static VSRESULT bspMergeBSP( VsBSP & ioDstBSP, VsBSP & inSrcBSP );
    static VSRESULT bspDraw( VsBSP & inBSP );
    static VSRESULT bspDrawCell( VsBSP & bsp, char * rCellCurr );
    static VSRESULT bspAddCellVertsToPlane( VsBSP & inBsp, char * rCell );
    static VSRESULT bspAppendColumns( VsBSP & inBsp );

    VSRESULT bspPrepare( 
        VsBSP & inBsp
    ,   int     inVolumeIndex           // -1 for all
    ,   bool    inDeleteOpenCells
    ,   bool    inComputePlaneROI
    ,   bool    inComputeCenter
    ,   bool    inComputeMaskAndBrickIdx
    ,   bool    inDeleteClippedCellsAllVolume
    ,   bool    inDeleteClippedCellsPerVolume
    ,   bool    inDeleteOutOfVolumeCells
    );

protected:
    /// sample the volume - invoke render methods
    VsRenderResult  compute2();
    void setProjectionMatrix( const McMat4f & inMat );
    void setModelViewMatrix( const McMat4f & inMat );
    int volumeStateCompute( int inLevelIdx = -1 );

    VSRESULT compute2prepareTechnique( 
        int             inVolumeMask
    ,   VsTechnique2  * inTechniqueCurr
    ,   VsTechnique2  * inTechniqueNext
    ,   bool            inDoJitter
    ,   VsBrick      ** inBricks
    ,   McVec4f       * outLutScaleOff
    );

public:
    ////////////////////////////////////////
    // external non-virtual interface
    ////////////////////////////////////////

private:
    ////////////////////////////////////////
    // virtual interface
    ////////////////////////////////////////

protected:

    virtual VSRESULT    vimpl_setOptioni( int inOption, int inValue );
    virtual VSRESULT    vimpl_setOptiond( int inOption, double inValue );
    virtual VSRESULT    vimpl_optioni( int inOption, int & outValue ) const;
    virtual VSRESULT    vimpl_optiond( int inOption, double & outValue ) const;
    virtual VsRenderResult vimpl_render();
    virtual VSRESULT    vimpl_cleanup();
    virtual VSRESULT    vimpl_setVolume( VsVolume * volume, int inVolumeIndex );
};


////////////////////////////////////////
// additional BSP columns
////////////////////////////////////////

// offsets
extern int o_cell_centerPos;
extern int o_cell_levelMask;
extern int o_cell_brick0;
extern int o_cell_brick1;

extern int o_plane_verts;

extern int o_surf_centerPos;

// IDs
extern int i_cell_centerPos;
extern int i_cell_levelMask;
extern int i_cell_brick0;
extern int i_cell_brick1;

extern int i_plane_verts;

extern int i_surf_centerPos;

////////////////////////////////////////


#endif

/// @}

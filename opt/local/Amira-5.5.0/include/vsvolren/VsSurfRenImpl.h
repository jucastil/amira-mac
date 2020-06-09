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
#ifndef _VS_SURFREN_IMPL_H
#define _VS_SURFREN_IMPL_H

#include "VsSurfRen.h"
#include "VsTechnique2.h"
#include "VsVolren.h"
#include "VsResourceManager.h"

#include "VsNodeImpl.h"


////////////////////////////////////////////////////////////////////////////////
class VsSurfRenImpl : public VsNodeImpl
{
    VS_IMPLEMENTATION( VsSurfRenImpl, VsNodeImpl, VsSurfRen )

    /// The maxumum number of depth peeling passes for order independent transparency
    enum {
        MAX_PEEL_PASSES = 5
    };

    /// Type for rendering optimizations
    enum Optimization {
        /// Use plain OpenGL rendering
        OP_NONE          = 0,
        /// Use OpenGL display lists
        OP_DISPLAY_LISTS = 1,
        /// Use Vertex Buffer Objects
        OP_VBOS          = 2
    };

public:
    struct SurfRecord {
        /// The surface to be rendered
        McHandle<VsSurface>       mSurface;
        /// Something in the surface has changed and we need to recreate caches
        bool                      mDirty;
        /// Should the surface be rendered.
        bool                      mSurfaceVisible;
        /// Display list
        VsResourceManager::Handle mListId;
        /// Vertex buffer object
        VsResourceManager::Handle mVBOId[2];
        /// Has the display list/VBO creation failed due to out of memory error
        bool                      mOutOfMemory;
        /// Default constructor
        SurfRecord() { 
            mSurface        = 0;
            mDirty          = true;
            mSurfaceVisible = true; 
            mListId         = VsResourceManager::H_UNDEF;
            mVBOId[0]       = VsResourceManager::H_UNDEF;
            mVBOId[1]       = VsResourceManager::H_UNDEF;
            mOutOfMemory    = false;
        };
    };

    /// The surface to be rendered
    McDArray<SurfRecord>            mSurfaces;
    /// Which mode to use
    Optimization                    mOptimization;

    // Shader and related objects
    Vs::TechniqueAPI                mTechniqueAPI;
    McHandle<VsTechnique2>          mDepthPeelTech;
    McHandle<VsTechnique2>          mRestoreFBTech;
    McHandle<VsTechnique2::Params2> mDepthPeelParams;
    VsResourceManager::Handle       mColorTex[MAX_PEEL_PASSES];
    VsResourceManager::Handle       mDepthTex[MAX_PEEL_PASSES];
    // The buffers for depth and color of the background
    VsResourceManager::Handle       mBackGroundDepth;
    VsResourceManager::Handle       mBackGroundColor;
    // Ids for shader programs variables
    int                             mId_DEPTH_TEX;
    int                             mId_COLOR_TEX;
    int                             mId_TEX_SIZE;
    int                             mId_DEPTH_MULT;
    int                             mId_COLOR_MULT;
    int                             mId_VIEW_DIR;
    // The number of peeling passes - of 0 if peeling is switched off
    int                             mNumPeels;
    /** Index of the first/last peeling layer that has not been composited during rendering().
        set to -1 if no layer is pending */
    int                             mFirstPendingPeelLayer;
    int                             mLastPendingPeelLayer;
    // The slave object(s) to be composited with the surface
    McHandle<VsNode>                mSlaveNode;
    // Ths current slave sorting mode
    VsSurfRen::SlaveSorting         mSlaveSorting;

public:
    
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////

private:

    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    virtual VSRESULT        vimpl_setSurface( VsSurface * inSurface, int inIndex );
    virtual VsSurface *     vimpl_surface( int inIndex ) const;
    virtual int             vimpl_numSurfaces() const;
    virtual VSRESULT        vimpl_clearSurfaces();
    virtual VSRESULT        vimpl_setSurfaceVisible( bool inFlag, int inIndex );
    virtual bool            vimpl_surfaceVisible( int inIndex ) const;
    virtual VSRESULT        vimpl_setNumPeels( int inNumPeels );
    virtual int             vimpl_numPeels() const;
    virtual VSRESULT        vimpl_setSlaveNode( VsNode * inSlaveNode );
    virtual VSRESULT        vimpl_setSlaveSorting( VsSurfRen::SlaveSorting inSlaveSorting );
    virtual VsSurfRen::SlaveSorting
                            vimpl_slaveSorting() const;
    virtual VSRESULT        vimpl_setOptioni( int inOption, int inValue );
    virtual VSRESULT        vimpl_setOptiond( int inOption, double inValue );
    virtual VSRESULT        vimpl_optioni( int inOption, int & outValue ) const;
    virtual VSRESULT        vimpl_optiond( int inOption, double & outValue ) const;
    virtual void *          vimpl_extension( int inEnum, void * inData );
    VSRESULT                vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );
    virtual VsRenderResult  vimpl_render();
    virtual VSRESULT        vimpl_cleanup();
    VSRESULT                vimpl_boundingBox( McBox3f & box ) const;

    ////////////////////////////////////////
    // local methods
    ////////////////////////////////////////
    void classifySurfaces( McDArray<SurfRecord*> & opaqueList, McDArray<SurfRecord*> & transparentList);

    void renderSurfaceList( McDArray<SurfRecord*> & surfList, VsSurfRenImpl::Optimization & optimization);
    void renderSurfaceRaw( VsSurface * surf );

    void initializeTextures(int sizeX, int sizeY);
    void restoreFrameBuffer(int xOffset, int yOffset, int xSize, int ySize, int xTexSize, int yTexSize);

    void renderPendingLayer();
    void renderPeelLayers(int inMinLayer, int inMaxLayer, bool inBackground,
                          int inXOffset, int inYOffset, int inXSize, int inYSize, 
                          int inTexSizeX, int inTexSizeY);
};

#endif

/// @}

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
#ifndef _VS_GL_SLICE_IMPL_H
#define _VS_GL_SLICE_IMPL_H

#include "VsSliceImpl.h"

#include "VsViewState.h"
#include "VsTechnique2.h"
#include "VsCropRegion.h"

#include <mclib/McPlane.h>
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>


////////////////////////////////////////////////////////////////////////////////
class VsGLSliceImpl : public VsSliceImpl
{

    VS_IMPLEMENTATION( VsGLSliceImpl, VsSliceImpl, VsSlice )

protected:

    /// The effective level used in the previous frame.
    int                            mLastLevel;
    
    /// The average rendering time
    float                          mAvgRenderTimeMS;
    /// The average time for texture initialization per pixel
    float                          mAvgSetupTimePerPixelNS;

    /// Shader related variables
    bool                           mTechniqueReset;
    McHandle<VsTechnique2>         mTechniqueSlice;
    McHandle<VsTechnique2>         mTechniqueSliceRGB;
    McHandle<VsTechnique2>         mTechniqueContour;
    McHandle<VsTechnique2>         mTechniqueRegion;
    McHandle<VsTechnique2>         mTechniqueSelection;
    McHandle<VsTechnique2::Params2> mParams;
    Vs::TechniqueAPI               mTechniqueAPI;

    /// Diverse color map resources
    unsigned int                   mLabelColorsId;
    unsigned int                   mColorMapIds[MAX_VOLUMES];

    bool                           mDrawScoutsColored;

    McDArray< McVec3f >            mCropBorderLines[4];
    McDArray< McVec3f >            mCropOutsideTriangles;
    unsigned int                   mBSPCropRegionTouchNumber[4];
    void                         * mBSPCropRegion[4]; // never dereference this
    McPlane                        mBSPBasePlane[4];

    McDArray<McPlane>              mScoutPlanes; // Internal buffer for recalling scoutlines on start of rendering.
    McDArray<McColor>              mScoutColors;
    McDArray<float>                mScoutThickness;

    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////

protected:

    virtual VsRenderResult vimpl_render();

private:

    void              * vimpl_extension( int inEnum, void * inData);
    VSRESULT            vimpl_cleanup();
    virtual VSRESULT    vimpl_setOptioni( int inOption, int inValue );
    virtual VSRESULT    vimpl_optioni( int inOption, int & outValue ) const;


    ////////////////////////////////////////
    // internal methods
    ////////////////////////////////////////

protected:

    // ----------------------------------------------
    // Compute and Render methods for different modes
    // ----------------------------------------------
    /// Compute single slice
    int computeSingleSlice(float & extractionTimeMS, float & setupTimeMS);
    /// Compute colored slice - density to be mapped via a transfer function
    int computeColoredSlice(float & extractionTimeMS, float & setupTimeMS);
    /// Compute native rgb-slice - 3 channels, without transfer function mapping
    int computeRawColoredSlice(float & extractionTimeMS, float &setupTimeMS);
    /// Compute multi volume slice
    int computeFusionVolumeSlice(float & extractionTimeMS, float & setupTimeMS);

    /// Compute for decoration like label contours or label regions
    int computeSliceDecoration(float & extractionTimeMS, float & setupTimeMS);


    /// Render single slice
    int renderSingleSlice();
    /// Render colored slice
    int renderColoredSlice();
    /// Render multi volume slice
    int renderFusionVolumeSlice();

    /// Render decoration like label contours or label regions
    int renderSliceDecoration();
    // ----------------------------------

    /// Render textured slice
    void renderSlicePolygon(
        VsSliceData   * inDataPrimary
    ,   VsSliceData   * inDataLabel
    ,   unsigned int    flt
    ,   float           dataWindowMin
    ,   float           dataWindowMax
    ,   McHandle<VsTechnique2> technique
    ,   int             colormapId
    ,   bool            useTexture
    );


    /// Render bounding box and scoutline.
    void renderWireframe(bool scoutsInColor, McDArray<unsigned char>* iostream, bool doRender, VsViewState& ioState);
    /// Uploads slice data to a texture map - the time for upload is reported in \c setupTimeMS.
    void reinitializeTexture(VsSliceData & sData, bool scaleBias, unsigned int flt,
                             float dataWindowMin, float dataWindowMax, float & setupTimeMS);
                             

private:

    /// Called by render() and overlayVectorData to collect all primitives to render
    void computeRenderElements(bool darkenCroppedArea, VsViewState & inState);

    /// Update internal timing statistics based on the values of the current frame
    void updateTimings(float setupTimePerPixelNS, float renderTimeMS);
    /// Adjust rendering parameters, such that the node renderes within a given time budget.
    void adjustQuality(VsSliceData & sData);

    /// Render the crop region including decoration. 
    void renderCropRegion(bool darkenCroppedArea, bool renderLines, VsViewState& ioState);
    void renderBoundingBox(VsViewState& ioState);
    void renderBoundingBoxOverlay(VsViewState& ioState);
    void renderScoutLines(VsViewState& ioState);

    /// Initializes the label colors texture
    void initLabelColorsTexture();
    /// Initializes the color map textures
    void initColorMapTextures();
    /// Initializes fragment shaders
    void initializeTechniques();

#if 0
    /// Calculate pixel offset in texture space
    void calcPixelOffset( VsSliceData & sData, double * outOffX, double * outOffY );
#endif

private:

    ////////////////////////////////////////
    // technique2 parameter identifeer
    ////////////////////////////////////////

    // textures
    int mId_RGBA;
    int mId_DENSITY;
    int mId_LABEL;
    int mId_LOOKUP_DENSITY;
    int mId_LOOKUP_LABEL;

    // matricies
    int mId_VIEW_PROJ;

    // vectors
    int mId_COLOR_SELECTION;
    int mId_COLOR_HIGHLIGHT;
    int mId_DW_HIGHLIGHT;


    int mId_CONTOUR_THICKNESS;
    int mId_LUT_SCALE_OFF;

};

#endif


/// @}

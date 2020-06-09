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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_RENDER_AREA_H
#define HX_RENDER_AREA_H

#include <mclib/McVec2f.h>
#include <mclib/McBox2f.h>
#include <Inventor/SbColor.h>
#include <Inventor/actions/SoGLRenderAction.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class HxRenderAreaPrivate;

/** Common base class of HxViewer and HxRemoteRenderArea. The class
    HxRemoteRenderArea is a simple graphics window which is used to
    represent additional screens in AmiraVR. A HxRemoteRenderArea is
    always associated with the Amira main viewer, i.e., it displays
    all geometry which is visible in this viewer. There are only few
    attributes which can be specified separately for instances of
    HxViewer and HxRemoteRenderArea. These attributes are encapsulated
    by this class (HxRenderArea), which is a common base class for
    HxViewer and HxRemoteRenderArea. The attributes include the
    subregion for tiled rendering, settings for soft edge blending,
    and the background mode (but not the background colors - these
    are taken from the main viewer). */
class HXCORE_API HxRenderArea
{
  public:
    /// Enumerates window edges for soft edge blending.
    enum {
        // Left edge
        LEFT=0,
        // Right edge
        RIGHT=1,
        // Bottom edge
        BOTTOM=2,
        // Top edge
        TOP=3
    };

    /// Camera modes used in setCameraMode().
    enum CameraMode {
        /// Monoscopic view, mono visual
        MONOSCOPIC=0,
        /// Left eye, monoscopic visual
        LEFT_VIEW=1,
        /// Right eye, monoscopic visual
        RIGHT_VIEW=2,
        /// Both eyes, active stereo visual
        ACTIVE_STEREO=3
    };

    /// Background patterns.
    enum BackgroundMode {
        /// Simple monochrome background.
        BG_DEFAULT=0,
        /// Horizontal color gradient.
        BG_GRADIENT=1,
        /// Checkerboad pattern, useful for transparent displays.
        BG_CHECKERBOARD=2,
        /// An arbitrary image is used as background.
        BG_IMAGE=3,
        /// Monochrome background using color2
        BG_UNIFORM_REVERSE=4,
        /// Gradient pattern with reversed colors
        BG_GRADIENT_REVERSE
    };

    /** Returns the render area being rendered by the calling thread.
        The method should only be called during rendering, i.e., in a
        derived Open Inventor node or in an SoCallback node. */
    static HxRenderArea* getCurrent();

    /** Enables tiled rendering. If tiled rendering is enabled the
        render area renders a subregion of a bigger virtual viewport.
        The subregion is specified by a box between (0,0) and (1,1).
        In order to disable tiled rendering use (0,1,0,1) as tile. */
    virtual void setTile(const McBox2f& inTile);

    /** Returns the subregion used for tiled rendering. If tiled
        rendering is disbled the box is (0,1,0,1), i.e., it covers
        the complete virtual viewport region. */
    const McBox2f& getTile() const;

    /** Enables soft edge blending for a particular edge. Edges should
        be indicated by LEFT, RIGHT, BOTTOM, and TOP. For each edge an
        overlap factor between 0 and 1 can be specified. A value of 0
        means that soft edge blending is disabled. */
    virtual void setSoftEdgeOverlap(int whichEdge, float overlap);

    /// Returns the soft edge overlap factor for the specified edge.
    const float& getSoftEdgeOverlap(int whichEdge) const;

    /** Adjusts the soft edge gamma value for a particular edge. The
        gamma value determines how fast the soft edges fades from bright
        to dark. For most projectors a value bigger than one need to be
        specified. */
    virtual void setSoftEdgeGamma(int whichEdge, float gamma);

    /// Returns the soft edge gamma value for the specified edge.
    const float& getSoftEdgeGamma(int whichEdge) const;

    /** Sets camera modes for (passive) stereo viewing. If mode is MONOSCOPIC,
        monoscopic viewing is used. If mode is LEFT_VIEW the left eye view of a
        stereo image is rendered. If mode is RIGHT_VIEW the right eye view of a
        stereo image is rendered. If mode is ACTIVE_STEREO OpenGL stereo is
        activated. This method is used by AmiraVR. Other stereo modes can be
        chosen using the Open Inventor SoStereoViewer interface. */
    virtual void setCameraMode(CameraMode mode);

    /// Returns the current camera mode.
    CameraMode getCameraMode() const;

    /** Returns the camera position in world coordinates (object space).
        This method returns the correct camera position even in AmiraVR
        mode with head-tracking enabled. In this mode, the camera of a
        viewer is not used but the projection matrix is set directly by
        the AmiraVR module. */
    const SbVec3f& getCameraPosition() const;

    /** Sets the camera position in world coordinates (object space).
        This method is called by the AmiraVR module in order to set
        the correct camera position in VR mode. */
    void setCameraPosition(const SbVec3f& cameraPosition);

    /** Specifies the background mode. For each render area a separate
        background mode can be specified. The actual background colors are
        stored in the HxViewer child class. Instances of HxRemoteRenderArea
        (the other child class of HxRenderArea) take the background color
        from the amira main viewer. */
    virtual void setBackgroundMode(BackgroundMode mode);

    /// Returns current background mode.
    BackgroundMode getBackgroundMode() const;

    /**  Returns pointer to user data (internal use only). This method
        is used by AmiraVR. */
    void* getUserData() const;

    /**  Sets pointer to user data (internal use only). This method is
        used by AmiraVR. */
    virtual void setUserData(void* d);

    // Renders a semi-transparent soft edge (internal use only).
    void renderSoftEdge();

    /// Returns the width of the graphics window in pixels.
    virtual int width() const;

    /// Returns the height of the graphics window in pixels.
    virtual int height() const;

    /// Makes the graphics window visible and raises it to the front.
    virtual void show();

    /// Makes the graphics window invisible.
    virtual void hide();

    /** In VR mode, returns the screen ID that corresponds to this render area in the
        VR config file.
        In "standard" Avizo mode, return the render area number.
        */
    int  getRenderAreaID();

    /// Specifies the ID of this render area (internal use only).
    void setRenderAreaID(int id);

  protected:
    HxRenderArea(int renderAreaID=0);

    virtual ~HxRenderArea();

    HxRenderAreaPrivate* d;

    /**
     *  To set the render area element within the OIV state.
     *  This method must be called from an an OIV SoCallBack node.
     *  Internal use only.
     */
    static void setRenderAreaElement(void *userData, SoAction *action);
};


/**
    An implementation of this class allows post processing,
    because the scene will be rendered between the methods
    begin() and end().

    In the implementation of a derived class, a frame buffer object
    (fbo) could be bound in the begin() method, resulting in the scene
    being rendered directly into the fbo instead of into the frame
    buffer.  Rendering directly into an fbo improves both quality and
    speed.  In the end() method, the rendered image can be manipulated
    using post processing shaders, which could work on the image only
    but also employ the depth buffer.
*/
class HXCORE_API SxGLPostRenderer
{
  public:

    virtual ~SxGLPostRenderer();
    virtual void begin(unsigned int contextID) = 0;
    virtual void end(unsigned int contextID) = 0;

  protected:

    SxGLPostRenderer() {};

  private:

    SxGLPostRenderer(const SxGLPostRenderer &);
    SxGLPostRenderer & operator=(const SxGLPostRenderer &);
};


/// @if UNDOCUMENTED

#pragma warning(push)

// non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
#pragma warning(disable:4275)

class HXCORE_API SxGLRenderAction : public SoGLRenderAction {
  public:
    SxGLRenderAction(HxRenderArea* ra);
    virtual void apply(SoNode* node);
    HxRenderArea* getRenderArea() const { return renderArea; }
    int renderCount;

    /**
        Sets a post processing renderer.  Without setting a
        renderer the apply method will render the scene graph in
        the default frame buffer.
    */
    void setPostRenderer(SxGLPostRenderer* renderer);

    /**
        Removes the post renderer so that the scene graph will
        be rendered in the default frame buffer.
    */
    void unsetPostRenderer();

  protected:
    SxGLPostRenderer* postRenderer;
    HxRenderArea* renderArea;
};

#pragma warning(pop)

/// @endif

#endif

/// @}

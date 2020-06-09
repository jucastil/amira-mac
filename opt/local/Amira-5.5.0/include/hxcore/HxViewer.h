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
#ifndef HX_VIEWER_H
#define HX_VIEWER_H

#include <tcl.h>
#include <hxcore/HxRenderArea.h>
#include <hxcore/HxViewerBase.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/components/stereo/SoBaseStereo.h>


#define HX_TILED_RENDERING

class QWidget;
class QEvent;
class QImage;
class QMenu;
class QPushButton;
class QToolButton;
class QxViewer;
class McBox2f;
class McTypeInfo;
class HxColorEditor;
class HxCameraPath;
class SoSelection;
class SoSceneManager;
class SoDirectionalLight;
class HxTimeCompositingController;

/** Amira's customized viewer class. This class encapsulated a customized
    Open Inventor examiner viewer (QxViewer, derived from SoQtExaminerViewer).
    The class allows amiraDev users to access the viewer without needing to
    install any Qt headers. It is simply a wrapper for QxViewer.
*/
class HXCORE_API HxViewer : public HxViewerBase, public HxRenderArea 
{
    QxViewer* _viewer;

  public:
    /** List of possible drawing styles. This enumeration type is used in
        setDrawStyle() and getDrawStyle(). */
    enum DrawStyle {
        /// Standard appearance
        VIEW_AS_IS,
        /// Render only the frontmost lines
        VIEW_HIDDEN_LINE,
        /// Render without textures
        VIEW_NO_TEXTURE,
        /// Render low complexity and no texture
        VIEW_LOW_COMPLEXITY,
        /// Wireframe draw style
        VIEW_LINE,
        /// Point draw style
        VIEW_POINT,
        /// Bounding box draw style
        VIEW_BBOX,
        /// Low complexity wireframe + no depth clearing
        VIEW_LOW_RES_LINE,
        /// Low complexity point + no depth clearing
        VIEW_LOW_RES_POINT,
        /// Forces the INTERACTIVE draw style to match STILL
        VIEW_SAME_AS_STILL
    };

    /// Indicates to what type of rendering a draw style applies to.
    enum DrawType {
        /// Applies to static rendering
        STILL,
        /// Applies to rendering while interactive viewing
        INTERACTIVE
    };

    /// List of different buffering types
    enum BufferType {
        /// Single buffer
        BUFFER_SINGLE,
        /// Double buffer
        BUFFER_DOUBLE,
        /// Double buffer while interactive viewing
        BUFFER_INTERACTIVE
    };

    /** Enumerates different camera types. This type is used in
        getCameraType() and setCameraType(). */
    enum CameraType {
        /// An orthographic camera.
        ORTHOGRAPHIC_CAMERA = 0,
        /// A perspective camera.
        PERSPECTIVE_CAMERA  = 1
    };

    /// Enumerates rotation axes when calling rotate().
    enum RotAxis {
        /// Rotation around x-axis.
        ROT_X=0,
        /// Rotation around y-axis.
        ROT_Y,
        /// Rotation around z-axis.
        ROT_Z,
        /// Rotation around x, y, or z, depending on viewer orientation.
        ROT_MOST_VERTICAL,
        /// Rotation around camera up direction.
        ROT_UP_DIR,
        /// Rotation around camera view direction.
        ROT_VIEW_DIR
    };

    /** Constructor. @c id indicated the Amira viewer id. The id of
        the main viewer is 0. @c parent must not be NULL. Usually, amira
        viewers are created as a child of a QxViewerPanel's centralWidget().
        However, any other Qt widget can be used as well. */
    HxViewer(QWidget* parent, const char* name=0, int id=0);

    /// Destructor.
    ~HxViewer();

    /** Returns true is viewer is in interactive mode (mouse button pressed). */
    int isInteractive() const;

    /** Returns the cuurent draw type (INTERACTIVE or STILL). */
    DrawType getDrawType() const { return isInteractive() ? INTERACTIVE : STILL; }

    /** Returns draw style depending on current draw type. */
    DrawStyle getDrawStyle();

    /** Returns the root of the scene graph. The returned node is a separator
        node containing the complete scene graph of the viewer, including
        any nodes added by the viewer itself, e.g., the camera or the head
        light. */
    SoNode* getSceneRoot();

    /** Returns the user-defined part of the scene graph. The returned node
        is the same node which has been set using setSceneGraph(). It does
        not contain the nodes added by the viewer itself. */
    SoNode* getSceneGraph();

    /** Adds a node into a special group which is traversed before any
        other ordinary geometry. In particular, Amira inserts lights
        into this group. The header group is a group rather then a
        separator. This allows nodes inserted in the header group to
        make changes affecting the whole scene. */
    void addHeaderNode( SoNode * node );

    /// Removes a node added by addHeaderNode().
    void removeHeaderNode( SoNode * node );

	/** Adds a node into a special group which is traversed after any
        other ordinary geometry. */
    void addTailNode( SoNode * node );

    /// Removes a node added by addTailNode().
    void removeTailNode( SoNode * node );

    /** Adds a node into a group which is traversed before any other
        geometry including header nodes (see above). In contrast to
        header nodes root nodes are not taken into account when
        computing the scene's bounding box. This method can be used
        for example in a head tracking module where the environment
        should be displayed, but not be affect viewAll(). */
    void addRootNode( SoNode * node );

    /// Removes a node added using addRootNode().
    void removeRootNode( SoNode * node );

    void setBackgroundMode(BackgroundMode mode);

    /** Sets the primary background color. This color is used if the
        background mode is set to BG_DEFAULT. It is used as the upper
        color if the background mode is set to BG_GRADIENT. */
    void setBackgroundColor(const SbColor& color);

    /// Returns the primary (upper) background color.
    const SbColor& getBackgroundColor() const;

    /** Sets the secondardy background color. This color is used if the
        background mode is set to BG_UNIFORM_REVERSE. It is used as the
        lower color if the background mode is set to BG_GRADIENT. */
    void setBackgroundColor2(const SbColor& color);

    /// Returns the secondary (lower) background color.
    const SbColor & getBackgroundColor2() const ;
    
    /// Reads a background image from file.
    int setBackgroundImage(const char* filename);

    /** Sets a background image. The width of the image, its height, as
        well as the number of color channels must be stored in dims[0],
        dims[1], and dims[2], respectively. The actual image data must
        be stored in @c data. The image pixels must be stored in
        contiguous order without any padding between the lines. Only
        8-bit data is supported. The number of color channels must be
        either 1 (greyscale data), 3 (rgb data), or 4 (rgba data). The
        image data is copied into an internal buffer. */
    void setBackgroundImage(const int dims[3], const unsigned char* data);

    /** Reads a stereo background image from one or two fles. If two file
        names are specified, it is assumed that these files represent the
        left eye view and the right eye view, respectively. If only one
        file name is specified, it is assumed that this file contains both
        the left eye view and the right eye view side by side. Such images
        are for example generated by the amira movie maker module. */
    int setStereoBackgroundImage(const char* left, const char* right=0);

    /** Sets a stereo background image. @c dims has the same meaning as in
        setBackgroundImage(). For the image data the same remarks apply as
        in setBackgroundImage(). If both @c left and @c right are specified
        two separate images for the left and right eye view are assumed. If
        only @c left is specified, it is assumed that this image contains
        both the left eye view and the right eye view side by side. */
    void setStereoBackgroundImage(const int dims[3],
        const unsigned char* left, const unsigned char* right=0);

    /** Returns the current background image file. If the background image
        has been been read from an image file the name of this file is
        returned in @c left. @c right is set to the name of the right
        image file. If only one image file has been set but this is
        interpreted as a stereo image, @c stereo is set to 1. */
    void getBackgroundImage(const char*& left, const char*& right, bool& stereo);

    /** Sets a new camera. The method remembers all connections attached to
        the position and orientation fields of the previous camera, and
        reattaches them to the position and orientation fields of the new
        camera. This is required for lights defined in camera space. */
    void setCamera(SoCamera* cam);

    /** Sets the camera type. This method can be used to set an orthographic
        or a perspective camera. */
    void setCameraType(CameraType type);

    /// Returns the current camera type.
    CameraType getCameraType();

    /// Checks if currently a perspective camera is active.
    bool hasPerspectiveCamera(); 

    /** Sets camera in dependence of the given time. To use this method you
	have to set a camera path first using setCameraPath.*/
    void setCameraPt( float time );

    /// Set camera's position
    void setCameraPosition( const SbVec3f& pos );

    /// Set camera's orientation
    void setCameraOrientation( const SbRotation& rot );

    /// Check whether camera path is still in object pool, unref if necessary.
    void verifyCameraPath();

    /// Set camera path.
    void setCameraPath( HxCameraPath * which );

    // ???
    void initCameraPath();

    // rotateCamera() is made virtual since oiv 4.0.6
    // virtual void rotateCamera (const SbRotation & rot);

    /** Turn on/off auto-animating of the camera. Animation is done using the
	actually set camera path. Use setCameraPath() to set the camera path
	for the viewer.*/
    void autoAnimateCamera(bool);
    
    /// Is animating turned on ?
    int isAnimating(); 
  
    /// Sets logo to be displayed in the overlay planes.
    void setLogo( const char* ivfile );

    /// Switch for displaying a safety frame for video grabbing
    void setVideoFrame( bool onOrOff );

    /** Write scene graph as an Open Inventor file. Note that many Amira
        modules use their own customized Open Inventor nodes. Although these
        nodes can be written into a file other applications can't interprete
        these nodes. Therefore, this export method should only be used for
        special purposes, e.g. for debugging. If @c rootNodes is true, nodes
        added by the viewer, e.g., the camera or the head light, will be
        included in the file. */
    void saveScene(const char* filename, bool binary=false, bool rootNodes=false);

    /** Write scene graph as an VRML file. @c version should be either 1 or
        2, indicating if a VRML 1 or a VRML 2 file should be written. If @c
        rootNodes is true, nodes added by the viewer, e.g., the camera or the
        head light, will be included in the file. */
    void saveSceneAsVRML(const char *filename, int version=1, bool binary=false, bool rootNodes=false);

    void setPanel(QxViewerPanel* panel);

    QxViewerPanel* getPanel() const;

    /// Select axial view.
    void viewX( int reverse=0 );

    /// Select frontal view.
    void viewY( int reverse=0 );

    /// Select sagittal view.
    void viewZ( int reverse=0 );

    /// Rotate camera around some axis. 
    void rotate( RotAxis axis, float angle );

    /// Tcl-command interface.
    int parse( Tcl_Interp * interpreter, int argc, char ** argv );
    
    /// Set the viewer's scene graph.
    void setSceneGraph(SoNode*);

    /// Get position of viewer's frame window.
    SbVec2s getPosition();

    /// Set position of viewer's frame window.
    void setPosition(int x,int y);

    /// Get size of viewer's frame window.
    SbVec2s getSize();

    /// Set size of viewer's frame window.
    void setSize( const SbVec2s& size );

    SbVec2s getGlxSize() const; 

    // Show viewer.
    void show(bool raise = true);

    /// Hide viewer.
    void hide();

    // Is viewer visible?
    int isVisible();

    /* This method is obsolete. It was used to show or hide the old-style
       viewer decoration. The method is provided for compatibility reasons
       only. It does nothing. */
    void setDecoration( int flag );

    /// A little performance test. The result is written to @c theMsg.
    float performanceTest( int verbose, int numFrames );

    /// Ask whether or not the performance test is currently performed.
    bool inPerformanceTest( void );

    /// returns 1 if the specified stereo type is supported 
    int hasStereoCapability( const SoBaseStereo::StereoViewType stereoType = SoBaseStereo::OPENGL_STEREO );

    /// Sets slave viewer.
    void setSlaveViewer( int which );

	/// Init frame grabber
	void initFrameGrabber(const McTypeInfo *grabberClassTypeId);

    /// Create snapshot of viewer window, pops up dialog if filename is null.
    void snapshot( const char* filename=0 );

    /** Snapshot method with more arguments. If @c numTilesX or
        @c numTilesY is bigger than one, tiled rendering is used.
        If @c offscreenWidth and @c offscreenHeight are bigger than
        0, offscreen rendering is used. If @c filename is null, the
        snapshot dialog is popped up and all parameters can be
        overwritten by the user. */
    void snapshot( const char * filename, int numTilesX, int numTilesY,
                   int offscreenWidth=0, int offscreenHeight=0, const bool stereo=false,
		   const char * filename2=0 );

    /** Creates a snapshot from the viewer and returns the image data in @c outData.
        The memory must be freed by user. The images dimensions (width, height, number
        of color channels) are delivered in @c outSize. If @c inNumTilesX or @c inNumTilesY
        is bigger than one, tiled rendering is applied. When the snapshot is taken with
        @c inCamMode set to ACTIVE_STEREO, the resulting images are twice as wide as the
        window. In the left half of the image the left eye snapshot is stored and in the
        right half the right eye snapshot. If @c inMakeAlpha is nonzero the resulting image
        has an alpha channel which blends out the background. */
    void snapshot(int outSize[3], unsigned char*& outData,
                  int inNumTilesX, int inNumTilesY,
                  int inMakeAlpha, int inBytesPerPixel, CameraMode inCamMode);

	/// Enables or disables fps counter.
	void showFramesPerSecond(bool value);

	/// Checks if fps counter is enabled or not.
	bool areFramesPerSecondShown() const;

    /// Get default directional light direction.
    void getDefaultDirectionalLightDirection( SbVec3f& );

    void sizeChanged( const SbVec2s& s ); 

    virtual void processEvent(QEvent* xe);

    ////////////////////////////////////////
    // overloaded methods of HxRenderArea
    ////////////////////////////////////////
    void            setCameraMode( CameraMode mode );

    ////////////////////////////////////////
    // methods of SoQtExaminerViewer
    ////////////////////////////////////////
    void            setFeedbackVisibility (bool onOrOff);
    bool            isFeedbackVisible () const;
    void            setFeedbackSize (int newSize);
    int             getFeedbackSize () const;
    void            setAnimationEnabled (bool onOrOff);
    bool            isAnimationEnabled ();
    void            stopAnimating ();
    virtual void    viewAll ();
    virtual void    resetToHomePosition ();
    virtual void    setViewing (bool onOrOff);
    virtual void    setViewing (bool onOrOff, bool notify);
    virtual void    setCursorEnabled (bool onOrOff);

    ////////////////////////////////////////
    // methods of SoQtFullViewer 
    ////////////////////////////////////////
    bool            isDecoration ();
    void            setPopupMenuEnabled (bool trueOrFalse);
    bool            isPopupMenuEnabled ();
    void            setClientPopupMenu (QMenu *menu);
    bool            isClientPopupMenuInstalled ();
    QWidget       * getAppPushButtonParent () const;
    int             lengthAppPushButton ();
    QWidget       * getRenderAreaWidget ();
    virtual void    setHeadlight(bool onOrOff);
    virtual void    setDrawStyle(DrawType type, DrawStyle style);
    virtual void    setBufferingType(BufferType type);

    ////////////////////////////////////////
    // methods of SoQtViewer 
    ////////////////////////////////////////
    SoCamera              * getCamera () ;
    virtual void            saveHomePosition () ;
    bool                    isHeadlight () ;
    SoDirectionalLight    * getHeadlight () ;
    DrawStyle               getDrawStyle (DrawType type) ;
    BufferType              getBufferingType () ;
    bool                    isViewing () const ;
    bool                    isCursorEnabled () const ;
    void                    setAutoClipping (bool onOrOff) ;
    bool                    isAutoClipping () const ;
    virtual void            setStereoViewing (bool onOrOff) ;
    virtual bool            isStereoViewing () ;
    void                    setStereoOffset (float dist) ;
    float                   getStereoOffset () ;
    void                    setStereoBalance (float balance) ;
    float                   getStereoBalance () ;
    void                    setDetailSeek (bool onOrOff) ;
    bool                    isDetailSeek () ;
    void                    setSeekTime (float seconds) ;
    float                   getSeekTime () ;
    virtual void            recomputeSceneSize () ;
    void                    setAutoClipTolerance (float tolerance) ;
    float                   getAutoClipTolerance () const ;

    ////////////////////////////////////////
    // Methods of SoQtRenderArea
    ////////////////////////////////////////
    void                    setBackgroundIndex (int index) ;
    int                     getBackgroundIndex () const ;
    void                    setColorMap (int startIndex, int num, const SbColor *colors) ;
    void                    setOverlayColorMap (int startIndex, int num, const SbColor *colors) ;
    void                    setViewportRegion (const SbViewportRegion &newRegion) ;
    const SbViewportRegion& getViewportRegion () const ;
    void                    setTransparencyType (SoGLRenderAction::TransparencyType type) ;
    SoGLRenderAction::TransparencyType getTransparencyType () const ;
    void                    setAntialiasing (bool smoothing, int numPasses) ;
    void                    getAntialiasing (SbBool &smoothing, int &numPasses) const ;
    void                    setClearBeforeRender (bool trueOrFalse, bool zbTrueOrFalse=TRUE) ;
    bool                    isClearBeforeRender () const ;
    bool                    isClearZBufferBeforeRender () const ;
    void                    setAutoRedraw (bool trueOrFalse) ;
    bool                    isAutoRedraw () const ;
    void                    setRedrawPriority (uint32_t priority) ;
    uint32_t                getRedrawPriority () const ;
    void                    render () ;
    void                    scheduleRedraw() ;
    void                    redrawOnSelectionChange (SoSelection *s) ;
    void                    setSceneManager (SoSceneManager *sm) ;
    SoSceneManager        * getSceneManager () const ;
    void                    setGLRenderAction (SoGLRenderAction *ra) ;
    SoGLRenderAction      * getGLRenderAction () const ;
    uint32_t                getDefaultRedrawPriority () ;

    ////////////////////////////////////////
    // Methods of SoQtGLWidget 
    ////////////////////////////////////////
    unsigned long           getOverlayTransparentPixel () ;
    int                     getOverlayColorMapSize () ;
    int                     getColorMapSize () ;
    QWidget               * getNormalWidget () ;
    virtual void            setDoubleBuffer (bool onOrOff) ;
    bool                    isDoubleBuffer () ;
    void                    setBorder (bool onOrOff) ;
    int                     getBorderSize () ;
    bool                    isBorder () const ;
    void                    setDrawToFrontBufferEnable (bool enableFlag) ;
    bool                    isDrawToFrontBufferEnable () const ;
    bool                    bindNormalContext();
    bool                    unbindNormalContext();
    bool                    swapNormalBuffers () ;
    bool                    makeOverlayCurrent () ;
    bool                    swapOverlayBuffers () ;

    ////////////////////////////////////////
    // Methods of SoQtComponent  
    ////////////////////////////////////////
    QWidget               * getWidget () const ;
    QWidget               * getShellWidget () const ;
    QWidget               * getParentWidget () const ;
    bool                    setFullScreen (const bool enable) ;
    bool                    isFullScreen (void) const ;
    void                    setFullScreenEnable (const bool enable) ;
    bool                    isFullScreenEnable (void) const ;
    const SbString&         getWidgetName () const ;
    const SbString&         getClassName () const ;
    bool                    setInsideOut(bool enable, bool alwaysOnTop=false); // shows viewer in a borderless top-level window (for amiraVR)

    virtual void adjustCameraClippingPlanes();

    QxViewer* qxViewer() const { return _viewer; }

    virtual void redraw();

  protected:
    virtual void actualRedraw();
    void redrawClusterSlave();
	void generateFrameClusterSlave();
    void bgColorEdit();
    void changeWidgets(){} //<! deprecated
    void removeButton(int);
    void updateViewerToggles();
    void doActualSnapshot(QImage& image);
    void snapshotSimple ( int outSize[3], unsigned char*& outData, int inNumTilesX, int inNumTilesY, int inRsrvAlpha );
    void snapshotAlpha  ( int outSize[3], unsigned char*& outData, int inNumTilesX, int inNumTilesY );
    void doActualOffscreenRendering(QImage& image, int width, int height);

    static void colorChangedCB(void*, const HxColorEditor &);

    friend class HxController;
    friend class HxVRSessionController;
    friend class HxRemoteRenderArea;
	friend class HxTimeCompositingController;
    friend class QxViewer;
	friend class HxSoftMouse;
};

#endif


/// @}

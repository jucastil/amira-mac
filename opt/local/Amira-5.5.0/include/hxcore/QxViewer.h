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
#ifndef QX_VIEWER_H
#define QX_VIEWER_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/SoAnimCam.h>
#include <hxcore/HxViewer.h>
#include <hxcore/HxPickCallback.h>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
#include <Inventor/Gui/viewers/SoGuiExaminerViewer.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoAnnotation.h>
#include <Inventor/components/stereo/SoBaseStereo.h>

#include <mclib/McBox2f.h>
#include <tcl.h>

#if defined(TGS_VERSION) && TGS_VERSION>=2620
#define HX_TILED_RENDERING
#endif

class McVec2f;
class McBox2f;
class McWatch;
class QEvent;
template <class T> class QQueue;
class QTimer;
class QImage;
class QPixmap;
class QAbstractButton;
class QMenu;
class QxToolButton;
class HxController;
class HxColorEditor;
class HxRemoteRenderArea;
class SoGLRenderAction;
class HxViewerGadget;
class SoPickStyle ;
class HxFrameGrabber;
class HxFrameRender;
class SoMemoryBuffer2D;
class SoShadowGroup;
class HxPreferences;

/// Amira's customized viewer class.
class HXCORE_API QxViewer : public SoQtExaminerViewer
{
    Q_OBJECT

    friend class HxRemoteRenderArea;

    // moved from QxViewerNotifier
  public slots: 
    void _viewX();
    void _viewY();
    void _viewZ();
    void _rotateVD();
    void _bgColorEdit();
    void _snapshot();
    void _animateCamera( );
    void _lightDialog( );
    void _addMeasuringTool();
    void _selectMeasuringTool (int);
    void _toggleFullScreen();
    void sizeChanged();
    void sizeChanged(const SbVec2s &s);
    void menuActivatedAction(QAction*);

  signals:
    void viewingModeActivated(bool value);
    
    /**
    *  Emitted when viewX has been called.
    *  Camera direction vector is (1,0,0) if reverse is false, (-1,0,0) otherwise
    */
    void viewXDone(bool reverse);
    
    /**
    *  Emitted when viewY has been called.
    *  Camera direction vector is (0,1,0) if reverse is false, (0,-1,0) otherwise
    */
    void viewYDone(bool reverse);

    /**
    *  Emitted when viewZ has been called.
    *  Camera direction vector is (0,0,1) if reverse is false, (0,0,-1) otherwise
    */
    void viewZDone(bool reverse);

    /**
    *  Emitted before viewAll() is processed
    */
    void aboutToViewAll();

    /**
    *  Emitted when viewAll has been processed
    */
    void viewAllDone();

  public:
    /** Constructor. @c num indicated the Amira viewer id. The id of
        the main viewer is 0. The other arguments have the same
        meaning as in the base class @ SoQtExaminerViewer. */
    QxViewer( QWidget       * parent, 
              HxViewer      * myOwner, 
              const char    * name      = 0, 
              int             num       = 0,
              SbBool buildInsideParent  = TRUE,
              SoQtFullViewer::BuildFlag flag = BUILD_ALL,
              SoQtViewer::Type          type = BROWSER ) ;

    /// Destructor.
    ~QxViewer();

    /** Root separator containing the viewer's camera. In contrast to
        the result returned by setSceneGraph() this separator contains
        all internal nodes created by the viewer including the camera
        and all lights. */
    SoNode * getSceneRoot() 
    { 
        return sceneRoot; 
    }

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

    /// Overloaded from SoQtFullViewer for internal reasons.
    virtual void setCamera( SoCamera * cam );

    /// Sets the camera type (Open Inventor 4.0 method).
    void setCameraType(SoType type);
    
    /// Sets the camera type.
    void setCameraType( HxViewer::CameraType type );

    /// Overloaded method from SoQtViewer, updates camera icon in panel.
    void toggleCameraType();

    /// Returns the current camera type.
    HxViewer::CameraType getCameraType();

    /// Checks if currently a perspective camera is active.
    bool hasPerspectiveCamera() {
        return (getCameraType()==HxViewer::PERSPECTIVE_CAMERA); 
    }

    /** Sets camera modes for (passive) stereo viewing. If mode is 0, ordinary
        monoscopic viewing is used. If mode is 1 the left eye view of a
        stereo image is rendered. If mode is 2 the right eye view of a stereo
        image is rendered. If mode is 3 OpenGL active stereo is activated. This
        method is used by AmiraVR. Other stereo modes can be chosen using the
        Open Inventor SoStereoViewer interface. */
    void setCameraMode( int mode );

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

    /// ???
    void initCameraPath();

    // rotateCamera() is made virtual since oiv 4.0.6
    // virtual void rotateCamera (const SbRotation & rot);

    /** Turn on/off auto-animating of the camera. Animation is done using the
        actually set camera path. Use setCameraPath() to set the camera path
        for the viewer.*/
    void autoAnimateCamera(SbBool);
    
    /// Is animating turned on ?
    int isAnimating() 
    { 
        return ((SoAnimCam*)animCam)!=0; 
    }

    bool isAnimatingNow()
    {
        return (bool)SoQtExaminerViewer::isAnimating();
    }
  
    /// Sets logo to be displayed in the overlay planes.
    void setLogo( const char* ivfile );

    /// Switch for displaying a safety frame for video grabbing
    void setVideoFrame( bool onOrOff );

    /// Write scene graph as an Open Inventor file.
    void saveScene(const char* filename, bool binary=false, bool rootNodes=false);

    /// Write scene graph as an VRML file.
    void saveSceneAsVRML(const char* filename, int version=1, bool binary=false, bool rootNodes=false);
    
    /// 
    virtual void viewAll();

    /// Select axial view.
    void viewX( int reverse=0 );

    /// Select frontal view.
    void viewY( int reverse=0 );

    /// Select sagittal view.
    void viewZ( int reverse=0 );

    /// Rotate camera around some axis. 
    void rotate( HxViewer::RotAxis axis, float angle );

    /// Tcl-command interface.
    int parse( Tcl_Interp * interpreter, int argc, char ** argv );
    
    /// Set the viewer's scene graph.
    virtual void setSceneGraph ( SoNode * );

    /// Get position of viewer's frame window.
    SbVec2s getPosition();

    /// Set position of viewer's frame window.
    void setPosition(int x,int y);

    /// Set size of viewer's frame window.
    void setSize( const SbVec2s& size );
    void setMasterSize( const SbVec2s& size );

    const SbVec2s & getGlxSize() const 
    {
        return SoQtGLWidget::getGlxSize();
    }

    /// Show viewer.
    void show(bool raise = true);

    /// Hide viewer.
    void hide();

    /// A little performance test. The result is written to @c theMsg.
    float performanceTest( int verbose, int numFrames = 10 );

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
    void snapshot( const char * filename, int numTilesX, int numTilesY, int nrSamples = 1,
                   int offscreenWidth=0, int offscreenHeight=0, const bool stereo=false,
                   const char * filename2=0 );

    /// Snapshot to a QImage instead of a file
    /// Important note: the snapshot dialog values must be set before calling this function
    void snapshot( QImage &image1, int numTilesX, int numTilesY, int nrSamples = 1,
                   int offScreenWidth=0, int offScreenHeight=0, const bool stereo=false,
                   QImage *image2 = 0);

    inline void setSnapshotAlpha(bool toggle) {snapshotAlpha = toggle;}
    
    /// Enables or disables fps counter.
    void showFramesPerSecond(bool value);

    /// Checks if fps counter is enabled or not.
    bool areFramesPerSecondShown() const { return showFpsFlag; }

    /// Get default directional light direction.
    void getDefaultDirectionalLightDirection( SbVec3f& );

    virtual void processEvent(QEvent* xe);
    virtual bool eventFilter(QObject * object,QEvent *event);

    virtual bool processEvent(SoEvent* e);

    void setTile(const McBox2f& tile) {_myOwner->setTile(tile);}
    McBox2f & getTile() { return (McBox2f &)_myOwner->getTile(); }

    void setSoftEdge(int whichEdge, float overlap, float gamma=0.f);

    void setBackgroundMode(HxRenderArea::BackgroundMode mode);

    void setBackgroundColor2(const SbColor& color);

    const SbColor& getBackgroundColor2() const { return backgroundColor2; }

    int setBackgroundImage(const char* filename);

    int setStereoBackgroundImage(const char* left, const char* right=0);

    void setBackgroundImage(const int dims[3], const unsigned char* data);

    void setStereoBackgroundImage(const int dims[3], const unsigned char* left, const unsigned char* right);

    void getBackgroundImage(const char*& left, const char*& right, bool& stereo);

    /// query support of stereo capabilities
    int hasStereoCapability (const SoBaseStereo::StereoViewType 
                             theStereoType = SoBaseStereo::OPENGL_STEREO ); 

    virtual void setViewing(SbBool onOrOff);
    virtual void setViewing(SbBool onOrOff, bool notify);

    /// Display logos if we have a trial or demo version
    void displayLogos() ;

    void redraw();
    void redrawClusterSlave();
    void generateFrameClusterSlave();
    void redrawClusterMaster();
    void actualRedraw();
    void adjustCameraClippingPlanes();
    void setStereoActive(SbBool activate);
    void setStereoViewType(SoBaseStereo* viewType);
    void setAntialiasing(SbBool smoothing, int numPasses);
    void setMultiVolumeEnabled(bool enable);

    /// Enumerates viewer buttons in getButton().
    enum {
        BTN_INTERACT=0,
        BTN_VIEWING=1,
        BTN_VIEW_ALL=2,
        BTN_CAMERA_TYPE=3,
        BTN_YZ=4,
        BTN_XZ=5,
        BTN_XY=6,
        BTN_COLOR=7,
        BTN_PRINT=8,
        BTN_SEEK=9,
        BTN_HOME=10,
        BTN_SET_HOME=11,
        BTN_ROTATE=12,
        BTN_MEASURE=13
    };
  
    QAbstractButton * getButton(int which);

    QMenu* getPopupMenu() const;

    /// Override SoQtRenderArea::setFullScreen
    virtual SbBool setFullScreen( const SbBool enable );

    bool setInsideOut(bool enable, bool alwaysOnTop = false);
    
    QObject* getRemoteEventConsumer();

    int isInteractive() const;

    void checkRemoteMode();
    void enableStereoDialog(bool enable);
    void checkGadgetsVisibility();

    void enableViewing(bool);
    bool isViewingEnabled() { return m_enableViewing; }

    HxViewer *getHxViewer() const { return _myOwner; }

    void renderBackground(SoGLRenderAction *renderAction);

    /// The possible gadgets.
    enum {CAMERA_TRACKBALL = 0, COMPASS = 1};

    bool inPerformanceTest (void) { return m_performanceTest; }

    /// To get the viewer gadgets.
    inline McDArray<HxViewerGadget*> getViewerGadgets() const {return m_viewerGadgets;};

    /** Override the cursor for the specified viewing mode.
     * This cursor will be displayed in the viewer until restoreOverrideCursor() or another setOverrideCursor() is called.
     * Viewer cursors are stored on an internal stack. setOverrideCursor() pushes the cursor onto the stack, and restoreOverrideCursor() pops the active cursor off the stack.
     * Every setOverrideCursor() must eventually be followed by a corresponding restoreOverrideCursor(), otherwise the stack will never be emptied.
     */
    void setOverrideCursor(SoGuiExaminerViewer::ViewerModes mode, const QCursor & cursor);

    /** Undoes the last setOverrideCursor() for the specified viewing mode.
     * If setOverrideCursor() has been called twice, calling restoreOverrideCursor() will activate the first cursor set. 
     * Calling this function a second time restores the original viewers' cursors.
     */
    void restoreOverrideCursor(SoGuiExaminerViewer::ViewerModes mode);
protected:
    virtual void defineCursors();
    virtual void updateCursor();

    HxViewer          * _myOwner;

    McDArray< McHandle<SoSwitch> > m_viewerGadgetsSwitches;
    McDArray<HxViewerGadget*> m_viewerGadgets;
    McDArray<SoPickStyle*> m_scenePickStyles;

    McHandle<SoSwitch>      backgroundSwitch;
    McHandle<SoSeparator>   logo;
    McHandle<SoAnnotation>  overlay;
    McHandle<SoSeparator>   videoFrame;
    McHandle<SoGroup>       headerGroup;
    McHandle<SoGroup>       tailGroup;
    McHandle<SoGroup>       m_volumeGroup; // This is a SoVolumeGroup!
    McHandle<SoGroup>       m_shadowGroup; // This is a SoShadowGroup!

    int             slaveViewer;
    int             waitSwap;
    int             didActualRedraw;
    int             panelChildIndex;

    float           heightAngle;

    bool snapshotAlpha;

    unsigned int    dontWaitForExpose:1;
    unsigned int    passiveStereo:2;
    unsigned int    interactiveFlag:1;
    unsigned int    showFpsFlag:1;
    unsigned int    recursiveFlag:1;
    SbColor         backgroundColor2;
    int             backgroundImageDims[3];
    unsigned char*  backgroundImageData[2];
    McString        leftBackgroundImage;
    McString        rightBackgroundImage;

    static int  allViewersPickCallbackStack;
    McString    pickCallbackProc;
    HxPickCallback::EventType   pickCallbackEventType;

    bool m_enableLocalPickEvents;
    bool m_enableViewing;
    bool m_performanceTest;

    McWatch* m_perfTimer;
    QQueue<float>* m_previousFrames;

    McHandle<SoAnimCam>     animCam;
    McHandle<HxCameraPath>  cameraPath;

    HxFrameRender    *m_frameRender;
    HxFrameGrabber   *m_frameGrabber;
    SoMemoryBuffer2D *m_frameMemoryBuffer;
    SbVec2f           m_masterViewSize;
    bool              m_resizeViewport;

    void            removeButton(int);
    void            updateViewerToggles();
    static void     windowCloseCB(void*, SoQtComponent*);

    void resizeViewport();

    class QxViewerPanel * panel;
    class QxToolButton  * btnViewX;
    class QxToolButton  * btnViewY;
    class QxToolButton  * btnViewZ;
    class QxToolButton  * btnRotateVD;
    class QxToolButton  * btnSeek;
    class QxToolButton  * btnColor;
    class QxToolButton  * btnPrint;
    class QxToolButton  * btnAnimate;
    class QxToolButton  * btnMeasure;

    static QPixmap      * qIconMeasureLine;
    static QPixmap      * qIconMeasureAngle;
    static QPixmap      * qIconMeasureAnnotation;

    QTimer * timer;

    QMenu* measureMenu;
    QAction* IDM_DPOPUP_TRACKBALL;
    QAction* IDM_DPOPUP_COMPASS;
    int stateBtnMeasure;
    QObject* remoteEventConsumer;

    QMap<SoGuiExaminerViewer::ViewerModes, QList<QCursor> > cursorsMap;

    static void colorChangedCB(void*, const HxColorEditor &);
    static void interactiveStartCallback(void *, SoQtViewer *v);
    static void interactiveFinishCallback(void *, SoQtViewer *v);

    void bgColorEdit();
    void doActualSnapshot(QImage& image);
    void doActualOffscreenRendering(QImage& image, int width, int height);
    void renderFps(float fps);
    int setStereoCmd(Tcl_Interp* t, int argc, char **argv);

    void setPickCallback(const McString& cb, HxPickCallback::EventType eventType);
    void unsetPickCallback();
    static void allViewersPickCallback(void*, SoEventCallback* node);

    // Upscale and downscale an Image to achive antialiasing 
    // while executing an snapshot    
    void imageAntialiasing(const QImage &source, QImage &dest, int factor=1);

    // The copyOrCropImage function is a helper function used by the imageAntialiasing function    
    void copyOrCropImage(const QImage &source, QImage &dest, bool crop, int destWidth, int destHeight);

    friend class HxController;
    friend class QxViewerPanel;
    friend class HxViewer;

public slots:
    /**
     *  To be notified that preferences changed.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

public:
    SbMatrix getProjectionMatrix();
    static McString s_productBannerFile;
    static McString s_companyBannerFile;
};

#endif

/// @}

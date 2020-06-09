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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef EXBASEVIEWER_H
#define EXBASEVIEWER_H

#include <QWidget>
#include <QContextMenuEvent>
#include <QMenu>

#include <mcgl/McGLText.h>

#include <vsvolren/VsCamera.h>
#include <vsvolren/VsSlice.h>
#include <vsvolren/VsVolume.h>
#include <vsvolren/VsVolren.h>
#include <vsvolren/VsBoundingBox.h>
#include <vsvolren/VsCommonRenderer.h>

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <mclib/McPlane.h>
#include <mclib/McHashTable.h>

#include "ExNotifiable.h"
#include "ExViewerControl.h"
#include "ExBaseViewerRenderWidget.h"
#include "ExModal.h"
#include "ExViewerManager.h"
#include "VisageViewerWinDLLApi.h"

#include <hxcore/HxController.h>
#include <hxcore/HxViewer.h>
#include <hxcore/HxViewerPanel.h>

#ifdef CursorShape
    #undef CursorShape
#endif

class VsWidget;

////////////////////////////////////////////////////////////////////////////////
class HXVISAGEVIEWER_API ExBaseViewer 
:   public QWidget
,   public VsCommonRenderer
,   public ExNotifiable
{
    Q_OBJECT

public:

    ExBaseViewer( QWidget * parent = 0 );
    virtual ~ExBaseViewer();
    
    void setViewerManager(ExViewerManager*);
    ExViewerManager* viewerManager();

    virtual Ex::ViewerType type() const;


    ////////////////////////////////////////
    // overload QWidget
    ////////////////////////////////////////

//    bool event      ( QEvent * e );
    void resizeEvent        ( QResizeEvent * e );
    /** Note: This function won't be called, if the render widget
        (ExBaseViewerRenderWidget) completely covers the region of the
        widget! So if you wonder why the paint function isn't called at 
        all, this is most likely the case.        
    */
    void paintEvent         ( QPaintEvent  * e );
    void contextMenuEvent   ( QContextMenuEvent * e );

//    QPaintEngine * paintEngine () const;

    void setTrueScale( float pixelHeight );

    ////////////////////////////////////////
    // image alignment
    ////////////////////////////////////////

    /// Different alternatives for aligning the image inside a viewer
    enum ImageAlignment {
        IA_NONE     = 0,
        IA_CENTERED = 1<<0,
        IA_LEFT     = 1<<1,
        IA_RIGHT    = 1<<2,
        IA_TOP      = 1<<3,
        IA_BOTTOM   = 1<<4
    };

    /// Sets the image alignment for the viewer
    //void setImageAlignment( ImageAlignment ia );
    /// Sets the image alignment from a string representation
    //void setImageAlignment( QString str );
    /// Returns the image alignment for the viewer
    //ImageAlignment imageAlignment() const;
    /** Compute the reference point for the image alignment - The 3D point under 
        the top/bottom/right/left-most pixel (center of the border) will be fixed.
        This method needs the camera to be already set correctly. */
    void computeReferenceFromCamera();
    /** Compute the reference point from the displayed scene - the center of one of the
        bounding box's faces will be fixed to the image border. */
    //void computeReferenceFromScene();
    /// (Re-)aligns the scene with respect to the current image alignment
    //void realignImage();

    ////////////////////////////////////////


    ////////////////////////////////////////
    // overload VsCommonRenderer
    ////////////////////////////////////////

    virtual VSRESULT renderFrameBegin();
    virtual VSRESULT renderFrameEnd( VsRenderResult inResultFromRender );


    ////////////////////////////////////////
    // overload ExNotifiable
    ////////////////////////////////////////

    virtual void notified( const ExNotification & notification );

    ////////////////////////////////////////


    void updateHUDVisibility();


    bool isActiveViewer() const;
    static void setActiveViewer( ExBaseViewer * inViewer );
    static ExBaseViewer * activeViewer();

    /// flat widget at the bottom of the viewer for 
    /// displaying and manipulating most important settings
    void setViewerControl( ExViewerControl * , bool show);
    ExViewerControl* viewerControl() const;
    bool viewerControlVisible() const;


//    void setAllowTouch(bool value);

    void updateCameraAspect();

    bool rightMouseButtonEvent( QMouseEvent * me );

    //enum IdVisibility { IV_INVALID = -1, IV_OFF = 0, IV_ON = 1 };
    //int viewerId() { return displaySet() + 1; }; // returns an 'intuitive' ID 'for non-computerscientists'
    //void setViewerIdVisible(IdVisibility visibility);
    //IdVisibility viewerIdVisible();

    //void setImageSet(int imageSet);
    int imageSet() const {return 666;}

    //void setDisplaySet(int displaySet);
    //int displaySet() const;

    // volume
    void        setVolume( VsVolume * inVolume0, VsVolume * inVolume1 );
    VsVolume  * volume(int idx = 0) const;

    // slice
    void        setSlice(VsSlice* slice);
    VsSlice   * slice() const;

    // volren
    void        setVolren( VsVolren * volren );
    VsVolren  * volren() const;

    // bounding box
    void        setBoundingBox( VsBoundingBox * volren );
    VsBoundingBox  * boundingBox() const;

    //
    void updateRegistrationTransform();
    


    VSRESULT snapshot( VsMemoryData * outData, bool inIncludeControls);

    // sets the background color, renders 
    // and then returns to the previous bg color
    VSRESULT snapshot( VsMemoryData * outData, bool inIncludeControls, McColor backgroundColor );

    // renders the snapshot offscreen in the specified dimensions
    // with specified background color
    VSRESULT snapshotOffscreen( VsMemoryData * outData, int width, int height, McColor backgroundColor );

    /** Returns the preferred data window of a volume. The method
        reads the preferred data window from the parameter bundle. */
    void getPreferredDataWindow(VsVolume* volume, float& vmin, float& vmax);

    /** Returns list of supported data windows for the given volume. */
    void getDataWindows(VsVolume* volume, McDArray<McString>& names, McDArray<McVec2f>& windows, McDArray<int>& separatedAt, bool readObsoleteColormapWindow);

    /** Sets the default data window. possible sources: preferredDataWindow, hanging protocol, color templates*/
    void setDefaultDataWindow(VsVolume* volume, float vmin, float vmax);

    virtual float windowPixelHeight();  // todo: this is the first step to encapsulate the camera

    virtual void viewAll();
    virtual void viewWidth();
    virtual void viewHeight();

    virtual void resetView(Ex::View view);                             // sets to initial view
    virtual void resetView(McVec3f & viewDir, McVec3f & upDir);        // sets to initial view
    virtual void resetOrientation(Ex::View view);                      // does not reset zoom level
    virtual void resetOrientation(McVec3f & viewDir, McVec3f & upDir); // does not reset zoom level

    virtual const char * preferredOrientation();
    virtual void setPreferredOrientation(const char right, const char bottom);
    virtual void setPreferredOrientation(Ex::View view);

    void    setDefaultOrthoPlane( const McPlane & plane );
    McPlane defaultOrthoPlane() const;

    //virtual bool sameOrientation(ExBaseViewer * other);
    static Ex::View getViewOrientation(const char axes[2]);

    // restore camera view and projection related parameters.
    // if current viewer is a slice viewer the slice plane will
    // also be restored
    // if saveHome() has not been applied before, the current camera and slice plane
    // will be set as default
    void setToHome();
    // save camera view and projection related parameters plus
    // the slice plane if available
    void saveHome();

    virtual void setStandardTools();

    /// appends a modal tool to the list of modal tools. Ensures that
    /// no tool is inserted twice.
    /// Which tool of the list is used for a mouse event depends on the following:
    ///  - first an exclusive tool (isExclusive() returns true) is used.
    ///    by definition there should be only one exclusive tool in the
    ///    the list of tools, if not, the behavior is not defined.
    ///  - shape tools are asked whether pick() returns true for them.
    ///    if any, the one with the smallest picking distance is used.
    ///  - all remaining tools are tried as long as one returns true
    /// If the notify parameter is true, an ACTIVE_TOOL_CHANGED notification
    /// is issued in the active viewer
    void append(ExModal*, bool notify);

    /// removes a modal tool from the list of modal tools.
    /// If the notify parameter is true, an ACTIVE_TOOL_CHANGED notification
    /// is issued in the active viewer with the tool that is active now.
    /// if the tool is not found and cannot be removed, the return value
    /// is false and no notification is sent in any case. 
    bool remove(ExModal*, bool notify);

    ExModal* tool(unsigned int idx) const;

    unsigned int numTools() const;

    ////////////////////////////////////////
    // the overlay 2d-widgets
    ////////////////////////////////////////
    enum ViewerWidget 
    { 
        VW_TEXT_NW      = 1<<0  // 1    0x0001
    ,   VW_TEXT_NE      = 1<<1  // 2    0x0002
    ,   VW_TEXT_SE      = 1<<2  // 4    0x0004
    ,   VW_TEXT_SW      = 1<<3  // 8    0x0008
    ,   VW_HISTOGRAM    = 1<<4  // 16   0x0010
    ,   VW_WARNING      = 1<<5  // 32   0x0020
    ,   VW_QUALITY      = 1<<6  // 64   0x0040
    ,   VW_NAVCUBE      = 1<<7  // 128  0x0080
    ,   VW_TEXT_PROBE   = 1<<8  // 256  0x0100
    ,   VW_TEXT_N       = 1<<9  // 512  0x0200
    ,   VW_TEXT_S       = 1<<10 // 1024 0x0400
    ,   VW_TEXT_E       = 1<<11 // 2048 0x0800
    ,   VW_TEXT_W       = 1<<12 // 4096 0x1000
    ,   VW_TEXT_C       = 1<<13 // 8192 0x2000
    };
    VsWidget * vsWidget( ViewerWidget inWhich );
    void setVsWidget( ViewerWidget inWhich, VsWidget * inWidget );
    void addVsWidgetsToScene( bool inShowPatientInfo );
    mcuint64 vsWidgetVisibilityMask();
    void setVsWidgetVisibilityMask( mcuint64 inMask );
    void setVsWidgetVisibilityMask( mcuint64 inMask, bool inFlag );
    void setVsWidgetVisibilityMaskDefault();
    void updateVsWidgetLayout();

    void patientInfoSetVisible( bool inFlag );
    void infoSetVisible(bool inFlag);
    bool patientInfoVisible();
    void patientInfoUpdate();
    void calculateOrientationLabels();

    void enableContextMenu(bool iFlag) { mContextMenuEnabled = iFlag; }
    bool contextMenuEnabled() { return mContextMenuEnabled; }

    ////////////////////////////////////////
    // Overloaded methods from VsRenderer
    ////////////////////////////////////////
//    virtual McVec2i windowSize() const;

//    virtual VSRESULT deInitialize();








//    void setTrueScale( float pixelHeight );

    void setCursorShape(Ex::CursorShape shape);

    void updateWindowSize();

    /** Enables drawing a border around the active viewer. If this property
        is set to true, a border is drawn around the active viewer. In this
        case the actual render widget is 2 pixels smaller on each side. For
        the MPR viewer of the Neuron Editor no border is drawn, because this
        viewer is managed by Amira's QxViewerPanel class which already draws
        a border by its own. */
    void setBorderEnabled(bool value);

    /** Returns true if a border around the active viewer should be drawn.
        The default value is true. */
    bool borderEnabled() const;

    /** Returns the color of the border drawn around the active viewer. This
        color is identical to the frame color of the viewer's slice node. If
        the viewer does not have a slice node the border color is white. */
    McColor borderColor() const;

    void repaintBorder();

    virtual void rendererGeometry( QRect & outRect ) const;

    void updateLayout();

private:
    const char * findTagInAll(const HxParamBundle * dicomBundle, const char * tagName, const char * defaultString = NULL);
    
    McHandle<ExViewerManager> mViewerManager;

    bool mContextMenuEnabled;
//public:

    //// Overloaded methods from VsRenderer
    //virtual VsRenderResult render();
    //virtual VSRESULT renderFrameEnd( VsRenderResult inResultFromRender );
    //virtual VSRESULT setBackgroundColor( const McColor & inColor );

    //// Overloaded methods from QWidget
    //virtual void paintEvent  ( QPaintEvent * e );
    //virtual void resizeEvent ( QResizeEvent* e );
//public:
    // Overloaded methods from QWidget
    

//public slots:
//    // Overloaded slots from QWidget
//    virtual void show ();
//    virtual void hide ();

public slots:
    virtual void setFocus();    
    /** Emits a contextMenuClicked() signal with a mouse event with
        globalPos at the current mouse cursor position. This way, 
        widgets can trigger display of the context menu without knowing
        the ExContextMenu class. */
//    void openContextMenu();
//
//signals:
//    void contextMenuClicked(QMouseEvent*);

    // used in remote rendering. This requires a cleanup
public:

    /** Returns current data window of this viewer in vmin and vmax.
        The data window is reported in raw units, i.e. in the same units
        used for VsSlice::setdataWindow() or VsVolren::setDataWindow().
        In order to convert these units intp physical units (like
        Hounsfield for CT), use volume->rescale(value).

        \param vmin Min value of data window is stored here.
        \param vmax Max value of data window is stored here.
        \param idx If 0 the data window of the primary volume is
            reported. If 1 the data window of the overlay volume
            is reported.
        \return true on success, false otherwise (for example because
            the viewer currently has no volume).
    */
    bool dataWindow( float& vmin, float& vmax, int idx );

//protected:
//
//    friend class ExWindowLevelTool;
//    /// Sets the data window of volume with index idx to vmin and vmax
    void setDataWindow( float vmin, float vmax, int idx );
//    

//signals:
//    void rightButtonClicked(QMouseEvent* me);
//    void rightButtonDragged(QMouseEvent* me);


public:

    // Vs-Objects
    McHandle<VsVolren>      mVolren;
    McHandle<VsSlice>       mSlice;
    McHandle<VsBoundingBox> mBoundingBox;

    // the tools
    McDArray< McHandle<ExModal> > mTools;


    QPoint                  mRightMouseOrigin;
    bool                    mRightMouseMoved;
//    bool                    mFullscreen;
//    McBox2f                 mRect;

    // current cursor shape
    Ex::CursorShape         mCursorShape;


    ExBaseViewerRenderWidget    * mRenderWidget;
    
    // the widget with these fency buttons and sliders
    ExViewerControl       * mViewerControl;
    bool                    mViewerControlVisible;

    // each bit (see enum ExBaseViewer::ViewerWidget) is the visibility hint for the specific VsWidget
    // if the VsWidget is really visible depends on app-specific constraints implemented in setVsWidgetVisibilityMask()
    mcuint64                mVsWidgetVisibilityMask;

    static ExBaseViewer   * mActiveViewer;
    bool                    mLastBorderDrawnActive;
    bool                    mRepaintBorderOnly;

    // True if the viewer should draw a frame around the active viewer.
    // This is true inside the Visage Viewer sub-application but not for
    // the MPR viewer of the Neuron Editor. In the latter case the active
    // viewer frame will be drawn by Amira QxViewerPanel.
    bool                    mBorderEnabled;

    


    char                    mPreferredOrientation[2];

    McPlane                 mDefaultOrthoPlane;

    QMenu                   mContextMenu;


    ////////////////////////////////////////
    struct ExDataWindow
    {
        ExDataWindow() : vmin(0), vmax(400) {}
        float vmin;
        float vmax;
    };
    McHashTable< VsVolume *, ExDataWindow > mDefaultDataWindows;

    ////////////////////////////////////////
    struct ExKeyView
    {
        // indicator if key view has been already set by saveHome()
        bool initialized;

        // camera view related parameters
        McVec3f cameraPosition;
        McVec3f camerUpDir;
        McVec3f cameraLookAt;

        // camera projection related parameters
        VsCamera::ProjectionType cameraType;
        float   cameraHeightAngle;
        float   cameraHeight;
        // slice related
        McPlane slicePlane;
    };

    ExKeyView mHome;
};

#endif // EXBASEVIEWER_H

/// @}

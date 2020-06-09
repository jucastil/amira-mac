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
#ifndef HX_CONTROLLER_H
#define HX_CONTROLLER_H

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <hxcore/HxBase.h>

#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/actions/SoGLRenderAction.h>


#ifdef HX_HAS_X11
    // Required for the declaration of XVisualInfo used below.
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #ifdef CursorShape
        #undef CursorShape
    #endif
#endif

class QTime;
class QWidget;
class QEvent;
class McBox2f;
class HxViewer;
class HxLight;
class HxRemoteRenderArea;
class SoQtSpaceball;
class SoMotion3Event;
class SoTransform;
class SoSeparator;
class SoEnvironment;
class SoPickStyle;
class SoEvent;
class SbMatrix;

#define USE_SPACEBALL 1

typedef SbBool HxControllerCB(const SoEvent*, HxViewer*, void*);

/** Prototype for timeout methods. Timeout methods can be registered
    using HxController::addTimeOutMethod. Such methods are called
    in regular intervals and can be used e.g. for animation purpose.
    @see HxTimeOuFunction */
typedef void (HxBase::*HxTimeOutMethod)();

/** Prototype for timeout functions. Timeout functions can be registered
    using HxController::addTimeOutFunction. Such methods are called
    in regular intervals and can be used e.g. for animation purpose.
    @see HxTimeOutMethod */
typedef void (*HxTimeOutFunction)(void* userData);

class SxGLHandleDeleter;

/** This class controls all 3D viewers and Open Inventor geometry. The
    controller can be accessed via the global pointer @c theController.
    Developers typically access the controller in order to register event
    or pick callbacks, to force certain viewers to be redrawn, or to change
    certain global viewer settings. */
class HXCORE_API HxController {

  public:
    /// Defines the maximum number of viewers.
    enum MaxNumViewers {
        /// Maximum number of viewers is 16.
        nViewers = 16
    };

    /// Defines some viewer masks.
    enum ViewerMasks {
        /// All viewers
        ALL = 0xffff,
        /// Main viewer
        MAIN_VIEWER = 0x0001
    };

    /// Spaceball navigation modes.
    enum SpaceballMode {
        /// Spaceball off.
        NONE,
        /// Rotate mode (like a trackball).
        ROTATE,
        /// Fly mode (for walkthroughs).
        FLY
    };

    /// Constructor.
    HxController();

    /// Destructor.
    ~HxController();

    /** Returns pointer to one of the viewers. If viewer number @c which does
        not exist and the @c create flag is set to 1 a new @c HxViewer is created
        with the given @c parent. If no @c parent is given and @c which<4 the new
        viewer is put into the global panel (HxViewerPanel::getThePanel),
        otherwise a new HxViewerPanel is created.
        If viewer number @c which does not exist and @c create is 0
        null is returned. */
    HxViewer* viewer(int which, int create=1, QWidget* parent=0);

    /// Returns 1 if viewer exists and is visible.
    int viewerExist(int which);

    ///Fills the given array with all existing viewer IDs.
    void getAllExistingViewerIDs(McDArray< int >& viewerIDs);

    /// Hide and delete viewer.
    void removeViewer(int which);

    /** Creates new viewer number @c which with given parent and
        returns the wrapper widget of the viewer. An existing viewer
        number @c which will be removed before creating the new one. */
    QWidget* reparentViewer(int which, QWidget* parent);

    /** Returns the viewer which is currently rendering or processing events or
        the last one to do so. This method may be used for special-purpose
        rendering tasks. For example, the Voltex module can render
        multiple transparent volumes at once. For this purpose the
        render routine must determine which particular Voltex module
        is visible in the viewer currently being rendered. */
    HxViewer* getCurrentViewer() { return viewer(currentViewerId,0); }

    /// Returns the id of the current viewer.
    int getCurrentViewerId() const { return currentViewerId; }

    /** Sets the id of the current viewer. This method is called by the
        amira viewer just before it starts to render or process events. */
    void setCurrentViewerId(int id) { currentViewerId = id; }

    /// Returns transformation from table to world coords.
    SoTransform* getTableToWorldTransform() { return tableToWorldTransform; }

    /** Set new transformation matrix from world to table coords. Certain modules,
        e.g. modules representing a radiotherapy device with adjustable table, may
        call this method in order to transform the geometry of all other modules at
        once. In the constructor of such a module the method
        HxBase::useWorldCoords should have been called. */
    void setWorldToTableTransform(const SbMatrix& matrix);

    /** Resets the cameras of all viewers specified by @c mask. The orientation of
        the cameras are not changed, but each camera is translated in such a way
        that all geometry displayed in the corresponding viewer becomes visible. */
    void viewAll(int mask=ALL);

    /// Renders the scenes in all viewers specified by @c mask.
    void render(int mask=ALL);

    /// Gets bit mask consisting of all viewer's auto redraw flags.
    int getAutoRedrawState() const;

    /** Sets auto redraw flag of all viewers. If flag is set the render area of
        the viewer will automatically redraw whenever something in the viewer's
        scene graph changes.*/
    void setAutoRedrawState(int mask);

    /** Sets smoothing flag of all viewers. Smoothing uses OpenGL's line- and
        point-smoothing features to provide cheap antialising of lines and points.
        This method also calls the viewer's render method if necessary.
     */
    void setSmoothing(int onOff);

    /// Returns 1, if smoothing is enabled.
    int isSmoothing();

    /// Sets strategy used to render transparent objects.
    void setTransparencyType(SoGLRenderAction::TransparencyType);

    /// Where fog starts and ends, normalized to bbox range 0...1.
    void setFogRange(float minPlane, float farPlane);

    /// Returns current transparency type.
    SoGLRenderAction::TransparencyType getTransparencyType() const;

    /** Display an Open Inventor node in all viewers specified by @c mask.
        This method is called from HxBase::showGeom and
        HxBase::hideGeom. The parameter @c owner indicates the
        base object the node belongs to. */
    void setGeom(SoNode* node, HxBase* owner, int mask=ALL);

    /** Returns the current viewer mask of an Open Inventor node. The viewer
        mask of the base object the specified node belongs too is returned.
        /sa getSource() */
    int getMask(SoNode* node);

    /** Returns the base object an Open Inventor node belongs too. HxBase
        objects insert geometry into a viewer by calling setGeom(). If
        the specified /c node is identical to a node inserted with setGeom()
        or if it is a child of such a node, the corresponding HxBase pointer
        is returned. If there is no base object associated with the node /c
        null is returned. */
    HxBase* getSource(SoNode* node);

    /** Register a pick callback. A pick callback is used to receive mouse clicks
        in a viewer which is set to interaction mode. For example, the point probe
        module uses a pick callback in order to update the position of the probe
        when the user clicks on any geometry using the middle mouse button.
        This code looks as follows:
        @code
        HxDataProbe::HxDataProbe(...) {
            ...
            // Register pick callback in the constructor
            theController->addPickCallback(pickCallback,this);
            ...
        }

        HxDataProbe::~HxDataProbe() {
            ...
            // Remove pick callback in destructor
            theController->removePickCallback(pickCallback,this);
            ...
        }

        void HxDataProbe::pickCallback(void *userData, SoEventCallback* node) {
            SoMouseButtonEvent* event = (SoMouseButtonEvent*) node->getEvent();
            if (!SO_MOUSE_BUTTON_PRESS_EVENT(event,BUTTON2))
                return;
            if (!node->getPickedPoint())
                return;
            SbVec3f point = node->getPickedPoint()->getPoint();
            ...
            // Indicates that no further pick callback should be invoked
            node->setHandled();
        }
        @endcode
    */
    void addPickCallback(SoEventCallbackCB *f, void *userData);

    /// Remove a pick callback registered with addPickCallback.
    void removePickCallback(SoEventCallbackCB *f, void *userData);

    /** Register an event callback. Any event occurring in a viewer window
        including keyboard and mouse move events is passed to an event
        callback before the event is interpreted by the viewer itself. If the
        event callback returns 1 the event is considered as being handled
        and no further processing takes place, no matter if the viewer is in
        viewing or in interaction mode. */
    void addEventCallback(HxControllerCB* cb, void* userData);

    /// insert an event callback 
    void insertEventCallback( HxControllerCB* cb, void* userData );

    /// Remove an event callback registered with addEventCallback.
    void removeEventCallback(HxControllerCB* cb, void* userData);

    /** Add a SoPickStyle which is applied for each object. */
    void addOverridePickStyle( SoPickStyle * style );

    /** Remove the SoPickStyle */
    void removeOverridePickStyle();

    /** Write scene graph as an Open Inventor file. Note, that many Amira
        modules use their own customized  Open Inventor nodes. Although these
        nodes can be written into a file other applications can't read such
        a file. Therefore, this export method should only be used for
        special purposes, e.g. for debugging. */
    void writeSceneGraph(int whichViewer, const char *fn=NULL);

    /** Returns in @c b the bounding box of all Inventor nodes in the scene except
        nodes defined by @c exclude or nodes defined by objects of type
        @c type. Returns true if the bounding box is based upon actual geometry and 
        false if it contains the standard values ([-5, 5]) because no geometry 
        matched the given criterias.
        If you need to examine the scene graph more closely
        you may also iterate over all object in the object pool and look at
        the objects root nodes returned by HxBase::getRoot(). */
    bool getBoundingBox(float b[6], HxBase* exclude=0, const McTypeInfo* type=0);

    /// Returns the scene graph root separator of a given viewer.
    SoNode* getSceneGraph(int viewer);

    /// Returns global environment node (used for setting fog etc.).
    SoEnvironment* getEnvironment();

    /// Inserts a new light into the scene graph.
    void insertLight(HxLight *light, int viewerNdx = 0);

    /**
     * To bind a context on a given viewer.
     */
    void glBindCurrent(int which = 0);
    void glBindCurrent(HxViewer* viewer);

    /**
     * To unbind a context on a given viewer.
     */
    void glUnbindCurrent(int which = 0);
    void glUnbindCurrent(HxViewer* viewer);

    /** This method deletes a texture created with glGenTextures()
        the next time the apropriate context is being rendered. */
    void glDeferredDeleteTexture(unsigned int ctxId, unsigned int textName);

    /** This method deletes a display list created with glNewLists()
        the next time the apropriate context is current. */
    void glDeferredDeleteList(unsigned int ctxtId, unsigned int listId);

    /**
	    Delete OpenGL handles in a given OpenGL Context.
	    @param ctxtId Cache Context, the handle is allocated in.
	    @param sxGLHandleDeleter heap allocated object that gets deleted when the given ctxtId is current.
    */
    void glDeferredDelete(unsigned int ctxtId, SxGLHandleDeleter* sxGLHandleDeleter);

    /** Sets the font to be used in a subsequent glText() call. Supported
        font families are at least helvetica, times, and courier. 
        On X11, if the font with the spcified family name could not be found, a font
        of an arbitrary family will be used instead.
    */
    static void glTextSetFont(int pointSize=12, bool bold=true,
        bool italic=false, const char* family="helvetica");

    /** Sets the background color of text rendered with glText(). Unless
        an alpha parameter a=0 is used the text will be drawn inside a
        semi-transparent rectangle filled with the background color. */
    static void glTextSetBackground(float r=0, float g=0, float b=0, float a=0);

    /** Sets the foreground color of text rendered with glText(). If the
        alpha parameter is not 1 (fully opaque) blending is used. */
    static void glTextSetForeground(float r=1, float g=1, float b=1, float a=1);

    enum { LEFT=-1, CENTER=0, RIGHT=1, BOTTOM=-1, TOP=1 };

    /** Sets the alignment mode for text rendered with glText(). The
        alignment mode determines how the text is positioned relative to
        the raster position specified as an argument of glText(). */
    static void glTextSetAlignment(int horizontal=LEFT, int vertical=BOTTOM);

    /** Sets an offset in pixels for rendered with glText(). The text
        will be offset by this amount relative to the raster position
        specified as an argument to glText(). */
    static void glTextSetPixelOffset(int x=0, int y=0);

    /** Renders a text using OpenGL. The properties of the rendered text
        can be modified using glTextSetFont(), glTextSetBackground(),
        glTextSetForeground(), and glTextSetAlignment(). The text may
        contain new line characters or '\\n' delimiters. In this case
        multiple lines will be printed. The arguments x, y, and z specify
        the current OpenGL raster position where the text should be
        rendered. */
    static void glText(float x, float y, float z, const char* text);

    /** Same as the glText() above, but with 2d raster position. The z
        component of the current raster position will be set to 0. */
    static void glText(float x, float y, const char* text) {
        glText(x,y,0.f,text);
    }

    /** This method calculates the area that will be covered when
        rendering the specified text using glText(). The method
        returns the number of lines in the text. */
    static int glGetTextExtent(const char* text, int& w, int& h);

    /** Obsolete. This method if provided just for compatibility with
        previous versions of Amira. */
    static int glGetFontBase(int pointSize=14);

    /** Registers a timeout method. The method will be called every
        @c msec milliseconds or as often as possible. If @c sshot is set it
        will be called only once. For example, in order to ensure that the
        compute method of a module is called automatically once every
        second, use
        @code
        theController->addTimeOutMethod(this,(HxTimeOutMethod)&compute,1000);
        @endcode
        Time out methods will not be called if the application is busy,
        i.e., if the busy cursor is set or if the stop button is active. */
    void addTimeOutMethod(HxBase* base, HxTimeOutMethod, int msec, bool sshot=0);

    /** Registers a time out function. This is identical to the above
        method except that a static c-style function is registered instead
        of a member method of a class derived from HxBase. */
    void addTimeOutFunction(void* userData, HxTimeOutFunction, int mesc, bool sshot=0);

    /// Removes a time out method registered with addTimeOutMethod.
    void removeTimeOutMethod(HxBase* base, HxTimeOutMethod);

    /// Removes a time out function registered with addTimeOutFunction.
    void removeTimeOutFunction(void* userData, HxTimeOutFunction);

    static void displaySpaceballInfo();
    static void setSpaceballMode(SpaceballMode onOff);

#ifdef USE_SPACEBALL
    static SoQtSpaceball* spaceball;        // Spaceball device
    static SpaceballMode spaceballMode;     // How to interprete events
#endif

    static int viewerCmd(ClientData, Tcl_Interp*, int argc, char** argv);

    static int fullScreenFlag;

    /// This is set if "-no_overlays" is specified on the command line.
    static int noOverlays;

    /// This is set if "-no_stencils" is specified on the command line.
    static int noStencils;

    /// This is set if "-depth_size" is specified on the command line.
    static int defaultDepthSize;

    /// Determines where fog should start or stop (values between 0...1)
    float fogRange[2];

    void checkRemoteMode();

    /// Indicate if the view should be reset (i.e. viewAll on the viewer
    /// should be called).
    /// Returns true if we have only one geometry to display.
    bool shouldResetView(int viewNum);

    /**
     *  Enable or not 'X', 'Y' and 'Z'shortcuts. True by default.
     */
    inline void setXYZShortcutsEnabled(bool enableXYZShortcuts) {m_enableXYZShortcuts = enableXYZShortcuts;}

    /**
     * Internal use only.
     */
    static SbBool eventCallback(void *userData, QEvent *xe);

  protected:
    bool m_enableXYZShortcuts;

  private:
    struct CtrlData {
        SoNode* node;
        HxBase* source;
        int mask;
        CtrlData(SoNode* nd, HxBase* src, int msk) :
            node(nd), source(src), mask(msk) { }
    };

    struct CbData {
        HxControllerCB* callback;
        void* userData;
        CbData(HxControllerCB* cb, void* ud) :
            callback(cb), userData(ud) {};
    };

    McHandle<SoEventCallback> pickCallback;
    SoEnvironment* environment;         // Environment for fogging.
    HxViewer* viewers[nViewers];        // List of all viewers
    SoSeparator* roots[nViewers];       // Root node for each viewer
    // Root node for geometry nodes which have a shader program.
    // We have to store SG with shader at the end of the graph
    // to let a chance to SORTED_LAYERS_BLEND and DELAYED_SORTED_LAYERS_BLEND
    // which contain shader to work correctly.
    SoSeparator* geomWithShaderRoots[nViewers];

    // Indicates respectively the number of nodes before the geometry nodes (resp.
    // geometry nodes with shader) added by setGeom.
    // Should updated at each addChild to roots (resp. geomWithShaderRoots).
    // Those counters are maintained/updates for each viewer.
    int numNodesBeforeGeom[nViewers];
    int numNodesBeforeGeomShader[nViewers];

    SoPickStyle * m_overridePickStyle;

    McDArray<CtrlData*> geomList;       // All geometry nodes
    McDArray<CbData*> callbackList;     // Event callbacks

#ifdef HX_HAS_X11
  public:
    /** Returns the preferred Amira visual for a specific display and
        screen. If @c stereo is true the method tries to find an OpenGL
        stereo visual. If @c attribList is not null the GLX attributes
        of the preferred visual are written into attribList. The array
        pointed to by @c attribList should have space for 32 ints. */
    static XVisualInfo* getVisualInfo(Display* display,
        int screen, int stereo, int* attribList=0);
#endif

  private:
    void* dummyVisualInfo;            // dummy, not used
    void* dummyVisualInfoStereo;   // dummy, not used

    SoGLRenderAction::TransparencyType transparencyType;
    int smoothing; // Point and line smoothing
    float boundingBox[6];
    SoTransform* tableToWorldTransform;
    SoTransform* worldToTableTransform;
    int currentViewerId;

    static void rotate(SoMotion3Event* motion, HxViewer *viewer);
    static void fly(SoMotion3Event* motion, HxViewer *viewer);
    static void smoothingCallback(void* userData, SoAction* action);

    static HxController* _theController;

    bool geomHasShaderProgram(SoNode* node);
    int getGeomWithShaderGroupIdx(int forWhichViewer);

    static void transparencyTypeCBFunc(void *userData, SoAction *action);

  public:
    static HxController*& getTheController();
};

/**
	Class for the destruction of OpenGL-Handles which must be 
	deleted in the OpenGL contexts where they are constructed. 
	Instances of this object must be heap allocated, and they
	get deleted when the right OpenGL context is current.
*/
class HXCORE_API SxGLHandleDeleter
{
public:
	virtual ~SxGLHandleDeleter();
};

#define theController (HxController::getTheController())

#endif

/// @}

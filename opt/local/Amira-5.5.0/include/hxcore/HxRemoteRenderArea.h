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
#ifndef HX_REMOTE_RENDER_AREA_H
#define HX_REMOTE_RENDER_AREA_H

#include <mclib/McVec2i.h>
#include <mclib/McVec2f.h>
#include <mclib/McBox2f.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <hxcore/HxThread.h>
#include <hxcore/HxRenderArea.h>
#include <hxcore/HxAmiraWinDLLApi.h>

#include <hxcore/hxgl.h>

#ifdef HX_HAS_X11
#include <GL/glx.h>
#include <X11/Xlib.h>
#ifdef CursorShape
    #undef CursorShape
#endif
#elif defined HX_OS_MACX
#include <AGL/agl.h>
#endif

class SoCamera;
class SoSeparator;
class SoGLRenderAction;
class QxRemoteRenderAreaWidget;
class QMouseEvent;
class SoCallback;
class SoGLContext;

/** Remote render area class. A remote render area in Amira is always
    associated with viewer 0. Whenever viewer 0 is rendered all remote
    render areas will also be rendered. On Unix platforms a remote render
    area can be rendered on a remote X11 display. */

class HXCORE_API HxRemoteRenderArea : public HxRenderArea, public HxThread {

  public:
    /** Creates a new remote render area and inserts it into the global
        list of remote render areas. @c id is an arbitrary number
        which can be used to store application data. @c geom specifies the
        size of the remote render area's window either in relative
        coordinates (upper left corner of screen is (0,0), lower right
        corner of screen is (1,1)), or in absolute pixel coordinates.

        @c display specifies the X-display on which the remote render area
        should be opened. If @c display is null, the display of viewer 0
        is used. @c hostname specifies the host on which the remote render
        area should be rendered. This argument is specific to the amira
        cluster version and usually can be set to NULL.
        
        Remote render areas with the same @c threadGroup are rendered one 
        after the other instead of in parallel. If @c threadGroup is negative,
        a new thread group will be created.
        
        In order to activate parallel rendering Amira has to be started with
        the command line option -mt or the environment variable
        AMIRA_MULTITHREAD has to be set. Otherwise rendering is done
        sequentially even if multiple thread groups have been defined. */
    static HxRemoteRenderArea* create(int id, 
                                      McBox2f& geom, 
                                      bool remote,
                                      const char* display,
                                      const char* hostname,
                                      int threadGroup=-1);

    /// Global list of remote render areas.
    static McDArray<HxRemoteRenderArea*> all;

    /// Global list of remote render areas, managed by local host.
    static McDArray<HxRemoteRenderArea*> allOnLocalHost;

    /// Deletes all remote render areas.
    static void deleteAll();

    static void deleteRenderArea(const char* host);
    static void renderAll();

    static void renderAllInThreadGroup0();

    static void swapAll();

	static void waitAll();

    static void setCursorAll(int which);

    static void enableThreads(bool);

    static bool threadsEnabled();

    static bool beginInteraction(QMouseEvent* me);

    static void endInteraction();

    static void raiseAll();

    ~HxRemoteRenderArea();

    int id() const { return theId; }

    int threadGroup() const { return theThreadGroup; }

    int width() const { return (int) (geometry.max[0]-geometry.min[0]+1); }

    int height() const { return (int) (geometry.max[1]-geometry.min[1]+1); }

    int isRemoteHost();

    void show();

    void hide();

    void startRender();

    void waitRender();

    void terminate();

    void setCursor(int which);

    virtual void setCameraMode(CameraMode mode);

    void setTransparencyType(SoGLRenderAction::TransparencyType type);
    
#ifdef HX_HAS_X11
    Display* getDisplay() const { return display; }
    Window getWindow() const { return w; }
#endif

  protected:
    HxRemoteRenderArea(int id, 
                       McBox2f& geom, 
                       bool remote, 
                       const char* display, 
                       const char* hostname,
                       int threadGroup);

    virtual void run();
    void runRemoteHost();
    void runLocal();
    int checkWindow();
    void render();
    void cleanup();
    void joinSwapGroup();

    int theId;
    int theThreadGroup;

#if defined HX_HAS_X11
    Window w;
    Colormap cmap;
    Display* display;
    unsigned int screenNum;
#elif defined(HX_OS_MACX)
    WindowRef w;
#else
    HWND w;
    HDC dc;
#endif

    SoGLContext* m_oglContext;

    McBox2f geometry;
    McString displayName;
    bool m_isRemote;
    McString hostname;
    unsigned int isStereo;
    unsigned int shouldExit;
    unsigned int readyToRender;
    unsigned int isThreadGroupLeader;
    HxThreadBarrier beforeRender;
    HxThreadBarrier beforeSwap;
    SoGLRenderAction* renderAction;
    SoCamera* viewerCamera;
    SoCamera* localCamera;
    SoSeparator* localRoot;
    SoCallback* setRemoteRenderAreaElementCB;
    int cacheContextId;
    QxRemoteRenderAreaWidget* qw;
    McVec2i desktopSize;

#ifdef HX_HAS_X11
    unsigned int cursorsCreated;
    Cursor arrowCursor,spinCursor,dollyCursor,panCursor,seekCursor;
    static int x11EventFilter(XEvent* xe);
#endif
};

#endif

/// @}

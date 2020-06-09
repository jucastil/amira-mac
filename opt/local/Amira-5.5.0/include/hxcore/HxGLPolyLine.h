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
#ifndef HX_GL_POLYLINE_H
#define HX_GL_POLYLINE_H

#include <mclib/McVec2i.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec2f.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <hxcore/HxViewerTool.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class QCursor;

/** Base class for viewer lasso tools. 

    Utility class for drawing contours in the viewer. Some modules like the
    ones derived from HxViewbase allow the user to draw contours in
    the 3D viewer so that triangles or other objects inside a contour can be
    selected. This kind of selection via contouring is implemented by the
    @c HxGLPolyLine class.

    In order to support contouring in your own module simply add a member
    variable of type @c HxGLPolyLine in your class. In the constructor a
    callback function must be set (setDoneCallback) which is called
    when contouring is finished. In the callback function the points of the
    contour may be investigated or a point selection test may be performed
    by calling isSelected. Here is a small hypothetic example:

    @code
    class MyModule : public HxModule {
        HxGLPolyLine polyline;
        McDArray<McVec3f> points;
        static void viewerSelectCB(void* userData);
        ...
    };

    MyModule::MyModule() {
        polyLine.setDoneCallback(viewerSelectCB,this);
        ...
    }

    void MyModule::compute() {
        if ( someButtonPressed() ) {
            theWorkArea->setProgressInfo("Draw contour in viewer window");
            polyLine.activate(); // Start contouring
            return;
        }
        ...
    }

    void MyModule::viewerSelectCB(void* userData) {
        MyModule m = (MyModule*) userData;
        // Perform selection test
        polyLine.startSelectionTest();
        for (int i=0; i<m->points.size(); i++)
            if (polyLine.isSelected(m->points[i]))
                selectPoint(i);
        polyLine.stopSelectionTest();
        theWorkArea->setProgressInfo("");
    }
    @endcode
*/
class HXCORE_API HxViewerLassoTool : public HxViewerModalTool
{
  public:
    /// Constructor.
    HxViewerLassoTool(const char* text, const char* iconFilename=0);

    /// Destructor.
    ~HxViewerLassoTool();

    /** Set callback which is invoked after contour has been drawn. 
        After the callback returns the tool is automatically
        deactivated and the previous tool is activated. In order to
        draw a new contour activate() has to be called again. */
    void setDoneCallback(void (*done)(void*), void* userData);

    /** Set callback which is invoked after contour has been drawn.
        If false is returned the tool remains active and a new contour
        can be drawn. If true is returned the tool is deactivated and
        the previous tool is activated. */
    void setDoneCallback(bool (*done)(void*), void* userData);

    /** This method implements the operation to be performed by the
        lasso tool. Derived tools should reimplement this method.
        The default implementation calls one of the callback methods
        described above, see setDoneCallback(). If the compute()
        method returns true, the tool deactivates itself in all
        viewers. */
    virtual bool compute();

    /** Must be called prior to the selection test. The method allocates a
        bitmask of the size of the screen. The purpose of the bitmask is to
        mark pixels located inside the contour. */
    void startSelectionTest();

    /** Returns true if projection of 3D point @c v lies inside the contour. In
        order to project @c v onto the screen the current camera settings of
        the viewer specified in the constructor are taken. */
    int isSelected(const McVec3f& v) const;

    /** Returns true if projected point @c v lies inside the contour. v
        should be in normalized viewer coords 0...1. */
    int isSelected(const McVec2f& dst) const;

    /** Project given 3D point to screen. */
    void projectToScreen(const McVec3f& v3, McVec3f& proj) const;

    /** Must be called after the selection test. The bitmask allocated in
        startSelectionTest is freed again. */
    void stopSelectionTest();

    /// Returns true if shift key was down when contouring started.
    int wasShiftDown() const;

    /// Returns true if ctrl key was down when contouring started.
    int wasCtrlDown() const;

    /// Returns true if alt key was down when contouring started.
    int wasAltDown() const;

    /// Array containing all points of last contour in screen coordinates.
    McDArray<McVec2i> points;

    /// Returns the viewer the contour should be drawn in.
    HxViewer* getViewer() const;

    /// Sets a custom cursor to be used when the class is active.
    void setCursor(const QCursor& cursor);

    /// Returns the custom cursor set for this tool.
    virtual QCursor* cursor() const;

    /// Deactivates the tool in all viewers where it is active.
    void deactivate();

    int getTestWidth();
    int getTestHeight();
    float getTestAspect();
    int isTestSet(int x, int y);

  protected:
    virtual bool processEvent(const SoEvent* e, HxViewer* viewer);
    virtual void onDeactivate(HxViewerBase* viewer);

    class HxViewerLassoToolPrivate* d;

  friend class HxGLPolyLine;
};


/** Wrapper around a lasso tool. This wrapper class is mainly
    provided for compatibility with Amira 4.0 and older versions.
    In contrast to the tool this wrapper object might be created
    on the stack or as an aggregate object. */
class HXCORE_API HxGLPolyLine {
    
  protected:
    McHandle<HxViewerLassoTool> lasso;

  public:
    /** Constructor. The constructor automatically registers the
        tool in all specified viewers. The tool will not yet be
        activated but can be activated via a keyboard short-cut. */
    HxGLPolyLine(int whichViewers=0xffff);

    /// Destructor.
    ~HxGLPolyLine();

    /// Make the tool the active tool in the specified viewer.
    void activate(int viewer=0);

    ///
    void deactivate() { lasso->deactivate(); }

    ///
    void setDoneCallback(void (*done)(void*), void* userData) { lasso->setDoneCallback(done, userData); }

    ///
    void setDoneCallback(bool (*done)(void*), void* userData) { lasso->setDoneCallback(done, userData); }

    ///
    void startSelectionTest() { lasso->startSelectionTest(); }

    ///
    int isSelected(const McVec3f& v) const { return lasso->isSelected(v); }

    ///
    int isSelected(const McVec2f& dst) const { return lasso->isSelected(dst); }

    ///
    void projectToScreen(const McVec3f& v3, McVec3f& proj) const { lasso->projectToScreen(v3,proj); }

    ///
    void stopSelectionTest() { lasso->stopSelectionTest(); }

    ///
    int wasShiftDown() const { return lasso->wasShiftDown(); }

    ///
    int wasCtrlDown() const { return lasso->wasCtrlDown(); }

    ///
    int wasAltDown() const { return lasso->wasAltDown(); }

    ///
    McDArray<McVec2i>& points;

    /// 
    HxViewer* getViewer() { return lasso->getViewer(); }

    ///
    void setCursor(const QCursor& cursor) { lasso->setCursor(cursor); }

    ///
    void setRememberAsLastToolEnabled(bool value) { lasso->setRememberAsLastToolEnabled(value); }

    ///
    bool rememberAsLastToolEnabled() const { return lasso->rememberAsLastToolEnabled(); }

    ///
    HxViewerLassoTool* getLassoTool() const { return lasso; }

    int getTestWidth() { return lasso->getTestWidth(); }
    int getTestHeight() { return lasso->getTestHeight(); }
    float getTestAspect() { return lasso->getTestAspect(); }
    int isTestSet(int x, int y) { return lasso->isTestSet(x,y); }
    static int eventCallback(const SoEvent*, HxViewer*, void*);
};

#endif

/// @}

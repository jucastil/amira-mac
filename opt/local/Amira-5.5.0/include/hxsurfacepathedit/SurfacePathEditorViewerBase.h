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

/// @addtogroup hxsurfacepathedit hxsurfacepathedit
/// @{
#ifndef SURFACE_PATH_EDITOR_VIEWER_BASE_H
#define SURFACE_PATH_EDITOR_VIEWER_BASE_H

#include <hxsurfacepathedit/hxsurfacepatheditAPI.h>
#include <hxsurfacepathedit/PathOperation.h>
#include <hxsurfacepathedit/PathEditUndoBuffer.h>
#include <hxsurfacepathedit/PathEditClickInfo.h>
#include <mclib/McTypedObject.h>

#include <hxsurfacepath/HxDisplaySurfacePathSet.h>
#include <hxsurftools/HxDisplaySurface.h>

class HxSurfacePathSet;

class HXSURFACEPATHEDIT_API SurfacePathEditorViewerBase : public McTypedObject {

    MC_HEADER(SurfacePathEditorViewerBase);

public:

    /// Constructor.
    SurfacePathEditorViewerBase(HxSurfacePathSet* paths);

    /** Default constructor.
        Call setPathSet(HxSurfacePathSet*) after this constructor! */
    SurfacePathEditorViewerBase();

    /// Destructor.
    ~SurfacePathEditorViewerBase();

    /// Return true if viewer can edit paths.
    virtual bool canEditPathSet(HxSurfacePathSet* pathSet) { return true; }

    /// Enables editing.
    virtual void activate();

    /// Disables editing.
    virtual void deactivate();

    /// Returns pointer to surface path object.
    HxSurfacePathSet* getPathSet(void);

    /// Set path set.
    virtual void setPathSet(HxSurfacePathSet* pathSet);

    /// Return selection.
    SelectionInfo& getSelection();

    /// Execute path operation and manage undo stack.
    bool exec(PathOperation* op);

    /// Update editor data.
    virtual void updateData() {}

    // ----------------- Mouse/keyboard stuff -----------------

    /// Pointer to callback function.
    void (*editCB)( void* );

    /// Pointer to callback data.
    void* editData;

    /// Set pointer to callback function.
    virtual void setEditorCallback( void (*func)(void*), void* editData )
    {
        this->editData=editData;
        editCB=func;
    }

    /// Callback for any key.
    static int keyCallBack (const SoEvent *event, HxViewer *viewer, void *userData);

    /// Implementation of keyboard-event handling.
    virtual int keyCB(const SoEvent *event) = 0;

    /** Gets the pick information from @c evCB.  This function then
        calls @c initPathClickInfo passing the picked points list to
        it.  The acquired information will be stored in @c
        clickInfo. */
    static void initClickInfo(PathEditClickInfo* clickInfo,
                              SoEventCallback* evCB,
                              HxSurfacePathSet* pathSet);

    /** This function gets the picked geometries from @c ppl.  The
        acquired information will be stored in @c clickInfo. */
    static void initPathClickInfo(PathEditClickInfo* clickInfo,
                                  HxSurfacePathSet* pathSet,
                                  const SoPickedPointList& ppl);

    /** Try to find a HxDisplaySurface module in the object pool that
        already visualizes the surface which is connected to @c ps.
        If such a module is found, it is returned.  Otherwise, a new
        module is created and returned. */
    static HxDisplaySurface* surfaceView(HxSurfacePathSet* ps);

    // ----------------- Undo/redo stuff -----------------

    /// Undo function.
    void undo(void) { mUndoBuffer.undo(); }

    /// Redo function.
    void redo(void) { mUndoBuffer.redo(); }

    /// Check whether start of undo buffer is reached.
    bool canUndo(void) { return mUndoBuffer.canUndo(); }

    /// Check whether end of undo buffer is reached.
    bool canRedo(void) { return mUndoBuffer.canRedo(); }

    /// Clear undo stack.
    void clearUndoStack() { mUndoBuffer.clear(); }

protected:

    // ----------------- Data -----------------

    /// Surface.
    HxSurface* mSurface;

    /// Pointer to surface path object.
    HxSurfacePathSet* mPathSet;

    /// Display module for the surface.
    McHandle<HxDisplaySurface> mDisplaySurface;

    /// Display module for the paths.
    McHandle<HxDisplaySurfacePathSet> mDisplayLine;

    /// Contains undo/redo information.
    PathEditUndoBuffer mUndoBuffer;

    /// Flag for mousePickCB.
    short mPickCallbackRegistered;

    // ----------------- Functions -----------------

    /// Create new SurfaceView or attach to existing one.
    HxDisplaySurface* surfaceView();

    /// Create new LineSetView or attach to existing one.
    HxDisplaySurfacePathSet* lineView();

    /// OIV callback registerd in the SurfaceView for pick events on the surface.
    static void pickCallBack(void* userData, SoEventCallback* evCB);

    /// Callback method called by pickCB.
    virtual void mousePickCB(SoEventCallback* evCB) = 0;

    /// Create specific surface node from mouse-click info.
    static SurfaceNode* createNewSurfaceNode(SurfacePathSet* pathSet, PathEditClickInfo& clickInfo, int nodeType);

private:
    
    /** If any key callbacks have been registered, this value is true,
        otherwise it is false. */
    bool mKeyCallbackRegistered;

    /** Store the type of the last hit geometry.  Also see
        PathEditClickInfo::CLICKGEOM. */
    int mLastHitGeometry;

public:

    /// Set the last hit geometry type.
    void setLastHitGeometry(int hit) { mLastHitGeometry = hit; }
	
    /// Return the last hit geometry type.
    int getLastHitGeometry() { return mLastHitGeometry; }
};

#endif

/// @}

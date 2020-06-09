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
#ifndef SINGLE_PATH_OPERATION_H
#define SINGLE_PATH_OPERATION_H

#include <hxsurfacepathedit/hxsurfacepatheditAPI.h>
#include <hxsurfacepathedit/PathOperation.h>
#include <mclib/McHandle.h>

#include <hxsurfacepath/SurfacePathSet.h>
#include <hxsurfacepath/HxDisplaySurfacePathSet.h>
#include <hxsurface/Surface.h>

class SurfacePathEditorViewerBase;

/// Abstract definition of path operations on arbitrary data.

class HXSURFACEPATHEDIT_API SinglePathOperation : public PathOperation
{

    MC_ABSTRACT_HEADER(SinglePathOperation);

public:

    /// Default constructor.
    SinglePathOperation() : mTargetPathset(0), mTargetSelection(0), mTargetSurface(0) {}

    /// Constructor (set pointer to zero, if it is unchanged by this operation).
    SinglePathOperation(SurfacePathSet* ps, SelectionInfo* sel, Surface* surf);

    /// Perform path operation.
    virtual bool exec();

    /// Initialize undo operation (copy current state).
    virtual void initUndo() { init(0); }

    /// Initialize redo operation (copy current state).
    virtual void initRedo() { init(1); }

    /// Perform undo (get undo state).
    virtual void undo() { undoRedo(0); }

    /// Perform redo (get redo state).
    virtual void redo() { undoRedo(1); }

    /// Set pointer to editor.
    void setEditor(SurfacePathEditorViewerBase* editor) { mEditor = editor; }

protected:

    /// Pathset to be modified.
    SurfacePathSet* mTargetPathset;

    /// Selection to be modified.
    SelectionInfo* mTargetSelection;

    /// Surface to be modified.
    Surface* mTargetSurface;

    /// Undo/redo buffer for pathset.
    SurfacePathSet mPathsetBuffer[2];

    /// Undo/redo buffer for selection.
    SelectionInfo mSelectionBuffer[2];

    /// Undo/redo buffer for surface.
    Surface mSurfaceBuffer[2];

    /// Pointer to editor.
    SurfacePathEditorViewerBase* mEditor;

    /// Helper function.
    void init(int which);

    /// Helper function.
    void undoRedo(int which);

    /** Update path set according to the operation that has been
        carried out.  Returns true if path set was successfully
        updated, otherwise false is returned. */
    virtual bool updatePathset() { return false; }
};

#endif

/// @}

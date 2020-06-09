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
#ifndef  EX_SCOUTLINETOOL_H
#define  EX_SCOUTLINETOOL_H

#include "ExShapeTool.h"

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McVec3f.h>

#include <vsvolren/VsSlice.h>

class ExBaseViewer;

/** Tool for picking and interacting with scout lines */
class ExScoutLineTool : public ExShapeTool {
public:

    enum PickObject {
        PO_NONE,
        PO_SCOUT_LINE,
        PO_CROP_REGION,
        PO_MEASURE,
        PO_ANNOTATION
    };

    struct PickInfo {
        PickInfo() : type(PO_NONE), oblique(false), distance(9999), shape(Ex::ArrowCursor) { }

        PickObject                      type;     // the type of object that was picked
        bool                            oblique;  // whether we want to rotate or to slice
        McDArray<McHandle<VsSlice> >    constrainedSlices;
        float                           distance; // distance in pixels to picked element
        Ex::CursorShape                 shape;    // cursor shape if something was hit
    };

    ExScoutLineTool(bool lowResSliceInteraction = true);
    virtual ~ExScoutLineTool();

    virtual bool supports(Ex::ViewerType) const;

    void setLowResSliceInteraction(bool);
    bool lowResSliceInteraction() const;

    void startScoutLineEditing(ExBaseViewer* viewer, int x, int y, const PickInfo& pickInfo);
    void stopScoutLineEditing();

    virtual bool pick(ExBaseViewer* viewer, int inX, int inY, float& outDistance);

    virtual bool processMouseEvent(ExBaseViewer* viewer, Vs::MouseEvent inEvent, int inX, int inY, 
        Vs::ButtonState inState, Ex::CursorShape& outCursor);
    virtual bool processKeyEvent(ExBaseViewer* viewer, Vs::KeyEvent inEvent, Vs::Key inKey, Vs::ButtonState inState);
    virtual bool processWheelEvent(ExBaseViewer* viewer, int inX, int inY, int inDelta);

    virtual const McString identifier() const;

    void setSlicePos(ExBaseViewer* viewer, int x, int y);

    /// The method touches all slices that use \c slice as scoutline
    /// with VsSlice::NEW_SCOUT_LINES
    static void touchScoutLines(ExBaseViewer* manager, VsSlice* slice);

private:
    bool                         mScoutLineEditing;

    bool                         mLowResSliceInteraction;

    McDArray<McHandle<VsSlice> > mConstrainedSlices;
    bool                         mOblique;
    McVec3f                      mRotateCenter;

    bool    computeScoutLine(const VsSlice* slice, const VsSlice * comp, McVec3f & a, McVec3f & b, int thickMode);
    bool    scoutLinePicked(ExBaseViewer* viewer, const VsSlice* slice, int x, int y, PickInfo& pi);
    void    modifyScoutLines(ExBaseViewer* viewer, VsSlice* slice, int x, int y);
    void    setSlicePos(ExBaseViewer* viewer, VsSlice* slice, int x, int y);
};

#endif // EX_SCOUTLINETOOL_H


/// @}

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
#ifndef  EX_CROPREGIONTOOL_H
#define  EX_CROPREGIONTOOL_H

#include "ExShapeTool.h"

#include <mclib/McBox3f.h>
#include <mclib/McVec3f.h>

class VsCropBox;
class VsCropRegion;

/** Tool for picking and interacting with scout lines */
class ExCropRegionTool : public ExShapeTool {
public:
    ExCropRegionTool();
    virtual ~ExCropRegionTool();

    virtual bool supports(Ex::ViewerType) const;

    enum PickObject {
        PO_NONE,
        PO_SCOUT_LINE,
        PO_CROP_REGION,
        PO_MEASURE,
        PO_ANNOTATION
    };

    struct PickInfo {
        PickInfo() : type(PO_NONE), info(-1), distance(9999), shape(Ex::ArrowCursor) { }

        PickObject      type;     // the type of object that was picked
        int             info;     // which object was picked. meaning depends on object type
        float           distance; // distance in pixels to picked element
        Ex::CursorShape shape;    // cursor shape if something was hit
    };

    void startCropEditing(ExBaseViewer* viewer, int x, int y, const PickInfo& pickInfo);
    void stopCropEditing();

    virtual bool pick(ExBaseViewer* viewer, int inX, int inY, float& outDistance);

    virtual bool processMouseEvent(ExBaseViewer* viewer, Vs::MouseEvent inEvent, int inX, int inY, 
        Vs::ButtonState inState, Ex::CursorShape& outCursor);
    virtual bool processKeyEvent(ExBaseViewer* viewer, Vs::KeyEvent inEvent, Vs::Key inKey, Vs::ButtonState inState);
    virtual bool processWheelEvent(ExBaseViewer* viewer, int inX, int inY, int inDelta);

private:
    bool    mCropEditing;

    McVec3f mlasttrans;

    McBox3f mRefCropBox;
    McVec3f mRefPickedPoint;
    McVec3f mRefOffset;
    int     mRefPickInfo;
    ExBaseViewer* mViewer;

    bool moveCropSlab(VsCropRegion* crop, int x, int y, int& pickInfo);
    bool cropSlabPicked(VsCropRegion* crop, const McVec3f& q, int x, int y, PickInfo& pi);
    bool cropBoxPicked(VsCropRegion* crop, const McVec3f& q, int x, int y, PickInfo& pi);
    bool cornerCutPicked(VsCropRegion* crop, const McVec3f& pickedPoint, int x, int y, PickInfo& pi);
    bool moveCutPlane(VsCropRegion* crop, int x, int y, int pickInfo);
    bool cutPlanePicked(VsCropRegion* crop, const McVec3f& q, int x, int y, PickInfo& pi);
    bool cropRegionPicked(VsCropRegion* crop, int x, int y, PickInfo& pi);
    void modifyCropRegion(VsCropRegion* crop, int x, int y, Vs::ButtonState inState);
    void adjustVolrenViewer(VsCropBox* cropBox, const McBox3f& newBox, bool allViewers);

    virtual const McString identifier() const;
};

#endif // EX_CROPREGIONTOOL_H


/// @}

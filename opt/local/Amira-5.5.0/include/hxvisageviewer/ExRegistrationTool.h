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
#ifndef  EX_REGISTRATIONTOOL_H
#define  EX_REGISTRATIONTOOL_H


#include "ExShapeTool.h"
#include "ExTrigger.h"
#include "ExToolUI.h"

#include <mclib/McVec2f.h>
#include <mclib/McMat4f.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>


#include <vsvolren/VsColorMap.h>


/** Tool for registration of two volume data sets, i.e., adjusting the relative 
    location and orientation between two volume data sets. */
class ExRegistrationTool : public ExShapeTool,
                           public ExTrigger 
{
public:
    
    ExRegistrationTool();
    ~ExRegistrationTool();

    virtual bool isActive(ExToolUI* ui = 0) const { return mState; };

    virtual bool process(ExBaseViewer* viewer, bool set);

    virtual void notified( const ExNotification& notification );

    /** returns true if a tool can be used with a viewer, else
        return false. See ExTool. */
    virtual bool supportsViewer(const ExBaseViewer* viewer) const;

    /** Returns a name for identifying the class in ExTools.
        Should be the class-name. See ExTool. */
    virtual const McString identifier() const {
        static McString const id("ExRegistrationTool");
        return id;
    }

    virtual bool processMouseEvent(ExBaseViewer* viewer, Vs::MouseEvent inEvent, int inX, int inY, 
                                   Vs::ButtonState inState, Ex::CursorShape& outCursor);
    
    virtual bool pick(ExBaseViewer* viewer, int inX, int inY, float& outDistance);

    virtual bool processKeyEvent( ExBaseViewer * viewer, Vs::KeyEvent inEvent, Vs::Key inKey, Vs::ButtonState inState );
protected:

    enum DragMode {
        DM_NO        = 0,
        DM_TRANSLATE = 1,
        DM_ROTATE    = 2,
        DM_SCALE_HOR = 3,
        DM_SCALE_VER = 4,
        DM_SHEAR_HOR = 5,
        DM_SHEAR_VER = 6
    };

    void updateRegistrationCursor(ExBaseViewer* viewer, McVec3f * ancor = NULL);

private:

    bool                  mPicked;
    DragMode              mModeForPickedObject;
    DragMode              mDragMode;
    McVec2f               mStartPoint;
    McMat4f               mStartTransform, mRefenceTransform;
    McVec3f               mRotCenter;
    McHandle<VsColorMap>  mPriColormap;
    McHandle<VsColorMap>  mSecColormap;
    float                 mPriDataWindow[2];
    float                 mSecDataWindow[2];
    int                   mFusionMode;
    int                   mSliceDecoration;
    bool                  mState;

    class VsVolume *      mPriVolume;
    class VsVolume *      mOvlVolume;
    ExBaseViewer *        mRefViewer;
    int                   mImageSet;
    static bool           sRecursionGuard;
    bool                  mIsKeyPressed;
};

#endif // EX_REGISTRATIONTOOL_H

/// @}

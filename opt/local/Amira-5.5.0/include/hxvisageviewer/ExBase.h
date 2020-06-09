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
#ifndef EXBASE_H
#define EXBASE_H

#include <vsvolren/VsObject.h>

#ifdef CursorShape
#undef CursorShape
#endif

#ifdef VS_SIEMENS_VISAGE_WS_SMI
# define VS_HAVE_BONE_MORPH   1        // also controled by license option
# define VS_HAVE_LINE_PROFILE_EXPORT 1
# define VS_HAVE_ROI_STATS    1        // also controled by license option
#endif

#ifndef VS_SIEMENS_VISAGE_WS_SMI
# define VS_HAVE_REGISTRATION 1
# define VS_HAVE_VESSEL       1
# define VS_HAVE_CURVED_SLICE 1
#endif

#if 1
# define VS_HAVE_BONE_MORPH   1 
# define VS_HAVE_ISO_SURFACE  1
# define VS_HAVE_ADD_REMOVE   1
# define VS_HAVE_CALCIUM_SCORING 1
# define VS_HAVE_CARDIO       1
# define VS_HAVE_ROI_STATS    1 
# define VS_HAVE_LINE_PROFILE_EXPORT 1
#endif

// The following strings are used in the user interface and for chosing
// the corresponding icon using hxexamine.rc
#ifdef VS_SIEMENS_VISAGE_WS_SMI 
# define EX_ANTERIOR_UI_STRING  "Ventral"
# define EX_POSTERIOR_UI_STRING "Dorsal"
# define EX_LEFT_UI_STRING      "Left"
# define EX_RIGHT_UI_STRING     "Right"
# define EX_HEAD_UI_STRING      "Superior"
# define EX_FOOT_UI_STRING      "Inferior"
#else
# define EX_ANTERIOR_UI_STRING  "Anterior"
# define EX_POSTERIOR_UI_STRING "Posterior"
# define EX_LEFT_UI_STRING      "Left"
# define EX_RIGHT_UI_STRING     "Right"
# define EX_HEAD_UI_STRING      "Head"
# define EX_FOOT_UI_STRING      "Foot"
#endif

namespace Ex {

    enum ViewerType {
        VT_UNDEFINED,
        VT_SLICE,
        VT_VOLREN,
        VT_LIGHTBOX,
        VT_STENOSIS,      // for vessel analysis
        VT_REFERENCE,     // for vessel analysis
        VT_CURVEDSLICE    // for curved slices/vessel analysis
    };

    enum LayoutType {
        LT_UNDEFINED,
        LT_SINGLE,
        LT_STACK,
        LT_PROCESSED,
        LT_TILED
    };

    enum SliceRenderMode {
        SLICEMODE_MPR = 0,
        SLICEMODE_MIP = 1,
        SLICEMODE_MINIP = 2,
        SLICEMODE_THIN = 3,
        SLICEMODE_AVERAGE = 4
    };

    enum RenderMode {
        MODE_MPR    = 0,
        MODE_MIP    = 1,
        MODE_MIPI   = 2,
        MODE_VRT    = 3,
        MODE_SVRT   = 4,
        MODE_SVRTS  = 5,
        MODE_SSD    = 6,
        MODE_DRR    = 7
    };

    enum CursorShape 
    {   // entries should match corresponding values in VsInteractionManager because 
        // some are casted internally (for example, in tools using VsOverlay)
        UndefinedCursor = -1,
        ArrowCursor,
        ForbiddenCursor,
        WaitCursor,
        SizeHorCursor,
        SizeVerCursor,
        SizeAllCursor,
        SeekCursor,
        SeekCursorAppend,
        RotateCursor,
        CurvedHandCursor,
        FlatHandCursor,
        PointingHandCursor,
        CrossCursor,
        MeasureCursor,
        ContrastCursor,
        CameraCursor,
        ScrollCursor,
        AnnotationCursor,
        MagicWandCursor,
        PencilCursor,
        DeleteCursor,
        SeekCursorNode,
        SeekCursorPoint,
        SeekCursorNodeAppend,
        SeekCursorPointAppend,
        SeekCursorEdge,
        SeekCursorEdgeAppend
    };

    enum View {
        VIEW_X  = 0,
        VIEW_Y  = 1,
        VIEW_Z  = 2,
        VIEW_minusX = 3,
        VIEW_minusY = 4,
        VIEW_minusZ = 5
    };

};


class VsDeferredNotificationLock {
    VsObject* mObject;
    bool      mOldNotificationStatus;
public:
    VsDeferredNotificationLock(VsObject* object) 
        : mObject(object)
    {
        if (mObject) {
            mObject->lock();
            mOldNotificationStatus = mObject->notificationEnabled();
            mObject->enableNotification(false);
        }
    }
    ~VsDeferredNotificationLock() {
        if (mObject) {
            mObject->enableNotification(mOldNotificationStatus);
            mObject->unlock();
            mObject->touch();
        }
    }
};

#endif // EXBASE_H

/// @}

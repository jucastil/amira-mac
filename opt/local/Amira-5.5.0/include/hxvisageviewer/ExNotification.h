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
#ifndef EX_NOTIFICATION_H
#define EX_NOTIFICATION_H

class ExBaseViewer;
class ExTool;

struct ExNotification {

    enum Type {
        NONE                            = 0,
        PROTOCOL_LOADED                 = 1,
        VOLUME_LOADED                   = 2,
        VOLUME_REMOVED                  = 3,
        ACTIVE_VIEWER_CHANGED           = 4,
        VIEWER_SIZE_CHANGED             = 5,
        ACTIVE_TOOL_CHANGED             = 6,
        SLICE_CHANGED                   = 7,
        TOOLBUTTON_CHANGED              = 10,
        FULLSCREEN_CHANGED              = 20,
        ZOOM_CHANGED                    = 100,
        PERSPECTIVE_CHANGED             = 101,
        DATA_WINDOW_CHANGED             = 102,
        FUSION_WEIGHT_CHANGED           = 103,
        FUSION_MODE_CHANGED             = 104,
        MAGIC_WAND_SEED_SET             = 105,
        SELECTION_CHANGED               = 106,
        SLICE_MIP_MODE_CHANGED          = 107,
        SLICE_SEG_MODE_CHANGED          = 108,
        SLICE_THICKNESS_CHANGED         = 109,
        VOLREN_RENDERING_MODE_CHANGED   = 110,
        VOLREN_SEG_MODE_CHANGED         = 111,
        ALPHA_FADE_CHANGED              = 112,
        _3D_QUALITY_CHANGED             = 113,
        SMART_SAMPLING_CHANGED          = 114,
        VOLUME_FILTERED                 = 115,
        THICK_SEG_MODE_CHANGED          = 116,
        WINDOW_LEVELLING_STARTED        = 200,
        WINDOW_LEVELLING_STOPPED        = 201,
        COLORMAP_CHANGED                = 300,
        CROP_REGION_CHANGED             = 301,
        MEASUREMENT_CHANGED             = 302,
        MEASUREMENT_REMOVED             = 303,
        // TODO: give LABELS_CHANGED and LABELS_MODIFIED a useful name
        // really telling the difference, or at least document the difference.
        LABELS_CHANGED                  = 304,
        LABELS_MODIFIED                 = 305,
        MOVIE_RECORD_START              = 306,
        COLORMAP_LOADED                 = 307,
        REGISTRATION_TRANSFORM_CHANGED  = 308,
        REGISTRATION_TOOL_CHANGED       = 309,
        LABELS_LOADED                   = 310,
        PATIENTINFO_TOGGLE_CHANGED      = 400,
        PIXELPROBING_TOGGLE_CHANGED     = 401,
        ANNOTATIONS_TOGGLE_CHANGED      = 402,
        ORIENTATIONINFO_TOGGLE_CHANGED  = 403,
        ORIENTATIONCUBE_TOGGLE_CHANGED  = 404,
        HISTOGRAM_TOGGLE_CHANGED        = 405,
        _2DCROSSHAIR_TOGGLE_CHANGED     = 406,
        _3DCROSSHAIR_TOGGLE_CHANGED     = 407,
        _3DBOUNDINGBOX_TOGGLE_CHANGED   = 408,
        _2DBOUNDINGBOX_TOGGLE_CHANGED   = 409,
        WINDOWLEVELLINKED_TOGGLE_CHANGED= 410,
        LINK_TRANSFORM_CHANGED          = 411,
        CURVED_SLICE_VISIBILITY_CHANGED = 412,
        VIEWER_LAYOUT_CHANGED           = 413,
        SURFACES_CHANGED                = 450,
        CLIPLABEL_CHANGED               = 451,
        ACQUISITIONINFO_TOGGLE_CHANGED  = 452,
        VESSEL_PATH_CHANGED             = 500,
        SHUTTER_ANGLE_CHANGED           = 600,
        SHUTTER_RADIUS_CHANGED          = 601,
        LUMEN_PATH_CHANGED              = 602,
        INFO_TOGGLE_CHANGED             = 700,

    };

    ExNotification(Type inType = NONE, ExBaseViewer* inViewer = 0, ExTool* inTool = 0, void* inData = 0)
        : type(inType),
          viewer(inViewer),
          tool(inTool),
          data(inData)
    {
    }

    Type           type;
    ExBaseViewer * viewer;
    ExTool       * tool;
    void         * data;
};

#endif // EX_NOTIFICATION_H

/// @}

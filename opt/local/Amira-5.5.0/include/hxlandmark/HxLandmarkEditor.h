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

/// @addtogroup hxlandmark hxlandmark
/// @{
#ifndef HX_LANDMARK_EDITOR_H
#define HX_LANDMARK_EDITOR_H

#include <hxlandmark/HxLandmarkWinDLLApi.h>
#include <mclib/McHandle.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/sensors/SoFieldSensor.h>

#include <hxcore/HxEditor.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxlandmark/HxDisplayLandmarks.h>
#include <Inventor/manips/SoTransformerManip.h>

class HxLandmarkSet;

/// Edit a landmark set.
class HXLANDMARK_API HxLandmarkEditor : public HxEditor {

    HX_HEADER(HxLandmarkEditor);

public:
    /// Constructor
    HxLandmarkEditor();

    /// Destructor
    ~HxLandmarkEditor();

    /// Edit modes.
    enum EditMode {

        /** Select mode. Allows the user to click at a marker and to
        change its type later on. */
        E_SELECT=0,

        /** Add mode. The user is requested to click at any point in the
        scene. A new marker is created at this point. */
        E_ADD,

        /** Move mode. The user first has to click at some existing marker.
        Then he or she clicks at some other location. The selected
        marker moved to the new position. */
        E_MOVE,

        /** Transform mode. The user clicks at a marker. A manipulator is
        attached to that marker. Using the manipulator position and
        orientation of the marker can be modified. */
        E_TRANSFORM,

        /** Flip mode. The user clicks at a marker. The orientation of this
        marker is inverted. Useful for PHILLIPS markers, because the
        orientation of these markers is hard to detect automatically.*/
        E_FLIP,

        /** Remove mode. The user clicks at a marker. The selected marker
        is deleted. */
        E_REMOVE
    };

    /// Flag to signal HxDisplayLandmarks the adding of the first point (via touch).
    static const unsigned int FIRST_ADDED = 512;

    /// This menu determines which edit mode is active currently.
    HxPortMultiMenu portEditMode;

    /// This menu lets the user change the type of a marker.
    HxPortMultiMenu portMarkerType;

    /// This port displays the position of the selected marker.
    HxPortInfo portPosition;

    /// 
    virtual void startEditing(HxData *data);

    /// Tcl command interface
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    ///
    virtual void fire();

    ///
    void selection(int set, int point);

    ///
    void deselection();

protected:

    struct {
        int set;
        int point;
    } selectedPoint;

    int addMarkerCurrentSet;
    void checkDisplayModule();
    static void pickCallbackCB(void *userData, SoEventCallback* node);
    void pickCallback(SoEventCallback* node);

    // This flag is set to 1 if after theController->addPickCallback()
    // has been called.
    int pickCallbackRegistered;

    void update();
    HxLandmarkSet* pointSet;
    McHandle<HxDisplayLandmarks> displayModule;

    void detachManip();
    int transformerIsAttached;
    McHandle<SoTransformerManip> transformer;

    SoFieldSensor sensor;
    static void sensorCB(void* userData, SoSensor*);
};

#endif


/// @}

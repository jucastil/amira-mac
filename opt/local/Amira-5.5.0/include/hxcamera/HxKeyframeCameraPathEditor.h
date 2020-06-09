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

/// @addtogroup hxcamera hxcamera
/// @{
#ifndef HX_KEYFRAME_CAMERA_PATH_EDITOR_H
#define HX_KEYFRAME_CAMERA_PATH_EDITOR_H

#include <mclib/McHandle.h>
#include <hxcore/HxEditor.h>
#include <hxcore/HxPortButtonList.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoAnnotation.h>
#include <Inventor/nodes/SoCallback.h>
#include <hxcamera/HxPortTimeSlider.h>
#include <hxcamera/HxPortPlayerButtons.h>
#include <hxcamera/HxDisplayCameraPath.h>
#include <hxcamera/HxKeyframeCameraPath.h>
#include <hxcamera/HxCameraWinDLLApi.h>

class SoNode;
class SoSensor;
class HideEventCatcher;

///
class HXCAMERA_API HxKeyframeCameraPathEditor : public HxEditor {

  HX_HEADER(HxKeyframeCameraPathEditor);

  public:
    /// Constructor
    HxKeyframeCameraPathEditor();

    /// Destructor
    virtual ~HxKeyframeCameraPathEditor();

    /// Start editing a labelled volume
    virtual void startEditing(HxData *data);
    
    /// Stop editing a labelled volume
    virtual void stopEditing();

    /// Tcl command interface
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

    /// This method is called whenever a port has changed.
    virtual void update();

    ///
    void  play();
    ///
    void  playbwd();
    ///
    void  stop();
    ///
    void  jmpfwd();
    ///
    void  jmpbwd();
    ///
    void  stepfwd();
    ///
    void  stepbwd(); 
    ///
    void  add();
    ///
    void  remove();

    /// Creates a circular camera path by rotating the camera of viewer 0.
    void createCircularPath(float degrees);

    /// Changes parametrisation to make velocity constant.
    void makeConstv();

protected:

    int editCameraIndex;
    int saveDepth;
    static void cameraSelectedCB(void* userData,int which, int selected) {
	((HxKeyframeCameraPathEditor*) userData)->
	    cameraSelected(which,selected);
    }

    void cameraSelected(int which, int selected);


    static void sensorCallbackCB(void* data,SoSensor* sensor) {
	((HxKeyframeCameraPathEditor*) data)->sensorCallback(sensor);
    }
    void sensorCallback(SoSensor* sensor);


    static void annotationCallbackCB(void* data,SoAction* action) {
	((HxKeyframeCameraPathEditor*) data)->annotationCallback(action);
    }
    void annotationCallback(SoAction* act) ;
    void zflow();
    McDArray<float> velocity;
    McDArray<float> length;
    float getRealTime(float t);
    void initTimeTable();
    int lockAnnotation;
    int usezflow;
    void setAnimation(float t);
    void updateKeyframeSlider();
    int playing;
    int closedPath;
    float cameraScaleFactor;
    float animationTime;
    float fps;

    HxPortTimeSlider portTimeSlider;
    HxPortPlayerButtons portPlayerButtons;

    enum{ ADD, REMOVE, CIRCULAR_PATH, CONST_VELOCITY };
    HxPortButtonList portKCPEButtons;

    McHandle<HxKeyframeCameraPath> cameraPath;
    McHandle<HxDisplayCameraPath> displayPath;
    McHandle<SoSeparator> pathGeom;
    McHandle<SoTransform> manipulator;
    McHandle<SoAnnotation> annotation;
    class SoNodeSensor* sensor;
    HideEventCatcher * eventFilter;
};

#endif


/// @}

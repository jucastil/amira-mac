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
#ifndef HX_DISPLAY_CAMERA_PATH_H
#define HX_DISPLAY_CAMERA_PATH_H

#include <mclib/McHandle.h>
#include <mclib/McHandable.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoSeparator.h>
#include <hxcamera/HxKeyframeCameraPath.h>
#include <hxcamera/HxCameraWinDLLApi.h>

/** Create Inventor Scene Graph from camerapath as polyline and
    'tetrahedra' for keyframes.*/

class HXCAMERA_API HxDisplayCameraPath : public McHandable {    
public:
    
    /** The SceneGraph will be inserted into this separator. It must not 
	contain any children. */
    HxDisplayCameraPath(SoSeparator* sep,HxKeyframeCameraPath* path,
			float sceneSize, int allowSelection=1);
    void update();
    void updateKeyframe(int which=-1);
    void updatePath();
    void setAnimatedCamera(SoCamera* cam);
    void hideAnimatedCamera();

    float getScaleFactor() { return cameraScaleFactor; }

    typedef void SelectionCallback(void* userData, int camIndex,int selected);
    void setSelectionCallback(void* userData,SelectionCallback* cb);
    void replaceTransformation(int which, SoTransform* transform);
protected:
    void* cbData;
    SelectionCallback* cbFunc;
    
    static void selectionCB(void *userData, SoPath *selectionPath) {
	((HxDisplayCameraPath*) userData)->selection(selectionPath);
    }
    static void deselectionCB(void *userData, SoPath *selectionPath) {
	((HxDisplayCameraPath*) userData)->deselection(selectionPath);
    }

    void selection(SoPath *selectionPath);
    void deselection(SoPath *selectionPath);

    static SoSeparator *createCameraGeometry(SoCamera *c, int special, float scaleFactor);

    McHandle<HxKeyframeCameraPath> theCameraPath;
    float cameraScaleFactor;
    McHandle<SoSeparator> geometry;
    McHandle<SoSeparator> keyframeRoot;
    McHandle<SoSeparator> movedCam;
    McHandle<SoSeparator> pathGeom;

    McHandle<SoLineSet> lineset;
    McHandle<SoCoordinate3> coords;
    
};

#endif // HX_DISPLAY_CAMERA_PATH_H

/// @}

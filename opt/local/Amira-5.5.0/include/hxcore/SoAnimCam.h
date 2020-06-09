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

/// @addtogroup hxcore hxcore
/// @{
#ifndef SO_ANIM_CAM_H
#define SO_ANIM_CAM_H

#include <Inventor/engines/SoSubEngine.h>
#include <Inventor/fields/SoSFRotation.h>
#include <Inventor/fields/SoSFTime.h>
#include <Inventor/nodes/SoCamera.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SoDB.h>
#include <hxcore/HxCameraPath.h>
#include <mclib/McHandle.h>
#include <mclib/McWatch.h>

/// Inventor engine used for camera animations.
class SoAnimCam : public SoEngine
{
    SO_ENGINE_HEADER (SoAnimCam);

  public:
    /// Constructor.
    SoAnimCam();

    /// Time input.
    SoSFTime timeIn;

    /// Camera orientation
    SoEngineOutput orientationOut;

    /// Camera position (why is this called directionOut ?).
    SoEngineOutput directionOut;

    /// Initializes the type.
    static void initClass();

    /// Sets animation speed in frames per second.
    void setFps(float f);

    /// Sets camera path to be played back.
    void setCameraPath(HxCameraPath* cp);

    /// Sets the camera to be animated.
    void setCamera(const SoCamera*);

  protected:
    virtual ~SoAnimCam ();

  private:
    virtual void inputChanged(SoField*);
    virtual void evaluate();

    McHandle<HxCameraPath> cameraPath;
    McHandle<SoCamera> cam;
    SbBool initState;
    float camRadius, initCamRadius, fps;
    SbVec3f camPos, initCamPos;
    SbRotation camRot, initCamRot;
    float lastSeconds;
    float time, startTime;
    McWatch swatch;
};

#endif


/// @}

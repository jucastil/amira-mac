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
#ifndef HX_CAMERA_PATH_H
#define HX_CAMERA_PATH_H

#include <Inventor/SbLinear.h>
#include <hxcore/HxData.h>

class SoCamera;

/** Base class for camera paths in Amira. A camera path is a special
    data object which is able to return an Open Inventor camera node
    for a particular time @c t (see getCamera()). Camera paths are
    used by the viewer to play back animations. A camera path object
    based on key frames is provided by the derived class
    HxKeyFrameCameraPath. */

class HXCORE_API HxCameraPath : public HxData {
    HX_HEADER(HxCameraPath);

  public:
    /**@name Some convenience functions for handling cameras. */
    //@{

    /** Assuming you could rotate from a1 to a2 using the axis r,
        which angle is between them? */
    static float getAngle(SbVec3f a1, SbVec3f a2, SbVec3f r);

    /// Set p to the up-direction of the camera
    static void UPDIR(const SoCamera *cam, SbVec3f &p);

    /// Set p to the aimpoint of the camera
    static void AIMPOINT(const SoCamera *cam, SbVec3f &p);

    /// Modify camera according to position, aimpoint, and updir.
    static void setCamera(SoCamera *cam, SbVec3f position,
        SbVec3f aimpoint, SbVec3f updir);
    //@}

    /// Constructor.
    HxCameraPath();

    /// Destructor.
    ~HxCameraPath();

    /// Checks whether camera path is closed or not.
    virtual int isClosed();

    /// Returns the length of the path in seconds.
    virtual float getDuration();

    /// Returns the start time of the path in seconds.
    virtual float getTime(int n);

    /// Creates a new camera and returns pointer to it.
    virtual SoCamera* getCamera(float t);

    /// Sets existing camera.
    virtual void getCamera(float t, SoCamera& cam);

  private:
    float startTime;
};

#endif

/// @}

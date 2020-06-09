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
#ifndef HX_CIRCULAR_CAMERA_PATH_H
#define HX_CIRCULAR_CAMERA_PATH_H

#include <Inventor/nodes/SoCamera.h>
#include <hxcore/HxCameraPath.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxtime/HxPortTime.h>
#include <hxcamera/HxCameraWinDLLApi.h>

/** This class defines a circular camera path. */

class HXCAMERA_API HxCircularCameraPath : public HxCameraPath {

  HX_HEADER(HxCircularCameraPath);

  public:
    // Constructor.
    HxCircularCameraPath();

    /// Time port for animations..
    HxPortTime portTime;
    
    /// Action button: compute circular path
    HxPortButtonMenu portAction;

    /// No info.
    virtual void info();

    /// Always returns true.
    virtual int isClosed();

    /// Returns the length of the path in seconds.
    virtual float getDuration();

    /// Returns a new perspective camera for time t.
    virtual SoCamera* getCamera(float t);

    /// Sets position and orientation of an existing camera.
    virtual void getCamera(float t, SoCamera& camera);

    /// Checks the time port.
    virtual void compute();

    /// Make sure path can be saved to a network
    virtual int saveCreation(FILE* fp, const char* dataDir, int savingFlags);

    /// Writes a command sequence initializing the ports to fp.
    virtual void savePorts(FILE* fp);

    /// Duplicates camera path.
    virtual HxData* duplicate() const;

    /// Tcl command interface of the object.
    virtual int parse(Tcl_Interp* interpreter, int argc, char **argv);

  protected:
    ~HxCircularCameraPath();

    float t0;
    float tScale;
    SbVec3f position;
    SbVec3f aimPoint;
    SbVec3f upDirection;
    SbVec3f axis;

    void recompute(int mode);
    void copyData(const HxCircularCameraPath& other);
};

#endif

/// @}

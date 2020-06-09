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
#ifndef HX_KEYFRAME_CAMERA_PATH_H
#define HX_KEYFRAME_CAMERA_PATH_H

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <hxcore/HxCameraPath.h>
#include <hxcore/HxPortButtonList.h>
#include <Inventor/nodes/SoCamera.h>
#include <hxtime/HxPortTime.h>
#include <hxcamera/HxCameraMetric.h>
#include <hxcamera/HxCameraWinDLLApi.h>

class HxCameraMetric;
class QxCameraEditorDrawArea;

/** This class defines a camera path by interpolating between a set of
    discrete key frames. While the base class HxCameraPath merely
    has a virtual function @c getCamera() this class provides methods
    for manipulating the keyframes and specifying various interpolation
    types.
*/

class HXCAMERA_API HxKeyframeCameraPath : public HxCameraPath {

  HX_HEADER(HxKeyframeCameraPath);

  public:
    /// Interpolation types.
    enum InterpolationType {
	/// Linear interpolation.
	INTERP_LINEAR,
	/// Cubic Hermite interpolation.
	INTERP_SPLINE
    };

    /// Data members.
    //@{

    // Action button (not to be released in 3.0)
    // HxPortButtonList portAction;

    /// Keyframe cameras.
    McDArray<McHandle<SoCamera> > cameras;

    /// Keyframe times.
    McDArray<float> camTime;

    /// Specifies how the camera aim points are interpolated.
    InterpolationType Aim_Interp;
    
    /// Specifies how the camera up directions are interpolated.
    InterpolationType Up_Interp;
    
    /// Specifies how the camera positions are interpolated.
    InterpolationType Pos_Interp;

    //@}

    /// Default constructor (creates no keyframes).
    HxKeyframeCameraPath();

    /// Creates camera path from an Inventor scene graph.
    HxKeyframeCameraPath(SoNode *cameraPath);

    /** Connection to current time. When this is new the cameras
        of all viewers with an active viewer mask will be set. */
    HxPortTime portTime;

    /// Overloaded methods of HxCameraPath.
    //@{

    /// Returns 1 if the camera path is closed.
    virtual int isClosed() { return closedPath; }

    /// Returns the length of the path in seconds.
    virtual float getDuration();

    /** Returns a new perspective camera with interpolated position and
	orientation. The user is responsible for deleting the camera! */
    virtual SoCamera* getCamera(float t);

    /// Sets position and orientation of an existing camera.
    virtual void getCamera(float t, SoCamera& camera);

    //@}

    /** This method creates a circular camera path. The path rotates
        around an aimpoint computed from the orientation and focalDistance
	fields of an existing camera. If @c degrees is an integer multiple
	of 360 a closed path is produced. The old path is replaced by the
	new one. */
    void createCircularPath(const SoCamera* initialCamera, float degrees=360,
	float duration=100, int nKeyFrames=16);

    int saveAscii(const char* filename);
    int saveInventor(const char* filename);
    static int readInventor(const char* filename);
    static int isCameraPath(SoNode *root);    
    void setCameraPath(SoSeparator *root);

    /** Interpolates between keyframe f1 and f1+1 with t in [0...1].
	In particular, position and orientation of the given Inventor
	camera are set. Warning: t is not arclength. If you want
	arclength, call <tt>void interp(f1,getRealTime(f1,t),...)</tt>. */
    void interp(int f1, float t, SoCamera *cam);

    ///
    void setMetric(HxCameraMetric* metric);

    /// 
    float getRealTime(int keyframe,float t);
    
    ///
    void makeConstVelocity();
    
    ///
    void setUpDir(const SbVec3f& upDir, int firstCam=0, int lastCam=-1);

    ///
    void setAimPoint(const SbVec3f& aim, int firstCam=0, int lastCam=-1);
  
    ///
    void equalDist(SbVec3f aimpoint);
    
    /// Apply or not apply the equal distance patch.
    void setEqualDistance(int flag) { equalDistFlag=flag; }

    ///
    void setPosInterp(InterpolationType type) { Pos_Interp=type; }
  
    ///
    void setAimInterp(InterpolationType type) { Aim_Interp=type; }
    
    ///
    void setUpInterp(InterpolationType type) { Up_Interp=type; }
  
    /// 
    void setClosedPath(int flag) { closedPath=flag; }

    ///
    int getNoOfKeyframes(){
	return (cameras.size());
    }
    
    /// Get temporal position of n. keyframe
    float getTime(int n);

    /** Add camera c at time t. The new camera is inserted in the list of
	keyframes. If the time and the time of an existing camera differ
	less then one ms, the existing camera will be replaced.*/
    void addKeyframe(float t, SoCamera *c);
    
    /// remove the n. keyframe
    void removeKeyframe(int n);
    
    ///
    const SoCamera *getKeyframe(int n) const { return (cameras[n]); }

    /** If you modify the camera, you have to call update afterwards,
      to make sure that the arclength table is updated.*/
    SoCamera *getKeyframe(int n) { return (cameras[n]); }

    /// update the arclength table.
    virtual void update();

    /// Checks the time port.
    virtual void compute();

    ///
    void info();

    /// overload saveCreation method to ensure proper saving of empty
    /// keyframecamera paths
    virtual int saveCreation(FILE* fp, const char* dataDir, int savingFlags);
    
    /// read from file. return != 0 in case of error.
    int read(const char *);
    
    /// read from file that  contains positions as ascii values.
    int importFile(const char *);
    
    /// save positions to file as ascii.
    int exportFile(const char *);
    
    /// save the path to a file. By default only the keyframes are saved.
    int write(const char *,int onlyKeyFrames=1);
    
    /// Tcl command interface
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Method for parsing camera commands, e.g. "path camera 0 getPosition".
    int cameraParse(Tcl_Interp* t, int argc, char **argv);

    /// Duplicates camera path.
    virtual HxData* duplicate() const;

  protected:
    ~HxKeyframeCameraPath();

    int equalDistFlag;
    int closedPath;
    int lastKeyframe;  
    int interpRot;
    
    McDArray<float> arclength;
    McHandle<HxCameraMetric> metric;

    /** Step along the spline starting at keyframe @c nr, making 100
	steps to the next keyposition. Fill the lengths into the field
	path. This is used to create an arclength parameterization.*/
    void fillPath(int nr);

    void copyData(const HxKeyframeCameraPath& other);
};

#endif

/// @}

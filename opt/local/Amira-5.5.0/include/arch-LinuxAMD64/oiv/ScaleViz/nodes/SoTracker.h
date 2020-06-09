/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Sep 2006)
**=======================================================================*/


#ifndef SO_TRACKER_H
#define SO_TRACKER_H

#include <Inventor/fields/SoSFVec3f.h>
#include <Inventor/fields/SoSFFloat.h>
#include <Inventor/fields/SoSFInt32.h>
#include <Inventor/fields/SoSFString.h>
#include <Inventor/fields/SoSFFilePathString.h>
#include <Inventor/fields/SoMFVec4f.h>

#include <Inventor/nodes/SoNode.h>

class SoTrackerImpl;
class SoTrackerReader;
class SoControllerReader;

/**
 * @SCVEXT Defines immersive viewing parameters in a MultiPipe configuration file. 
 * 
 * @ingroup ScaleVizNodes
 * 
 * @DESCRIPTION
 *  The SoTracker class is used in ScaleViz configuration file to set various
 *  parameters for an immersive, tracked environment.
 *  Some of these parameters set objects within the scene graph. The camera
 *  position is set initially to #defaultCameraPosition.
 *  A transform node  is inserted in the scene graph after the camera node.
  * This transform node contains the #defaultObjectPosition as well
 *  as the scaling (computed with) others set tracker information (trackd shared memory
 *  keys, head/wand ids...).
 *
 * @FILE_FORMAT_DEFAULT
 *    Tracker {
 *    @TABLE_FILE_FORMAT
 *       @TR defaultCameraPosition  @TD -1,-1,-1
 *       @TR defaultObjectPosition  @TD -1,-1,-1
 *       @TR defaultObjectBoxMaxDim @TD -1
 *       @TR unitScaleFactor        @TD 1.0
 *       @TR server                 @TD "0:0"
 *       @TR interEyeDistance       @TD 0.0
 *       @TR wandTrackerId          @TD 0
 *       @TR headTrackerId          @TD 1
 *       @TR wandFile               @TD "wand.iv"
 *       @TR calibrate              @TD -1.0, -1.0, -1.0, -1.0
 *    @TABLE_END
 *    }
 *
 * 
 */ 

class SCALEVIZ_API SoTracker : public SoNode
{

  SO_NODE_HEADER(SoTracker);

public :

  /**
   * Initial camera position. This is useful if head tracking will not be used.
   */    
  SoSFVec3f defaultCameraPosition;

  /**
   * Initial scene position. In a CAVE environment, it makes sense to set the
   * default postion to the center of the front wall.
   */    
  SoSFVec3f defaultObjectPosition;

  /**
   * Radius of a bounding sphere. The scene is scaled to fit initially within 
   * the sphere. In a CAVE environment, it makes sense to choose a radius equal 
   * to half the width of the front screen.
   */    
  SoSFFloat defaultObjectBoxMaxDim; 

  /**
   * A factor that will be applied to all position coordinates retrieved 
   * from the tracking system. Its value depends on the units the tracking 
   * system is using, and on the units that are appropriate in the Open Inventor 
   * world. 
   *
   * Example: The tracking system is in feet and it makes sense for Open Inventor 
   * to have inches; the unitScaleFactor should be 12.0.
   * The default value is 1.0.
   */      
  SoSFFloat unitScaleFactor;

  /**
   * Specifies a string used to initialize the connection to the tracking 
   * system. In order to connect to a VRCO trackd daemon, the string should 
   * contain the shared memory key for the trackd controller data, and the 
   * shared memory key for the trackd tracker data. The format of the
   * string is:
   *
   * "<controller key> : <tracker key>"
   *
   * The shared memory keys are defined in the trackd.conf file.
   */    
  SoSFString server;

  /**
   * Inter-eye distance with respect to the system coordinates. In an immersive
   * environment, this value should be
   * around 0.65 cm or equivalent (which is the actual average inter-eye distance
   * for humans) depending on the units used in the Open Inventor world.
   */    
  SoSFFloat interEyeDistance;

  /**
   * ID of the trackd sensor which should be used to control the wand. Default is 0.
   */    
  SoSFInt32 wandTrackerId;

  /**
   * ID of the trackd sensor which should be used to control the head/camera.
   * The default value is 1. If set to -1, headtracking is disabled and the 
   * defaultCameraPosition is used to set the camera node.
   */    
  SoSFInt32 headTrackerId;

  /**
   * Name of a geometry file that the MultiPipe viewer uses for the wand geometry.
   * The geometry should be centered at the origin, and should point towards the -z
   * axis.  
   */    
  SoSFFilePathString wandFile;

  /**
   * Optional calibration matrix that converts from actual tracker coordinates 
   * to world coordinates. The default values (-1., -1., -1., -1.) indicate that 
   * the matrix has not been defined. If actually set, the field must contain a 
   * 4x4 matrix (as four Vec4f values).
   */      
  SoMFVec4f calibrate;
  
  /**
   * Constructor.
   */    
  SoTracker();

  /**
   * Gets associated tracker reader.
   */
  SoTrackerReader* getTrackerReader();

  /**
   * Gets associated controller reader.
   */
  SoControllerReader* getControllerReader();

SoINTERNAL public:

  static void initClass();
  static void exitClass();

  SoTrackerImpl* m_soTrackerImpl;

protected:
  virtual ~SoTracker();

};

#endif

/**/

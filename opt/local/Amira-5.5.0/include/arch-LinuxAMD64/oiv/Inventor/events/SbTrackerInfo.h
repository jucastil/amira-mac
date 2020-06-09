/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Modified (MMM yyyy)
**=======================================================================*/

#ifndef  _SB_TRACKER_INFO_
#define  _SB_TRACKER_INFO_

#include <Inventor/SbLinear.h>

#ifdef OIV_NET_DOC
/**
* @VSGEXT Class for representing 3D tracker information.
* 
* @ingroup Basics
* 
* @DESCRIPTION
*   An object that stores information about the state of a 3D tracker device,
*   specifically position and orientation.
*   
*   A "tracker" is any device whose position and orientation are dynamically tracked
*   in 3D, typically for immersive VR applications. For example: a head tracker. A
*   "controller" is an input device which typically has buttons and/or valuators
*   (e.g. a joystick). Many controllers have an associated tracker. For example, the
*   commonly used "wand" input device has three buttons, a two-axis joystick (two
*   valuators), and an associated tracker.
*   
*   The virtual method SoEvent::getTrackerInfo() can be used to determine if an
*   event object has associated tracker information. Traditional 2D events like
*   SoMouseButtonEvent and SoLocation2Event return NULL. 3D events like
*   SoTrackerEvent and SoControllerButtonEvent return a reference to their associated
*   tracker information (SbTrackerInfo).
*   
*   In addition to the usual methods for setting an orientation, this class provides
*   a method that takes three Euler angles specified in radians. This allows
*   orientation information returned by the widely used trackd API to be stored
*   directly into an Open Inventor event object.
*   
*   Tracker info is most often used by Open Inventor classes to specify a direction
*   for picking or intersection with a dragger. This class provides the
*   getRay() method to conveniently get an SbLine defining the direction the
*   tracker is pointing.
*   
*   This class also provides a @B void @b* data member that could be used, for
*   example, to distinguish different tracker devices or communicate any other
*   information between an application and custom nodes in the scene graph. Open
*   Inventor does not set or use this variable.
* 
* @SEE_ALSO
*    SoControllerButtonEvent,
*    SoEvent,
*    SoTrackerEvent
* 
* 
*/ 
#else
/**
* @VSGEXT Class for representing 3D tracker information.
* 
* @ingroup Basics
* 
* @DESCRIPTION
*   An object that stores information about the state of a 3D tracker device,
*   specifically position and orientation.
*   
*   A "tracker" is any device whose position and orientation are dynamically tracked
*   in 3D, typically for immersive VR applications. For example: a head tracker. A
*   "controller" is an input device which typically has buttons and/or valuators
*   (e.g. a joystick). Many controllers have an associated tracker. For example, the
*   commonly used "wand" input device has three buttons, a two-axis joystick (two
*   valuators), and an associated tracker.
*   
*   The virtual method SoEvent::getTrackerInfo() can be used to determine if an
*   event object has associated tracker information. Traditional 2D events like
*   SoMouseButtonEvent and SoLocation2Event return NULL. 3D events like
*   SoTrackerEvent and SoControllerButtonEvent return a pointer to their associated
*   tracker information (SbTrackerInfo).
*   
*   In addition to the usual methods for setting an orientation, this class provides
*   a method that takes three Euler angles specified in radians. This allows
*   orientation information returned by the widely used trackd API to be stored
*   directly into an Open Inventor event object.
*   
*   Tracker info is most often used by Open Inventor classes to specify a direction
*   for picking or intersection with a dragger. This class provides the
*   getRay() method to conveniently get an SbLine defining the direction the
*   tracker is pointing.
*   
*   This class also provides a @B void @b* data member that could be used, for
*   example, to distinguish different tracker devices or communicate any other
*   information between an application and custom nodes in the scene graph. Open
*   Inventor does not set or use this variable.
* 
* @SEE_ALSO
*    SoControllerButtonEvent,
*    SoEvent,
*    SoTrackerEvent
* 
* 
*/ 
#endif //OIV_NET_DOC


class INVENTOR_API SbTrackerInfo {
    
 public:

  /**
   * Constructor.
   */
  SbTrackerInfo();
  /**
   * Destructor.
   */
  ~SbTrackerInfo();
    
  /**
   * Set position of tracker in world coordinates.
   */
  void            setPosition3(const SbVec3f &p)      { m_position3 = p; }

  /**
   * Get position of tracker in world coordinates.
   */
  const SbVec3f &     getPosition3() const            { return m_position3; }

  /**
   * Get orientation of tracker as a standard Open Inventor rotation
   * (quaternion).
   */
  const SbRotation &getOrientation() const { return m_orientation; }

  /**
   * Get orientation of tracker. Return value as axis and angle.
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  void  getOrientation(SbVec3f &axis, float &angle) const
    { m_orientation.getValue(axis, angle); }

  /**
   * Set orientation value from 4 floats defining the rotation quaternion.
   */
  void  setOrientation(float q0, float q1, float q2, float q3)
    { m_orientation.setValue( q0, q1, q2, q3 ); }
    
  /**
   * Set orientation value from array of 4 floats defining the rotation quaternion.
   */
  void  setOrientation(const float q[4])
    { m_orientation.setValue( q ); }

  /**
   * Set orientation value from axis and angle in radians.
   */
  void  setOrientation(const SbVec3f &axis, float angle)
    { m_orientation.setValue( axis, angle ); }

  /**
   * Set orientation value from an SbRotation.
   */
  void  setOrientation( SbRotation orientation )
    { m_orientation = orientation; }

  /**
   * Set orientation value from Euler angles in radians
   * (using the trackd convention Z*X*Y).
   */
  void  setOrientation( float xangle, float yangle, float zangle );

  /**
   * Convenience function to get ray for picking/intersecting.
   */
  const SbLine getRay() const;

  /**
   * Set application data.
   */
  void  setData( void *appData ) { m_data = appData; }

  /**
   * Get application data.
   */
  const void *getData() const    { return m_data;    }
    
 private:

  // Essential tracker info
  SbVec3f    m_position3;
  SbRotation m_orientation;

  void      *m_data;

};

#endif /* _SB_TRACKER_INFO_ */


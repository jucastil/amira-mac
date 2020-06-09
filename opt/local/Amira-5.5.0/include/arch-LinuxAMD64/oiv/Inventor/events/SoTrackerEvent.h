/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Modified (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_TRACKER_EVENT_
#define  _SO_TRACKER_EVENT_

#include <Inventor/events/SoSubEvent.h>
#include <Inventor/events/SbTrackerInfo.h>


#ifdef OIV_NET_DOC
/**
* @VSGEXT 3D tracker event.
*
* @ingroup events
*
* @DESCRIPTION
*   SoTrackerEvent represents 3D position and orientation events in the Open
*   Inventor event model.
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
*   Many tracker devices generate a continuous stream of position and orientation
*   reports, so strictly speaking there are no "events." Generally Open Inventor
*   classes that recognize the SoTrackerEvent interpret it as notification of a
*   "significant" change in the tracker position and/or orientation. Processing of
*   SoTrackerEvents may be relatively expensive. For example, a pick operation will
*   usually be done automatically. The application (or other software above Open
*   Inventor) is responsible for deciding when to actually create an SoTrackerEvent.
*
* @SEE_ALSO
*    SoControllerButtonEvent,
*    SoEvent,
*    SbTrackerInfo
*
*
*/
#else
/**
* @VSGEXT 3D tracker event.
*
* @ingroup events
*
* @DESCRIPTION
*   SoTrackerEvent represents 3D position and orientation events in the Open
*   Inventor event model.
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
*   Many tracker devices generate a continuous stream of position and orientation
*   reports, so strictly speaking there are no "events." Generally Open Inventor
*   classes that recognize the SoTrackerEvent interpret it as notification of a
*   "significant" change in the tracker position and/or orientation. Processing of
*   SoTrackerEvents may be relatively expensive. For example, a pick operation will
*   usually be done automatically. The application (or other software above Open
*   Inventor) is responsible for deciding when to actually create an SoTrackerEvent.
*
* @SEE_ALSO
*    SoControllerButtonEvent,
*    SoEvent,
*    SbTrackerInfo
*
*
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoTrackerEvent : public SoEvent {

  SO_EVENT_HEADER();

 public:
  /**
   * Constructor.
   */
  SoTrackerEvent();

#ifndef HIDDEN_FROM_DOC
  virtual ~SoTrackerEvent();
#endif // HIDDEN_FROM_DOC

  /**
   * Set position of associated tracker in world coordinates.
   */
  void                setPosition3(const SbVec3f &p)
    { m_trackerInfo.setPosition3( p ); }

  /**
   * Get position of associated tracker in world coordinates.
   */
  const SbVec3f &     getPosition3() const
    { return m_trackerInfo.getPosition3(); }

  /**
   * Set orientation value of associated tracker from Euler angles in radians
   * (using the trackd convention Z*X*Y).
   */
  void  setOrientation( float x, float y, float z)
    { m_trackerInfo.setOrientation( x, y, z ); }

  /**
   * Set orientation value of associated tracker from an SbRotation.
   */
  void  setOrientation( SbRotation orientation )
    { m_trackerInfo.setOrientation( orientation ); }

  /**
   * Set orientation value of associated tracker from axis and angle in radians.
   */
  void  setOrientation(const SbVec3f &axis, float angle)
    { m_trackerInfo.setOrientation( axis, angle ); }

  /**
   * Get orientation of associated tracker as a standard
   * Open Inventor rotation (quaternion).
   */
  const SbRotation & getOrientation() const
    { return m_trackerInfo.getOrientation(); }

  /**
   * Get a ray for picking/intersecting. This is a convenience function.
   */
  const SbLine getRay() const
    { return m_trackerInfo.getRay(); }


  // Imports declaration from SoEvent.
  using SoEvent::getTrackerInfo;

#ifdef OIV_NET_DOC
  /**
  * Returns the SbTrackerInfo object.
  * Can be used as a quick check if an event has tracker info
  * associated with it.
  * [OIV-WRAPPER-RETURN-TYPE VALUE]
  */

#else
  /**
  * Returns a const pointer to the SbTrackerInfo object.
  * Can be used as a quick check if an event has tracker info
  * associated with it.
  */

#endif //OIV_NET_DOC
  virtual const SbTrackerInfo *getTrackerInfo() const
    { return &m_trackerInfo; }

  /**
   * Returns the SbTrackerInfo object.
   */
  virtual const SbTrackerInfo & trackerInfo() const
    { return m_trackerInfo; }

 SoINTERNAL public:
  static void initClass();
  static void exitClass();

 private:
  SbTrackerInfo m_trackerInfo;

};

#endif /* _SO_TRACKER_EVENT_ */

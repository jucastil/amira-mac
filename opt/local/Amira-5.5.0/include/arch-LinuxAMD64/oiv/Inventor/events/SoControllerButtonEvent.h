/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Modified (MMM yyyy)
**=======================================================================*/

#ifndef  _SO_CONTROLLER_BUTTON_EVENT_
#define  _SO_CONTROLLER_BUTTON_EVENT_

#include <Inventor/events/SoButtonEvent.h>
#include <Inventor/events/SbTrackerInfo.h>

// some convenience macros for determining if an event matches

#define SO_CONTROLLER_PRESS_EVENT(EVENT,BUTTON) \
    (SoControllerButtonEvent::isButtonPressEvent(EVENT,SoControllerButtonEvent::BUTTON))

#define SO_CONTROLLER_RELEASE_EVENT(EVENT,BUTTON) \
    (SoControllerButtonEvent::isButtonReleaseEvent(EVENT,SoControllerButtonEvent::BUTTON))


#ifdef OIV_NET_DOC
/**
* @VSGEXT Controller button press and release event.
*
* @ingroup events
*
* @DESCRIPTION
*   SoControllerButtonEvent represents controller button press and release events in
*   the Open Inventor event model. A controller device generally has associated 3D
*   tracker information.
*
*   A "tracker" is any device whose position and orientation are dynamically tracked
*   in 3D, typically for immersive VR applications. For example: a head tracker. A
*   "controller" is an input device which typically has buttons and/or valuators
*   (e.g. a joystick). Many controllers have an associated tracker. For example, the
*   commonly used "wand" input device has three buttons, a two-axis joystick (two
*   valuators), and an associated tracker.
*
*
*   The virtual method SoEvent::getTrackerInfo() can be used to determine if an
*   event object has associated tracker information. Traditional 2D events like
*   SoMouseButtonEvent and SoLocation2Event return NULL. 3D events like
*   SoTrackerEvent and SoControllerButtonEvent return a reference to their associated
*   tracker information (SbTrackerInfo).
*
*   Many controller devices generate a continuous stream of data, so strictly
*   speaking there are no "events". However Open Inventor classes that recognize the
*   SoControllerButtonEvent interpret it as notification of a change in the button
*   state (press or release). The application (or other software above Open
*   Inventor) is responsible for deciding when to actually create an
*   SoControllerButtonEvent.
*
*   Some convenience macros for determining if an event matches
*     - SO_CONTROLLER_PRESS_EVENT(EVENT,BUTTON)
*     - SO_CONTROLLER_RELEASE_EVENT(EVENT,BUTTON)
*
* @SEE_ALSO
*    SbTrackerInfo,
*    SoEvent,
*    SoTrackerEvent
*
*
*/
#else
/**
* @VSGEXT Controller button press and release event.
*
* @ingroup events
*
* @DESCRIPTION
*   SoControllerButtonEvent represents controller button press and release events in
*   the Open Inventor event model. A controller device generally has associated 3D
*   tracker information.
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
*   Many controller devices generate a continuous stream of data, so strictly
*   speaking there are no "events". However Open Inventor classes that recognize the
*   SoControllerButtonEvent interpret it as notification of a change in the button
*   state (press or release). The application (or other software above Open
*   Inventor) is responsible for deciding when to actually create an
*   SoControllerButtonEvent.
*
*   Some convenience macros for determining if an event matches
*     - SO_CONTROLLER_PRESS_EVENT(EVENT,BUTTON)
*     - SO_CONTROLLER_RELEASE_EVENT(EVENT,BUTTON)
*
* @SEE_ALSO
*    SbTrackerInfo,
*    SoEvent,
*    SoTrackerEvent
*
*
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoControllerButtonEvent : public SoButtonEvent {

  SO_EVENT_HEADER();

 public:

   /** Button */
  enum Button {
    ANY     = 0,
    /**
     *  Controller button 1
     */
    BUTTON1 = 1,
    /**
     *  Controller button 2
     */
    BUTTON2 = 2,
    /**
     *  Controller button 3
     */
    BUTTON3 = 3
  };

  /**
   * Constructor.
   */
  SoControllerButtonEvent();
#ifndef HIDDEN_FROM_DOC
  virtual ~SoControllerButtonEvent();
#endif // HIDDEN_FROM_DOC

  /**
   * Set which button generated the event.
   */
  void                setButton(SoControllerButtonEvent::Button b)  { button = b; }
  /**
   * Get which button generated the event.
   */
  SoControllerButtonEvent::Button     getButton() const { return button; }

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
  * Can be used as a quick check if an SoEvent has tracker info
  * associated with it.
  * [OIV-WRAPPER-RETURN-TYPE VALUE]
  */

#else
  /**
  * Returns a const pointer to the SbTrackerInfo object.
  * Can be used as a quick check if an SoEvent has tracker info
  * associated with it.
  */

#endif //OIV_NET_DOC
  virtual const SbTrackerInfo *getTrackerInfo() const
    { return &m_trackerInfo; }

  /**
   * Get the SbTrackerInfo object.
   */
  virtual const SbTrackerInfo & trackerInfo() const
    { return m_trackerInfo; }

  /**
   * Convenience function to see if an SoEvent is a press of the passed
   * mouse button.
   */
  static SbBool       isButtonPressEvent(
                                         const SoEvent *e,
                                         SoControllerButtonEvent::Button whichButton);

  /**
   * Convenience function to see if an SoEvent is a release of the passed
   * mouse button.
   */
  static SbBool       isButtonReleaseEvent(
                                           const SoEvent *e,
                                           SoControllerButtonEvent::Button whichButton);

 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

 private:
  Button        button;       // which button
  SbTrackerInfo m_trackerInfo;

};

#endif /* _SO_CONTROLLER_BUTTON_EVENT_ */

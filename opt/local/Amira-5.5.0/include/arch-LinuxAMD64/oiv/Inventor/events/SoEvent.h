/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifndef  _SO_EVENT_
#define  _SO_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/SbViewportRegion.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbTime.h>
#include <Inventor/SoTypedObject.h>

class SbTrackerInfo;

#ifdef OIV_NET_DOC
/**
* Base class for all events.
*
* @ingroup events
*
* @DESCRIPTION
*   SoEvent is the base class for events in the Open Inventor event model. An event
*   typically represents a user action, such as a mouse button being pressed or a
*   keyboard key being released. SoEvent contains general information found in all
*   Open Inventor events, including the time the event occurred, the position of the
*   locater when the event occurred, and the state of the modifier keys when the
*   event occurred.
*
*   The virtual method SoEvent::getTrackerInfo() can be used to determine if an
*   event object has associated 3D tracker information. Traditional 2D events like
*   SoMouseButtonEvent and SoLocation2Event return NULL. 3D events like
*   SoTrackerEvent and SoControllerButtonEvent return a reference to their associated
*   tracker information (SbTrackerInfo).
*
* @SEE_ALSO
*    SoButtonEvent,
*    SoControllerButtonEvent,
*    SoKeyboardEvent,
*    SoLocation2Event,
*    SoMotion3Event,
*    SoMouseButtonEvent,
*    SoSpaceballButtonEvent,
*    SoTrackerEvent,
*    SoHandleEventAction,
*    SoEventCallback,
*    SoSelection,
*    SoInteraction,
*    SoWinDevice,
*    SoWinRenderArea
*
*
*/
#else
/**
* Base class for all events.
*
* @ingroup events
*
* @DESCRIPTION
*   SoEvent is the base class for events in the Open Inventor event model. An event
*   typically represents a user action, such as a mouse button being pressed or a
*   keyboard key being released. SoEvent contains general information found in all
*   Open Inventor events, including the time the event occurred, the position of the
*   locater when the event occurred, and the state of the modifier keys when the
*   event occurred.
*
*   The virtual method SoEvent::getTrackerInfo() can be used to determine if an
*   event object has associated 3D tracker information. Traditional 2D events like
*   SoMouseButtonEvent and SoLocation2Event return NULL. 3D events like
*   SoTrackerEvent and SoControllerButtonEvent return a pointer to their associated
*   tracker information (SbTrackerInfo).
*
* @SEE_ALSO
*    SoButtonEvent,
*    SoControllerButtonEvent,
*    SoKeyboardEvent,
*    SoLocation2Event,
*    SoMotion3Event,
*    SoMouseButtonEvent,
*    SoSpaceballButtonEvent,
*    SoTrackerEvent,
*    SoHandleEventAction,
*    SoEventCallback,
*    SoSelection,
*    SoInteraction,
*    SoWinDevice,
*    SoWinRenderArea
*
*
*/
#endif //OIV_NET_DOC


class INVENTOR_API SoEvent: public SoTypedObject {
 public:

  /**
   * Constructor.
   */
  SoEvent();
  /**
   * Destructor.
   */
  virtual ~SoEvent();

  /**
   * Returns the type id for this event instance.
   */
  virtual SoType      getTypeId() const;

  /**
   * Returns the type id for the SoEvent class.
   */
  static SoType       getClassTypeId();

  /**
   * Sets the time at which the event occurred.
   */
  void                setTime(SbTime t)               { timestamp = t; }
  /**
   * Gets the time at which the event occurred.
   */
  SbTime              getTime() const                 { return timestamp; }

  /**
   * Sets the window pixel location of the cursor when the event occurred. The
   * position is relative to the lower left corner of the window in which the event
   * occurred.
   */
  void                setPosition(const SbVec2s &p)   { position = p;
                                                        positionFloat[0] = (float)position[0];
                                                        positionFloat[1] = (float)position[1];}

  /**
   *  Float version of #setPosition(const SbVec2s &p). It can be used when a desktop is magnified
   *  on a wall of screens using ScaleViz with a tracker device calibrated for this wall.
   */
  void                setPosition(const SbVec2f &p)   { positionFloat = p;
                                                        position[0] = (short)positionFloat[0];
                                                        position[1] = (short)positionFloat[1];}


  /**
   * Gets the window pixel location of the cursor when the event occurred. The
   * position is relative to the lower left corner of the window in which the event
   * occurred.
   */
  const SbVec2s &     getPosition() const             { return position; }

  /**
   *  Float version of #getPosition(). It can be used when a desktop is magnified
   *  on a wall of screens using ScaleViz with a tracker
   *  device calibrated for this wall.
   */
  const SbVec2f &     getPositionFloat() const             { return positionFloat; }

  /**
   * Gets the viewport pixel location of the cursor when the event occurred, relative
   * to the specified viewport region.
   */
  const SbVec2s &     getPosition(const SbViewportRegion &vpRgn) const;

  /**
   * Float version of #getPosition. It can be used
   * when a desktop is magnified on a wall of screens using ScaleViz with a tracker
   * device calibrated for this wall.
   */
  const SbVec2f &     getPositionFloat(const SbViewportRegion &vpRgn) const;

  /**
   * Gets the normalized location of the cursor when the event occurred, relative to
   * the specified viewport region. The returned value will lie between 0.0 and 1.0.
   */
  const SbVec2f & getNormalizedPosition(const SbViewportRegion &vpRgn) const;

  /**
   * Sets whether the shift key was down when the event occurred.
   */
  void                setShiftDown(SbBool isDown)     { shiftDown = isDown; }
  /**
   * Sets whether the CTRL key was down when the event occurred.
   */
  void                setCtrlDown(SbBool isDown)      { ctrlDown = isDown; }
  /**
   * Sets whether the ALT key was down when the event occurred.
   */
  void                setAltDown(SbBool isDown)       { altDown = isDown; }
  /**
   * Sets whether mouse Button 1 was down when the event occurred.
   */
  void                setButton1Down(SbBool isDown)       { button1Down = isDown; }

  /**
   * Returns true if the shift key was down when the event occurred.
   */
  SbBool              wasShiftDown() const            { return shiftDown; }
  /**
   * Returns true if the CTRL key was down when the event occurred.
   */
  SbBool              wasCtrlDown() const             { return ctrlDown; }
  /**
   * Returns true if the ALT key was down when the event occurred.
   */
  SbBool              wasAltDown() const              { return altDown; }
  /**
   * Returns true if mouse button 1 was down when the event occurred.
   */
  SbBool              wasButton1Down() const              { return button1Down; }

  /**
   * Gets whether an event object has associated tracker information.
   * [OIV-WRAPPER-RETURN-TYPE-VALUE]
   */
  virtual const SbTrackerInfo *getTrackerInfo() const { return NULL; }

  /**
   * Gets whether an event object has associated tracker information.
   * [OIV-WRAPPER-RETURN-TYPE-VALUE]
   * [OIVJAVA-WRAPPER NO_WRAP]
   */
  inline SbTrackerInfo* getTrackerInfo();

 SoINTERNAL public:
  // Initializes base event class
  static void         initClass();
  static void exitClass();

  // Initialize ALL Inventor event classes
  static void         initClasses();
  static void exitClasses();

 private:
  // all of these are set according to when the event occurred
  SbTime              timestamp;   // time the event occurred
  SbBool              shiftDown;   // TRUE if shift key was down
  SbBool              ctrlDown;    // TRUE if ctrl key was down
  SbBool              altDown;     // TRUE if alt key was down
  SbBool              button1Down; // TRUE if first mouse button was down

  SbVec2s             position;         // locator position when event occurred
  SbVec2f             positionFloat;    // locator position when event occurred
  SbVec2s             viewportPos;      // position relative to viewport
  SbVec2f             viewportPosFloat;  // position relative to viewport
  SbVec2f             normalizedPos;    // normalized position

  static SoType      classTypeId; // base typeId for all events
};

SbTrackerInfo* SoEvent::getTrackerInfo()
{
  const ::SoEvent* constEvent = this;
  return const_cast< ::SbTrackerInfo* >(constEvent->getTrackerInfo());
}

#endif /* _SO_EVENT_ */


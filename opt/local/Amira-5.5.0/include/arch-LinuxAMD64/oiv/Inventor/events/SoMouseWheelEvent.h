/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MOUSEWHEEL_EVENT_
#define  _SO_MOUSEWHEEL_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/events/SoSubEvent.h>


/**
 * Mouse wheel events.
 * 
 * @ingroup events
 * 
 * @DESCRIPTION
 *   SoLocation2Event represents 2D location events in the Open Inventor event model.
 *
 * The wheel has discrete, evenly spaced notches. When you rotate the
 * wheel, a wheel message is sent as each notch is encountered. Most
 * modern mouse wheels generate an event with a value of 120 per each
 * notch of the wheel. If necessary, you can use environment
 * variable OIV_WHEEL_DELTA to change this value (see SoPreferences). Pressing the shift
 * key while moving the mouse wheel will generate events of double
 * the wheel delta (i.e., 240 by default).
 *
 * The methods #getDelta() and #setDelta() return and set the distance 
 * that the mouse wheel
 * has been rotated. A positive value indicates the wheel was rotated
 * forward (away from the user); a negative value indicates the wheel
 * was rotated backwards (toward the user). The values are specified 
 * in multiples of the wheel delta.
 * 
 * @SEE_ALSO
 *    SoEvent,
 *    SoButtonEvent,
 *    SoKeyboardEvent,
 *    SoMotion3Event,
 *    SoMouseButtonEvent,
 *    SoSpaceballButtonEvent,
 *    SoHandleEventAction,
 *    SoEventCallback,
 *    SoSelection,
 *    SoInteraction,
 *    SoWinDevice,
 *    SoMouseWheelEvent
 * 
 * 
 */ 

class INVENTOR_API SoMouseWheelEvent : public SoEvent {

  SO_EVENT_HEADER();
    
 public:
  
  /**
   * Constructor.
   */
  SoMouseWheelEvent();

  /** Sets the mouse wheel delta. 
   */
  void                setDelta(int delta)  { m_delta = delta; }

  /**
   * Gets the mouse wheel delta.
   */
  int  getDelta() const   { return m_delta; }


#ifndef HIDDEN_FROM_DOC
  virtual ~SoMouseWheelEvent();
#endif // HIDDEN_FROM_DOC
    
 SoINTERNAL public:
  static void     initClass();
  static void exitClass();
  int   getDefaultDelta();
  int   SO_WHEEL_DELTA;
 private:
   int m_delta;
};


#endif /* _SO_MOUSEWHEEL_EVENT_ */


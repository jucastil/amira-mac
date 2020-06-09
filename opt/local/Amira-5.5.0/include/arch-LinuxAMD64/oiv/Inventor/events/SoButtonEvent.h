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


#ifndef  _SO_BUTTON_EVENT_
#define  _SO_BUTTON_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoSubEvent.h>


/**
 * Base class for all button events.
 * 
 * @ingroup events
 * 
 * @DESCRIPTION
 *   SoButtonEvent represents generic button press and release events in the Open
 *   Inventor event model. It is the base class for device-specific button events,
 *   namely SoControllerButtonEvent, SoKeyboardEvent, SoMouseButtonEvent, and
 *   SoSpaceballButtonEvent. This class stores the down/up state of the button when
 *   the event occurred.
 * 
 * @SEE_ALSO
 *    SoEvent,
 *    SoControllerButtonEvent,
 *    SoKeyboardEvent,
 *    SoLocation2Event,
 *    SoMotion3Event,
 *    SoMouseButtonEvent,
 *    SoSpaceballButtonEvent,
 *    SoHandleEventAction,
 *    SoEventCallback,
 *    SoSelection,
 *    SoInteraction,
 *    SoWinDevice
 * 
 * 
 */ 

class INVENTOR_API SoButtonEvent : public SoEvent {

  SO_EVENT_HEADER();
    
 public:
  /**
   * Constructor.
   */
  SoButtonEvent();

#ifndef HIDDEN_FROM_DOC
  virtual ~SoButtonEvent();
#endif // HIDDEN_FROM_DOC
    
  /** State */
  enum State {
    /**
     *  Button up event 
     */
    UP, 
    /**
     *  Button down event 
     */
    DOWN,
	/**
     *  Button double click event 
     */
    DBCLK,
    /**
     *  Button in unknown state 
     */
    UNKNOWN
  };
    
  /**
   * Sets the state of the button.
   */
  void                 setState(SoButtonEvent::State s)   { state = s; }
  /**
   * Gets the state of the button.
   */
  SoButtonEvent::State getState() const           { return state; }
    
 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

 private:
  State           state;       // up, down, or unknown

};


#endif /* _SO_BUTTON_EVENT_ */


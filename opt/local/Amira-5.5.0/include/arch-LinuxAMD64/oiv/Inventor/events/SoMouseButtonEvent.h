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


#ifndef  _SO_MOUSE_BUTTON_EVENT_
#define  _SO_MOUSE_BUTTON_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>

// some convenience macros for determining if an event matches

#define SO_MOUSE_PRESS_EVENT(EVENT,BUTTON) \
    (SoMouseButtonEvent::isButtonPressEvent(EVENT,SoMouseButtonEvent::BUTTON))

#define SO_MOUSE_RELEASE_EVENT(EVENT,BUTTON) \
    (SoMouseButtonEvent::isButtonReleaseEvent(EVENT,SoMouseButtonEvent::BUTTON))




/**
 * Mouse button press and release events.
 * 
 * @ingroup events
 * 
 * @DESCRIPTION
 *   SoMouseButtonEvent represents mouse button press and release events in the Open
 *   Inventor event model.
 * 
 *   Some convenience macros for determining if an event matches
 *     - SO_MOUSE_PRESS_EVENT(EVENT,BUTTON)
 *     - SO_MOUSE_RELEASE_EVENT(EVENT,BUTTON)
 *
 * @SEE_ALSO
 *    SoEvent,
 *    SoButtonEvent,
 *    SoKeyboardEvent,
 *    SoLocation2Event,
 *    SoMotion3Event,
 *    SoSpaceballButtonEvent,
 *    SoHandleEventAction,
 *    SoEventCallback,
 *    SoSelection,
 *    SoInteraction,
 *    SoWinDevice
 * 
 * 
 */ 

class INVENTOR_API SoMouseButtonEvent : public SoButtonEvent {

  SO_EVENT_HEADER();
    
 public:

   /** Button */
  enum Button {
    /**
     *  Any button 
     */
    ANY = 0, 
    /**
     *  First mouse button 
     */
    BUTTON1 = 1, 
    /**
     *  Second mouse button 
     */
    BUTTON2 = 2, 
    /**
     *  Third mouse button 
     */
    BUTTON3 = 3
  };
    
  /**
   * Constructor.
   */
  SoMouseButtonEvent();

#ifndef HIDDEN_FROM_DOC
  virtual ~SoMouseButtonEvent();
#endif // HIDDEN_FROM_DOC
    
  /**
   * Sets which mouse button generated the event.
   */
  void                setButton(SoMouseButtonEvent::Button b)  { button = b; }
  /**
   * Gets which mouse button generated the event.
   */
  SoMouseButtonEvent::Button  getButton() const           { return button; }
    
  /**
   * Returns whether the passed event is a mouse button press event of the
   * passed button. When SoMouseButtonEvent::ANY is passed, this returns TRUE if the
   * event represents a button press of any mouse button.
   */
  static SbBool       isButtonPressEvent(
                                         const SoEvent *e,
                                         SoMouseButtonEvent::Button whichButton);

	/**
   * Returns whether the passed event is a mouse button double click event of the
   * passed button. When SoMouseButtonEvent::ANY is passed, this returns TRUE if the
   * event represents a button press of any mouse button.
   */
  static SbBool isButtonDoubleClickEvent( const SoEvent* e,
																					SoMouseButtonEvent::Button whichButton );
                            
  /**
   * Returns whether the passed event is a mouse button release event of the
   * passed button. When SoMouseButtonEvent::ANY is passed, this returns TRUE if the
   * event represents a button release of any mouse button.
   */
  static SbBool       isButtonReleaseEvent(
                                           const SoEvent *e,
                                           SoMouseButtonEvent::Button whichButton);
    
 SoINTERNAL public:
  static void         initClass();
  static void exitClass();

 private:
  Button          button;     // which button

};


#endif /* _SO_MOUSE_BUTTON_EVENT_ */


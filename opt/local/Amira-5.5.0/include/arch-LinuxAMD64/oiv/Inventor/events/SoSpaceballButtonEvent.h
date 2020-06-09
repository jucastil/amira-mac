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


#ifndef  _SO_SPACEBALL_BUTTON_EVENT_
#define  _SO_SPACEBALL_BUTTON_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/events/SoButtonEvent.h>

// some convenience macros for determining if an event matches
#define SO_SPACEBALL_PRESS_EVENT(EVENT,BUTTON) \
    (SoSpaceballButtonEvent::isButtonPressEvent(EVENT, \
                        SoSpaceballButtonEvent::BUTTON))

#define SO_SPACEBALL_RELEASE_EVENT(EVENT,BUTTON) \
    (SoSpaceballButtonEvent::isButtonReleaseEvent(EVENT, \
                        SoSpaceballButtonEvent::BUTTON))


/**
 * @VSGEXT Spaceball button press and release events.
 * 
 * @ingroup events
 * 
 * @DESCRIPTION
 *   SoSpaceballButtonEvent represents spaceball button press and release events in
 *   the Open Inventor event model.
 *  
 *   Some convenience macros for determining if an event matches
 *     - SO_SPACEBALL_PRESS_EVENT(EVENT,BUTTON)
 *     - SO_SPACEBALL_RELEASE_EVENT(EVENT,BUTTON) 
 *
 * @SEE_ALSO
 *    SoEvent,
 *    SoButtonEvent,
 *    SoKeyboardEvent,
 *    SoLocation2Event,
 *    SoMotion3Event,
 *    SoMouseButtonEvent,
 *    SoHandleEventAction,
 *    SoEventCallback,
 *    SoSelection,
 *    SoInteraction,
 *    SoWinDevice
 * 
 * 
 */ 

class INVENTOR_API SoSpaceballButtonEvent : public SoButtonEvent {

  SO_EVENT_HEADER();
    
 public: 
    /** Button */
  enum Button {
    ANY = 0, 
    /**
     *  Spaceball button 1 
     */
    BUTTON1 = 1, 
    /**
     *  Spaceball button 2 
     */
    BUTTON2 = 2, 
    /**
     *  Spaceball button 3 
     */
    BUTTON3 = 3, 
    /**
     *  Spaceball button 4 
     */
    BUTTON4 = 4, 
    /**
     *  Spaceball button 5 
     */
    BUTTON5 = 5, 
    /**
     *  Spaceball button 6 
     */
    BUTTON6 = 6, 
    /**
     *  Spaceball button 7 
     */
    BUTTON7 = 7, 
    /**
     *  Spaceball button 8 
     */
    BUTTON8 = 8, 
    /**
     *  Spaceball pick button 
     */
    PICK = 9
  };
    
  /**
   * Constructor.
   */
  SoSpaceballButtonEvent();

#ifndef HIDDEN_FROM_DOC
  virtual ~SoSpaceballButtonEvent();
#endif // HIDDEN_FROM_DOC
    
  /**
   * Sets which spaceball button generated the event.
   */
  void                setButton(SoSpaceballButtonEvent::Button b)
    { button = b; }
  /**
   * Gets which spaceball button generated the event.
   */
  SoSpaceballButtonEvent::Button      getButton() const
    { return button; }
    
  /**
   * Returns whether the passed event is a spaceball button press event of
   * the passed button. When SoSpaceballButtonEvent::ANY is passed, this returns
   * @B TRUE @b if the event represents a button press of any spaceball
   * button.
   */
  static SbBool isButtonPressEvent(
                                   const SoEvent *e,
                                   SoSpaceballButtonEvent::Button whichButton);
                            
  /**
   * Returns whether the passed event is a spaceball button release event of
   * the passed button. When SoSpaceballButtonEvent::ANY is passed, this returns
   * @B TRUE @b if the event represents a button release of any spaceball
   * button.
   */
  static SbBool isButtonReleaseEvent(
                                     const SoEvent *e,
                                     SoSpaceballButtonEvent::Button whichButton);
    
 SoINTERNAL public:
  static void initClass();
  static void exitClass();
    
 private:
  Button button;                  // which button

};

#endif /* _SO_SPACEBALL_BUTTON_EVENT_ */


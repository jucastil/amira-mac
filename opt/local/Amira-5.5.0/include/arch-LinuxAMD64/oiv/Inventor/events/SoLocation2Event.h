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


#ifndef  _SO_LOCATION2_EVENT_
#define  _SO_LOCATION2_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/events/SoSubEvent.h>


/**
 * 2D location events.
 * 
 * @ingroup events
 * 
 * @DESCRIPTION
 *   SoLocation2Event represents 2D location events in the Open Inventor event model.
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
 *    SoWinDevice
 * 
 * 
 */ 

class INVENTOR_API SoLocation2Event : public SoEvent {

  SO_EVENT_HEADER();
    
 public:

   enum EventSource
   {
     MOUSE_MOVE,
     MOUSE_ENTER,
     MOUSE_LEAVE,
     OTHER
   };
  
  /**
   * Constructor.
   */
  SoLocation2Event();

#ifndef HIDDEN_FROM_DOC
  virtual ~SoLocation2Event();
#endif // HIDDEN_FROM_DOC

  EventSource getEventSource() const;

  void setEventSource(EventSource source);
    
 SoINTERNAL public:
  static void     initClass();
  static void exitClass();

private:

  EventSource m_eventSource;
};


#endif /* _SO_LOCATION2_EVENT_ */


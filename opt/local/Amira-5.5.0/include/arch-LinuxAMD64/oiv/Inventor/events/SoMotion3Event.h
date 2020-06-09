/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_MOTION3_EVENT_
#define  _SO_MOTION3_EVENT_

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/events/SoSubEvent.h>


/**
 * 3D motion events.
 * 
 * @ingroup events
 * 
 * @DESCRIPTION
 *   SoMotion3Event represents 3D relative motion events in the Open Inventor event
 *   model.
 * 
 * @SEE_ALSO
 *    SoEvent,
 *    SoButtonEvent,
 *    SoKeyboardEvent,
 *    SoLocation2Event,
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

class INVENTOR_API SoMotion3Event : public SoEvent {

  SO_EVENT_HEADER();
    
 public:
  
  /**
   * Constructor.
   */
  SoMotion3Event();

#ifndef HIDDEN_FROM_DOC
  virtual ~SoMotion3Event();
#endif // HIDDEN_FROM_DOC
    
  /**
   * Sets the relative change in translation since the last translation event.
   */
  void                setTranslation(const SbVec3f &t)    { translation = t; }
  /**
   * Gets the relative change in translation since the last translation event.
   */
  const SbVec3f &     getTranslation() const              { return translation; }
    
  /**
   * Sets the relative change in rotation since the last rotation event.
   */
  void                setRotation(const SbRotation &r)    { rotation = r; }
  /**
   * Gets the relative change in rotation since the last rotation event.
   */
  const SbRotation &  getRotation() const                 { return rotation; }
    
    
 SoINTERNAL public:
  static void     initClass();
  static void exitClass();

 private:
  SbVec3f         translation;    // translation value
  SbRotation      rotation;       // rotation value

};


#endif /* _SO_MOTION3_EVENT_ */


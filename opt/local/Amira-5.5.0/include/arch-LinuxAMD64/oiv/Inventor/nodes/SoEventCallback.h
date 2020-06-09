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


#ifndef  _SO_EVENT_CALLBACK_
#define  _SO_EVENT_CALLBACK_

#include <Inventor/misc/SoCallbackList.h>
#include <Inventor/SoPath.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/actions/SoHandleEventAction.h>

class SoEvent;
class SoEventCallback;

// callback function prototypes
/** 
 * [OIV-WRAPPER NAME{EventCB}] 
 */
typedef void SoEventCallbackCB(void *userData, SoEventCallback *node);

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoEventCallback
//
//////////////////////////////////////////////////////////////////////////////

/**
 * Node which invokes callbacks for events.
 * 
 * @ingroup nodes
 * 
 * @DESCRIPTION
 *   SoEventCallback will invoke application supplied \oivnetdoc delegates \else callbacks \endoivnetdoc during
 *   SoHandleEventAction traversal. Methods allow the application to specify which
 *   Open Inventor events should trigger callbacks, and which path must be picked, if
 *   any, for the \oivnetdoc delegate \else callback \endoivnetdoc invocation to occur. The application \oivnetdoc delegate \else callback \endoivnetdoc is able to
 *   get information about the event and the pick detail, and may grab events,
 *   release events, and set whether the event was handled.
 *   
 *   If you register more than one \oivnetdoc delegate \else callback \endoivnetdoc in an SoEventCallback node, all
 *   the \oivnetdoc delegates \else callbacks \endoivnetdoc will be invoked when an event occurs, even if one of the
 *   callbacks handles the event. However, if the event is handled 
 *   (i.e. \oivnetdoc SetHandled \else setHandled \endoivnetdoc is called) by any of the
 *   \oivnetdoc delegates \else callbacks \endoivnetdoc, no subsequent node in the scene graph will see the event.
 *   Generally SoEventCallback nodes should be placed near the beginning of the scene graph, so the
 *   SoHandleEventAction does not need to traverse the rest of the scene graph if the event is handled.
 *   Note that events may be handled by other nodes in the scene graph, for example draggers and
 *   manipulators.  If the event is handled before the SoEventCallback node is traversed, then none of
 *   the \oivnetdoc delegates \else callbacks \endoivnetdoc will be invoked.
 *
 *   Remember that when using the Open Inventor viewer classes, SoHandleEventAction traversal is
 *   only done when the viewer is in "selection" mode (the arrow cursor is displayed).  Also note
 *   that some methods may only only be called from the \oivnetdoc delegate \else callback \endoivnetdoc
 *   function.
 *
 * @EXAMPLE
 *   \oivnetdoc
 *     \code
 *     . . .
 *     // An event callback node so we can receive key press events
 *     SoEventCallback eventCB = new SoEventCallback();
 *     eventCB.AddEventCallback( typeof(SoKeyboardEvent), new SoEventCallback.EventCB(keyCB) );
 *     . . .
 *     \endcode
 *     \code
 *      // Handler for key press events
 *      private void keyCB( SoEventCallback sender )
 *      {
 *        SoKeyboardEvent evt = (SoKeyboardEvent)sender.GetEvent();
 *        if (evt.GetKey() == SoKeyboardEvent.Keys.UP_ARROW)
 *        {
 *          // Take some action
 *          sender.SetHandled();
 *        }
 *        else if (evt.GetKey() == SoKeyboardEvent.Keys.DOWN_ARROW)
 *        {
 *          // Take some action
 *          sender.SetHandled();
 *        }
 *      }
 *     \endcode
 *   \else
 *     \code
 *     . . .
 *     // An event callback node so we can receive key press events
 *     SoEventCallback *myEventCB = new SoEventCallback;
 *     myEventCB->addEventCallback( SoKeyboardEvent::getClassTypeId(), myKeyPressCB );
 *     . . .
 *     \endcode
 *     \code
 *     // Handler for key press events
 *     void myKeyPressCB( void *userData, SoEventCallback *eventCB ) {
 *       const SoEvent *event = eventCB->getEvent();
 *       if (SO_KEY_PRESS_EVENT(event, UP_ARROW)) {
 *         // Take some action
 *         eventCB->setHandled();
 *       } else if (SO_KEY_PRESS_EVENT(event, DOWN_ARROW)) {
 *         // Take some action
 *         eventCB->setHandled();
 *       }
 *     }
 *     \endcode
 *   \endoivnetdoc
 * 
 * @FILE_FORMAT_DEFAULT
 *    EventCallback {
 *    @TABLE_FILE_FORMAT
 *    @TABLE_END
 *    }
 * 
 * @SEE_ALSO
 *    SoInteraction,
 *    SoSelection,
 *    SoHandleEventAction,
 *    SoDragger
 * 
 * 
 */ 

class INVENTOR_API SoEventCallback : public SoNode {

  SO_NODE_HEADER(SoEventCallback);

 public:
  /**
   * Constructor creates an event callback node with no event interest and a NULL
   * path.
   */
  SoEventCallback();
    
  /**
   * Sets the path which must be picked in order for the callbacks to be
   * invoked. If the path is NULL, the callbacks will be invoked for every
   * interesting event, as specified by addEventCallback(), regardless of what
   * is picked. The setPath() method makes its own copy of the passed path.
   */
  void                setPath(SoPath *path);
  /**
   * Gets the path which must be picked in order for the callbacks to be
   * invoked.
   */
  const SoPath *      getPath()               { return pathOfInterest; }

  /**
   * Adds event callback.
   * Specifies the callback functions to be invoked for different event types. When
   * invoked, the callback function will be passed the userData, along with a pointer
   * to this SoEventCallback node. For example, passing
   * SoMouseButtonEvent::getClassTypeId() means callbacks will be invoked only
   * when a mouse button is pressed or released. Passing
   * SoEvent::getClassTypeId() for the eventType will cause the callback to be
   * invoked for every event which passes through this event callback node.
   */
  void                addEventCallback(SoType eventType,
                                       SoEventCallbackCB *f,
                                       void *userData = NULL);
  /**
   * Removes event callback.
   */
  void                removeEventCallback(SoType eventType,
                                          SoEventCallbackCB *f,
                                          void *userData = NULL);

  //////////////////////
  //
  // These all provide information to callback functions. They
  // return NULL when called from anywhere but a callback function.
  //
    
  /**
   * Returns the SoHandleEventAction currently traversing this node, or NULL if
   * traversal is not taking place. This should be called only from \oivnetdoc delegate \else callback \endoivnetdoc.
   */
  SoHandleEventAction *       getAction() const { return eventAction; }

  /**
   * Returns the event currently being handled, or NULL if traversal is not taking
   * place. This should be called only from \oivnetdoc delegate \else callback \endoivnetdoc functions.
   */
  const SoEvent *             getEvent() const
    { return (eventAction != NULL ? eventAction->getEvent() : NULL); }

  /**
   * Returns pick information during SoHandleEventAction traversal, or NULL if
   * traversal is not taking place. This should be called only from \oivnetdoc delegate \else callback \endoivnetdoc
   * functions.
   *
   * When this method is called, an SoRayPickAction is automatically applied to the
   * scene graph that the SoHandleEventAction is traversing, using the current event.
   * However this is only done once for each SoHandleEventAction traversal and the
   * result is cached for subsequent queries.
   */
  const SoPickedPoint *       getPickedPoint() const
    { return (eventAction != NULL ? eventAction->getPickedPoint() : NULL);}
    
  //
  //////////////////////

  /**
   * Tells the node the event was handled. The \oivnetdoc delegate \else callback \endoivnetdoc is responsible for
   * setting whether the event was handled or not. If there is more than one \oivnetdoc delegate \else callback \endoivnetdoc
   * registered with an SoEventCallback node, all of them will be invoked,
   * regardless of whether one has handled the event or not. This should be called
   * only from \oivnetdoc delegate \else callback \endoivnetdoc functions.
   */
  void                setHandled()
    { if (eventAction != NULL) eventAction->setHandled(); }

  /**
   * Returns whether the event has been handled. This should be called only from
   * \oivnetdoc delegate \else callback \endoivnetdoc functions.
   */
  SbBool              isHandled() const
    { return (eventAction != NULL) ? eventAction->isHandled() : FALSE; }
    
  /**
   * Tells the event callback node to grab events. While
   * grabbing, the node will consume all events; however, each \oivnetdoc delegate \else callback \endoivnetdoc will
   * only be invoked for events of interest.
   */
  void                grabEvents()
    { if (eventAction != NULL) eventAction->setGrabber(this); }

  /**
   * Tells the event callback node to release the grab of events. Event grabbing
   * is requested using grabEvents().
   */
  void                releaseEvents()
    { if (eventAction != NULL) eventAction->releaseGrabber(); }

 SoEXTENDER public:
  // This will be called during handleEventAction traversal.
  virtual void        handleEvent(SoHandleEventAction *ha);

 SoINTERNAL public:
  static void         initClass();    // initialize the class
  static void         exitClass();

 protected:
  // Destructor - protected since ref/unref is what should destroy this
  virtual ~SoEventCallback();
    
 private:
  // Only invoke callbacks if this path was picked.
  // If path is NULL, always invoke callbacks.
  SoPath              *pathOfInterest;
    
  // List of callback functions, event types, and user data.
  SbPList *           cblist;
    
  // This is set for each SoHandleEventAction traversal of this node
  // so that the apps callback routine can invoke methods on the action.
  SoHandleEventAction *eventAction;
};

#endif /* _SO_EVENT_CALLBACK_ */


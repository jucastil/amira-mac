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


#ifdef SOQT
#  include <Inventor/Qt/devices/SoQtMouse.h>
#elif defined _WIN32
#  include <Inventor/Win/devices/SoWinMouse.h>
#else // _WIN32

#ifndef  _SO_XT_MOUSE_
#define  _SO_XT_MOUSE_

#include <Inventor/Xt/devices/SoXtDevice.h>
#include <Inventor/events/SoLocation2Event.h>
#include <Inventor/events/SoMouseButtonEvent.h>
#include <X11/X.h>

#define SO_XT_ALL_MOUSE_EVENTS \
    (ButtonPressMask | ButtonReleaseMask | \
     PointerMotionMask | ButtonMotionMask)

/**
 * Translates and reports events for the mouse device.
 *
 * @ingroup Xt
 *
 * @DESCRIPTION
 *   This class manages events generated by the mouse, including mouse motion
 *   (SoLocation2Event), and mouse button press and release events
 *   (SoMouseButtonEvent).
 *
 * @SEE_ALSO
 *    SoXtDevice,
 *    SoLocation2Event,
 *    SoMouseButtonEvent
 *
 *
 */

class INVENTORXT_API SoXtMouse : public SoXtDevice {
 public:
  /**
   * Constructor. To the constructor, pass which mouse messages you
   * are interested in as a bitwise OR of the following values:
   *
   * ButtonPressMask - Mouse down events
   *
   * ButtonReleaseMask - Mouse up events
   *
   * PointerMotionMask - Mouse motion with no buttons
   *
   * ButtonMotionMask - Mouse motion with buttons pressed
   *
   * Or simply pass the defined value SO_XT_ALL_MOUSE_EVENTS for all mouse events. The
   * device will only report events of this type for the window it is enabled on.
   */
  SoXtMouse(EventMask mask = SO_XT_ALL_MOUSE_EVENTS);
  /**
   * Destructor.
   */
  ~SoXtMouse();

  // These functions enable/disable this device for the passed widget.
  // The callback function f will be invoked when events occur in w.
  // data is the clientData which will be passed.
  virtual void        enable(SoWidget w, XtEventHandler f,
                             XtPointer data, Window win = (Window)NULL);
  virtual void        disable(SoWidget w, XtEventHandler f, XtPointer data);

  //
  // Converts an X event into an SoEvent,
  // returning NULL if the event is not from this device.
  //
  virtual const SoEvent * translateEvent(XAnyEvent *xevent);

 private:
  EventMask           eventMask;      // X event interest for this device
  SoLocation2Event    *loc2Event;     // mouse motion
  SoMouseButtonEvent  *buttonEvent;   // mouse button press

  SoLocation2Event    *translateMotionEvent(XMotionEvent *me);
  SoMouseButtonEvent  *translateButtonEvent(XButtonEvent *be, SoButtonEvent::State s);

};

#endif /* _SO_XT_MOUSE_ */

#endif // _WIN32


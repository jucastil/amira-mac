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
#  include <Inventor/Qt/devices/SoQtInputFocus.h>
#elif defined _WIN32
#  include <Inventor/Win/devices/SoWinInputFocus.h>
#else // _WIN32

#ifndef  _SO_XT_FOCUS_
#define  _SO_XT_FOCUS_

#include <X11/X.h>
#include <Inventor/Xt/devices/SoXtDevice.h>

#define SO_XT_ALL_FOCUS_EVENTS \
    (EnterWindowMask | LeaveWindowMask)

// NOTE: this does not generate any SoEvent.
// It simply makes sure the passed X events occur in the widget.

/**
 * Reports input focus change events.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class reports input focus change events (i.e. when the cursor crosses into
 *   or out of the window). There are no input focus event in Open Inventor, so this
 *   always returns NULL when asked to translate events. When this class is
 *   registered on a render area, the render area will receive X input focus change
 *   events. (This class is extensively employed by the viewer classes.) 
 * 
 * @SEE_ALSO
 *    SoXtDevice
 * 
 * 
 */ 

class INVENTORXT_API SoXtInputFocus : public SoXtDevice {
 public:
  /**
   * Constructor. To the constructor, pass which input focus events
   * you are interested in as a bitwise OR of the following values: 
   * 
   * EnterWindowMask - Input focus entered the window. 
   * 
   * LeaveWindowMask - Input focus left the window 
   * 
   * Or simply pass the defined value SO_XT_ALL_FOCUS_EVENTS for all input focus
   * events. 
   */
  SoXtInputFocus(EventMask mask = SO_XT_ALL_FOCUS_EVENTS);
  /**
   * Destructor. 
   */
  ~SoXtInputFocus() {}
    
  // These functions enable/disable this device for the passed widget.
  // the callback function f will be invoked when events occur in w.
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
  EventMask           eventMask;

};

#endif /* _SO_XT_FOCUS_ */

#endif // _WIN32



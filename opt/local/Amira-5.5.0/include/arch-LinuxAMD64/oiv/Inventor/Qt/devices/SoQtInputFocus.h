/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/


#ifndef  _SO_QT_FOCUS_
#define  _SO_QT_FOCUS_

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/devices/SoQtDevice.h>

#define SO_QT_ALL_FOCUS_EVENTS \
        (EnterWindowMask | LeaveWindowMask)


class INVENTORQT_API SoQtInputFocus : public SoQtDevice {

  Q_OBJECT

    public:
  /**
   * Constructor. To the constructor, pass which input focus events
   * you are interested in as a bitwise OR of the following values: 
   * 
   * EnterWindowMask - Input focus entered the window. 
   * 
   * LeaveWindowMask - Input focus left the window 
   * 
   * Or simply pass the defined value SO_QT_ALL_FOCUS_EVENTS for all input focus
   * events. 
   */
  SoQtInputFocus(EventMask mask = SO_QT_ALL_FOCUS_EVENTS);
  /**
   * Destructor. 
   */
  ~SoQtInputFocus() {}
    
  // these functions will enable/disable this device for the passed widget.
  // the callback function f will be invoked when events occur in w.
  // data is the clientData which will be passed.
  virtual void        enable(QWidget *w, XtEventHandler f, XtPointer data , void* unused=NULL);
  virtual void        disable(QWidget *w, XtEventHandler f, XtPointer data);
  //
  // this converts an X event into an SoEvent,
  // returning NULL if the event is not from this device.
  //
  virtual const SoEvent * translateEvent(QEvent *event);
  
 private:
  EventMask           eventMask;

};

#endif /* _SO_QT_FOCUS_ */



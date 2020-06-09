/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/


#ifndef  _SO_QT_DEVICE_
#define  _SO_QT_DEVICE_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/SbLinear.h>
#include <Inventor/events/SoEvent.h>

#include <QtCore/QObject>
# include <QtCore/QEvent>
#include <Inventor/Qt/SoQtDef.h>

// Stuff for SoQtMouse/Keyboard
#define   EventMask int
#ifdef _WIN32
#define   ButtonPressMask   0x01
#define   ButtonReleaseMask 0x02
#define   PointerMotionMask 0x04
#define   ButtonMotionMask  0x08
#define   KeyPressMask      0x10
#define   KeyReleaseMask    0x20
#define   EnterWindowMask   0x40
#define   LeaveWindowMask   0x80
#elif defined __APPLE__
#define   ButtonPressMask   0x01
#define   ButtonReleaseMask 0x02
#define   PointerMotionMask 0x04
#define   ButtonMotionMask  0x08
#define   KeyPressMask      0x10
#define   KeyReleaseMask    0x20
#define   EnterWindowMask   0x40
#define   LeaveWindowMask   0x80        
#else
#define NoEventMask			0L
#define KeyPressMask			(1L<<0)  
#define KeyReleaseMask			(1L<<1)  
#define ButtonPressMask			(1L<<2)  
#define ButtonReleaseMask		(1L<<3)  
#define EnterWindowMask			(1L<<4)  
#define LeaveWindowMask			(1L<<5)  
#define PointerMotionMask		(1L<<6)  
#define PointerMotionHintMask		(1L<<7)  
#define Button1MotionMask		(1L<<8)  
#define Button2MotionMask		(1L<<9)  
#define Button3MotionMask		(1L<<10) 
#define Button4MotionMask		(1L<<11) 
#define Button5MotionMask		(1L<<12) 
#define ButtonMotionMask		(1L<<13)
#endif

class QEvent;

/**
 * @VSGEXT Abstract base class for input devices.
 * 
 * @ingroup Qt
 * 
 * @DESCRIPTION
 *   This is the abstract base class for devices in the Open Inventor Windows
 *   component and utility library. When a device is registered with an
 *   SoQtRenderArea, the device is able to generate messages in the render area
 *   window.
 *
 *   Used internally by SoQtRenderArea and derived classes.  Can also be used
 *   by the application to translate system events into SoEvent objects.
 * 
 * @SEE_ALSO
 *    SoQtMouse,
 *    SoQtKeyboard,
 *    SoQtRenderArea
 * 
 * 
 */ 


class INVENTORQT_API SoQtDevice : public QObject{

  Q_OBJECT

    //typedef void* QtPointer;
    //typedef void* QtEventHandler;

    public:
  /**
   * Enables the device for the passed widget. When enabled, the callback
   * function @B f @b will be invoked when events occur in the window. @B data @b
   * is the @B clientData @b which will be passed.
   */
  virtual void        enable(QWidget *w, XtEventHandler f, XtPointer data, void* unused=NULL) = 0;
  /**
   * Disables the device for the passed widget. 
   */
  virtual void        disable(QWidget *w, XtEventHandler f, XtPointer data) = 0;
    
  /**
   * Attempts to convert the passed event into an SoEvent. @BR
   * Returns a pointer to an internal SoEvent object owned by the class.
   * Do not delete this object. If the message was not generated by this 
   * device, then NULL is returned.
   */
  virtual const SoEvent * translateEvent(QEvent *event) = 0;

  /**
   * Sets the size of the window this device is registered for. This allows
   * the device to correctly convert position information from X window coordinates
   * (origin at top left) to Open Inventor window coordinates (origin at bottom
   * left). (SoQtRenderArea will automatically call this method for each device
   * registered on it whenever the window size changes.) Note: Setting the window
   * size only affects the size as perceived by the device and not the actual window
   * size.
   */
  inline void                setWindowSize(const SbVec2s &s);
  /**
   * Gets the size of the window this device is registered for. 
   */
  const SbVec2s &     getWindowSize() const           { return winSize; }

 protected:
   /**
    *  Set the event's position from the passed window system x,y value. 
    *  This will flip the y value to convert to Inventor coordinates.
    *  Note : The position is float to handle particular use cases when a desktop is magnified
    *  on a wall of screens when using ScaleViz in correlation with a tracker
    *  device calibrated for this wall.
    */
   inline void         setEventPosition(SoEvent *event, float x, float y) const;
    
  //because qt doesn't give us the widget of an event we have to keep track on it
  //and set it with enable and disable
  QWidget * deviceWidget;

 private:
  SbVec2s             winSize;    // size of the window this device works in

};

// Inline functions
void
SoQtDevice::setEventPosition(SoEvent *event, float x, float y) const
{
  event->setPosition(SbVec2f(x, (((float)winSize[1]) - 1.f) - y));
}

void
SoQtDevice::setWindowSize(const SbVec2s &s)
{ 
  winSize = s;
}

#endif /* _SO_QT_DEVICE_ */
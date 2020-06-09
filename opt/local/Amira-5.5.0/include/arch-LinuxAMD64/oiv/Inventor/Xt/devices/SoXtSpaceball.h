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


#ifdef SOQT
#  include <Inventor/Qt/devices/SoQtSpaceball.h>
#elif defined _WIN32
#  include <Inventor/Win/devices/SoWinSpaceball.h>
#else

#ifndef  _SO_XT_SPACEBALL_
#define  _SO_XT_SPACEBALL_

#include <X11/X.h>
#ifndef __NUTC__
#  include <X11/extensions/XInput.h>
#endif

#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/devices/SoXtDevice.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

#include <Inventor/Gui/devices/SoGuiSpaceball.h>

/**
 * Translates and reports events for a SpaceBall or SpaceMouse (Magellan) device.
 * 
 * @ingroup Xt
 * 
 * @DESCRIPTION
 *   This class manages events generated by the spaceball, including spaceball motion
 *   (SoMotion3Event), and spaceball button press and release events
 *   (SoSpaceballButtonEvent).
 * 
 * 
 */ 

class INVENTORXT_API SoXtSpaceball : public SoXtDevice 
{
 public:
  
  //
  // valid event mask values:
  //        SoXtSpaceball::MOTION   - spaceball translation and rotation
  //        SoXtSpaceball::PRESS    - spaceball button press
  //        SoXtSpaceball::RELEASE  - spaceball button release
  //        SoXtSpaceball::ALL      - all spaceball events
  // Bitwise OR these to specify whichEvents this device should queue.
  //
  // The second constructor allows the spaceball to be attached
  // to a different display than the one used by SoXt::init().
  
  /**
   * Constructor.
   */
  SoXtSpaceball(SoGuiSpaceball::Mask mask = SoGuiSpaceball::ALL);
  /**
   * Constructor.
   */
  SoXtSpaceball(Display *d, SoGuiSpaceball::Mask mask = SoGuiSpaceball::ALL);
  /**
   * Destructor.
   */
  ~SoXtSpaceball();
  
  /**
   * Enables this device for the passed widget. The
   * callback function f will be invoked when events occur in w. Data is the
   * clientData which will be passed.
   */
  virtual void        enable(SoWidget w, XtEventHandler f,
                             XtPointer data, Window win = NULL);
  /**
   * Disables this device for the passed widget. The
   * callback function f will be invoked when events occur in w. Data is the
   * clientData which will be passed.
   */
  virtual void        disable(SoWidget w, XtEventHandler f, XtPointer data);
  
  /**
   * This converts a system event into an SoEvent, returning NULL if the event is not
   * from this device.
   */
  virtual const SoEvent * translateEvent(XAnyEvent *xevent);
  
  /**
   * The spaceball reports rotations and translations as integers. These values must
   * be scaled to be useful. This method sets the rotation scale factor. 
   * Default is .006.
   */
  void          setRotationScaleFactor(float f)    { m_guiSpaceball->setRotationScaleFactor( f ); }
  /**
   * Returns the rotation scale factor.
   */
  float         getRotationScaleFactor() const     { return m_guiSpaceball->getRotationScaleFactor(); }
  /**
   * The spaceball reports rotations and translations as integers. These values must
   * be scaled to be useful. This method sets the translation scale factor. Default
   * is .006.
   */
  void          setTranslationScaleFactor(float f) { m_guiSpaceball->setTranslationScaleFactor( f ); }
  /**
   * Returns the translation scale factor.
   */
  float         getTranslationScaleFactor() const  { return m_guiSpaceball->getTranslationScaleFactor(); }
  
  /**
   * Returns whether or not the spaceball device exists for use.
   */
  static SbBool exists() { return exists(SoXt::getDisplay()); }
  /**
   * Returns whether or not the spaceball device exists for use.
   */
  static SbBool exists(Display *d);

  /**
   * Sets the input focus method used to get events from the space ball.
   * If FALSE: SpaceBall events are received only if the cursor is in the window or
   * when the window has the focus (default). @BR
   * If TRUE: SpaceBall events are received even if cursor is out of the window. 
   */
  void          setFocusToWindow(SbBool flag);
  /**
   * Gets the input focus method. See setFocusToWindow() for details.
   */
  SbBool        isFocusToWindow() const { return m_guiSpaceball->isFocusToWindow(); }

 private:
  SoMotion3Event          *motionEvent;   // spaceball rotation/translation
  SoSpaceballButtonEvent  *buttonEvent;   // spball button press/release
  
  SoWidget parentWidget;

  SoGuiSpaceball* m_guiSpaceball; // Implementation class for SoXxSpaceball
  
  // the X display 
  Display *display;

  // flag indicating when to receive events.
  SbBool focusToWindow;

  // the window receiving events
  Window window;

  // event translators for SPACE BALL!
  SoMotion3Event           *translateMotionEvent(XDeviceMotionEvent *me);
  SoSpaceballButtonEvent *translateButtonEvent(XEvent *be,
                                               SoButtonEvent::State whichState);
  // event translators for MAGELLAN SPACE MOUSE!
  SoMotion3Event           *translateMotionEventMagellan(XEvent *me);
  
  void constructorCommon(Display *d, SoGuiSpaceball::Mask mask);         

};

#endif /* _SO_XT_SPACEBALL_ */

#endif // _WIN32


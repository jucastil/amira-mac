/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef  _SO_QT_SPACEBALL_
#define  _SO_QT_SPACEBALL_
#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/events/SoMotion3Event.h>
#include <Inventor/events/SoSpaceballButtonEvent.h>

#include <Inventor/Gui/devices/SoGuiSpaceball.h>

/**
 * Translates and reports events for a SpaceBall or SpaceMouse (Magellan) device.
 * 
 * @ingroup Qt
 * 
 * @DESCRIPTION
 *   This class manages events generated by the spaceball, including spaceball motion
 *   (SoMotion3Event), and spaceball button press and release events
 *   (SoSpaceballButtonEvent).
 * 
 * 
 */ 

class INVENTORQT_API SoQtSpaceball : public SoQtDevice {
  
  Q_OBJECT

#ifdef __APPLE__
public:
  SoQtSpaceball(SoGuiSpaceball::Mask mask = SoGuiSpaceball::ALL) { };
  SoQtSpaceball(Display *d, SoGuiSpaceball::Mask mask = SoGuiSpaceball::ALL) { };
  ~SoQtSpaceball() { };
  virtual void  enable(QWidget *w, XtEventHandler f, XtPointer data, void *unused=NULL) { };
  virtual void  disable(QWidget *w, XtEventHandler f, XtPointer data) { };
  virtual const SoEvent * translateEvent(QEvent *xevent) { return NULL;};
  void setRotationScaleFactor(float f) { };
  float getRotationScaleFactor() const { return 0.0; };
  void setTranslationScaleFactor(float f) { };
  float getTranslationScaleFactor() const { return 0.0; };
  static SbBool exists() { return FALSE;};
  static SbBool exists(Display);
  void setFocusToWindow(SbBool);
  SbBool isFocusToWindow() const { return FALSE;};

#else
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
  SoQtSpaceball(SoGuiSpaceball::Mask mask = SoGuiSpaceball::ALL);
  /**
   * Constructor.
   */
  SoQtSpaceball(SbGlContextHelper::Display d, SoGuiSpaceball::Mask mask = SoGuiSpaceball::ALL);
  /**
   * Destructor.
   */
  ~SoQtSpaceball();
  
  /**
   * Enables this device for the passed widget. The
   * callback function f will be invoked when events occur in w. Data is the
   * clientData which will be passed.
   */
  virtual void        enable(QWidget *w, XtEventHandler f, XtPointer data, void *unused=NULL);
  /**
   * Disables this device for the passed widget. The
   * callback function f will be invoked when events occur in w. Data is the
   * clientData which will be passed.
   */
  virtual void        disable(QWidget *w, XtEventHandler f, XtPointer data);
  
  /**
   * This converts a system event into an SoEvent, returning NULL if the event is not
   * from this device.
   */
  virtual const SoEvent * translateEvent(QEvent *xevent);
  
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
  static SbBool exists() { return exists(SoQt::getDisplay());}
  /**
   * Returns whether or not the spaceball device exists for use.
   */
  static SbBool exists(SbGlContextHelper::Display d);

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

  SoGuiSpaceball* m_guiSpaceball; // Implementation class for SoXxSpaceball

  SoMotion3Event            *motionEvent;   // spaceball rotation/translation
  SoSpaceballButtonEvent    *buttonEvent;   // spball button press/release
  
  QWidget* parentWidget;

#ifdef _WIN32
  // The first widget which registered the space ball object
  HWND m_curHwnd;
  // Magellanstruct _MagellanControl_ Space Mouse data structure 
  struct _MagellanControl_ *magellanHandle;

#else

    // the X display 
    Display *display;
  
    // device type: SPACE_BALL or MAGELLAN_SPACE_MOUSE
    SoGuiSpaceball::DeviceType deviceType;

#endif

  // event translators for SPACE BALL!
  SoMotion3Event           *translateMotionEvent(QEvent *me);
  SoSpaceballButtonEvent *translateButtonEvent(QEvent *be,
                                               SoButtonEvent::State whichState);
  // event translators for MAGELLAN SPACE MOUSE!
  SoMotion3Event           *translateMotionEventMagellan(XEvent *me);
  
  void constructorCommon(SbGlContextHelper::Display d, SoGuiSpaceball::Mask mask);
#endif
};

#endif /* _SO_QT_SPACEBALL_ */

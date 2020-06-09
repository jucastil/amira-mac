/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#  include <QtCore/QEvent>
#  include <QtGui/QApplication>

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/SoQt.h>

// For compatibility reasons
#define ExtEventApplication SoQtExtEventApplication

/** 
 * QCustomEvent no longer exists in full Qt4 so we have to subclass QEvent
 * to provide our own custom event.
 */
class INVENTORQT_API ExtEvent : public QEvent
{
public:
 /** 
  * Constructor.
  */
  ExtEvent( QEvent::Type type, void* data ) : QEvent( type ), m_data(data) {}; 

 /** 
  * Returns the data sent with the event.
  */
  void* data() { return m_data; }

 /** 
  * Sets the data sent with the event.
  */
  void setData( void* data ) { m_data = data; } 

private:
  void* m_data;
};

/**
 * Overload the QApplication to be able to get devices events like SpaceMouse.
 */
class INVENTORQT_API SoQtExtEventApplication : public QApplication {
public:
 /** 
  * Constructor.
  */
  SoQtExtEventApplication( int &argc, char **argv): QApplication(argc, argv) {}

#ifdef _WIN32	
  virtual bool winEventFilter( MSG *event, long *result );

  void allEventFilter( XEvent *event );

#elif defined(__APPLE__)
  virtual bool  macEventFilter( EventHandlerCallRef event, EventRef eventRef );

  void allEventFilter (EventHandlerCallRef event);

#else
  virtual bool x11EventFilter( XEvent *event );

  void allEventFilter (XEvent *event);
#endif
};


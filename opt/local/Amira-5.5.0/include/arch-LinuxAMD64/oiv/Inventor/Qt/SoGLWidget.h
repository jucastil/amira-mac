/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_GLWIDGET_
#define _SO_GLWIDGET_

#include <QtCore/qglobal.h>
#include <QtGui/QWidget>

#include <Inventor/Qt/SoQtDef.h>

#include <Inventor/helpers/SbGlContextHelper.h>
#include <Inventor/sys/port.h>

class INVENTORQT_API  SoGLWidget : public QWidget
{
  Q_OBJECT

public:

#if defined(__APPLE__)
  SoGLWidget() { };
  ~SoGLWidget() { };
#else
  SoGLWidget( SbGlContextHelper::VisualInfo vis = NULL, QWidget* parent = 0, const char* name = 0);
  ~SoGLWidget();
  virtual bool x11Event(XEvent *event);
#endif
  
Q_SIGNALS:
  void XEnterEvent( unsigned int );  
  void XLeaveEvent( unsigned int );
};

#endif // _SO_GLWIDGET_


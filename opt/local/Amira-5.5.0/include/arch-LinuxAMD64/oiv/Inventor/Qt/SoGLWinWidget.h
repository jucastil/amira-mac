/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_GLWINWIDGET_
#define _SO_GLWINWIDGET_

#include <Inventor/Qt/OivQtCompat.h>
#include <Inventor/Qt/SoQt.h>

#include <QtCore/qglobal.h>
#include <QtCore/QObject>
#include <QtGui/QWidget>

/** 
 * OIV custom QWidget which will handle Open GL.
 */
class INVENTORQT_API SoGLWinWidget : public QWidget
{
  Q_OBJECT

public:
/** 
 * Constructor.
 */
  SoGLWinWidget( QWidget *widget, const char *name,
                 Qt::WFlags flags );
  ~SoGLWinWidget();
  QPaintEngine *paintEngine() const;
};

#endif // _SO_GLWINWIDGET_

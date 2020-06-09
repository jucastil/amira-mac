/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nick Thompson (MMM yyyy)
** Modified by : Paul Isaacs (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/


#ifndef _SO_QT_
#define _SO_QT_

#ifndef SOQT
#define SOQT
#endif

#include <Inventor/Qt/SoXt2SoQt.h>

#include <QtCore/qglobal.h>

#include <QtCore/QEvent>
#include <QtCore/QObject>
#include <QtGui/QWidget>
#include <QtGui/QToolButton>
#include <QtGui/QPushButton>
#include <QtGui/QApplication>
#include <QtCore/QPointer>

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/Qt/SoQtDef.h>
#include <Inventor/Qt/SoQtLibName.h>

#ifdef _WIN32
#if !defined(InventorQt_EXPORTS) && !defined(InventorQt4_EXPORTS)
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__INVQTLIB)
#endif
#endif
#endif //win

class SbPList;
class SoQtSensorHandler;

/**
 * @VSGEXT Routines for Open Inventor/Qt compatibility.
 *
 * @ingroup Qt
 *
 * @DESCRIPTION
 *   The SoQt class initializes Open Inventor for use with Qt.
 *   SoQt::init() must be called in order for Open Inventor to work properly with
 *   Qt. SoQt::finish() should be called to clean up static memory allocations.
 *
 *   SoQt::mainLoop() must be called in order for extension device messages
 *   to be passed to Open Inventor render areas. The other methods are convenience
 *   functions.
 *
 *   Refer to the SoQtComponent reference pages for examples on how this class should
 *   be used when using Open Inventor Qt components.
 *
 * @SEE_ALSO
 *    SoQtComponent
 *
 *
 */

class INVENTORQT_API  SoQt : public QObject
{
  Q_OBJECT
    // QObject inheritance is not required here.
    // Just for consistency and to allow possible Q_SLOTS.
    public:
  /**
   * This is called to initialize Open Inventor and Qt, and bind Open Inventor
   * with Qt message handling so that Open Inventor sensors will work correctly.
   * This returns the top level shell widget handle. This method calls
   * SoDB::init(), SoNodeKit::init(), and SoInteraction::init(),
   * and creates an initial window.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static QWidget *init(const char *appName, const char *className = "Inventor");

  /**
   * This is called to initialize Open Inventor and Qt, and bind Open Inventor
   * with Qt message handling so that Open Inventor sensors will work correctly.
   * This returns the top level shell widget handle. This method calls
   * SoDB::init(), SoNodeKit::init(), and SoInteraction::init(),
   * and creates an initial window.
   */
  static QWidget *init(const SbString& appName, const SbString& className = "Inventor");

  /**
   * This method calls SoDB::threadInit() rather than SoDB::init().
   * Otherwise it is the same as the corresponding SoQt::init() method.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static QWidget *threadInit(const char *appName,
                             const char *className = "Inventor");

  /**
   * This method calls SoDB::threadInit() rather than SoDB::init().
   * Otherwise it is the same as the corresponding SoQt::init() method.
   */
  static QWidget *threadInit(const SbString& appName,
                             const SbString& className = "Inventor");

  /**
   * This alternate form of init allows the application to initialize Qt. The
   * passed widget handle should be the top level widget handle returned from the
   * Qt initialization. This method will call SoDB::init(),
   * SoNodeKit::init(), and SoInteraction::init().
   */
  static void init(QWidget *topLevelWidget);

  /**
   * This method calls SoDB::threadInit() rather than SoDB::init().
   * Otherwise it is the same as the corresponding SoQt::init() method.
   */
  static void threadInit(QWidget *topLevelWidget);

  /**
   * Convenience routine to show the passed widget handle.
   *
   * This includes any children the widget may have.
   */
  static void show(QWidget *widget);
  /**
   * Convenience routine to hide the passed widget handle.
   *
   * This includes any children the widget may have.
   */
  static void     hide(QWidget *widget);
  /**
   * This retrieves and dispatches messages (loops forever).
   */
  static void mainLoop();
  /**
   * This method is included for portability only.
   */
  static SbGlContextHelper::Display getDisplay();
  /**
   * Returns information based on the initial QWidget handle returned by or passed to
   * init.
   */
  static QWidget *getTopLevelWidget();
  /**
   * Convenience routine to set the size of the given widget.
   */
  static void     setWidgetSize(QWidget *widget, const SbVec2s &size);
  /**
   * Convenience routine to get the size of the given widget.
   */
  static SbVec2s getWidgetSize(QWidget *widget);

  /**
   * Convenience routine which brings a simple Qt error dialog box displaying
   * the given error string(s) and window title. The OK button, which destroys the
   * dialog, is the only button displayed.
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE static void createSimpleErrorDialog(QWidget *widget, char *dialogTitle,
                                      char *errorStr1, char *errorStr2 = NULL);

  /**
   * Convenience routine which brings a simple Qt error dialog box displaying
   * the given error string(s) and window title. The OK button, which destroys the
   * dialog, is the only button displayed.
   */
  static void createSimpleErrorDialog( QWidget *widget, const SbString& sdialogTitle,
                                      const SbString& errorStr1, const SbString& errorStr2 = "" );

  /**
   * Frees Open Inventor's internal static memory
   * allocations. This avoids false positives from memory
   * leak checking software. We recommend calling this method
   * and it should be the last Open Inventor method called by
   * the application. This method calls SoDB::finish(),
   * SoNodeKit::finish(), and SoInteraction::finish().
   *
   *@B Note@b: Open Inventor objects should be destroyed before you call this method.
   *
   * For example:
   * @TABLE_1B
   *  @TR @B Wrong Open Inventor Ending@b
   *  @TD @B Safe Open Inventor Endings@b
   *  @TR <PRE>
   * void main() {
   *   QWidget myW = SoQt::init("");
   *   SoQtExaminerViewer viewer( myW );
   *   ....
   *   ....
   *   SoQt::mainLoop();
   *   SoQt::finish();
   * }
   *  </PRE>
   *  @TD
   *    @TABLE_0B
   *    @TR <PRE>
   * void runApp() {
   *   SoQtExaminerViewer viewer( myW );
   *   ....
   *   ....
   *   SoQt::mainLoop();
   * }
   *
   * void main () {
   *   QWidget myW = SoQt::init("");
   *   runApp();
   *   SoQt::finish();
   * }
   * </PRE>
   * @TD <PRE>
   * void main () {
   *   QWidget myW = SoQt::init("");
   *   SoQtExaminerViewer* viewer
   *          = new SoQtExaminerViewer( myW );
   *   ....
   *   ....
   *   SoQt::mainLoop();
   *   delete viewer;
   *   SoQt::finish();
   *  }
   * </PRE>
   *     @TABLE_END
   * @TR
   * SoQt doesn't end properly: SoQtExaminerViewer is destroyed after the #finish() method has been called.
   * @TD
   * The SoQtExaminerViewer (that uses Open Inventor) is destroyed before calling the #finish() method.
   *     @TABLE_END
   */
  static void finish();

  /**
   * Returns TRUE if SoQt module is currently initialized.
   */
  static bool isInitialized();

  /**
   * Returns the type number of the Open Inventor
   * extension QCustomEvent. This number can be set with
   * the environment variable OIV_EXTENSION_EVENT_NUMBER.
   */
  static int getExtensionEventNumber();

 SoINTERNAL public:
  // Hide from docs...

  static QPointer<QWidget> mainWidget;
  static QPointer<QApplication> qapplication;
  static QApplication *getQApp() {return qapplication;};

  // Add/remove the passed event handler for X extension device events
  // (Xt does not handle extension events.)
  // Extension event types are queried from the server at runtime.
  static void addExtensionEventHandler(QWidget *w,
                                       int extensionEventType,
                                       XtEventHandler proc,
                                       XtPointer clientData);
  static void removeExtensionEventHandler(QWidget *w,
                                          int extensionEventType,
                                          XtEventHandler proc,
                                          XtPointer clientData);

  static void   getExtensionEventHandler(XEvent *event, QWidget *w,
                                         XtEventHandler &proc,
                                         XtPointer &clientData);

 protected:

  static SoQtSensorHandler *sensorHandler;

  private:

  static SbPList *handlerList;

  static int OIVExtensionEventNumber;

  static void setupInventorGLDisplay();

private:
    static int s_initRefCount;
    static const char *s_versionString;
    static SbBool s_ownTopLevelWindow;
    static SbBool s_ownApplication;
    static int s_defaultArgc;
    static char** s_defaultArgv;
};

#ifdef __APPLE__
#define SoQtButton QToolButton
#else
#define SoQtButton QPushButton
#endif

#endif // _SO_QT_

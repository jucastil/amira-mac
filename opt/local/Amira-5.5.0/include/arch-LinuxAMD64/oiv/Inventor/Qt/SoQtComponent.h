/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_QT_COMPONENT_
#define _SO_QT_COMPONENT_

#include <Inventor/Qt/OivQtCompat.h>

#include <QtCore/QString>
#include <QtCore/QPointer>

#include <Inventor/Qt/SoQt.h>
#include <Inventor/Gui/SoGuiComponent.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SbDict.h>

#if defined(__APPLE__)
# undef Display
#endif

class SoQtComponent;

typedef void SoQtComponentCB( void* userData, SoQtComponent* comp );

/**
 * @VSGEXT Abstract base class for all Open Inventor Qt components.
 *
 * @ingroup Qt
 *
 * @DESCRIPTION
 *   Abstract base class from which all Open Inventor Qt components are derived.
 *   This class provides a basic C++ protocol for building and displaying Qt
 *   components. Components are used to encapsulate some function or task into a
 *   reusable package in the form of a Qt widget handle that can be used in any
 *   Open Inventor Qt program. See the Example section on how to build and use
 *   SoQtComponents.
 *
 * @EXAMPLE
 *    This example shows how an Open Inventor component can be built inside a program
 *   using the Qt widget handle set. The example uses the SoQtExaminerViewer
 *   widget handle to view some simple geometry.
 *
 *   \#include <Inventor/Qt/SoQt.h> @BR
 *   \#include <Inventor/nodes/SoCone.h> @BR
 *   \#include <Inventor/Qt/viewers/SoQtExaminerViewer.h> @BR
 *
 *   void main(int, char* *argv)
 *
 *   // Initialize Inventor and Qt, which must be done @BR
 *   // before any Inventor calls are made.@BR
 *
 *   QWidget*  myWidget = SoQt::init(argv[0]);
 *
 *   // Create the viewer in the toplevel window @BR
 *   // and set some scene to display. @BR
 *
 *   SoQtExaminerViewer *myViewer = new SoQtExaminerViewer(myWidget); @BR
 *   myViewer->setSceneGraph( new SoCone() );
 *
 *   // Map window on screen.
 *
 *   myViewer->show();  @BR
 *   SoQt::show(myWidget); // calls Show()
 *
 *   // Loop forever
 *
 *   SoQt::mainLoop();
 *
 *
 * @SEE_ALSO
 *    SoQt,
 *    SoQtRenderArea,
 *    SoQtViewer
 *
 *
 */
class INVENTORQT_API SoQtComponent : public QObject
{
  Q_OBJECT

    public:

  /**
   * This shows the component.
   */
  virtual void show();

  /**
   * This hides the component.
   */
  virtual void hide();

  /**
   * Returns TRUE if this component is mapped onto the screen. For a component to be
   * visible, its widget and the shell containing this widget must be mapped (which
   * is FALSE when the component is iconified).
   */
  SbBool isVisible();

  /**
   * This returns the base widget handle for this component.
   */
  virtual QWidget* getWidget() const { return _baseWidget; }

  /**
   * Returns TRUE if this component is a top level shell component (has its own
   * window). Subclasses may use this to decide if they are allowed to resize
   * themselves.
   */
  SbBool isTopLevelShell() const { return m_guiComponent->isTopLevelShell(); }

  /**
   * Returns the topLevelShell widget handle (NULL if the topLevelShell
   * hasn't been created by this component).
   */
  QWidget* getShellWidget() const { return m_guiComponent->isTopLevelShell() ? parentWidget : NULL; }

  /**
   * Returns the parent widget handle.
   */
  QWidget* getParentWidget() const { return parentWidget; }

  /**
   * Convenience routine on the widget handle.
   */
  void setSize( const SbVec2s& size );

  /**
   * Convenience routine on the widget handle.
   */
  SbVec2s getSize();
  /**
   * Switches the viewer into (or out of) fullscreen mode. This
   * works fine on Windows, but has certain problems under the
   * X Window System. For details, see the Qt documentation for
   * QWidget::showFullScreen.
   */
  virtual SbBool setFullScreen( const SbBool enable );

  /**
   * Queries if the viewer is in fullscreen mode.
   */
  SbBool isFullScreen( void ) const;

  /**
   * Enables/disables fullscreen mode. If fullscreen mode is disabled, it
   * is not possible to activate fullscreen mode with the right mouse button
   * popup menu.
   */
  void setFullScreenEnable( const SbBool enable );

  /**
   * Queries if it is possible to put the viewer
   * in fullscreen mode.
   */
  SbBool isFullScreenEnable(void) const;

  /**
   * On UNIX, returns the X display associated with this components widget.
   */
  inline SbGlContextHelper::Display getDisplay();

  /**
   * Sets window title.
   * The window title can be set for topLevelShell components or components which are
   * directly under a shell window handle (i.e. components which have their own
   * window).
   */
  void setTitle( const char* newTitle );

   /**
   * Sets window title.
   * The window title can be set for topLevelShell components or components which are
   * directly under a shell window handle (i.e. components which have their own
   * window).
   */
  void setTitle( const SbString& newTitle );

   /**
   * Sets window title.
   * The window title can be set for topLevelShell components or components which are
   * directly under a shell window handle (i.e. components which have their own
   * window).
   */
  void setTitle( const QString& newTitle );

  /**
   * Gets window title.
   */
  const QString getTitle() const;

  /**
   * Included for portability only.
   */
  void setIconTitle( const QString& newIconTitle );

  /**
   * Included for portability only.
   */
  const QString getIconTitle() const;

  /**
   * Returns the SoQtComponent for this widget handle. If the widget handle
   * does not match that of any Open Inventor component, then NULL is returned.
   */
  static SoQtComponent* getComponent( QWidget* widget );

  /**
   * Returns the widget handle name. The widget
   * handle name is passed to the build method.
   */
  SbString getWidgetName() const;

  /**
   * Returns the class name.
   * The class name is predefined by each component.
   */
  SbString getClassName() const;

  /**
   * Name of help file to open when the viewer Help button is pressed.
   */
  SbString    helpFileName;

#ifdef _WIN32
  /**
   * The context ID of the help topic to open when the viewer Help button is
   * pressed.
   */
  UINT                helpContextID;
#endif

 /**
  * Sets which callback to call when the user closes this component (double click in
  * the upper left corner) - by default hide() is called on this component,
  * unless a callback is set to something other than NULL. A pointer to this class
  * will be passed as the callback data.
  * 
  * Note: this callback is supplied because the user may wish to delete this
  * component when it is closed.
  */
  void setWindowCloseCallback( SoQtComponentCB* func, void* data = NULL )
  { m_windowCloseFunc = func; m_windowCloseData = data; }


 SoINTERNAL public:

  virtual ~SoQtComponent();

  void setFullScreenOn( SbBool enable ) { m_guiComponent->setFullScreen( enable ); };

  static void finish();

  SoGuiComponent* getGuiComponent() const;

Q_SIGNALS:
#ifndef HIDDEN_FROM_DOC
  void visibilityChanged(SbBool visible);
#endif // HIDDEN_FROM_DOC

 protected:

  SoQtComponent( QWidget* parent = NULL,
                 const char* name = NULL,
                 SbBool buildInsideParent = TRUE,
                 SbBool sync = TRUE );

  SoQtComponent( QWidget* parent,
                 const char* name,
                 SbBool buildInsideParent,
                 SbBool sync,
                 SoGuiComponent* guiComponent );

  void setBaseWidget( QWidget* w );

  void setClassName( const char* n ) { m_guiComponent->setClassName( n ); }

  virtual void  afterRealizeHook();

  //First realize state
  SbBool firstRealize;

  virtual SbString  getDefaultWidgetName() const;
  virtual SbString  getDefaultTitle() const;
  virtual SbString  getDefaultIconTitle() const;

  //
  // Register widget - should be called by subclasses after
  // they have created their top most widget (which is passed here),
  // and before they build any child widgets. Calling this method
  // ensures that the widgets name and class will be used when
  // calls are made to get X resource values for this widget.
  //
  // *** NOTE ***
  // ALL subclasses should register their top most widget within the
  // component, whether they retrieve resources or not, so that children
  // widgets can get X resources properly.
  // Unregister the widget when the widget is destroyed.
  //
  void registerWidget( QWidget* w );
  void unregisterWidget( QWidget* w );

#ifdef _WIN32
  // Utility function to setup logical color palette for 8bit devices
  static HPALETTE _setupColorPalette( HDC );
#endif //_WIN32

  virtual bool eventFilter( QObject* object,QEvent *event );
  //
  // This method can be used by subclasses to open a component help
  // card. The name of the file should be supplied withought a path
  // name. By default the file will be searched using:
  // 1) current working directory
  // 2) SO_HELP_DIR environment variable
  // 3) /usr/share/help/Inventor
  // 4) else bring a no help card found dialog
  //
  void openHelpCard( const char* cardName );

  static void windowCloseActionCB( SoWidget widget, SoQtComponent* p, void* data );

 private:
#ifdef _WIN32
	const char* buildHelpPath( const char* filename );
#endif
   void constructorCommon( QWidget* parent, const char* name, SbBool buildInsideParent, SbBool sync );

  //Implementation class for SoXxComponent
  SoGuiComponent* m_guiComponent;

  SbBool createdShell; // TRUE if we created that toplevel shell
  QWidget* parentWidget; // topLevel shell if in its own window
  QPointer<QWidget> _baseWidget; // returned by getWidget()

  SbVec2s size; // size of the '_baseWidget' and 'shell' (if toplevel)

  // The widget dictionary maps widgets to SoXtComponents. It's used
  // by getComponent(), and kept up to date by registerWidget().
  static SbDict* widgetDictionary;

  // For fullscreen mode.
  SbBool  wasTopLevel;

  QWidget* m_fullScreen;
  QSize* m_wSize;

  QPoint m_wPosition;

  // Window close action data
  SoQtComponentCB* m_windowCloseFunc;
  void* m_windowCloseData;
};

// Inline routines
INVENTORQT_API SbGlContextHelper::Display
SoQtComponent::getDisplay()
{
  return SoQt::getDisplay();
}

inline const QString
SoQtComponent::getTitle() const
{
  return QString::fromUtf16( m_guiComponent->getTitle().toUtf16() );
}

inline const QString
SoQtComponent::getIconTitle() const
{
  return QString::fromUtf16( m_guiComponent->getIconTitle().toUtf16() );
}

inline SbString
SoQtComponent::getClassName() const
{
 return m_guiComponent->getClassName();
}

inline SbString
SoQtComponent::getWidgetName() const
{
 return m_guiComponent->getWidgetName();
}

#endif // _SO_QT_COMPONENT_

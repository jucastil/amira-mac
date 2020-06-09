/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David Mott (MMM yyyy)
** Modified by : Alain Dumesny (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifdef SOQT
#  include <Inventor/Qt/SoQtComponent.h>
#elif defined SOWX
#  include <Inventor/Wx/SoWxComponent.h>
#elif defined _WIN32
#  include <Inventor/Win/SoWinComponent.h>
#else // _WIN32

#ifndef _SO_XT_COMPONENT_H_
#define _SO_XT_COMPONENT_H_

#include <X11/Intrinsic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>
#include <Inventor/Gui/SoGuiComponent.h>
#include <Inventor/Xt/SoXtDef.h>

class SbDict;
class SoXtComponent;
class SoCallbackList;

typedef void SoXtComponentCB( void* data, SoXtComponent* v );
typedef void SoXtComponentVisibilityCB( void* data, SbBool b );

/**
 * Abstract base class for all Open Inventor components.
 *
 * @ingroup Xt
 *
 * @DESCRIPTION
 *   Abstract base class from which all Open Inventor Xt components are derived.
 *   This class provides a basic C++ protocol for building and displaying Motif
 *   components. Components are used to encapsulate some function or task into a
 *   reusable package in the form of a Motif widget that can be used in any
 *   Open Inventor Xt program. See the Example section on how to build and use
 *   SoXtComponents.
 *
 * @EXAMPLE
 *    This example shows how an Open Inventor component can be built inside a program
 *   using the Xt widget set. The example uses the SoXtExaminerViewer widget to view
 *   some simple geometry.
 *
 *   @code
 *
 *   #include <Inventor/Xt/SoXt.h>
 *
 *   #include <Inventor/nodes/SoCone.h>
 *
 *   #include <Inventor/Xt/viewers/SoXtExaminerViewer.h>
 *
 *   void main(int, char **argv)
 *
 *   // Initialize Inventor and Xt, which must be done
 *
 *   // before any Inventor calls are made.
 *
 *   SoWidget myWindow = SoXt::init(argv[0]);
 *
 *   // create the viewer in the toplevel window
 *
 *   // and set some scene to display
 *
 *   SoXtExaminerViewer *myViewer = new SoXtExaminerViewer(myWindow);
 *
 *   myViewer->setSceneGraph( new SoCone() );
 *
 *   // manage and map window on screen
 *
 *   myViewer->show();
 *
 *   SoXt::show(myWindow); // calls Show()
 *
 *   // Loop forever
 *
 *   SoXt::mainLoop();
 *
 *   @endcode
 *
 * @RESOURCES
 * <PRE>
 *   !!------------------------------------------------
 *   !! Xt Component ( For Light and Material Sliders Set )
 *   !!------------------------------------------------
 *   *IvXtComponentTitle.labelString: Xt Component
 *   *IvTGSXtComponentTitle.labelString: VSG: Xt Component
 * </PRE>
 *
 * @SEE_ALSO
 *    SoXt,
 *    SoXtRenderArea,
 *    SoXtViewer,
 *    SoXtMaterialEditor
 *
 *
 */

class INVENTORXT_API SoXtComponent
{

 public:

  /**
   * Static method to display the specified topic of the specified help file.
   * This method can be used when the help file needs to be displayed from
   * a user's application but the pointer to the viewer is not available.
   * For example,
   * in an MFC application where the method used to display the help file
   * is not in the View class.
   * Only a compiled HTML help file (.chm) can be displayed with this method.
   */
  static  void displayHelp( const char*  filename, UINT contextID );

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
   *
   * Subclasses should call this routine before redrawing anything and in any sensor
   * trigger methods. Calling this will check the current visibility (which is really
   * cheap) and invoke the visibility changed callbacks if the state changes (see
   * addVisibilityChangeCallback()).
   */
  SbBool isVisible();

  /**
   * This returns the base widget for this component. If the component created its
   * own shell, this returns the topmost widget beneath the shell. Call
   * getShellWidget() to obtain the shell.
   */
  SoWidget getWidget() const { return _baseWidget; }

  /**
   * Returns TRUE if this component is a top level shell component (has its own
   * window). Subclasses may use this to decide if they are allowed to resize
   * themselves.
   */
  SbBool isTopLevelShell() const { return m_guiComponent->isTopLevelShell(); }

  /**
   * Returns the shell widget (NULL if the shell
   * hasn't been created by this component).
   */
  SoWidget getShellWidget() const { return m_guiComponent->isTopLevelShell() ? parentWidget : NULL; }

  /**
   * Returns the parent widget, be it a shell or not.
   */
  SoWidget getParentWidget() const { return parentWidget; }

  /**
   * Convenience routine on the widget.
   */
  void setSize( const SbVec2s& size );

  /**
   * Convenience routine on the widget.
   */
  SbVec2s getSize();

  /**
   * Switches the viewer into (or out of) fullscreen mode.
   */
  SbBool setFullScreen( const SbBool enable );

  /**
   * Queries if the viewer is in fullscreen mode.
   */
  SbBool isFullScreen(void) const;

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
  SbBool isFullScreenEnable() const;

  /**
   * Queries if the viewer is in DirectViz mode.
   */
  SbBool isDirectViz(void) const;

  /**
   * Enables/disables DirectViz mode.
   */
  void setDirectVizEnable(const SbBool enable);

  /**
   * Queries if it is possible to put the viewer
   * in DirectViz mode.
   */
  SbBool isDirectVizEnable(void) const;

  /**
   * Returns the X display associated with this components widget.
   */
  inline Display* getDisplay();

  /**
   * Sets window title.
   * The window title can be set for topLevelShell components or
   * components which are directly under a shell widget (i.e. components which have
   * their own window).
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setTitle( const char* newTitle );


  /**
   * Sets window title.
   * The window title can be set for topLevelShell components or
   * components which are directly under a shell widget (i.e. components which have
   * their own window).
   */
  void setTitle( const SbString& newTitle );

  /**
   * Gets window title.
   */
  SbString getTitle() const { 
    return m_guiComponent->getTitle(); }

  /**
   * Sets icon title.
   * The icon title can be set for topLevelShell components or
   * components which are directly under a shell widget (i.e. components which have
   * their own window).
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setIconTitle( const char* newIconTitle );

  /**
   * Sets icon title.
   * The icon title can be set for topLevelShell components or
   * components which are directly under a shell widget (i.e. components which have
   * their own window).
   */
  void setIconTitle( const SbString& newIconTitle );

  /**
   * Gets icon title.
   */
  SbString getIconTitle() const { 
    return m_guiComponent->getIconTitle(); }


  /**
   * Sets which callback to call when the user closes this component (double click in
   * the upper left corner) - by default hide() is called on this component,
   * unless a callback is set to something other than NULL. A pointer to this class
   * will be passed as the callback data.
   *
   * Note: this callback is supplied because the user may wish to delete this
   * component when it is closed.
   */
  void setWindowCloseCallback( SoXtComponentCB* func, void* data = NULL )
    { windowCloseFunc = func; windowCloseData = data; }

  /**
   * This returns the SoXtComponent for this widget. If the widget does not match
   * that of any Open Inventor component, then NULL is returned.
   */
  static SoXtComponent* getComponent( SoWidget w );

  /**
   * Returns the widget name. The widget name is
   * passed to the build method.
   */
  SbString getWidgetName() const { 
    return m_guiComponent->getWidgetName(); }

  /**
   * Returns the class name.
   * The class name is predefined by each component.
   */
  SbString getClassName() const { 
    return m_guiComponent->getClassName(); }


 SoINTERNAL public:

  virtual ~SoXtComponent();

  // Deprecated. Replaced by getWidget().
  SoWidget baseWidget() const { return getWidget(); }

  virtual void posChanged( const SbVec2i32&, const SbVec2i32& ) {};

  SoGuiComponent* getGuiComponent() const;

 protected:
  //
  // If `parent` widget is suplied AND `buildInsideParent` is TRUE, this
  // component will build inside the given parent widget, else
  // it will create its own topLevelShell widget (component resides in
  // its own window).
  // The topLevelShell can either be created under the given
  // parent shell (`parent` != NULL) or under the main window.
  //
  // The name is used for looking up X resource values. If NULL,
  // then this component inherits resource values defined for its class.
  //
  // Calling setBaseWidget is needed for looking up Xt like
  // resources in the widget tree. It will use the class name of
  // the Inventor component (e.g. SoXtRenderArea) instead of
  // the class name of the Motif widget this component employs
  // (e.g. XmForm).
  //
  // Thus apps are able to do this in their app-defaults file:
  //
  // *SoXtRenderArea*BackgroundColor: salmon
  //
  SoXtComponent( SoWidget parent = NULL,
                 const char* name = NULL,
                 SbBool buildInsideParent = TRUE,
                 SbBool sync = TRUE );

  SoXtComponent( SoWidget parent,
                 const char* name,
                 SbBool buildInsideParent,
                 SbBool sync,
                 SoGuiComponent* guiComponent );

  // Subclasses need to call this method passing the top most
  // widget after it has been created.
  void setBaseWidget( SoWidget w );

  // Subclasses need to set the class name in the constructor
  // before the widget is built.
  void setClassName( const SbString &n ) { m_guiComponent->setClassName( n ); }

  // this routine is called whenever the top level shell widget receives
  // a close action (WM_DELETE_WINDOW message) from the window manager.
  // Instead of destroying the widget (default shell behavior) this
  // routine is used, which by default calls exit(0) if it is the main
  // window else calls hide() on the component.
  //
  virtual void windowCloseAction();

  // Support for doing things right after the widget is realized
  // for the first time.
  // The base class will set the window and icon title for shell widgets.
  virtual void afterRealizeHook();
  SbBool firstRealize;

  //
  // Subclasses should redefine these routines to return the appropriate
  // default information. Those are used when creating the widget to set
  // the name (used for resources), window title and window icon
  // name. Those default values are only used if the user didn't
  // explicitly specify them.
  //
  virtual SbString getDefaultWidgetName() const;
  virtual SbString getDefaultTitle() const;
  virtual SbString getDefaultIconTitle() const;

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
  void registerWidget( SoWidget w );
  void unregisterWidget( SoWidget w );

  // subclasses can add a callback to be called whenever the component
  // becomes visible or become hidden (like when it is iconified).
  // Sublcasses should use this to attach or detach any sensors they
  // have, or stop any ongoing anymation.
  void addVisibilityChangeCallback( SoXtComponentVisibilityCB* func, void* userData = NULL );
  void removeVisibilityChangeCallback( SoXtComponentVisibilityCB* func, void* userData = NULL );

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

  // This method is used to get label from resources for Localisation.
  static SbString getlabel( unsigned int whatisit );// const;



 private:

  void constructorCommon( SoWidget parent, const char* name, SbBool buildInsideParent, SbBool sync );

  // Call a web browser to open the passed URL
  SbBool callWebBrowser( const char* url ) const;

  // widgetDestroyed is called when the widget is destroyed.
  // There is no way to reconstruct the widget tree, so calling
  // this simply generates an error. The component should be
  // deleted to dispose of the widget.
  virtual void widgetDestroyed();

  SbBool createdShell; // TRUE if we created that toplevel shell
  SoWidget parentWidget; // topLevel shell if in its own window
  SoWidget _baseWidget; // returned by getWidget()
  SbVec2s size; // size of the '_baseWidget' and 'shell' (if toplevel)

  // visibiltity stuff
  SbBool visibleState;
  SbBool ShellMapped, widgetMapped;
  SoCallbackList* visibiltyCBList;
  void checkForVisibilityChange();
  static void widgetStructureNotifyCB( SoWidget w, SoXtComponent* p, XEvent* xe, Boolean* b );
  static void shellStructureNotifyCB( SoWidget w, SoXtComponent* p, XEvent* xe, Boolean* b );
  static void widgetDestroyedCB( SoWidget w, XtPointer clientData, XtPointer p );

  // window close action data
  SoXtComponentCB* windowCloseFunc;
  void* windowCloseData;
  static void windowCloseActionCB( SoWidget w, SoXtComponent* v, void* data );

  // The widget dictionary maps widgets to SoXtComponents. It's used
  // by getComponent(), and kept up to date by registerWidget().
  static SbDict* widgetDictionary;

  // For fullscreen mode.
  Dimension posX, posY, width, height;

  SoGuiComponent* m_guiComponent;

  // For DirectViz mode
  SbBool m_directVizOn;
  SbBool m_directVizEnabled;
};

// Inline routines
Display*
SoXtComponent::getDisplay()
{
  return (_baseWidget != NULL ? XtDisplay(_baseWidget) : NULL);
}

#endif // _SO_XT_COMPONENT_H_

#endif // _WIN32



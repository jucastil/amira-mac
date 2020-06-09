/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/



#ifndef _SO_WIN_COMPONENT_H_
#define _SO_WIN_COMPONENT_H_

#include <Inventor/Win/SoWinBeginStrict.h>
#include <windows.h>
#include <Inventor/Win/SoWin.h>
#include <Inventor/Win/SoWinDef.h>
#include <Inventor/Gui/SoGuiComponent.h>

#include <Inventor/SbLinear.h>
#include <Inventor/SbString.h>

class SbDict;
class SoWinComponent;
class SoCallbackList;
class SoWinComponentP;

typedef void SoWinComponentCB( void* userData, SoWinComponent* comp );
typedef void SoWinComponentVisibilityCB( void* userData, SbBool visibleFlag );

/**
 * @VSGEXT Abstract base class for all Open Inventor components.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   Abstract base class from which all Open Inventor Windows components are derived.
 *   This class provides a basic C++ protocol for building and displaying Windows
 *   components. Components are used to encapsulate some function or task into a
 *   reusable package in the form of a Windows window handle that can be used in any
 *   Open Inventor Windows program. See the Example section on how to build and use
 *   SoWinComponents.
 * 
 * @EXAMPLE
 *    This example shows how an Open Inventor component can be built inside a program
 *   using the Windows window handle set. The example uses the SoWinExaminerViewer
 *   window handle to view some simple geometry.
 *
 *   @code
 *   #include <Inventor/Win/SoWin.h>
 *   
 *   #include <Inventor/nodes/SoCone.h>
 *   
 *   #include <Inventor/Win/viewers/SoWinExaminerViewer.h>
 *   
 *   
 *   void main(int, char* *argv)
 *   
 *   
 *   // Initialize Inventor and Windows, which must be done
 *   
 *   // before any Inventor calls are made.
 *   
 *   HWND myWindow =
 *   SoWin::init(argv[0]);
 *   
 *   
 *   // create the viewer in the toplevel window
 *   
 *   // and set some scene to display
 *   
 *   SoWinExaminerViewer *myViewer = new SoWinExaminerViewer(myWindow);
 *   
 *   myViewer->setSceneGraph( new SoCone() );
 *   
 *   
 *   // manage and map window on screen
 *   
 *   myViewer->show();
 *   
 *   SoWin::show(myWindow); // calls Show()
 *   
 *   
 *   // Loop forever
 *   
 *   SoWin::mainLoop();
 *
 *   @endcode
 * 
 * @SEE_ALSO
 *    SoWin,
 *    SoWinRenderArea,
 *    SoWinViewer,
 *    SoWinMaterialEditor
 * 
 * 
 */ 

class INVENTORW_API SoWinComponent
{
    friend class SoWinComponentP;
  
 public:

#ifdef OIV_NET_DOC
	 /**
	 * Static method to display the specified topic of the specified help file.
	 * This method can be used when the help file needs to be displayed from 
	 * a user's application but the reference to the viewer is not available.
   *
   * @UNICODE_WARNING
	 */

#else
	 /**
	 * Static method to display the specified topic of the specified help file.
	 * This method can be used when the help file needs to be displayed from 
	 * a user's application but the pointer to the viewer is not available.
	 * For example,
	 * in an MFC application where the method used to display the help file
	 * is not in the View class.
	 * Only a compiled HTML help file (.chm) can be displayed with this method.
   *
   * @UNICODE_WARNING
	 */

#endif //OIV_NET_DOC
	 SoNONUNICODE static void displayHelp( const char*  filename, UINT contextID );   
  

#ifdef OIV_NET_DOC
	 /**
	 * Static method to display the specified topic of the specified help file.
	 * This method can be used when the help file needs to be displayed from 
	 * a user's application but the reference to the viewer is not available.
	 */

#else
	 /**
	 * Static method to display the specified topic of the specified help file.
	 * This method can be used when the help file needs to be displayed from 
	 * a user's application but the pointer to the viewer is not available.
	 * For example,
	 * in an MFC application where the method used to display the help file
	 * is not in the View class.
	 * Only a compiled HTML help file (.chm) can be displayed with this method.
	 */

#endif //OIV_NET_DOC
	 static void displayHelp( const SbString& filename, UINT contextID ); 

  /**
   * This shows the component. If this is a topLevelShell component, then show()
   * will Realize and Map the window, else it will simply Manage the widget.
   * In addition, show() will also pop the component window to the top and de-iconify
   * if necessary, to make sure the component is visible by the user.
   */
  virtual void show();

  /**
   * This hides the component. It calls the appropriate unrealize or unmanage routines.
   */
  virtual void hide();
    
  /**
   * Returns TRUE if this component is mapped onto the screen. For a component to be
   * visible, its window handle and the shell containing this window handle must be
   * mapped (which is FALSE when the component is iconified).
   * 
   * Subclasses should call this routine before redrawing anything and in any sensor
   * trigger methods. Calling this will check the current visibility (which is really
   * cheap) and invoke the visibility changed callbacks if the state changes (see
   * addVisibilityChangeCallback()).
   */
  SbBool isVisible();
    
  /**
   * This returns the base window handle for this component. If the component created
   * its own shell, this returns the topmost window handle beneath the shell. Call
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
   * Returns the shell window handle (NULL if the shell
   * hasn't been created by this component).
   */
  SoWidget getShellWidget() const { return m_guiComponent->isTopLevelShell() ? parentWidget : NULL; }

  /**
   * Returns the parent window handle, be it a shell or not.
   */
  SoWidget getParentWidget() const { return parentWidget; }

  /**
   * Convenience routine on the window handle.
   */
  void setSize( const SbVec2s& size );

  /**
   * Convenience routine on the window handle.
   */
  SbVec2s getSize();

  /**
   * Switches the viewer into (or out of) fullscreen mode.
   */
  SbBool setFullScreen( const SbBool enable );

  /**
   * Queries if the viewer is in fullscreen mode.
   */
  SbBool isFullScreen() const;

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
  SbBool isFullScreenEnable( void ) const;

  /**
   * Included for portability only.
   */
  UINT* getDisplay() { return NULL; }

  /**
   * Sets window title.
   * The window title can be set for topLevelShell components or components which are
   * directly under a shell window handle (i.e. components which have their own
   * window).
   *
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setTitle( const char* newTitle );

  /**
   * Sets window title.
   * The window title can be set for topLevelShell components or components which are
   * directly under a shell window handle (i.e. components which have their own
   * window).
   *
   */
  void setTitle( const SbString& newTitle );

  /**
   * Gets window title.
   */
  SbString getTitle() const { return m_guiComponent->getTitle(); }

  /**
   * Included for portability only.
   * @UNICODE_WARNING
   */
  SoNONUNICODE void setIconTitle( const char* newIconTitle );

  /**
   * Included for portability only.
   */
  void setIconTitle( const SbString& newIconTitle );

  /**
   * Included for portability only.
   */
  SbString getIconTitle() const { return m_guiComponent->getIconTitle(); }

#ifdef OIV_NET_DOC
  /**
  * Sets the delegate to invoke when the user closes this component (double click in
  * the upper left corner) - by default Hide() is called on this component,
  * unless a delegate is specified. A reference to this class
  * will be passed as invocation method argument.
  * 
  * Note: this delegate is supplied because the user may wish to dispose this
  * component when it is closed.
  */

#else
  /**
  * Sets which callback to call when the user closes this component (double click in
  * the upper left corner) - by default hide() is called on this component,
  * unless a callback is set to something other than NULL. A pointer to this class
  * will be passed as the callback data.
  * 
  * Note: this callback is supplied because the user may wish to delete this
  * component when it is closed.
  */

#endif //OIV_NET_DOC
  void setWindowCloseCallback( SoWinComponentCB *func, void* data = NULL )
    { windowCloseFunc = func; windowCloseData = data; }

  /**
   * Returns the SoWinComponent for this window handle. If the window handle
   * does not match that of any Open Inventor component, then NULL is returned.
   */
  static SoWinComponent* getComponent( SoWidget w );

  /**
   * Returns the window handle name. The window
   * handle name is passed to the build method. 
   */
  SbString getWidgetName() const { return m_guiComponent->getWidgetName(); } 

  /**
   * Returns the class name. 
   * The class name is predefined by each component.
   */
  SbString getClassName() const { return m_guiComponent->getClassName(); }

  /**
   * Name of help file to open when the viewer Help button is pressed.
   */
  SbString helpFileName;

  /**
   * The context ID of the help topic to open when the viewer Help button is
   * pressed.
   */
  UINT helpContextID;

  /**
   * The TopicID of the help topic to open when the viewer Help button is
   * pressed.
   */
  SbString helpContextString;

 SoINTERNAL public:

  /** [OIV-WRAPPER VISIBILITY{Internal}] */
  virtual ~SoWinComponent();

  // Deprecated. Replaced by getWidget().
  SoWidget baseWidget() const { return getWidget(); }

  static void exitClass();

  // Returns the current guiComponent
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
  // the Inventor component (e.g. SoWinRenderArea) instead of
  // the class name of the Motif widget this component employs
  // (e.g. XmForm).
  // 
  // Thus apps are able to do this in their app-defaults file:
  //
  // *SoWinRenderArea*BackgroundColor: salmon
  //
  SoWinComponent( SoWidget parent = NULL,
                  const SbString& name = "", 
                  SbBool buildInsideParent = TRUE,
                  SbBool sync = TRUE );

  SoWinComponent( SoWidget parent,
                  const SbString& name, 
                  SbBool buildInsideParent,
                  SbBool sync,
                  SoGuiComponent* guiComponent );

  // Subclasses need to call this method passing the top most
  // widget after it has been created.
  void setBaseWidget( SoWidget w );
  
  // Subclasses need to set the class name in the constructor
  // before the widget is built.
  void setClassName( const SbString& n ) { m_guiComponent->setClassName( n ); }
  
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
  void addVisibilityChangeCallback( SoWinComponentVisibilityCB* func, 
                                    void* userData = NULL );
  void removeVisibilityChangeCallback( SoWinComponentVisibilityCB* func, 
                                       void* userData = NULL );
  
  //
  // This method can be used by subclasses to open a component help
  // card. The name of the file should be supplied without a path
  // name. By default the file will be searched using:
  // 1) current working directory
  // 2) SO_HELP_DIR environment variable
  // 3) /usr/share/help/Inventor
  // 4) else bring a no help card found dialog
  //
  void openHelpCard( const SbString& cardName );
  
  // Used to factorize displayHelp and openHelpCard methods.
  static void internalDisplayHelp(const SbString& path, UINT contextID, HWND hWndMain = NULL);  

  SoWidget buildFormWidget( SoWidget parent );
  
  void setResize( SbBool nResize ) { m_nResizeBaseWidget = nResize; }
  SbBool getResize() { return m_nResizeBaseWidget ; }

  // Utility function to setup logical color palette for 8bit devices
  static HPALETTE _setupColorPalette( HDC );
  
  void unSubclassDialog( Hwnd hWnd );
  void subclassDialog( Hwnd hWnd );
  void drawDialogIcon( Hwnd hWnd );
  
  static LRESULT CALLBACK dlgWndProc( Hwnd hwnd, UINT message,
                                      WPARAM wParam, LPARAM lParam );
  static Hwnd getMDIAncestor( Hwnd win );
  
  // If parent of glxMgrWindow is MDI we need to call DefMDIChildProc
  // in mgrWindowProc instead of DefWindowProc
  SbBool m_nParentIsMDI;
  
  HICON hDlgIcon;
  
  char* windowName;
  SbBool buildInside;
  
  static void widgetStructureNotifyCB( SoWidget w, SoWinComponent* c, XEvent* e, Boolean* b );
  static void windowCloseActionCB(SoWidget, SoWinComponent *, void *);
  static int ChoosePixelFormatOIV( HDC hdc, int pixelType, int glModes, PIXELFORMATDESCRIPTOR* pfd );

 private:

   void constructorCommon( SoWidget parent, const SbString& name, SbBool buildInsideParent, SbBool sync );

  // widgetDestroyed is called when the widget is destroyed.
  // There is no way to reconstruct the widget tree, so calling
  // this simply generates an error. The component should be
  // deleted to dispose of the widget.
  virtual void widgetDestroyed();

	// Builds the path to the filename and returns it if the file exists, NULL otherwise.
	static SbString buildHelpPath( const SbString& filename );
  
  SbBool createdShell; // TRUE if we created that toplevel shell
  SoWidget parentWidget; // topLevel shell if in its own window
  SoWidget _baseWidget; // returned by getWidget()
  SbVec2s size; // size of the '_baseWidget' and 'shell' (if toplevel)
  
  // visibiltity stuff
  SbBool visibleState;
  SbBool ShellMapped, widgetMapped;
  SoCallbackList *visibiltyCBList;
  void checkForVisibilityChange();
  
  // For fullscreen.
  SbVec2s viewerPos;
  SbVec2s viewerSize;
  long style, extStyle;
  
  static void shellStructureNotifyCB( SoWidget w, SoWinComponent* c, XEvent* e, Boolean* b );
  static void widgetDestroyedCB( SoWidget w, XtPointer p1, XtPointer p2 );
  
  // window close action data
  SoWinComponentCB* windowCloseFunc;
  void* windowCloseData;

  // The widget dictionary maps widgets to SoWinComponents. It's used
  // by getComponent(), and kept up to date by registerWidget().
  static SbDict* widgetDictionary;
  
  // If we subclass our parent, remember parent's original wndproc so we
  // can pass messages along to it.
  //
  // The bit about "ifdef STRICT" is strange but true...
#ifdef STRICT
  WNDPROC parentWndProc;
  WNDPROC origDlgWndProc;
#else
  FARPROC parentWndProc;
  FARPROC origDlgWndProc;
#endif
  // if this is true, then SoWinComponent resizes the base widget when
  // it receive WM_SIZE, otherwise no resize
  SbBool m_nResizeBaseWidget;
  
  static void OnWmSize( Hwnd hwnd, UINT message,
                        WPARAM wParam, LPARAM lParam );
  static void OnWmPaint( Hwnd hwnd, UINT message,
                         WPARAM wParam, LPARAM lParam );
  static void OnWmDestroy( Hwnd hwnd, UINT message,
                           WPARAM wParam, LPARAM lParam );
  
  // Window proc for "subclassing" parent shell window (to track size changes)
  static LRESULT CALLBACK componentWndProc( Hwnd hwnd, UINT message,
                                            WPARAM wParam, LPARAM lParam );
  static LRESULT CALLBACK formWindowProc( Hwnd hwnd, UINT message,
                                          WPARAM wParam, LPARAM lParam );

  //Implementation class for SoXxComponent
  SoGuiComponent* m_guiComponent;
};

#include <Inventor/Win/SoWinEndStrict.h>

#endif // _SO_WIN_COMPONENT_H_


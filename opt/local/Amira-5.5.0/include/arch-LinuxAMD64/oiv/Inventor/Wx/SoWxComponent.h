/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef SO_WX_COMPONENT
#define SO_WX_COMPONENT

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWxComponent
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/Wx/SoWx.h>
#include <Inventor/Gui/SoGuiComponent.h>

#include <Inventor/SbBasic.h>
#include <Inventor/SbString.h>
#include <Inventor/SbDict.h>

/**
 * @VSGEXT Abstract base class for all Open Inventor Wx components.
 * 
 * @ingroup Wx
 * 
 * @DESCRIPTION
 *   Abstract base class from which all Open Inventor Wx components are derived.
 *   This class provides a basic C++ protocol for building and displaying Wx
 *   components. Components are used to encapsulate some function or task into a
 *   reusable package in the form of a Wx widget handle that can be used in any
 *   Open Inventor Wx program. See the Example section on how to build and use
 *   SoWxComponents.
 * 
 * @EXAMPLE
 *    This example shows how an Open Inventor component can be built inside a program
 *   using the Wx widget handle set. The example uses the SoWxExaminerViewer
 *   widget handle to view some simple geometry.
 *   
 *   // For compilers that support precompilation, includes "wx.h".
 *   \#include <wx/wxprec.h>
 *
 *   // must be inserted in case of a compilation with Borland C++
 *   \#ifdef __BORLANDC__
 *   \#pragma hdrstop
 *   \#endif
 *
 *   \#ifndef WX_PRECOMP
 *   \#include <wx/wx.h>
 *   \#endif
 *
 *   \#include <Inventor/Wx/SoWx.h> @BR
 *   \#include <Inventor/nodes/SoCone.h> @BR
 *   \#include <Inventor/Wx/viewers/SoWxExaminerViewer.h> @BR
 *   
 *    class WxHelloCone: public wxApp
 *    {
 *      public:
 *      virtual bool OnInit();
 *
 *      virtual int OnExit();
 *    };
 *
 *    IMPLEMENT_APP( WxHelloCone )
 *   
 *    bool
 *    WxHelloCone::OnInit()
 *    {
 *      // Initialize Inventor and Wx, which must be done @BR
 *      // before any Inventor calls are made.@BR
 *   
 *      wxFrame* myWindow = new wxFrame( NULL, wxID_ANY, argv[0], wxDefaultPosition, 
 *                                       wxDefaultSize, wxDEFAULT_FRAME_STYLE, "" );
 *
 *      SoWx::init( wxTheApp, myWindow );
 *   
 *      // Create the viewer in the toplevel window @BR
 *      // and set some scene to display. @BR
 *   
 *      SoWxExaminerViewer *myViewer = new SoWxExaminerViewer(myWindow); @BR
 *      myViewer->setSceneGraph( new SoCone() );
 *   
 *      // Map window on screen.
 *   
 *      myViewer->show();  @BR
 *      SoWx::show(myWindow); // calls Show()
 *      return true;
 *    }
 *
 *    int
 *    WxHelloCone::OnExit()
 *    {
 *      SoWx::finish(); // Properly cleans Open Inventor
 *
 *      return 0;
 *    }
 *   
 * 
 * @SEE_ALSO
 *    SoWx,
 *    SoWxRenderArea,
 *    SoWxViewer
 * 
 * 
 */ 
class INVENTORWX_API SoWxComponent : public wxEvtHandler
{

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
  wxWindow* getWidget() const { return m_baseWidget; }

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
  wxWindow* getShellWidget() const { return m_guiComponent->isTopLevelShell() ? m_parentWidget : NULL; }

  /**
   * Returns the parent widget handle.
   */     
  wxWindow* getParentWidget() const { return m_parentWidget; }

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
   * X Window System. For details, see the wxWidgets documentation 
   * for wxTopLevelWindow::ShowFullScreen.
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
  SbBool isFullScreenEnable( void ) const;
        
  /**
   * On UNIX, returns the X display associated with this components widget. 
   */
  inline SbGlContextHelper::Display getDisplay();

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
   */ 
  void setTitle( const SbString& newTitle );

  /**
   * Gets window title.
   */ 
  SbString getTitle() const { return m_guiComponent->getTitle(); }

  /**
   * Included for portability only.
   *
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
  SbString getIconTitle() const 
  { return m_guiComponent->getIconTitle(); }

  /**
   * Returns the SoWxComponent for this widget handle. If the widget handle
   * does not match that of any Open Inventor component, then NULL is returned.
   */
  static SoWxComponent* getComponent( wxWindow* widget );

  /**
   * Returns the widget handle name. The widget
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

#ifdef _WIN32
  /**
   * The context ID of the help topic to open when the viewer Help button is
   * pressed.
   */
  UINT helpContextID;
#endif
           
 SoINTERNAL public:
        
  virtual ~SoWxComponent();
        
  void setFullScreenOn( SbBool enable ) { m_guiComponent->setFullScreen( enable ); }

  static void finish();

  SoGuiComponent* getGuiComponent() const;

 protected:
        
  SoWxComponent( wxWindow* parent = NULL,
                 const SbString& name = "", 
                 SbBool buildInsideParent = TRUE,
                 SbBool sync = TRUE );

  SoWxComponent( wxWindow* parent,
                 const SbString& name, 
                 SbBool buildInsideParent,
                 SbBool sync,
                 SoGuiComponent* guiComponent );
        
  void setBaseWidget( wxWindow* w );

  void setClassName( const SbString& n ) { m_guiComponent->setClassName( n ); }
        
  virtual void  afterRealizeHook();

  //First realize state
  SbBool m_firstRealize;

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
  void registerWidget( wxWindow* w );
  void unregisterWidget( wxWindow* w );

#ifdef _WIN32
#ifdef WX_NOPORT
  // Utility function to setup logical color palette for 8bit devices
  static HPALETTE _setupColorPalette( HDC );
#endif // WX_NOPORT
        
  static int ChoosePixelFormatOIV( HDC hdc,int pixelType, int glModes, PIXELFORMATDESCRIPTOR* pfd );
#endif //_WIN32

  //
  // This method can be used by subclasses to open a component help
  // card. The name of the file should be supplied withought a path
  // name. By default the file will be searched using:
  // 1) current working directory
  // 2) $(SO_HELP_DIR)/index.htm
  // 3) $(OIVHOME)/doc/index.htm
  // 4) else open the default browser at "http://www.tgs.com/support/oiv_doc/index.htm"
  //
  void openHelpCard( const SbString& cardName );

  //SbBool canSynchronize() { return m_guiComponent->canSynchronize(); }

 private:

   void constructorCommon( wxWindow* parent, const SbString& name, SbBool buildInsideParent, SbBool sync );

  //Implementation class for SoXxComponent
  SoGuiComponent* m_guiComponent;
        
  SbBool m_createdShell; // TRUE if we created that toplevel shell
  wxWindow* m_parentWidget; // topLevel shell if in its own window
  wxWindow* m_baseWidget; // returned by getWidget()
  wxFrame* m_fullScreen;
  SbVec2s m_size; // size of the 'm_baseWidget' and 'shell' (if toplevel)
        
  // The widget dictionary maps widgets to SoWxComponents. It's used
  // by getComponent(), and kept up to date by registerWidget().
  static SbDict* m_widgetDictionary;

  SbBool  m_wasNotTopLevel;
};

// Inline routines
INVENTORWX_API SbGlContextHelper::Display
SoWxComponent::getDisplay()
{
  return SoWx::getDisplay();
}


#endif // SO_WX_COMPONENT

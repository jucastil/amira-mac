/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jun 2007)
**=======================================================================*/

#ifndef SO_GUI_COMPONENT_H
#define SO_GUI_COMPONENT_H

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGuiComponent
//
// SoXXComponent implementation class
// 
//
//////////////////////////////////////////////////////////////////////////////


#include <ScaleViz/viewers/SoGuiBase.h>
#include <Inventor/Gui/SoGui.h>
#include <Inventor/STL/string>
#include <Inventor/SbBasic.h>

#ifndef HIDDEN_FROM_DOC
 // Defines used when specifying the glModes flag to the constructor.
 // (used instead of the glx.h defines which do overlap)
#  define SO_GLX_RGB      (1<<0)
#  define SO_GLX_DOUBLE   (1<<1)
#  define SO_GLX_ZBUFFER  (1<<2)
#  define SO_GLX_OVERLAY  (1<<3)
#  define SO_GLX_STEREO   (1<<4)
#  define SO_GLX_STENCIL  (1<<5)
#endif

/** [OIV-WRAPPER-NO-WRAP] */
class INVENTORGUI_API SoGuiComponent : public SoGuiBase
{
#ifndef HIDDEN_FROM_DOC
  SO_FIELDCONTAINER_HEADER( SoGuiComponent );
#endif

SoINTERNAL public:

  /**
   * Constructor.
   */
  SoGuiComponent();

  /**
   * Returns TRUE if this component is a top level shell component (has its own
   * window). Subclasses may use this to decide if they are allowed to resize
   * themselves. 
   */
  SbBool isTopLevelShell() const;

  /**
   * Sets whether the component is a top level shell component or not.
   */
  void setTopLevelShell( const SbBool topLevelShell );

  /**
   * Switches the viewer into (or out of) fullscreen mode.
   */
  void setFullScreen( const SbBool enable );

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
  SbBool isFullScreenEnable() const;

  /**
   * Sets window title.
   * The window title can be set for topLevelShell components or
   * components which are directly under a shell widget (i.e. components which have
   * their own window). 
   * @param newTitle the title of the window
   */
  void setTitle( const SbString& newTitle );

  /**
   * Returns window title. 
   */
  SbString getTitle() const;

  /**
   * Sets icon title.
   * The icon title can be set for topLevelShell components or
   * components which are directly under a shell widget (i.e. components which have
   * their own window). 
   * @param newTitle the title of the icon
   */
  void setIconTitle( const SbString& newIconTitle );

  /**
   * Returns icon title. 
   */
  SbString getIconTitle() const;
 
  /**
   * Returns the widget name. The widget name is
   * passed to the build method.
   */
  SbString getWidgetName() const;

  /**
   * Returns the widget name. The widget name is
   * passed to the build method.
   * @param name the name of the widget
   */
  void setWidgetName( const SbString& name );

  /**
   * Returns the class name. 
   * The class name is predefined by each component. 
   */
  SbString getClassName() const;

  // ----------------------- Extension usage -----------------------------------
  
  // Subclasses need to set the class name in the constructor
  // before the widget is built.
  void setClassName( const SbString& n );

  void setSynchronize( SbBool synch );
  SbBool getSynchronize();

  void setVisible( SbBool visible );

  void setIsQt( const SbBool flag )  { m_isQt = flag; }

  SbBool isQt() const { return m_isQt; }

  void setBaseWidgetHandle( void* _baseWidget ) { m_baseWidgetHandle = _baseWidget; };
  void* getBaseWidgetHandle() const { return m_baseWidgetHandle; };

  virtual SbBool bindNormalContext() { return FALSE; };
  virtual SbBool unbindNormalContext() { return FALSE; };

protected:

  /**
   * Destructor.
   */
  virtual ~SoGuiComponent();

// ----------------------- Private usage -------------------------------------
private:
 
  SbBool m_topLevelShell; // TRUE if in its own window
  SbString m_name; // name of the widget
  SbString m_title; // title for window if in its own window
  SbString m_iconTitle; // title for icon if in its own window
  SbString m_className;

  // For fullscreen mode.
  SbBool m_fullScreenOn;
  SbBool m_fullScreenEnabled;

  SbBool m_isQt;
  void* m_baseWidgetHandle;
};

#endif // SO_GUI_COMPONENT_H



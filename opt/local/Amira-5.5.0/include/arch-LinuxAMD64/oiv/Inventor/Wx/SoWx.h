/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Jul 2007)
**=======================================================================*/

#ifndef SO_WX
#define SO_WX

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoWx
//
//////////////////////////////////////////////////////////////////////////////

#ifndef SOWX
  #define SOWX
#endif

// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

// must be inserted in case of a compilation with Borland C++
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#if defined(_WIN32)
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __INVWXDLL "InventorWxD.dll"
#    define __INVWXLIB "InventorWxD.lib"
#  else
#    define __INVWXDLL "InventorWx.dll"
#    define __INVWXLIB "InventorWx.lib"
#  endif
#  ifndef InventorWx_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__INVWXLIB)
#    endif
#  endif
#else
#    define __INVWXDLL "libInventorWx"
#endif


#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <Inventor/SbLinear.h>
#include <Inventor/Wx/SoWxDef.h>
#include <Inventor/helpers/SbGlContextHelper.h>

#if !defined(_WIN32) && !defined(APPLE)
#include <X11/Xlib.h> 
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoInventorWx, __INVWXDLL)

class SoWxSensorHandler;
class SbPList;

/**
 * @VSGEXT Routines for Open Inventor/Wx compatibility.
 * 
 * @ingroup Wx
 * 
 * @DESCRIPTION
 *   The SoWx class initializes Open Inventor for use with Wx.
 *   SoWx::init() must be called in order for Open Inventor to work properly with
 *   Wx. SoWx::finish() should be called to clean up static memory allocations.
 *   
 *   Refer to the SoWxComponent reference pages for examples on how this class should
 *   be used when using Open Inventor Wx components.
 * 
 * @SEE_ALSO
 *    SoWxComponent
 * 
 * 
 */

class INVENTORWX_API SoWx
{
    
public:

  /**
   * This is called to initialize Open Inventor and Wx, and bind Open Inventor
   * with Wx message handling so that Open Inventor sensors will work correctly. The
   * passed widget handle should be the top level widget handle returned from the
   * Wx initialization. This method will call SoDB::init(),
   * SoNodeKit::init(), and SoInteraction::init().
   */
  static void init( wxApp* app, wxFrame* topLevelWidget );

	/**
	 * Same as above but it initializes wxWidgets and return a wxWindow pointer
	 * without using the "classic" initialization of wxWidgets.
	 */
	static wxWindow* init( const char* appName, const char* className = NULL );

  /**
   * This method calls SoDB::threadInit() rather than SoDB::init().
   * Otherwise it is the same as the corresponding SoWx::init() method.
   */
  static void threadInit( wxApp* app, wxFrame* topLevelWidget  );

  /**
   * Returns TRUE if SoWx module is currently initialized.
   */
  static bool isInitialized();

  /**
   * Convenience routine to show the passed widget handle.
   * 
   * This includes any children the widget may have.
   */           
  static void show( wxWindow* widget );

  /**
   * Convenience routine to hide the passed widget handle.
   * 
   * This includes any children the widget may have.
   */
  static void hide( wxWindow* widget );

  /**
   * This retrieves and dispatches messages (loops forever).
   */
  static void mainLoop();

  /**
   * This method is included for portability only.
   */
  static SbGlContextHelper::Display getDisplay();

  /**
   * Returns information based on the initial wxWindow handle returned by or passed to
   * init.
   */
  static wxFrame* getTopLevelWidget();

  /**
   * Convenience routine to set the size of the given widget.
   */
  static void setWidgetSize( wxWindow* widget, const SbVec2s& size );

  /**
   * Convenience routine to get the size of the given widget.
   */
  static SbVec2s getWidgetSize( wxWindow* widget );

  /**
   * Convenience routine which brings a simple Wx error dialog box displaying
   * the given error string(s) and window title. The OK button, which destroys the
   * dialog, is the only button displayed.
   */
  static void createSimpleErrorDialog( wxWindow* widget, char *dialogTitle, 
                                       char *errorStr1, char *errorStr2 = NULL );

  /** 
   * Frees Open Inventor's internal static memory 
   * allocations. This avoids false positives from memory
   * leak checking software. We recommend calling this method
   * and it should be the last Open Inventor method called by
   * the application. This method calls SoDB::finish(),
   * SoNodeKit::finish(), and SoInteraction::finish().
   */
  static void finish();

 SoINTERNAL public:
  // Hidden from docs...

  static wxFrame* m_mainWidget;

  static wxApp* m_wxApplication;
  static wxApp* getWxApp() { return m_wxApplication; }
 
protected:

 static SoWxSensorHandler* m_sensorHandler;

private:
  static void constructorCommon();
	static int m_wxInitCount;
  static int s_initRefCount;
  static const char *s_versionString;
};

#endif // SO_WX

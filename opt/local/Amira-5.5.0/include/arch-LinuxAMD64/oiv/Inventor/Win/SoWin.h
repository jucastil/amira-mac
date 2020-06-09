/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_WIN_
#define _SO_WIN_

#ifdef _WIN32
#  include <Inventor/Win/SoWinBeginStrict.h>
#  include <string.h>
#  include <windows.h>
#  include <Inventor/Win/SoXt2SoWin.h>
#  include <Inventor/Win/SoWinDef.h>
#  include <Inventor/SbBasic.h>
#  include <SoVersion.h>
#  define RESOURCE_DLL "Error: SoWin resources not loaded\n Cannot find InventorR.DLL"
#else
#  include <Xm/Xm.h>
#endif
#include <Inventor/threads/SbThreadMutex.h>
#include <Inventor/helpers/SbGlContextHelper.h>

#include <Inventor/Win/SoWinLibName.h>

#ifndef InventorWin_EXPORTS
#ifndef OIV_DISABLE_AUTOLINK
#  pragma comment(lib,__INVWLIB)
#endif
#endif

#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/sys/SoDynamicLibManager.h>

class SbPList;
class SoEvent;
class SoWinEventHandler;
class SoOffscreenRenderer;
class SoConsole;
class SbConfig;

#ifdef _WIN32
// Under _WIN32 certain messages are only sent to the toplevel window
// (unlike X where any window can get any event), so SoWin provides an
// additional service.  Other SoWin classes can register a "message
// hook" to request that any time a particular message is sent to the
// toplevel window it will also be sent to that class's window proc.
// This mechanism (generally) requires the cooperation of the app in
// calling SoWin::IsInventorMessage in its message loop (similar to the
// existing Windows requirement to call IsDialogMessage and so on).
class SoWinMessageHook;

// Define some undocumented Windows messages used in SoWinGLWidget
// (supposedly will be defined in NT 3.51 and/or Windows95)
#ifndef WM_ENTERSIZEMOVE
#define WM_ENTERSIZEMOVE 0x0231
#endif
#ifndef WM_EXITSIZEMOVE
#define WM_EXITSIZEMOVE  0x0232
#endif

// Need this decl for error handler (see comments there)
class SoError;

extern CRITICAL_SECTION SoWinGLSection;

#define SOWIN_ENTER_GL_SECTION()\
EnterCriticalSection(&SoWinGLSection)

#define SOWIN_LEAVE_GL_SECTION()\
LeaveCriticalSection(&SoWinGLSection)

#define SOWIN_LEAVE_GL_SECTIONR()\
{\
LeaveCriticalSection(&SoWinGLSection);\
return;\
}

#define SOWIN_LEAVE_GL_SECTIONRV(v)\
{\
LeaveCriticalSection(&SoWinGLSection);\
return v;\
}

#define SOWIN_TIMER_MSG SoWin::wmTimerMsg
#define SOWIN_WORK_MSG  SoWin::wmWorkMsg

#else

#define SOWIN_ENTER_GL_SECTION()
#define SOWIN_LEAVE_GL_SECTION()
#define SOWIN_LEAVE_GL_SECTIONR()
#define SOWIN_LEAVE_GL_SECTIONRV(v)

#endif  //_WIN32

/**
 * @VSGEXT Routines for Open Inventor/Windows compatibility.
 * 
 * @ingroup Win
 * 
 * @DESCRIPTION
 *   The SoWin class initializes Open Inventor for use with Microsoft Windows.
 *   SoWin::init() must be called in order for Open Inventor to work properly with
 *   Windows. SoWin::finish() should be called to clean up static memory allocations.
 *
 *   SoWin::mainLoop() must be called in order for extension device messages
 *   to be passed to Open Inventor render areas. The other methods are convenience
 *   functions.
 *   
 *   Refer to the SoWinComponent reference pages for examples on how this class should
 *   be used when using Open Inventor Windows components.
 * 
 * @SEE_ALSO
 *    SoWinComponent, SoWinErrorConsole
 * 
 * 
 */ 

class INVENTORW_API SoWin {

 public:
  /**
   * This is called to initialize Open Inventor and Windows, and bind Open Inventor
   * with Windows message handling so that Open Inventor sensors will work correctly. @BR
   * Use this method for convenience if you want Open Inventor to create a top-level
   * window for the application.
   * Returns the top level shell window handle.
   * Calls SoDB::init(), SoNodeKit::init(), and SoInteraction::init().
   */
  static SoWidget init(const char *appName,
                     const char *className = "Inventor");

  /**
   * This method calls XXX::threadInit(), rather than XXX::init(). @BR
   * Otherwise it is the same as the corresponding SoWin::init() method.
   * Use this method if you need to use multi-threading with Open Inventor.
   */
  static SoWidget threadInit(const char *appName,
                           const char *className = "Inventor");

  /**
   * This alternate form of init allows the application to initialize Windows. @BR
   * @I TopLevelWidget @i should be the top level window handle returned from the
   * Windows initialization. @BR
   * Calls SoDB::init(), SoNodeKit::init(), and SoInteraction::init().
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static void init(SoWidget topLevelWidget);

  /**
   * This method calls XXX::threadInit(), rather than XXX::init(). @BR
   * Otherwise it is the same as the corresponding SoWin::init() method.
   * Use this method if you need to use multi-threading with Open Inventor.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static void threadInit(SoWidget topLevelWidget);

  /**
   * This alternate form of init does not require a top level window. @BR
   * Calls SoDB::init(), SoNodeKit::init(), and SoInteraction::init().
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static void init();

  /**
   * This method calls XXX::threadInit(), rather than XXX::init(). @BR
   * Otherwise it is the same as the corresponding SoWin::init() method.
   * Use this method if you need to use multi-threading with Open Inventor.
   * [OIV-WRAPPER-CUSTOM-CODE]
   */
  static void threadInit();

  /**
   * Returns TRUE if SoWin module is currently initialized.
   */
  static bool isInitialized();

  /** 
   * Frees Open Inventor's internal static memory 
   * allocations. This avoids false positives from memory
   * leak checking software. We recommend calling this method
   * and it should be the last Open Inventor method called by
   * the application. This method calls SoDB::finish(),
   * SoNodeKit::finish(), and SoInteraction::finish().
   * 
   *@B Note@b: Open Inventor objects should be destroyed before you call this method.
   * \oivnetdoc
   * \else
   * For example:
   * @TABLE_1B
   *  @TR @B Wrong Open Inventor Ending@b
   *  @TD @B Safe Open Inventor Endings@b
   *  @TR <PRE>
   * void main() {
   *   SoWidget myW = SoWin::init("");
   *   SoWinExaminerViewer viewer( myW );
   *   ....
   *   ....
   *   SoWin::mainLoop();
   *   SoWin::finish();
   * }
   *  </PRE>
   *  @TD
   *    @TABLE_0B
   *    @TR <PRE>
   * void runApp() {
   *   SoWinExaminerViewer viewer( myW );
   *   ....
   *   ....
   *   SoWin::mainLoop();
   * }
   *
   * void main () {
   *   SoWidget myW = SoWin::init("");
   *   runApp();
   *   SoWin::finish();
   * }
   * </PRE>
   * @TD <PRE>
   * void main () {
   *   SoWidget myW = SoWin::init("");
   *   SoWinExaminerViewer* viewer
   *          = new SoWinExaminerViewer( myW );
   *   ....
   *   ....
   *   SoWin::mainLoop();
   *   delete viewer;
   *   SoWin::finish();
   *  }
   * </PRE>
   *     @TABLE_END
   * \endoivnetdoc
   * @TR
   * SoWin doesn't end properly: SoWinExaminerViewer is destroyed after the #finish() method has been called.
   * @TD
   * The SoWinExaminerViewer (that uses Open Inventor) is destroyed before the #finish() method is called.
   *     @TABLE_END
   */
  static void finish();

  /**
   * This retrieves and dispatches messages (loops forever). It calls
   * SoWin::nextEvent() and SoWin::dispatchEvent() to do this.
   */
  static void mainLoop();

  /**
   * Get the nextEvent by calling GetMessage. The @B appContext @b can be had by
   * calling SoWin::getAppContext().
   */
  static SbBool nextEvent(XtAppContext appContext, XEvent *event);

  /**
   * Dispatch the passed message to a handler. This returns TRUE if a handler was
   * found, else it returns FALSE.
   */
  static Boolean dispatchEvent(XEvent *event);

  /**
   * This method is included for portability only.
   */
  static XtAppContext getAppContext();
  /**
   * This method is included for portability only.
   */
  static SbGlContextHelper::Display getDisplay();

  /**
   * Returns information based on the initial window handle returned by or passed to
   * init.
   */
  static SoWidget getTopLevelWidget();

  //
  // Convenience routines
  //

  /**
   * Convenience routine to show the passed window handle.
   * 
   * This includes any children the window may have.
   */
  static void show(SoWidget w);

  /**
   * Convenience routine to hide the passed window handle.
   * 
   * This includes any children the window may have.
   */
  static void hide(SoWidget w);

  /**
   * This method is included for portability only.
   */
  static XmString encodeString(char *s);

  /**
   * This method is included for portability only.
   */
  static char *decodeString(XmString xs);

  /**
   * Convenience routine to set the size of the given window.
   */
  static void setWidgetSize(SoWidget w, const SbVec2s &size);
  /**
   * Convenience routine to get the size of the given window.
   */
  static SbVec2s getWidgetSize(SoWidget w);

  // Convenience routine which will return the ShellWidget 
  // containing the given widget. The widget tree is traversed up until
  // a shell widget is found (using XtIsShell()).
  /**
   * Convenience routine which will return the topmost window containing the given
   * window handle. The window handle tree is traversed up until the last window
   * handle is found using GetParent.
   */
  static SoWidget getShellWidget(SoWidget w);

  /**
   * Convenience routine which brings a simple Windows error dialog box displaying
   * the given error string(s) and window title. The OK button, which destroys the
   * dialog, is the only button displayed.
   */
  static void createSimpleErrorDialog(SoWidget widget, char *dialogTitle, 
                                      char *errorStr1, char *errorStr2 = NULL);

  /**
   * This method is included for portability only.
   */
  static void getPopupArgs(UINT *d, int scr, ArgList args, int *n);

  /**
   * This method is included for portability only.
   */
  static void addColormapToShell(SoWidget widget, SoWidget shell);

  /**
   * Returns the VSG error console. An application can use the
   * VSG error console to display its own text messages. See
   * #SoConsole for details.
   */
  static SoConsole *getErrorConsole(void);

  /**
   * If you use SoWin::mainLoop or SoWin::nextEvent, Inventor automatically
   * calls this when the Windows message queue is empty.  If you don't use
   * those utilities you are responsible for periodically processing the
   * tasks in the Inventor "delay queue", *** some of which are critical! ***
   * like notifying the viewer when the scene graph changes.
   */
  static void doIdleTasks(void);

 SoINTERNAL public:
  // This method is obsolete.
  // Processes message hooks defined by SoWin classes so they can get
  // notification of messages that are only passed to toplevel window.
  // Intended to be called by app as first thing in its window proc
  // (at this we consider this better than subclassing toplevel window).
  //
  // SoWin::windowProc makes this call when SoWin creates toplevel window.
  static LRESULT isInventorMessage(HWND hwnd, UINT message,
                                   WPARAM wParam, LPARAM lParam);

  // called when thread terminates
  static void terminate(long terminateSyncTime = 100);
  
  // This method processes thread messages.  It returns TRUE
  // if a message was processed.
  static SbBool PreTranslateMessage(MSG *event);
  
  static UINT wmTimerMsg;
  static UINT wmWorkMsg;
  
  // Add/remove the passed event handler for X extension device events
  // (Xt does not handle extension events.)
  // Extension event types are queried from the server at runtime.
  static void addExtensionEventHandler(SoWidget w,
                                       int extensionEventType,
                                       XtEventHandler proc, 
                                       XtPointer clientData);
  static void removeExtensionEventHandler(SoWidget w,
                                          int extensionEventType,
                                          XtEventHandler proc, 
                                          XtPointer clientData);
  
  // register a class and add it to the registered class list.
  static ATOM registerClass(WNDCLASS *pWndClass, char *actualClassName);
  
  // get information about a class if it has been registered
  static SbBool getClassInfo(HINSTANCE hDll, const char *className,
                             char *actualClassName, WNDCLASS *pClassInfo);
  
  // Called at DLL process detach
  static void unregisterProcessClasses();
  
  // Message hook functions (see long comment above)
  static void addMessageHook(Hwnd hwnd, UINT msg);
  static void removeMessageHook(Hwnd hwnd, UINT msg);
  
  // These member functions only exist to let the Inventor WinMain
  // function save these values for when we actually get around to
  // creating a window (or windows).  --mmh
  
  static void  setInstance(Hinst hInst);
  static Hinst getInstance(void);
  
  static const SoDynamicLibManager::SafeLibraryHandle& getResDllSafeHandle();
  
  static void setPrevInstance(Hinst hInst);
  
  static void setCmdLine(LPSTR cmdLine);
  
  static void setCmdShow(int cmdShow);
  
  // _WIN32 needs this get method for the SoWinEventHandler::xtTimerCallback
  // because we can't specify "client data" when we create the timer.
  
  static SoWinEventHandler *getEventHandler();
  
  // _WIN32 needs this method to identify so-called User Interface (UI)
  // threads (as opposed to Worker threads).  Any thread that creates a
  // window is obligated to process messages for that window (and any
  // others it created) and is considered a UI thread. Therefore any
  // thread that creates an Open Inventor viewer is a UI thread.
  // Worker threads are typically not associated with any window and do
  // not process messages, therefore SoWin does not allow them to
  // schedule timers.  A worker thread might be used to compute data
  // and modify a scene graph.
  //
  // All classes derived from SoWinComponent should call this method.
  // If called with no parameter, uses the current thread id.
  
  static void registerUIThread(uint32_t threadId = 0);
  
  static void forwardQueryPalette(Window hWnd);
  static void forwardPaletteChanged(Window hWnd);
  
  static SbBool handleCtl3DMessage();
  
  static void setHandleCtl3DMessage(SbBool n);
  
  static void Ctl3dColorChange();
  
  // Note: The default error handler in SoError writes to stderr,
  // which is generally the "bit bucket" for _WIN32 apps, so we
  // setup this handler which pops up a message dialog.  --mmh
  static void errorHandlerCB(const SoError *error, void *data);
  static void errorHandlerCBMessageBox(const SoError *error, void *userData);
  
  // Access to shared offscreen renderer for UI components
  static SoOffscreenRenderer *getOffscreenRenderer();
  
  // Make sure offscreen renderer's bitmap is at least this big.
  // Returns actual current size.
  static SbVec2s &updateRendererSize(SbVec2s size);
  
  // MP
  static SbConfig * getConfig(void);
  static void setConfig(SbConfig *);
  static void setConfigFilename(char*);
  static char * getConfigFilename(void);

  static void addAccelerator(ACCEL accel);

 protected:
  static FARPROC m_procCtl3dColorChange;
  static HINSTANCE m_hCtl3d;
  static void   getExtensionEventHandler(XEvent *event, SoWidget &w, 
                                         XtEventHandler &proc, 
                                         XtPointer &clientData);
  // register mutex 
  static SbThreadMutex *registerMutex;
  
 private:
  static bool internalMainWidget;
  static SoWidget mainWidget;
  static SoWinEventHandler *eventHandler;
  static SbPList *handlerList;
  
  // flag indicates whether or not we are processing CTL3D messages
  static SbBool nHandleCtl3D;
  
  // Message hook list
  static SbPList *msgHookList;
  
  // Resource DLL
  static void loadResourceDll();
  
  // Save initial values passed into WinMain function.
  static Hinst hInstance;
  static Hinst hPrevInstance;
  static LPTSTR lpszCmdLine;
  static int nCmdShow;
  static SoDynamicLibManager::SafeLibraryHandle hResDll;
  
  // List of classes registered by SoWin
  static SbPList registeredClassList;
  
  friend class SoWinTimerManager;
  friend class SoWinEventHandler;
  
  static HWND createThreadWindow(SoWinTimerManager *pTimerManager);
  
  // SoWin contains the generic window proc for Inventor windows.
  // Among other things, it converts appropriate messages into
  // Inventor events.
  //
  // SoWin also provides a winmain function for Inventor programs
  // that only make SoWin calls, but it is not a member function.
  // It is a separate entity in the library so it is only linked
  // in when the app doesn't have its own winmain.
  static LRESULT CALLBACK WindowProc(Hwnd hwnd, UINT message,
                                     WPARAM wParam, LPARAM lParam);
  
  // Offscreen renderer for UI components to share
  // (reduces number of on-screen OpenGL contexts required).
  static SoOffscreenRenderer *m_pRenderer;
  
  static SoConsole *errorConsole;
  static SbBool s_useOldErrorHandler;

  static SbConfig *config;
  static char *configFile;

  static HACCEL m_haccel;

  static int s_initRefCount;
};


///////////////////////EXCEPTION METHODS/////////////////////////////////////
//
// #duplicated nextEvent(XtAppContext appContext, XEvent * event)
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#   include <Inventor/Win/SoWinEndStrict.h>
#endif

#endif  /* _SO_WIN_ */


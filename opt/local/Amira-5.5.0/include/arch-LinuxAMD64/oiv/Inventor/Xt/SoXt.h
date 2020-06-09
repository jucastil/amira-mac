/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nick Thompson (MMM yyyy)
** Modified by : Paul Isaacs (MMM yyyy)
** Modified by : David Mott (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/

#ifdef SOQT
#  include <Inventor/Qt/SoQt.h>
#elif defined(SOWX)
#	 include <Inventor/Wx/SoXt2SoWx.h>
#	 include <Inventor/Wx/SoWx.h>
#elif defined(_WIN32)
#  include <Inventor/Win/SoXt2SoWin.h>
#  include <Inventor/Win/SoWin.h>
#else

#ifndef _SO_XT_
#define _SO_XT_

#include <inttypes.h>
#include <Xm/Xm.h>
#include <Inventor/SbBasic.h>
#include <Inventor/SbLinear.h>
#include <Inventor/Xt/SoXtDef.h>
#include <Inventor/Xt/SoXtLocalisation.h>

#define __INVXTDLL "libInventorXt"
#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoInventorXt, __INVXTDLL)

class SbPList;
class SoXtEventHandler;
class SbConfig;


#ifndef HIDDEN_FROM_DOC
// Callback that MP viewer will ask SoXt to make.
// For internal use only!
typedef int SoMPRealizeCB( SbConfig* );
#endif //HIDDEN_FROM_DOC

/**
 * Routines for Open Inventor/Xt compatibility.
 *
 * @ingroup Xt
 *
 * @DESCRIPTION
 *   The SoXt class initializes Open Inventor for use with the Xt toolkit and Motif.
 *   SoXt::init() must be called in order for Open Inventor to work properly with Xt
 *   SoXt::finish() should be called to clean up static memory allocations.
 *
 *   SoXt::mainLoop() must be called in order for extension device events to be
 *   passed to Open Inventor render areas. The other methods are convenience
 *   functions.
 *
 *   Refer to the SoXtComponent reference pages for examples on how this class should
 *   be used when using Open Inventor Xt components.
 *
 * @SEE_ALSO
 *    SoXtComponent
 *
 *
 */

class INVENTORXT_API SoXt {

 public:
  /**
   * This is called to initialize Open Inventor and Xt, and bind Open Inventor with X
   * events handling so that Open Inventor sensors will work correctly. This returns
   * the top level shell widget. This method calls SoDB::init(),
   * SoNodeKit::init(), and SoInteraction::init() and creates an
   * initial window.
   */
  static SoWidget init(const char *appName,
                     const char *className = "Inventor");

  /**
   * This method calls SoDB::threadInit() rather than SoDB::init().
   * Otherwise it is the same as the corresponding SoXt::init() method.
   */
  static SoWidget threadInit(const char *appName,
                           const char *className = "Inventor");

  /**
   * This alternate form of init allows the application to initialize Xt. The passed
   * widget should be the top level widget returned from the Xt initialization. This
   * method will call SoDB::init(), SoNodeKit::init(), and
   * SoInteraction::init().
   */
  static void init(SoWidget topLevelWidget);

  /**
   * This method calls SoDB::threadInit() rather than SoDB::init().
   * Otherwise it is the same as the corresponding SoXt::init() method.
   */
  static void threadInit(SoWidget topLevelWidget);

  /**
   * Returns TRUE if SoXt module is currently initialized.
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
   *
   * For example:
   * @TABLE_1B
   *  @TR @B Wrong Open Inventor Ending@b
   *  @TD @B Safe Open Inventor Endings@b
   *  @TR <PRE>
   * void main() {
   *   SoWidget myW = SoXt::init("");
   *   SoXtExaminerViewer viewer(myW);
   *   ....
   *   ....
   *   SoXt::mainLoop();
   *   SoXt::finish();
   * }
   *  </PRE>
   *  @TD
   *    @TABLE_0B
   *    @TR <PRE>
   * void runApp() {
   *   SoXtExaminerViewer viewer(myW);
   *   ....
   *   ....
   *   SoXt::mainLoop();
   * }
   *
   * void main () {
   *   SoWidget myW = SoXt::init("");
   *   runApp();
   *   SoXt::finish();
   * }
   * </PRE>
   * @TD <PRE>
   * void main () {
   *   SoWidget myW = SoXt::init("");
   *   SoXtExaminerViewer* viewer
   *          = new SoXtExaminerViewer(myW);
   *   ....
   *   ....
   *   SoXt::mainLoop();
   *   delete viewer;
   *   SoXt::finish();
   *  }
   * </PRE>
   *     @TABLE_END
   * @TR
   * SoXt doesn't end properly: SoXtExaminerViewer is destroyed after the #finish() method has been called.
   * @TD
   * The SoXtExaminerViewer (that uses OpenInventor) is destroyed before calling the #finish() method.
   *     @TABLE_END
   */
  static void finish();

  /**
   * This retrieves and dispatches events (loops forever). It calls SoXt::nextEvent()
   * and SoXt::dispatchEvent() to do this.
   */
  static void mainLoop();

  /**
   * Gets the nextEvent by calling XtAppNextEvent(). The @B appContext @b can be had by
   * calling SoXt::getAppContext().
   */
  static void nextEvent(XtAppContext appContext, XEvent *event)
    { XtAppNextEvent(appContext, event); }

  /**
   * Dispatches the passed event to a handler. This returns TRUE if a handler was
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
  static Display *getDisplay();

  /**
   * Returns information based on the initial widget returned by or passed to init.
   */
  static SoWidget getTopLevelWidget();

  //
  // Convenience routines
  //

  /**
   * Convenience routine to show the passed widget.
   * This includes any children the window may have.
   */
  static void show(SoWidget widget);

  /**
   * Convenience routine to hide the passed widget.
   * This includes any children the window may have.
   */
  static void hide(SoWidget widget);

  /**
   * Convenience routine for encoding a character string as an
   * @B XmString @b. decodeString() is used for decoding an @B XmString @b back to
   * a character string.
   * (@B XmString @b is a Motif string). The application is responsible for freeing
   * up the memory pointed to by the return value. Use @B XmStringFree @b() to
   * free an @B XmString @b.
   */
  static XmString encodeString(char *s);

  /**
   * Convenience routine for decoding an @B XmString @b back to a character string.
   * encodeString() is used for encoding a character string as an
   * @B XmString @b.
   * (@B XmString @b is a Motif string). The application is responsible for freeing
   * up the memory pointed to by the return value. Use
   * @B free @b() to free a character pointer.
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

  /**
   * Convenience routine which will return the topmost window containing the given
   * widget. The widget tree is traversed up until the last widget is found using
   * @B GetParent @b.
   */
  static SoWidget getShellWidget(SoWidget w);

  /**
   * Convenience routine which brings a simple Xt error dialog box displaying the
   * given error string(s) and window title. The OK button, which destroys the
   * dialog, is the only button displayed.
   */
  static void createSimpleErrorDialog(SoWidget widget, char *dialogTitle,
                                      char *errorStr1, char *errorStr2 = NULL);

  /**
   * Convenience routine which gets visual args for the popup planes. These args can
   * then be passed in to @B XmCreatePulldownMenu @b() or @B XmCreatePopupMenu @b()
   * to create menus in the popup planes. addColormapToShell() has to be
   * called on the main popup window to set the proper color map.
   */
  static void getPopupArgs(Display *d, int scr, ArgList args, int *n);

  /**
   * Convenience routine which will register map/unmap callbacks to load and unload
   * the pulldown menu color map right before the menu is about to be posted. This
   * should be called when creating pulldown or popup menus in the overlays. This
   * will make sure that the right color map is loaded into the shell widget (to make
   * the pulldown/popup look right) and remove it when no longer needed (to make sure
   * the OpenGL overlay widget color map is correctly loaded for 8 bit machines).
   */
  static void registerColormapLoad(SoWidget widget, SoWidget shell);

  /**
   * Convenience routine to insert the given widget colormap onto the supplied
   * shell widget. This will not replace the existing installed colormaps (or list of
   * windows), but instead insert the new colormap first into the existing list using
   * @B XGetWMColormapWindows @b() and @B XSetWMColormapWindows @b().
   */
  static void addColormapToShell(SoWidget widget, SoWidget shell);

  /**
   * Convenience routine to remove the given widget colormap from the supplied
   * shell widget.
   */
  static void removeColormapFromShell(SoWidget widget, SoWidget shell);

  /**
   * Returns the MultiPipe configuration.
   */
  static SbConfig *getConfig(void);

  /**
   * Sets the MultiPipe configuration.
   */
  static void setConfig(SbConfig * config);

  /**
   * Specifies the name and path of the configuration file that MultiPipe
   * viewers will read. This method must be called before the
   * constructor of the MultiPipe viewer, otherwise it will have no
   * effect. The default configuration file name is "oivmp.cfg". If
   * the configuration file cannot be found, the MultiPipe viewer is
   * set to INSIDE mode (and behaves like a standard viewer).
   */
  static void setConfigFilename(char* fileName);

  /**
   * Returns the configuration file name.
   */
  static char * getConfigFilename(void);

 SoINTERNAL public:
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

  // This method is an acces method to label (Widgets).

  // This method is an acces method to label ( Widgets ).
  // Begin
  static SoWidget getwidget( unsigned int whatisit );
  // End

  static void setMPRealizeCB( SoMPRealizeCB *cb )
    { mpRealizeCB = cb; }

  static void canExit(SbBool ce);

  static void setEventHandler();

  static SoXtEventHandler *eventHandler;

 protected:
  static void             getExtensionEventHandler(
                                                   XEvent *event,
                                                   SoWidget &w,
                                                   XtEventHandler &proc,
                                                   XtPointer &clientData);

 private:
  static SoWidget           mainWidget;
  static bool             m_internalApp;
  static SbBool           m_canExit;

  static SbPList          *handlerList;

  // Begin
  // Widgets for localisation.
  static SoWidget label[155];

  static void localisationlabel(SoWidget parent);
  // End

  static SbConfig * config;
  static char * configFile;
  static SoMPRealizeCB *mpRealizeCB;

  // setup display in Inventor for GL extensions check
  static void setupInventorGLDisplay();
  
  static int s_initRefCount;
  static const char *s_versionString;
};

#endif  /* _SO_XT_ */

#endif // SOQT


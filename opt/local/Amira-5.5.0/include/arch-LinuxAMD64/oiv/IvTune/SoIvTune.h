/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Colas Fievet (MMM YYYY)
** Author      : Tristan Mehamli (MMM YYYY)
**=======================================================================*/
#if defined(_WIN32) && defined(_MSC_VER)
#  ifdef _WIN64
#    define PROC_ARCH processorArchitecture='amd64'
#  else
#    define PROC_ARCH processorArchitecture='x86'
#  endif
#  if (_MSC_VER == 1400 /*VC++ 8.0*/) || (_MSC_VER == 1500 /*VC++ 9.0, Qt 4.3.x built on VC++ 8.0*/)
#    ifdef _WIN64
#      pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.VC80.CRT' version='8.0.50608.0' processorArchitecture='amd64' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#    else
#      pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.VC80.CRT' version='8.0.50608.0' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#    endif
#  elif (_MSC_VER == 1500 /*VC++ 9.0*/)
#    ifdef _WIN64
#      pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.VC90.CRT' version='9.0.20404.44800' processorArchitecture='amd64' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#    else
#      pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.VC90.CRT' version='9.0.20404.44800' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b'\"")
#    endif
#  endif
#endif

#include <Inventor/sys/port.h>
#include <Inventor/SbBasic.h>
#include <Inventor/STL/map>

#if defined(_WIN32)
#  include <SoVersion.h>
#  if defined(_DEBUG)
#    define __IVTUNELIB  "IvTuneD.lib"
#    define __IVTUNEDLL  "IvTuneD.dll"
#  else
#    define __IVTUNELIB  "IvTune.lib"
#    define __IVTUNEDLL  "IvTune.dll"
#  endif
#  ifndef IvTune_EXPORTS
#    ifndef OIV_DISABLE_AUTOLINK
#      pragma comment(lib,__IVTUNELIB)
#     endif
#  endif
#else
#    define __IVTUNEDLL  "libIvTune"
#endif

#include <Inventor/SoModule.h>
SO_MODULE_HEADER(SoIvTune, __IVTUNEDLL)

#ifndef SoIvTune_included
#define SoIvTune_included

#if defined(_WIN32)
#  pragma warning(disable:4251)
#endif

#if defined(_WIN32)
class SoWinRenderArea;
#else
class SoXtRenderArea;
#endif

class DvGUIManager;
class SoQtRenderArea;
class SoOIVViewer;
class SoNode;
class QWidget;
class QStringList;
class QString;
class SoIvTuneMainFrame;
class SbViewportRegion;
class SbVec2s;
class SoIvTuneXtLoop;
class ScRenderArea;
class SoGuiRenderArea;

/**
 * @VSGEXT Opens an IvTune window
 *
 * @ingroup IvTune
 *
 * @DESCRIPTION
 *
 * IvTune is an editor and viewer for Open Inventor scene graphs. Using SoIvTune,
 * it can be used for viewing and interacting with the scene
 * graph in an Open Inventor application.
 *
 * When IvTune is started from an application, it opens a separate window.
 * This window
 * includes a Tree View which represents the scene graph, a Node Overview
 * to display an overview of a node, and a Field Editor and a Field Watch
 * to track interesting fields.
 *
 * For details of its operation, see the on-line documentation provided for
 * the pre-built IvTune viewer supplied with the Open Inventor SDK in the
 * program (Windows) or bin (Unix/Linux) directory. The IvTune viewer application
 * can be used to view Open Inventor scene graph files.
 *
 * NOTE: IvTune 8.0 is currently built using Qt 4.x and Qt3 Support libraries.
 * This implies that if your application is built with Qt 3.x, you will not be
 * able to invoke IvTune 8.0 from it.
 *
 * [OIVJAVA-WRAPPER-CLASS NO_WRAP]
 */

class IVTUNE_API SoIvTune
{

public:
#ifndef HIDDEN_FROM_DOC
  //Offline mode
  // @UNICODE_WARNING
  SoNONUNICODE SoIvTune(int argc, char **argv);

  // Unicode version of the function.
  SoIvTune( const QStringList* arguments );

  //Inline mode
  SoIvTune(int argc, char **argv, SoGuiRenderArea *viewer);

  //Inline mode
#if defined(_WIN32)
  SoIvTune(int argc, char **argv, SoWinRenderArea *viewerWint);
#elif !defined(__APPLE__)
  SoIvTune(int argc, char **argv, SoXtRenderArea *viewerXt);
#endif
  SoIvTune(int argc, char **argv, SoQtRenderArea *viewerQt);

  ~SoIvTune();
#endif

  /**
   * Opens an IvTune window displaying the specified scene graph.
   * The argc and argv parameters are not normally used.
   * if createViewer is true then a viewer is created to do the rendering
   * else only the treeview part will be shown.
   */
  static void setInstance(int argc, char ** argv, SoNode * root, bool createViewer = false);

  /**
   * Opens an IvTune window displaying the scene graph from the specified
   * viewer. The argc and argv parameters are not normally used.
   * When called from non Qt application, the function enters a Qt process events loop
   * ( QCoreApplication::exec() ). Use launch() and processEvents() instead.
   *
   * You should pass the pointer returned by getGuiRenderArea() from your viewer
   * object (which can be derived from SoQtRenderArea, SoXtRenderArea,
   * SoWinRenderArea or SoWxRenderArea).
   *
   * For example:
   *  <PRE>
   *  SoIvTune::setInstance ( 0, NULL, pViewer->getGuiRenderArea());
   * </PRE>
   * NOTE: There is currently no way to programmatically close an IvTune
   * window. It can be closed manually, or it will be closed when the
   * program exits.
   */
  static void setInstance(int argc, char **argv, SoGuiRenderArea* viewer);

#ifdef _WIN32
  /**
   * @deprecated No longer used. Use setInstance with SoGuiRenderarea parameter.
   * Opens an IvTune window displaying the scene graph from the specified
   * viewer. The argc and argv parameters are not normally used.
   *
   * You should pass a non-NULL value for either the viewerXt or viewerQt
   * parameter. If you're using an SoWin or SoXt viewer, use the viewerXt
   * parameter. If you're using an SoQt viewer, use the viewerQt parameter.
   *
   * For example:
   *  <PRE>
   *  SoIvTune::setInstance ( 0, NULL, pViewer, NULL );
   * </PRE>
   * NOTE: There is currently no way to programmatically close an IvTune
   * window. It can be closed manually, or it will be closed when the
   * program exits.
   * @DEPRECATED_SINCE_OIV 8.0
   */
  SoDEPRECATED static void setInstance(int argc, char **argv, SoWinRenderArea *viewerWin, SoQtRenderArea *viewerQt);
#elif defined(__APPLE__)
  /**
   * @deprecated No longer used. Use setInstance with SoGuiRenderarea parameter.
   * Opens an IvTune window displaying the scene graph from the specified
   * viewer. The argc and argv parameters are not normally used.
   *
   * You should pass a non-NULL value for viewerQt parameter.
   *
   * For example:
   *  <PRE>
   *  SoIvTune::setInstance ( 0, NULL, pViewer );
   * </PRE>
   * NOTE: There is currently no way to programmatically close an IvTune
   * window. It can be closed manually, or it will be closed when the
   * program exits.
   */

  SoDEPRECATED static void setInstance(int argc, char **argv, SoQtRenderArea *viewerQt);
#else
  /**
   * @deprecated No longer used. Use setInstance with SoGuiRenderarea parameter.
   * Opens an IvTune window displaying the scene graph from the specified
   * viewer. The argc and argv parameters are not normally used.
   *
   * You should pass a non-NULL value for either the viewerXt or viewerQt
   * parameter. If you're using an SoWin or SoXt viewer, use the viewerXt
   * parameter. If you're using an SoQt viewer, use the viewerQt parameter.
   *
   * For example:
   *  <PRE>
   *  SoIvTune::setInstance ( 0, NULL, pViewer, NULL );
   * </PRE>
   * NOTE: There is currently no way to programmatically close an IvTune
   * window. It can be closed manually, or it will be closed when the
   * program exits.
   */

  SoDEPRECATED static void setInstance(int argc, char **argv, SoXtRenderArea *viewerXt, SoQtRenderArea *viewerQt);
#endif

   /**
   * Opens an IvTune window displaying the scene graph from the specified
   * viewer, and returns immediatly. The argc and argv parameters are not normally used.
   * After launching IvTune, a non Qt application should call the processEvents function
   * periodically so that Qt events will be treated.
   *
   * You should pass the pointer returned by getGuiRenderArea() from your viewer
   * object (which can be derived from SoQtRenderArea, SoXtRenderArea,
   * SoWinRenderArea or SoWxRenderArea).
   *
   * For example:
   *  <PRE>
   *  SoIvTune::setInstance ( 0, NULL, pViewer->getGuiRenderArea());
   * </PRE>
   * NOTE: There is currently no way to programmatically close an IvTune
   * window. It can be closed manually, or it will be closed when the
   * program exits.
   */
  static void launch(int argc, char **argv, SoGuiRenderArea* viewer);

  /**
   * Returns TRUE if an IvTune window is currently open.
   */
  static SbBool isInstance();

  /**
   * Returns the IvTuneMainFrame instance.
   */
  static SoIvTuneMainFrame* getMainFrame();


  /**
  * Process the Qt events ( calling QCoreApplication::processEvents() ).
  *
  * A non Qt application should call this function periodically so that
  * IvTune Qt events should be treated.
  */
  static void processEvents();

#ifndef HIDDEN_FROM_DOC

  static void setPickAction( const SbViewportRegion &region, SbVec2s mouseCoord );

  QWidget * getWidget();
  void setScene(SoNode *);
  SoOIVViewer * getViewer();

  typedef std::map< ScRenderArea*, SoIvTune*> SoIvTuneOiruMap;
  typedef SoIvTuneOiruMap::value_type value_type;
  static SoIvTuneOiruMap ivTuneOiruMap;

  static void setInstance(ScRenderArea*);
  static void setScene(SoNode*, ScRenderArea*);
#endif

private:
  void init(int argc, char **argv, SoOIVViewer *viewer);

  void init( const QStringList* arguments, SoOIVViewer *viewer);

  void finish();

  void setFile( const QString* file );
  void initScene();

  static SoIvTuneMainFrame *m_mainFrame;
  //used to know if when we close ivTune we must kill the QApplication or not
  static SoOIVViewer *m_viewer;
  static bool m_alive;
  static bool m_noQApp;
  static bool m_didModulesinit;
  DvGUIManager* m_guiManager;
};

extern "C" IVTUNE_API SbBool _isInstance();
extern "C" IVTUNE_API void _setPickAction( const SbViewportRegion &region, SbVec2s mouseCoord );
extern "C" IVTUNE_API void _setInstance(int argc, char **argv, SoGuiRenderArea* viewer);
extern "C" IVTUNE_API void _launch(int argc, char **argv, SoGuiRenderArea* viewer);
extern "C" IVTUNE_API void _setScInstance(ScRenderArea*);
extern "C" IVTUNE_API void _setScene(SoNode*, ScRenderArea*);
extern "C" IVTUNE_API void _processEvents();

#endif //SoIvTune_included


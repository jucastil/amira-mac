/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Aug 2010)
**=======================================================================*/
#ifndef DV_GUI_MANAGER_H
#define DV_GUI_MANAGER_H

#include <IvTune/plugins/DvLibName.h>

#include <Inventor/SbString.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/string>

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class DvGUIManagement;
class DvIvtPlugins;
class DvIvtPluginsManagerDialog;

/** 
 * @VSGEXT Class that manages the loading of IvTune editors and GUI plug-ins.
 *
 * @ingroup DemoViewer
 *
 * @DESCRIPTION
 *
 * This class loads automatically the editors and GUI elements 
 * (i.e. toolbars and menus) plug-ins.
 *
 * Note: all the plugins must be placed in the same specified folder.
 *       The plug-ins are unloaded when DvGUIManager is deleted.
 *
 */

/** Plugin look-up function pointer. */
typedef WINGDIAPI DvIvtPlugins* (*DV_pluginStartPtr_t)(DvGUIManagement*);
typedef WINGDIAPI void (*DV_pluginFinishPtr_t)();

class DEMOVIEWER_API DvGUIManager
{
public:
  /**
   * Constructor.
   */
  DvGUIManager( DvGUIManagement* guiToManage );

  /**
   * Destructor.
   */
  ~DvGUIManager();

  /**
   * Returns the plug-ins path.
   */
  SbString getPluginsPath() const;

  /**
   * Loads the specified plug-in and returns a pointer to it.
   *
   * @param path the path to the plug-in to load.
   */
  DvIvtPlugins* loadPlugin( const SbString& path );

  /**
   * Unloads the specified plug-in.
   *
   * @param path the path to the plug-in to unload.
   */
  void unloadPlugin( const SbString& path );

private:
  /** Looks for the plug-ins and loads them. */
  void loadDvPlugins();

  /** Builds the plug-ins paths list. */
  void buildFilesPaths( const SbString& startPath );

  /** Provides access to GUI elements. */
  DvGUIManagement* m_guiToManage;

  /** Dialog for the plug-in management. */
  DvIvtPluginsManagerDialog* m_plgDialog;

  /** Plug-ins path. */
  SbString m_pluginsPath;

  /** Vectors of plug-ins paths. */
  std::vector<std::string> m_filesPaths;

  /** Vectors of plug-ins instances. */
  std::vector<DvIvtPlugins*> m_pluginsInstances;
};

#endif // DV_GUI_MANAGER_H
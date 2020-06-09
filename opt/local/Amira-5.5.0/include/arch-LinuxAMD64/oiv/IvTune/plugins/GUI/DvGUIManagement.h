/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Aug 2010)
**=======================================================================*/
#ifndef DV_GUI_MANAGEMENT_H
#define DV_GUI_MANAGEMENT_H

#include <QtGui/QMainWindow>

#include <IvTune/plugins/DvLibName.h>

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class QMenu;
class QToolBar;
class QTreeWidget;

class SoGuiAlgoViewers;
class SoNode;
class SoQtFullViewer;

/**
 * @VSGEXT Abstract class to manage IvTune GUI
 *
 * @ingroup DemoViewer
 *
 * @DESCRIPTION
 *
 * This abstract class provides getters to access the different GUI 
 * elements of IvTune. Thus it is possible to modify or extend them.
 *
 * @SEE_ALSO
 *    DvGUITreeviewManagement,
 *    DvGUITreeviewItemManagement,
 *
 */

class DEMOVIEWER_API DvGUIManagement : public QMainWindow
{
public:
  // Menus
  /**
   * Adds the menu before the help (?) menu of IvTune.
   */
  virtual void addMenu( QMenu* newMenu ) = 0;

  /**
   * Returns the bookmark menu.
   */
  virtual QMenu* getBookmarkMenu() const = 0;

  /**
   * Returns the edit menu.
   */
  virtual QMenu* getEditMenu() const = 0;

  /**
   * Returns the file menu.
   */
  virtual QMenu* getFileMenu() const = 0;

  /**
   * Returns the filter menu.
   */
  virtual QMenu* getFilterMenu() const = 0;

  /**
   * Returns the help menu.
   */
  virtual QMenu* getHelpMenu() const = 0;

  /**
   * Returns the treeview menu.
   */
  virtual QMenu* getTreeviewMenu() const = 0;

  /**
   * Returns the treeview contextual menu.
   */
  virtual QMenu* getTreeviewContextMenu() const = 0;

  /**
   * Returns the view menu.
   */
  virtual QMenu* getViewMenu() const = 0;

  // Toolbars
  /**
   * Returns the bookmark toolbar.
   */
  virtual QToolBar* getBookmarkToolbar() const = 0;

  /**
   * Returns the edit toolbar.
   */
  virtual QToolBar* getEditToolbar() const = 0;

  /**
   * Returns the bookmark toolbar.
   */
  virtual QToolBar* getFileToolbar() const = 0;

  /**
   * Returns the filter toolbar.
   */
  virtual QToolBar* getFilterToolbar() const = 0;

  /**
   * Returns the search toolbar.
   */
  virtual QToolBar* getSearchToolbar() const = 0;

  /**
   * Returns the treview.
   */
  virtual QTreeWidget* getTreeview() const = 0;

  /**
   * Returns the viewer.
   */
  virtual SoQtFullViewer* getViewer() const = 0;

  /**
   * Returns the viewer's algorithms instance.
   */
  virtual SoGuiAlgoViewers* getGuiAlgoViewers() const = 0;

  /**
   * Returns IvTune's scenegraph.
   */
  virtual SoNode* getIvTuneSceneGraph() const = 0;

  /**
   * Destructor
   */
  virtual ~DvGUIManagement() {};

protected:
  /**
   * Constructor
   */
  DvGUIManagement( QWidget* parent, const char* name ) : QMainWindow( parent ) 
  { setObjectName( name ); };

  // Menus
  /**
   * Bookmark menu
   */
  QMenu* m_bookmarkMenu;

  /**
   * Edit menu
   */
  QMenu* m_editMenu;

  /**
   * File menu
   */
  QMenu* m_fileMenu;

  /**
   * Filter menu
   */
  QMenu* m_filterMenu;

  /**
   * Help menu
   */
  QMenu* m_helpMenu;

  /**
   * Treeview menu
   */
  QMenu* m_treeviewMenu;

  /**
   * View menu
   */
  QMenu* m_viewMenu;

  // Toolbars
  /**
   * Bookmark toolbar
   */
  QToolBar* m_bookmarkToolbar;

  /**
   * Edit toolbar
   */
  QToolBar* m_editToolbar;

  /**
   * File toolbar
   */
  QToolBar* m_fileToolbar;

  /**
   * Filter toolbar
   */
  QToolBar* m_filterToolbar;

  /**
   * Search toolbar
   */
  QToolBar* m_searchToolbar;

  /**
   * Treeview
   */
  QTreeWidget* m_treeview;

  /**
   * Viewer
   */
  SoQtFullViewer* m_viewer;
};

#endif // DV_GUI_MANAGEMENT_H

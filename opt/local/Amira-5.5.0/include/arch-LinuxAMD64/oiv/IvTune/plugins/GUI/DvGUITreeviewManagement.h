/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Aug 2010)
**=======================================================================*/
#ifndef DV_GUI_TREEVIEW_MANAGEMENT_H
#define DV_GUI_TREEVIEW_MANAGEMENT_H

#include <QtGui/QTreeWidget>

#include <IvTune/plugins/DvLibName.h>

#include <Inventor/SbBase.h>

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class QWidget;

/**
 * @VSGEXT Abstract class to manage the IvTune treeview
 *
 * @ingroup DemoViewer
 *
 * @DESCRIPTION
 *
 * This abstract class provides methods to interact with the treeview.
 *
 * @SEE_ALSO
 *    DvGUIManagement,
 *    DvGUITreeviewItemManagement
 *
 */

class DEMOVIEWER_API DvGUITreeviewManagement : public QTreeWidget
{
  Q_OBJECT

public:
  /**
   * Destructor
   */
  virtual ~DvGUITreeviewManagement() {};

signals:
  /**
   * Emitted when an item has been right-clicked.
   */
  void rightClicked( QTreeWidgetItem* item );

  /**
   * Emitted when a new scene graph is loaded.
   */
  void newSceneGraph();

protected:
  /**
   * Constructor
   */
  DvGUITreeviewManagement( QWidget* parent ) : QTreeWidget( parent ) {};
};

#endif // DV_GUI_TREEVIEW_MANAGEMENT_H

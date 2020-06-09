/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : T.MEHAMLI (Aug 2010)
**=======================================================================*/
#ifndef DV_GUI_TREEVIEW_ITEM_MANAGEMENT_H
#define DV_GUI_TREEVIEW_ITEM_MANAGEMENT_H

#include <QtGui/QTreeWidgetItem>

#include <IvTune/plugins/DvLibName.h>

#include <Inventor/SbBase.h>
#include <Inventor/SbString.h>

#ifdef _WIN32
# if !defined(DemoViewerAPI_EXPORTS)
#  ifndef OIV_DISABLE_AUTOLINK
#   pragma comment(lib,__DEMOVLIB)
#  endif
# endif
#endif //win

class SoBaseKit;
class SoNode;
class QTreeWidget;

/** 
 * @VSGEXT Abstract class to manage IvTune treeview items
 *
 * @ingroup DemoViewer
 *
 * @DESCRIPTION
 *
 * This abstract class provides methods to interact with treeview items.
 *
 * @SEE_ALSO
 *    DvGUIManagement,
 *    DvGUITreeviewManagement
 *
 */

class DEMOVIEWER_API DvGUITreeviewItemManagement : public QTreeWidgetItem
{
public:
  /**
   * Destructor
   */
  virtual ~DvGUITreeviewItemManagement() {};

  /**
   * Return the node represented by this item.
   */
  virtual SoNode* getNode() const = 0;

  /**
   * Return parent node or 0 if there isn't.
   */
  virtual SoNode* getParentNode() = 0;

  /**
   * Return true if the node is part of a subtree whose root is a basekit.
   */
  virtual bool fromBaseKit() const = 0;

  /** 
   * Return True if node is a part of a catalog.
   */
  virtual bool baseKitPart() const = 0;

  /**
   * If node is not a part from a catalog, returns -1. Else returns part number.
   */
  virtual int partNumber() const = 0;

  /**
   * If node is not a part from a catalog, returns "".
   * Else, returns the parent name of the specified part. 
   */
  virtual const SbName getParentPartName() const = 0;

  /**
   * If node is not a part from a catalog, returns "".
   */
  virtual SbName partName() const = 0;

  /**
   * Returns TRUE if the node is a public part, FALSE otherwise.
   */
  virtual bool isPartPublic() const = 0;

  /** 
   * Returns nodekit parent node or 0 if there isn't.
   */
  virtual SoBaseKit* getBaseKit() const = 0;

protected:
  /**
   * Constructors
   */
  DvGUITreeviewItemManagement( QTreeWidgetItem* parent, QTreeWidgetItem* preceding ) : QTreeWidgetItem( parent, preceding ) {};
  DvGUITreeviewItemManagement( QTreeWidget* parent, QTreeWidgetItem* preceding ) : QTreeWidgetItem( parent, preceding ) {};
};

#endif // DV_GUI_TREEVIEW_ITEM_MANAGEMENT_H

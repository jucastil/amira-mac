/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup hxtreeview hxtreeview
/// @{
#ifndef QX_TREE_VIEW_H
#define QX_TREE_VIEW_H

#include <QTreeWidget>
#include <qpixmap.h>

#include <hxtreeview/hxtreeviewAPI.h>
#include <hxtreeview/LibHxTreeView.h>

class HxObject;
class HxTreeViewGUI;
class HxConnection;
class QxTreeViewItem;
class QDragObject;

class HXTREEVIEW_API QxTreeView : public QTreeWidget
{
    Q_OBJECT


public:

    /// Constructor.
    QxTreeView(QWidget* parent=0);

    /// Destructor.
    virtual ~QxTreeView();

    /// To set the current object.
    void setCurrentObject(HxObject * object);

    /// To get the current object.
    inline HxObject * getCurrentObject() const {return m_currentObject;};

    /// To find an item in the tree representation.
    QxTreeViewItem * findTreeViewItem(const QString & itemName) const;

    /// To add an item into the tree.
    QxTreeViewItem * addItem(QxTreeViewItem * parentItem, const QString & itemName);

    /// To move an item as child of another.
    void moveItemAsChildOf(QxTreeViewItem * itemToMove, QxTreeViewItem * newParentItem);

    /// To know if a connection can be made between two objects.
    bool connectionCanBeMade(QxTreeViewItem * owner, QxTreeViewItem * source);
    bool connectionCanBeMade(HxObject * objectToConnect, HxObject * source);

    /// To update the work area.
    void updateWorkArea();

    /// To expand or collapse an item (recursively or not).
    void expandOrCollapseItem(QTreeWidgetItem * item, bool expand = true, bool allChild = false);

    /// To (re-)initialize the tree view attributes.
    void init(bool clearAll = false);

    /// To resize the columns;
    void resizeColumns() const;
public slots:

    /// To delete the selected objects.
    void deleteSelectedObjects();

    /// To create a directory in the tree view.
    void createDirectory();
    
    /**
     * To update the displayed port value of an object.
     */
    void updatePortValue();

    /** 
     * Called when the pool tab index has changed.
     */
    void poolTabChanged(int newTab);     

    /**
     * Called when a network is loading.
     */
    void networkIsLoading(bool loadInProgress);

    /** 
     * Called when terminating the application.
     */
    void aboutToQuit();

	void onItemChanged( QTreeWidgetItem * item, int column );
	void onItemSelectionChanged();
	void onItemCollapsed(QTreeWidgetItem * item);
	void onItemExpanded( QTreeWidgetItem * item);

protected:

    /// To remove the items of the tree view except the default and the basic ones.
    void clearTreeView();

    /// To add an object item into the tree.
    QxTreeViewItem * addObjectItem(QxTreeViewItem * parentItem, HxObject * object);

    /// Qt events.
    virtual void keyPressEvent(QKeyEvent* e);
    
    /// Displays the popup menu associated to an item.
	void contextMenuEvent(QContextMenuEvent * event);

    virtual bool dropMimeData ( QTreeWidgetItem * parent, int index, const QMimeData * data, Qt::DropAction action );

	virtual void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	virtual void paintEvent ( QPaintEvent * event );

    QItemSelectionModel::SelectionFlags selectionCommand ( const QModelIndex & index, const QEvent * event = 0 ) const;
private:
	/// The object associated to the current item.
    HxObject * m_currentObject;

    int   numVisibleRows;
    QRect lastRowRect;

    int mIsEditing;

	friend class QxTreeViewItemDelegate;
};

#endif

/// @}

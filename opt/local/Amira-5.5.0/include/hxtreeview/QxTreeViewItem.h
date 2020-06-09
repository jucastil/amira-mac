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
#ifndef QX_TREE_VIEW_ITEM_H
#define QX_TREE_VIEW_ITEM_H

#include <QTreeWidgetItem>

#include <hxtreeview/hxtreeviewAPI.h>
#include <hxtreeview/LibHxTreeView.h>

class HxEditor;
class QxTreeViewShortcutItem;
class HxObject;

class HXTREEVIEW_API QxTreeViewItem : public QTreeWidgetItem
{

public:

    //////////////////////////////////////////////////////////////////////////
    /// Constructors and destructor.
    //////////////////////////////////////////////////////////////////////////

    /// Constructors.
	QxTreeViewItem( QTreeWidget * parent, HxObject * object); 
	QxTreeViewItem( QTreeWidgetItem * parent, HxObject * object);

    /// Destructor is virtual.
    virtual ~QxTreeViewItem();

	virtual QVariant data ( int column, int role ) const;

    //////////////////////////////////////////////////////////////////////////
    /// Attributes management.
    //////////////////////////////////////////////////////////////////////////

    /// To get the matching pool object.
    inline HxObject * getPoolObject() const {return m_poolObject;};

    /// To set the matching pool object.
    void setPoolObject(HxObject* object);

    /// To get the visibility in a viewer.
    bool getVisibility(int viewerId) const;

    /// To set the visibility in a viewer.
    void setVisibility(int viewerId, bool visible);


    //////////////////////////////////////////////////////////////////////////
    /// Item GUI management (icons, name...).
    //////////////////////////////////////////////////////////////////////////

    /// To initialize the item.
    virtual void initialize();

    virtual void updateShortcuts();

    /// To get the displayed name.
    inline virtual QString getName() const {return text(ITEM_NAME_COLUMN);};

    /// To set the displayed name.
    virtual void setName(const QString & newName);

    /// To set the displayed port value.
    void setDisplayedPortValue(float value);

    /// To hide the displayed port value.
    void hideDisplayedPortValue();

    /// To update the visibility in the viewers.
    void updateVisibility();

    /** 
     * To update the colormap icon.
     */
    void updateColormapIcon();

    /** 
     * To update the editor icon.
     */
    void updateEditorIcon(HxEditor* editor);

    /** 
     * To fix the object icon.
     */
    virtual void fixObjectIcon();

    
    /// Called when the item is expanded or collapsed.
    virtual void setOpen(bool o);

    //////////////////////////////////////////////////////////////////////////
    /// Qt inherited methods.
    //////////////////////////////////////////////////////////////////////////
	virtual void setData ( int column, int role, const QVariant & value );
 
    void addShortcut(QxTreeViewShortcutItem*);
    void removeShortcut(QxTreeViewShortcutItem*);
protected:

    //////////////////////////////////////////////////////////////////////////
    /// Protected methods.
    //////////////////////////////////////////////////////////////////////////

    /** 
     * To fix the object type icon.
     */
    void fixObjectTypeIcon();
private:
	//////////////////////////////////////////////////////////////////////////
    /// Attributes.
    //////////////////////////////////////////////////////////////////////////
    /// The associated shortcut item.
    QList<QxTreeViewShortcutItem*> m_associatedShortcutItem;

	/// The matching pool object.
    HxObject * m_poolObject;

    /// Shortcut recursion guard
    bool shortcutInUpdate;

	/// The visibilities of the item in the viewers.
    QVector<bool> m_visibilities;
};

#endif

/// @}

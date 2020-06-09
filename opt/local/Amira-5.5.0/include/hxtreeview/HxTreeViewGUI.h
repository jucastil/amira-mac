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
#ifndef HX_TREE_VIEW_GUI_H
#define HX_TREE_VIEW_GUI_H

#include <hxtreeview/hxtreeviewAPI.h>
#include <hxtreeview/LibHxTreeView.h>
#include <hxcore/HxObjectPoolListener.h>
#include <mclib/McDArray.h>
#include <mclib/McHashTable.h>

class QToolButton;
class HxObject;
class QxTreeView;
class QxTreeViewItem;
class QSplitter;
class QFrame;
class QColor;
class QLabel;
class QVBoxLayout;
class HxTViewInfo;
class HxCompModule;
class HxPreferences;
class QxTreeViewGUINotifier;

class HXTREEVIEW_API HxTreeViewGUI : public HxObjectPoolListener
{

    Q_OBJECT

public:

    /// Constructor.
    HxTreeViewGUI();

    /// Destructor.
    virtual ~HxTreeViewGUI();

    /// To get the gui container.
    inline QxTreeView * getGUIContainer() const {return m_guiContainer;};

    /// To know if the auto update is enabled.
    inline bool updateIsEnabled() const {return m_updateEnabled;};

    /// To know if the tree view is in interaction mode or not.
    bool inInteractionMode() const;

    /// To get a default directory name.
    McString getDefaultDirectoryName(int index) const;

    /// To build a tree representation from a graph one.
    void buildTreeView(bool clearAll = false);

    /// To update the tree representation.
    void updateTreeView(bool resizeCol = false);

    /// To update the position of an object in the tree view.
    void updateObjectPosition(QxTreeViewItem * item);

    /// To find an item in the tree representation.
    QxTreeViewItem * findTreeViewItem(const char * itemName) const;

    /// Inits the container and erases its contents.
    void initContainer(bool clearAll = false) const;

    /// Enables or not the update of the tree when objects are created, renamed or deleted.
    inline void enableAutoUpdate(bool enabled = true) {m_updateEnabled = enabled;};

    /// To update the value of the accessible port of an object.
    void updateAccessiblePortValue(QxTreeViewItem * item) const;

    /// To update the visibility of an object.
    void updateObjectVisibility(QxTreeViewItem * item);

    /// To update the visibility of all objects.
    void updateAllObjectsVisibilities();

    /// To show the colormap menu.
    void showColormapMenu(HxObject * object, int x, int y) const;

    /// To show the colormap editor.
    void showColormapEditor(HxObject * object) const;

    /// To set the focus on the tree view.
    void setFocus() const;

    /// To know if an object is a tree directory.
    int isTreeDirectory(HxObject* object) const;

    /// To select/deselect an item.
    void selectItem(HxObject * object, bool select = true);

    /// To get the directory where an object must be stored.
    HxObject * getContainerDirectory(HxObject * obj) const;

    /// To resize the columns;
    void resizeColumns() const;

    /// To show/hide info in the tree view.
    void showInfo(HxPort * port, bool show = true) const;

    /// Returns pointer to global instance.
    static HxTreeViewGUI * getGlobalInstance(bool create = false);

    /// Interface to Tcl scripting language.
    static int staticParse(ClientData data, Tcl_Interp* t, int argc, char **argv);

    /// To manage the matching items table.
    void setMatchingItem(HxObject * object, QxTreeViewItem * item);
    QxTreeViewItem * getMatchingItem(HxObject * object);

    /// To rename an item.
    void startRenameItem(QxTreeViewItem * item) const;

    /**
     * Called when the pool view changed.
     */
    void poolViewChanged(int poolView);

    /**
     * Called when the pool tab changed.
     */
    void poolTabChanged(int tab);
  
    /**
     * Called when a network is loading.
     */
    void networkIsLoading(bool loadInProgress);

    /// internal.
    void checkRemoteMode();

    typedef enum {DATA_DIR_NAME = 0, DISPLAY_DIR_NAME = 1, COMPUTE_DIR_NAME = 2, ANIM_DEMO_DIR_NAME = 3, COLORMAPS_DIR_NAME = 4, SETTINGS_DIR_NAME = 5} DefaultDirectoryNameIndex;

    /// To know if a directory is a default one.
    bool isADefaultDirectory(QxTreeViewItem * item) const;
    bool isADefaultDirectory(const char * itemName) const;

    /**
     * To allow/inhibit the creation of HxDataDirectory objects (used by TimeSeries).
     */
    void enableDataDirCreation(bool enabled = true);

    /** 
     * To get the tree view splitter.
     */
    const QWidget* getTreeViewSplitter() const;

    /** 
     * Called when terminating the application.
     */
    void aboutToQuit();

    /** 
     * To manage the m_oldBehavior flag.
     */
    bool hasExtendedBehavior() const { return m_extendedBehavior; }
    void setExtendedBehavior(bool extendedBehaviour);

    /** 
     * To be able to change a tree view accessible port.
     */
    void treeViewAccessiblePortChanged(HxPort* oldAccessiblePort, HxPort* newAccessiblePort);

    /**
     * Called to update an item (port value, colormap icon, editor icon...).
     */
    void updateObjectItem(QxTreeViewItem* item);

    

protected:

    /// To associate items to objects.
    McHashTable<HxObject*, QxTreeViewItem*> m_matchingItems;

    /// The informations about the current tree view.
    HxTViewInfo * m_currentTViewInfos;

    /// The GUI container.
    QxTreeView * m_guiContainer;

    /// To know if the first update has been made.
    bool m_firstUpdateMade;

    /// To check the update of the tree.
    bool m_updateEnabled;

    /// To inhibit the interaction.
    int m_interactionInhibit;

    QToolButton *m_toolExplorer;

    /**
     * To inhibit the building of the tree view.
     */
    int m_treeViewBuildingInhibit;

    /// The list of objects which position must be updated in the tree view when their parent is added to the pool.
    McDArray<HxObject*> m_objectsToUpdate;

    /// The objects which item must be deleted in the tree view.
    McDArray<QxTreeViewItem*> m_itemsToDelete;

    /// The default directories variables.
    McDArray<McString> m_defaultDirectoriesNames;
    McDArray<QxTreeViewItem*> m_defaultDirectoriesItems;

    /// To know the tree basic directories names.
    McDArray<McString> m_basicDirectoriesNames;

    /**
     * To allow/inhibit the creation of HxDataDirectory objects (used by TimeSeries).
     */
    bool m_dataDirCreationEnabled;

    /// Qt variables.
    QSplitter * wTViewSplitter;
    QWidget * wTabPage;
    QFrame * wTViewFrame;
    QVBoxLayout * wTViewLayout;
    QLabel * wNetworkIsLoadingWarning;

    /// Find the parent object under which an object must be displayed.
    HxObject * getTheParentObject(HxObject * object);

    /// To create the data directory associated to a data.
    void createAssociatedDataDirectory(HxObject * object);

    /// To display an object in the tree.
    void displayObject(HxObject * object);

    /// To add an item into the tree.
    QxTreeViewItem * addItem(QxTreeViewItem * parentItem, const char * itemName) const;

    /// To move an item as child of another.
    void moveItemAsChildOf(QxTreeViewItem * itemToMove, QxTreeViewItem * newParentItem) const;

    /// To add the basic directories to the list.
    void addBasicDirectoriesNames();

    /// Updates the tree view when a connection changed.
    void connectionChanged(HxConnection *);

    /// Inherited from HxObjectPoolListener.
    void objectAdded(HxObject *);
    void objectRemoved(HxObject *);
    void objectRenamed(HxObject *, const char *);
    void objectConnected(HxConnection *, HxObject *);
    void objectDisconnected(HxConnection *, bool, HxObject*);
    void objectSelected(HxObject* object);
    void objectDeselected(HxObject* object);
    void objectReplaced(HxObject* oldObject, HxObject* newObject);

    /**
     * To initialize the tree view.
     */
    void init();

    /**
     * To create the GUI.
     */
    void createTreeViewGUI();

    /**
     * To set the current template for the tree view.
     */
    void setCurrentTemplate();

    /**
     * To register the default directories.
     */
    void registerDefaultDirectories();

    /** 
     * The current pool view.
     */
    int m_currentPoolView;

  public slots:
    /**
     *  To be notified that preferences changed.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

  protected:
    /** 
     * To know if we use the old or the new behavior of the tree view.
     * With the old behavior, modules are displayed under their first connected object (if any).
     * With the new behavior, modules are always displayed under their default category.
     */
    bool m_extendedBehavior;


private:

    /// Instance.
    static HxTreeViewGUI * m_theInstance;
};

/// Global instance of the tree view
#define theTreeView HxTreeViewGUI::getGlobalInstance()


// ------------------------------ INLINE methods. ------------------------------
inline void
HxTreeViewGUI::enableDataDirCreation(bool enabled)
{
    m_dataDirCreationEnabled = enabled;
}

inline const QWidget*
HxTreeViewGUI::getTreeViewSplitter() const
{
  return (const QWidget*) wTViewSplitter;
}


#endif

/// @}

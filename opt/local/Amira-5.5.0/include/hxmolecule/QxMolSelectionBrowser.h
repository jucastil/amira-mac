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

/// @addtogroup hxmolecule hxmolecule
/// @{
#ifndef QX_SELECTION_DIALOG_H
#define QX_SELECTION_DIALOG_H

#include <hxmolecule/ui_QxMolSelectionBrowser.h>

#include <mclib/McList.h>
#include <mclib/McList2.h>
#include <mclib/McBitfield.h>
#include <mclib/McDArray.h>

#include <hxcore/HxColorEditor.h>

#include <molecule/MtGroupRef.h>

#include "HxMoleculeWinDLLApi.h"
#include "HxMolecule.h"

class Q3PopupMenu;
class Q3ListView;
class Q3ListViewItem;
class QxSelectionListView;
class QxSelectionListViewItem;
class QxHistoryLineEdit;
class HxMolecule;
class MolFilter;
class MolColoring;

/** This class implements a Qt window to easily explore the topology
    of a molecule and to highlight atoms as well as to select and
    deselect atoms in various molecule viewing modules. */

class HXMOLECULE_API QxMolSelectionBrowser : public QMainWindow, public Ui::QxMolSelectionBrowserBase
{
    Q_OBJECT
    
protected:
    /// Bitfield in which all highlighted atoms are stored.
    McBitfield highlighted;

protected:
    
    // Menu bar plus menus contained in it.
    Q3PopupMenu  * masterLevelMenu; 
    Q3PopupMenu  * infoMenu;
    Q3PopupMenu  * optionsMenu;
    Q3PopupMenu  * modulesMenu;
    Q3PopupMenu  * highlightMenu;
    Q3PopupMenu  * helpMenu;

    // Popup menus that are used for all modules (viewers).
    Q3PopupMenu  * modulesPopup;
    Q3PopupMenu  * restrictToPopup;
    Q3PopupMenu  * combineWithPopup;
    Q3PopupMenu  * colorPopup;

    // Enumeration for pictures of tick boxes.
    enum Marking {
        MARKED, 
        HALF_MARKED, 
        UNMARKED, 
        BACKBONE, 
        HALF_BACKBONE
    };

    HxMolecule  * hxmol;
    
    // several maps
    McDArray<int> infoToColMap;   // maps info index to column in list view
    McDArray<int> colToInfoMap;   // opposite of the above map
    McDArray<int> moduleToColMap; // maps module index to column
    McDArray<int> colToModuleMap; // opposite of the above map
    
    /* @c colElems is an array of levels, each level containing an
       array of all its groups; all groups contained in one group of
       the inner array are stored in the list */
    McDArray<McDArray<McList2<MtGroupRef > > > colElems; 
    /* @c selInfo is an array of levels, each level containing a
       bitfield in which all groups that need to be highlighted are
       set; this auxiliary array of bitfields is used when
       highlighting is done by clicking in an info column */
    McDArray<McBitfield > selInfo; 

    int  curMasterLevel;       // current master level
    int  nInfoColumns;         // current number of info columns
    int  curPopupColumn;       // current popup column in listview
    bool callBackHandled;      /* used to check whether further actions 
                                  are necessary */
    int  nAdditionalInfoItems; /* how many items are there before the
                                  level info items start - currently
                                  there is type and a separator */
    bool moduleOnOff;          // add or remove ticks for modules
    int  nLevels;              // number of levels in topo    
    bool showColor;

public:
    /// Constructor.
    QxMolSelectionBrowser(HxMolecule * mol, QWidget * parent=0, 
                          const char* name = 0, Qt::WFlags fl = 0);
    /// Destructor.
    ~QxMolSelectionBrowser();

    /// Return pointer to molecule.
    HxMolecule * getMolecule() { return hxmol; }
    /// Initialize list view used for displaying all groups.
    void initListView();
    /// Add filter owned by viewing module.
    void addFilter(int id);
    /// Remove filter.
    void removeFilter(int id);
    /// Add molColoring owned by viewing module.
    void addMolColoring(int id);
    /// Remove molColoring.
    void removeMolColoring(int id);
    /// Add highlighting port owned by viewing module.
    void addHighlightPort(int id);
    /// Remove highlighting port.
    void removeHighlightPort(int id);
    //  Get name of module section.
    int  getModuleName(int section, QString & str);
    /// Update selection from filter.
    void updateSelectionFromFilter(MolFilter * filter, int filterId, MolColoring * molColoring);
    /// Update list of highlighted atoms from @c list.
    void updateHighlighted(McList<HxMolecule::HighlightedAtom> & list);
    /// Update levels in case new levels or groups have been added.
    void update();
    /// Update levels in case new levels or groups have been added.
    void updateLevels(MtGroupRef & gr);
    //  update first column 
    void updateItemColumn();
    //  update first column for subentries of @c it 
    void updateItems(QxSelectionListViewItem * it);
    //  parse tcl command
    int  parse(Tcl_Interp* t, int argc, char **argv);
    //  save current settings
    void saveSettings(FILE* fp);
    // Return module index from column index.
    int getModuleIdx(int colIdx);
    // Return if color should be shown.
    bool useColor() { return showColor; }
    // Return color for group reference and module index.
    QRgb getColor(QxSelectionListViewItem * item, 
                  int moduleIdx);

    struct MolColoringUserData {
        QxSelectionListViewItem * item;
        unsigned char mode;
        unsigned char molIdx;
    };
    MolColoringUserData cbUserData;
    void colorEditCB(const HxColorEditor &colEd);
    static void colorEditCBS(void *userData, const HxColorEditor &colEd);

protected:
    // initialize menus
    void initInfoAndMasterLevelMenus();
    
    // create abbreviation for common viewer names such as, e.g. MoleculeView
    int  getShortCut(const char * name, QString & str);
    
    // add item @c it and call @c addItems() for all subitems
    void addItems(MtGroupRef &gref, QxSelectionListViewItem * it);
    // add/remove info column to/from listview 
    void addInfoColumn(MolTopology * topo, int infoMapId);
    void removeInfoColumn(int infoMapId);
    // set info for info column infoMapId
    void setInfo(MolTopology * topo, int infoMapId);
    // add @c item information for column @c infoMapId
    void addInfoColumnEntry(MolTopology * topo, int infoMapId, 
                            QxSelectionListViewItem * item, QString str);
    // add @c item type for column @c infoMapId
    void addInfoColumnEntry(int infoMapId, QxSelectionListViewItem * item, 
                            McDArray<McDArray<QString > > &typeStr);
    // auxiliary functions that fill some arrays
    void makeInfoForLevelInfoColumn(MolTopology * topo, int levelId);
    void makeInfoForAdditionalInfoColumn(MolTopology * topo, int colInfoMapId);
    void makeInfoForHighlighting(QxSelectionListViewItem * item);
    void makeInfoForHighlighting(MolTopology * topo,
                                 McDArray<MtGroupRef> &list);
    // add/remove module column with tick boxes
    void addModuleColumn(int moduleMapId);
    void removeModuleColumn(int moduleMapId);

    // open @c item - if all is true, all subitems will also be opened
    void openItem(QxSelectionListViewItem * item, bool all=false);
    // see @c openItem()
    int  closeItem(QxSelectionListViewItem * item, bool all=false);
    // highlight/unhighlight all items depending on @c onOff
    void highlightAllItems(bool onOff);
    // if @c highlightFlag is false, unhighlight item and subitems
    void highlightItem(QxSelectionListViewItem * item, bool highlightFlag=true);
    // update all items depending on currently highlighted items
    void handleHighlighting();
    // update @c item and subitems
    bool handleHighlightedItem(QxSelectionListViewItem * item);
    // highlight/unhighlight children of @c item depending on @c highlightFlag
    void highlightChildren(QxSelectionListViewItem * item, bool highlightFlag);
    // add/remove/replace highlighted atoms according to @c selected bitfield 
    float highlightAtoms(QxSelectionListViewItem * item, McBitfield & selected, 
                         int buttonId);
    void toggleSelection(QxSelectionListViewItem * item, int col);
    bool isItemSelected(QxSelectionListViewItem * item, MolFilter * filter);
    void updateSelection(MolFilter * filter, int section, MolColoring * molColoring);
    // set selection status for @c item
    float setSelectionStatus(QxSelectionListViewItem * item, 
                             MolFilter * filter, int section,
                             MolColoring * molColoring);
    // update selection depending on highlighting
    void highlightToSelect(QxSelectionListViewItem * item,
                           MolFilter * filter, bool addFlag);
    // add a new level (we are not able to remove levels yet)
    void addLevel();
    
signals:
    void exit(bool ok);         
    
public slots:
    void accept();
    /* called whenever masterLevelMenu is selected
       @c id is the is of the menu item */
    void handleMasterLevelMenu(int id);
    /* called whenever infoMenu is selected
       @c id is the is of the menu item */
    void handleInfoMenu(int id);
    // @c optionsMenu is selected
    void handleOptionsMenu(int id);
    /* @c button  - which mouse button is pressed (cur. not used)
       @c item    - list item that was clicked
       @c p       - point in listview (cur. not used)
       @c section - listview section that was pressed */
    void handleMousePressEvent(int button, Q3ListViewItem * item, 
                               const QPoint & p, int section);
    void handleMouseClickEvent(int button, Q3ListViewItem * item, 
                               const QPoint & p, int section);
    void handleMouseMoveEvent(int button, Q3ListViewItem * item, 
                              const QPoint & p, int section);
    // @c ctrlPressed states whether Ctrl key is pressed in addition.
    void handleSpacePressEvent(unsigned int ctrlPressed);

    void handleColorModification(QxSelectionListViewItem * item,
                                 int molIdx, int button);

    // selfexplaining
    void initHighlightMenu();
    void handleModulesMenu(int id);
    void handleHighlightMenu(int id);

    // sets the focus correctly when item expand or collapse
    void setFocusCollapseExpand(Q3ListViewItem * item);

    // module popup stuff - setting the atom selection for modules 
    void openSelectPopup(int id);
    void handleRestrictToPopup(int id);
    void handleCombineWithPopup(int id);
    void handleSetPopup(int id);
    
    // highlight item in listview according to expression and the type
    // of button pressed
    void handleExpression(int buttonId);

    // open help browser
    void openHelp();
};

#endif

/// @}

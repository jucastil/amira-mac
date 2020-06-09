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

/// @addtogroup hxneuroneditor hxneuroneditor
/// @{
#ifndef QXVIEWONLYHIERARCHICALLABELSVIEW_H
#define QXVIEWONLYHIERARCHICALLABELSVIEW_H

#include "hxneuroneditorAPI.h"
#include "QxHierarchicalLabelsViewItems.h"
#include <QTreeWidget>
#include <hxspatialgraph/HierarchicalLabels.h>
#include <hxspatialgraph/HxSpatialGraph.h>


/** This class is a Qt widget for viewing label trees, 
 *  represented by one or more HierarchicalLabels objects.
 *  It also shows the color, a checkbox, and the location (VERTEX, EDGE, etc.) for each label
 */
class HXNEURONEDITOR_API QxViewOnlyHierarchicalLabelsView : public QTreeWidget
{
    Q_OBJECT

public:

    enum COLUMN {
        COL_NAME
    ,   COL_COLOR
    ,   COL_VISIBILITY
    ,   COL_LOCATION
    ,   COL_LABEL_ID   // Hidden column
    ,   COL_SIZE
    };

    QxViewOnlyHierarchicalLabelsView(QWidget *parent);
    ~QxViewOnlyHierarchicalLabelsView();

    /// add a label group at once
    virtual void addLabelGroup(HierarchicalLabels const& labelGroup, const char* attribName, bool onEdge, bool onVertex);

    /// remove a label group
    void removeLabelGroup(McString name);

    /// update tri state checkboxes state according to \a visibility
    /// Where visibility is an array of all current available labelGroups (toplevel items)
    /// holding an array visibility states for each label of the labelGroup
    /// The visibility state is defined as follows:
    /// 1 = invisible (first bit set)
    /// 2 = visible   (second bit set)
    /// 3 = partially visible (first and second bit set)
    /// 0 = label id is not present in current spatialgraph attribute
    void setVisibility(const McDArray< McDArray<char> >& visibility);

    /// returns a list \a labelIds of selected labels from the corresponding label group
    /// \a labelIds[i] is in the labelgroup with name \a labelGroupNames[i]
    void getSelectedItems(McDArray<McString>& labelGroupNames, McDArray<int>& labelIds);

    /// returns a list \a labelIds of visible labels from the corresponding label group
    /// \a labelIds[i] is in the labelgroup with name \a labelGroupNames[i]
    void getVisibleItems(McDArray<McString>& labelGroupNames, McDArray<int>& labelIds);

    /// Updates the label names and colors of all existing label trees in the
    /// label tree window, according to the label information in \a labelGroups.
    void updateLabelNamesAndColors(HxSpatialGraph::LabelGroups& labelGroups);

    /// Shows the label name in bold font and increase font point size by 2 if \a highlight is set.
    /// Otherwise, the label name is printed in normal font.
    void highlightItem(const char* labelGroupName, const int labelId, const bool highlight = true);

signals:

    /// This signal is emitted when the label with id \a labelId 
    /// from labelGroup with \a labelGroupName changed. The new state is \a state.
    void visibilityChanged(McString labelGroupName, int labelId, bool state);

protected:

    QTreeWidgetItem* findItem(int id, QTreeWidgetItem *item);

    /// Recursively sets the child checkboxes of \a item to state \a state.
    /// Where state could be either true \a Qt::checked or false \a Qt::unchecked.
    /// Note: checkbox stateChanged() signals will be blocked
    void updateChildrenCheckboxes(QTreeWidget *tree, QTreeWidgetItem *item, bool state);

    /// Recursively sets the visibility of all child checkboxes according to \a visibility
    /// see also setVisibility() for a description of \a visibility
    /// Note: checkbox stateChanged() signals will be blocked
    int updateChildrenCheckboxes(int topLevelId, QTreeWidgetItem *item, const McDArray< McDArray<char> >& visibility);

    /// Set the column widgets for a root item in the tree
    virtual void setRootItemColumnWidgets(QTreeWidgetItem* rootItem, 
                                          const McString labelName, 
                                          const int labelId, 
                                          const McColor color, 
                                          bool onEdge, 
                                          bool onVertex);

    /// Set the column widgets for one non-root item in the tree
    virtual void setColumnWidgets(QTreeWidgetItem* item, 
                                  const McString labelName, 
                                  const int labelId, 
                                  const McColor color);

    void addLabelSubTree(HierarchicalLabels const& labelTree, QTreeWidgetItem* parentItem, const int labelId);

    void updateLabelNamesAndColorsInSubtree(QTreeWidgetItem* labelItem,
                                            const HierarchicalLabels* labelGroup);

    /// Changes the color of the existing color icon in \a labelItem to \a color.
    virtual void setLabelItemColor(QTreeWidgetItem* labelItem, const McColor color);

protected slots:

    /// Process signals from the visibility checkboxes. The labelId and labelGroupName
    /// of the changed checkbox is figured out and emitted with the \a visibilityChanged signal.
    void emitVisibilityChange(int state);
};

#endif


/// @}

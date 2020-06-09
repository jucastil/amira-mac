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
#ifndef QX_LABEL_TREE_VIEW_H
#define QX_LABEL_TREE_VIEW_H

#include "hxneuroneditorAPI.h"
#include "QxViewOnlyHierarchicalLabelsView.h"

class HxNeuronEditorSubApp;
class QDropEvent;

class HXNEURONEDITOR_API QxEditableHierarchicalLabelsView : public QxViewOnlyHierarchicalLabelsView
{
    Q_OBJECT

public:
    QxEditableHierarchicalLabelsView(QWidget *parent);
    ~QxEditableHierarchicalLabelsView();
    
    void setEditor(HxNeuronEditorSubApp *editor) { mEditor = editor; }

    /// add a single new label to a existing label group or to a label
    void addLabel(const char* labelGroupName, int parentId, int labelId, const char* name, const McColor& color);
    
    /// remove a label 
    void removeLabel(const char* labelGroupName, int labelId);
    
signals:
    /// This signal is emitted when the color of label with id \a labelId 
    /// from labelGroup with \a labelGroupName changed. The new color is \a newColor.
    void colorChanged(McString labelGroupName, int labelId, McColor newColor);

    /// emitted after swap of labels \a srcLblId and \a dstLblId 
    /// within labelgroup \a labelGroupName has been completed
    void labelRelocated(const McString &labelGroupName, int srcLblId, int dstLblId);

    // emitted after swap of labelgroups \a srcGrpLbl and \a dstGrpLbl has been completed
    void labelGroupRelocated(const McString &srcGrpLbl, const McString &dstGrpLbl);

protected slots:
    /// rename label callback 
    void setItemName(QTreeWidgetItem*, int);

    /// Process signals from the color widgets. The labelId and labelGroupName
    /// of the changed color is figured out and emitted with the \a colorChanged signal.
    void emitColorChange(McColor color);

protected:
    /// show on right click on label or labelGroup
    void showRenameOrDeleteLabelContextMenu(QMouseEvent * event);

    /// show on right click on background
    void showAddLabelGroupContextMenu(QMouseEvent * event);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void dropEvent(QDropEvent *event);

    virtual void dragEnterEvent(QDragEnterEvent *event);

    virtual void dragMoveEvent(QDragMoveEvent *event);

    /// creates a deep copy of a \a sourceItem QTreeWidgetItem and copies it to \a targetItem
    void deepCopySubTree(QTreeWidgetItem& sourceItem, QTreeWidgetItem& targetItem);

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

    virtual void setLabelItemColor(QTreeWidgetItem* labelItem, const McColor color);

private:
    HxNeuronEditorSubApp     *mEditor;

    // helper if one of the root nodes get deleted
    McString mOldName;

    // starting drag position relative to QTreeWidget
    QPoint dragStartPosition;
};

#endif 


/// @}

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
#ifndef QX_STEP_EDGES_LABEL_TREE_COMBO_BOX_H
#define QX_STEP_EDGES_LABEL_TREE_COMBO_BOX_H

#include <QAbstractItemModel>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QComboBox>
#include <QTreeView>

#include <vector>

#include <hxspatialgraph/HxSpatialGraph.h>
#include <hxspatialgraph/HierarchicalLabels.h>

class QWidget;
class QObject;
class QButtonGroup;
class HxColormap256;

class ModelItem: public QObject {

    Q_OBJECT

public:
    ModelItem(ModelItem * parent, QString labelName, int row, int labelId, QString groupName);
    virtual ~ModelItem();

    ModelItem * getParent() const;
    const QString & getLabelName() const;
    const int getLabelId() const;
    const QString & getGroupName() const;

    int getRow() const;
    const std::vector<ModelItem*>& getChildren() const;

    void addChild(ModelItem* child);
    void setChildren(const std::vector<ModelItem*>& childList);
    void setLabelName(QString labelName);

private:
    QString mLabelName;
    int mLabelId;
    QString mGroupName;

    ModelItem * mParent;
    std::vector<ModelItem*> mChildren;

    int mRow;
};

class Model : public QAbstractItemModel
{
    Q_OBJECT

public:
    Model(QObject *parent = 0);
    ~Model();

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    //bool hasChildren(const QModelIndex &parent) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    enum LabelFilter{ NODE, EDGE };
    void setupModelData(HxSpatialGraph* graph, LabelFilter filter);

    const int getLabelId(const QModelIndex& index) const;
    const QString getGroupName(const QModelIndex& index) const;

    void clear();
    const QModelIndex find(const QString& groupName, const QString& labelName, ModelItem* item = NULL);

    /** @brief Returns the default item index.
        @param currentItem if not NULL the index of the group default item to which \c currentItem belongs to ('Not assigned')
               will be returned, otherwise the index of the global default item ('All') will be returned.
    */
    const QModelIndex getDefaultModelIndex(QModelIndex* currentIndex = 0);
    

private:
    void addItem(const HierarchicalLabels &labelTree, ModelItem* parentItem, const QString& groupName, const unsigned int labelId);

    /// Returns the matching group ModelItem for an arbitray ModelItem
    const ModelItem* getGroupModelItem(const ModelItem* item);

    ModelItem* mRootItem;
    std::vector <ModelItem *> mModelItems;
};

class QxStepEdgesLabelTreeComboBox : public QComboBox
{
    Q_OBJECT

public:
    QxStepEdgesLabelTreeComboBox(QWidget* parent = 0);

    bool eventFilter(QObject* object, QEvent* event);

    virtual void showPopup();
    virtual void hidePopup();

    const int getCurrentLabelId() const;
    const QString getCurrentGroupName();

    void clear();
        
    void updateModel(HxSpatialGraph* graph, Model::LabelFilter filter);

    /** Set the current index according to the stepping mode (segment or node)
        and according to the selected @see SpatialGraph segment or node index.
    */
    void setCurrentIndexToSelected(const int selectedIdx, bool edgeStepMode);
    void setCurrentIndexToDefault();


//public slots:
//    void setEditText(const QString & text );

private:
    void setCurrentIndexToModelIndex(QModelIndex& index);

    bool skipNextHide;

    QTreeView* mTree;
};

#endif


/// @}

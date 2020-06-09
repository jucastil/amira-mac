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
#ifndef QX_STEP_EDGES_TOOL_H
#define QX_STEP_EDGES_TOOL_H

#include <QtCore/QObject>

#include <hxneuroneditor/QxNeuronEditorToolBox.h>
#include <hxneuroneditor/HxNeuronEditorSubApp.h>

#include <hxneuroneditor/hxneuroneditorAPI.h>
#include <hxneuroneditor/ui_QxViewToolbox.h>

class QWidget;
class QShortcut;

class HXNEURONEDITOR_API QxStepEdgesTool  : public QObject
{

    Q_OBJECT

public:

    QxStepEdgesTool();
    ~QxStepEdgesTool();

    /// Initialize @see QxStepEdgesTool::ui with ViewToolbox Ui
    void setUi(Ui::ViewToolbox &viewToolBoxUi);

protected:
    struct CurrentEdge
    {
        int edgeID;
        McVec3f edgeSourceCoords;
        McVec3f edgeTargetCoords;
    };
    struct CurrentPoint
    {
        SpatialGraphPoint spatialGraphPoint;
        McVec3f pointCoords;
    };
    struct CurrentNode
    {
        int nodeID;
        McVec3f nodeCoords;
    };

    enum SteppingToolSelectionChangeCases { SINGLE_EDGE_SELECTED =0, SINGLE_NODE_SELECTED, STEPPER_DEFAULT};

    CurrentEdge mCurrentEdge;
    CurrentPoint mCurrentPoint;
    CurrentNode mCurrentNode;

    Ui::ViewToolbox ui;

    McBitfield mEdges;
    McBitfield mNodes;
    McVec3f getVoxelSize();

    void update();
    void updateAfterGeometryChanged();

    void updateEdgeNumber();
    void updatePointNumber();
    void updateNodeNumber();

    void updateCurrentPoint();
    void updateCurrentEdge();
    void updateCurrentNode();
    void updateCurrentEdgeAfterGeometryChanged();
    void updateCurrentEdgeAfterSelectionChanged();
    void updateCurrentNodeAfterGeometryChanged();
    void updateCurrentNodeAfterSelectionChanged();

    void updateCurrentLabelAfterSelectionChanged();
    void updateEdgesAssignedToCurrentLabel();
    void updateNodesAssignedToCurrentLabel();

    void initCurrentEdge();
    void initCurrentPoint();
    void initCurrentNode();

    void initEdgeStepper();
    void initEdgesAndPoints(bool forceHighlight = false);
    void initNodes(bool forceHighlight = false);

    void selectCurrentSpatialGraphPoint();
    void selectCurrentEdge();
    void selectCurrentNode();
    void clearSelection();

    void readCurrentEdge();
    void readCurrentPoint();
    void readCurrentNode();
    void writeCurrentEdge(int newEdge, bool forceHighlight = false);
    void writeCurrentPoint(int newPoint);
    void writeCurrentNode(int newNode, bool forceHighlight = false);

    bool isEdgeUpToDate() const;
    bool isPointUpToDate() const;
    bool isNodeUpToDate() const;

    bool isCurrentEdgeValid() const;
    bool isCurrentNodeValid() const;
    int getValueFromEdgeIdx(int edgeIdx);
    int getValueFromNodeIdx(int nodeIdx);

    int getSelectionCase();

    void handleSingleNodeSelectedESMode();
    void handleSingleNodeSelectedNSMode();
    void handleSingleEdgeSelected();
    
    void blockAllSignals();
    void unblockAllSignals();

public slots:
    void processLabelComboBox(int);
    void processCurrentEdgeChanged(int);
    void processCurrentPointChanged(int);
    void processCurrentNodeChanged(int);
    void processSpatialGraphChanges(HxNeuronEditorSubApp::SpatialGraphChanges);
    void processSpatialGraphSelectionChanges();
    void stepModeChanged();

signals:

    void steppedEdge(int);
    void steppedNode(int);


private:

    QShortcut* mNodesEdgesUp;
    QShortcut* mNodesEdgesDown;
    QShortcut* mPointsUp;
    QShortcut* mPointsDown;
};

#endif


/// @}

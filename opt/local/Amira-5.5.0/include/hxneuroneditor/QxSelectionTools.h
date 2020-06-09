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
#ifndef QX_STANDARD_TOOLS_H
#define QX_STANDARD_TOOLS_H

#include "QxNeuronEditorTool.h"
#include "SelectionHelpers.h"
#include <QObject>
#include <hxcore/HxGLPolyLine.h>
#include <hxcore/HxWorkArea.h>
#include "hxneuroneditorAPI.h"
#include "HxNeuronEditorSubApp.h"


//////////////////////////////////////////////////////////////////////////////////////////
class QxSelectAllTool  : public QxNeuronEditorTriggerTool {
public:
    
    QxSelectAllTool(HxNeuronEditorSubApp* editor);
    ~QxSelectAllTool();
    bool supportsViewer(HxViewerBase* baseViewer); 
    void onTrigger(HxViewerBase* activeViewer, int modifiers);

protected:

    void selectAll();
};

//////////////////////////////////////////////////////////////////////////////////////////
class QxClearSelectionTool  : public QxNeuronEditorTriggerTool {
    
public:
    
    QxClearSelectionTool(HxNeuronEditorSubApp* editor);
    ~QxClearSelectionTool();
    bool supportsViewer(HxViewerBase* baseViewer); 
    void onTrigger(HxViewerBase* activeViewer, int modifiers);

protected:

    void clear();
};



//////////////////////////////////////////////////////////////////////////////////////////
class QxLassoTool  : public HxViewerLassoTool, public QxNeuronEditorTool {
    
public:

    QxLassoTool(HxNeuronEditorSubApp* editor);
    ~QxLassoTool();

    bool supportsViewer(HxViewerBase* baseViewer);

protected:

    static bool drawSelectionCB(void* userData);

    void doLassoSelection();
    SpatialGraphSelection getLassoSelection(const HxSpatialGraph* graph);
};


//////////////////////////////////////////////////////////////////////////////////////////
class QxSelectSubTreeTool : public QxNeuronEditorModalTool {
public:

    QxSelectSubTreeTool(HxNeuronEditorSubApp* editor);
    ~QxSelectSubTreeTool();

    bool supportsViewer(HxViewerBase* baseViewer);
    void onActivate(HxViewerBase* activeViewer);
    void onDeactivate(HxViewerBase* activeViewer);
    void pickCallback(const SpatialGraphViewNode *viewNode, SoEventCallback *node);

protected:
    void selectSubTree(int vertexId, 
                       int edgeId, 
                       SpatialGraphPoint pointId, 
                       SelectionHelpers::Modifier modKeys);
};


//////////////////////////////////////////////////////////////////////////////////////////
class QxShortestPathTool : public QxNeuronEditorTriggerTool {
public:
    QxShortestPathTool(HxNeuronEditorSubApp* editor);
    ~QxShortestPathTool();

    bool supportsViewer(HxViewerBase* baseViewer); 
    void onTrigger(HxViewerBase* activeViewer, int modifiers);

protected:
    
    void calculateShortestPath();
    
};

//////////////////////////////////////////////////////////////////////////////////////////
class QxSelectTool : public QxNeuronEditorModalTool {
    
public:
    
    enum SelectMode {
        SELECT_SINGLE_ELEMENT     = 0,
        SELECT_CONNECTED_COMPONENT = 1
    };

    QxSelectTool(HxNeuronEditorSubApp* editor, SelectMode sm);
    ~QxSelectTool();

    bool supportsViewer(HxViewerBase* baseViewer);
    void onActivate(HxViewerBase* activeViewer);
    void onDeactivate(HxViewerBase* activeViewer);
    void pickCallback(const SpatialGraphViewNode *viewNode, SoEventCallback *node);

protected:
    // Modifies the selection in SELECT_CONNECTED_COMPONENT mode
    void doConnectedComponentSelection(const int vertexId, 
                                       const int edgeId, 
                                       const SpatialGraphPoint &pointId,
                                       const SelectionHelpers::Modifier modKeys) const;

    // Modifies the selection in SELECT_SINGLE_ELEMENT mode
    void doSingleElementSelection(const int vertexId, 
                                  const int edgeId, 
                                  const SpatialGraphPoint &pointId,
                                  const SelectionHelpers::Modifier modKeys) const;


    SelectMode mSelectMode;
};



/** Function to register the SelectionTool at the HxNeuronEditorSubApp.
 *  We use extern "C" to avoid name mangling so HxDSO can find it. */
#ifdef __cplusplus
extern "C" {
#endif
	void HXNEURONEDITOR_API QxSelectionTools_init_plugin(HxNeuronEditorSubApp* editor);
#ifdef __cplusplus
}
#endif




#endif

/// @}

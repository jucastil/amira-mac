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

#include <hxcore/HxGLPolyLine.h>
#include <hxcore/HxWorkArea.h>
#include <QObject>
#include "hxneuroneditorAPI.h"
#include "QxNeuronEditorTool.h"
#include "HxNeuronEditorSubApp.h"

class QToolButton;

class QxRemoveTool  : public QxNeuronEditorTriggerTool {

    

public:
    QxRemoveTool(HxNeuronEditorSubApp* editor);
    ~QxRemoveTool();

    bool supportsViewer(HxViewerBase* baseViewer);
    void onTrigger(HxViewerBase* activeViewer, int modifiers);

protected:
    void deleteSelection();
  

};

class QxConnectTool : public QxNeuronEditorTriggerTool {
public:
    QxConnectTool(HxNeuronEditorSubApp* editor);
    ~QxConnectTool();

    bool supportsViewer(HxViewerBase* baseViewer);
    void onTrigger(HxViewerBase* activeViewer, int modifiers);

protected:
 
    void connectSelection();

};


class QxRemoveIntermediateVerticesTool : public QxNeuronEditorTriggerTool {
public:
    QxRemoveIntermediateVerticesTool(HxNeuronEditorSubApp* editor);
    ~QxRemoveIntermediateVerticesTool();

    bool supportsViewer(HxViewerBase* baseViewer);
    void onTrigger(HxViewerBase* activeViewer, int modifiers);

protected:
    void removeIntermediateVertices();
};


class QxConvertPointIntoNodeTool : public QxNeuronEditorTriggerTool {
public:
    QxConvertPointIntoNodeTool(HxNeuronEditorSubApp* editor);
    ~QxConvertPointIntoNodeTool();

    bool supportsViewer(HxViewerBase* baseViewer);
    void onTrigger(HxViewerBase* activeViewer, int modifiers);

protected:
    void convertPointIntoNode();
};


/** Function to register the StandardTools at the HxNeuronEditorSubApp. 
    We use extern "C" to avoid name mangling so HxDSO can find it. */
#ifdef __cplusplus
extern "C" {
#endif
	void HXNEURONEDITOR_API QxStandardTools_init_plugin(HxNeuronEditorSubApp* editor);
#ifdef __cplusplus
}
#endif




#endif

/// @}

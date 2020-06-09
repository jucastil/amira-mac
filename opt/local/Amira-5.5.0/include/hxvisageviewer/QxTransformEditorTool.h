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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef QX_SKELETON_TOOL_H
#define QX_SKELETON_TOOL_H

#include "hxvisageviewer/QxVVEditorTool.h"
#include "VisageViewerWinDLLApi.h"
#include <hxvisageviewer/ui_QxTransformEditorTool.h>
#include <hxregistration/HxAffineRegistration.h>
#include "ExNotifiable.h"
#include "HxVisageViewerSubApplication.h"

class HxVisageViewerSubApplication;
class QWidget;
class QObject;
class QButtonGroup;

class QxTransformEditorTool  : public QxVisageViewerTriggerTool, public ExNotifiable, public Ui::TransformEditorOptions {
    
    Q_OBJECT

public:

    QxTransformEditorTool(HxVisageViewerSubApplication* editor);
    ~QxTransformEditorTool();


    virtual QWidget* toolcard();
    virtual bool supportsViewer(HxViewerBase *baseViewer);
    virtual void updateToolcard();
    virtual void process(); 
    //virtual void onDeactivate() {}

    virtual void notified(const ExNotification& notification);
    
    void onStart();
    void onStop();

public slots:
    
    void updateEditor();
    void resetTransformation();
    void processDataCheckBox(bool);

protected:
    QWidget *uiParent;
    Ui::TransformEditorOptions ui;

    // resets corresponding gui controls
    void resetTranslation();
    void resetRotation();
    void resetScale();

    void setTransform(const SbVec3f& trans, const SbRotation& rot, const SbVec3f& scale);

private:

    int mRecursionGuard;
	bool mEnabled;
};

/** Function to register the Skeleton Tool at the HxVisageViewerSubApp.
 *  We use extern "C" to avoid name mangling so HxDSO can find it. */
#ifdef __cplusplus
extern "C" {
#endif
	void HXVISAGEVIEWER_API QxTransformEditorTool_init_plugin(HxVisageViewerSubApplication* editor);
#ifdef __cplusplus
}
#endif

#endif

/// @}

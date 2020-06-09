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
#include <hxvisageviewer/ui_QxAutoRegTool.h>
#include <hxvisageviewer/ui_QxAutoRegToolDialog.h>
#include <hxregistration/HxAffineRegistration.h>

#include "HxVisageViewerSubApplication.h"

class HxVisageViewerSubApplication;
class QWidget;
class QObject;
class QButtonGroup;

class QxAutoReg  : public QxVisageViewerTriggerTool, public Ui::AutoReg {
    
    Q_OBJECT

public:

    QxAutoReg(HxVisageViewerSubApplication* editor);
    ~QxAutoReg();


    virtual QWidget* toolcard();
    virtual bool supportsViewer(HxViewerBase *baseViewer);

    virtual void process(); 
    //virtual void onDeactivate() {}


    void onStart();
    void onStop();

public slots:
    void processcomboBoxMetric(int);

    void processcheckBoxAnisoScale(bool);
    void processcheckBoxIso(bool);
    void processcheckBoxRigid(bool);
    void processcheckBoxShear(bool);

    void processpushButtonAlignCenters();
    void processpushButtonAlignPrincipalAxes();
    void processpushButtonRegister();
    void processDataCheckBox(bool state = true);
    void processpushButtonMoreOptions();

protected:
    QWidget *uiParent;
    QDialog *uiDialog;
    Ui::AutoReg ui;
    Ui::AutoRegDialog   moreOptionsDialog;

    QButtonGroup *mShowItems;
    QButtonGroup *mSegmentStyle;

    McHandle <HxAffineRegistration> affineRegistration;

    void checkConnections();
    void enableControls(bool state);

	
};

/** Function to register the Skeleton Tool at the HxVisageViewerSubApp.
 *  We use extern "C" to avoid name mangling so HxDSO can find it. */
#ifdef __cplusplus
extern "C" {
#endif
	void HXVISAGEVIEWER_API QxAutoReg_init_plugin(HxVisageViewerSubApplication* editor);
#ifdef __cplusplus
}
#endif

#endif

/// @}

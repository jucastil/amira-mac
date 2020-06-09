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
#ifndef QX_VIEW_TOOLBOX_H
#define QX_VIEW_TOOLBOX_H

#include <QObject>
#include "HxNeuronEditorSubApp.h"
#include "QxNeuronEditorToolBox.h"
#include "QxStepEdgesTool.h"

#include <hxneuroneditor/ui_QxViewToolbox.h>

#include "hxneuroneditorAPI.h"
#include <hxcolor/HxColormap256.h>


class QWidget;
class QButtonGroup;
class QDoubleValidator;

class QxViewToolbox  : public QObject, public QxNeuronEditorToolBox, public Ui::ViewToolbox {
    
    Q_OBJECT

public:

    QxViewToolbox(HxNeuronEditorSubApp* editor);
    virtual ~QxViewToolbox();

    QWidget* toolcard();
    void updateToolcard();

    const int getFocusSelectionState();

    // Return visible items based on the visibility configuration.
    const SpatialGraphSelection getVisibleItems();

    void setDefaultMPRViewerValues();

public slots:
    
    void nodeColoringChanged(const QString&);
    void edgeColoringChanged(const QString&);
    void nodeScalingChanged(int);
    void nodeScalingLineEditChanged();
    void segmentLineWidthSliderChanged(int);
    void segmentLineWidthLineEditChanged();
    void pointSizeSliderChanged(int);
    void pointSizeLineEditChanged();
    void transparencySliderChanged(int);
    void transparencyLineEditChanged();
    void tracingWindowLineWidthSliderChanged(int);
    void tracingWindowLineWidthLineEditChanged();
    void tracingWindowNodeSizeSliderChanged(int);
    void tracingWindowNodeSizeLineEditChanged();
    void showItemChanged(int);
    void segmentStyleChanged(int);
    void hideSelection();
    void invertSelection();
    void viewAll();
    void focusSelectionIn3dViewer();
    void hideElementsAfterFocusIn3dViewer();

signals:
    void MPRnodeSizeSliderChanged(float);
    void MPRsegmentWidthSliderChanged(float);

protected slots:
    void updateAfterSpatialGraphChange(HxNeuronEditorSubApp::SpatialGraphChanges changes);

protected:
    QWidget *uiParent;
    Ui::ViewToolbox ui;

    QButtonGroup *mShowItems;
    QButtonGroup *mSegmentStyle;

    QDoubleValidator* mNodeScalingValidator;
    const int mNumNodeScaleSliderSteps;
    QDoubleValidator* mSegmentLineWidthValidator;
    const int mNumSegmentLineWidthSliderSteps;
    QDoubleValidator* mPointSizeValidator;
    const int mNumPointSizeSliderSteps;

private:
    QxStepEdgesTool mEdgeStepper;
    bool shouldAddVertexAttributeToVertexColoringBox(const char* item);

    McHandle<HxColormap256> mLabelsColorMap;

};

#endif

/// @}

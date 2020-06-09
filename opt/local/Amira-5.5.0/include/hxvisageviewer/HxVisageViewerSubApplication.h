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
#ifndef HX_VISAGEVIEWER_SUBAPPLICATION_H
#define HX_VISAGEVIEWER_SUBAPPLICATION_H

#include "VisageViewerWinDLLApi.h"

#include <hxvisageviewer/ui_QxVisageViewerCommonUI.h>
#include <hxvisageviewer/ui_QxVisageViewerFooterUI.h>
#include <hxvisageviewer/ui_QxVisageViewerToolbox.h>


#include <hxcore/HxSubApplication.h>
#include <hxcolor/HxColormap256.h>
#include <hxcolor/HxColormap.h>

#include <mclib/McPrimType.h>

#include <qobject.h>

#include <vsvolren/VsVolume.h>
#include <hxvsdata/VsVolumeInterface.h>


#include <QSplitter>

class QFrame;
class QWidget;
class QxApplication;
class HxVisageViewerCommon;
class QToolBar;
class QStackedLayout;
class QxVisageViewerTool;
class QxViewerPanel;
class HxViewer;
class QTreeWidget;
class QTreeWidgetItem;
class HxVisageViewerMaterialList;

class HXVISAGEVIEWER_API HxVisageViewerSubApplication : public QObject, public HxSubApplication {


    Q_OBJECT


    MC_HEADER(HxVisageViewerSubApplication);


  public:
    /// Constructor
    HxVisageViewerSubApplication();

    /// Destructor
    ~HxVisageViewerSubApplication();

    static QTabWidget* tabWidget;

    static HxVisageViewerSubApplication *getInstance();

    virtual void onStart();
    virtual void onStop();
    virtual void newObjectsCreated(const McDArray<HxObject*>& newObjects);

    /// load plugins
    void loadTools();

    McHandle <HxColormap256> grayColor;
    QxApplication* mVisageViewer;

    McPrimType primaryMcPrimType;
    McPrimType overlayMcPrimType;

    static QString getProperNumber(McPrimType dataType, float num);

    void registerTool(QxVisageViewerTool* tool);

    Ui::QxVisageViewerCommonUI uiVVPanel;
    Ui::QxVisageViewerFooterUI uiFooter;
    Ui::wToolBoxWidget uiToolBox;
    //HxVisageViewerMaterialList *materialList;
    QActionGroup *mVisageViewerTools;
    QxViewerPanel* mPanel;
    HxViewer* mViewer;
    float dataWindow[4];


    void processwROIWidget( QTreeWidget *qTreeWidget, QTreeWidgetItem * item, int column);
    void processwROIWidget( QTreeWidget *qTreeWidget );

    
    McHandle<VsVolume> primaryVolume;
    McHandle<VsVolume> overlayVolume;

    McHandle<HxColormap> primaryDataColormap2D;
    McHandle<HxColormap> overlayDataColormap2D;
    static QAction *primaryColorlastAction2D;
    static QAction *overlayColorlastAction2D;

    McHandle<HxColormap> primaryDataColormap3D;
    McHandle<HxColormap> overlayDataColormap3D;
    static QAction *primaryColorlastAction3D;
    static QAction *overlayColorlastAction3D;

    HxData *getOverlayData();


    bool isPrimaryVolumeVisible(); 
    bool isOverlayVolumeVisible();

    void setMonitor(bool status) { dataMonitoring = status; }

    void notifyStop();

  protected slots:
    void configureColormapMenu();
    void processDataCheckBox(bool checked, bool force = false);
    void processwLabelDataCheckBox(bool);
    void processwDataComboBox(int value, bool resetRangeSlider=true);
    void processwLabelDataComboBox(int value);
    void processwFusionWeightSlider(int value);
    void slotDataTouched(unsigned int);
    void slotLabelTouched(unsigned int touch);

    void processColormap(QAction* action, QMenu *alternativeSender = NULL );


    void processDataRangeSlider(float vmin, float vmax);
    void processThicknessSlider(int);
    void processThicknessLineEdit();

    void processwRenderMode(bool checked);
    void slotProcess3DRenderMode(bool checked);

    void slotObjectAddedSA(HxObject* object);
    void slotObjectRemovedSA(HxObject* object);
    void slotObjectRenamedSA(HxObject* object, const char* old_name);

    void slotSplitterMoved(int pos, int index);
    
    void slotToolTriggered(QAction *action);
    
    void process3DMPR(bool);
    
    void slotMaterialColorChanged(int);

    void slotMaterialNameChanged(int);

  protected:
   
    bool blockTouchMaterial;

    QWidget* mGuiWidget;

    QWidget* mViewerWidget;

    QSplitter * mSplitter;
    QFrame* mToolBoxFrame;
    
    QButtonGroup *m3DRenderModeButtonGroup;
    QButtonGroup *m3DRenderOptionsVRTButtonGroup;
    QButtonGroup *m3DRenderOptionsMIPButtonGroup;

    QMenu *primarycolorMenu2D;
    QMenu * overlaycolorMenu2D;
    QMenu *primarycolorMenu3D;
    QMenu *overlaycolorMenu3D;
    HxData *oldDataP;
    HxData *oldDataO;
    HxData *oldLabelData;
    int oldIndexP;
    int oldIndexO;

    bool autoAdjustRangeForPrimaryData;
    bool autoAdjustRangeForOverlayData;

     // default toolbar and it's toolcard
    QToolBar *mDefaultToolBar;
    QStackedLayout *mToolOptions;
    static HxVisageViewerSubApplication *visageViewerInstance;


    int primaryIndex;
    int overlayIndex;
    bool noTextUpdate;


    void resetView(VsData *data) ;
    void processwPrimaryDataComboBox(int value, bool resetRangeSlider);
    void setVolume(void);
    void initializeDataBoxes(void);
    /// initialize label data combobox
    void initializeLabelData(void);
    void updateRegistrationTransform();
    void setControlsEnabled(bool state);

    void enablePrimaryDataControl(bool state);
    void enableOverlayDataControl(bool state);
    void checkFusion();

    void processSliderHistogram(bool primaryComboBox, HxObject* object);
    bool isDataTypeSupported(VsData *data);
 
    // block updates of thickness QxLineEdit
    bool mThicknessLineEditNoTextFieldAdjust;

    bool mIsToolboxCollapsed;
    int mToolbarSize;
    QList<int> mToolsSizes;

    void setToolBoxAreaSize(int height);

    bool dataMonitoring;
};

#endif

/// @}

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

/// @addtogroup hxplot hxplot
/// @{
#ifndef QZ_OBJECTEDITOR
#define QZ_OBJECTEDITOR

#include <hxplot/PzPlotWinDLLApi.h>

#include <QDialog>
#include <QPalette>
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>

#include <mclib/McDArray.h>

#ifdef _WIN32
#include <windows.h>
#endif

class QMenuBar;
class QGroupBox;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QSpinBox;
class QButtonGroup;
class QRadioButton;
class QTabBar;
class QPixmap;
class QButton;
class QMenu;
class QDoubleValidator;
class QxChooseColorButton;
class QxFullSlider;
class QHBoxLayout;
class QAction;
class QTreeWidget;
class QTreeWidgetItem;

class QzObjectEditor;
class QzPortFrame;

class PzBaseObject;
class PzPlotObject;
class PzPlotGroup;
class PzLegend;
class PzCurve;
class PzAnCurve;
class PzAnnotation;
class PzMarkerline;
class PzGrid;
class PzDrawArea;
class PzPlotArea;
class PzAxis;
class PzPolarAxis;
class PzErrorbar;
class PzLattice;
class PzColormap;

typedef void QzMenuCB(int itemNo, const QzObjectEditor &edwin, void* userdata);

typedef void QzObjectEditorCB(int result, const QzObjectEditor &edwin,
                              void* userdata);

typedef void QzSelectedCB(const char* objName, const QzObjectEditor &edwin,
                          void* userdata);

typedef void QzShowitCB(bool showit, const QzObjectEditor &edwin,
                        void* userdata);

/**
   Class for the object editor of the plotting tool
@author Olaf Paetsch
*/
class HXPLOT_API QzObjectEditor: public QDialog {

    Q_OBJECT

private:

    QzObjectEditorCB *editorCallback;
    void             *editorUserdata;
    QzMenuCB         *menuCallback;
    void             *menuUserdata;
    QzSelectedCB     *selectedCallback;
    void             *selectedUserdata;
    QzShowitCB       *showitCallback;
    void             *showitUserdata;

    QWidget     *changedWidget;

    QTreeWidget  *objectListView;
    QHBoxLayout  *objectLayout;

    QPushButton *okButton;
    QPushButton *applyButton;
    QPushButton *cancelButton;
    QCheckBox   *showobject;

    QMenuBar*   theMenu;
    QMenu*      editMenu;
    QAction*    copyAction;
    QAction*    cutAction;
    QAction*    pasteAction;
    QAction*    appendAction;
    QMenu*      newMenu;

    QGroupBox*   baseAttrBox;
    QGroupBox*   oldAttrBox;
    QGroupBox*   legendAttrBox;
    QGroupBox*   curveAttrBox;
    QGroupBox*   annoAttrBox;
    QGroupBox*   mlineAttrBox;
    QGroupBox*   gridAttrBox;
    QGroupBox*   pareaAttrBox;
    QGroupBox*   axisAttrBox;
    QGroupBox*   paxisAttrBox;
    QGroupBox*   errorbarAttrBox;
    QGroupBox*   groupAttrBox;
    QGroupBox*   latticeAttrBox;
    QGroupBox*   colormapAttrBox;

    QzPortFrame *groupRangeFrame;
    QLabel      *groupRange;

    QzPortFrame *curveRangeFrame;
    QLabel      *curveRange;
    QzPortFrame *curveTypeFrame;
    QComboBox   *curveTypeMenu;
    QxChooseColorButton *curveColor;
    QzPortFrame *curveLineFrame;
    QComboBox   *curveLineMenu;
    QSpinBox    *curveLinewidth;
    QzPortFrame *curveMarkerFrame;
    QComboBox   *curveMarkerMenu;
    QSpinBox    *curveMarkerFreq;
    QxChooseColorButton *curveMarkerColor;
    QzPortFrame *curveLabelFrame;
    QLineEdit   *curveLabel;

    QzPortFrame *ancurveFunctionFrame;
    QComboBox   *ancurveFunction;
    QCheckBox   *ancurveExplicit;
    QzPortFrame *ancurveRangeFrame;
    QLineEdit   *ancurveFrom, *ancurveTo, *ancurveDelta;
    QDoubleValidator* onlyDoubles;

    QzPortFrame   *legendPosFrame;
    QLineEdit     *legendPosX, *legendPosY, *legendPosD;
    QzPortFrame   *legendRowColFrame;
    // QLineEdit   *legendRow, *legendCol;
    QButtonGroup  *legendOrientation;
    QRadioButton  *legendHorizontal;
    QRadioButton  *legendVertical;
    QzPortFrame   *legendOptionsFrame;
    QxChooseColorButton *legendFrameColor;
    QxChooseColorButton *legendLabelColor;
    QCheckBox     *legendFrame;
    QzPortFrame   *legendTypeFrame;
    QComboBox     *legendTypeMenu;

    QxChooseColorButton *mlineColor;
    QzPortFrame   *mlinePosFrame;
    QButtonGroup  *mlineOrientation;
    QRadioButton  *mlineHorizontal;
    QRadioButton  *mlineVertical;
    QLineEdit     *mlinePos;
    QzPortFrame   *mlineLineFrame;
    QComboBox     *mlineLineMenu;
    QSpinBox      *mlineLinewidth;
    QzPortFrame   *mlineLabelFrame;
    QCheckBox     *mlineAnno;
    QLineEdit     *mlineLabelFormat;
    QComboBox     *mlineLabelPos;
    QzPortFrame   *mlineProbeFrame;
    QCheckBox     *mlineProbe;
    QComboBox     *mlineProbenames;
    QComboBox     *mlineMarkerMenu;

    QzPortFrame   *annoTextFrame;
    QLineEdit     *annoText;
    QzPortFrame   *annoPosFrame;
    QLineEdit     *annoPosX, *annoPosY;
    QButtonGroup  *annoCoord;
    QRadioButton  *annoWC;
    QRadioButton  *annoNC;
    QzPortFrame   *annoFontFrame;
    QComboBox     *annoFontMenu;
    QzPortFrame   *annoColorFrame;
    QxChooseColorButton *annoColor;
    QzPortFrame   *annoOptionsFrame;
    QxChooseColorButton *annoFillColor;
    QCheckBox     *annoFrame;
    QCheckBox     *annoFillBg;

    QzPortFrame   *gridLineFrame;
    QComboBox     *gridLineMenu;
    QSpinBox      *gridLinewidth;
    QxChooseColorButton *gridColor;
    QzPortFrame   *gridShowFrame;
    QButtonGroup  *gridShow;
    QCheckBox     *gridShow1;
    QCheckBox     *gridShow2;
    QCheckBox     *gridShow3;

    QzPortFrame   *pareaAreaLabelFrame;
    QzPortFrame   *pareaAreaFrame;
    QLineEdit     *pareaBlX, *pareaBlY, *pareaTrX, *pareaTrY;
    QzPortFrame   *pareaOptionsFrame;
    QCheckBox     *pareaRelative;
    QCheckBox     *pareaBoxFill;
    QCheckBox     *pareaBoxFrame;
    QCheckBox     *pareaHandles;
    QzPortFrame   *pareaColorFrame;
    QxChooseColorButton *pareaColor;
    QzPortFrame   *pareaLineFrame;
    QComboBox     *pareaLineMenu;
    QSpinBox      *pareaLinewidth;

    QTabBar       *xyTabBar;
    QzPortFrame   *axisRangeFrame;
    QLineEdit     *axisMinRange, *axisMaxRange;
    QCheckBox     *axisAuto;
    QCheckBox     *axisNiceNum;
    QzPortFrame   *axisTickFrame;
    QSpinBox      *axisTicks;
    QPushButton   *axisDeltaTickButton;
    QLineEdit     *axisDeltaTick;
    QCheckBox     *axisDTNiceNum;
    QLineEdit     *axisTickFormat;
    QzPortFrame   *axisSubtickFrame;
    QSpinBox      *axisSubticks;
    QzPortFrame   *axisInterFrame;
    QButtonGroup  *axisInter;
    QRadioButton  *axisInterMin;
    QRadioButton  *axisInterMid;
    QRadioButton  *axisInterMax;
    QRadioButton  *axisInterZero;
    QCheckBox     *axisBoxShow;
    QzPortFrame   *axisLinLogFrame;
    QButtonGroup  *axisLinLog;
    QRadioButton  *axisLin;
    QRadioButton  *axisLog;
    QCheckBox     *axisShow;
    QzPortFrame   *axisLineFrame;
    QxChooseColorButton *axisColor;
    QSpinBox      *axisLinewidth;
    QCheckBox     *axisArrow;
    QzPortFrame   *axisLabelFrame;
    QLineEdit     *axisLabel;
    QComboBox     *axisLabelPosMenu;
    QxChooseColorButton *axisLabelColor;

    QTabBar       *phirTabBar;
    QzPortFrame   *paxisRangeFrame;
    QLineEdit     *paxisMinRange, *paxisMaxRange;
    QCheckBox     *paxisAuto;
    QCheckBox     *paxisNiceNum;
    QzPortFrame   *paxisQuadrantFrame;
    QCheckBox     *paxisQI;
    QCheckBox     *paxisQII;
    QCheckBox     *paxisQIII;
    QCheckBox     *paxisQIV;
    QzPortFrame   *paxisTickFrame;
    QSpinBox      *paxisTicks;
    QPushButton   *paxisDeltaTickButton;
    QLineEdit     *paxisDeltaTick;
    QCheckBox     *paxisDTNiceNum;
    QLabel        *paxisTickFormatLabel;
    QLineEdit     *paxisTickFormat;
    QzPortFrame   *paxisSubtickFrame;
    QSpinBox      *paxisSubticks;
    QzPortFrame   *paxisRadDegFrame;
    QButtonGroup  *paxisRadDeg;
    QRadioButton  *paxisRad;
    QRadioButton  *paxisDeg;
    QCheckBox     *paxisShow;
    QzPortFrame   *paxisLineFrame;
    QxChooseColorButton *paxisColor;
    QSpinBox      *paxisLinewidth;
    QzPortFrame   *paxisLabelFrame;
    QLineEdit     *paxisLabel;
    QComboBox     *paxisLabelPosMenu;
    QxChooseColorButton *paxisLabelColor;

    QzPortFrame   *errorbarRangeFrame;
    QLabel        *errorbarRange;
    QzPortFrame   *errorbarTypeFrame;
    QComboBox     *errorbarTypeMenu;
    QxChooseColorButton *errorbarColor;
    QzPortFrame   *errorbarLineFrame;
    QComboBox     *errorbarLineMenu;
    QSpinBox      *errorbarLinewidth;
    QzPortFrame   *errorbarMarkerFrame;
    QComboBox     *errorbarMarkerLineMenu;
    QSpinBox      *errorbarMarkerLinewidth;
    QxChooseColorButton *errorbarMarkerColor;
    QzPortFrame   *errorbarLabelFrame;
    QLineEdit     *errorbarLabel;

    QzPortFrame   *latticeRangeFrame;
    QLabel        *latticeRange;
    QzPortFrame   *latticeTypeFrame;
    QComboBox     *latticeTypeMenu;
    QzPortFrame   *latticeGammaFrame;
    QxFullSlider  *latticeGamma;
    QzPortFrame   *latticeOptionsFrame;
    QCheckBox     *latticeGlobalColormap;

    QzPortFrame   *colormapFrame;
    QLabel        *colormapLength;
    QPixmap       *colormapPixmap;
    QLabel        *colormapPic;
    QzPortFrame   *colormapRangeFrame;
    QLineEdit     *colormapMinRange, *colormapMaxRange;
    QCheckBox     *colormapAuto;
    QzPortFrame   *colormapEditFrame;
    QPushButton   *colormapReverse;

    QPalette       activeCols, inactiveCols;

    int            currTab;

    bool           callApply;

    static void portChanged(const QzPortFrame &pf, void* userdata,
                            QWidget* sender);

    void switchAttrBox(QGroupBox *newAttrBox, PzBaseObject* obj);

protected slots:

    virtual void accept();
    virtual void apply();
    virtual void reject();

    virtual void objSingleClicked(QTreeWidgetItem* item);

    virtual void objDoubleClicked(QTreeWidgetItem* item);

    void showObject(bool showit);

    void menuCB(QAction* action);

    void axisSelected(int tabNo);

    void delta_or_tick();

protected:

    virtual void keyPressEvent (QKeyEvent* e);

    McDArray<PzBaseObject*> objectlist;

public:

    enum cbResult { OK=2, APPLY=1, CANCEL=0 };

    enum actionState { copyOK=0x01, cutOK=0x02, pasteOK=0x04, appendOK=0x08 };

    /// Constructor
    QzObjectEditor(QWidget* parent, const char* name);

    /// Destructor
    ~QzObjectEditor();

    ///
    void setEditorCallback(QzObjectEditorCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetEditorCallback() { editorCallback = NULL; }

    ///
    void setSelectedCallback(QzSelectedCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetSelectedCallback() { selectedCallback = NULL; }

    ///
    void setShowitCallback(QzShowitCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetShowitCallback() { showitCallback = NULL; }

    ///
    void setMenuCallback(QzMenuCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetMenuCallback() { menuCallback = NULL; }

    /// tells the editor the state of the last action
    void setActionState(int state);

    /// builds the list of objects to be shown in a ListView
    void buildObjectList(PzPlotGroup* group, PzBaseObject* selObj,
                         QTreeWidgetItem* parent = NULL);

    /// shows attributes of base object (for dummy usage!)
    void showAttr(PzBaseObject* obj);

    /// shows attributes of PzPlotGroup object
    void showAttr(PzPlotGroup* obj);

    /// shows attributes of PzCurve object
    void showAttr(PzCurve* obj);

    /// shows attributes of PzLegend object
    void showAttr(PzLegend* obj);

    /// shows attributes of PzMarkerline object
    void showAttr(PzMarkerline* obj);

    /// shows attributes of PzAnnotation object
    void showAttr(PzAnnotation* obj);

    /// shows attributes of PzGrid object
    void showAttr(PzGrid* obj);

    /// shows attributes of PzPlotArea object
    void showAttr(PzPlotArea* obj);

    /// shows attributes of PzAxis object
    void showAttr(PzAxis* obj);

    /// shows attributes of PzPolarAxis object
    void showAttr(PzPolarAxis* obj);

    /// shows attributes of PzErrorbar object
    void showAttr(PzErrorbar* obj);

    /// shows attributes of PzLattice object
    void showAttr(PzLattice* obj);

    /// shows attributes of PzColormap object
    void showAttr(PzColormap* obj);

    /// returns attributes of object
    void applyAttr(PzCurve* obj);

    /// returns attributes of object
    void applyAttr(PzLegend* obj);

    /// returns attributes of object
    void applyAttr(PzMarkerline* obj);

    /// returns attributes of object
    void applyAttr(PzAnnotation* obj);

    /// returns attributes of object
    void applyAttr(PzGrid* obj);

    /// returns attributes of object
    void applyAttr(PzPlotArea* obj);

    /// returns attributes of object
    void applyAttr(PzAxis* obj);

    /// returns attributes of object
    void applyAttr(PzPolarAxis* obj);

    /// returns attributes of object
    void applyAttr(PzErrorbar* obj);

    /// returns attributes of object
    void applyAttr(PzLattice* obj);

    /// returns attributes of object
    void applyAttr(PzColormap* obj);
};

#endif

/// @}

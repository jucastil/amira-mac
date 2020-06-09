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

/// @addtogroup hxcolormapeditor hxcolormapeditor
/// @{
#ifndef QX_OLD_COLORMAP_EDITOR_H
#define QX_OLD_COLORMAP_EDITOR_H

#include <hxcolormapeditor/HxColormapEditorWinDLLApi.h>

#include <qdialog.h>
#include <qstring.h>

class QxColorchart;
class QxFullSlider;
class QLabel;
class QMenu;
class QCheckBox;
class QGridLayout;
class HxColormap256;
class HxData;
class QxColoredSlider;
class QxColorbuttons;
class QxColorbar;
class HxColorStack;
class QResizeEvent;
class QAction;

///
class HXCOLORMAPEDITOR_API QxOldColormapEditor : public QDialog
{
    Q_OBJECT

 public: 
    /// Constructor
    QxOldColormapEditor(int stacksize = 10, QWidget *parent=0,
        const char *name=0, bool modal=FALSE, Qt::WFlags f=0);
  
    /// Destructor
    ~QxOldColormapEditor();
    /// Start editing the colormap
    virtual void startEditing(HxData *data);

 protected:
    typedef enum {
        pushNormal = 0,
        preparePush,
        pushPrepared,
        freePrepared
    } TPush;
    
    typedef enum {
        undoing = 0,
        redoing
    } TPop;
    
    
    /// Initalize data
    virtual void initData(int stacksize);

    /// Build and dress the whole widget tree
    virtual void buildAndDressWidgetTree();

    /// Making the scale labels
    virtual void makeScaleString();

    /// Posting an error
    virtual void postError(const char *message);

    /// Pushing a colormap state on the stack
    virtual void push(TPush which);

    /// Undoing / Redoing a modification
    virtual void pop(TPop why);

    /// Invoked editor is closed via window close button
    virtual void closeEvent(QCloseEvent *);

    /// Invoked when user changes to RGB color model
    void modeRGB(int doit);

    /// Invoked when user changes to HSV color model
    void modeHSV(int doit);

    /// Repaints colorchart, colorbar, and colorbuttons widget.
    void repaintAll();

    /// Pops up dialog for discretizing the colormap
    void makeSteps();

    /// Pops up dialog for computing alpha curve.
    void makeAlpha();

    /// Set the color cell label acording to the color index @c cellIndex
    void setColorCellLabel(int cellIndex);

    HxColormap256  *cmap;               // current (working) color map
    HxColormap256  *immediatecmap;      // colormap which was passed to
    HxColormap256  *oldcmap;            // copy of colormap before editing

    int         length;                 // size of each color map
    float       min;                    // minimum of the colormap
    float       max;                    // maximum of the colormap
    float       dScale;                 // (max - min) / (length - 1)

    int         mode;                   // color space
    int         focus;                  // focus
    int         changed;                // changed flag for the stack
    int         lastActionWasPushing;
    int         immediate;              // immediate mode or not

    // Widget labels
    QString    scaleString[2][6];       // text for scales in each mode
    QString    snapString[2][6];        // text for snap menu items

    // Menu / Actions
    QMenu *editMenu;
    QMenu *modeMenu;
    QMenu *brushMenu;
    QMenu *extrasMenu;
    
    QAction* undoAction;//6
    QAction* redoAction;//7
    QAction* deleteAction;//8

    QAction* rgbAction;//1
    QAction* hsvAction;//2
    QAction* showAlphaAction;//3
    QAction* immediateAction;//4

    QAction* squareAction;//1
    QAction* circleAction;//2
    QAction* diamondAction;//3

    QAction* snapRedAction;//0
    QAction* snapGreenAction;//1
    QAction* snapBlueAction;//2
    QAction* snapAlphaAction;//3
    QAction* snapAction;//4
    QAction* snapAllAction;//5

    QAction* grayRampAction;//1
    QAction* hueRampAction;//2
    QAction* hotIronAction;//3
    QAction* glowAction;//4
    QAction* stepsAction;//5
    QAction* alphaAction;//6
    QAction* interpolAction;//7

    QLabel*      WScaleLabels[4];       // Labels left to the sliders
    QLabel*      WCellLabel;            // Label indicating color cell id

    // Color Objects
    QxColoredSlider *sliders[7];
    QxColoredSlider *actualSliders[4];
    QCheckBox       *checkBoxes[4];
    QxColorbar      *colorbar;
    QxColorbuttons  *colorbuttons;
    QxColorchart    *colorchart;
    HxColorStack    *undostack;
    HxColorStack    *redostack;

    QxFullSlider*   numStepsSlider;    
    QxFullSlider*   brightnessSlider;
    QxFullSlider*   gammaSlider;

 signals:
    void exit(bool ok);
	void applyClicked();
	void valueChanged();

 protected slots:
    void okCB();
    void applyCB();
    void cancelCB();
    void helpCB();

    void undoCB();
    void redoCB();
    void snapCB(QAction*);
    
    void immediateChangedCB();
    void setBrush(QAction*);
    void modeRGB();
    void modeHSV();
    void extras(QAction*);
    void makeStepsCompute();
    void makeAlphaCompute();
    void editMenuShow();
    void editMenuHide();
    void handleCheckBoxes();
    
    void colorbuttons_focusSetCB(int);
    void colorbuttons_knotSetCB(int);
    void colorbuttons_knotUnsetCB(int);
    void colorbuttons_colormapChanged();
    void colorchart_colormapChanged(int,int);
    void colorchart_startMovingCB();
    void colorchart_finishMovingCB();
    
    void slider0_valueChangedCB(float);
    void slider1_valueChangedCB(float);
    void slider2_valueChangedCB(float);
    void slider3_valueChangedCB(float);
    
    void sliders_startMovingCB();
    void sliders_finishMovingCB();

 public slots:
    void setFocusAndColor(int i, float* rgba);
};

#endif // QX_COLORMAP_EDITOR_H


/// @}

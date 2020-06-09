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
#ifndef EX_VIEWER_CONTROL_H
#define EX_VIEWER_CONTROL_H

#include "ExNotifiable.h"

#include <mclib/McVec2f.h>
#include <mclib/McString.h>

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QWidget>
#include <QLabel>

#include "QxPopupMenuComboBox.h"


class ExBaseViewer;


class ExViewerControl
:   public QWidget
,   public ExNotifiable
{
    Q_OBJECT


public:

    ExViewerControl( ExBaseViewer * inViewer );

    virtual void notified( const ExNotification& notification );
    
    void setupUi( QWidget * ExViewerControlBase );


public slots:

    void slot_activateViewer();

    void slot_setDataWindowCenter( const QString & s );
    void slot_setDataWindowWidth ( const QString & s );
    void slot_setDataWindow( McVec2f & dw );
    void slot_updateWindowLevelUI();
    void slot_dataWindowListStateToUI();
    void slot_setPredefinedDataWindow();


    void slot_updateSliceRenderModeUI();

    void slot_setZoom( const QString & s );
    void slot_updateZoomUI();

    void slot_setThickness( const QString & newThickness );
    void slot_updateThicknessActions();
    void slot_updateThicknessUI();


    void slot_updateFullUI();

    void slot_actionTriggered();


private:

    ExBaseViewer          * mViewer;

    // render mode menu
    QAction               * mActionModeTHINMPR;
    QAction               * mActionModeMAXIP;
    QAction               * mActionModeMINIP;
    QAction               * mActionModeAVRGE;

    // zoom menu
    QAction               * mActionZoomFIT_WIDTH;
    QAction               * mActionZoomFIT_HEIGHT;
    QAction               * mActionZoomFIT_ALL;
    QAction               * mActionZoom16_1;
    QAction               * mActionZoom8_1;
    QAction               * mActionZoom4_1;
    QAction               * mActionZoom2_1;
    QAction               * mActionZoom1_1;
    QAction               * mActionZoom1_2;
    QAction               * mActionZoom1_4;
    QAction               * mActionZoom1_8;
    QAction               * mActionZoom1_16;

    // thickness menu
    QAction               * mActionThickThin[8];

    QHBoxLayout           * wHBoxLayout;
    QxPopupMenuLineEdit   * wLabelC;
    QxPopupMenuLineEdit   * wWindowCenter;
    QxPopupMenuLineEdit   * wLabelW;
    QxPopupMenuLineEdit   * wWindowWidth;
    QxPopupMenuComboBox   * wDataWindowPresets;
    QxPopupMenuComboBox   * wSliceRenderMode;
    QxPopupMenuComboBox   * wThickness;
    QxPopupMenuComboBox   * wZoom;
    QSpacerItem           * wSpacerItem;

    QLabel                * wSeparator1;
    QLabel                * wSeparator2;
    QLabel                * wSeparator4;
    QLabel                * wSeparator5;


    McDArray<McString> mDwNames;
    McDArray<McVec2f>  mDwRanges;
};

#endif

/// @}

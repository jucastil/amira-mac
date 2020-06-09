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

/// @addtogroup hxalign hxalign
/// @{
#ifndef QX_VIEW_ALIGN_SLICES_ORTHOGONAL_COMMON_TOOLBAR_H
#define QX_VIEW_ALIGN_SLICES_ORTHOGONAL_COMMON_TOOLBAR_H


#include <qlabel.h>
#include <qtoolbutton.h>
#include <QToolBar>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qvalidator.h>
#include <hxcore/QxFullSlider.h>

class QxAlignSlices;
class QxOrthoViewManager;

/** \class QxViewAlignSlicesOrthogonalCommonToolBar QxViewAlignSlicesOrthogonalCommonToolBar.h "hxalign/QxViewAlignSlicesOrthogonalCommonToolBar.h"
 *  \brief This class provides the user interface elements to control both the coronal and the sagittal orthogonal views of the alignment editor.
 *
 *  This class provides the user interface elements to control both the coronal and the sagittal orthogonal views of the alignment editor. 
 *  An object of this class  should be created when an orthogonal view is created (QxViewAlignSlicesOrthogonal) 
 *  and an object of this class does not yet exist. It should be deleted when the last orthogonal view is deleted. 
 *  This class provides the following user interface elements:
 *  - lineedit's to provide a minimum and a maximum z-value to display
 *  - update button to update the images in the ortho-windows
 *  - a checkbox for turning automatic updating on/off
 */

class QxViewAlignSlicesOrthogonalCommonToolBar : public QToolBar {

  Q_OBJECT

  public:
    /** Constructor */
    QxViewAlignSlicesOrthogonalCommonToolBar(QxOrthoViewManager* orthoMan, QxAlignSlices *parent = 0, const char *name = 0);
    /** Destructor */
    ~QxViewAlignSlicesOrthogonalCommonToolBar();
    
    void setAutoUpdate(bool value);
    bool getAutoUpdate() const;

    void setShowZRange(bool show);
    void setZRange(int r);

    void setSagittalSliderRange(const int min, const int max);
    void setCoronalSliderRange(const int min, const int max);

    void showSagittal (bool show);
    void showCoronal (bool show);

    void setSagittalSliceNumber(int sn) {sagittalSlider->setValue(float(sn));};
    void setCoronalSliceNumber(int sn) {coronalSlider->setValue(float(sn));};

    void setZoomLabel(const char* str);

  public slots:
    void autoCheckBoxChange(bool);
    void updateView();
    void sagittalSliceNumberChange(float x);
    void coronalSliceNumberChange(float x);
    void zoomIn();
    void zoomOut();
    void showZRangeCheckBoxChange(bool);
    void zRangeChange();

  signals:
    void updateViewSignal();

  private:
    /** Automatic update after each alignment operation */
    bool autoUpdate;

    /** Show only a window of zRange slices above and below the current slice */
    bool showZRange;
    int zRange;

    QxOrthoViewManager* orthoViewManager;

  protected:
    QLabel* autoUpdateLabel;
    QCheckBox* autoCheckBox;
    QToolButton* updateViewButton;
    QCheckBox* showZRangeCheckBox;
    QLabel* zRangeLabel;
    QLineEdit* zRangeEdit;

    QxFullSlider* sagittalSlider;
    QxFullSlider* coronalSlider;
    QLabel* sagittalLabel;
    QLabel* coronalLabel;
    QLabel* zoomLabel;
    QToolButton* zoomInButton;
    QToolButton* zoomOutButton;

    QAction* m_sagittalLabelAction;
    QAction* m_sagittalSliderAction;
    QAction* m_coronalLabelAction;
    QAction* m_coronalSliderAction;

};

#endif


/// @}

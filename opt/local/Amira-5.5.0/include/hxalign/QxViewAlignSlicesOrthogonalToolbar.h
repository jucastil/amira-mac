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
#ifndef QX_VIEW_ALIGN_SLICES_ORTHOGONAL_TOOLBAR_H
#define QX_VIEW_ALIGN_SLICES_ORTHOGONAL_TOOLBAR_H

#include <q3groupbox.h>
#include <qlabel.h>
#include <hxcore/QxFullSlider.h>
#include <qtoolbutton.h>
#include <QToolBar>
//#include "QxAlignSlices.h"


class QxAlignSlices;
class QxOrthoViewManager;

/** \class QxViewAlignSlicesOrthogonalToolbar QxViewAlignSlicesOrthogonalToolbar.h "hxalign/QxViewAlignSlicesOrthogonalToolbar.h"
 *  \brief This class provides a toolbar containing user interface elements controlling the associated
 *         orthogonal view (QxViewAlignSlicesOrthogonal).
 *
 *  This class provides a toolbar containing user interface elements controlling the associated orthogonal 
 *  view (QxViewAlignSlicesOrthogonal). An object of this class needs to be created together with a 
 *  QxViewAlignSlicesOrthogonal and should have the same orientation. The following user interface elements
 *  are provided:
 *  - a slider + lineedit to change the currently displayed slice
 *  - buttons to zoom in and zoom out
 *  Settings that hold for both the sagittal view and the coronal view can be changed with QxViewAlignSlicesOrthogonalCommonToolbar.
 */

class QxViewAlignSlicesOrthogonalToolbar : public QToolBar {

  Q_OBJECT

  public:

    /** Constructor */
    QxViewAlignSlicesOrthogonalToolbar(int orient, const int* latDims, QxOrthoViewManager* orthoMan, QxAlignSlices *parent = 0, const char *name = 0);
    /** Destructor */
    ~QxViewAlignSlicesOrthogonalToolbar();

    /** Set the slice number */
    void setSliceNumber(float sn);
    void setZoomLabel(const char* str);

  public slots:
    /** Calculate new zoom factor after "zoom in" button has been pressed and signal the orthoview image windows */
    void zoomIn();
    /** Calculate new zoom factor after "zoom out" button has been pressed and signal the orthoview image windows */
    void zoomOut();
    void sliceNumberChange(float x);
    void setUseMaxIntProjection(bool val);

  signals:
    void sliceNumberChanged(float);
    void zoomChanged(float);
    void updateViewSignal();

  private:
      /** orientation: SAGITTAL or CORONAL */
      int orientation;
      /** Input data dimensions */
      const int* dims;

      QxOrthoViewManager* orthoViewManager;

  protected:
    QxFullSlider* slSlider;
    QLabel* orientLabel;
    QLabel* zoomLabel;
    
    /** zoom factor */
    float zoom;
};

#endif




/// @}

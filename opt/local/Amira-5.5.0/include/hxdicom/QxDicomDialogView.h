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

/// @addtogroup hxdicom hxdicom
/// @{
#ifndef QX_DICOM_DIALOG_VIEW_H
#define QX_DICOM_DIALOG_VIEW_H


#include <hxdicom/HxDicomWinDLLApi.h>

#include <hxdicom/QxDicomListView.h>
#include <hxdicom/HxDicomImage.h>
#include <hxdicom/HxDicomImageStack.h>

#include <qsplitter.h>
#include <q3textview.h>
#include <qlabel.h>
#include <qevent.h>

#include <hxdicom/dynamicOnOff.h>


// DICOM dialog view (load info and list of images)
class HXDICOM_API DicomDialogView : public QSplitter
{

    Q_OBJECT

public:

    DicomDialogView (QWidget *parent = 0, const char *name = 0);
   ~DicomDialogView (void) {}

    void loadImages (const McDArray<HxDicomImage *> &images);

    bool accept (McDArray<HxDicomImageStack *> &stacks);

    int numLoadableStacksSelected();

#ifdef DYNAMIC
    bool asDynamic;
#endif
    bool asTimeSeries;

    // If this variable is set, only uniform 3D volumes can be loaded
    bool mForceUniform;
    // If this variable is set, only selected stacks will be loaded
    bool mForceSelected;

signals:

    void loadOptionsRequest (void);
    void dicomParameterRequest (bool);
    void anonymizeDicomParameters (bool);
    void parameterViewRequest (void);
    void imagesAreLoaded (const QString &);
    void stacksAreSelected (int);

public slots:
    void saveSettings();
    void resetSettings();

protected slots:

    void forceUniformRequest (void);
    void asDynamicRequest(bool); 
    void asTimeSeriesRequest(bool); 
    void updateDicomInfo(const QString &);
    void updateStackInfo(const QString &);
    void updateStackInfo(int);
    void updateStackInfo(void);

private:

    QLabel          *theDicomInfo;
    Q3TextView       *theStackInfo;
    DicomListView   *theList;
};


#endif

/// @}

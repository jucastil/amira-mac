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
#ifndef QX_DICOM_DIALOG_H
#define QX_DICOM_DIALOG_H

#include <hxcore/HxMain.h>
#include <hxcore/QxDialog.h>
#include <hxcore/ThreadNegotiator.h>

#include <mclib/McDArray.h>

#include <dicom/dicom.h>

#include <hxdicom/HxDicomWinDLLApi.h>
#include <hxdicom/dynamicOnOff.h>

class DicomMenuBar;
class DicomDialogView;
class HxDicomImage;
class HxDicomImageStack;

// the dialog widget itself (menu, dialog, buttons)
class HXDICOM_API DicomDialog : public QxDialog, public ForkedObject
{

    Q_OBJECT

public:
    DicomDialog ();

    ~DicomDialog (void) {}

    void setImages(const McDArray<HxDicomImage *> *images);
    void setStacks(McDArray<HxDicomImageStack *> *stacks);
#ifdef DYNAMIC
    bool getAsDynamic();
    void setAsDynamic(bool val);
#endif
    bool getAsTimeSeries();

    void exportImageStacks();

    void setTitle(char const *title) {mTitle = title;}
protected slots:

    // overloaded QxDialog method
    void accept (void);
    // slot for reacting on selection changes, e.g. enable/disable OK button 
    void stackSelectionChanged(int);

protected:
    virtual void putData();
    virtual int exec();
    virtual void getData() {}

private:

    // dialog content and result
    const McDArray<HxDicomImage *>  *theImages;
    McDArray<HxDicomImageStack *>   *theStacks;

    DicomMenuBar      *theMenuBar;
    DicomDialogView   *theDialog;

    QString mTitle;

public:
    // if this is set, certain features of the dicom load dialog are disabled
    static void setLoaderLite(bool onOff);
};

class QxDicomDialogNegotiator : public ThreadNegotiator 
{
public:
    ForkedObject *create() {return new DicomDialog;}
};

#endif

/// @}

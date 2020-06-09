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

/// @addtogroup hximio hximio
/// @{
#ifndef QX_IMREAD_DIALOG_H
#define QX_IMREAD_DIALOG_H

#include <QDialog>

#include <mclib/McString.h>

#include <hximio/ui_QxImReadDialogBase.h>
#include <hxcore/ThreadNegotiator.h>

#include "HxImIOWinDLLApi.h"

class QxLineEdit;

// Channel conversion dialog
class HXIMIO_API QxImReadDialog : public QDialog, public Ui::QxImReadDialogBase, public ForkedObject
{
    Q_OBJECT

  public:

    enum ConvertMethod {
        CONVERT_MAXIMUM=0,
        CONVERT_LUMINANCE=1,
        CONVERT_CHANNEL1=2,
        CONVERT_CHANNEL2=3,
        CONVERT_CHANNEL3=4,
        CONVERT_CHANNEL4=5,
        CONVERT_CHANNEL5=6,
        CONVERT_CHANNEL6=7,
        CONVERT_CHANNEL7=8,
        CONVERT_CHANNEL8=9,
        CONVERT_COLORFIELD=10,
        CONVERT_ALL_CHANNELS=11,
        NUM_CONVERT_METHODS=12
    };

    QxImReadDialog(QWidget *parent=0, const char *name=0,
        bool modal=TRUE, Qt::WFlags f=0);

    void setDims(
        int dims[3],
        int numberOfChannels,
        const char* proposedLabel,
        int colormapFound=0,
        float* bbox=0,
        int supportAllChannels=0,
        int numberOfTimeSteps=1);

    int getConvertMethod();

    void getObjectLabel(McString& label);
    void setObjectLabel(const char* label);

    void getBox(float* box);

  protected slots:
    void boundingBoxMode();
    void voxelSizeMode();

  protected:
    virtual void putData();
    virtual int exec();
    virtual void getData();

    float mBbox[6];
    int mDims[3];
    int mNumberOfChannels;
    McString mLabel;
    int mColormapFound;
    int mSupportAllChannels;
    int mNumberOfTimeSteps;
    int mConvertMethod;

    QxLineEdit* bbTxt[6];
    QString channelItem[NUM_CONVERT_METHODS];

    void getBox(float* box, int mode);
};

class QxImReadDialogNegotiator : public ThreadNegotiator 
{
public:
    ForkedObject *create() {return new QxImReadDialog;}
};

#endif // QX_IMG_READ_DIALOG_H

/// @}

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

/// @addtogroup hxfield hxfield
/// @{
#ifndef QX_READ_RAW_DIALOG_H
#define QX_READ_RAW_DIALOG_H

#define READ_RAW_NTEXTFIELDS 10
#define READ_RAW_NRADIOBUTTONS 4
#define READ_RAW_NCOMBOBOXES 2

#include <hxfield/ui_QxReadRawDialogBase.h>
#include "HxReadRawDialog.h"

#include <mclib/McPrimType.h>

// GUI class used by HxReadRawDialog
class QxReadRawDialog : public QDialog, public Ui::QxReadRawDialogBase 
{
    Q_OBJECT
    
public:

    QxReadRawDialog (QWidget *parent=0, const char *name=0,
        bool modal=FALSE, Qt::WFlags f=0);
    void getDims(int* dims);
    int getHeaderBytes();
    void getMinMax(float*);
    McPrimType getPrimType();
    int getNDataVar();
    HxReadRawDialog::ContentTypeFlag getContentTypeFlag();
    int isBigEndian();
    int isXFastest();
    int isNoWarning();
    void setNumFiles(int n);
    void setFilesize(mcint64 s);

protected slots:
    void modeChanged();
    void sizeChanged ();

protected:
    QSpinBox* dimsTxt[3];
    QxLineEdit* bBoxTxt[6];
    
    void getMinMax(float*, int mode);

	mcint64 mFileSize;
};

#endif // QX_READ_RAW_DIALOG_H

/// @}

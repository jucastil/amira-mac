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

/// @addtogroup hxcore hxcore
/// @{
#ifndef QX_DIALOG_H
#define QX_DIALOG_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <QDialog>

class QPushButton;
class QHBoxLayout;

/// DEPRECATED: use Qt designer ui in addition to a QDialogButtonBox 
class HXCORE_API QxDialog : public QDialog 
{
    Q_OBJECT
    
public: 
    enum {
        OkButton = 1 << 0,
        ApplyButton = 1 << 1,
        ResetButton = 1 << 2,
        CancelButton = 1 << 3,
        HelpButton = 1 << 4
    };
    QxDialog (QWidget *parent=0, const char *name=0,
        bool modal=FALSE, Qt::WFlags f=0);
    QHBoxLayout* createButtons (int ids=OkButton|CancelButton, int spacing=5,
        int alignment=Qt::AlignRight);

    virtual void show (); 
    virtual int exec ();

protected slots:
    virtual void accept();
    virtual void apply();
    virtual void reset();
    virtual void reject();
    virtual void help();

protected:
    QPushButton *okButtonWidget() const;
    QPushButton *applyButtonWidget() const;
    QPushButton *resetButtonWidget() const; 
    QPushButton *cancelButtonWidget() const;
    QPushButton *helpButtonWidget() const;

private:
    QPushButton *theOkButtonWidget,
        *theApplyButtonWidget,
        *theResetButtonWidget, 
        *theCancelButtonWidget,
        *theHelpButtonWidget;
};

// callback function prototypes
typedef void QxDialogCB(void *userData, const QxDialog &colEd);

#endif // QX_DIALOG_H

/// @}

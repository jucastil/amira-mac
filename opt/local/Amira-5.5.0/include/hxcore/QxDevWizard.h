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
#ifndef QX_DEV_WIZARD_H
#define QX_DEV_WIZARD_H

#include <hxcore/ui_QxDevWizardDialogBase.h>

#include "HxAmiraWinDLLApi.h"

#include <mclib/McString.h>

class HXCORE_API QxDevWizard : public QDialog, public Ui::QxDevWizardDialogBase
{
    Q_OBJECT

  public:

    QxDevWizard();
    ~QxDevWizard();

    virtual void show();

    int createAmiraLocal(const char* amiraLocalDir, bool inDirsOnly=0 );
    int setAmiraLocal(const char* amiraLocalDir);
    bool isAmiraRoot( const char * inDir );
    int copyDemoPackages(const char* packageDir);
    int addNewPackage(const char* packageDir);
    int addNewModule(const char* packageDir, const char* name, int isCompute);
    int addNewReader(const char* packageDir, const char* name);
    int addNewWriter(const char* packageDir, const char* name);

  private slots:

    void closeButtonClicked();
    void okButtonClicked();
    void radioButtonClicked();
    void componentButtonClicked();
    void browseButtonClicked();
    void unsetButtonClicked();

  private:

    QString amiraLocal;

    QWidget* stack1;
    QWidget* stack2;
    QWidget* stack3;
    QWidget* stack4;
    QWidget* stack5;
    QWidget* stack6;
    QWidget* stack7;
    QWidget* stack8;

    void buildStack1();
    void buildStack2();
    void buildStack3();
    void buildStack4();
    void buildStack5();
    void buildStack6();
    void buildStack7();
    void buildStack8();
    void raiseStack4();
    void raiseStack5();
    void raiseStack7();
    void raiseStack8();

    void updatePackageBox(QComboBox* box);

    void scanDirForDirs( McString & inDir, McDArray<McString> & outDirsFound );
    bool dirHasPackageFile( McString & inDir );
};

#endif // QX_DEV_WIZARD_H

/// @}

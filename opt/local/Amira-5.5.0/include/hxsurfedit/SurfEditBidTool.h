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

/// @addtogroup hxsurfedit hxsurfedit
/// @{
#ifndef SURF_EDIT_BID_TOOL_H
#define SURF_EDIT_BID_TOOL_H

#include <qobject.h>
#include <QHash>
#include <QListWidget>
#include <mclib/McString.h>
#include <mclib/McHandable.h>
#include "SurfEditTool.h"

class QDialog;
class QLabel;
class QPushButton;
class QComboBox;
class QSpinBox;
class QLineEdit;
class QGroupBox;
class QxChooseColorButton;

/// Tool for manipulating boundary ids.
class SurfEditBidTool : public SurfEditTool {

  Q_OBJECT

  public:
    SurfEditBidTool(HxSurfEdit* surfEdit);

    ~SurfEditBidTool();

    virtual void activate(int);

    virtual void surfaceChanged();

    virtual void selectionChanged();

    static void setBoundaryId(HxSurface*, McBitfield&, int id);

    static void printText(char* buffer, int id, HxParamBundle*);

    static int currentItemIdFromText(const QString& text);

  public slots:
    void updateSelection();
    void addToSurface();
    void removeBoundaryId();
    void addNewBoundaryId();
    void editBoundaryId();
    void checkId(int);
    void set();
    void showHelp();

  protected:
    QDialog* dialog;
    QListWidget* surfaceBids;
    QListWidget* databaseBids;
    QLabel* infoLabel;
    QPushButton* editBtn;
    QPushButton* removeBtn;
    QPushButton* setBtn;
    QHash<int, int> triangleCount;

    QDialog* editDialog;
    QGroupBox* groupBox;
    QSpinBox* idSpinBox;
    QLineEdit* infoEdit;
    QComboBox* typeCombo;
    QxChooseColorButton* colorBtn;
    QPushButton* okBtn;
    int editId;
    int activeBox;

    void updateBox();
    int currentItem(QListWidget*);    
    int currentItemId(QListWidget*);

    void computeTriangleCount();
    void createDialog(QWidget* parent);
    void createEditDialog(QWidget* parent);
};

#endif

/// @}

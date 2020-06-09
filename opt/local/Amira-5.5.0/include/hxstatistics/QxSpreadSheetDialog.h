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

/// @addtogroup hxstatistics hxstatistics
/// @{
#ifndef QX_SPREAD_SHEET_DIALOG_H
#define QX_SPREAD_SHEET_DIALOG_H

#include <hxstatistics/ui_QxSpreadSheetDialogBase.h>
#include <hxstatistics/HxStatisticsWinDLLApi.h>

#include <mclib/McDArray.h>

#include <QItemSelection>

class QTabWidget;
class HxSpreadSheet;
class HxSpreadSheetEditor;

class HXSTATISTICS_API QxSpreadSheetWidget : public QWidget
{
    Q_OBJECT
public:
    QxSpreadSheetWidget(HxSpreadSheetEditor* editor=0, QWidget *parent=0, const char* name=0);
    ~QxSpreadSheetWidget();

    void setSpreadSheet(HxSpreadSheet* inSpreadSheet);

    int getSelection(McDArray<int>& rowId);
    void setSelection( const McDArray<int>& rowId, int tableIdx=0);

    HxSpreadSheetEditor* getEditor();

public slots:

    virtual void applyChanges();

    void slotRestoreOrder();
    void slotCopy();
    void slotSelectionChanged();

private:
    QTabWidget *mTabWidget;

    HxSpreadSheetEditor* mEditor;
    HxSpreadSheet *mSpreadSheet;
};

class HXSTATISTICS_API QxSpreadSheetDialog :  public QDialog, public Ui::SpreadSheetDialog
{
    Q_OBJECT

public:

    QxSpreadSheetDialog(HxSpreadSheetEditor* editor = 0, QWidget* parent = 0, const char* name = 0, bool modal = FALSE);
    ~QxSpreadSheetDialog(void);

    void setSpreadSheet(HxSpreadSheet* inSpreadSheet);

    int getSelection(McDArray<int>& rowId);
    void setSelection( const McDArray<int>& rowId, int tableIdx=0);

public slots:

    virtual void accept();
    virtual void reject();

    void slotRestoreOrder();

signals:
    void aboutToDelete();

private:
    QxSpreadSheetWidget *mSpreadSheetWidget;

};


#endif //end QX_SPREAD_SHEET_DIALOG_H

/// @}

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
#ifndef QX_PARAMDIALOG_H
#define QX_PARAMDIALOG_H

#include <QValidator>
#include <QTreeWidgetItem>

#include <hxcore/ui_QxParamDialogBase.h>

#include <mclib/McColor.h>

#include <hxcore/HxAmiraWinDLLApi.h>
#include <amiramesh/HxParamBundle.h>

class QxParamDialog;
class QxParamSearchDialog;

// Avoid user to input a name not beginning with a letter.
class HXCORE_API QxMaterialValidator : public QValidator
{
public:
    QxMaterialValidator( QObject * parent, const char *name = 0 ): QValidator( parent){}
    QValidator::State validate( QString & str, int & pos) const;
};

class HXCORE_API QxParamDialog : public QDialog, public Ui::QxParamDialogBase
{
    Q_OBJECT

  public:
    // QxParamDialog(int apply=0, int databaseMenu=0, int modal=0);
    QxParamDialog(QWidget* parent=0, int apply=0, int databaseMenu=0, int modal=0);

    ~QxParamDialog();

    const HxParamBundle& getBundle() const;

    void setBundle(HxParamBundle* bundle, const char* name=0);
    void enableApply(bool on);
    void enableDatabaseMenu(bool on);
    bool hasDatabaseMenu();
    static QxParamDialog* getDialog();

  signals:
    void exit(bool ok);
    void dataChanged();

  protected slots:
    void accept();
    void apply();
    void reject();
    void changeColor();
    void updateHeaderSize(int section, int oldSize, int newSize);
    void updateItem();
    void selectionChanged();
    void popupContextMenu(const QPoint &);
    void help();
    void search();
    void startSearch();
    void load();
    void import();
    void restoreDefault();
    void saveAs();
    void removeAll();
    void setDefaultDatabase();
    void setSystemDefault();
    void cut();
    void copy();
    void paste();
    void configureEditMenu();
  private:
    int isColor(const HxParameter& param);
    McColor getColor(const HxParameter& param);
    void setColor(HxParameter& param, const McColor& color);

    int colorDlgOpened;
    class Param : public QTreeWidgetItem {
      public:
        Param(HxParamBase* p, int i, QTreeWidgetItem* parent)
            : QTreeWidgetItem(parent),paramBase(p),idx(i) { }

        Param(HxParamBase* p, int i, QTreeWidget* parent)
            : QTreeWidgetItem(parent),paramBase(p),idx(i) { }

        virtual void setData ( int column, int role, const QVariant & value );
        virtual QVariant data ( int column, int role ) const;
        virtual bool operator< ( const QTreeWidgetItem & other ) const;

        HxParamBase* paramBase;
        int idx;
    };

    HxParamBundle bundle;
    HxParamBundle* originalBundle;

    QMenu * databaseMenu;
    QAction *cutAction, *copyAction, *pasteAction;

    QxParamSearchDialog* searchDlg;

    void insert(Param* parent, HxParamBundle* b);
    void updateAdd(Param* parent, HxParamBundle* b);
    void updateRemove(Param* parent, HxParamBundle* b);
    virtual void closeEvent(QCloseEvent* e);
    void copyToClipboard(HxParamBase*);

};

#endif

/// @}

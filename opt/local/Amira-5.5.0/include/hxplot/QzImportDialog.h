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

/// @addtogroup hxplot hxplot
/// @{
#ifndef QZ_IMPORTDIALOG
#define QZ_IMPORTDIALOG

#include <hxplot/PzPlotWinDLLApi.h>

#include <QWizard>
#include <QString>
#include <QPixmap>
#include <QLabel>

#include <mclib/McString.h>
#include <mclib/McDArray.h>

#ifdef _WIN32
#include <windows.h>
#endif

class QzImportDialog;
struct PzDataImportRules;

class QWizardPage;
class QTableWidget;
class QMenuBar;
class QLabel;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QSpinBox;
class QButtonGroup;
class QGroupBox;
class QRadioButton;
class QTabBar;
class QPixmap;
class QButton;
class QMenu;
class QxChooseColorButton;
class QxFullSlider;
class QAction;

typedef void QzImportDialogCB(int result, const QzImportDialog &edwin,
                              void* userdata);

/**
   Import dialog wizard widget for data files to be subject to plot
@author Olaf Paetsch
*/
class HXPLOT_API QzImportDialog: public QWizard {

    Q_OBJECT

private:

    QzImportDialogCB* importCallback;
    void*             importUserdata;

    QTableWidget*     importTable;

    QWizardPage*      page0Box;
    bool              page0NextEnabled;
    QGroupBox*        page0TypeBox;
    QButtonGroup*     page0TypeGroup;
    QRadioButton*     page0Separator;
    QRadioButton*     page0FixedWidth;
    QRadioButton*     page0FixedFormat;
    QRadioButton*     page0Binary;

    QWizardPage*      pageCmntBox;
    bool              pageCmntNextEnabled;
    QGroupBox*        pageCmntCommentBox;
    QButtonGroup*     pageCmntCommentGroup;
    QRadioButton*     pageCmntCmntSharp;
    QRadioButton*     pageCmntCmntPercent;
    QRadioButton*     pageCmntCmntSlash;
    QRadioButton*     pageCmntCmntAny;
    QRadioButton*     pageCmntCmntNone;
    QGroupBox*        pageCmntQuoteBox;
    QButtonGroup*     pageCmntQuoteGroup;
    QRadioButton*     pageCmntQuoteApo;
    QRadioButton*     pageCmntQuoteDbl;
    QRadioButton*     pageCmntQuoteNone;
    QSpinBox*         pageCmntStartLine;

    QWizardPage*      pageSepBox;
    bool              pageSepNextEnabled;
    QGroupBox*        pageSepSepBox;
    QButtonGroup*     pageSepSepGroup;
    QRadioButton*     pageSepCommaCheck;
    QRadioButton*     pageSepSemicolonCheck;
    QRadioButton*     pageSepWhitespaceCheck;
    QRadioButton*     pageSepSlashCheck;
    QRadioButton*     pageSepTabCheck;
    QRadioButton*     pageSepNone;
    QSpinBox*         pageSepColNames;

    QWizardPage*      pageFmtBox;
    bool              pageFmtNextEnabled;
    QLineEdit*        pageFmtLine;
    QLabel*           pageFmtHeadlineLabel;
    QLineEdit*        pageFmtHeadline;

    QWizardPage*      pageColTypeBox;
    bool              pageColTypeNextEnabled;
    QGroupBox*        pageColTypeTypeBox;
    QButtonGroup*     pageColTypeTypeGroup;
    QRadioButton*     pageColTypeText;
    QRadioButton*     pageColTypeNum;
    QRadioButton*     pageColTypeDate;
    QPushButton*      pageColTypeMenu;
    QMenu*            pageColTypePopup;

    QWizardPage*      pagePlotBox;
    bool              pagePlotNextEnabled;
    QGroupBox*        pagePlotPlotBox;
    QButtonGroup*     pagePlotPlotGroup;
    QRadioButton*     pagePlotAllCols;
    QRadioButton*     pagePlotAllRows;
    QRadioButton*     pagePlotColsFirst;
    QRadioButton*     pagePlotRowsFirst;
    QRadioButton*     pagePlotXY;
    QGroupBox*        pagePlotSelectBox;
    QButtonGroup*     pagePlotSelectGroup;
    QCheckBox*        pagePlotSelect;

    int numLines, numColumns, numRows, numFmtColumns;
    McDArray<int> selColumns;
    int lastPage;
    char separator;
    bool hasHeadline;
    int wizardsDataTypeLine;  // contains data structure type, set in page0
    int lineOfPages[7];       // contains the line of pages: -1 = not appropr.

    PzDataImportRules &myImportRules;

    void checkLineOfPages();

    /// checks c-like format line and returns number of number values
    int checkFmtLine();

    void addCsvLine(char* line, int num, int linetype);

    void addFmtLine(char* line, int num, int linetype);

    int newFormat();

protected slots:

    virtual void accept();

    //virtual void apply();

    //virtual void next();

    //virtual void back();

    virtual void reject();

    void page0Changed( int selButton );

    void pageCmntChanged();

    void pageSepChanged();

    void pageFmtChanged();

    void pageColTypeChanged( QAction* action );

    void pageColTypeChanged( int selButton );

    void pagePlotChanged( int selButton );

    void pagePlotChanged( bool clicked );

    void horHeaderClick( int col );

    void vertHeaderClick( int row );

    //void tableItemClicked(int row, int col, int button, const QPoint & );

    //void newSelection();

    void newId(int pageId);

protected:

    void setupPage0();

    void setupSepPage();

    void setupCmntPage();

    void setupFmtPage();

    void setupTypePage();

    void setupPlotPage();

    void updateGUI();

    virtual void goForward();

    virtual void goBackward();

public slots:

    virtual int exec();

public:

    enum cbResult { CANCEL = 0, APPLY = 1, OK = 2, NEXT = 3, BACK = 4,
                    PREVIEW = 5 };

    enum lineType { isNORMAL=0, isCOMMENT=1, isHEADLINE=2, tobeSKIPPED=3 };

    /// Constructor
    QzImportDialog(const char* name, PzDataImportRules& importRules,
                   const int numPreviewLines);

    /// Destructor
    ~QzImportDialog();

    /// reimplemented from QWizard
    virtual int nextId() const;

    ///
    void setImportCallback(QzImportDialogCB* clientfunc, void* clientdata);

    /// unsets the notifier above
    void unsetImportCallback() { importCallback = NULL; }

    void addLine(char* line, int num = -1, int linetype = isNORMAL);

    void startTable();

    void endTable();

    void headLine(char* headline = NULL);

    int headLine(char* headline, char separator);
};

#endif

/// @}

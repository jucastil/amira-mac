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
#ifndef QXFILEDIALOG_H
#define QXFILEDIALOG_H

class QxFileDialogPrivate;
class QPushButton;
class QLabel;
class QPixmap;
class QWidget;
class QTimer;
class QxFileDialog;
class HxFileFormat;
class QStringList;

#ifndef QT_H
    #include "qdir.h"
    #include "qdialog.h"
    #include "q3listbox.h"
    #include "qlineedit.h"
    #include "q3listview.h"
#endif

#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <hxcore/HxAmiraWinDLLApi.h>
#include "HxSettingsMgr.h"
#include "QxSettingsMgrNotifier.h"

#include <hxcore/ui_QxFileDialogBase.h>

class HXCORE_API QxFileIconProvider : public QObject
{
    Q_OBJECT
public:
    QxFileIconProvider( QObject * parent = 0, const char* name = 0 );

    virtual const QPixmap * pixmap( const QFileInfo & );
};

class QxRenameEdit : public QLineEdit
{
    Q_OBJECT

public:
    QxRenameEdit(QWidget *parent) : QLineEdit(parent) {}

protected:
    void keyPressEvent( QKeyEvent *e );
    void focusOutEvent( QFocusEvent *e );

signals:
    void escapePressed();
};

class QxFileListBox : public Q3ListBox
{
    friend class QxFileDialog;
    friend class QxFileDialogPrivate;

    Q_OBJECT

private:
    QxFileListBox( QWidget *parent, QxFileDialog *d );

    void clear();
    void show();
    void startRename( bool check = TRUE );
    void setSelected( Q3ListBoxItem *i, bool s );
    void setSelected( int i, bool s );

private:
    void viewportMousePressEvent( QMouseEvent *e );
    void viewportMouseDoubleClickEvent( QMouseEvent *e );
    void keyPressEvent( QKeyEvent *e );

private slots:
    void rename();
    void cancelRename();

private slots:
    void doubleClickTimeout();

private:
    QxRenameEdit *lined;
    QxFileDialog *filedialog;
    bool renaming;
    QTimer* renameTimer;
    Q3ListBoxItem *renameItem;
};

class QxFileListView : public Q3ListView
{
    friend class QxFileDialog;
    friend class QxFileDialogPrivate;

    Q_OBJECT

private:
    QxFileListView( QWidget *parent, QxFileDialog *d );

    void clear();
    void startRename( bool check = TRUE );

private:
    void viewportMousePressEvent( QMouseEvent *e );
    void viewportMouseDoubleClickEvent( QMouseEvent *e );
    void keyPressEvent( QKeyEvent *e );

private slots:
    void rename();
    void cancelRename();

private slots:
    void doubleClickTimeout();

private:
    QxRenameEdit *lined;
    QxFileDialog *filedialog;
    bool renaming;
    QTimer* renameTimer;
    Q3ListViewItem *renameItem;
};

#ifdef HX_OS_WIN

#include <windows.h>

#include <mclib/McHandle.h>
#include <mclibthreaded/McThread.h>

class DriveInfo;

class DriveTypeThread:public McThread
{
public:
    DriveTypeThread(DriveInfo *info);

protected:
    void run();

private:
    McHandle<DriveInfo> m_info;
};

class DriveInfo:public McHandable
{
    friend class DriveTypeThread;

public:
    static UINT GetType(const McString& root,unsigned long timeout=500) {
        McHandle<DriveInfo> info(new DriveInfo(root));
        return info->GetType(timeout);
    }

protected:
    DriveInfo(const McString& root):
        m_type_thread(new DriveTypeThread(this)),m_root(root) {}

    ~DriveInfo() {
        delete m_type_thread;
    }

    UINT GetType(unsigned long timeout) {
        m_type=DRIVE_UNKNOWN;

        // Do not start a new thread if there already is one running.
        if (!m_type_thread->running()) {
            m_type_thread->start();
        }

        // Block until the thread terminates or the timeout is reached.
        m_type_thread->wait(timeout);

        return m_type;
    }

private:
    DriveTypeThread *m_type_thread;
    McString m_root;
    UINT m_type;
};

inline DriveTypeThread::DriveTypeThread(DriveInfo *info):
    m_info(info)
{
}

inline void DriveTypeThread::run() {
    m_info->m_type=GetDriveType(m_info->m_root.getString());
}

#endif // HX_OS_WIN

class HXCORE_API QxFileDialog : public QDialog
{
    friend class QxFileListBox;
    friend class QxFileListView;

    Q_OBJECT
public:
    QxFileDialog( const QString& dirName, const QString& filter = QString::null,
                 QWidget *parent=0, const char *name=0, bool modal=FALSE,
                 QString recentPathsSettingName = "fileDialog" );
    QxFileDialog( QWidget *parent=0, const char *name=0, bool modal=FALSE,
                  QString recentPathsSettingName = "fileDialog" );
    ~QxFileDialog();

    // static functions

    static void setIconProvider( QxFileIconProvider * );
    static QxFileIconProvider * iconProvider();

    // non-static function for special needs

    QString selectedFile() const;
    QString selectedDirectory() const;

    // AMIRA: required for multi-file mode
    int numSelectedFiles() const;
    void selectedFiles(McDArray<QString>& files) const;
    void fileFormats(McDArray<HxFileFormat*>& formats) const;

    void setSelection( const QString &);

    QString dirPath() const;

    void setDir( const QDir & );
    const QDir *dir() const;

    void refresh();

    void setOkButtonLabel(const char* labeltext);

    enum Mode { AnyFile, ExistingFile, Directory, ExistingFiles };
    void setMode( Mode );
    Mode mode() const;

    bool eventFilter( QObject *, QEvent * );

    // AMIRA: in save mode filter determines requested save format
    void registerFileType(const char* name=NULL, const char* suffix=NULL,
        int multiSave=0);

    const char* getFileType();

    bool setFileType(const char* name);

    void addToPathList(QString directory, int dynamic=0, bool checkDir=true);

    void savePathList();

    void restorePathList();

    void rereadDir();

    QStringList* getFilters();

    QString getSelectedFilter() const;
    void setSelectedFilter(const QString& filter);

    /** 
     * To clear the filename field if it doesn't match the current filter extension.
     * Called by theFileDialog->postAndWait() method.
     */
    void checkCurrentFilenameAccordingToCurrentFilterExtension();

public slots:
    void setDir(const QString&);
    void setFilter(const QString&);
    void setFilters(const char**);
    void setFilters(const QStringList&);
    void setFilterAndRereadDir(const QString&);

signals:
    void fileHighlighted( const QString& );
    void fileSelected( const QString& );
    void dirEntered( const QString& );

private slots:
    void fileSelected(int);
    void fileHighlighted(int);
    void dirSelected(int);
    void pathSelected(int);
    void fileTypeChanged(int);

    void updateFileNameEdit();
    void updateFileNameEditBox();
    void updateFileNameEditBoxSingle();
    void selectDirectoryOrFile( Q3ListViewItem * );
    void popupContextMenu( Q3ListViewItem *, const QPoint &, int );
    void popupContextMenu( Q3ListBoxItem *, const QPoint & );
    void selectDirectoryOrFile( Q3ListBoxItem * );
    void fileNameEditDone();

    void okClicked(bool okButtonClicked=true);
    void cancelClicked();

    void cdUpClicked();
    void newFolderClicked();

    void fixupNameEdit();
    void queryOneFileFormat();

    /** 
     * Called when the user presses the return key after
     * entering or pasting a path into the paths combo box.
     */
    void pathsListEdited();

protected:
    void keyPressEvent( QKeyEvent * );
    void addWidgets( QLabel *, QWidget *, QPushButton * );

    /// The setting name which identify the recent paths for this instance
    McString m_recentPathsSettingName;

private:
    enum PopupAction {
        PA_Open = 0,
        PA_Delete,
        PA_Rename,
        PA_Refresh,
        PA_SortAscent,
        PA_SortDescent,
        PA_Format,
        PA_Cancel,
        PA_SelectAll
    };

    void init();
    void deleteFile( const QString &filename );
    void popupContextMenu( const QString &filename, bool withSort,
                           PopupAction &action, const QPoint &p );

    QDir cwd;
    QxFileDialogPrivate *d;

    void setFileFormat();

    /** 
     * To fix bug #1291.
     * This flag allow to check if an extension is known or not.
     * If it's not the case, no replacement will be done in the filename:
     * the file extension is only appended, not replaced.
     */
    static bool s_hasUnknownExtension;

  public slots:
    /**
     *  To be notified that recent documents has been reset.
     */
    virtual void recentDocumentsReset();
};

#endif // QFILEDIALOG_H

/// @}

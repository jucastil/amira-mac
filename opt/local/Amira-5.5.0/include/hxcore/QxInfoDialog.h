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
#ifndef _HX_INFO_DIALOG
#define _HX_INFO_DIALOG

#include <hxcore/ui_QxInfoDialogBase.h>

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxThread.h>
#include <hxcore/HxBunch.h>

#include <mclib/McString.h>
#include <mclib/McList.h>

//! System information dialog class
/*! QxInfoDialog create a
    dialog that provide information
    for the developer. The first tab
    displays OpenGL Information, the second
    tab displays version information for
    linked libraries.
*/
class HXCORE_API QxInfoDialog : public QDialog, public Ui::QxInfoDialogBase
{
    Q_OBJECT

public:

    // Return the version information for the given library file (without path).
    // If versionTag is specified, only return that particular version string.
    static McString getLibVersion(McString const& filename,McString const& versionTag=NULL);

    QxInfoDialog( QWidget * parent );
    virtual ~QxInfoDialog();

    class LibInfo : public QTreeWidgetItem, public McLink
    {
    public:
        LibInfo( QTreeWidget * inParent );
        ~LibInfo();

        HxBunch         _infoPatch;
        HxBunch         _infoCurr;
        HxBunch         _infoDB;

        McString        _dirname;   // absolute path to lib
        McString        _filename;  // file name of the lib
        mculong         _size;      // current file size

        // thread stuff
        int             _processed; // true if the process thread has finished this lib
        int             _displayed; // true if the result of the processing was displayed in the list view
    };

    ////////////////////////////////////////////////////////////////////////////////
    // MyThread
    // performs the parallel retrieval library data
    ////////////////////////////////////////////////////////////////////////////////
    class MyThread : public HxThread
    {
    public:
        MyThread( QxInfoDialog & inDlg );
        ~MyThread();

        virtual void  run(); // abstract from base class

        QxInfoDialog & _dlg;
    };

    void libsList();
    void libsList( McString & pathName );
    void dbRead();

protected slots:

    void reportSave();

public:

    // The graphic board driver version.
    McString            _gbDriverVersion;

    QString             _atiDriverVersion;

    McString            _glVersion;
    McString            _glVendor;
    McString            _glRenderer;
    McDArray<McString>  _glExtensions;

    McList<LibInfo>     _libs;

    // processing thread
    MyThread            _thread;

    // info database
    struct dbIdx
    {
        McString    _file;
        int         _idxStart;
        int         _len;
    };

    HxBunch           * _dbBunch;
    McDArray<dbIdx>     _dbIdx;

    /** 
     * To show or not the Libraries tab.
     */
    static bool s_showLibrariesTab;
};

#endif

/// @}

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

/// @addtogroup hxvisageviewer hxvisageviewer
/// @{
#ifndef QX_MAIN_H
#define QX_MAIN_H

#include <hxvisageviewer/ui_QxMainWindowBase.h>
#include "ExBaseViewer.h"

#include <QMainWindow>
#include <QAction>
#include <QMap>
#include <QString>
#include <QToolBar>
#include <QMenu>

#include <vsvolren/VsRenderer.h>

//#define app QxMainWindow::instance()

////////////////////////////////////////////////////////////////////////////////
class QxMainWindow
:   public  QMainWindow
,   public  Ui::QxMainWindowBase
{
    Q_OBJECT

public:

    QxMainWindow( QWidget * parent = 0 );
   ~QxMainWindow();
    

    static QAction * actionCreate( QString inName, QObject * parent = 0 );


    virtual bool event ( QEvent * event );
   

   // void setVolume( VsVolume * inVolume );
   // void cleanup();
   // void slot_decoUIToState();

    //static QxMainWindow & instance( int argc = 0, char ** argv = 0 );

   // QxMainWindow & mainWindow();

    // the volume
    McHandle<VsVolume>  mVolume;


public slots:

    void slot_close();
    void slot_about();


public:

    ExBaseViewer * viewer( int inIndex );

    void setFullscreen( int inViewerIndex );
    int fullscreen();

    ////////////////////////////////////////
    // actions
    ////////////////////////////////////////

    QAction * mActionExit;
#ifdef VS_DEBUG
    QAction * mActionLoad;
#endif
    QAction * mActionAbout;

    QAction * mActionNavDefault;
    QAction * mActionNav3DRotate;
    QAction * mActionNavPan;
    QAction * mActionNavZoom;
    QAction * mActionRegTool;
    QAction * mActionNavWindowLevel;
    QAction * mActionNavBrowseSlices;
    QAction * mActionNavPerspectiveProjection;
    QAction * mActionNavOrthographicProjection;

    QAction * mActionToolSnapshot;
    QAction * mActionToolCenter;
    QAction * mActionToolFitAll;
    QAction * mActionToolResetMPR;

    QAction * mActionCropClipBox;
    QAction * mActionCropClipCorner;
    QAction * mActionCropClipPlane;
    QAction * mActionCropClipSlab;

    QAction * mActionDecoBound2D;
    QAction * mActionDecoBound3D;
    QAction * mActionDecoScouts;
    QAction * mActionDecoPatientInfo;
    QAction * mActionDecoHistogram;

    QAction * mActionViewAll;
    QAction * mActionViewXY;
    QAction * mActionViewXZ;
    QAction * mActionViewYZ;

    Qt::KeyboardModifiers mKeyMod;

    class ActionInfo
    {
    public:

        void set( char * inIconNameNorm, char * inIconNameDisabled, char * inText );

        QString mIconNameNormal;
        QString mIconNameDisabled;
        QString mText;
    };

    static QMap< QString, ActionInfo >    sActionInfo;

    ////////////////////////////////////////
    // tool bars
    ////////////////////////////////////////

    QToolBar * mToolBarNav;
    QToolBar * mToolBarTool;
    QToolBar * mToolBarCrop;
    QToolBar * mToolBarView;

    ////////////////////////////////////////
    // menus
    ////////////////////////////////////////

    QMenu * mMenuTool;
    QMenu * mMenuCrop;
    QMenu * mMenuDeco;
    QMenu * mMenuView;

    void warning(const char* error);
private:
    McHandle<ExViewerManager> mViewerManager;

};

#endif

/// @}

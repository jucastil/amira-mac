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
#ifndef VSVOLREN_EXAMPLE_VR_VIEWER_APPLICATION_H
#define VSVOLREN_EXAMPLE_VR_VIEWER_APPLICATION_H

#ifdef None
  #undef None
#endif
#include <QApplication>

#include "QxMainWindow.h"

//#include "ExViewerManager.h"
#include "ExNotifiable.h"

//#define PL_WINDOW_CLASS_NAME  "Platsch Class"
//#define PL_WINDOW_WINDOW_NAME "Platsch Window"

#include <mclib/McHandle.h>

#include <vsvolren/VsVolume.h>
#include <vsvolren/VsGroup.h>
#include <vsvolren/VsCamera.h>
#include <vsvolren/VsVolren.h>
#include <vsvolren/VsSlice.h>
#include <vsvolren/VsCropRegion.h>

#include <amiramesh/HxParamBundle.h>
#include "ExWindowLevelTool.h"

#include <hxcolor/HxColormap.h>
#include <hxcolor/HxPortColormap.h>


////////////////////////////////////////////////////////////////////////////////
class QxApplication
    : public QObject,
    public ExNotifiable
{
    Q_OBJECT
    
    static QxApplication * sTheApplication;
public:


    McHandle<VsSlice >      slice[4];
    McHandle<VsVolren>      volren[4];

    McHandle<ExWindowLevelTool> levelingTool[4];

    

    QxApplication( int & argc, char ** argv );

    ~QxApplication();

    void init();
   
    static QxApplication & instance( int argc = 0, char ** argv = 0 );

    void setVolume( VsVolume * inVolume, VsVolren::RenderMode renderMode, VsVolume * inVolume2 = NULL,  bool clearScene = TRUE);
    VsVolume * volume();

    void createColormap( HxPortColormap  &port, int volumeID, float fade, float dataWindow[4]);

    void touchSlices(unsigned int mask);
    
    void cleanup();

    void processCommandLine();

    static void parseCommandLine( int & argc, char ** argv );

    ExTool* getCurrentActiveTool() {return mCurrentActiveTool; }
    ////////////////////////////////////////
    // override QObject
    ////////////////////////////////////////
    
    virtual void customEvent( QEvent * event );


    ////////////////////////////////////////
    // override ExNotifiable
    ////////////////////////////////////////

    virtual void notified( const ExNotification & notification );


    ////////////////////////////////////////
    // singletons
    ////////////////////////////////////////

    QxMainWindow & mainWindow();

    static void dbgTick();


    ////////////////////////////////////////
    // slots
    ////////////////////////////////////////
public slots:

#ifdef VS_DEBUG
    void loadDataFromFile();
#endif

    // navigation
    void slot_navigationUpdate();

    // crop
    void slot_cropUpdate();

    // tools
    void slot_toolSnapshot();
    void slot_toolCenterView();
    void slot_toolResetMPR();
    void slot_toolFitAll();

    // decoration
    void slot_decoUIToState();
    void slot_decoStateToUI();

    // update slice info
    void slot_updateSliceInfo();

    // Perspective Projection
    void slot_PerspectiveProjection();

    // Orthographic Projection
    void slot_OrthographicProjection();

    // view options
    void slot_viewAll();
    void slot_viewXY();
    void slot_viewXZ();
    void slot_viewYZ();



private:

    // the main window
    QxMainWindow      * mMainWindow;

    // the volume
    McHandle<VsVolume>  mVolume;
    // the volume
    McHandle<VsVolume>  mVolume2;

    // input Files for dicom conversion
    static McDArray<McString> mInputFiles;

    bool display_info;

    ExTool *mCurrentActiveTool;

public:

    class CommandLineInfo
    {
    public:
        
        CommandLineInfo()
        :   mDoDicom    ( false )
        ,   mDoHelp     ( false )
        ,   mDoWinSize  ( false )
        ,   mWidth      ( 0 )
        ,   mHeight     ( 0 )
        ,   mDoWinPos   ( false )
        ,   mPosX       ( 0 )
        ,   mPosY       ( 0 )
        {
        }


        bool    mDoDicom;

        bool    mDoHelp;

        bool    mDoWinSize;
        int     mWidth;
        int     mHeight;

        bool    mDoWinPos;
        int     mPosX;
        int     mPosY;
    };

    static CommandLineInfo mCMDL;
};

#define theQxApp QxApplication::instance()


////////////////////////////////////////////////////////////////////////////////
class QxCustomEvent
:   public QEvent
{
public:

    enum Type
    {
        T_CMD_DICOM_LOAD        = QEvent::User
    ,   T_VIEWER_LAYOUT_INVALID = QEvent::User + 100
    };


public:

    QxCustomEvent( Type inType, void * inData = 0 )
    :   QEvent  ( QEvent::Type(inType) )
    ,   mData   ( inData )
    {
    }

    void setData( void * inData )
    {
        mData = inData;
    }

    void * data()
    {
        return mData;
    }

    void * mData;
};


////////////////////////////////////////////////////////////////////////////////
//
// each time a VsVolume (volume) gets created call:
//
// VsVolumeObserver::instance().observeObject(volume);
//
class VsVolumeObserver
:   public VsObject
{
public:

    int     mNumVolumesObserving;

    VsVolumeObserver()
    :   mNumVolumesObserving    ( 0 )
    {
    }

    virtual void observerAdded( VsObject * inObserver )
    {
        assert( mNumVolumesObserving==0 );
        mNumVolumesObserving++;
    }
    virtual void observerRemoved( VsObject * inObserver )
    {
        McHandle<VsVolume> v = dynamic_cast<VsVolume*>(inObserver);
        assert( v.ptr()!=0 );

        HxParamBundle * p = & v->parameters();

        if ( p )
        {
            v->setParameters(0);

            HxParamBundle * p2 = & v->parameters();

            if ( p!=p2 )
            {
                delete p;
            }
        }

        mNumVolumesObserving--;
        assert( mNumVolumesObserving==0 );
    }

    static VsVolumeObserver & instance()
    {
        static McHandle<VsVolumeObserver> theObserver;

        if ( theObserver.ptr()==0 )
            theObserver = new VsVolumeObserver;

        return * theObserver.ptr();
    }
};


#endif

/// @}

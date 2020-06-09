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
#ifndef EXBASEVIEWER_RENDERWIDGET_H
#define EXBASEVIEWER_RENDERWIDGET_H

#include <QWidget>
#include <QPaintEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTimer>

class ExBaseViewer;
class ExVsWidget;

#include "ExNotification.h"
#include "ExNotifiable.h"


////////////////////////////////////////////////////////////////////////////////
class ExBaseViewerRenderWidget
:   public QWidget
,   public ExNotifiable
{
    Q_OBJECT

public:

    ExBaseViewerRenderWidget( QWidget * parent );

    virtual ~ExBaseViewerRenderWidget();

    virtual void create( WId id );

    void notified( const ExNotification & notification ) ;

    ExBaseViewer & viewer();

    bool rightMouseButtonEvent(QMouseEvent* me);

    ////////////////////////////////////////
    // override QWidget
    ////////////////////////////////////////
    
    QPaintEngine * paintEngine () const;
    void paintEvent( QPaintEvent * e );
    bool event( QEvent* e );
    void resizeEvent( QResizeEvent * e );

#ifdef HX_OS_MACX
    // on hide we have to set the size of AGL_BUFFER_RECT to zero
    // in order to hide the renderwidget 
    void hideEvent( QHideEvent * e );
    // MacX carbon specific widget region, which is needed to clip the 
    // AGL_BUFFER_RECT during rendering    
    const QRegion& getAGLClipRegion();
    QRegion mAGLClipRegion;
#endif

public slots:

    void slot_restoreRenderQueue();


public:

    ExVsWidget  * mTextNW;
    ExVsWidget  * mTextSW;
    ExVsWidget  * mTextNE;
    ExVsWidget  * mTextSE;

    ExVsWidget  * mTextN;
    ExVsWidget  * mTextS;
    ExVsWidget  * mTextE;
    ExVsWidget  * mTextW;

//    ExVsWidget  * mTextC;

    ExVsWidget  * mHistogram;
    ExVsWidget  * mNavCube;
    ExVsWidget  * mLowQ;
    ExVsWidget  * mWarning;

protected:

    QGridLayout * mLayAll;

    QVBoxLayout * mLayNW;
    QVBoxLayout * mLayNE;
    QVBoxLayout * mLaySW;
    QVBoxLayout * mLaySE;

    QHBoxLayout * mLayTextNW;
    QHBoxLayout * mLayTextSW;
    QHBoxLayout * mLayTextNE;
    QHBoxLayout * mLayTextSE;

    QVBoxLayout * mLayTextN;
    QVBoxLayout * mLayTextS;
    QHBoxLayout * mLayTextE;
    QHBoxLayout * mLayTextW;
    
//    QHBoxLayout * mLayTextC;

    QHBoxLayout * mLayHistogram;
    QHBoxLayout * mLayNav;
    QHBoxLayout * mLayWarning;
    QHBoxLayout * mLayLowQ;

    QTimer  mTimer;
};

#endif

/// @}

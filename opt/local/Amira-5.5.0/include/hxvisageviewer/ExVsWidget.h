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
#ifndef _EX_VS_WIDGET_H_
#define _EX_VS_WIDGET_H_

#include <QWidget>
#include <QLayout>
#include <QSize>

#include <mclib/McHandle.h>
#include <mclib/McString.h>

#include <vsvolren/VsWidget.h>


class ExVsWidget 
:   public QLayoutItem
{
public:

    ExVsWidget( QWidget * inParent, VsWidget * inVsWidget = 0 );
    
   ~ExVsWidget();

    VsWidget * vsWidget();
    void setVsWidget( VsWidget * inVsWidget );

    QWidget * parent();

public:

    //////////////////////////////////////////////////
    // override QLayoutItem
    //////////////////////////////////////////////////

    virtual Qt::Orientations expandingDirections () const;
    virtual QRect geometry () const;
    virtual bool isEmpty () const;
    virtual QSize maximumSize () const;
    virtual QSize minimumSize () const;
    virtual void setGeometry ( const QRect & r );
    virtual QSize sizeHint () const;


    //////////////////////////////////////////////////
    // own methods
    //////////////////////////////////////////////////

    const char * toolTip();
    void setToolTip( const char * inText );
    void setExpandingDirections( Qt::Orientations mExpandData );

private:

    QWidget               * mParent;
    McHandle<VsWidget>      mVsWidget;
    McString                mToolTip;
    QRect                   mToolTipRect;
    QRect                   mGeometry;
    Qt::Orientations        mExpandData;

    McHandle<VsObject>  mTouchReceiver;

private:

    void updateToolTip();
};

#endif // QXSEGMENTWIDGET_H

/// @}

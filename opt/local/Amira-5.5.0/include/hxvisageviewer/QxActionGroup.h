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
#ifndef QX_ACTION_GROUP_H
#define QX_ACTION_GROUP_H

#include <QObject>
#include <QList>
#include <QAction>



////////////////////////////////////////////////////////////////////////////////
class QxActionGroup 
:   public QObject
{
    Q_OBJECT

public:

    ////////////////////////////////////////
    QxActionGroup ( QObject * parent )
    :   QObject( parent)
    {
    }


    ////////////////////////////////////////
    ~QxActionGroup ()
    {
        while ( mActions.count() )
        {
            if ( mActions.at(0)->parent() == this )
                mActions.at(0)->deleteLater();
            mActions.removeFirst();
        }
    }


    ////////////////////////////////////////
    QList<QAction *> actions () const
    {   
        return mActions;
    }


    ////////////////////////////////////////
    QAction * addAction ( QAction * action )
    {
        if (    action==0 
            ||  mActions.contains( action )
        )
            return action;

        mActions.append( action );

        connect ( action, SIGNAL(destroyed(QObject*)), this, SLOT(slot_destroyed(QObject*)) );
        connect ( action, SIGNAL(toggled(bool))      , this, SLOT(slot_toggled(bool))       );

        return action;
    }


    ////////////////////////////////////////
    QAction * checkedAction () const
    {
        for ( int i=mActions.count() ; i-- ; )
        {
            if ( mActions.at(i)->isChecked() )
                return mActions.at(i);
        }
        return 0;
    }


    ////////////////////////////////////////
    void removeAction ( QAction * action )
    {
        if ( !mActions.contains( action ) )
            return;

        action->disconnect( this );

        mActions.removeAll(action);
    }


public slots:

    void slot_destroyed( QObject * obj )
    {
        QAction * action = dynamic_cast<QAction*>(obj);
        removeAction(action);
    }

    void slot_toggled( bool state )
    {
        if ( !state )
            return;

        QAction * action = dynamic_cast<QAction*>( sender() );

        if ( !mActions.contains(action) )
            return;

        for ( int i=mActions.count() ; i-- ; )
        {
            if ( mActions.at(i)->isChecked() && mActions.at(i)!=action )
            {
                mActions.at(i)->setChecked(false);
                break;
            }
        }
    }


private:

    QList<QAction*>     mActions;
};


#endif

/// @}

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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_OBJECT_IMPL_H
#define _VS_OBJECT_IMPL_H

#include "VsObject.h"
#include "VsInterfaceImpl.h"

#include <mclibthreaded/McMutex.h>
#include <mclibthreaded/McWaitCondition.h>

#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McHandle.h>

class VsJobControl;

////////////////////////////////////////////////////////////////////////////////
class VsObjectImpl : public VsInterfaceImpl
{
    VS_IMPLEMENTATION( VsObjectImpl, VsInterfaceImpl, VsObject )

public:

    struct VsLock
    {
        VsJobControl  * mJob;       // non-zero if the lock is cancelable
        unsigned long   mThread;    // thread-ID of the thread that aquired the lock
        bool            mWrite;     // true, if the lock is a write-lock
        bool            mIgnore;    // write locks set the mIgnore of read locks to true
        int             mDeferredTouchMask; // if touched done with write-locked objects,
                                            // instead of propagating the touches we store
                                            // the mask here and trigger a touch once the
                                            // lock is released. 
    };

    // the name of the object
    McString                mShortName;
    McString                mLongName;

    // lock mechanism
    McDArray<VsLock>        mLocks;         // one entry for each current lock
    McMutex                 mLocksMutex;    // synchronisation of access to mLocks - non-recursive.
    McWaitCondition         mWait;
    bool                  (*mInterruptCallback)();

    // touch mechanism
    unsigned int            mTouchNumber;

    // notification mechanism
    McDArray< VsObject* >   mObservers;
    McDArray< VsObject* >   mObserved;

    McMutex               * mObserveMutex;
//RK    bool                    mObserveLockWrite;
//RK    int                     mObserveLockCount;
    int                     mObserversNumReader; // number of functions that currently iterate mObservers
    bool                    mObserversRepair;

    McDArray<unsigned int>  mTouchMasks;
    bool                    mEnableNotify;
    unsigned int            mState;

    // to mark an object for debugging this can be set by calling setOptioni( Vs::OPT_ID, .. ); default -1
    int                     mId; 


    bool                    mNoWriteLockCheckEnabled;

public:

    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////
    
    VSRESULT    connect   ( VsObject * inObjectToObserve );
    VSRESULT    disconnect( VsObject * inObservedObject  );
    unsigned int state();

    /*  If elements from mObservers need to be removed during iterations of that array, the entry is set to zero 
        instead of really been removed from that array. If the outermost iteration has finished, these 
        zero-entries need to be removed from the array. */
    void repair();


    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////

    VSRESULT    lock( bool inWriteable, bool cancelCurrentOperation, VsJobControl * locker );
    VSRESULT    unlock();
    VSRESULT    observeObject( VsObject * ioObject );
    VSRESULT    ignoreObject( VsObject * ioObject );
    VSRESULT    observedObjects( McDArray< McHandle<VsObject> > & outObjects );
    bool        isNew( unsigned int mask=VsObject::NEW_UNSPECIFIED ) const;
    unsigned int touchNumber() const;
    VSRESULT    enableNotification( bool on );
    bool        notificationEnabled();
    bool        canceled();
    bool        setCancelEnable( bool inFlag );
    VSRESULT    setInterruptCallback(bool (*interruptCallback)());

    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
private:

    VSRESULT        vimpl_touch( unsigned int mask );
    VSRESULT        vimpl_untouch( unsigned int mask=VsObject::NEW_ALL );
    VSRESULT        vimpl_observedObjectAdded( VsObject * inObject );
    VSRESULT        vimpl_observedObjectRemoved( VsObject * inObject );
    void            vimpl_observerAdded( VsObject * inObject );
    void            vimpl_observerRemoved( VsObject * inObject );
    void          * vimpl_extension( int inEnum, void * ioData );


protected:
    virtual VSRESULT    vimpl_setOptioni( int inOption, int inValue );
    virtual VSRESULT    vimpl_setOptiond( int inOption, double inValue );
    virtual VSRESULT    vimpl_optioni( int inOption, int & outValue ) const;
    virtual VSRESULT    vimpl_optiond( int inOption, double & outValue ) const;

protected:

    VSRESULT    vimpl_observedObjectTouched( VsObject * inObject, unsigned int inMask );
};



////////////////////////////////////////////////////////////////////////////////
// convenience macros
////////////////////////////////////////////////////////////////////////////////
#define VS_LOCK_OBJECT_WRITE_IMPL  VsObjectLocker _object_locker_impl_w_(m,true);
#define VS_LOCK_OBJECT_READ_IMPL   VsObjectLocker _object_locker_impl_r_(m,false);
#define VS_LOCK_OBJECT_WRITE_CONTROL_IMPL(ctl) VsObjectLocker _object_locker_impl_r_(m,true,true,ctl);
#define VS_LOCK_OBJECT_READ_CONTROL_IMPL(ctl) VsObjectLocker _object_locker_impl_r_(m,false,true,ctl);
#define VS_UNLOCK_OBJECT_WRITE_IMPL _object_locker_impl_w_.unlock();
#define VS_UNLOCK_OBJECT_READ_IMPL _object_locker_impl_r_.unlock();
        
            

#endif


/// @}

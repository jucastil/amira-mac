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
#ifndef _VS_OBJECT_H_
#define _VS_OBJECT_H_


#include "Vs.h"

#include "VsHandable.h"
#include "VsInterface.h"

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>


class VsJobControl;
class VsObject;

// VS_RELAY_CLASS VsObject VsRelay
// VS_RELAY_EXPORT_CLASS VsObject VSVOLREN_API


/** Base class for thread-safe objects.
    This class provides three main features, namely

    -#  Locking and unlocking to facilitate concurrent use of the
        object within multiple threads.
    -#  Notification via a touch() mechanism which in turn touches
        observers of this object.
    -#  Mechanism to set options that are not available as separate 
        set and get methods.
*/
class VSVOLREN_API VsObject
:   public VsInterface
{
    VS_DECL_INTERFACE        ( VsObject )
    VS_DECL_INTERFACE_IMPL   ( VsObject )
    VS_DECL_INTERFACE_FACTORY( VsObject )
    VS_DECL_INTERFACE_RELAY  ( VsObject )

public:

    /** Notification flags.
        These flags or a combination of them is used for 
        touch() and observedObjectTouched() in order to specify more
        detailed which kind of changes have been performed on the object. 
        It is up to a particular object how to interprete the touch flags.

        If a parameter of a VsObject is changed, usually touch() will
        be called automatically with an appropriate combination of
        object-specific notification flags. This causes observing
        objects to be touched as well, see observeObject().
        A VsRenderer, for instance, observes all \link VsNode VsNodes \endlink
        attached to it.
        Whenever one of this nodes is changed, the VsRenderer is notified
        and thus can submit a new render request. */
    enum TouchFlag
    {
        /** General-purpose flag for unspecified changes. */
        NEW_UNSPECIFIED = 1<<0,

        /** Set if an observed object was modified. */
        NEW_OBSERVE     = 1<<31,

        // Force enum to be 32 bit
        NEW_ALL         = 0xffffffff
    };

public:
    /** Returns the short name of the object. If the object does not have a
        short name, the shortName() function returns "unnamed".
        \return The short object's name.
    */
    const char* shortName() const;

    /** Sets the short name of the object. Specifying a null pointer unsets
        the object's name. In this case shortName() returns "unnamed".
        \param inName 
               The new name of the object.
    */
    void setShortName(const char* inName);

    /** Returns the long name of the object. If the object does not have a
        long name, the longName() function returns "unnamed".
        \return The long object's name.
    */
    const char* longName() const;

    /** Sets the long name of the object. Specifying a null pointer unsets
        the object's name. In this case longName() returns "unnamed".
        \param inName
               The new name of the object.
    */
    void setLongName(const char* inName);

    //////////////////////////////////////////////////////////////
    //  Methods dedicated to implement the locking-mechanism
    //////////////////////////////////////////////////////////////

    /** Sets an interrupt callback. During time-consuming operations,
        derived classes should frequently call canceled() in order
        to check if the current operation should be terminated or
        not. If an interrupt callback has been set via this method
        this callback will be called from canceled(). The callback
        should return \c true in order to indicate that the current
        operation should be terminated, or \c false if it should be
        continued. If no interrupt callback has been set and if also
        no VsJobControl object has been specified in lock(), canceled()
        will always return \c false.
        
        You may want to set an interrupt callback if you are directly
        calling the \link VsNode::render() render() \endlink method
        of a VsNode object. When using VsCommonRenderer usually there
        is no need to set a user-defined interrupt callback, since
        the renderer automatically interrupts high-resolution rendering
        operations and reschedules interactive rendering requests, if
        necessary.

        \param  inInterruptCallback 
                The function pointer of the interrupt callback. If zero,
                the interrupt callback is turned off.
        \return 
                If the method succeeds, the return value is #VS_OK. To get 
                extended error information, call Vs::lastError().
        */
    VSRESULT setInterruptCallback( bool (*inInterruptCallback)() );

    /** Locks this object for write access.
        After this, the object cannot be locked by any other 
        thread. Note that the individual set-methods of derived \link VsObject 
        VsObjects \endlink are 
        typically thread-safe by itself, thus, there is usually no need
        to lock the object before calling an individual method.
        However, if a sequence of several methods has to be called,
        locking the object explicitly guarantees that the object is not
        being modified in-between.

        If the object is already locked by some other thread, the method
        blocks until the other thread releases the object. If
        \c inCancelCurrentOperation is set to \c true, the other thread
        holding the lock is asked to release the lock as soon as possible.
        This means that time-consuming operations will be interrupted if possible.

        In order to be informed about another thread trying to acquire the lock
        on the same object, a thread has to call lock() with a non-zero 
        \c inLocker. If then another thread tries to obtain the lock with
        \c inCancelCurrentOperation set to \c true, the \link VsJobControl::cancel()
        cancel() \endlink method of the VsJobControl object will be called.

        \param  inCancelCurrentOperation 
                If set to \c true and the object is already locked with a 
                VsJobControl object, this VsJobControl gets a signal to stop 
                current operations on this object.
        \param  inLocker 
                Optional VsJobControl object which may receive cancel-signals
                from other threads that request a lock on the same object.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT lock( bool inCancelCurrentOperation = true, VsJobControl * inLocker = 0 );

    /** Locks this object for read only access. 
        After this, the object can not be write-locked by any other thread, 
        but it can still be read locked by other threads.

        If the object is already write-locked by some other thread,
        the method blocks until the other thread releases the write lock.

        If the lock could not be obtained and if \c inCancelCurrentOperation is set to \c true, 
        other threads holding locks to this object are asked to 
        release the lock as soon as possible. This means that time-consuming
        operations will be interrupted if possible.

        In order to be informed about another thread trying to acquire the lock
        on the same object, a thread has to call lock() or lockReadOnly() with a non-zero 
        \c inLocker. If then another thread tries to obtain the lock with
        \c inCancelCurrentOperation set to \c true, the \link VsJobControl::cancel()
        cancel() \endlink method of the VsJobControl object will be called.

        \param  inCancelCurrentOperation 
                If set to \c True and the object is already locked with a 
                VsJobControl object, this VsJobControl gets a signal to stop 
                current operations on this object.
        \param  inLocker 
                Optional VsJobControl object which may receive cancel-signals
                from other threads that request a lock on the same object.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT lockReadOnly( bool inCancelCurrentOperation = true, VsJobControl * inLocker = 0 );

    /** Unlocks the node. After locking the object it should be unlocked as soon as the
        lock is not longer needed.

        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT unlock();

    /** This method should be frequently called during time-consuming operations.
        The method checks if an interrupt callback has been set via
        setInterruptCallback() or if the object has been locked with a
        VsJobControl object. It then calls the interrupt callback or the
        \link VsJobControl::canceled() canceled() \endlink method of the
        VsJobControl object. If the current operation should be terminated
        prematurely, the method returns \c true.

        \return 
            \c True if termination was requested, \c false if not.
    */
    bool canceled();


    //////////////////////////////////////////////////////////////
    //  Methods dedicated to implement the touch-mechanism
    //////////////////////////////////////////////////////////////
public:

    /** Touch the object to indicate that specific parts of its 
        state have changed.
        Calling touch() causes all objects observing this object to
        be informed via the method observedObjectTouched(). In derived
        objects you should call touch() whenever the object is modified.
        For example, in VsSlice, touch() is called when a new plane
        orientation is set via VsSlice::setPlane() or when the data window is
        modified via VsSlice::setDataWindow(). The argument \c inMask can
        be used to specify what property of the object has been altered.
        Interpretation of the touch mask is the responsibility of derived
        classes. 
        
        If this method is overloaded, make sure to call VsObject::touch() as
        well. Otherwise observing objects will not be notified. 
        If an object A observes object B and object B gets touched this doesn't
        necessarily mean that object A needs to be re-rendered. If object A 
        required to be re-rendered then it has to touch itself in its 
        observedObjectTouched() method with a flag different from NEW_OBSERVE 
        (i.e. make an invasive touch).

        When the touched object has been locked (both write- and read-locked)
        by the same thread that invokes the touch method, the touch-propagation
        is not done immediately. Instead the touch mask is stored internally.
        The recorded touches are propagated later when the last lock of the
        thread is released. This mechanism is included to circumvent deadlocks
        that can easily happen if the observing object tries to acquire locks
        on different objects inside the object's observedObjectTouched() method. 
        
        \param  inMask 
                Bitwise combination of touch flags. See VsObject::TouchFlag and
                similar enumarations of the subclasses. 
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT touch( unsigned int inMask=NEW_UNSPECIFIED );
    
    /** Gets touch number for last touch. A global counter of type unsigned int
        is maintained. This counter is incremented for each touch, and the new
        value is stored as touch number in the VsObject. 
        By comparing the touch number with a locally stored value of the past, 
        an application can determine whether a VsObject has been touched
        since a certain time.

        If the notification is disabled, the touch number is also not updated.

        \return 
                The touch number for the last touch. 
    */
    unsigned int touchNumber() const;

    /** Start observation of another object.
        If an observed object gets modified, i.e., if touch() is
        called on it, the method observedObjectTouched() gets invoked on all its 
        observer objects. Take care to avoid cycles in the observation graph.
        If the object was successfully added the method observedObjectAdded() 
        is called from inside this method.

        \param  inObject 
                The object that gets observed from now on. The method performs a 
                null operation if \c inObject is zero or references the observing 
                object itself. If \c inObject is already in the list of directly
                observed objects, the methods also does nothing.
                Note that it is an error to create cyclic observation dependencies. 
                Currently there is no detection of cycles in the observation graph,
                therefore, expect infinite looping or program crashes.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().        
    */
    VSRESULT observeObject( VsObject * inObject );

    /** Disconnect an observed object.
        After the object is disconnected by this method the method 
        observedObjectTouched() of the current object is no longer called if the
        \c inObject changes its state. Upon sucessfully disconnecting an object
        the method observedObjectRemoved() gets called from within this method.

        \param  inObject 
                the object that is no longer observed from now on. The method 
                performs no operation is \c inObject is zero or references an 
                object that is currently not observed.
                
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().  
    */
    VSRESULT ignoreObject( VsObject * inObject );

    /** TODO docu    
    */
    VSRESULT observedObjects( McDArray< McHandle<VsObject> > & outObjects );

    /** Enables/disables the notification of observing objects.
        Usually if an object gets touched, all objects observing this object are 
        notified via observedObjectTouched().
        Sometimes it's desired that this notification is suppressed.
        By default the notification is enabled. 
        
        \param  inFlag 
                Flag that indicates if notification gets enabled or not. 
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    VSRESULT enableNotification( bool inFlag );

    /** Get current status of notification enable flag.
       
        \return 
                If \c True, the notification is enabled and disabled on \c False. 
    */
    bool notificationEnabled();


protected:

    /** Indicates that an observed object was modified.
        This method will be called automatically when an observed object gets 
        modified, i.e., if the touch() method of an observed object is called.
        The default implementation just calls touch() with a bitmask set to 
        VsObject::NEW_OBSERVE. 
        This call in turn causes objects observing this object to be 
        notified recursively. Override this method to implement special actions
        which need to be performed if particular observed objects are changing.
        From a subclass's implementation, don't forget to call 
        VsObject::observedObjectTouched() or VsObject::touch()
        with the new observe bit set if you want recursive promotion of the touch.

        \param  inObject 
                The observed object that has changed. If zero, method does nothing.
        \param  inMask
                The bitmask that has been used for the touch on the observed object.
                Refer to VsObject::TouchFlag or corresponding enum types of derived
                classes for the semantics of particular flags.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT observedObjectTouched( VsObject * inObject, unsigned int inMask );

    /** Indicates that an object was added to the list of observed objects.
        This method will be called automatically when observation of an object begins.
        The default implementation recursively calls observedObjectAdded() also on all
        objects observing this object.

        \param  inObject
                The object that gets observed. If zero, method does nothing.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT observedObjectAdded( VsObject * inObject );

    /** Indicates that an object was removed from the list of observed objects.
        This method will be called automatically when an observed object was removed
        from the list of observed objects. The default implementation recursively 
        calls observedObjectRemoved() also on all objects observing this object.

        \param  inObject
                The object that was removed. If zero, method does nothing.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().
    */
    virtual VSRESULT observedObjectRemoved( VsObject * inObject );

    virtual void observerAdded( VsObject * inObserver );

    virtual void observerRemoved( VsObject * inObserver );


    //////////////////////////////////////////////////////////////
    //  Methods dedicated to implement the options-mechanism
    //////////////////////////////////////////////////////////////
public:

    /** Set an option of type integer.

        \param  inOption
                Identifier that addresses the option to be set. See Vs::Option.
        \param  inValue
                New value for that option.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().    
    */
    virtual VSRESULT setOptioni( int inOption, int inValue );

    /** Set an option of type double.

        \param  inOption
                Identifier that addresses the option to be set. See Vs::Option.
        \param  inValue
                New value for that option.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().    
    */
    virtual VSRESULT setOptiond( int inOption, double inValue );

    /** Retrieve current value of an integer option.

        \param  inOption
                Identifier that addresses the option to be retrieved. See Vs::Option.
        \param  outValue
                Reference to the location that will receive the current value of that option.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().    
    */
    virtual VSRESULT optioni( int inOption, int & outValue ) const;

    /** Retrieve current value of a double option.

        \param  inOption
                Identifier that addresses the option to be retrieved. See Vs::Option.
        \param  outValue
                Reference to the location that will receive the current value of that option.
        \return 
                If the method succeeds, the return value is #VS_OK. 
                To get extended error information, call Vs::lastError().    
    */
    virtual VSRESULT optiond( int inOption, double & outValue ) const;


    //////////////////////////////////////////////////////////////
    //  Backdoor
    //////////////////////////////////////////////////////////////
public:

    /** This method is used to invoke methods that are not part of the official API.
        These methods may be experimental, internal or customer specific.
        Using this multiplexer method, new functionality can be provided
        without losing binary compatibility to older versions.
        If there will be a new major release, the binary API may change and some of
        the functionality available though this method may become available as new
        set of methods part the new interface.

        \param  inEnum
                Identifier that addresses action to be performed.
        \param  userData
                Action-dependent data.
        \return 
                Action-dependent result. 
    */
    virtual void * extension( int inEnum, void * userData );
};


/** Helper class that locks and automatically unlocks an object.

    This is a convenience class that locks a VsObject object 
    in its constructor and unlocks it in its destructor. You should
    use this class as local variable. The variable will be automatically
    destroyed and the object will be unlocked if the current scope is
    left.

\code
    int VsCamera::setPosition(const McVec3f& pos)
    {
        VsObjectLocker locker(this);
        mPos = pos;
        return VS_OK;
    }
\endcode

   \sa VS_LOCK_OBJECT
*/
class VsObjectLocker
{

public:

    /** Constructor. The given object gets instantly locked.
        \param  inObject
                The object that is going to be locked. 
                If zero, no locking operations are performed.
        \param  inWriteLock
                If \c True, a write-lock is performed and a read-only lock on \c False.
        \param  inInterrupt
                If set and someone else is holding a lock on the object in question,
                the locker tries to interrupt this thread
        \param  inControl
                VsJobControl object which may receive cancel-signals
                from other threads that request a lock on the same object.
                \sa VsObject::lock()
    */
    VsObjectLocker( VsObject * inObject, bool inWriteLock = true, bool inInterrupt = true, VsJobControl * inControl = 0 )
    :   mObject ( inObject )
    {
        if (mObject)
        {
            if (inWriteLock)
                mObject->lock(inInterrupt, inControl); 
            else
                mObject->lockReadOnly(inInterrupt, inControl);
        }
    }

    void unlock()
    {
        if (mObject)
            mObject->unlock();
        mObject = 0;
    }

    /** Destructor. The locked object gets unlocked.
    */
    ~VsObjectLocker() 
    { 
        unlock();
    }

protected:

    VsObject * mObject;
};



/** \file VsObject.h
    Macros for convenient creation of local VsObjectLocker instances
*/

/// macro for convenient creation of local VsObjectLocker instances
#define VS_LOCK_OBJECT              VsObjectLocker _object_locker_w_(this);
                                                                                 
/// macro for convenient creation of local VsObjectLocker instances
#define VS_LOCK_OBJECT1(OBJ)        VsObjectLocker _object_locker_w1_(OBJ);
                                                                                 
/// macro for convenient creation of local VsObjectLocker instances
#define VS_LOCK_OBJECT_READ         VsObjectLocker _object_locker_r_(this, false);
                                                                                 
/// macro for convenient creation of local VsObjectLocker instances
#define VS_LOCK_OBJECT_READ1(OBJ)   VsObjectLocker _object_locker_r1_(OBJ, false);
                                                                                 
#endif                                                      

/// @}

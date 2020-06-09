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
#ifndef HX_THREAD_H
#define HX_THREAD_H

#include <limits.h>
#include <mclib/McHandable.h>
#include <hxcore/HxAmiraWinDLLApi.h>

#if !defined WIN32 && !defined WIN64
#define MyWaitCondition QWaitCondition
#endif

class QObject;
class QEvent;
class QMutex;
class QThread;
class QThreadStorageData;
class QxThreadNotifier;
class MyWaitCondition;

/** The minimal interface for an object which can be run (in the spirit of Java's Runnable).

    Right now you can pass an instance to HxThread::scheduleRunInMainThread() which 
    will asynchronously call run() in the main thread. 

    \todo HxThread should have a constructor HxThread(HxRunnable*).
  */
class HXCORE_API HxRunnable {
    public:
        ///
        HxRunnable ();
        
        ///
        virtual ~HxRunnable ();

        ///
        virtual void run () = 0;
};

/// A platform-independent thread class.
class HXCORE_API HxThread
{
  public:
    /// Returns a handle to the current thread.
    static void* currentThread();

    /// Terminates the current thread.
    static void exit();

    /// Constructor.
    HxThread();

    /// Destructor (does not terminate a running thread).
    virtual ~HxThread();

    /** Wait for a time-out or for a thread to terminate. The method waits
        until if the associated thread terminates or until the specified
        number of milliseconds have elapsed. In the first case true is
        returned, in the second case false is returned. */
    bool wait(unsigned long time = ULONG_MAX);

    /** Starts the thread. The overloaded method run() is execuated in a
        separate thread. If the thread is already running the method waits
        until it terminates and then starts it again. */
    void start();

    /// Checks if the thread has been finished or not.
    bool finished() const;

    /// Checks if the thread is running or not.
    bool running() const;

    /// Posts an Qt event from a thread. See Qt thread documentation for details.
    static void postEvent(QObject*, QEvent*);

    /** Call this function in the child thread to wake-up the main
        (event) thread. */
    void callThreadCallback(void* userData);

    /// System independent sleep for secs seconds.
    static void sleep(unsigned long secs);

    /// System independent sleep for msecs milliseconds.
    static void msleep(unsigned long msecs);

    /// System independent sleep for usecs microseconds.
    static void usleep(unsigned long usec);

    /** The object will be scheduled to be run (asynchronously) in the main thread.
        After successfully queueing the object the method returns immediately.
        It is your task to synchronize between threads. 
        If deleteAfterRun is true, the runner will be deleted after run() returns.
        If deleteAfterRun is false, it is your responsibility to delete the runner.
        If you call this method from the main thread, run() will be called immediately.
      */  
    static void scheduleRunInMainThread (HxRunnable* runner, bool deleteAfterRun = true);

  protected:
    QThread* qthread;
    QxThreadNotifier* threadnotifier;
    
    /// Override this function to do the actual work.
    virtual void run() = 0;
	
    /** This function is called in the main thread (asynchronously) if
        the child thread calls callThreadCallback(). */
    virtual void threadCallback(void* userData);
    
  friend class HxThreadP;
  friend class QxThreadNotifier;
};

/** The HxMutex class provides access serialization between threads.
    A mutex object can only be locked by one thread at a time. Calling
    lock() for an already locked mutex causes the calling thread to be
    suspended until the mutex is unlocked again. */
class HXCORE_API HxMutex
{
  public:
    /** Constructor. The mutex is created in an unlocked state. A recursive
        mutex is created if recursive is TRUE; a normal mutex is created if
        recursive is FALSE (the default). With a recursive mutex, a thread
        can lock the same mutex multiple times and it will not be unlocked
        until a corresponding number of unlock() calls have been made. */
    HxMutex(bool recursive = 0);

    /// Destructor.
    virtual ~HxMutex();

    /** Locks the mutex. If the mutex is already locked the method waits
        until the mutex gets unlocked again. */
    void lock();

    /** Attempt to lock the mutex. If the lock was obtained, this function 
        returns TRUE. If another thread has locked the mutex, this function 
        returns FALSE, instead of waiting for the mutex to become available, 
        i.e. it does not block.  */
    int tryLock();

    /// Unlocks a locked mutex.
    void unlock();

    /// Checks if the mutex is locked.
    bool locked();

    QMutex* qmutex;
};

/** Allows waiting and waking for conditions between threads. */
class HXCORE_API HxWaitCondition 
{
  public:
    /// Cosntructor.
    HxWaitCondition();

    /// Destructor.
    virtual ~HxWaitCondition();

    /** Wait for a wake call. The thread calling this will block until
        either of these conditions is met: Another thread signals it using
        wakeOne() or wakeAll(). This function will return TRUE in this
        case. time milliseconds has elapsed. If time is ULONG_MAX (the
        default), then the wait will never timeout (the event must be
        signalled). This function will return FALSE if the wait timed out. */
    bool wait(unsigned long time = ULONG_MAX);

    /** Release the locked mutex and wait on the thread event object. The
        mutex must be initially locked by the calling thread. If mutex is
        not in a locked state, this function returns immediately. If mutex
        is a recursive mutex, this function returns immediately. The mutex
        will be unlocked, and the calling thread will block until either of
        these conditions is met: Another thread signals it using wakeOne()
        or wakeAll(). This function will return TRUE in this case.   time
        milliseconds has elapsed. If time is ULONG_MAX (the default), then
        the wait will never timeout (the event must be signalled). This
        function will return FALSE if the wait timed out. The mutex will be
        returned to the same locked state.  This function is provided to
        allow the atomic transition from the locked state to the wait
        state. */
    bool wait(HxMutex * mutex, unsigned long time = ULONG_MAX);

    /** This wakes one thread waiting on the HxWaitCondition. The thread
        that is woken up depends on the operating system's scheduling
        policies, and cannot be controlled or predicted. */
    void wakeOne();

    /** This wakes all threads waiting on the HxWaitCondition. The order in
        which the threads are woken up depends on the operating system's
        scheduling policies, and cannot be controlled or predicted. */
    void wakeAll();

    MyWaitCondition* qwaitcondition;
};

/** Facilitates synchronization between multiple threads. */
class HXCORE_API HxThreadBarrier
{
  public:
    /// Creates a new barrier for @c count threads.
    HxThreadBarrier(int count);

    /// Destructor.
    virtual ~HxThreadBarrier(void); 

    /** Enter the barrier. The methods waits until as many threads as were
        specified in the constructor have entered the barrier. */
    int enter();

  private:
    int barrierCount;
    int barrierThreshold;
    int barrierCycle;

    QMutex* mutex;
    MyWaitCondition* waitCondition;
};

class HXCORE_API HxThreadStorageBase
{
  public:
    HxThreadStorageBase();
    ~HxThreadStorageBase();
    bool hasLocalData() const;
    void* localData() const;
    void setLocalData(void* data);

  protected:
    QThreadStorageData* d;
};

/** Class providing per-thread data storage. This class only
    accepts pointer types as a template argument. For each
    thread in an application a specific pointer can be stored
    using setLocalData(). It can be read using localData(). */
template <class T>
class HxThreadStorage
{
  public:
    /// Constructor.
    HxThreadStorage() { }

    /// Destructor.
    ~HxThreadStorage() { }

    /// Checks if a local data pointer has been set for the calling thread.
    bool hasLocalData() const { return base.hasLocalData(); }

    /** Returns the local data pointer associated with the calling thread.
        If no local data pointer has been set for this thread, NULL is
        returned. */
    T localData() const { return (T) base.localData(); }

    /** Sets a local data pointer for a the current thread. If there was
        already a local data pointer set, the old pointer will be
        overridden but the object the pointer pointed to will not be
        deleted. */
    void setLocalData(T data) { base.setLocalData((void*)data); }

  protected:
    HxThreadStorageBase base;
};

#endif

/// @}

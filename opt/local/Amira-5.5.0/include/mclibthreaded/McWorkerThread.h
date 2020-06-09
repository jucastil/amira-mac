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

/// @addtogroup mclibthreaded mclibthreaded
/// @{
#ifndef MC_WORKER_THREAD_H
#define MC_WORKER_THREAD_H

#include "McLibThreadedWinDLLApi.h"

class McWorkerThreadPrivate;

/** This class implements a worker thread. In contrast to the standard
    thread class McThread this class provides more sophisticated means
    of synchronization between the main thread and the worker thread.
    In particular, the worker thread is running permanently but it waits
    without consuming resources until the main thread calls start().
    While the worker thread is running, computation may be paused and
    resumed, or it may be canncelled completely.

    Derived classes should implement compute(). This method will be
    executed after the worker thread is started via start(). Inside
    the compute() method the worker thread should regularly call the
    two methods suspended() and canceled() in order to check if the main
    thread asked the worker thread to pause computation or to cancel
    it. Both methods simply check an internal state variable and do
    not require any locking or synchronization procedures.
*/
class MCLIBTHREADED_API McWorkerThread
{
    friend class McWorkerThreadPrivate;

public:

    /// Enumerates all states the worker thread can take on.
    enum State
    {
        TERMINATED      // underlying thread has terminated
    ,   WAITING         // waiting for the next invocation
    ,   RUNNING         // currently executing compute()
    ,   SUSPENDED       // the worker is halted for a pause
    ,   CANCELED        // last run of compute() got the cancel() signal
    ,   SHOULD_SUSPEND  // the worker should pause its computation but has not paused yet
    ,   SHOULD_CANCEL   // the current run of compute() should terminate asap 
    ,   SHOULD_EXIT     // thread is going to exit
    };

    /** Sets the name of the worker thread. The name is not used
        internally but may be helpful for testing and debugging. */
    void setName( const char * name );

    /** Returns the name of the worker thread. \sa setName() */
    const char * name() const;

    /** Returns the current state of the worker thread. */
    State state() const;

    /** Starts working. This method assigns the worker thread to
        call compute(). The method returns false if the worker
        thread is not waiting when calling this method.
        If inBlocking is set to true, the method blocks until
        the worker thread de-blocked the caller from inside compute()
        or compute() terminated.
    */
    bool start( bool inBlocking = false );

    /** De-block the thread that has invoked a blocking start().
    */
    void wakeCaller();

    /** Waits until the worker thread finished or accepted a suspend or
        cancel request. A time out interval can be specified in
        \c timeoutMsec (to be specified in milliseconds). If \c
        timeoutMsec is set to ULONG_MAX, the method will wait without
        a time limit. The parameter \c timeoutFlag will be set to \c
        true is a time out occurred. Otherwise, it will be set to
        \c false. The method returns \c true if the worker thread was
        actually running when this method was called (so the return
        value indicates whether the method waited at all or not). If
        the thread was not running, the method immediately returns
        \c false (and \c timeoutFlag is set to \c false as well). */
    bool wait( bool & timeoutFlag, unsigned long timeoutMsec );

    /** Waits until the worker thread finished or accepted a suspend or
        cancel request. This is an overloaded member function,
        provided for convenience. It essentially behaves like the above
        method, but it will wait without a time limit. */
    bool wait();

    /** Asks the worker thread to suspend its current operation. The
        method returns immediately. In order to wait for the worker
        thread to actually react on the suspend request, you should
        call wait(). The worker thread should call suspend() in regular
        intervals. */
    bool suspend();

    /** Tells the worker thread do resume computation. Calling this
        method causes the worker thread to return from a previous
        call of suspend(). The method returns false if the worker
        thread was not sucessfully suspended via suspend(). */
    bool resume();

    /** Tells the worker thread to cancel computation. If this
        method is called, a subsequent call to canceled() in the
        worker thread returns true, indicating that the worker
        thread should cancel its current computation. The method
        does not block. In order to ensure that the current
        operation was actually canceled or finished, call wait().
        The method works on a suspended worker thread as well.
        Suspended threads are automatically resumed, to allow them
        to cleanly cancel the computation. */
    bool cancel();

    /** Checks if the main thread requested the worker thread to
        pause. This method should be called frequently inside the
        compute() method of the worker thread. If the main thread
        called suspend(), the method blocks until the main thread
        calls resume(). The method returns true if computation was
        actually paused. This allows the worker thread to check if
        some resources have to be reallocated or reinitialized. */
    bool suspended();

    /** Checks if the main thread requested the worker thread to
        pause. This method should be called frequently inside the
        compute() method of the worker thread. */
    bool canceled();

    /** Terminates the worker thread. This method should be called
        from the destructor of a derived class. It terminates the
        worker thread, calling the overloaded version of computeDtor(). */
    void terminate();

    static void test();


protected:

    /** Constructor. The constructor does not actually start the
        working thread. This happens on-the-fly the first time
        start() is called from the main thread. */
    McWorkerThread( const char * name = "McWorkerThread" );

    /** Destructor. Derived classes should implement their own
        descructor and call terminate() in it. This is necessary in
        order to ensure that an overloaded version of computeDtor()
        will be called when the worker thread terminates. */
    virtual ~McWorkerThread();

    /** Compute constructor. This method is called synchronously
        inside the worker thread when the main thread the first time
        calls start(). */
    virtual void computeCtor();

    /** Compute method. This method will be called asynchronously
        inside the worker thread when the main thread calls start(). */
    virtual void compute();

    /** Compute destructor. This method is called synchronously
        inside the worker thread when the main thread calls
        terminate(). */
    virtual void computeDtor();


    McWorkerThreadPrivate * d;
};

#endif

/// @}

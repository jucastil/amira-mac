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

/// @addtogroup mclib mclib
/// @{
#ifndef MC_PROGRESS_INTERFACE_H
#define MC_PROGRESS_INTERFACE_H

#include "McWinDLLApi.h"
#include "McDArray.h"

class McProgressNode;

/** Abstract base class for a progress bar. Compute-intensive algorithms can
    use a @c McProgressInterface in order to report progress information
    and to check if the operation should be interrupted or not. The latter
    is achieved by calling McProgressInterface::wasInterrupted(). The Amira
    class HxWorkArea is derived from this class. For details see there.

    This class provides a mechanism for subdividing the progress bar in order
    to support multiple consequtive actions. A progress bar can be recursively
    subdivided into subranges using the command subdivide(). Then each pair of
    startWorking() and stopWorking() addresses the progress bar within a subrange.
    After all sub-tasks have terminated, undivide() should be called. The
    resulting structure is a tree of intervals. When busy, the progress has one
    active subrange as a leaf. stopWorking() automatically moves to the next
    sub-range.

    Example: We split the progress interval into two equal intervals and run
    a subtask in each of the intervals.
    \code
    void compute(McProgressInterface* progress)
    {
        progress->subdivide(2);

        progress->startWorking("First task");
        for (int i=0; i<10; i++) {
            progress->setProgressValue( i / 10.0);
            .... do fancy stuff ....
        }
        progress->stopWorking(); // finish first task and move to next interval

        progress->startWorking("Second task");
        for (i=0; i<10; i++) {
            progress->setProgressValue( i / 10.0);
            .... do even more fancy stuff ....
        }
        progress->stopWorking();

        progress->undivide();
    }
    \endcode
*/
class MCLIB_API McProgressInterface
{
public:
    /** Indicates the beginning of a non-interruptable time-consuming
        operation. During the operation itself information about the
        progress should be given using setProgressValue(). In contrast
        to busy() this method should be used when the operation takes
        longer than 5 seconds. A printf-like message string should be
        specified as an argument. */
    virtual void startWorkingNoStop(const char* format, ...);

    /** Indicates the beginning of an interruptable time-consuming operation.
        This method behaves similar as startWorkingNoStop() except that the
        user is allowed to interrupt the operation. In Amira the stop button
        becomes active when this method is called. During the operation the
        method McProgressInterface::wasInterrupted() should be call frequently
        in order to detect that the task should be terminated prior to completion. */
    virtual void startWorking(const char* format, ...);

    /** Indicates that time-consuming operation has been completed. For every
        call to startWorking() or startWorkingNoStop() there must be a
        corresponding call to this method. Multiple levels of calls to
        startWorking() or startWorkingNoStop() are allowed. After
        stopWorking() is called the previous state of the progress bar
        and the progress message are restored. */
    virtual void stopWorking();

    /// Set progress bar progress in the range 0..1.
    virtual void setProgressValue(float percentDone);

    /** Checks whether the current operation should be interrupted or not.
        In Amira, a local event loop is entered and it is checked if the user
        hit the stop button. In a multi-threaded context a derived class
        may just check for a flag set from the main thread. In any case,
        during a time-consuming interruptable operation this method should
        be called frequently. The default implementation always returns 0. */
    virtual int wasInterrupted(bool sync = true);

    /** Returns true if the calling thread has been paused inside this
        method. This method can be used in a multi-threading context in order
        for the main thread to suspend and resume a worker thread. The worker
        thread should frequently call wasSuspended(). Inside this method
        the thread may wait until some wake-up condition occurs. If this was
        the case true is returned. The default implementation always returns
        false. */
    virtual int wasSuspended();

    /// Updates text string displayed on the progress bar.
    virtual void setProgressInfo(const char* format, ... );

    /// Returns the current progress value.
    virtual float getProgressValue();

    /** Subdivides the current range into subranges. The relative size of the
        subranges is defined by the list of scalar values. */
    virtual void subdivide(McDArray<float>& scales);

    /** Subdivides the current range into multiple subranges of equal size.
        For example, after calling subdivide(3) and startWorking(),
        setProgressValue(1) will put the progress bar at 33% instead of 100%.
        See example in class description. */
    virtual void subdivide(int ranges);

    /** Undos subdividision. For every call of subdivide() there must be a
        matching call of undivide(). */
    virtual void undivide();

    /** Activates busy state. A derived class may choose to modifiy the mouse
        cursor in busy state. Calling startWorking() automatically activates
        busy state. You may call this method if you do not want to report
        progress information and also do not want the operation to be
        interrupted by the user. */
    virtual void busy() {}

    /** Deactivates busy state. You must call this method after calling
        busy() in order to indicate that the application is not busy anymore. */
    virtual void notBusy() {}

    /** Alternative initialization of the progress bar. Assuming you know
        how many steps your operation requires, you can do the following:

        @li Initially, call <tt>startWorking(numSteps, message)</tt>
        @li For every step call
        @code
        if (!progressStep()) { stop your work; }
        @endcode
        If you want to do several steps at once specify the number of
        steps a an argument of @c progressStep().
        @li Finally, call stopWorking().
    */
    void startWorking(int numSteps, const char* format, ...);

    void startWorkingNoStop(int numSteps, const char* format, ...);

    /** Notify, that a step is taken. Will return 0 on interruption. The
        argument @c n can be specified if multiple steps are performed at
        once. */
    int progressStep(int n=1);

  protected:
    McProgressInterface();
    virtual ~McProgressInterface();

    McProgressNode* mCurrentNode;
    McProgressNode* mRoot;

    int mNumSteps;
    int mStepsProcessed;

    /** Set value in the root interval. Derived classes should override
        this method. */
    virtual void setProgressValueGlobal(float howMuch);

	/** Sets text describing current task or subtask. Derived classes
	    should override this method. */
	virtual void setProgressText(const char* text);

    /// Go to next subrange. This is is next sibling in the tree.
    void nextRange();

    /// Returns to the parent of the current range.
    void parentRange();
};

#endif

/// @}

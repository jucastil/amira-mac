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
#ifndef PROGRESS_SENDER_IFACE_H
#define PROGRESS_SENDER_IFACE_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McInterface.h>

#include <QObject>

class McProgressNode;
class ProgressReceiverIface;

/**
 * This interface provides the sender part of a progress interface. The receiver part is provided 
 * by @see ProgressReceiverIface. The interface works similar to the old @see McProgressInterface
 * but is divided into a sender and a receiver part. 
 * The logic of subdividing/undividing a progress should be provided by implementations of this
 * interface. Thus, new receivers can be attached to a sender interface even if the progress
 * is already started. The sender can inform the receiver about its current state by sending
 * the appropriate signals (see @ProgressSenderIfaceGenImpl for such an implementation).
 * The connection is done using Qt signals and slots. All needed connections can automatically be 
 * established by using @see ProgressSenderIface::connect().
 *
 * @see ProgressSenderIfaceGenImpl provides a ready-to-use implementation of the interface.
 */
class HXCORE_API ProgressSenderIface : public QObject, public McInterface
{
    Q_OBJECT
    MC_INTERFACE(ProgressSenderIface);
public:
    /** 
       Indicates the beginning of a non-interruptable time-consuming
       operation. During the operation itself information about the
       progress should be given using setProgressValue(). In contrast
       to busy() this method should be used when the operation takes
       longer than 5 seconds. A message string should be specified as 
       an argument. 
     */
    void startWorkingNoStop(QString const &text) {doStartWorkingNoStop(text);}
    /// Convenient method for legacy code.
    void startWorkingNoStop(const char* format, ...);
    /** 
       Indicates the beginning of an interruptable time-consuming operation.
       This method behaves similar as startWorkingNoStop() except that the
       user is allowed to interrupt the operation. During the operation the
       method @see ProgressSenderIface::wasInterrupted() should be call 
       frequently in order to detect that the task should be terminated prior 
       to completion. 
     */
    void startWorking(QString const &text) {doStartWorking(text);}
    /// Convenient method for legacy code.
    void startWorking(const char* format, ...);
    /** 
       Indicates that time-consuming operation has been completed. For every
       call to startWorking() or startWorkingNoStop() there must be a
       corresponding call to this method. Multiple levels of calls to
       startWorking() or startWorkingNoStop() are allowed. After
       stopWorking() is called the previous state of the progress bar
       and the progress message are restored. 
     */
    void stopWorking() {doStopWorking();}
    /// Set progress bar progress in the range 0..1.
    void setProgressValue(float percentDone) {doSetProgressValue(percentDone);}
    /** 
       Checks whether the current operation should be interrupted or not.
       This method should be called frequently. 
     */
    bool wasInterrupted(bool sync = true) {return doWasInterrupted(sync);}
    /** 
       Returns true if the calling thread has been paused inside this
       method. This method can be used in a multi-threading context in order
       for the main thread to suspend and resume a worker thread. The worker
       thread should frequently call wasSuspended(). Inside this method
       the thread may wait until some wake-up condition occurs. If this was
       the case true is returned. 
     */
    bool wasSuspended() {return doWasSuspended();}

    /// Updates text string displayed on the progress bar.
    void setProgressInfo(QString const &text) {doSetProgressInfo(text);}
    /// Convenient method for legacy code.
    void setProgressInfo(const char* format, ... );
    /** 
       Subdivides the current range into subranges. The relative size of the
       subranges is defined by the list of scalar values. 
     */
    void subdivide(McDArray<float> &scales) {doSubdivide(scales);}
    /** 
       Subdivides the current range into multiple subranges of equal size.
       For example, after calling subdivide(3) and startWorking(),
       setProgressValue(1) will put the progress bar at 33% instead of 100%.
       See example in class description.
     */
    void subdivide(int ranges) {doSubdivide(ranges);}
    /** 
       Undos subdividision. For every call of subdivide() there must be a
       matching call of undivide().
     */
    void undivide() {doUndivide();}
    /** 
       Activates busy state. A derived class may choose to modifiy the mouse
       cursor in busy state. You may call this method if you do not want to 
       report progress information and also do not want the operation to be
       interrupted by the user. 
     */
    void busy() {doBusy();}
    /** 
       Deactivates busy state. You must call this method after calling
       busy() in order to indicate that the application is not busy anymore. 
     */
    void notBusy() {doNotBusy();}
    /** 
       Alternative initialization of the progress bar. Assuming you know
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
    void startWorking(int numSteps, QString const &text) {doStartWorking(numSteps, text);}
    /// Convenient method for legacy code.
    void startWorking(int numSteps, const char* format, ...);

    void startWorkingNoStop(int numSteps, QString const &text) {doStartWorkingNoStop(numSteps, text);}
    /// Convenient method for legacy code.
    void startWorkingNoStop(int numSteps, const char* format, ...);
    /** 
       Notify, that a step is taken. The argument @c n can be specified if 
       multiple steps are performed at once. 
    */
    void progressStep(int n=1) {doProgressStep(n);}
    /**
     * Establish all needed connections between a sender and a receiver interface.
     */
    virtual void connect(ProgressReceiverIface const *receiver) = 0;

public slots:
    void cancel() {doCancel();}
    void suspend() {doSuspend();}
    void resume() {doResume();}
    /**
     * Disconnects all connections between a sender and a receiver interface.
     */
    virtual void disconnect(ProgressReceiverIface const *receiver) = 0;

signals:
     void sigStartWorkingNoStop(QString const &text);
     void sigStartWorking(QString const &text);
     void sigStopWorking(bool);
     void sigSetInterruptible(bool);
     void sigSetProgressValueGlobal(float percentDone);
     void sigSetProgressInfo(QString const &text);

private:
    virtual void doStartWorkingNoStop(QString const &text) = 0;
    virtual void doStartWorking(QString const &text) = 0;
    virtual void doStopWorking() = 0;
    virtual void doSetProgressValue(float percentDone) = 0;
    virtual bool doWasInterrupted(bool sync) = 0;
    virtual bool doWasSuspended() = 0;
    virtual void doSetProgressInfo(QString const &text) = 0;
    virtual float doGetProgressValue() = 0;
    virtual void doSubdivide(McDArray<float> &scales) = 0;
    virtual void doSubdivide(int ranges) = 0;
    virtual void doUndivide() = 0;
    virtual void doBusy() = 0;
    virtual void doNotBusy() = 0;
    virtual void doStartWorking(int numSteps, QString const &text) = 0;
    virtual void doStartWorkingNoStop(int numSteps, QString const &text) = 0;
    virtual void doProgressStep(int n) = 0;

    virtual void doCancel() = 0;
    virtual void doSuspend() = 0;
    virtual void doResume() = 0;
};

/**
 * This class implements the sender part of a ProgressInterface (@see ProgressSenderIface).
 * It provides the same functionality as @see McProgressInterface.
 * New receivers can be attached even if the progress is already running. They will be
 * initialized correctly.
 *
 * @Note: Using the progress with the "numSteps" initialization is currently not compatible
 * with subdividing the progress.
 */
class  HXCORE_API ProgressSenderIfaceGenImpl : public ProgressSenderIface {
    Q_OBJECT
public:
    ProgressSenderIfaceGenImpl(McInterface *owner);
    ~ProgressSenderIfaceGenImpl();
    virtual void connect(ProgressReceiverIface const *receiver);
public slots:
    virtual void disconnect(ProgressReceiverIface const *receiver);
private:
    virtual void doStartWorkingNoStop(QString const &text);
    virtual void doStartWorking(QString const &text);
    virtual void doStopWorking();
    virtual void doSetProgressValue(float percentDone);
    virtual bool doWasInterrupted(bool sync);
    virtual bool doWasSuspended();
    virtual void doSetProgressInfo(QString const &text);
    virtual float doGetProgressValue() {return mPercentDone;}
    virtual void doSubdivide(McDArray<float> &scales);
    virtual void doSubdivide(int ranges);
    virtual void doUndivide();
    virtual void doBusy() {}
    virtual void doNotBusy() {}
    virtual void doStartWorking(int numSteps, QString const &text);
    virtual void doStartWorkingNoStop(int numSteps, QString const &text);
    virtual void doProgressStep(int n);
    
    virtual void doCancel();
    virtual void doSuspend();
    virtual void doResume();

    bool mStarted;
    bool mCanceled;
    bool mSuspended;

    QString mText;
    float   mPercentDone;
    bool    mInterruptible;

    // Methods needed locally
    /// Go to next subrange. This is is next sibling in the tree.
    bool nextRange();

    /// Returns to the parent of the current range.
    void parentRange();

    McProgressNode* mCurrentNode;
    McProgressNode* mRoot;

    int mNumSteps;
    int mStepsProcessed;
};

#endif //PROGRESS_SENDER_IFACE_H

/// @}

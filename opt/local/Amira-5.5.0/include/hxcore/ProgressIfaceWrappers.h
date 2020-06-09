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
#ifndef MC_PROGRESS_INTERFACE_WRAPPER_H
#define MC_PROGRESS_INTERFACE_WRAPPER_H

#include <hxcore/ProgressSenderIface.h>
#include <hxcore/ProgressReceiverIface.h>

#include <mclib/McProgressInterface.h>

class ProgressSenderIface;

/**
 * Wrapper to use objects implementing the @ProgressSenderIface with classes
 * expecting a @see McProgressInterface object.
 * I.e. this class can be used with legacy compute modules and new progress modules.
 *
 * Here is an example:
 *
 * @code
 * ProgressSenderIfaceGenImpl progressSender;
 * ProgressReceiverIface *progressReceiver = new SomeReceiver();
 * progressSender.connect(progressReceiver);
 *
 * McProgressInterfaceWrapper senderWrapper(&progressSender);
 *
 * McRawData::downSample3D(..., senderWrapper);
 * @endcode
 *
 * +----------------------------------+
 * | McProgressInterfaceWrapper       |
 * | (progressWrapper)                |
 * |  +----------------------------+  |      +--------------------+
 * |  | ProgressSenderIfaceGenImpl |  |      | SomeReceiver       |
 * |  | (progressSender)           |--+----->| (progressReceiver) |
 * |  +----------------------------+  |      +--------------------+
 * +----------------------------------+
 *
 */
class HXCORE_API McProgressInterfaceWrapper : public McProgressInterface
{
public:
    McProgressInterfaceWrapper(ProgressSenderIface *senderIface);

    virtual void startWorkingNoStop(const char* format, ...);
    virtual void startWorking(const char* format, ...);
    virtual void stopWorking();
    virtual void setProgressValue(float percentDone);
    virtual int wasInterrupted(bool sync = true);
    virtual int wasSuspended();
    virtual void setProgressInfo(const char* format, ... );
    virtual float getProgressValue();
    virtual void subdivide(McDArray<float>& scales);
    virtual void subdivide(int ranges);
    virtual void undivide();
    virtual void busy();
    virtual void notBusy();
    void startWorking(int numSteps, const char* format, ...);
    void startWorkingNoStop(int numSteps, const char* format, ...);
    int progressStep(int n=1);
private:
    ProgressSenderIface *mSenderIface;

};

//---------------------------------------------------------------------------

/**
 * Wrapper to use objects of type @see McProgressInterface with the 
 * @see ProgressSenderIface (non-thread-safe). 
 * See @see ProgressReceiverIfaceWrapper for a thorough documentaion.
 */
class HXCORE_API ProgressSenderIfaceWrapper : public ProgressSenderIface
{
public:
    ProgressSenderIfaceWrapper(McProgressInterface *mcProgressInterface);
    ~ProgressSenderIfaceWrapper();
    virtual void connect(ProgressReceiverIface const *receiver);
    virtual void disconnect(ProgressReceiverIface const *receiver);
private:
    virtual void doStartWorkingNoStop(QString const &text);
    virtual void doStartWorking(QString const &text);
    virtual void doStopWorking();
    virtual void doSetProgressValue(float percentDone);
    virtual bool doWasInterrupted(bool sync);
    virtual bool doWasSuspended();
    virtual void doSetProgressInfo(QString const &text);
    virtual float doGetProgressValue();
    virtual void doSubdivide(McDArray<float> &scales);
    virtual void doSubdivide(int ranges);
    virtual void doUndivide();
    virtual void doBusy();
    virtual void doNotBusy();
    virtual void doStartWorking(int numSteps, QString const &text);
    virtual void doStartWorkingNoStop(int numSteps, QString const &text);
    virtual void doProgressStep(int n);

    virtual void doCancel();
    virtual void doSuspend();
    virtual void doResume();

private:
    McProgressInterface *mMcProgressInterface;
};

//---------------------------------------------------------------------------

/**
 * Wrapper to use objects of type @see McProgressInterface with the 
 * @see ProgressReceiverIface. 
 *
 * This class can be used with new compute modules supporting 
 * @see ProgressSenderIface and legacy progress bars (e.g. theWorkArea).
 *
 * If the connection does not need to negotiate between a worker thread
 * and the main thread, @see ProgressSenderIfaceWrapper can be used instead
 * of this class. It establishes a direct connection between sender and receiver,
 * i.e., no qt connections are used.
 * 
 * Here is a thread-safe example using @see ProgressReceiverIfaceWrapper:
 *
 * @code
 * ProgressSenderIfaceGenImpl progressSender;
 * ProgressReceiverIfaceWrapper progressWrapper(theWorkArea);
 * progressSender.connect(&progressWrapper);
 * 
 * NewFancyComputeClass fancyCompute;
 * fancyCompute.doSomething(&progressSender);
 * @endcode
 *
 *                                     +------------------------------+
 * +----------------------------+      | ProgressReceiverIfaceWrapper |
 * | ProgressSenderIfaceGenImpl |      | (progressWrapper)            |
 * | (progressSender)           |----->|  +---------------------+     |
 * +----------------------------+      |  | McProgressInterface |     |
 *                                     |  | (theWorkArea)       |     |
 *                                     |  +---------------------+     |
 *                                     +------------------------------+
 *
 * And here is a non-thread-safe one using @see ProgressSenderIfaceWrapper:
 *
 * @code
 * ProgressSenderIfaceWrapper progressWrapper(theWorkArea);
 * NewFancyComputeClass fancyCompute;
 *
 * fancyCompute.doSomething(&progressWrapper);
 * @endcode
 *
 * +----------------------------+
 * | ProgressSenderIfaceWrapper |
 * | (progressWrapper)          |
 * |  +---------------------+   |
 * |  | McProgressInterface |   |
 * |  | (theWorkArea)       |   |
 * |  +---------------------+   |
 * +----------------------------+
 *
 */
class HXCORE_API ProgressReceiverIfaceWrapper : public ProgressReceiverIface
{
    Q_OBJECT
public:
    ProgressReceiverIfaceWrapper(McProgressInterface *mcProgressInterface);
    ~ProgressReceiverIfaceWrapper();
    /** Shedules the object for deletion.

        The Object will be delete when control returns to the Qt main thread's event loop
        (@see QObject::deleteLater()). After the object has been scheduled for deletion
        it will ignore all calls (signals) except for @see ProgressReceiverIface::stopWorking().

        This function can be used in situations where it's not feasible to keep a pointer
        to an instance of this wrapper class. Using this function it will be ensured, that
        the final @see ProgressReceiverIface::stopWorking() call (signal) won't be lost.

        @code
        { // beigin of scope
            ProgressSenderIfaceWrapper* progressWrapper = new ProgressSenderIfaceWrapper(theWorkArea);
            NewFancyComputeClass fancyCompute;
            fancyCompute.doSomething(progressWrapper);
            progressWrapper->deferredDelete();
        } // end of scope
        @endcode
    */
    void deferredDelete();

private:
    virtual void doStartWorkingNoStop(QString const &text);
    virtual void doStartWorking(QString const &text);
    virtual void doStopWorking(bool);
    virtual void doSetProgressValueGlobal(float percentDone);
    virtual void doSetProgressInfo(QString const &text);
    virtual void doSetInterruptible(bool);

    virtual void doCancel() {emit sigCancel();}
    virtual void doSuspend() {}
    virtual void doResume() {}
    virtual void doDisconnect() {}

    McProgressInterface *mMcProgressInterface;
    int mStartWorkingCounter;
    bool mAboutToDelete;
};

//---------------------------------------------------------------------------

#endif // MC_PROGRESS_INTERFACE_WRAPPER_H

/// @}

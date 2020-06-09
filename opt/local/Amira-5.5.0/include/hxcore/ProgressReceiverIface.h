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
#ifndef PROGRESS_RECEIVER_IFACE_H
#define PROGRESS_RECEIVER_IFACE_H

#include <hxcore/HxAmiraWinDLLApi.h>

#include <mclib/McInterface.h>

#include <QObject>

class McProgressNode;

/**
 * This interface provides the receiver part of a progress interface. The sender part is provided 
 * by @see ProgressSenderIface.
 *
 * This interface is kept simple. More complex logic, e.g., subdividing of a progress, should be
 * implemented in the sender part. Only a few methods need to be reimplemented.
 */
class HXCORE_API ProgressReceiverIface : public QObject, public McInterface
{
    Q_OBJECT
    MC_INTERFACE(ProgressReceiverIface);
public:
    /// Sends a cancel signal to the sender component of the interface.
    void cancel() {doCancel();}
    /// Sends a suspend signal to the sender component of the interface.
    void suspend() {doSuspend();}
    /// Sends a resume signal to the sender component of the interface.
    void resume() {doResume();}
    /// Disconnect from @see ProgressSenderIface
    void disconnect() {doDisconnect();}
public slots:
    void startWorkingNoStop(QString const &text) {doStartWorkingNoStop(text);}
    void startWorking(QString const &text) {doStartWorking(text);}
    void stopWorking(bool canceled) {doStopWorking(canceled);}
    void setInterruptible(bool isInterruptible) {doSetInterruptible(isInterruptible);}
    void setProgressValueGlobal(float percentDone) {doSetProgressValueGlobal(percentDone);}
    void setProgressInfo(QString const &text) {doSetProgressInfo(text);}
    

signals:
    void sigCancel();
    void sigSuspend();
    void sigResume();
    void sigDisconnect(ProgressReceiverIface const *);
private:
    virtual void doStartWorkingNoStop(QString const &text) = 0;
    virtual void doStartWorking(QString const &text) = 0;
    virtual void doStopWorking(bool) = 0;
    virtual void doSetInterruptible(bool) = 0;
    virtual void doSetProgressValueGlobal(float percentDone) = 0;
    virtual void doSetProgressInfo(QString const &text) = 0;

    virtual void doDisconnect() = 0;

    virtual void doCancel() = 0;
    virtual void doSuspend() = 0;
    virtual void doResume() = 0;
};

/**
 * This class can be used as basis for own classes implementing @see ProgressReceiverIface.
 */
class HXCORE_API ProgressReceiverIfaceGenImpl : public ProgressReceiverIface
{
    Q_OBJECT
public:
    ProgressReceiverIfaceGenImpl(McInterfaceOwner* owner = 0,
        McInterfaceOwner::MemoryPolicy mempolicy = McInterfaceOwner::DELETE_IFACE);
    ~ProgressReceiverIfaceGenImpl();

private:
    virtual void doStartWorkingNoStop(QString const &text);
    virtual void doStartWorking(QString const &text);
    virtual void doStopWorking(bool);
    virtual void doSetInterruptible(bool);
    virtual void doSetProgressValueGlobal(float percentDone);
    virtual void doSetProgressInfo(QString const &text);

    virtual void doDisconnect() {emit sigDisconnect(this);}

    virtual void doCancel() {emit sigCancel();}
    virtual void doSuspend() {emit sigSuspend();}
    virtual void doResume() {emit sigResume();}

};

#endif //PROGRESS_RECEIVER_IFACE_H

/// @}

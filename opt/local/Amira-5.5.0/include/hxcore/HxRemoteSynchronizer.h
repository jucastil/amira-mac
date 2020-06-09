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
#ifndef HX_REMOTE_SYNCHRONIZER_H
#define HX_REMOTE_SYNCHRONIZER_H


//---------------------------------------------------------------------------//
#include <stack>

#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>

#include <mclib/McBox2f.h>
#include <mclib/McHandle.h>
#include <mclib/McList.h>
#include <mclib/McString.h>
#include <mclib/McStringTokenizer.h>

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/SoVRSeparatorBase.h>

class HxFileFormat;
class SoEvent;
class SoPickStyle;
class QxSlot;
class HxRemoteSessionController;
class HxVRSessionController;

//---------------------------------------------------------------------------//
/** Helper class for distributing events in the Amira cluster version.
    This class can be used to send a Tcl command to the slave nodes in
    a cluster configuration. The constructor simply calls
    theRemoteSynchronizer->pushEval() with a command string which is built
    from the printf()-style format string. The destructor calls
    theRemoteSynchronizer->pop(). */
class HXCORE_API HxRemoteSynchronizerCmd {
public:
    /** Builds a Tcl synchronization command from its arguments. The
        command is sent to the slave nodes in a cluster configuration
        using theRemoteSynchronizer->pushEval(). */
    HxRemoteSynchronizerCmd(const char* fmt, ...);

    /** Calls theRemoteSynchronizer->pop(). */
    ~HxRemoteSynchronizerCmd();
};

//---------------------------------------------------------------------------//
class HXCORE_API HxVRSynchronizerCmd {
public:
    HxVRSynchronizerCmd(const char* fmt, ...);
    ~HxVRSynchronizerCmd();
};


/** Provides routines required for remote synchronization. 
    First, the Amira cluster version is an extension of the Amira virtual 
    reality package. It allows it Amira to run on a graphics cluster. 
    The basic assumption is that multiple Amira processes are running on 
    all the nodes of the graphics cluster. Each node is rendering a different 
    view of the scene but besides this all Amira processes are in the exact 
    same state and the same computations are performed on all nodes. 
    The methods provided by this class are intended to synchronize the different
    Amira processes. 
    Then, amiraTeamWork allows a pool synchronization between remote users, 
    with shared ability to modify the scene. One specificity is that the master 
    may change. On other side, the synchronization is less strict, since master 
    do not wait commands aknowlegements, and do not constraint rendering swapping.*/
class HXCORE_API HxRemoteSynchronizer 
{
  public:

    static HxRemoteSynchronizer* getTheRemoteSynchronizer();

    // return TRUE if either amiraTeamWork or amiraVR is active
    bool isActive() const;
    // return TRUE if this amira instance is remotely driven by either amiraTeamWork or amiraVR
    bool isSlave() const;
	
    // return TRUE if amiraTeamWork is active
    bool isTeamWorkActive() const;
    // return TRUE if this amira instance is a TeamWork slave (always FALSE if amiraTeamWork is not active)
    bool isTeamWorkSlave() const;
    // return TRUE if this amira instance is the TeamWork operator (always FALSE if amiraTeamWork is not active)
    bool isTeamWorkMaster() const;

    // return TRUE if amiraVR is active
    bool isVRActive() const;
    // return TRUE if this amira instance is an amiraVR slave (return TRUE even if amiraVR is not active)
    bool isVRSlave() const;
    // return TRUE if this amira instance is the amiraVR master (always FALSE if amiraVR is not active)
    bool isVRMaster() const;
	// returns TRUE if amiraVR has time compositing activated
	bool isVRTimeCompositing() const;

    /** Sends a Tcl command to the slaves, if necessary. This method
        should be used if some "event" occurs on the master which need to
        be send to the slave nodes as well. The "event" is encoded by a
        Tcl command. The method first increments the push level. If
        getPushLevel() was 0 before the Tcl command is actually send to
        the slaves and executed there. If getPushLevel() was bigger then 0
        before nothing happens. In this case it is assumed that the current
        event was triggered by some other event which already has been sent
        to the slaves and is executed there. Thus the current event will
        be triggered on the slaves automatically. An example:
        \code
        void load(const char* filename) {
            McString cmd;
            cmd.printf("load %s", filename);
            theRemoteSynchronizer->pushEval(cmd);
            // read the file here
            theRemoteSynchronizer->pop();
        }
        \endcode
        Instead of using pushEval() and pop() you may also use
        HxRemoteSynchronizerCmd for convenience. pop() will then be called
        automatically.
        \code
        void load(const char* filename) {
            HxRemoteSynchronizerCmd cmd("load %s", filename);
            // read the file here
        }
        \endcode
        The optional "restrictedCtrl" argument allows to send the command to 
        only one of the remote controllers.
    */
    void pushEval(const char* cmd, HxRemoteSessionController* restrictedCtrl = NULL);

    /** Tells the slave nodes to read and executed a script. This method
        behaves essentially like the standard pushEval(). However, if the
        script is located under $AMIRA_ROOT, this part of the file name
        will be replaced by the value of $AMIRA_ROOT on the slaves. */
    void pushEvalFile(const char* script, int interruptable);

    /** Tells the slave nodes to load a list of files. The files will be
        loaded using the specified file format. If a file is located under
        $AMIRA_ROOT, this part of the file name will be replaced by the
        value of $AMIRA_ROOT on the slaves. */
    void pushLoadFile(HxFileFormat* fmt, int n, const char* const* files);

    /** Decrements the push level. This command should be used to indicate
        that a synchronization "event" is completed. The method implies a
        barrier, i.e,, it waits until all nodes have called pop(). */
    void pop();

    /** Sends a Tcl command to the slaves, if necessary. This method
        is similar to pushEval() but it does not request an aknowlegement
        from the slaves inidcating that the command has been completed.
        After calling this method, popEvalNoOK() should be used to decrease
        the push level instead of pop(). */
    void pushEvalNoOK(const char*, HxRemoteSessionController* restrictedCtrl = NULL);

    void pushEmptyNoOK(HxRemoteSessionController* restrictedCtrl = NULL);

    /** Decrements the eval level after calling pushEvalNoOK(). In contrast
        to pop() this method does not imply a barrier. */
    void popNoOK();

    /** Returns false when called between push and pop methods.
        Setting restrictedCtrl will check only push/pop of that controller. */
    bool isEvalStackEmpty(HxRemoteSessionController* restrictedCtrl = NULL);

     /** Sends data from the master to the slaves. This method should be
        called by the master if certain data need to be synchronized
        between the master and the slaves. For example, imagine that the
        master is connected to some input device. The slaves cannot directly
        read data from the device. Instead the master sends the data
        using this method while the slaves read the data using receiveData().
        This is illustrated in the following example:
        \code
        float data[3];
        theRemoteSynchronizer->syncData(data,sizeof(float),3);
        \endcode
        The method does not include a barrier, i.e., syncData() may return
        before the slaves actually received the data. If needed you may call
        barrier() after syncData(). */
    void syncData(void* buffer, int elem_size, int count, 
                  HxRemoteSessionController* restrictedCtrl = NULL);

    /** Sends an integer value from the master to the slaves. This is an
        overloaded method. It behaves essentially like the above method. */
    void syncData(int& value, HxRemoteSessionController* restrictedCtrl = NULL) 
        { syncData(&value,sizeof(int),1,restrictedCtrl); }

    /** Sends an float value from the master to the slaves. This is an
        overloaded method. It behaves essentially like the above method. */
    void syncData(float& value, HxRemoteSessionController* restrictedCtrl = NULL) 
        { syncData(&value,sizeof(float),1,restrictedCtrl); }

    /** Sends a string from the master to the slaves. This is an
        overloaded method. It behaves essentially like the above method. */
    void syncData(McString& str, HxRemoteSessionController* restrictedCtrl = NULL);

	/** Sends data from a slave to the master
	The method does not include a barrier, i.e., syncDataBack() may return
	before the master actually received the data. If needed you may call
	barrier() after syncDataBack(). */
	void syncDataBack(int slaveID, char* buffer, int count, 
		HxRemoteSessionController* restrictedCtrl = NULL);

	/** Sends an integer value from a slave to the master. This is an
	overloaded method. It behaves essentially like the above method. */
	void syncDataBack(int slaveID, int& value, HxRemoteSessionController* restrictedCtrl = NULL); 

    /// Sends an inventor event to all slaves nodes
    void broadcastEvent(const SoEvent* e);

    void broadcastFile(const char* filename, bool asTmpFile=false, bool remove=false, HxRemoteSessionController* restrictedCtrl = NULL);

    /** Network barrier. You may use this method in your own code in
        order to synchronize code execution on all nodes of a cluster
        configuration. The method waits until all slaves have entered
        the barrier. 
        This only affects amiraVR, not TeamWork. */
    void barrier();

    /** This method is called by the viewers to synchronize the rendering. 
        This only affects amiraVR, not TeamWork. */
    void render();

    void setTeamWorkController(HxRemoteSessionController* ctrl);
    HxRemoteSessionController* getTeamWorkController() {return m_twCtrl;}

	void setTimeCompositingController(HxRemoteSessionController* ctrl);
	HxRemoteSessionController* getTimeCompositingController() {return m_tcCtrl;}

    HxVRSessionController* getVRController()       {return m_vrCtrl;}

    static void binaryEncode(
        unsigned char* data, int elem_size, int count, McString& msg);
    static unsigned char* binaryDecode(
        unsigned char* data, int elem_size, int count, unsigned char* msg);

    static void cameraEncode(const SoCamera*, McString&);
    static unsigned char* cameraDecode(SoCamera*, unsigned char*);

    void registerVRSeparator(SoVRSeparatorBase*);
    SoVRSeparatorBase* getVRSeparator() { return m_vrSep; }

    bool needPoolReload();
    void poolReload();

protected:

    HxRemoteSynchronizer();
    ~HxRemoteSynchronizer();

    void push(const McString& cmd, HxRemoteSessionController* restrictedCtrl);

    static void remoteRenderingCB(void *userData, SoAction* action);

SoINTERNAL public:

    void newMessage(HxRemoteSessionController* sender);
    void newConnection(HxRemoteSessionController* sender,int remoteID);
    void stateChanged(HxRemoteSessionController* sender);

    const McString& getLastReceivedTmpFile() const { return m_tmpFile; }

private:

	// TeamWork controller
    HxRemoteSessionController* m_twCtrl;
	// VR controller
    HxVRSessionController* m_vrCtrl;
	// Time compositing controller. Used in combination with the VR controller
	HxRemoteSessionController* m_tcCtrl;

    // hidden Qt slots 
    QxSlot* m_newMessageSlot;
    QxSlot* m_newConnectionSlot;
    QxSlot* m_stateChangedSlot;

    int m_twLevel;
    int m_vrLevel;
    std::stack<HxRemoteSessionController*> m_incrementLevelStack;

    SbViewportRegion    m_masterViewerViewport;
    McBox2f             m_masterViewerTile;
    McHandle<SoCamera>  m_masterCamera;

    McHandle<SoVRSeparatorBase> m_vrSep;

    McString m_tmpFile;
};

// Global instance.
#define theRemoteSynchronizer (HxRemoteSynchronizer::getTheRemoteSynchronizer())

#endif // HX_REMOTE_SYNCHRONIZER_H

/// @}

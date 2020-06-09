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
#ifndef HX_VR_SESSION_CONTROLLER_H
#define HX_VR_SESSION_CONTROLLER_H

#include <hxcore/HxRemoteSessionController.h>

#include <mclib/McListQueue.h>

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcom/HxScSocket.h>

class HxPreferences;

class QxServerSocket;

//---------------------------------------------------------------------------//
struct HxVRNode {
    McString host;
    int port;
    Q3Socket* socket;
    HxScSocket* frameSocket;
    int status;
};

//---------------------------------------------------------------------//
class HXCORE_API HxVRSessionController : public HxRemoteSessionController
{
    Q_OBJECT

public:

	struct DataInfo {
	public:
		unsigned int size;
		DataInfo(unsigned int theSize): size(theSize) {} 
		DataInfo(const McString &string): size(string.length()) {}
	};


    HxVRSessionController();
    virtual ~HxVRSessionController();

    virtual bool isMaster() const;
    virtual bool isSlave() const;

    int getMasterScreen() const { return m_masterScreen; }

    //master-side methods
    void initMaster(const McDArray<McString>& slaves, const McString& configFile, int masterScreen);
    void resetMaster();

    int getNumSlaves() const;
    const McString& getSlave(int slaveID) const;
    int getSlaveID(const McString& host) const;
	  virtual int getFrameSlaveID() const { return 0; };

    void startSlave(int slaveID);
    void startSlaves() { startSlave(-1); }
    void stopSlave(int slaveID);
    void stopSlaves() { stopSlave(-1); }
    bool isConnected(int slaveID) const;

    void sendToSlave(int slaveID, const McString& msg);
    void sendToSlaves(const McString& msg) { sendToSlave(-1, msg); }
	void sendToSlaves(const McString *msg);
    void waitAcknowledge(int slaveID, const McString& ack);
	void waitAcknowledge(const McString *acks);
    void waitAcknowledges(const McString& ack) { waitAcknowledge(-1, ack); }
    void waitBlocking(int slaveID, const McString& msg);

    virtual void sendTo(int remoteID, const McString& msg) { sendToSlave(remoteID, msg); }
    virtual void sendToAll(const McString& msg) { sendToSlaves(msg); }
	  void receiveFromSlave(int slaveID, void *buffer, int maxLen);

	void barrier() { barrier(-1); }
	void barrier(int slaveID);

    virtual void render();
    void generateFrame();
	
    //slave-side methods
    void initSlave(int id, const McDArray<McString>& masterAddrs, int port);
    int getSlaveID() const;
    void connectToMaster();

    void sendToMaster(void *buffer, int size);
    void returnAcknowledge(const McString& ack);

    virtual bool handleDelayedMessage(const McString& msg);

    virtual void initConnection(HxRemoteSessionController* ctrl, int remoteID);

protected slots:

    void connectedToSlave(int);
    void connectedToMaster();
    virtual void socketError();

    /**
     *  To be notified that preferences changed.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

protected:

    virtual bool handleImmediateMessage(const McString& msg);

    virtual Q3Socket* mainSocket() { return m_master.socket; };

    int connectToSlave(int slaveID);
    void waitAndDesync(int slaveID, const McString& msg, int timeout);

    bool m_masterFlag;
    
    // master-side variables
    McString m_configFile;
    McDArray<HxVRNode> m_slaves;
    QxServerSocket* m_serverSocket;
    int m_desyncTimeOut;
    int m_resyncTimeOut;
	  HxScSocket*	m_frameServerSocket;

    // slave-side variables
    int m_slaveID;
	  int	m_numSlaves;
    HxVRNode m_master;
    McListQueue<McString> m_alternativeMasterAddresses;

    int m_masterScreen;
    int m_barrierID;
	McDArray<int> m_barrierIDs;

    /**
     *  Send preferences to slaves.
     */
    void syncPreferences();
};

#endif // HX_VR_SESSION_CONTROLLER_H


/// @}

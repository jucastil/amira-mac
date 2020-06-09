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

/// @addtogroup hxtrackd hxtrackd
/// @{
#ifndef SPACEPADCLIENT_H
#define SPACEPADCLIENT_H

#include <mclib/McWatch.h>
#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McRotation.h>

#include <hxtrackd/HxTrackingSystem.h>

#ifdef __linux
#define USE_PTHREADS 1
#endif

#ifdef __hpux
#define NO_THREADS 1
#endif

#ifdef __sgi
#define USE_PTHREADS 1
#endif

#if defined WIN32 || defined WIN64
#define USE_QTHREADS 1
#endif

/** This class establishes a connection to a SpacePad server. Once the
    client is connected to the server positions and orientations of
    active 3D-sensors are sent to the client, where they may be interpreted
    by the application. In addition, the application by send certain
    commands to the server, thereby examining or changing the configuration
    of the SpacePad 3D-tacking system.

    The SpacePad system can handle up to 4 3D-sensors (receivers) and
    up to 2 antennas (transceivers). Usually only 2 receivers and 1
    transceiver will be installed. In order to obtain data from a receiver
    it must be activated, i.e., attached to one of the transceivers.
    This can be done using the command @c changeConfiguration(). On default,
    the first receiver (Rx1) is attached to transceiver Tx1, while all
    other receivers possibly installed in the system are deactivated
    (ReceiverConfig=OFF).
*/
class SpacePadClient : public HxTrackingSystem
{
  public:
    /// Constructor.
    SpacePadClient();

    /// Destructor.
    virtual ~SpacePadClient();

    /// Returns the number sensors the tracker daemon is storing.
    virtual int getNumberOfSensors();

    /// Gets the position values for sensor[id].
    virtual void getPosition(int id, float* pos);

    /// Gets the transformation matrix for sensor[id].
    virtual void getMatrix(int id, float mat[4][4]);

    /// Returns the number of buttons the tracker daemon is storing.
    virtual int getNumberOfButtons();

    /// Returns the value of button[id] from the tracker daemon.
    virtual int getButton(int id);



    /// Connect to remote server, start main loop as separate thread.
    int connect(const char* hostname, int port=7200);

    /// Check if client is connected to server.
    virtual bool isConnected() { return (sd>=0); }

    /// Disconnect from server, terminates main loop thread.
    void disconnect();

    /// Receiver configurations.
    enum ReceiverConfig {
	/// Receiver is inactive, no data is sent.
	OFF = 0,
	/// Receiver is attached to antenna 1.
	Tx1 = 1,
	/// Receiver is attached to antenna 2 (may not be installed).
	Tx2 = 2
    };

    /// Return current receiver configuration.
    int examineConfiguration(ReceiverConfig receiver[4]);

    /// Change current receiver configuration.
    int changeConfiguration(ReceiverConfig receiver[4]);

    /// Examine software revision number.
    unsigned int examineSoftwareRevisionNumber();

  protected:
    int initSocket(long ipaddr, int port);
    void closeSocket();

    /*  If no threads are being used, this method has to be called in order
        to process the data sent by the server. It performs non-blocking
        reads until no more data is available. This is called for example
        from @c getPosition() or from @c sendMessageAndReceive(). */
    int checkInput();

    // Main loop used in multi-threaded version, performs blocking read.
    int mainLoop();

    void processMessage(McString& msg);
    int sendMessage(const McString&);
    int sendMessageAndReceive(const McString& msg, McString& answer);

    int sd;
    McString* answer;
    int isRunning;
    int waitingForAnswer;
    int terminateMainLoop;

    McVec3f pos[4];
    McVec3f euler[4];
    unsigned int buttonStatus;

#ifdef NO_THREADS
    static void timeOut(void* userData);
#endif

#ifdef USE_PTHREADS
    static void* pthreadEntry(void* userData);
#endif

#ifdef USE_QTHREADS
    friend class SpacePadClientThread;
#endif

    McString msg;
    char* msgPointer;
    int numMissingBytes;

    McWatch watch;
    int pointMessageCount;
};

#endif 

/// @}

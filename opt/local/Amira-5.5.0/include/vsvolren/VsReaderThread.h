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
#ifndef VS_READER_THREAD_H
#define VS_READER_THREAD_H

#ifndef VS_NO_QT
#include <QObject>
#include <QThread>
#else
#define QObject void
#endif

#include <mclib/McPrimType.h>
#include <mclib/McDArray.h>
#include <mclib/McWatch.h>

#include "VsServer.h"

/** Reader thread for client-server communication. This thread performs
    a blocking read on a socket. As soon as a command is received the
    command is inserted into the VsServer command queue and the signal
    newCmdAdded() is emitted. */
class VSVOLREN_API VsReaderThread
#ifndef VS_NO_QT
:   public QThread
#endif
{
#ifndef VS_NO_QT
    Q_OBJECT
#endif

    // VsServer must be able to access mSd in order to enable/disable TCP_NODELAY
    friend class VsServer;

public:    

    /** Constructor.
        On the client the thread is created in VsServer::connectToServer().
        On the server the object is created in VsServer::startServer().
    
        \param inSocketDesc Socket descriptor of the client-server connection.
            The socket must already be in a connected state.
        \param inDoEncrypt True if traffic should be encrypted using SSL.
            If encryption should be enabled or not is decided in the initial
            handshake, see VsServer::handshake().
    */
    VsReaderThread(int inSocketDesc, bool inDoEncrypt);

    mcint64 bandwithSendMax();
    mcint64 bandwithReadMax();

    void bandwithSendMeasureStart();
    void bandwithSendMeasureStop();

    void bandwithReadMeasureStart();
    void bandwithReadMeasureStop();

    /** Appends a received command to the command queue and wakes the main thread
        or sends it a signal. Later, the main thread calls processCmdQueue() and
        executes the command. */
    int processCommand( VsServer::Cmd * inCmd );

    // sends a heartbeat to the remote side and waits msec milliseconds for the response.
    // if msec is -1 it waits until the response arrived or an error occours.
    // returns roundtrip time in seconds.
    float ping( int inMsec = -1 );


    ////////////////////////////////////////
    // abstracts
    ////////////////////////////////////////

    virtual int  send( unsigned char const * inData, int inLen, bool inFlush = false ) = 0;
    virtual void waitForInit() = 0;
    virtual bool connected() = 0;
    virtual void flush(){}

    mcint64 numBytesSent() const { return mTotalBytesSent; }
    mcint64 numBytesRead() const { return mTotalBytesRead; }

#ifndef VS_NO_QT
signals:
    // Emitted after a command was added to the command queue.
    void sig_newCmdAdded();

    // Emitted if the connection was lost and the reader thread terminated.
    void sig_terminated( const QString & errorMessage );
#endif

protected:
    int     mSocket; // socket descriptor
    bool    mDoEncrypt;

    McMutex         mPingMutex;
    McWaitCondition mPingWait;
    float           mPingLastRecvdSendTime;


    McDArray<mcint64>   mBWR_samples;
    int                 mBWR_samplesCurrIdx;
    int                 mBWR_startCount;
    int                 mBWR_startNumBytes;
    McWatch             mBWR_watch;

    McDArray<mcint64>   mBWS_samples;
    int                 mBWS_samplesCurrIdx;
    int                 mBWS_startCount;
    int                 mBWS_startNumBytes;
    McWatch             mBWS_watch;

    mcint64             mTotalBytesRead;
    mcint64             mTotalBytesSent;
    bool                mTerminating;
};

#ifdef QObject
#undef QObject
#endif

#endif

/// @}

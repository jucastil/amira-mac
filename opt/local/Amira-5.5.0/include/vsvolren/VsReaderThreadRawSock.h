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
#ifndef VS_READER_THREAD_RAWSOCK_H
#define VS_READER_THREAD_RAWSOCK_H

#include "VsReaderThread.h"

#include <mclib/McMemArray.h>
#include <mclib/McWatch.h>
#include <mclib/McMemArray.h>
#include <mclib/McMemArray.h>

#ifndef VS_NO_QT

#include <openssl/ssl.h>

class QTcpSocket;

#else

#define QObject void

#endif


////////////////////////////////////////////////////////////////////////////////
/** Reader thread for client-server communication. This thread performs
    a blocking read on a socket. As soon as a command is received the
    command is inserted into the VsServer command queue and the signal
    newCmdAdded() is emitted. */
class VsReaderThreadRawSock
:   public VsReaderThread
{
#ifndef VS_NO_QT
    Q_OBJECT
#endif

    // VsServer must be able to access mSd in order to enable/disable TCP_NODELAY
    friend class VsServer;

public:    
    VsReaderThreadRawSock(int inSocketDesc, bool inDoEncrypt);

    ////////////////////////////////////////
    // override QThread
    ////////////////////////////////////////

    virtual void run();


    ////////////////////////////////////////
    // override VsReaderThread
    ////////////////////////////////////////

    virtual int  send( unsigned char const * inData, int inLen, bool inFlush = false );
    virtual void waitForInit();
    virtual bool connected();
    virtual void flush();


private:

#ifndef VS_NO_QT

    /** Reads a remote command from the socket and inserts it into the
        VsServer command queue. This method is called in the thread's
        run() method.
        \param socket Pointer to a QTcpSocket the command should be read from.
            If null native socket functions are used to read from the socket
            specified in the constructor.
         \param outCmd Reference to a pointer that gets bend to the newly received command.
            Null on error.
        \return 1 on success, 0 if socket was closed, -1 if a socket read
            error occured, -2 if comporessed data could not be uncompressed.
    */
    int readCommand( QTcpSocket * socket, VsServer::Cmd * & outCmd );

    int receive( QTcpSocket * socket, unsigned char * dest, int len );
    int safeSend( const unsigned char * inData, int inLen );

#endif

    bool initSSL(bool isClient);

private:

    McWatch                     mReadWatch;
    McWatch                     mSendWatch;
    mcint64                     mNumBytesRead;
    mcint64                     mNumBytesSent;
    McMemArray<unsigned char>   mCompressedBuffer;

    bool                        mConnected;

    // send buffer
    McMutex                     mSendBufferMutex;
    McMemArray<unsigned char>   mSendBuffer;
    int                         mSendBufferLen;

#ifndef VS_NO_QT
    SSL_CTX* ssl_ctx;
    SSL* ssl;
    bool mUseSSL;
#endif
};

#ifdef QObject
#undef QObject
#endif

#endif

/// @}

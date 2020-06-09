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
#ifndef VS_SERVER_H
#define VS_SERVER_H

#include "VsRenderQueue2.h"

#include "Vs.h"
#include "VsInterface.h"
#include "VsMsg.h"
#include "VsObject.h"


#ifdef CursorShape
#undef CursorShape
#endif

#ifndef VS_NO_QT
#   include <QObject>
#endif

#include <stdarg.h>

#include <mclib/McHandle.h>
#include <mclib/McList.h>
#include <mclib/McString.h>
#include <mclib/McHashTable.h>
#include <mclib/McWatch.h>

#include <mclibthreaded/McMutex.h>
#include <mclibthreaded/McWaitCondition.h>


class VsCompressor;
class VsRemoteRenderer;
class VsServerPeer;
class QTcpSocket;

////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_API VsServer
#ifndef VS_NO_QT
:   public QObject
#endif
{
#ifndef VS_NO_QT
    Q_OBJECT
#endif
    friend class VsServerThread;
    friend class VsReaderThread;
    friend class VsReaderThreadRawSock;


protected:

    VsServer();
   
    virtual ~VsServer();


public:
    /** Returns server instance. In local mode, a null pointer is returned.
        In fake mode (server running in a thread, see startLocalServer())
        a pointer to the local or remote server object is returned depending
        on the scope of the calling thread. */
    static VsServer * instance();

    enum SSLMode
    {
        SSL_ON = 0,
        SSL_OFF = 1,
        SSL_AUTO = 2
    };

    static void registerThread( bool useRemoteServer=true );

    static VSRESULT connectToServer(const char* hostname, int port);

    static VSRESULT disconnectFromServer();

    static VSRESULT startServer(int sd, SSLMode sslMode);

    // True on client side, false on server side.
    bool isClient() const;

    // Returns the name of the render server as specified in connectToServer()
    const char* renderServer() const;

    // the type of the remote operating system
    enum RemoteOS
    {
        OS_LINUX    = 0,
        OS_WINDOWS  = 1
    };

    RemoteOS remoteOS();

    VsServerPeer * peer() const;

    // returns the thread ID where the VsServer inctance is created in. (usually the main thread)
    unsigned long mainThreadId();

    // query the time (seconds since timesync on start of communication)
    float time();


    enum VsServerLogType
    {
        LT_INFO  = 1 << 0
    ,   LT_ERROR = 1 << 1
    };

    static void debug_log( int inType, const char * format, ... );

    enum StatType
    {
        STAT_READ_BANDWIDTH  // in bits/sec
    ,   STAT_SEND_BANDWIDTH  // in bits/sec
    ,   STAT_NUM_CALLS
    ,   STAT_NUM_REMOTE_OBJECTS
    ,   STAT_NUM_RENDER_REQUESTS
    ,   STAT_NUM_RECEIVED_IMAGES
    ,   STAT_NUM_RENDERED_IMAGES
    ,   STAT_IMAGE_SIZE_PIXELS
    ,   STAT_COMPRESSION_RATIO
    };

    void getStatistics( StatType, McDArray<unsigned int> & result );

    // Updates the current read bandwidth, called by reader thread
    void setReadBandwidth(unsigned int numBytesPerSecond);
    // Updates the current send bandwidth, called from reader thread's send() method
    void setSendBandwidth(unsigned int numBytesPerSecond);
    // Returns total number of received bytes, called in WAN statistics dialog.
    mcint64 numBytesRead() const;
    // Returns total number of sent bytes, called in WAN statistics dialog.
    mcint64 numBytesSent() const;

    // adds number of pixels received
    void addImageSizeStats(unsigned aPixels);
    // adds number of bytes of compressed images received and amount of bytes these occupy after decompression
    // then computes compression ratio
    void addCompressionRatioStats(unsigned aOriginalBytes, unsigned aCompressedBytes);
    // resets dedicated counter of compressed image bytes recieived
    void resetImageBytesReceived();
    // returns dedicated counter of compressed image bytes recieived
    unsigned getImageBytesReceived();
    // increase number of remode render requests for statistics
    void incrementRenderRequestCount();
    // increase number of received images for statistics
    void incrementReceivedImageCount();
    // increase number of rendered images for statistics
    void incrementRenderedImageCount();



    ////////////////////////////////////////
    // per frame statistics
    ////////////////////////////////////////

    class FrameSample
    :   public McLink
    {
    public:
        float           mTime;
        float           mTimeToLast;
        McString        mCaption;
        mcint64         mThreadId;
        bool            mIsClient;
    };

    class FrameLog
    :   public VsHandable
    {
    public:

        mcint64                 mId;
        McList<FrameSample>     mSamples;
    };

    McHashTable< int, McHandle<FrameLog> >  mFrameLogs;
    McMutex                                 mFrameLogsMutex;

    void frameSampleAdd( mcint64 inFrameId, char const * inCaption );
    void frameRemove( mcint64 inFrameId );
    void frameLog( FrameLog * inLog );
    void frameSamples( mcint64 inFrameId, VsMsg & outMsg );
    void frameSamplesAdd( mcint64 inFrameId, VsMsg & inMsg );
    static bool frameSamplesEnabled();


    ////////////////////////////////////////
    // remote call of methods
    ////////////////////////////////////////


    // Messages are sent to specific instances of VsObject by addressing them with their object-ID.
    // If the transmitted object-ID is zero, the message is handled by the VsServer instance.
    // The transmitted func-ID then then is a command-ID rather than a method index in the target object.
    // Following command-IDs are supported:
    enum VsServerCommands
    {
        FUNC_ID_CREATE_OBJECT = 0
    ,   FUNC_ID_DELETE_OBJECT = 1

    ,   FUNC_ID_PING          = 3
    ,   FUNC_ID_PONG          = 4
    ,   FUNC_ID_DISCONNECT    = 5

    ,   FUNC_ID_MAX
    };

    void remoteCall( VsInterface * inObject, int funcID, VsMsg & inArgs, bool inDelayed=false, bool inCompress=true );

    void remoteCallLastSent( int & outObjectID, int & outFuncID );
    void remoteCallLastInvoked( int & outObjectID, int & outFuncID );

    // process all pending specific commands for a specific object
    // the processed commands are removed from the command queue
    void processCmd( int inObjectId, int inFuncId );

    void socketSetNagle( bool inDoNagle );
    void socketFlush();

    // returns true as long the network connection to the remote machine is established
    bool isConnected();

    // tracing for sync calls
    // intended to detect unsupported overlapping sync calls
    static void traceSyncCall( bool inEntering, VsInterface * ioObject );


    ////////////////////////////////////////
    // object management
    ////////////////////////////////////////

    void deregisterLocalObject( int inObjectId );


    void createRemoteObject( const char* inClassName, VsInterface * inObject );

    void deleteRemoteObject( VsInterface * object );

    VsInterface * findObject( int const inObjectId );

    // Checks if remote objects should be created or not (thread-local).
    static bool remoteObjectConstructionEnabled();

    // Enables or disables remote object creation in calling thread, returns previous value.
    static bool enableRemoteObjectConstruction(bool enabled);

    // create a remote-object
    void createObject( VsMsg & msg );

    // delete a remote-object
    void deleteObject( VsMsg & msg );


    ////////////////////////////////////////
    // method invoke level (depth of call stack inside the vsvolren)
    ////////////////////////////////////////

    // Returns call level in current thread (thread-local storage)
    static int & level();

    // Increments call level in current thread.
    static void levelUp() { ++level(); }

    // Decrements call level in current thread.
    static void levelDown() { --level(); }


    ////////////////////////////////////////
    // rendering
    ////////////////////////////////////////

    // Sets rendermask, i.e., which type of rendering shall be performed by renderer (thread-local).
    static void setRenderMask(unsigned int mask);

    // Gets the rendermask, returns previous value.
    static unsigned int renderMask();

 
    // get the render queue
    VsRenderQueue2 * renderQueue();

    // on server side, get the renderer that is responsible for rendering all the scenes
    static VsRemoteRenderer * theRemoteRenderer();

        
    void addCompressor( VsCompressor * );
    void setPreferredCompressor( int id );
    VsCompressor * compressor( int id = -1 ) const;


#ifndef VS_NO_QT

    public slots:
    void readerThreadTerminated(const QString& errorMessage);
#endif

    void processCmdQueue( bool inWaitForCmd = false );
    
    static bool setCmdQueueEnabled(bool value);

    void processRenderQueue();
    
#ifndef VS_NO_QT

signals:

    void newCmdAdded();
    void CriticalError(const char * text);

#endif


public:

    ////////////////////////////////////////
    // singletons
    ////////////////////////////////////////

    class VsWANImageSender      * mImageSender;
    class VsWANDataSender       * mDataSender;
    class VsReaderThread        * mReaderThread;
    class VsServerPeer          * mPeer;
    class ExDataManager         * mDataManager;
    class VsBackendPeer         * mBackendPeer;
    class VsVolumeInfoCache     * mVolumeInfoCache;
    class VsJobController       * mJobController;


private:

    int             mLastObjectID;  // objectID that was assigned to the last created object on this side (separate for client and server)

    bool            mIsClient;

    RemoteOS        mRemoteOS;


    unsigned long   mMainThreadId;

    // incremented each time a call-command arrives from the other side
    int             mCountCMDRecv;

    // incremented each time a call-command is send to the other side
    int             mCountCMDSend;

    // list of all objects
    McHashTable< int, VsInterface* >    mObjects;
    McMutex                           * mObjectsMutex;


    ////////////////////////////////////////
    // statistics
    ////////////////////////////////////////

    struct StatData
    {
        StatData()
        {
            mNumBytesReceive    = 0;
            mNumBytesSent       = 0;
            mNumCalls           = 0;
            mNumObjects         = 0;
            mNumRenderRequests  = 0;
            mNumReceivedImages  = 0;
            mNumRenderedImages  = 0;
            mImageSizePixels    = 0;
            mCompressionRatio   = 0;

            // intermediate statistics values
            mImageSizePixelsAbs             = 0;
            mImageSizePixelsSamples         = 0;
            mCompressionBytesOriginal       = 0;
            mCompressionBytesCompressed     = 0;
        };

        unsigned int mNumBytesReceive;
        unsigned int mNumBytesSent;
        unsigned int mNumCalls;
        unsigned int mNumObjects;
        unsigned int mNumRenderRequests;
        unsigned int mNumReceivedImages;
        unsigned int mNumRenderedImages;
        unsigned int mImageSizePixels;
        unsigned int mCompressionRatio;
        
        // intermediate statistics values
        unsigned int mImageSizePixelsAbs;
        unsigned int mImageSizePixelsSamples;
        unsigned int mCompressionBytesOriginal;
        unsigned int mCompressionBytesCompressed;
    };


    McDArray<StatData>  mStatData;
    int                 mStatCurrent;
    McWatch             mStatWatch;

    // number of image bytes received since last reset. dedicated counter.
    unsigned            mNumImageBytesReceived;

    /** Updates and returns the current index into mStatData. The method is
        called before updating or reading WAN statistics data. The index is
        updated once a second, so that getStatistics() can return a graph
        for the last 60 seconds. */
    int statCurrent();

    // Minimum packet size that would be compressed using z-lib compression
    // TODO: This should be set according to the network backwidth. Be aware that
    // the overhead of z-lib compression is high, so it does not make sense
    // to set this value to 0 even for very slow networks! For very fast networks
    // it is best to disable z-compression at all.
    unsigned int        mMinSizeForZCompression;


    ////////////////////////////////////////
    // commands & communication
    ////////////////////////////////////////

public:

    struct Cmd
    :   public McLink
    {
        Cmd()
        :   mId                 ( sIdNext++ )
        ,   mTimeReceiveStart   ( 0 )
        ,   mTimeReceiveStop    ( 0 )
        ,   uid                 ( 0 )
        ,   funcID              ( 0 )
        {
        
        }

        static mcint64  sIdNext;
        mcint64         mId;

        float           mTimeReceiveStart;
        float           mTimeReceiveStop;

        int             uid;
        int             funcID;
        VsMsg           args;
    };


    // The reader thread appends received cmds at the end of the cmd queue.
    // In the local server debug scenario the local thread directly inserts
    // cmds at the end of the cmd queue.
    McMutex                         mCmdLock;
    McWaitCondition                 mCmdLockWait;
    McList<Cmd>                     mCmdQueue;
    Cmd                             mCmdLastSent;
    Cmd                             mCmdLastInvoked;


    ////////////////////////////////////////
    // rendering
    ////////////////////////////////////////

    McHandle<VsRenderQueue2>        mRenderQueue;
    McHashTable<int, VsCompressor*> mCompressors; 
    int                             mPreferredCompressor;


    ////////////////////////////////////////
    // debugging & logging
    ////////////////////////////////////////

    bool                            mLogEnabled;

public:

    McWatch                         mWatch;


private:
    // Execute the specified command
    void execCmd( Cmd & inCmd );

    /** Performs the initial handshake after the socket connection has been established.
        On the client side the method is called in connectToServer(). On the server side
        the method is called in startServer().
        \param inOutUseSSL
            Indicates if SSL encryption should be used or not. If the client sends
            SSL_AUTO the mode suggested by the server is taken. Otherwise the mode
            suggested by the client is taken. Thus the client can overwrite the
            settings suggested by the server.
        \param outProtocolVersion
            Indicates the protocol version of the remote side. Only VSPV_Internal
            (or outProtocolVersion[3]) might differ. In all other case an error is
            returned.
        \return
            If the handshake was sucessfull VS_OK is return, otherwise VS_FAILED is
            returned. The error text returned by Vs::lastError() describes the error
            (unexpected network protocol, protocol version mismatch, socket read error).
    */
    VSRESULT handshake(int inSocket, SSLMode& inOutUseSSL, unsigned int outProtocolVersion[4]);
};

#define theServer VsServer::instance()

#endif

/// @}

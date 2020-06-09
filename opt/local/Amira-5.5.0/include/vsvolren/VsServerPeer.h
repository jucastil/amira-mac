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
#ifndef VS_SERVER_PEER_H
#define VS_SERVER_PEER_H

#include "Vs.h"
#include "VsInterface.h"

class VsScene;

// VS_RELAY_CLASS VsServerPeer VsRelay

////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_API VsServerPeer
:   public VsInterface
{
    VS_DECL_INTERFACE        ( VsServerPeer )
    VS_DECL_INTERFACE_FACTORY( VsServerPeer )
    VS_DECL_INTERFACE_RELAY  ( VsServerPeer )

public:    
    VsServerPeer( VsMeta * inMeta = 0 );
   ~VsServerPeer();

    enum ImageCompression {
        COMPRESS_AUTO = 0,
        COMPRESS_RAW = 1,
        COMPRESS_RLE = 2,
        COMPRESS_JPG90 = 3,
        COMPRESS_JPG60 = 4,
        COMPRESS_JPG30 = 5
    };

    void sendSessionId(const char* backend); // VS_RELAY

    const char* sessionId() const;

    // send name of the backend computer on the WAN server to the client
    // this name must be used there to access the web services. Under the 
    // external name, the web services are probably not exported to the 
    // client so they would not work.
    void sendInternalBackendName(const char* backend); // VS_RELAY VS_NODELAY

    const char* internalBackendName() const;

    void setRenderServerVersion(const char* version); // VS_RELAY

    const char* renderServerVersion() const;

    void setRenderServerHostname(const char* hostname); // VS_RELAY

    const char* renderServerHostname() const;

    // Called from client: info like user name and client computer are
    // printed to session log file on server
    void printSessionInfo(const char* info, int msec); // VS_RELAY

    void printSessionLog(const char* info); // VS_RELAY

    void setLanguage(const char* languageCode); // VS_RELAY

    VSRESULT testNetworkBandwidthUpload(
        bool            inIsCaller
    ,   mcint64         inNumberOfBytes
    ,   unsigned char * inBytes
    ); // VS_SYNC_CALL VS_NOCOMPRESS VS_NODELEY

    VSRESULT testNetworkBandwidthDownload(
        bool            inIsCaller
    ,   mcint64         inNumBytes
    ); // VS_SYNC_CALL VS_NOCOMPRESS VS_NODELEY


    // time function - for measuring some time on server side
    void  startTimer(int id); // VS_RELAY VS_NODELAY
    float stopTimer(int id); // VS_SYNC_CALL

    // Process next request in server-side render queue
    void processNext(); // VS_RELAY VS_NODELAY
    
    // Process all requests of a given frame in server-side render queue 
    void processFrame( mcint64 inFrameId ); // VS_RELAY VS_NODELAY

    // send per-frame performance samples to the remote side
    void frameSamplesSend( mcuint64 inFrameId, VsMsg & inMsg, bool inIsWorkerSide = false ); // VS_RELAY

    void setImageCompression(VsServerPeer::ImageCompression value, int lowres); // VS_RELAY

    ImageCompression imageCompression(int lowres) const;

    void setViewPortAutoScaleRange( float vmin, float vmax ); // VS_RELAY

    void viewPortAutoScaleRange( float& vmin, float& vmax ) const;

    void setNagleEnabled(bool value);

    bool isNagleEnabled() const { return mNagleEnabled; }

    static void writeLog(const char* fmt, ...);

private:
    McString mSessionId;
    McString mInternalBackendName;
    McString mRenderServerVersion;
    McString mRenderServerHostname;
    ImageCompression mImageCompression[4];
    bool mNagleEnabled;
};

#endif // VS_SERVER_COMMUNICATOR_H

/// @}

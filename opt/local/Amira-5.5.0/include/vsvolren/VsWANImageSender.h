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
#ifndef VS_WAN_IMAGE_SENDER_H
#define VS_WAN_IMAGE_SENDER_H

#include "Vs.h"
#include "VsHandable.h"
#include "VsMemoryData.h"
#include "VsScene.h"

#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McWatch.h>

#include <mclibthreaded/McThread.h>
#include <mclibthreaded/McMutex.h>
#include <mclibthreaded/McWaitCondition.h>

// - performs image compression and transmission to remote WAN side
// - does this in a separate thread

////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_API VsWANImageSender
:   public McThread
{
public:

    VsWANImageSender();
   
    virtual ~VsWANImageSender();

    static VsWANImageSender & instance();

    enum ImageState
    {
        STATE_UNUSED     = 0    // image is unused and free for application use
    ,   STATE_APPUSED    = 1    // image is currently filled up by the application
    ,   STATE_COMPRESS   = 2    // image is going to be compressed
    ,   STATE_DELAYED    = 3    // image is waiting for delayed transmission
    ,   STATE_COUNT             // number of states
    };

    // Called by the application to get an image for filling it up
    // processImage() be called later with the returned image container.
    VsMemoryData * getImage( VsScene * inTargetScene );

    // Called by the application to furter process the image previously
    // retrieved by calling getImage().
    // Image is now under control of VsWANImageSender again and must never be accessed after.
    void processImage( VsMemoryData * inData, bool inIsInteractive, VsRenderResult inResultFromRender, mcint64 inFrameId );

    void cancelAll( ImageState inState );

    // wait until the frame with frameId has been sent
    void wait( mcint64 frameId );


    ////////////////////////////////////////
    // override McThread
    ////////////////////////////////////////

    void run();


private:
    
    class ImageInfo
    :   public VsHandable
    {
    public:

        ImageInfo();
        ~ImageInfo();

        static int sNextImageID;

        VsWANImageSender::ImageState mState;
        int                          mImageID;
        McHandle<VsScene>            mTargetScene;
        bool                         mIsInteractive;
        bool                         mSendAgainLossless;
        VsRenderResult               mResultFromRender;
        int                          mUserData;
        mcint64                      mFrameId;
        McHandle<VsMemoryData>       mImage;
        unsigned char              * mImageCompressed;
        int                          mImageCompressedLen;
        int                          mImageCompressorID;
        int                          mBytesSend;
        float                        mDelayedTransmissionTime;
        bool                         mDeleteMe;
    };

private:

    void priv_imageCompress( ImageInfo & ioImage );
    void priv_imageSend    ( ImageInfo & ioImage );
    void priv_enqueueDelayedImages();
    void priv_removeDelayedImages();


private:

    McMutex                             mMutex;
    McWaitCondition                     mWait;
    McDArray< McHandle<ImageInfo> >     mImages[STATE_COUNT];

    mcint64                             mCurrentProcessedFrameId;

    bool                                mCanceled;

    McWatch                             mLastImageSentTimer;
    McWatch                             mStatisticsStartedTimer;
    float                               mIdleTimeBeforeSendingImages;
    unsigned int                        mNumImagesSent;
    unsigned int                        mNumRLE;
    unsigned int                        mNumJPEG;
};

#endif

/// @}

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
#ifndef _VS_RENDER_QUEUE2_IMPL_H_
#define _VS_RENDER_QUEUE2_IMPL_H_

#include "VsRenderQueue2.h"

#include "VsVolrenAPI.h"

#include "VsRenderQueue2.h"
#include "VsInterfaceImpl.h"
#include "VsRendererImpl.h"
#include "VsNode.h"
#include "VsScene.h"
#include "VsServer.h"

#include <mclib/McWatch.h>
#include <mclib/McDArray.h>
#include <mclib/McDArray.h>
#include <mclib/McResult.h>
#include <mclib/McString.h>
#include <mclib/McWatch.h>

#include <mclibthreaded/McMutex.h>

#define PRINT_QUEUE 0



////////////////////////////////////////////////////////////////////////////////

class VsRenderQueue2Impl : public VsInterfaceImpl
{
    VS_IMPLEMENTATION( VsRenderQueue2Impl, VsInterfaceImpl, VsRenderQueue2 )

public:

    VSRESULT processNext();
    VSRESULT processFrame( mcint64 inFrameId );

    /** This method is called by a render thread when rendering of a frame is 
        finished. It simply removes the current request from the queue, but it 
        does not start processing the next request. It is assumed that the main 
        thread is notified via some other mechanism and that then the main 
        thread in response to this notification calls 
        VsRenderQueue2::processNext(). */
    VSRESULT renderFinished( VsScene * inScene );

    void print();


public:

    struct Request 
    {
        McHandle<VsScene> mScene;
        VsRenderer      * mRenderer;

        unsigned int      mInsertionTimeMsec;
        bool              mInteractive;
        bool              mSuspended;
        mcint64           mFrameId;
        int               mUserData;
    };


    McMutex                 mMutex;
    McWatch                 mTimer;
    
    McDArray<Request*>      mQueue;
    McDArray<Request*>      mPool;

    
    Request               * mCurrentRequest;
    unsigned int            mInteractiveTimeMsec;
    
    // if true, new render requests are accepted, if false not.
    bool                    mOpen;

    VsRenderer            * mPreferredRenderer;

    McHandle<VsRenderer>    mDefaultRenderer;
};

#endif

/// @}

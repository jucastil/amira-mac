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
#ifndef _VS_RENDERER_IMPL_H
#define _VS_RENDERER_IMPL_H

#include "VsRenderer.h"

#include "VsObjectImpl.h"
#include "VsJobControl.h"
#include "VsNodeImpl.h"
#include "VsCameraImpl.h"
#include "VsMemoryData.h"
#include "VsRenderQueue2.h"
#include "VsScene.h"

#include <mclibthreaded/McWorkerThread.h>
#include <mclib/McHandle.h>
#include <mclib/McResult.h>

class VsMemoryData;

////////////////////////////////////////////////////////////////////////////////
class VsRendererJobControl : public VsJobControl
{
public:

    VsRendererJobControl()
    :   mCanceled   ( false )
    {
    
    }
    
    virtual void cancel()
    {
        mCanceled = true;
    }
    
    virtual bool canceled()
    {
        return mCanceled;
    }

    bool mCanceled;
};


////////////////////////////////////////////////////////////////////////////////
class VsRendererImpl : public VsObjectImpl, public McWorkerThread
{
    VS_IMPLEMENTATION( VsRendererImpl, VsObjectImpl, VsRenderer )

public:

    McHandle<VsScene>            mScene;
    McDArray<McHandle<VsNode> >  mNodes;  // the nodes to render in the next frame

    McHandle<VsRenderQueue2>     mRenderQueue2;
    McHandle<VsRenderQueue2>     mRenderQueueOfCurrentJob2;

    VsInteractionManager       * mInteractionManager;
    McHandle<VsMemoryData>       mSnapshot;
    int                          mNumSnapshotChannelsColor;
    int                          mNumSnapshotChannelsGrayScale;
    unsigned int                 mRenderTimeMsec;

    bool                         mGrayScale;
    
    // use only permitted for vimpl_setRenderTime() !!!
    // if false, no render jobs are submitted from vimpl_touch()
    bool                         mAllowTouch;  
    
    // use by calling 
    // if false, no render jobs are submitted from vimpl_touch()
    bool                         mAllowTouchExternal;  
    

    bool			             mActive;
    McHandle<VsRendererJobControl>
                                 mJobControl;

    McMutex                      mCleanupNodeMutex;
    McHandle<VsNode>             mCleanupNode;

    VsRenderResult               mLastResult;
    unsigned int                 mRenderingRequired;

    unsigned int                 mLastRenderingStarted;
    bool                         mShowBuffer;

    McMutex                      mSupportedMutex;
    bool                       * mSupported;
    McResult                     mSupportedResult;

    mcint64                      mFrameId;

    ////////////////////////////////////////
    // virtual from base class
    ////////////////////////////////////////

    /** This method is executed by the worker thread if startRendering() is
        called. It in turn calls render(), submits a new render request to
        the render queue if interactive rendering was enabled, notifies the 
        render queue that rendering is finished, and finally calls
        renderFinished(), so that a derived class can inform the main thread
        that rendering is finished. The main thread then should call
        VsRenderQueue::processNext(). */
    virtual void compute();

    /** */
    virtual void computeCtor();

    /** Compute destructor. This method is called synchronously
        inside the worker thread when the main thread calls
        terminate(). */
    virtual void computeDtor();


public:
    ////////////////////////////////////////
    // non-virtual interface methods
    ////////////////////////////////////////
    VsInteractionManager   * interactionManager() const;
    bool                     isInteractive() const;
    bool                     cancelRendering();
    VsRenderer::WaitResult   waitRendering( VsRenderResult & outResult, int inTimeOutMSec );
    VSRESULT                 terminateRendering();
    VSRESULT                 cleanUpNode(VsNode * ioNode);
    VsMemoryData           * snapshotBuffer();
    VSRESULT                 setNumSnapshotChannelsColor(int inNum);
    VSRESULT                 setNumSnapshotChannelsGrayScale(int inNum);
    int                      numSnapshotChannelsColor() const;
    int                      numSnapshotChannelsGrayScale() const;
    McColor                  backgroundColor() const;
    void                     setActive(bool value);
    bool                     isActive() const;
    VSRESULT                 setRenderQueue2( VsRenderQueue2 * inQueue );
    VsRenderQueue2         * renderQueue2() const;
    void                     setFrameId( mcint64 inFrameId );
    mcint64                  frameId();

private:
    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////
    VsRenderResult  vimpl_render();
    VSRESULT        vimpl_checkGraphics();
    VSRESULT        vimpl_setCamera( VsCamera* inCam );
    VsCamera      * vimpl_camera() const;
    VSRESULT        vimpl_setScene( VsNode* inScene, int sceneIdx );
    VsNode        * vimpl_scene(int sceneIdx) const;
    VSRESULT        vimpl_setSceneDescription( VsScene* inScene );
    VsScene       * vimpl_sceneDescription() const;
    VSRESULT        vimpl_touch(unsigned int mask);
    VSRESULT        vimpl_startRendering( unsigned int msec );
    VSRESULT        vimpl_startRendering( VsScene* inScene, unsigned int msec, mcint64 inFrameId );
    VSRESULT        vimpl_startRenderingToBuffer( VsMemoryData * outData, unsigned int msec, mcint64 inFrameId );
    VSRESULT        vimpl_initialize();
    VSRESULT        vimpl_deInitialize();
    VSRESULT        vimpl_cleanUpNodeInternal(VsNode * ioNode);
    VSRESULT        vimpl_renderFinished();
    VSRESULT        vimpl_setRenderTime(int msec);
    VSRESULT        vimpl_renderFrameBegin();
    VSRESULT        vimpl_setBackgroundColor( const McColor & inColor );
    VSRESULT        vimpl_renderPrepare();

protected:

    virtual VSRESULT    vimpl_setOptioni( int inOption, int inValue );
    virtual VSRESULT    vimpl_setOptiond( int inOption, double inValue );
    virtual VSRESULT    vimpl_optioni( int inOption, int & outValue ) const;
    virtual VSRESULT    vimpl_optiond( int inOption, double & outValue ) const;
};


#endif


/// @}

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
#ifndef VS_REMOTE_RENDERER_IMPL
#define VS_REMOTE_RENDERER_IMPL

#include "VsRemoteRenderer.h"
#include "VsCommonRendererImpl.h"
#include "VsCamera.h"
#include "VsVolren.h"
#include "VsScene.h"

#include <mclib/McHashTable.h>
#include <mclib/McMat4f.h>
#include <mclib/McWatch.h>

#include <mclibthreaded/McMutex.h>


class VsRemoteRendererImpl : public VsCommonRendererImpl
{
    VS_IMPLEMENTATION( VsRemoteRendererImpl, VsCommonRendererImpl, VsRemoteRenderer )

public:
    
    ////////////////////////////////////////
    // overload McWorkerThread
    ////////////////////////////////////////

    virtual void computeCtor();


private:

    ////////////////////////////////////////
    // virtual interface methods
    ////////////////////////////////////////

    //
    VSRESULT vimpl_startRendering( VsScene * inScene, unsigned int inMSec, mcint64 inFrameId );

    // Announces rendermask of scene to renderer
    VSRESULT vimpl_renderFrameBegin();

    // Sends scene background image back to client
    VSRESULT vimpl_renderFrameEnd( VsRenderResult inResultFromRender );

    VSRESULT vimpl_renderFinished();

    VSRESULT vimpl_observedObjectRemoved( VsObject * inObject );

    VSRESULT vimpl_touch(unsigned int mask);

    ////////////////////////////////////////
    // own methods
    ////////////////////////////////////////

private:

    class SceneInfo
    {
    public:

        bool                    mDoLoadBalancing;
        float                   mLastViewScale;         // view scale value of the last load balanced frame
        float                   mCurrViewScale;
        float                   mNextViewScale;         // view scale value for the next load balanced frame computed by the last frame
        McMat4f                 mMatViewProjLast;       // view projection matrix of the last frame
        McWatch                 mWatch;
        McHandle<VsMemoryData>  mSnapshot;
    public:

        SceneInfo()
        :   mDoLoadBalancing    ( false )
        ,   mLastViewScale      ( 1.0f )
        ,   mCurrViewScale      ( 1.0f )
        ,   mNextViewScale      ( 1.0f )
        ,   mMatViewProjLast    ( McMat4f::identity() )
        {
        }
    };

    McMutex                               mScenesMutex;
    McHashTable< VsScene*, SceneInfo* > * mScenes;
    McHandle<VsScene>                     mCurrentScene;
    McHandle<VsCamera>                    mCurrentCamera;
    McHandle<VsVolren>                    mCurrentVolren;
};

#endif // VS_REMOTE_RENDERER_IMPL

/// @}

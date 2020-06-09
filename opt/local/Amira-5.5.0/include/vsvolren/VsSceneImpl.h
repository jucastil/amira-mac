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
#ifndef VS_SCENE_IMPL_H
#define VS_SCENE_IMPL_H

#include "VsScene.h"

#include "VsInterfaceImpl.h"
#include "VsCamera.h"
#include "VsMemoryData.h"
#include "VsNode.h"

#include <mclib/McColor.h>
#include <mclib/McVec2i.h>
#include <mclib/McHandle.h>

#include <mclibthreaded/McMutex.h>

class VsRenderer;

// class VsScene : public VsObject, public VsRelayable
class VSVOLREN_API VsSceneImpl : public VsInterfaceImpl
{
    VS_IMPLEMENTATION( VsSceneImpl, VsInterfaceImpl, VsScene )

public:

    void setOwner(VsRenderer* owner);
    VsRenderer* owner() const;
    
    void setCamera(VsCamera* camera);
    VsCamera* camera() const;

    void setRootNode(VsNode* node, int idx=1);
    VsNode* rootNode(int idx=1);

    void setBackgroundColor(const McColor& color);
    McColor backgroundColor() const;

    void setImageSize(const McVec2i& size);
    McVec2i imageSize() const;
    
    void invalidateBackgroundImage();

    void setRenderMask(int renderMask);
    int renderMask() const;

    void setUserData(int userData);
    int userData() const;

    void setFrameId(mcint64 frameId);
    mcint64 frameId() const;

    VsMemoryData * backgroundImage() const;
    void setBackgroundImage(VsMemoryData* inBackgroundImage);
    McVec2i backgroundImageSize() const;

//    VsRenderResult backgroundRenderResult() const;
//    bool backgroundLossyCompressed() const;

    void generateState(
        mcint64 inFrameId
    );

    void deleteStatesOlderThan(
        mcint64 inFrameId
    );

    void submitRemoteRenderRequest(
        mcint64      inFrameId 
    ,   int          inUserData
    ,   unsigned int inRenderMask
    );

    VsRenderResult submitRemoteRenderRequestSync( 
        mcint64      inFrameId 
    ,   int          inUserData
    ,   unsigned int inRenderMask 
    );

    void remoteRenderCompleted(
        mcint64         inFrameId 
    // user data
    ,   int             inUserData
    // per image data
    ,   int             inBufferSize
    ,   McVec2i const & inImageSize
    ,   int             inNumChannels
    ,   int             inCompressorId
    ,   VsRenderResult  inResultFromRender
    // per chunk data
    ,   int             inChunkOffset
    ,   int             inNumberOfChunkBytes
    ,   unsigned char * inChunkBytes
    );



public:

    VsRenderer            * mOwner;
    VsScene::ContentType    mContentType;
    McHandle<VsCamera>      mCamera;
    McHandle<VsNode>        mRootNode[3];
    McColor                 mBackgroundColor;
    McVec2i                 mImageSize;
    int                     mRenderMask;
    int                     mUserData; // ???
    int                     mFrameId; // only used for inserting high-res jobs into the render queue

    float                   mLastViewScale;         // only used on server

    // background image buffers
    McHandle<VsSceneImageBuffer>    mBackgroundImages[2];

    // buffer into which the current image transmitted is received into
    int                     mReceiveBufferLen;
    unsigned char         * mReceiveBuffer;

    McDArray<mcint64>       mFrameStatesToDelete;


public:

    VsSceneImageBuffer * decompressedNewestLockedBackgroundImage();
    VsSceneImageBuffer * bufferLocked( bool inNewest );

    void vimpl_nextImageBufferLocked( mcint64 inFrameId, McHandle<VsSceneImageBuffer> & outImageBuffer );
};

#endif

/// @}

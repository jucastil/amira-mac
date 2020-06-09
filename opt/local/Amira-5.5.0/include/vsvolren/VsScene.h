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
#ifndef VS_SCENE_H
#define VS_SCENE_H

#include "VsInterface.h"
#include "VsHandable.h"
#include "VsRelay.h"
#include "VsSceneImageBuffer.h"

#include <mclib/McColor.h>
#include <mclib/McHandle.h>
#include <mclib/McVec2i.h>

class VsCamera;
class VsNode;
class VsRenderer;

// VS_RELAY_CLASS VsScene VsRelay

class VSVOLREN_API VsScene
:   public VsInterface
{
    VS_DECL_INTERFACE        ( VsScene )
    VS_DECL_INTERFACE_IMPL   ( VsScene )
    VS_DECL_INTERFACE_FACTORY( VsScene )
    VS_DECL_INTERFACE_RELAY  ( VsScene )

public:

    enum ContentType {
        CONTENT_2D, // used to enforce lossless transmission of high-res images
        CONTENT_3D  // lossy compression of high-res images is allowed
    };

    void setOwner(VsRenderer* owner);

    VsRenderer* owner() const;



    void setCamera(VsCamera* camera); // VS_RELAY

    VsCamera* camera() const; // LOCAL_GET

    void setRootNode(VsNode* node, int idx=1); // VS_RELAY

    VsNode* rootNode(int idx=1); // LOCAL_GET

    void setContentType(VsScene::ContentType value); // VS_RELAY

    ContentType contentType() const; // LOCAL_GET



    void setBackgroundColor(const McColor& color); // VS_RELAY

    McColor backgroundColor() const; // LOCAL_GET


    void setImageSize(const McVec2i& size); // VS_RELAY

    McVec2i imageSize() const; // LOCAL_GET



    void invalidateBackgroundImage();



    // Called from client if raster image needs to be rendered (see ExBaseViewer::checkRenderingRequired())
    void submitRemoteRenderRequest(
        mcint64      inFrameId             // Frame Id
    ,   int          inUserData
    ,   unsigned int inRenderMask
    ); // VS_RELAY VS_NODELAY

    VsRenderResult submitRemoteRenderRequestSync(
        mcint64      inFrameId             // Frame Id
    ,   int          inUserData
    ,   unsigned int inRenderMask 
    ); // VS_SYNC_CALL


    // Called from server when raster image is ready (see VsRemoteRenderer).
    // Called multiple times for an image to send it in multiple chunks.
    // Sending of an image can be stopped then inbetween.
    void remoteRenderCompleted(
        mcint64         inFrameId             // Frame Id
    ,   int             inUserData            // user data passed through render server
    // per image data
    ,   int             inBufferSize          // memory size of the whole compressed image
    ,   McVec2i const & inImageSize           // dimensions of the image
    ,   int             inNumChannels         // number of channels
    ,   int             inCompressorId        // id of the image compressor
    ,   VsRenderResult  inResultFromRender    // result from the image rendering
    // per chunk data
    ,   int             inChunkOffset         // byte offset of this chunk
    ,   int             inNumberOfChunkBytes  // length of this chunk
    ,   unsigned char * inChunkBytes          // data
    ); // VS_RELAY VS_NODELAY VS_NOCOMPRESS

    virtual void nextImageBufferLocked( mcint64 inFrameId, McHandle<VsSceneImageBuffer> & outImageBuffer );

    virtual void newImageReceived( int userData );
};

#endif

/// @}

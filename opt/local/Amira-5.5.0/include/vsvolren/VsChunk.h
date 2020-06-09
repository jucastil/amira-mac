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
#ifndef _VS_CHUNK_H_
#define _VS_CHUNK_H_

#include "Vs.h"

#include "VsHandable.h"
#include "VsVoxelDescriptor.h"
#include "VsData.h"


#include <mclib/McBox3f.h>
#include <mclib/McHandle.h>



class VsBrick;
class VsVolumeLevel;

/** A VsChunk object is part of a VsBrick. It represents a 3D texture
    required to render the brick. Each brick should have at least one
    chunk (or texture). This chunk should represent the image data to
    be rendered. There may be an additional chunk representing
    precomputed normals. The precise format and the semantics of a
    chunk is encoded in a VsVoxelDescriptor, which can be retrieved
    using voxelDescriptor(). Chunks are created and initialized by
    VsVolumeLevel::createBricks(). */
class VSVOLREN_IMPL VsChunk : public VsHandable
{
    friend class VsBrick;
    friend class VsVolumeLevel;
    friend class VsResourceManager;
    friend class VsGLTexture;

private:

    VsChunk();

public:


     VsChunk( McHandle< VsBrick > & inBrick );
    ~VsChunk();

    /// ID of the chunk
    mcuint64 id() const { return mId; }

    /// Returns total number of bytes for this chunk
    mclong numBytes() const
    {
        if (mSourceData)
        {
            VsData* d = mSourceData;
            return (mclong) mSize[0]*mSize[1]*mSize[2]*d->primType().size()*d->nDataVar();
        } 
        else
        {
            return 0;
        }
    }

    /// Return the number of bytes per texel.
    int numBytesPerTexel() const
    { 
        return mSourceData ? mSourceData->primType().size()*mSourceData->nDataVar() : 0;
    }

    /// Size of the chunk in the source volume
    const unsigned int * size() const
    { 
        return mSize;
    }
    
    /** Set size of the chunk in the source volume.
        For this dimension the origin is set to 0.
    */
    McResult sizeSet( unsigned int inDimIdx, unsigned int inSize );

    /// for each dimension x,y,z this indicates if its the 0:fastest, 1:middle and 2:slowest dimension of the chunks data
    const unsigned int * dimOrder() const
    { 
        return mDimOrder;
    }
    
    
    /// size of the texture used to render this chunk
    const unsigned int * textureSize() const
    {
        return mTexSize;
    }

    /** Set size of the chunk in the source volume.
        For this dimension the origin is set to 0.
    */
    McResult textureSizeSet( unsigned int inDimIdx, unsigned int inSize );

    /// Offset of the first voxel in source volume
    const unsigned int * origin() const
    {
        return mOrigin;
    }
    
    /// Set offset of the first voxel in the source volume
    McResult originSet( unsigned int inDimIdx, unsigned int inOffset );

    /// Get voxel descriptor
    McResult voxelDescriptor( McHandle<VsVoxelDescriptor> & outVoxelDescriptor ) 
    { 
        outVoxelDescriptor = mSourceDescriptor;
        return McOK;
    }

    
    /// Set voxel descriptor
    McResult voxelDescriptorSet( McHandle<VsVoxelDescriptor> & inVoxelDescriptor ) 
    { 
        mSourceDescriptor = inVoxelDescriptor;
        return McOK;
    }

    
    /// returns the box that the brick covers in chunk space.
    const McBox3f & BoxBrickChunkSpace() const
    {
        return mBoxBrickChunkSpace;
    }

    /// Source data object
    McResult source( McHandle<VsData> & outSourceData );

    /// Source data object
    McResult sourceSet( McHandle<VsData> & inSourceData );

    bool usePbo() const { return mUsePbo; }

    void clone( McHandle<VsChunk> & outChunk );


// private:
public:

    /// Unique ID of this chunk
    mcuint64                    mId;
    /// Handle to the container brick
    McHandle< VsBrick >         mBrick;
    /// Size of the chunk in voxels (usually smaller than mSourceData->dims())
    unsigned int                mSize[3];       
    /// Index of first voxel in source volume
    unsigned int                mOrigin[3];
    /// box inside the chunk volume that covers the bricks box. Range: [0..1] for each dimension. may be smaller due to overlap.
    McBox3f                     mBoxBrickChunkSpace;

    /// Handle to the source volume data object
    McHandle<VsData>            mSourceData;
    /// Voxel descriptor of the source volume
    McHandle<VsVoxelDescriptor> mSourceDescriptor;

    bool                        mClipMask[256];


    /// index of the texture the chunk data were loaded into last time
    int                         mTexIdxLast;
    /// Size of the texture in voxels
    unsigned int                mTexSize[3];
    /// nonzero if that chunk is currently used as texture data source
    int                         mTexInUse;

    ///
    static mcuint64             mIdNext;

    bool                        mUsePbo;

    unsigned char               mGLTextureIsResident;

    /// this indicates the 0:fastest, 1:middle and 2:slowest dimension of the chunks data
    unsigned int                mDimOrder[3];

    /// used by the resource manager to detect if this chunk was already processed in this frame
    mcint64                     mFrameId;


private:

    void reset();
};

#endif

/// @}

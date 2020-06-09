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
#ifndef _VS_TEXTURE_H
#define _VS_TEXTURE_H

#include "VsVolrenAPI.h"
#include "VsImpl.h"
#include "VsHandable.h"
#include "VsVoxelDescriptor.h"
#include "VsBrick.h"

#include <mclib/McHandle.h>
#include <mclib/McVec2d.h>




class VsTexture : public VsHandable
{
    friend class VsResourceManager;

public:

    /// Constructor
                VsTexture();

    /// Destructor, releases the texture resource
    virtual    ~VsTexture();

    /// texture id
    mcuint64    id()
    {
        return mID;
    }

    /// Creates the texture, taking size from HxVolren. returns 0 on failure
    McResult    create( mcuint64 inFormat, const unsigned int * inDims, McHandle<VsChunk> & inChunk );

    /// Uploads data from chunk into texture
    McResult    upload( McHandle<VsChunk> & inChunk, mcuint64 inFormat, McVec2d const & inRange, mcuint64 * ioNumBytes=0 );

    /// releases the resources
    McResult    release();

    /// releases the texture to the current render state
    McResult    bind( McHandle<VsChunk> & inChunk );

    /// wait until this texture is not used for rendering anymore
    virtual void wait()
    {
    }

    /// sets magnification filter (may only be called by texture manager)
    virtual void setMagFilterLinear(bool value);

    bool magFilterLinear() const
    {
        return mMagFilterLinear;
    }


private:

    virtual McResult createInternal(
        mcuint64                inFormat
    ,   const unsigned int    * inDims
    ,   McHandle<VsChunk>     & inChunk
    ) = 0;

    virtual McResult uploadInternal(
        McHandle<VsChunk> & inChunk
    ,   int                 inInit
    ,   mcuint64            inFormat
    ,   McVec2d const     & inRange
    ,   mcuint64          * ioNumBytes
    ) = 0;

    virtual McResult releaseInternal() = 0;

    virtual McResult bindInternal( McHandle<VsChunk> & inChunk ) = 0;


protected:
    
    /// internal format
    mcuint64                    mFormat;
    /// texture-ID, valid if nonzero
    mcuint64                    mID;
    /// dimensions
    int                         mDims[3];
    ///
    bool                        mMagFilterLinear;

public:

    /// internal size of the texture in bytes
    mcuint64                    mSizeInternal;
    /// ID of the chunk which has supplied the current texture data
    mcuint64                    mChunkId;
    /// value range currently mapped into the texture
    McVec2d                     mRangeMapped;

    /// index of this texture in an array object
    mcuint64                    mMyIdx;
    /// how much of the texture is used [0..1]
    float                       mAmount;
    /// this is increased by the resource manager each frame and reset if used for rendering including the current frame
    mcuint64                    mNumFramesUnused;
    /// this is increased by the resource manager each time a texture is uploaded and reset if this texture gets uploaded
    mcuint64                    mNumOthersUploaded;
    /// multiple chunks may have to be uploaded for a brick, in this case textures with the current transaction id must not be overwritten
    mcuint64                    mTransactionId;
    /// current textures voxel semantics
    mcuint32                    mSemantic;

    // hack
    unsigned int mUnit;
};

#endif


/// @}

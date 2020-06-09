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
#ifndef _VS_RESOURCE_MANAGER_H_
#define _VS_RESOURCE_MANAGER_H_

#include "Vs.h"

#include "VsHandable.h"
#include "VsVoxelDescriptor.h"
#include "VsBrick.h"
#include "VsTexture.h"

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <mclib/McHashTable.h>
#include <mclib/McVec2d.h>
#include <mclib/McVec2i.h>


/// \if UNDOCUMENTED

class VSVOLREN_API VsResourceManager : public VsHandable
{
public:
    
    // this enumeration defines the tags for various strategies used to select a texture
    // to overwrite for the case a texture has to be overwritten
    enum Strategy
    {
        STRATEGY_FIRST  // take the first matching 
    ,   STRATEGY_FIFO   // overwrite the "oldest" texture but try to preserve textures from the last frame
    ,   STRATEGY_FIFO2  // overwrite the "oldest" texture
    };

    // This enum defines different resource types that are beeing maintained by the resource manager
    enum ResType
    {
        RT_UNKOWN       // Unspecified
    ,   RT_TEXTURE      // Texture object
    ,   RT_DLIST        // Display list
    ,   RT_VBO          // Vertex buffer
    };

    struct TextureInfo3d
    {
        VsBrick       * mBrick;     // the brick the texture data is taken from
        VsChunk       * mChunk;     // the chunk that needs to be uploaded
        int             mUnit;      // destination OpenGL texture unit

        McVec2d         mRangeRequested;    // value range of the input domain that is requested to be in the texture
        McVec2d         mRangeMapped;       // value range of the input domain that gets mapped into the texture
                                            // might be larger than mRangeRequested
        McVec2i         mRangeRaw;          // texture raw data range

        // reserved
        unsigned int    mFormat;
        unsigned int    mTexelSizeInBits;
    };

    // The handle for addressing a resource maintained by the resource manager
    typedef unsigned int Handle; // unsigned int Handle;
    // The constant for an invalid/uninitialized handle
    enum
    {
        H_UNDEF = 0
    };

                        VsResourceManager();
    virtual            ~VsResourceManager();

    // deprecated
    void                nextFrame( int chunksToBeUsed, mcuint32 inSemantic ); // chunksToBeRendered just for statistics

    VSRESULT            nextFrame( int numBricks, VsBrick ** inBrick, mcuint32 * inSemantics, unsigned int * inChunkIndex );

    void                statistics(McString * string = NULL);

    // deprecated
    McResult            bricksLoad( int inTexInfoNum, TextureInfo3d * inTexInfo, mcuint64 * ioNumBytes, bool dryRun );
    
    McResult            brickPreload(
        mcuint32            inSemantics
    ,   McHandle<VsBrick>   inBrick
    ,   McVec2d const     & inRange
    ,   mcuint64          * ioNumBytes = 0
    );

    bool                brickIsCached( mcuint32 inSemantics, McHandle<VsBrick> inBrick, unsigned int inChunkIndex=0, mcuint64 *ioNumBytes=0);
    int                 chunksTexture( VsChunk * chunk );

    virtual bool        textureNeedPow2();
    virtual mcuint64    textureMaxEdgeLen();
    virtual mcuint64    textureMaxBytes();

    static VSRESULT     textureDimsHint(
                            McVec3l       & outDimsTexoutDimsTex            // dimensions of the 3d-textures
                        ,   McVec3l       & outDimsVoloutDimsVol            // preferred size of the downsampled input data
                        ,   McVec3l const & inDimsVolinDims                 // dimensions of the input data
                        ,   bool          * outNeedResampleoutNeedResample  // true if volume needs to be resampled
                        );

    unsigned int        texturesNum();
    McResult            texturesDelete();
    McResult            textureDelete( int inIndex );
    bool                textureRangeMapped( unsigned int inIndex, McVec2d & outRange );

    // force re-upload of texture bricks at next render
    void         invalidateTextures();

    virtual void        enablePboUpload(bool value);

    virtual bool        pboUploadEnabled() const;

    static void         setMaxTexMem( mcuint64 inNewSize );
    static void         setMaxTexMem( McString inNewSize );
    static mcuint64     maxTexMem();
    static void         setMaxDListPolygons( McString inNewNum );
    static void         setMaxDListPolygons( mcuint64 inNewSize );
    static mcuint64     maxDListPolygons();
    static void         setMaxVBOMem( McString inNewNum );
    static void         setMaxVBOMem( mcuint64 inNewSize );
    static mcuint64     maxVBOMem();

    void                setMagFilterLinear(bool value);

    bool                magFilterLinear() const { return mMagFilterLinear; }

    /// Returns pointer to global object
    static VsResourceManager * & theInstance();

    void                setStrategy( Strategy inStrategy );
    Strategy            strategy();

    static VSRESULT     textureInfo(
        VsVoxelDescriptor & inDesc
    ,   unsigned int * outInternalType
    ,   unsigned int * outExternalType
    ,   unsigned int * outExternalFormat
    ,   McVec2i      * outRange
    ,   unsigned int * outTexelBits
    );

    // Methods for maintaining generic resources
    Handle createResource(ResType inType, int inSize = 0);
    void destroyResource(Handle inHandle);
    bool resourceValid(Handle inHandle);
    void setResourceValid(Handle inHandle, bool inValid);
    unsigned int resourceHwId(Handle inHandle);
    void cleanupResources(); // A method to be called on destruction or from time to time to free resources that are pending for deletion.


public:

    ////////////////////////////////////////
    // statistics
    ////////////////////////////////////////

    mcint64                             mLogFrameId;            // ID of the current frame - gets increased by nextFrame()
    mcint64                             mLogNumBytesUploaded;   // number of bytes uploaded
    int                                 mLogNumChunksUploaded;  // number of chunks uploaded
    int                                 mLogNumChunksTotal;     // number of chunks handled
    float                               mLogUploadTimeSec;      // time consumed for upload
    mcint64                             mLogNumTexBytesUsed;    // sum number of bytes of all textures used (always full texture, even if partially filled)

protected:

    //
    int                                 mUsePbo;


    McDArray< McHandle< VsTexture > >   mTextures;
    McHashTable< mcuint64, int >        mTexturesFormats;   // number of textures currently allocated per format

    McHashTable< mcuint64, int >        mCurrFrameFormats;   // minimal number of textures required for current frame

    static mcuint64                     mTexMemBytesMax;
    static mcuint64                     mTexMemBytesCurr;
    static mcuint64                     mPolygonsInDListMax;
    static mcuint64                     mPolygonsInDListCurr;
    static mcuint64                     mVBOMemBytesMax;
    static mcuint64                     mVBOMemBytesCurr;

//    mcuint32                            mSemantic;

    bool                                mMagFilterLinear;

    Strategy                            mStrategy;

    // Members for generic resource maintenance
    struct Resource
    {
        Handle       mHandle; // The handle for internal maintanance
        ResType      mType;   // The resource type
        unsigned int mHwId;   // The actual id for OpenGL
        bool         mValid;  // Flag indicating the validity
        mcuint64     mSize;   // The space consumed by this resource

        Resource()
        :   mHandle ( 0 )
        ,   mType   ( RT_UNKOWN )
        ,   mHwId   ( 0 )
        ,   mValid  ( false )
        ,   mSize   ( 0 )
        {
        }
    };

    McDArray< Resource >                mResources;         // All active resources
    McDArray< Resource >                mPendingResources;  // Resources to be cleaned up
    McMutex                             mMutex;             // Used to protect mResources

private:
    
    virtual McResult textureCreate( McHandle<VsTexture> & outTexture ) = 0;
    virtual McResult textureFormat( McHandle<VsVoxelDescriptor> & inDescriptor, mcuint64 & outFormat ) = 0;

    static int resCompare(const VsResourceManager::Resource& res1, const VsResourceManager::Resource& res2);
};


#define theResourceManager (VsResourceManager::theInstance()) 

/// \endif

#endif

/// @}

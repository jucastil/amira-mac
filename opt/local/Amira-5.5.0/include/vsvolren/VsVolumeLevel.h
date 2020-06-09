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
#ifndef _VS_VOLUME_LEVEL_H
#define _VS_VOLUME_LEVEL_H

#include "VsVolrenAPI.h"
#include "VsImpl.h"
#include "VsBrick.h"

#include <mclib/McDArray.h>
#include "VsHandable.h"
#include <amiramesh/AmiraMesh.h>

class VsVolume;

////////////////////////////////////////////////////////////////////////////////
class VSVOLREN_API VsVolumeLevel : public VsHandable
{
private:
    VsVolumeLevel();
public:

             VsVolumeLevel( VsVolume * inVolume );
    virtual ~VsVolumeLevel();

    McResult bricksDelete();

    McResult bricksCreate( const unsigned int* brickSize, bool copyData );

    McResult bricks( McDArray< McHandle<VsBrick> > & outBricks );

    McResult bricksSortedOrtho( const McVec3f & inViewDir, McDArray< McHandle<VsBrick> > & outBricks );

    McResult bricksSortedPerspective( const McVec3f & inViewPos, McDArray< McHandle<VsBrick> > & outBricks );

    /** This box is the union of the bounding boxes of all bricks. It is used,
        e.g. in VsSliceTB to determine the geometric area in which slice polygons
        may be generated. */
    McBox3f  bricksBoundingBox();

    McResult dataAdd( VsData * inData, VsVoxelDescriptor inDesc );

    McResult dataRemove( mcuint32 inSemantics );
    
    McResult dataRemove( McHandle<VsData> inData );

    mcuint32 semantics();


    /// Returns the number of data objects associated with this level.
    int nData() const { return mDatas.size(); }

    /** Returns a pointer to a particular data object. In order to access
        the volume data, call data(0). Optionally, pre-computed normals
        might be stored in data(1). */
    VsData* data( unsigned int inIdx ) const 
    {
        if (inIdx < unsigned(mDatas.size()) )
            return mDatas[inIdx];
        return 0;
    }

    /** Returns if the data contained in this level is consistent. It is not
        consistent, e.g., if some thread is still reading data values or 
        doing initialization on the data */
    bool isValid() const;

    int nBricks() const { return mBricks.size(); }

    /// returns the index of that brick or -1 if that brick is not one of that level
    int bricksIndex( McHandle<VsBrick> & inBrick ) const;

    /// returns the index of the brick the given point is inside or -1 if point is outside the volume
    int brickIndex( const McVec3f & inPosition );

    McResult voxelDescriptor( unsigned int inIdx, McHandle<VsVoxelDescriptor> & outDesc  ) const ;

    /// Returns the bounding box of the level.
    void boundingBox( McBox3f & outBox ) const { outBox = mBoundingBox; }

    /// Returns the bounding box of the level.
    const McBox3f& boundingBox() const { return mBoundingBox; }

    /// Set bounding box (used in VsVolumeImpl::readAmiraMesh fixPixelSpacing)
    void setBoundingBox(const McBox3f& inBox) { mBoundingBox = inBox; }

    /// Returns the voxel size of the level.
    McVec3f voxelSize() const;

    /// Returns the smallest extent of a voxel.
    float voxelWidth() const;

    /** Automatically computes normals. The method requires that the volume level
        has exactly one data object with a voxel type VD_DENS_U8 (unsigned bytes),
        VD_DENS_U16 (unsigned shorts), or VD_DENS_S16 (signed shorts). The
        parameter @c normalType must be either VD_NORM_U5U6U5 (2 byte normals)
        or VD_NORM_U8U8U8X8 (4 byte normals).

        If the volume data is VD_DENS_U8, also VD_NORM_U8U8U8_DENS_U8 can be
        used, indicating that normals and data values should be interlaced. */
    McResult computeNormals( VsVoxelDescriptor::VoxelDescriptor normalType, unsigned int mask=0 );

    void clearNormals();

    bool hasNormals() const;

    int densityRange( double & outMin, double & outMax );

    /** For each chunk this method creates two new chunks with the same image data but 
        rotated in by 90 degrees around different axes. */
    McResult createATISwizzleChunks();
    bool     hasATISwizzleChunks();
    void     setForceATISwizzleChunks( bool inFlag );

    VsChunk * updateClippedChunk( VsBrick * inBrick, int inChunkIndex, int inChunkLabelIndex, bool * inClipMask );


    VsVolume * volume(){return mVolume;}

    VSRESULT brickNums( int outNums[3] );

    mcuint64 requiredTexMem(bool withLabels) const;


private:
    
    // the volume
    VsVolume                                  * mVolume;

    // all bricks  x-fastest  y-slowest
    McDArray< McHandle<VsBrick> >               mBricks;

    // number of bricks per direction
    int                                         mBrickNums[3];

    // original data objects
    McDArray< McHandle<VsData> >                mDatas;

    // voxel descriptors
    McDArray< McHandle<VsVoxelDescriptor> >     mDescriptors;


    /** This is the bounding box of the level. Usually this is identical
        to mDatas[0]->boundingBox(). However, the bounding box is stored
        in a separate variable in order to support volume levels with
        pre-swizzled bricks only but without the original data objects. */
    McBox3f mBoundingBox;

    /** This variable is set if the volume is part of a bigger logical volume
        which is distributed across multiple processors. It indicates the
        index position of the first voxel of the level-0 volume within the
        distributed logical volume. */
    McVec3i mDistVolumeOrigin;

    /** If this variable is not (0,0,0) it this volume is part of a bigger
        logical volume which is distributed across multiple processors. It
        indicates the total size of the distributed logical volume. */
    McVec3i mDistVolumeTotalSize;

    //
    bool    mForceATISwizzle;


private:

    bool isVisibleX( int i, const McVec3f & viewPoint );
    bool isVisibleY( int j, const McVec3f & viewPoint );
    bool isVisibleZ( int k, const McVec3f & viewPoint );

    bool isVisibleXOrtho( int i, const McVec3f & normal );
    bool isVisibleYOrtho( int j, const McVec3f & normal );
    bool isVisibleZOrtho( int k, const McVec3f & normal );

//    void clipBricks(const McBox3f& boxROI);
    VsBrick * brick(int i, int j, int k) { return mBricks[(k*mBrickNums[1]+j)*mBrickNums[0]+i]; }
    VsBrick * brick(int i) { return mBricks[i]; }

    static bool writeRawData(FILE* out, bool swapBytes, AmiraMesh::Data*, void* userData);



    // Information storage for the reader parsing clipping planes
    struct ThresholdInfo
    {
        unsigned int      mThresholdNumber; 
        int               mThreshold; 
        McDArray<McPlane> mPlanes;
        ThresholdInfo() : mThresholdNumber(0), mThreshold(0) {}
    };

    struct BrickInfo
    {
        unsigned int            mBrickNumber; 
        McDArray<ThresholdInfo> mThresholds; 

        BrickInfo(unsigned int b) : mBrickNumber(b) {}

        BrickInfo(){}
    };

    McDArray<BrickInfo> mBrickInfos; // will be read, when the bricks are created


friend class VsVolumeImpl;
};


#endif

/// @}

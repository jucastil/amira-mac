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
#ifndef _VS_BRICK_H_
#define _VS_BRICK_H_

#include "Vs.h"

#include "VsHandable.h"
#include "VsChunk.h"
#include "VsEmptySpaceClip.h"
#include "VsMemoryManager.h"


#include <mclib/McBox3f.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include <mclib/McPlane.h>


class VsCornerCut;

/** Texture-based volume rendering requires big data volumes to be
    subdivided into bricks so that each brick fits into texture memory
    at once. Bricks are created and initialized by VsVolumeLevel in
    VsVolumeLevel::bricksCreate().
    
    A brick contains one or two textures (chunks), representing the
    data to be rendered and optionally precomputed normals.

    Currently all textures (chunks) have the same size, and thus share
    the same bounding boxes in object space and texture space.
*/

class VsBrick : public VsHandable
{
    friend class VsVolumeLevel;
    friend class VsResourceManager;


public:

    /** Bounding box in object space. The bounding box is set up
        in such a way that the boxes of neighbouring bricks fit
        tightly together. */
    const McBox3f & boxObjSpace() const { return mBoxObjSpace; }

    /** Same as above but box but clipped against the volumes BoundingBoxAllLevels.
        Because of that returned box may be smaller if parts of the original box
        were outside BoundingBoxAllLevels.
    */    
    const McBox3f & boxObjSpaceClipped();

    /** Returns the bounding box in texture space. Depending on the
        number of overlapping voxels between neighbouring bricks the
        texture coordinates start at the center of the first voxel
        (0.5/texDim[k]) or even at larger values. */
    const McBox3f & boxTexSpace() const { return mBoxTexSpace; }

    /** Same as above but box but clipped against the volumes BoundingBoxAllLevels.
        Because of that returned box may be smaller if parts of the original box
        were outside BoundingBoxAllLevels.
    */    
    const McBox3f & boxTexSpaceClipped();

    /** Returns a bounding box suitable for inside-outside tests in
        texture space. This box can be bigger than boxTexSpace()
        because neighbouring bricks may share more than one voxel.
        This is required for computing normals on-the-fly or for
        applying the high-quality iso-shader. In each case texture
        lookup outside the actual bounding box can be performed.
        The box returned by this method indicates the size of the
        texture space filled by legal data. */
    const McBox3f & boxTexSpaceInside() const { return mBoxTexSpaceInside; }

    /** Returns a scale vector allowing you to transform a direction
        vector in object space into a direction vector in texture
        space via component-wise multiplication:
        \code
            McVec3f dir_tex = brick->texSpaceScale().compprod(dir_obj);
        \endcode */
    const McVec3f & texSpaceScale() const { return mTexSpaceScale; }

    /** Determines the location of the brick with respect to the specified
        plane @c plane. The semantic of the return values is similar to strcmp:
        A return value of 0 indicates that the brick is intersected by the plane,
        +1/-1 indicates a brick in the positive/negative half space of @plane.
        (The plane normal points to the positive half space of the plane.)
    */
    int planeCompare( McPlane plane );

    /** Sets a clip box. This brick is clipped against the specified roi.
        Subsequent calls of subBox() return a single clipped box. If the
        intersection is empty false is returned, otherwise true is returned. */
    bool clip( const McBox3f & roi );

    /** Clips this brick against the specified corner cut object. Subsequent
        calls of subBox() return up to seven individual boxes. The union
        of these boxes represents the clipped brick with one corner cut away.
        If this brick is completely cut away false is returned. */
    bool clip( const VsCornerCut* roi );

    void unclip();

    int numSubBoxes() const { return mSubBoxes.size(); }

    McResult subBox(unsigned int k, McBox3f& boxObjSpace, McBox3f& boxTexSpace, McBox3f& normalClipBox);

    int numChunks() const { return mChunks[0].size(); }

    VsChunk * chunk(int iChunk) const { return mChunks[0][iChunk]; }

    VsChunk * chunk(int iChunk, int axis) const { return mChunks[axis][iChunk]; }


    /// release references to the chunks
    void chunksRelease();


private:

    VsBrick();

public:

    VsBrick( VsVolumeLevel * inLevel );

    virtual ~VsBrick(){};

    VsVolumeLevel   * mLevel;

    // the three boxes 
    McBox3f           mBoxObjSpace;
    McBox3f           mBoxTexSpace;
    McBox3f           mBoxNormalClip;

    // same as above but clipped against volumes "all levels box"
    McBox3f           mBoxObjSpace_Clipped;
    McBox3f           mBoxTexSpace_Clipped;

    // TexCoord = (ObjectCoord + mTexSpaceOffset) * mTexSpaceScale
    McVec3f           mTexSpaceScale;
    McVec3f           mTexSpaceOffset;

    McBox3f           mBoxTexSpaceInside;   // the bounding box of the volume - for all bricks!! - in the shaders needed to check if sample is inside valid volume data
                                        

//    McDArray< McHandle< VsChunk > > mChunks[3]; // one for each orientation swizzle [x,y,z] [z,y,x] [z,x,y] oder so ähnlich
    McDArray< McHandle< VsChunk > > mChunks[2];
    McDArray< McHandle< VsMemoryReserver > > mMemoryReserver;


    struct SubBox 
    {
        McBox3f boxObjSpace;
        McBox3f boxTexSpace;
        McBox3f normalClipBox;
    };

    McDArray<SubBox> mSubBoxes;

    /* These variables are set in VsVolumeLevel::bricksSort(). This information
       is required in order to sort the subboxes obtained after clipping. */
    McVec3f mViewPoint;
    bool    mIsOrthogonal;


    ////////////////////////////////////////
    // simple empty space clipping performed by clipping planes
    ////////////////////////////////////////

    McDArray<VsEmptySpaceClipPlane> mEmptySpaceClips;
};

#endif

/// @}

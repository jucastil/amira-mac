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

/// @addtogroup hxfield hxfield
/// @{
#ifndef UNIFORMCOORD3
#define UNIFORMCOORD3

#include <hxfield/HxCoord3.h>
#include <mclib/McVec3f.h>

/// Class representing uniform axis-aligned coordinates.

class HXFIELD_API HxUniformCoord3 : public HxCoord3
{
  public:
    /// Constructor.
    HxUniformCoord3(const int dims[3]);

    /// Constructor.
    HxUniformCoord3(const int dims[3], const float* bbox);

    /// Destructor.
    ~HxUniformCoord3() { }

    /// Returns bounding box information.
    const float* bbox() const { return theBBox; }

    /// Returns bounding box information.
    float* bbox() { return theBBox; }

    /// Resizes coordinate array.
    virtual void resize(const int dims[3]);

    /// Creates HxLocation3 instance.
    virtual HxLoc3Regular* createLocation();

    /// Returns bounding box of lattice.
    virtual void getBoundingBox(float bbox[6]) const;

    /// Computes coordinates of given lattice node.
    virtual void pos(int i, int j, int k, float* res) const;

    /// Sets bounding box (non-uniform coords are scaled properly).
    virtual void setBoundingBox(const float bbox[6]);

    /// Performs swap operation on coordinates.
    virtual bool swapDims(const int didx[3]);

    /// Performs crop operation and adjusts coordinates.
    virtual bool crop(const int min[3], const int max[3]);

    /// Creates a copy of coordinate object.
    virtual HxCoord3* duplicate() const;

    /// Copys bounding box from other coord object into this one.
    void copyBoundingBox(const HxUniformCoord3& other) {
        setBoundingBox(other.bbox());
    }

    /// Calculates the voxel size
    McVec3f getVoxelSize ();
  protected:
    float theBBox[6];

  private:
    /// Returns true if coordinates are equal.
    virtual bool doEquals( HxCoord3* other ) const;
};

#endif

/// @}

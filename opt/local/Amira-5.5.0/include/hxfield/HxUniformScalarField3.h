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
#ifndef UNIFORMSCALARFIELD3
#define UNIFORMSCALARFIELD3

#include <hxfield/HxUniformCoord3.h>
#include <hxfield/HxRegScalarField3.h>
#include <mclib/McTypedData2D.h>

/// Represents a scalar field defined on a uniform lattice.

class HXFIELD_API HxUniformScalarField3 : public HxRegScalarField3
{
  HX_DATA_HEADER(HxUniformScalarField3);

  public:
    /// Constructor.
    HxUniformScalarField3(const int dims[3], McPrimType primType,
        void* data=0);

    /// This constructor uses an existing lattice object.
    HxUniformScalarField3(HxLattice3* existingLattice);

    /// Destructor.
    ~HxUniformScalarField3();

    /// Returns pointer to coordinate object.
    HxUniformCoord3* coords() { return (HxUniformCoord3*) lattice.coords(); }

    /// Returns pointer to bounding box array.
    float* bbox() { return coords()->bbox(); }

    /// New info method
    virtual void info();

    /// Read binary raw data.
    static int readRawData(const int dims[3], float bbox[6],
                           McPrimType pType, const char* filename);

    /// Compute divergence from a vector field.
    int computeDivergence(const float* vField);

    /// Duplicates the current HxUniformScalarField3 object
    virtual HxData *duplicate() const;

    /** Resample data to a new grid. The Matrix transform determines
        the transformation from local coordinates to world coordinates. The
        new bounding box is interpreted in world coodinates. Nearest
        neighbour or trilinear interpolation is used.*/
    void resample(const int ndims[3], float nbbox[6],
                  void* ndata, const SbMatrix& transform, int interpol, float paddingVal = 0.0f );

    /// Parse method
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

    /** Returns the voxel size. The voxel size is computed as
        (xmax-xmin)/(dims[0]-1) in x-direction, and similarly in y- and
        z-direction. */
    McVec3f getVoxelSize() const;

    /** overload for function in HxRegScalarfield3 */
    virtual McVec3f getVoxelSize(int i, int j, int k) const;

    /** Extracts a sub-volume from this field. The index bounds are clipped
        to fit completely in this field. */
    HxUniformScalarField3* extractSubVolume(const int* from, const int* to);

    /// Extracts a sub-volume from this field centered around @c center.
    HxUniformScalarField3* extractSubVolume(const McVec3f& center, const int* size);

    static HxUniformScalarField3* createSlice(McTypedData2D &typedData,
            McPrimType primType);

  protected:
    void copyData(const HxUniformScalarField3& source);

    void merge(HxUniformScalarField3* otherField, unsigned char dir);

    /** Apply transformation transform by resampling data. The new
        resolution (number of voxels) is either constant (autoDims=0) or
        automatically calulated such that the voxelsize is constant (in
        case of isotropic voxels) (autoDims=1).  The new boundingBox is
        either the old one (autoBBox=0) or the old one but translated such
        that old and new center are the same (autoBBox=1) or the bounding
        box of the transformed old bounding box. */
    virtual void applyTransform(SbMatrix& transform, int autoDims,
                                int autoBBox, int interpol,
                                int autoCrop, float threshold,
                                const int* forcedims,
                                const float* forcebox,
                                float paddingVal = 0.0f );
};

#endif

/// @}

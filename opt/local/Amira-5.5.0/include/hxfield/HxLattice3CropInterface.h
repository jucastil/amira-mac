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
#ifndef HX_LATTICE3_CROP_INTERFACE_H
#define HX_LATTICE3_CROP_INTERFACE_H

#include <hxcore/HxInterface.h>
#include <hxfield/HxFieldWinDLLApi.h>

class HxCoord3;
/// Interface needed to apply crop editor to data object
class HXFIELD_API HxLattice3CropInterface : public HxInterface
{
    MC_ABSTRACT_HEADER(HxLattice3CropInterface);
  
  public:
    /// Returns lattice dimensions.
    virtual const int* cropinterface_dims() const = 0;

    /// Returns pointer to coordinate object.
    virtual HxCoord3* cropinterface_coords() const = 0;

    /** Crops or enlarges the lattice. If @c replicate=NULL (default),
	the data set is enlarged by replicating the last slice. Otherwise 
	@c replicate will interpreted as pixel value for additional pixel.
	The coordinates of the lattice are adjusted automatically. */
    virtual bool cropinterface_crop(const int min[3], const int max[3], const char* replicate = NULL) = 0;

    /// Does kind of 90 degree rotation by reordering 3d array with new indexing order.
    virtual bool cropinterface_swapDims(int ix, int iy, int iz) = 0;

    /** Flips the order of slices in any dimension. For example, in order
        to flip the data set in z direction use @c flip(2). */
    virtual bool cropinterface_flip(int dimension) = 0;

    /// Call coords()->setBoundingBox() and touches the owner.
    virtual void cropinterface_setBoundingBox(const float bbox[6]) = 0;

    /// Compute smallest box containing all voxels>=threshold
    virtual void cropinterface_computeAutoBox(float threshold, int box[6]) = 0;

    /// Tcl command interface
    virtual int interface_parse(Tcl_Interp* t, int argc, char** argv);
};

template<class PROXY>
class HxLattice3CropInterfaceImplTemplate : public HxLattice3CropInterface
{
    MC_ABSTRACT_TEMPLATE_HEADER (HxLattice3CropInterfaceImplTemplate <PROXY>);
  
  public:
    HxLattice3CropInterfaceImplTemplate (HxObject* owner, PROXY* p) : proxy(p) {
        setOwner (owner);
    }

    virtual const int* cropinterface_dims() const {
        return proxy->cropinterface_dims();
    }

    virtual HxCoord3* cropinterface_coords() const {
        return proxy->cropinterface_coords();
    }

    virtual bool cropinterface_crop(const int min[3], const int max[3], const char* replicate) {
        return proxy-> cropinterface_crop(min, max, replicate);
    }

    virtual bool cropinterface_swapDims(int ix, int iy, int iz) {
        return proxy-> cropinterface_swapDims(ix, iy, iz);
    }

    virtual bool cropinterface_flip(int dimension) {
        return proxy->cropinterface_flip(dimension);
    }

    virtual void cropinterface_setBoundingBox(const float bbox[6]) {
        proxy->cropinterface_setBoundingBox(bbox);
    }

    virtual void cropinterface_computeAutoBox(float threshold, int box[6]) {
        proxy-> cropinterface_computeAutoBox(threshold, box);
    }

  protected:
    PROXY* proxy;
};

#endif

/// @}

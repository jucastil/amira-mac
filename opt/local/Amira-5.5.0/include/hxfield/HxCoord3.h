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
#ifndef COORD3
#define COORD3

#include <mclib/McHandable.h>
#include <mclib/McPrimType.h>
#include <hxfield/HxCoordType.h>
#include <hxfield/HxFieldWinDLLApi.h>

class HxLoc3Regular;

/// Abstract base class for all types of lattice coordinates.

class HXFIELD_API HxCoord3 : public McHandable 
{
  public:
    /// Returns coordinate type.
    HxCoordType coordType() const { return theCoordType; }

#ifndef HX_NO_DIMS
    /** Returns lattice dimensions as pointer to an int vector.
        The same remarks apply as for HxLattice3::dims(). This
        method will be hidden if HX_NO_DIMS is defined.
        /sa HxLattice::dims() */
    const int* dims() const { return theDims32; }
#endif

    /** Returns lattice dimensions as pointer to a mculong vector.
        The same remarks apply as for HxLattice3::dimsLong().
        /sa HxLattice::dimsLong() */
    const mculong* dimsLong() const { return theDims; }

    /** Returns lattice dimensions as pointer to an int vector.
        This method is identical to dims() but it will not be hidden
        if HX_NO_DIMS is defined. Moreover, the same remarks apply as
        for HxLattice3::dimsInt().
        /sa HxLattice::dimsInt() */
    const int* dimsInt() const { return theDims32; }

    /// Resizes coordinate array.
    virtual void resize(const int dims[3]) = 0;

    /// Create a HxLocation3 object for the particular coordinate type.
    virtual HxLoc3Regular* createLocation() = 0;

    /// Creates a coordinate object of given type.
    static HxCoord3* create(const int dims[3], HxCoordType coordType);

    /// Returns bounding box of lattice.
    virtual void getBoundingBox(float bbox[6]) const = 0;

    /// Sets bounding box (non-uniform coords are scaled properly).
    virtual void setBoundingBox(const float bbox[6]) = 0;

    /// Performs flip operation on coordinates.
    virtual bool flip(int dimension);

    /// Performs swap operation on coordinates.
    virtual bool swapDims(const int didx[3]);

    /// Performs crop operation and adjusts coordinates.
    virtual bool crop(const int min[3], const int max[3]) = 0;

    /// Computes coordinates of given lattice node.
    virtual void pos(int i, int j, int k, float* res) const = 0;

    /// Creates a copy of coordinate object.
    virtual HxCoord3* duplicate() const = 0;

    static const char* getCoordTypeName(HxCoordType coordType);

    /// returns true if other object describes the same coordinates.
    bool equals( HxCoord3* other ) const;
  protected:
    /// Constructor.
    HxCoord3(const int dims[3], HxCoordType c);

    int theDims32[3];
    mculong theDims[3];
    const HxCoordType theCoordType;

  private:
    /** Implements equals().  Derived classes must implement this
        function.  Return true if the internal state describes the
        same coordinates.
      */
    virtual bool doEquals( HxCoord3* other ) const = 0;
};

#endif

/// @}

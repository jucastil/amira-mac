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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef _HX_LEGO_SURFACE_
#define _HX_LEGO_SURFACE_

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortToggleList.h>
#include <hxsurface/HxSurface.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>
#include <mclib/McData3D.h>

/// This class computes a Lego-like surface from a UniformLabelField

class HXSURFTOOLS_API HxLegoSurface : public HxCompModule
{
    HX_HEADER(HxLegoSurface);

  public:

    /// Default constructor.
    HxLegoSurface();

    /// Invokes actual computation.
    virtual void compute();

    /// Port select
    HxPortToggleList portOptions;

    /// Do it button.
    HxPortDoIt portAction;

  protected:

    McDArray<McDArray<McDArray<int> > > help;

    typedef short BlockIndices[4];
    typedef short SignArray[3];

    struct Wall {
        McVec3f points[4];           ///< The points for one wall (two triangles).
        BlockIndices const* indices; ///< Lego block corner indices of the points.
    };

    enum Direction {
        DIR_X_POS,
        DIR_Y_POS,
        DIR_Z_POS,
        DIR_X_NEG,
        DIR_Y_NEG,
        DIR_Z_NEG,
        DIR_COUNT
    };

    Wall wall;

    double vx, vy, vz, vx2, vy2, vz2;

    /// Generate the surface and put it into the Object pool.
    void doIt();

    /// Computes the 4 points for one wall (two triangles) for the given voxel
    /// position. Note that in Amira, voxels are sampled at their centers.
    void computePoints(int x, int y, int z, Direction dir);

    /// Make a rectangular wall (two triangles) between two voxels from the UniformLabelField.
    void makeWall(short in, short out, HxSurface *surface, int x, int y, int z);

    /// Make all possible patches for this LabelField (without i = j and without i, j and j, i).
    void createPatches(HxSurface *surface);
};

#endif

/// @}

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

/// @addtogroup hxsurfremesh hxsurfremesh
/// @{
#ifndef _Rm_SURFACE_PATCH_GROWER_h_
#define _Rm_SURFACE_PATCH_GROWER_h_

#include <mclib/McBitfield.h>
#include <mclib/McDArray.h>
#include <mclib/McHandable.h>

#include <hxsurface/Surface.h>
#include "hxsurfremeshAPI.h"

/** Extraction of a patch of triangles from a region
    growing process on the surface from a given number
    of edge-connected seed points. The resulting patch
    may touch itself (like an open cylinder) and it
    will be cut open through one seed.
*/

class HXSURFREMESH_API RmSurfacePatchGrower : public McHandable {

public:

    /// Constructor.
    RmSurfacePatchGrower(Surface* surf);

    /** Compute patch by doing a breadth-first search
        on the triangles (across their edges) starting
        from a set of seed triangles (see also Surazhky 
        et al.: Explicit Surface Remeshing). */
    void compute(const McBitfield& allowedTris,
                 McDArray<int>& seedTris,
                 McDArray<int>& seedPoints,
                 McDArray<int>& triangles,
                 McDArray<McDArray<int> >& boundary);

    /// Compute local neighbourhood around given triangle
    void computeTriangleNeighbourhood(int tri, 
                                      const McVec3f& bary,
                                      McDArray<int>& triangles,
                                      McDArray<McDArray<int> >& boundary);

    /// Create contour information of a surface
    static void createContours(Surface* surface, int createEdgeIds = 0);

    /// Destructor.
    ~RmSurfacePatchGrower();

protected:

    /// Surface object.
    Surface* theSurface;

    /// Surface of the new patch.
    Surface* thePatch;

    /// Visited triangles during patch growing.
    McBitfield visitedTriangles;

    /// Init flag
    bool wasInit;

    /// Initialize computations
    void init();

    /// Recompute patch and its contours using given triangles
    void recomputePatch(Surface* patch, const McDArray<int>& triangles);

    /// Check orientation of edge-connected nodes, if false: repair
    static int checkOrientation(Surface* surface,
                                McDArray<int>& nodes, 
                                const McDArray<int>& triangleList);

    /// Breadth first search from initTri, stopping when other seedTris are visited
    void bfs(int initTri, const McDArray<int>& seedTris, McDArray<int>& triangles);
    void bfs(McDArray<int>& termTris, McDArray<int>& seedPoints, McDArray<int>& triangles);

    ///
    void trim(const McBitfield& forbiddenTris, McDArray<int>& triangles);

    /** Determines whether a point (given by barycentric coordinates) lies
        a) inside the triangle (with respect to some safety margin),
        b) along one of the edges, or
        c) close to a vertex.
        Returns 
        a) all vertices belonging to the triangle, 
        b) vertices belonging to the triangle, or
        c) vertex.
    */
    void computeTriangleRegion(int tri, 
                               const McVec3f& bary,
                               McSmallArray<int,3>& vertices,
                               float margin = 0.2);

    ///
    int findEdge(int p1, int p2);

};

#endif

/// @}

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
#ifndef _Rm_SURFACE_CHART_h_
#define _Rm_SURFACE_CHART_h_

#ifdef _WIN32
// warning C4355: 'this' : used in base member initializer list
#pragma warning( disable: 4355 )
#endif

#include <hxsurface/Surface.h>

#include "hxsurfremeshAPI.h"
#include <mclib/McStaticQuadtree.h>
#include <mclib/McList.h>

class ChartTimer;

template <class Key, class Value> class McHashTable;


/// This class contains the parametrization of a surface-patch

class HXSURFREMESH_API RmSurfaceChart : public Surface {

public:

    /// Different chart types.
    typedef enum { UNDEFINED_CHART, MAIN_CHART } ChartType;

    /// Constructor.
    RmSurfaceChart();

    /// Destructor.
    ~RmSurfaceChart();

    /** Determine the amount of console output.  A value of 0 will
        suppress all output. */
    void setVerbosity( const int verbosity );

    /* --------------------- Data section -------------------- */

    /** Mapping of param-points to surface points 
        This mapping is surjective, due to boundary construction
        (see SurfacePatchification). */
    McDArray<int> originalPoints;

    /// Bijective mapping of param-triangles to surface triangles
    McDArray<int> originalTriangles;
    
    /// Branch-points of the boundary in the parameter domain
    McDArray<int> branchPoints;

    /// Chart type
    ChartType type;

    /// Chart timer
    ChartTimer *timer;

    /* --------------------- Member section -------------------- */
        
    /// Clear chart
    void clear();

    /// Clear (large) temporary variables
    void clearTemps();

    /// Initializes computation of quadtree, triangle areas and paramTriangles
    void initLookup(bool useQt=true);

    /// Compute triangle and barycentric coords from coord in the domain (using a quadtree)
    bool findTriangle(const McVec3f& coord2d, int& tri3d, McVec3f& bary, bool findBorderTri=true) const;

    /// Compute triangle and barycentric coords from coord on the border of the domain
    bool findBorderTriangle(const McVec3f& coord2d, int& tri3d, McVec3f& bary) const;

    /// Compute coord in parameter domain from barycentric coords of given triangle
    bool getCoord2d(int tri3d, const McVec3f& bary, McVec3f& coord2d) const;
    bool getCoord2d(int point3d, McVec3f& coord2d) const;

    /// Assignment operator
    RmSurfaceChart& operator=(const RmSurfaceChart& other)
    {
        copyData(other);
        return (*this);
    }

protected:

    int m_verbosity;

    /* --------------------- Lookup data -------------------- */

    /// Flag for usage of quadtree
    bool useQuadtree;

    /// Inverse mapping of originalTriangles. Initialized by @c initLookup (temporary).
    McHashTable<int,int>* paramTriangles;
    McHashTable<int,int>* paramPoints;

    /// Quadtree used in the computation of the domain triangulation (temporary).
    McStaticQuadtree<int> quadtree;

    /// Areas of the triangles in the parameter domain (temporary)
    McDArray<float> triAreas;

    /* --------------------- Lookup members -------------------- */

    /// Compute paramTriangles array.
    void invertOriginalTriangles();

    /// Create quadtree for domain triangulation.
    void buildQuadtree();
    
    /// Compute area of domain triangles.
    void getTriAreas();

    /// Compute triangle/barycentric coordinates in domain
    int findTriangle(const McVec3f& coord2d, McVec3f& bary) const;

    /** Compute triangle and barycentric coords from coord in the domain 
        (using the method by Owen et al., Meshing Roundtable 2002) */
    bool findTriangle2(const McVec3f& coord2d, int& tri3d, McVec3f& bary, bool findBorderTri=true) const;

    /// Compute triangle/barycentric coordinates closest to @c pos on boundary of domain
    int findBorderTriangle(const McVec3f& pos, McVec3f& bary) const;

    /// Compute barycentric coordinates for given triangle
    void computeBarycentricCoords(float x, float y, int which, McVec3f& bary) const;

    /// Copy data
    void copyData(const RmSurfaceChart &source);
};

/// Class for timing chart survival
class ChartTimer : public McLink {
public:
    int delta;
    RmSurfaceChart* chart;
};


#endif

/// @}

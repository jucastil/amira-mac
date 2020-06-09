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
#ifndef TETRA_CUT
#define TETRA_CUT

#include <mclib/McBitfield.h>
#include <Inventor/SbLinear.h>
#include <hxfield/TetraGrid.h>
#include <hxfield/HxFieldWinDLLApi.h>

#define EPS 1E-8

/** Computes intersection of a tetrahedral grid and a plane
	This class intersects an arbitrary cutting plane with any data field
    defined on a tetrahedral grid. Every single tetrahedron is tested for
    intersection with a plane defined by an origin and two linear
    independent direction vectors u and v. If an intersection is detected
    an user-defined callback function is invoked. The triangle or
    rectangle, which arises by intersecting a tetrahedron with a plane, is
    passed as an argument to the callback.  The polygon may also be
    scan-converted into a raster defined by multiples of the direction
    vectors u and v. For each raster position again a user-defined callback
    is invoked.
   
    This class is tuned for maximal speed. Therefore the interface
    is somewhat restricted and awkward. 
*/

class HXFIELD_API TetraCut {

  public:
    struct Vertex;
    struct Polygon;

    /** Prototype of intersection callback. It is called for
	    each tetraeder that is intersected and returns the 
		intersection as a polygon. */
    typedef void IntersectionCB(int whichTetrahedron, Polygon& p);

    /** Prototype of scan conversion callback. This is called
	if no IntersectionCB is present. Then a scanconverted version
	of the polygon is produced and for each raster point
	this function is called to render it. */
    typedef void ScanConverionCB(int x, int y, Vertex& v);

    /** Provides access to node data during scan conversion.
		If no data is attached, this callback returns 0.
		\param whichTetrahedron  number of tetraheder
		\param data0 a pointer to the field in which the data is read
		Analogously, the pointers for all four vertices of tetraheder.
		At most, 6 scalar values for each vertex can be read (in the
		case of complex vector fields). 
		\return dimension of data at vertex. If a scalar field is
		attached, the return value is 1.
	*/
    typedef int DataAccessCB(int whichTetrahedron,
	float* data0, float* data1, float* data2, float* data3);

    /// 2D-vertex in cutting plane.
    struct Vertex {
	// the coordinates in the plane and height over the plane
	float sx, sy, z;
	/* the coordinates of the vertex (3 entries) and
	   the data field value at the vertex (maximum dimension 6) */
	float c[9]; 
    };

    /// 2D-polygon in cutting plane.
    struct Polygon {
	int n;
	Vertex v[4];
    };

    /// Constructor.
    TetraCut(const TetraGrid* grid, const SbVec3f& orig,
	const SbVec3f& norm, const SbVec3f& uVec, const SbVec3f& vVec);

    /// Default contructor.
    TetraCut();

    /// Destructor.
    ~TetraCut();

    /// Initializes cut operation.
    void init(const TetraGrid* grid, const SbVec3f& orig,
	const SbVec3f& norm, const SbVec3f& uVec, const SbVec3f& vVec);

    /// Computes intersection.
    void compute(DataAccessCB* dataAccess, IntersectionCB* intersectionCb,
	ScanConverionCB* scanConversionCb = NULL);

    /// Start scan conversion.
    void scanConvert(Polygon& p, ScanConverionCB* scanConversionCb);

    /// Select all tetrahedra of given matId (only selected ones will be cut)
    void selectMaterial(int matId);

    /// Unselect all tetrahedra of with given matId.
    void unselectMaterial(int matId);

    /// Select all tetrahedra. This is called automatically for new grids.
    void selectAll();

    /// Unselect all tetrahedra.
    void unselectAll();

    /** Returns a bitfield indicating which materials are selected. The
        bitfield has as many elements as there are materials in the current
        tetrahedral grid. If a material is at least partially selected then
        corresponding bit in the bitfield is set. */
    void getSelectionFlags(McBitfield& flags) const;

  private:
    const TetraGrid* grid;
    float orig[3];
    float norm[3];
    float uVec[3];
    float vVec[3];
    int N;  // number of additional variables to interpolate

    float* z;
    int cacheFlag;
    McDArray<int> tetraSelection;
    
    inline void initVertex(Vertex& v, float z, float *c);
    inline void intersect(const Vertex& a, const Vertex& b, Vertex& c);
    void scanline(int, Vertex& l, Vertex& r, ScanConverionCB*);
    void increment_x(const Vertex&, const Vertex&, Vertex&, Vertex&, int);
    void increment_y(const Vertex&, const Vertex&, Vertex&, Vertex&, int);
    void computeFromCache(DataAccessCB* dataAccess, IntersectionCB*
	intersectionCb, ScanConverionCB* scanConversionCb = NULL);
};

inline void
TetraCut::initVertex(Vertex& v, float z, float *c)
{
    v.z = z;
    v.c[0] = c[0];
    v.c[1] = c[1];
    v.c[2] = c[2];
}

inline void
TetraCut::intersect(const Vertex& a, const Vertex& b, Vertex& res)
{
    float q[3], dist = a.z - b.z;

    if (dist<EPS && dist>-EPS) {
        for (int i=0; i<3+N; i++)
            res.c[i] = 0.5*(a.c[i] + b.c[i]);
    }
    else {
        float u = a.z/dist;
        for (int i=0; i<3+N; i++)
            res.c[i] = a.c[i] + u*(b.c[i] - a.c[i]);
    }

    q[0] = res.c[0] - orig[0];
    q[1] = res.c[1] - orig[1];
    q[2] = res.c[2] - orig[2];
    res.sx = uVec[0]*q[0] + uVec[1]*q[1] + uVec[2]*q[2];
    res.sy = vVec[0]*q[0] + vVec[1]*q[1] + vVec[2]*q[2];
}

#endif

/// @}

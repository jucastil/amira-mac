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
#ifndef TETRAGRID_H
#define TETRAGRID_H

#include "oint.h"

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <mclib/McStaticOctree.h>
#include <mclib/McBitfield.h>
#include <mclib/McMat3f.h>

#include <amiramesh/AmiraMesh.h>

/// New data-structure for tetrahedral grids.
class SoProjection;
class HXFIELD_API TetraGrid { 

  public:

    // ------------------------------------------------------------------
    //@name Subclass declarations
    //@{

    /// Tetrahedron.
    struct HXFIELD_API Tetra {
	/// Indices of the four points of a tetrahedron.
	int points[4];

	/// Indices of the four triangles of a tetrahedron.
	int triangles[4];

	/// Assignment operator.
	Tetra& operator= (const Tetra& other) {
	    for (int i=sizeof(Tetra)/sizeof(int)-1; i>=0; i--)
		((int*)this)[i] = ((int*)&other)[i];
	    return *this;
	}
    };

    /// Triangle.
    struct HXFIELD_API Triangle {
	/// Indices of the three points of the triangle.
	int points[3];

	/** Indices of the neighbouring tetras (0=lower, 1=upper).
	    If there is only one neigbour, the 2nd index must be -1.
    */
	int tetras[2];

	/// Normal vector of the triangle.
	McVec3f normal;

	/// This is true if triangle is part of a domain boundary.
	unsigned short isBoundary;

	/** This denotes the type of numerical boundary condition. Note,
	    that boundary conditions may also be defined for inner
	    triangles which are not part of a domain boundary. Likewise,
	    there may be boundary triangles with no special numerical
	    boundary condition. That is, why we need two variables. */
	unsigned short boundaryConditionId;



	/// Assignment operator.
	Triangle& operator= (const Triangle& other) {
	    for (int i=sizeof(Triangle)/sizeof(int)-1; i>=0; i--)
		((int*)this)[i] = ((int*)&other)[i];
	    return *this;
	}
    };
    
    /// Edge.
    struct HXFIELD_API Edge {
	/// Index of the first point of the edge.
	int points[2];

	/// Index operator.
	int& operator[] (int i) { return points[i]; }

	/// Assignment operator.
	Edge& operator= (const Edge& other) {
	    points[0] = other.points[0];
	    points[1] = other.points[1];
	    return *this;
	}
    };

    /// For each tetrahedron the indices of the six edges.
    /// ATTENTION: index starts with 1
    struct HXFIELD_API EdgesPerTetra {
	/// Index of the six edges.
	int idx[6];

	/// Index operator.
	int& operator[] (int i) { return idx[i]; }

	/// Assignment operator.
	EdgesPerTetra& operator= (const EdgesPerTetra& other) {
	    for (int i=0; i<6; i++)
		idx[i] = other.idx[i];
	    return *this;
	}
    };

    //@}

    // ------------------------------------------------------------------
    //@name Member variables
    //@{

    /// Array of grid points.
    McDArray<McVec3f> points;

    /// For every point id of a triangle incident at that point.
    McDArray<int> vertexHints;

    /// Array of tetrahedrons.
    McDArray<Tetra> tetras;

    /// For every tetrahedron a material id.
    McDArray<unsigned char> materialIds;

    /// For every tetrahedron indices of its edges (optional).
    McDArray<EdgesPerTetra> edgesPerTetra;

    /// Array of triangles.
    McDArray<Triangle> triangles;

    /// Array of edges (optional).
    McDArray<Edge> edges;    

    /// Tetrahedrons per point (optional).
    McDArray< McSmallArray<int,8> > tetrasPerPoint;

    /// Indicates how many points are duplicated.
    int numDuplicatedNodes;

    /// Reference to parameters of derived HxTetraGrid
    HxParamBundle& params;

    /// Octree for point location
    McStaticOctree<int> octree;

    //@}

    // ------------------------------------------------------------------
    //@name Public methods
    //@{

    /// Constructor.
    TetraGrid(HxParamBundle* parameters);

    /// Destructor.
    ~TetraGrid();

    /// Deletes everything, creating an empty grid.
    void clear();

    /// Returns bounding box of point coordinates.
    void getBoundingBox(float box[6]) const;

    /// Sort tetrahedra according to material type and z-direction.
    void sortTetrahedra();

    /** Extracts all faces (need to be called after topology changed).
	In case of duplicated vertices two neighbouring tetrahedra may
	reference different points with truely identical coordinates.
	This situation will be checked and only a single triangle will
	be created between such tetrahedra. If you know in advance
	which vertices are duplicated, you may provide an @c aliasInfo
	array, denoting for each vertex the id of the original non-aliased
	vertex. If @c aliasInfo is zero, the required information will be
	computed by means of computeAliasInfo(). Optionally, a list of
	boundary triangles can be passed to the methods. Each one is given by
	by 3 point indices.*/
    void createTriangles2(const int* aliasInfo=0, int nBoundaryTriangles=0, 
			  int (*pointIndices)[3]=0, unsigned char* ids=0);

    /** Computes triangle normals. Need to be called after the coordinates
	of the grid vertices have been modified. This method is also
	called from createTriangles. */
    void computeNormals();

    void setProjection(SoProjection *projection){m_projection = projection;}

    SoProjection *m_projection;

    /// Extracts all edges (needs to be called after topology changed)
    void createEdges();

    /// Creates edgesPerTetra.
    void createEdgesPerTetra();

    /** Fix inverted tetrahedra. The volume of every tetrahedron is
	computed. If the volume is negative, the tetrahedron's vertices
	are swapped so that the volume gets positive. */
    void fixOrientation();

    /** Marks a tetrahedron as removed.  It doesn't get physically removed
	until the next call of removeObsoleteTetras(). */
    inline void makeObsolete(int i){tetras[i].points[0]=-1;};

    /// Returns true if a tetrahedron is marked obsolete, false otherwise.
    inline int isObsoleteTetra(int i){
	if (i<0 || i>=tetras.size())
	    return 1;
	else
	    return (tetras[i].points[0]==-1);};
    
    /// Returns true if a triangle is marked obsolete, false otherwise.
    inline int isObsoleteTriangle(int i){
	if (i<0 || i>=triangles.size())
	    return 1;
	else
	    if (triangles[i].tetras[0]==-1 && triangles[i].tetras[1]==-1)
		return 1;
	    else
		return (triangles[i].points[0]==-1);};
    
    /// returns opposite face of vertex iVert in tetra iTet.
    inline int getOppositeFace(int iTet, int iVert){
	if (isObsoleteTetra(iTet))
	    return -1;
	int i;
	for (i=0; i<4; i++)
	    if (tetras[iTet].points[i] == iVert)
		return tetras[iTet].triangles[i];
	return -1;};

    /// Returns opposite face of face iFace at edge from-to in tetra iTet.
    inline int getOppositeFaceAtEdge(int iTet, int iFace, int from, int to){
	if (isObsoleteTetra(iTet))
	    return -1;
	if (iFace < 0 || from < 0 || to < 0)
	    return -1;
	int i;
	for (i=0; i<4; i++) {
	    int iVert = tetras[iTet].points[i];
	    if (iVert != from && iVert != to) {
		int iTri = tetras[iTet].triangles[i];
		if (iTri != iFace)
		    return iTri;
	    }
	}
	return -1;};

    /// returns opposite vertex of face iFace in tetra iTet.
    inline int getOppositeVertex(int iTet, int iFace){
	if (isObsoleteTetra(iTet))
	    return -1;
	int i;
	for (i=0; i<4; i++)
	    if (tetras[iTet].triangles[i] == iFace)
		return tetras[iTet].points[i];
	return -1;};

    /// returns opposite tetra of tetra iTet at face iFace.
    inline int getOppositeTetra(int iFace, int iTet){
	if (isObsoleteTriangle(iFace))
	    return -1;
	if (triangles[iFace].tetras[0] == iTet)
	    return triangles[iFace].tetras[1];
	if (triangles[iFace].tetras[1] == iTet)
	    return triangles[iFace].tetras[0];
	return -1;};

    /// creates tetrahedron from 4 faces given.
    int createTetraFromFaces(int iTet, int* faces);

    /** Removes unused tetrahedrons. A tetrahedron is considered not to be
        part of the grid if the value of tetras[i].points[0] is negative.
	This methods removes all such tetrahedrons. All arrays and indices
	of the grid are updated as necessary. */
    void removeObsoleteTetras();

    /** Removes unused triangles. A triangle is considered not to be
        part of the grid if the value of triangles[i].points[0] is negative.
	This methods removes all such triangles. All arrays and indices
	of the grid are updated as necessary. */
    void removeObsoleteTriangles();

    /** performs a consistency check on the tetragrid. returns one if
	grid is consistent, zero otherwise */
    int checkConsistency();

    /** For every point find one triangle incident at that point. The
	results are stored in the vertexHints array. For points not
	referenced by any triangle the value of vertexHints is
	set to -1. This is the case for duplicated points. */
    void computeVertexHints();

    ///
    void computeTetrasPerPoint();

    ///
    int computeAliasInfo(McDArray<int>& aliases);

    /// Initialize tetrahedral grid from a AmiraMesh file descriptor.
    int initFromAmiraMesh(AmiraMesh* m);

    /// Rebuilds octree.
    void rebuildOctree();

    /// find out if edge is boundary edge
    int isBoundaryEdge(int vert1, int vert2);

    /// find out if edge is boundary condition edge
    int isBoundaryConditionEdge(int vert1, int vert2);

    /// bisect edge
    int bisectEdge(int iEdge);

    /// bisect edge
    int bisectEdge(int vert1, int vert2, McVec3f* newVertex=0);
    
    /// collapse edge
    int collapseEdge(int vert1, int vert2);

    /**
        Computes the coordinate transform matrix from local barycentric coordinates
        to world coordinates.
    */
    McMat3f getCoordTransformMatrix(int iTetra);

    /// determinant of Jacobi matrix for transformation to unit tetrahedron.
    float detJ(int iTet);

    /// Compute determinant, inner and outer radius for tetrahedron.
    void getQuality(int nr_tetrahedron, float &determinante, 
		    float &inner_radius, float &outer_radius);

    /// Compute edge quality.
    float getEdgeQuality(int iEdge);

    /// compute minimal determinant for list of tetras.
    float calcMinDet(McSmallArray<int,8>& tetraList,
		     McSmallArray<int,8>& iTetWorst);

    /// compute maximal diameter ratio for list of tetras.
    float calcMaxDiamRatio(McSmallArray<int,8>& tetraList,
			   McSmallArray<int,8>& iTetWorst);

    /// Global refinement.
    void globalRefine();

    /** The volume of the grid (default) or of the given material id.
        Note: Stored Material Ids start with zero, thus Parameter values
              must be decremented by 1.*/
    double getVolume(int materialId = -1);

    /** The amount of islands, i.e. isolated regions within the grid */
    int getNumIslands(void);

    /** face connected component search, starting from tetraIndex.
        @param tetras must be a bit field with the same size as the amount
        of tetrahedrons, wherein connected tetras of the region are marked.
        The return value indicates the size, i.e. the number of 
        tetrahedrons of the region that contains tetra[@c tetraIndex]. */
    unsigned long getConnectedElements(unsigned int tetraIndex, McBitfield & tetras);

    /** Sets a triangle. The size of the triangle array is not modified.
        It must have been resized before. The method also recomputes the
        triangle normal.
        @param index the index of the triangle to be set
        @param point1 the index of the first point of the triangle
        @param point2 the index of the second point of the triangle
        @param point3 the index of the third point of the triangle
        @param cell1 the index of the first adjacent tetrahedron
        @param cell2 the index of the second adjacent tetrahedron or -1,
               if the triangle is a boundary face with only one adjacent cell
        @param bnd a flag indicating if the traingle is a boundary face or not
        @param bndCnd the boundary condition id of the triangle */
    inline void insertTriangle(int index, int point1, int point2, 
        int point3, int cell1, int cell2, int bnd, int bndCond)
    {
        if (cell1==-1) {
            cell1 = cell2;
            cell2 = -1;
        }		

        assert(index < triangles.size());
        Triangle &triangle = triangles[index];
        triangle.points[0] = point1;
        triangle.points[1] = point2;
        triangle.points[2] = point3;
        triangle.tetras[0] = cell1;
        triangle.tetras[1] = cell2;
        triangle.isBoundary = bnd;
        triangle.boundaryConditionId = bndCond;

        triangle.normal = 
            ((coords()[point2]-coords()[point1]).cross(coords()[point3]-coords()[point1]));
        triangle.normal.normalize();
    }


    /** Appends a triangle to the grid. The size of the triangle array is enlarged
        by one. The method also recomputes the triangle normal. It returns
        the id of the new triangle.
        @param point1 the index of the first point of the triangle
        @param point2 the index of the second point of the triangle
        @param point3 the index of the third point of the triangle
        @param cell1 the index of the first adjacent tetrahedron
        @param cell2 the index of the second adjacent tetrahedron or -1,
               if the triangle is a boundary face with only one adjacent cell
        @param bnd a flag indicating if the traingle is a boundary face or not
        @param bndCnd the boundary condition id of the triangle */
    inline int addTriangle(int point1, int point2, 
        int point3, int cell1, int cell2, int bnd, int bndCond)
    {
        if (cell1==-1) {
            cell1 = cell2;
            cell2 = -1;
        }		

        int id = triangles.appendSpace(1);
        Triangle& face = triangles.last(); 
        face.points[0] = point1;
        face.points[1] = point2;
        face.points[2] = point3;
        face.tetras[0] = cell1;
        face.tetras[1] = cell2;
        face.isBoundary = bnd;
        face.boundaryConditionId = bndCond;
        return id;
    }

    // Updates the triangle normal. insidePoint ???
    inline void updateFaceNormal(int i, int insidePoint) 
    {
        assert(i<triangles.size());

        Triangle &face = triangles[i];
        face.normal = 
            ((coords()[face.points[1]]-coords()[face.points[0]]).cross(coords()[face.points[2]]-coords()[face.points[0]]));
        face.normal.normalize();

        if (face.normal.dot(coords()[face.points[1]]-coords()[insidePoint]) > 0) {
            face.normal *= -1;
            insidePoint = face.points[1];
            face.points[1] = face.points[0];
            face.points[0] = insidePoint;
        }
    }

    //@}

    // ------------------------------------------------------------------
    //@name For compatibility with old HxTetraGrid.
    //@{

    /// Returns the number of vertices.
    int nNodes() const { return points.size(); }

    /// Returns the number of edges.
    int nEdges() const { return edges.size(); }

    /// Returns the number of triangles.
    int nFaces() const { return triangles.size(); }

    /// Returns the number of tetrahedrons.
    int nTetras() const { return tetras.size(); }

    /// Returns the number of duplicated nodes.
    int nDuplicatedNodes() const { return numDuplicatedNodes; }

    /// Returns pointer to vertex coordinates.
    McVec3f* coords() const { return (McVec3f*) points.dataPtr(); }

    /// Returns pointer to edge's vertex indices.
    int (*edgePIdx() const)[2] { return (int(*)[2]) edges.dataPtr(); }

    /// Returns pointer to tetraheda's edge indices.
    int (*tetraEIdx() const)[6] { return (int(*)[6]) edgesPerTetra.dataPtr(); }

    /* Not supported any longer:

    int nBoundaryTriangles() const -> ordinary triangles are tagged now
    SbVec3f* normals() -> normals stored in struct Triangle
    FacePIdx facePIdx() -> triangle vertices stored in struct Triangle
    FaceTet* faceTet() -> neighbouring tetras stored in struct Triangle
    TetraPIdx tetraPIdx() -> vertices of tetra stored in struct Tetra
    TetraFIdx tetraFIdx() -> triangles of tetra stored in struct Tetra

    */

    //@}
};

#endif


/// @}

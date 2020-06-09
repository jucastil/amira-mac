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
#ifndef HEXAGRID_H
#define HEXAGRID_H

#include <hxfield/HxFieldWinDLLApi.h>
//#include "oint.h"

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <amiramesh/AmiraMesh.h>
#include <amiramesh/HxParamBundle.h>
#include <mclib/McMat3f.h>
#include <mclibthreaded/McMutex.h>

#include <mclib/McSpacetree.h>

/// New data-structure for hexahedral grids.

class HXFIELD_API HexaGrid { 

  public:

    // ------------------------------------------------------------------
    //@name Subclass declarations
    //@{

    /// Hexahedron.
    struct HXFIELD_API Hexa {
	/// Indices of the eight points of a hexahedron.
	/// The order of indices for a regular cell
	/// is: 0:(x0,y0,z0),1:(x1,y0,z0),2:(x1,y1,z0),3:(x0,y1,z0)
	///     4:(x0,y0,z1),5:(x1,y0,z1),6:(x1,y1,z1),7:(x0,y1,z1)
	int points[8];

	/// Indices of the faces of a hexahedron.
	McSmallArray<int,6> faces;

	/// Assignment operator.
	Hexa& operator= (const Hexa& other) {
	    for (int i=0; i<8; i++)
		points[i] = other.points[i];
            faces = other.faces;
	    return *this;
	}
    };

    /// Faces (squares) 
    struct HXFIELD_API Face {
	/// Indices of the four points of the face.
	int points[4];

	/// Indices of the neighbouring hexas.
	int hexas[2];

	McVec3f normal;

	/// This is true if the face is part of a domain boundary.
        unsigned short isBoundary;

	/** This denotes the type of numerical boundary condition. Note,
	    that boundary conditions may also be defined for inner
	    faces which are not part of a domain boundary. Likewise,
	    there may be boundary faces with no special numerical
	    boundary condition. That is, why we need two variables. */
	unsigned short boundaryConditionId;

        /// Assignment operator.
        Face& operator= (const Face& other) {
            for (int i=sizeof(Face)/sizeof(int)-1; i>=0; i--)
                ((int*)this)[i] = ((int*)&other)[i];
            return *this;
        }
    };
    
    //@}

    // ------------------------------------------------------------------
    //@name Member variables
    //@{

    /// Array of grid points.
    McDArray<McVec3f> points;

    /// Array of hexahedrons.
    McDArray<Hexa> hexas;

    /// For every hexahedron a material id.
    McDArray<unsigned char> materialIds;

    /// Array of faces.
    McDArray<Face> faces;

    /// Hexahedrons per point (optional).
    McDArray< McSmallArray<int,8> > hexasPerPoint;

    /// Indicates how many points are duplicated.
    int numDuplicatedNodes;

    /// Reference to parameters of derived HxHexaGrid
    HxParamBundle& params;

    // point location in hexa grid.
    bool locatePoint(McVec3f pos, int& iCell, McVec3f& barycentrics);

    // invalidate point location data structure (octree)
    void octreeInvalidate();

    // prints some informations about the octree to stdout.
    void octreeInfo();

    // Calculates the jacobian of the mapping from local (barycentric coordinates) into world-coordinates
    McMat3f calcJacobianOfBarycentricsToWc(int iCell, McVec3f& b);

    // Calculates the center of the hexahedrons
  	const McDArray<McVec3f>& getCentroids();

protected: 
    /// Array of grid center points. 
	  /// Computed on demand by the getCentroids method
    McDArray<McVec3f> m_centerPoints;

    McMutex m_octreeMutex;
private:

    // no copy construction allowed!
    HexaGrid(HexaGrid&);

    McSpacetree<int,3,float> octree;

    // find local coordinates of pos in a given cell.
    void stencilWalk(int cell, McVec3f pos, McVec3f& b);

public:
    //@}

    // ------------------------------------------------------------------
    //@name Public methods
    //@{

    /// Constructor.
    HexaGrid(HxParamBundle* parameters);

    /// Destructor.
    virtual ~HexaGrid();

    /// Deletes everything, creating an empty grid.
    void clear();

    /// Returns bounding box of point coordinates.
    void getBoundingBox(float box[6]) const;

    /// Sort hexahedra according to material type and z-direction.
    void sortHexahedra();

    /** Fix inverted hexahedra.*/
    void fixOrientation();

    /** Extracts all faces (need to be called after topology changed).
	In case of duplicated vertices two neighbouring tetrahedra may
	reference different points with truely identical coordinates.
	This situation will be checked and only a single triangle will
	be created between such tetrahedra. If you know in advance
	which vertices are duplicated, you may provide an @c aliasInfo
	array, denoting for each vertex the id of the original non-aliased
	vertex. If @c aliasInfo is zero, the required information will be
	computed by means of computeAliasInfo(). */
    void createFaces(const int* aliasInfo=0, int nBoundaryTriangles=0, 
                     int (*pointIndices)[4]=0, unsigned char* ids=0);

    /** Computes Face normals. Need to be called after the coordinates
	of the grid vertices have been modified. This method is also
	called from createFaces. */
    void computeNormals();

    /** Marks a hexahedron as removed.  It doesn't get physically removed
	until the next call of removeObsoleteHexas(). */
    inline void makeObsolete(int i){hexas[i].points[0]=-1;};

    /// Returns true if a hexahedron is marked obsolete, false otherwise.
    inline int isObsoleteHexa(int i) {
        return (i<0) || (i>=hexas.size()) || (hexas[i].points[0]==-1);
    }
    
    /// Returns true if a face is marked obsolete, false otherwise.
    inline int isObsoleteFace(int i) {
	return (i<0) || (i>=faces.size()) || (faces[i].points[0]==-1) ||
            (faces[i].hexas[0]==-1 && faces[i].hexas[1]==-1);
    }

    /// returns opposite hexa of hexa iHex at face iFace.
    inline int getOppositeHexa(int iFace, int iHex) {
	if (isObsoleteFace(iFace))
	    return -1;
	if (faces[iFace].hexas[0] == iHex)
	    return faces[iFace].hexas[1];
	if (faces[iFace].hexas[1] == iHex)
	    return faces[iFace].hexas[0];
	return -1;
    }

    // creates hexahedron from 6 faces given.
    // int createHexaFromFaces(int iHex, int* faces);

    /** Removes unused hexahedrons. A hexahedron is considered not to be
        part of the grid if the value of hexas[i].points[0] is negative.
	This methods removes all such hexahedrons. All arrays and indices
	of the grid are updated as necessary. */
    void removeObsoleteHexas();

    /** Removes unused faces. A face is considered not to be
        part of the grid if the value of faces[i].points[0] is negative.
	This methods removes all such faces. All arrays and indices
	of the grid are updated as necessary. */
    void removeObsoleteFaces();

    /**
        Removes all vertices that are not referenced by any hexahedron.
        @return number of removed points
    */
    int removeUnusedPoints();

    /// 
    void computeHexasPerPoint();

    ///
    int computeAliasInfo(McDArray<int>& aliases);

    /// Initialize hexahedral grid from a Hypermesh file descriptor.
    int initFromAmiraMesh(AmiraMesh* m);

    /// Rebuilds octree.
    void rebuildOctree();

    /** Sets a face in the face array. The size of the face array is not modified.
        It must have been resized before. The method does not compute the normal
        of the face.
        @param index the index of the face to be set
        @param point1 the index of the first point of the face
        @param point2 the index of the second point of the face
        @param point3 the index of the third point of the face
        @param point4 the index of the fourth point of the face
        @param cell1 the index of the first adjacent hexahedron
        @param cell2 the index of the second adjacent hexahedron or -1,
               if the face is a boundary face with only one adjacent cell
        @param bnd a flag indicating if the face is a boundary face or not
        @param bndCnd the boundary condition id of the face */
    inline void insertFace(int index, int point1, int point2, 
        int point3, int point4, int cell1, int cell2, int bnd, int bndCond)
    {
        if (cell1==-1) {
            cell1 = cell2;
            cell2 = -1;
        }		

        assert(index < faces.size());
        Face &face = faces[index];
        face.points[0] = point1;
        face.points[1] = point2;
        face.points[2] = point3;
        face.hexas[0] = cell1;
        face.hexas[1] = cell2;
        face.isBoundary = bnd;
        face.boundaryConditionId = bndCond;
    }

    /** Appends a face to the face array. The size of the face array is enlarged
        by one. The method does not compute the normal of the face. It returns
        the id of the new face.
        @param point1 the index of the first point of the face
        @param point2 the index of the second point of the face
        @param point3 the index of the third point of the face
        @param point4 the index of the fourth point of the face
        @param cell1 the index of the first adjacent hexahedron
        @param cell2 the index of the second adjacent hexahedron or -1,
               if the face is a boundary face with only one adjacent cell
        @param bnd a flag indicating if the face is a boundary face or not
        @param bndCnd the boundary condition id of the face */
    inline int addFace(int point1, int point2, 
        int point3, int point4, int cell1, int cell2, int bnd, int bndCond)
    {
        if (cell1==-1) {
            cell1 = cell2;
            cell2 = -1;
        }		

        int id = faces.appendSpace(1);
        Face& face = faces.last(); 
        face.points[0] = point1;
        face.points[1] = point2;
        face.points[2] = point3;
        face.points[3] = point4;
        face.hexas[0] = cell1;
        face.hexas[1] = cell2;
        face.isBoundary = bnd;
        face.boundaryConditionId = bndCond;
        return id;
    }

    /** Updates the face normal. The method recomputes the face normal from
        the coordinates of the vertices of the face. The normal will be
        normalized to unit length.
        @param i the index of the face to be updated */
    inline void updateFaceNormal(int i) {
        assert(i<faces.size());
        Face &face = faces[i];
        face.normal = 
            ((points[face.points[1]]-points[face.points[0]]).cross(points[face.points[2]]-points[face.points[0]])) +
            ((points[face.points[3]]-points[face.points[2]]).cross(points[face.points[1]]-points[face.points[2]]));
        face.normal.normalize();
    }

    //@}
};



#endif


/// @}

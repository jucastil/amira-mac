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

/// @addtogroup hxvertexset hxvertexset
/// @{
#ifndef TESS_SPHERE
#define TESS_SPHERE

#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <mclib/McVec3f.h>

#include <hxvertexset/HxVertexsetWinDLLApi.h>

#include <Inventor/SbLinear.h>

/** This class implements the triangulation of a sphere.
    The sphere will be centered at the origin. A radius and
    a complexity need to be specified, whereas the radius
    is optional (default radius exists).
    
    The triangulation of the sphere starts from an octahedron.
    The octahedron faces are then subdivided into a number
    of equilateral triangles according to the complexity,
    which is one less than the number of parts each octahedron
    edge is divided into. In order to obtain a sphere, the 
    points on the octahedron are normalized and scaled
    appropriately (according to the radius).
 */

class HXVERTEXSET_API TessSphere {
    
protected:  
    /// Radius of sphere.
    float radius;
    /** Complexity. Number of triangles is equal to
	8*(complexity+1)*(complexity+1). */
    int complexity;
    
    /// Octahedron edge.
    struct OctahedronEdge {
	int vertices[2];
	McDArray<int> points;
	OctahedronEdge() {};
	OctahedronEdge(int _vertices[2]) {
	    vertices[0] = _vertices[0];
	    vertices[1] = _vertices[1];
	}
	void setVertices(int _vertex0, int _vertex1) {
	    vertices[0] = _vertex0;
	    vertices[1] = _vertex1;
	}
	void startTesselation() {
	    points.clear();
	    points.append(vertices[0]);
	}
	void finishTesselation() {
	    points.append(vertices[1]);
	}
	void clear() {
	    points.clear();
	}
    };
    
    /// Octahedron face.
    struct OctahedronFace {
	int vertices[3];
	int edges[3];
	McDArray<int> points;
	OctahedronFace(int _vertices[3]) {
	    vertices[0] = _vertices[0];
	    vertices[1] = _vertices[1];
	    vertices[2] = _vertices[2];
	}
	OctahedronFace() {};
	void setVertices(int _vertex0, int _vertex1, int _vertex2) {
	    vertices[0] = _vertex0;
	    vertices[1] = _vertex1;
	    vertices[2] = _vertex2;
	}
	void setEdges(int _edge0, int _edge1, int _edge2) {
	    edges[0] = _edge0; 
	    edges[1] = _edge1; 
	    edges[2] = _edge2; 
	}   
	void getEdges(int idx[3]) {
	    idx[0] = edges[0];
	    idx[1] = edges[1];
	    idx[2] = edges[2];
	}
	void clear() {
	    points.clear();
	}
    };
    
    /// Information about octahedron edges.
    OctahedronEdge octahedronEdges[12];
    /// Information about octahedron faces.
    OctahedronFace octahedronFaces[8];
    /// Octahedron coords.
    McDArray<SbVec3f> octahedronCoords;
    /// Sphere coords.
    McDArray<SbVec3f> sphereCoords;
    
    /// All triangles - each tri is represented by 3 vertex indices.
    McDArray<int> triangles;
    /** Apart from a list of triangles, the triangles are also
	representing by a list of triangle strips and fans. */
    McDArray<McDArray<int> > triangleStrips;
    McDArray<McDArray<int> > triangleFans;

    /// Initialize octahedron.
    void makeOctahedron(float radius); 
    /// Generate tesselation.
    void tesselateSphere(float radius, int complexity);    
    
public:
    /// Constructor. Default radius is 1.0.
    TessSphere(float radius = 1.0);

    /** Invokes sphere tesselation. Must be called before
	getCoords(..), getTriangles(..) or getTriangleStrips(..)
	might be called. */
    void compute(int complexity);
    void compute(float radius, int complexity);

    /// Return sphere coords.
    void getCoords(McDArray<SbVec3f> &_coords) 
	{ _coords = sphereCoords; }
    /// Return triangles.
    void getTriangles(McDArray<int> &_triangles) 
	{ _triangles = triangles; }
    /// Return triangle strips along with the triangle fans.
    void getTriangleStrips(McDArray<McDArray<int> > &_triStrips,
			   McDArray<McDArray<int> > &_triFan) {
	_triStrips = triangleStrips; 
	_triFan    = triangleFans;
    }
    
};


#endif

/// @}

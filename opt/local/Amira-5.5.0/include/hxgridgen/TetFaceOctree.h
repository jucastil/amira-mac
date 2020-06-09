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

/// @addtogroup hxgridgen hxgridgen
/// @{
#ifndef TET_FACE_OCTREE_H
#define TET_FACE_OCTREE_H

#include <hxgridgen/HxGridGenWinDLLApi.h>

#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <mclib/McBitfield.h>
#include <hxfield/TetraGrid.h>
#include <mclib/McBox3f.h>
#include <mclib/McVec3f.h>

class HXGRIDGEN_API TetFaceOctree {

  public:
    
    TetFaceOctree(int maxDepth=6, int maxTriPerLeaf=50);

    ~TetFaceOctree();

    void insertAllTriangles(TetraGrid* grid, McVec3f* normals);

    void insertTriangle(int t);

    void insertNewTriangle(int t);

    void removeTriangle(int t);

    void getNearbyTriangles(int triangle, McDArray<int>& result);

    void lookupTriangles(const McBox3f &box, McDArray<int>& result);

    void cleanup();

    void info();

    float memSize();

    int getNumElements() const{ return allElements.size(); }

    int getMaxDepth() const { return maxDepth; }

    void setMaxDepth(int maxDepth) { this->maxDepth = maxDepth; }

    float getEps() const { return eps; }

    /// Find including surfaces for a given surface.
    void findIncludingSurfaces(McDArray<short> &markTriangles,
			       const int jSurf,
			       McDArray<signed char> &includingSurfaces);
    /// Determine which surfaces enclose each other.
    void findInclusions(McDArray<short> &markTriangles,
			const int nSurfaces,
			McDArray<signed char> &inclusionInfo);

  // protected:

    union Element {

	struct Node {
	    int negativeChildIndex;
	} node;

	struct Leaf {
	    int nTriangles;
	    int* triangles;
	} leaf;
    };

    McDArray<Element> allElements;

    // An element is a leaf if negativeChildIndex/nTriangles >= 0
    int isLeaf(int elem) {
	return (allElements[elem].node.negativeChildIndex >= 0);
    }

  protected:

    void insertTriangle(int elem, int depth, const McBox3f &elemBox, int t);

    void insertTriangle(Element::Leaf& leaf);

    void subdivide(int elem, const McBox3f &elemBox);

    void computeTriBox(int t, McBox3f &triBox);

    void computeTriBoxes();

    int intersectTriangle(const McBox3f &elemBox, int t)const;

    void computeEps();

    void lookupTriangle(int elem, McBox3f &elemBox,
	int t, McDArray<int>& result);

    void lookupTriangle(int elem, const McBox3f &elemBox,
	const McBox3f &box, McDArray<int>& result);

    int removeTriangle(int elem, McBox3f &elemBox, int t);

    // the following eight routines check whether a point is contained
    // in a particular octant in space, relative to 'center'

    int lowerLeftFront(float x, float y, float z, const McVec3f &center)const{
	return x<=center.x && y<=center.y && z<=center.z;
    };

    int lowerLeftBack(float x, float y, float z, const McVec3f &center)const{
	return x<=center.x && center.y<=y && z<=center.z;
    };

    int lowerRightFront(float x, float y, float z, const McVec3f &center)const{
	return center.x<=x && y<=center.y && z<=center.z;
    };

    int lowerRightBack(float x, float y, float z, const McVec3f &center)const{
	return center.x<=x && center.y<=y && z<=center.z;
    };

    int upperLeftFront(float x, float y, float z, const McVec3f &center)const{
	return x<=center.x && y<=center.y && center.z<=z;
    };

    int upperLeftBack(float x, float y, float z, const McVec3f &center)const{
	return x<=center.x && center.y<=y && center.z<=z;
    };

    int upperRightFront(float x, float y, float z, const McVec3f &center)const{
	return center.x<=x && y<=center.y && center.z<=z;
    };

    int upperRightBack(float x, float y, float z, const McVec3f &center)const{
	return center.x<=x && center.y<=y && center.z<=z;
    };

    float eps;
    int maxDepth;
    int maxTriPerLeaf;
    TetraGrid* grid;
    McVec3f* normals;
    McBox3f gridBox;
    McBitfield lookupFlags;
    McDArray<McBox3f> triBoxes;
};

#endif

/// @}

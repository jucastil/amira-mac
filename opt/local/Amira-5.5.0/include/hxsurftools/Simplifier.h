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
#ifndef SIMPLIFIER_H
#define SIMPLIFIER_H

#include <stdio.h>
#include <mclib/McFHeap.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <Inventor/SbLinear.h>
#include <hxsurface/Surface.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>

/** This class reduces the number of triangles of a surface. The
    simplification is achieved by collapsing short edges into points.
    With each collapse two triangles are removed (except for edges
    on boundary curves). */

class HXSURFTOOLS_API Simplifier {

  public:
    /// Constructor.
    Simplifier(Surface* surface = NULL);

    /// Destructor.
    ~Simplifier();

    /** Set the surface to be simplified. No surface information other
	than @c points, @c triangles, and @c patches is required. In fact, if
	the surface contains edges or contours, these data is deleted. */
    void setSurface(Surface* surface);

    /** Simplify the surface. Edges are collapsed repeatedly until no
        edge is found with an edge length smaller than @c minLength. */
    void simplify(float minLength);

  protected:
    // We use a new edge structure because we don't need the "triangles"
    // array of Surface::Edge
    struct Edge : public McFHeapElement {
	int to;
	int from;
	int nTriangles;
	float costs; // squared edge length
	int operator < (const Edge& other) { return costs < other.costs; }
    };

    Surface* surface;
    int nEdges;
    int nEdgesToBeRemoved;
    int nRemovedEdges;
    float minLength2;

    McDArray<int> surroundingPoints; 
    McDArray<int> aliasInfo;
    McBitfield pointFlag;
    McBitfield isBoundary;
    McFHeap<Edge> edgeHeap;
    McDArray<Edge> allEdges;
    McDArray<McSmallArray<int,8> > edgesPerPoint;

    void createAllEdges();
    void collapse(int e);
    void cleanUp();

    // Evaluate alias info array iteratively
    inline int getNewIdx(int i) {
	while (aliasInfo[i]>=0)
	    i = aliasInfo[i];
	return -aliasInfo[i]-1;
    }

    // Get squared length of given edge
    inline float getEdgeLength2(int edgeIdx) {
	Edge& e = allEdges[edgeIdx];
	return (surface->points[e.from]-surface->points[e.to]).length2();
    }

};

#endif

/// @}

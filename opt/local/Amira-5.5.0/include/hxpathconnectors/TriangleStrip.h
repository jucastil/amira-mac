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

/// @addtogroup hxpathconnectors hxpathconnectors
/// @{
#ifndef _TRIANGLE_STRIP_H_
#define _TRIANGLE_STRIP_H_

#include <mclib/McVec2f.h>
#include <mclib/McList.h>
#include <mclib/McDArray.h>
#include <mclib/McSmallArray.h>
#include <mclib/McHandle.h>

#include <hxsurface/Surface.h>
#include <hxpathconnectors/hxpathconnectorsAPI.h>

class SurfaceNode;
class TriangleStripData;

class HXPATHCONNECTORS_API TriangleStrip {

    // MC_HEADER(TriangleStrip);

public:

    class Edge;

    /// Class for storing boundary vertices of 2d polygon
    class Vertex : public McLink {
    public:
        /// Constructor
        Vertex() : v(-1) {}
        /// index into surface points
        int v;
        /// 2d coords
        McVec2f p;
        /// strip edges incident to vertex
        McSmallArray<Edge*,6> edges;
        /// Return side: undefined=-1, left=0, right=1
        inline int side() const;
    };

    /// Class for storing interior edges of 2d polygon
    class Edge : public McLink {
    public:
        /// Constructor
        Edge() : e(-1) { s[0] = s[1] = 0; }
        /// index into surface edges
        int e;
        /// index into strip vertices
        Vertex* s[2];
    };

    /// Constructor
    TriangleStrip(TriangleStripData* d) : data(d), sourceNode(0), targetNode(0) {}

    /// Destructor
    ~TriangleStrip();

    /// Initialize source node.
    void setSource(SurfaceNode* p) { sourceNode = p; }

    /// Initialize target node.
    void setTarget(SurfaceNode* p) { targetNode = p; }

    /// Initialize edge array with edge indices (new strip)
    void initEdges(const McDArray<int>& newEdges);

    /// Recompute strip
    bool recompute();

    /// Compute detour around given vertex on side @c s
    bool detour(Vertex* v);

    /** Compute shortest path from source to target.
        Algorithm by Lee, Preparata; Euclidean Shortest Paths
        in the Presence of Rectilinear Barriers;
        Networks vol 14 (1984), pp. 393-410. */
    void computeShortestPath( McDArray<Vertex*>& path );

    /// Returns length of path
    float getPathLength( const McDArray<Vertex*>& path ) const;

    /// Check whether detour is needed around path vertex
    bool needsDetour( const McDArray<Vertex*>& path, int i );

    /// Convert 2d path to surface path
    bool getSurfacePath( const McDArray<Vertex*>& path, McDArray<McHandle<SurfaceNode> >& intermediate ) const;

    /// For debugging
    void show( bool showTriangles3d=true, bool showTriangles2d=false, bool showPoly=false ) const;

    /// Print info
    void print() const;

    /// For debugging
    static void showPath(const McDArray<Vertex*>& path, const McDArray<Vertex*>* funnel);

private:

    /// 2d source coords
    Vertex source;

    /// 2d target coords
    Vertex target;

    /// Interior edges of strip
    McList<Edge> edges;

    /// Boundaries of 2d strip (left=0, right=1)
    McList<Vertex> side[2];

    /// Pointer to associated data object
    TriangleStripData* data;

    /// Source node
    SurfaceNode* sourceNode;

    /// Target node
    SurfaceNode* targetNode;

    /// Update existing strip by removing edges @c from to @c last, adding newEdges
    void updateEdges(Edge* first, Edge* last, const McSmallArray<int,6>& newEdges);

    /// Compute indices of new edges
    bool getNewEdges(Vertex* v, McSmallArray<int,6>& newEdges);

    /// Remove obsolete edges around source/target nodes
    void removeObsoleteEdges(SurfaceNode* node, McSmallArray<int,6>& newEdges);

    /// Isometric projection of 3d point onto plane
    static void project2D(const McVec2f& v1, const McVec2f& v2, float len12,
                          const McVec3f& p1, const McVec3f& p2, const McVec3f& p3,
                          McVec2f& v3);

    /// Check whether @c p lies on the left of line @c p1 -> @c p2
    static inline int getSide(const McVec2f& p1, const McVec2f& p2, const McVec2f& p);

    ///
    static bool intersection2d(const McVec2f& p1, const McVec2f& p2,
                               const McVec2f& q1, const McVec2f& q2,
                               float& lambda, float& mu);

    /// For debugging
    static void showLines(const McVec2f& p1, const McVec2f& p2, const McVec2f& q1, const McVec2f& q2);

    /// Helper function for show
    void collectTriangles( McDArray<Surface::Triangle>& triangles, McDArray<int>& origTris ) const;

    /// Helper function for show
    int findTouchingTriangle(SurfaceNode* node, int tri) const;

    /// Compute star neighbourhood at non-manifold point
    bool computeNonManifoldStar(int i, const McDArray<Vertex*>& path,
                                McSmallArray<int,6>& trianglesPerPoint,
                                McSmallArray<int,6>& edgesPerPoint);
};

//--------------------------------------------------------------------

inline int TriangleStrip::Vertex::side() const
{
    if ( !edges.size() )
        return -1;

    const Edge* e = edges[0];

    if ( e->s[0] == this )
        return 0;
    else if ( e->s[1] == this )
        return 1;
    else
        return -1;
}

//--------------------------------------------------------------------

inline int TriangleStrip::getSide(const McVec2f& p1, const McVec2f& p2, const McVec2f& p)
{
    // direction of line p1->p2
    McVec2f dp = p2-p1;

    // rotate dp by 90 degree anti-clockwise
    dp = McVec2f( -dp.y, dp.x );

    // compute projection of
    return ((p-p1).dot(dp) > 0) ? 0 : 1;
}

//--------------------------------------------------------------------

#endif

/// @}

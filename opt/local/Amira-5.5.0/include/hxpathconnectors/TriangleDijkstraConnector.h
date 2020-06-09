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
#ifndef _TriangleDijkstraConnector_H
#define _TriangleDijkstraConnector_H

#include <hxsurfacepath/PathConnector.h>
#include <hxsurfacepath/SurfaceNode.h>
#include <hxsurfacepath/SurfaceTriangleNode.h>
#include <hxsurfacepath/SurfaceEdgeNode.h>

#include <hxpathconnectors/hxpathconnectorsAPI.h>
#include <hxpathconnectors/TriangleStripData.h>

#include <mclib/McFHeap.h>

class Surface;
class McBitfield;

class HXPATHCONNECTORS_API TriangleDijkstraConnector : public PathConnector
{

    MC_HEADER(TriangleDijkstraConnector);

public:
    /// Default constructor
    TriangleDijkstraConnector();

    /// Destructor
    ~TriangleDijkstraConnector();

    /// Initialize computation
    virtual void init(Surface* surface, McProgressInterface* progress = 0);

    /// Compute intermediate nodes between startNode and endNode
    virtual bool computeConnection(SurfaceNode* startNode,
                                   SurfaceNode* endNode,
                                   McDArray<McHandle<SurfaceNode> >& intermediate,
                                   McProgressInterface* progress = 0);



    /// Class for the computation of shortest triangle strip.
    class ShortestTriangleStrip : public McFHeapElement {
    public:
        /// Constructor
        ShortestTriangleStrip()
        {
            triangle=-1;
            neighbour=-1;
            edge=-1;
            distance=-1;
            nTris=-1;
            inlist=false;
        }
        /// current triangle
        int triangle;
        /// next triangle on the way to the source
        int neighbour;
        /// next edge on the way to the source
        int edge;
        /// distance to source
        float distance;
        /// number of triangles to source
        int nTris;
        /// temporary variable for heap generation
        bool inlist;
        /// Distance comparison
        int operator <(const ShortestTriangleStrip& other) {
            return distance < other.distance;
        }
    };

private:

    /// Pointer to data required by TriangleStrip
    TriangleStripData* mData;

public:

    /** Compute the shortest @c triangle strip (in terms of getTriangleDistance)
        from @c startNode to @c endNode. */
    static bool getTriangleStrip( SurfaceNode* startNode, SurfaceNode* endNode, TriangleStripData* data,
                                  McDArray<int>& triangles, McDArray<int>& edges,
                                  McDArray<ShortestTriangleStrip>& shortestStrip,
                                  McBitfield* allowedTris=0, McBitfield* allowedEdges=0,
                                  bool cleanObsoleteTriAndEge = true );

    /// Compute distance between triangles
    static float getTriangleDistance(int t1, int t2, int e, TriangleStripData* data);

    /// Alternativ to getTriangleDistance
    inline static float getTriangleDistance2(int t1, int t2, int e, TriangleStripData* data)
    {
        float u = 1./3.;

        SurfaceTriangleNode p1(u, u, t1, data->surface);
        SurfaceTriangleNode p2(u, u, t2, data->surface);
        SurfaceEdgeNode edgeNode(0.5, e, data->surface);

        McVec3f edgePoint = edgeNode.point();

        float d1 = ( p1.point() - edgePoint ).length2();
        float d2 = ( p2.point() - edgePoint ).length2();
        return d1+d2;
    }
};

#endif

/// @}

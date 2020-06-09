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
#ifndef _GeodesicTraceBack_H
#define _GeodesicTraceBack_H

#include <hxpathconnectors/EdgeWindow.h>
#include <hxsurfacepath/SurfaceNode.h>

#include <mclib/McHandle.h>

/** Helper class for GeodesicConnector.  It computes the shortest
    geodesic with the help of a distance map.  For further information
    see "Fast approximate and exact geodesics on meshes", Hoppe et
    al., SIGGRAPH 2005.
 */
class GeodesicTraceBack {

public:

    /// Constructor.
    GeodesicTraceBack(GeodesicConnector* connector, SurfaceNode* startNode,
                      McDArray< McDArray<McHandle<EdgeWindow> > >& windowsPerEdge);

    /// Trace back from endNode to startNode
    bool compute(SurfaceNode* endNode, McDArray<McHandle<SurfaceNode> >& intermediate);

protected:

    /// Distance map
    McDArray< McDArray<McHandle<EdgeWindow> > >& windowsPerEdge;

    /// Start node
    SurfaceNode* startNode;

    /// Pointer to surface
    Surface* surface;

    /// Pointer to connector
    GeodesicConnector* connector;

    int v[3];
    int adj[2];
    McVec2f p2d[3];
    McVec2f wp2d;

    /// represents a traced point on an EdgeWindow
    struct PointOnWindow
    {
        /// constructor
        PointOnWindow() : window(0), lambda(-1) {}

        /// another constructor
        PointOnWindow(EdgeWindow* w, const float& l) : window(w), lambda(l) {}

        /// the @c EdgeWindow the point lies on
        EdgeWindow* window;

        /// the barycentric coordinate of this point. 3d-coordinate is
        /// lambda*(from-node of edge)+(1-lambda)*(to-node of edge)
        float lambda;
    };

    /// finds the window from which we start the trace
    PointOnWindow findInitialWindow(SurfaceNode* endNode);

    /// Return the next point on the window from @c pointOnWindow.  If
    /// the source node was found an empty PointOnWindow() is returned.
    PointOnWindow getNextPointOnWindow(const GeodesicTraceBack::PointOnWindow& pointOnWindow);

    /// Set up the coordinate system given by the two points
    /// specifying the window edge and the opposite point.
    void setupCoordSystem(const GeodesicTraceBack::PointOnWindow& pointOnWindow);

    /// Similar to @c getNextPointOnWindow(), but for the case in
    /// which we start from a vertex.
    PointOnWindow getNextPointFromVertex(const GeodesicTraceBack::PointOnWindow& pointOnWindow);

    /// Create and return a surface node that lies on the @c pow window.
    SurfaceNode* createSurfaceNode(GeodesicTraceBack::PointOnWindow pow,Surface* surface);
};

#endif

/// @}

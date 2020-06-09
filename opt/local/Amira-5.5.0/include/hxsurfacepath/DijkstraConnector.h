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

/// @addtogroup hxsurfacepath hxsurfacepath
/// @{
#ifndef DIJKSTRA_CONNECTOR_H
#define DIJKSTRA_CONNECTOR_H

#include "PathConnector.h"
#include "SurfaceNode.h"
#include "hxsurfacepathAPI.h"

class HxSurface;
class McBitfield;

/** This class implements a path connector that connects two nodes on
    the surface in a Dijkstra-like fashion, that is, it finds the
    shortest path that only lies on vertices of the surface.
*/
class HXSURFACEPATH_API DijkstraConnector : public PathConnector {
    
    MC_HEADER(DijkstraConnector);

public:

    /// Default constructor.
    DijkstraConnector() : mSurface(0), mAllowedPoints(0) {}

    /// Initializes computation.
    virtual void init(Surface* surface, McProgressInterface* progress = 0);

    /// Computes intermediate nodes between @c startNode and @c endNode.
    virtual bool computeConnection(SurfaceNode* startNode, 
                                   SurfaceNode* endNode, 
                                   McDArray<McHandle<SurfaceNode> >& intermediate,
                                   McProgressInterface* progress = 0);

    /// Calculates path from @c startNode to @c endNode and return its
    /// length.
    static float calculateEuclideanPathLength(SurfaceNode* startNode, 
                                              SurfaceNode* endNode, 
                                              McDArray<int> intermediate);

    /// Sets pointer to allowed surface vertices.
    void setAllowedPoints(McBitfield* allowed)
    {
        mAllowedPoints = allowed;
    }
    
private:
    
    /// Reference to surface on which the connector operates.
    Surface* mSurface;

    /// Surface edge lengths
    McDArray<float> mEdgeLengths;

    /// Optional container for edge weights
    McDArray<float> mEdgeWeights;

    /// Reference to bitfield containing points that can be added to
    /// the path between two nodes.
    McBitfield* mAllowedPoints;

    /// Returns pointer to weight field for shortest-path computation
    virtual float* setWeightField();

    /// Helper function
    void getNeighVertices(SurfaceNode* node, McDArray<int>& vertices) const;
};

#endif // DIJKSTRA_CONNECTOR_H

/// @}

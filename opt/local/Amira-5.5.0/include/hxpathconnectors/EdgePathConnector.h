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
#ifndef _EdgePathConnector_H
#define _EdgePathConnector_H

#include <hxpathconnectors/hxpathconnectorsAPI.h>

#include <hxsurfacepath/PathConnector.h>
#include <hxsurfacepath/SurfaceNode.h>
#include <mclib/McBitfield.h>

class Surface;

class HXPATHCONNECTORS_API EdgePathConnector : public PathConnector
{

    MC_ABSTRACT_HEADER(EdgePathConnector);

  public:

    /// Default constructor
    EdgePathConnector() : surface(0) {}

    /// Initialize computation
    virtual void init(Surface* surface, McProgressInterface* progress = 0);

    /// Compute intermediate nodes between startNode and endNode
    virtual bool computeConnection(SurfaceNode* startNode,
                                   SurfaceNode* endNode,
                                   McDArray<McHandle<SurfaceNode> >& intermediate,
                                   McProgressInterface* progress = 0);

    /// Sets pointer to allowed surface vertices.
    void setAllowedPoints(McBitfield* allowed)
    {
        mExtAllowedPoints = allowed;
    }

  protected:

    /// Get information if edge is allowed
    virtual bool isAllowedEdge(int e) = 0;

    /// Pointer to surface
    Surface* surface;

    /// Holds edge weights
    McDArray<float> edgeWeights;

    /// Marks all allowed vertices
    McBitfield mIsAllowedVertex;

    /// Marks all allowed edges
    McBitfield mIsAllowedEdge;

    /// Reference to bitfield containing points that can be added to
    /// the path between two nodes.
    McBitfield* mExtAllowedPoints;

    /// Calculate path from @c startNode to @c endNode via
    /// @c intermediate nodes.
    float calculatePathLength(SurfaceNode* startNode,
                              SurfaceNode* endNode,
                              McDArray<int> intermediate);
};
#endif

/// @}

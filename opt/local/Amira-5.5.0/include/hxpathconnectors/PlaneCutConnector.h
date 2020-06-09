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
#ifndef _PLANE_CUT_CONNECTOR_H_
#define _PLANE_CUT_CONNECTOR_H_

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <hxlines/HxLineSet.h>

#include <hxsurface/HxSurface.h>
#include <hxsurfacepath/PathConnector.h>
#include <hxpathconnectors/hxpathconnectorsAPI.h>

class SurfaceNode;

/** Class for connecting two points on a surface with a
    path that results from a cut of the surface with a
    plane whose normal is perpendicular to the average of the
    normals at both given nodes. */

class HXPATHCONNECTORS_API PlaneCutConnector : public PathConnector {

    MC_HEADER(PlaneCutConnector);

public:

    /// Default constructor
    PlaneCutConnector() : surface(0) {
        setDebug(false);
    }

    /// Initialize computation
    virtual void init(Surface* surface, McProgressInterface* progress = 0);

    /// Compute intermediate nodes between startNode and endNode
    virtual bool computeConnection(SurfaceNode* startNode,
                                   SurfaceNode* endNode,
                                   McDArray<McHandle<SurfaceNode> >& intermediate,
                                   McProgressInterface* progress = 0);

    void setDebug(bool value){debug=value;};

    // Flag used for debugging.
    bool debug;

protected:

    /// Pointer to surface on which path is computed.
    Surface* surface;

    /// defines the orientation of the plane through start/end node via a third point
    virtual bool setPlaneOrientation(SurfaceNode* startNode, SurfaceNode* endNode, McVec3f& thirdPoint);

private:

    /// Computes points and triangles these points lie on, that build
    /// a path between @c startNode and @c endNode.
    int connect(SurfaceNode* startNode , SurfaceNode* endNode , McDArray<McHandle<SurfaceNode> >&intermediate);

    /// Concatenate connected lines.
    int mergeConnectedLines( McDArray<McDArray<McHandle<SurfaceNode> > > & nodes);
    
    /** Writes the points and triangleIDs between startNode and
        EndNode of the line in the arrays triangles and points.
        @c theNodes is the considered line created by intersecting the
        plane with the surface. */
    bool findPointsInbetween(McDArray<McHandle<SurfaceNode> >theNodes  , SurfaceNode* startNode, SurfaceNode* endNode,McDArray<McHandle<SurfaceNode> > & intermediate );

    /// Calculate length of the path given by @points.
    double calculateLength(McDArray<McHandle<SurfaceNode> > points);

    /// Create a line set from @c points.
    HxLineSet* createLineset(McDArray<McDArray<McVec3f> > points);

    /// Create surface nodes, @c pathNodes, from @c thePoints and @c
    /// theTriangles.
    void createSurfaceNodes(    McDArray< McDArray<McHandle<SurfaceNode> > >&pathNodes,     McDArray< McDArray<McVec3f > >&thePoints, McDArray<McDArray<int> >theTriangles);
};

#endif

/// @}

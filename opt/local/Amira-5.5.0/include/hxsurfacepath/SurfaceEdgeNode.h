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
#ifndef SURFACE_EDGE_NODE_H
#define SURFACE_EDGE_NODE_H

#include "hxsurfacepathAPI.h"
#include "SurfaceNode.h"
#include <hxsurface/Surface.h>

/** SurfaceNode for points in triangles */
class HXSURFACEPATH_API SurfaceEdgeNode : public SurfaceNode {

    MC_ABSTRACT_HEADER(SurfaceEdgeNode);

public:

    /// Default constructor.
    SurfaceEdgeNode(Surface* surface = NULL);

    /// Constructor.
    SurfaceEdgeNode(float u, int edge, Surface* surface = NULL);
    
    /// Destructor.
    ~SurfaceEdgeNode() {}

    // ------------------ operators ------------------ 

    /// Equality operator.
    bool operator==( const SurfaceNode& node) const;

    /// Assignment operator.
    SurfaceNode& operator=( const SurfaceNode& other );

    // ------------------ functions ------------------ 

    /// Sets the relative position @c u of the node on @c edge; from
    /// this information the bary-centric coordinates can be computed.
    void set(const float u, int edge);

    /** Computes and save bary-centric coords for surface node, given
        by @c point, w.r.t. to triangle @c triIdx.

        This function computes and stores only the relative position
        on one of the edges of triangle @c triIdx.  The triangle index
        is not stored, but the edge index and the relative position.
        This is a single scalar value.
    */
    void setBary(const McVec3f& point, int triIdx);
	
    /// Returns the bary-centric values of this node.
    McVec3f getBary() const 
    {
        return McVec3f( value, 1-value, 0 );
    }

    /// Returns the bary-centric coords of this node w.r.t. to
    /// triangle @c triIdx.
    bool getAbsBary(int triIdx, McVec3f& bary) const;

    /// Returns the 3d coords of this node.
    McVec3f point() const;

    /// Prints some info about surface node.
    void info() const;

    /// Returns one touching triangle.
    int touchingTriangle() const;

    /// Returns all touching triangles.
    void touchingTriangles(McSmallArray<int,6>& trngls) const;

    /// Returns all touching triangles which have the materialId.
    void touchingTrianglesWithMaterial(McSmallArray<int,6>& trngls, int materialId) const;

    /// Returns all touching triangles which have materialId. 
    /// In case of the material is the outer one, the triangle is inverted so that all triangles are consistent.
    void touchingTrianglesWithMaterial(McSmallArray< Surface::Triangle,6 >& trngls, int materialId) const;

    /// Returns all touching edges.
    void touchingEdges(McSmallArray<int,6>& edges) const;

    /// Returns the edgeID of the point.
    int edge() const { return edgeID; }

    /// Duplicate the current node.
    virtual SurfaceNode* duplicate() const;

    /** For a general description see SurfaceNode::unfoldNeighbourhood.

        This overloaded function simply maps the two triangles
        adjacent to the edge on which the node resides to the plane.
    */
    void unfoldNeighbourhood(McDArray<int>& points,
                             McDArray<McVec2f>& coords2d,
                             McVec2f& center2d);

    /** for a general description see SurfaceNode::unfoldNeighbourhood

        This overloaded function simply maps the two triangles of a specific material
        adjacent to the edge on which the node resides to the plane.
    */
    void unfoldNeighbourhood(McDArray<int>& points,
                             McDArray<McVec2f>& coords2d,
                             McVec2f& center2d,
                             int materialId);
    
    // -------------------- data --------------------

    /// Value on edge (0..1).
    float value;

    /// Index of the edge on which the node resides.
    int edgeID;

protected:

    void unfold(McDArray<int>& points, 
                McDArray<McVec2f>& coords2d,
                McVec2f& center2d,
                int* other );
};

#endif // SURFACE_EDGE_NODE_H

/// @}

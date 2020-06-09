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
#ifndef SURFACE_VERTEX_NODE_H
#define SURFACE_VERTEX_NODE_H

#include "hxsurfacepathAPI.h"
#include "SurfaceNode.h"

/** This class implements a SurfaceNode given on a vertex of
    the surface.
*/
class HXSURFACEPATH_API SurfaceVertexNode : public SurfaceNode
{

    MC_ABSTRACT_HEADER(SurfaceVertexNode);

public:

    /// default constructor
    SurfaceVertexNode(Surface* surface = NULL);

    /// constructor
    SurfaceVertexNode(int vertex, Surface* surface = NULL);
    
    /// destructor
    ~SurfaceVertexNode() {};

    // ------------------ operators ------------------ 

    /// equality operator
    bool operator==( const SurfaceNode& other ) const;

    /// assignment operator
    SurfaceNode& operator=( const SurfaceNode& other );

    // ------------------ functions ------------------ 

    /** for a general description see SurfaceNode::setBary

        This overloaded function identifies the vertex closest 
        to @c point.
    */
    void setBary(const McVec3f& point, int triIdx);

    /// return the barycentric coords of this node
    McVec3f getBary() const { return McVec3f(1,0,0); }

    /// return the barycentric coords of this node w.r.t. to
    /// triangle @c triIdx
    bool getAbsBary(int triIdx, McVec3f& bary) const;

    /// return the 3d coords of this node
    McVec3f point() const;

    /// print some info about surface node
    void info() const;

    /// return one touching triangle
    int touchingTriangle() const;

    /// return all touching triangles
    void touchingTriangles(McSmallArray<int,6>& trngls) const;

     /// return all touching triangles which have the materialId.
    void touchingTrianglesWithMaterial(McSmallArray<int,6>& trngls, int materialId) const;

    /// return all touching edges
    void touchingEdges(McSmallArray<int,6>& edges) const;

    /// return vertex index of the node if node is a surface point,
    /// -1 otherwise
    int vertex() const { return vertexID; }

    /// duplicate the current node
    virtual SurfaceNode* duplicate() const;

    /** for a general description see SurfaceNode::unfoldNeighbourhood

        This overloaded function unfolds the vertex star, i.e. the
        discrete geodesic polar map.
    */
    void unfoldNeighbourhood(McDArray<int>& points, McDArray<McVec2f>& coords2d, McVec2f& center2d);

    /** for a general description see SurfaceNode::unfoldNeighbourhood

        This overloaded function unfolds the vertex star of a specific material, i.e. the
        discrete geodesic polar map.
    */
    void unfoldNeighbourhood(McDArray<int>& points, McDArray<McVec2f>& coords2d, McVec2f& center2d, int materialId);

    // -------------------- data --------------------

    /// the surface vertex index of the node
    int vertexID;
};

#endif // SURFACE_VERTEX_NODE_H

/// @}

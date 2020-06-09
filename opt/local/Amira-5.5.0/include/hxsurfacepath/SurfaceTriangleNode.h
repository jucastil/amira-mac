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
#ifndef SURFACE_TRIANGLE_NODE_H
#define SURFACE_TRIANGLE_NODE_H

#include "hxsurfacepathAPI.h"
#include "SurfaceNode.h"

/** This class implements a SurfaceNode given on a triangle of the
    surface.
*/
class HXSURFACEPATH_API SurfaceTriangleNode : public SurfaceNode
{

    MC_ABSTRACT_HEADER(SurfaceTriangleNode);

public:

    /// constructor
    SurfaceTriangleNode(Surface* surface = NULL);

    /// constructor
    SurfaceTriangleNode(float u, float v, int triangle,
                        Surface* surface = NULL);
    
    /// destructor
    ~SurfaceTriangleNode() {};

    // ------------------ operators ------------------ 

    /// equality operator
    bool operator==(const SurfaceNode& node) const;

    /// assignment operator.
    SurfaceNode& operator=( const SurfaceNode& other );

    // ------------------ functions ------------------

    /// set the bary-centric coordinates and the triangle index; in
    /// contrast to setBary(..), the bary-centric coordinates are not
    /// computed but handed over
    void set(const McVec3f& bary, int triIdx);

    /// compute and save bary-centric coords for surface node, given
    /// by @c point, w.r.t. to triangle @c triIdx
    void setBary(const McVec3f& point, int triIdx);

    /// return the bary-centric coords of this node
    McVec3f getBary() const
    {
        return McVec3f( values[0], values[1], 1-values[0]-values[1]);
    }

    /// return the bary-centric coords of this node w.r.t. to
    /// triangle @c triIdx
    bool getAbsBary(int triIdx, McVec3f& bary) const
    {
        if ( !touches(triIdx) )
            return false;
        
        bary = getBary();
        return true;
    }
    
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

    /// return triangle index of the node if node lies inside a
    /// triangle, -1 otherwise
    int triangle() const { return trnglID; }

    /// duplicate the current node
    virtual SurfaceNode* duplicate() const;

    /** for a general description see SurfaceNode::unfoldNeighbourhood

        This overloaded function simply maps the triangle in which the
        node resides into the plane.
    */
    void unfoldNeighbourhood(McDArray<int>& points,
                             McDArray<McVec2f>& coords2d,
                             McVec2f& center2d);

    /** for a general description see SurfaceNode::unfoldNeighbourhood

        This overloaded function simply maps the triangle in which the
        node resides into the plane.
        Depending on whether material is choosen the coords2d are orientated.
    */
    void unfoldNeighbourhood(McDArray<int>& points, McDArray<McVec2f>& coords2d, McVec2f& center2d, int materialId);

    // -------------------- data --------------------

    /// bary-centric coordinates; 2 values are stored, the third value
    /// can be computed from the other two, hence it is redundant
    float values[2];

    /// the triangle of the point
    int trnglID;
};

#endif // SURFACE_TRIANGLE_NODE_H

/// @}

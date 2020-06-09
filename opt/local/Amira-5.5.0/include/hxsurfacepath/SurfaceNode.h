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
#ifndef _SURFACE_NODE_H_
#define _SURFACE_NODE_H_

#include "hxsurfacepathAPI.h"

#include <mclib/McHandable.h>
#include <mclib/McTypedObject.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec2f.h>
#include <mclib/McSmallArray.h>

class Surface;

/** This class is an abstract class for points that are implicitly
    defined on triangle meshes.
 */
class HXSURFACEPATH_API SurfaceNode : public McTypedObject, public McHandable {

    MC_ABSTRACT_HEADER(SurfaceNode);

public:

    /// Destructor.
    virtual ~SurfaceNode() { surface = NULL; }

    // ------------------ operators ------------------ 

    /// Equality operator, checks for equality of values, no tolerance allowed.
    virtual bool operator==( const SurfaceNode& other ) const = 0;

    /// Inequality operator.
    int operator!=( const SurfaceNode& other ) const { return !(*this==other); }

    /// Assignment operator.
    virtual SurfaceNode& operator=( const SurfaceNode& other );

    // ------------------ functions ------------------ 

    /** Computes the bary-centric coordinates w.r.t. the triangle
        @c triIdx and initialize node according to the bary-centric
        coordinates.  Furthermore, the function stores the
        bary-centric coordinates.
    */
    virtual void setBary(const McVec3f& point, int triIdx) = 0;
    
    /// Returns the barycentric coords of this node.
    virtual McVec3f getBary() const = 0;

    /// Returns the barycentric coords of this node w.r.t. to
    /// triangle @c triIdx
    virtual bool getAbsBary(int triIdx, McVec3f& bary) const = 0;

    /// Returns the 3d coords of this node.
    virtual McVec3f point() const = 0;

    /// Returns all touching triangles.
    virtual void touchingTriangles(McSmallArray<int,6>& trngls) const = 0;

    /// Returns all touching triangles which have the materialId.
    virtual void touchingTrianglesWithMaterial(McSmallArray<int,6>& trngls, int materialId) const = 0;

    /// Returns all touching edges.
    virtual void touchingEdges(McSmallArray<int,6>& edges) const = 0;

    /// Prints some info about surface node.
    virtual void info() const;

    /// Returns one touching triangle.
    virtual int touchingTriangle() const { return -1; }

    /// Returns true if node touches triangle @c triIdx.
    virtual bool touches(int triIdx) const;

    /// Returns triangle index of the node if node lies inside a
    /// triangle, -1 otherwise.
    virtual int triangle() const { return -1; }

    /// Returns edge index of the node if node is on edge, -1 otherwise.
    virtual int edge() const { return -1; }

    /// Returns vertex index of the node if node is a surface point,
    /// -1 otherwise.
    virtual int vertex() const { return -1; }

    /// Returns triangle index of common touching triangle
    /// if one exists, -1 otherwise.
    virtual int isConsistentTo( const SurfaceNode* other ) const;

    /// Returns edge index of common touching edge if one exists,
    /// -1 otherwise.
    virtual int shareSameEdge( const SurfaceNode* other ) const;

    /// Duplicates the current node.
    virtual SurfaceNode* duplicate() const = 0;

    /** Computes local neighbourhood and map it to the plane.

        \param[out] points   contains the indices of the surface points
                             in the local neighborhood;  this list is empty 
                             if pathnode is in non-manifold location
        \param[out] coords2d 2d coordinates corresponding to @c points
        \param[out] center2d center of neighborhood in 2d
    */
    virtual void unfoldNeighbourhood(McDArray<int>& points,
                                     McDArray<McVec2f>& coords2d,
                                     McVec2f& center2d) = 0;

    /** Computes local neighbourhood and map it to the plane.

        \param[out] points   contains the indices of the surface points
                             in the local neighborhood;  this list is empty 
                             if pathnode is in non-manifold location
        \param[out] coords2d 2d coordinates corresponding to @c points
        \param[out] center2d center of neighborhood in 2d
        \param[out] materialId only unfold the triangles with a specific materialId
    */
    virtual void unfoldNeighbourhood(McDArray<int>& points,
                                     McDArray<McVec2f>& coords2d,
                                     McVec2f& center2d,
                                     int materialId) = 0;

    /// Returns normal vector on surface at surface node.
    virtual void getNormal(McVec3f& normal) const;

    /// Computes and return the barycentric coordinates of @c point
    /// w.r.t. triangle @c triIdx.
    static McVec3f computeBarycentric(Surface* surface,
                                      const McVec3f& point,
                                      int triIdx);

    // -------------------- data --------------------

    /// Surface the surface node is defined on.
    Surface* surface;

    /// Special flag.
    bool isControlPoint;

protected:

    /// Constructor protected (only node factory allowed to call it).
    SurfaceNode( Surface* s ) : surface(s), isControlPoint(false) {}
};

#endif // _SURFACE_NODE_H_

/// @}

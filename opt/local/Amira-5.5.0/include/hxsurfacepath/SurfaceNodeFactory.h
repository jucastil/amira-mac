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
#ifndef _SURFACE_NODE_FACTORY_H_
#define _SURFACE_NODE_FACTORY_H_

#include "hxsurfacepathAPI.h"
#include "SurfaceNode.h"
#include <mclib/McVec3f.h>
#include <mclib/McVec3f.h>
#include <mclib/McHandle.h>

class Surface;
class SurfaceVertexNode;
class SurfaceEdgeNode;
class SurfaceTriangleNode;

/** Class for creating, comparing, type-checking and converting
    surface nodes. */
class HXSURFACEPATH_API SurfaceNodeFactory
{

public:

    /// Path node types (0=vertex, 1=edge, 2=triangle).
    enum { VERTEX_NODE=0, EDGE_NODE, TRIANGLE_NODE };

    /// Tolerance mode types (0=none, 1=barycentric, 2=world).
    enum { NO_TOL=0, BARY_TOL, WORLD_TOL };

    /// Constructor.
    SurfaceNodeFactory(Surface* surface) : 
          mSurface(surface)
        , mMode(NO_TOL)
        , mTol(0.)
        , mPrevMode(NO_TOL)
        , mPrevTol(0.)
    {}

    /// Changes surface pointer.
    void setSurface(Surface* surface) { mSurface = surface; }

    /// Changes surface pointer.
    Surface* getSurface() const { return mSurface; }

    /// Sets tolerance for autonomous node selection (remember previous
    /// values).
    void setTolerance(unsigned char mode, float tol)
    {
        mPrevMode = mMode;
        mPrevTol = mTol;
        mMode = mode;
        mTol = tol;
    }

    /// Resets tolerance to previous values.
    void resetTolerance()
    {
        mMode = mPrevMode;
        mTol = mPrevTol;
    }

    /// Checks type.
    static int isVertexNode(const SurfaceNode* node);

    /// Checks type.
    static int isEdgeNode(const SurfaceNode* node);

    /// Checks type.
    static int isTriangleNode(const SurfaceNode* node);

    /// Gets node type.
    static int getNodeType(const SurfaceNode* node);

    /// Checks equality of two surface nodes using the given tolerance.
    bool isEqual(SurfaceNode* node1, SurfaceNode* node2);

    /// Creates node by type id (0="Vertex", 1="Edge" or 2="Triangle").
    SurfaceNode* createNode(int id, int triangle, const McVec3f& point);

    /// Creates node by type name ("Vertex", "Edge" or "Triangle").
    SurfaceNode* createNode(const char* label, int triangle, const McVec3f& point);

    /// Creates surface node from 3D coordinates (if mMode!=0, node may
    /// be converted).
    SurfaceNode* createNode(int triangle, const McVec3f& point);

    /// Creates vertex node.
    SurfaceNode* createVertexNode(int vertex);

    /// Creates edge node.
    SurfaceNode* createEdgeNode(int edge, float val);

    /// Creates triangle node.
    SurfaceNode* createTriangleNode(int triangle, float u, float v);

    /** Converts node according to given tolerance.  If no conversion
        is performed, output==input node, otherwise a new surface node
        is created. */
    SurfaceNode* convertNode( SurfaceNode* node );

    /// Convert a set of nodes.
    int convertNodes(McDArray< McHandle<SurfaceNode> >& nodes);

protected:

    /// Surface.
    Surface* mSurface;

    /// Tolerance mode.
    unsigned char mMode;

    /// Tolerancee.
    float mTol;

    /// Previous mode.
    unsigned char mPrevMode;

    /// Previous tolerance.
    float mPrevTol;

    /// Tries to convert a SurfaceEdgeNode.
    SurfaceNode* convertSurfaceEdgeNode(SurfaceEdgeNode* node);

    /// Tries to convert a SurfaceTriangleNode.
    SurfaceNode* convertSurfaceTriangleNode(SurfaceTriangleNode* node);

    /// Checks, whether a SurfaceEdgeNode can be converted.  If it can,
    /// the function returns the vertex for VertexPathNode.
    int canConvertEdgeNode(SurfaceEdgeNode* node);

    /// Helper function.
    static inline float shortestDistanceFromPointToEdge(const McVec3f& point,
                                                        const McVec3f& v1,
                                                        const McVec3f& v2)
    {
        McVec3f edge = (v1-v2);
        McVec3f p = (point-v2);
        edge.normalize();
        return fabs(edge.dot(p));
    }
};

#endif // _SURFACE_NODE_FACTORY_H_

/// @}

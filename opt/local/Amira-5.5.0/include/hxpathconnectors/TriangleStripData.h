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
#ifndef _TRIANGLE_STRIP_DATA_H_
#define _TRIANGLE_STRIP_DATA_H_

#include <hxpathconnectors/TriangleStrip.h>
#include <hxpathconnectors/hxpathconnectorsAPI.h>

class Surface;

class HXPATHCONNECTORS_API TriangleStripData : public McHandable {

    //MC_HEADER(TriangleStripData);

public:

    /// Constructor
    TriangleStripData();

    /// Destructor
    ~TriangleStripData();

    /// Initialize data
    void init(Surface* surface);

    /// Some heuristics to check whether data is initialized correctly
    bool isInitCorrect();

    /// Return new strip edge, if possible from unusedEdges
    inline TriangleStrip::Edge* getEdge();

    /// Return new strip vertex, if possible from unusedVertices
    inline TriangleStrip::Vertex* getVertex();

    /// Return new strip edge, if possible from unusedEdges
    inline void addEdge(TriangleStrip::Edge* edge);

    /// Return new strip vertex, if possible from unusedVertices
    inline void addVertex(TriangleStrip::Vertex* vertex);

    /// Compute total angle around 3D star
    float getAngleStar(int v, const McSmallArray<int,6>& trianglesPerPoint);

    /// Returns common edge of triangles t1 and t2, -1 if there exists none
    static int commonEdge(Surface* surface, int t1, int t2);

    /// Helper function
    void createContours();

    // ------------------ Data members ------------------

    /// Pointer to surface
    Surface* surface;

    /// Edge lengths of surface
    McDArray<float> edgeLength;

    /// Angles per triangle
    McDArray< McSmallArray<float,3> > angles;

    /// Sorted edges around surface vertices (manifolds only)
    McDArray< McSmallArray<int,6> > edgesPerPoint;

    /// Pointer to allowed triangles
    McBitfield* mAllowedTriangles;

    /// Pointer to allowed edges
    McBitfield* mAllowedEdges;

    /// Pointer to forbidden vertices
    McBitfield* mForbiddenVertices;

    /** Discriminate vertices as
        - manifold,
        - boundary,
        - non-manifold */
    enum { MANIFOLD=0, BOUNDARY, NON_MANIFOLD };

    /// Vertex types
    McDArray<unsigned char> pointType;

protected:

    /// Unused strip edges
    McList<TriangleStrip::Edge> unusedEdges;

    /// Unused strip vertices
    McList<TriangleStrip::Vertex> unusedVertices;
};

//--------------------------------------------------------------------

inline TriangleStrip::Edge* TriangleStripData::getEdge()
{
    if ( unusedEdges.last()!=0 )
    {
        TriangleStrip::Edge* e = unusedEdges.Pop();
        e->e = -1;
        e->s[0] = e->s[1] = 0;
        e->_pre = e->_suc = 0;
        return e;
    }
    else
        return new TriangleStrip::Edge;
}

//--------------------------------------------------------------------

inline TriangleStrip::Vertex* TriangleStripData::getVertex()
{
    if ( unusedVertices.last()!=0 )
    {
        TriangleStrip::Vertex* v = unusedVertices.Pop();
        v->v = -1;
        v->p = McVec2f(0);
        v->edges.resize(0);
        v->_pre = v->_suc = 0;
        return v;
    }
    else
        return new TriangleStrip::Vertex;
}

//--------------------------------------------------------------------

inline void TriangleStripData::addEdge(TriangleStrip::Edge* edge)
{
    edge->_pre = 0;
    edge->_suc = 0;
    unusedEdges.append( edge );
}

//--------------------------------------------------------------------

inline void TriangleStripData::addVertex(TriangleStrip::Vertex* vertex)
{
    vertex->_pre = 0;
    vertex->_suc = 0;
    unusedVertices.append( vertex );
}

#endif

/// @}

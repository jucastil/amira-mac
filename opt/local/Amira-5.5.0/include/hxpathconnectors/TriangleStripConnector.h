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
#ifndef _TriangleStripConnector_H
#define _TriangleStripConnector_H

#include <hxsurfacepath/PathConnector.h>
#include <hxsurfacepath/SurfaceNode.h>
#include <hxpathconnectors/hxpathconnectorsAPI.h>
#include <hxpathconnectors/TriangleDijkstraConnector.h>

#include <mclib/McFHeap.h>

class Surface;
class TriangleStripData;
class McBitfield;

class HXPATHCONNECTORS_API TriangleStripConnector : public PathConnector
{

    MC_HEADER(TriangleStripConnector);

public:
    /// Default constructor
    TriangleStripConnector();


    /// Destructor
    ~TriangleStripConnector();

    /// Initialize computation
    virtual void init(Surface* surface, McProgressInterface* progress = 0);

    /// Compute intermediate nodes between startNode and endNode
    virtual bool computeConnection(SurfaceNode* startNode,
                                   SurfaceNode* endNode,
                                   McDArray<McHandle<SurfaceNode> >& intermediate,
                                   McProgressInterface* progress = 0);

    /// Computes triangle strip around given surface path
    static bool collectTrianglesAlongPath( SurfaceNode* startNode, SurfaceNode* endNode,
                                           McDArray< McHandle<SurfaceNode> >& intermediate,
                                           McDArray<int>& triangles, McDArray<int>& edges );

    /// Set pointer to allowed surface triangles
    void setAllowedTriangles(McBitfield* allowedTriangles)
    {
        if ( data.ptr() )
            data->mAllowedTriangles = allowedTriangles;
    }

    /// Set pointer to allowed surface edges
    void setAllowedEdges(McBitfield* allowedEdges)
    {
        if ( data.ptr() )
            data->mAllowedEdges = allowedEdges;
    }

    /// Set pointer to surface edges that must not be crossed
    void setForbiddenVertices(McBitfield* forbiddenVertices)
    {
        if ( data.ptr() )
            data->mForbiddenVertices = forbiddenVertices;
    }

    /// Set pointer to surface edges that must not be crossed
    virtual void setAllowedPoints(McBitfield* allowedPoints)
    {
        if ( data.ptr() )
        {
            if ( !allowedPoints )
                data->mForbiddenVertices = NULL;
            else
            {
                data->mForbiddenVertices = new McBitfield();
                data->mForbiddenVertices->resize(allowedPoints->nBits());
                data->mForbiddenVertices->unsetAll();

                for ( unsigned int i=0 ; i<data->mForbiddenVertices->nBits(); i++ )
                {
                    bool is = false;
                    int was = -1;
                    if ( !(*allowedPoints)[i] )
                    {
                        data->mForbiddenVertices->set(i);

                        is = (*(data->mForbiddenVertices))[i];
                        was = (*(data->mForbiddenVertices))[i];
                    }



                }
            }
        }
    }

    /// Set maximum number of iterations
    void setMaxNumberOfIterations(int nIter) { mNumMaxIter = nIter; }

    /// Parse method
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

private:

    /// Pointer to data required by TriangleStrip
    McHandle<TriangleStripData> data;

    McBitfield mAllowedTriangles;
    McBitfield mAllowedEdges;
    McBitfield mForbiddenVertices;

    /// Maximum number of iterations
    int mNumMaxIter;

    /// For debugging
    void showPath( SurfaceNode* start, SurfaceNode* end,
                   const McDArray<McHandle<SurfaceNode> >& intermediate );

    /// Array used when TriangleDijkstraConnector::getTriangleStrip is
    /// called.  For performance only.
    McDArray<TriangleDijkstraConnector::ShortestTriangleStrip> mShortestStrip;
};

#endif

/// @}

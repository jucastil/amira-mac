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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef SHORTEST_EDGE_PATH_H
#define SHORTEST_EDGE_PATH_H

#include <hxsurftools/HxSurfToolsWinDLLApi.h>

#include <mclib/McDArray.h>
#include <mclib/McFHeap.h>
#include <mclib/McBitfield.h>

class Surface;

/** This class computes the shortest path between two vertices
    of a given surface along edges. Weights for the edges must be
    supplied, which define the metric of the computation. Per default 
    (i.e. if no weights are supplied), each edge has weight 1. */

class HXSURFTOOLS_API ShortestEdgePath {

  public:

    ///
    ShortestEdgePath(Surface* surface) : mSurface(surface) {}

    /** Compute the shortest @c path on the surface from @c from to @c to,
        restricted to @c allowed points. Returns 1 on success. */
    int findShortestPath(int from, int to, 
                         McDArray<int>& path,
                         bool doInit=true,
                         McBitfield* allowed=0,
                         float* weights=0);

    /// Initializes the shortest path computation from origin to all other points
    void initShortestPaths(int origin,
                           McBitfield* allowed=0,
                           float* weights=0);

    /// Stop initialization after target has been found
    void initShortestPaths(int origin, int target,
                           McBitfield* allowed=0,
                           float* weights=0);

    /// Stop initialization after all targets have been found
    void initShortestPaths(int origin, McDArray<int> targets,
                           McBitfield* allowed=0,
                           float* weights=0);

    /// Compute shortest distance to all seed points
    void computeDistanceMap(const McDArray<int>& seeds,
                            McDArray<float>& distance,
                            McBitfield* allowed=0,
                            float* weights=0);

    /// Return length of given edge path
    float getPathLength(const McDArray<int>& path, float* weights) const;

    /// Return distance at given vertex @v in current distance map
    float getDistance(int v)
    {
        if ( !mShortPaths.size() ) return 0;
        return mShortPaths[v].path;
    }

  protected:

    /// Class for the computation of shortest paths on a surface.
    class PointPath : public McFHeapElement {
      public:
        ///
        PointPath() : point(-1), neighbour(-1), path(-1), inlist(false) {}
        ///
        int point;
        ///
        int neighbour;
        ///
        float path;
        ///
        bool inlist;
        ///
        int operator <(const PointPath& other) {
            return path < other.path;	    
        }
    };

    /// Surface pointer
    Surface* mSurface;

    /// Distance map for computation of shortest path
    McDArray<PointPath> mShortPaths;

    /// Flag for checking if entry in shortestPath was initialized
    McBitfield mUsed;

};

#endif

/// @}

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

/// @addtogroup hxspatialgraph hxspatialgraph
/// @{
#ifndef EDGEPOINTSMANAGER_H
#define EDGEPOINTSMANAGER_H

#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>

#include <hxcore/HxMessage.h>

class EdgePointsManager {
public:
    /// Constructor
    EdgePointsManager();

    /// Insert the edge points of one new edge
    void insertEdgeBefore(const int edgeNum, const McDArray<McVec3f>& points);

    /// Insert the edge points of multiple edges, such that, after insertion, the indices of the new
    /// edges correspond to the indices in \a edgeNums
    void insertMultipleEdges(const McDArray<int>& edgeNums, const McDArray<McDArray<McVec3f> >& points);

    /// Add one edge (by appending)
    void addEdge(const McDArray<McVec3f>& points);

    /// Set the edge points of edge \a edgeNum to \a points
    /// inserts/removes space when required
    void setEdgePoints(const int edgeNum, const McDArray<McVec3f>& points);

    ///  Insert points \a points into edge \a edgeNum before \a beforePoint
    void insertEdgePoints(const int edgeNum, const int beforePoint, const McDArray<McVec3f>& points);

    /** Remove \a numValues points from edge \a edgeNum, starting from \a
     *  firstIndexToDelete.
     *  \a firstIndexToDelete + \a numValues must not exceed the number of
     *  points on edge \a edgeNum.
     */
    void removeEdgePoints(const int edgeNum,
                          const int firstIndexToDelete,
                          const int numValues);

    /// Get the number of edge points of edge \a edgeNum
    int getNumEdgePoints(const int edgeNum) const;

    /// Get the number of edges
    int getNumEdges() const;

    /// Get the total number of edge points
    int getTotalNumEdgePoints() const;

    /// Return a copy of the points for edge \a edgeNum
    McDArray<McVec3f> getEdgePoints(const int edgeNum) const;

    /// Returns a const pointer of edge \a edgeNum. \a numPoints contains the number of points of edge \a edgeNum
    const McVec3f* getEdgePoints(const int edgeNum, int& numPoints) const;

    /// Get the coordinates of a single edge point
    McVec3f getEdgePoint(const int edgeNum, const int pointNum) const;

    /// Set the coordinates of a single edge point
    void setEdgePoint(const int edgeNum, const int pointNum, const McVec3f coords);

    /// Remove one edge
    void removeEdge(const int edgeNum);

    /// Remove multiple edges
    void removeMultipleEdges(const McDArray<int>& edgeNums);

    /// Clear Edgepoints and EdgePointSum
    void clear();

    /// Give a hint about the expected number of points.
    /// This reserves space and therefore avoids multiple reallocations
    void setSizeHint(const int numPoints);

protected:
    /// Array containing all edge points after each other
    McDArray<McVec3f> mEdgePoints;

    /// mEdgePointSum[i] is the index of the first point of edge i in the points array mEdgePoints
    /// mEdgePointSum.size() = numEdges + 1, the last element contains the total number of points
    McDArray<int> mEdgePointSum;
};

#endif

/// @}

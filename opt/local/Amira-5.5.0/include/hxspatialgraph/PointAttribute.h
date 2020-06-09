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
#ifndef POINT_ATTRIBUTE_H
#define POINT_ATTRIBUTE_H

#include "hxspatialgraphAPI.h"

#include <mclib/McPrimType.h>
#include <mclib/McTypedPointer.h>
#include <mclib/McTypedElement.h>
#include <mclib/McHandable.h>
#include <mclib/McDArray.h>
#include <mclib/McTypedData2D.h>

#include "GraphAttribute.h"

class HxSpatialGraph;

class HXSPATIALGRAPH_API PointAttribute : public GraphAttribute
{

    PointAttribute();

public:

    PointAttribute(HxSpatialGraph * sg, const char* name, McPrimType type, int nDataVar=1);

    /// Destructor.
    ~PointAttribute();

    /// allocate memory for all points at once
    void init(const McDArray<int> &numEdgePointsPerEdge);

    /// Returns the number of elements
    int size() const { return getTotalNumEdgePoints(); }

    /// returns the number of edges
    int getNumEdges() const;

    /// return the total number of edge points
    int getTotalNumEdgePoints() const;

    /// returns the number of edge points for edge \a iEdge
    int getNumEdgePoints(const int iEdge) const ;

    /// float data access
    float* floatDataAtPoint(const int iEdge, const int iPoint);
    const float* floatDataAtPoint(const int iEdge, const int iPoint) const;

    float getFloatDataAtPoint(const int iEdge, const int iPoint) const;
    void  setFloatDataAtPoint(const float value, const int iEdge, const int iPoint);

    /// int data access
    int * intDataAtPoint(const int iEdge, const int iPoint);
    const int* intDataAtPoint(const int iEdge, const int iPoint) const;

    int getIntDataAtPoint(const int iEdge, const int iPoint) const;
    void  setIntDataAtPoint(const int value, const int iEdge, const int iPoint);

    /// generic data
    char* genericDataAtPoint(const int iEdge, const int iPoint);
    const char* genericDataAtPoint(const int iEdge, const int iPoint) const;

    /// get the value of point \a iPoint on edge \a iEdge
    McTypedElement getValue(const int iEdge, const int iPoint) const;

    /// set the value of point \a iPoint on edge \a iEdge
    void setValue(const int iEdge, const int iPoint, const McTypedElement value);

    /// get the values of all points on edge \a iEdge
    McTypedData2D getValues(const int edgeNum) const;

    /// Set values for all points of edge \a iEdge.
    void setValues(const int edgeNum, const McTypedData2D& values);

    /// Add values for one new edge (by appending)
    void addEdge(const McTypedData2D& values);

    /// Add edge with \a numPoints uninitialized values (by appending)
    void addEdge(const int numPoints=2);

    /// Remove values of edge \a iEdge
    void removeEdge(const int iEdge);

    /// Remove values of edges with indices \a edgeNums
    void removeMultipleEdges(const McDArray<int>& edgeNums);

    /// Insert uninitialized space for values for all points on a single edge
    void insertEdgeBefore(const int edgeNum, const int numPoints=2);

    /// Insert values for new edge before edge \a edgeNum
    void insertEdgeBefore(const int edgeNum, const McTypedData2D& values);

    /// Insert values for multiple edges
    /// values[i][j]: i=edgeNum, j=pointNum
    void insertValuesForMultipleEdges(const McDArray<int>& edgeNums, const McDArray<McTypedData2D>& values);

    void insertEdgePoints(const int edgeNum, const int beforePoint, const int numValues);

    /** Remove \a numValues points from edge \a edgeNum, starting from \a
     *  firstIndexToDelete.
     *  \a firstIndexToDelete + \a numValues must not exceed the number of
     *  points on edge \a edgeNum.
     */
    void removeEdgePoints(const int edgeNum, const int firstIndexToDelete, const int numValues);

private:

    void* dataPtr() {return mData; }
    const void* dataPtr() const {return mData; }

    void resizeEdgePoints(int iEdge, int numPoints);

    char* mData;

    /// total sum of edge points up to (not including!) edge i
    /// the array is of size #numEdges + 1, the last item contains the total number of points
    McDArray<int> mEdgePointSum;

    friend class HxSpatialGraph;
};

#endif

/// @}

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
#ifndef SPATIALGRAPHOPERATIONSET_H
#define SPATIALGRAPHOPERATIONSET_H

#include "SpatialGraphOperation.h"

//////////////////////////////////////////////////////////////////////////////////////////////
class HXSPATIALGRAPH_API OperationSet : public Operation {
public:
    OperationSet(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~OperationSet();
    virtual void undo();

    /// Given a selection \a sel, this method returns what \a sel looks like after the operation
    /// (operating on a selection potentially different from \a sel) has been undone.
    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;

    void setRemoveIntermediateVertices(const bool val);

protected:
    McDArray<Operation*> operations;
    bool mRemoveIntermediateVertices; /// Remove vertices with exactly 2 incident edges
};

//////////////////////////////////////////////////////////////////////////////////////////////
class HXSPATIALGRAPH_API ConnectPointToVertexOperationSet : public OperationSet {
public:
    ConnectPointToVertexOperationSet(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~ConnectPointToVertexOperationSet();
    virtual void exec();
};

//////////////////////////////////////////////////////////////////////////////////////////////
class HXSPATIALGRAPH_API ConnectTracedPointToVertexOperationSet : public OperationSet {
public:
    ConnectTracedPointToVertexOperationSet(HxSpatialGraph* sg, McDArray<McVec3f>* inCenterLine, McDArray<float>* inRadii, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~ConnectTracedPointToVertexOperationSet();
    virtual void exec();

protected:
    McDArray<McVec3f> centerLine;
    McDArray<float> radii;
};

//////////////////////////////////////////////////////////////////////////////////////////////
class HXSPATIALGRAPH_API ConnectTracedVertexToPointOperationSet : public OperationSet {
public:
    ConnectTracedVertexToPointOperationSet(HxSpatialGraph* sg, McDArray<McVec3f>* inCenterLine, McDArray<float>* inRadii, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~ConnectTracedVertexToPointOperationSet();
    virtual void exec();

protected:
    McDArray<McVec3f> centerLine;
    McDArray<float> radii;
};

//////////////////////////////////////////////////////////////////////////////////////////////
class HXSPATIALGRAPH_API ConnectPointToPointOperationSet : public OperationSet {
public:
    ConnectPointToPointOperationSet(HxSpatialGraph* sg, SpatialGraphPoint* inDstPoint, McDArray<McVec3f>* inCenterLine, McDArray<float>* inRadii, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~ConnectPointToPointOperationSet();
    virtual void exec();

protected:
    SpatialGraphPoint* dstPoint;
    McDArray<McVec3f> centerLine;
    McDArray<float> radii;
};

//////////////////////////////////////////////////////////////////////////////////////////////
class HXSPATIALGRAPH_API MultipleVerticesToPointsOperationSet : public OperationSet {
public:
    MultipleVerticesToPointsOperationSet(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~MultipleVerticesToPointsOperationSet();
    virtual void exec();
};

//////////////////////////////////////////////////////////////////////////////////////////////
/// Find all vertices with 2 incident edges and convert them to points.
/// A check is made to ascertain that the edge is not a contour (i.e. is twice in incidence list)
class HXSPATIALGRAPH_API FindAndConvertVerticesToPointsOperationSet : public MultipleVerticesToPointsOperationSet {
public:
    FindAndConvertVerticesToPointsOperationSet(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~FindAndConvertVerticesToPointsOperationSet();
};

//////////////////////////////////////////////////////////////////////////////////////////////
/// Given a selection, add edges to the graph, such that afterwards the entire
/// selection is on one connected component of the graph.
/// Components are connected by searching for the shortest connection between vertices (euclidean distance).
/// Connections are created only between end points, i.e. vertices with only one incident edge.
class HXSPATIALGRAPH_API ConnectSelectionOperationSet : public OperationSet {
public:
    ConnectSelectionOperationSet(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~ConnectSelectionOperationSet();
    virtual void exec();
};


class HXSPATIALGRAPH_API AddTracedEdgeOperationSet : public OperationSet {
public:
    /// exactly one point/node has to be selected
    AddTracedEdgeOperationSet(  HxSpatialGraph* sg,
                                McVec3f dstPoint,
                                McDArray<McVec3f> &edgePoints,
                                McDArray<float>  &radi,
                                const SpatialGraphSelection &selectedElements,
                                const SpatialGraphSelection &visibleElements
                              );
    /// exactly two nodes/points or mixture of both have to be selected
    AddTracedEdgeOperationSet(  HxSpatialGraph* sg,
                                McDArray<McVec3f> &edgePoints,
                                McDArray<float>  &radi,
                                const SpatialGraphSelection &selectedElements,
                                const SpatialGraphSelection &visibleElements
                              );
    virtual ~AddTracedEdgeOperationSet();
    virtual void exec();

    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;
    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;

protected:
    McDArray<McVec3f> mEdgePoints;
    McDArray<float> mRadi;
    McVec3f mDstVertexCoords;
    int mSelectedVertexIdx;
    SpatialGraphSelection mSelAfterOpSet;
};

//////////////////////////////////////////////////////////////////////////////////////////////
class HXSPATIALGRAPH_API MoveVertexOperationSet : public OperationSet {
public:
    /// This operation-set moves a vertex at a new postion at adapts the geometric embedding
    /// of all incident edges.
    ///
    /// exactly one point/node has to be selected
    MoveVertexOperationSet(HxSpatialGraph* sg, const int vertexIdx,
                            const McVec3f& newPos,
                            const IncidenceList& incidentEdges,
                            const McDArray<McDArray<McVec3f> >& edgePoints,
                            const SpatialGraphSelection &selectedElements,
                            const SpatialGraphSelection &visibleElements);
    virtual ~MoveVertexOperationSet();
    virtual void exec();
    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;
    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;
protected:
    int mVertexIdx;
    McVec3f mNewPos;
    IncidenceList mIncidentEdges;
    McDArray<McDArray<McVec3f> > mEdgePoints;
    SpatialGraphSelection mSelectedElements;
    SpatialGraphSelection mVisibleElements;
};

//////////////////////////////////////////////////////////////////////////////////////////////
/// Split an exiting edge into 2 and use either a previous edgePoint or a newly picked point as split-vertex
class HXSPATIALGRAPH_API SplitEdgeWithNewVertexOperationSet : public OperationSet {
public:
    SplitEdgeWithNewVertexOperationSet(HxSpatialGraph* sg, McVec3f newVertexCoord, int pickedEdge, int nextEdgePointIdx, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~SplitEdgeWithNewVertexOperationSet();
    virtual void exec();
    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;

protected:
    McDArray<McVec3f> mNewPointCoords;
    int mEdge;
    int mEdgePoint;

    SpatialGraphSelection mHighSelAfter;
};

//////////////////////////////////////////////////////////////////////////////////////////////
///  Split an exiting edge into 2 and use either a previous edgePoint or a newly picked point as split-vertex.
///  The new vertex is connected to the currently selected vertex
class HXSPATIALGRAPH_API SplitEdgeWithNewVertexAndConnectOperationSet : public OperationSet {
public:
    SplitEdgeWithNewVertexAndConnectOperationSet(HxSpatialGraph* sg, McVec3f newVertexCoord, int pickedEdge, int nextEdgePointIdx, McDArray<McVec3f>* inCenterLine, McDArray<float>* inRadii, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~SplitEdgeWithNewVertexAndConnectOperationSet();
    virtual void exec();
    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;

protected:
    McDArray<McVec3f> mNewPointCoords;
    McDArray<McVec3f> centerLine;
    McDArray<float> radii;
    int mEdge;
    int mEdgePoint;

    SpatialGraphSelection mHighSelAfter;
};

//////////////////////////////////////////////////////////////////////////////////////////////
/// Create a new vertex in the graph and connect it to a selected vertex/edgePoint
class HXSPATIALGRAPH_API AddVertexAndConnectOperationSet : public OperationSet {
public:
    AddVertexAndConnectOperationSet(HxSpatialGraph* sg, McVec3f newVertexCoord, McDArray<McVec3f>* inCenterLine, McDArray<float>* inRadii, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~AddVertexAndConnectOperationSet();
    virtual void exec();
    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;

protected:
    McDArray<McVec3f> mNewPointCoords;
    McDArray<McVec3f> centerLine;
    McDArray<float> radii;
    SpatialGraphSelection mHighSelAfter;
};

#endif

/// @}

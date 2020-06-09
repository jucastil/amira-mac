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
#ifndef SPATIALGRAPHOPERATION_H
#define SPATIALGRAPHOPERATION_H

#include "SpatialGraphSelection.h"
#include "SpatialGraphEdge.h"
#include "IncidenceList.h"
#include <mclib/McVec3f.h>
#include <mclib/McTypedElement.h>
#include <mclib/McTypedData2D.h>

class HxSpatialGraph;


/// Abstract base class for Operations and OperationSets.
/// Provides some helper functions to manipulate a spatialGraph.
class HXSPATIALGRAPH_API Operation {
public:
    Operation(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~Operation();
    virtual void exec() = 0;
    virtual void undo() = 0;

    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;
    virtual SpatialGraphSelection getHighlightSelectionAfterUndo() const;

    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;
    virtual SpatialGraphSelection getVisibleSelectionAfterUndo() const;

    SpatialGraphEdge getEdge(const int edgeNum);
    McVec3f getVertex(const int vertexNum);

protected:
    HxSpatialGraph* graph;
    SpatialGraphSelection mSelection;
    SpatialGraphSelection mVisibleSelection;
    SpatialGraphSelection::Iterator mSelectionIter;
};

//////////////////////////////////////////////////////////////////////////////////////////////
/** Creates a new vertex */
class HXSPATIALGRAPH_API AddVertexOperation : public Operation {
public:
    AddVertexOperation( HxSpatialGraph* sg,
                        McVec3f inVertex,
                        const SpatialGraphSelection &selectedElements,
                        const SpatialGraphSelection &visibleElements
                       );
    virtual ~AddVertexOperation();
    virtual void exec();
    virtual void undo();
    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;
    int getNewVertexNum() const;
protected:
    int mNewVertexIdx; ///!< index of added vertex
    McVec3f mNewVertex; ///!< the new vertex
};


//////////////////////////////////////////////////////////////////////////////////////////////
/** Creates a new edge between two vertices. The selection should contain exactly two vertices. */
class HXSPATIALGRAPH_API ConnectOperation : public Operation {
public:
    ConnectOperation(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~ConnectOperation();
    virtual void exec();
    virtual void undo();

    int getNewEdgeNum() const;
    void setEdgePoints(const McDArray<McVec3f> &edgePoints);

    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;
    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;

protected:
    int mNewEdge; ///!< index of added edge
    McDArray<McVec3f> mEdgePoints; ///!< the edge points if available
};


//////////////////////////////////////////////////////////////////////////////////////////////
/** Deletes all vertices and edges in the selection.
 *  Also all edges are deleted, which have a vertex in the selection (the edges would become invalid otherwise).*/
class HXSPATIALGRAPH_API DeleteOperation : public Operation {
public:
    DeleteOperation(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~DeleteOperation();
    virtual void exec();
    virtual void undo();

    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;

protected:
    McDArray<SpatialGraphEdge> removedEdges; ///!< removed edges, stored for undo
    McDArray<McDArray<McVec3f> > removedEdgePoints;
    McDArray<McVec3f> removedVertices; ///!< removed vertices, stored for undo
    McDArray<McTypedData2D> vertexAttributes;
    McDArray<McTypedData2D> edgeAttributes;
    McDArray<McDArray<McTypedData2D> > pointAttributes;

    McDArray<int> vertexAttribId;
    McDArray<int> edgeAttribId;
    McDArray<int> pointAttribId;
};

//////////////////////////////////////////////////////////////////////////////////////////////
/** Moves selected vertex.*/
class HXSPATIALGRAPH_API MoveOperation : public Operation {
public:
    MoveOperation(HxSpatialGraph* sg, const int vertexIdx, const McVec3f newVertex, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~MoveOperation();
    virtual void exec();
    virtual void undo();

protected:
    int mVertexIdx; ///!< index of added vertex
    McVec3f mNewVertex; ///!< the new vertex position
    McVec3f mOldVertex; ///!< the old vertex position


};
//////////////////////////////////////////////////////////////////////////////////////////////
/** Replace geometric embedding of an edge (edgePoints).*/
class HXSPATIALGRAPH_API ReplaceOperation : public Operation {
public:
    ReplaceOperation(HxSpatialGraph* sg, const int edgeIdx, const McDArray<McVec3f> newEdgePoints, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~ReplaceOperation();
    virtual void exec();
    virtual void undo();

protected:
    int mEdgeIdx; ///!< index of modified edge
    McDArray<McVec3f> mNewEdgePoints; ///!< the new edge points
    McDArray<McVec3f> mOldEdgePoints; ///!< the old edge points


};

//////////////////////////////////////////////////////////////////////////////////////////////
/** Convert a vertex into an edge point. The selection should contain exactly one vertex with
 *  exactly two incident edges. This operation merges the two edges into one and removed the vertex.
 */

class HXSPATIALGRAPH_API VertexToPointOperation : public Operation {
public:
    VertexToPointOperation(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~VertexToPointOperation();
    virtual void exec();
    virtual void undo();

    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;

protected:
    McDArray<int> mOldEdgeNums;
    McDArray<SpatialGraphEdge> mOldEdges;
    McDArray<McDArray<McVec3f> > mOldEdgePoints;

    int mOldVertexNum;
    McVec3f mOldVertex;
    McDArray<McTypedElement> mOldVertexAttributes;
    McDArray<McTypedData2D> mOldEdgeAttributes;
    McDArray<McDArray<McTypedData2D> > mOldPointAttributes;

    McDArray<int> mVertexAttribId;
    McDArray<int> mEdgeAttribId;
    McDArray<int> mPointAttribId;

    int mNewEdgeNum;
};

//////////////////////////////////////////////////////////////////////////////////////////////
/// This class takes a selection with one edge point selected, it converts the point to a vertex
/// and splits the edge of which the point was a part into two edges.
class HXSPATIALGRAPH_API PointToVertexOperation : public Operation {
public:
    PointToVertexOperation(HxSpatialGraph* sg, const SpatialGraphSelection &selectedElements, const SpatialGraphSelection &visibleElements);
    virtual ~PointToVertexOperation();

    virtual void exec();
    virtual void undo();

    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;
    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;

    int getNewVertexNum() const;

protected:
    int mOldEdgeNum;
    SpatialGraphEdge mOldEdge;
    McDArray<McVec3f> mOldEdgePoints;

    McDArray<McTypedElement> mOldEdgeAttributeValues;
    McDArray<McTypedData2D> mOldPointsAttributeValues;

    McDArray<int> mOldEdgeAttribId;
    McDArray<int> mOldPointAttribId;

    int mNewVertexNum;
    McDArray<int> mNewEdgeNums;

};


//////////////////////////////////////////////////////////////////////////////////////////////
/** Insert edge points on edge.
 *  The \a selectedElement selection must contain exactly one selected edge point.
 *  The selected edge point must not be the first point on the edge.
 *  The points \a points are inserted before this selected point on the same edge.
 */
class HXSPATIALGRAPH_API InsertEdgePointsOperation : public Operation {
public:
    InsertEdgePointsOperation(HxSpatialGraph* sg,
                              McDArray<McVec3f> newPointCoords,
                              const SpatialGraphSelection &selectedElements,
                              const SpatialGraphSelection &visibleElements);
    virtual ~InsertEdgePointsOperation();
    virtual void exec();
    virtual void undo();

    virtual SpatialGraphSelection getVisibleSelectionAfterOperation() const;
    virtual SpatialGraphSelection getHighlightSelectionAfterOperation() const;

protected:
    McDArray<McVec3f> mNewPointCoords; ///!< the new edge points
    int mEdgeNum;
    int mEdgePoint;
};


//////////////////////////////////////////////////////////////////////////////////////////////
/// This operation finds isolated vertices and removes them.
class HXSPATIALGRAPH_API FindAndDeleteIsolatedVertices : public DeleteOperation {
public:
    FindAndDeleteIsolatedVertices(HxSpatialGraph* sg, SpatialGraphSelection sel,SpatialGraphSelection vis);
    ~FindAndDeleteIsolatedVertices();

    virtual void exec();
    virtual void undo();

private:
    SpatialGraphSelection mRememberOldSelection;
};


#endif

/// @}

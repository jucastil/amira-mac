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
#ifndef SPATIALGRAPHSELECTION_H
#define SPATIALGRAPHSELECTION_H

#include "hxspatialgraphAPI.h"

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>

class HxSpatialGraph;


struct HXSPATIALGRAPH_API SpatialGraphPoint
{
    SpatialGraphPoint();
    SpatialGraphPoint(const int edge, const int point);
    bool operator== (const SpatialGraphPoint &other) const { return (edgeNum == other.edgeNum && pointNum == other.pointNum); }
    int edgeNum;
    int pointNum;
};

class HXSPATIALGRAPH_API SpatialGraphSelection
{
  private:

    struct BitfieldIterator {
        BitfieldIterator(McBitfield const& field):field(field) {
            reset();
        }

        void reset() {
            index=-1;
        }

        int nextSelected() {
            ++index;
            while (index < static_cast<int>(field.nBits()) && (!field[index])) {
                ++index;
            }
            if (index == static_cast<int>(field.nBits())) {
                return -1;
            }
            else {
                return index;
            }
        }

        McBitfield const& field;
        int index;
    };

  public:

    struct Iterator
    {
        Iterator(SpatialGraphSelection const& sel)
        :   vertices(sel.vertices)
        ,   edges(sel.edges)
        ,   edgesWithAllPointsSelected(sel.edgesWithAllPointsSelected)
        {
        }

        BitfieldIterator vertices,edges,edgesWithAllPointsSelected;
    };

    SpatialGraphSelection();
    SpatialGraphSelection(const int numVertices, const int numEdges);
    SpatialGraphSelection(const HxSpatialGraph* graph);

    void resize (const int numVertices, const int numEdges);
    void clear();
    void selectAllEdges();
    void selectAllVertices();
    void deselectAllEdges();
    void deselectAllVertices();
    void deselectAllPoints();
    void selectAllVerticesAndEdges();
    bool isEmpty() const;
    bool isSameSize(const SpatialGraphSelection& sel) const;

    void selectVertex(const int vertexNum);
    void deselectVertex(const int vertexNum);
    void toggleVertex(const int vertexNum);
    bool isSelectedVertex(const int vertexNum) const;
    int getNumSelectedVertices() const;
    void setVertexSelection(const McBitfield& selectedVertex);
    McBitfield getVertexSelection() const;

    /// Returns index of \a i-th selected vertex (i=0 for first selected vertex).
    /// Returns -1 if there is none.
    int getSelectedVertex(const int i) const;

    int getNumVertices() const;

    void selectEdge(const int edgeNum);
    void deselectEdge(const int edgeNum);
    bool isSelectedEdge(const int edgeNum) const;
    int getNumSelectedEdges() const;
    void setEdgeSelection(const McBitfield& selectedEdges);
    McBitfield getEdgeSelection() const;

    /// Returns index of \a i-th selected edge (i=0 for first selected edge).
    /// Returns -1 if there is none.
    int getSelectedEdge(const int i) const ;

    void toggleEdge(const int edgeNum);
    int getNumEdges() const;

    void copyEdgeSelection(const SpatialGraphSelection& sel);
    void copyVertexSelection(const SpatialGraphSelection& sel);
    void copyPointSelection(const SpatialGraphSelection& sel);
    void copyEdgesWithAllPointsSelected(const SpatialGraphSelection& sel);

    void selectPoint(SpatialGraphPoint p);
    int getNumSelectedPoints() const;
    SpatialGraphPoint getSelectedPoint(const int i) const;
    bool isPointSelected(const SpatialGraphPoint& p) const;
    void togglePoint(const SpatialGraphPoint& p);

    void addSelection(const SpatialGraphSelection& sel);
    void subtractSelection(const SpatialGraphSelection& sel);
    void toggleAll();

    /// Returns true if all selected vertices are also selected in \a sel.
    bool isSubsetVertices(const SpatialGraphSelection& sel) const;

    /// Returns true if all selected edges are also selected in \a sel.
    bool isSubsetEdges(const SpatialGraphSelection& sel) const;

    SpatialGraphSelection& operator  = (const SpatialGraphSelection &rhs);
    SpatialGraphSelection& operator &= (const SpatialGraphSelection &other);
    SpatialGraphSelection& operator & (const SpatialGraphSelection &other);
    bool operator == (const SpatialGraphSelection &other) const;

    void selectAllPointsOnEdge(const int edgeNum);
    void selectAllPointsOnEdgesFromSelection(const SpatialGraphSelection &sel);
    void selectAllPoints();
    int getNumEdgesWithAllPointsSelected() const;
    bool allPointsOnEdgeSelected(const int edgeNum) const;

    // serialize \a edges and \a vertices bitfields content
    // compressed as string containing only letters [A-Z].
    void serialize(McString& edgeStr, McString& vertexStr);
    // deserialize compressed \a edgeStr and \a vertexStr containing only letters [A-Z],
    // into appropriate bitfields.
    void deserialize (const char* edgeStr, const char* vertexStr);

protected:
    McBitfield vertices;
    McBitfield edges;

    // Bitfield containing all edges for which all points are selected. Is only created when required.
    McBitfield edgesWithAllPointsSelected;
    // Array of individual points
    McDArray<SpatialGraphPoint> points;

    int edgesWithAllPointsSelectedIterIdx;
};

#endif // SPATIALGRAPHSELECTION_H

/// @}

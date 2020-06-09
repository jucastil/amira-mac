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
#ifndef HXSPATIALGRAPH_H
#define HXSPATIALGRAPH_H

/** \class HxSpatialGraph
 *  \brief This class represents a (possibly directed) graph, embedded in \f$R^3\f$, with optional attribute data.
 *
 *  The connectivity of the graph \f$G\f$ is defined by a set of vertices \f$V\f$ and edges \f$E\f$: \f$G = (V,E)\f$.
 *  An edge is defined by 2 vertices: \f$e \in E = (v_i,v_j)\f$. The graph can be interpreted as a directed graph,
 *  in this case the edge is directed from the first vertex to the second: \f$v_i\to v_j\f$.
 *  The graph forms the minimal topological skeleton of the represented object. This geometry-free representation
 *  allows for the application of standard graph algorithms.
 *
 *  This graph in mathematical sense is embedded in 3D. Each vertex has a location in \f$R^3\f$. Each edge is defined by an ordered set
 *  of points, the first point corresponds to \f$v_i\f$, the second to \f$v_j\f$.
 *  The points in each list are implicitly connected by straight line segments
 *  and thus form a piece-wise linear (PL) representation of the edge in space. In principle, any other
 *  approximation (splines, downsampled PL, etc.) could be used instead of the PL representation.
 *  The geometry of the graph is considered to be continuous at the vertices where two or more edge meet.
 *
 *  Data can be stored on the graph itself and on its embedding in 3D. The data can be elements of \f$R^M\f$, \f$N\f$,
 *  or of an enumerated set \f$L\f$ of labels \f$ \{l_0, \ldots, l_m\}\f$. The following functions can be stored on the graph:
 *  - \f$V\to L\f$. Example: store specific vertex types
 *  - \f$V\to R^M\f$.
 *  - \f$E\to R^M\f$. Example: store length of each edge.
 *  - \f$E\to L\f$.
 *  - \f$(V,E)\to L\f$. Disjoint, complete partitioning of the graph.
 *    Example: store names of all vertices/edges that belong to a connected component. (The alternative would be to create selections, i.e.\
 *    create subsets of vertices and edges by enumerating them in a list. A fuzzy partitioning could be created by storing a number of
 *    floats for each vertex/edge, one for each material, which represent confidence values. This takes however more space.)
 *  - \f$(V,E)\to N\f$. Graph partitioning. Example: store original image slice number from which the vertices/edges were segmented.
 *  - \f$R^3\rightarrow R^M\f$, a function which is continuous on the edges, but possibly non-continuous at the vertices.
 *    This function is defined by storing data values at each point. Example: radius of a blood vessel.
 *
 * Other possibilities would be:
 *  - \f$R^3\rightarrow R^M\f$ or \f$R^3\rightarrow L\f$, a piece-wise constant function defined by storing data values
 *    for each connection line between two points.
 *
 *
 */

#include "hxspatialgraphAPI.h"
#include "SpatialGraphSelection.h"
#include "IncidenceList.h"
#include "SpatialGraphEdge.h"

#include "EdgeVertexAttribute.h"
#include "PointAttribute.h"

#include "EdgePointsManager.h"

#include "SpatialGraphOperation.h"

#include <hxcore/HxSpatialData.h>

#include <hxcolor/HxRangeSet.h>

#include <mclib/McHandle.h>
#include <mclib/McHandable.h>
#include <mclib/McHashTable.h>

#include <Inventor/SbColor.h>

class HxSpatialGraphInterface;
class AmiraMesh;
class HierarchicalLabels;

class HXSPATIALGRAPH_API HxSpatialGraph : public HxSpatialData
{
    friend class Operation;
    friend class DeleteOperation;
    friend class PointToVertexOperation;
    friend class VertexToPointOperation;

    MC_HEADER(HxSpatialGraph);

    //// predefined attribute types
    enum AttributeType {
        VERTEX_LABEL
    ,   VERTEX_INT
    ,   EDGE_LABEL
    ,   EDGE_INT
    ,   GRAPH_VERTEX_LABEL
    ,   GRAPH_VERTEX_INT
    ,   GRAPH_EDGE_LABEL
    ,   GRAPH_EDGE_INT
    };

    //// attribute locations
    enum Location {
        VERTEX   // Data per vertex
    ,   EDGE     // Data per edge (segment between branching points)
    ,   POINT    // Data per point of an edge
    };

private:
    class HxRangeSetDataImpl : public HxRangeSetData {
      public:
        HxRangeSetDataImpl(HxSpatialGraph* o)
            : HxRangeSetData(o->getOwner(), McInterfaceOwner::STATIC_IFACE)
            , mOuter(o)
        {}

        /** Returns true if the min / max values of the specified data set
            were determined successfully, and false otherwise.  setId must
            be encoded with encodeCurrentSetWithLocation(). */
        virtual bool getRangeSet(float& min, float& max, int setId);

      private:
        HxSpatialGraph* mOuter;
    };
    friend class HxRangeSetDataImpl;

public:

    typedef McHashTable<const char*, HierarchicalLabels*> LabelGroups;

    /// Default Constructor
    HxSpatialGraph();

    /// Destructor
    ~HxSpatialGraph();

    /// Tcl commands
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Returns the number of edges in the graph
    int getNumEdges() const;

    /// Returns the number of vertices in the graph
    int getNumVertices() const;

    /// Get a list of edges incident on vertex \a vertexNum
    const IncidenceList& getIncidentEdges(const int vertexNum) const;

    /** Give a hint on the total expected size of the spatial graph.
     *  This method will allocate space for items in all relevant arrays, without actually
     *  changing the number of items. This method helps to avoid constant reallocation,
     *  resulting in a performance increase.
     */
    void setSizeHint(const int numVertices, const int numEdges, const int numPoints);

    /// Clear the spatialgraph, i.e. clear all vertices, edges, points, attributes and labels.
    void clear();

    /// Returns a new SpatialGraph, which is a duplicate of the current SpatialGraph
    HxSpatialGraph* duplicate() const;

    /// Copies an existing SpatialGraph \a copyFrom to the current SpatialGraph
    void copyFrom(const HxSpatialGraph* copyFrom);

    /// Merges SpatialGraph \a other with this spatialGraph. All data is copied.
    /// Note: no check for label correspondence is done. Any vertex/edge label larger than the number of labels is set to 0,
    /// any graph label larger than the total number of graph labels is set to undefined (1)
    void merge(const HxSpatialGraph* other);

    /// Returns a new graph containing only the selected elements of the
    /// current graph.
    HxSpatialGraph* getSubgraph(const SpatialGraphSelection& sel) const;

    /// Can be used to set a default bounding box (e.g. to the bounding box of the refering image data)
    void setBoundingBox(const McBox3f& box);

    /// Computes the bounding box of the spatial graph (ignoring the transform).
    void getBoundingBox(float bbox[6]) const;

    /// Computes the bounding box of the spatial graph taking the transform into account.
    void getBoundingBoxAfterTransform(float bbox[6]) const;

    /// Computes the bounding box of a selected subgraph of the spatial graph.
    McBox3f getBoundingBoxOfSelection(const SpatialGraphSelection& sel) const;

    /// Applies the current transformation matrix to all vertices and edge points of the spatialGraph and resets the transformation.
    void applyTransform();

    /// Get a read-only interface for the spatialGraph
    HxSpatialGraphInterface* getSpatialGraphInterface() const;

    /// Do a consistency check on the spatialGraph
    bool isConsistent() const;

    /** Encode a data set together with its location as a setId for getRangeSet().
        For location VERTEX, set is the index of the corresponding vertex
        attribute.  EDGE and POINT locations share the saem index space,
        starting with edge attributes.  For example, if you have 2 edge
        attributes and 2 point attributes, set=3 refers to the first point
        attribute.
      */
    static int encodeCurrentSetWithLocation(int set, Location location) {
        return 4*set + int(location);
    };

    //////////////////////// I/O methods ///////////////////////////

    ///// Read a spatialGraph from an AmiraMesh struct and adds it to the object pool.
    static int readAmiraMesh(AmiraMesh* m, const char* filename);

    ///// Do the actual reading from the amiraMesh object and create a spatialGraph
    static HxSpatialGraph* readAmiraMeshToSpatialGraph(AmiraMesh* m, const char* filename);

    ///// Writes the spatialGraph into an AmiraMesh file.
    int saveAmiraMesh(const char* filename);

    ///// Save spatialGraph as binary amiraMesh file
    static int saveAmiraMeshBinary(HxSpatialGraph *graph, const char* filename);

    ///// Save spatialGraph as ascii amiraMesh file
    static int saveAmiraMeshASCII(HxSpatialGraph *graph, const char* filename);

    //////////////////////// Connectivity-related searches on the spatialgraph //////////////////

    /// Returns the connected component (set of connected edges and vertices) of which \a vertexNum is part
    SpatialGraphSelection getConnectedComponent(const int vertexNum) const;

    /// Returns a list of all connected components which have a vertex/edge in \a sel.
    McDArray <SpatialGraphSelection> getAllConnectedComponents(const SpatialGraphSelection& sel) const;

    /// Returns selection containing all connected components which have a vertex/edge in \a sel.
    SpatialGraphSelection getConnectedComponentFromSelection(const SpatialGraphSelection& sel) const;

    /// Returns the number of connected components which have a vertex/edge in \a sel.
    int getNumComponentsInSelection(const SpatialGraphSelection& sel) const;

    /// Returns the connected components all entirely in \a sel, combined in a
    /// single selection.
    SpatialGraphSelection getConnectedComponentsContainedInSelection(const SpatialGraphSelection& sel) const;

    /// Returns a selection containing a subtree including the starting edge \a edgeId plus its vertices.
    /// If \a downStream is set to \a false which is the default all up stream nodes and segments
    /// starting at \a edgeId up to the leaves of the tree will be included (rank(incidentEdges) > rank(currentEdge).
    /// Otherwise if \a downStream is set to \a true all nodes and segments on the shortest path
    ///  starting with \a edgeId back to the root will be included (rank(incidentEdges) < rank(currentEdge).
    /// This operation requires a valid ranked graph (in particular the \a Ranks label edge attribute has to exist),
    /// otherwise an empty selection will be returned.
    SpatialGraphSelection getSubTreeByEdge(const int edgeId, bool downStream = false) const;

    /// Convenience function in order to select a subtree by specifying a vertex \a vertexId instead of an edge.
    /// see getSubTreeByEdge
    SpatialGraphSelection getSubTreeByVertex(const int vertexId, bool downStream = false) const;

    /// Calculates the shortest path from a \a startVertex to an \a endVertex, returning a selection containing
    /// all edges and vertices on the path.
    /// Returns an empty selection if no path exists.
    SpatialGraphSelection getShortestPath(const int startVertex, const int stopVertex) const;

    /////////////// Edge related methods //////////////////////////

    /// Adds an edge from the vertex with index \a source to \a target. Returns the edge number of the new edge.
    int addEdge(const int source, const int target);
    int addEdge(const int source, const int target, const McDArray<McVec3f>& edgePoints);
    bool hasEdge(const int source, const int target) const;
    void removeEdge(const int edgeNum);
    void removeMultipleEdges(McDArray<int>& edgeNums);

    int getEdgeSource(const int edgeNum) const;
    int getEdgeTarget(const int edgeNum) const;

    /// Set source vertex of edge \a edgeNum.
    /// The first edge point on the edge is updated to match the vertex coordinates
    void setEdgeSource(const int edgeNum, const int newSourceVertex);

    /// Set target vertex of edge \a edgeNum.
    /// The last edge point on the edge is updated to match the vertex coordinates
    void setEdgeTarget(const int edgeNum, const int newTargetVertex);

    /// Returns the number of points on the edge \a edgeNum.
    int getNumEdgePoints(const int edgeNum) const;

    /// Returns the total number of edge points on the graph
    int getTotalNumEdgePoints() const;

    /// Returns a reference to the points array of edge \a edgeNum
    const McVec3f* getEdgePoints(const int edgeNum, int& numPoints) const;
    McDArray<McVec3f> getEdgePoints(const int edgeNum) const;
    McVec3f getEdgePoint(const int edgeNum, const int pointNum) const;

    /// Sets the points for edge \a edgeNum. This method resizes the edgePointData array appropriately.
    void setEdgePoints(const int edgeNum, const McDArray<McVec3f>& points);

    /// Insert the edge points \a points into edge \a edgeNum before \a beforePoint
    void insertEdgePoints(const int edgeNum, const int beforePoint, const McDArray<McVec3f>& points);

    /** Remove \a numValues points from edge \a edgeNum, starting from \a
     *  firstIndexToDelete.
     *  \a firstIndexToDelete + \a numValues must not exceed the number of
     *  points on edge \a edgeNum.
     */
    void removeEdgePoints(const int edgeNum,
                          const int firstIndexToDelete,
                          const int numValues);

    /////////////// Vertex related methods ///////////////////////////

    /// Adds a vertex and returns the vertex number of the new vertex
    int addVertex(const McVec3f coords);
    void removeVertex(const int vertexNum);
    void removeMultipleVertices(McDArray<int>& vertexNums);

    /// Get/set the coordinate of vertex \a vertexNum
    McVec3f getVertexCoords(const int vertexNum) const;
    const McVec3f * getVertices(const int vertexNum) const;
    void setVertexCoords(const int vertexNum, const McVec3f coords);

     /**
     *  Get the number of attributes for a specific location.
     *
     *  \param location     Location where to evaluate the number of available attributes
     *
     *  \return             number of attributes stored for this location
     */
    int numAttributes(Location loc) const;

    GraphAttribute* attribute(Location location, int i) const;

    GraphAttribute* findAttribute(Location location, const char* attributeName) const;
    EdgeVertexAttribute* findEdgeAttribute(const char* attributeName) const;
    EdgeVertexAttribute* findVertexAttribute(const char* attributeName) const;
    PointAttribute* findEdgePointAttribute(const char* attributeName) const;

    /** 
     *  Adds attribute to the graph. If an attribute with the same name already exists
     *  and the primeType and nDataVar are the same, then the function returns the existing attribute. 
     *  If an attribute with the same name already exists but the primeType or the nDataVar are not 
     *  identically, then the existing attribute is deleted and a new attribute is created.
     *
     *  \param name      The name of the attribute
     *  \param location  The location where to add
     *  \param primType  Currently only mc_float and mc_int32 are supported
     *  \param nDataVar  Number of data variables per element
     *
     *  \return          The attribute.
     */
    GraphAttribute* addAttribute(const char* name, Location location, McPrimType primType, int nDataVar);
    

    /**
     *  Deletes attribute from the graph
     *
     *  \param loc     The location from where to delete
     *  \param iAttribute Attribute index to delete
     *
     */
    void deleteAttribute(Location loc, int iAttribute);

    /**
     *  Deletes attribute from the graph
     *
     *  \param attribute Attribute to delete
     *
     */
    void deleteAttribute(GraphAttribute *attribute);

    // set all attribute values for edge \a edgeNum
    void setEdgeAttributeValues(const int edgeNum, const McDArray<McTypedElement>& values);
    // set all point attribute values for edge \a edgeNum. values[i][j]: i=attribute number, j=point number
    void setPointAttributeValues(const int edgeNum, const McDArray<McTypedData2D>& values);

    /** This method creates a new ParamBundle named \a name and inserts it into the HxSpatialGraph::parameters object.
     *  It also creates a new HierarchicalLabels object to manage the labelGroup and inserts the name and the
     *  HierarchicalLabels object into the \a mLabelGroups table.
     *  The label attribute on points is only created when \a onPoints is true and
     *  there is no attribute with the same name defined on vertices and/or edges. */
    HierarchicalLabels* addNewLabelGroup(const char* name, const bool onEdge, const bool onVertex, const bool onPoint=false);

    /** This method creates a new HierarchicalLabels object managing an existing parameterbundle \a pBundle.
     *  It inserts the new object in the \a mLabelGroups table and return a pointer to it. */
    HierarchicalLabels* addExistingLabelGroup(HxParamBundle* pBundle);

    void addLabelGroup(HierarchicalLabels* hierarchicalLabels);

    /// Swaps labelgroup \a srcLblGrpName with labelgroup \a dstLblGrpName.
    /// This operation is persistent, thus the graph will be touched.
    bool relocateLabelGroup(const char* srcLblGrpName, const char* dstLblGrpName);

    // Swaps label with id \a src and label with id \a dst of labelGroup \a lblGrpName.
    /// This operation is persistent, thus the graph will be touched.
    bool relocateLabel(const char* lblGrpName, int src, int dst);

    /// delete label group and the corresponding attribute
    /// for graph labels both vertex/edge attributes will be removed
    void deleteLabelGroup(const char* name);

    /** Returns whether the attribute \a attrib has labels associated with it. */
    bool hasLabel(const GraphAttribute *attrib) const;

    /** Returns the total number of labels within the label group associated with \a attrib. */
    int  getNumLabels(const GraphAttribute *attrib) const;

    /** Gets the name of the label with id \a value. */
    bool getLabelName(const GraphAttribute *attrib, int value, McString &name) const;

    /** Gets the color of the label with id \a value. */
    bool getLabelColor(const GraphAttribute *attrib, int value, SbColor &color) const;

    /** Sets the color of the label with id \a value. */
    bool setLabelColor(const GraphAttribute *attrib, int value, const McColor& color);

    int getMaxLabelId(const GraphAttribute* attrib) const;

    int getLabelId(const GraphAttribute* attrib, const McString& labelName) const;

    /** Adds a label with name \a labelName to the labelGroup with name \a attributeName.
     *  The label is added as a child of the label with id \a parentId.
     *  The color associated with the label is \a color.
     *  This method returns the label id of the new label (-1 when an error occurred). */
    int addLabel(const char* attributeName, const int parentId, const char* labelName, SbColor color);

    HierarchicalLabels* getLabelGroup(const GraphAttribute *attrib) const;
    HierarchicalLabels* getLabelGroup(const char* name) const;
    LabelGroups& getLabelGroups() { return mLabelGroups; }

    /// change labelgroup name and name(s) of attribute(s) plus update the hashtable
    void changeLabelGroupName(HierarchicalLabels* labelGroup, const char* labelGroupName);

    virtual McString getLoggingInfo();

protected:

    /// insert a single edge, including edge point coordinates, edge attributes and point attributes
    void insertEdge(
        const int edgeNum,
        const SpatialGraphEdge edge,
        const McDArray<McVec3f>& edgePoints,
        const McDArray<McTypedElement>& edgeAttributeValues,
        const McDArray<int>& edgeAttribId,
        const McDArray<McTypedData2D>& pointAttributeValues,
        const McDArray<int>& pointAttribId
    );

    /* insert the edges in \a edgeList such that after this operation, these edges can be found at indices \a edgeNums
     * edgeAttributeValues[i] are the values of edgeAttribute i for all edges in the edgeList
     * pointAttributeValues[i][j]: i=attributeNum, j=edgeNum
     */
    void insertMultipleEdges(
        const McDArray<int>& edgeNums,
        const McDArray<SpatialGraphEdge>& edgeList,
        const McDArray<McDArray<McVec3f> >& edgePoints,
        const McDArray<McTypedData2D>& edgeAttributeValues,
        const McDArray<int>& edgeAttribId,
        const McDArray<McDArray<McTypedData2D> >& pointAttributeValues,
        const McDArray<int>& pointAttribId
    );

    /** Insert a single vertex, including vertex coordinates and vertex attributes.
     *  \a vertexNum is the index of the vertex after insertion.
     *  When \a vertexNum equals the number of current number of vertices, the
     *  new vertex is appended at the end of the vertex list. Otherwise, it is
     *  inserted at position \a vertexNum.
     *  This method is thus the complement of \a removeVertex().
     */
    void insertVertex(
        const int vertexNum,
        const McVec3f vertexCoords,
        const McDArray<McTypedElement>& vertexAttributeValues,
        const McDArray<int> vertexAttribId
    );

    /** insert vertices with coordinates \a vertexCoords, such that after this operation, these vertices can be found at indices \a vertexNums
     *  VertexAttributeValues[i] are the values of vertexAttribute i for all new vertices
     */
    void insertMultipleVertices(
        const McDArray<int>& vertexNums,
        const McDArray<McVec3f>& vertexCoords,
        const McDArray<McTypedData2D>& vertexAttributeValues,
        const McDArray<int>& vertexAttribId // ids of attributes in order to match.
    );

    SpatialGraphEdge getEdge(const int edgeNum);

    /// Show info about data set.
    virtual void info();

    /// do the actual saving of the spatialGraph
    static int saveAmiraMeshInternal(HxSpatialGraph *graph, const char* filename, int ascii);

    // this is for backward compatibility (files that have been created before Amira 5.0)
    static HxSpatialGraph* readLegacyAmiraMeshToSpatialGraph(AmiraMesh* m, const char* filename);
    static int assignLabelIds(HxParamBundle* pb, const int value);
    static bool assignChildLabelId(HxParamBundle* parent, const char* childName, const int childId);

    void computeBoundingBox(float bbox[6], const bool useTransform) const;

    McDArray<McVec3f>           vertices;           ///!< List of all vertices
    McDArray<SpatialGraphEdge>  edges;              ///!< List of all edges
    McDArray<IncidenceList>     incidentEdges;      ///!< For each vertex a list of indices into edges array
    EdgePointsManager           mEdgePointsManager; ///!< This object manages the edge point coordinates

    // the actual data for each location
    McDArray<McHandle<EdgeVertexAttribute> >       mVertexAttributes;
    McDArray<McHandle<EdgeVertexAttribute> >       mEdgeAttributes;
    McDArray<McHandle<PointAttribute> >            mPointAttributes;

    /// Read-only interface for HxSpatialGraph
    HxSpatialGraphInterface* iface;

    /// Searches the graph starting from vertex \a vertexNum and adds all connected edges and vertices to \a selection
    void depthFirstSearch(const int vertexNum, SpatialGraphSelection& selection) const;

    /// Searches the graph starting from vertex \a vertexNum and adds all edges and vertices
    /// with \a rank of rank(incidentEdges) > rank(currentEdge) if \a searchDir is \a false
    /// otherwise with rank(incidentEdges) < rank(currentEdge) to a given \a selection.
    /// This operation requires a valid ranked graph (in particular the \a Ranks label edge attribute has to exist),
    /// otherwise an empty selection will be returned.
    void depthFirstSearch( const int vertexNum
                         , const int rank
                         , const EdgeVertexAttribute &rankAttrib
                         , SpatialGraphSelection& selection
                         , const bool searchDir = false ) const;

    /// Calculates the shortest path from a \a startVertex to an \a endVertex and adds all edges and vertices on
    /// the path to a given \a selection.
    /// Returns true if a path exists otherwise false.
    bool breadthFirstSearch(const int startVertex, const int endVertex, SpatialGraphSelection &selection) const;

    void printIncidentEdges();
    void printEdges();

    /// Table containing a mapping from attribute names to labelGroups. For each attribute representing labels,
    /// there should be an entry in the table.
    LabelGroups mLabelGroups;

    // initial/default bounding box
    McBox3f mDefaultBoundingBox;
    bool mUseDefaultBoundingBox;

    HxRangeSetDataImpl mRangeSetData;
};

#endif

/// @}

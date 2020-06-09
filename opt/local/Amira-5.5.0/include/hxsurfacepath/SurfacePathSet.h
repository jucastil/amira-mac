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
#ifndef _SURFACE_PATH_SET_H
#define _SURFACE_PATH_SET_H

#include "hxsurfacepathAPI.h"
#include "SurfaceNode.h"
#include "SurfaceNodeFactory.h"
#include <hxcore/HxMessage.h>
#include <mclib/McHandle.h>
#include <mclib/McBox3f.h>

class Surface;
class PathConnector;

/** This class implements a data structure representing a path on a
    surface.  Such a path consists of @c SurfaceNodes that form a 
    @c SurfacePathSet::SurfacePath.  A SurfacePathSet is a set of such
    paths.
*/
class HXSURFACEPATH_API SurfacePathSet {

public:
    
    /// Constructor.
    SurfacePathSet() : nFactory(0) {}

    /// Destructor.
    ~SurfacePathSet() {}

    /*********************** Subclasses ***********************/

    /// Subclass representing a single path.
    class SurfacePath {
    public:
        /** Indices to vertex coordinates.
 
            These indices refer to SurfacePathSet::nodes.  For closed
            lines the first index should be duplicated at the end.
        */
        McDArray<int> nodes;

        /// Assignment operator.
        SurfacePath& operator=(const SurfacePath& path)
        {
            nodes = path.nodes;
            return *this;
        }

        /// Returns true if path is closed, false otherwise.
        bool isClosed() const { 
            if ( nodes.size()<2 )
                return false;
            return (nodes[0]==nodes.last());
        }

        /// Destructor.
        ~SurfacePath() { nodes.resize(0); }
    };

    /** This class implements functionality to compute the length of a
        path and stores the respective information in member variables.
     */
    class PathLength : public McHandable
    {
    private:

        /// Length of this path.
        float length;

        /// Reference to the path set which the path belongs to.
        SurfacePathSet* pathSet;

        /// Index of the path for which the length should be computed.
        int path;

        /// The nodes of the path.
        McDArray<int> nodes;

    public:

        /// Constructor.
        PathLength(SurfacePathSet* ps,int tPath)
        {
            length  = -1;
            path    = tPath;
            pathSet = ps;
            
            assert(pathSet);
            assert(tPath>-1&&tPath<pathSet->paths.size());
            
            nodes = pathSet->paths[path].nodes;
        }

        /** Compares two path lengths (ascending).

            If the length of @c elem1 is smaller than the length of @c
            elem2 then -1 will be returned, 1 otherwise.
        */
        static int compareEuclideanLength(const McHandle<PathLength> & elem1, 
                                          const McHandle<PathLength> & elem2)
        {
            if ( elem1->getLength() < elem2->getLength() )
                return -1;
            return 1;
        };

        /// Computes and returns length of this path.
        float getLength()
        {
            if ( length == -1 )
            {
                length = pathSet->getPathLength(path);
            }
            return length;
        }

        /// Returns the nodes of the path.
        McDArray<int> & getNodes() { return nodes; }
    };

    /// SurfaceNode whose index points into the SurfacePathSet::nodes array.
    class IndexedSurfaceNode : public McHandable
    {

    public: 
        
        /// Constructor.
        IndexedSurfaceNode(McHandle<SurfaceNode>n,
                           int ind,
                           int iD) : 
              mNode(n)
            , mIndex(ind)
            , mID(iD)
        {
            mcrequire(mID!=-1&&"IndexedSurfaceNode:mID may not be -1!");
        }

        /// Returns triangle index of surface if @c mNode lies inside
        /// a triangle.
        int triangle() { return mNode->triangle(); }

        /// Returns edge index of surface if @c mNode lies on an edge.
        int edge()     { return mNode->edge(); }

        /// Returns vertex index of surface if @c mNode lies on a vertex.
        int vertex()   { return mNode->vertex(); }

        /// Returns index of node.
        int getIndex() { return mIndex; }

        /// Returns an identifier different to the index.
        int getIdentifier() { return mID; }

        /// Returns the 3d coords of the node.
        McVec3f point()     { return mNode->point(); }

        /// Returns the node itself.
        McHandle<SurfaceNode> & getNode() { return mNode; }

    private:
        // Reference to node.
        McHandle<SurfaceNode> mNode;

        // Index of node.
        int mIndex;
        
        // Identifier of node.
        int mID;
    };

    // Comparator for IndexedSurfaceNode, which compares the nodes'
    // identifiers.
    static int compareID(const McHandle<IndexedSurfaceNode> & node1,
                         const McHandle<IndexedSurfaceNode> & node2)
    {
        if ( node1->getIdentifier() < node2->getIdentifier() )
            return -1;
        return 1;
    }
    
    /************************** Data **************************/

    /// The paths of the path set.
    McDArray<SurfacePath> paths;

    /// All nodes of the path set, stored per path.
    McDArray< McHandle<SurfaceNode> > nodes;
    
    /// Surface node factory, which creates new nodes.
    SurfaceNodeFactory nFactory;

    /*********************** Const Functions ***********************/

    /// Const index operator to single path.
    const SurfacePath& operator[](int index) const;

    /// Returns pointer to vertex coordinates.
    McVec3f* getCoords() const { 
        return const_cast<McVec3f*>(coords.dataPtr());
    }

    /// Returns pointer to node with @c index.
    SurfaceNode* getNode(int index) const;

    /// Returns the index of the given node in the node array.
    int getNodeIndex(SurfaceNode* node) const;

    /// Returns the index of node in the nodes array, which is on
    /// position \p node of \p path.
    int getNodeIndex(int path, int node) const;

    /// Returns the index of the given node in the path nodes array.
    int getPathNodeIndex(int path, SurfaceNode * node) const;
    
    /** Is every node in the object referred to by @c theOwner a
        vertex-node?
        
        Returns false if there exists a non-vertex-node currently
        referenced in SurfacePathSet, and true if all nodes are
        vertex-nodes.
    */
    bool isPureSurfaceVertexPath() const;

    /** Returns the index of the surface vertex for path \p path and
        node \p node, if path is purely vertex-path.
        
        \return surface-vertexId for \p path's \p nodes' node\n
                -1 is surface is null\n
                -2 if \p path is out of bounds\n
                -3 if \p node is out of bounds
    */
    int vertex(int path, int node) const;

    /** Gets the path given in argument \p path as an array of path
        nodes.

        \return true if path exists, false otherwise. 
        \param[in]  Index of path for which path nodes are returned.
        \param[out] Array of path nodes on @c path.  The path nodes
                    are appended to the @c pathData array.
        
        An empty array is returned in case surface attached to
        SurfacePathSet is null or \p path is out of bounds
    */
    bool getPath(int path, McDArray<int> & pathData) const;

    /// Returns the path given in argument \p path as an array of
    /// surface nodes.
    bool getSurfNodePath(int path,
                         McDArray< McHandle<SurfaceNode> > & pathData) const;
    
    /// Returns node of given path.
    SurfaceNode* getSurfaceNode(int path, int node) const;

    /// Returns pointer to surface the path is defined on.
    Surface* getSurface() const;
	
    /// Checks whether paths match surface.  Returns index of first
    /// inconsistent node.
    bool isConsistent(bool verbose = true, int* badNode = 0) const;

    /// Returns number of control points on given path.
    int getNumControlPointsOnPath(int path) const;

    /// Checks whether path is closed.
    bool isPathClosed(int path) const;

    /// Checks whether path set contains any paths.
    bool isEmpty() const;

    /// Checks whether path with index @c path is empty.
    bool isPathEmpty(int path) const;

    /// Returns the index of the first occurrence of @c node in @c
    /// path, -1 otherwise.
    int getFirstNodeIndexOnPath(int path, int node) const;

    /// Returns the number of nodes on @c path.
    int getNumNodesOnPath(int path) const;

    /// Returns the number of control points (CP) on path before
    /// control point @c cp.  Returns -1 if cp not on path.
    int getCPIndexOnPath(int cp, int path) const;

    /// Returns the node index in the path nodes array of the control
    /// point with index @c cpIdx.
    int getIndexOfIthCP(int cpIdx, int path) const;

    /// Returns the index of the path that contains the node with
    /// index @c nodeIndex.
    int getPathForNode(int nodeIndex) const;

    /// Returns path length.
    float getPathLength(int path) const;

    /// Returns total number of path nodes.
    int getNumNodes(void) const { return nodes.size(); }

    /// Returns total number of paths.
    int getNumPaths(void) const { return paths.size(); }

    /// Returns last node on given path.
    SurfaceNode* getLastSurfaceNode(int path) const;

    /// Returns index of previous editable control point in path.
    int getPrevControlPoint(int path, int idx) const;

    /// Returns index of next editable control point in path.
    int getNextControlPoint(int path, int idx) const;

    /// Returns the number of control points in the SurfacePathSet.
    int getNumControlPoints() const;

    /// Computes tangent at path node (always points along path
    /// indexing).
    void getTangent(int path, int idx, McVec3f& tangent) const;

    /// Returns index of node @c nodeIdx in the path nodes array of 
    /// @c path.
    int getNodeIndexOnPath(int path, int nodeIdx) const;

    /// Returns the number of paths, a node belongs to.
    int getNumPathsForNode(int nodeIdx) const;
    
    /// Returns number of entangled nodes.
    int getNumEntangledNodes() const;

    /// Computes bounding box from coordinates.
    void boundingBox(McBox3f& bb) const;

    /// Returns true if index @c nodeIdx in paths.nodes array is an
    /// inner node, meaning it is not a first and nor a last idx.
    bool isInnerPathNodeIdx(int pathNodeIdx, int path ) const;

    /// Returns true if index @c nodeIdx in nodes array is an
    /// inner node, meaning it is not a first and nor a last idx.
    bool isInnerNodeIdx(int nodeIdx, int path ) const;

    /** Collects all paths that contain given node, and an array with
        pathnodeIdx.

        - get all paths that containing node with nodeIdx
        - all pathIdx are returned in pathsCN
        - the idx in path, where the containing node will be find is stored
          in idxInPaths on corresponding idx
        - regard that the same pathIdx can be in pathsCN more than once
          if containing node is in path more than once
    */
    void getAllPathsContainingNode(int nodeIdx,
                                   McDArray<int> & pathsCN,
                                   McDArray<int> & idxInPaths) const;
    
    /// Collects all paths that contain given node.
    void getAllPathsContainingNode(int nodeIdx,
                                   McDArray<int> & pathsCN) const;

    /// Collects all paths that contain given node but not at first or
    /// last index.
    void getAllPathsContainingInnerNode(int nodeIdx,
                                        McDArray<int> & pathsCN) const;

    /// Collects all inner nodes of path @c pathIdx that are also
    /// contained in other paths.
    void getInnerPathNodesIdxAlsoInOtherPaths(int pathIdx,
                                              McDArray<int> & allNodesThatAreAlsoInOtherPAths) const;

    /// Collects all paths that are entangled, but not paths that are
    /// only entangled on first or last point.
    void getAllInnerEntangledPaths(McDArray<int> & allInnerEntagelPaths) const;

    /// Collect all paths that are entangled
    void getAllEntangledPaths(McDArray<int> & allEntagelPaths) const;
    
    bool getInnerCrossedNodeIdxOfPath(int pathIdx,
                                      McDArray<int> & allInnerNodeIdx,
                                      float mTol) const;

    /// Collects all paths that are crossed from other paths
    /// (crossings at first or last point noticed if one of the
    /// crossings is inner).
    bool getInnerCrossedPaths(McDArray<int> & allInnerEntagelPaths,
                              float mTol=1.e-3) const;

    /// Collects all paths that are crossed from other paths
    /// (crossings at first or last point are noticed).
    bool getCrossedPaths(McDArray<int> & allEntagelPaths,
                         float mTol=1.e-3) const;

    /*********************** Non-const Functions ***********************/

    /// Clears the path-array.
    void clear() { this->paths.resize(0); }

    /// Removes unused points or empty lines.
    void cleanup();

    /// Checks for duplicate points.
    int removeDuplicateNodes(float tol=1.e-6,
                             int mode=SurfaceNodeFactory::BARY_TOL);

    /// Removes interior triangle and duplicate edge/vertex
    /// nodes.  Control Points will be kept if /p removeControlPoints
    /// is set (default).
    int removeInteriorNodes(int pathIdx, 
                            int removeControlPoints = 1);

    /// Copy data, possibly attach to new surface (yet with same
    /// connectivity!)
    void copyData(const SurfacePathSet& other, 
                  Surface* surface=0);

    /// Collapses shared pathnodes to single node.
    void untangle(void);
    
    /// Multiply shared pathnodes.
    void untangle(const McDArray<int> & selectedPaths);
    
    /// Parses contours from @p surface and creates a corresponding
    /// vertex pathset.
    void importContours(Surface* surface);

    /// Changes pointer to surface for all nodes.
    void setSurface(Surface* surface);

    /** Adds a new path to the path set. The path consists of @c n
        points.  @c points specifies the index of each point in the
        global node array. @c pos specifies the index of the new
        path. If @c pos is -1 the new path will be appended after all
        existing paths.
    */
    void addPath(int n, int* whichPoints, int pos=-1)
    {
        SurfacePath path;
        path.nodes.resize(n);

        for ( int i=0; i<n; i++ )
            path.nodes[i] = whichPoints[i];
        if ( pos == -1 )
            paths.append(path);
        else
            paths.insert(pos,path);
    }

    /// Deletes @c vertex of @c path.
    void removePathVertex(int p, int vertex)
    {
        if ( p < paths.size() )
            if ( vertex < paths[p].nodes.size() )
                paths[p].nodes.remove(vertex);
    }

    /** Adds an additional vertex to path @c p. The second argument 
        @c v is the index of the referenced point. @c pos specifies the
        position of the new vertex within the path. If @c pos is -1
        the new vertex will be appended after all other vertices of
        the path.
    */
    void addPathVertex(int p, int v, int pos=-1)
    {
        if ( p < paths.size() && v < nodes.size() )
        {
            if ( pos == -1 )
                paths[p].nodes.append(v);
            else
                paths[p].nodes.insert(pos,v);
        }
    }

    /// Index operator to single path.
    SurfacePath& operator[](int index);

    /// Assignment operator.
    SurfacePathSet& operator=(const SurfacePathSet& other)
    {
        this->copyData(other);
        return *this;
    }    
    
    /// Rotates closed path so that idx becomes 0.
    void rotateClosedPath(int path, int idx);

    /** This Method removes all nodes from a path between pathIndex1
        and pathIndex2, regardless of whether they are controlPoints,
        or not. Nodes are removed forward, so, if the pathIndex2 is
        smaller that pathIndex1, all nodes after pathIndex1 and all
        before pathIndex2 are deleted This method will leave the path
        afterwards as is and therefore the path is likely to be
        inconsistent.
    */
    bool removeIntermediateNodesFromPath(int pathID,
                                         int pathIndex1,
                                         int pathIndex2);
    
    /** This method computes a path between the node on @p index1 and
        @p index2 on the path and inserts the found nodes after index1
        on the path.  It does not check for consistency and does not
        delete any intermediate nodes, if any.  If index1 is the last
        index on the path, than the path lacks a last ControlPoint.
        
        Returns true on success, false on failure
    */
    bool connectSurfaceNodes(int pathId, int index1, int index2,
                             PathConnector* connector);
    
    /** Create path from given vertex chain.
        
        The function does not unnecessarily create new nodes, surface-
        and control-point-properties are modified if needed.  Note
        that no consistency check is being performed.
        
        \param vertices contains the surface-vertices to be included.
    */
    void makePath(Surface* surface, McDArray<int> & vertices);

    /** Adds new vertex to given path.
        
        \return 1 if operation was successfull\n 
                0 if surface is null\n
               -1 if vertex is out of bounds\n
               -2 if path is out of bounds
    */
    int addVertexToPath(Surface* surface,
                        int vertex, int path,
                        bool isControlPoint);

    /// Removes paths that consists of only one node.
    void  removeStandAloneNodes();

    /// Sorts paths according to their euclidean length in ascending
    /// order.
    void sortPathsByLength();

    /// Update 3d coordinates.
    void updateCoords();

protected:
    
    /// Checks if @p word1 is contained as a subsequence in @p word2.
    static bool isSubArray(const McDArray<int> & word1, 
                           const McDArray<int> & word2);

    /** Computes the prefix for the KMP-matching-algorithm used in
        isSubArray().  @p word is the array the prefix-array @p pi is
        calculated for.
    */
    static void compute_prefix(const McDArray <int> & word,
                               McDArray<int> & pi);
    
    /** Shows self-intersections in the following manner: anywhere
        where path-segments begin or end to self-intersect, a split
        position is appended at the end of @p splitPositions.
    
        Note that @c is NOT modified by this operation, only the
        second argument is filled with split-nodes.
    
        \param splitPositions are the split-nodes for @p path, where
        each entry denotes a position in the corresponding paths-array
        (SurfacePathSet::SurfacePath::nodes).
    */
    void getSelfIntersections(int path, McDArray<int> & splitPositions);

    McDArray<McVec3f> coords; 
};

#endif // _SURFACE_PATH_SET_H

/// @}

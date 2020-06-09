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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_IGRAPH_H
#define MOLCHEM_IGRAPH_H

#include "MolChemWinDLLApi.h"

class McBitfield;
template <class T> class McDArray;
template <class T> class McDMatrix;
template <class T> class McGeneralTree;

namespace molchem {
    class INode;
    class IEdge;
    class IGraph;
    class Logger;
    template <class T> class IteratorBase;
    template <class T> class IteratorBaseGraphTraversal;

    /** \brief Abstract edge of an undirected graph.
    
        An edge knows the two nodes that it connects and its index in the graph data structure.
    */

    class MOLCHEM_API IEdge {
    public:
        virtual ~IEdge() {}
        // ---------------------- abstract interface -----------------------

        /** Returns the first node connected by the edge. Order is undefined.*/
        virtual INode* getNode1() const = 0;
        /** Returns the second node connected by the edge. Order is undefined.*/
        virtual INode* getNode2() const = 0;
        /** Returns index of edge in graph.*/
        virtual int getIx() const = 0;

       // -------------------------------------------------------------------
 
        /** Returns the neighbour of node n that is connected via this edge.
            0 if there is none. */
        INode* getNeighbor(const INode* n) const;

        /** Returns iterator over all edges directly connected to this edge.*/
        IteratorBase<IEdge>* getNeighborEdgeIterator() const;

        /** Returns node common to this edge and the edge e. 0 if there is none. */
        INode* isConnected(const IEdge* e) const;

    private:
        static Logger* logger;

    };

    /** \brief Abstract node of an undirected graph.
    
        A node knows its incident edges and its index in the graph data structure.
    */

    class MOLCHEM_API INode {
    public:
        virtual ~INode() {}    
        // ---------------------- abstract interface -----------------------

        /** Returns number of edges. */
        virtual int getNumEdges() const = 0;

        /** Returns i'th edge.*/
        virtual IEdge* getEdge(int i) const = 0;

        /** Returns index of node in molecule. */
        virtual int getIx() const = 0;

        // -------------------------------------------------------------------
       
        /** Returns the i'th neighbor.*/
        INode* getNeighbor(int i) const;

        /** Returns degree, if restricted to node subgraph */
        int getNumEdges(const McBitfield& bf) const;

        /** Returns edge that connects this node to node n. 0 if they are not neighbors. */
        IEdge* isNeighbor(const INode* n) const;

        /** Returns iterator over all edges.*/
        IteratorBase<IEdge>* getEdgeIterator() const;

        /** Returns container with all edges.*/
        void getEdges(McDArray<IEdge*>& edges) const;

        /** Returns container with all edges which connect to an node in the subgraph.*/
        void getEdges(McDArray<IEdge*>& edges,const McBitfield& mask) const;
        
        /** Returns container with all neighbors.*/
        void getNeighbors(McDArray<INode*>& nodes) const;
        
        /** Returns container with all neighbors which are in the given subgraph.*/
        void getNeighbors(McDArray<INode*>& nodes,const McBitfield& mask) const;
        
        /** Returns iterator over all neighbors.*/
        IteratorBase<INode>* getNeighborIterator() const;

        /** Returns first node found that is a neighbor of both this node and node n. 0 if there is none. */
        INode* hasCommonNeighbor(const INode* n) const;
    private:
        static Logger* logger;

    };

    /** \brief An abstract undirected simple graph.
        
        Self-loops or multiple indentical edges are not allowed and 
        may lead to incorrect results or crashes.
    
        IGraph is a container for nodes and edges. 
        They can be accessed via continuous indices.
    */


    class MOLCHEM_API IGraph {
    public:
        // ---------------------- abstract interface -----------------------

        /** Returns number of nodes */
        virtual int getNumNodes() const = 0;
        /** Returns number of edges */
        virtual int getNumEdges() const = 0;
        /** Returns ix'th node */
        virtual INode* getNode(int ix) const = 0;
        /** Returns ix'th edge */
        virtual IEdge* getEdge(int ix) const = 0;

        // -------------------------------------------------------------------
        
        void findRings(McDArray<McDArray<int> >& rings,int maxSize) const;
        
        /** Returns iterator which breadth-first traverses the graph starting at at node n.
            If the graph has more than one connection component not all atoms will be visited.
            If the node mask bf is set, iterator will be restricted to subgraph.*/
        IteratorBaseGraphTraversal<INode>* getNodeBreadthFirstIterator(const INode* n,const McBitfield* bf=0) const;
        
        /** Returns iterator which depth-first traverses the container starting at at atom a
            If the graph has more than one connection component not all atoms will be visited.
            If the node mask bf is set, iterator will be restricted to subgraph.*/
        IteratorBaseGraphTraversal<INode>* getNodeDepthFirstIterator(const INode* a,const McBitfield* bf=0) const;

        IteratorBase<INode>* getNodeIterator() const;
        IteratorBase<IEdge>* getEdgeIterator() const;

        IEdge* getEdge(int nix1,int nix2) const;
        /** All-Pairs-Shortest-Path computation based on Floyds algorithm. 
            Produces an nxn matrix A of lengths of shortest
            paths. For diagonal elements the distance will be 0, 
            for unconnected parts it will be INT_MAX */
        void computeShortestPathMatrix(McDMatrix<int> & mat) const;
        /** Return connectivity matrix as bitfield. 
            Connectivity of node with index nIx1 and nIx2 can be accessed via 
            mat[nIx1*getNumNodes()+nIx2] or mat[nIx2*getNumNodes()+nIx1] */
        void getConnectivityMatrix(McBitfield& mat) const;
        /** Generate a spannign tree of the connection component cc.
            The nodes of the tree will contain the atom indices.
            The spannign tree is sorted in order of longest paths.
         -   If cc is not a connection component, only one of the components
            will be returned. startIx defined the index of the root node. If -1
            the first set bit of cc will be used. */
        void getOrderedSpanningTree(const McBitfield& cc, McGeneralTree<int>& g,int startIx=-1) const;
        /** Returns the longest chain of mask. Masked part of molecule must not
            contain cycles but may consist of multiple connection components.*/
        void getLongestChain(const McBitfield& cc,McDArray<INode*>& chain) const;
        /** Returns the longest chain of mask. Masked part of molecule must not
            contain cycles but may consist of multiple connection components.*/
        void getLongestChain(const INode* startINode,const McBitfield& cc,McDArray<INode*>& chain) const;
        /** */
        void getShortestPath(const INode* startINode, const INode* endINode,const McBitfield& cc,McDArray<INode*>& path) const;
        /** \exception Exception*/
        void getShortestPath(const INode* startINode, const INode* endINode,const McDArray<int>& shortestPathArray,McDArray<INode*>& path) const;
        /** Returns the path lengths from each atom to other atoms.  -1 if there is none. 0 for the startINode itself.*/
        void getShortestPathArray(const INode* startINode, const McBitfield& cc,McDArray<int>& lengths) const;
        /** Returns minimum number of cycles O(V+E).*/
        int getFrerejacqueNumber() const;
        /** Returns minimum number of cycles under the assumption that graph is connected (O(1)).*/
        int getFrerejacqueNumberConnected() const;
        /** Returns all connection components */
        void getConnectionComponents(McDArray<McDArray<INode*> >& c) const;
        /** Same as above but resticts the search to atoms in bf */
        void getConnectionComponents(const McBitfield& bf,McDArray<McDArray<INode*> >& c) const;
        int getConnectionComponents(McDArray<int>& c) const;
        /** Returns whether molecule is a connection component O(V+E) */
        bool isConnected(const McBitfield* bf=0) const;
        /** Returns the number of connection components O(V+E) */
        /** Same as above but resticts the search to atoms in bf */
        int getNumConnectionComponents(const McBitfield* bf=0) const;
        /** Grows connection component starting at atom startINode in direction of bond directionIEdge, which must be a
            bond incident to startINodes. Elements will be appended to result, which will not be cleared.
            startINode will be the first element appended element, the remaining elements are appended in breadth first order.

            \exception Exception
        */
        void growConnectionComponent(const INode* startINode, const IEdge* directionIEdge,McDArray<INode*>& result) const;
        /** Returns whether graph is a complete graph. If bf is set, the function is restricted to the given subgraph */
        bool isComplete(const McBitfield* nodebf=0) const; 
        /** Returns whether graph is a cycle. If bf is set, the function is restricted to the given subgraph */
        bool isCycle(const McBitfield* nodebf=0) const; 
        /** Returns regular degree of graph. -1 if the graph is not regular.
            If bf is set, the function is restricted to the given subgraph */
        int getRegularDegree(const McBitfield* nodebf=0) const;
        virtual ~IGraph();
    private:
        static Logger* logger;
    };
    
    /** \brief An undirected simple graph which is editable by the client.
        
        IDynamicGraph extens IGraph by methods to add and remove nodes and edges.
    */    
    class IDynamicGraph : public IGraph {
    public:
        virtual ~IDynamicGraph() {}        
        /** Allocates a new node which is added to the graph. Indices
            of already existant nodes do not change.*/
        virtual INode* newNode() = 0;
        
        /** Allocates and adds to the graph a new edge connecting nodes with index n1 and n2.
            Indices of already existant edges do not change. */
        virtual IEdge* newEdge(int n1,int n2) = 0;
        
        /* Deletes edges as specified by edge bitfield. This may invalidate edge indices.*/
        virtual void deleteEdges(const McBitfield& bf) = 0;
        
        /* Deletes nodes as specified by the node bitield. Also removes all edges incident to these nodes.
           This may invalidate node and edge indices.*/
        virtual void deleteNodes(const McBitfield& bf) = 0;
        
        // -------------------------------------------------------------------
        
        /** Allocates enough memory to accomodate num edges to avoid a large number of reallocs.
            if newEdge is called many times. The default implementation is empty.*/
        virtual void remaxEdges(int num) {};
        
        /** Allocates enough memory to accomodate num nodes to avoid a large number of reallocs
            if newNode is called many times. The default implementation is empty.*/
        virtual void remaxNodes(int num) {};   

        /** Deletes all contained edges and nodes. Must be called by destructor of concrete class. */
        virtual void clear();
       
        static Logger* logger;
    };
}

#endif

/// @}

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
#ifndef MOLCHEM_GRAPH_H
#define MOLCHEM_GRAPH_H
#include "MolChemWinDLLApi.h"

#include "IGraph.h"
#include <mclib/McDArray.h>
#include <mclib/McHandable.h>

namespace molchem {
    class Edge;
    class Node;

    class MOLCHEM_API Edge : public IEdge {
        friend class Graph;
    public:
        virtual ~Edge() {}
        /** Returns the first node connected by the edge. Order is undefined.*/
        virtual INode* getNode1() const;

        /** Returns the second node connected by the edge. Order is undefined.*/
        virtual INode* getNode2() const;

        /** Returns index of edge in graph.*/
        virtual int getIx() const;

    private:
        int ix; 
        Node* a1; 
        Node* a2;
    };

    class MOLCHEM_API Node : public INode {
        friend class Graph;
    public:
        virtual ~Node() {}
        /** Returns number of edges */
        int getNumEdges() const;

        /** Returns i'th edge.*/
        IEdge* getEdge(int i) const;

        /** Returns index of nodes in molecule. */
        int getIx() const;
        
    private:
        int getEdgeIx(const IEdge* e) const;
        McDArray<Edge*> edge;
        int ix;
    };

    /** \brief Factory for nodes and edges. 
    
       An easy way to use your own extended node and
       edge classes is to derive them from Node and Edge and add a class
       derived from GraphFactory that constructs instances.
       The factory has to be given as a parameters in the constructor of the graph. 
       Graph uses the default implementation if no other is set.
    */

    class MOLCHEM_API GraphFactory {
    public:
        virtual ~GraphFactory() {}
        virtual Edge* newEdge() const { return new Edge;}
        virtual Node* newNode() const { return new Node;} 
    };

    class MOLCHEM_API Graph : public IDynamicGraph , public McHandable {
    public:
        using IDynamicGraph::getEdge;
        /** Returns number of nodes
        */
        virtual int getNumNodes() const;
        /** Returns number of edges 
        */
        virtual int getNumEdges() const;

        virtual INode* getNode(int ix) const;

        virtual IEdge* getEdge(int ix) const;

        virtual void remaxEdges(int num);
        virtual void remaxNodes(int num);

        virtual IEdge* newEdge(int nix1,int nix2);
        virtual INode* newNode();

        /** Delete atoms and incident bonds. Iterators may loose validity. */
        virtual void deleteNodes(const McBitfield& nodes);

        /** Delete atoms and incident bonds. Iterators may loose validity.
        Faster than deleting atoms one by one.*/
        virtual void deleteEdges(const McBitfield& edges);

        void setStandardNumEdges(int deg=0);
        //
        int getStandardNumEdges() const;
        /** If no factory is supplied, the default factory GraphFactory will be used. Factory is owned by Graph.*/
        Graph(GraphFactory* factory=0);
        /**  Factory is owned by Graph.*/        
        void setFactory(GraphFactory* fac);
        virtual ~Graph();

    private:
        GraphFactory* factory;
        int standardNumEdges;
        template <class T> void sweepFragmentation(T& t);
        McDArray<Node*> node;
        McDArray<Edge*> edge;
        static Logger* logger;
    };

}
#endif

/// @}

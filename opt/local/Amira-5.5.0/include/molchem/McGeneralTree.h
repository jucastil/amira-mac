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
#ifndef MCGENERALTREE_H
#define MCGENERALTREE_H

#include "MolChemWinDLLApi.h"

#include <stdlib.h>
#include <mclib/McDArray.h>
#include <mclib/McListQueue.h>

/** @c McGeneralTree implements a general tree structure as defined by graph theory.
Unlike McTree which is binary a McTreeGeneral node can have an arbitrary number of subnodes.
Each node of a intree carries a <em> key</em>. inthere are iterators like
McGeneralTreeIBreadthFirst and McGeneralTreeIDepthFirst for traversing
trough a @c McGeneralTree. */

template <class T> class McGeneralTree {
public:

    /** inthe node of a intree.  */

    struct Node{

        /** @name Constructors */
        //@{
        /** Default constructor. Note that @c key is not initialized.
        Consequently, its type should provide a default constructor.
        */
        Node() : p(0) {}

        /// Create new node with specified key.
        Node(const T& key) :  key(key), p(0) {}

        /** Copy constructor. inthe type of @c key should
        define a copy constructor. */
        Node(const Node& o) : key(o.key), p(o.p), childs(o.childs) {}
        //@}

        //@}

        /** @name Members */
        //@{
        /// inthe key of the node.
        T key;
        /// Pointer to parent node.
        Node* p;
        /// Pointer to children nodes.
        McDArray<Node*> childs;


        //@}
    };

    /// Pointer to root of tree.
    Node* root;

    McGeneralTree() : root(NULL) {}
    //@}
    void getLeaves(McDArray<Node*>& leaves) const;

    void getDepth(Node* n) const;

    void getPath(Node* n,McDArray<Node*>& path) const;
    /** Returns size (number of nodes) of tree below (and incl.) n. 
        If n is 0, returns the size of the whole tree. */
    int getTreeSize(const Node* n=0) const;
    int getTreeDepth(const Node* n=0) const;

    McGeneralTree(const McGeneralTree& o) {}
    //@}
    ~McGeneralTree();

private:
    /** @name Constructors */
    //@{

    /** Copy constructor. */
};


template <class T> class McGeneralTreeIteratorDepthFirst {
public:
    McGeneralTreeIteratorDepthFirst(McGeneralTree<T>* t)  {
        toDo.append(t->root);
    }
    McGeneralTreeIteratorDepthFirst(typename McGeneralTree<T>::Node* startNode)  {
        toDo.append(startNode);
    }
    typename McGeneralTree<T>::Node* next(){
        if (toDo.size() == 0)
            return 0;
        typename McGeneralTree<T>::Node* n = toDo.last();
        toDo.removeLast();
        for (unsigned i = n->childs.size(); i--; )
            toDo.append(n->childs[i]);
        return n;
    }
    ~McGeneralTreeIteratorDepthFirst() {};
protected:
    McDArray<typename McGeneralTree<T>::Node*> toDo;
};


template <class T> class  McGeneralTreeIteratorUpstream  {
public:
    McGeneralTreeIteratorUpstream(McGeneralTree<T>* t)  {
        McDArray<typename McGeneralTree<T>::Node*> nodes;
        t->getLeaves(nodes);
        for (int i=0;i<nodes.size();i++)
            toDo.put(nodes[i]);
    }
    typename McGeneralTree<T>::Node* next() {
        if (toDo.isEmpty())
            return 0;
        typename McGeneralTree<T>::Node* n = toDo.get();
        if (n->p && n->p->childs.last()==n) 
            toDo.put(n->p);
        return n;
    }
    ~McGeneralTreeIteratorUpstream() {};
protected:
    McListQueue<typename McGeneralTree<T>::Node*> toDo;
};

template <class T> class  McGeneralTreeIteratorBreadthFirst  {
public:
    McGeneralTreeIteratorBreadthFirst(McGeneralTree<T>* t)  {
        toDo.put(t->root);
        toDo.put(0);
        depth = 0;
    }
    McGeneralTreeIteratorBreadthFirst(typename McGeneralTree<T>::Node* startNode)  {
        toDo.put(startNode);
        toDo.put((typename McGeneralTree<T>::Node*)0);
        depth = 0;
    }
    typename McGeneralTree<T>::Node* next() {
        typename McGeneralTree<T>::Node* n = toDo.get();
        if (n==0) {
            if (toDo.isEmpty())
                return 0;
            depth++;
            n=toDo.get();
            toDo.put((typename McGeneralTree<T>::Node*)0);
        }
        for (int i=0;i<n->childs.size();i++)
            toDo.put(n->childs[i]);
        return n;
    }
    int getDepth() {return depth;}
    ~McGeneralTreeIteratorBreadthFirst() {};
protected:
    int depth;
    McListQueue<typename McGeneralTree<T>::Node*> toDo;
};

template <class T> void McGeneralTree<T>::getLeaves(McDArray<Node*>& leaves) const {
    McGeneralTreeIteratorDepthFirst<T> d((McGeneralTree<T>*)this);
    Node* n;
    while ((n = d.next())) {
        if (n->childs.size() == 0)
            leaves.append(n);
    }
}

template <class T> int McGeneralTree<T>::getTreeSize(const Node* n) const {
    if (!n)
        n = root;
    if (!n)
        return 0;
    int size = 0;
    McGeneralTreeIteratorDepthFirst<T> d(n);
    while ((n = d.next()))
        size++;
    return size;
}


template <class T> int McGeneralTree<T>::getTreeDepth(const Node* n) const {
    if (!n)
        n = root;
    if (!n)
        return 0;
    int depth = 0;
    McGeneralTreeIteratorBreadthFirst<T> d(n);
    while ((n = d.next()))
        if (d.getDepth()>depth) depth = d.getDepth();
    return depth;
}

template <class T> void McGeneralTree<T>::getPath(Node* n,McDArray<Node*>& path) const 
{
    while (n) {
        path.append(n);
        n = n->p;
    }
    path.reverse();
}

template <class T> void McGeneralTree<T>::getDepth(Node* n) const 
{
    int depth = 0;
    while (n->p) {
        n = n->p;
        depth++;
    }
    return depth;
}

template <class T> McGeneralTree<T>::~McGeneralTree() {
    if (!root) return;
    McGeneralTreeIteratorDepthFirst<T> d(this);
    Node* n;
    while ((n = d.next())) {
        delete n;
    }
}



#endif



/// @}

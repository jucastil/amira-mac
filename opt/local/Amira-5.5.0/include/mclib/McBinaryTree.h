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

/// @addtogroup mclib mclib
/// @{
#ifndef __MCBINARYTREE_H
#define __MCBINARYTREE_H

#include "McWinDLLApi.h"
#include "McTree.h"

/** @c McBinaryTree implements the Binary Tree data structure and its
  basic set of operations. Each node of a Binary Tree carries a <em>
  key</em> which is used to specify the sorting criteria. The type
  <em> T</em> of the key should provide useful implementations of the
  following operations:

  @li Default constructor
  @li Copy constructor
  @li Lower-than operator
  @li Not-equal operator
  @li Assignment operator
   */

template <class T>
class McBinaryTree : public McTree<T> {
private:
    /** @name Constructors */
    //@{
    /** Copy constructor. */
    McBinaryTree(const McBinaryTree& o) {}
    //@}
    typedef typename McTree<T>::Node Node;

public:
    /** @name Constructors */
    //@{
    /** Default constructor. Just creates an empty tree. */
    McBinaryTree() { this->_root = NULL; }
    //@}

    /** @name Methods */
    //@{
    /** Insert specified node <em> z</em> into tree. The key of <em> z</em>
        is used to find <em> z</em>'s correct position. Consequently, the type
        of key must provide a useful lower-than operation. */
    void insert(Node* z) {
        Node* y = NULL;
        Node* x = this->_root;
        while (x != NULL) {
            y = x;
            x = (z->key() < x->key() ? x->child() : x->sibling());
        }
        z->p() = y;
        if (y == NULL)
            this->_root = z;
        else {
            if (z->key() < y->key())
                y->child() = z;
            else
                y->sibling() = z;
        }
    }

    void insert(const T& w) { insert(new Node(w)); }

    /** Remove specified node <em> z</em> from tree. Returns a pointer to
        the removed node. It may be necessary to copy the key from one node
        to another. Consequently, the type of the key must provide a useful
        assignment operation.

        <b> <em> WARNING:</b> The given node must belong to this tree,
        otherwise the behavior of this method is undefined !</em>
    */
    Node* remove(Node* z) {
        Node* y;
        if (z->child() == NULL || z->sibling() == NULL)
            y = z;
        else
            y = successor(z);
        Node* x = (y->child() != NULL ? y->child() : y->sibling());
        if (x != NULL) x->p() = y->p();
        if (y->p() == NULL)
            this->_root = x;
        else {
            if (y == y->p()->child())
                y->p()->child() = x;
            else
                y->p()->sibling() = x;
        }
        if (y != z) z->key() = y->key();
        return y;
    }

    /** Return a pointer to a node with the smallest key value or
        @c NULL if tree is empty. */
    Node* minimum() {
        if(this->_root) return _minimum(this->_root);
        else return NULL;
    }

    /** Return a pointer to a node with the largest key value or
        @c NULL if tree is empty. */
    Node* maximum() {
        if(this->_root) return _maximum(this->_root);
        else return NULL;
    }

    /** Return a pointer to a node with the specified key value <em> k</em>
        or @c NULL if no such node exists. See the description of
        <tt>_search(Node*, const T&)</tt> for demands on type <em> T</em>. */
    Node* search(const T& k) { return _search(this->_root, k); }

    /** Given a tree rooted at specified node <em> x</em>, return a pointer to
        the node with the smallest key value. */
    static inline Node* _minimum(Node* x) {
        while (x->child() != NULL) x = x->child();
        return x;
    }

    /** Given a tree rooted at specified node <em> x</em>, return a pointer to
        the node with the largest key value. */
    static inline Node* _maximum(Node* x) {
        while (x->sibling() != NULL) x = x->sibling();
        return x;
    }

    /** Given a tree rooted at specified node <em> x</em>, return a pointer
        to a node with the specified key value <em> k</em> or @c NULL if no such
        node exists. Since this requires to compare the given key value
        <em> k</em> with key values of nodes, the type of the keys must provide
        a useful not-equal operation. This method  is linear in the height of
        tree rooted at specified node <em> x</em>. */
    static inline Node* _search(Node* x, const T& k) {
        while (x != NULL && k != x->key())
            x = (k < x->key() ? x->child() : x->sibling());
        return x;
    }

    /** Given a node <em> x</em>, return a pointer to the node with the
        successor of its actual key value. */
    static Node* successor(Node* x) {
        if (x->sibling() != NULL) return _minimum(x->sibling());
        Node* y = x->p();
        while (y != NULL && x == y->sibling()) {
            x = y;
            y = y->p();
        }
        return y;
    }

    /** Given a node <em> x</em>, return a pointer to the node with the
        predecessor of its actual key value. */
    static Node* predecessor(Node* x) {
        if (x->child() != NULL) return _maximum(x->child());
        Node* y = x->p();
        while (y != NULL && x == y->child()) {
            x = y;
            y = y->p();
        }
        return y;
    }
    //@}
};

#endif

/// @}

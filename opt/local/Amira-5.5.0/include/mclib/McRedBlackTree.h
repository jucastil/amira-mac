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
#ifndef __MCREDBLACKTREE_H
#define __MCREDBLACKTREE_H

#include "McWinDLLApi.h"

#include <stdio.h>
#include "McBinaryTree.h"


/** Red-Black Tree
    @c McRedBlackTree implements a Red-Black Tree. These trees are in fact
    balanced Binary Trees. To achieve that, every node is colorized as either
    <em> black</em> or <em> red</em>. Insertion guarantees that <em> if</em> a node is red,
    <em> then</em> both its children are black. Also, every simple path from a node
    to a descendant leaf contains the same number of black nodes. This ensures
    that no path is more than twice as long as any other.
*/

template<class T>
class McRedBlackTree : public McBinaryTree<T> {
 public:
    /// Node color.
    typedef enum { Red, Black } Color;

    /// Node of a Red-Black Tree. Just add its color.
    struct RBNode : public McTree<T>::Node {

        Color _color;

        /** @name Constructors */
        //@{
        /// Default constructor. Make black node.
        RBNode(Color color = Black) :
            McTree<T>::Node(), _color(color) {}

        /// Create red node with specified key value.
        RBNode(const T& key) :
            McTree<T>::Node(key) {
                _color = Red;
            }
        //@}

        /** @name Access Methods */
        //@{
        /// Return reference to pointer to parent node.
        RBNode*& parent() { return (RBNode*&) this->p(); }

        /// Return reference to pointer to left subtree.
        RBNode*& left() { return (RBNode*&) this->child(); }

        /// Return reference to pointer to right subtree.
        RBNode*& right() { return (RBNode*&) this->sibling(); }

        /// Return reference to color value.
        Color& color() { return _color; }
        //@}
    };

 private:
    RBNode* _nil;

    void _leftRotate(RBNode* x) {
        RBNode* y = x->right();
        x->right() = y->left();
        if (y->left() != NULL) y->left()->parent() = x;
        y->parent() = x->parent();
        if (x->parent() == NULL)
            this->_root = y;
        else {
            if (x == x->parent()->left())
                x->parent()->left() = y;
            else
                x->parent()->right() = y;
        }
        y->left() = x;
        x->parent() = y;
    }

    void _rightRotate(RBNode* x) {
        RBNode* y = x->left();
        x->left() = y->right();
        if (y->right() != NULL) y->right()->parent() = x;
        y->parent() = x->parent();
        if (x->parent() == NULL)
            this->_root = y;
        else {
            if (x == x->parent()->right())
                x->parent()->right() = y;
            else
                x->parent()->left() = y;
        }
        y->right() = x;
        x->parent() = y;
    }

    McRedBlackTree(const McRedBlackTree &o) {}

 public:
    /** @name Constructor */
    //@{
    /// Default constructor. Create new empty tree.
    McRedBlackTree() : McBinaryTree<T>() { _nil = new RBNode(); }
    //@}

    /** @name Methods */
    //@{
    /// Insert specified node <em> x</em> into tree. Reorganize tree if necessary.
    void insert(RBNode* x) {
        McBinaryTree<T>::insert(x);
        x->_color = Red;
        RBNode* y;
        while (x != (RBNode*) this->_root && x->parent()->_color == Red) {
            if (x->parent() == x->parent()->parent()->left()) {
                y = x->parent()->parent()->right();
                if (y == NULL) y = _nil;
                if (y->_color == Red) {
                    x->parent()->_color = Black;
                    y->_color = Black;
                    x->parent()->parent()->_color = Red;
                    x = x->parent()->parent();
                }
                else {
                    if (x == x->parent()->right()) {
                        x = x->parent();
                        _leftRotate(x);
                    }
                    x->parent()->_color = Black;
                    x->parent()->parent()->_color = Red;
                    _rightRotate(x->parent()->parent());
                }
            }
            else {
                y = x->parent()->parent()->left();
                if (y == NULL) y = _nil;
                if (y->_color == Red) {
                    x->parent()->_color = Black;
                    y->_color = Black;
                    x->parent()->parent()->_color = Red;
                    x = x->parent()->parent();
                }
                else {
                    if (x == x->parent()->left()) {
                        x = x->parent();
                        _rightRotate(x);
                    }
                    x->parent()->_color = Black;
                    x->parent()->parent()->_color = Red;
                    _leftRotate(x->parent()->parent());
                }
            }
        }
        ((RBNode*) this->_root)->_color = Black;
    }

    /// Insert specified item <em> w</em> into tree.
    void insert(const T& w) { insert(new RBNode(w)); }

    /// Remove specified node from tree. Currently <b> NOT</b> implemented.
    RBNode* remove(RBNode* z) {
        fprintf(stderr, "McRedBlackTree::remove() not implemented.\n");
        return 0;
    }

    /** Return pointer to node containing specified item <em> key</em>, NULL if
        item cannot be found. */
    RBNode* search(const T& key) { return (RBNode*) McBinaryTree<T>::search(key); }

    /** Return pointer to node containing the minimum item, NULL if tree is
        empty. */
    RBNode* minimum() { return (RBNode*) McBinaryTree<T>::minimum(); }

    /** Return pointer to node containing the maximum item, NULL if tree is
        empty. */
    RBNode* maximum() { return (RBNode*) McBinaryTree<T>::maximum(); }

    /** Given a node <em> x</em>, return a pointer to the node with the
        successor of its actual key value. */
    static RBNode* successor(RBNode* x) {
        return (RBNode*) McBinaryTree<T>::successor(x);
    }

    /** Given a node <em> x</em>, return a pointer to the node with the
        predecessor of its actual key value. */
    static RBNode* predecessor(RBNode* x) {
        return (RBNode*) McBinaryTree<T>::predecessor(x);
    }
    //@}
};

#endif

/// @}

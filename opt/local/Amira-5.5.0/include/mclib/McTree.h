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
#ifndef __MCTREE_H
#define __MCTREE_H

#include "McWinDLLApi.h"

#include <stdlib.h>

/** @c McTree implements the basic class for all Tree data structures
    like McBinaryTree and McRedBlackTree.
    Each node of a Tree carries a <em> key</em>. There are iterators like
    McTreeIBreadthFirst and McTreeIDepthFirst for traversing
    trough a @c McTree. */

template <class T>
class McTree {
public:

        /** The ``raw'' node of a Tree. It only provides pointers to
          implement the link structure of such a tree. */

        struct _node {
                /// Pointer to parent node.
                _node* _p;

                /// Pointer to root of left subtree.
                _node* _child;

                /// Pointer to root of right subtree.
                _node* _sibling;

                /** @name Constructors */
                //@{
                /// Default constructor. Every pointer is set to @c NULL.
                _node() : _p(NULL), _child(NULL), _sibling(NULL) {}

                /** Copy constructor. Simply sets every pointer to the value
                  of its pendant in specified node <em> o</em>. */
                _node(const _node& o) :
                        _p(o._p), _child(o._child), _sibling(o._sibling) {}
                //@}

                /** @name Access Methods */
                //@{
                /// Return reference of pointer to parent.
                _node*& p() { return _p; }

                /// Return reference of pointer to left subtree.
                _node*& child() { return _child; }

                /// Return reference of pointer to right subtree.
                _node*& sibling() { return _sibling; }
                //@}
        };

public:
        /** The node of a Tree. It adds a @c _key to the ``raw'' node
          which represents the key of the node. */

        struct Node : public _node {
                /// The key of the node.
                T _key;

                /** @name Constructors */
                //@{
                /** Default constructor. Note that @c _key is not initialized.
                  Consequently, its type should provide a default constructor.
                  */
                Node() : _node() {}

                /// Create new node with specified key.
                Node(const T& key) : _node(), _key(key) {}

                /** Copy constructor. The type of @c _key should
                  define a copy constructor. */
                Node(const Node& o) : _node(o), _key(o._key) {}
                //@}

                /** @name Access Methods */
                //@{
                /// Return reference to @c _key.
                T& key() { return _key; }

                /// Return reference of pointer to parent.
                Node*& p() { return (Node*&) _node::p(); }

                /// Return reference of pointer to left subtree.
                Node*& child() { return (Node*&) _node::child(); }

                /// Return reference of pointer to right subtree.
                Node*& sibling() { return (Node*&) _node::sibling(); }
                //@}
        };

protected:
        /// Pointer to root of tree.
        Node* _root;

private:
        /** @name Constructors */
        //@{

        /** Copy constructor. */
        McTree(const McTree& o) {}
        //@}

public:
        /** @name Constructors */
        //@{
        /** Default constructor. Just creates an empty tree. */
        McTree() : _root(NULL) {}
        //@}

        /** @name Access Methods */
        //@{
        /// Return pointer to root of tree.
        Node* getRoot() { return _root; }
        //@}
};

#endif

/// @}

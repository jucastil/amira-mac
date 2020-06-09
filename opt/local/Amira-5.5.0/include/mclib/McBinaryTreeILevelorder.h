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
#ifndef __MCBINARYTREEILEVELORDER_H
#define __MCBINARYTREEILEVELORDER_H

#include "McWinDLLApi.h"
#include "McBinaryTree.h"
#include "McListQueue.h"

/** Binary Tree Level-Order Iterator. @c McBinaryTreeILevelorder implements a tree iterator which traverses
  through the tree using level-order traversal. This strategy is defined as
  visiting the elements from top to bottom and from left to right.
  See Iterator for a detailed description of the iterator concept.
  @see McBinaryTreeIInorder
  */

template <class T>
class McBinaryTreeILevelorder {
public:
    typedef typename McTree<T>::Node Node;

    McBinaryTree<T>* _tree;
    McListQueue<Node* > _queue;

public:
    /** @name Constructors */
    //@{
    /// Default constructor. Creates unattached iterator.
    McBinaryTreeILevelorder() : _tree(NULL) {}

    /// Attach constructor. Create iterator attached to specified tree.
    McBinaryTreeILevelorder(McBinaryTree<T>& tree) {
        _tree = &tree;
        rewind();
    }
    //@}

    /** @name Methods */
    //@{
    /// Attach iterator to specified tree.
    void attach(McBinaryTree<T>& tree) {
        _tree = &tree;
        rewind();
    }

    /// Rewind iterator to first node to be visited.
    void rewind() {
        _queue.flush();
        _queue.put(_tree->getRoot());
    }

    /// Return reference to current <em> item</em>.
    T& current() { return _queue.peek()->key(); }

    /// Return pointer to current <em> element</em>.
    Node* currentNode() { return _queue.peek(); }

    /** Termination check. Return 1 if iterator has visited all nodes, 0
        otherwise. */
    int ready() { return _queue.isEmpty(); }

    /// Step method. Move iterator to next element.
    void next() {
        if (_queue.isEmpty()) return;
        Node* _cursor = _queue.get();
        if (_cursor->child()) _queue.put(_cursor->child());
        if (_cursor->sibling()) _queue.put(_cursor->sibling());
    }
    //@}
};

#endif

/// @}

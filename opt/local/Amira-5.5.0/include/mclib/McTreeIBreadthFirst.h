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
#ifndef __MCTREEIBREADTHFIRST_H
#define __MCTREEIBREADTHFIRST_H

#include "McWinDLLApi.h"
#include "McTree.h"
#include "McListQueue.h"

/** Tree Breadth-First Iterator.
	@c McTreeIBreadthFirst implements a tree iterator which traverses
  through the tree using breadth-first traversal. This strategy is defined as
  visiting the elements from top to bottom and from left to right.
  This iterator <b> does not</b> work with @c McBinaryTree, cause McTree::Node's
  right pointer is a child in a McBinaryTree, and not a pointer to the next sibling
  as needed by this iterator. Use McBinaryTreeILevelorder instead.
  See Iterator for a detailed description of the iterator concept.
  @see McTreeIDepthFirst, McBinaryTreeILevelorder, McBinaryTreeIInorder
*/

template <class T>
class MCLIB_API McTreeIBreadthFirst {
	McTree<T>* _tree;
	McListQueue<McTree<T>::Node*> _queue;

public:
	/** @name Constructors */
	//@{
	/// Default constructor. Creates unattached iterator.
	McTreeIBreadthFirst() : _tree(NULL) {}

	/// Attach constructor. Create iterator attached to specified tree.
	McTreeIBreadthFirst(McTree<T>& tree) {
		_tree = &tree;
		rewind();
	}
	//@}

	/** @name Methods */
	//@{
	/// Attach iterator to specified tree.
	void attach(McTree<T>& tree) {
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
	McTree<T>::Node* currentNode() { return _queue.peek(); }

	/** Termination check. Return 1 if iterator has visited all nodes, 0
	  otherwise. */
	int ready() { return _queue.isEmpty(); }

	/// Step method. Move iterator to next element.
	void next() {
		if (_queue.isEmpty()) return;
		McTree<T>::Node* _cursor = _queue.get();
		if (_cursor->child()) {
			McTree<T>::Node* n = _cursor->child();
			while (n) {
				_queue.put(n);
				n = n->sibling();
			}
		}
	}
	//@}
};

#endif

/// @}

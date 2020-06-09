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
#ifndef __MCLISTQUEUE_H
#define __MCLISTQUEUE_H

#include "McWinDLLApi.h"
#include "McList2.h"

/** Queue using doubly linked list.
	@c McListQueue implements a Queue data structure and its basic set of
  operations.
  @see McListStack
*/
template <class T>
class McListQueue : public McList2<T> {
public:
    /** @name Constructors */
	//@{
	/// Default constructor.
	McListQueue() : McList2<T>() {}

	/// Copy constructor.
	McListQueue(const McListQueue& o) : McList2<T>(o) {}
	//@}

	/** @name Methods */
	//@{
	/// Put specified node <em> z</em> into queue.
	void put(typename McList2<T>::Node* z) { insert(z); }

	/// Put specified key <em> k</em> into queue.
	void put(const T& k) { this->insert(k); }

	/// Get item from queue.
	T get() {
	    typename McList2<T>::Node* node = this->remove(McList2<T>::_tail);
	    T key = node->_key;
	    delete node;
	    return key;
	}

	/// Get pointer to node of topmost item from queue.
	typename McList2<T>::Node* getNode() { return(this->remove(McList2<T>::_tail)); }

	/// Peek for topmost item on queue.
	T& peek() { return McList2<T>::_tail->_key; }

	/// Peek for pointer to node of topmost item on queue.
	typename McList2<T>::Node* peekNode() { return McList2<T>::_tail; }

	/// Return 1 if queue is empty, 0 otherwise.
	int isEmpty() { return McList2<T>::_tail == NULL; }

	/// Flush queue.
	void flush() { McList2<T>::flush(); }
	//@}
};

#endif

/// @}

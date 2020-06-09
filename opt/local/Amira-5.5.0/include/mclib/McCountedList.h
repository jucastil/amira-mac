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
#ifndef __MCCOUNTEDLIST_H
#define __MCCOUNTEDLIST_H

#include "McWinDLLApi.h"
#include "McList2.h"

/** @c McCountedList is a doubly linked list which counts its elements.  */

template <class T>
class MCLIB_API McCountedList : public McList2<T> {
	unsigned long _size;

public:
	/** @name Constructors */
	//@{
	/// Default constructor. Creates empty list.
	McCountedList() : McList2<T>(), _size(0) {}

	/// Copy constructor.
	McCountedList(const McCountedList& o) : McList2<T>(o), _size(o._size) {}
	//@}

	/** @name Methods */
	//@{

	/** Insert given node <em> x</em> to list. <em> x</em> becomes the first element of
	  the list. This method assumes that the caller allocates the node for the
	  actual item. */
	void insert(Node* x) {
		McList2<T>::insert(x);
		_size++;
	}

	/** Insert given node <em> x</em> to list. <em> x</em> becomes the first element of
	   the list. This method assumes that the caller allocates the node for the
		actual item. */
	void insert(Node& x) { insert(&x); }


	/** Insert given item <em> x</em> to list. <em> x</em> becomes the first element of
	  the list. This method allocates the node for the item. */
	void insert(const T& x) { insert(new Node(x, 1)); }

	/** Remove given node <em> x</em> from list. It returns a pointer to this node.
	  */
	Node* remove(Node* x) {
		if (_size > 0) _size--;
		return McList2<T>::remove(x);
	}

	/// Flush list.
	void flush() {
		_size = 0;
		McList2<T>::flush();
	}
	//@}

	/**@name Access Methods */
	//@{
	/** Return size of list. */
	unsigned long getSize() { return _size; }
	//@}
};

#endif

/// @}

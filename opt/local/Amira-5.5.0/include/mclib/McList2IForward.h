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
#ifndef __MCLIST2IFORWARD_H
#define __MCLIST2IFORWARD_H

#include "McWinDLLApi.h"
#include "McList2.h"

/** @c McList2IForward implements a forward iterator for McList2. See
  Iterator for a detailed description of the iterator concept.
  @see McList2IBackward
*/

template <class T>
class MCLIB_API McList2IForward {
	McList2<T>* _list;
	McList2<T>::Node* _cursor;

public:
	/** @name Constructors */
	//@{
	/// Default constructor. Creates unattached iterator.
	McList2IForward() : _list(NULL), _cursor(NULL) {}

	/// Attach constructor. Create iterator attached to specified list.
	McList2IForward(McList2<T>& list) {
		_list = &list;
		_cursor = list.getHead();
	}
	//@}

	/** @name Methods */
	//@{
	/// Attach iterator to specified list.
	void attach(McList2<T>& list) {
		_list = &list;
		_cursor = list.getHead();
	}

	/// Rewind iterator to beginning of list.
	void rewind() { _cursor = _list->getHead(); }

	/// Return reference to current <em> item</em>.
	T& current() { return _cursor->key(); }

	/// Return pointer to current <em> element</em>.
	McList2<T>::Node* currentNode() { return _cursor; }

	/// Termination check. Return 1 if iterator is at end of list, 0 otherwise.
	int ready() { return _cursor == NULL; }

	/// Step method. Move iterator to next element.
	void next() { _cursor = _list->getNext(_cursor); }
	//@}
};

#endif

/// @}

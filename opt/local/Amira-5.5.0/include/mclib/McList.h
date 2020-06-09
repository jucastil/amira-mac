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
#ifndef MC_LIST
#define MC_LIST

#include "McWinDLLApi.h"

#include <stdio.h>
#include <assert.h>

#define _mcListNullPtr_ stdout


/** @c McList implements an intrusive doubly linked list as a template
    class. Intrusive means that list elements must provide links to their
    predecessor and successor elements themselves. For convenience, a class
    McLink is provided that adds these links to an arbitrary class.
    @see McList2, McListStack, McListQueue
*/

template <class T>
class McList {

  public:
    /**@name Access*/
    //@{

    /// Returns first element in list.
    T* first() const { return _first; }

    /// Returns last element in list.
    T* last() const { return _last; }

    /// Returns successor of given element.
    T* succ(const T* elem) const { return (T*) elem->_suc; }

    /// Returns predecessor of given element.
    T* pred(const T* elem) const { return (T*) elem->_pre; }

    //@}

    /**@name Extension*/
    //@{

    /// Appends given element to end of list.
    inline void	append(T* elem);

    /// Appends second list to end of list.
    inline void append(McList<T> &other);

    /// Adds given element in front of list.
    inline void push(T* elem);

    /// Same as inserAfter()
    inline void	insert(T* elem, T* after) { insertAfter(elem,after); }

    /// Inserts @c elem after @c after.
    inline void	insertAfter(T* elem, T* after);

    /// Inserts @c elem before @c before.
    inline void	insertBefore(T* elem, T* before);

    //@}

    /**@name Removal*/
    //@{

    /// Removes first element of list and returns pointer to it.
    inline T* pop() { return _first ? remove(_first) : (T*) NULL; }

    /// Removes last element of list and returns pointer to it.
    inline T* Pop() { return _last ? remove(_last) : (T*) NULL; }

    /// Removes and returns @c elem from list.
    inline T* remove(T* elem);

    /** Removes all elements and sets @c _suc of all list elements to
	@c _mcListNullPtr_ before removing them.*/
    inline void removeAll();

    /// empties the list and calls the desctructor for each element
    inline void killAll();

    //@}

    /// Constructor
    McList() : _first(0), _last(0) { }

    /// Makes list empty.
    void clear() { _first=0; _last=0; }

    /// Returns number of elements in list.
    inline int getLength() const;

    /** Sort the list using a compare function. In most cases
        mcStandardCompare can be used as compare function.
        Sorting is done using the deterministic quick sort algorithm.
	It is therefore slow on lists that are already (almost) sorted.
	@see mcStandardCompare */
    void sort( int (*compare)(const T& t1,const T& t2) ) { sort(_first, _last, compare); }

    /// Does a quicksort on a part of the list
    inline void sort(T* first, T* last, int (*compare)(const T& t1,const T& t2) );

  protected:
    T*	    _first;
    T*	    _last;
};

/// @if EXCLUDETHIS
template <class T>
inline void McList<T>::append(T* elem)
{
    if (_last) {
	_last->_suc = elem;
	elem->_pre = _last;
	elem->_suc = 0;
	_last = elem;
    } else {
	elem->_pre = 0;
	elem->_suc = 0;
        _last = _first = elem;
    }
}

template <class T>
inline void McList<T>::append(McList<T> &other)
{
    if (!other.first())
	return;

    if (_last) {
	_last->_suc = other.first();
	other.first()->_pre = _last;
	other.last()->_suc = 0;
	_last = other.last();
    } else {
	_first = other.first();
	_last  = other.last();
    }

    other.clear();
}

template <class T>
inline void McList<T>::push(T* elem)
{
    if (_first) {
	_first->_pre = elem;
	elem->_suc = _first;
	elem->_pre = 0;
	_first = elem;
    } else {
	elem->_pre = 0;
	elem->_suc = 0;
        _last = _first = elem;
    }
}

template <class T>
inline void McList<T>::insertAfter(T* elem, T* after)
{
    if (after == _last) {
       append(elem);
    } else {
       elem->_suc = after->_suc;
       elem->_pre = after;
       after->_suc = ((T*)elem->_suc)->_pre = elem;
    }
}

template <class T>
inline void McList<T>::insertBefore(T* elem, T* before)
{
    if (before == _first) {
       push(elem);
    } else {
       elem->_pre = before->_pre;
       elem->_suc = before;
       before->_pre = ((T*)elem->_pre)->_suc = elem;
    }
}

template <class T>
inline T* McList<T>::remove(T* elem)
{
    if (elem == _first) {
	_first = (T*) elem->_suc;
	if (_first) _first->_pre = 0;
	    else _last = 0;
    }
    else if (elem == _last) {
	_last = (T*) elem->_pre;
	if (_last) _last->_suc = 0;
	    else _first = 0;
    }
    else {
       ((T*)elem->_suc)->_pre = elem->_pre;
       ((T*)elem->_pre)->_suc = elem->_suc;
    }
    elem->_suc = _mcListNullPtr_;
    return elem;
}

template <class T>
inline void McList<T>::removeAll()
{
    if (!_first) return;

    if (_first == _last) {
	_first->_suc = _mcListNullPtr_;
	_first = _last = 0;
	return;
    }

    T *cur, *old;
    old = cur = _first;
    do {
	cur = (T*)cur->_suc;
	old->_suc = _mcListNullPtr_;
	old = cur;
    } while (cur != _last);
    cur->_suc = _mcListNullPtr_;
    _first = _last = 0;
}

template <class T>
inline void McList<T>::killAll()
{
    T *curr, *next;

    curr = _first;
    while (curr){
	next = (T*)curr->_suc;
	delete(curr);
	curr = next;
    }

    _first = _last = 0;
}

template <class T>
inline int McList<T>::getLength() const
{
    int n=0;
    T* elem = _first;
    while (elem) {
	n++;
	elem = (T*) elem->_suc;
    }
    return n;
}

template <class T>
inline void McList<T>::sort(T* first, T* last, int (*compare)(const T& t1,const T& t2) )
{
    if (!first || !last || first==last || succ(last)==first) return;

    T* leftBound  = pred(first);
    T* rightBound = succ(last);

    // partition the list
    T* pivot = last;
    T* pointer = pred(pivot);
    T* nextPointer;

    while (pointer){

	if (compare(*pointer, *pivot)==1) {

	    nextPointer = pred(pointer);
	    remove(pointer);
	    insertAfter(pointer, last);
	    pointer = nextPointer;

	}else

	    pointer = pred(pointer);

    }

    // sort sublists
    leftBound  = (leftBound) ?  succ(leftBound)  : this->first();
    rightBound = (rightBound) ? pred(rightBound) : this->last();

    sort(leftBound, pred(pivot), compare);
    sort(succ(pivot), rightBound, compare);
}


/**
    Struct providing pointers required for insertion into @c McList.
    Class @c McLink allows easy construction of list elements for the
    intrusive doubly linked list @c McList. It adds two pointers @c pre and
    @c suc to each element. To use this struct simply derive from it.
    @c McList always will cast pointers to @c McLink to pointers to the
    actual list element type defined by the template parameter.
    */

struct McLink {

    /// Default constructor.
    McLink() : _suc(_mcListNullPtr_) { }

    /// Checks if element is contained in a list.
    int isInList() const { return (_suc != _mcListNullPtr_); }

    /// Sets pointers to zero.
    void initializeLinks() { _suc = _mcListNullPtr_; }

    void* _suc;  // link to next element
    void* _pre;  // link to prev element
};

/// @endif

#endif

/// @}

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
#ifndef MC_MEM_DARRAY_H
#define MC_MEM_DARRAY_H

#include "McWinDLLApi.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "McPrimType.h"

#ifndef MC_MEMFACTOR
    #define MC_MEMFACTOR 1.5
#endif

/// @if UNDOCUMENTED

/**
  This class provides a dynamic array for objects without a constructor.
  <b> In most other cases the use of McDArray is recommended.</b>

  The elements of an instance of @c McMemArray can be accessed just like
  ordinary C++ array elements by means of the index @c operator[]. Safety is
  provided by

  @li	automatic memory management in constructor and destructor
  preventing memory leaks
  @li checking of array bounds when accessing elements with the
  indexing @c operator[] (only when compiled without @c -DNDEBUG).


  Moreover, @c McMemArrays may easily be extended by @c inserting or @c appending
  elements to the @c McMemArray or shrunken by @c removing elements. Method
  <tt>resize(int n)</tt> resets the <tt>McMemArray</tt>s size to <tt>n</tt> thereby possibly
  appending elements or truncating the @c McMemArray to the required size.

  A @c McMemArrays may be used as arguments for standard C functions requiring
  pointers through a cast operator.

  Internally, a @c McMemArray objects allocates a block of memory that fits up
  to @c max() elements, only @c size() of them are used. This makes extension
  and shrinking methods perform better.

*/

template<class T> class McMemArray
{
  public:
    /// Copy constructor.
    McMemArray(const McMemArray& old) : thesize(old.thesize),
	themax(old.themax)
    {
	data = (T*)malloc(themax*sizeof(T));
	if (thesize)
	    memcpy(data, old.data, thesize*sizeof(T));
	assert(isConsistent());
    }

    /** Default constructor. The constructor allocates an @c Array
	containing @c size uninitialized elements. The internal array
	is allocated to have @c max non-zeros, and the memory extension
	factor is set to @c fac.  */
    McMemArray(int size=0, int max=0)
    {
	thesize = (size < 0) ? 0 : size;
	themax = (max > thesize) ? max : thesize;
	if (themax) data = (T*) malloc(themax * sizeof(T));
	    else data = 0;
	assert(isConsistent());
    }

    /// Destructor.
    ~McMemArray() { if (data) free(data); }

    /// Append element @c t to @c McMemArray.
    int append(const T& t) {
	insert(thesize, 1, &t);
	return(thesize-1);
    }

    /** Append @c n elements in @c t to @c McMemArray.
      @return Index of appended element.*/
    int append(int n, const T t[]) {
	insert(thesize, n, (const T*)t);
	return(thesize-1);
    }

    /// Append all elements in @c t to @c McMemArray.
    int appendArray(const McMemArray<T>& t) {
      return insertArray(thesize, t);
    }

    /** Append @c n default elements.
	@return Index of first appended element.*/
    int appendSpace(int n) {
	resize(thesize+n);
	return (thesize-n);
    }

    /// Insert @c n uninitialized elements before @c i-th element.
    int insertSpace(int addBefore, int n=1)
    {
	size();
	int delta = resize(thesize+n);

	T* ptrdest = &last();        // new last element
	T* ptrsrc  = ptrdest-n;      // previously the last element was here
	T* inspos  = data+addBefore+n-1;

	for (; ptrdest>inspos; ptrdest--, ptrsrc--)
	    *ptrdest = *ptrsrc;

	return delta;
    }

    /// Insert @c n elements in @c t before @c i-the element.
    int insert(int addBefore, int n, const T t[]) {
	if (n > 0) {
	    int delta = insertSpace(addBefore, n);
	    memcpy(&(data[addBefore]), t, n*sizeof(T));
	    return delta;
	}
	return 0;
    }

    /// Insert all elements in @c t before @c i-the element.
    int insertArray(int addBefore, const McMemArray<T>& t)
    {
	if( t.size() ) {
	    int delta = insertSpace(addBefore, t.size()) ;
	    memcpy(&(data[addBefore]), t.data, t.size()*sizeof(T)) ;
	    return delta ;
	}
	return 0 ;
    }

    /// Insert t in @c i-the element.
    int insert(int addBefore, const T& t)
    {
	int delta = insertSpace(addBefore, 1) ;
	data[addBefore]=t;
	return delta ;
    }

    /// Initialize all @c size() elements with t.
    void fill(const T& t)
    {
	T *ptr;
	T *end = data+size();
	for (ptr=data; ptr<end; ptr++) {
	    *ptr=t;
	}
    }

    /// Index operator.
    T&  operator[](int n) {
	assert(n>=0 && n<thesize);
	return data[n] ;
    }

    /// Const version of index operator.
    const T& operator[](int n) const {
	assert(n>=0 && n<thesize);
	return data[n];
    }

    /// Returns reference to last element of array.
    T&  last() {
	assert(thesize>0);
	return data[thesize-1];
    }

    /// Returns const reference to last element of array.
    const T& last() const {
	assert(thesize>0);
	return data[thesize-1];
    }

    /// Returns pointer to array data.
    operator T* () { return data; }

    /// Returns const pointer to array data.
    operator const T* () const  { return data; }

    /// Returns pointer to array data.
    T* dataPtr() { return data; }

    /// Returns const pointer to array data.
    const T* dataPtr() const  { return data; }


    /// Removes @c n elements starting at @c firstIndexToDelete.
    void remove(int firstIndexToDelete=0, int n=1)
    {
	if (n<=0)
	    return;
	assert(firstIndexToDelete<thesize && firstIndexToDelete>=0);
	if (firstIndexToDelete+n < thesize)
	    memcpy(&(data[firstIndexToDelete]), &(data[firstIndexToDelete+n]),
		(thesize-(firstIndexToDelete+n))*sizeof(T));
	else n = thesize - firstIndexToDelete;
	thesize -= n;
    }

    /// Removes @c n last elements.
    void removeLast(int n=1)
    {
	assert(n<=size() && n>=0);
	thesize -= n;
    }

    /// Same as append().
    int push(const T& t) { return append(t); }

    /// Removes last element into @c t. Returns 0 if array is empty.
    int pop(T& t) {
	if (thesize < 1)
	    return 0;
	t = last();
	thesize--;
	return 1;
    }

    /// Removes all elements.
    void clear() { thesize = 0; }

    /// Returns number of elements in array.
    int size() const { return thesize; }

    /// Set size to @c newsize.
    int resize(int newsize)
    {
	if (newsize<themax) {
	    if (newsize < 0) thesize = 0;
		else thesize = newsize;
	    return thesize;
	} else {
	    return remax((int)(MC_MEMFACTOR*newsize), newsize);
	}
    }

    /** This method returns the number of elements which fit into the
	internal buffer of the array. This number may be somewhat larger
	than the actual number of elements in the array as returned by
	@c size(). */
    int memSize() const { return themax; }

    /** Reset size of internal buffer. The value of @c max() is reset
	to @c newMax thereby setting @c size() to @c newSize. However, if
	@c newSize has a value @c < 0 (as the default argument does)
	@c size() remains unchanged and @c max() is set to <tt>MAX(size(),
	newMax)</tt>. Hence, calling @c remax() without the default
	arguments, will reduce the memory consumption to a minimum. In
	no instance @c max() will be set to a value less than 0 (even
	if specified). */
    int remax(int newMax=-1, int newSize=-1)
    {
	int oldmax = themax;
	if (newSize >= 0) thesize = newSize;
	if (newMax < newSize) newMax = newSize;
	if (newMax < 0) newMax = thesize;
	if (newMax == themax) return 0;
	themax = newMax;

	if (themax) {
	    if (data)
		data = (T*)realloc( data, themax * sizeof(T) ) ;
	    else
		data = (T*)malloc(themax * sizeof(T) ) ;
	} else {
	    if (data) free(data);
	    data = 0;
	}
	return oldmax-themax;
    }

    /// Consistency check.
    int isConsistent() const {
      assert(!(themax<0 || themax<thesize));
      return 1;
    }

    /** Assignment operator. Assigning an lvalue @c McMemArray to a
        rvalue @c McMemArray involves resizing the lvalue to the rvalues
        @c size() and copying all elements via @c memcpy(). */
    McMemArray& operator=(const McMemArray& rhs)
    {
	resize(rhs.size());
	memcpy(data, rhs.data, size()*sizeof(T));
	return *this;
    }


    /** Insert element t into array, according to the sorting scheme
      induced by compare. Insert before element end but after element
      start.
      @return The index of the inserted element.*/
    int insertSorted(const T& t,int (*compare)(const T& t1,const T& t2),
		     int start=-1,int end=-1)
    {
	if (end==-1)
	    end=size();

	if (end-start<=1) {
	    insert(start+1,t);
	    return(start+1);
	}
	int middle=(start+end)/2;
	int res=(*compare)(t,(*this)[middle]);
	if (res<0) /* t < middle */
	    return(insertSorted(t,compare,start,middle));

	return(insertSorted(t,compare,middle,end));
    }

    /** Find element t in a sorted array, according to the sorting scheme
      induced by compare.
      @return The index of the element, or -1 if not found.*/
    int findSorted(const T& t,int (*compare)(const T& t1,const T& t2),
		   int start=-1,int end=-1)
    {
	if (end==-1)
	    end=size();

	if (end-start<=1) {
	    if (start>-1 && compare(t,(*this)[start])==0)
		return(start);
	    if (end<size() && compare(t,(*this)[end])==0)
		return(end);
	    return(-1);
	}
	int middle=(start+end)/2;
	int res=(*compare)(t,(*this)[middle]);
	if (res<0) /* t < middle */
	    return(findSorted(t,compare,start,middle));

	return(findSorted(t,compare,middle,end));
    }

    void sort(int (*compare)(const T& t1,const T& t2)) {
	qsort(data,size(),sizeof(T),(int (*)(const void *, const void *))compare);
    }

	/// exchanges the items given by index1 and index2
	void swap(int index1, int index2) {
	    //T tmp;
	    //T tmp(data[index2]);
	    //memcpy(&tmp, &(data[index2]), sizeof(T));
	    char tmp[sizeof(T)];
	    memcpy(tmp, &(data[index2]), sizeof(T));
	    memcpy(&(data[index2]), &(data[index1]), sizeof(T));
	    memcpy(&(data[index1]), tmp, sizeof(T));
	}

    /** This method exchanges the content of the array with the one in other.
        Only the data pointers are changed, i.e., the method is very fast. */
    void swapWith(McMemArray<T> & other) {
        mclong tmp = thesize;
        thesize = other.thesize;
        other.thesize = tmp;

        tmp = themax;
        themax = other.themax;
        other.themax = tmp;

        T* tmpPtr = data;
        data = other.data;
        other.data = tmpPtr;
    }

    /** Returns the number of elements which fit into the internal buffer
        of the array. This number may be somewhat larger than the actual
        number of elements in the array as returned by @c size(). */
    int getMax() const { return themax; }


  protected:
    int thesize;	// Number of active elements in array
    int themax;		// Determines size of internal buffer
    T *data;		// Pointer t internal buffer
};

/// Looks for first occurrence of given element and returns its index.
template<class T>
static int index(McMemArray<T>& array, const T& elem)
{
    for (int i=0; i<array.size(); i++)
	if (array[i] == elem) return i;
    return -1;
}

/// Looks for last occurrence of given element and returns its index.
template<class T>
static int rindex(McMemArray<T>& array, const T& elem)
{
    int i;
    for ( i=array.size()-1; i>=0; i--)
	if (array[i] == elem) return i;
    return i;
}

/// @endif

#endif

/// @}

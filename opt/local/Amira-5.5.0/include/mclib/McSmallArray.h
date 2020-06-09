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
#ifndef MC_SMALL_ARRAY_H
#define MC_SMALL_ARRAY_H

#include "McWinDLLApi.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#ifdef HX_HAS_STDIOSTREAM
    #include <new>
#else
    #include <new.h>
#endif

#if 0

#if defined _WIN32 || defined _WIN64
    #include <malloc.h>
#elif
    #include <alloca.h>
#endif

#endif

#include "McMalloc.h"
#include "McStdlib.h"

#ifndef MC_MEMFACTOR
    #define MC_MEMFACTOR 1.5
#endif

/** This class provides an array of movable C++ objects.  If the size
    of the array is greater than MC_MAXSTATIC, it is implemented as a
    dynamic array.  If not, a static array is used.
    C++ Constructors/Destructors are called, but the objects may
    be moved in memory by memmove ! Therefore you must not
    store the address of an individual element elsewhere.
    This class requires the template parameter class to have a public
    default constructor.

    The elements of an instance of @c McSmallArray can be
    accessed just like ordinary C++ array elements by means of the
    index @c operator[]. Safety is provided by

    @li automatic memory management in constructor and destructor
    preventing memory leaks
    @li checking of array bounds when accessing elements with the
    indexing @c operator[] (only when compiled without @c -DNDEBUG).


    Moreover, @c McSmallArrays may easily be extended by @c inserting or
    @c appending elements to the @c McSmallArray or shrunken by @c removing
    elements. Method <tt>resize(int n)</tt> resets the <tt>McSmallArray</tt>s size
    to @c n thereby possibly appending elements or truncating the
    @c McSmallArray to the required size.

    A @c McSmallArray may be used as arguments for standard C functions requiring
    pointers through a cast operator.

    Internally, a @c McSmallArray objects allocates a block of memory that fits up
    to @c getMax() elements, only @c size() of them are used. This makes extension
    and shrinking methods perform better.

    @see McMemArray, McDArray
*/

template<class T, int MAXSTATIC> class McSmallArray
{
  public:
    typedef T value_type;

    /// Copy constructor.
    McSmallArray(const McSmallArray& old) : thesize(0) {
        appendArray(old);
        assert(isConsistent());
    }

    /** Default constructor.*/
    McSmallArray() : thesize(0) {
    }

    /** This constructor allocates an array containing @c size default
        elements. The internal array is allocated to provide space for
        @c max elements. */
    McSmallArray(int size, int max=0) : thesize(0)
    {
        remax(max,size);
        assert(isConsistent());
    }

    /// Destructor.
    ~McSmallArray() {
        clear();
    }

    /** Append element @c t to @c McSmallArray.
        @return Index of appended element.*/
    int append(const T& t) {
        insert(thesize, 1, &t);
        return (thesize-1);
    }

    /** Append @c n elements in @c t to @c McSmallArray.
        @return Index of first appended element.*/
    int append(int n, const T t[]) {
        insert(thesize, n , (const T*)t);
        return (thesize-n);
    }

    /** Append all elements in @c t to @c McSmallArray.
        @return Index of first appended element.*/
    int appendArray(const McSmallArray<T, MAXSTATIC>& t) {
        insertArray(thesize, t);
        return (thesize-t.size());
    }

    /** Append @c n default elements.
        @return Index of first appended element.*/
    int appendSpace(int n) {
        resize(thesize+n);
        return (thesize-n);
    }

    /// Insert @c n default elements at given position.
    void insertSpace(int addBefore, int n=1) {
        insertMemory(addBefore,n);
        T* data = dataPtr();
        for (int j = addBefore; j<addBefore+n; j++)
            new(&data[j]) T;
    }

    /// Insert @c n elements in @c t at given position.
    void insert(int addBefore, int n, const T t[]) {
        if (n > 0) {
            insertMemory(addBefore, n);
            T* data = dataPtr();
            for (int i=0; i<n; i++)
                new(&data[addBefore+i]) T(t[i]);
        }
    }

    /// Insert all elements in @c t at given position.
    void insertArray(int addBefore, const McSmallArray<T, MAXSTATIC>& t) {
        int n = t.size();
        if (n > 0) {
            insertMemory(addBefore, n) ;
            T* data = dataPtr();
            const T* otherdata = t.dataPtr();
            for (int i=0; i<n; i++)
                new(&data[addBefore+i]) T(otherdata[i]);
        }
    }

    /// Insert t at given position.
    void insert(int addBefore, const T& t) {
        insertMemory(addBefore, 1);
        T* data = dataPtr();
        new(&data[addBefore]) T(t);
    }

    /// Initialize all @c size() elements with t.
    void fill(const T& t) {
        T* data = dataPtr();
        T *end = data+size();
        for (T* ptr=data; ptr<end; ptr++)
            *ptr = t;
    }

    /// Index operator.
    T&  operator[](int n) {
        assert(n>=0 && n<thesize);
        T* data = dataPtr();
        return data[n];
    }

    /// Const version of index operator.
    const T& operator[](int n) const {
        assert(n>=0 && n<thesize);
        const T* data = dataPtr();
        return data[n];
    }

    /// Returns reference to last element of array.
    T& last() {
        assert(thesize>0);
        T* data = dataPtr();
        return data[thesize-1];
    }

    /// Returns const reference to last element of array.
    const T& last() const {
        assert(thesize>0);
        const T* data = dataPtr();
        return data[thesize-1];
    }

    /// Returns pointer to array data.
    operator T* () { return dataPtr(); }

    /// Returns const pointer to array data.
    operator const T* () const  { return dataPtr(); }

    /// Returns pointer to array data.
    T* dataPtr() {
        return (thesize<=MAXSTATIC) ? (T*)d.values : d.dynamic.data;
    }

    /// Returns const pointer to array data.
    const T* dataPtr() const  {
        return (thesize<=MAXSTATIC) ? (T*)d.values : d.dynamic.data;
    }


    /// Removes @c n elements starting at @c firstIndexToDelete.
    void remove(int firstIndexToDelete=0, int n=1) {
        if (n<=0)
            return;
        assert(firstIndexToDelete<thesize && firstIndexToDelete+n<=thesize);

        T* data = dataPtr();
        for (int i=firstIndexToDelete; i<firstIndexToDelete+n; i++)
            data[i].~T();

        int rest = thesize-(firstIndexToDelete+n);

        if (rest>0)
            memmove(&(data[firstIndexToDelete]), &(data[firstIndexToDelete+n]),
                    (rest)*sizeof(T));

        if (thesize>MAXSTATIC && thesize-n<=MAXSTATIC) {
            memcpy(d.values,data,(thesize-n)*sizeof(T));
            free(data);
        }

        thesize -= n;
    }

    /// Removes @c n last elements.
    void removeLast(int n=1) {
        assert(n<=size() && n>=0);
        resize(thesize-n);
    }

    /// Same as append().
    int push(const T& t) { return append(t); }

    /// Removes last element into @c t. Returns 0 if array is empty, otherwise 1.
    int pop(T& t) {
        if (thesize < 1)
            return 0;
        t = last();
        resize(thesize-1);
        return 1;
    }

    /// Removes all elements.
    void clear() {
        T* data = dataPtr();
        for (int i=0 ; i<thesize ; i++)
            ((T*)&data[i])->~T();
        if (thesize>MAXSTATIC)
            free(data);
        thesize=0;
    }

    /// Returns number of elements in array.
    int size() const { return thesize; }

    /// Set size to @c newsize. Returns new number of elements.
    int resize(int newsize) {
        if (newsize<0)
            newsize=0;

        T* data = dataPtr();
        for (int i=newsize; i<thesize; i++)
            ((T*)&data[i])->~T();

        if (thesize<=MAXSTATIC) {
            if (newsize>MAXSTATIC) {           // static -> dynamic
                int nmax = (int)(MC_MEMFACTOR*thesize);
                if (nmax<newsize) nmax=newsize;
                data = (T*)malloc(nmax*sizeof(T));
                memcpy(data, d.values, thesize*sizeof(T));
                d.dynamic.data = data;
                d.dynamic.themax = nmax;
            }
        }
        else {
            if (newsize>MAXSTATIC) {          // dynamic -> dynamic
                if (newsize>d.dynamic.themax) {
                    int nmax = (int)(MC_MEMFACTOR*thesize);
                    if (nmax<newsize) nmax=newsize;
                    d.dynamic.data = (T*)realloc(d.dynamic.data, nmax*sizeof(T));
                    d.dynamic.themax = nmax;
                    data = d.dynamic.data;
                }
            } else {                         // dynamic -> static
                memcpy(d.values, data, newsize*sizeof(T));
                free(data);
                data = (T*)d.values;
            }
        }

        for (int j = thesize; j<newsize; j++)
            new(&data[j]) T;

        thesize = newsize;
        return thesize;
    }

    /** This method returns the number of elements which fit into the
        internal buffer of the array. This number may be somewhat larger
        than the actual number of elements in the array as returned by
        @c size(). */
    int getMax() const {
        return (thesize<=MAXSTATIC) ? MAXSTATIC : d.dynamic.themax;
    }

    /** Reset size of internal buffer. The value of @c getMax() is reset
        to @c newMax thereby setting @c size() to @c newSize. However, if
        @c newSize has a value @c < 0 (as the default argument does)
        @c size() remains unchanged and @c getMax() is set to <tt>MAX(size(),
        newMax)</tt>. Hence, calling @c remax() without the default
        arguments, will reduce the memory consumption to a minimum. In
        no instance @c getMax() will be set to a value less than 0 (even
        if specified).
        @return the number that @c getMax() is reduced.
    */
    int remax(int newmax=-1, int newsize=-1) {
        int i;
        int oldsize = thesize;
        int oldmax = getMax();

        if (newmax < 0) newmax = thesize;
        if (newsize < 0) newsize = thesize;
        if (newmax < newsize) newmax = newsize;

        T* data = dataPtr();
        for ( i=newsize ; i<oldsize ; i++)
            ((T*)&data[i])->~T();

        if (thesize<=MAXSTATIC) {
            if (newsize>MAXSTATIC) {     // static -> dynamic
                data = (T*)malloc(newmax*sizeof(T));
                memcpy(data, d.values, oldsize*sizeof(T));
                d.dynamic.themax = newmax;
                d.dynamic.data = data;
            }
            // static -> static: nothing happens
        } else {
            if (newsize<=MAXSTATIC) {    // dynamic -> static
                memcpy(d.values, data, newsize*sizeof(T));
                free(data);
                data = (T*)d.values;
            } else {                       // dynamic -> dynamic
                data = (T*)realloc(data, newmax*sizeof(T));
                d.dynamic.themax = newmax;
                d.dynamic.data = data;
            }
        }

        for (i = oldsize; i<newsize; i++)
            new(&data[i]) T;

        thesize = newsize;
        return oldmax-getMax();
    }

    /// Consistency check.
    int isConsistent() const {
        return (getMax()>=0 && getMax()>=thesize);
    }

    /** Assignment operator. Assigning an lvalue @c McSmallArray to a
        rvalue @c McSmallArray involves resizing the lvalue to the rvalues
        @c size() and copying all elements via @c memcpy(). */
    McSmallArray& operator=(const McSmallArray& rhs) {
        resize(rhs.size());
        T* data = dataPtr();
        const T* rhsdata = rhs.dataPtr();
        for (int i=0; i<thesize; i++)
            data[i] = rhsdata[i];
        return *this;
    }


    /** Insert element t into array, according to the sorting scheme
        induced by compare. Insert before element @c end but after element
        @c start. In default, t will be inserted somewhat between
        "before first element" and "after last element".
        For many standard data types the global template
        function mcStandardCompare can be used. The compare
        function should return either -1, 0, 1, depending on whether
        the first argument is smaller, equal, or bigger than the second
        one.
        @return The index of the inserted element.
        @see mcStandardCompare */
    int insertSorted(const T& t,int (*compare)(const T& t1,const T& t2),
                     int start=-1,int end=-1) {
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
        induced by compare. For details refer to insertSorted.
        @return The index of the element or -1 if not found.
        @see mcStandardCompare */
    int findSorted(const T& t,int (*compare)(const T& t1,const T& t2),
                   int start=-1,int end=-1) const {
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

    /** Sort array using a compare function. In most cases
        mcStandardCompare can be used as compare function.
        Sorting is done using the quick sort algorithm.
        @see mcStandardCompare */
    void sort(int (*compare)(const T& t1,const T& t2)) {
        qsort(dataPtr(),size(),sizeof(T),
              (int (*)(const void *, const void *))compare);
    }

    /** Swap the elements specified by @c index1 and @c index2. No copy
        constructors are called but the elements are swapped on a per-byte
        basis. */
    void swap(int index1, int index2) {
        int nBytes = sizeof(T);
        T* data = dataPtr();
        unsigned char* dst1 = (unsigned char*) &(data[index1]);
        unsigned char* dst2 = (unsigned char*) &(data[index2]);
        for (int i=0 ; i<nBytes ; i++) {
            unsigned char tmp = dst1[i];
            dst1[i] = dst2[i];
            dst2[i] = tmp;
        }
    }

    void reverse() {
        int n2 = size()/2;
        int s = size();
        for (int i=0 ; i<n2 ; i++)
            swap(i,s-1-i);
    }

    /// Rotate all elements to the left (offset<0) or to the right (offset>0).
    void rotate(int offset) {
        int i, s = size();
        T* data = dataPtr();
        if (offset<0) {
            int n = -offset;
            T* tmp = (T*)alloca(n*sizeof(T));
            for (i=0; i<n; i++)
                tmp[i] = data[i];
            for (i=0; i<s-n; i++)
                data[i] = data[i+n];
            for (i=0; i<n; i++)
                data[i+s-n] = tmp[i];
        } else if (offset>0) {
            int n = offset;
            T* tmp = (T*)alloca(n*sizeof(T));
            for (i=0; i<n; i++)
                tmp[i] = data[s-n+i];
            for (i=s-n-1; i>=0; i--)
                data[n+i] = data[i];
            for (i=0; i<n; i++)
                data[i] = tmp[i];
        }
    }

  protected:
    // Inserts @c n uninitialized elements at given position.
    void insertMemory(int addBefore, int n=1) {

        int newsize = thesize+n;

        T* data = dataPtr();
        if (thesize<=MAXSTATIC) {
            if (newsize>MAXSTATIC) { // static -> dynamic
                int nmax = (int)(MC_MEMFACTOR*thesize);
                if (nmax<newsize) nmax=newsize;
                data = (T*)malloc(nmax*sizeof(T));
                memcpy(data, d.values, thesize*sizeof(T));
                d.dynamic.data = data;
                d.dynamic.themax=nmax;
            }
        } else {
            if (newsize>MAXSTATIC) {          // dynamic -> dynamic
                if (newsize>d.dynamic.themax) {
                    int nmax = (int)(MC_MEMFACTOR*thesize);
                    if (nmax<newsize) nmax=newsize;
                    d.dynamic.data = (T*)realloc(d.dynamic.data,nmax*sizeof(T));
                    d.dynamic.themax = nmax;
                    data = d.dynamic.data;
                }
            } else if (newsize<MAXSTATIC) { // dynamic -> static
                memcpy(d.values, data, newsize*sizeof(T));
                free(data);
                data = (T*)d.values;
            }
        }

        thesize = newsize;

        if (thesize-n-addBefore) {
            T* src = data+addBefore;
            T* dst = src+n;
            memmove(dst, src, (thesize-n-addBefore)*sizeof(T));
        }
    }

    int thesize;        // Number of active elements in array
    union {             // static array for small McSmallArrays
        unsigned char values[MAXSTATIC*sizeof(T)];
        struct {
            int themax; // Determines size of internal buffer
            T *data;    // Pointer t internal buffer
        } dynamic;
    } d;
};

/// @if EXCLUDETHIS
// we need a named namespace to select different index functions.
// namespace has to be different to the class name
// first character is lowercase
namespace mcSmallArray {
/**Template functions for searching and comparisons.
   This section lists some global template function which are often
   used in conjunction with a  McSmallArray. For example, the @c index
   function allows you to look for the index of a certain element in the
   array. The reason that this method is not a member of the <tt> McSmallArray</tt>
   itself is that not all types which one may want to insert in an array
   necessarily have a equality operator.
*/

    /// Looks for first occurrence of given element and returns its index.
    template<class SA>
    int index(SA& array, const typename SA::value_type& elem)
    {
        for (int i=0; i<array.size(); i++)
            if (array[i] == elem) return i;
        return -1;
    }

/*
    /// Looks for last occurrence of given element and returns its index.
    template<class SA>
    int rindex(SA& array, const typename SA::value_type& elem)
    {
        int i;
        for ( i=array.size()-1; i>=0; i--)
            if (array[i] == elem) return i;
        return i;
    }
*/

}; // end namespace mcSmallArray

/// @endif

#endif

/// @}

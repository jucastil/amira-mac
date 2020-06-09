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
#ifndef MC_SORTER_H
#define MC_SORTER_H

#include "McWinDLLApi.h"
#include <assert.h>

/**@name sorting functions
   Some useful sorting function.
*/
//@{
/**
    Sort array using Comparator object.
    The template function @c sort sorts an array @c t holding @c n elements of
    type @c T using a @c COMPARATOR class for comparisons.
    Class @c COMPARATOR must be provide an overloaded
    <tt>operator()(const T& t1,const T& t2)</tt>, that returns

    @li [@c <0]         if @c t1 is to appear before @c t2,
    @li [@c ==0]        if @c t1 and @c t2 can appear in any order or
    @li [@c >0]         if @c t1 is to appear after @c t2.

    This sorting method implements the quicksort algorithm.
 */
template< class COMPARATOR, class T >
void sort( T* t, int end, COMPARATOR& compare, int start = 0 )
{
    int         i0, i1, j ;
    double      c ;

    T   work, mid, tmp ;

    work             = t[start] ;
    t[start]         = t[(start+end)/2] ;
    t[(start+end)/2] = work ;

    mid  = t[start] ;
    work = t[end-1] ;

    for(i0 = i1 = start, j = end-1 ; i1 < j ; )
    {
        c = compare(mid,work) ;
        if( c > 0 )
        {
            tmp   = t[i0] ;
            t[i0] = work ;
            i0++ ;
            i1++ ;
            work  = t[i1] ;
            t[i1] = tmp ;
        }
        else if( c < 0 )
        {
            t[j] = work ;
            --j ;
            work = t[j] ;
        }
        else
        {
            i1++ ;
            tmp   = t[i1] ;
            t[i1] = work ;
            work  = tmp ;
        }
    }

    if( start < i0-1 )
        sort( t, i0, compare, start ) ;
    if( i1+1 < end )
        sort( t, end, compare, i1+1 ) ;
}

/// @if UNDOCUMENTED

#ifndef _CRAYMPP
/** Sort array using @c operator<.
	The template function @c sort sorts an array @c t holding @c n elements of
    type @c T, which must provide an @c operator>.
    This sorting method implements the quicksort algorithm.
 */
template< class T >
void sort( T* t, int n )
{
    struct XYZ {
        int operator()(T i, T j) {
            return (i < j) ? -1 : ((j < i) ? 1 : 0) ;
        }
    } c ;
    sort(t, n, c, 0) ;
}

/** heapsort algorithm based on Knuth vol.3 p.145
    assumes @c T to have @c operator< */
template<class T>
void heapSort( T* t, int size)
{
    if(size <= 1) return;

    T * R_ = t-1;

    // initialize (H1)
    int l = size/2+1;
    int r = size;

    T R;

    while(1){
        // deccrease l or r (H2)
        if(l>1){
            l--;
            R = R_[l];
        } else {
            R = R_[r];
            R_[r] = R_[1];
            r--;
            if(r==1) {
                R_[1] = R;
                break; // terminate the algorithm
            }
        }

        // prepare for siftup (H3)
        int i, j = l;

        while(1){
            // advance downward (H4)
            i = j;
            j *= 2;

            if(j>r)
                break;  // goto step (H8)

            if(j<r){
                // find larger child (H5)
                if(R_[j] < R_[j+1]){
                    j++;
                }
            }

            // larger than R ? (H6)
            if(R < R_[j]){
                // move it up (H7)
                R_[i] = R_[j];
            } else {
                break;  // goto step (H8)
            }
        }

        // store R (H8)
        R_[i] = R;
    }
}

#endif  //@ _CRAYMPP

/// @endif

//@}

#endif // #MC_SORTER_H#

/// @}

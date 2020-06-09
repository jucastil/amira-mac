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

/// @addtogroup molchem molchem
/// @{
#ifndef MOLCHEM_ITERATOR_H
#define MOLCHEM_ITERATOR_H

#include <mclib/McHandable.h>
#include <mclib/McHandle.h>
#include <mclib/McBitfield.h>

namespace molchem {
    /** \brief Allows iteration over molecular groups
    
    Design patterns: Iterator
    */
    template <class T> class IteratorBase : public McHandable {
    public:
        /// return current element 
        virtual T* current() = 0;
        /// jump to next element and return it
        virtual T* next() = 0;
    };
    
    template <class T> class IteratorBaseGraphTraversal : public IteratorBase<T> {
    protected:
        McBitfield nVisited;
        McBitfield eVisited;
        int depth;
    public:
        int getDepth() { return depth;}
        McBitfield& getNodeVisitedBitfield() { return IteratorBaseGraphTraversal::nVisited;}
        McBitfield& getEdgeVisitedBitfield() { return IteratorBaseGraphTraversal::eVisited;}
        virtual void restart(const T*) = 0;
    };
    /** \brief Allows iteration over molecular groups
    
    Design patterns: Iterator, Proxy
    */
    template <class T> class Iterator {
    protected:
        McHandle < IteratorBase < T > > ib;
    public:
        Iterator() {};
        Iterator(IteratorBase < T > *rhs) {
            (*this) = rhs;
        }
        Iterator(const Iterator < T > &rhs) {
            (*this) = rhs;
        }
        Iterator<T>& operator = ( IteratorBase < T > *rhs) {
            ib = rhs;
            return (*this);
        }
        Iterator<T>& operator = ( const Iterator < T > &rhs) {
            ib = rhs.ib;
            return (*this);
        }
        /// return current element must be overloaded
        T* current() { return ib->current();}
        /// jump to next element and return it, must be overloaded
        T* next() { return ib->next();}
        /// 
        operator T*() { return ib->current();}
        /// (*this)-> operator
        T* operator->() { return ib->current();}
        /// (*this)++ operator. For higher efficiency Use ++(*this) instead wherever possible
        T* operator++(int) {T* t = ib->current();ib->next();return t;}
        /// ++(*this) operator
        T* operator++() {return ib->next();}
    };

    template <class T> class IteratorGraphTraversal : public Iterator<T> {
    public:
        IteratorGraphTraversal() {};
        IteratorGraphTraversal(IteratorBaseGraphTraversal < T > *rhs) {
            (*this) = rhs;
        }
        IteratorGraphTraversal(const IteratorGraphTraversal < T > &rhs) {
            (*this) = rhs;
        }
        IteratorGraphTraversal<T>& operator = ( IteratorBaseGraphTraversal < T > *rhs) {
            IteratorGraphTraversal::ib = rhs;
            return (*this);
        }
        IteratorGraphTraversal<T>& operator = ( const Iterator < T > &rhs) {
            IteratorGraphTraversal::ib = rhs.ib;
            return (*this);
        }
        int getDepth() {
            return ((IteratorBaseGraphTraversal<T>*)IteratorGraphTraversal::ib.ptr())->getDepth();
        }
        McBitfield& getNodeVisitedBitfield() {
            return ((IteratorBaseGraphTraversal<T>*)IteratorGraphTraversal::ib.ptr())->getNodeVisitedBitfield();
        };
        McBitfield& getEdgeVisitedBitfield() {
            return ((IteratorBaseGraphTraversal<T>*)IteratorGraphTraversal::ib.ptr())->getEdgeVisitedBitfield();
        };
        void restart(T* t) { 
            ((IteratorBaseGraphTraversal<T>*)IteratorGraphTraversal::ib.ptr())->restart(t);
        }
    };
}

#endif



/// @}

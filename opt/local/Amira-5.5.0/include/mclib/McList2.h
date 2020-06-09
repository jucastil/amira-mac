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
#ifndef __MCLIST2_H
#define __MCLIST2_H

#include "McWinDLLApi.h"

/** Alternative intrusive doubly linked list.
    @c McList2 is an implementation of a doubly linked list providing
    <b>only</b> basic list methods. For a complete discussion of this
    set of operations refer to

    @li Thomas H. Cormen, Charles E. Leierson and Ronald L. Rivest.
    <em>Introduction to Algorithms</em>, MIT Press/McGraw-Hill, 1990,
    chapter 11.

    @see McList, McListStack, McListQueue
*/
template <class T> class McList2 {
  public:
    /** @c McList2<<em> T</em>@c >::Node implements a single node in the list. Each
	node carries a @c _key which is the actual <em> list item</em>. */
    struct Node {
        /// The list item of this node.
        T _key;

        /// Ownership indicator. If set to 1, this node is owned by the list.
        int _ownership;

        /// Pointer to previous node.
        Node* _prev;

        /// Pointer to next node.
        Node* _next;

        /** Default constructor. The list item is <b> not</b> initialized.
	    Consequently, type <em> T</em> should provide a default constructor. */
	Node() : _ownership(0), _prev(NULL), _next(NULL) {}

        /** Create new node for specified list item. */
        Node(const T& key, int ownership = 0, Node* prev = NULL, Node* next = NULL) :
            _key(key), _ownership(ownership), _prev(prev), _next(next) {}

        /// Return reference to list item.
        T& key() { return _key; }
        const T& key() const { return _key; }

        /// Ownership. Returns 1 if node is owned by list, 0 otherwise.
        int& ownership() { return _ownership; }

        /// Return reference to pointer of previous node.
        Node*& prev() { return _prev; }
        const Node* prev() const { return _prev; }

        /// Return reference to pointer of next node.
        Node*& next() { return _next; }
        const Node* next() const { return _next; }
    };

  protected:
    /// Pointer to very first node in the list.
    Node* _head;

    /// Pointer to very last node in the list.
    Node* _tail;

  public:
    /// Default constructor. Creates empty list.
    McList2() { _head = _tail = NULL; }

    /// Copy constructor.
    McList2(const McList2& o) {
        Node* p = o._head;
        while (p) {
            insert(p->_key);
            p = p->_next;
        }
    }

    /// Flushes list.
    ~McList2() { flush(); }

    /** Insert given node <em> x</em> to list. <em> x</em> becomes the first element of
        the list. This method assumes that the caller allocates the node for the
        actual item. */
    void insert(Node* x) {
        if (!_head) {
            _head = _tail = x;
        }
        else {
            x->_next = _head;
            _head->_prev = x;
            _head = x;
        }
    }

    /** Insert given node <em> x</em> to list. <em> x</em> becomes the first element of
        the list. This method assumes that the caller allocates the node for the
        actual item. */
    void insert(Node& x) { insert(&x); }

    /** Insert given item <em> x</em> to list. <em> x</em> becomes the first element of
        the list. This method allocates the node for the item. */
    void insert(const T& x) { insert(new Node(x, 1)); }

    /** Remove given node <em> x</em> from list. It returns a pointer to this node. */
    Node* remove(Node* x) {
        if (x->_prev != NULL)
            x->_prev->_next = x->_next;
        else
            _head = x->_next;
        if (x->_next != NULL)
            x->_next->_prev = x->_prev;
        else
            _tail = x->_prev;
        return x;
    }

    /** Search for given item <em> k</em> in list. Returns a pointer to the list
        element carrying the item or @c NULL. */
    Node* search(const T& k) {
        Node* x = _head;
        while (x && x->_key != k) x = x->_next;
        return x;
    }

    /** Flush list. Walk through list and delete every owned node. */
    void flush() {
        Node* x;
        while (_head) {
            x = _head;
            _head = _head->_next;
            if (x->_ownership) delete x;
        }
        _head = _tail = NULL;
    }

    /** Return pointer to first element of list. Returns @c NULL if list is
        empty. */
    Node* getHead() const { return _head; }

    /** Return pointer to last element of list. Returns @c NULL if list is
        empty. */
    Node* getTail() const { return _tail; }

    /** Return next node of given node <em> x</em>. */
    Node* getNext(Node* x) const { return x->_next; }

    /** Return previous node of given node <em> x</em>. */
    Node* getPrev(Node* x) const { return x->_prev; }
};

#endif

/// @}

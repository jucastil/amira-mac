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
#ifndef MC_HASHTABLE_DOUBLE_H
#define MC_HASHTABLE_DOUBLE_H

#include "McHashTable.h"
#include "McDArray.h"

/** Dictionary implemented via double hashing.
        This data type maintains a set of key-value pairs. It provides a
    very simple interface via the index operator. Both key and value
    of a hash entry are copied into the internal data-structure. The
    user has not to bother with an extra hash entry data type. However,
    this also involves dynamic memory allocation on each insertion,
    which might impair performance.

    Any data type or class can be used as a key or as a value as long
    as a public copy constructor and a public assignment operator are
    provided. Hashing and comparison relies on the existence of global
    functions @c hash(), @c hash2() and @c compare(). For integer, McVec2i
    and McVec3i these functions are already provided.

    To reduce the costs implied by copying large data objects you may
    use appropriate pointers as key or value types. Preferable these
    should be smart pointers as provided by McHandle.

    The hash table is implemented using double hashing. For more
    information see any book on hashing.
*/

template<class Key, class Value> class McHashTableDouble
{
public:
    /// Constructor takes default value for hash entries.
    McHashTableDouble(const Value& defaultValue);

    /** Constructor allowing to set the minimum size of the hashtable.
        The actual size of the hashtable will be the smallest prime
        number greater than @c minSize. */
    McHashTableDouble(const Value& defaultValue, int minSize);

    /** Yet another constructor. The parameter @c minSize has the same
        meaning as in the above constructor. The parameter @c max should
        be a power of two. It is used as an argument to the hash function.
        The default is 8. */
    McHashTableDouble(const Value& defaultValue, int minSize, int max);

    /// Destructor.
    ~McHashTableDouble();

    /// Number of buckets in hash table.
    int getSize() const { return size; }

    /// Set (minimum) number of buckets in hash table.
    void setSize(int _size) {
        if ( _size>size ) { size = _size; enlargeTable(); }
        else { size = _size; reduceTableSize(); }
    }

    /// Number of buckets in hash table.
    int getNItems() const { return nItems; }

    /** Inserts or updates key-value pair.
                If the given key does not already exist, a new table entry is
        created. The value of this entry is initialized with the second
        argument. If the key does already exist its value is overridden.
        The return value indicates if a new entry has been created (1)
        or if an existing one has been used (0).
    */
    int insert(const Key& key, const Value& val);

    /// Inserts default value if key doesn't exist.
    Value* insert(const Key& key);

    /// Find place where item with key should be inserted.
    int insertNewTable(const Key& key);

    /// Returns pointer to associated value if key does exist, 0 otherwise.
    inline Value* lookup(const Key& key) {
        int idx, offset;
        idx = hash(key, base, size);
        offset = -1;

        while (table[idx] || delItems[idx]) {
            if (!delItems[idx]) {
                if (compare(table[idx]->key,key)==0) {
                    return &table[idx]->value;
                }
            }
            if (offset == -1)
                offset = hash2(key, base2);
            idx = (idx+offset) % size;
        }
        return 0;
    }

    /** Read-write access via index operator.
                If given key does not already exist, a new table entry is
        created. The value of this entry is initialized with the default
        value specified in the constructor.
    */
    inline Value& operator[](const Key& key) { return *insert(key); }

    /// Removes key and associated value from hash table.
    int remove(const Key&);

    /// Removes all elements.
    void removeAll();

    /// Resets iterator to first key-value pair.
    void resetIter() { iterIdx=0; }

    /** Return next key-value pair.
                Successively returns all key-value pairs. Does not stop
        if end of table is reached. Instead it starts from the
        beginning.
    */
    int next(Key& key, Value& value);

    /// Print out some statistics (for debugging only).
    void printStat();

  protected:

    struct Item {
        Key key;
        Value value;
        Item(const Key& k, const Value& v) : key(k), value(v) { }
    };

    void reduceTableSize();// Adjusts size of bucket array.
    void enlargeTable();   // Adjusts size of bucket array.

    int     size;          // Size of hashtable, i.e. number of buckets.
    int     base;          // Base value used to truncate hash index.
    int     base2;         // Value used to compute second hash value.
    int     nItems;        // Number of filled buckets.
    int     nDelItems;     // Number of deleted items.
    int     iterIdx;       // Bucket index used for iteration.
    McDArray<Item*> table; // Hashtable.
    McDArray<unsigned char> delItems; // Table of deleted items.
    Value   defaultValue;  // Default value.
private:
    /** Copy construction and assignment nontrivial and not implemented, therefore disabled */
    McHashTableDouble(const McHashTableDouble<Key,Value> &) { assert(0); }
    McHashTableDouble<Key,Value> & operator=(const McHashTableDouble<Key,Value> &) { assert(0); return this; }

    /**
        Computes and sets base2 based on the current value of size.
    */
    void computeBase2();

};

/** Hash functions and comparators.
*/

/// Hash function for integers.
MCLIB_API int hash(int key, int b, int m);

/// Hash function for McVec2i.
MCLIB_API int hash(McVec2i key, int b, int m);

/// Hash function for McVec3i.
MCLIB_API int hash(McVec3i key, int b, int m);

/// Second hash function for Key (uses hash).
MCLIB_API int hash2(int key, int b2);

/// Second hash function for Key (uses hash).
MCLIB_API int hash2(McVec2i key, int b2);

/// Second hash function for Key (uses hash).
MCLIB_API int hash2(McVec3i key, int b2);

/// Computes smallest prime greater than minSize.
MCLIB_API int computePrime(int minSize);

//--------------------------------------------------------------
//  Implementation
//--------------------------------------------------------------

/// @if EXCLUDETHIS

template<class Key, class Value>
McHashTableDouble<Key,Value>::McHashTableDouble(const Value& val)
    : defaultValue(val)
{
    size        = 11;
    base        = 8;
    computeBase2();

    nItems      = 0;
    nDelItems   = 0;
    iterIdx     = 0;
    table.resize(size);
    table.fill(0);
    delItems.resize(size);
    delItems.fill(0);
}

template<class Key, class Value>
McHashTableDouble<Key,Value>::McHashTableDouble(const Value& val,
                                                int minSize)
    : defaultValue(val)
{
    size        = computePrime(minSize);
    base        = 8;
    computeBase2();

    nItems      = 0;
    nDelItems   = 0;
    iterIdx     = 0;
    table.resize(size);
    table.fill(0);
    delItems.resize(size);
    delItems.fill(0);
}

template<class Key, class Value>
void McHashTableDouble<Key,Value>::computeBase2() {
#if 0
    base2       = 64;
    while (base2 > size)
        base2 /= 2;
#endif
    // changed from the above code to size-1.
    // base2 determines the range of the second hashfunction hash2 [1..base2]
    base2 = size-1;
}

template<class Key, class Value>
McHashTableDouble<Key,Value>::McHashTableDouble(const Value& val,
                                                int minSize, int max)
    : defaultValue(val)
{
    size        = computePrime(minSize);
    computeBase2();

    base        = 2;
    while(base < max) { base *= 2; }

    nItems      = 0;
    nDelItems   = 0;
    iterIdx     = 0;
    table.resize(size);
    table.fill(0);
    delItems.resize(size);
    delItems.fill(0);
}

template<class Key, class Value>
McHashTableDouble<Key,Value>::~McHashTableDouble()
{
    // free all table elements
    for (int i=0; i<table.size(); i++) {
        if (table[i]) delete table[i];
    }
}

template<class Key, class Value>
int McHashTableDouble<Key,Value>::insert(const Key& key, const Value& value)
{
    int idx, offset, firstIdx;
    idx      = hash(key, base, size);
    offset   = -1;
    firstIdx = -1;

    // due to deleted elements, some keys would not be found
    // if we did not keep track about delItems
    while (table[idx] || delItems[idx]) {
        if (!delItems[idx]) { // table[idx] != 0
            if (compare(table[idx]->key,key)==0) {
                table[idx]->value = value; // override old value
                return 0;
            }
        }
        else if (firstIdx == -1) {
            // empty element with index idx
            // found which was formerly filled
            firstIdx = idx;
        }
        if (offset == -1) // hash2(..) must only be called once
            offset = hash2(key, base2);
        idx = (idx+offset) % size;
    }
    if (firstIdx != -1) { // bucket found which was formerly filled
        idx = firstIdx;
        delItems[idx] = 0;
        nDelItems--;
    }
    table[idx]    = new Item(key,value);
    nItems++;

    // if table is filled up to 3/4th, enlarge it;
    // the sum of nItems+nDelItems must be tested, otherwise
    // if nItems+nDelItems==size the search for an element or a
    // new bucket would never stop
    if (nItems+nDelItems > 0.75*size) {
        enlargeTable();
    }
    return 1;
}

template<class Key, class Value>
Value* McHashTableDouble<Key,Value>::insert(const Key& key)
{
    if (nItems+nDelItems > 0.75*size) {
        enlargeTable();
    }

    int idx, offset, firstIdx;
    idx      = hash(key, base, size);
    offset   = -1;
    firstIdx = -1;

    while (table[idx] || delItems[idx]) {
        if (!delItems[idx]) {
            if (compare(table[idx]->key,key)==0) {
                return &table[idx]->value;
            }
        }
        else if (firstIdx == -1) {
            firstIdx = idx;
        }
        if (offset == -1)
            offset = hash2(key, base2);
        idx = (idx+offset) % size;
    }
    if (firstIdx != -1) {
        idx = firstIdx;
        delItems[idx] = 0;
        nDelItems--;
    }
    Item* newItem = new Item(key,defaultValue);
    table[idx]    = newItem;
    nItems++;
    return &newItem->value;
}

template<class Key, class Value>
int McHashTableDouble<Key,Value>::remove(const Key& key)
{
    int idx, offset;
    idx = hash(key, base, size);
    offset = -1;

    // compare insert(..)
    while (table[idx] || delItems[idx]) {
        if (!delItems[idx]) {
            if (compare(table[idx]->key,key)==0) {
                delete table[idx];
                table[idx]    = 0;
                delItems[idx] = 1;
                nItems--;
                nDelItems++;
                if (nItems < 0.1*size) reduceTableSize();
                return 1;
            }
        }
        if (offset == -1)
            offset = hash2(key, base2);
        idx = (idx+offset) % size;
    }
    return 0;
}

template<class Key, class Value>
void McHashTableDouble<Key,Value>::removeAll()
{
    for (int i=0; i<size; i++) {
        if (table[i]) delete table[i];
    }
    size = 11;
    computeBase2();
    table.resize(size);
    table.fill(0);

    delItems.resize(size);
    delItems.fill(0);

    nItems    = 0;
    nDelItems = 0;
    iterIdx   = 0;
}

template<class Key, class Value>
int McHashTableDouble<Key,Value>::insertNewTable(const Key& key)
{
    int idx, offset;
    idx      = hash(key, base, size);
    offset   = -1;

    while (table[idx]) {
        if (compare(table[idx]->key,key)==0) {
            return idx;
        }
        if (offset == -1)
            offset = hash2(key, base2);
        idx = (idx+offset) % size;
    }
    return idx;
}

template<class Key, class Value>
void McHashTableDouble<Key,Value>::enlargeTable()
{
    int i;
    McDArray<Item*> oldTable = table;
    size = 2*size; // at least double size
    size = computePrime(size);
    computeBase2();

    table.resize(size);
    table.fill(0);

    delItems.resize(size);
    delItems.fill(0);

    nItems    = 0;
    nDelItems = 0;
    iterIdx   = 0;
    int idx;
    for (i=0; i<oldTable.size(); i++) {
        if (oldTable[i]) {
            idx = insertNewTable(oldTable[i]->key);
            table[idx] = oldTable[i];
            nItems++;
        }
    }
}

template<class Key, class Value>
void McHashTableDouble<Key,Value>::reduceTableSize()
{
    int i;
    McDArray<Item*> oldTable = table;
    size = (2*nItems > 11 ? 2*nItems : 11);
    size = computePrime(size);
    computeBase2();

    table.resize(size);
    table.fill(0);

    delItems.resize(size);
    delItems.fill(0);

    nItems    = 0;
    nDelItems = 0;
    iterIdx   = 0;
    for (i=0; i<oldTable.size(); i++) {
        if (oldTable[i]) {
            insert(oldTable[i]->key, oldTable[i]->value);
            delete oldTable[i];
        }
    }
}

template<class Key, class Value>
int McHashTableDouble<Key,Value>::next(Key& key, Value& value)
{
    if (nItems == 0) return 0;

    while (!table[iterIdx]) { iterIdx = (iterIdx+1)%size; }
    key     = table[iterIdx]->key;
    value   = table[iterIdx]->value;

    iterIdx = (iterIdx+1)%size;
    return 1;
}

template<class Key, class Value>
void McHashTableDouble<Key,Value>::printStat()
{
    printf("Hash table contains %d buckets, %d items and %d deleted items\n",
           size, nItems, nDelItems);
}

/// @endif

#endif

/// @}

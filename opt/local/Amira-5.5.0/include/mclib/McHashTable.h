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
#ifndef MC_HASHTABLE_H
#define MC_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "McVec2i.h"
#include "McVec3i.h"
#include "McVec4i.h"
#include "McWinDLLApi.h"

template<class Key, class Value> class McHashTableIterator;

template< class T >
int compare( T const & a, T const & b )
{
    return a==b ? 0 : 1;
}

template<>
inline int compare( char const * const & a, char const * const & b )
{
    return strcmp(a,b);
}


/** Dictionary implemented by hashing with chaining.

    This class stores a set of key-value pairs. The keys are unique,
    i.e., for each key only one value can be stored. The value for
    a given key can be easily accessed via an index operator. If no
    value yet exists for a key, the index operator inserts a default
    value into the dictionary and returns it. The default value has
    to be specified in the constructor. In order to check if a key
    is already defined the method @c lookup can be used.

    Any data type or class can be used as a key or as a value as long
    as a public copy constructor and a public assignment operator are
    provided. Hashing and comparison relies on the existence of global
    functions @c hash() and @c compare(). For character strings and
    integers both type of functions are already provided.

    To reduce the costs implied by copying large data objects you may
    use appropriate pointers as key or value types. Preferable these
    should be smart pointers as provided by McHandle.

    You should avoid to include McHashTable.h in other headers.
    Prefere to use a forward declaration
    \code
        template <class Key, class Value> class McHashTable;
    \endcode
    in the header and include McHashTable.h only in the cpp file.
*/
template<class Key, class Value> class McHashTable
{
  public:
    /// Constructor takes default value for hash entries.
    McHashTable(const Value& defaultValue);

    /// Copy constructor.
    McHashTable(const McHashTable<Key,Value> &table);

    /// Destructor.
    ~McHashTable();

    /// Returns number of key-value pairs in the dictionary.
    int size() const { return nItems; }

    /** Index operator providing read and write access, If the given
        key does not already exist, a new table entry is created. The
        value of this entry is initialized with the default value
        specified in the constructor. */
    Value& operator[](const Key& key);

    /// Assignment operator.
    McHashTable<Key,Value>& operator=(const McHashTable<Key,Value> &table);

    /** Inserts or updates a value for a given key. If the key does not
        already exist, a new table entry is created. The value of this
        entry is initialized with the second argument. If the key does
        already exist its value is overridden.

        The return value indicates if a new entry has been created (true
        is returned) or if the key did already exit (false is returned). */
    bool insert(const Key& key, const Value& val);

    /** Returns a pointer to the value associated with a key. If the
        key does not exist a null pointer is returned. This method can be
        used to check if some key has already been inserted into the
        dictionary. */
    Value* lookup(const Key& key) const;

    /** Removes a key and its associated value from the hash table. The
        return value indicates if the key did exist (true is returned)
        or not (the dictionary remains unchanged and false is returned).

        Note, that if the value is a pointer type the object the value
        points to will not be deleted. To achieve this it is recommended
        to use smart pointers (see McHandle) instead of C pointers. */
    bool remove(const Key&);

    /** Removes all key-value pairs from the hash table.

        Note, that if the values of the hash table are pointers the objects
        the values point to will not be deleted. To achieve this it is
        recommended to use smart pointers (see McHandle) instead of C
        pointers. */
    void removeAll();

    /** Resets the built-in iterator. After resetting the iterator next()
        returns the first key-value pair in the dictionary. */
    void resetIter() { iterIdx=0; iterItem=bucketList[0]; }

    /** Successively returns all key-value pairs using the built-in iterator.
        If there are no more entries in the hashtable @c key and @c value
        are left unmodified and false is returned. Othwerwise true is
        returned. In addition to the built-in iterator also one or more
        external iterators of type McHashTableIterator can be used. */
    bool next(Key& key, Value& value);

    /// Print out some statistics (for debugging only).
    void printStat();

  protected:
    struct Item {
        Key key;
        Value value;
        Item* next;
        Item(const Key& k, const Value& v) : key(k), value(v), next(0) { }
    };

    int     mask;          // Mask value used to truncate hash index
    int     nItems;        // Number key-value pairs stored
    Item**  bucketList;    // Pointer to bucket array
    Item*   staticList[2]; // Static array initially avoids malloc()
    int     iterIdx;       // Bucket index used for iteration
    Item*   iterItem;      // Current item in iteration
    Value   defaultValue;  // Should this be static or a pointer ?

    void rebuildTable();   // Adjusts size of bucket array.

    friend class McHashTableIterator<Key,Value>;
};

/** Iterator for the McHashTable template class. McHashTable already
    provides a built-in iterator. However, in some situations you may
    want to iterate multiple times over all entries of the hash table
    with different iterators. In such cases you need to use this class
    as an external iterator.

    Example:
    \code
    McHashTable<const char*,int> scores(0);
    scores["john"] = 17;
    scores["susan"] = 23;
    scores["gerald"] = 12;

    int value;
    const char* key;
    McHashTableIterator<const char*,int> it(scores);
    while (it.next(key,value))
        printf("name=%s score=%d\n", key, value);
    \endcode
*/
template<class Key, class Value> class McHashTableIterator
{
  public:
    /// Constructor, creates an iterator in resetted state.
    McHashTableIterator(const McHashTable<Key,Value>& table);

    /** Resets the iterator. After resetting the iterator next()
        returns the first key-value pair in the dictionary. */
    void resetIter();

    /** Successively returns all key-value pairs. If there are no more
        entries in the hashtable @c key and @c value are left
        unmodified and false is returned. Othwerwise true is returned. */
    bool next(Key& key, Value& value);

  protected:
    const McHashTable<Key,Value>& table;
    typename McHashTable<Key,Value>::Item* iterItem;
    int iterIdx;
};

/** Hash functions. */

/// Hash function for character strings.
MCLIB_API int hash(const char* str);

/// Hash function for pointers.
MCLIB_API int hash(void* ptr);

MCLIB_API int hash(const void* ptr);

/// Hash function for integers.
MCLIB_API int hash(int i);

/// Hash function for McVec2i.
MCLIB_API int hash(McVec2i v);

/// Hash function for McVec3i.
MCLIB_API int hash(McVec3i v);

/// Hash function for McVec4i.
MCLIB_API int hash(McVec4i v);


//--------------------------------------------------------------
//  Implementation
//--------------------------------------------------------------

/// @if EXCLUDETHIS

template<class Key, class Value>
McHashTable<Key,Value>::McHashTable(const Value& val) : defaultValue(val)
{
    bucketList = staticList;
    staticList[0] = staticList[1] = 0;
    mask = 1;
    nItems = 0;
}

template<class Key, class Value>
McHashTable<Key, Value>::McHashTable(const McHashTable<Key,Value>& table)
{
    // Initialize hash table.
    bucketList = staticList;
    staticList[0] = staticList[1] = 0;
    mask = 1;
    nItems = 0;

    // Copy values from table.
    *this = table;
}

template<class Key, class Value>
McHashTable<Key,Value>::~McHashTable()
{
    removeAll();
    if (bucketList!=staticList)
        free(bucketList);
}

template<class Key, class Value>
bool McHashTable<Key,Value>::insert(const Key& key, const Value& value)
{
    int i = hash(key) & mask;
    Item* item = bucketList[i];

    while (item) {
        if (compare(item->key,key)==0) {
            item->value = value;
            return false;
        }
        item = item->next;
    }

    item = new Item(key,value);
    item->next = bucketList[i];
    bucketList[i] = item;
    nItems++;

    if (nItems>2*mask+1)
        rebuildTable();
    return true;
}

template<class Key, class Value>
Value& McHashTable<Key,Value>::operator[](const Key& key)
{
    int i = hash(key) & mask;
    Item* item = bucketList[i];

    while (item) {
        if (compare(item->key,key)==0)
            return item->value;
        item = item->next;
    }

    item = new Item(key,defaultValue);
    item->next = bucketList[i];
    bucketList[i] = item;
    nItems++;

    if (nItems>2*mask+1)
        rebuildTable();
    return item->value;
}

template<class Key, class Value>
McHashTable<Key,Value>&
McHashTable<Key, Value>::operator=(const McHashTable<Key,Value>& table)
{
    // Remove all existing items.
    removeAll();

    // Reset defaultValue.
    defaultValue = table.defaultValue;

    // Insert all items from table.
    McHashTableIterator<Key, Value> tableIt( table );
    tableIt.resetIter();
    Key key;
    Value value;
    while ( tableIt.next(key, value) )
        insert( key, value );

    return *this;
}

template<class Key, class Value>
Value* McHashTable<Key,Value>::lookup(const Key& key) const
{
    Item* item = bucketList[hash(key) & mask];
    while (item) {
        if (compare(item->key,key)==0)
            return &item->value;
        item = item->next;
    }
    return 0;
}

template<class Key, class Value>
bool McHashTable<Key,Value>::remove(const Key& key)
{
    int i = hash(key) & mask;
    Item* item = bucketList[i];
    if (item == 0)
        return false;

    // Check the first item of the bucket.
    if (compare(item->key,key)==0)
    {
        Item * next = item->next;

        // RK: Destructors are called here.
        // Their execution might possibly lead to deletion of the same element.
        // So before calling delete(), the item needs to be unhooked to prevent
        // multiple calls to delete() to the same object.

        // So, FIRST unhook ...
        bucketList[i] = next;
        nItems--;

        // ... and delete AFTERWARDS.
        delete item;

        return true;
    }

    // Check the following items of the bucket.
    while (item->next)
    {
        if (compare(item->next->key,key)==0)
        {
            Item * curr = item->next;
            Item * next = item->next->next;

            // RK: Destructors are called here.
            // Their execution might possibly lead to deletion of the same element.
            // So before calling delete(), the item needs to be unhooked to prevent
            // multiple calls to delete() to the same object.

            // So, FIRST unhook ...
            item->next = next;
            nItems--;

            // ... and delete AFTERWARDS.
            delete curr;

            return true;
        }
        item = item->next;
    }

    return false;
}

template<class Key, class Value>
void McHashTable<Key,Value>::removeAll()
{
    // RK: Destructors are called here.
    // Their execution might possibly lead to deletion of the same elements.
    // So before calling delete(), the items needs to be unhooked to prevent
    // multiple calls to delete() to the same object.

    // Collect all items to be deleted.
    Item * itemsToDelete = 0;

    for ( int i=0 ; i<=mask ; i++ )
    {
        Item * curr = bucketList[i];

        while (curr)
        {
            Item * next = curr->next;

            // Prepend to chain, ...
            curr->next = itemsToDelete;

            // ... set new head, ...
            itemsToDelete = curr;

            // ... advance to next one.
            curr = next;
        }

        bucketList[i]=0;
    }
    nItems = 0;

    // Now, the hash table is empty and in a valid state.
    // It is time to delete the objects, there is now
    // no need to fear double delete().

    Item * curr = itemsToDelete;

    while (curr)
    {
        Item * next = curr->next;
        delete curr;
        curr = next;
    }
}


template<class Key, class Value>
void McHashTable<Key,Value>::rebuildTable()
{
    Item** oldList = bucketList;
    int size = mask+1;
    mask = (mask << 1) + 1;
    bucketList = (Item**) calloc(2*size,sizeof(Item));

    for (int i=0; i<size; i++) {
        Item* item = oldList[i];
        while (item) {
            int k = hash(item->key) & mask;
            Item* next = bucketList[k];
            Item* oldNext = item->next;
            bucketList[k] = item;
            item->next = next;
            item = oldNext;
        }
    }

    if (oldList != staticList) free(oldList);
}

template<class Key, class Value>
bool McHashTable<Key,Value>::next(Key& key, Value& value)
{
    while (1) {
        while (iterItem) {
            key = iterItem->key;
            value = iterItem->value;
            iterItem = iterItem->next;
            return true;
        }
        if (++iterIdx > mask) {
            iterItem = bucketList[iterIdx=0];
            return false;
        }
        iterItem = bucketList[iterIdx];
    }
}

template<class Key, class Value>
void McHashTable<Key,Value>::printStat()
{
    int i, total=0, noZero=0, count[10];
    for (i=0; i<10; i++) count[i] = 0;

    for (i=0; i<=mask; i++) {
        int n = 0;
        Item* item = bucketList[i];
        while (item) { n++; item = item->next; }
        if (n<10) count[n]++;
        if (n) { total += n; noZero++; }
    }

    printf("Hash table contains %d buckets and %d items\n",
        mask+1, nItems);
    for (i=0; i<10; i++)
        printf("%3d buckets with %d entries\n", count[i], i);
    if (noZero)
        printf("Average search distance is %.1f\n", (float) total/noZero);
}

template<class Key, class Value>
McHashTableIterator<Key,Value>::McHashTableIterator(const McHashTable<Key,Value>& t) : table(t)
{
    iterIdx = 0;
    iterItem = table.bucketList[0];
}

template<class Key, class Value>
void McHashTableIterator<Key,Value>::resetIter()
{
    iterIdx = 0;
    iterItem = table.bucketList[0];
}

template<class Key, class Value>
bool McHashTableIterator<Key,Value>::next(Key& key, Value& value)
{
    while (1) {
        while (iterItem) {
            key = iterItem->key;
            value = iterItem->value;
            iterItem = iterItem->next;
            return true;
        }
        if (++iterIdx > table.mask) {
            iterItem = table.bucketList[iterIdx=0];
            return false;
        }
        iterItem = table.bucketList[iterIdx];
    }
}

/// @endif

#endif

/// @}

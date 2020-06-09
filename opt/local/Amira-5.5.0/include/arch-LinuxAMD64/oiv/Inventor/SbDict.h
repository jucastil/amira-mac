/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_DICT_
#define _SB_DICT_

#include <Inventor/SbBase.h>
#include <Inventor/SbString.h>
#include <Inventor/SbPList.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbDictEntry (internal to SB)
//
//  A dictionary is stored as a collection of entries, each of which
//  is an SbDictEntry. It contains the key and value for the entry and
//  a link to create lists of entries.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTORBASE_API SbDictEntry {
 private:
  uintptr_t key;
  void *value;
  
  SbDictEntry *next;
  
  // Constructor
  SbDictEntry(uintptr_t k, void *v)     { key = k; value = v; };
  
  friend class SbDict;
};

class SbThreadRWMutex ;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbDict
//
//  This is a dictionary mapping (unsigned long) integer keys to (void *) data
//  pointers.
//
//////////////////////////////////////////////////////////////////////////////

SoEXTENDER class INVENTORBASE_API SbDict {
 public:
  // Constructor
  SbDict(int entries = 251);
  
  // Destructor
  ~SbDict();
  
  // Calls given routine (passing value) for each entry in dictionary.
  //  The order of entries is not guaranteed to mean anything.
  void applyToAll(void (*rtn)(uintptr_t key, void *value));
  
  // Calls given routine (passing value,data) for each entry in dictionary.
  //  The order of entries is not guaranteed to mean anything.
  void applyToAll(void (*rtn)(uintptr_t key, void *value, void *data), void *data);
  
  // Removes all entries from dictionary.
  void clear();
  
  // Enters a key,value pair into the dictionary. Overwrites entry and
  //  returns FALSE if key already exists.
  SbBool enter(uintptr_t key, void *value);
  
  // Finds entry with given key, setting value to point to value.
  //  Returns FALSE if no such entry.
  SbBool find(uintptr_t key, void *&value) const;
  
  // Makes two SbPLists, one for keys and the other for values.
  //  The order of entries is not guaranteed to mean anything.
  void makePList(SbPList &keys, SbPList &values);
  
  // Removes the entry with the given key. Returns FALSE if no such entry.
  SbBool remove(uintptr_t key);
  
 private:
  // Entries are stored as an external hash table of SbDictEntry instances.
  int tableSize; // Entries in table
  SbDictEntry **buckets; // Hash table
  
  SbDictEntry *&findEntry(uintptr_t key) const;
  static void addEntryToPLists(uintptr_t key, void *value, void *data);

  SbThreadRWMutex * mutex;
};

#endif /* _SB_DICT_ */

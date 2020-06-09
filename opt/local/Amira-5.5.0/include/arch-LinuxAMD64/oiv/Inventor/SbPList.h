/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Paul S. Strauss (MMM yyyy)
** Modified by : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SB_PLIST_
#define _SB_PLIST_

#include <Inventor/SbBase.h>

class SbVec3f;

/** 
 * List of generic (void *) pointers.
 * 
 * @ingroup Basics
 * 
 * @DESCRIPTION 
 *   This class manages a dynamic list of generic void * pointers. This class allows
 *   random access, insertion, and removal of pointers.
 *   Changes in SbPList can be detected by attaching an SoListSensor to this list.
 *
 * @SEE_ALSO
 *   SoListSensor
 *
 * 
 * [OIV-WRAPPER-NO-WRAP]
 */ 

class INVENTORBASE_API SbPList {

 public:

  /**
   * Default constructor.  The list is initially empty.
   */
  SbPList();

  /**
   * Constructor. @B initSize @b specifies an initial size for the
   * list, which is useful as an optimization if you can estimate the length of the
   * list before you construct it.
   */
  SbPList(int initSize);

  /**
   * Constructor. It returns a copy of the specified SbPList.
   */
  SbPList(const SbPList &pl);

  /**
   * Destructor.
   */
  virtual ~SbPList();

  /**
   * Adds given pointer to end of list.
   */
  void append(void * ptr);

  /**
   * Returns index of given pointer in list, or -1 if not found.
   */
  int find(const void *ptr) const;

  /**
   * Inserts given pointer in list before pointer with given index.
   */
  void insert(void *ptr, int addBefore);

  /**
   * Removes pointer with given index.
   */
  void remove(int which);

  /**
   * Returns number of pointers in list.
   */
  inline int getLength() const
  { return nPtrs; }

  /** 
   * Removes all pointers after one with given index, inclusive
   */
  void truncate(int start);

  /**
   * Copies a list.
   */
  void copy(const SbPList &pl);

  /**
   * Assignment operator: copies list into this list.
   */
  SbPList &operator =(const SbPList &pl);

  /**
   * Returns pointer with given index.
   */
  void *&operator [](int i) const;

  /**
   * Equality operator.
   */
  int operator ==(const SbPList &pl) const;

  /**
   * Inequality operator.
   */
  int operator !=(const SbPList &pl) const;

 SoINTERNAL public:

  void *get(int i) const;
  void set(int i, void *j);
  void **getArray();

  // internal public call to expand function (see below) in order to reserve more memory in the list.
  // same name than stl reserve function
  void reserve(int size)
  { expand(size); }

protected:
  // Number of pointers used
  int nPtrs;

  // There are three(!) methods to expand the list.  grow() is used
  // when space is dynamically created, and needs to be initialized
  // to NULL:
  void grow(int max) const;

  // setSize is used by grow and in other places internally where we
  // know that nothing needs to be initialized to NULL.
  void setSize(int size);

 private:

  // NOTE: this must be called only if the number of elements in the two
  // lists is the same, otherwise badness could result
  int compare(const SbPList &pl) const;

  // The collection of pointers
  void **ptrs;

  // Number of pointers allocated
  int ptrsSize;

  // expand is the lowest level routine.  It just reallocates the
  // array and copies over the old values.
  void expand(int size);

};

#ifndef HIDDEN_FROM_DOC
//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbIntList
//
//  List of generic (void *) pointers. SbIntList allows random access,
//  insertion, and removal.
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTORBASE_API SbIntList : public SbPList {
  
 public:
  // Constructors, similar to SbPList
  SbIntList();
  SbIntList(int initSize);
  
  // Adds given integer to end of list.
  void append(int integer);

  void set(int index, int val);
  
  // Returns index of given integer in list, or -1 if not found
  int find(int integer);
  
  // Inserts given integer in list before integer with given index
  void insert(int integer, int addBefore);
  
  // Returns int with given index.
  int &operator [](int i) const;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbVec3fList
//
//  List of vectors. Probably mostly used for vertices of polygons
//
//////////////////////////////////////////////////////////////////////////////

SoINTERNAL class INVENTORBASE_API SbVec3fList : public SbPList {
  
 public:
  
  SbVec3fList();
  ~SbVec3fList();
  
  // Adds given SbVec3f pointer to end of list.
  void append(SbVec3f *vec);
  
  // Inserts given integer in list before integer with given index
  void insert(SbVec3f *vec, int addBefore);
  
  // Returns SbVec3f pointer with given index.
  SbVec3f *operator [](int i) const;
};

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbStringList
//
//  A list of strings.  This list is used to list classes associated with 
//  a specific error.
//
//////////////////////////////////////////////////////////////////////////////

class SbString;
/**
 * [OIV-WRAPPER-NO-WRAP]
 */
SoEXTENDER class INVENTORBASE_API SbStringList : public SbPList {

 public:

  // Adds given SbString pointer to end of list.
  void append(SbString *string);

  // Returns index of given SbString in list, or -1 if not found (pointer check)
  int find(SbString *string);

  // Returns index of given SbString in list, or -1 if not found (string check)
  int findString( const SbString &string);

  // Inserts given SbString in list before SbString with given index
  void insert(SbString *string, int addBefore);

  // Returns SbString pointer with given index.
  SbString *&operator [](int i) const;

  /**
   * This function splits a string according to a separator.
   *
   * @param str The string to split.
   * @param separator The separator which is used to split the string.
   *
   * @return The list of strings.
   */
  static SbStringList split( const SbString& str, const SbString& separator );

};
#endif // HIDDEN_FROM_DOC

#endif /* _SB_PLIST_ */


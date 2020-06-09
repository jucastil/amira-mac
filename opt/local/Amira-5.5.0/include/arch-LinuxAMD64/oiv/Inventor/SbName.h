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
** Modified by : VSG (oct 2011)
**=======================================================================*/

#ifndef _SB_NAME_
#define _SB_NAME_

#ifndef HIDDEN_FROM_DOC

#include <Inventor/SbString.h>

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbNameEntry (internal to SB)
//
//  This is used to make lists of SbName instances.
//
//////////////////////////////////////////////////////////////////////////////


// The size of a chunk is about a page (4K) minus room for other stuff
// in the structure

SoINTERNAL class INVENTORBASE_API SbNameEntry
{

 public:
  // Returns TRUE if entry's string is empty ("")
  SbBool isEmpty() const;

  // Returns TRUE if entry's string is same as passed string
  SbBool isEqual(const char *s) const;

  // Returns TRUE if entry's string is lower than passed string
  bool isLowerThan(const SbNameEntry *n) const;

  // Initializes/Unload SbNameEntry class
  static void initClass();
  static void exitClass();

  // Reomoves string from table
  static SbBool remove(const char *s);

 private:

   class SbNameChunk
   {
   public:
     SbNameChunk();
     ~SbNameChunk();
     char* mem;                // Chunk o'memory
     char* curByte;            // Current byte of chunk
     size_t bytesLeft;         // Bytes left in chunk
     SbNameChunk* next; // Pointer to next chunk
   };
 
  static int nameTableSize;  // Number of buckets in name table
  static SbNameEntry **nameTable;    // Array of name entries
  static SbNameChunk* chunk;  // Chunk of memory for string storage
  static int chunkSize;

  const char *string; // String for this entry
  bool stringDup;
  uint32_t hashValue; // Its hash value
  SbNameEntry *next;  // Pointer to next entry

  ~SbNameEntry();

  // Constructor
  SbNameEntry(const char *s, uint32_t h, SbNameEntry *n);

  // Inserts string in table
  static const SbNameEntry *insert(const char *s);

  // Finds string entry in table
  static SbNameEntry *&findEntry(const char *s);

  friend class SbName;
};

inline SbNameEntry::SbNameEntry(const char *s, uint32_t h, SbNameEntry *n)
{
  string = s;
  hashValue = h;
  next = n;
  stringDup = false;
}

// Returns TRUE if entry's string is empty ("")
inline SbBool SbNameEntry::isEmpty() const
{
  return (string[0] == '\0');
}

// Returns TRUE if entry's string is same as passed string
inline SbBool SbNameEntry::isEqual(const char *s) const
{
  return (string[0] == s[0] && ! strcmp(string, s));
}

// Returns TRUE if entry's string is lower than passed string
inline bool SbNameEntry::isLowerThan(const SbNameEntry *n) const
{
  return ( strcmp(string, n->string )<0);
}

#endif // HIDDEN_FROM_DOC

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SbName
//
//  An SbName is a character string that is stored in a special table.
//  When a string is stored in this table, a pointer to the storage is
//  returned. Two identical strings will return the same pointer. This
//  means that comparison of two SbNames for equality can be
//  accomplished by comparing their pointers!
//
//////////////////////////////////////////////////////////////////////////////


/**
 * Character string stored in a hash table.
 *
 * @ingroup Basics
 *
 * @DESCRIPTION
 *   This class of strings stores the string in a hash table. It is used by the Open
 *   Inventor toolkit for keywords and other unique names. It is not recommended for
 *   general use (only in the context of Open Inventor objects). When a string is
 *   stored in this table, a pointer to the storage is returned. Two identical
 *   strings will return the same pointer. This means that comparison of two SbNames
 *   for equality can be accomplished by comparing their identifiers. SbNames are
 *   used for strings which are expected to show up frequently, such as node names.
 *
 *   @B Note: @b SbName does not support Unicode strings.
 *
 * @SEE_ALSO
 *    SbString
 *
 *
 * [OIV-WRAPPER-NO-WRAP]
 */

class INVENTORBASE_API SbName
{
 public:
  /**
   * Constructor.
   */
  SbName();

  /**
   * Constructor.
   */
  SbName(const char *s) { entry = SbNameEntry::insert(s); }

  /**
   * Constructor.
   */
  SbName(const SbString &s) { entry = SbNameEntry::insert(s.toLatin1()); }

  /**
   * Constructor.
   */
  SbName(const SbName &n) { entry = n.entry; }

  /**
   * Destructor.
   */
  ~SbName();

  /**
   * Returns pointer to the character string.
   */
  const char* getString() const { return entry->string; }

  /**
   * Returns length of string.
   */
  int getLength() const { return static_cast<int>(strlen(entry->string)); }

  /**
   * Returns TRUE if given character is a legal starting character for an identifier.
   */
  static SbBool isIdentStartChar(char c);

  /**
   * Returns TRUE if given character is a legal nonstarting character for an
   * identifier.
   */
  static SbBool isIdentChar(char c);

  /**
   * Returns TRUE if given character is a legal starting character
   * for an SoBase's name.
   */
  static SbBool isBaseNameStartChar(char c);

  /**
   * Returns TRUE if given character is a legal nonstarting
   * character for an SoBase's name.
   */
  static SbBool isBaseNameChar(char c);

  /**
   * Unary "not" operator; returns TRUE if string is empty ("").
   */
  int operator !() const   { return entry->isEmpty(); }

  /**
   * Equality operator for SbName/char* and SbName/SbName comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbName &n, const char *s)
  { return n.entry->isEqual(s); }

  /**
   * Equality operator for SbName/char* and SbName/SbName comparison.
   */
  INVENTORBASE_API friend int operator ==(const char *s, const SbName &n)
  { return n.entry->isEqual(s); }

  /**
   * Equality operator for SbName/char* and SbName/SbName comparison.
   */
  INVENTORBASE_API friend int operator ==(const SbName &n1, const SbName &n2)
  { return n1.entry == n2.entry; }

  /**
   * Inequality operator for SbName/char* and SbName/SbName comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbName &n, const char *s)
  { return ! n.entry->isEqual(s); }

  /**
   * Inequality operator for SbName/char* and SbName/SbName comparison.
   */
  INVENTORBASE_API friend int operator !=(const char *s, const SbName &n)
  { return ! n.entry->isEqual(s); }

  /**
   * Inequality operator for SbName/char* and SbName/SbName comparison.
   */
  INVENTORBASE_API friend int operator !=(const SbName &n1, const SbName &n2)
  { return n1.entry != n2.entry; }

  /**
   * "less than" relational operator for SbName / SbName that returns
   * TRUE if the first operand is less than the second,
   * FALSE otherwise.
   */
  INVENTORBASE_API friend bool operator < (const SbName &n1, const SbName &n2)
  { return n1.entry->isLowerThan(n2.entry); }

  /**
   * Writes the SbName to the specified output stream.
   */
  INVENTORBASE_API friend std::ostream& operator << (std::ostream& os, const SbName& n)
  {
    return os << n.getString();
  }

SoINTERNAL public:
  static void enableUseNameCompat( const SbBool enable )
  { s_useNameCompat = enable; }

  static SbBool useNameCompat()
  { return s_useNameCompat; }

 private:
  // Name string storage
  const SbNameEntry *entry;

  // Flag to control use of valid names
  static SbBool s_useNameCompat;
};

#endif // _SB_NAME_

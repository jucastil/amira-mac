/*=======================================================================
** SGI_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nick Thompson (MMM yyyy)
** Modified by : Gavin Bell (MMM yyyy)
**=======================================================================*/
/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Modified by : VSG (MMM YYYY)
**=======================================================================*/


#ifndef _SO_TYPE_
#define _SO_TYPE_

#include <Inventor/SbString.h>
#include <Inventor/SbDict.h>
#include <Inventor/STL/ostream>

class SoTypeList;
struct SoTypeData;
class ScDataInputStream;

typedef void *SoTypeFromNameCB(SbName name);

/**
 * Stores runtime type information.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 * The SoType class keeps track of runtime type information in Open Inventor. Each
 * type is associated with a given name, so lookup is possible in either
 * direction.
 *
 * Many Open Inventor classes request a unique SoType when they are initialized.
 * This type can then be used to find out the actual class of an instance when only
 * its base class is known, or to obtain an instance of a particular class given
 * its type or name.
 *
 * Note that the names associated with types of Open Inventor classes do not contain
 * the "So" prefix.
 *
 * @SEE_ALSO
 * SoAction,
 * SoBase,
 * SoDetail,
 * SoError,
 * SoEvent,
 * SoField
 *
 *
 * [OIV-WRAPPER-NO-WRAP]
 */

class INVENTORBASE_API SoType {

#ifdef __DELTA
#  pragma __nondynamic_class
#endif

 public:

  /**
   * Returns the type associated with the given name.
   */
  static SoType fromName(const SbName &name);

  /**
   * Returns the name associated with a type.
   */
  SbName getName() const;

  /**
   * Returns the type of the parent class.
   */
  SoType getParent() const;

  /**
   * Returns an always-illegal type. Useful for returning errors.
   */
  static SoType badType();

  /**
   * Returns TRUE if the type is a bad type.
   */
  SbBool isBad() const;

  /**
   * Returns TRUE if the type is derived from type @B t@b.
   */
  SbBool isDerivedFrom(const SoType &t) const;

  /**
   * Adds all types derived from the given type to the given type list. Returns the
   * number of types added.
   */
  static int getAllDerivedFrom(const SoType &type, SoTypeList &list);

  /**
   * Some types are able to create instances; for example, most nodes and engines
   * (those which are not abstract classes) can be created this way. This method
   * returns TRUE if the type supports such creation.
   */
  SbBool canCreateInstance() const;

#ifdef OIV_NET_DOC
  /**
  * Creates and returns a reference to an instance of the type. Returns NULL if an
  * instance could not be created for some reason. The reference is returned as a
  * generic reference, but can be cast to the appropriate type.
  */

#else
  /**
  * Creates and returns a pointer to an instance of the type. Returns NULL if an
  * instance could not be created for some reason. The pointer is returned as a
  * generic pointer, but can be cast to the appropriate type. For example:
  *
  * <PRE>
  * SoCube *c = (SoCube *) SoCube::getClassTypeId().createInstance();
  * </PRE>
  * is a convoluted way of creating a new instance of an SoCube.
  */

#endif //OIV_NET_DOC
  void *createInstance(SoType *overrideType=NULL) const;

  /**
   * Returns TRUE if this type is the same as the given type.
   */
  int operator ==(const SoType t) const;

  /**
   * Returns TRUE if this type is not the same as the given type.
   */
  int operator !=(const SoType t) const;

  /**
   * Less-than comparison operator that can be used to sort types.
   * This is pretty useless otherwise.
   */
  int operator <(const SoType t) const;

  /**
   * Writes the SoType to the specified output stream.
   */
  INVENTORBASE_API friend std::ostream& operator << (std::ostream& os, const SoType& t)
  {
    return os << "<" << t.getName() << "," << t.getKey() << ">";
  }

 SoEXTENDER public:

  // set a callback that will be called if unknown node are found
  static SoTypeFromNameCB *setUnknownNameCB(SoTypeFromNameCB *func);

  // Create a new type
  static SoType createType(const SoType &parent, const SbName &name,
                           void * (*createMethod)(SoType *) = NULL,
                           short data = 0);

  // Make an new type act like an existing type. The new type MUST
  // be a C++ subclass of the original (e.g. MyCubeClass must be
  // derived from SoCube), but there is no way for us to check that.
  // This can be used to get the database to create a different
  // subclass whenever it reads in an SoNode class from a file.
  static SoType overrideType(const SoType &existingType,
                             void * (*createMethod)(SoType *) = NULL);

  static SbBool removeType( const SbName &name );

 SoINTERNAL public:

  // Constructor.
  SoType();

  SoType(unsigned int storageValue) { storage.intValue = storageValue; }

  // Initialize the type system
  static void init();
  static void finish();

  // Get data
  short getData() const;

  // Returns the type key as a short
  short getKey() const;

  // Mark this type as internal; if internal, getAllDerivedFrom and
  // fromName will not return the type.
  void makeInternal();
  bool isInternal() const;

  // Get the number of types currently registed in the types dictionary.
  // This is used by SoAction when setting up the action method list.
  static int getNumTypes();

  // Get the name of the types currently registered with the key 'key'.
  static SbName getTypeName(const short key);

  inline unsigned int getStorageValue() const { return storage.intValue; }

 private:

  // SoTypes are passed around on the stack a lot, and are cast to
  // void *'s; they MUST fit into a single word.
  union
  {
    struct {
      unsigned int data : 16;
      unsigned int index : 15; // Assumes we have fewer than 32,768 types
      unsigned int isPublic :1; // 0 if is an internal class
    } storageStruct;
    unsigned int intValue;
  } storage;

  // name->sotype dictionary
  static SbDict *nameDict;

  // array of SoTypeData
  static int nextIndex;
  static int arraySize;
  static SoTypeData *typeData;

  static void expandTypeData();
  static SoType fromNameExt(const SbName &name, bool extent);

  static SoTypeFromNameCB *unknownNameFunc;
  static void *unknownNameData;

};


/**
 * Maintains a list of SoTypes.
 *
 * @ingroup General
 *
 * @DESCRIPTION
 *   This subclass of SbPList holds lists of SoType type identifiers.
 *
 * @SEE_ALSO
 *    SoType
 *
 *
 */
class INVENTORBASE_API SoTypeList : public SbPList {
 public:
  /**
   * Constructor.
   */
  SoTypeList()                        : SbPList()     {}
  /**
   * Constructor that pre-allocates storage for @B size @b types.
   */
  SoTypeList(int size)                : SbPList(size) {}
  /**
   * Constructor that copies the contents of another list.
   */
  SoTypeList(const SoTypeList &l)     : SbPList(l)    {}
  /**
   * Destructor.
   */
  ~SoTypeList()                       { truncate(0); }

  /**
   * Adds a type to the end of the list.
   */
  void                append(SoType typeId);

  /**
   * Returns index of given type in list, or -1 if not found.
   */
  int                 find(SoType typeId) const;

  /**
   * Inserts given type in list before type with given index.
   */
  void                insert(SoType typeId, int addBefore);

  /**
   * Accesses an element of a list.
   */
  SoType              operator [](int i) const;

  /**
   * Sets an element of a list.
   */
  void                set(int i, SoType typeId);
private:

  /**
   * Set a SoType value into a pointer.
   */
  static void *putSoTypeIntoPointer(const SoType& typeId);

};

#endif /* _SO_TYPE_ */


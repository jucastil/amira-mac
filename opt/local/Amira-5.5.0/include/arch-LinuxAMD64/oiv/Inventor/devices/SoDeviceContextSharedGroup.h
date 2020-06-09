/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Nicolas DAGUISE (Oct 2010)
**=======================================================================*/

#if !defined SO_DEVICE_CONTEXT_SHARE_GROUP_H
#define SO_DEVICE_CONTEXT_SHARE_GROUP_H

#include <Inventor/misc/SoRefCounter.h>
#include <Inventor/STL/set>

class SoDeviceContext;
class SoBaseContextCache;
class SoBaseContextObject;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
* @VSGEXT Shared context management class.
*
* @ingroup GLDevice
*
* @DESCRIPTION
*
* This class provides functions to manage a shared group of device contexts.
*
*/
class INVENTORBASE_API SoDeviceContextSharedGroup : public SoRefCounter
{
public:
  typedef std::set<SoDeviceContext*> SoDeviceContextSet;

  /** Creates a new SharedGroup. */
  SoDeviceContextSharedGroup();

  /** Creates a new SharedGroup with specific id. */
  SoDeviceContextSharedGroup(int id);

  /** Adds a device context to the group. */
  void add(SoDeviceContext* ctx);

  /** Removes a device context from the group. */
  void remove(SoDeviceContext* ctx);
  
  /** Sets a specific id for this shared group. */
  void setId( int id );

  /** Gets the id of this shared group. */
  int getId() const;

  /** Gets the list of contexts managed by this shared group. */
  const SoDeviceContextSet& getContexts() const;

  /** Returns the first context found in the shared group. */
  SoDeviceContext* getPrimaryContext() const;

  /** Returns TRUE if the passed context is part of the shared group*/
  bool contains(const SoDeviceContext* ctx) const;
  
  /**
   * Increment reference count.
   *
   * Object is the ContextObject that should be triggered when this context is deleted.
   */
  void ref(SoBaseContextCache* object = NULL);

  /**
   * Decrement reference count.
   *
   * Object is the ContextObject that was referenced originally.
   *
   * If this call causes the reference count to go from 1 to 0 then the
   * context is automatically deleted and all ContextObject that previously
   * called ref(SoContextObject*) will be triggered for deletion
   * (potentially asynchronously).
   */
  void unref(SoBaseContextCache* object = NULL);


  /** Returns TRUE if the specified object is already in the list of notified objects.
   *  To add or remove an object, from this list, the ref(object) and unref(object) methods can be used.
   */
  bool contains(SoBaseContextCache* object) const;

  /**
   * Force all attached objects to release the context, by calling
   * their respective release function, and force deletion of the contained context.
   */
  virtual void dispose();

SoINTERNAL public:

  void setTargetMergedGroup(SoDeviceContextSharedGroup* sharedGroup);

  /**
   * Add an object to the list to be freed when this context is bond or deleted.
   */
  void addToPendingDeleteList(SoBaseContextObject *obj);

  /**
   * Used to check if an object pointer still exists in any existing context lists and remove it.
   */
  static void checkRefIssues(SoBaseContextObject* object);
  static void checkRefIssues(SoBaseContextCache* cache);

  /** delete objects that are in the waiting to be freed list (see addToPendingDeleteList) */
  void clearPendingDeleteList();

  void setDisposing( bool b );
  
  /** returns the threadId that allocate this context */
  SbThreadId_t getThreadId() const;

  /** the global shared group id counter */
  static int getNewSharedIdGroup();

  /** Prints all shared group and which contexts are in. */
  static void printSharedGroups();

  /** Returns true if this shared group has at least one valid context.
   *  A valid context is a context which returns true when it's isValid function returns true.
   */
  bool hasValidContext() const;

  /** Returns the first valid context found in the shared group. */
  SoDeviceContext* getPrimaryValidContext() const;

protected:

  /** class destructor. delete can only be done through the ref/unref process. */ 
  virtual ~SoDeviceContextSharedGroup();

  /**
   * This function force all attached object to release the context, by calling
   * their respective release function.
   */
  void forceReleaseAttachedObject();

  bool m_isDisposing;

private:

  void commonConstructor();

  SoDeviceContextSet m_ctxSet;
  int m_id;
  SoDeviceContextSharedGroup* m_mergedGroup;

  /** Keep track of all created context */
  static SbThreadSpinlock s_listLock;
  typedef std::list<SoDeviceContext*> SoDeviceContextList;
  static SoDeviceContextList s_deviceContextList;

  /** handle list of object link to this context **/
  typedef std::list<SoBaseContextCache*> SoBaseContextCacheList;
  SoBaseContextCacheList m_listContextedObject;
  bool m_isClearingPendingList;

  /** handle list of object that must be freed when bind or delete is called */
  typedef std::set<SoBaseContextObject*> SoBaseContextObjectList;
  SoBaseContextObjectList m_waitingToBeFreed;

  /** Global sharedGroup id count. */
  static int s_sharedGroupId;

  /** keep track of which thread created this context */
  SbThreadId_t m_threadId;
};

// INLINE METHODS
inline void SoDeviceContextSharedGroup::setDisposing( bool b )
{
  m_isDisposing = b;
}
  
inline SbThreadId_t SoDeviceContextSharedGroup::getThreadId() const
{
  return m_threadId;
}

inline int SoDeviceContextSharedGroup::getNewSharedIdGroup()
{
  return s_sharedGroupId++;
}

#ifdef WIN32
#pragma warning( pop )
#endif

#endif // SO_DEVICE_CONTEXT_SHARE_GROUP_H

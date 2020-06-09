/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/

#ifndef _SO_BUFFER_OBJECT_CACHE_H_
#define _SO_BUFFER_OBJECT_CACHE_H_

#include <Inventor/SbBase.h>
#include <Inventor/STL/map>

class SoBufferObject;
class SoCpuBufferObject;
class SbThreadSpinlock;

/**
 * @VSGEXT CPUBufferObject cache management class.
 *
 * 
 * @DESCRIPTION
 *
 *  A base class used to manage a simple cache of SoCpuBufferObject objects.
 *
 *  SoBufferObject creates an instance of this class that is primarily used
 *  for the LDM tile cache (see SoLDMGlobalResourceParameters for more information).
 *  The buffer object cache can be accessed using the SoBufferObject static method
 *  getBufferObjectCache.
 *
 *  This class was added in Open Inventor 8.5.
 *
 */
class INVENTORBASE_API SoCpuBufferObjectCache
{
 public:
   
  /** 
   * Remove all unused buffers (ref count = 0) from the cache.
   */
  virtual void flush();

  /**
  * Resize cache to the given size.
  * @param New size for the cache (number of buffers). @BR
  * Default is 50 or the value specified for OIV_BUFFER_OBJECT_CACHE_SIZE.
  */
  virtual void resize( const size_t newSize );

 /**
  * Return the max size of the cache (number of buffers).
  */
  virtual size_t getSize( );

 SoINTERNAL public:
  /**
   * Constructor.
   */
  SoCpuBufferObjectCache();

  /** Destructor */
  virtual ~SoCpuBufferObjectCache();
  
  /**
  * Get a pointer to a buffer in the cache and add a reference to that buffer,
  * indicating the buffer is in use. @BR
  * Returns NULL if bufferId does not match any buffer in the cache.
  * If bufferId is valid, increments the buffer's ref count and returns its address.
  * Therefore a call to this function guarantees that, if present in cache, the 
  * buffer cannot be removed from the cache until releaseBufferRef() has been called
  * and the ref count reaches zero.  To get a point to a buffer without incrementing
  * the ref count use the getBuffer() method.
  *
  * @param bufferId of buffer to retrieve.
  */
  virtual SoCpuBufferObject* getBufferRef( const uint64_t bufferId );

  /** 
   * Add the given buffer to the cache. @BR
   * If the buffer was successfully inserted in the cache, returns a unique
   * non-zero id that can be used with the other methods in this class and 
   * initializes the buffer's ref count to 1.  Therefore the buffer cannot
   * be removed from the cache until releaseBufferRef() has been called. @BR
   * Returns 0 if the insertion failed.
   *
   * @param buffer object to be added in the cache
   */
  virtual uint64_t addInCache( SoCpuBufferObject* bufferObject, const uint64_t& bufferSignature = 0 );

  /**
  * Release a reference to a buffer in the cache, indicating the buffer is no longer
  * in use. @BR
  * Returns false if the specified buffer was not found in the cache or its ref count
  * is already zero, else returns true and decrements the buffer's ref count. A buffer
  * cannot be removed from the cache until its ref count reaches zero (addInCache sets
  * the initial ref count to 1). Even when its ref count reaches zero, the buffer will
  * remain in the cache until internal management removes it, for example because the
  * space is needed for a new buffer.  This method must be called when the buffer is
  * no longer in use, otherwise it will never be removed from the cache.
  *
  * @param bufferId of buffer to release.
  */
  virtual bool releaseBufferRef ( const uint64_t bufferId );

  /**
  * Get a pointer to a buffer in the cache without incrementing the ref count. @BR
  * Returns NULL if the buffer Id does not match any buffer in cache. Warning: This 
  * method must be called between getBufferRef/addInCache and releaseBufferRef 
  * to guarantee the buffer is valid
  *
  * @param bufferId of buffer to retrieve.
  */
  SoCpuBufferObject* getBuffer(const uint64_t bufferId);

  SoINTERNAL public:

  void getInternalCounter(  uint64_t &nbCacheAccess, uint64_t& nbCacheDefault);
  void resetInternalCounter( );

  // Internal method

  // Remove from cache the SoCpuBufferObject associated to bufferId
  virtual bool removeFromCache( const uint64_t bufferId );
  
  // Force a delete from cache (mainly used as a double checked in SoCpuBufferCache destructor
  // costly because we have to search for the bufferId first.
  virtual bool deleteFromCache( const uint64_t bufferId );

  // Retrieve bufferId from its signature. 
  uint64_t getMappingIdfromSig(const uint64_t& cacheSig);

private:

  // Check if SoCpuBufferObject associated with bufferId is in cache
  virtual bool isInCache( const uint64_t bufferId );

  // internal cache management
  typedef std::map<uint64_t, SoCpuBufferObject*> cacheListType;
  typedef std::map<uint64_t, uint64_t> bufferMapRefCountType;
  typedef std::map<uint64_t, uint64_t> bufferSignatureMap;

  cacheListType m_cacheList;
  bufferMapRefCountType bufferMapRefCount;
  bufferSignatureMap m_bufferIdToSigMap;
  bufferSignatureMap m_bufferSigToIdMap;

  // Max size of the cache
  size_t m_maxCacheSize;

  // Uniq Id management
  uint64_t getUniqueId();
  uint64_t m_lasUniqId;

  // Clean cache to get some space
  bool makeRoomInCache();
  
  // Spinlock used to protect cache access
  SbThreadSpinlock *m_cacheListLock;

  // perf counter manager
  uint64_t m_perfNbCacheAccess ;
  uint64_t m_perfNbCacheDefault;
};

#endif //_SO_BUFFER_OBJECT_CACHE_H_

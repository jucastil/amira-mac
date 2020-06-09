/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : David BEILLOIN (Mar 2007)
**=======================================================================*/


#ifndef SO_MEMORY_OBJECT_H
#define SO_MEMORY_OBJECT_H

#include <Inventor/misc/SoRefCounter.h>
#include <Inventor/STL/map>
#include <Inventor/SbDataType.h>
#include <Inventor/threads/SbThreadMutex.h>

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#endif

class SoBufferObject;

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoMemoryObject
//
//  Class used to encapsulate a memory buffer pointer potentially shared
//  by multiple objects.
//  A reference counter is associated with this object to avoid deletion
//  until reference exists.
//
//////////////////////////////////////////////////////////////////////////////

/**
*
* @VSGEXT Handle memory buffer with reference counter.
*
* @ingroup General
*
* @DESCRIPTION
*  This object encapsulates a memory buffer with a reference counter,
*  allowing it to be shared across multiple objects.
*  The buffer will be released when no more references to it exist.
*
* @SEE_ALSO
*    SoRefCounter,
*    SoRef,
*
*
* [OIV-WRAPPER-NO-WRAP]
*/

class INVENTOR_API SoMemoryObject : public SoRefCounter
{
public:

  /**
   * SoMemoryObject may be manipulating large amounts of memory.
   * It is therefore convenient to be able to set the memory usage
   * policy.
   */
  enum CopyPolicy
  {
    /**
     *  Open Inventor will make a copy of the data
     */
    COPY = 0,
#ifdef OIV_NET_DOC
    /**
     *  Passed buffer used.
     */

#else
    /**
     *  Passed buffer used, user will delete
     */

#endif //OIV_NET_DOC
    NO_COPY,
    /**
     * Passed buffer used, SoMemoryObject will delete.
     * Use this if memory is allocated with operator "new[]".
     */
    NO_COPY_AND_DELETE,
    /**
     * Passed buffer used, SoMemoryObject will free.
     * Use this if memory is allocated with "malloc".
     */
    NO_COPY_AND_FREE
  };

  /**
   * Default Constructor.
   * No memory area is handled, but default parameters are set to 
   * a type of SbDataType::UNSIGNED_BYTE and a CopyPolicy of NO_COPY_AND_DELETE
   */
  SoMemoryObject();

  /**
   * Constructor. Takes the object to manage. @BR
   * Default type will be assigned to UNSIGNED_BYTE. 
   * if owner flag is true, Policy will be set to NO_COPY_AND_FREE , then the memory area 
   * pointed to by buf should be allocated by malloc/realloc C function
   * in order to be correctly deleted during unref.
   * else policy is NO_COPY (disables automatic release of the managed buffer).
   */
  SoMemoryObject(void* buf, size_t byteSize, bool owner=true);

  /**
   * Constructor. Takes the object to manage. @BR
   */
  SoMemoryObject(void* buf, size_t byteSize, SbDataType type, CopyPolicy policy);


  /**
   * Constructor. Takes the buffer object to manage. @BR
   * Policy is NO_COPY_AND_DELETE if owner flag is true, else
   * policy is NO_COPY (disables automatic release of the buffer object).
   */
  SoMemoryObject(SoBufferObject* bufObj, SbDataType type=SbDataType::UNSIGNED_BYTE, bool owner=true);

  /**
   * Destructor. It will be called when there are no more references to this object.
   * It will destroy the managed buffer as well.
   */
  virtual ~SoMemoryObject();

  /**
   * Returns a pointer to the encapsulated buffer.
   * 
   */
  void* get() const;

  /**
   * Returns the size in bytes of the encapsulated buffer.
   */
  size_t length() const;

  /**
   * Returns the type of the encapsulated buffer.
   */
  inline SbDataType getType() const;

SoINTERNAL public:

  void setOwner(bool f) { m_policy = f ? NO_COPY_AND_FREE:NO_COPY; }

  // setup a user allocated buffer
  void setBuffer(void *buf, size_t byteSize);

  // just change the m_size value without reallocation
  void forceSize(size_t byteSize);

  static SoMemoryObject* getMemoryObject(uint32_t id);
  uint32_t getId() { return m_index; }
  void setId( uint32_t id );

  inline SoBufferObject* getBufferObject() const;

private:
  void registerMemObj();

  /**
   * Delete m_buffer if needed with free or delete[]
   */
  void releaseValues();

  /**
   * Delete m_buffer with delete[]
   */
  template <typename T> void deleteValues(void *buffer);

  /**
   * Set m_buffer to a buffer of m_len/m_type.getSize()
   */
  template <typename T> void allocValues(void*& buffer, size_t byteSize);


  bool m_userPointer;
  SoBufferObject * m_bufferObj;

  uint32_t m_index;
  static uint32_t index;

  typedef std::map< uint32_t, SoMemoryObject*> SoMemObjMap;
  typedef SoMemObjMap::value_type SoMemObjValue;
  static SoMemObjMap s_memObjMap;
  static SbThreadMutex s_accessMutex;

  SbDataType m_type;
  CopyPolicy m_policy;
};

/*******************************************************************************/
SbDataType
SoMemoryObject::getType() const
{
  return m_type;
}

SoBufferObject* 
SoMemoryObject::getBufferObject() const
{
  return m_bufferObj;
}

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif // SO_MEMORY_OBJECT_H

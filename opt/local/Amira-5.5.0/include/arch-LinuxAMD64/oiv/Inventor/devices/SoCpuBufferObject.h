/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCPUBUFFEROBJECT_H
#define SOCPUBUFFEROBJECT_H

#include <Inventor/devices/SoBufferObject.h>
#include <Inventor/devices/SoCpuContext.h>

class SoGLBufferObject;

/**
* @VSGEXT CPU buffer object managment class
*
* @ingroup CpuDevice
*
* @DESCRIPTION
*
* This class provides management functions for CPU memory buffers.
*
* See SoBufferObject for general information about buffer objects.
* [OIVNET-WRAPPER-CLASS MODULE{InventorBase}]
*/

class INVENTORGL_API SoCpuBufferObject : public SoBufferObject
{
  SO_TYPED_CLASS_HEADER();

  friend class SoGLBufferObject;

  // ----------------------- Public usage --------------------------------------

public:

  /**
   * Default constructor.
   * The contents of the buffer are initially empty.
   */
  SoCpuBufferObject();

  /**
   * Constructor that takes an existing block of CPU memory. @BR
   * This memory is owned, and should be freed by, the application.
   *
   * @param buffer Pointer to the buffer to manage.
   * @param size Size of buffer in bytes.
   * [OIV-WRAPPER-ARG ARRAY,NO_WRAP{buffer != nullptr? buffer->Length: 0}]
   */
  SoCpuBufferObject(void *buffer, size_t size);

  /**
   * Destructor. @BR
   * Any memory allocated by the buffer object (e.g. by setSize()) is freed.
   */
  virtual ~SoCpuBufferObject();

  /**
   * Map the current "source" buffer object into the specified "target" buffer object. @BR
   * This is useful in order to use a buffer in multiple contexts (e.g. OpenGL and CUDA).
   * The default is to map the entire contents of this buffer, but it is also possible
   * to map a subset of this buffer's memory using the @I startPosition @i and
   * @I mappingSize @i parameters.
   *
   * A source buffer may be mapped into multiple target buffers.  However a target
   * buffer can only be mapped from one source buffer at a time.  If a different source
   * buffer is currently mapped into the target buffer, it is automatically unmapped
   * and may be left in an undefined state.
   *
   * Note: If the current buffer is empty or startPosition is beyond the end of the
   * managed memory, the buffer is not mapped (and an error message is issued in debug builds).
   *
   * @param targetBufferObject The buffer object which will be the mapped version of
   *                           this buffer.
   * @param accessMode The access mode used for the mapping.
   * @param startPosition Offset (in bytes) in source buffer to map from (default is start of buffer).
   * @param mappingSize Size (in bytes) from the startPosition, if SO_BUFFER_SIZE_ALL then the whole buffer is mapped.
   * 
   */
  virtual void map( SoBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Unmap this buffer from the specified buffer object. @BR
   * In other words, remove the specified target buffer from the list of buffers which
   * this buffer is mapped to. If the access mode supports writing, the specified buffer is 
   * sync'd with the current buffer.  An error is reported (in debug builds) if the
   * buffer is not mapped to the specified buffer.
   *
   * @param bufferObject Buffer to be unmapped.
   */
  virtual void unmap( SoBufferObject* bufferObject );

  /**
   * Map the buffer to a system memory address.
   *
   * @return Pointer to the memory managed by the buffer.  NULL if empty.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetSize()}]
   */
  virtual void* map( AccessMode accessMode );

  /**
   * Unmap a buffer mapped to a system memory address.
   *
   * No error is reported if the buffer was not mapped.
   */
  virtual void unmap();

 /**
   * Copy data from the specified buffer object into this buffer object. @BR
   *
   * If the size or the offset are not valid an error is reported (SoDebugError).
   * This buffer is not resized, if it is too small an error is reported.
   *
   * Source and destination overlaping is supported if both are of type SoCpuBufferObject.
   *
   * @param sourceBufferObject The buffer object to be copied.
   * @param destOffset The starting offset in the destination buffer object, useful for data subsets.
   * @param sourceOffset The starting offset in the source buffer object, useful for data subsets.
   * @param copySize The number of bytes to copy from the source buffer object (SO_BUFFER_SIZE_ALL means all).
   */
  virtual void memcpy( SoBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * @copydoc SoBufferObject::memset
   */
  virtual void memset( void* value, size_t valueSize = 1, size_t offset = 0, size_t count = SO_BUFFER_SIZE_ALL );

  /**
   * Sets the size in bytes of the buffer object. @BR
   * In other words, a request to allocate @I size @i bytes of CPU memory.
   * Returns true if the allocation succeeded.
   *
   * If the requested size is the same as the current size, this method does
   * nothing and returns true.  If there is existing memory that is owned
   * by the buffer object, that memory is released. If the requested size is
   * zero, the buffer object is now empty. By default memory allocations have
   * the maximum possible alignment to allow use with (for example) SSE instructions. 
   *
   * By default memory is managed using the new/delete operators. On Microsoft 
   * Windows platforms it is possible to use VirtualAlloc/VirtualFree instead
   * by setting OIV_BUFFER_USE_VIRTUAL_ALLOC (see SoPreferences).
   *
   * @param size The size in bytes of the memory to allocate.
   * @return True if allocation succeeded.
   */
  virtual bool setSize( size_t size );

  /**
    * Create a new buffer with the same properties as the current one. @BR
    * The new instance will have the same context
    * or device properties, but no memory is allocated.
    */
  virtual SoBufferObject* createInstance() const;

  /**
   * This function clears the content of the buffer, it frees the memory if the mode was COPY.
   */
  virtual void clearInstance();

  /**
   * Request that the buffer object manage an existing block of memory. @BR
   * The application still owns this memory and is responsible for releasing
   * the memory (when no SoCpuBufferObjects have a reference on it).
   *
   * We recommend to use the most aligned memory pointer possible to enable
   * optimized algorithm usage (ie. SSE/Altivec computing, CUDA memory mapping, etc).
   *
   * NOTE: If another buffer object is currently mapped into another buffer, the
   * other buffer is automatically unmapped and its contents are undefined.
   */
  void setBuffer(void *buffer, size_t size);

  /**
   * Map the current buffer object into the specified CPU buffer object.
   *
   * This is an optimized implementation. See the general map() method for more information.
   */
  virtual void map( SoCpuBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Unmap the specified CPU buffer object.
   *
   * This is an optimized implementation. See the general unmap function for more information.
   */
  virtual void unmap( SoCpuBufferObject* bufferObject );

 /**
   * Copy data from the specified CPU buffer object into this buffer object. @BR
   *
   * This is an optimized implementation. See the general memcpy method for more information.
   */
  virtual void memcpy( SoCpuBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * Copy data from the specified GL buffer object into this buffer object. @BR
   *
   * This is an optimized implementation. See the general memcpy method for more information.
   */
  virtual void memcpy( SoGLBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * Map the current buffer object into the specified GL buffer object.
   *
   * This is an optimized implementation. See the general map() method for more information.
   */
  virtual void map( SoGLBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Unmap the specified GL buffer object.
   *
   * This is an optimized implementation. See the general unmap function for more information.
   */
  virtual void unmap( SoGLBufferObject* bufferObject );

SoINTERNAL public:

  /**
   * Copy data from this buffer object to the specified CPU buffer object. @BR
   */
  void copyToCpuBuffer( SoCpuBufferObject* targetBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * This function indicates if the buffer memory was allocated by the object
   * or if it was set using the setBuffer funcion.
   */
  bool isBufferOwner() const;

protected:

  static void memcpyPtr2Ptr( void* dest, void* data, size_t dataSize, size_t count );

  /** Pointer on the memory array used to store the buffer object. */
  unsigned char* m_buffer;

private:

  /** This variable indicates if memory is allocated/deallocated by us or not*/
  bool m_isOwner;

  /** This variable indicates if the memmory allocation is done using VirtualAlloc on win32. */
  static bool m_useVirtualAlloc;

  /** Buffer alignment for SSE */
  int m_alignment;
};


// ----------------------- Inline functions --------------------------------------


//------------------------------------------------------------------------------
inline bool
SoCpuBufferObject::isBufferOwner() const
{
  return m_isOwner;
}

//------------------------------------------------------------------------------

#endif // SOCPUBUFFEROBJECT_H


/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDABUFFEROBJECT_H
#define SOCUDABUFFEROBJECT_H

#include <Inventor/devices/SoBufferObject.h>
#include <Inventor/devices/SoCudaContext.h>
#include <Inventor/cuda/SoCudaDefs.h>

class SoCpuBufferObject;
class SoGLBufferObject;

/**
* @VSGEXT CUDA buffer object managment class
*
* @ingroup CudaDevice
*
* @DESCRIPTION
*
* This class provides management functions for CUDA memory buffers.
*
* @NOTES
*
* - The SoCudaContext used for this buffer is the one active when the constructor is called.
* - Most of the functions don't actually care about the context.
*
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTORCUDA_API SoCudaBufferObject : public SoBufferObject
{
  SO_TYPED_CLASS_HEADER();

public:

  /** Default constructor. @BR
   *  The SoCudaContext used for this buffer is the one active when the constructor is called.
   */
  SoCudaBufferObject();

  /** Destructor */
  virtual ~SoCudaBufferObject();

  /**
   * Sets the size in bytes of the buffer.
   *
   * @param size The new buffer size in bytes.
   *
   * @NOTES
   * - If the context is not valid, SoError is called.
   * - If the current context is not the one active when the constructor was called, then SoError is called.
   * - If the buffer is already allocated, the memory is freed and re-allocated with the new size. @BR
   *   Therefore if you increase the size of the buffer, the original data is lost!
   */
  virtual bool setSize( size_t size );

  /**
   * Copy data from any SoBufferObject into the CUDA memory.
   *
   * @param sourceBufferObject The source buffer object which contains the data to copy.
   * @param destOffset The starting offset in the source buffer.
   * @param sourceOffset The starting offset in the source buffer.
   * @param copySize The size in bytes of the chunk of data to copy.
   *
   * @warning: Source and destination overlaping is NOT supported.
   *
   * @NOTES
   * - Ensure that the context which was used
   *   when the constructor was called is currently bound before calling this function.
   */
  virtual void memcpy( SoBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * Copy data from a CPU buffer into the CUDA buffer.
   *
   * This function is a specialized function for speed-up. @BR
   * See the regular memcpy function for more information
   */
  virtual void memcpy( SoCpuBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * Copy data from a CUDA buffer into this CUDA buffer.
   *
   * @warning: Source and destination overlaping is NOT supported.
   *
   * This function is a specialized function for speed-up. @BR
   * See the regular memcpy function for more information
   */
  virtual void memcpy( SoCudaBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * Copy data from the specified GL buffer object into this buffer object. @BR
   *
   * This is an optimized implementation. See the general memcpy method for more information.
   */
  virtual void memcpy( SoGLBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * @copydoc SoBufferObject::memset
   */
  virtual void memset( void* value, size_t valueSize = 1, size_t offset = 0, size_t count = SO_BUFFER_SIZE_ALL );

  /**
   * Map the buffer object to any buffer object. @BR
   * It can be called from any context, the function binds the correct context when it's called!
   *
   * If the target buffer is another CUDA buffer object, the map function copies the data according
   * to the context. It does a copy of the source buffer in a temp buffer if the two buffers
   * don't use the same CUDA context.
   *
   * @param targetBufferObject The target buffer object which receives the mapping from the CUDA buffer.
   * @param accessMode The access mode used for the mapping.
   * @param startPosition Offset in source buffer to map from.
   * @param mappingSize Number of bytes to map, if SO_BUFFER_SIZE_ALL then the whole buffer is mapped.
   */
  virtual void map( SoBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Map the buffer object to a CUDA buffer object. @BR
   * It is defined just to speed up the call when the type of the object is known. @BR
   *
   * See the general map function for more information.
   */
  virtual void map( SoCudaBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Map the buffer object to a CPU buffer object. @BR
   * It is defined just to speed up the call when the type of the object is known. @BR
   * 
   * See the general map function for more information.
   */
  virtual void map( SoCpuBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Map the buffer object to a GL buffer object. @BR
   * It is defined just to speed up the call when the type of the object is known. @BR
   *
   * See the general map function for more information.
   */
  virtual void map( SoGLBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Unmap the specified buffer object.
   */
  virtual void unmap( SoBufferObject* bufferObject );

  /**
   * Unmap the specified CUDA buffer object.
   * It is defined just to speed up the call when the type of the object is known. @BR
   *
   * See the general unmap function for more information.
   */
  virtual void unmap( SoCudaBufferObject* bufferObject );

  /**
   * Unmap the specified CPU buffer object.
   * It is defined just to speed up the call when the type of the object is known. @BR
   *
   * See the general unmap function for more information.
   */
  virtual void unmap( SoCpuBufferObject* bufferObject );

  /**
   * Unmap the specified GL buffer object.
   * It is defined just to speed up the call when the type of the object is known. @BR
   *
   * See the general unmap function for more information.
   */
  virtual void unmap( SoGLBufferObject* bufferObject );

  /**
   * Returns a CUDA pointer for this buffer object. @BR
   * Be careful, the returned pointer is only valid in a CUDA device function.
   *
   * @return CUDA pointer of this buffer.
   * [OIV-WRAPPER-RETURN-TYPE POINTER_VALUE]
   */
  virtual void* getLocation();

  /**
    * Creates a new buffer with the same properties as the current one. @BR
    * The new instance will have the same context
    * or device properties, but no memory is allocated.
    */
  virtual SoBufferObject* createInstance() const;

  virtual void clearInstance();

  // ----------------------- Internal usage --------------------------------------

SoINTERNAL public:

  virtual void copyToCpuBuffer( SoCpuBufferObject* targetBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  SoCpuBufferObject* createFastCpuBufferObject( size_t size, bool copyData );

  void destroyFastCpuBufferObject( SoCpuBufferObject* cpuBufferObject, bool copyData );

  void copyToGLBuffer( SoGLBufferObject* targetBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  // ----------------------- Protected usage --------------------------------------
protected:

  /**
   * This function copies data from the device to the host.
   */
  virtual void copyHostToDevice( void* sourceBuffer, size_t sourceOffset, size_t destOffset, size_t copySize );

  /**
   * This function copies data from the host to the device.
   */
  virtual void copyDeviceToHost( void* targetBuffer, size_t targetOffset, size_t sourceOffset, size_t copySize );

private:

  /** Private function to force the buffer */
  void setBuffer( void *buffer, size_t size );

  void* m_buffer;

  bool m_isOwner;
};


#endif //SOCUDABUFFEROBJECT_H

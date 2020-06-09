/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOBUFFEROBJECT_H
#define SOBUFFEROBJECT_H

#include <Inventor/SbBase.h>
#include <Inventor/SoTypedObject.h>
#include <Inventor/SoSubTypedClass.h>
#include <Inventor/threads/SbThreadSpinlock.h>
#include <Inventor/STL/limits>

class SoCpuBufferObject;
class SoDeviceContext;
class SoCpuBufferObjectCache;

/**
 * Used to indicate that we want to use the whole buffer.
 */
#define SO_BUFFER_SIZE_ALL  (std::numeric_limits<size_t>::max())

/**
* @VSGEXT Abstract base class for buffer object management
*
* @ingroup Devices
*
* @DESCRIPTION
*
* This class provides generic functions to manage buffer objects.
*
* There are specific implementations of this class for buffer
* objects on each type of device:
* - SoCpuBufferObject: A buffer in CPU system memory.
* - SoGLBufferObject: A buffer in GPU memory managed through the
*   OpenGL API.
* - SoCudaBufferObject: A buffer in GPU memory managed through
*   Nvidia's CUDA API.
* - SoOpenCLBufferObject: A buffer (usually) in GPU memory managed
*   through the OpenCL API.
*
* In many cases the abstract SoBufferObject methods allow the 
* application to handle buffer objects without knowing the specific 
* type of the buffer. This is very convenient when computation is
* implemented on multiple devices.  For example if computation is
* done using CUDA when available, but using the CPU when a CUDA
* device is not available.  
*
* Since version 8.0, some Open Inventor classes take or return data
* using an SoBufferObject (or derived class).  For example texture
* images (see SoSFImage), geometry data (see SoBufferedShape) and
* tiles of volume data (see SoVolumeTransform).
*
* @SEE_ALSO
*   SoCpuBufferObject, SoGLBufferObject, SoCudaBufferObject, SoOpenCLBufferObject
*
*   SoCpuDevice, SoCudaDevice, SoGLDevice, SoOpenCLDevice
*/

class INVENTORBASE_API SoBufferObject: public SoTypedObject
{
  SO_TYPED_CLASS_ABSTRACT_INTERNAL_HEADER();
  // ----------------------- Public usage --------------------------------------

public:

  /** This enum provides the possible access modes for a mapped buffer object. */
  enum AccessMode
  {
    /** The target buffer initially has the same contents as the source buffer.
     */
    READ_ONLY,

    /** The target buffer contents are initially undefined (although they may be
     *  the same as the source buffer) but the source buffer will contain the 
     *  contents of the target buffer after the unmap.
     */
    SET,

    /** The target buffer initially has the same contents as the source buffer
     *  and the source buffer will contain the contents of the target buffer 
     *  after the unmap.
     */
    READ_WRITE
  };

  /**
   * Default constructor.
   *
   * The default constructor initializes the internal OpenInventor system and creates the
   * mutex which is used to lock/unlock the buffer.
   */
  SoBufferObject();

  /**
   * Destructor.
   */
  virtual ~SoBufferObject();

  /**
   * Locks the buffer against concurrent calls from different threads. @BR
   * This is a blocking call.  In other words it will not return
   * immediately if another thread currently has the buffer locked.
   */
  void lockBuffer();

  /**
   * Unlocks the buffer object. @BR
   * If a thread calls lockBuffer() then it must call unlockBuffer()
   * to allow other threads to lock the buffer.
   */
  void unlockBuffer();

  /**
   * Sets the size in bytes of the buffer object. @BR
   *
   * @param size The requested size in bytes.
   * @return True if the operation was successful.
   */
  virtual bool setSize( size_t size );

  /**
   * Returns the size, in bytes, of the buffer object.
   *
   * @return The size in bytes of the buffer object.
   */
  size_t getSize() const;

  /**
   * Maps the current buffer object into the specified buffer object. @BR
   * It is useful in order to use a buffer in multiple contexts (e.g. OpenGL and CUDA).
   *
   * @param targetBufferObject The buffer object which will be the mapped version of
   *                           this buffer.
   * @param accessMode The access mode used for the mapping.
   * @param startPosition Offset in source buffer to map from (default is start of buffer).
   * @param mappingSize Number of bytes from the startPosition to map
   *                    (default is SO_BUFFER_SIZE_ALL meaning the whole buffer is mapped.
   *
   */
  virtual void map( SoBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL ) = 0;

  /**
   * Maps the current buffer object into the specified CPU buffer object. @BR
   *
   * See the general map method for more information.
   */
  virtual void map( SoCpuBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL ) = 0;

  /**
   * Remove the specified bufferObject from the list of buffers which map
   * the current buffer.
   *
   * If the access mode supports writing the specified buffer is sync'd with the buffer.
   *
   * @param bufferObject Buffer to be unmapped.
   */
  virtual void unmap( SoBufferObject* bufferObject ) = 0;

  /**
   * Unmap the specified CPU buffer. @BR
   *
   * See the general unmap method for more information.
   */
  virtual void unmap( SoCpuBufferObject* bufferObject ) = 0;

 /**
   * Copies data from the specified buffer object into this buffer object. @BR
   * If the size or the offset are not valid an error is reported (SoDebugError).
   * This buffer is not resized, if it is too small an error is reported.
   *
   * @warning: Source and destination overlaping support is implementation dependent, if not supported an error is reported.
   *
   * @param sourceBufferObject The buffer object to be copied.
   * @param destOffset The starting offset in the destination buffer object, useful for data subsets.
   * @param sourceOffset The starting offset in the source buffer object, useful for data subsets.
   * @param copySize The number of bytes to copy from the source buffer object (SO_BUFFER_SIZE_ALL means all).
   */
  virtual void memcpy( SoBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL ) = 0;


 /**
   * Copies data from the specified CPU buffer object into this buffer object. @BR
   *
   * See the general memcpy method for more information.
   */
  virtual void memcpy( SoCpuBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL ) = 0;

  /**
   * This function sets the contents of (or a portion of) this buffer object to the specified value.
   *
   * The valueSize parameter provides a way to do a memset with float, short, byte, etc values.
   * The number of bytes set in this buffer object is exactly valueSize*count. The first byte changed 
   * in this buffer is given by the offset argument.
   *
   * @param value is a pointer to the value to set in the buffer.
   * @param valueSize The size in bytes of the value. Default is 1 byte.
   * @param offset The offset in bytes (where to start setting values). Default is 0.
   * @param count The number of values to set.  Default is number of bytes in buffer.
   * [OIVNET-WRAPPER-ARG POINTER_VALUE,IN,IN,IN]
   */
  virtual void memset( void* value, size_t valueSize = 1, size_t offset = 0, size_t count = SO_BUFFER_SIZE_ALL ) = 0;

  /**
    * Create a new buffer with the same properties as the current one. @BR
    * The new instance will have the same context or device properties, but no memory is allocated.
    */
  virtual SoBufferObject* createInstance() const = 0;


  // ----------------------- Internal usage --------------------------------------

  /**
   * Free the memory allocated by the buffer object.
   */
  virtual void clearInstance() = 0;

  /**
  * Returns the device context where this buffer is valid.
  *
  * @return A device context.
  */

  SoDeviceContext* getContext() const;

  /**
  * Returns a pointer to the buffer object which is mapped by the actual object.
  */
  SoBufferObject* getMappedBufferObject();


  /**
  * This function is used when the instance of buffer object is used to map
  * a buffer. It stores the pointer on the buffer which is mapped by *this*.
  *
  * @param bufferObject The buffer object which is mapped.
  */
  void setMappedBufferObject( SoBufferObject* bufferObject );

  /**
  * Sets the mapping mode used for the mapping of a buffer object.
  *
  * @param accessMode The accessMode used for the mapping.
  */
  void setMappingAccessMode( AccessMode accessMode );


  /**
  * Returns the access mode used for the buffer mapping.
  */
  AccessMode getMappingAccessMode();

  /**
   * Stores information about the mapping in order to know the subset of the data
   * mapped in the buffer.
   */
  void setMappingZoneInformation( size_t startPosition, size_t size );

  /**
   * Returns the position in the source buffer mapped in this buffer.
   *
   * @return Returns a position in bytes.
   */
  size_t getMappingStartPosition() const;

  /**
   * Returns the size of the mapped area in bytes.
   *
   * @return The size of the mapped area.
   */
  size_t getMappingSize() const;


  /**
  * Returns the cache manager object.
  */
  static SoCpuBufferObjectCache* getBufferObjectCache();

SoINTERNAL public:

  // should not be used elsewhere than in SoMemoryObject for compatibility purpose
  void forceSize(size_t size);

  // This function does a copy of the buffer to a CPU buffer object
  virtual void copyToCpuBuffer( SoCpuBufferObject* targetBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  // Init/Exit class method. Internal use
  static void initClass();
  static void exitClass();

  // ----------------------- Protected usage --------------------------------------
protected:

  /**
   * Stores the Device context active when the buffer object was allocated.
   *
   * @param context The device context used during the allocation.
   */
  void setDeviceContext( SoDeviceContext* context );

  /**
   * Checks that the arguments are valid for a specific memory copy.
   */
  virtual bool checkCopyConditions( size_t sourceSize, size_t sourceOffset,
    size_t targetSize, size_t targetOffset, size_t copySize );

  // ----------------------- Protected data usage --------------------------------------

protected:

  /** The current size, in bytes, of the buffer. */
  size_t m_size;


  // ----------------------- Private usage --------------------------------------

private:
  /** copy operator not implemented so prevent its use to avoid double delete
   * of mutex and other things
   */
  SoBufferObject(const SoBufferObject&) {}

  /** The device context which was used when the buffer object was created. */
  SoDeviceContext* m_deviceContext;

  /** Open Inventor thread mutex used to lock/unlock the buffer object. */
  SbThreadSpinlock m_bufferMutex;

  /** Pointer on the source buffer when *this* is a mapped buffer. */
  SoBufferObject* m_mappedBufferObject;

  /** AccessMode used for the mapping of the source buffer. */
  AccessMode m_mappingAccessMode;

  size_t m_mappingStartPosition;

  size_t m_mappingSize;

  // Instance of the class responsible for the cache of BufferObject. 
  static SoCpuBufferObjectCache* s_bufferObjectCache;

};

// ----------------------- Inline functions --------------------------------------



//------------------------------------------------------------------------------
inline SoBufferObject*
SoBufferObject::getMappedBufferObject()
{
  return m_mappedBufferObject;
}


//------------------------------------------------------------------------------
inline void
SoBufferObject::setMappingAccessMode( SoBufferObject::AccessMode accessMode )
{
  m_mappingAccessMode = accessMode;
}


//------------------------------------------------------------------------------
inline SoBufferObject::AccessMode
SoBufferObject::getMappingAccessMode()
{
  return m_mappingAccessMode;
}


//------------------------------------------------------------------------------
inline void
SoBufferObject::setMappingZoneInformation( size_t startPosition, size_t size )
{
  m_mappingStartPosition = startPosition;
  m_mappingSize = size;
}


//------------------------------------------------------------------------------
inline size_t
SoBufferObject::getMappingStartPosition() const
{
  return m_mappingStartPosition;
}


//------------------------------------------------------------------------------
inline size_t
SoBufferObject::getMappingSize() const
{
  return m_mappingSize;
}

//------------------------------------------------------------------------------
inline bool
SoBufferObject::setSize( size_t size )
{
  m_size = size;
  return true;
}

//------------------------------------------------------------------------------
inline size_t
SoBufferObject::getSize() const
{
  return m_size;
}


//------------------------------------------------------------------------------
inline bool
SoBufferObject::checkCopyConditions( size_t sourceSize, size_t sourceOffset,
                                     size_t targetSize, size_t targetOffset, size_t copySize )
{
  if ( copySize == SO_BUFFER_SIZE_ALL )
  {
    if ( targetOffset >= getSize() )
      return false;
    else
      copySize = targetSize - targetOffset;
  }

  if ( sourceOffset + copySize > sourceSize )
    return false;

  if ( targetOffset + copySize > targetSize )
    return false;

  return true;
}


//------------------------------------------------------------------------------
inline SoDeviceContext*
SoBufferObject::getContext() const
{
  return m_deviceContext;
}



//------------------------------------------------------------------------------
inline void
SoBufferObject::setDeviceContext( SoDeviceContext* context )
{
  m_deviceContext = context;
}


//------------------------------------------------------------------------------

#endif //SOBUFFEROBJECT_H

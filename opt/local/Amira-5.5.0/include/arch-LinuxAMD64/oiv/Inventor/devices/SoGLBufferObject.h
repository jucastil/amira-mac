/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOGLBUFFEROBJECT_H
#define SOGLBUFFEROBJECT_H

#include <Inventor/devices/SoBufferObject.h>
#include <Inventor/sys/SoGLType.h>

class SoGLBufferObjectImpl;

/**
* @VSGEXT OpenGL buffer object class.
*
* @ingroup GLDevice
*
* @DESCRIPTION
*
* This class provides management functions for OpenGL memory buffers.
*
* WARNING: The function setTarget must be called before any operation, as long as
* OpenGL requires the target for any operation.
* [OIVNET-WRAPPER-CLASS MODULE{InventorBase}]
*/
class INVENTORGL_API SoGLBufferObject : public SoBufferObject
{
  SO_TYPED_CLASS_HEADER();

  friend class SoCpuBufferObject;

  // ----------------------- Public usage --------------------------------------

public:

  /**
   * This enum declares the possible targets of the buffer.
   */
  enum BufferObjectTarget
  {
    /** 
    * The buffer is used as a pixel pack buffer, it can be used as texture.
    * For instance as a Texture Buffer Object (TBO).
    */
    PIXEL_PACK_BUFFER,

    /**
    * The buffer is used as a pixel unpack buffer, it can be used for readback operation.
    * For instance as a Pixel Buffer Object (PBO).
    */
    PIXEL_UNPACK_BUFFER,

    /**
    * The buffer is used as an array buffer, it can be used for vertices, normals, colors. 
    * For instance as a Vertex Buffer Object (VBO). Tis is the default value.
    */
    ARRAY_BUFFER,

    /**
     * The buffer is used as a pixel pack buffer, it is used to specify the indices for indexed geometries. 
     * For instance a Vertex Buffer Object (VBO).
     */
    ELEMENT_ARRAY_BUFFER
  };

  /**
   * This enum declares the possible usages of the memory allocated for the buffer.
   * This is a hint to the OpenGL driver implementation as to how a buffer object's 
   * data store will be accessed. This enables the OpenGL implementation to make 
   * more intelligent decisions that may significantly impact buffer object performance. 
   * It does not, however, constrain the actual usage of the data store.
   * usage can be broken down into two parts: first, the frequency of access (modification 
   * and usage - STATIC, STREAM, DYNAMIC), and second, the nature of that access - DRAW, COPY, READ.
   */
  enum Usage
  {
    /**
    * The data store contents will be modified once and used at most a few times.
    * The data store contents are modified by the application, and used as the source 
    * for GL drawing and image specification commands.
    */
    STREAM_DRAW,

    /**
    * The data store contents will be modified once and used at most a few times.
    * The data store contents are modified by reading data from the GL, and used 
    * to return that data when queried by the application.
    */
    STREAM_READ,

    /**
    * The data store contents will be modified once and used at most a few times.
    * The data store contents are modified by reading data from the GL, and used 
    * as the source for GL drawing and image specification commands.
    */
    STREAM_COPY,

    /**
    * The data store contents will be modified once and used many times.              
    * The data store contents are modified by the application, and used as the source 
    * for GL drawing and image specification commands.
    */
    STATIC_DRAW,

    /**
    * The data store contents will be modified once and used many times.
    * The data store contents are modified by reading data from the GL, and used 
    * to return that data when queried by the application.
    */
    STATIC_READ,

    /**
    * The data store contents will be modified once and used many times.
    * The data store contents are modified by reading data from the GL, and used 
    * as the source for GL drawing and image specification commands.
    */
    STATIC_COPY,

    /**
    * The data store contents will be modified repeatedly and used many times.
    * The data store contents are modified by the application, and used as the source 
    * for GL drawing and image specification commands.
    */
    DYNAMIC_DRAW,

    /**
    * The data store contents will be modified repeatedly and used many times.
    * The data store contents are modified by reading data from the GL, and used 
    * to return that data when queried by the application.
    */
    DYNAMIC_READ,

    /**
    * The data store contents will be modified repeatedly and used many times.
    * The data store contents are modified by reading data from the GL, and used 
    * as the source for GL drawing and image specification commands.
    */
    DYNAMIC_COPY
  };

  /**
   * Constructor.
   *
   * @param usage The usage of this buffer.
   */
  SoGLBufferObject( Usage usage );

  /**
   * Destructor.
   */
  virtual ~SoGLBufferObject();

  /**
   * Query if SoGLBufferObjects are available on this system.
   *
   * @return Returns true if SoGLBufferObjects are available on this system.
   */
  static bool isAvailable();

  /**
   * Store the buffer target, which defines possible usage of the buffer. @BR
   *
   * WARNING: The function setTarget must be called before any operation, as long as
   * opengl requires the target for any operation.
   * 
   * @param target The new target of the buffer.
   */
  void setTarget( BufferObjectTarget target );

  /**
   * Returns the current buffer target.
   *
   * @return The actual buffer target.
   */
  BufferObjectTarget getTarget() const;

  /**
   * Set the size of the buffer in bytes.
   *
   * @param size New size in bytes of the buffer.
   *
   * @NOTES
   * - If the buffer is already allocated, the memory is freed and re-allocated with the new size. @BR
   *   Therefore if you increase the size of the buffer, the original data is lost!
   */
  virtual bool setSize( size_t size );

  /**
   * Map the current buffer object into the specified buffer object. @BR
   *
   * @param targetBufferObject The buffer object which will be the mapped version of
   *                           this buffer.
   * @param accessMode The access mode used for the mapping.
   * @param startPosition offset in source buffer to map from (default is start of buffer).
   * @param mappingSize size from the startPosition, if SO_BUFFER_SIZE_ALL then the whole buffer is mapped.
   * 
   */
  virtual void map( SoBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Map the current buffer object into the specified GL buffer object. @BR
   * It is defined just to speed up the call when the type of the object is known. @BR
   *
   * See the general map function for more information.
   */
  virtual void map( SoGLBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Map the current buffer object into the specified CPU buffer object. @BR
   * It is defined just to speed up the call when the type of the object is known. @BR
   *
   * See the general map function for more information.
   */
  virtual void map( SoCpuBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Unmap the specified buffer object.
   */
  virtual void unmap( SoBufferObject* bufferObject );

  /**
   * Unmap the specified CPU buffer object. @BR
   * It is defined just to speed up the call when the type of the object is known. @BR
   */
  virtual void unmap( SoCpuBufferObject* bufferObject );

  /**
   * Unmap the specified GL buffer object. @BR
   * It is defined just to speed up the call when the type of the object is known. @BR
   */
  virtual void unmap( SoGLBufferObject* bufferObject );

  /**
   * Copy data from any SoBufferObject into this buffer.
   *
   * @warning: Source and destination overlaping is NOT supported.
   *
   * @param sourceBufferObject The source buffer object which contains the data to copy.
   * @param destOffset The starting offset in the source buffer.
   * @param sourceOffset The starting offset in the source buffer.
   * @param copySize The size in bytes of the chunk of data to copy.
   */
  void memcpy( SoBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * Copy data from a GL buffer into this buffer. @BR
   *
   * @warning: Source and destination overlaping is NOT supported.
   *
   * This function is a specialized function for speed-up. @BR
   * See the general memcpy function for more information
   */
  void memcpy( SoGLBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * Copy data from a CPU buffer into this buffer. @BR
   *
   * This function is a specialized function for speed-up. @BR
   * See the general memcpy function for more information
   */
  void memcpy( SoCpuBufferObject* sourceBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  /**
   * @copydoc SoBufferObject::memset
   */
  virtual void memset( void* value, size_t valueSize = 1, size_t offset = 0, size_t count = SO_BUFFER_SIZE_ALL );

  /**
   * Bind the current buffer in the OpenGL context, so it's usable by OpenGL operations.
   */
  void bind();

  /**
   * Unbind the buffer from the OpenGL context.
   */
  void unbind();

  /**
   * This function uses the regular OpenGL mapping function to map the buffer memory into the central
   * paging system. So the returned pointer is usable as a regular pointer. @BR
   *
   * WARNING: The function unmap must be called before using the buffer for any OpenGL operation,
   * otherwise the operation will produce an error.
   *
   * @return The pointer in the mapped region of the OpenGL buffer.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetSize()}]
   */
  void* map( AccessMode accessMode );

  /**
   * Unmaps the buffer using the regular unmap function.
   */
  void unmap();

  /**
   * Query if the buffer is valid in the current context.
   */
  bool isValid();

  /**
   * Returns the OpenGL id of the buffer.
   */
  GLuint getId() const;

  /**
    * Create a new buffer with the same properties as the current one. @BR
    * The new instance will have the same context
    * and device properties, but no memory is allocated.
    */
  virtual SoBufferObject* createInstance() const;

  virtual void clearInstance();

  // ----------------------- Internal usage --------------------------------------

SoINTERNAL public:

  void copyToCpuBuffer( SoCpuBufferObject* targetBufferObject, size_t destOffset = 0, size_t sourceOffset = 0, size_t copySize = SO_BUFFER_SIZE_ALL );

  // ----------------------- Protected usage --------------------------------------

protected:

  SoGLBufferObject();

  /** This function returns the OpenGL value for the current buffer target */
  GLenum getOpenGLTarget() const;

  /** This function set the OpenGL value for the current buffer usage */
  void setOpenGLUsage(const Usage usage);

  /** This function returns the OpenGL value for the current buffer usage */
  GLenum getOpenGLUsage() const;

  bool checkContext();

  /** This function returns the OpenGL value for the specified AccessMode */
  static unsigned int getOpenGLAccessMode( AccessMode accessMode );

private:

  SoGLBufferObjectImpl* m_impl;
};

//------------------------------------------------------------------------------

#endif // SOGLBUFFEROBJECT_H


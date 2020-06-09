/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCPUBUFFERCOMPRESSED_H
#define SOCPUBUFFERCOMPRESSED_H

class SoDataCompressor;

// Inventor include
#include <Inventor/devices/SoCpuBufferObject.h>

// LDM include
#include <LDM/tiles/SoBufferPropertiesInterface.h>

/**
* @LDMEXT LDM buffer object optimized for compressed tile data.
*
* @ingroup LDMTiles
*
* @DESCRIPTION
* This type of buffer efficiently represents a tile containing
* compressed data (usually read from a compressed LDM file).
* The buffer can be used like any other buffer, but uses much
* less memory when its contents are not actually being accessed.
*
* @SEE_ALSO
*    SoBufferPropertiesInterface, SoCpuBufferObject
*/
class LDM_API SoCpuBufferCompressed: public SoCpuBufferObject, public SoBufferPropertiesInterface
{
  SO_TYPED_CLASS_HEADER();

  // ----------------------- Public usage --------------------------------------
public:


  /**
   * Default constructor.
   */
  SoCpuBufferCompressed();

  /**
   * Constructor with compressor given as parameter
   */
  SoCpuBufferCompressed(SoDataCompressor* compressor);

  /**
   * Destructor.
   */
  virtual ~SoCpuBufferCompressed();

  /**
   * Map the current buffer object into the specified buffer object. @BR
   * It is useful in order to use a buffer in multiple contexts (e.g. OpenGL and CUDA).
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
   * Map the current buffer object into the specified CPU buffer object. @BR
   *
   * See the general map method for more information.
   */
  virtual void map( SoCpuBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL);
  
  /**
   * Map the current buffer object into the specified GL buffer object. @BR
   *
   * See the general map method for more information.
   */
  virtual void map( SoGLBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL);

  /**
   * Returns a pointer to the memory array used for the storage of the buffer.
   *
   * @return Pointer to the memory array used for the storage.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetSize()}]
   */
  virtual void* map( AccessMode accessMode );

  /**
  * Unmap the specified CPU buffer object @BR
  * It is defined just to speed up the call when the type of the object is known. @BR
  * Remove the specified bufferObject from the list of buffers which map
  * the current buffer.
  *
  * See the general unmap function for more information.
  */
  virtual void unmap( SoCpuBufferObject* bufferObject );

  /**
  * Unmap the specified GL buffer object @BR
  * It is defined just to speed up the call when the type of the object is known. @BR
  * If the access mode supports writing the specified buffer is sync'd with the buffer.
  *
  * See the general unmap function for more information.
  * @param bufferObject Buffer to be unmapped.
  */
  virtual void unmap( SoGLBufferObject* bufferObject );

  /**
   * Remove the specified bufferObject from the list of buffers which map
   * the current buffer.
   *
   * If the access mode supports writing the specified buffer is sync'd with the buffer.
   *
   * @param bufferObject Buffer to be unmapped.
   */
  virtual void unmap( SoBufferObject* bufferObject );

  /**
   * Unmap a mapped buffer.
   *
   * No error is reported if the buffer was not mapped.
   */
  virtual void unmap();
  
  /**
   * Get the min and max values in the buffer, if they are known. @BR
   * Returns false if these values have not been set or computed.
   * Returns true if values are available.
  *
  * @param min user variable to store min value
  * @param max user variable to store max value
  */
  virtual bool getMinMax ( double& min, double& max);

  /**
  * Set the min and max values for this buffer.
  *
  * @param min user variable containing min value
  * @param max user variable containing max value
  */
  virtual void setMinMax(const double& min, const double& max);
  
  /**
  * Returns the size of the uncompressed data in bytes.
  */
  size_t getRealSize() const;

  /**
  * Set the compressor used to decompress buffer
  *
  * @param compressor Pointer to the compressor to use
  */
  virtual void setCompressor( SoDataCompressor* compressor );
  
  /**
  * Sets the size in bytes of the buffer object.
  * Return FALSE if allocation failed. TRUE otherwise
  *
  * @param size The size in bytes of the raw buffer object.
  */
  virtual bool setSize( size_t size );

private:
  SoDataCompressor* m_compressor;
  
  SoCpuBufferObject* createCachedBuffer();

};

#endif //SOCPUBUFFERCOMPRESSED_H
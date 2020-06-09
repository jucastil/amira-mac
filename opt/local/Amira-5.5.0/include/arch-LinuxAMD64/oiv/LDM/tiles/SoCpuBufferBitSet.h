/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCPUBUFFERBITSET_H
#define SOCPUBUFFERBITSET_H

// Inventor include
#include <Inventor/devices/SoCpuBufferObject.h>

// LDM include
#include <LDM/tiles/SoBufferPropertiesInterface.h>
#include <LDM/tiles/SoCpuBufferCompressed.h>

class SoDataCompressor;

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
* @LDMEXT LDM buffer object optimized for bitset tile data.
*
* @ingroup LDMTiles
*
* @DESCRIPTION
* This type of buffer efficiently represents a tile containing
* bitset data.  The buffer can be used like any other buffer,
* but uses less memory when its contents are not actually being
* accessed.
*
* @SEE_ALSO
*    SoBufferPropertiesInterface, SoCpuBufferObject
*/
class LDM_API SoCpuBufferBitSet: public SoCpuBufferObject, public SoBufferPropertiesInterface
{
  SO_TYPED_CLASS_HEADER();

  // ----------------------- Public usage --------------------------------------
public:

  /**
   * Default constructor.
   */
  SoCpuBufferBitSet();

  /**
   * Constructor from a SoCpuBufferObject containing a bitset.
   */
  SoCpuBufferBitSet(SoCpuBufferObject* cpuBuffer);

  /**
   * Destructor.
   */
  virtual ~SoCpuBufferBitSet();

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
  * Set min and max values for this buffer.
  *
  * @param min user variable containing min value
  * @param max user variable containing max value
  */
  virtual void setMinMax ( const double& min, const double& max);
  
  /**
  * Returns the size of the buffer in bytes. @BR
  * For this type of buffer the real size is the same as the
  * size of the SoBufferObject.
  */
  virtual size_t getRealSize() const;

  /**
  * Sets the size in bytes of the buffer object.
  * Return FALSE if allocation failed. TRUE otherwise
  *
  * @param size The size in bytes of the raw buffer object.
  */
  virtual bool setSize( size_t size );

  /** @DEPRECATED_BEGIN */

  /** @deprecated. Use contructor with SoCpuBufferCompressed.
   * Constructor with compressor given as parameter
   * @DEPRECATED_SINCE_OIV 9.1
   */
  SoDEPRECATED SoCpuBufferBitSet(SoDataCompressor* compressor);

  /** @deprecated. Use contructor with SoCpuBufferCompressed.
  * Set the compressor used to decompress buffer. 
  *
  * @param compressor Pointer to the compressor to use
  * @DEPRECATED_SINCE_OIV 9.1
  */
  virtual void setCompressor( SoDataCompressor* compressor );
  
  /** @deprecated. Use contructor with SoCpuBufferBuffer.
  * Set the data associated to this buffer. 
  *
  * @param dataBuffer Pointer to buffer containing data
  * @param bufferSize Size (in byte) of the data buffer
  * @DEPRECATED_SINCE_OIV 9.1
  */
  virtual void setBufferUncompress( unsigned char* dataBuffer, size_t bufferSize );

  /** @deprecated. No longer used.
  * Set the state of the buffer.Flag must be set to true if
  * buffer is compressed, or false otherwise.
  * @DEPRECATED_SINCE_OIV 9.1
  */
  virtual void setBufferCompressed( bool flag ){};

  /** @DEPRECATED_END */

SoINTERNAL public:

  /** Experimental API for Avizo project only */
  unsigned char* mapRawBitSet(AccessMode accessMode);

  /** Experimental API for Avizo project only */
  void unmapRawBitSet();

  /** Experimental API for Avizo project only */
  inline unsigned char getBit(unsigned char* dataPtr, const int pos) const
  { return (((dataPtr[pos>>0x3]) >> (7- (pos & 0x7))) & 1); }

  // Set the cache id allocated by the DataSet
  virtual void setCacheSignature(const uint64_t& cacheSignature);

private:
  /** Fill the buffer from a SoCpuBufferObject containing a bitset */
  void setBitSetData(SoCpuBufferObject* buffer);

  /** update m_unpackedBuffer from m_bitSetBuffer fro map usage */
  void updateUnpackBuffer(AccessMode accessMode);

  SoCpuBufferObject* m_tempBitSetBuffer;
  SoCpuBufferObject* m_unpackedBuffer;
#if (SO_VERSION>=9)
  SoRef<SoCpuBufferObject> m_bitSetBuffer;
#else
  SoCpuBufferObject* m_bitSetBuffer;
#endif
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif //SOCPUBUFFERBITSET_H

/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCPUBUFFERUNIFORM_H
#define SOCPUBUFFERUNIFORM_H

// Inventor include
#include <Inventor/SbDataType.h> 
#include <Inventor/devices/SoCpuBufferObject.h>

// LDM include
#include <LDM/tiles/SoBufferPropertiesInterface.h>


/**
*
* @LDMEXT LDM buffer object optimized for uniform (single value) tile data.
*
* @ingroup LDMTiles
*
* @DESCRIPTION
* This type of buffer efficiently represents a uniform tile, in other words
* a tile in which every value is the same. The buffer can be used like any
* other buffer, but uses very little memory when its contents are not
* actually being accessed.
*
* @SEE_ALSO
*    SoBufferPropertiesInterface, SoCpuBufferObject
*/
class LDM_API SoCpuBufferUniform: public SoCpuBufferObject, public SoBufferPropertiesInterface
{
  SO_TYPED_CLASS_HEADER();

  // ----------------------- Public usage --------------------------------------
public:

  /**
   * Default constructor.
   */
  SoCpuBufferUniform();

  /**
   * Constructor. 
   *
   * @param value Initial value of uniform buffer.
   * @param valueType Initial value type of uniform buffer.
   */
  SoCpuBufferUniform(const double value, SbDataType valueType );

  /**
   * Destructor.
   */
  virtual ~SoCpuBufferUniform();

  /**
   * Map the current buffer object into the specified buffer object. @BR
   * It is useful in order to use a buffer in multiple contexts (e.g. OpenGL and CUDA).
   *
   * @param targetBufferObject The buffer object which will be the mapped version of
   *                           this buffer.
   * @param accessMode The access mode used for the mapping. Support only READ_ONLY mode
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
  virtual void map( SoCpuBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

  /**
   * Map the current buffer object into the specified GL buffer object. @BR
   *
   * See the general map method for more information.
   */
  virtual void map( SoGLBufferObject* targetBufferObject, AccessMode accessMode, size_t startPosition = 0, size_t mappingSize = SO_BUFFER_SIZE_ALL );

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
   * Returns a pointer to the memory array used for the storage of the buffer.
   *
   * @return Pointer to the memory array used for the storage.
   * [OIV-WRAPPER-RETURN-TYPE ARRAY{GetSize()}]
   */
  virtual void* map( AccessMode accessMode );

  /**
   * Unmap a mapped buffer.
   *
   * No error is reported if the buffer was not mapped.
   */
  virtual void unmap();

  /**
  * This function sets the contents of (or a portion of) the buffer object to the specified value.
  *
  * The dataSize parameter provides a way to do a memset with float, short, byte, etc values.
  *
  * @param data A pointer to the value to set in the buffer.
  * @param dataSize The size in bytes of the data value. Default is 1 byte.
  * @param offset The offset in bytes (where to start setting values). Default is 0.
  * @param count The number of values to set.  Default is number of bytes in buffer.
  */
  virtual void memset( void* data, size_t dataSize = 1, size_t offset = 0, size_t count = SO_BUFFER_SIZE_ALL );

  /**
   * Sets the size in bytes of the buffer object. @BR
   * Returns false if allocation failed, true otherwise.
   *
   * @param size The size in bytes of the raw buffer object.
   */
  virtual bool setSize( size_t size );

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
  * Get the value of the uniform tile
  */
  virtual double getValue() const;

  /**
  * Get the type of the value of the uniform tile
  */
  virtual SbDataType getType() const;
  
  /**
  * Set the value and data type for this uniform buffer.
  */
  void setValue(const double &value, const SbDataType &dataType);

  /**
  * Returns the real size of the buffer in bytes.
  */
  virtual size_t getRealSize() const;

  /**
  * Set the real size of the buffer object in bytes.
  */
  virtual void setRealSize(const size_t &realSize);

private:

  // Define an union to be able to cast
  // the generic value into specific type
  union 
  {
    /** [OIV-WRAPPER-NO-WRAP] */
    unsigned char  l_uCHAR;
    /** [OIV-WRAPPER-NO-WRAP] */
    unsigned short l_uSHORT;
    /** [OIV-WRAPPER-NO-WRAP] */
    unsigned int   l_uINT;
    /** [OIV-WRAPPER-NO-WRAP] */
    signed char    l_sCHAR;
    /** [OIV-WRAPPER-NO-WRAP] */
    signed short   l_sSHORT;
    /** [OIV-WRAPPER-NO-WRAP] */
    signed int     l_sINT;
    /** [OIV-WRAPPER-NO-WRAP] */
    float          l_FLOAT;

  } valueToWrite;

  double m_value;
  SbDataType m_type;

  void convertValue();
  SoCpuBufferObject* createCachedBuffer();

};

#endif //SOCPUBUFFERUNIFORM_H
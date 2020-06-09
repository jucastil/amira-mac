/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOBUFFERPROPERTIESINTERFACE_H
#define SOBUFFERPROPERTIESINTERFACE_H

#include <Inventor/SbBase.h>
#include <Inventor/devices/SoBufferObject.h>

class SoCpuBufferObjectCache;
class SoCpuBufferObject;


/**
* @LDMEXT LDM interface to optimize memory management of tiles .
*
* @ingroup LDMTiles
*
* @DESCRIPTION
* Specialized buffer object classes may implement this interface
* to provide additional information about the contents of the buffer.
*
* @SEE_ALSO
*    SoBufferObject
*    SoCpuBufferCompressed
*    SoCpuBufferUniform
*/
class LDM_API SoBufferPropertiesInterface
{

  // ----------------------- Public usage --------------------------------------
public:

  /**
   * Default constructor.
   */
  SoBufferPropertiesInterface();

  /**
   * Destructor.
   */
  virtual ~SoBufferPropertiesInterface();

  /**
   * Get the min and max values in the buffer, if they are known. @BR
   * Returns FALSE if these values have not been set or computed.
   * Returns TRUE if values are available.
   *
   * @param min user variable to store min value
   * @param max user variable to store max value
   */
  virtual bool getMinMax(double& min, double& max) = 0;

  /**
   * Returns the real size of the buffer in bytes. @BR
   * For a standard buffer this is the same as the size.
   * For a compressed buffer this is the uncompressed size.
   * For a uniform (single value) buffer this is the size it would be
   * if actually populated with the value (data type size * number of values).
   */
  virtual size_t getRealSize() const = 0;

SoINTERNAL public:

  // Set the cache id allocated by the DataSet
  virtual void setCacheSignature(const uint64_t& cacheSignature);

  // Retrieve cache id allocated by the DataSet
  uint64_t getCacheSignature();

protected:

  // Tell if the Min/Max values are available
  bool m_bMinMaxIsSet;

  // Real size of the buffer (once uncompressed)
  size_t m_realSize;

  // Min and Max value of the buffer
  double m_dMin, m_dMax;

  // id of the buffer in the mapping of Inventor base
  uint64_t m_mappingId;

  // Pointer  to the instance of bufferObject cache managed by Inventorbase
  SoCpuBufferObjectCache* m_bufferObjectCache;

  // Internal buffer Management
  SoCpuBufferObject* m_internalPtrRef;
  uint64_t m_internalPtrRefCount;

  // Check the given access mode is supported by buffer
  bool checkAccessMode( const SoBufferObject::AccessMode accessMode );

  // Internal unmap method. As long as code is the same
  // for all buffer that inherits of this interface
  void internalUnmap( SoBufferObject* bufferObject );

  // Unique Id allocated by volumeData;
  uint64_t m_cacheSignature;
};

#endif //SOBUFFERPROPERTIESINTERFACE_H

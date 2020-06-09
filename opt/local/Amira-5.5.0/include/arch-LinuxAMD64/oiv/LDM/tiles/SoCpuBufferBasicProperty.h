/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCPUBUFFERBASICPROPERTY_H
#define SOCPUBUFFERBASICPROPERTY_H

// Inventor include
#include <Inventor/devices/SoCpuBufferObject.h>

// LDM include
#include <LDM/tiles/SoBufferPropertiesInterface.h>

/**
* @LDMEXT LDM buffer object handling basic LDM tile information.
*
* @ingroup LDMTiles
*
* @DESCRIPTION
* This type of buffer represents a standard LDM tile.
*
* @SEE_ALSO
*    SoBufferPropertiesInterface, SoCpuBufferObject,
*    SoCpuBufferUniform, SoCpuBufferCompressed
*/
class LDM_API SoCpuBufferBasicProperty: public SoCpuBufferObject, public SoBufferPropertiesInterface
{
  SO_TYPED_CLASS_HEADER();

  // ----------------------- Public usage --------------------------------------
public:

  /**
   * Default constructor.
   */
  SoCpuBufferBasicProperty();

  /**
   * Destructor.
   */
  virtual ~SoCpuBufferBasicProperty();


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
  virtual void setMinMax ( const double& min, const double& max);
  
  /**
  * Returns the size of the buffer in bytes. @BR
  * For this type of buffer the real size is the same as the
  * size of the SoBufferObject.
  */
  virtual size_t getRealSize() const;

private:

};

#endif //SOCPUBUFFERBASICPROPERTY_H
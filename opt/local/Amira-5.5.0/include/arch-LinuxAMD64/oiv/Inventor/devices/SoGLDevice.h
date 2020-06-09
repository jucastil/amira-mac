/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : Tristan MEHAMLI (Aug 2009)
**=======================================================================*/

#ifndef SO_GL_DEVICE
#define SO_GL_DEVICE

//////////////////////////////////////////////////////////////////////////////
//
//  Class: SoGLDevice
//
// Provides methods to retrieve the properties of a GPU.
// 
//
//////////////////////////////////////////////////////////////////////////////

#include <Inventor/devices/SoDevice.h>
#include <Inventor/STL/vector>

/**
* @VSGEXT OpenGL device management class
*
* @ingroup GLDevice
*
* @DESCRIPTION
*
* This class provides functions to discover, and query information about, GPU
* devices available in the system through the OpenGL API.  You can query, for
* example, the total memory available on the device. 
*
* Please see SoDevice for general information about the device classes.
*
* @SEE_ALSO
*   SoGLContext, SoGLBufferObject,
*   SoCpuDevice, SoCudaDevice, SoOpenCLDevice
*/
class INVENTORGL_API SoGLDevice : public SoDevice
{
  // ----------------------- Public usage --------------------------------------
public:

  /**
   * Returns the total memory of this device in bytes.
   */
  virtual unsigned long long getTotalMemory() const;

  /**
   * Returns the currently available memory of this device in bytes.
   *
   * IMPORTANT NOTE: This function is not available yet because of Driver 
   * limitations.  Currently it returns the same value as getTotalMemory().
   */
  virtual unsigned long long getAvailableMemory() const;

  /**
   * Returns the number of logical units on this device 
   * (i.e. the number of cores of this GPU).
   */
  virtual unsigned int getLogicalUnits() const;

  /** 
   * Returns the driver version of this GPU.
   */
  virtual SbString getDriverVersion() const;

  /**
   * Returns the name of this device.
   */
  virtual SbString getDeviceName() const;

  /** 
   * Returns the first available device found in the system. 
   */
  static SoGLDevice* findFirstAvailableDevice();

  /** 
   * Returns the number of GPUs on the sytem. 
   */
  static unsigned int getDevicesCount();

  /** 
   * Returns the SoGLDevice indicated by index (starting from 0). 
   *
   * @param index The index of the SoGLDevice.
   */
  static SoGLDevice* getDevice( int index );

  /**
   * Initializes SoGLDevice.
   */
  static void initClass();

  /**
   * Cleans SoGLDevice.
   */
  static void exitClass();

  /**
   * Prints information about this device.
   */
  friend std::ostream& operator << ( std::ostream& os, const SoGLDevice& dev )
  {
    unsigned long long allocatedMemory, availableMemory;
    dev.getMemoryInfo( allocatedMemory, availableMemory );

    return os << "[GPU name]: " << dev.m_name.toLatin1() << "\n" << \
                 "[Driver ver]: " << dev.m_drvVer.toLatin1() << "\n" << \
                 "[Vram size]: " << (dev.m_totalMemory)/(1024*1024) << "MB" << "\n" <<  // memory size returned in Mbytes.
                 "[Available Vram size]: " << availableMemory/(1024*1024) << "MB" << "\n" <<  // memory size returned in Mbytes.
                 "[LogicalUnits]: " << dev.m_logicalUnitsCount;
  }

  // ----------------------- Protected usage --------------------------------------
protected:

  /**
   * Protected constructor.
   */
  SoGLDevice();

  /**
   * Protected destructor.
   */
  virtual ~SoGLDevice();

  /** 
   * Find function for the find mechanism in SoDevice. 
   */
  static bool findFirstDeviceFunc( SoDevice* device );

  // ----------------------- Private usage --------------------------------------
private:

  // Only used under Linux
  /** List of the supported video card detection */
  enum VideoCardType
  {
    /**
     *  ATI/AMD video card type
     */
    VC_ATI,
    /**
     *  NVIDIA video card type
     */
    VC_NVIDIA,
    /**
     * Virtual Box video card Type
     */
    VC_VIRTUALBOX,
    /**
     * Unknown video card type
     */
    VC_UNKNOWN
  };

  void getMemoryInfo( unsigned long long& allocatedMemory, unsigned long long& availableMemory ) const;

  // Initializes the device with default parameters
  static void defaultDeviceInit();

  // Memory
  unsigned long long m_totalMemory;

  // Logical units
  unsigned int m_logicalUnitsCount;

  // GPU name
  SbString m_name;

  // Driver version
  SbString m_drvVer;

  VideoCardType m_vcType;

  // List of GPU devices removed when this module is unlocked
  static std::vector<SoGLDevice*> s_glDevices;

  // Thread mutex for initClass and exitClass
  static SbThreadMutex s_initThreadMutex;

  // Refs counter
  static int s_initRefCount;
};

// ----------------------- Inline functions --------------------------------------
inline unsigned long long
SoGLDevice::getTotalMemory() const
{
  return m_totalMemory;
}

inline unsigned int 
SoGLDevice::getLogicalUnits() const
{
  return m_logicalUnitsCount;
}

inline SbString 
SoGLDevice::getDeviceName() const
{
  return m_name;
}

#endif // SO_GL_DEVICE

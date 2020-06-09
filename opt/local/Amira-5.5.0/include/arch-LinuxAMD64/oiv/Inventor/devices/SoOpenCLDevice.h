/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SoOpenCLDEVICE_H
#define SoOpenCLDEVICE_H

#include <Inventor/SoDB.h>

#include <Inventor/devices/SoDevice.h>

#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/OpenCL/SoOpenCLDefs.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/string>

#include <Inventor/sys/SoCL.h>

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
* @VSGEXT OpenCL device management class
*
* @ingroup OpenCLDevice
*
* @DESCRIPTION
*
* This class provides functions to discover, and query information about,
* OpenCL-enabled devices (CPU, GPU, etc) available in the system using
* the standard OpenCL API.  You can query the memory available on a device,
* the compute capability, etc.
*
* Please see SoDevice for general information about the device classes.
*
* NOTE: Before using these devices the application must initialize OpenCL
* by calling SoOpenCL::init.
*
* @SEE_ALSO
*   SoOpenCL, SoOpenCLApi, SoOpenCLContext, SoOpenCLBufferObject,
*   SoCpuDevice, SoCudaDevice, SoGLDevice
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTOROPENCL_API SoOpenCLDevice : public SoDevice
{
  friend class SoDevice;

  // ----------------------- Public usage --------------------------------------

public:


  /**
   * The OpenCL device type.
   * The type can be a combination of those values.
   */
  enum OpenCLDeviceType
  {
    DEVICE_CPU = 1,
    DEVICE_GPU = 2,
    DEVICE_ACCELERATOR = 4,
    DEVICE_DEFAULT = 8
  };

  /**
   * Detect and register available OpenCL devices.
   */
  static void init();

  /**
   * Returns true if module is currently initialized.
   */
  static bool isInitialized();

  /**
   * Unregister the class and previously registered devices.
   */
  static void finish();

  /**
   * Returns the first available OpenCL device in the system. @BR
   * Note the result is always null if SoOpenCL::init() has not been called.
   */
  static SoOpenCLDevice* findFirstAvailableDevice();

  /** 
   * Returns the SoOpenCLDevice indicated by index. 
   *
   * @param index the index of the SoOpenCLDevice.
   */
  static SoOpenCLDevice* getDevice( int index );

  /**
   * Returns the number of OpenCL capable devices in the system.  @BR
   * Note the result is always null if SoOpenCL::init() has not been called.
   */
  static unsigned int getDevicesCount();

  /**
   * Returns the device type, or a binary combination of device type.
   */
  OpenCLDeviceType getDeviceType() const;

  /**
   * Returns a string which describes the device type combination.
   */
  SbString getDeviceTypeString() const;

  /**
   * Returns the version of OpenCL supported by this device.
   *
   * @return The supported OpenCL version.
   */
  float getComputingVersion() const;

  /**
   * Returns the total memory of this device in bytes.
   */
  virtual unsigned long long getTotalMemory() const;

  /**
   * Returns the currently available memory on this device in bytes.
   */
  virtual unsigned long long getAvailableMemory() const;

  /** 
   * Returns the number of logical (computing) units of this device 
   * (i.e. the number of cores of this device).
   */
  virtual unsigned int getLogicalUnits() const;

  /** 
   * Returns the driver version of this device.
   */
  virtual SbString getDriverVersion() const;

  /**
   * Returns the device name.
   *
   * @return The device name.
   */
  virtual SbString getDeviceName() const;

  /**
   * Returns the OpenCL device ID.
   *
   * @return The OpenCL device id.
   */
  cl_device_id getOpenCLDeviceId() const;

  /**
   *  Returns the maximum grid size for this device.
   */
  void getMaxWorkItemSizes( int& x, int& y, int& z ) const;

  /**
   *  Returns the maximum group size for this device.
   */
  unsigned long getMaxWorkGroupSize() const;

  /**
   *  Returns the maximum size (in bytes) of a buffer allocated on the device.
   */
  unsigned long getMaxMemoryAllocationSize() const;

  /** 
   * Prints information about this device.
   */
  friend std::ostream& operator << ( std::ostream& os, const SoOpenCLDevice& dev )
  {
    return os << "[Device name]: " << dev.m_name.toLatin1() << "\n" <<
                 "[Device type ]: " << dev.getDeviceTypeString() << "\n" <<
                 "[Driver ver]: " << dev.m_drvVer << "\n" <<
                 "[Computing ver]: " << dev.m_computingVersion << "\n" << \
                 "[Vram size]: " << (dev.m_totalMemory)/(1024*1024) << "MB" << "\n" << // memory size returned in Mbytes.
                 "[Available Vram size]: " << (dev.m_totalMemory)/(1024*1024) << "MB" << "\n" << // memory size returned in Mbytes.
                 "[Compute units]: " << dev.getLogicalUnits() << "\n" <<
                 "[Max memory allocation size]: " << dev.m_maxMemAllocSize/(1024*1024) << "MB\n" <<
                 "[Max work group size]: " << dev.m_maxWorkGroupSize << "\n" <<
                 "[Max work items sizes]: " << dev.m_maxWorkItemSizes[0] << " / " <<
                 dev.m_maxWorkItemSizes[1] << " / " <<
                 dev.m_maxWorkItemSizes[2] << "\n";
  }

  // ----------------------- Protected usage --------------------------------------

protected:

  /**
  * Default constructor.
  */
  SoOpenCLDevice();


  /**
   * Destructor.
   */
  virtual ~SoOpenCLDevice();

  // ----------------------- Private usage --------------------------------------

private:

  static bool findFirstDeviceFunc( SoDevice* device );


  // ----------------------- Private usage --------------------------------------

private:

  /** Stores the total memory in bytes available on the device */
  cl_ulong m_totalMemory;

  /** This variable stores the OpenCL version supported by the device. */
  float m_computingVersion;

  // Driver version 
  SbString m_drvVer;

  /** Internal ID of the device. */
  cl_device_id m_devicePtr;

  /** This variable stores the device type. */
  OpenCLDeviceType m_deviceType;

  /** The name of the device */
  SbString m_name;

  /** This variable stores the max grid size. */
  int m_maxWorkItemSizes[ 3 ];

  /** This variable stores the max work group size.*/
  int m_maxWorkGroupSize;

  /** This variable stores the limit of a buffer allocation.*/
  unsigned long m_maxMemAllocSize;

  /** This variable stores the maximum usable compute units on the device. */
  unsigned int m_maxComputeUnits;

  /** We keep a list of OpenCL devices so we can remove then when we unlocd this module */
  static std::vector< SoOpenCLDevice * > s_openCLDevices;

  // We keep the number of references to this module, so we really free the data when nobody uses it..
  static SbThreadMutex s_initThreadMutex;

  // The refs counter
  static int s_initRefCount;
};

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif // SoOpenCLDEVICE_H


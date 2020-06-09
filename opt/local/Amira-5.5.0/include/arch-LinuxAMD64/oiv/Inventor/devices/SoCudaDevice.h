/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCUDADEVICE_H
#define SOCUDADEVICE_H

#include <Inventor/SbVec.h>
#include <Inventor/SoDB.h>

#include <Inventor/cuda/SoCudaDefs.h>
#include <Inventor/devices/SoDevice.h>
#include <Inventor/threads/SbThreadMutex.h>


#include <Inventor/STL/vector>
#include <Inventor/STL/string>

#ifdef _WIN32
#pragma warning( push )
#pragma warning(disable:4251)
#endif

/**
* @VSGEXT CUDA device management class
*
* @ingroup CudaDevice
*
* @DESCRIPTION
*
* This class provides functions to discover, and query information about,
* CUDA-enabled devices (typically GPUs) available in the system using
* NVIDIA's CUDA API.  You can query the memory available on a device,
* the CUDA compute capability, etc.
*
* Please see SoDevice for general information about the device classes.
*
* NOTE: Before using these devices the application must initialize CUDA
* by calling SoCuda::init.
*
* @SEE_ALSO
*   SoCuda, SoCudaApi, SoCudaContext, SoCudaBufferObject,
*   SoCpuDevice, SoGLDevice, SoOpenCLDevice
*
* [OIVJAVA-WRAPPER-CLASS NO_WRAP]
* 
*/

class INVENTORCUDA_API SoCudaDevice : public SoDevice
{
  friend class SoDevice;

  // ----------------------- Public usage --------------------------------------

public:

  /**
   * Detect and register available CUDA devices.
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
   * Returns the first available CUDA device in the system. @BR
   * Note the result is always null if SoCuda::init() has not been called.
   */
  static SoCudaDevice* findFirstAvailableDevice();

  /**
   * Returns the SoCudaDevice indicated by index (starting with zero).
   *
   * @param index The index of the SoCudaDevice.
   */
  static SoCudaDevice* getDevice( int index );

  /**
   * Returns the number of CUDA capable GPUs in the system. @BR
   * Note the result is always zero if SoCuda::init() has not been called.
   */
  static unsigned int getDevicesCount();

  /**
   * Returns the total available memory on this device in bytes.
   *
   * @return The total memory in bytes on the device.
   */
  virtual unsigned long long getTotalMemory() const;

  /**
   * Returns the current available memory on this device in bytes.
   */
  virtual unsigned long long getAvailableMemory() const;

  /**
   * Returns the number of logical units of this device 
   * (i.e. the number of cores of this GPU).
   */
  virtual unsigned int getLogicalUnits() const;

  /**
   * Returns the driver version of this device.
   */
  virtual SbString getDriverVersion() const;

  /**
   * Returns the version of CUDA supported by the device.
   *
   * @return The supported CUDA version.
   */
  float getComputingVersion() const;

  /**
   * Returns the device name.
   *
   * @return The device name.
   */
  virtual SbString getDeviceName() const;

  /**
   * Returns the CUDA device ID.
   *
   * @return The CUDA device id.
   */
  int getCudaDeviceId() const;

  /**
   *  Returns the maximum grid size for this device.
   */
  void getMaxGridSize( int& x, int& y, int& z ) const;

  /**
   *  Returns the maximum grid size for this device.
   */
  SbVec3i32 getMaxGridSize() const;

  /**
   *  Returns the maximum block size for this device.
   */
  SbVec3i32 getMaxBlockSize() const;

  /**
   *  Returns the maximum number of threads per block.
   */
  int getMaxThreads() const;

  /**
   * Returns the maximum size of the shared memory per block in bytes.
   */
  unsigned long long getMaxSharedMemoryPerBlock() const;

  /**
   * Returns the memory pitch for this device.
   */
  unsigned long long getMemPitch() const;

  /**
   * Prints information about this device.
   */
  friend std::ostream& operator << ( std::ostream& os, const SoCudaDevice& dev )
  {
    unsigned long long allocatedMemory, availableMemory;
    dev.getMemoryInfo( allocatedMemory, availableMemory );

    return os << "[GPU name]: " << dev.m_name.toLatin1() << "\n" << \
                 "[Driver ver]: " << dev.m_drvVer << "\n" << \
                 "[Vram size]: " << (dev.m_totalMemory)/(1024*1024) << "MB" << "\n" << // memory size returned in Mbytes.
                 "[Available Vram size]: " << availableMemory/(1024*1024) << "MB" << "\n" << // memory size returned in Mbytes.
                 "[LogicalUnits]: " << dev.m_logicalUnits;
  }

  // ----------------------- Protected usage --------------------------------------

protected:

  /**
  * Default constructor.
  */
  SoCudaDevice();


  /**
   * Destructor.
   */
  virtual ~SoCudaDevice();

  // ----------------------- Private usage --------------------------------------

private:

  static bool findFirstDeviceFunc( SoDevice* device );


  // ----------------------- Private usage --------------------------------------

private:

  void getMemoryInfo( unsigned long long& allocatedMemory, unsigned long long& availableMemory ) const;

  /** Stores the total memory in bytes available on the device */
  unsigned long long m_totalMemory;

  unsigned int m_logicalUnits;

  /** This variable stores the CUDA version supported by the device. */
  float m_computingVersion;

  // Driver version
  SbString m_drvVer;

  /** Internal ID of the device */
  unsigned int m_devicePtr;

  /** The name of the device */
  SbString m_name;

  /** This variable stores the max grid size. */
  SbVec3i32 m_maxGridSize;

  /** This variable stores the max block size. */
  SbVec3i32 m_maxBlockSize;

  /** This variable stores the max number of threads per block. */
  int m_maxThreadsPerBlock;

  /** This variable stores the max shared memory per block, in bytes */
  unsigned long long m_maxSharedMemoryPerBlock;

  /** This variable stores the mem pitch */
  unsigned long long m_memPitch;

  /** We keep a list of Cuda devices so we can remove then when we unlocd this module */
  static std::vector< SoCudaDevice * > s_cudaDevices;

  // We keep the number of references to this module, so we really free the data when nobody uses it..
  static SbThreadMutex s_initThreadMutex;

  // The refs counter
  static int s_initRefCount;
};

#ifdef _WIN32
#pragma warning( pop )
#endif

#endif // SOCUDADEVICE_H


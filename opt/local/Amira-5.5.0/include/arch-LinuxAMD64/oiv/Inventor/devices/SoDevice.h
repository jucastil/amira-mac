/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SODEVICE_H
#define SODEVICE_H

#include <Inventor/threads/SbThreadMutex.h>
#include <Inventor/SbString.h>

#include <Inventor/STL/vector>

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning(disable:4251)
#endif

class SoDevice;

/** Find function type */
typedef bool SoDeviceFindFunction( SoDevice* device );

/**
* @VSGEXT Abstract device management class
* 
* @ingroup Devices
* 
* @DESCRIPTION
*
* This class provides generic functions to manage and to get data about specific devices.
*
* There are specific implementations of this class for each type of device
* supported by Open Inventor. These classes may provide additional methods
* to query information specific to the device type.  Currently the supported
* device types are:
* - SoCpuDevice: A system CPU, including multiple cores.
* - SoCudaDevice: A GPU, managed through Nvidia's CUDA API.
* - SoGLDevice: A GPU, managed through the OpenGL API.
* - SoOpenCLDevice: A CPU or GPU, managed through the OpenCL API.
*
* A single physical device may be accessible as more than one type of logical device.
* For example, a GPU (graphics board) may be accessible as an OpenGL device and as a
* CUDA device.  Using the query methods, you can determine the number of each type of
* device and specific information about each device such as the total memory.
*
* Before using any CUDA or OpenCL devices, the application must initialize the
* corresponding module using SoCuda::init() or SoOpenCL::init() These methods should
* only be called after initializing Open Inventor (using SoXt::init() etc).
*
* On most devices other than the CPU, a device "context" is necessary when using
* the device.  Open Inventor provides classes to manage contexts for each type of
* device.  See SoDeviceContext and its derived classes SoCpuContext, SoCudaContext,
* SoGLContext and SoOpenCLContext.
*
* Open Inventor provides classes to manage data objects (blocks of memory), called
* buffer objects, on each type of device.  See SoBufferObject and its derived classes 
* SoCpuBufferObject, SoCudaBufferObject, SoGLBufferObject and SoOpenCLBufferObject.
*
* On some devices, for example CUDA and OpenCL, Open Inventor provides a wrapper
* class that allows the application to call functions in the corresponding API using
* object oriented methods.  See SoCudaApi and SoOpenCLApi.
*
* Open Inventor also provides a set of classes that implement commonly used computing
* algorithms that operate on data buffer objects.  See, for example: SoArithmetic,
* SoConversion, SoConvolution and SoSeismic.  Some of these classes have device
* specific implementations, for example SoCudaConvolution and SoOpenCLConvolution.
*
* Note: The word "device" is also used to refer to input devices such as the mouse
* and keyboard.  These devices are associated with the viewer or render area and
* are represented by window system dependent classes.  See, for example: SoWinDevice,
* SoQtDevice and SoXtDevice.
*
* @SEE_ALSO
*   SoCpuDevice, SoCudaDevice, SoGLDevice, SoOpenCLDevice
*/ 

class INVENTORBASE_API SoDevice
{
public:

  /**
   * Performs a generic search on the list of devices. @BR
   * The SoDeviceFindFunction should return true if a device is the one we are looking for.
   *
   * @param findFunction The find function to be called on each device.
   * [OIV-WRAPPER SINGLE_CALLBACK{True}]
   */
  static SoDevice* find( SoDeviceFindFunction* findFunction );

  /**
   * Returns the total memory of this device in bytes.
   */
  virtual unsigned long long getTotalMemory() const = 0;

  /**
   * Returns the current available memory of this device in bytes.
   */
  virtual unsigned long long getAvailableMemory() const = 0;

  /**
   * Returns the number of logical units of this device.
   */
  virtual unsigned int getLogicalUnits() const = 0;

  /**
   * Returns the driver version of this device.
   */
  virtual SbString getDriverVersion() const = 0;

  /**
   * Returns the name of this device.
   */
  virtual SbString getDeviceName() const = 0;

  /**
   * Returns the number of devices.
   */
  static unsigned int getDevicesCount();

  /** 
   * Returns the SoDevice pointed by index. 
   *
   * @param index the index of the SoDevice.
   */
  static SoDevice* getDevice( int index );

SoINTERNAL public:
  /**
   * exitClass function called by OpenInventor 
   * [OIV-WRAPPER-NO-WRAP]
   */
  static void exitClass();

  /**
   * Returns the operating system name.
   */
  static SbString getOSName();


  /**
   * Returns the version of the system running on top of the device.
   *
   * Note: Available only on Microsoft platforms
   */
  static SbString getSystemVersion();

  /**
   * Reads the version of the system running on top of the device.
   *
   * @param majorVersion Major part of the system version.
   * @param minorVersion Minor part of the system version.
   *
   * Note: Available only on Microsoft platforms
   */
  static void readSystemVersion( unsigned int& majorVersion, unsigned int& minorVersion );


protected:

  /** 
   * Protected constructor.
   */
  SoDevice();

  /** 
   * Protected destructor.
   */
  virtual ~SoDevice();

  static void registerDevice( SoDevice* );

  static void unRegisterDevice( SoDevice* );

  static void lockDevicesList();
  
  static void unlockDevicesList();

protected:

  static std::vector< SoDevice * > s_devices;

  static SbThreadMutex s_devicesListMutex;

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#endif // SODEVICE_H


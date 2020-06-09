/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#if !defined SOCPUDEVICE_H
#define SOCPUDEVICE_H

#include <Inventor/devices/SoDevice.h>

#include <Inventor/STL/vector>
#include <Inventor/STL/string>
#include <Inventor/STL/map>

#include <Inventor/threads/SbThreadMutex.h>

#include <Inventor/SbString.h>
#include <Inventor/errors/SoDebugError.h>

/**
* @VSGEXT CPU device management class
*
* @ingroup CpuDevice
*
* @DESCRIPTION
*
* This class provides functions to manage or to get data for each CPU device available in the system.
*
* Please see SoDevice for general information about the device classes.
*
* @SEE_ALSO
*   SoCpuContext, SoCpuBufferObject,
*   SoDevice, SoCudaDevice, SoGLDevice, SoOpenCLDevice
*/

class INVENTORGL_API SoCpuDevice : public SoDevice
{
  friend class SoDevice;

  // ----------------------- Public usage --------------------------------------

public:

  /**
   * Returns the device name.
   *
   * @return The device name.
   */
  virtual SbString getDeviceName() const;

  /**
   * This enum contains the list of possible architectures for the CPU.
   */
  enum ProcessorArchitecture
  {
    X86_64,
    X86_32,
    IA64,
    PPC_32,
    PPC_64,
    UNKNOWN
  };

  /** Returns the total memory of this device in bytes. */
  virtual unsigned long long getTotalMemory() const;

  /**
   * Returns the current available memory of this device in bytes.
   */
  virtual unsigned long long getAvailableMemory() const;

  /**
   * Returns the driver version of this device. @BR
   * Always returns 0.0 on CPU device.
   */
  virtual SbString getDriverVersion() const { return SbString("0.0"); };

  /** Returns the architecture of the processor. */
  ProcessorArchitecture getArchitecture() const;

  /** Returns true if the CPU is active in the system. */
  bool isActive() const;

  /** Returns true if MMX instructions are supported on this device. */
  bool hasMMX() const;

  /** Returns if SSE instructions are supported on this device. */
  bool hasSSE() const;

  /** Returns the SSE instruction level available on this device. */
  int getSSELevel() const;

  /**
   * Returns the number of cores available on this device.
   * 
   * Note: On Microsoft Windows platforms this function only returns a valid number
   * on Windows XP SP3 and newer.
   */
  virtual unsigned int getLogicalUnits() const;

  /**
   * Returns the size of the cache on this device in bytes.
   *
   * Note: On Microsoft Windows platforms this function only returns a valid number
   * on Windows XP SP3 and newer.
   *
   * @param cacheLevel The cache level can be 1, 2, or 3.
   */
  unsigned int getCacheSize( int cacheLevel ) const;

  /**
   * Returns the SoCpuDevice. 
   *
   * @param index not used.
   */
  static SoCpuDevice* getDevice( int index = 0 );

  /**
   * Returns the total number of cores available in the sytem. 
   */
  static unsigned int getDevicesCount();

  /** Returns the first available device found in the system. */
  static SoCpuDevice* findFirstAvailableDevice();

  /**
   * This function detects the CPU available in the system.
   */
  static void initClass();

  /**
   * This function frees the allocated memory.
   */
  static void exitClass();

  /**
   * Prints information about the device.
   */
  friend std::ostream& operator << ( std::ostream& os, const SoCpuDevice& dev )
  {
    unsigned long long allocatedMem,  freeMem;
    dev.getMemoryInfo( allocatedMem, freeMem );

    return os << "[CPU name]: " << dev.m_name.toLatin1() << "\n" << \
                 "[RAM Size]: " << (dev.m_totalMemory)/(1024*1024) << "MB" << "\n" << // memory size returned in Mbytes.
                 "[Available RAM size]: " << freeMem /(1024*1024) << "MB" << "\n" << // memory size returned in Mbytes.
                 "[Cores number]: " << dev.m_coresCount << "\n" << \
                 "[L1 cache size]: " << dev.m_cacheSize[0]/1024 << "KB\n" << \
                 "[L2 cache size]: " << dev.m_cacheSize[1]/1024 << "KB\n" << \
                 "[L3 cache size]: " << dev.m_cacheSize[2]/1024 << "KB\n" << \
                 "[MMX]: " << (dev.m_hasMMX?"available":"not available") << "\n" << \
                 "[SSE level]: " << dev.m_sseLevel;
  }

  // ----------------------- Protected usage --------------------------------------

  SoINTERNAL public:
  static unsigned int s_sse_alignement;

  // return the total memory used by the caller process
  virtual unsigned long long getProcessMemory() const;

protected:

  /**
   * Protected constructor.
   */
  SoCpuDevice();

  /**
   * protected destructor.
   */
  virtual ~SoCpuDevice();

  /** Find function for the find mechanism in SoDevice. */
  static bool findFirstDeviceFunc( SoDevice* device );

  /** Find function to figure out the number of processors. */
  static bool findDevicesCount( SoDevice* device );

  // ----------------------- Private usage --------------------------------------

private:
  void getMemoryInfo( unsigned long long& allocatedMem, unsigned long long& freeMem ) const;

  typedef std::map<std::string, unsigned long long> MemInfoMap;

  /** Fill memInfo with system dependent infos */
  static void fetchMemInfos( MemInfoMap& memInfo );

  /**
   * use m_memInfo to compute memory informations.
   * return true on success
   */
  static bool getTotalAndFreeMem( unsigned long long& totalMem, unsigned long long& freeMem );

  /** Total amount of memory associated to this CPU. */
  unsigned long long m_totalMemory;

  // CPU name
  SbString m_name;

  /** The architecture of the CPU. */
  ProcessorArchitecture m_architecture;

  /** Indicates if the CPU is active in the system. */
  bool m_isActive;

  /** Indicates if the MMX instructions are supported by this device. */
  bool m_hasMMX;

  /** Indicates if SSE is available on this device. */
  bool m_hasSSE;

  /** Indicates the SSE revision for this device. */
  int m_sseLevel;

  /** The number of cores for this processor */
  unsigned int m_coresCount;

  /** The cache size in bytes for the first three levels */
  unsigned int m_cacheSize[3];

  /** Thread mutex to protect the initClass and the exitClass functions. */
  static SbThreadMutex s_initThreadMutex;

  /** The number of processors in the system. */
  static unsigned int s_processorsCount;

  /** The init/exit references counter. */
  static int s_initRefCount;
};

// ----------------------- Inline functions --------------------------------------

inline unsigned long long
SoCpuDevice::getTotalMemory() const
{
  return m_totalMemory;
}

//------------------------------------------------------------------------------
inline SoCpuDevice::ProcessorArchitecture
SoCpuDevice::getArchitecture() const
{
  return m_architecture;
}


//------------------------------------------------------------------------------
inline bool
SoCpuDevice::isActive() const
{
  return m_isActive;
}


//------------------------------------------------------------------------------
inline bool
SoCpuDevice::hasSSE() const
{
  return m_hasSSE;
}


//------------------------------------------------------------------------------
inline int
SoCpuDevice::getSSELevel() const
{
  return m_sseLevel;
}

//------------------------------------------------------------------------------
inline bool
SoCpuDevice::hasMMX() const
{
  return m_hasMMX;
}


//------------------------------------------------------------------------------

#endif // SOCPUDEVICE_H


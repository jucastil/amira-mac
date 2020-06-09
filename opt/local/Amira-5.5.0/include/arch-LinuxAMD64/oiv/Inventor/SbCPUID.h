/*=======================================================================
** VSG_COPYRIGHT_TAG
**=======================================================================*/
/*=======================================================================
** Author      : VSG (MMM YYYY)
**=======================================================================*/
#ifndef _Sb_CPUID_H_
#define _Sb_CPUID_H_

#include <Inventor/sys/port.h>

// currently only support win32 and gcc on x86
#if defined(_WIN32) || (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)))
# define OIV_BUILD_OPTIMIZED 1
#else
# define OIV_BUILD_OPTIMIZED 0
#endif

class INVENTORBASE_API SbCPUID {
public:
  static bool sseSupported();
  static bool sse2Supported();
  static bool sse3Supported();
  static bool mmxSupported();

private:
  static void doCPUCheck();
  static void doCPUID(unsigned int what, unsigned int* features);
  static bool m_sseSupported;
  static bool m_mmxSupported;
  static bool m_sse2Supported;
  static bool m_sse3Supported;
  static bool m_featuresTested;
};

#endif

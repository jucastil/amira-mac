/*
Copyright 1999-2013 Visualization Sciences Group, SAS
Copyright 1995-2013, ZIB Berlin
ALL RIGHTS RESERVED.

amira(R) is a registered trademark of ZIB.

amira(R) is being jointly developed by Zuse Institute Berlin and
Visualization Sciences Group, SAS.
Avizo® is a registered trademark of Visualization Sciences Group, SAS
HardCopy, MeshViz, VolumeViz, TerrainViz are marks of Visualization
Sciences Group, SAS 
Visualization Sciences Group, SAS is a source licensee of OpenGL®, Open Inventor® 
from Silicon Graphics, Inc. OpenGL® and Open Inventor® are 
registered trademark of Silicon Graphics, Inc. All other products and 
company names are trademarks or registered trademarks of 
their respective companies. 

FEI Visualization Sciences Group accepts no liability to any 
party for loss or damage caused by errors or omissions or by 
statements of any kind in this publication, whether such errors 
result from accident, negligence or any other cause. FEI Visualization
Sciences Group assumes  no liability for incidental or consequential
damages arising from the use of information in this publication.
FEI Visualization Sciences Group provides no 
warranties regarding the information contained in this 
publication, whether expressed, implied, or statutory, including 
implied warranties of merchantability or fitness for a 
particular purpose. 

FEI Visualization Sciences Group also does not assume any liability
for links from this publication to publications from other companies,
organizations or individuals. FEI Visualization Sciences Group does not
imply endorsement of any specific  company, organization or individual
through offering links to this content.
All information provided within this publication 
is subject to change at any time and is provided for 
informational purposes only by FEI Visualization Sciences Group.
Copyright 1994-2012 by Visualization Sciences Group, SAS Merignac, France.

*/

/// @addtogroup mclib mclib
/// @{
#ifndef MC_CPUINFO_H
#define MC_CPUINFO_H

#include "McSingleton.h"
#include "McWinDLLApi.h"

#ifdef HX_OS_WIN
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#endif

#if defined HX_OS_LINUX || defined HX_OS_MACX
    #include <unistd.h>
#endif


class MCLIB_API McCPUInfo:public McSingleton<McCPUInfo> {
    friend class McSingleton<McCPUInfo>;

  public:

    /// @return Returns true if the number of cpus, cores and threads per core
    ///         have been successfully detected, otherwise false.
    bool cpuInfoSucceed() const;

    /// Check if this is a little- vs. big-endian machine.
    bool isLittleEndian() const {
        // See http://sjbaker.org/steve/software/cute_code.html.
        static int i=1;
        return *((char*)&i)!=0;
    }

    /// Check for the presence of the CPUID instruction.
    bool hasCPUID() const;

    /// Get the maximum input value supported by the CPUID instruction.
    unsigned int getMaxCPUIDFunc() const;

    /// Get the maximum extended function input value supported.
    unsigned int getMaxCPUIDExtFunc() const;

    /// Return the CPU vendor string.
    const char* getVendorString() const {
        return m_vendor;
    }

    /// Returns if this is an Intel CPU.
    bool isIntel() const {
        unsigned const* vendor=reinterpret_cast<unsigned const*>(m_vendor);

        if (*vendor!=*reinterpret_cast<unsigned const*>("Genu")) {
            return false;
        }

        ++vendor;
        if (*vendor!=*reinterpret_cast<unsigned const*>("ineI")) {
            return false;
        }

        ++vendor;
        if (*vendor!=*reinterpret_cast<unsigned const*>("ntel")) {
            return false;
        }

        return true;
    }

    /// Returns if this is an AMD CPU.
    bool isAMD() const {
        unsigned const* vendor=reinterpret_cast<unsigned const*>(m_vendor);

        if (*vendor!=*reinterpret_cast<unsigned const*>("Auth")) {
            return false;
        }

        ++vendor;
        if (*vendor!=*reinterpret_cast<unsigned const*>("enti")) {
            return false;
        }

        ++vendor;
        if (*vendor!=*reinterpret_cast<unsigned const*>("cAMD")) {
            return false;
        }

        return true;
    }

    /// Returns the number of processors (i.e. CPU sockets), never returns less
    /// than 1.
    unsigned int getCPUCount() const;

    /// Returns the number of cores per processor, never returns less than 1.
    unsigned int getCoreCount() const;

    /// Returns the number of hardware threads per core, never returns less
    /// than 1.
    unsigned int getLPUCount() const ;

    /// Check for an i387-compatible on-chip FPU.
    bool hasFPU() const { return (m_feat_flags_edx&(1<<0))!=0; }

    /// Check for the virtual-8086 mode extension.
    bool hasVME() const { return (m_feat_flags_edx&(1<<1))!=0; }

    /// Check for the debugging extension and register trapping.
    bool hasDE() const { return (m_feat_flags_edx&(1<<2))!=0; }

    /// Check for the page size (support for 4-MB pages).
    bool hasPSE() const { return (m_feat_flags_edx&(1<<3))!=0; }

    /// Check for the time-stamp counter and RDTSC instruction.
    bool hasTSC() const { return (m_feat_flags_edx&(1<<4))!=0; }

    /// Check for model specific registers (RDMSR / WRMSR instructions).
    bool hasMSR() const { return (m_feat_flags_edx&(1<<5))!=0; }

    /// Check for the physical address extension (greater than 32 bits).
    bool hasPAE() const { return (m_feat_flags_edx&(1<<6))!=0; }

    /// Check for the machine check extension (exception 18).
    bool hasMCE() const { return (m_feat_flags_edx&(1<<7))!=0; }

    /// Check if the CMPXCHG8 instruction is supported.
    bool hasCX8() const { return (m_feat_flags_edx&(1<<8))!=0; }


    /// Check if conditional moves (CMOVcc instructions) are supported.
    bool hasCMOV() const { return (m_feat_flags_edx&(1<<15))!=0; }

    /// Check for enabled Processor Serial Number support.
    bool hasPSN() const { return (m_feat_flags_edx&(1<<18))!=0; }

    /// Check for presence of the MMX instruction set.
    bool hasMMX() const { return (m_feat_flags_edx&(1<<23))!=0; }

    /// Check for presence of the SSE instruction set.
    bool hasSSE() const { return (m_feat_flags_edx&(1<<25))!=0; }

    /// Check for presence of the SSE2 instruction set.
    bool hasSSE2() const { return (m_feat_flags_edx&(1<<26))!=0; }

    /// Check Hyper-Threading Technology capability of this processor.
    bool hasHTT() const { return (m_feat_flags_edx&(1<<28))!=0; }

    /// Check for presence of the SSE3 instruction set.
    bool hasSSE3() const { return (m_feat_flags_ecx&(1<<0))!=0; }

    /// Check for implementation of Enhanced Intel SpeedStep technology.
    bool hasEST() const { return (m_feat_flags_ecx&(1<<7))!=0; }

    /// Check if the execution disable bit is supported in PAE mode.
    bool hasXDBit() const { return (m_ext_feat_flags_edx&(1<<20))!=0; }

    /// Checks for availability of MMX instruction extensions.
    bool hasMMXExt() const { return (m_ext_feat_flags_edx&(1<<22))!=0; }

    /// Checks for availability of 64-bit extensions.
    bool hasEM64T() const { return (m_ext_feat_flags_edx&(1<<29))!=0; }

    /// Checks for availability of 3DNow! instruction extensions.
    bool has3DNowExt() const { return (m_ext_feat_flags_edx&(1<<30))!=0; }

    /// Checks for availability of 3DNow! instructions.
    bool has3DNow() const { return (m_ext_feat_flags_edx&(1<<31))!=0; }

    /// Checks if the logical processor count refers to Multi-Core or Hyper-Threading.
    bool hasCMP() const { return isAMD() && (m_ext_feat_flags_ecx&(1<<1))!=0; }

    /// Checks if LAHF /SAHF instructions are supported in 64-bit mode.
    bool hasLAHF() const {
        if (isAMD()) {
            return (m_ext_feat_flags_ecx&(1<<0))!=0;
        }

        if (isIntel()) {
            return (m_ext_feat_flags_ecx&(1<<22))!=0;
        }

        return false;
    }

    /// Conveniece function returning the maximum number of native threads.
    /// Never returns less than 1
    unsigned int getMaxThreadCount() {
        unsigned int numberOfProcessors     = getCPUCount();
        unsigned int numberOfCores          = getCoreCount();
        unsigned int numberOfThreadsPerCore = getLPUCount();
        return numberOfProcessors * numberOfCores * numberOfThreadsPerCore;
    }

  private:

    /// Try to initialize number of cpus, cores per cpu and threads per core
    /// @return Returns false if initalization failed.
    bool initCPUInfo();
    bool m_CPUInfoSuccess;

    mutable char m_vendor[3*4+1];

    unsigned int m_misc_info_ebx;
    unsigned int m_cache_params_eax;
    unsigned int m_ext_addr_ecx;

    unsigned int m_feat_flags_ecx;
    unsigned int m_feat_flags_edx;

    unsigned int m_ext_feat_flags_ecx;
    unsigned int m_ext_feat_flags_edx;

    /// number of physical cpus
    unsigned int m_CPUs;
    /// number of cores per cpu
    unsigned int m_CoresPerCPU;
    /// number of logical processing units per core (e.g. Hyper Threading)
    unsigned int m_LPUsPerCore;

    McCPUInfo();
};

extern MCLIB_API McCPUInfo& McCPU;

#endif // MC_CPUINFO_H

/// @}

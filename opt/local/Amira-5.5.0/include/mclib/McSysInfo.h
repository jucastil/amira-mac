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
#ifndef _MC_SYSINFO_H
#define _MC_SYSINFO_H

#include "McWinDLLApi.h"
#include "McPrimType.h"
#include "McString.h"

class MCLIB_API McSysInfo
{
public:
    /// Return the total amount of physical memory, in bytes.
    static mcuint64 physmem_total();

    ///Return the amount of physical memory available, in bytes.
    static mcuint64 physmem_available();

    /**
     *  Some operating systems (at least Microsoft Vista) can reserve a specific
     *  amount of the system memory for the graphic board.
     *  The graphic board is then able,
     *  to directly work on this memory location.
     *  This method returns the maximum possible shared system video memory in megabytes.
     *  Return 0 if the OS do not support this feature. Currently, only Vista support this feature.
     *  Return 0 if AMIRA_USER_VIDEO_MEM_AMOUNT is set.
     */
    static int maxSharedSystemVideoMemory_total();

    /**
     * Convenience function to verify that the current operating system is >= Windows XP SP2
     * @return returns true if operating system is >= Win XP SP2 otherwise false. On MacX or
     *         Linux respectively the function will always return false.
     */
    static bool verifyGEWinXPSP2(); 

    /**
     * Returns a string containing the operating system Amira is running on.
     */
    static McString operatingSystem();

protected:
    McSysInfo(){}
    static void detectOperatingSystem();
private:
    static int mIsGEWindowsXPSP2;
    static McString mOSString;
};

#endif

/// @}

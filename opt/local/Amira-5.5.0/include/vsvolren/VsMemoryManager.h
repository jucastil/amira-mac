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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef VS_MEMORYMANAGER_H
#define VS_MEMORYMANAGER_H

#include "Vs.h"

#include "VsHandable.h"
#include "VsInterface.h"
#include "VsRelay.h"

#include <mclib/McPrimType.h>

// VS_RELAY_CLASS VsMemoryManager VsRelay
// VS_RELAY_EXPORT_CLASS VsMemoryManager VSVOLREN_API

class VSVOLREN_API VsMemoryManager : public VsInterface
{
    VS_DECL_INTERFACE         ( VsMemoryManager )
    VS_DECL_INTERFACE_FACTORY ( VsMemoryManager )
    VS_DECL_INTERFACE_RELAY   ( VsMemoryManager )

protected:
    VsMemoryManager(VsMeta * inMeta = 0);
    virtual ~VsMemoryManager();

public:
    /// Returns the load manager singleton.
    static VsMemoryManager & getInstance();

    void initMemorySettings(mcuint64 inVolumeMemorySize, mcuint64 inMinMemPerProc, int inMaxNumProc); // VS_RELAY

    //  Set the reserved memory under Linux (on the server side)
    //  bytes      = number of bytes to be reserved
    //  bytes_left = number of bytes which possibly can be reserved
    //               (currently available server main memory)
    //  return     = true means that the server had resered the memory
    bool reserveMemory(mcuint64 bytes, mcuint64 & bytes_left); // VS_SYNC_CALL

    //  Gives some reserved memory under Linux free (on the server side)
    //  bytes      = number of bytes what should be given free
    //  return     = true means that the server had given free the memory
    bool decreaseReservedMemory(mcuint64 bytes); // VS_SYNC_CALL

    //  Reserves some memory under Linux additionally (on the server side)
    //  bytes      = number of bytes what should be given free
    //  bytes_left = number of bytes which possibly can be reserved
    //               (currently available server main memory)
    //  return     = true means that the server had reserved the memory
    bool increaseReservedMemory(mcuint64 bytes, mcuint64 & bytes_left); // VS_SYNC_CALL

    // Gets the reserved memory size.
    const mcuint64 getReservedMemory(); // VS_SYNC_CALL
};


// This is helper class to reserve additional memory.
// The constructor is used to reserve additional memory
// (by calling VsMemoryManager::increaseReservedMemory()).
// The memory is then freed in the destructor
// (by calling VsMemoryManager::decreaseReservedMemory())
class VSVOLREN_API VsMemoryReserver : public VsHandable
{
public:
    enum
    {
        RESERVE_UNKNOWN = 0,
        RESERVE_LABELS,
        RESERVE_BONE,
        RESERVE_CALCIUM_SCORING,
        RESERVE_CARDIAC_SEGMENT,
        RESERVE_CARDIAC_ANALYSIS,
        RESERVE_PATIENT_TABLE,
        RESERVE_VESSEL,
        RESERVE_LASSO,
        RESERVE_CLIPPED_DENSITY,
        RESERVE_COUNT
    };
    
    // increases reserved memory by "bytes".
    VsMemoryReserver(mcuint64 bytes, int hint = RESERVE_UNKNOWN);

    // decreases reserved memory that was reserved in constructor
    ~VsMemoryReserver();

    // returns true if memory reservation was successful or false
    // otherwise
    bool isReservedOK() const;

    // when set to false, memory reserved by constructor will not be
    // decreased by destructor. this is helpful for algorithms that if
    // sucessful keep the memory allocated for its results.
    // by default memory IS decreased by constructor - UnreserveOnDestruction equals true.
    /* for example workflow for labels creation:
    
        bool createLabels(VsVolume *v)
        {
            size_t size = mulitiply_of_volume_dimensions;
            VsMemoryReserver reserver(size);
            if (reserver.isReservedOK() == false)
            {
                // cannot reserve memory - operation cannot be performed!!!
                return false;
            }
            // some operations that might fail
            if (operation1 failed)
            {
                // destructor will decrease reserved memory
                return false
            }
            ...
            if (operation2 failed)
            {
                // destructor will decrease reserved memory
                return false
            }
            // labels created - success!!!
            // keep memory reserved
            reserver.setKeepReservedOnDestruction(true);
            // destructor will not decrease reserved memory
            return true;
       }
    */
    void setKeepReservedOnDestruction(bool aFlag);
    
private:
    // never call default constructor
    VsMemoryReserver();
    // never call copy constructor
    VsMemoryReserver(const VsMemoryReserver &other);
    
    
    bool mReservedOK;
    bool mKeepReserved;
    mcuint64 mReservedBytes;
    
    int mHint;
    
    // for statistics only follows
    static bool mVerbose;
    // memory kept (not released by destructors)
    static mcuint64 mKeptAfterDestruction;
    
    static const char *mHintData[];
};

#endif // VS_MEMORYMANAGER_H

/// @}

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

/// @addtogroup mclibthreaded mclibthreaded
/// @{
#ifndef _MC_MUTEX_H
#define _MC_MUTEX_H

#include "McLibThreadedWinDLLApi.h"

class McMutexPrivate;
class McWaitCondition;


/** The HxMutex class provides access serialization between threads.
    A mutex object can only be locked by one thread at a time. Calling
    lock() for an already locked mutex causes the calling thread to be
    suspended until the mutex is unlocked again. */
class MCLIBTHREADED_API McMutex
{
  public:
    /** Constructor. The mutex is created in an unlocked state. A recursive
        mutex is created if recursive is TRUE; a normal mutex is created if
        recursive is FALSE (the default). With a recursive mutex, a thread
        can lock the same mutex multiple times and it will not be unlocked
        until a corresponding number of unlock() calls have been made. */
    McMutex( bool recursive = 0 );

    /// Destructor.
    virtual ~McMutex();

    /** Locks the mutex. If the mutex is already locked the method waits
        until the mutex gets unlocked again. */
    void lock();

    /** Attempt to lock the mutex. If the lock was obtained, this function 
        returns TRUE. If another thread has locked the mutex, this function 
        returns FALSE, instead of waiting for the mutex to become available, 
        i.e. it does not block.  */
    bool tryLock();

    /// Unlocks a locked mutex.
    void unlock();

    /// Checks if the mutex is locked.
    bool locked();

private:

    McMutexPrivate * d;

    friend class McWaitCondition;
};


#endif // _MC_MUTEX_H

/// @}

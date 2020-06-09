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
#ifndef _MC_THREAD_BARRIER_H
#define _MC_THREAD_BARRIER_H

#include "McLibThreadedWinDLLApi.h"

#include "McMutex.h"
#include "McWaitCondition.h"


/** Facilitates synchronization between multiple threads. */
class MCLIBTHREADED_API McThreadBarrier
{
public:

    /// Creates a new barrier for @c count threads.
    McThreadBarrier( int count )
    :   mThreshold  ( count ),
        mCount      ( count ),
        mCycle      ( 0 )
    {
    }

    /** Enter the barrier. The methods waits until as many threads as
    specified in the constructor have entered the barrier. Returns true 
    if current thread was the last missed thread in this barrier. */
    bool enter()
    {
        bool status = false;

        mMutex.lock();
        int cycle = mCycle;

        --mCount; // next thread has arrived

        if ( mCount == 0 )
        {   // all threads have arrived
            mCycle++;
            mCount = mThreshold;
            mWaitCondition.wakeAll(); // wake all waiting threads
            status = true;
        } 
        else 
        {   // there are missing threads -> wait
            while (cycle == mCycle) // guard against spurious returns
                mWaitCondition.wait( & mMutex );
        }

        mMutex.unlock();
        return status;
    }


private:

    int                 mThreshold;     // number of threads that have to be in the barrier until it opens
    int                 mCount;         // number of threads missing
    int                 mCycle;

    McMutex             mMutex;
    McWaitCondition     mWaitCondition;
};


#endif // _MC_THREAD_BARRIER_H

/// @}

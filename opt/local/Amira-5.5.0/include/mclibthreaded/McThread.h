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
#ifndef _MC_THREAD_H
#define _MC_THREAD_H

#include "McLibThreadedWinDLLApi.h"

#include <limits.h> // ULONG_MAX


class McThreadPrivate;


/// A platform-independent thread class.
class MCLIBTHREADED_API McThread
{
public:

    /// Constructor.
    McThread();

    /// Constructor taking a custom thread name;
    McThread(const char* name);

    /// Destructor (does not terminate a running thread).
    virtual ~McThread();

    /// Sets the name of the thread.
    void setThreadName(const char* name);

    /// Returns the name of the thread.
    const char* threadName() const;

    /** Wait for a time-out or for a thread to terminate. The method waits
        until the associated thread terminates or until the specified
        number of milliseconds have elapsed. In the first case true is
        returned, in the second case false is returned. */
    bool wait( unsigned long time = ULONG_MAX );

    /** Starts the thread. The overloaded method run() is executed in a
        separate thread. If the thread is already running the method waits
        until it terminates and then starts it again. */
    void start();

    /// Checks if the thread has been finished or not.
    bool finished() const;

    /// Checks if the thread is running or not.
    bool running() const;

    static void exit();

    static void sleep ( unsigned long secs );

    static void msleep( unsigned long msecs );

    static void usleep( unsigned long usec );

    static void setThreadNameNative(const char* name);

protected:

    /// Override this function to do the actual work.
    virtual void run() = 0;


private:

    McThreadPrivate * d;
    friend class McThreadPrivate;
};


#endif // _MC_THREAD_H

/// @}

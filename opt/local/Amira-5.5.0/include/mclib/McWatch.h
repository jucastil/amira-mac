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
#ifndef MC_WATCH_H
#define MC_WATCH_H

#include "McWinDLLApi.h"

#include <stdio.h>
#include <limits.h>

/** Timer class for benchmarking purposes.
    This is a simple timer class which is useful for benchmarking. All
    times are returned in seconds. On Windows systems the implementation
    relies on the @c QueryPerformanceCounter() function while on UNIX
    systems it relies on the @c times() system call. The timer can be
    started, stopped, and continued. In addition a simple print method
    is provided.
*/
class McString;

#ifdef HX_OS_WIN

class MCLIB_API McWatch
{
  public:
    /// Constructor already starts the watch.
     McWatch();
     McWatch( const char * inName );
    ~McWatch();

    /// Starts stop watch from 0.
    void start();

    /// Stops counting and returns elapsed time in seconds.
    float stop();

    /// Continues counting at current score.
    void cont();

    /// Returns elapsed time in seconds, watch need not to be stopped.
    float getTime();

    /// Returns user time in seconds (UNIX only).
    float getUserTime();

    /// Returns system time in seconds (UNIX only).
    float getSystemTime();

    /// Returns CPU time, i.e., sum of user and system time (UNIX only).
    float getCPUTime();

    /// Print current times.
    void show(FILE* fp = stderr);

    /// Return string with hours, minutes and seconds
    McString getHumanReadableString();

  protected:
    int         stopped;
    __int64     cAcc;
    __int64     cOffset;
    __int64     cFrequency;
    McString  * mName;
};

// #elif !defined(__sgi) && !defined(__linux) //needarch
#elif !defined(__sgi)

#include <unistd.h>
#include <sys/times.h>

#ifndef CLK_TCK
#ifdef __linux
#define CLK_TCK sysconf(2) /* 2 is _SC_CLK_TCK, clock ticks per second */
#else
#define CLK_TCK sysconf(3) /* 3 is _SC_CLK_TCK, clock ticks per second */
#endif
#endif

class McWatch
{
  protected:
    int stopped;
    clock_t cAcc, cOffset;
    struct tms tAcc, tOffset;

    clock_t getTime(struct tms* acc) {
    clock_t c = cAcc;
    *acc = tAcc;
    if (!stopped) {
        struct tms t;
        c += times(&t) - cOffset;
        acc->tms_utime += t.tms_utime - tOffset.tms_utime;
        acc->tms_stime += t.tms_stime - tOffset.tms_stime;
        acc->tms_cutime += t.tms_cutime - tOffset.tms_cutime;
        acc->tms_cstime += t.tms_cstime - tOffset.tms_cstime;
    }
    return c;
    }

  public:
    // Starts stop watch from 0.
    void start() {
    stopped = 0;
    cAcc = 0;
    tAcc.tms_utime = 0;
    tAcc.tms_stime = 0;
    tAcc.tms_cutime = 0;
    tAcc.tms_cstime = 0;
    cOffset = times(&tOffset);
    }

    // Stops counting and returns elapsed time in seconds.
    float stop() {
    stopped = 1;
    struct tms t;
    cAcc += times(&t) - cOffset;
    tAcc.tms_utime += t.tms_utime - tOffset.tms_utime;
    tAcc.tms_stime += t.tms_stime - tOffset.tms_stime;
    tAcc.tms_cutime += t.tms_cutime - tOffset.tms_cutime;
    tAcc.tms_cstime += t.tms_cstime - tOffset.tms_cstime;
    return (float)cAcc/CLK_TCK;
    }

    // Continues counting at current score.
    void cont() {
    stopped = 0;
    cOffset = times(&tOffset);
    }

    // Returns elapsed time in seconds.
    float getTime() {
    struct tms t;
    return (float) getTime(&t)/CLK_TCK;
    }

    // Returns elapsed user time in seconds.
    float getUserTime() {
    struct tms t;
        getTime(&t);
    return (float) t.tms_utime/CLK_TCK;
    }

    // Returns elapsed system time in seconds.
    float getSystemTime() {
    struct tms t;
        getTime(&t);
    return (float) t.tms_stime/CLK_TCK;
    }

    // Returns elapsed CPU time (user and system) in seconds.
    float getCPUTime() {
    struct tms t;
        getTime(&t);
    return (float)(t.tms_utime+t.tms_stime)/CLK_TCK;
    }

    // Print current times.
    void show(FILE* fp = stderr) {
    struct tms t;
        clock_t c = getTime(&t);
    fprintf(fp, "Elapsed Time %.3fs (CPU time=%.3fs)\n",
       (float) c/CLK_TCK, (float) (t.tms_utime+t.tms_stime)/CLK_TCK);
    }

    // Constructor starts stop watch.
     McWatch();
     McWatch( const char * inName );
    ~McWatch();

    /// Return string with hours, minutes and seconds
    McString getHumanReadableString();

    McString  * mName;
};

#else /* __sgi */

#include <time.h>

#ifdef __sgi
#define CLOCK_ID CLOCK_SGI_CYCLE
#else
#define CLOCK_ID CLOCK_REALTIME
#endif

class McWatch
{
  public:
    // Constructor already starts the watch.
     McWatch();
     McWatch( const char * inName );
    ~McWatch();

    // Starts stop watch from 0.
    void start() {
        stopped = 0;
        cAcc.tv_sec = 0;
        cAcc.tv_nsec = 0;
        clock_gettime(CLOCK_ID,&cOffset);
    }

    // Stops counting and returns elapsed time in seconds.
    float stop() {
        stopped = 1;
        struct timespec c;
        clock_gettime(CLOCK_ID,&c);
        addTo(cAcc,c);
        subtractFrom(cAcc,cOffset);
        return (float)cAcc.tv_sec + cAcc.tv_nsec/1000000000.0f;
    }

    // Continues counting at current score.
    void cont() {
        stopped = 0;
        clock_gettime(CLOCK_ID,&cOffset);
    }

    // Returns elapsed time in seconds, watch need not to be stopped.
    float getTime() {
        struct timespec c = cAcc;
        if (!stopped) {
            clock_gettime(CLOCK_ID,&c);
            addTo(c,cAcc);
            subtractFrom(c,cOffset);
        }
        return (float)c.tv_sec + c.tv_nsec/1000000000.0f;
    }

    // Returns user time in seconds (UNIX only).
    float getUserTime() {
        return getTime();
    }

    // Returns system time in seconds (UNIX only).
    float getSystemTime() {
        return getTime();
    }

    // Returns CPU time, i.e., sum of user and system time (UNIX only).
    float getCPUTime() {
        return getTime();
    }

    // Print current times.
    void show(FILE* fp = stderr) {
        fprintf(fp, "Elapsed Time %.3fs\n", getTime());
    }

    /// Return string with hours, minutes and seconds
    McString getHumanReadableString();



  protected:
    int stopped;
    struct timespec cAcc, cOffset;
    McString  * mName;

    void addTo(struct timespec& a, const struct timespec& b) {
        a.tv_sec += b.tv_sec;
        a.tv_nsec += b.tv_nsec;
        if (a.tv_nsec >= 1000000000) {
            a.tv_sec++;
            a.tv_nsec -= 1000000000;
        }
    }

    void subtractFrom(struct timespec& a, const struct timespec& b) {
        a.tv_sec -= b.tv_sec;
        a.tv_nsec -= b.tv_nsec;
        if (a.tv_nsec < 0) {
            a.tv_sec--;
            a.tv_nsec += 1000000000;
        }
    }
};

#endif

#endif

/// @}

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

/// @addtogroup schedule schedule
/// @{
#ifndef HX_JOB_LIST_H
#define HX_JOB_LIST_H

#include <schedule/ScheduleWinDLLApi.h>

#include <mclib/McDArray.h>
#include <mclib/McString.h>
#include <mclib/McHandle.h>
#include <mclib/McFilename.h>
#include <schedule/HxJob.h>

class SCHEDULE_API HxJobList {
  public:
    HxJobList();

    ~HxJobList();

    int size() const { return list.size(); }

    McHandle<HxJob> operator[] (int i) const { return list[i]; }

    void submit(const char* cmd, const char* info, const char* tmpdir);

    int remove(McHandle<HxJob> job);

    int run(McHandle<HxJob> job=0);

    int kill();

    void update();

    int hasWaitingJobs();

    int isRunning();

  protected:
    McString theHost;
    McString theUser;
    McString theHome;
    McDArray< McHandle<HxJob> > list;

    void lockQueue();
    void readQueue(McDArray< McHandle<HxJob> >&);
    void writeQueue(McDArray< McHandle<HxJob> >&);
    void readQueue(const char* value, McDArray< McHandle<HxJob> >&);
    void writeQueue(McString& value, McDArray< McHandle<HxJob> >&);
    void unlockQueue();
    McHandle<HxJob> find(McHandle<HxJob>, McDArray< McHandle<HxJob> >&);

    int serverPort;
    McDArray<int> socketsToBeClosed;

#ifdef _WIN32
    HxJob* currentJob;
    static void execute(void* userData);
#endif
    
    friend class HxJobServer;

    static McFilename logFile;
    static void log(const char* format, ...);
};

#endif


/// @}

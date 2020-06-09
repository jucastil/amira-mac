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
#ifndef HX_JOB_SERVER_H
#define HX_JOB_SERVER_H

#include <schedule/ScheduleWinDLLApi.h>

#include <stdio.h>
#include <mclib/McFilename.h>
#include <mclib/McServerSocket.h>
#include <mclib/McStringTokenizer.h>
#include <schedule/HxJobList.h>

class SCHEDULE_API HxJobServer : public McServerSocket {

  public:
    HxJobServer(int port);

    ~HxJobServer();

    void mainLoop();

    void submit(int csd, McStringTokenizer&);

    void remove(int csd, McStringTokenizer&);

    void run(int csd, McStringTokenizer&);

    void kill(int csd);

    void status(int csd);

    void list(int csd);

    void done(int csd);

    int isRunning() const { return runFlag; }

    static void send(int port, const char* format, ...);

    static int main(int argc, char* argv[]);

  protected:
    void handleRequest(int client_socket);

    void interprete(int client_socket, char* command);

    void answer(int client_socket, const char* format, ...);

    McHandle<HxJob> findJob(McStringTokenizer&);

    HxJobList jobList;
    unsigned int runFlag:1;
    unsigned int terminated:1;
    unsigned int runQueueFlag:1;
};

#endif

/// @}

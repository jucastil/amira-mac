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
#ifndef MC_HTTPD_H
#define MC_HTTPD_H

#include "McWinDLLApi.h"
#include "McDArray.h"
#include "McSocket.h"
#include "McServerSocket.h"

#include <stdio.h>

/// Provides a simple http daemon.

class MCLIB_API McHttpd : public McServerSocket
{
  public:
    /// Constructor.
    McHttpd(int port, FILE* log=stderr);

    /// Destructor.
    virtual ~McHttpd();

    /// Returns host name of server as IP-number.
    const char* getHost();

    /// Reads command from client socket and interpretes it.
    void handleRequest(int csd);

    /// Enters an endless loop, waits for incoming connections.
    void mainLoop();

    ///
    void setHxCallback(void (*f)(const char*, void*), void* ptr) {
	hxCallback = f;
	hxUserData = ptr;
    }

protected:
    FILE* log;
    int terminated;
    void* hxUserData;
    void (*hxCallback)(const char* script, void*);

    ///
    int interprete(int which, char *request);

    /// Check, if file is a script which should be executed.
    int executeScript(int which, char* file);
    int fileNotFound(int which, char* file, int flen);
    int send(int which, const char *msg, int len);
};

#endif

/// @}

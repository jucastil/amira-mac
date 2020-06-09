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
#ifndef MC_SOCKET_H
#define MC_SOCKET_H

#include "McWinDLLApi.h"
#include <fcntl.h>
#include <stdio.h>

class McString;

/** This class provides useful functions for dealing with sockets. The
    class contains no member variables and all functions are static.
    @see McServerSocket
*/

class MCLIB_API McSocket
{
  public:
    /** On WIN32 this function has to be called once before using sockets.
        It is called automatically in the constructor of McServerSocket. */
    static void initSocketLayer();

    /// Checks whether WIN32 socket layer has been initialized.
    static int isInitialized() { return socketLayerInitialized; }

    /// Turns a socket into blocking mode.
    static void blocking(int sd);

    /// Turns a socket into non-blocking mode.
    static void nonBlocking(int sd);

    /// Checks whether the socket is non-blocking.
    static int isNonBlocking(int sd);

    /** The method blocks until n bytes have been read from the socket
        or until an error occurred. If @c lineMode is true the method
        terminates reading if a new-line character has been found or if
        n-1 bytes have been read. The string read into @c buf will be
        terminated by a null character if @c lineMode is true. On success
        the number of bytes read is returned, otherwise -1. */
    static int receive(int sd, char *buf, int n, int lineMode=0);

    /** The method reads characters from the socket @c sd into the
        specified string until a new-line character is found. The method
        is blocking. If some error is encountered -1 is returned.
        Otherwise the number of bytes read is returned, which is given
        by buf.length(). */
    static int readLine(int sd, McString& buf);

    /// Writes string without trailing zero into socket.
    static int send(int sd, const char* format, ...);

    /// Calls close() on Unix and closesocket() on Windows.
    static int close(int sd);

    /// Calls setsockopt() in order to resize the send buffer.
    static void resizeSendBuffer(int sd, int size);

    /** Connects to specified port and host. If host is null the local host
        will be used. On success a new socket descriptor will be returned.
        Otherwise -1 will be returned. In this case, use strerror() in order
        to get an error description. */
    static int connect(const char* hostname, int port);

    /// Returns string indicating last socket error.
    static const char* strerror();

  protected:
    static int socketLayerInitialized;
};

#endif // MC_SOCKET_H

/// @}

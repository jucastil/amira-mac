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
#ifndef MC_SERVER_SOCKET_H
#define MC_SERVER_SOCKET_H

#include "McWinDLLApi.h"
#include <fcntl.h>

/** This class opens a server socket which clients may connect to.
    @see McSocket
*/

class MCLIB_API McServerSocket
{
  public:
    /** Constructor. If verbose is true a message will be printed
        to stderr whenever a socket operation failed. If this option
	is false you may still access the last error message via
	McSocket::strerror(). */
    McServerSocket(int verbose=1);

    /// Destructor.
    ~McServerSocket();

    /** Opens the socket, binds it to the specified port, and makes it
        listening for connections.

        If the specified port has not been closed properly before it will
        usually be disabled by the system for a while. In this case binding
        the socket will fail and @c openSocket() will return 0. If the
        parameter @c nTries is larger than 1 then multiple attempts will be
        taken to bind the socket. Between each attempt execution of the
        program will be suspended by one second. If @c nTries is zero an
        infinite number of attempts will be taken.

        If @c nTries is negative the method does not retry to bind the
        socket to the same port but to the next higher port. In this case,
        program execution is not suspended but the next attempt to bind the
        socket is taken immediately. On success the method returns the port
	the socket has been actually bound to. Otherwise, it returns -1.

        The argument @c backlog denotes the size of the queue for incoming
        connections. */
    int openSocket(int port, int nTries=1, int backlog=10);

    /** Accepts a connection on the server socket. If a new connection
        has been accepted a new socket file descriptor is returned. You
        may use this new file descriptor in order to communicate with
        the client via @c read() or @c write(). If no connection is pending
        and non-blocking mode has been enabled via @c nonBlocking()
        the method returns -1. Otherwise, it waits until a connection
        has been accepted. */
    int accept();

    /// Makes the socket blocking.
    void blocking();

    /// Makes the socket non-blocking.
    void nonBlocking();

    /// Checks whether the socket is non-blocking.
    int isNonBlocking() const;

    /// Returns the port the socket is bound to, or 0 if socket isn't open.
    int port() const { return thePort; }

    /// Returns socket identifier, or 0 if socket isn't open.
    int socket() const { return theSocket; }

    /// Returns 1 if the socket is open and bound to a port.
    int isOpen() const { return (theSocket>-1) && (thePort>-1); }

    /// Closes the socket.
    void close();

    /// If this flag is set error messages are printed to stderr.
    int verbose;

  protected:
    int thePort;
    int theSocket;

    void error(const char* func=0);
};

#endif

/// @}

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
#ifndef __MCPERLFILE_H
#define __MCPERLFILE_H

#include "McWinDLLApi.h"
#include "McString.h"

#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

/** Perl file handling
	@c McPerlFile provides open and access functionality as known from
  Perl. For example, you can easily pipe a command's output into your program.
  The constructor takes a string argument which indicates
  how the file should be opened. If it starts with ``<'' the file is
  opened for input. If it begins with ``>'' the file is opened for
  output. If the string begins with ``>>'', the file is opened for
  appending. If it begins with ``|'', the string is interpreted as a
  command to which output is to be piped, and if the string ends with a
  ``|'', it is interpreted as a command which pipes to us.
  */

class MCLIB_API McPerlFile {
    int _filed;
    char* _str;
    pid_t _pid;

    McDArray<char*>& cmdArgv(char* str) {
        McDArray<char*> argv;
        argv.append("sh");
        argv.append("-c");
        char* q = str + strlen(str);
        while (str < q) {
            argv.append(str);
            while (*str) str++;
            str++;
            while (str < q && isspace(*str)) str++;
        }
        argv.append((char*) 0);
        return argv;
    }

public:
    /** @name Constructor */
    //@{
    /** Create a new file descriptor. See the class description for detailed
      information about the string's format. */

    McPerlFile(char* str) {
        _str = MC_strdup("");
        open(str);
    }
    //@}

    /** @name Destructor */
    //@{
    /// Close file.
    ~McPerlFile() {
        free(_str);
        close();
    }
    //@}

    /** @name Access Method */
    //@{
    /// Return file descriptor.
    int filed() { return _filed; }
    //@}

    /** @name Methods */
    //@{
    /** Open a file. See the class description for detailed information about
      the string's syntax. If a file is created it is created using access
      modes as specified by <em> mode</em>. */
    int open(char* str, mode_t mode = 0644) {
        free(_str);
        _str = MC_strdup(str);
        char* strp = _str;
        while (*strp && isspace(*strp)) strp++;
        int oflag = O_WRONLY;
        _pid = -1;
        switch (*strp) {
            case '<' :
                strp++;
                while (*strp && isspace(*strp)) strp++;
                return(_filed = ::open(strp, O_RDONLY));

            case '>' :
                if (strp[1] == '>') {
                    strp++;
                     oflag |= O_APPEND;
                }
                 else
                      oflag |= O_CREAT;
                 strp++;
                while (*strp && isspace(*strp)) strp++;
                return(_filed = ::open(strp, oflag, mode));

            case '|' :
                strp++;
                while (*strp && isspace(*strp)) strp++;
                {
                    int io[2];
                    pipe(io);
                    _pid = fork();
                    if (_pid > 0) {
                        ::close(io[0]);
                        return(_filed = io[1]);
                    }
                    if (_pid == 0) {
                        McDArray<char*>& argv = cmdArgv(strp);
                        ::close(io[1]);
                        dup2(io[0], MC_fileno(stdin));
                        execvp(argv[0], argv);
                    }
                    return -1;
                }
        }

        if (strp[strlen(strp) - 1] == '|') {
            strp[strlen(strp) - 1] = '\0';
            int io[2];
            pipe(io);
            _pid = fork();
            if (_pid > 0) {
                ::close(io[1]);
                return(_filed = io[0]);
            }
            if (_pid == 0) {
                McDArray<char*>& argv = cmdArgv(strp);
                dup2(io[1], MC_fileno(stdout));
                ::close(io[0]);
                execvp(argv[0], argv);
            }
        }

        while (*strp && isspace(*strp)) strp++;
        return(_filed = ::open(strp, O_RDONLY));
    }

    /// Close file.
    int close() {
        if (_pid > 0) kill(_pid, SIGKILL);
        return ::close(_filed);
    }

    /** Read a single line from file into string <em> s</em>. Return 1 on
      success, 0 otherwise. */
    int readLine(McString& s) {
        char c;
        s = "";
        if (::read(_filed, &c, 1) <= 0) return 0;
        do
            s += c;
        while (c != '\n' && ::read(_filed, &c, 1) > 0);
        return 1;
    }

    /** Return a reference to an array of lines of the file. */
    McDArray<McString>& readLines() {
        McDArray<McString> lines;
        McString* s;
        while (readLine(*(s = new McString()))) lines.append(*s);
        return lines;
    }

    /// Read <em> len</em> bytes into specified buffer <em> buf</em> from file.
    int read(McDArray<char>& buf, size_t len) {
        if (buf.size() != len) buf.resize(len);
        return ::read(_filed, (void*) ((char*) buf), len);
    }
    //@}
};

#endif

/// @}

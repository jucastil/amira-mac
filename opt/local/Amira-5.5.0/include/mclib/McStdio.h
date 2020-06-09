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
#ifndef MC_STDIO_H
#define MC_STDIO_H

#include <fcntl.h>

#if defined(_WIN32) || defined(_WIN64)
#   include <io.h>
#   include <direct.h>

#   define MC_getpid     ::_getpid
#   define MC_isatty     ::_isatty
#   define MC_creat      ::_creat
#   define MC_chmod      ::_chmod
#   define MC_open       ::_open
#   define MC_close      ::_close
#   define MC_lseek      ::_lseeki64
#   define MC_tstat      ::_tstat
#   define MC_read       ::_read
#   define MC_write      ::_write
#   define MC_access     ::_access
#   define MC_getcwd     ::_getcwd
#   define MC_chdir      ::_chdir
#   define MC_mkdir(a,b) ::_mkdir(a)
#   define MC_rmdir      ::_rmdir
#   define MC_unlink     ::_unlink
#   define MC_ftello     ::_ftelli64
#   define MC_off_t      __int64

#   if defined(_MSC_VER) && _MSC_VER >= 1400
#       define MC_fileno     ::_fileno
#   else
#       define MC_fileno     ::fileno
#   endif

#   define MC_rename     ::rename

#   define MC_O_RDONLY   _O_RDONLY
#   define MC_O_WRONLY   _O_WRONLY
#   define MC_O_RDWR     _O_RDWR
#   define MC_O_CREAT    _O_CREAT
#   define MC_O_TRUNC    _O_TRUNC
#   define MC_O_APPEND   _O_APPEND
#   define MC_O_BINARY   _O_BINARY

#   define MC_F_OK 00
#   define MC_R_OK 04
#   define MC_W_OK 02

#   define MC_strdup _strdup
#   define MC_stricmp _stricmp
#   define MC_strnicmp _strnicmp
#else
#   include <unistd.h>

#   define MC_getpid     ::getpid
#   define MC_isatty     ::isatty
#   define MC_creat      ::creat
#   define MC_chmod      ::chmod
#   define MC_open       ::open
#   define MC_close      ::close

#   if defined (HX_OS_MACX)
#       define MC_lseek      ::lseek
#   else
#       define MC_lseek      ::lseek64
#   endif

#   define MC_tstat      ::tstat
#   define MC_read       ::read
#   define MC_write      ::write
#   define MC_access     ::access
#   define MC_getcwd     ::getcwd
#   define MC_chdir      ::chdir
#   define MC_mkdir      ::mkdir
#   define MC_rmdir      ::rmdir
#   define MC_unlink     ::unlink
#   define MC_fileno     ::fileno
#   define MC_rename     ::rename
#   define MC_ftello     ftello
#   define MC_off_t      off_t

#   define MC_O_RDONLY   O_RDONLY
#   define MC_O_WRONLY   O_WRONLY
#   define MC_O_RDWR     O_RDWR
#   define MC_O_CREAT    O_CREAT
#   define MC_O_TRUNC    O_TRUNC
#   define MC_O_APPEND   O_APPEND
#   define MC_O_BINARY   0

#   define MC_F_OK F_OK
#   define MC_R_OK R_OK
#   define MC_W_OK W_OK

#   define MC_strdup strdup
#   define MC_stricmp stricmp
#   define MC_strnicmp strnicmp
#endif

#endif // MC_STDIO_H

/// @}

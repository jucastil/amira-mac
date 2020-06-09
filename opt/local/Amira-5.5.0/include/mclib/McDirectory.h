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
#ifndef MC_DIRECTORY_H
#define MC_DIRECTORY_H

#include "McWinDLLApi.h"

#include "McDArray.h"
#include "McString.h"

/// Scan directory in file system.
class MCLIB_API McDirectory {

  public:
    /** Character used to separate directories in a path.*/
    static inline char pathDelimiter() {
#ifdef WIN32
        return('\\');
#else
        return('/');
#endif
    }

    /** Scan a directory for files. @c dirname contains the path of the directory,
        @c pattern specifies a filter (may contain wild cards),
        the result is returned in @c list.
        @return number of directory entries or -1 if error occurred */
    static int scan(const char *dirname, McDArray<McString> &list,
	            const char *pattern=0);

    /** This method is provided for compatibility only. The list elements
        are allocated with MC_strdup(). You have to explicitly free() them.
        @return number of directory entries or -1 if error occurred */
    static int scan(const char *dirname, McDArray<char*> &list,
	            const char *pattern=0);

    /** Check whether a given name is a directory.*/
    static int isDirectory(const char *dirname);

    /** Recursively copy a directory to another one. If @c to denotes
        an existing directory a new subdirectory with the basename of
        @c from is created in it. If @c to does not already exist it is
        created and the contents of @c from are copied into the new
        directory. @return 0 on success, !=0 otherwise. */
    static int copy(const char* from, const char* to);

    /** Returns the available free space on the filesystem where @c dirname resides
        @return number of free bytes or -1 if the number could not be obtained */
    static mcint64 freeSpace(const char * dirname);
};

#endif

/// @}

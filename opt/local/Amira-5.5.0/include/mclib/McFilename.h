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
#ifndef MCFILENAME_H
#define MCFILENAME_H

#include "McWinDLLApi.h"

#include "McString.h"
#include <sys/types.h>

/** This class implements some utility methods which are useful when
    working with filenames. All methods return 1 on success and 0 on
    failure. This is in contrast to the standard system calls. The
    permissions of a file are interpreted as octal numbers in the
    usual way (see chmod(1)). Remember that octal numbers in C and C++
    begin with a 0.
    @see McTmpDir
*/

class MCLIB_API McFilename : public McString
{
  public:
    /// Default constructor.
    McFilename();

    /// Copy constructor.
    McFilename(const McString& rhs);

    /// Copy constructor.
    McFilename(const McFilename& rhs);

    /// Assignment operator.
    McFilename& operator=(const McString& rhs);

    /// Assignment operator.
    McFilename& operator=(const McFilename& rhs);

    /// Assignment operator.
    McFilename& operator=(const char* rhs);

    /// This constructs a filename from a character string.
    McFilename(const char* str);

    /// Check if file does exist.
    int doesExist() const;

    /// Check if file does exist and is a directory.
    int isDirectory() const;

    /** Check if file does exist and is readable. On Windows the method
        always returns 1 if applied to an existing directory. On Unix the
        method returns 1 if the directory contents can be read. */
    int isReadable() const;

    /** Check if file does exist and is writable. On Windows the method
        always returns 1 if applied to an existing directory. On Unix the
        method returns 1 if files can be written in the directory. */
    int isWriteable() const;

    /// Check if file name represents a relative path.
    int isRelative() const;

    /// Create an empty file with given permissions.
    int create(int mode = 0664) const;

    /// Return permissions or 0 if file doesn't exist.
    int getMode() const;

    /// Set permissions of file.
    int setMode(int mode) const;

    /// Removes file.
    int unlink() const;

    /// Renames file.
    int rename(const char* newName);

    /// Copies file.
    int copy(const char* dst);

    /// Create unique filename by appending numbers.
    void makeUnique();

    /// Returns base part of file name.
    char* basename() const;

    /// Returns extension part of file name
    char* extension() const;

    /// Gets directory part of file name including the trailing @c /.
    int dirname(McString& result) const;

    /** Creates a temporary file in the given directory. If @c tmpPath is null
	(as it is in the default case) McTmpDir::getSystemTmpPath() is
	used to get the system temp directory. */
    static McFilename getTempFilename(const char* tmpPath = 0);

    /// Static version of basename().
    static const char* basename(const char* string);

    /// Static version of extension().
    static const char* extension(const char* string);

    /// Static version of dirname().
    static int dirname(const char* string, McString& result);

    /** Expands filename so that it represents an absolute path.
	This method inserts the current working directory in front
	of the filename, if it does not already begin with a @c /.
	If the first character of the filename is a @c ~, POSIX style
	tilde substitution is performed.

	If the tilde is followed by a @c /, then the environment
	variable HOME is substituted. Otherwise the characters
	between the tilde and the next slash are taken as a user name.
	This name is looked up in the NIS passwd database. The
	user's home directory is retrieved from the database and
	is substituted. */
    void expandPath();

    /// Converts the path into a canonical form.
    void canonizePath();

    /// Replace backslashes as used on windows with slashes.
    void fixSlashes();

    /// Tries to eliminate occurences of /. and <dirname>/..  and // parts in the path
    void pack();

    /// Adds quotes around the path if none are present and it contains spaces.
    void quote();

    /** Makes this filepath relative to the dirname of an other filename.
        For example if this is c:/foo/bar/file.jpg and the target is set to
        c:/foo/bla/ the result is ../bar/file.jpg .
        If for example this is c:/foo/bar/file.jpg and the target is set to
        c:/foo/bla the result is ./bar/file.jpg since the targets dirname is
        c:/foo/ .
    */
    void makeRelativeTo( McFilename & inTargetFile );

    /** Append a new directory level or filename to the filepath.
        The function will check whether the current filepath is a directory and
        append a new filename/directory separated by the path separator. In order
        to allow for constructs like that McFilename("dir").appendFile("file").unlink();
        the reference to the new filename is returned.
    */
    McFilename& appendFile( McString file );

    /// Returns time of last data modification.
    time_t getModTime() const;

    /// Returns time of last access.
    time_t getAccessTime() const;

    /** \brief Return the file of the size. -1 in case of error.
      */
    mcint64 fileSize () const;

    /// Remove extension from file name
    void removeExtension();
};

#endif

/// @}

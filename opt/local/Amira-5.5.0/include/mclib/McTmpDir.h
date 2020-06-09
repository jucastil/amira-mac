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
#ifndef MC_TMPDIR_H
#define MC_TMPDIR_H

#include "McWinDLLApi.h"
#include "McString.h"

/// Creates and removes a temporary directory.

class MCLIB_API McTmpDir : public McString
{
  public:
    /** Constructor. @c base specifies the beginning of the directory name. If
        base is not an absolute path, the system tmp directory will be used.
        The constructor calls makeUnique() in order to create a unique directory
        name. The directory will not be created automatically unless create is
        true. You need to explicitely call create() otherwise. The directory
        will not be removed automatically when the object is deleted, unless
        autoRemove is true or setAutoRemove() was called. */
    McTmpDir(const char* base = "tmp", bool create=false, bool autoRemove=false);

    /** Destructor. The destructor removes the directory and all files in it
        if setAutoRemove() was set. On default, auto remove is off. */
    ~McTmpDir();

    /// Returns absolute path of system tmp directory
    static const char* getSystemTmpPath();

    /// Creates a unique directory name.
    void makeUnique(const char* base=0);

    /// Check if the directory does exist (and is a directory).
    int doesExist() const;

    /// Create directory with given permissions.
    int create(int mode = 0775);

    /// Remove directory and all files in it.
    int remove();

    /** Enables or disables auto removeal. If auto removeal is on the directory
        and all files in it will be automatically removed if the object is
        deleted. On default, auto removal is off. */
    void setAutoRemove(bool enable) { _autoRemove=enable; }

    /// Returns true if auto removal is on.
    bool autoRemove() const { return _autoRemove; }

    /** Returns the absolute path of the temporary directory. The subdirectories
        of the path are separated by '/' characters on all platforms. The last
        character of the path name is also a '/'. */
    char* str() const { return data; }

    /// Assignment operator.
    McTmpDir& operator= (const char* str) {
        McString::operator=(str);
        return *this;
    }

  protected:
    bool _autoRemove;
};

#endif

/// @}

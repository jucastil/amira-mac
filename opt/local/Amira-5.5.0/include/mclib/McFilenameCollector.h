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
#ifndef MCFILENAMECOLLECTOR_H
#define MCFILENAMECOLLECTOR_H

#include "McWinDLLApi.h"
#include "McFilename.h"


/** This class implements a utility method that gathers files
    of a certain name or extension (or of any other given type)
    starting from a given directory and recursively searching
    all subdirectories. In future extensions search should be
    restricted to local file systems, avoiding time consuming
    directory parsing, as well as loop checking when following
    directory links.
*/

class MCLIB_API McFilenameCollector
{
  public:

    /// Default constructor
    McFilenameCollector () {}

    /// Assignment of directory to start search with
    void setStartDir (const char * name) { _directory = name; }

    /// Assignment of directory to start search with
    void setStartDir (const McString & name) { _directory = name; }

    /// Assignment of directory to start search with
    void setStartDir (const McFilename & name) { _directory = name; }

    /// Assignment of a file name including extension
    void setFileName (const char * name) { _file = name; }

    /// Assignment of a file name including extension
    void setFileName (const McString & name) { _file = name; }

    /// Assignment of a file name including extension
    void setFileName (const McFilename & name) { _file = name; }

    /** Searches for a file name, that has been set using
        McFilenameCollector::setFileName, starting from a
        directory, specified with McFilenameCollector::setStartDir.
        Matching file names are appended to the given array @c fileNames.*/
    void collect (McDArray<McString> & fileNames) {
        this->collect(fileNames, _file.getString(), _directory.getString());
    }

    /** static version of McFilenameCollector::collect, that can be used
        for one shot searches of a given @c file name starting from a
        given @c directory. The file names that match the given one are
        appended to the given array @c fileNames.*/
    static void collect (McDArray<McString> & fileNames,
                         const char * file,
                         const char * directory);

  private:

    McString  _directory;
    McString  _file;
};

#endif

/// @}

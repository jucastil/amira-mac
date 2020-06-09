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

/// @addtogroup hxrawio hxrawio
/// @{
#ifndef READ_RAW_H
#define READ_RAW_H

#include "HxRawIOWinDLLApi.h"

class HxLattice3;
class McString;
class McPrimType;

/** Read binary data and returns an appropriate field instance
 This method expects to get a command line of the following form:
 <tt>filename {filenames} endian fastest primType nDataVar dimX dimY dimZ bb[0] ... bb[5]</tt>
 In total at least 14 arguments have to be present. There are two additional arguments available
 which are a <tt>header</tt> and a <tt>nowarning</tt> command that take int values as arguments.
 If the nowarning argument is set to 1 messages that are produced because not all data could be read
 in are suppressed.

 The allowed values of @c primType are "byte", "short", "int", "float", and "double".
 The allowed values of @c endian are "little", "big" or anything other to request via dialog.
 The allowed values of @c fastest are "xfastest", "zfastest" or anything other to request via dialog.
 The other arguments are expected to contain valid integer or
 floating point numbers in ascii format.

 Alternatively, only a single argument @c filename may be specified.
 In this case the user is asked to enter the missing arguments
 in a dialog box.
 */
HXRAWIO_API int readRawData( int n, const char** argv );

/** The same as readRawData but this returns an unregistered lattice.
    This function is called also by readRawData();
*/
HXRAWIO_API HxLattice3* readRawDataLattice( int n, const char** argv, McString * loadCommand = 0 );

/** Completly the same as readRawDataLattice(int, const char**, McString*), but without parsing of argv.
    This function is used by the other functions.
*/
HXRAWIO_API HxLattice3* readRawDataLattice(
    const char** filenames,
    const int numFiles,
    McPrimType primType,
    int* dims,
    float* boundingBox,
    int isBigEndian = 1,
    int isXFastest = 1,
    int nDataVar = 1,
    long headerBytes = 0,
    int contentTypeFlag = 0,
    int reverse = 0,
    int nowarning = 0,
    McString* loadCommand = 0
);

#endif

/// @}

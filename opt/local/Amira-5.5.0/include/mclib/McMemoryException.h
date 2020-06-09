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
#ifndef MC_MEMORYEXCEPTION_H
#define MC_MEMORYEXCEPTION_H

#include "McException.h"

/** Base class for malloc related exceptions. This exception
    indicates that some attempt to allocate memory has failed.
    It is thrown by the methods mcmalloc() and mcrealloc()
    defined in McMalloc.h.

    Memory exception should be handled by the user whenever
    possible. In order to pop up a message box indicating that
    not enough memory could be allocated you may use the
    following code:

    @code
    #include <hxcore/HxMessage.h>

    try {
        ...
    } catch (McMemoryException& e) {
        theMsg->memError(e.getNumBytes());
    }
    @endcode
*/
class MCLIB_API McMemoryException : public McException
{
  public:
    /** Default constructor. This constructor might be used
        if it is not known how many bytes should be allocated.
        When using this constructor the error message obtained
        by what() will be "Could not allocate enough memory." */
    McMemoryException();

    /** Constructor taking the number of bytes which could not
        be allocated. When using this constructor the error
        message obtained by what() will be "Could not allocate
        <num> bytes." */
    McMemoryException(mcuint64 nbytes);

    /// Destructor.
    virtual ~McMemoryException();

    /// Returns the number of bytes which could not be allocated.
    mcuint64 getNumBytes() const { return nbytes; }

  protected:
    mcuint64 nbytes;
};

#endif

/// @}

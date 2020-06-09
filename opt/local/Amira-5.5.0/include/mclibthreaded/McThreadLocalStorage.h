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

/// @addtogroup mclibthreaded mclibthreaded
/// @{
#ifndef _MC_THREAD_STORAGE_H
#define _MC_THREAD_STORAGE_H

#include "McLibThreadedWinDLLApi.h"


class McThreadLocalStorageBasePrivate;


typedef void ( * PDESTRUCTORFUNCTION) (void * INPTR);

/// Helper class for McThreadLocalStorage
class MCLIBTHREADED_API McThreadLocalStorageBase
{
public:
    McThreadLocalStorageBase();
    McThreadLocalStorageBase( PDESTRUCTORFUNCTION inFuncPtr );
    ~McThreadLocalStorageBase();
    void * get() const;
    void set( void * inPtr );

private:

    McThreadLocalStorageBasePrivate * d;
};



/** Class providing per-thread data storage. This class stores
pointers to the template argument type. For each thread in an 
application a specific pointer can be stored using set(). 
It can be read using get(). */
template <class T>
class McThreadLocalStorage : public McThreadLocalStorageBase
{
public:

    /// Constructor.
    McThreadLocalStorage(){}

    /** Constructor.
    The inFuncPtr argument, if not NULL, specifies a destructor function. 
    When a thread terminates inFuncPtr is called with arguments the value 
    associated with this ThreadStorage in that thread. The inFuncPtr 
    is not called if that value is NULL. The order in which destructor 
    functions are called at thread termination time is unspecified. */
    McThreadLocalStorage( PDESTRUCTORFUNCTION inFuncPtr ) : McThreadLocalStorageBase(inFuncPtr){}

    /// Destructor.
    ~McThreadLocalStorage(){}

    /** Returns the local data pointer associated with the calling thread.
    If no local data pointer has been set for this thread, NULL is
    returned. */
    T * get() const
    {
        return (T*)(McThreadLocalStorageBase::get());
    }

    /** Sets a local data pointer for a the current thread. If there was
    already a local data pointer set, the old pointer will be
    overridden but the object the pointer pointed to will not be
    deleted. */
    void set( T * inPtr )
    {
        McThreadLocalStorageBase::set((T*)inPtr);
    }
};


#endif // _MC_THREAD_STORAGE_H

/// @}

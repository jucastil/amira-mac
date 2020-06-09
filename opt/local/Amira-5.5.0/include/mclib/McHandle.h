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
#ifndef MC_HANDLE_H
#define MC_HANDLE_H

#include "McWinDLLApi.h"

/// Implements smart pointers to McHandables.

template <class T>
class McHandle
{
public:
    /// Default constructor.
    McHandle() : pointer(0) { }

    /// Copy constructor.
    McHandle(const McHandle<T>& handle) : pointer(handle.pointer) {
        if (pointer)
            pointer->ref();
    }

    /// Construct from C++ pointer.
    McHandle(T* pIn) : pointer(pIn) {
        if (pointer)
            pointer->ref();
    }

    template<class Y>
    McHandle(const McHandle<Y>& handle) : pointer(handle.ptr()) {
        if (pointer)
            pointer->ref();
    }

    /// Destructor.
    ~McHandle() {
        if (pointer) {
            T* pToUnref = pointer;
            pointer = 0;
            pToUnref->unref();
        }
    }

    /// Assign another @c McHandle.
    McHandle<T>& operator=(const McHandle<T>& handle) {
        T* pBak = pointer;
        pointer = handle.pointer;
        if (pointer)
            pointer->ref();
        if (pBak)
            pBak->unref();
        return *this;
    }

    /// Assign to another @c McHandle if the types are assignable (from derived to base classes).
    template<class Y>
    McHandle<T>& operator=(const McHandle<Y>& handle) {
        (*this)=handle.ptr();
        return *this;
    }

    /// Assign ordinary C pointer.
    McHandle<T>& operator=(T* pIn) {
        T* pBak = pointer;
        pointer = pIn;
        if (pointer)
            pointer->ref();
        if (pBak)
            pBak->unref();
        return *this;
    }

    /// Cast to C pointer.
    operator T*() const { return pointer; }

    /// Dereference pointer.
    T& operator*() const { return *pointer; }

    /// Cast to C pointer.
    T* operator->() const { return pointer; }

    /// Cast to C pointer.
    T* ptr() const { return pointer; }

private:
    T* pointer;
};

#endif

/// @}

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

/// @addtogroup hxlatticex hxlatticex
/// @{
#ifndef HX_LATTICE_HANDLE_H
#define HX_LATTICE_HANDLE_H

#include "HxLatticeXWinDLLApi.h"
#include <string.h>
class McMemorySelection;
class McDataSpace;

/** \brief The HxLatticeHandle provides a simple and
    efficient way to get read access to a HxLattice.
    
    Use lockReadable() to get access to the physical memory. The returned
    McMemorySelection describes the layout of the requested block.
    By handling requests in this way the implementation has the 
    freedom to implement caching.  The block is stored in Amira data order (==
    Fortran array order, dim[0] == x runs fastest).

    Call unlock() as soon as possible after you no longer
    need the memory.

    Use release() when you no longer need this HxLatticeHandle.
  
    When using a HxLatticeHandle all the memory handling is done
    by the implementation which is free to do it in an optimal way.

    For lattices stored completely in internal memory
    you probably directly get a datapointer to 
    their memory. No copying is performed.
    
    For lattices stored in external memory buffers are allocated. 
    These might be cached to optimize performance.

    If you need write access you have to use the HxMutableLatticeHandle.
    You should only use it if you really need to write because
    it might cause runtime penalties.
  */
class HXLATTICEX_API HxLatticeHandle {
    public:
        virtual ~HxLatticeHandle ();

        /** \brief Get the physical memory of the selection passed as an argument. 
                    Call unlock() as soon as possible to release the lock.
                    The dataset numbering is as requested in the getHandle call.
          */
        virtual const McMemorySelection* lockReadable (const McDataSpace& selection) = 0;

        /** You MUST call this method if you no longer
            need the block of memory allowing the data object
            to do some cleanup.
            Accessing the data after a call to unlock() is not allowed.

            The default is to do nothing.
          */
        virtual void unlock ();

        /** You MUST call this method if you no longer need the Handle.
            The handle will be invalid after this call and MUST NOT
            be used any further.

            The default is to delete the Handle (delete this).
          */
        virtual void release ();
};

class HXLATTICEX_API HxNonBlockingLatticeHandle : public HxLatticeHandle {
    public:
        /** \brief Nonblocking version of lockReadable.

            \return 0 If I/O would be triggered.
          */
        virtual const McMemorySelection* trylockReadable (const McDataSpace& selection) = 0;

};

#endif

/// @}

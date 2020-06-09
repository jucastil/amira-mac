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

/// @addtogroup hxlatticexbase hxlatticexbase
/// @{
#ifndef MC_DATASPACE_CACHE_H
#define MC_DATASPACE_CACHE_H

#include "HxLatticeXBaseWinDLLApi.h"
#include <mclib/McDataSpace.h>
#include <mclib/McDArray.h>

/** A class to help in caching selections of a McDataSpace.
  */
class HXLATTICEXBASE_API McDataSpaceCache {
    public:
        /** Initializes a cache for the dataspace space.
            If the memory used by the cache exceeds maxelements * elemSize, old entries are
            deleted in LRU order.
          */
        McDataSpaceCache (const McDataSpace& space, mclong maxelements);
        
        ~McDataSpaceCache ();

        /** Returns a selection to the hyperslab selected in sel.
           
            \note Not more than 10 locks at the same time are supported.
                This will be changed in the future.

            \returns
                - 0 if sel is not in the cache.
                - A pointer to a selection if successful. It must be
                    released by a call to unlockSelection.
         */
        McMemorySelection* lockSelection (const McDataSpace& sel, bool dirtyallowed = false); 

        /** Return if sel is contained in the cache.
          */
        int isCached (const McDataSpace& sel); 
        
        /** Unlock the memory used by this selection. 
            The cache is free to remove the element which
            provided this selection.

          */
        void unlockSelection (const McMemorySelection* sel);

        /** Insert a block of memory into the cache.
            The cache will take over memory management. Blocks must
            have been allocated by mcmalloc.
          */
        void insert (const McDataSpace& sel, const McMemorySelection& mem, bool dirty = false);

        /** Invalidate all entries.

          */
        void invalidate ();
    private:
        mclong mymaxelements;
        mclong numelems; 

        enum {
            MAX_LOCKS = 10
        };
        McMemorySelection lockedSels [MAX_LOCKS];
        int lockedElementId [MAX_LOCKS];

        int now;

        struct CacheElement {
            CacheElement () {
                id = -1;
                lastUsed = -1;
                refs = 0;
                dirty = 0;
            }
            
            int id;
            int lastUsed;
            int refs;
            int dirty;

            McDataSpace space;
            McMemorySelection mem;
        };

        McDArray<CacheElement> cache;

        void makeRoomFor (mclong elements); 
};

#endif /* MC_DATASPACE_CACHE_H */

/// @}

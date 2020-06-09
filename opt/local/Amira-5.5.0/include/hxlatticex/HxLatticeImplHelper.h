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
#ifndef HX_LATTICE_IMPL_HELPER_H
#define HX_LATTICE_IMPL_HELPER_H

#include "HxLatticeXWinDLLApi.h"
#include "HxLattice.h"
#include <mclib/McSmallArray.h>

class HxData;
class HxLatticeDefaultGetQueue;

/** You might use this default implementation.
    It caches the result and recalculates only
    if the touchtime changes.
    You might use it in an interface implementation 
    or in the dataclass.
\code
private:
    HxLattice::DefaultComputeRange computeRange;

public:
    HxLatticeImpl () :
        computeRange (*this) {
        };

    void getRange (int dataset, float& min, float& max) {
        computeRange.getRange (dataset, min, max);
    }
\endcode
*/
class HXLATTICEX_API HxLattice::DefaultComputeRange {
    public:
        /** Use to directly provide a HxLattice.
         *  The HxLattice will be asked for its owner
         *  if needed.
         */
        DefaultComputeRange (HxLattice* lat);
        /** Use this if you have an data object.
         *  The data object will be asked to provide a HxLattice 
         *  if needed.
         */ 
        DefaultComputeRange (HxData* lat);

        /** Compute the range by scanning over all data. 
            \todo: set is restricted to 0 -> extend to 0 <= set < 10
         */
        void getRange (int set, float& min, float& max);

        /** Return the range if already available.
            Don't start a calculation which would block.
         */
        int trygetRange (int set, float& min, float& max);
    private:
        bool needscalc (int set);

        float mymin;
        float mymax;
        int touchtime;
        bool isValid;
        HxLattice* mylattice;
        HxData* myobj;
};

/** You might use this default implementation for queue handling.
  It returns nonthreaded HxLatticeDefaultGetQueues and handles them in a pool. Use it
\code
private:
   HxLattice::DefaultGetQueueHandler handleQueues;

public:
    HxLatticeImpl () :
        handleQueues (*this) {
        };

    HxLatticeGetQueue* getQueue (int datasetcount, const int* datasets) {
        return handleQueues.getQueue (int datasetcount, const int* datasets);
    }
\endcode
*/
class HXLATTICEX_API HxLattice::DefaultGetQueueHandler {
    public:
        DefaultGetQueueHandler (HxLattice* lat);

        ~DefaultGetQueueHandler ();

        HxLatticeGetQueue* getQueue (int datasetcount, const int* datasetidxs);
    private:            
        McDArray<HxLatticeDefaultGetQueue*> mQueues;

        HxLattice* mLat;
};

/** This is a default implementation which might
 *  be used to implement the valueOfSet method.
 *
 *  It allocates small local caches. 
 */
class HXLATTICEX_API HxLattice::DefaultValueHandler {
    public:
        DefaultValueHandler (HxLattice* lat);

        /** Use this if you have an data object.
         *  The data object will be asked to provide a HxLattice 
         *  if needed.
         */ 
        DefaultValueHandler (HxData* lat);

        ~DefaultValueHandler ();

        void valueOfSet (void* res, int datasetidx, const int* pos);
    private:
        void cleanCache ();
        void initCache (int size);

        class CacheEntry;

        int touchtime;
        McSmallArray<CacheEntry*, 5> cache;

        HxLattice* mylat;
        HxData* myobj;
};

#endif

/// @}

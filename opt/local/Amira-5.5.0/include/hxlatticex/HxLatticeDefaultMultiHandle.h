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
#ifndef HX_LATTICE_DEFAULT_HANDLE
#define HX_LATTICE_DEFAULT_HANDLE

#include "HxLatticeXWinDLLApi.h"
#include "HxMutableLatticeHandle.h" 
#include <mclib/McDArray.h>
#include <mclib/McDataSpace.h>
class McDataSpace;

/** This is a convenience class which can be used
    to implement a handle on more than one dataset
    at the same time. 

    You have to implement handles to a single
    dataset and to the coordinates. If more
    than one dataset is requested at the same
    time you could wrap them with this class.
    You might use it as a HxLatticeHandle or
    as a HxMutableLatticeHandle. 
    
    Use it similar to:
\code
HxLatticeHandle* myImpl::getHandle (int datasetcount, const int* datasets) {
    // if we are asked for a handle with more than 1 datasets
    // we create a DefaultMultiHandle to bundle them
    // if we only return 1 handle this is not needed.
    HxLatticeDefaultMultiHandle* handle = 0;
    HxLatticeHandle* subhandle = 0;
    if (datasetcount > 1) {
        handle = new HxLatticeDefaultMultiHandle;
    }
    for (int i = 0; i < datasetcount; i++) {
        switch (datasets[i]) {
            case HxLattice::DATASET_POSITION_XYZ:
            case HxLattice::DATASET_COORD_XYZT:
            case HxLattice::DATASET_TIME:
                {
                    SpecialDataSet format = SpecialDataSet (datasets[i]);
                    subhandle = new HxCoord4HandleImpl (format, obj ());
                }
                break;
            default:
                {
                    subhandle = new HxLattice3ToMutableLatticeDataHandleImpl (&(obj()->getChannel (datasets[i])->lattice));
                }
        }
        if (handle) {
            handle->addSubHandle (subhandle);
        }
    }
    if (handle) {
        return handle;
    } else {
        return subhandle;
    }
}

HxMutableLatticeHandle* myImpl::getMutableHandle (int datasetcount, const int* datasets) {
    HxLatticeDefaultMultiHandle* handle = 0;
    HxMutableLatticeHandle* subhandle = 0;
    if (datasetcount > 1) {
        handle = new HxLatticeDefaultMultiHandle;
    }
    for (int i = 0; i < datasetcount; i++) {
        // special datasets are not allowed
        mcrequire (datasets[i] >= 0);
        subhandle = new HxLattice3ToMutableLatticeDataHandleImpl (&(obj()->getChannel (datasets[i])->lattice));
        if (handle) {
            handle->addSubHandle (subhandle);
        }
    }
    if (handle) {
        return handle;
    } else {
        return subhandle;
    }
}
\endcode
 
 */
class HXLATTICEX_API HxLatticeDefaultMultiHandle : public HxMutableLatticeHandle {
    public:
        ///
        HxLatticeDefaultMultiHandle ();

        ///
        virtual ~HxLatticeDefaultMultiHandle ();

        /** Add a handle to the set of used handles.
         *  If you're going to use the HxLatticeDefaultMultiHandle as
         *  a HxMutableLatticeHandle you MUST only provides
         *  handles of type HxMutalbleLatticeHandle.
         *  Otherwise you'll get runtime errors.
         */
        void addSubHandle (HxLatticeHandle* handle);

        /** Lock all subhandles.
         */ 
        virtual const McMemorySelection* lockReadable (const McDataSpace& selection);

        /** Lock all subhandles.
         */ 
        virtual const McMemorySelection* lockWritable (const McDataSpace& selection);

        /** Unlock all subhandles.
         */ 
        virtual void unlock ();

        /** Unlock all subhandles and delete this.
         */ 
        virtual void release ();
    private:
        McDArray<HxLatticeHandle*> handles;
        McDArray<McMemorySelection> selections;
};


/** same for non blocking handle */
class HXLATTICEX_API HxNonBlockingLatticeDefaultMultiHandle : public HxNonBlockingLatticeHandle {
    public:
        ///
        HxNonBlockingLatticeDefaultMultiHandle ();

        ///
        virtual ~HxNonBlockingLatticeDefaultMultiHandle ();

        /** Add a handle to the set of used handles.
         *  If you're going to use the HxNonBlockingLatticeDefaultMultiHandle as
         *  a HxMutableLatticeHandle you MUST only provides
         *  handles of type HxMutalbleLatticeHandle.
         *  Otherwise you'll get runtime errors.
         */
        void addSubHandle (HxNonBlockingLatticeHandle* handle);

        /** Lock all subhandles.
         */ 
        virtual const McMemorySelection* lockReadable (const McDataSpace& selection);

        /** try lock all subhandles.
         */ 
        virtual const McMemorySelection* trylockReadable (const McDataSpace& selection);

        /** Unlock all subhandles.
         */ 
        virtual void unlock ();

        /** Unlock all subhandles and delete this.
         */ 
        virtual void release ();
    private:
        McDArray<HxNonBlockingLatticeHandle*> handles;
        McDArray<McMemorySelection> selections;
};
#endif

/// @}

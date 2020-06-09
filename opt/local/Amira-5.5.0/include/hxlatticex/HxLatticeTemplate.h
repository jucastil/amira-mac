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
#ifndef HX_LATTICE_TEMPLATE_H
#define HX_LATTICE_TEMPLATE_H

#include "HxLattice.h"
/** \brief A template class to ease the construction of HxLattice interfaces.
 
 *  The implementation class OWNER which is derived from HxObject has to provide a minimal set
 *  of methods to override all pure virtual methods of HxLattice. 
 *
 *  Additionally you have to provide a method validInterface () which
 *  checks if an instance of any interface is valid with this
 *  object. It is used by this template class to implement HxInterface::isValid
 *
 *  After definition you can instantiate this template with:
 *  \code
HX_INIT_TEMPLATE_CLASS (HxLatticeOwnerTemplate<OWNER>, HxLattice);
 *  \endcode 
 *
 *  \todo How to override non pure virtual methods?
 *
 *  An incomplete example:
 *  \code
// in header file
template <class IMPL> class HxLatticeOwnerTemplate;

class HXHDF5LATTICE_API HxExternalHDF5Lattice : public HxSpatialData {
        ...
     public:
        /// 
        const int* dims4 () const {
            return theDims;
        };
        ...
        int validInterface (HxDynamicInterface* iface);
        ...
};

// in source file
 ...

MC_INIT_TEMPLATE_CLASS (HxLatticeOwnerTemplate<HxExternalHDF5Lattice>, HxLattice);

void HxExternalHDF5Lattice::createInterfaces () {
    addInterface (HxLatticeOwnerTemplate<HxExternalHDF5Lattice>::getClassTypeId ()); 
    HxSpatialData::createInterfaces ();
}

int HxExternalF5Lattice::validInterface (HxDynamicInterface* iface) {
    if (iface->isOfType (HxMutableLatticeOwnerTemplate<HxExternalF5Lattice>::getClassTypeId ())) {
        if (PRIVATE(readonly) != 0) {
            return 0;
        }
    } else if (iface->isOfType (HxLatticeOwnerTemplate<HxExternalF5Lattice>::getClassTypeId ())) {
        if (PRIVATE(readonly) != 1) {
            return 0;
        }
    } else if (...) {
        ...
    } else {
        // shouldn't be called
        fprintf (stderr, "Internal error: HxExternalF5Lattice::validInterface () called with wrong type\n");
    }
    return 1;
}

 *  \endcode
 */

template <class PROXY>
class HxLatticeProxyTemplate : public HxLattice {
    MC_ABSTRACT_TEMPLATE_HEADER (HxLatticeProxyTemplate<PROXY>);

    public:
        HxLatticeProxyTemplate (McInterfaceOwner* owner, PROXY* p) 
                : HxLattice (owner) 
                , mProxy (p) {}

        HxLatticeProxyTemplate (McInterface* iface, PROXY* p) 
                : HxLattice (static_cast<McInterfaceOwner*>(iface->getInterface (McInterfaceOwner::getClassTypeId()))) 
                , mProxy (p) {}

    private:
        int doGetNDataSets () {
            return mProxy->nDataSets ();
        }

        const char* doGetNameOfSet (int datasetidx) {
            return mProxy->getNameOfSet (datasetidx);
        }

        int doGetNDataVarOfSet (int dataset) {
            return mProxy->nDataVarOfSet (dataset);
        }

        McDataType doGetDataTypeOfSet (int dataset) {
            return mProxy->dataTypeOfSet (dataset);
        }
        
        void doGetRangeOfSet (int dataset, float& min, float& max) {
            mProxy->getRangeOfSet (dataset, min, max);
        }

        McDataSpace doGetDataSpace () {
            return mProxy->getDataSpace ();
        }

        McBoundingBox doGetBoundingBox (const McDataSpace* dataspace) {
            return mProxy->getBoundingBox (dataspace);
        }

        HxLatticeType doGetLatticeType () {
            return mProxy->latticeType ();
        }

        HxLatticeHandle* doGetHandle (int datasetcount, const int* datasets) { 
            return mProxy->getHandle (datasetcount, datasets);
        }

        void doGetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) {
            mProxy->getDataOfSet (srcdatasetidx, srcspace, destmem);
        }

        void doGetValueOfSet (void* result, int set, const int* indices) {
            mProxy->valueOfSet (result, set, indices);
        }

    protected:
        /// .
        PROXY* mProxy;
};

template <class PROXY>
class HxNonBlockingLatticeProxyTemplate : public HxNonBlockingLattice {
    MC_ABSTRACT_TEMPLATE_HEADER (HxNonBlockingLatticeProxyTemplate<PROXY>);

    public:
        HxNonBlockingLatticeProxyTemplate (McInterfaceOwner* owner, PROXY* p) 
                : HxNonBlockingLattice (owner) 
                , mProxy (p) {}

        HxNonBlockingLatticeProxyTemplate (McInterface* iface, PROXY* p) 
                : HxNonBlockingLattice (static_cast<McInterfaceOwner*>(iface->getInterface (McInterfaceOwner::getClassTypeId()))) 
                , mProxy (p) {}

    private:
        int doGetNDataSets () {
            return mProxy->nDataSets ();
        }

        const char* doGetNameOfSet (int datasetidx) {
            return mProxy->getNameOfSet (datasetidx);
        }

        int doGetNDataVarOfSet (int dataset) {
            return mProxy->nDataVarOfSet (dataset);
        }

        McDataType doGetDataTypeOfSet (int dataset) {
            return mProxy->dataTypeOfSet (dataset);
        }
        
        int doTrygetRangeOfSet (int datasetidx, float& min, float& max) {
            return mProxy->trygetRangeOfSet (datasetidx, min, max);
        } 
        
        McDataSpace doGetDataSpace () {
            return mProxy->getDataSpace ();
        }

        McBoundingBox doGetBoundingBox (const McDataSpace* dataspace) {
            return mProxy->getBoundingBox (dataspace);
        }

        HxLatticeType doGetLatticeType () {
            return mProxy->latticeType ();
        }

        HxNonBlockingLatticeHandle* doGetHandle (int datasetcount, const int* datasets) { 
            return mProxy->getHandle (datasetcount, datasets);
        }

        HxLatticeGetQueue* doGetQueue (int datasetcount, const int* datasets) {
            return mProxy->getQueue (datasetcount, datasets);
        }

        int doTrygetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) {
            return mProxy->trygetDataOfSet (srcdatasetidx, srcspace, destmem);
        }

    protected:
        /// .
        PROXY* mProxy;
};

#endif

/// @}

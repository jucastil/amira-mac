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
#ifndef HX_MUTABLE_LATTICE_TEMPLATE_H
#define HX_MUTABLE_LATTICE_TEMPLATE_H

#include "HxMutableLattice.h"

template <class PROXY>
class HxMutableLatticeProxyTemplate : public HxMutableLattice {
    MC_ABSTRACT_TEMPLATE_HEADER (HxMutableLatticeProxyTemplate<PROXY>);
    public:
        HxMutableLatticeProxyTemplate (McInterfaceOwner* owner, PROXY* p) : HxMutableLattice (owner),  proxy(p) {}

        HxMutableLatticeProxyTemplate (McInterface* iface, PROXY* p) 
                : HxMutableLattice (static_cast<McInterfaceOwner*>(iface->getInterface (McInterfaceOwner::getClassTypeId()))) 
                ,  proxy(p) {}

        int doGetNDataSets () {
            return proxy->nDataSets ();
        }

        const char* doGetNameOfSet (int datasetidx) {
            return proxy->getNameOfSet (datasetidx);
        }

        int doGetNDataVarOfSet (int dataset) {
            return proxy->nDataVarOfSet (dataset);
        }

        McDataType doGetDataTypeOfSet (int dataset) {
            return proxy->dataTypeOfSet (dataset);
        }

        int doIsMutableDataSet (int datasetidx) {
            return proxy->isMutableDataSet (datasetidx);
        }
        
        void doGetRangeOfSet (int dataset, float& min, float& max) {
            proxy->getRangeOfSet (dataset, min, max);
        }
        
        int doTrygetRangeOfSet (int datasetidx, float& min, float& max) {
            return proxy->trygetRangeOfSet (datasetidx, min, max);
        } 
        
        McDataSpace doGetDataSpace () {
            return proxy->getDataSpace ();
        }

        McBoundingBox doGetBoundingBox (const McDataSpace* dataspace) {
            return proxy->getBoundingBox (dataspace);
        }

        HxLatticeType doGetLatticeType () {
            return proxy->latticeType ();
        }

        HxLatticeHandle* doGetHandle (int datasetcount, const int* datasets) { 
            return proxy->getHandle (datasetcount, datasets);
        }

        HxMutableLatticeHandle* doGetMutableHandle (int datasetcount, const int* datasets) { 
            return proxy->getMutableHandle (datasetcount, datasets);
        }

        HxLatticeGetQueue* doGetQueue (int datasetcount, const int* datasets) {
            return proxy->getQueue (datasetcount, datasets);
        }

        void doGetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) {
            proxy->getDataOfSet (srcdatasetidx, srcspace, destmem);
        }

        int doTrygetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) {
            return proxy->trygetDataOfSet (srcdatasetidx, srcspace, destmem);
        }

        void doPutDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem) {
            proxy->putDataOfSet (srcdatasetidx, srcspace, destmem);
        }

        void doGetValueOfSet (void* result, int set, const int* indices) {
            proxy->valueOfSet (result, set, indices);
        }

    protected:
        PROXY* proxy;

};
#endif

/// @}

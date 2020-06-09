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

/// @addtogroup hxlatticecompat hxlatticecompat
/// @{
#ifndef HX_LABEL_LATTICE3_TO_MUTABLE_LABEL_LATTICE_IMPL_H
#define HX_LABEL_LATTICE3_TO_MUTABLE_LABEL_LATTICE_IMPL_H

#include "HxLatticeCompatWinDLLApi.h"
#include <hxfield/HxLabelLattice3.h>
#include <hxlatticex/HxLatticeHandle.h>
#include <hxlatticex/HxLatticeGetQueue.h>
#include <hxlatticex/HxLatticeThreadedGetQueue.h>
#include "HxCoord3AsLatticeHandle.h"
#include <hxlatticex/HxLatticeDefaultMultiHandle.h>
#include <hxlatticex/HxMutableLabelLattice.h>


class HXLATTICECOMPAT_API HxLabelLattice3ToMutableLabelLatticeImpl : public HxMutableLabelLattice {
    MC_ABSTRACT_HEADER(HxLabelLattice3ToMutableLabelLatticeImpl);

public:
    HxLabelLattice3ToMutableLabelLatticeImpl (McInterfaceOwner* owner, HxLabelLattice3* l) : HxMutableLabelLattice (owner), lat(l) {}

    enum DataSetIds {
        DS_MAIN = 0,
        DS_POSXYZ = 1
    };
   
private: 
    ~HxLabelLattice3ToMutableLabelLatticeImpl();

    HxParamBundle* doGetMaterials();
    HxLattice* doGetImageVolume();
    void doRelabel(HxParamBundle& newMaterials);
    virtual McDataSpace doGetDataSpace ();
    virtual McBoundingBox doGetBoundingBox (const McDataSpace* dataspace);
    HxLatticeType doGetLatticeType ();
    HxLatticeHandle* doGetHandle(int, const int*);
    void doGetValueOfSet (void* res, int dataset, const int* indices);
    HxMutableLatticeHandle* doGetMutableHandle (int datasetcount, const int* datasets);
    int doGetNDataSets ();
    const char* doGetNameOfSet (int set); 
    int doGetNDataVarOfSet (int set);
    McDataType doGetDataTypeOfSet (int set);
    void doGetRangeOfSet (int set, float& min, float& max);
    void doGetDataOfSet (int srcdatasetidx, const McDataSpace& srcspace, const McMemorySelection& destmem);
    void doPutDataOfSet (int datasetidx, const McDataSpace& space, const McMemorySelection& memspace); 

private:
    HxLabelLattice3* lat;   // The LabelLattice3 for which this class provides an interface
    McDArray<HxLatticeThreadedGetQueue*> queues;
};


#endif

/// @}

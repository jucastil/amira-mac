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

/// @addtogroup hxlatticexviz hxlatticexviz
/// @{
#ifndef HX_LATTICE_ORTHO_SLICE_H
#define HX_LATTICE_ORTHO_SLICE_H

#include "HxLatticeXVizWinDLLApi.h"
#include <hxlattice/HxOrthoSlice.h>

class HxLatticeGetQueue;
class HxLattice;
class HxNonBlockingLattice;

/** Orthoslice using HxLattice to synchronously access data.

    The derived version HxNonBlockingLatticeOrthoSlice provides
    asynchronous access and progressive updates of the display.
    It accesses data through HxNonBlockingLattice.
    Besides this, the class is not designed to be a base class.

    \todo review/refactor/cleanup HxLatticeOrthoSlice and HxNonBlockingLatticeOrthoslice.
            Remove unclear dependencies in doCheckNewVolume/doInvalidateVolume.
            Perhaps a common base class would be more appropriate.

    You MUST NOT derive from this class. See HxOrthoSliceBase instead.
  */
class HXLATTICEXVIZ_API HxLatticeOrthoSlice : public HxOrthoSliceBase {
        MC_HEADER(HxLatticeOrthoSlice);
    public:
        HxLatticeOrthoSlice();

        HxLatticeOrthoSlice(const McTypeInfo*);
    private:

        virtual void update();
        
        int mDims[3];
        HxLattice*         latticeX;          

        /* template callbacks from HxOrthoSliceBase */
        virtual void doGetDataAndUpdateTexture();
        virtual void doGetBoundingBoxOfVolume (float* bbox);
        virtual const int* doGetDims();
        virtual void doInvalidateVolume();
        virtual void doGetSliceTexture (unsigned char* tex, int i, int j, int* idx, int *size, TransparencyOption& transMode, const void* childData);
        virtual bool doMakeMesh(int factor[2], int size[3]);
        /* end template callbacks from HxOrthoSliceBase */

    protected:
        virtual HxData* doCheckNewVolume (HxData* dat);
        void mapLinearFromMemSel(const McMemorySelection* memsel, unsigned char* value, int i, int j, int idx[3], int x);
        void copyFromMemSel(const McMemorySelection* memsel, unsigned char* value, int i, int j, int idx[3], int x);
        void mapColorFromMemSel(const McMemorySelection* memsel, unsigned char* value, int i, int j, int idx[3], int x, bool alpha);
};


/** Orthoslice using asynchronous data access through HxNonBlockingLattice.

    You MUST NOT derive from this class. See HxOrthoSliceBase instead.
  */
class HXLATTICEXVIZ_API HxNonBlockingLatticeOrthoSlice : public HxLatticeOrthoSlice {
        MC_HEADER(HxNonBlockingLatticeOrthoSlice);
    public:
        HxNonBlockingLatticeOrthoSlice();
    private:
        ~HxNonBlockingLatticeOrthoSlice();

        HxNonBlockingLattice*         latticeNB;          
        HxLatticeGetQueue* queue;
        int downsampling;

        static void queueNotification (HxLatticeGetQueue* queue, void* data);

        /* template callbacks from HxOrthoSliceBase */
        virtual void doGetDataAndUpdateTexture();
        virtual HxData* doCheckNewVolume (HxData* dat);
        virtual void doInvalidateVolume();
        /* end template callbacks from HxOrthoSliceBase */
};

#endif

/// @}

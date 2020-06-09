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

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef SP_DISTANCE_MAP_H
#define SP_DISTANCE_MAP_H

#ifndef NULL
    #define NULL 0
#endif

#include <hxdistmap/HxNeighborIndexing3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McPackedIndexing.h>
#include "HxSkeletonWinDLLApi.h"

enum SpDistanceRoot {
    TO_OBJECT_BOUNDARY,
    TO_BACKGROUND
};

class McProgressInterface;

class HXSKELETON_API SpDistanceMap
{
  public:

    /** Construct the object in which all the distance maps
     *  will be calculated.
     *
     *  If dat is not zero it must point to a voxel representation
     *  of the object, i.e. an array of size dims[0] * dims[1] * dims[2].
     *
     *  If dat is zero you must call useData to provide the voxel
     *  representation block by block. Using the block by block
     *  initialization allows SpDistanceMap to pack the data
     *  and process larger object which cover only part of volume
     *  covered by voxels.
     *
     */
    SpDistanceMap (const unsigned char* dat, const int dims[3]
                      , const float voxSize[3], McProgressInterface* p, SpDistanceRoot root);

    SpDistanceMap (const McBitfield& dat, const int dims[3]
                      , const float voxSize[3], McProgressInterface* p, SpDistanceRoot root);

    ~SpDistanceMap ();

    void useData (const unsigned char* dat, mclong count);

    void calcSSDM (int i, int j, int k) {
        calcSSDM (indexing->index1D (i, j, k));
    };
    void calcSSDM (int i);
    float getSSD (int i, int j, int k) {
        return ssdm[packer->index (indexing->index1D (i, j, k))];
    };
    float getSSD (int i) {
        return ssdm[packer->index (i)];
    };
    float *grabSSDM ();

    void clearSSPDM ();
    void calcSSPDM (int i, int j, int k) {
        calcSSPDM (indexing->index1D (i, j, k));
    };
    void calcSSPDM (int i);
    void addLS2SSDM (int numSeeds, int* seeds);
    void addLS2PDM (int numSeeds, int* seeds);
    float getSSPD (int i, int j, int k) {
        return sspdm[packer->index (indexing->index1D (i, j, k))];
    };
    float getSSPD (int i) {
        return sspdm[packer->index (i)];
    };
    float *grabSSPDM ();

    void calcBDM ();
    float getBD (int i, int j, int k) {
        return bdm[packer->index (indexing->index1D (i, j, k))];
    };
    float getBD (int i) {
        return bdm[packer->index (i)];
    };
    float *grabBDM ();

    /** returns the boundary point that propagated to i, j, k
        return value can be mapped to 3D with
        indexing->index3D (ret, bi, bj, bk);
        */
    int getBPoint (int i, int j, int k) {
        return boundaryPoint[packer->index (indexing->index1D (i, j, k))];
    };
    int getBPoint (int i) {
        return boundaryPoint[packer->index (i)];
    };

    void clearTubes ();
    void addTube (int numSeeds, int* seeds, float slope, float zeroVal);
    bool getTube (int i, int j, int k) {
        assert ((int)tubes.nBits () == srcVoxelNum);
        return tubes[packer->index (indexing->index1D (i, j, k))];
    };
    bool getTube (int i) {
        assert ((int)tubes.nBits () == srcVoxelNum);
        return tubes[packer->index (i)];
    };
    float getTubeFillRatio () {
        return float(tubes.nSetBits ()) / float(srcVoxelNum);
    }
    unsigned char* grabTubes ();

    void freeMem ();

    /** special stuff
      */
    McSuperPackedIndexing* getPacker () {
        return packer;
    }

  protected:

    McDArray<int> front;
    HxNeighborIndexing3* indexing;
    McSuperPackedIndexing* packer;
    McDArray<float> ssdm;
    McDArray<float> sspdm;
    McDArray<float> bdm;
    McDArray<int> boundaryPoint;
    McBitfield tubes;
//        const unsigned char* srcDat;
    int srcVoxelNum;
    McVec3f voxSize;
    McProgressInterface* progress;
    float maxBDM;

    const SpDistanceRoot mDistanceRoot;

  private:

    void propagatePDM ();
    void propagateSSDM ();
};

#endif

/// @}

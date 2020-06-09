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
#ifndef MC_DISTANCEMAP_H
#define MC_DISTANCEMAP_H

#include "McDArray.h"
#include "McProgressInterface.h"
#include "McNeighborIterator33.h"
#include "McWatch.h"
#include "Mc64Bit.h"

#include <math.h>

// see also amiraKernelTests/testmclib/TestMcDistanceMap.cpp

namespace McDistanceMap {

    /** Normally this method is not used directly but via one of the
        interface routines.  The template parameters DISTTYPE and
        SRCTYPE are normally pointer types, pointing to the image data
        and distance map data respectively. However it can also
        be other types of arrays providing an index operator.
        For all boundary voxels which belong to the object (src[i]!=0)
        dist[i] is set to mindist[n]. If front != NULL the indices
        of the boundary voxels are appended to the array front.
        If gather!=NULL the indices of all voxels belonging
        to the object are collected in gather as well as their
        border configuration in bordered until maxgather
        pixels are detected.
*/
    template <class DISTTYPE, class DISTVAL, class SRCTYPE, class INDEXTYPE>
    void findBoundaryVoxelsChamferInside(DISTTYPE dist, int ctype, DISTVAL mindist[27],
                                         SRCTYPE src,const int* dims,
                                         McDArray<INDEXTYPE> *front,
                                         McProgressInterface* workArea,
                                         McDArray<INDEXTYPE>* gather = 0,
                                         McDArray<unsigned char>* bordered = 0,
                                         INDEXTYPE maxgather=0)
    {
        McNeighborIterator33 indexing(26,dims);
        INDEXTYPE index=0;
        int i,j,k;
        indexing.setWeights(mindist, 1);

        if (workArea) workArea->startWorking("Detecting boundary");
        for (k=0 ; k<dims[2] ; k++) {
            if (workArea) workArea->setProgressValue((float)k/dims[2]);
            for (j=0 ; j<dims[1] ; j++) {
                unsigned char bordercase = indexing.borderstatus(0,j,k);
                unsigned char borderbase = bordercase & 252;

                for (i=0 ; i<dims[0] ;
                     i++, index++,
                         bordercase = borderbase |
                           (i==dims[0]-1)*McNeighborIterator33::BORDERX2
                         | (i==0)*McNeighborIterator33::BORDERX1) {
                    if (src[index]){ // init inside
                        if (gather) {
                            if (gather->size()==maxgather) {
                                gather->remax(0,0);
                                bordered->remax(0,0);
                                gather=0;
                            } else {
                                gather->append(index);
                                bordered->append(bordercase);
                            }
                        }
                        for (int l=0 ; l<indexing.ctype ; l++) {
                            INDEXTYPE indexn = index + INDEXTYPE (indexing.offsets[l]);
                            // this would cause the out-of-domain voxels
			    // to be beckground -> problem for 2D.
			    // we prefer to not consider them.
			    //if ((bordercase&indexing.bordered[l]) || src[indexn]==0){
			    if ( (!(bordercase&indexing.bordered[l])) && src[indexn]==0){
                                dist[index] = DISTVAL(indexing.fweights[l]);
                                if (front) front->append(index);
                                break;
                            }
                        }
                    } else { // init outside
                        for (int l=0 ; l<indexing.ctype ; l++) {
                            INDEXTYPE indexn = index + INDEXTYPE(indexing.offsets[l]);
                            if (!(bordercase&indexing.bordered[l]) && src[indexn]!=0){
                                dist[index] = DISTVAL(indexing.fweights[l]);
                                if (front) front->append(index);
                                break;
                            }
                        }
                    }// end if src[index]
                }// end for i
            }// end for j
        }// end for k
        if (workArea) workArea->stopWorking();
    }


    /* copy 3x3x3 mask inmask to outmask and set all values not needed in the
    chamfer propagation pass (0..1) to -1 */
    template <class T>
        void prepareChamferPropagationMask(int pass, const T* inmask, T* outmask) {
        memcpy(outmask,inmask,27*sizeof(T));
        if (pass==0) {
            for (int i=14 ; i<27 ; i++) outmask[i]=-1;
        } else {
            for (int i=0 ; i<13 ; i++) outmask[i]=-1;
        }
    }

    /*
    template <class DISTTYPE, class DISTVAL, class SRCTYPE>
    void findBoundaryVoxelsChamfer(DISTTYPE dist, DISTVAL mindist,
                                   SRCTYPE src,const int* dims,
                                   McDArray<int> *front,
                                   McProgressInterface* workArea)
    {
        HxNeighborIndexing3 indexing(dims,N26,W_CHAMFER);
        int nnn = indexing.zyxDim();
        int index,i,j,k;
        int in,jn,kn,indexn;
        float weight;
        int inside;
        if (workArea) workArea->startWorking("Detecting boundary");
        for (index=0; index<nnn; index++){
            if (workArea && (index%10000)==0) {
                if(workArea->wasInterrupted()) break;
                workArea->setProgressValue((float)index/nnn);
            }
            if (src[index]){
                // check all neighbors
                int boundaryMember = 0;
                int nextNumber = 0;
                indexing.index3D(index,i,j,k);
                {
                    while (indexing.nextNeighbor(nextNumber,
                                                 i,j,k,index,
                                                 in,jn,kn,indexn,
                                                 inside,weight)){
                        if (!inside){
                            boundaryMember = 1;
                            break;
                        }
                        if (src[indexn]==0){
                            boundaryMember = 1;
                            break;
                        }
                    }// end while
                    if (boundaryMember){
                        dist[index] = 0;
                        if (front) front->append(index);
                    }
                }// end else
            }// end if src[index]
        }// for index
        if (workArea) workArea->stopWorking();
    }
    */
/*
        static signed char stdchamfermask[27] = {
        5,4,5,
            4,3,4,
            5,4,5,

            4,3,4,
            3,0,3,
            4,3,4,

        5,4,5,
            4,3,4,
            5,4,5,
            };

    static signed char mask1[27] = {
        5,4,5,
            4,3,4,
            5,4,5,

            4,3,4,
            3,0,-1,
            -1,-1,-1,

            -1,-1,-1,
            -1,-1,-1,
            -1,-1,-1
            };

    static signed char mask2[27] = {
        -1,-1,-1,
            -1,-1,-1,
            -1,-1,-1,

            -1,-1,-1,
            -1,0,3,
            4,3,4,

            5,4,5,
            4,3,4,
            5,4,5
            };
*/
    template <class DISTTYPE, class SRCTYPE, class DISTVAL>
    void propagateBSFieldChamferFast(DISTTYPE dist, SRCTYPE src, DISTVAL chamfermask[27],
                                     const int* dims, McProgressInterface* workArea, int insideonly=1)
    {
        int i,j,k;
        int change=0;
        DISTVAL mask1[27], mask2[27];
        prepareChamferPropagationMask(0, chamfermask, mask1);
        prepareChamferPropagationMask(1, chamfermask, mask2);

        if (workArea) workArea->startWorking("Propagating pass 1/2 ...");
        for (k=0 ; k<dims[2] ; k++) {
            if (workArea) workArea->setProgressValue(0.5f*k/dims[2]);
            for (j=0 ; j<dims[1] ; j++) {
                for (i=0 ; i<dims[0] ; i++) {
                    for (int dk=0 ; dk<2 ; dk++) {
                        mclong idx = (mclong(k)*mclong(dims[1])+mclong(j))*mclong(dims[0])+mclong(i);
                        if (insideonly && !src[idx]) continue;
                        DISTVAL &currval = dist[idx];
                        int k1,j1,i1;
                        k1=dk-1+k;
                        if (k1<0 || k1>=dims[2])
                            continue;
                        for (int dj=0 ; dj<3 ; dj++) {
                            j1 = dj-1+j;
                            if (j1<0 || j1>=dims[1])
                                continue;
                            for (int di=0 ; di<3 ; di++) {
                                i1 = i+di-1;
                                DISTVAL m = mask1[dk*9+dj*3+di];
                                if (m<0 || i1<0 || i1>=dims[0])
                                    continue;
                                mclong idx2 = (mclong(k1)*mclong(dims[1])+mclong(j1))*mclong(dims[0])+mclong(i1);
                                if (!insideonly || src[idx2]) {
                                    DISTVAL val = m+dist[idx2];
                                    if (val<currval) {
                                        currval=val;
                                        change++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //theMsg->printf("%d changes in pass 1",change);
        change=0;
        if (workArea) workArea->setProgressInfo("Propagating pass 2/2 ...");

        for (k=dims[2]-1 ; k>=0 ; k--) {
            if (workArea) workArea->setProgressValue(0.5f*(dims[2]-1-k)/dims[2]+0.5f);
            for (j=dims[1]-1 ; j>=0 ; j--) {
                for (i=dims[0]-1 ; i>=0 ; i--) {
                    for (int dk=1 ; dk<3 ; dk++) {
                        mclong idx = (mclong(k)*mclong(dims[1])+mclong(j))*mclong(dims[0])+mclong(i);
                        if (insideonly && !src[idx]) continue;
                        DISTVAL &currval = dist[idx];
                        int k1,j1,i1;
                        k1=dk-1+k;
                        if (k1<0 || k1>=dims[2])
                            continue;
                        for (int dj=0 ; dj<3 ; dj++) {
                            j1 = dj-1+j;
                            if (j1<0 || j1>=dims[1])
                                continue;
                            for (int di=0 ; di<3 ; di++) {
                                i1 = i+di-1;
                                DISTVAL m = mask2[dk*9+dj*3+di];
                                if (m<0 || i1<0 || i1>=dims[0])
                                    continue;
                                mclong idx2 = (mclong(k1)*mclong(dims[1])+mclong(j1))*mclong(dims[0])+mclong(i1);
                                if (!insideonly || src[idx2]) {
                                    DISTVAL val = m+dist[idx2];
                                    if (val<currval) {
                                        currval=val;
                                        change++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        //theMsg->printf("%d changes in pass 2",change);
        if (workArea) workArea->stopWorking();
    }

    template<class T>
    void initChamfer345_templ(T mask[27]) {
        mask[13]=0;
        mask[12] = mask[14] = mask[10] = mask[16] = mask[4]  = mask[22] = T(3);
        mask[9]=mask[11]=mask[15]=mask[17] = mask[3]=mask[5]=mask[21]=mask[23]
        = mask[1]=mask[7]=mask[19]=mask[25] = T(4);
        mask[0]  = mask[2] = mask[6] = mask[8]
            = mask[18] = mask[20] = mask[24] = mask[26] = T(5);
    }

    inline void initChamfer345(short mask[27]) {
        initChamfer345_templ(mask);
    }

    inline void initChamfer345(int mask[27]) {
        initChamfer345_templ(mask);
    }
    inline void initChamfer345(float mask[27]) {
        initChamfer345_templ(mask);
    }
    template<class T>
    void initChamfer123_templ(T mask[27]) {
        mask[13]=0;
        mask[12] = mask[14] = mask[10] = mask[16] = mask[4]  = mask[22] = T(1);
        mask[9]=mask[11]=mask[15]=mask[17] = mask[3]=mask[5]=mask[21]=mask[23]
        = mask[1]=mask[7]=mask[19]=mask[25] = T(2);
        mask[0]  = mask[2] = mask[6] = mask[8]
            = mask[18] = mask[20] = mask[24] = mask[26] = T(3);
    }

    inline void initChamfer123(short mask[27]) {
        initChamfer123_templ(mask);
    }

    inline void initChamfer123(int mask[27]) {
        initChamfer123_templ(mask);
    }

    // fill 3x3x3 mask with values according to voxelsize
    inline void initChamferExact(float voxelsize[3], float mask[27]) {
        float v2[3];
        v2[0]=voxelsize[0]*voxelsize[0];
        v2[1]=voxelsize[1]*voxelsize[1];
        v2[2]=voxelsize[2]*voxelsize[2];
        mask[13]=0;
        mask[12] = mask[14] = voxelsize[0];
        mask[10] = mask[16] = voxelsize[1];
        mask[4]  = mask[22] = voxelsize[2];
        mask[9]=mask[11]=mask[15]=mask[17] = sqrt(v2[0]+v2[1]);
        mask[3]=mask[5]=mask[21]=mask[23] = sqrt(v2[0]+v2[2]);
        mask[1]=mask[7]=mask[19]=mask[25] = sqrt(v2[1]+v2[2]);
        mask[0]  = mask[2] = mask[6] = mask[8]
            = mask[18] = mask[20] = mask[24] = mask[26] = sqrt(v2[0]+v2[1]+v2[2]);

    /* just to be sure...
        int idx=0;
        for (int k=-1 ; k<=1 ; k++) {
            for (int j=-1 ; j<=1 ; j++) {
                for (int i=-1 ; i<=1 ; i++) {
                    float l1 = mask[idx] ;
                    float l2 = hypot(hypot(i*voxelsize[0],j*voxelsize[1]),
                    k*voxelsize[2]);
                        idx++;
                    assert(fabs(l2-l1)<0.00001);
                }
            }
        }
        printf("alles ok\n");
        */
    }

    template <class DISTTYPE, class SRCTYPE, class DISTVAL, class INDEXTYPE>
    void propagateBSFieldChamferFast2(DISTTYPE dist, SRCTYPE src, DISTVAL chamfermask[27],
    INDEXTYPE* imgpixels, unsigned char* bordered, INDEXTYPE nnn,
                                     const int* dims, McProgressInterface* workArea)
    {
        int i;
        DISTVAL mask[27];
        if (workArea) workArea->startWorking("Propagating pass 1/2 ...");
        McNeighborIterator33 indexing(26,dims);
        INDEXTYPE i1=0,i2=nnn,incr=1;

        for (int pass=0 ; pass<2 ; pass++) {
            if (pass==1) {
                if (workArea) workArea->setProgressInfo("Propagating pass 2/2 ...");
                i1=nnn-1; i2=-1; incr=-1;
            }
            prepareChamferPropagationMask(pass,chamfermask, mask);
            indexing.setWeights(mask);
            for (i=i1 ; i!=i2 ; i+=incr) {
                if (workArea && i%10000==0) workArea->setProgressValue((float)(i*incr+i1)/nnn);
                DISTVAL &currval = dist[imgpixels[i]];
                if (currval>0)
                    i=i;
                assert(src[imgpixels[i]]);
                assert(imgpixels[i]<INDEXTYPE(dims[0])*INDEXTYPE(dims[1])*INDEXTYPE(dims[2]));
                DISTVAL m;
                for (int l=0 ; l<indexing.ctype ; l++) {
                    getWeight(indexing,l,m);
                    if (m>0) {
                        if (!bordered[i] || !(bordered[i] & indexing.bordered[l]) ) {
                            INDEXTYPE index2 = imgpixels[i]+INDEXTYPE(indexing.offsets[l]);
                            if (src[index2]) {
                                DISTVAL val = m+dist[index2];
                                if (val<currval) {
                                    assert(val>0);
                                    currval=val;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (workArea) workArea->stopWorking();
    }

    template <class IMGTYPE, class DISTTYPE>
    void computeDistanceMapChamferShort(IMGTYPE image, const int* dims,
                                              DISTTYPE output, McProgressInterface* workArea, int ch123=0) 
    {    
        mculong nnn = (mculong)dims[0]*(mculong)dims[1]*(mculong)dims[2];
        for (mclong index=0; index<nnn; index++){
                output[index] = (1<<15)-100; // use at most MAX_SHORT - max_mask_weight
        }
        McDArray<int> bweights(27);
        bweights.fill(1);
        short mask[27];
        if (ch123)
            initChamfer123(mask);
        else
            initChamfer345(mask);
        
        if (mcNeeds64BitIndex3D (dims)) {
            findBoundaryVoxelsChamferInside(output, ch123 ? 6 : 18, bweights.dataPtr(), image,
                                            dims, (McDArray<mclong>*)0, workArea,
                                            (McDArray<mclong>*)0, 0, (mclong)0);
            propagateBSFieldChamferFast(output, image, mask, dims, workArea,0);
        } else {
            findBoundaryVoxelsChamferInside(output, ch123 ? 6 : 18, bweights.dataPtr(), image,
                                        dims, (McDArray<int>*)0, workArea,  
                                        (McDArray<int>*)0, 0, (int)0);
            propagateBSFieldChamferFast(output, image, mask, dims, workArea,0);
        }
    }

    template <class IMGTYPE, class DISTTYPE>
    void computeDistanceMapChamferFloat(IMGTYPE image, const int* dims,
                                                float voxelSize[3], DISTTYPE output,
                                                McProgressInterface* workArea)
    {
        float mask[27];
        mclong nnn = (mclong)dims[0]*(mclong)dims[1]*(mclong)dims[2];
        for (mclong index=0; index<nnn; index++){
            output[index] = 1e25;
        }
        initChamferExact(voxelSize,mask);
        McDArray<float> bweights(27);
        // init boundary with half weights
        for (int i = 0; i < 27; i++) {
            bweights[i] = 0.5 * mask[i];
        }
        if (mcNeeds64BitIndex3D (dims)) {
            McDArray<mclong> gather;
            findBoundaryVoxelsChamferInside(output, 18, bweights.dataPtr(), image, dims, (McDArray<mclong>*)0, 
                                            workArea, (McDArray<mclong>*)0, 0, (mclong)0);

            propagateBSFieldChamferFast(output, image, mask, dims, workArea, 0);

        } else  {
            findBoundaryVoxelsChamferInside(output, 18, bweights.dataPtr(), image,
                                            dims, (McDArray<int>*)0, workArea, (McDArray<int>*)0, 0, (int)0);

            propagateBSFieldChamferFast(output, image, mask, dims, workArea, 0);
        }
    }

    template <class IMGTYPE, class DISTTYPE>
    void computeInsideDistanceMapChamferShort(IMGTYPE image, const int* dims,
                                              DISTTYPE output, McProgressInterface* workArea, int ch123=0) 
    {
        mclong nnn = mclong(dims[0])*mclong(dims[1])*mclong(dims[2]);
        for (mclong index=0; index<nnn; index++){
            if (image[index])
                output[index] = (1<<15)-100; // use at most MAX_SHORT - max_mask_weight
        }
        //findBoundaryVoxelsChamfer(output, 1, image, dims, 0, workArea);
        //propagateBSFieldChamferFast(output, image, (short) 0, dims, workArea);

        McDArray<int> bweights(27);
        short mask[27];
        if (ch123)
            initChamfer123(mask);
        else
            initChamfer345(mask);

        for (int i=0 ; i<27 ; i++)
            bweights[i]=1; //(mask[i]+1)/2;

        McDArray<unsigned char> bordered;

        if (mcNeeds64BitIndex3D (dims)) {
            McDArray<mclong> gather;
            findBoundaryVoxelsChamferInside(output, ch123 ? 6 : 18, bweights.dataPtr(), image,
                                            dims, (McDArray<mclong>*)0, workArea,
                                            &gather,
                                            &bordered,  (mclong)(dims[0]*dims[1]*dims[2]*0.15));
            if (gather.size()) {
                printf("Detected sparse data set: %lld\n", (long long)(gather.size()));
                propagateBSFieldChamferFast2(output, image, mask, gather.dataPtr (), bordered.dataPtr (), 
                                             gather.size(),  dims, workArea);
            } else {
                propagateBSFieldChamferFast(output, image, mask, dims, workArea);
            }
        } else {
            McDArray<int> gather;
            findBoundaryVoxelsChamferInside(output, ch123 ? 6 : 18, bweights.dataPtr(), image,
                                            dims, (McDArray<int>*)0, workArea,
                                            &gather,
                                            &bordered,  (int)(dims[0]*dims[1]*dims[2]*0.15));

            if (gather.size()) {
                printf("Detected sparse data set: %lld\n", (long long)(gather.size()));
                propagateBSFieldChamferFast2(output, image, mask, gather.dataPtr (), bordered.dataPtr (), 
                                             int(gather.size()),  dims, workArea);
            } else {
                propagateBSFieldChamferFast(output, image, mask, dims, workArea);
            }
        }
    }

    template <class IMGTYPE, class DISTTYPE>
    void computeInsideDistanceMapChamferFloat(IMGTYPE image, const int* dims,
                                                float voxelSize[3], DISTTYPE output,
                                                McProgressInterface* workArea) 
    {
        float mask[27];
        mclong nnn = (mclong)dims[0]*(mclong)dims[1]*(mclong)dims[2];
        for (mclong index=0; index<nnn; index++){
            if (image[index])
                output[index] = 1e25;
        }
        initChamferExact(voxelSize,mask);

        // init boundary with half weights
        McDArray<float> bweights(27);
        for (int i = 0; i < 27; i++) {
            bweights[i] = 0.5 * mask[i];
        }
        McDArray<unsigned char> bordered;
        
        if (mcNeeds64BitIndex3D (dims)) {
            McDArray<mclong> gather;
            findBoundaryVoxelsChamferInside(output, 18, bweights.dataPtr(), image, 
                                            dims, (McDArray<mclong>*)0, workArea,
                                            &gather, &bordered,
                                            mclong(dims[0]*dims[1]*dims[2]*0.15));
            if (gather.size()) {
                printf("Detected sparse data set:%lld\n",(long long)(gather.size()));
                propagateBSFieldChamferFast2(output, image, mask, gather.dataPtr(), bordered.dataPtr(), 
                                             gather.size(), dims, workArea);
            } else {
                propagateBSFieldChamferFast(output, image, mask, dims, workArea);
            }
        } else {
            McDArray<int> gather;
            findBoundaryVoxelsChamferInside(output, 18, bweights.dataPtr(), image,
                                        dims, (McDArray<int>*)0, workArea,
                                        &gather, &bordered, (int)(dims[0]*dims[1]*dims[2]*0.15));

            if (gather.size()) {
                printf("Detected sparse data set:%lld\n",(long long)(gather.size()));
                propagateBSFieldChamferFast2(output, image, mask, gather.dataPtr(), bordered.dataPtr(), 
                                             int(gather.size()), dims, workArea);
            } else {
                propagateBSFieldChamferFast(output, image, mask, dims, workArea);
            }
        }
    }

    // like the above one but only finds boundary voxels between insideMat and boundaryMat (useful in very special cases only...)
    template <class DISTTYPE, class DISTVAL, class SRCTYPE, class INDEXTYPE>
    void findBoundaryVoxelsChamferInsideSpecial(DISTTYPE dist, int ctype, DISTVAL mindist[27],
                                         SRCTYPE* src,const int* dims,
                                         SRCTYPE insideMat,SRCTYPE boundaryMat,
                                         McDArray<INDEXTYPE> *front,
                                         McProgressInterface* workArea,
                                         McDArray<unsigned char>* bordered = 0,
                                         INDEXTYPE maxgather=0)
    {
        McNeighborIterator33 indexing(26,dims);
        INDEXTYPE index=0;
        int i,j,k;
        indexing.setWeights(mindist, 1);

        if (workArea) workArea->startWorking("Detecting boundary");
        for (k=0 ; k<dims[2] ; k++) {
            if (workArea) workArea->setProgressValue((float)k/dims[2]);
            for (j=0 ; j<dims[1] ; j++) {
                unsigned char bordercase = indexing.borderstatus(0,j,k);
                unsigned char borderbase = bordercase & 252;

                for (i=0 ; i<dims[0] ;
                     i++, index++,
                         bordercase = borderbase |
                           (i==dims[0]-1)*McNeighborIterator33::BORDERX2
                         | (i==0)*McNeighborIterator33::BORDERX1) {
                    if (src[index] == insideMat){ // init inside
                        for (int l=0 ; l<indexing.ctype ; l++) {
                            INDEXTYPE indexn = index + INDEXTYPE (indexing.offsets[l]);
                            // this would cause the out-of-domain voxels
			    // to be beckground -> problem for 2D.
			    // we prefer to not consider them.
			    //if ((bordercase&indexing.bordered[l]) || src[indexn]==0){
			    if ( (!(bordercase&indexing.bordered[l])) && src[indexn]==boundaryMat){
                                dist[index] = DISTVAL(indexing.fweights[l]);
                                if (front) front->append(index);
                                break;
                            }
                        }
                    }// end if src[index]==insideMat
                }// end for i
            }// end for j
        }// end for k
        if (workArea) workArea->stopWorking();
    }

    template <class IMGTYPE, class DISTTYPE>
    void computeInsideDistanceMapChamferFloatSpecial(IMGTYPE* image, const int* dims,
                                                float voxelSize[3], 
                                                IMGTYPE insideMat, IMGTYPE boundaryMat,
                                                DISTTYPE output,
                                                McProgressInterface* workArea) {
        // TODO not yet 64 bit safe, needs modifications similar to computeInsideDistanceMapChamferShort
        float mask[27];
        int nnn = dims[0]*dims[1]*dims[2];
        for (int index=0; index<nnn; index++){
            if (image[index] == insideMat)
                output[index] = 1e25;
        }
        initChamferExact(voxelSize,mask);
        //initChamfer345(mask);
        // init boundary with half weights
        McDArray<float> bweights(27);
        for (int i = 0; i < 27; i++) {
            bweights[i] = 0.5 * mask[i];
        }
        McDArray<unsigned char> bordered;

        findBoundaryVoxelsChamferInsideSpecial(output, 18, bweights.dataPtr(), image,
            dims, insideMat, boundaryMat, 
            (McDArray<int>*)0, workArea, &bordered);

        propagateBSFieldChamferFast(output, image, mask, dims, workArea,insideMat);
    }

};

#endif

/// @}

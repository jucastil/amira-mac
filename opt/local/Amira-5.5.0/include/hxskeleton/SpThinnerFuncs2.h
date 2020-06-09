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
#ifndef SP_THINNERFUNCS2_H
#define SP_THINNERFUNCS2_H

#include <hxskeleton/SpNeighborhoodTest.h>
#include <hxcore/HxMessage.h>
#include <mclib/McBitfield.h>
#include <mclib/McProgressInterface.h>
#include <mclib/McDArray.h>
#include <mclib/McIndexer3D.h>
#include <mclib/McSobolSequence.h>
#include <mclib/Mc64Bit.h>

#include <limits.h>

namespace SpThinnerFuncs {

    // real Distance Ordered Thinning with O(n+m) (in two subiterations)
    // see Pudney, C. Distance-ordered homotopic thinning: A skeletonization algorithm for 3D digital images. Computer Vision and Image Understanding 72 (1998), 404
    // To Steffen: see Note March 1, 2006

    // the only valid type ist short.
    // TODO: support for other primTypes.
    // supports 64 bit indexing via INDEXTYPE
    template <class DISTMAP, class INDEXTYPE>
    inline
    int calcIterativeAccurateDistanceOrderedLineThinningIndexType2 (const int* dims
            , unsigned char* image
            , const DISTMAP& distmap
            , int keepWhat
            , int maxIterations
            , const McBitfield* locked
            , McProgressInterface* progress
            , int orgIteration
            , int lockOnlyFacePoints
            , bool* reachedTop
            , float speedUp
            , INDEXTYPE /*dummy*/) {

        mcrequire (maxIterations >= -1);
        mcrequire (dims[0] > 2);
        mcrequire (dims[1] > 2);
        mcrequire (dims[2] > 2);

        const int PLAIN = 1; // plain object voxel
        const int SUBITER0 = 2; // marked vor subiteration 0
        const int SUBITER1 = 3; // marked for subiteration 1
        const int QUEUED = 5; // indicating that voxel is queued

        mclong offsets[3] = {1, dims[0], dims[0] * dims[1]};

        // if we use lenX check, use X voxel border
        const int border = (keepWhat < 1) ? 1 : keepWhat;

        // compute maximum distance value
        int dmax = 0;
        {
            mclong idx;
            McIndexer3DBoxed indexer (dims, border);
            while (indexer.nextLong (idx)) {
                 if (image[idx] == 0) {
                     continue;
                 }
                 mcassert (distmap[idx] >= 0);
                 if (distmap[idx] > dmax) {
                     dmax = distmap[idx];
                 }
            }
        }

        // mark outside voxels as queued without actually queuing them
        // this keeps us off the boundary
        {
            mclong idx;
            McIndexer3DNotBoxed indexer (dims, border);
            while (indexer.nextLong (idx)) {
                 if (image[idx] == 0) {
                     continue;
                 }
                 image[idx] = QUEUED;
            }
        }

        // create queues for every distance
        const int nq = dmax + 1;
        McDArray<McDArray<INDEXTYPE> > queues (nq);

        SpNeighborhoodTest<unsigned char> sTest (dims);

        // ... and queue all boundary voxels
        {
            mclong idx;
            McIndexer3DBoxed indexer (dims, border);
            while (indexer.nextLong (idx)) {
                 if (image[idx] == 0 || (locked && (*locked)[idx])) {
                     continue;
                 }
                 if (      image[idx - offsets[0]] == 0
                        || image[idx + offsets[0]] == 0
                        || image[idx - offsets[1]] == 0
                        || image[idx + offsets[1]] == 0
                        || image[idx - offsets[2]] == 0
                        || image[idx + offsets[2]] == 0) {
                     // one background 6-neighbor
                     queues[(int)distmap[idx]].append (idx);
                     image[idx] = QUEUED;
                 } else {
                     image[idx] = PLAIN;
                 }
            }
        }

        int iteration = 0;
        bool changed = true;

        // main thinning loop
        while (changed && (maxIterations <= 0 || iteration < maxIterations)) {
            changed = false;

            // the lowest queue with changes will stop processing
            // new queues with lower distance might have filled -> restart from 0 
            for (int q = 0; q < nq && !changed; q++) {
                const int nels  = queues[q].size();
                if (!nels) {
                    continue;
                }

                bool subiter[2] = { false, false };
                // first check
                // mark voxels that could be deleted with subiteration label
                // if one voxel on this distance is marked, all voxels will be rechecked and labeled accordingly below
                for (int el = 0; el < nels; el++) {
                    const INDEXTYPE idx = queues[q][el];
                    if (image[idx] && !(locked && (*locked)[idx])) {
                        if (     (keepWhat == 0 && !sTest.isNotSimple (image+idx, 0xff))
                              || (keepWhat == 1 && !sTest.isNotSimpleOrIsEnd (image+idx, 0xff))
                              || (keepWhat >= 2 && !sTest.isNotSimpleOrIsEndWithLen (image+idx, 0xff, keepWhat))) {
                            // deletable -> mark subiteration
                            if (sTest.isWSBBoundary (image+idx, 0xff)) {
                                image[idx] = SUBITER0; // subiteration 0
                                subiter[0] = true;
                            } else if (sTest.isENTBoundary (image+idx, 0xff)) {
                                image[idx] = SUBITER1; // subiteration 1
                                subiter[1] = true;
                            } else {
                                mcassert (0 && "must not reach this point");
                            }
                        } else {
                            // not simple -> plain
                            image[idx] = PLAIN;
                        }
                    }
                }

                // if we found a voxel in any of the subiterations, we need to recheck
                if (subiter[0] || subiter[1]) {
                    changed = true;
                }
                // ... but only one of the two subiterations
                if (subiter[0] && subiter[1]) {
                    subiter[iteration % 2] = false;
                }

                int ndeleted = 0;
                // recheck
                if (changed) {
                    mcassert (subiter[0] != subiter[1]);
                    const int subiterlabel = subiter[0] ? SUBITER0 : SUBITER1; // we only accept voxels marked with this value
                    const int othersubiterlabel = subiter[0] ? SUBITER1 : SUBITER0; // ... these will get requed

                    for (int el = 0; el < nels; el++) {
                        const INDEXTYPE idx = queues[q][el];
                        if (image[idx] == subiterlabel) {
                            // recheck simple test
                            if (       (keepWhat == 0 && !sTest.isNotSimple (image+idx, 0xff))
                                    || (keepWhat == 1 && !sTest.isNotSimpleOrIsEnd (image+idx, 0xff))
                                    || (keepWhat >= 2 && !sTest.isNotSimpleOrIsEndWithLen (image+idx, 0xff, keepWhat))) {
                                // ... either delete
                                image[idx] = 0;
                                ndeleted++;
                                // ... and queue plain 26-neighbors
                                for (int k = -1; k < 2; k+= 1) {
                                    for (int j = -1; j < 2; j+= 1) {
                                        for (int i = -1; i < 2; i+= 1) {
                                            // voxel itself is excluded because it's already set to 0 right above
                                            const mclong neighboridx = idx + i * offsets[0] + j * offsets[1] + k * offsets[2];
                                            if (image[neighboridx] == PLAIN) {
                                                mcassert (distmap[neighboridx] >= 0);
                                                queues[(int)(distmap[neighboridx])].append (neighboridx);
                                                image[neighboridx] = QUEUED;
                                            }
                                        }
                                    }
                                }
                            } else {
                                // ... or
                                // simple test fails -> unqueue for now -> will be requeued if neighborhood changes
                                image[idx] = PLAIN;
                            }
                        } else if (image[idx] == othersubiterlabel) {
                            // subiteration didn't match -> requeue because simple test needs to be repeated
                            queues[q].append (idx);
                            image[idx] = QUEUED;
                        } 
                    }
                    printf ("ndeleted = %d\n", ndeleted);
                } 
                // cleanup old elements in any case
                queues[q].remove (0, nels);
            }

            iteration++;
        }

        // reset voxels marked outside
        {
            mclong idx;
            McIndexer3DNotBoxed indexer (dims, border);
            while (indexer.nextLong (idx)) {
                if (image[idx] == 0) {
                    continue;
                }
                image[idx] = PLAIN;
            }
        }


        return iteration;
    }


    template <class DISTMAP>
    inline
    int calcIterativeAccurateDistanceOrderedLineThinning2 (const int* dims
            , unsigned char* image
            , const DISTMAP& distmap
            , int keepWhat
            , int maxIterations = -1
            , const McBitfield* locked = 0
            , McProgressInterface* progress = 0
            , int orgIteration = 0
            , int lockOnlyFacePoints = 0
            , bool* reachedTop = 0
            , float speedUp = 0.3) {

        // choose 64 bit indexing only if needed
        if (mcNeeds64BitIndex3D (dims)) {
            return calcIterativeAccurateDistanceOrderedLineThinningIndexType2 (
                         dims
                        , image
                        , distmap
                        , keepWhat
                        , maxIterations
                        , locked
                        , progress
                        , orgIteration
                        , lockOnlyFacePoints
                        , reachedTop
                        , speedUp
                        , (mclong)1);  // use long indices
        }
        return calcIterativeAccurateDistanceOrderedLineThinningIndexType2 (
                     dims
                    , image
                    , distmap
                    , keepWhat
                    , maxIterations
                    , locked
                    , progress
                    , orgIteration
                    , lockOnlyFacePoints
                    , reachedTop
                    , speedUp
                    , (int)1); // int indices are sufficient
    }

}; // end of namespace

#endif

/// @}

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
#ifndef HXTHINNER2__SP_THINNERFUNCS_H
#define HXTHINNER2__SP_THINNERFUNCS_H

#include "SpNeighborhoodTest.h"
#include <hxcore/HxMessage.h>
#include <mclib/McBitfield.h>
#include <mclib/McProgressInterface.h>
#include <mclib/McDArray.h>
#include <mclib/McIndexer3D.h>
#include <mclib/McSobolSequence.h>
#include <mclib/Mc64Bit.h>

#include <limits.h>

namespace SpThinnerFuncs {

    // the only valid type ist short.
    // TODO: support for other primTypes.
    // supports 64 bit indexing via INDEXTYPE
    template <class DISTMAP, class INDEXTYPE>
    inline
    int calcIterativeAccurateDistanceOrderedLineThinningIndexType (const int* dims
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

        // create queues for every distance
        McDArray<McDArray<INDEXTYPE> > queues (SHRT_MAX + 1);

        // scan through all voxels and queue distance sorted
        // use Sobol quasi random order
        // this is not locally deterministic 
        //              --> changed to 2 subiteration thinner
#if 0
        if (progress) {
            progress->startWorkingNoStop ("Initializing pseudo random order"); 
        }
        // if we use len2 check, use 2 voxel border
        McIndexer3DBoxed idx (dims, (keepWhat < 1) ? 1 : keepWhat);
        McSobolSequence seq (dims[0] * dims[1] * dims[2]);
        int pos;
        int srcVoxelNum = 0;
        while (seq.next (pos)) {
            if (!idx.inside (pos) || image[pos] == 0) {
                continue;
            }
            assert (distmap[pos] >= 0);
            queues[(int)distmap[pos]].append (pos);
            srcVoxelNum++;
        }
        //theMsg->printf ("Num of srcvoxels: %d", srcVoxelNum);
        if (progress) {
            progress->stopWorking (); 
        }
#endif
        // initialize straight forward + subfields
        if (progress) {
            progress->startWorkingNoStop ("Initializing..."); 
        }
        // if we use lenX check, use X voxel border
        mclong pos;
        mclong srcVoxelNum = 0;

        McIndexer3DBoxedSubfields idx (dims, (keepWhat < 1) ? 1 : keepWhat, 2);
        while (idx.nextLong (pos)) {
             if (image[pos] == 0) {
                 continue;
             }
             assert (distmap[pos] >= 0);
             queues[(int)distmap[pos]].append (pos);
             srcVoxelNum++;
        }
        // return if there are no voxels to be processed
        if (srcVoxelNum == 0) {
            if (reachedTop) {
                *reachedTop = true;
            }
			if (progress) {
				progress->stopWorking (); 
			}
           return 0; // no iteration performed
        }
        //theMsg->printf ("Num of srcvoxels: %d", srcVoxelNum);
        if (progress) {
            progress->stopWorking (); 
        }

        // start thinning
        if (progress) {
            progress->startWorkingNoStop ("Thinning"); 
        }
        
        SpNeighborhoodTest<unsigned char> sTest (dims);
        int minQueue = 0;
        while (queues[minQueue].size () == 0) {
            minQueue++;
        }

        //int count = 0;
        int iteration = 0;
        // subiteration stuff
        const int numOfSubIt = 2;
        int subIt = 0;
        int highestQueue = SHRT_MAX;
        while (queues[highestQueue].size () == 0) {
            highestQueue--;
        }
        if (reachedTop) {
            *reachedTop = false; // will be set if reached
        }

        // main thinning loop
        while (    minQueue < SHRT_MAX + 1
                && (maxIterations < 0 || iteration < maxIterations)) {

            if (queues[minQueue].size () == 0) {
                minQueue++;
                continue;
            }
            // calc which queues to use
            // assure that at some time, all queues will be processed.
            int maxQueue = int(float((orgIteration + iteration) / numOfSubIt) 
                                        * speedUp); 
            // check if we reached the highest value
            if (reachedTop && (maxQueue > highestQueue)) {
                *reachedTop = true;
            }
            if (maxQueue < minQueue) {
                maxQueue = minQueue;
            }
            progress->setProgressInfo ("Thinning - Iteration %d: processing distances %d - %d", orgIteration + iteration, minQueue, maxQueue);

            // check all voxels in low queues
            // and mark voxels that may be removed
            // 2 subiteration --> map iteration to ENT or WSB boundary
            int changed = 0;
            for (int qu = minQueue; qu <= maxQueue; qu++) {
              int size = queues[qu].size ();
              int el;
              for (el = 0; el < size; el++) {
                pos = queues[qu][el];

                if (image[pos] 
                      && (!locked || !(*locked)[pos]) 
                                || (lockOnlyFacePoints && !sTest.isFaceEnd (image+pos, 0xff))) {
                  if ((
                        (subIt == 0) ? sTest.isWSBBoundary (image+pos, 0xff)
                                     : sTest.isENTBoundary (image+pos, 0xff)
//                            sTest.isSubIt (image+pos, 0xff
//                                    , subIt)
                      )  
                          &&
                      (
                         (keepWhat == 0 && !sTest.isNotSimple (image+pos, 0xff))
                      || (keepWhat == 1 
                            && !sTest.isNotSimpleOrIsEnd (image+pos, 0xff))
                      || (keepWhat >= 2
                            && !sTest.isNotSimpleOrIsEndWithLen (image+pos
                                                       , 0xff, keepWhat))
                      )
                      ) {
                    image[pos] = 3;
                  } else {
                      // queue again
                      queues[qu].append (pos);
                  }
                }
              }

              // check again and remove all marked that are still simple
              // after removal of previous voxels
              for (el = 0; el < queues[qu].size (); el++) {
                  pos = queues[qu][el];

                  if ((image[pos] & 2)) { 
                    if ((keepWhat == 0 && !sTest.isNotSimple (image+pos, 0xff))
                      || (keepWhat == 1 
                             && !sTest.isNotSimpleOrIsEnd (image+pos, 0xff))
                      || (keepWhat >= 2
                            && !sTest.isNotSimpleOrIsEndWithLen (image+pos
                                                       , 0xff, keepWhat))) {
                          image[pos] = 0;
                          changed++;
                      } else {
                          // queue again
                          image[pos] = 1;
                          queues[qu].append (pos);
                      }
                  }
              }
              // remove old elems
              queues[qu].remove (0, size);
            }
            // check for removal of any voxel
            // if no voxel removed break.
            if (changed == 0 && maxQueue > highestQueue) {
                break;
            }
            iteration++;
//            theMsg->printf ("removed %d voxel", changed);
            // check removed voxel stuff only after full subiteration
            subIt++;
            if (subIt == numOfSubIt) {
                subIt = 0;
            }
        }

		if (progress) {
            progress->stopWorking ();
        }
        return iteration;
    }


    template <class DISTMAP>
    inline
    int calcIterativeAccurateDistanceOrderedLineThinning (const int* dims
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
            return calcIterativeAccurateDistanceOrderedLineThinningIndexType (
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
        return calcIterativeAccurateDistanceOrderedLineThinningIndexType (
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

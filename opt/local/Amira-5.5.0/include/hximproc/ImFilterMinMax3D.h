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

/// @addtogroup hximproc hximproc
/// @{
#ifndef _IMFILTERMINMAX_H__
#define _IMFILTERMINMAX_H__

#include "ImFilterParallel.h"

template<class Type>
static void _minmax(const int *dim,const Type* src, Type* dst,const int neighbour, class McProgressInterface* progress, int maxFilter)
{
    const mcint64 dimX = dim[0];
    const mcint64 dimY = dim[1];
    const mcint64 dimZ = dim[2];

    const mcint64 dx = 1;
    const mcint64 dy = dimX;
    const mcint64 dz = dimX * dimY;

    ImFilterParallel parallel;

    int workDone0 = 1;
    int workDone  = 1;
    bool abort = false;
    int numSlicesPerThread = parallel.getNumSlicesPerThread();

    parallel.initProgressBar(progress, dimZ);  

/**********************************************************/
// Calculate min or max on all the middle slices
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 z = 1; z < dimZ-1; ++z) {

        // abort the computation
        if (abort)
            continue;

        // update the progress bar
        workDone = workDone0 + z;
        abort = parallel.updateProgressBar(workDone);
        if (abort)
        {
#pragma omp flush(abort)
            continue;
        }


        // do actual the computation
        for (mcint64 y = 1; y < dimY-1; ++y)
            for (mcint64 x = 1 ;x < dimX-1 ;++x)
            {
                mcint64 index = x + y*dy + z*dz;
                Type value = src[index];
                if (maxFilter == 0)
                {

                    value = (value < src[index - dx]) ? value : src[index - dx];
                    value = (value < src[index + dx]) ? value : src[index + dx];
                    value = (value < src[index - dy]) ? value : src[index - dy];
                    value = (value < src[index + dy]) ? value : src[index + dy];
                    value = (value < src[index - dz]) ? value : src[index - dz];
                    value = (value < src[index + dz]) ? value : src[index + dz];

                    if (neighbour > 6)
                    {
                        value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                        value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];
                        value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];
                        value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];

                        value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                        value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                        value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
                        value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];

                        value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                        value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                        value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
                        value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
                    }

                    if (neighbour > 18)
                    {
                        value = (value < src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                        value = (value < src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                        value = (value < src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                        value = (value < src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];

                        value = (value < src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                        value = (value < src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
                        value = (value < src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
                        value = (value < src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
                    }
                } 
                else
                {
                    value = (value > src[index - dx]) ? value : src[index - dx];
                    value = (value > src[index + dx]) ? value : src[index + dx];
                    value = (value > src[index - dy]) ? value : src[index - dy];
                    value = (value > src[index + dy]) ? value : src[index + dy];
                    value = (value > src[index - dz]) ? value : src[index - dz];
                    value = (value > src[index + dz]) ? value : src[index + dz];

                    if (neighbour > 6)
                    {
                        value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                        value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];
                        value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];
                        value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];

                        value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                        value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                        value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
                        value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];

                        value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                        value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                        value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
                        value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];   
                    }
                    if (neighbour > 18)
                    {
                        value = (value > src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                        value = (value > src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                        value = (value > src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                        value = (value > src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];

                        value = (value > src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                        value = (value > src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
                        value = (value > src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
                        value = (value > src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
                    }
                }

                dst[index] = value;
            }// end loop x y
    } //end loop z


    if (abort) 
        return ;

/**********************************************************/
// the UP slice
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 y = 1; y < dimY-1 ; ++y) {
        for (mcint64 x = 1; x < dimX-1; ++x) {
            // The TOP slice
            mcint64 index = x + y*dy;
            Type value = src[index];

            if (maxFilter == 0)
            {

                value = (value < src[index - dx]) ? value : src[index - dx];
                value = (value < src[index + dx]) ? value : src[index + dx];
                value = (value < src[index - dy]) ? value : src[index - dy];
                value = (value < src[index + dy]) ? value : src[index + dy];   
                value = (value < src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                    value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];
                    value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];
                    value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];

                    value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                    value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                    value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
                    value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
                }

                if (neighbour > 18)
                {
                    value = (value < src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                    value = (value < src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
                    value = (value < src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
                    value = (value < src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
                }
            } 
            else
            {
                value = (value > src[index - dx]) ? value : src[index - dx];
                value = (value > src[index + dx]) ? value : src[index + dx];
                value = (value > src[index - dy]) ? value : src[index - dy];
                value = (value > src[index + dy]) ? value : src[index + dy];
                value = (value > src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                    value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];
                    value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];
                    value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];

                    value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                    value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                    value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
                    value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
                }
                if (neighbour > 18)
                {
                    value = (value > src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                    value = (value > src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
                    value = (value > src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
                    value = (value > src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
                }
            }

            dst[index] = value;
        }
    }

/***********************************************************/
// The DOWN slice
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 y = 1; y < dimY-1 ; ++y) {
        for (mcint64 x = 1; x < dimX-1; ++x) {
            // the bottom slice
            mcint64 index = x + y*dy+dimZ*dz-dz;
            Type value = src[index];

            if (maxFilter == 0)
            {
                value = (value < src[index - dx]) ? value : src[index - dx];
                value = (value < src[index + dx]) ? value : src[index + dx];
                value = (value < src[index - dy]) ? value : src[index - dy];
                value = (value < src[index + dy]) ? value : src[index + dy];
                value = (value < src[index - dz]) ? value : src[index - dz];

                if (neighbour > 6)
                {
                    value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                    value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];
                    value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];
                    value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];

                    value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                    value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                    value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
                    value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];
                }

                if (neighbour > 18)
                {
                    value = (value < src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                    value = (value < src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                    value = (value < src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                    value = (value < src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
                }
            } 
            else
            {
                value = (value > src[index - dx]) ? value : src[index - dx];
                value = (value > src[index + dx]) ? value : src[index + dx];
                value = (value > src[index - dy]) ? value : src[index - dy];
                value = (value > src[index + dy]) ? value : src[index + dy];
                value = (value > src[index - dz]) ? value : src[index - dz];

                if (neighbour > 6)
                {
                    value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                    value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];
                    value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];
                    value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];

                    value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                    value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                    value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
                    value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];

                }
                if (neighbour > 18)
                {
                    value = (value > src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                    value = (value > src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                    value = (value > src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                    value = (value > src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
                }
            } 

            dst[index] = value;
        }
    }

//*********************************************************/
// LEFT SLICE
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 y = 1; y < dimY-1; ++y) {
        for (mcint64 z = 1 ;z < dimZ-1 ;++z) {
            mcint64 index = y*dy + z*dz;
            Type value = src[index];
            if (maxFilter == 0)
            {
                value = (value < src[index + dx]) ? value : src[index + dx];
                value = (value < src[index - dy]) ? value : src[index - dy];
                value = (value < src[index + dy]) ? value : src[index + dy];
                value = (value < src[index - dz]) ? value : src[index - dz];
                value = (value < src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];
                    value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];

                    value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                    value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
                    value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];

                    value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                    value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
                    value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
                }

                if (neighbour > 18)
                {
                    value = (value < src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                    value = (value < src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
                    value = (value < src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
                    value = (value < src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
                }
            } 
            else
            {

                value = (value > src[index + dx]) ? value : src[index + dx];
                value = (value > src[index - dy]) ? value : src[index - dy];
                value = (value > src[index + dy]) ? value : src[index + dy];
                value = (value > src[index - dz]) ? value : src[index - dz];
                value = (value > src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];
                    value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];

                    value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                    value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
                    value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];


                    value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                    value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
                    value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];   
                }

                if (neighbour > 18)
                {

                    value = (value > src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                    value = (value > src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
                    value = (value > src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
                    value = (value > src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
                }
            } 

            dst[index] = value;
        }// end loop x y
    }

//**********************************************************/
// RIGHT SLICE
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 y = 1; y < dimY-1; ++y) {
        for (mcint64 z = 1 ;z < dimZ-1 ;++z) {
            mcint64 index = dimX-dx+y*dy + z*dz;
            Type value = src[index];

            if (maxFilter == 0)
            {

                value = (value < src[index - dx]) ? value : src[index - dx];
                value = (value < src[index - dy]) ? value : src[index - dy];
                value = (value < src[index + dy]) ? value : src[index + dy];
                value = (value < src[index - dz]) ? value : src[index - dz];
                value = (value < src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                    value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];

                    value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                    value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
                    value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];

                    value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                    value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
                    value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
                }

                if (neighbour > 18)
                {
                    value = (value < src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                    value = (value < src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                    value = (value < src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                    value = (value < src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
                }
            } 
            else
            {
                value = (value > src[index - dx]) ? value : src[index - dx];
                value = (value > src[index - dy]) ? value : src[index - dy];
                value = (value > src[index + dy]) ? value : src[index + dy];
                value = (value > src[index - dz]) ? value : src[index - dz];
                value = (value > src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                    value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];

                    value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                    value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
                    value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];

                    value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                    value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
                    value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];   
                }
                if (neighbour > 18)
                {
                    value = (value > src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                    value = (value > src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                    value = (value > src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                    value = (value > src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
                }
            } 
            dst[index] = value;
        }// end loop x y
    }

//*********************************************************/
// TOP SLICE
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 z = 1 ; z < dimZ-1 ; ++z) {
        for (mcint64 x = 1 ; x < dimX-1 ; ++x) {
            mcint64 index = x + z*dz;
            Type value = src[index];

            if (maxFilter == 0)
            {
                value = (value < src[index - dx]) ? value : src[index - dx];
                value = (value < src[index + dx]) ? value : src[index + dx];
                value = (value < src[index + dy]) ? value : src[index + dy];
                value = (value < src[index - dz]) ? value : src[index - dz];
                value = (value < src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];
                    value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];

                    value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                    value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                    value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];

                    value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                    value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                    value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
                }

                if (neighbour > 18)
                {
                    value = (value < src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                    value = (value < src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];


                    value = (value < src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
                    value = (value < src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
                }
            } 
            else
            {
                value = (value > src[index - dx]) ? value : src[index - dx];
                value = (value > src[index + dx]) ? value : src[index + dx];
                value = (value > src[index + dy]) ? value : src[index + dy];
                value = (value > src[index - dz]) ? value : src[index - dz];
                value = (value > src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];
                    value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];

                    value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                    value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                    value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];

                    value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                    value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                    value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
                }

                if (neighbour > 18)
                {
                    value = (value > src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];                        
                    value = (value > src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];                        
                    value = (value > src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];                        
                    value = (value > src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
                }
            } 

            dst[index] = value;
        }// end loop x y
    }

//*********************************************************/
// Bottom SLICE
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 z = 1 ; z < dimZ-1 ; ++z) {
        for (mcint64 x = 1 ; x < dimX-1 ; ++x) {
            mcint64 index = x + dimY*dy - dy +z*dz;
            Type value = src[index];

            if (maxFilter == 0)
            {
                value = (value < src[index - dx]) ? value : src[index - dx];
                value = (value < src[index + dx]) ? value : src[index + dx];
                value = (value < src[index - dy]) ? value : src[index - dy];
                value = (value < src[index - dz]) ? value : src[index - dz];
                value = (value < src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                    value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];

                    value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                    value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                    value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];

                    value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                    value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                    value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];                        
                }

                if (neighbour > 18)
                {
                    value = (value < src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                    value = (value < src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                    value = (value < src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                    value = (value < src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];                        
                }
            } 
            else
            {
                value = (value > src[index - dx]) ? value : src[index - dx];
                value = (value > src[index + dx]) ? value : src[index + dx];
                value = (value > src[index - dy]) ? value : src[index - dy];                        
                value = (value > src[index - dz]) ? value : src[index - dz];
                value = (value > src[index + dz]) ? value : src[index + dz];

                if (neighbour > 6)
                {
                    value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];                            
                    value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];

                    value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                    value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                    value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];                            

                    value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                    value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                    value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];                             
                }
                if (neighbour > 18)
                {
                    value = (value > src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                    value = (value > src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                    value = (value > src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                    value = (value > src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];                            
                }
            } 
            dst[index] = value;
        }// end loop x y
    }


//**********************************************************/
// The X lines 1
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 x = 1 ; x < dimX-1;x++) {
        mcint64 index = x;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index + dx]) ? value : src[index + dx];

            value = (value < src[index + dy]) ? value : src[index + dy];                    
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {                       
                value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];
                value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];


                value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];         
                value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
            }
            if (neighbour > 18)
            {
                value = (value < src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];                 
                value = (value < src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
            }

        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index + dx]) ? value : src[index + dx];

            value = (value > src[index + dy]) ? value : src[index + dy];                    
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {                       
                value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];
                value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];


                value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];         
                value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
            }
            if (neighbour > 18)
            {
                value = (value > src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];                 
                value = (value > src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
            }
        } 


        dst[index] = value;
    }


// The X lines 2
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 x = 1 ; x < dimX-1;x++) {
        mcint64 index = x+dimY*dy-dy;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index + dx]) ? value : src[index + dx];
            value = (value < src[index - dy]) ? value : src[index - dy];                                        
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];                        
                value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];

                value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {

                value = (value < src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                value = (value < src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];

            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index + dx]) ? value : src[index + dx];
            value = (value > src[index - dy]) ? value : src[index - dy];                                        
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];                        
                value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];

                value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                value = (value > src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
            }
        } 

        dst[index] = value;
    }

// The X lines 3
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 x = 1 ; x < dimX-1;x++) {
        mcint64 index = x+dimZ*dz-dz;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index + dx]) ? value : src[index + dx];                    
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];                    
                value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];

                value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];                    
                value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                value = (value < src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];            
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index + dx]) ? value : src[index + dx];                    
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index - dz]) ? value : src[index - dz];


            if (neighbour > 6)
            {
                value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];                    
                value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];

                value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];                    
                value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                value = (value > src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];            
            }
        } 

        dst[index] = value;
    }



// The X lines 4
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 x = 1 ; x < dimX-1;x++) {
        mcint64 index = x+dimY*dy-dy+dimZ*dz-dz;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index + dx]) ? value : src[index + dx];
            value = (value < src[index - dy]) ? value : src[index - dy];
            value = (value < src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];    
                value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];

                value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];              
                value = (value < src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index + dx]) ? value : src[index + dx];
            value = (value > src[index - dy]) ? value : src[index - dy];
            value = (value > src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];    
                value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];

                value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];              
                value = (value > src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
            }
        } 

        dst[index] = value;
    }

//***********************************************************/
// The Y lines 1
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 y = 1; y < dimY-1; ++y) {
        mcint64 index = y*dy;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index + dx]) ? value : src[index + dx];
            value = (value < src[index - dy]) ? value : src[index - dy];
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];
                value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];

                value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
                value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
                value = (value < src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
            }
        } 
        else
        {
            value = (value > src[index + dx]) ? value : src[index + dx];
            value = (value > src[index - dy]) ? value : src[index - dy];
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];
                value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];

                value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
                value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
                value = (value > src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
            }
        } 

        dst[index] = value;
    }


// The Y lines 2
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 y = 1; y < dimY-1; ++y) {
        mcint64 index = y*dy + dimX - dx;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index - dy]) ? value : src[index - dy];
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];

                value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
                value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                value = (value < src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index - dy]) ? value : src[index - dy];
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];

                value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
                value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
                value = (value > src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
            }
        } 

        dst[index] = value;
    }

// The Y lines 3
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 y = 1; y < dimY-1; ++y) {
        mcint64 index = y*dy + dimZ*dz-dz;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index + dx]) ? value : src[index + dx];
            value = (value < src[index - dy]) ? value : src[index - dy];
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];
                value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];

                value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
                value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                value = (value < src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
            }
        } 
        else
        {
            value = (value > src[index + dx]) ? value : src[index + dx];
            value = (value > src[index - dy]) ? value : src[index - dy];
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];
                value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];

                value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
                value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                value = (value > src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
            }
        } 

        dst[index] = value;
    }

// The Y lines 4
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 y = 1; y < dimY-1; ++y) {
        mcint64 index = y*dy + dimZ*dz-dz + dimX-dx;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index - dy]) ? value : src[index - dy];
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index - dz]) ? value : src[index - dz];


            if (neighbour > 6)
            {
                value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];

                value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
                value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];


            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                value = (value < src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index - dy]) ? value : src[index - dy];
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index - dz]) ? value : src[index - dz];


            if (neighbour > 6)
            {
                value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];

                value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
                value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                value = (value > src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
            }
        } 

        dst[index] = value;
    }


//***********************************************************/
// The Z lines 1
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 z = 1; z < dimZ-1 ; z++) {
        mcint64 index = z*dz;
        Type value = src[index];


        if (maxFilter == 0)
        {
            value = (value < src[index + dx]) ? value : src[index + dx];                    
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index - dz]) ? value : src[index - dz];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];                        
                value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];

                value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];                       
                value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];                        
                value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
                value = (value < src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
            }
        } 
        else
        {
            value = (value > src[index + dx]) ? value : src[index + dx];                    
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index - dz]) ? value : src[index - dz];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];                        
                value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];

                value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];                       
                value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];                        
                value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
                value = (value > src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
            }
        } 

        dst[index] = value;
    }



// The Z lines 2
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 z = 1; z < dimZ-1 ; z++) {
        mcint64 index = z*dz + dimX-dx;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index - dz]) ? value : src[index - dz];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];
                value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];

                value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];        
                value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                value = (value < src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index - dz]) ? value : src[index - dz];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];
                value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];

                value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];        
                value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
                value = (value > src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
            }
        } 

        dst[index] = value;
    }


// The Z lines 3
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 z = 1; z < dimZ-1 ; z++) {
        mcint64 index = z*dz + dimY*dy - dy;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index + dx]) ? value : src[index + dx];
            value = (value < src[index - dy]) ? value : src[index - dy];                    
            value = (value < src[index - dz]) ? value : src[index - dz];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];
                value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];

                value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                value = (value < src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
            }
        } 
        else
        {
            value = (value > src[index + dx]) ? value : src[index + dx];
            value = (value > src[index - dy]) ? value : src[index - dy];                    
            value = (value > src[index - dz]) ? value : src[index - dz];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];
                value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];

                value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
                value = (value > src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
            }
        } 


        dst[index] = value;
    }

// The Z lines 4
#pragma omp parallel for schedule(static,numSlicesPerThread)
    for (mcint64 z = 1; z < dimZ-1 ; z++) {
        mcint64 index = z*dz + dimY*dy - dy + dimX - dx;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];                    
            value = (value < src[index - dy]) ? value : src[index - dy];                    
            value = (value < src[index - dz]) ? value : src[index - dz];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];

                value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                value = (value < src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];                    
            value = (value > src[index - dy]) ? value : src[index - dy];                    
            value = (value > src[index - dz]) ? value : src[index - dz];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];

                value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
                value = (value > src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
            }
        } 

        dst[index] = value;
    }


//*************************
//  The corners
    // Corner 1 0 0 0
    {
        mcint64 index = 0;         
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index + dx]) ? value : src[index + dx];                    
            value = (value < src[index + dy]) ? value : src[index + dy];                    
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];
                value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {                        
                value = (value < src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
            }
        } 
        else
        {
            value = (value > src[index + dx]) ? value : src[index + dx];                    
            value = (value > src[index + dy]) ? value : src[index + dy];                    
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];
                value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {                        
                value = (value > src[index + dx + dy + dz]) ? value : src[index + dx + dy + dz];
            }
        } 


        dst[index] = value;
    }

    // Corner 2 1 1 1
    {
        mcint64 index = dimX * dimY * dimZ - 1;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];                    
            value = (value < src[index - dy]) ? value : src[index - dy];                    
            value = (value < src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];                    
            value = (value > src[index - dy]) ? value : src[index - dy];                    
            value = (value > src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
            }
            if (neighbour > 18)
            {
                value = (value > src[index - dx - dy - dz]) ? value : src[index - dx - dy - dz];
            }
        } 

        dst[index] = value;
    }

    // Corener 3 0 1 0

    {
        mcint64 index = dimY*dy-dy;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index + dx]) ? value : src[index + dx];
            value = (value < src[index - dy]) ? value : src[index - dy];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];            
                value = (value < src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
            }
        } 
        else
        {
            value = (value > src[index + dx]) ? value : src[index + dx];
            value = (value > src[index - dy]) ? value : src[index - dy];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];            
                value = (value > src[index + dx + dz]) ? value : src[index + dx + dz];
                value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index + dx - dy + dz]) ? value : src[index + dx - dy + dz];
            }
        } 

        dst[index] = value;
    }

    // Corener 4 1 0 0
    {
        mcint64 index = dimX-dx;
        Type value = src[index];
        if (maxFilter == 0)
        {

            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];
                value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value < src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];
                value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];
                value = (value > src[index + dy + dz]) ? value : src[index + dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx + dy + dz]) ? value : src[index - dx + dy + dz];
            }
        } 
        dst[index] = value;
    }

    // Corener 5 0 0 1
    {
        mcint64 index = dimZ*dz-dz;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index + dx]) ? value : src[index + dx];                    
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value < src[index + dx + dy]) ? value : src[index + dx + dy];
                value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
            }
        } 
        else
        {
            value = (value > src[index + dx]) ? value : src[index + dx];                    
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value > src[index + dx + dy]) ? value : src[index + dx + dy];
                value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index + dx + dy - dz]) ? value : src[index + dx + dy - dz];
            }

        } 
        dst[index] = value;
    }

    // Corener 6 1 1 0
    {
        mcint64 index = dimY*dy - dy + dimX - dx;
        Type value = src[index];

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];                    
            value = (value < src[index - dy]) ? value : src[index - dy];
            value = (value < src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value < src[index - dx + dz]) ? value : src[index - dx + dz];                    
                value = (value < src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];                    
            value = (value > src[index - dy]) ? value : src[index - dy];
            value = (value > src[index + dz]) ? value : src[index + dz];

            if (neighbour > 6)
            {
                value = (value > src[index - dx - dy]) ? value : src[index - dx - dy];
                value = (value > src[index - dx + dz]) ? value : src[index - dx + dz];                    
                value = (value > src[index - dy + dz]) ? value : src[index - dy + dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx - dy + dz]) ? value : src[index - dx - dy + dz];
            }
        } 
        dst[index] = value;
    }

    // Corener 7 0 1 1
    {
        mcint64 index = dimY*dy - dy + dimZ*dz - dz;
        Type value = src[index];    
        if (maxFilter == 0)
        {
            value = (value < src[index + dx]) ? value : src[index + dx];
            value = (value < src[index - dy]) ? value : src[index - dy];
            value = (value < src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value < src[index + dx - dy]) ? value : src[index + dx - dy];
                value = (value < src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value < src[index - dy - dz]) ? value : src[index - dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
            }
        } 
        else
        {
            value = (value > src[index + dx]) ? value : src[index + dx];
            value = (value > src[index - dy]) ? value : src[index - dy];
            value = (value > src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value > src[index + dx - dy]) ? value : src[index + dx - dy];
                value = (value > src[index + dx - dz]) ? value : src[index + dx - dz];
                value = (value > src[index - dy - dz]) ? value : src[index - dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index + dx - dy - dz]) ? value : src[index + dx - dy - dz];
            }
        } 
        dst[index] = value;
    }

    // Corener 8 1 0 1
    {
        mcint64 index = dimX-dx + dimZ*dz-dz;                
        Type value = src[index]; 

        if (maxFilter == 0)
        {
            value = (value < src[index - dx]) ? value : src[index - dx];
            value = (value < src[index + dy]) ? value : src[index + dy];
            value = (value < src[index - dz]) ? value : src[index - dz];

            if (neighbour > 6)
            {
                value = (value < src[index - dx + dy]) ? value : src[index - dx + dy];
                value = (value < src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value < src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value < src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
            }
        } 
        else
        {
            value = (value > src[index - dx]) ? value : src[index - dx];
            value = (value > src[index + dy]) ? value : src[index + dy];
            value = (value > src[index - dz]) ? value : src[index - dz];


            if (neighbour > 6)
            {
                value = (value > src[index - dx + dy]) ? value : src[index - dx + dy];
                value = (value > src[index - dx - dz]) ? value : src[index - dx - dz];
                value = (value > src[index + dy - dz]) ? value : src[index + dy - dz];
            }

            if (neighbour > 18)
            {
                value = (value > src[index - dx + dy - dz]) ? value : src[index - dx + dy - dz];
            }
        } 
        dst[index] = value;
    }
}
#endif //_IMFILTERMINMAX_H__

/// @}

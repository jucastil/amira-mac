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

/// @addtogroup vsvolren vsvolren
/// @{
#ifndef _VS_FILTER_IMPL_H
#define _VS_FILTER_IMPL_H


#include "VsFilter.h"
#include "VsJobControl.h"
#include "VsImpl.h"

#include <mclib/McString.h>


////////////////////////////////////////////////////////////////////////////////
template <class FILTER>
VsFilter<FILTER>::VsFilter(VsData* data, VsJobControl* control)
{
    mData       = data;    
    mJobControl = control;   
    mComponents = mData->nDataVar();
    mSrcSize    = mData->dims();
}


////////////////////////////////////////////////////////////////////////////////
template <class FILTER>
VsFilter<FILTER>::~VsFilter()
{
    for ( int i=0 ; i<3 ; i++ )
        VS_SAFE_FREE(mContrib[i]->p);
}


////////////////////////////////////////////////////////////////////////////////
/* This method computes an adjusted bounding box for the resampled field. */
template<class FILTER>
void VsFilter<FILTER>::setUniformCoords()
{
    McBox3f coords;
    mData->boundingBox(coords);

    for (int i=0; i<3; i++) 
    {
        // if different dims corr bbox 
        if (fabs(float(mSrcSize[i]) - mFracDstSize[i]) > 1e-10) 
        {
            float* box = &coords[2*i];
            // bbox to pixelbox
            const float pixsizeSrc = (mSrcSize[i] > 1) ? 
                ((box[1] - box[0]) / float(mSrcSize[i]-1)) : (box[1] - box[0]);
            const float pixsizeDst = pixsizeSrc * float(mSrcSize[i]) / mFracDstSize[i];
            const float center = 0.5f * (box[1] + box[0]);
            const float bboxSizeDst = pixsizeDst * float((mDstSize[i] > 1) ? (mDstSize[i] - 1) : 1); 

            box[0] = center - 0.5f * bboxSizeDst;
            box[1] = center + 0.5f * bboxSizeDst;
        }
    }

    mTarget->setBoundingBox(coords);
}


////////////////////////////////////////////////////////////////////////////////
template<class FILTER>
VSRESULT VsFilter<FILTER>::contrib()
{
    for ( int d=0 ; d<3 ; d++ ) 
    {
        int   dstSize = mDstSize[d];
        int   size    = mSrcSize[d];
        float scale   = mScale[d];

        const float phaseShift = 0;

        /* pre-calculate filter contributions for zoom in x,y,z-direction */
        float center;	         	/* filter calculation variables */
        float left, right;			/* filter calculation variables */
        float width, fscale, weight;/* filter calculation variables */
        float area;
        int   i,j,k,n;

        // origin of pixels isn't the same,
        // the center of the bounding boxes must be aligned
        // everthing is measured in old pixelsize
        // first old sample is at 0.
        // 1/scale is the new pixelsize.
        // origCorrection pofloat to the first new sample. 
        const float boxcenter       = 0.5f * (float(size) - 1.0f);
        const float newpixsize      = 1.0f / scale;
        const float newboxsize      = float(dstSize) * newpixsize;
        const float origCorrection  = boxcenter - 0.5f*newboxsize + 0.5f*newpixsize;

        CLIST * contrib = (CLIST*)calloc(dstSize, sizeof(CLIST));

        if (contrib==0)
            VS_FAIL2( Vs::CODE_OUTOFMEMORY, McString(0,"%d",int(dstSize)) );

        if (scale < 1.0f)
        {
            // Decimation
            // FILTER::width() is size on new lattice
            width = FILTER::width() / scale;
            fscale = 1.0f / scale;
            for (i=0; i<dstSize; ++i) 
            {
                contrib[i].n = 0;
                contrib[i].p = (CONTRIB*) calloc((int)(2*(width+1)), sizeof(CONTRIB));
                center  = (float) i / scale + origCorrection + phaseShift / scale;
                left    = (float) ceil(center - width);
                right   = (float) floor(center + width);
                area   = 0;

                for ( j=(int)left ; j<=right ; ++j )
                {
                    weight = center - (float) j;
                    weight = FILTER::filter(weight / fscale) / fscale;
                    if (j<0) 
                    {
                        continue; // border cut off. Don't change without 
                        // changing stacked coord treatment, (zoom1d)
                        n = -j;
                        if (n >= size) 
                        {
                            n = 0;
                        }
                    } 
                    else if ( j >= size ) 
                    {
                        continue; // border cut off. Don't change without 
                        // changing stacked coord treatment, (zoom1d)
                        n = -j;
                        n = (size - j) + size - 1;
                        if (n < 0) 
                        {
                            n = size -1;
                        }
                    } 
                    else 
                    {
                        n = j;
                    }
                    k = contrib[i].n++;
                    // assert((i<dstSize) && (k<(float)(width*2+1)));
                    contrib[i].p[k].pixel = n;
                    area+= (contrib[i].p[k].weight = weight);
                }
                if (!area)
                    continue;
                for ( j=0 ; j<contrib[i].n ; j++ )
                    contrib[i].p[j].weight /= area;
            }
        } 
        else 
        {
            // Interpolation
            // FILTER::width() is size on old lattice
            for ( i=0 ; i<dstSize ; ++i )
            {
                contrib[i].n = 0;
                contrib[i].p = (CONTRIB*) calloc((int)(2*(FILTER::width()+1)), sizeof(CONTRIB));
                center  = (float) i / scale + origCorrection + phaseShift / scale;
                left    = (float) ceil(center - FILTER::width());
                right   = (float) floor(center + FILTER::width());
                area    = 0;

                for ( j=(int)left ; j<=right ; ++j )
                {
                    weight = center - (float) j;
                    weight = FILTER::filter(weight);
                    if (j<0) 
                    {
                        continue; // border cut off. Don't change without 
                        // changing stacked coord treatment, (zoom1d)
                        n = -j;
                        n = -j;
                        if (n >= size) 
                        {
                            n = 0;
                        }
                    } 
                    else if (j>=size) 
                    {
                        continue; // border cut off. Don't change without 
                        // changing stacked coord treatment, (zoom1d)
                        n = -j;
                        n = (size - j) + size - 1;
                        if (n < 0) 
                        {
                            n = size -1;
                        }
                    } 
                    else 
                    {
                        n = j;
                    }
                    k = contrib[i].n++;
                    // assert((i<dstSize) && (k<(float)(FILTER::width()*2+1)));
                    contrib[i].p[k].pixel = n;
                    area += (contrib[i].p[k].weight = weight);
                }
                if (!area)
                    continue;
                for ( j=0 ; j<contrib[i].n ; j++ )
                    contrib[i].p[j].weight/=area;
            }
        }
        mContrib[d] = contrib;
    }
    return VS_OK;
}


////////////////////////////////////////////////////////////////////////////////
template<class FILTER>
void VsFilter<FILTER>::contribNoOverlap()
{
    for ( int d=0 ; d<3 ; d++ )
    {
        int     dstSize = mDstSize[d];
        int     size    = mSrcSize[d];
        float   scale   = 1.0f / mScale[d];

        /* pre-calculate filter contributions for zoom in x,y,z-direction */
        float weight;        /* filter calculation variables */
     
        int i,j,k;

        // origin of pixels isn't the same,
        // the center of the bounding boxes must be aligned
        // everthing is measured in old pixelsize
        // first old sample is at 0.
        // 1/scale is the new pixelsize.
        // origCorrection pofloat to the first new sample. 
       
        CLIST * contrib = (CLIST*) calloc(dstSize, sizeof(CLIST));


        int     width   = (int) (dstSize * scale +1); // max length of contribution
        float   right   = 0;
        float   left    = 0;

        for ( i=0 ; i<dstSize ; ++i )
        {
            contrib[i].n = 0;
            contrib[i].p = (CONTRIB*) calloc( size_t((float)(2*(width+1))), sizeof(CONTRIB));
            left    = right;
            right  += scale;
            
            for ( j=int(left) ; j<right && j<size ; ++j )
            {
                weight                  = 0;            
                k                       = contrib[i].n++;             
                contrib[i].p[k].pixel   = j;
            }
        }
        mContrib[d] = contrib;
    }
}


////////////////////////////////////////////////////////////////////////////////
template<class FILTER>
void VsFilter<FILTER>::zoomRow( int j, int k, float * sourceRow, float * targetRow ) 
{
    float w[4];

    CLIST * contrib = mContrib[0];

    int i,c;

    for ( i=0 ; i<mDstSize[0] ; ++i )
    {
        int iOffset = i * mComponents;
        for ( c=0 ; c<mComponents ; c++ )
            w[c] = FILTER::init();
// check this
        for ( j=0 ; j<contrib[i].n ; ++j ) 
        {
            int ijOffset = contrib[i].p[j].pixel * mComponents;

            for( c=0 ; c<mComponents ; c++ )
            {
                FILTER::eval(sourceRow[ijOffset+c],contrib[i].p[j].weight, w[c]);                   
            }
        }
        for ( c=0 ; c<mComponents ; c++ )
            targetRow[iOffset+c] = w[c];
    }
}


////////////////////////////////////////////////////////////////////////////////
template<class FILTER>
void VsFilter<FILTER>::zoomSlice( int k, float * slice )
{
    bool filtercontrib = true; //tmp

    int i,j, c;

    float * srcPtr    = mRow; // get storage for one row
    float * targetPtr = mSliceX; // storage for intermediate slice

    // for each row
    for ( j=0 ; j< mSrcSize[1] ; j++ )
    {
        mSource->row(-1, j, k, srcPtr);
        zoomRow( j, k, srcPtr, targetPtr);
        targetPtr += mDstSize[0] * mComponents;
    }   

    /// get y contrib
    CLIST * contrib = mContrib[1];

    targetPtr = slice;
    srcPtr    = (float*) mSliceX; 


    float w[4];

    for ( i=0 ; i<mDstSize[0] ; ++i ) 
    {
        for ( j=0 ; j<mDstSize[1] ; ++j ) 
        {
            for ( c=0 ; c<mComponents ; c++ )
                w[c] = FILTER::init();

            if ( filtercontrib ) 
            {
                for ( k=0 ; k<contrib[j].n ; ++k )
                {
                    int j0 = contrib[j].p[k].pixel;

                    for( c=0 ; c<mComponents ; c++ )
                    {
                        FILTER::eval((srcPtr)[(i + mDstSize[0] * j0) * mComponents + c ], contrib[j].p[k].weight, w[c]);
                    }
                }
                for( c=0 ; c<mComponents ; c++ )
                    targetPtr[ (i + mDstSize[0] * j) * mComponents + c]   = w[c];
            }
        }
    }
}     


////////////////////////////////////////////////////////////////////////////////
template<class FILTER>
VSRESULT VsFilter<FILTER>::zoom()
{
    float * destSlice;
    float * rowDest;
    float **sliceList;
	int     i,k,w;

    McDArray< float* > freeSlices;

    /// compute contributions
    if (FILTER::init() != 0) // if min or max filter
    {
        contribNoOverlap();
    }
    else
    {
        if ( VS_OK != contrib() )
            return VS_FAILED;
    }

    // allocate slice storage

    // create a list of pointers to resampled slices
    sliceList = new float*[mSrcSize[2]];
    // and init as empty
    memset(sliceList, 0, sizeof(float*) * mSrcSize[2]);

    /// temporary storage for a single destination slice
    destSlice = new float[ mDstSize[0] * mDstSize[1] * mComponents ]; 
    
    float * rowSource   = 0;
    CLIST * contrib     = mContrib[2];

    // compute range for contributions
    int bmin = contrib[0].n;
    int bmax = contrib[0].n;
    for ( k=0 ; k<mDstSize[2] ; k++ ) 
    {
        if ( contrib[k].n > bmax)
            bmax = contrib[k].n;
        if ( contrib[k].n < bmin)
            bmin = contrib[k].n;
    }


    /// init slice storage and add to list of free slices    
    for ( i=0 ; i<bmax ; i++ ) 
        freeSlices.append( new float[ mDstSize[0] * mDstSize[1] * mComponents] );

    int lowestSlice = 0;

    for ( k=0 ; k<mDstSize[2] ; k++ )
    {
        if (mJobControl)
            mJobControl->progress( k / (float) mDstSize[2] );

        // init destination slice
        for ( i=0 ; i < mDstSize[0] * mDstSize[1] * mComponents ; i++ )
            destSlice[i] = FILTER::init();
        // this is fast, but does not work for min/max: memset(destSlice, 0, mDstSize[0] * mDstSize[1] * mComponents * sizeof(float) );        

        /// free slices that are no longer needed
        int sliceIndex = contrib[k].p[0].pixel;
        for ( w=lowestSlice ; w<sliceIndex ; w++ ) 
        {
            if (sliceList[w])
            {
                freeSlices.append(sliceList[w]);
                sliceList[w] = 0;              
            }
        }
        lowestSlice = sliceIndex;

        for ( w=0 ; w < contrib[k].n ; w++ )
        {
            sliceIndex = contrib[k].p[w].pixel;            

            float * currentSlice = sliceList[sliceIndex];

            if ( ! currentSlice )
            {
                // slice must be computed          
                currentSlice = freeSlices.last(); // retrieve a storage
                freeSlices.removeLast();       
                sliceList[sliceIndex] = currentSlice; // set in list
                zoomSlice( sliceIndex, currentSlice ); // compute
            }

            for ( int j=0 ; j<mDstSize[1] ; j++ )
            {
                rowSource = currentSlice + (j * mDstSize[0]) * mComponents;   
                rowDest  =  destSlice    + (j * mDstSize[0]) * mComponents;

                for ( int i=0 ; i<mDstSize[0] ; i++ )            
                    for ( int c=0 ; c<mComponents ; c++ )
                        FILTER::eval( rowSource[i * mComponents +c], contrib[k].p[w].weight, rowDest[i * mComponents + c] );
            } // end of loop over current slice
        }  // end of loop over kernel


        // write destination slice to target
        for ( int j=0 ; j<mDstSize[1] ; j++ )
            mDest->putRow( -1, j, k, destSlice + j * mDstSize[0] * mComponents );
    } // end of loop over all sices


    for ( i=mSrcSize[2] ; i-- ; )
        VS_SAFE_DELETE_ARR( sliceList[i] );

    for ( i=freeSlices.size() ; i-- ; )
        VS_SAFE_DELETE_ARR( freeSlices[i] );

    delete [] sliceList;           
    delete [] destSlice;

    return VS_OK;
}


////////////////////////////////////////////////////////////////////////////////
template<class FILTER>
VsData * VsFilter<FILTER>::resample(float x, float y, float z) 
{
    VsMemoryData         * result = 0; // the resulting data object
    McHandle<VsMemoryData> target = new VsMemoryData;
    McResult               zoomResult;
	int	i;

    mTarget = target;
    mDest   = 0;
    mSource = 0;

    if (!mTarget)
    {
        VS_ERROR2( Vs::CODE_OUTOFMEMORY, McString(0,"%d bytes",sizeof(VsMemoryData)) );
        goto RESAMPLE_ON_ERROR; // out of mem
    }

    mFracDstSize[0] = x;
    mFracDstSize[1] = y;
    mFracDstSize[2] = z;

    for ( i=0 ; i<3 ; i++ ) 
    {
        mDstSize[i] = int (ceil (mFracDstSize[i]));

        if ( mDstSize[i]==0 || mSrcSize[i]==0 )
        {
            VS_ERROR(Vs::CODE_INVALIDARGUMENT);
            goto RESAMPLE_ON_ERROR;
        }

        mScale[i]  = mFracDstSize[i] / float(mSrcSize[i]);
    }

    if ( VS_OK != target->init( mDstSize, mData->primType(), mData->nDataVar() ) )
        goto RESAMPLE_ON_ERROR;

    setUniformCoords();

    mRow = new float[ mSrcSize[0] * mComponents];
    if ( !mRow )
    {
        VS_ERROR2( Vs::CODE_OUTOFMEMORY, McString(0,"%d bytes", int(sizeof(float) * mSrcSize[0] * mComponents) ) );
        goto RESAMPLE_ON_ERROR; // out of mem
    }
        
    mSliceX = new float[ mDstSize[0] * mSrcSize[1] * mComponents];
    if ( !mSliceX )
    {
        VS_ERROR2( Vs::CODE_OUTOFMEMORY, McString(0,"%d bytes", int(sizeof(float) * mSrcSize[0] * mSrcSize[1] * mComponents) ) );
        goto RESAMPLE_ON_ERROR; // out of mem
    }

    mDest   = mTarget->lock( VsData::P_READWRITE );
    if (!mDest)
        goto RESAMPLE_ON_ERROR;

    mSource = mData->lock( VsData::P_READONLY );
    if (!mSource)
        goto RESAMPLE_ON_ERROR;

    // resample
    if ( VS_OK!=zoom() )
        goto RESAMPLE_ON_ERROR;

    mTarget->ref();
    target = 0;
    mTarget->unrefNoDelete();
    result = mTarget;

RESAMPLE_ON_ERROR:

    if ( mSource )
    {
        mData->unlock( mSource );
        mSource = 0;
    }

    if ( mDest )
    {
        mTarget->unlock( mDest );
        mDest = 0;
    }

    mData   = 0;
    mTarget = 0;

    VS_SAFE_DELETE(mRow);
    VS_SAFE_DELETE(mSliceX);

    return result;
}

#endif

/// @}

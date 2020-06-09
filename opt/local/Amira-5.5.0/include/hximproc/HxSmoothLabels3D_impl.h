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
#ifdef _OPENMP
#  include <omp.h>
#  include <hxcore/HxSettingsMgr.h>
#endif

#include <mclib/McData2D.h>
#include <mclib/McMath.h>
#include <hxcore/HxWorkArea.h>
#include <hxcore/HxMessage.h>
#include <hxfield/HxLattice3.h>
#include <hximproc/convolve.h>

template<class T> HxSmoothLabels3D<T>::HxSmoothLabels3D(
    HxLattice3* r,
    int nm,
    T* l, 
    unsigned char* w,
    unsigned char* smoothMatWeights,
    int smoothMat) :
    mSmoothMatWeights(smoothMatWeights),
    mSmoothMat(smoothMat),
    nMat(nm),
    sizeType(sizeof(T))
{
    result = r;
    labels = l;
    weights = w;

#ifdef _OPENMP
    mNumThreads = theSettingsMgr->getPreferences().maxNumberOfComputeThreads;
    mNumThreads = MC_MAX2(mNumThreads, 1);

    mParallelMaterials = (nMat>=2*mNumThreads);  // ???
    mNumBuffers = mParallelMaterials? mNumThreads: 1;
#else
    mNumThreads=1;
    mParallelMaterials = false;
    mNumBuffers=1;
#endif
}


template<class T>
void HxSmoothLabels3D<T>::createKernel(float kernelSize, float* kernel)
{
    kernel[0] = 1;
    float sum = 1;
    int ksi = (int)(kernelSize+0.5);
    int i;
    for ( i=1; i<ksi; i++) {
	float x = (float)(2*i)/kernelSize;
	kernel[i] = exp(-0.5*x*x);
	sum += 2*kernel[i];
    }

    for ( i=0; i<ksi; i++)
	kernel[i] /= sum;
}



template<class T>
void HxSmoothLabels3D<T>::smoothAll(float kernelS, int constrainLabels, 
				    McBitfield& isLocked,
				    McProgressInterface* progress)
{
    constrained = constrainLabels;

    int slice;

    int ksi = (int) (kernelS+0.5);
    int halfkernel = ksi/2+1;
    const mculong* dims = result->dimsLong();
 
    const mculong nnn = dims[0]*dims[1]*dims[2];

    mculong nSlice = dims[0] * dims[1];

    if (dims[2]==1){
	//smooth(2, 0, kernelSize);
	return;
    }  

    float* kernel = (float*) mcmalloc(ksi*sizeof(float));
    createKernel(kernelS, kernel);

    progress->setProgressInfo("Smoothing labels");
    // Examine which materials really occur in each slice
    // and determine their bounding rectangles

    matFlag.resize(dims[2]);
       
    for (slice=0; slice<dims[2]; slice++) {
	    matFlag[slice].resize(nMat);
        matFlag[slice].fill(0);
    }

    minmaxes.resize(dims[2]);

    for (slice=0; slice<dims[2]; slice++) {
	    minmaxes[slice].resize(nMat);
        for (int mat=0; mat<nMat; mat++) {
	        minmaxes[slice][mat].makeEmpty();
        }
    }
   
    T* dataPtr = 0;
    if (result->isOfType(HxLabelLattice3::getClassTypeId()))
        dataPtr = (T*) ((HxLabelLattice3*) result)->getLabels();
    else dataPtr = (T*) result->dataPtr();

    int smin=0;
    int smax=dims[2];
    for (int slice=smin; slice<smax; slice++) {

	    T* src = dataPtr + slice * nSlice;

        McDArray<McVec2i> xRanges(nMat);
        for (int y=0, i=0; y<dims[1]; y++){
            xRanges.fill(McVec2i(-1,-2));
	        for (int x=0; x<dims[0]; x++, i++){
		        int mat = src[i];

                if (xRanges[mat].x<0)
                    xRanges[mat].x = x;
                xRanges[mat].y = x;
            }
            for (int mat=0; mat<nMat; mat++) {
                if (xRanges[mat].x<=xRanges[mat].y) {
                    matFlag[slice][mat] = 1;

		            // extend corresponding box
		            minmaxes[slice][mat].insert(McVec2i(xRanges[mat].x,y));   
                    if (xRanges[mat].x<xRanges[mat].y)
    		            minmaxes[slice][mat].insert(McVec2i(xRanges[mat].y,y));   
                }
            }
	    }
    	
	    // increase the size of the bounding box by half the kernelsize to each side
	    for (int mat=0; mat<nMat; mat++){
            if (matFlag[slice][mat]) {
	            minmaxes[slice][mat].p1.x-=halfkernel;
	            minmaxes[slice][mat].p1.y-=halfkernel;
	            minmaxes[slice][mat].p2.x+=halfkernel;
	            minmaxes[slice][mat].p2.y+=halfkernel;

	            if (minmaxes[slice][mat].p1.x<0)        minmaxes[slice][mat].p1.x = 0;
	            if (minmaxes[slice][mat].p2.x>=dims[0]) minmaxes[slice][mat].p2.x = dims[0]-1;
	            if (minmaxes[slice][mat].p1.y<0)        minmaxes[slice][mat].p1.y = 0;
	            if (minmaxes[slice][mat].p2.y>=dims[1]) minmaxes[slice][mat].p2.y = dims[1]-1;
            }
	    }
	    //update display
        progress->setProgressValue((float)(slice+1-smin)/(2*MC_MAX2(smax-smin,1)));
        if (progress->wasInterrupted()) {
            mcfree(kernel);
            return;
        }
    }

    for (slice=1; slice<dims[2]; slice++) {
        for (int mat=0; mat<nMat; mat++) {
            if (matFlag[slice][mat]==1 && !matFlag[slice-1][mat]) {
		        matFlag[slice-1][mat] = 2;
            }
        }
    }

    for (slice=dims[2]-2; slice>=0; slice--) {
        for (int mat=0; mat<nMat; mat++) {
            if (matFlag[slice][mat]==1 && !matFlag[slice+1][mat]) {
		        matFlag[slice+1][mat] = 2;
            }
        }
    }

    //create maxboxes (the maximal bounding box for each material) 
    maxboxes.resize(nMat);
    for (int mat=0; mat<nMat; mat++) {
        maxboxes[mat].makeEmpty();
        for (slice=0; slice<dims[2]; slice++) {
            if (matFlag[slice][mat]==1) {
		        maxboxes[mat].extendBy(minmaxes[slice][mat]);
            }
        }
    }
    
    unsigned char* probPtr = weights;

    // erase probabilities for all unlocked materials
    for (mculong i=0; i<nnn; i++)
        probPtr[i] = (isLocked[dataPtr[i]]) ? 255 : 0;

    // reset the weights for the smooth material 
    if (mSmoothMatWeights) {
        for (mculong i=0; i<nnn; i++) {
            mSmoothMatWeights[i] = 0;
        }
    }

    fast3DSmooth(ksi, kernel, isLocked, progress);

    if (mSmoothMatWeights) {
        // define the weights for voxels outside the smooth material
        for (mculong i=0; i<nnn; i++) {
            if (labels[i] != mSmoothMat) {
                mSmoothMatWeights[i] = 255 - mSmoothMatWeights[i];
            }
        }
    }

    mcfree(kernel);
}


template<class T>
void HxSmoothLabels3D<T>::CopyAndSmoothMat(T* src, unsigned char** temp,
					float* kernel, int kernelSize, int slice, int mat,
					unsigned char** buffer, McBitfield& isLocked)
{
    const mculong* dims = result->dimsLong();
    McDArray<T> &flags = matFlag[slice];

#ifdef _OPENMP
    int it = mParallelMaterials? omp_get_thread_num() : 0;
#else
    int it = 0;
#endif

    const McBox2i maxbox = maxboxes[mat];

    if ( !maxbox.isEmpty() ) {
	    memset(temp[mat], 0, maxbox.getSize().x*maxbox.getSize().y * sizeType);
    }

    if (flags[mat]==1 && !isLocked[mat] && !maxbox.isEmpty() ) {
        const McBox2i minmax = minmaxes[slice][mat];

        const int deltaX = minmax.p1.x-maxbox.p1.x;
        const int deltaY = minmax.p1.y-maxbox.p1.y;

        // separate this label

#ifdef _OPENMP
        if (!mParallelMaterials) {
#pragma omp parallel for
            for (int y=minmax.p1.y; y<=minmax.p2.y; y++){
                unsigned char* currentLine = temp[mat] + (y-maxbox.p1.y)*maxbox.getSize().x
                    + deltaX;

                for (int x=minmax.p1.x; x<=minmax.p2.x; x++, currentLine++)
                    *currentLine = (src[dims[0]*y+x]==mat) ? 255 : 0;
            }
        } else 
#endif
        {
            for (int y=minmax.p1.y; y<=minmax.p2.y; y++){
                unsigned char* currentLine = temp[mat] + (y-maxbox.p1.y)*maxbox.getSize().x
                    + deltaX;

                for (int x=minmax.p1.x; x<=minmax.p2.x; x++, currentLine++)
                    *currentLine = (src[dims[0]*y+x]==mat) ? 255 : 0;
            }
        }
	        			
#ifdef _OPENMP
        if (!mParallelMaterials) {
#pragma omp parallel for
            //convolve rows
            for (int y=deltaY; y<=minmax.p2.y-maxbox.p1.y; y++) {

                unsigned char* convsrc = temp[mat]  + y*maxbox.getSize().x + deltaX;
                unsigned char* dst     = buffer[it] + y*maxbox.getSize().x + deltaX;		    

                fastconv( (unsigned char*) convsrc, minmax.getSize().x, 1, (unsigned char*) dst);		
            }
        
        } else
#endif
        {
            //convolve rows
            for (int y=deltaY; y<=minmax.p2.y-maxbox.p1.y; y++) {

                unsigned char* convsrc = temp[mat]  + y*maxbox.getSize().x + deltaX;
                unsigned char* dst     = buffer[it] + y*maxbox.getSize().x + deltaX;		    

                fastconv( (unsigned char*) convsrc, minmax.getSize().x, 1, (unsigned char*) dst);		
            }
        }

#ifdef _OPENMP
        if (!mParallelMaterials) {
#pragma omp parallel for
            //convolve columns
            for (int x=deltaX; x<=minmax.p2.x-maxbox.p1.x; x++) {

                unsigned char* convsrc = buffer[it] + deltaY*maxbox.getSize().x + x;
                unsigned char* dst     = temp[mat]  + deltaY*maxbox.getSize().x + x;

                fastconv((unsigned char*) convsrc, minmax.getSize().y, maxbox.getSize().x, (unsigned char*) dst);	        		
            }

        } else
#endif
        {
            //convolve columns
            for (int x=deltaX; x<=minmax.p2.x-maxbox.p1.x; x++) {

                unsigned char* convsrc = buffer[it] + deltaY*maxbox.getSize().x + x;
                unsigned char* dst     = temp[mat]  + deltaY*maxbox.getSize().x + x;

                fastconv((unsigned char*) convsrc, minmax.getSize().y, maxbox.getSize().x, (unsigned char*) dst);	        		
            }
        }
    }
}

template<class T>
void HxSmoothLabels3D<T>::CopyAndSmooth(T* src, unsigned char** temp,
					float* kernel, int kernelSize, int slice,
					unsigned char** buffer, McBitfield& isLocked)
{    
    if (slice==0)
    	initPackedLuts(kernel, kernelSize);
      //else	  filter.calculateKernel( kernelSize/2.0, kernelSize);

#ifdef _OPENMP
    int numThreadsSav = omp_get_max_threads();
    omp_set_num_threads(mNumThreads);

    if (mParallelMaterials) {
#pragma omp parallel for schedule(static,1)
        // perform the convolution   
        for (int mat=0; mat<nMat; mat++) {
            CopyAndSmoothMat(src, temp, kernel, kernelSize, slice, mat,
                buffer, isLocked);
        }

    } else
#endif
    {
        // perform the convolution   
        for (int mat=0; mat<nMat; mat++) {
            CopyAndSmoothMat(src, temp, kernel, kernelSize, slice, mat,
                buffer, isLocked);
        }
    }

#ifdef _OPENMP
    omp_set_num_threads(numThreadsSav);
#endif
} 


///////////////////////////////////////////////////////////////////////////////////////////
// this routine takes three separated, separately smoothed slices (in temp0, temp1, temp2)
// and computes them into one final slice.
template<class T>
void HxSmoothLabels3D<T>::computeSlice(int slice, unsigned char** temp0,
				  unsigned char** temp1, unsigned char** temp2,
				  McDArray<McBox2i> &boxes0,McDArray<McBox2i> &boxes1,
				  McDArray<McBox2i> &boxes2, McBitfield& isLocked,
                  T* orgLabels)
{
    const mculong* dims = result->dimsLong();
    mculong nn = dims[0]*dims[1];

    T* currentSliceIn  = 0;
    if (result->isOfType(HxLabelLattice3::getClassTypeId()))
        currentSliceIn = (T*) ((HxLabelLattice3*) result)->getLabels() + slice * nn;
    else currentSliceIn = (T*) result->dataPtr() + slice * nn;

    T* currentSliceOut = labels + slice*nn;
    unsigned char* probPtr = weights + slice*nn;
    unsigned char* smoothProbPtr = mSmoothMatWeights + slice*nn;

    if (constrained) {
	    assert(orgLabels);
	    memcpy(orgLabels, currentSliceIn, nn * sizeType);
    }

#ifdef _OPENMP
    int numThreadsSav = omp_get_max_threads();
    omp_set_num_threads(mNumThreads);
#endif
    for (int mat=0; mat<nMat; mat++) {
	    //compute only if material is present in this or the adjacent slices
	    McBox2i maxbox = maxboxes[mat];
	    if (matFlag[slice][mat] && !isLocked[mat] && !maxbox.isEmpty() ){
    	    
	        // compute bounds of the relevant area
	        McBox2i tempBox = boxes0[mat];
    	    tempBox.extendBy(boxes1[mat]);
	        tempBox.extendBy(boxes2[mat]);

            if (!tempBox.isEmpty() ) {

	            unsigned char* mat0 = temp0[mat];
	            unsigned char* mat1 = temp1[mat];
	            unsigned char* mat2 = temp2[mat];
        	    
	            const int deltaX = tempBox.p1.x-maxbox.p1.x;
    	    
#ifdef _OPENMP
#ifndef HX_OS_MACX
#pragma omp parallel for
#endif
#endif
	            for (int y=tempBox.p1.y; y<=tempBox.p2.y; y++) {
        		
		            int pixel = y*dims[0] + tempBox.p1.x;
		            int pixelInTemp = (y-maxbox.p1.y)*maxbox.getSize().x + deltaX;
            		
		            for (int x=tempBox.p1.x; x<=tempBox.p2.x; x++, pixel++, pixelInTemp++){
		                int p = (2*mat0[pixelInTemp] + 5*mat1[pixelInTemp] + 
			                 2*mat2[pixelInTemp])/9;
                        if (mSmoothMatWeights && mSmoothMat==mat) {
                            smoothProbPtr[pixel] = p;
                        }
		                if (p > probPtr[pixel]&&!isLocked[currentSliceIn[pixel]]) {
                            // only relabel if mat!=mSmoothMat to avoid relabeling if p<128; see below
                            if (!mSmoothMatWeights || mSmoothMat!=mat) {
			                    currentSliceOut[pixel] = mat;
			                    probPtr[pixel] = p;
                            }
		                }
		            }
                }
            }
        }
    }

    if (mSmoothMatWeights) {
        // If the probability of the smooth material is >=128, relabel the pixel to
        // mSmoothMat to simulate the presence of just two materials. The probability
        // of all other materials should be < 128 in this case.

        int mat = mSmoothMat;
	    McBox2i maxbox = maxboxes[mat];
	    if (matFlag[slice][mat] && !isLocked[mat] && !maxbox.isEmpty() ){
    	    
	        // compute bounds of the relevant area
	        McBox2i tempBox = boxes0[mat];
    	    tempBox.extendBy(boxes1[mat]);
	        tempBox.extendBy(boxes2[mat]);

            if (!tempBox.isEmpty() ) {
#ifdef _OPENMP
#ifndef HX_OS_MACX
#pragma omp parallel for
#endif
#endif
                for (int y=tempBox.p1.y; y<=tempBox.p2.y; y++) {
	                int pixel = y*dims[0] + tempBox.p1.x;
	                for (int x=tempBox.p1.x; x<=tempBox.p2.x; x++, pixel++) {
                        if (smoothProbPtr[pixel]>=128 && !isLocked[currentSliceOut[pixel]]) {
                            currentSliceOut[pixel] = mSmoothMat;
                        }
                    }
                }
            }
        }
    }

#ifdef _OPENMP
    omp_set_num_threads(numThreadsSav);
#endif

    if (constrained && orgLabels) {
	    T* morg = orgLabels;
	    T* mnew = currentSliceOut;
	    for (mculong i=0; i<nn ; i++, morg++,mnew++) {
	        if (*morg!=*mnew) {
		        *mnew = *morg;
		        probPtr[i] = 128; 
	        }
	    }
    }
}


template<class T>
void HxSmoothLabels3D<T>::fast3DSmooth(int kernelSize, float* kernel, McBitfield& isLocked, McProgressInterface* progress)
{
    const mculong* dims = result->dimsLong();
    const int* dimsInt = result->dimsInt();
    mculong nn = dims[0]*dims[1];

    T* dataPtr = 0;
    if (result->isOfType(HxLabelLattice3::getClassTypeId()))
        dataPtr = (T*) ((HxLabelLattice3*) result)->getLabels();
    else dataPtr = (T*) result->dataPtr();
 
    if (labels != dataPtr)
	memcpy(labels,dataPtr,result->nNodes()*sizeType);

    unsigned char** temp0  = (unsigned char**)mcmalloc(nMat*sizeof(unsigned char*));
    unsigned char** temp1  = (unsigned char**)mcmalloc(nMat*sizeof(unsigned char*));
    unsigned char** temp2  = (unsigned char**)mcmalloc(nMat*sizeof(unsigned char*));
    unsigned char** buffer = (unsigned char**)mcmalloc(mNumBuffers*sizeof(unsigned char*));

    unsigned char** helper;

    for (int i=0; i<nMat; i++){
        if ( maxboxes[i].isEmpty() ) {
            temp0[i] = temp1[i] = temp2[i] = NULL;
        } else {
            temp0[i] = (unsigned char*)mcmalloc(mcuint64(maxboxes[i].getSize().x)*maxboxes[i].getSize().y *sizeType);
            temp1[i] = (unsigned char*)mcmalloc(mcuint64(maxboxes[i].getSize().x)*maxboxes[i].getSize().y *sizeType);
            temp2[i] = (unsigned char*)mcmalloc(mcuint64(maxboxes[i].getSize().x)*maxboxes[i].getSize().y *sizeType);
        }
    }
    
    for (int i=0; i<mNumBuffers; i++){
        buffer[i] = (unsigned char*) mcmalloc(mcuint64(dims[0])*dims[1] * sizeType);
    }

    T* orgLabels = 0;
    if (constrained) {
	    orgLabels = (T*) mcmalloc(mcuint64(dims[0])*dims[1]* sizeType);
    }

    // copy and smooth slice 0 into temp0
    CopyAndSmooth(labels, temp0, kernel, kernelSize, 0, buffer,
		  isLocked);
   
    // copy and smooth slice 1 into temp1   
    CopyAndSmooth(labels+nn, temp1, kernel, kernelSize, 1, buffer,
		  isLocked);

    // use temp0 and temp1 to compute the new slice 0
    computeSlice(0, temp0, temp0, temp1, minmaxes[0], minmaxes[0], minmaxes[1],
		 isLocked, orgLabels);

    // do the rest
    for (int slice=1; slice<dims[2]-1; slice++){

        // copy and smooth new slice into temp2
        CopyAndSmooth(labels+nn*(slice+1), temp2, kernel, kernelSize, slice+1, buffer,
	              isLocked);

        computeSlice(slice, temp0, temp1, temp2, minmaxes[slice-1],
	             minmaxes[slice], minmaxes[slice+1], isLocked, orgLabels);

        //update display
        progress->setProgressValue((float)(slice+1)/(2*dims[2])+0.5);
        if (progress->wasInterrupted())
            break;

        // rearrange temps
        helper = temp2;
        temp2 = temp0;
        temp0 = temp1;
        temp1 = helper;
    }

    // compute the very last slice using temp0 and temp1
    computeSlice(dimsInt[2]-1, temp0, temp1, temp1, minmaxes[dimsInt[2]-2],
		 minmaxes[dimsInt[2]-1], minmaxes[dimsInt[2]-1], isLocked, orgLabels);

    if (constrained && orgLabels) {
	    mcfree(orgLabels);
    }

    for (int i=0; i<nMat; i++){
	    mcfree(temp0[i]);
	    mcfree(temp1[i]);
	    mcfree(temp2[i]);
    }
    for (int i=0; i<mNumBuffers; i++) {
        mcfree(buffer[i]);
    }
    mcfree(temp0);   mcfree(temp1);   mcfree(temp2);  mcfree(buffer);
}




/// @}

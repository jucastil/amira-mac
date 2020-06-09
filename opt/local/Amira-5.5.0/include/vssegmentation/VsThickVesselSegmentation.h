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

/// @addtogroup vssegmentation vssegmentation
/// @{
#ifndef VS_THICK_VESSEL_SEGMENTATION_H
#define VS_THICK_VESSEL_SEGMENTATION_H

#include "VsSegmentationAPI.h"
#include "VsVesselSegmentation.h"

#ifdef USE_IN_AMIRA_MODULE
#else
#include <vsvolren/VsDataAccess.h>
#endif

#include <vsvolren/Vs.h>
#include <vsvolren/VsInterface.h>
#include <vsvolren/VsRelay.h>

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <mclib/McWatch.h>


typedef unsigned short COSTTYPE;
typedef unsigned short DISTTYPE;
typedef unsigned short BUCKETS;

// VS_RELAY_CLASS VsThickVesselSegmentation VsVesselSegmentationRelay

class VSSEGMENTATION_API VsThickVesselSegmentation : public VsVesselSegmentation
{

    VS_DECL_INTERFACE        ( VsThickVesselSegmentation )
    VS_DECL_INTERFACE_FACTORY( VsThickVesselSegmentation )
    VS_DECL_INTERFACE_RELAY  ( VsThickVesselSegmentation )

    static const COSTTYPE SINFI = 65534;
    static const DISTTYPE DISTMAX = 65534;
    static const BUCKETS NBUCKETS = 1000;


public:

    VsThickVesselSegmentation( VsMeta * inMeta = 0 );
    virtual ~VsThickVesselSegmentation();

    void setThresholdFill(int value); // VS_RELAY
    int  thresholdFill() const { return mFillThreshold;}; // LOCAL_GET
    void setThresholdGrow(int value); // VS_RELAY
    int  thresholdGrow() const { return mGrowThreshold;};  // LOCAL_GET

    
    virtual VSRESULT compute(int inNumberOfPoints, const McVec3f * inPoints); // VS_SYNC_CALL
    virtual VSRESULT getResult(VsVolume* volume, McBox3i& box, int materialIdx); // VS_SYNC_CALL
    virtual VSRESULT setVolume(VsVolume *vol); // VS_RELAY

private:
   
    int mSDims[3];
    McDArray<mculong> mFronts[NBUCKETS];
    McDArray<COSTTYPE*> mCostBricks;
    McDArray<DISTTYPE*> mDfBricks;
    McDArray<McBitfield*> mFillBricks;
    McDArray<McBitfield*> mResultBricks;

    int mSNNN;
    int mDims01;
    int mFillThreshold, mGrowThreshold;

#ifdef USE_IN_AMIRA_MODULE
    short* dataPtr;
    inline int dataVal(mculong idx) {
        return dataPtr[idx];
    }
    inline int dataVal(int i, int j, int k) {
        mculong idx = i+(j+k*dims[1])*dims[0];
        return dataPtr[idx];
    }
#else
    const VsDataAccess* dataPtr;
    void setDataAccess(const VsDataAccess* dataPtr_) { dataPtr = dataPtr_; }
    
    template<class T> inline int dataVal(mculong idx) {
        int k =  idx / (mDims01);
        int j = (idx - (mDims01*k))/mDims[0];
        int i =  idx - (mDims[0]*(j+mDims[1]*k));
        return *(T*)dataPtr->dataPtr(i,j,k);
    }
    
    template<class T> inline int dataVal(int i, int j, int k) {
        return *(T*)dataPtr->dataPtr(i,j,k);
    }
#endif
    
    // core method
    template<class T> bool computeVesselSeg(const McVec3f &pos, const McVec3f &pos2, int growThreshold, int dmin, int dmax, McDArray<McVec3f> &path);
    
    template<class T> bool floodfill(int threshold, int threshold2, int maxthick, McDArray<mculong>& path);
    template<class T> bool floodfill(int threshold1, int threshold2, McBox3i bbox, mculong startidx, mculong endidx); 
    template<class T> bool grow(int threshold1, int threshold2, int niter);

    void initDf();
    int  computeDF(mculong& maxidx,int bdfmax=0, int maxdist=0);
    int  walkback(mclong cnt, mclong endidx, McDArray<mculong>& way);
    void copyDfToCosts();
    
    void clear();

    inline int dist(int di,int dj,int dk) {
        int d = (di!=0) + (dj!=0) + (dk!=0) + 2; // 3,4,5 norm
        return d;
    }

    void brickedIndex(const mculong& idx, unsigned int& brickIdx) const {
        int k = idx/ (mDims01);
        int j = (idx - (mDims01*k))/mDims[0];
        int i =  idx - (mDims[0]*(j+mDims[1]*k));
        brickIdx = (k/32*mSDims[1]+j/32)*mSDims[0]+i/32;
    }

    void linearIndexToBrickedIndex(const mculong& idx, unsigned int& brickIdx, unsigned int& sidx) const {
        int k = idx/ (mDims01);
        int j = (idx - (mDims01*k))/mDims[0];
        int i =  idx - (mDims[0]*(j+mDims[1]*k));
        brickIdx = (k/32*mSDims[1]+j/32)*mSDims[0]+i/32;
        i &= 0x1f; // k = k % 32
        j &= 0x1f; // k = k % 32
        k &= 0x1f; // k = k % 32
        sidx = (k*32+j)*32+i;
    }

    void brickIndexToLinearIndex(unsigned int brickIdx, unsigned int sidx, mculong& idx) {
        int bk = brickIdx / (mSDims[0]*mSDims[1]);
        int bj = (brickIdx - (mSDims[0]*mSDims[1]*bk))/mSDims[0];
        int bi =  brickIdx - (mSDims[0]*(bj+mSDims[1]*bk));
        int sk = sidx/ (32*32);
        int sj = (sidx - (32*32*sk))/32;
        int si =  sidx - (32*(sj+32*sk));
        idx = bi*32+si + ( mDims[0]* ((bj*32+sj) + (bk*32+sk)*mDims[1]));
    }

    void index3ToBrickedIndex(int i, int j, int k, unsigned int& brickIdx, unsigned int& sidx) {
        brickIdx = (k/32*mSDims[1]+j/32)*mSDims[0]+i/32;
        i &= 0x1f; // k = k % 32
        j &= 0x1f; // k = k % 32
        k &= 0x1f; // k = k % 32
        sidx = (k*32+j)*32+i;
    }

    bool isFilled(int i, int j, int k) {
        unsigned int brickIdx;
        unsigned int sidx;
        index3ToBrickedIndex(i,j,k,brickIdx,sidx);
        if (!mFillBricks[(int)brickIdx])
            return false;
        return (*mFillBricks[(int)brickIdx])[sidx];        
    }

    void setFilled(int i, int j, int k) {
        unsigned int brickIdx;
        unsigned int sidx;
        index3ToBrickedIndex(i,j,k,brickIdx,sidx);
        if (!mFillBricks[(int)brickIdx])
            allocateFillBrick(brickIdx);

        mFillBricks[(int)brickIdx]->set(sidx);
    }

    bool isFilled(mculong idx) const {
        unsigned int brickIdx;
        unsigned int sidx;
        linearIndexToBrickedIndex(idx,brickIdx,sidx);
        if (!mFillBricks[(int)brickIdx])
            return false;
        return (*mFillBricks[(int)brickIdx])[sidx];        
    }

    bool isFilled(unsigned int sidx, unsigned int brickIdx) const {
        //if (!mFillBricks[(int)brickIdx])
        //    return false;
        return (*mFillBricks[(int)brickIdx])[sidx];  
    }

    void setFilled(unsigned int sidx, unsigned int brickIdx) {
        mFillBricks[(int)brickIdx]->set(sidx);
    }

    void setFilled(mculong idx) {
        unsigned int brickIdx;
        unsigned int sidx;
        linearIndexToBrickedIndex(idx,brickIdx,sidx);
        if (!mFillBricks[(int)brickIdx])
            allocateFillBrick(brickIdx);

        mFillBricks[(int)brickIdx]->set(sidx);
    }
    void allocateFillBrick(int brickIdx) {
        mFillBricks[brickIdx] = new McBitfield(32*32*32);
        mFillBricks[brickIdx]->clearAll();
    }

    void clearFronts() {
        for (int i=0 ; i<NBUCKETS ; i++) {
            mFronts[i].resize(0);
        }
    }
    void clearFilled() {
        for (int ii=0 ; ii<mFillBricks.size() ; ii++) {
            if (mFillBricks[ii]) {
                mFillBricks[ii]->unsetAll();
            }
        }
    }

    void clearCosts() {
        for (int ii=0 ; ii<mCostBricks.size() ; ii++) {
            if (mCostBricks[ii]) {
                for (int i=0 ; i<32*32*32 ; i++) {
                    mCostBricks[ii][i] = SINFI;
                }
            }
        }
    }

    void clearDf() {
        for (int ii=0 ; ii<mDfBricks.size() ; ii++) {
            if (mFillBricks[ii] && !mDfBricks[ii]) {
                allocateDfBrick(ii);
            }
            if (mDfBricks[ii]) {
                for (int i=0 ; i<32*32*32 ; i++) {
                    mDfBricks[ii][i] = DISTMAX;
                }
            }
        }
    }

    void allocateCostBrick(int brickIdx) {
        mCostBricks[brickIdx] = (COSTTYPE*) malloc(32*32*32*sizeof(COSTTYPE));
        for (int i=0 ; i<32*32*32 ; i++) {
            mCostBricks[brickIdx][i] = SINFI;
        }
    }
    COSTTYPE& costs(mculong idx) {
        unsigned int brickIdx;
        unsigned int sidx;
        linearIndexToBrickedIndex(idx,brickIdx,sidx);
        if (!mCostBricks[(int)brickIdx]) {
            allocateCostBrick(brickIdx);
        }
        return mCostBricks[(int)brickIdx][sidx]; 
    }   

    COSTTYPE& costs(unsigned int sidx, unsigned int brickIdx) {
        //if (!mCostBricks[(int)brickIdx]) {
        //    allocateCostBrick(brickIdx);
        //}
        return mCostBricks[(int)brickIdx][sidx]; 
    }

    void allocateDfBrick(int brickIdx) {
        mDfBricks[brickIdx] = (DISTTYPE*) mcmalloc(32*32*32*sizeof(DISTTYPE));
        for (int i=0 ; i<32*32*32 ; i++) {
            mDfBricks[brickIdx][i] = 0;
        }
    }

    DISTTYPE& df(mculong idx) {
        unsigned int brickIdx;
        unsigned int sidx;
        linearIndexToBrickedIndex(idx,brickIdx,sidx);
        if (!mDfBricks[(int)brickIdx]) {
            allocateDfBrick(brickIdx);
        }
        return mDfBricks[(int)brickIdx][sidx]; 
    }

    DISTTYPE& df(unsigned int sidx, unsigned int brickIdx) {
        //if (!mDfBricks[(int)brickIdx]) {
        //    allocateDfBrick(brickIdx);
        //}
        return mDfBricks[(int)brickIdx][sidx];
    }

};

#endif


/// @}

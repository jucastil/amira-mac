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
#ifndef VSSPARSEDATA_H
#define  VSSPARSEDATA_H

#include "VsSegmentationAPI.h"

#ifdef USE_IN_AMIRA_MODULE
#else
#include <vsvolren/VsDataAccess.h>
#endif

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>

template<class T>
class VsSparseData {

public:

    VsSparseData(const McVec3l& dims)
        :mDims(dims),
        mDefault(0)
    {   
        mDims01=mDims[0]*mDims[1];
        for (int i=0 ; i<3 ; i++) msDims[i] = (mDims[i]+32-1)/32;
        mSnnn = msDims[0]*msDims[1]*msDims[2];

        mBricks.resize(mSnnn);
        mBricks.fill(0);
}

    VsSparseData(const VsSparseData& other) 
    {

        mDims = other.mDims;
        msDims[0] = other.msDims[0];
        msDims[1] = other.msDims[1];
        msDims[2] = other.msDims[2];

        mSnnn = other.mSnnn;
        mDims01 = other.mDims01;

        mBricks.resize(mSnnn);
        mBricks.fill(0);

        for (int i=0; i<mBricks.size(); ++i) {
            if (other.dfBricks[i]) {
                allocateBrick(i);
                for (int j=0; j<32*32*32; ++j) {
                    mBricks[i][j] = other.mBricks[i][j];
                }
            }
    }
    }

    VsSparseData& operator=(const VsSparseData& other) 
    {
        // Self assignment?
        if (this==&other)
            return *this;

        // clean superfluous memory
        for (int i=mSnnn; i<mBricks.size(); ++i) 
            if (mBricks[i])
                delete mBricks[i];

        mDims = other.mDims;

        msDims[0] = other.msDims[0];
        msDims[1] = other.msDims[1];
        msDims[2] = other.msDims[2];

        mSnnn = other.mSnnn;
        mDims01 = other.mDims01;

        mBricks.resize(mSnnn);



        for (int i=0; i<mBricks.size(); ++i) {
            if (mBricks[i] && !other.mBricks[i]) {
                free(mBricks[i]);
                mBricks[i] = 0;
            }
            if (!mBricks[i] && other.mBricks[i]) {
                allocateBrick(i);
        }
            if (other.mBricks[i]) {
                for (int j=0; j<32*32*32; ++j) {
                    mBricks[i][j] = other.mBricks[i][j];
    }
                }
            }
        
        return *this;
        }

    ~VsSparseData()
    {
        for (int i=0; i<mBricks.size(); ++i) 
            if (mBricks[i])
                free(mBricks[i]);   
    }


    void resize(McVec3l& dims)
    {
        // clean superfluous memory
        for (int i=0; i<mBricks.size(); ++i) 
            if (mBricks[i])
                free(mBricks[i]);  
        
        mDims = dims;
        mDims01=mDims[0]*mDims[1];
        for (int i=0 ; i<3 ; i++) msDims[i] = (mDims[i]+32-1)/32;
        mSnnn = msDims[0]*msDims[1]*msDims[2];
     
        mBricks.resize(mSnnn);
        mBricks.fill(0);
        }

    McVec3l dims() const 
    {
        return mDims;
    }
    
    //void fill(const T& value);

    const T& defaultValue() const 
    {
        return mDefault;
        }

    void setDefaultValue(const T& value) {
        mDefault = value;
    }   

    //const T& get(int i, int j, int k) const;
    //void set(int i, int j, int k, const T& value);
    //const T& get(mclong idx) const;
    //void set(mclong idx, const T& value);

    void allocateBrick(int brickIdx) {
        mBricks[brickIdx] = (T*) mcmalloc(32*32*32*sizeof(T));
        for (int i=0 ; i<32*32*32 ; i++) {
            mBricks[brickIdx][i] = mDefault;
        }
    }

    void setAll(const T& value) {
        for (int ii=0 ; ii<mBricks.size() ; ii++) {
            if (mBricks[ii]) {
        for (int i=0 ; i<32*32*32 ; i++) {
                    mBricks[ii][i] = value;
                }
            }
        }
    }

    T& get(mculong idx) {
        unsigned int brickIdx;
        unsigned int sidx;
        linearIndexToBrickedIndex(idx,brickIdx,sidx);
        if (!mBricks[(int)brickIdx]) {
            allocateBrick(brickIdx);
        }
        return mBricks[(int)brickIdx][sidx]; 
    }

    T& get(unsigned int sidx, unsigned int brickIdx) {
        //if (!dfBricks[(int)brickIdx]) {
        //    allocateDfBrick(brickIdx);
        //}
        return mBricks[(int)brickIdx][sidx];
    }

    // void getFilledVoxelBox(McBox3i& box);
    //void getFilledBrickBox(McBox3i& box);

    // + index methods ?
    void linearIndexToBrickedIndex(const mculong& idx, unsigned int& brickIdx, unsigned int& sidx) const 
    {
            int k = idx/ (mDims01);
            int j = (idx - (mDims01*k))/mDims[0];
            int i =  idx - (mDims[0]*(j+mDims[1]*k));
            brickIdx = (k/32*msDims[1]+j/32)*msDims[0]+i/32;
            i &= 0x1f; // k = k % 32
            j &= 0x1f; // k = k % 32
            k &= 0x1f; // k = k % 32
            sidx = (k*32+j)*32+i;
    }


    McDArray<T*> mBricks;

private:
    // dims of the volume
    McVec3l mDims;
    int mDims01; // one slice
    
    // dims of bricks representing the volume
    McVec3i msDims;
    int mSnnn; // max bricks
    T mDefault; 
};





//class VSSEGMENTATION_API VsSparseData {
//
//private:
//    static const COSTTYPE SINFI = 65534;
//    static const DISTTYPE DISTMAX = 65534;
//    static const unsigned short NBUCKETS = 1000;
//public:
//    McVec3f bbo,bbs;
//    int dims[3];
//    int sdims[3];
//    
//    McDArray<COSTTYPE*> costBricks; // VsSparseD
//    McDArray<DISTTYPE*> dfBricks;
//    McDArray<McBitfield*> fillBricks;
//
//    int snnn;
//    int dims01;
//    VsSparseData(const VsSparseData&); // non trivial, don't forget to change when changing members
//    VsSparseData& operator=(const VsSparseData&); // law of the big three: operator= also required
//    ~VsSparseData();
//
//#ifdef USE_IN_AMIRA_MODULE
//    short* dataPtr;
//    VsSparseData(const int* dims, const McVec3f& bbo_, const McVec3f& bbs_, short* dataPtr);
//    inline int dataVal(mculong idx) {
//        return dataPtr[idx];
//    }
//    inline int dataVal(int i, int j, int k) {
//        mculong idx = i+(j+k*dims[1])*dims[0];
//        return dataPtr[idx];
//    }
//#else
//    const VsDataAccess* dataPtr;
//    VsSparseData(int* dims, const McVec3f& bbo_, const McVec3f& bbs_);
//    void setDataAccess(const VsDataAccess* dataPtr_) { dataPtr = dataPtr_; }
//
//    inline int dataVal(mculong idx) {
//        int k =  idx / (dims01);
//        int j = (idx - (dims01*k))/dims[0];
//        int i =  idx - (dims[0]*(j+dims[1]*k));
//        return *(unsigned short*)dataPtr->dataPtr(i,j,k);
//    }
//    inline int dataVal(int i, int j, int k) {
//        return *(unsigned short*)dataPtr->dataPtr(i,j,k);
//    }
//#endif
//
//    void getCosts(unsigned short* data);
//
//    void copyDfToCosts();
//    void addDfToCosts(int maxval);
//
//    void getFilled(unsigned char* data, int dist=0);
//    void getDist(unsigned short* data);
//
//    void clear();
//
//    void brickedIndex(const mculong& idx, unsigned int& brickIdx) const {
//        int k = idx/ (dims01);
//        int j = (idx - (dims01*k))/dims[0];
//        int i =  idx - (dims[0]*(j+dims[1]*k));
//        brickIdx = (k/32*sdims[1]+j/32)*sdims[0]+i/32;
//    }
//
//    void linearIndexToBrickedIndex(const mculong& idx, unsigned int& brickIdx, unsigned int& sidx) const {
//        int k = idx/ (dims01);
//        int j = (idx - (dims01*k))/dims[0];
//        int i =  idx - (dims[0]*(j+dims[1]*k));
//        brickIdx = (k/32*sdims[1]+j/32)*sdims[0]+i/32;
//        i &= 0x1f; // k = k % 32
//        j &= 0x1f; // k = k % 32
//        k &= 0x1f; // k = k % 32
//        sidx = (k*32+j)*32+i;
//    }
//
//    void brickIndexToLinearIndex(unsigned int brickIdx, unsigned int sidx, mculong& idx) {
//        int bk = brickIdx / (sdims[0]*sdims[1]);
//        int bj = (brickIdx - (sdims[0]*sdims[1]*bk))/sdims[0];
//        int bi =  brickIdx - (sdims[0]*(bj+sdims[1]*bk));
//        int sk = sidx/ (32*32);
//        int sj = (sidx - (32*32*sk))/32;
//        int si =  sidx - (32*(sj+32*sk));
//        idx = bi*32+si + ( dims[0]* ((bj*32+sj) + (bk*32+sk)*dims[1]));
//    }
//
//    void index3ToBrickedIndex(int i, int j, int k, unsigned int& brickIdx, unsigned int& sidx) {
//        brickIdx = (k/32*sdims[1]+j/32)*sdims[0]+i/32;
//        i &= 0x1f; // k = k % 32
//        j &= 0x1f; // k = k % 32
//        k &= 0x1f; // k = k % 32
//        sidx = (k*32+j)*32+i;
//    }
//
//    bool isFilled(int i, int j, int k) {
//        unsigned int brickIdx;
//        unsigned int sidx;
//        index3ToBrickedIndex(i,j,k,brickIdx,sidx);
//        if (!fillBricks[(int)brickIdx])
//            return false;
//        return (*fillBricks[(int)brickIdx])[sidx];        
//    }
//
//    void setFilled(int i, int j, int k) {
//        unsigned int brickIdx;
//        unsigned int sidx;
//        index3ToBrickedIndex(i,j,k,brickIdx,sidx);
//        if (!fillBricks[(int)brickIdx])
//            allocateFillBrick(brickIdx);
//
//        fillBricks[(int)brickIdx]->set(sidx);
//    }
//
//    bool isFilled(mculong idx) const {
//        unsigned int brickIdx;
//        unsigned int sidx;
//        linearIndexToBrickedIndex(idx,brickIdx,sidx);
//        if (!fillBricks[(int)brickIdx])
//            return false;
//        return (*fillBricks[(int)brickIdx])[sidx];        
//    }
//
//    bool isFilled(unsigned int sidx, unsigned int brickIdx) const {
//        //if (!fillBricks[(int)brickIdx])
//        //    return false;
//        return (*fillBricks[(int)brickIdx])[sidx];  
//    }
//
//    void setFilled(unsigned int sidx, unsigned int brickIdx) {
//        fillBricks[(int)brickIdx]->set(sidx);
//    }
//
//    void setFilled(mculong idx) {
//        unsigned int brickIdx;
//        unsigned int sidx;
//        linearIndexToBrickedIndex(idx,brickIdx,sidx);
//        if (!fillBricks[(int)brickIdx])
//            allocateFillBrick(brickIdx);
//
//        fillBricks[(int)brickIdx]->set(sidx);
//    }
//    void allocateFillBrick(int brickIdx) {
//        fillBricks[brickIdx] = new McBitfield(32*32*32);
//        fillBricks[brickIdx]->clearAll();
//    }
//
//    void clearFilled() {
//        for (int ii=0 ; ii<fillBricks.size() ; ii++) {
//            if (fillBricks[ii]) {
//                fillBricks[ii]->unsetAll();
//            }
//        }
//    }
//
//    void clearCosts() {
//        for (int ii=0 ; ii<costBricks.size() ; ii++) {
//            if (costBricks[ii]) {
//                for (int i=0 ; i<32*32*32 ; i++) {
//                    costBricks[ii][i] = SINFI;
//                }
//            }
//        }
//    }
//    void clearDf() {
//        for (int ii=0 ; ii<dfBricks.size() ; ii++) {
//            if (fillBricks[ii] && !dfBricks[ii]) {
//                allocateDfBrick(ii);
//            }
//            if (dfBricks[ii]) {
//                for (int i=0 ; i<32*32*32 ; i++) {
//                    dfBricks[ii][i] = DISTMAX;
//                }
//            }
//        }
//    }
//
//    void allocateCostBrick(int brickIdx) {
//        costBricks[brickIdx] = (COSTTYPE*) malloc(32*32*32*sizeof(COSTTYPE));
//        for (int i=0 ; i<32*32*32 ; i++) {
//            costBricks[brickIdx][i] = SINFI;
//        }
//    }
//    COSTTYPE& costs(mculong idx) {
//        unsigned int brickIdx;
//        unsigned int sidx;
//        linearIndexToBrickedIndex(idx,brickIdx,sidx);
//        if (!costBricks[(int)brickIdx]) {
//            allocateCostBrick(brickIdx);
//        }
//        return costBricks[(int)brickIdx][sidx]; 
//    }   
//
//    COSTTYPE& costs(unsigned int sidx, unsigned int brickIdx) {
//        //if (!costBricks[(int)brickIdx]) {
//        //    allocateCostBrick(brickIdx);
//        //}
//        return costBricks[(int)brickIdx][sidx]; 
//    }
//
//    void allocateDfBrick(int brickIdx) {
//        dfBricks[brickIdx] = (DISTTYPE*) mcmalloc(32*32*32*sizeof(DISTTYPE));
//        for (int i=0 ; i<32*32*32 ; i++) {
//            dfBricks[brickIdx][i] = 0;
//        }
//    }
//
//    DISTTYPE& df(mculong idx) {
//        unsigned int brickIdx;
//        unsigned int sidx;
//        linearIndexToBrickedIndex(idx,brickIdx,sidx);
//        if (!dfBricks[(int)brickIdx]) {
//            allocateDfBrick(brickIdx);
//        }
//        return dfBricks[(int)brickIdx][sidx]; 
//    }
//
//    DISTTYPE& df(unsigned int sidx, unsigned int brickIdx) {
//        //if (!dfBricks[(int)brickIdx]) {
//        //    allocateDfBrick(brickIdx);
//        //}
//        return dfBricks[(int)brickIdx][sidx];
//    }
//
//    void initDf(DISTTYPE init) {
//        for (int ii=0 ; ii<dfBricks.size() ; ii++) {
//            if (fillBricks[ii] && !dfBricks[ii]) {
//                allocateDfBrick(ii);
//            }
//            if (dfBricks[ii]) {
//                for (int i=0 ; i<32*32*32 ; i++) {
//                    dfBricks[ii][i] = init;
//                }
//            }
//        }
//    }
//};


#endif

/// @}

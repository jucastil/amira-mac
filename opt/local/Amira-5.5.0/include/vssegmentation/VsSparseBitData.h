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
#ifndef VSSPARSEBITDATA_H
#define  VSSPARSEBITDATA_H

#include "VsSegmentationAPI.h"

#include <vsvolren/VsDataAccess.h>
#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
//#include <stdexcept>
//#include <iterator>



class VSSEGMENTATION_API VsSparseBitData {

private:
   
    bool mDefault;

    // dims of the volume
    McVec3l mDims;
    int mDims01; // one slice
    
    // dims of bricks representing the volume
    McVec3i msDims;
    int mSnnn; // max bricks
    
    

public:
    
    // sparse data structure
    McDArray<McBitfield*> mBricks;

    VsSparseBitData(const McVec3l& dims);
    VsSparseBitData(const VsSparseBitData&); 
    VsSparseBitData& operator=(const VsSparseBitData&); 

    ~VsSparseBitData();
    
    void allocateBrick(int brickIdx);

    void resize(McVec3l& dims);
    McVec3l dims() const {return mDims;};

    bool defaultValue() const {return mDefault;};
    void setDefaultValue(bool value);
    
    void setAll(bool& value);

    bool get(unsigned int i, unsigned int j, unsigned int k);
    void set(unsigned int i, unsigned int j, unsigned int k, bool value);
    
    bool get(mculong idx) const;
    void set(mculong idx, bool value);
    
    // optimized version no checks are performed
    bool get(unsigned int brickIdx, unsigned int innerBrickIdx) const;
    void set(unsigned int innerBrickIdx, unsigned int brickIdx, bool value);

    //void getFilledVoxelBox(McBox3i& box);
    //void getFilledBrickBox(McBox3i& box);

    // index methods
    void brickedIndex(const mculong& idx, unsigned int& brickIdx) const;
    void brickIndexToLinearIndex(unsigned int brickIdx, unsigned int sidx, mculong& idx);
    void linearIndexToBrickedIndex(const mculong& idx, unsigned int& brickIdx, unsigned int& sidx) const;
    void index3ToBrickedIndex(int i, int j, int k, unsigned int& brickIdx, unsigned int& sidx);
    
};

// index transforms
inline void VsSparseBitData::brickedIndex(const mculong& idx, unsigned int& brickIdx) const {
        int k = idx/ (mDims01);
        int j = (idx - (mDims01*k))/mDims[0];
        int i =  idx - (mDims[0]*(j+mDims[1]*k));
        brickIdx = (k/32*msDims[1]+j/32)*msDims[0]+i/32;
    }

inline void VsSparseBitData::brickIndexToLinearIndex(unsigned int brickIdx, unsigned int sidx, mculong& idx) 
{
        int bk = brickIdx / (msDims[0]*msDims[1]);
        int bj = (brickIdx - (msDims[0]*msDims[1]*bk))/msDims[0];
        int bi =  brickIdx - (msDims[0]*(bj+msDims[1]*bk));
        int sk = sidx/ (32*32);
        int sj = (sidx - (32*32*sk))/32;
        int si =  sidx - (32*(sj+32*sk));
        idx = bi*32+si + ( mDims[0]* ((bj*32+sj) + (bk*32+sk)*mDims[1]));
}

inline void VsSparseBitData::linearIndexToBrickedIndex(const mculong& idx, unsigned int& brickIdx, unsigned int& sidx) const 
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

inline void VsSparseBitData::index3ToBrickedIndex(int i, int j, int k, unsigned int& brickIdx, unsigned int& sidx) 
{
        brickIdx = (k/32*msDims[1]+j/32)*msDims[0]+i/32;
        i &= 0x1f; // k = k % 32
        j &= 0x1f; // k = k % 32
        k &= 0x1f; // k = k % 32
        sidx = (k*32+j)*32+i;
}

// getter
inline bool VsSparseBitData::get(unsigned int i, unsigned int j, unsigned int k) 
{
        unsigned int brickIdx;
        unsigned int sidx;
        index3ToBrickedIndex(i,j,k,brickIdx,sidx);
        if (!mBricks[(int)brickIdx])
            return false;
        return (*mBricks[(int)brickIdx])[sidx];        
}

inline bool VsSparseBitData::get(mculong idx) const 
{
    unsigned int brickIdx;
    unsigned int sidx;
    linearIndexToBrickedIndex(idx,brickIdx,sidx);
    if (!mBricks[(int)brickIdx])
        return false;
    return (*mBricks[(int)brickIdx])[sidx];        
}

inline bool VsSparseBitData::get(unsigned int sidx, unsigned int brickIdx) const 
{
    return (*mBricks[(int)brickIdx])[sidx];  
}

// setter
inline  void VsSparseBitData::set(unsigned int i, unsigned int j, unsigned int k, bool value) 
{
    unsigned int brickIdx;
    unsigned int sidx;
    index3ToBrickedIndex(i,j,k,brickIdx,sidx);
    if (!mBricks[(int)brickIdx])
        allocateBrick(brickIdx);
    if(value)
        mBricks[(int)brickIdx]->set(sidx);
    else 
       mBricks[(int)brickIdx]->unset(sidx);
}
inline void VsSparseBitData::set(mculong idx, bool value)
{
    unsigned int brickIdx;
    unsigned int sidx;
    linearIndexToBrickedIndex(idx,brickIdx,sidx);
    if (!mBricks[(int)brickIdx])
        allocateBrick(brickIdx);

    if(value)
        mBricks[(int)brickIdx]->set(sidx);
    else 
       mBricks[(int)brickIdx]->unset(sidx);
}

inline void VsSparseBitData::set(unsigned int sidx, unsigned int brickIdx, bool value) 
{
    if(value)
        mBricks[(int)brickIdx]->set(sidx);
    else 
       mBricks[(int)brickIdx]->unset(sidx);
}

#endif


/// @}

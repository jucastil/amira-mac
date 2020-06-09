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
#ifndef _VS_THICK_SLICE_IMPL_H
#define _VS_THICK_SLICE_IMPL_H

#include "VsDataAccess.h"
#include "VsObject.h"

/*
   This is an internal helper modul that provides functionality for
   extracting thick slice information. It should never be part of
   an external release, which means that it should only be included
   within .cpp files.
*/


////////////////////////////////////////////////////////////////////////////////
/**
   ThickFunctor is the base class for handling different combination 
   modes like Maximum Intensity Projection or Averaging.
   The correct way to use the functor consists of the following steps:
   
   1. Construct
      using the specific constructor

   2. Initialize
      extract the first slice by calling ThickFunctor::init() for each 
      pixel of the slice image to be extracted. init() mainly differs
      from operator() in that it only stores the computed value internally
      without combining it with previous values - this is more efficient.

   3. Extract Thick slice
      call operator() for each pixel of each consecutive slice, this will
      combine the new pixel value with the old ones using the operation 
      defined by the functor (MIP, AVG, etc.)

   4. Finalize
      call finalize() once after all pixels have been extracted. This allows
      for post-processing as in the case of AVG where the accumulated pixel
      values need to be divided by the number of samples.

   5. Read results
      if at one point the finalization should be done for an individual pixel
      instead of for the whole image, call value() to receive the finalized
      pixel value.
*/
////////////////////////////////////////////////////////////////////////////////
class ThickFunctor {
public:
    // Operations for complete images
    virtual ~ThickFunctor() {};
    virtual void initialize(void* texData, const int* texDims, McDArray<bool> * clipLabels = NULL) { assert(0); };
    inline void start(const void * value, const unsigned char * label, unsigned int index) { assert(0); };
    inline void startLerp(const void * value0, const void * value1, float weight, const unsigned char * label, unsigned int index) { assert(0); };
    inline void accumulate(const void * value, const unsigned char * label, unsigned int index) { assert(0); };
    inline void accumulateLerp(const void * value0, const void * value1, float weight, const unsigned char * label, unsigned int index) { assert(0); };
    virtual inline void finalize(const int count, int nx, int ny) { assert(0); };
    // Return a specific value
    void value(const int count, int index, void * outVal) { assert(0); return; };

    /** These interfaces are provided for convenience only -
        they are used for template function instantiation and lookup
        and avoid extensive swich/case cascades */
    virtual bool extractExtraSliceXY(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object ) = 0;
    virtual bool extractExtraSliceXZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object ) = 0;
    virtual bool extractExtraSliceYZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object, int thickStride) = 0;
    virtual bool extractSliceXY(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) = 0;
    virtual bool extractSliceXZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) = 0;
    virtual bool extractSliceYZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object, int thickStride) = 0;
};


////////////////////////////////////////////////////////////////////////////////
template<class T, class F>
static bool extractExtraSliceXY(T* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, F * functor, VsObject & object )
{
    const McVec3l dims = a->dims();
    const McVec3l strides = a->strides();
    char* srcData = (char*) a->dataPtr(0);

    // Without label data
    if (l == 0) {
        for (mclong j=0; j<dims[1]; ++j) {
            int dstIdx = j*texDims[0];
            char* src = srcData + j*strides[1];
            for (mclong i=0; i<dims[0]; ++i, src+=strides[0]) {
                functor->accumulate((T*)src, 0, dstIdx+i);
            }
        }
    }
    // With label data
    else {
        const McVec3l dimsLabel = l->dims();
        const McVec3l stridesLabel = l->strides();
        char* srcLabel = (char*) l->dataPtr(0);

        assert(dimsLabel == dims);
        assert(l->primType() == McPrimType::mc_uint8);
            
        for (mclong j=0; j<dims[1]; ++j) {
            int dstIdx = j*texDims[0];
            char* src = srcData + j*strides[1];
            char* lab = srcLabel + j*stridesLabel[1];
            for (mclong i=0; i<dims[0]; ++i, src+=strides[0], lab+=stridesLabel[0]) {
                functor->accumulate((T*)src, (unsigned char*) lab, dstIdx+i);
            }
        }
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
template<class T, class F>
static bool extractExtraSliceXZ(T* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, F * functor, VsObject & object )
{
    const McVec3l dims = a->dims();
    const McVec3l strides = a->strides();

    // Without label data
    if (l == 0) {
        for (mclong k=0; k<dims[2]; ++k) {
            int dstIdx = k*texDims[0];
            char* src = (char*) a->dataPtr(k);
            for (mclong i=0; i<dims[0]; ++i, src+=strides[0]) {
                functor->accumulate((T*)src, 0, dstIdx+i);
            }
        }
    }
    // With label data
    else {
        const McVec3l dimsLabel = l->dims();
        const McVec3l stridesLabel = l->strides();

        assert(dimsLabel == dims);
        assert(l->primType() == McPrimType::mc_uint8);

        for (mclong k=0; k<dims[2]; ++k) {
            int dstIdx = k*texDims[0];
            char* src = (char*) a->dataPtr(k);
            char* lab = (char*) l->dataPtr(k);
            for (mclong i=0; i<dims[0]; ++i, src+=strides[0], lab+=stridesLabel[0]) {
                functor->accumulate((T*)src, (unsigned char*) lab, dstIdx+i);
            }
        }
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
template<class T, class F>
static bool extractExtraSliceYZ(T* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, F * functor, VsObject & object, int thickStride)
{
    const McVec3l dims = a->dims();
    const McVec3l strides = a->strides();

    // Without label data
    if (l == 0) {
        for (mclong k=0; k<dims[2]; ++k) {

            if ( object.canceled() )
                return false;

            int dstIdx = k*texDims[0];
            char* base = (char*) a->dataPtr(k);
            for (mclong j=0; j<dims[1]; ++j, base+=strides[1]) {
                char* src = base;
                functor->start(src, 0, dstIdx+j);
                for (mclong i=thickStride; i<dims[0]; i+=thickStride) {
                    src+=strides[0]*thickStride;
                    functor->accumulate((T*)src, 0, dstIdx+j);
                }
            }
        }
    } 
    // With label data
    else {
        const McVec3l dimsLabel = l->dims();
        const McVec3l stridesLabel = l->strides();

        assert(dimsLabel == dims);
        assert(l->primType() == McPrimType::mc_uint8);

        for (mclong k=0; k<dims[2]; ++k) {

            if ( object.canceled() )
                return false;

            int dstIdx    = k*texDims[0];
            char* base    = (char*) a->dataPtr(k);
            char* labbase = (char*) l->dataPtr(k);
            for (mclong j=0; j<dims[1]; ++j, base+=strides[1], labbase+=stridesLabel[1]) {
                char* src = base;
                char* lab = labbase;
                functor->start(src, (unsigned char*) lab, dstIdx+j);
                for (mclong i=thickStride; i<dims[0]; i+=thickStride) {
                    src+=strides[0]*thickStride;
                    lab+=stridesLabel[0]*thickStride;
                    functor->accumulate((T*)src, (unsigned char*) lab, dstIdx+j);
                }
            }
        }
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
template<class T, class F>
static bool extractSliceXY(T* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, F * functor, VsObject & object)
{
    const McVec3l dims = a->dims();
    const McVec3l strides = a->strides();

    // Without label data
    if (l == 0) {
        for (mclong j=0; j<dims[1]; ++j) {
            int dstIdx = j*texDims[0];
            char * src = (char*)(a->dataPtr(0)) + j*strides[1];
            for (mclong i=0; i<dims[0]; ++i) {
                functor->start(src, 0, dstIdx+i);
                src += strides[0];
            }
        }
    } 
    // With label data
    else {
        const McVec3l dimsLabel = l->dims();
        const McVec3l stridesLabel = l->strides();

        assert(dimsLabel == dims);
        assert(l->primType() == McPrimType::mc_uint8);

        for (mclong j=0; j<dims[1]; ++j) {
            int dstIdx = j*texDims[0];
            char * src = (char*)(a->dataPtr(0)) + j*strides[1];
            char * lab = (char*)(l->dataPtr(0)) + j*stridesLabel[1];
            for (mclong i=0; i<dims[0]; ++i) {
                functor->start(src, (unsigned char*) lab, dstIdx+i);
                src += strides[0];
                lab += stridesLabel[0];
            }
        }
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
template<class T, class F>
static bool extractSliceXZ(T* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, F * functor, VsObject & object)
{
    const McVec3l dims = a->dims();
    const McVec3l strides = a->strides();

    // Without label data
    if (l == 0) {
        for (mclong j=0; j<dims[2]; ++j) {
            int dstIdx = j*texDims[0];
            char * src = (char*) a->dataPtr(j);
            for (mclong i=0; i<dims[0]; ++i) {
                functor->start(src, 0, dstIdx+i);
                src += strides[0];
            }
        }
    }
    // With label data
    else {
        const McVec3l dimsLabel = l->dims();
        const McVec3l stridesLabel = l->strides();

        assert(dimsLabel == dims);
        assert(l->primType() == McPrimType::mc_uint8);

        for (mclong j=0; j<dims[2]; ++j) {
            int dstIdx = j*texDims[0];
            char * src = (char*) a->dataPtr(j);
            char * lab = (char*) l->dataPtr(j);
            for (mclong i=0; i<dims[0]; ++i) {
                functor->start(src, (unsigned char*) lab, dstIdx+i);
                src += strides[0];
                lab += stridesLabel[0];
            }
        }
    }

    return true;
}


////////////////////////////////////////////////////////////////////////////////
template<class T, class F>
static bool extractSliceYZ(T* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, F * functor, VsObject & object, int thickStride)
{
    const McVec3l dims = a->dims();
    const McVec3l strides = a->strides();

    // Without label data
    if (l == 0) {
        for (mclong k=0; k<dims[2]; ++k) {
            int dstIdx = k*texDims[0];
            char* src = (char*) a->dataPtr(k);
            for (mclong j=0; j<dims[1]; ++j) {
                functor->start(src, 0, dstIdx++);
                src += strides[1];
            }
        }
    }
    // With label data
    else {
        const McVec3l dimsLabel = l->dims();
        const McVec3l stridesLabel = l->strides();

        assert(dimsLabel == dims);
        assert(l->primType() == McPrimType::mc_uint8);

        for (mclong k=0; k<dims[2]; ++k) {
            int dstIdx = k*texDims[0];
            char* src = (char*) a->dataPtr(k);
            char* lab = (char*) l->dataPtr(k);
            for (mclong j=0; j<dims[1]; ++j) {
                functor->start(src, (unsigned char*) lab, dstIdx++);
                src += strides[1];
                lab += stridesLabel[1];
            }
        }
    }

    return true;
}

// BEGIN hazard related code
//       hazard key: F15_G5_U1_M1 (Wrong greyscale pixel values in reconstructed MIP/MPR images.)

// The code below computes greyscale values for thick MPR rendering
// in different mode (MIP, MinIP, AVG).

////////////////////////////////////////////////////////////////////////////////
// Functor base class
//    T:     data type
//    NUM:   number of attributes per data element (nDataVar)
//    LABEL: should label checking be performed?
//    ACCOP: operation used for accumulation (MIN, MAX, ADD ...)
////////////////////////////////////////////////////////////////////////////////
template <class T, int NUM, bool LABEL, void ACCOP(T *, const T *)>
class TypedThickFunctor : public ThickFunctor
{
public:
    typedef T      Type;

protected:
    T*             mTexData;
    int            mTexDims[2];
    McDArray<bool> mLabelsClip;

public:
    static inline void lerp(const T * value0, const T * value1, float weight, T * out)
    {
        // Replace val1 + (u*(val2-val1)) by fix-point arithmetic. This is faster
        // on my Pentium IV, even though this processor is quite slow at shifting.
        // Requires that T be char, short, or unsigned short, else
        // the data would not fit
        int uFixedPoint = McTruncZero(32768.0f * weight);
        for (int i = 0; i < NUM; i++)
            out[i] = value0[i] + (uFixedPoint*(value1[i]-value0[i]) >> 15);
    }

    virtual void initialize(void* texData, const int* texDims, McDArray<bool> * clipLabels = NULL) 
    {
        mTexData = (T*)texData;
        if (texDims) {
            mTexDims[0] = texDims[0];
            mTexDims[1] = texDims[1];
        }
        if (clipLabels && clipLabels->size())
            mLabelsClip.appendArray(*clipLabels);
    };
    inline void start(const void * value, const unsigned char * label, unsigned int index)
    { 
        assert(index < (unsigned int)(mTexDims[0]*mTexDims[1]));
        if (LABEL && label && mLabelsClip[(int)(*label)])
            copy(&mTexData[index*NUM], defaultValue());
        else
            copy(&mTexData[index*NUM], (T*)value);
    };
    inline void startLerp(const void * value0, const void * value1, float weight, const unsigned char * label, unsigned int index)
    {
        Type buffer[NUM];
        lerp((T*)value0, (T*)value1, weight, buffer);
        start(buffer, label, index);
    };
    inline void accumulate(const void * value, const unsigned char * label, unsigned int index)
    { 
        assert(index < (unsigned int)(mTexDims[0]*mTexDims[1]));
        if (!LABEL || !label || !mLabelsClip[(int)(*label)])
            for (int i = 0; i < NUM; i++)
                ACCOP(&mTexData[index*NUM+i], ((T*)value)+i); 
    };
    inline void accumulateLerp(const void * value0, const void * value1, float weight, const unsigned char * label, unsigned int index)
    {
        Type buffer[NUM];
        lerp((T*)value0, (T*)value1, weight, buffer);
        accumulate(buffer, label, index);
    };
    virtual inline void finalize(const int count, int nx, int ny) {};
    void value(const int count, int index, void * outVal) 
    { 
        copy((T*)outVal, &mTexData[index*NUM]); 
    };


    static inline void copy(T * dst, const T * src)
    {
        for (int i = 0; i < NUM; i++)
            dst[i] = src[i];
    };
    static inline void copyToAcc(int * dst, const T * src)
    {
        for (int i = 0; i < NUM; i++)
            dst[i] = src[i];
    };
    /* static inline void copyFromAcc(T * dst, const int * src)
    {
        for (int i = 0; i < NUM; i++)
            dst[i] = src[i];
    }; */
    static inline void add(int * dst, const T * src)
    {
        for (int i = 0; i < NUM; i++)
            dst[i] += src[i];
    };
    static inline void div(T * dst, const int * src, int divident)
    {
        for (int i = 0; i < NUM; i++)
            dst[i] = src[i] / divident;
    };
    static inline T * defaultValue()
    {
        assert(NUM <= 4);
        static T defaultValue[4] = {0, 0, 0, 0};
        return defaultValue;
    };
};


////////////////////////////////////////////////////////////////////////////////
template <typename T>
class Operations {
public:
    static void maxOp(T * dst, const T * src)
    {
        if (*src > *dst)
            *dst = *src;
    }

    static void minOp(T * dst, const T * src)
    {
        if (*src < *dst)
            *dst = *src;
    }

    static void nullOp(T * dst, const T * src) {}
};


////////////////////////////////////////////////////////////////////////////////
template <class T, int NUM, bool LABEL>
class MIPFunctor : public TypedThickFunctor<T, NUM, LABEL, Operations<T>::maxOp >
{
public:
    typedef T      Type;

    MIPFunctor(T* texData = 0, const int* texDims = 0, McDArray<bool> * clipLabels = NULL)
    {
        initialize(texData, texDims, clipLabels);
    }
    virtual void initialize(void* texData, const int* texDims, McDArray<bool> * clipLabels = NULL)
    {
        TypedThickFunctor<T, NUM, LABEL, Operations<T>::maxOp>::initialize(texData, texDims, clipLabels);
        if (texDims && texData)
            memset(texData, 0, sizeof(T)*texDims[0]*texDims[1]*NUM);
    }

    virtual bool extractExtraSliceXY(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object ) {
        return ::extractExtraSliceXY((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractExtraSliceXZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractExtraSliceXZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractExtraSliceYZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object, int thickStride) {
        return ::extractExtraSliceYZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object, thickStride); };
    virtual bool extractSliceXY(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractSliceXY((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractSliceXZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractSliceXZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractSliceYZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object, int thickStride) {
        return ::extractSliceYZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object, thickStride); };

    static ThickFunctor * create(int nDataVar, bool labels)
    {
        assert(nDataVar >= 1 && nDataVar <= 4);
        
        if (labels)
        {
            switch (nDataVar) {
            case 1: return new MIPFunctor<T, 1, true>;
            case 2: return new MIPFunctor<T, 2, true>;
            case 3: return new MIPFunctor<T, 3, true>;
            case 4: return new MIPFunctor<T, 4, true>;
            }
        }
        else {
            switch (nDataVar) {
            case 1: return new MIPFunctor<T, 1, false>;
            case 2: return new MIPFunctor<T, 2, false>;
            case 3: return new MIPFunctor<T, 3, false>;
            case 4: return new MIPFunctor<T, 4, false>;
            }
        }
        return 0;
    }
};


////////////////////////////////////////////////////////////////////////////////
template <class T, int NUM, bool LABEL>
class MINIPFunctor : public TypedThickFunctor<T, NUM, LABEL, Operations<T>::minOp>
{
public:
    typedef T      Type;

    MINIPFunctor(T* texData = 0, const int* texDims = 0, McDArray<bool> * clipLabels = NULL)
    {
        initialize(texData, texDims, clipLabels);
    };
    virtual void initialize(void* texData, const int* texDims, McDArray<bool> * clipLabels = NULL)
    {
        TypedThickFunctor<T, NUM, LABEL, Operations<T>::minOp>::initialize(texData, texDims, clipLabels);
        if (texDims && texData)
            memset(texData, 0, sizeof(T)*texDims[0]*texDims[1]*NUM);
    };

    virtual bool extractExtraSliceXY(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object ) {
        return ::extractExtraSliceXY((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractExtraSliceXZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractExtraSliceXZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractExtraSliceYZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object, int thickStride) {
        return ::extractExtraSliceYZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object, thickStride); };
    virtual bool extractSliceXY(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractSliceXY((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractSliceXZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractSliceXZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractSliceYZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object, int thickStride) {
        return ::extractSliceYZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object, thickStride); };

    static ThickFunctor * create(int nDataVar, bool labels)
    {
        assert(nDataVar >= 1 && nDataVar <= 4);
        
        if (labels)
        {
            switch (nDataVar) {
            case 1: return new MINIPFunctor<T, 1, true>;
            case 2: return new MINIPFunctor<T, 2, true>;
            case 3: return new MINIPFunctor<T, 3, true>;
            case 4: return new MINIPFunctor<T, 4, true>;
            }
        }
        else {
            switch (nDataVar) {
            case 1: return new MINIPFunctor<T, 1, false>;
            case 2: return new MINIPFunctor<T, 2, false>;
            case 3: return new MINIPFunctor<T, 3, false>;
            case 4: return new MINIPFunctor<T, 4, false>;
            }
        }
        return 0;
    }
};


////////////////////////////////////////////////////////////////////////////////
template <class T, int NUM, bool LABEL>
class AVGFunctor : public TypedThickFunctor<T, NUM, LABEL, Operations<T>::nullOp >
{
public:
    typedef T      Type;
private:
    McDArray<int>  mAccum;
    McDArray<int>  mCount;

public:
    static inline void lerp(const T * value0, const T * value1, float weight, T * out)
    {
        // Replace val1 + (u*(val2-val1)) by fix-point arithmetic. This is faster
        // on my Pentium IV, even though this processor is quite slow at shifting.
        // Requires that T be char, short, or unsigned short, else
        // the data would not fit
        int uFixedPoint = McTruncZero(32768.0f * weight);
        for (int i = 0; i < NUM; i++)
            out[i] = value0[i] + (uFixedPoint*(value1[i]-value0[i]) >> 15);
    }
    
    AVGFunctor(T* texData = 0, const int* texDims = 0, McDArray<bool> * clipLabels = NULL)
    {
        initialize(texData, texDims, clipLabels);
    };
    virtual void initialize(void* texData, const int* texDims, McDArray<bool> * clipLabels = NULL)
    {
        TypedThickFunctor<T, NUM, LABEL, Operations<T>::nullOp>::initialize(texData, texDims, clipLabels);
        if (texDims) {
            if (clipLabels && clipLabels->size()) {
                mCount.resize(texDims[0]*texDims[1]);
                mCount.fill(0);
            }
            mAccum.resize(texDims[0]*texDims[1]*NUM);
            mAccum.fill(0);
        }
    };
    inline void start(const void * value, const unsigned char * label, unsigned int index)
    { 
        assert(index < (unsigned int)(this->mTexDims[0]*this->mTexDims[1]));
        if (!LABEL || !label) {
            this->copyToAcc(&mAccum[index*NUM], (T*)value);
        } 
        else {
            bool skip = this->mLabelsClip[(int)(*label)];
            this->copyToAcc(&mAccum[index*NUM], skip ? this->defaultValue() : (T*)value);
            mCount[index] = skip ? 0 : 1;
        }
    };
    inline void startLerp(const void * value0, const void * value1, float weight, const unsigned char * label, unsigned int index)
    {
        Type buffer[NUM];
        lerp((T*)value0, (T*)value1, weight, buffer);
        start(buffer, label, index);
    };
    inline void accumulate(const void * value, const unsigned char * label, unsigned int index)
    { 
        assert(index < (unsigned int)(this->mTexDims[0]*this->mTexDims[1]));
        if (!LABEL || !label || !this->mLabelsClip[(int)(*label)]) {
            this->add(&mAccum[index*NUM], (T*)value);
            if (label)
                mCount[index]++;
        }
    };

    inline void accumulateLerp(const void * value0, const void * value1, float weight, const unsigned char * label, unsigned int index)
    {
        Type buffer[NUM];
        lerp((T*)value0, (T*)value1, weight, buffer);
        accumulate(buffer, label, index);
    };
    virtual inline void finalize(const int count, int nx, int ny)
    {
        if (!LABEL || this->mLabelsClip.size() == 0) {
            for (int j=0; j<ny; ++j) {
                T* dst = this->mTexData + j*this->mTexDims[0]*NUM;
                const int* src = mAccum + j*this->mTexDims[0]*NUM;
                for (int i=0; i<nx*NUM; ++i)
                    dst[i] = (T)(src[i]/count);
            }
        }
        else {
            int index = 0;
            for (int j=0; j<ny; ++j) {
                T* dst = this->mTexData + j*this->mTexDims[0]*NUM;
                int* src = mAccum + j*this->mTexDims[0]*NUM;
                for (int i=0; i<nx; ++i, index++) {
                    const int count = (mCount[index] > 0 ? mCount[index] : 1);
                    this->div(&dst[i*NUM], &src[i*NUM], count);
                }
            }
        }
    };
    void value(const int count, int index, void * outVal)
    {
        assert(index < this->mTexDims[0]*this->mTexDims[1]);
        int divisor = this->mLabelsClip.size() == 0 
                      ? (count > 0 ? count : 1) 
                      : (mCount[index] > 0 ? mCount[index] : 1);

        this->div(&this->mTexData[index*NUM], &mAccum[index*NUM], divisor);
        this->copy((T*)outVal, &this->mTexData[index*NUM]);
        return;
    };

    virtual bool extractExtraSliceXY(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object ) {
        return ::extractExtraSliceXY((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractExtraSliceXZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractExtraSliceXZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractExtraSliceYZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object, int thickStride) {
        return ::extractExtraSliceYZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object, thickStride); };
    virtual bool extractSliceXY(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractSliceXY((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractSliceXZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object) {
        return ::extractSliceXZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object); };
    virtual bool extractSliceYZ(void* texData, const int* texDims, const VsDataAccess* a, const VsDataAccess* l, VsObject & object, int thickStride) {
        return ::extractSliceYZ((T*)texData, texDims, a, this->mLabelsClip.size() ? l : 0, this, object, thickStride); };

    static ThickFunctor * create(int nDataVar, bool labels)
    {
        assert(nDataVar >= 1 && nDataVar <= 4);
        
        if (labels)
        {
            switch (nDataVar) {
            case 1: return new AVGFunctor<T, 1, true>;
            case 2: return new AVGFunctor<T, 2, true>;
            case 3: return new AVGFunctor<T, 3, true>;
            case 4: return new AVGFunctor<T, 4, true>;
            }
        }
        else {
            switch (nDataVar) {
            case 1: return new AVGFunctor<T, 1, false>;
            case 2: return new AVGFunctor<T, 2, false>;
            case 3: return new AVGFunctor<T, 3, false>;
            case 4: return new AVGFunctor<T, 4, false>;
            }
        }
        return 0;
    }
};

// END hazard related code

#endif // _VS_THICK_SLICE_IMPL_H


/// @}

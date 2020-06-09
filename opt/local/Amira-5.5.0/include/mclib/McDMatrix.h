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
#ifndef MCDMATRIX_H
#define MCDMATRIX_H

#ifdef HX_HAS_STDIOSTREAM
    #include <iostream>
#else
    #include <iostream.h>
#endif

#include "McAssert.h"
#include "McSysHeader.h"
#include "McProgressInterface.h"
#include "McDArray.h"
#include "McBitfield.h"

#include "McDVector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <cmath>

#if defined (HX_HAS_STDCOMPLEX)
#  include <complex>
#else
#  include <complex.h>
#endif

#include "McWinDLLApi.h"
#include "McStdlib.h"

// If this line is removed, clib memory routines are used.
#include "McMalloc.h"

#ifdef MC_MALLOC_H
    #define mcdmatrix_malloc(a) ::mcmalloc(a)
    #define mcdmatrix_realloc(a,b) ::mcrealloc(a,b)
    #define mcdmatrix_free(a) ::mcfree(a)
#else
    #define mcdmatrix_malloc(a) ::malloc(a)
    #define mcdmatrix_realloc(a,b) ::realloc(a,b)
    #define mcdmatrix_free(a) ::free(a)
#endif

class McProgressInterface;

/**
 * This class provides a dynamic two dimensional matrix of generic type T. The matrix
 * is stored in row-major order in memory, i.e. the elements (row,column)
 *
 *     (0,0) (0,1) (0,2) (0,3)
 *     (1,0) (1,1) (1,2) (1,3)
 *     (2,0) (2,1) (2,2) (2,3)
 *     (3,0) (3,1) (3,2) (3,3)
 *
 * are linearly stored as
 *
 *     (0,0) (0,1) (0,2) (0,3) (1,0) (1,1) (1,2) (1,3) ...
 *
 * in memory.
 */
template<class T> class McDMatrix
{
public:
    /** Default constructor.*/
    McDMatrix<T>() : nrows(0), ncols(0), data(0) {
    }

    /// Copy constructor.
    McDMatrix(const McDMatrix<T>& old) : nrows(0), ncols(0), data(0) {
        resize(old.nRows(), old.nCols());
        memcpy(dataPtr(),old.dataPtr(), nEntries()*sizeof(T));
    }

    /** This constructor allocates an @c McDMatrix of type @c T
    containing @c nr rows and @c nc columns. The matrix
    is initialized with the given data if data pointer @c d =! zero,
    otherwise it remains uninitialized.*/
    McDMatrix(int nr,int nc, T* d=0) : nrows(0), ncols(0), data(0)
    {
        resize(nr,nc);
        if (d) memcpy(dataPtr(),d, nEntries()*sizeof(T));
    }

    /// Destructor.
    ~McDMatrix() {
        if (data) mcdmatrix_free(data);
    }

    /// Initialize all elements with t.
    void fill(T f) {
        T *end = data+nEntries();
        for (T* ptr=data; ptr<end; ptr++)
            *ptr = f;
    }

    /// Index operator.
    T&  operator()(int row,int col) {
        assert(row>=0 && row<nrows && col>=0 && col<ncols);
        return data[row*ncols + col];
    }

    /// Const version of index operator.
    const T& operator()(int row,int col) const {
        assert(row>=0 && row<nrows && col>=0 && col<ncols);
        return data[row*ncols + col];
    }

    /// Get row vector
    T* operator[](int row) {
        assert(row>=0 && row<nrows);
        return data+row*ncols;
    }
    /// Get row vector
    T* operator[](unsigned int row) {
        assert(row>=0 && row<(unsigned int)nrows);
        return data+row*ncols;
    }

    /// Get const row vector
    const T* operator[](int row) const {
        assert(row>=0 && row<nrows);
        return data+row*ncols;
    }

    /// Get const row vector
    const T* operator[](unsigned int row) const {
        assert(row>=0 && row<(unsigned int)nrows);
        return data+row*ncols;
    }

    /** Scalar multiplication of matrix entries. */
    void multScal(const T& scal) {
        T *p = data;
        for (int j=nrows*ncols ; j>0 ; j--) {
            *(p++) *= scal;
        }
    }

    /** Returns the i-th row of the matrix. */
    McDVector<T> getRowVector(int i) const {
        mcrequire(i >= 0 && i < nrows);

        McDVector<T> v(ncols);

        memcpy(v.dataPtr(), (*this)[i], ncols * sizeof(T));

        return v;
    }

    /** Replaces the i-th row of the matrix. */
    McDMatrix<T>& setRowVector(const McDVector<T>& row, int i) {
        mcrequire(i >= 0 && i < nrows && row.size() == ncols);

        memcpy((*this)[i], row.dataPtr(), ncols * sizeof(T));

        return *this;
    }

    /** Returns the i-th column of the matrix. */
    McDVector<T> getColVector(int i) const {
        mcrequire(i >= 0 && i < ncols);

        McDVector<T> v(nrows);

        for(int idx = 0; idx < nrows; idx++)
            v[idx] = (*this)[idx][i];

        return v;
    }

    /** Replaces the i-th column of the matrix. */
    McDMatrix<T>& setColVector(const McDVector<T>& col, int i) {
        mcrequire(i >= 0 && i < ncols && col.size() == nrows);

        const T* colData = col.dataPtr();
        for(int idx = 0; idx < nrows; idx++)
            *(this->dataPtr() + (idx * ncols + i)) = *(colData++);

        return *this;
    }

    /** Matrix addition. If matrices cannot be added
        matrix remains unchanged.*/
    McDMatrix<T>& operator+=(const McDMatrix<T>& right) {
        if (ncols!=right.ncols || nrows!=right.nrows) {
            printf("McDMatrix: Can not add %dx%d matrix to %dx%d matrix.\n",
                   nrows,ncols,right.nrows,right.ncols);
            return *this;
        }

        T *p1 = data;
        T *p2 = right.data;
        for (int j=nrows*ncols ; j>0 ; j--) {
            *(p1++) += *(p2++);
        }
        return *this;
    }

    /** Matrix and Vector addition. The vector is added to each column of the matrix. If matrices cannot be added
        matrix remains unchanged.*/
    McDMatrix<T>& addColWise(const McDVector<T>& right) {
        if (nrows!=right.size()) {
            printf("McDMatrix: Can not add %dx%d vector to %dx%d matrix.\n",
                    int(right.size()),1,nrows,ncols);
            return *this;
        }

        T *p1 = data;
        const T* p2 = right.dataPtr();

        for (int i=nrows; i > 0; --i) {
            T val = *(p2++);

            for(int j=ncols; j > 0; --j)
                *(p1++) += val;
        }

        return *this;
    }

    /** Matrix and Vector addition. The vector is added to each row of the matrix. If matrices cannot be added
        matrix remains unchanged.*/
    McDMatrix<T>& addRowWise(const McDVector<T>& right) {
        if (ncols!=right.size()) {
            printf("McDMatrix: Can not add %dx%d vector to %dx%d matrix.\n",
                    1,int(right.size()),nrows,ncols);
            return *this;
        }

        T* p1 = data;
        const T* p2 = right.dataPtr();

        for (int i=nrows; i > 0; --i) {
            p2 = right.dataPtr();

            for(int j=ncols; j > 0; --j)
                *(p1++) += *(p2++);
        }

        return *this;
    }

    /// Matrix addition
    McDMatrix<T> operator+(const McDMatrix<T>& right) const {
        mcrequire(ncols == right.ncols);
        mcrequire(nrows == right.nrows);

        McDMatrix newMatrix(nrows,ncols);
        newMatrix.fill(T(0));

        T* p1 = data;
        const T* p2 = right.dataPtr();
        T* pe = newMatrix.data;
        for (int j=nrows*ncols; j > 0; --j) {
            *(pe++) = *(p1++) + *(p2++);
        }
        return newMatrix;
    }

    /** Matrix and Vector addition. The vector is added to each column of the matrix.*/
    McDMatrix<T> addColWise(const McDVector<T>& right) const {
        mcrequire(nrows == right.size());

        McDMatrix newMatrix(nrows,ncols);
        newMatrix.fill(T(0));

        T* p1 = data;
        const T* p2 = right.dataPtr();
        T* pe = newMatrix.data;

        for (int i=nrows; i > 0; --i) {
            T val = *(p2++);

            for(int j=ncols; j > 0; --j)
                *(pe++) = *(p1++) + val;
        }

        return newMatrix;
    }

    /** Matrix and Vector addition. The vector is added to each row of the matrix.*/
    McDMatrix<T> addRowWise(const McDVector<T>& right) const {
        mcrequire(ncols == right.size());

        McDMatrix newMatrix(nrows,ncols);
        newMatrix.fill(T(0));

        T* p1 = data;
        const T* p2 = right.dataPtr();
        T* pe = newMatrix.data;

        for (int i=nrows; i > 0; --i) {
            p2 = right.dataPtr();

            for(int j=ncols; j > 0; --j)
                *(pe++) = *(p1++) + *(p2++);
        }

        return newMatrix;
    }

    /** Matrix subtraction. If matrices cannot be subtracted
        matrix remains unchanged.*/
    McDMatrix<T>& operator-=(const McDMatrix<T>& right) {
        if (ncols!=right.ncols || nrows!=right.nrows) {
            printf("McDMat: Can not add %dx%d matrix to %dx%d matrix.\n",
                   nrows,ncols,right.nrows,right.ncols);
            return *this;
        }

        T *p1 = data;
        T *p2 = right.data;
        for (int j=nrows*ncols ; j>0 ; j--) {
            *(p1++) -= *(p2++);
        }
        return *this;
    }

    /** Matrix and Vector subtraction. The vector is subtracted from each column of the matrix. If matrices 
        cannot be subtracted matrix remains unchanged.*/
    McDMatrix<T>& subtractColWise(const McDVector<T>& right) {
        if (nrows!=right.size()) {
            printf("McDMatrix: Can not add %dx%d vector to %dx%d matrix.\n",
                    right.size(),1,nrows,ncols);
            return *this;
        }

        T* p1 = data;
        const T* p2 = right.dataPtr();

        for (int i=nrows; i > 0; --i) {
            T val = *(p2++);

            for(int j=ncols; j > 0; --j)
                *(p1++) -= val;
        }

        return *this;
    }

    /** Matrix and Vector subtraction. The vector is subtracted from each row of the matrix. If matrices 
        cannot be subtracted matrix remains unchanged.*/
    McDMatrix<T>& subtractRowWise(const McDVector<T>& right) {
        if (ncols!=right.size()) {
            printf("McDMatrix: Can not add %dx%d vector to %dx%d matrix.\n",
                    1,right.size(),nrows,ncols);
            return *this;
        }

        T* p1 = data;
        const T* p2 = right.dataPtr();

        for (int i=nrows; i > 0; --i) {
            p2 = right.dataPtr();

            for(int j=ncols; j > 0; --j)
                *(p1++) -= *(p2++);
        }

        return *this;
    }

    /// Matrix subtraction
    McDMatrix<T> operator-(const McDMatrix<T>& right) const {
        mcrequire(ncols == right.ncols);
        mcrequire(nrows == right.nrows);

        McDMatrix newMatrix(nrows,ncols);
        newMatrix.fill(T(0));

        T* p1 = data;
        const T* p2 = right.dataPtr();
        T* pe = newMatrix.data;
        for (int j=nrows*ncols; j > 0; --j) {
            *(pe++) = *(p1++) - *(p2++);
        }
        return newMatrix;
    }

    /** Matrix and Vector addition. The vector is subtracted from each column of the matrix.*/
    McDMatrix<T> subtractColWise(const McDVector<T>& right) const {
        mcrequire(nrows == right.size());

        McDMatrix newMatrix(nrows,ncols);
        newMatrix.fill(T(0));

        T* p1 = data;
        const T* p2 = right.dataPtr();
        T* pe = newMatrix.data;

        for (int i=nrows; i > 0; --i) {
            T val = *(p2++);

            for(int j=ncols; j > 0; --j)
                *(pe++) = *(p1++) - val;
        }

        return newMatrix;
    }

    /** Matrix and Vector subtraction. The vector is subtracted from each row of the matrix.*/
    McDMatrix<T> subtractRowWise(const McDVector<T>& right) const {
        mcrequire(ncols == right.size());

        McDMatrix newMatrix(nrows,ncols);
        newMatrix.fill(T(0));

        T* p1 = data;
        const T* p2 = right.dataPtr();
        T* pe = newMatrix.data;

        for (int i=nrows; i > 0; --i) {
            p2 = right.dataPtr();

            for(int j=ncols; j > 0; --j)
                *(pe++) = *(p1++) - *(p2++);
        }

        return newMatrix;
    }

    /** Matrix multiplication. If matrices cannot be multiplied,
    matrix remains unchanged.*/
    McDMatrix<T>& operator*=(const McDMatrix<T>& right) {
        if (ncols!=right.nrows) {
            fprintf(stderr,
                "McDMatrix:operator*: Can not multiply %dx%d matrix by %dx%d matrix.\n",
                nrows,ncols,right.nrows,right.ncols);
            return *this;
        }
        T* ndata = (T *) mcdmatrix_malloc(mcuint64(nrows)*right.ncols*sizeof(T));
        T* nd = ndata;
        for (int j=0 ; j<nrows ; j++) {
            for (int i=0 ; i<right.ncols ; i++) {
                T* row=(*this)[j];
                T* col=right.data+i;
                T result=0;
                for (int k=0 ; k<ncols ; k++) {
                    result += *row * *col;
                    row++;
                    col+=right.ncols;
                }
                *nd++=result;
            }
        }
        if (data) mcdmatrix_free (data);
        data = ndata;
        ncols = right.ncols;
        return *this;
    }

    /// Matrix multiplication.
    McDMatrix<T> operator*(const McDMatrix<T>& right) const {
    	mcrequire(ncols == right.nrows);

        McDMatrix newMatrix(nrows, right.ncols);
        newMatrix.fill(T(0));

        for(int i=0; i < nrows; ++i)
            for(int j=0; j < right.ncols; ++j)
                for(int k=0; k < right.ncols; ++k)
                    newMatrix(i,j) += data[i*ncols + k] * right(k,j);
        return newMatrix;
    }

    /** Element wise multiplication of two matrices. */
    McDMatrix<T>& multElementWise(const McDMatrix<T>& right) {
        if(ncols != right.ncols || nrows != right.nrows) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(" << right.nRows() << ", " << right.nCols() << ")" << std::endl;
            return *this;
        }

        unsigned int newSize = nrows * ncols;

        for(unsigned int i = 0; i < newSize; i++)
            ((*this).dataPtr())[i] *= (right.dataPtr())[i];

        return *this;
    }

    /** Element wise multiplication of two matrices. */
    McDMatrix<T> multElementWise(const McDMatrix<T>& right) const {
        if(ncols != right.ncols || nrows != right.nrows) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(" << right.nRows() << ", " << right.nCols() << ")" << std::endl;
            return *this;
        }

        McDMatrix<T> newMatrix(nrows, ncols);
        T* newDataPtr = newMatrix.dataPtr();
        unsigned int newSize = nrows * ncols;

        for(unsigned int i = 0; i < newSize; i++)
            newDataPtr[i] = (dataPtr())[i] * (right.dataPtr())[i];

        return newMatrix;
    }

    /** Element wise multiplication. Each row of the matrix is multiplied element wise by right. */
    McDMatrix<T>& multRowWise(const McDVector<T>& right) {
        if(ncols != right.size()) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(1, " << right.size() << ")" << std::endl;
            return *this;
        }

        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            unsigned int currentRow = i * ncols;

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                ((*this).dataPtr())[currentRow + j] *= right[j];
            }
        }

        return *this;
    }

    /** Element wise multiplication. Each row of the matrix is multiplied element wise by right. */
    McDMatrix<T> multRowWise(const McDVector<T>& right) const {
        if(ncols != right.size()) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(1, " << right.size() << ")" << std::endl;
            return *this;
        }

        McDMatrix<T> newMatrix(nrows, ncols);
        T* newDataPtr = newMatrix.dataPtr();
        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            unsigned int currentRow = i * ncols;

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                newDataPtr[currentRow + j] = (dataPtr())[currentRow + j] * right[j];
            }
        }

        return newMatrix;
    }

    /** Element wise multiplication. Each column of the matrix is multiplied element wise by right. */
    McDMatrix<T>& multColumnWise(const McDVector<T>& right) {
        if(nrows != right.size()) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(" << right.size() << ", 1)" << std::endl;
            return *this;
        }

        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            unsigned int currentRow = i * ncols;
            T tmp = right[i];

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                ((*this).dataPtr())[currentRow + j] *= tmp;
            }
        }

        return *this;
    }

    /** Element wise multiplication. Each column of the matrix is multiplied element wise by right. */
    McDMatrix<T> multColumnWise(const McDVector<T>& right) const {
        if(nrows != right.size()) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(" << right.size() << ", 1)" << std::endl;
            return *this;
        }

        McDMatrix<T> newMatrix(nrows, ncols);
        T* newDataPtr = newMatrix.dataPtr();
        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            unsigned int currentRow = i * ncols;
            T tmp = right[i];

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                newDataPtr[currentRow + j] = (dataPtr())[currentRow + j] * tmp;
            }
        }

        return newMatrix;
    }

    /** Element wise division. */
    McDMatrix<T>& divElementWise(const McDMatrix<T>& right) {
        if(ncols != right.ncols || nrows != right.nrows) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(" << right.nRows() << ", " << right.nCols() << ")" << std::endl;
            return *this;
        }

        unsigned int newSize = nrows * ncols;

        for(unsigned int i = 0; i < newSize; i++)
            ((*this).dataPtr())[i] /= (right.dataPtr())[i];

        return *this;
    }

    /** Element wise division of two matrices. */
    McDMatrix<T> divElementWise(const McDMatrix<T>& right) const {
        if(ncols != right.ncols || nrows != right.nrows) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(" << right.nRows() << ", " << right.nCols() << ")" << std::endl;
            return *this;
        }

        McDMatrix<T> newMatrix(nrows, ncols);
        T* newDataPtr = newMatrix.dataPtr();
        unsigned int newSize = nrows * ncols;

        for(unsigned int i = 0; i < newSize; i++)
            newDataPtr[i] = (dataPtr())[i] / (right.dataPtr())[i];

        return newMatrix;
    }

    /** Element wise division. Each row of the matrix is divided element wise by right. */
    McDMatrix<T>& divRowWise(const McDVector<T>& right) {
        if(ncols != right.size()) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(1, " << right.size() << ")" << std::endl;
            return *this;
        }

        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            unsigned int currentRow = i * ncols;

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                ((*this).dataPtr())[currentRow + j] /= right[j];
            }
        }

        return *this;
    }

    /** Element wise division. Each row of the matrix is divided element wise by right. */
    McDMatrix<T> divRowWise(const McDVector<T>& right) const {
        if(ncols != right.size()) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(1, " << right.size() << ")" << std::endl;
            return *this;
        }

        McDMatrix<T> newMatrix(nrows, ncols);
        T* newDataPtr = newMatrix.dataPtr();
        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            unsigned int currentRow = i * ncols;

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                newDataPtr[currentRow + j] = (dataPtr())[currentRow + j] / right[j];
            }
        }

        return newMatrix;
    }

    /** Element wise division. Each column of the matrix is divided element wise by right. */
    McDMatrix<T>& divColumnWise(const McDVector<T>& right) {
        if(nrows != right.size()) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(" << right.size() << ", 1)" << std::endl;
            return *this;
        }

        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            unsigned int currentRow = i * ncols;
            T tmp = right[i];

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                ((*this).dataPtr())[currentRow + j] /= tmp;
            }
        }

        return *this;
    }

    /** Element wise division. Each column of the matrix is divided element wise by right. */
    McDMatrix<T> divColumnWise(const McDVector<T>& right) const {
        if(nrows != right.size()) {
            std::cout << "ERROR: size mismatch : matrix (" << nrows << ", " << ncols << ") - right(" << right.size() << ", 1)" << std::endl;
            return *this;
        }

        McDMatrix<T> newMatrix(nrows, ncols);
        T* newDataPtr = newMatrix.dataPtr();
        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            unsigned int currentRow = i * ncols;
            T tmp = right[i];

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                newDataPtr[currentRow + j] = (dataPtr())[currentRow + j] / tmp;
            }
        }

        return newMatrix;
    }

    /** Returns a McDVector which contains the sum of each rows. */
    McDVector<T> rowSums() const {
        McDVector<T> res(nrows);
        T* dptr = res.dataPtr();
        T* ptr = data;

        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            *dptr = 0.0;

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                *dptr += *(ptr++);
            }
            dptr++;
        }

        return res;
    }

    /** Returns a McDVector which contains the sum of each columns. */
    McDVector<T> colSums() const {
        McDVector<T> res(ncols);
        res.fill(T(0));
        T* dptr = res.dataPtr();
        T* ptr = data;

        for(unsigned int i = 0; i < (unsigned int)nrows; i++) {
            dptr = res.dataPtr();

            for(unsigned int j = 0; j < (unsigned int)ncols; j++) {
                *(dptr++) += *(ptr++);
            }
        }

        return res;
    }

    /// Returns pointer to array data.
    operator T* () { return data; }

    /// Returns const pointer to array data.
    operator const T* () const  { return data; }

    /// Returns pointer to array data.
    T* dataPtr() { return data; }

    /// Returns const pointer to array data.
    const T* dataPtr() const  { return data; }

    /** Vector multiplication from right. The result is given in @c dst,
    therefore @c v must contain @c nCols() and @c dst @c nRows() Ts. */
    void multVec(const T* v, T* dst) const {
        for (int i=0 ; i<nrows ; i++) {
            T c = 0;
            const T* row = (*this)[i];
            for (int j=0 ; j<ncols ; j++)
                c+= *row++ * v[j];
            dst[i] = c;
        }
    }

    /** Vector multiplication from right.*/
    void multVec(T* v) const {
        assert(nrows==ncols);
        T* vtmp =(T *) MC_alloca(nCols()*sizeof(T));
        multVec(v,vtmp);
        for (int i=0 ; i<ncols ; i++)
            v[i]=vtmp[i];
    }

    /// Returns number of elements in array.
    int size() const { return nEntries(); }
    /// Returns number of elements in array.
    int nEntries() const {return ncols*nrows;}

    /// Returns number of elements in a column.
    int nCols() const {return ncols;}

    /// Returns number of elements in a row.
    int nRows() const {return nrows;}

    /** Set size to @c nr rows and @c nc columns, entries are NOT initialized, old
    entries may be lost. */
    void resize(int nr,int nc) {
        if (nr==nrows && nc==ncols)
            return;
        mcuint64 ne = mcuint64(nr)*nc;
        if (data)
            data = (T *)mcdmatrix_realloc(data,ne*sizeof(T));
        else
            data = (T *)mcdmatrix_malloc(ne*sizeof(T));
        nrows = nr;
        ncols = nc;
    }
    /// Set size to @c nr rows and @c nc columns, old entries are kept and resorted.
    void resizeKeep(int nr,int nc) {
        if (nr==nrows && nc==ncols)
            return;
        mcuint64 ne = mcuint64(nr)*nc;
        T* ndata = (T *)mcdmatrix_malloc(ne*sizeof(T));
        T* nd = ndata;
        for (int j=0 ; j<nr ; j++) {
            if (j<nrows) {
                T* oldd = data + ncols*j;
                for (int i=0 ; i<nc ; i++) {
                    if (i<ncols)
                        *nd++ = *oldd++;
                    else
                        *nd++ = 0;
                }
            } else {
                for (int i=0 ; i<nc ; i++)
                    *nd++=0;
            }
        }
        if (data) mcdmatrix_free(data);
        data=ndata;
        nrows = nr;
        ncols = nc;
    }

    /** Assignment operator. Assigning an lvalue @c McDMat to a
    rvalue @c McDMat involves resizing the lvalue to the rvalues
    size and copying all elements via @c memcpy(). */
    McDMatrix<T>& operator=(const McDMatrix<T>& rhs) {
        resize(rhs.nRows(), rhs.nCols());
        T* d = data;
        T* od = rhs.data;
        for (int i=nEntries() ; i ; i--)
            *d++ = *od++;
        return *this;
    }

    /** Make it an identity matrix. Diagonal elements are set to one,
    all others are set to zero, the matrixes size remains unchanged.*/
    void makeIdentity() {
        int m = nrows;
        if (m>ncols) m =ncols;
        fill(T(0.0));
        for (int i=0 ; i<m ; i++)
            (*this)(i,i) = T(1.0);
    }

    /// Transpose matrix.
    McDMatrix<T>& transpose() {
        T* ndata = (T *) mcdmatrix_malloc(mcuint64(nEntries())*sizeof(T));
        T* d = ndata;
        for (int j=0 ; j<ncols ; j++) {
            for (int i=0 ; i<nrows ; i++)
                *d++ = (*this)(i,j);
        }
        if (data) mcdmatrix_free(data);
        data=ndata;
        int t = ncols;
        ncols=nrows; nrows=t;
        return *this;
    }

    /** Make it a @c nxn matrix with diagonal elements are set to @c a[i],
    all others are set to zero.*/
    void setDiagonal(const T* a, int n) {
        resize(n,n);
        fill(0);
        for (int i=0 ; i<n ; i++) {
            (*this)(i,i) = a[i];
        }
    }

    /// Returns complex conjugate of @c z if T is complex
    T conjug(const T& z);

    /// Returns real part of @c z
    double realPart(const T& z);

    /// Returns imaginary part of @c z
    double imagPart(const T& z);

    /** Returns the max absolute element of the matrix. */
    T maxElement(bool absolute = false) const {
        T max = 0.0;
        T* dptr = data;

        if(absolute) {
            for(unsigned int i = 0, size = nrows * ncols; i < size; i++) {
                T val = fabs(*(dptr++));
                if(val > max)
                    max = val;
            }
        } else {
            for(unsigned int i = 0, size = nrows * ncols; i < size; i++) {
                T val = *(dptr++);
                if(val > max)
                    max = val;
            }
        }

        return max;
    }

    /** Returns the max absolute element of the matrix. */
    T minElement(bool absolute = false) const {
        T min = 0.0;
        T* dptr = data;

        if(absolute) {
            for(unsigned int i = 0, size = nrows * ncols; i < size; i++) {
                T val = fabs(*(dptr++));
                if(val < min)
                    min = val;
            }
        } else {
            for(unsigned int i = 0, size = nrows * ncols; i < size; i++) {
                T val = *(dptr++);
                if(val < min)
                    min = val;
            }
        }

        return min;
    }

    /// Prints matrix to file pointer
    void print(FILE *fp=stdout) {
        for (int j=0 ; j<nrows ; j++) {
            for (int i=0 ; i<ncols ; i++) {
                if (imagPart((*this)(j,i))==0)
                    fprintf(fp,"%1g%c",realPart((*this)(j,i)), i < ncols-1 ? '\t' : '\n');
                else if (imagPart((*this)(j,i))<0)
                    fprintf(fp,"%1g-%1gi%c",realPart((*this)(j,i)),
                    fabs(imagPart((*this)(j,i))), i < ncols-1 ? '\t' : '\n');
                else
                    fprintf(fp,"%1g+%1gi%c",realPart((*this)(j,i)),
                    fabs(imagPart((*this)(j,i))), i < ncols-1 ? '\t' : '\n');
            }
        }
        fprintf(fp,"\n");
    }

    /** Reads matrix from file in MatrixMarket format (see Maple):
        %% MatrixMarket ...
        nrows ncols
        data section (one number per line, row-wise) */
    void read(const char* file) {
        FILE* fp;
        fp = fopen(file, "r");

        if (!fp) {
            printf("File not found: %s\n", file);
            return;
        }

        char comment[256];
        fgets(comment, 255, fp);

        int nr, nc;
        fscanf(fp,"%d %d", &nr, &nc);

        printf("%snrows %d ncols %d\n", comment, nr, nc);

        resize(nr, nc);

        for (int j=0 ; j<nrows ; j++) {
            for (int i=0 ; i<ncols ; i++) {
                fscanf(fp,"%g",&(*this)(j,i));
            }
        }

        fclose(fp);
    }

    int LRdecomp(T **LR, T &d, McProgressInterface* progress=0) {
        T **b = 0;
        return solveLRdecomp(LR, b, 0, d, progress);
    }

    int solveLRdecomp(T **b, int m, McProgressInterface* progress=0) {
        int i, n = nRows();
        T dummy;

        T **LR;         /* LR decomposition of matrix */
        LR = (T **)mcdmatrix_malloc(mcuint64(n) * sizeof(T *));
        if (LR == NULL) {
            fprintf(stderr, "McDMatrix::solveLRdecomp: Not Enough Memory.\n");
            return 1;
        }

        for (i = 0; i < n; i++) {
            LR[i] = (T *)mcdmatrix_malloc(mcuint64(n) * sizeof(T));
            if (LR[i] == NULL) {
                fprintf(stderr, "McDMatrix::solveLRdecomp: Not Enough Memory (%d).\n",i);

                for (int k = 0; k < i; k++)
                    mcdmatrix_free(LR[k]);
                mcdmatrix_free(LR);

                return 1;
            }
        }

        int retVal = solveLRdecomp(LR, b, m, dummy, progress);

        for (i = 0; i < n; i++)
            mcdmatrix_free(LR[i]);
        mcdmatrix_free(LR);

        return retVal;
    }

    int solveLRdecomp(T **LR, T **b, int m, T &d, McProgressInterface* progress=0)
    {
#define SWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}
#define ISWAP(a,b) {itemp=(a);(a)=(b);(b)=itemp;}

        if (nRows() != nCols()) {
            fprintf(stderr, "McDMatrix::solveLRdecomp: must be a square matrix.\n");
            return 1;
        }

        int *ipiv;
        int i,irow=-1,j,k,l,ll,itemp;

        T dum,pivinv,temp;
        T *sol, *res, *rhs, *totalSol;

        int n = nRows();

        for (i=0; i<n; i++) {
            for (j=0; j<n; j++)
                LR[i][j] = (*this)[i][j];
        }

        ipiv     = (int *)mcdmatrix_malloc(mcuint64(n)*sizeof(int));
        sol      = (T *)mcdmatrix_malloc(mcuint64(n)*sizeof(T));
        totalSol = (T *)mcdmatrix_malloc(mcuint64(n)*sizeof(T));
        res      = (T *)mcdmatrix_malloc(mcuint64(n)*sizeof(T));
        rhs      = (T *)mcdmatrix_malloc(mcuint64(n)*sizeof(T));

        for (j=0;j<n;j++) ipiv[j]=j;

        d = T(1.0);
        for (i=0;i<n;i++) {
            if (progress && (i%20)==0) {
                progress->setProgressValue((float) (i+1.0)/n);
                if (progress->wasInterrupted()) {
                    mcdmatrix_free(rhs);
                    mcdmatrix_free(res);
                    mcdmatrix_free(totalSol);
                    mcdmatrix_free(sol);
                    mcdmatrix_free(ipiv);
                    return 1;
                }
            }

            // *** pivoting **
            // modification:
            // search only in column i for largest element
            double big = 0.0;
            for (k=i;k<n;k++) {
                double LRabs = sqrt(realPart(LR[k][i]*conjug(LR[k][i])));
                if (LRabs >= big) {
                    big=LRabs;
                    irow=k;
                }
            }

            if (irow != i && irow != -1) { 
                for (l=0;l<n;l++)
                    SWAP(LR[irow][l],LR[i][l]);
                ISWAP(ipiv[irow], ipiv[i]);
                d = -(d);
            }

            if (LR[i][i] == T(0.0)) {
                fprintf(stderr, "McDMatrix::solveLRdecomp: Singular Matrix-2\n");
                fprintf(stderr, "i, n: %d %d\n",i,n);

                mcdmatrix_free(rhs);
                mcdmatrix_free(res);
                mcdmatrix_free(totalSol);
                mcdmatrix_free(sol);
                mcdmatrix_free(ipiv);

                return(1);
            }

            pivinv = T(1.0) / LR[i][i];
            for (l=i+1;l<n;l++)
                LR[l][i] *= pivinv;

            for (ll=i+1;ll<n;ll++) {
                dum=LR[ll][i];
                for (l=i+1;l<n;l++)
                    LR[ll][l] -= LR[i][l]*dum;
            }
        } // loop i


        // *** solution for m different right hand sides ***
        for (k=0; k<m; k++) {

            for (i=0; i<n; i++)
                rhs[i] = b[k][i];

            double normRHS = 0.;
            for (i=0; i<n; i++)
                normRHS += realPart(rhs[i]*conjug(rhs[i]));
            normRHS = sqrt(normRHS);

            for (i=0; i<n; i++)
                res[i] = rhs[i];
            double normRES = normRHS;

            for (i=0; i<n; i++)
                totalSol[i] = T(0);

            //printf("normRHS, normRES: %g %g\n",normRHS, normRES);

            double eps = 1.e-5;
            int nLoop = 0;

            while (normRES > eps * normRHS && nLoop < 10) {
                // pivoting
                for (i=0; i<n; i++)
                    sol[i] = res[ipiv[i]];

                // forward substitution
                for (i=1; i<n; i++)
                    for (j=0; j<i; j++)
                        sol[i] -= LR[i][j] * sol[j];

                    // back substitution
                    for (i=n-1; i>=0; i--) {
                        for (j=i+1; j<n; j++)
                            sol[i] -= LR[i][j] * sol[j];
                        sol[i] /= LR[i][i];
                    }

                    for (i=0; i<n; i++)
                        totalSol[i] += sol[i];

                    for (i=0; i<n; i++) {
                        res[i] = rhs[i];

                        for (j=0; j<n; j++)
                            res[i] -= (*this)[i][j] * totalSol[j];
                    }

                    normRES = 0;
                    for (i=0; i<n; i++)
                        normRES += realPart(res[i]*conjug(res[i]));
                    normRES = sqrt(normRES);

                    nLoop++;
            }

            if (normRHS > 0) {
                double error = normRES / normRHS;
                if (error>1e-4)
                    printf("Warning: norm(residuum) / norm(rhs) = %g \n", error);
            }

            for (i=0; i<n; i++)
                b[k][i] = totalSol[i];
        }

        mcdmatrix_free(rhs);
        mcdmatrix_free(res);
        mcdmatrix_free(totalSol);
        mcdmatrix_free(sol);
        mcdmatrix_free(ipiv);

        return(0);
    }

    /// Inverse of a matrix.
    McDMatrix<T>& inverse(McProgressInterface* progress=0) {
        if (nRows() != nCols()) {
            fprintf(stderr, "McDMatrix::det: matrix must be a square matrix.\n");
            return *this;
        }

        int i, n = nRows();

        // set up rhs (identity)
        T **b = (T **)mcdmatrix_malloc(mcuint64(n) * sizeof(T *));
        for (i = 0; i < n; i++) {
            b[i] = (T *)mcdmatrix_malloc(mcuint64(n) * sizeof(T));
            memset(b[i],0,n*sizeof(T));
            b[i][i] = 1.0;
        }

        solveLRdecomp(b,n,progress);

        for (int j=0 ; j<ncols ; j++) {
            for (int i=0 ; i<nrows ; i++)
                (*this)(i,j) = b[j][i];
        }

        for (i = 0; i < n; i++)
            mcdmatrix_free(b[i]);
        mcdmatrix_free(b);

        return (*this);
    }

    /// Determinant of a matrix
    T det(McProgressInterface* progress=0) {
        if (nRows() != nCols()) {
            fprintf(stderr, "McDMatrix::det: matrix must be a square matrix.\n");
            return 0;
        }

        T d = T(1.0);
        T **LR;         /* LR decomposition of matrix */
        int i, n = nRows();

        LR = (T **)mcdmatrix_malloc(mcuint64(n) * sizeof(T *));
        if (LR == NULL) {
            fprintf(stderr, "McDMatrix::det: Not Enough Memory.\n");
            return 0;
        }
        for (i = 0; i < n; i++) {
            LR[i] = (T *)mcdmatrix_malloc(mcuint64(n) * sizeof(T));
            if (LR[i] == NULL) {
                fprintf(stderr, "McDMatrix::det: Not Enough Memory (%d).\n",i);
                return 0;
            }
        }

        LRdecomp(LR, d, progress);
        for (i=0; i<n; i++) {
            d *= LR[i][i];
        }

        for (i = 0; i < n; i++)
            mcdmatrix_free(LR[i]);
        mcdmatrix_free(LR);

        return d;
    }

    /// Reduce real symmetric matrix to tridiagonal form (Householder method).
    /// This is taken from "Numerical Recipes in C", chapter 11.2, page 474 and
    /// converted to work with indices 0 ... n-1 instead of 1 ... n.
    void tred2(T* d, T* e) {
        const int n = nRows();

        int l,k,j,i;
        T scale,hh,h,g,f;

        for (i=n-1;i>=1;i--) {
            l=i-1;
            h=scale=0.0;
            if (l > 0) {
                for (k=0;k<=l;k++)
                    scale += fabs((*this)(i,k));
                if (scale == 0.0)
                    e[i]=(*this)(i,l);
                else {
                    for (k=0;k<=l;k++) {
                        (*this)(i,k) /= scale;
                        h += (*this)(i,k)*(*this)(i,k);
                    }
                    f=(*this)(i,l);
                    g = (f>=0.0 ? -sqrt(h) : sqrt(h));
                    e[i]=scale*g;
                    h -= f*g;
                    (*this)(i,l)=f-g;
                    f=0.0;
                    for (j=0;j<=l;j++) {
                        // Next statement can be omitted if
                        // Eigenvectors are not wanted.
                        (*this)(j,i)=(*this)(i,j)/h;
                        g=0.0;
                        for (k=0;k<=j;k++)
                            g += (*this)(j,k)*(*this)(i,k);
                        for (k=j+1;k<=l;k++)
                            g += (*this)(k,j)*(*this)(i,k);
                        e[j]=g/h;
                        f += e[j]*(*this)(i,j);
                    }
                    hh=f/(h+h);
                    for (j=0;j<=l;j++) {
                        f=(*this)(i,j);
                        e[j]=g=e[j]-hh*f;
                        for (k=0;k<=j;k++)
                            (*this)(j,k) -= (f*e[k]+g*(*this)(i,k));
                    }
                }
            } else
                e[i]=(*this)(i,l);
            d[i]=h;
        }

        // Next statement can be omitted if Eigenvectors are not wanted.
        d[0]=0.0;
        e[0]=0.0;

        // Contents of this loop can be omitted if Eigenvectors not are
        // wanted, except for statement d[i]=(*this)(i,i);
        for (i=0;i<n;i++) {
            l=i-1;
            if (d[i]) {
                for (j=0;j<=l;j++) {
                    g=0.0;
                    for (k=0;k<=l;k++)
                        g += (*this)(i,k)*(*this)(k,j);
                    for (k=0;k<=l;k++)
                        (*this)(k,j) -= g*(*this)(k,i);
                }
            }
            d[i]=(*this)(i,i);
            (*this)(i,i)=1.0;
            for (j=0;j<=l;j++) (*this)(j,i)=(*this)(i,j)=0.0;
        }
    }

    T sign(T a, T b) {
        return ((b) >= 0.0 ? fabs(a) : -fabs(a));
    }

    /// Reduce real tridiagonal symmetric matrix to diagonal form (iterative QL decomposition).
    /// This is taken from "Numerical Recipes in C", chapter 11.3, page 480 and
    /// converted to work with indices 0 ... n-1 instead of 1 ... n.
    void tqli(T* d, T* e) {
        const int n = nRows();

        // Determine machine dependent epsilon.
        T unit=1.0, eps=1.e-10, macheps;
        while (unit + eps > unit && eps > 1.e-35)
            eps *= 0.5;
        macheps = eps;

        int m,l,iter,i,k;
        T s,r,p,g,f,dd,c,b;

        for (i=1;i<n;i++) e[i-1]=e[i];
        e[n-1]=0.0;
        for (l=0;l<n;l++) {
            iter=0;
            do {
                for (m=l;m<n-1;m++) {
                    dd=fabs(d[m])+fabs(d[m+1]);
                    //if (fabs(e[m])+dd == dd) break;
                    if (fabs(e[m]) <= macheps * dd) break;
                }
                if (m != l) {
                    if (iter++ == 30) {
                        printf("Too many iterations in TQLI\n");
                        return;
                    }
                    g=(d[l+1]-d[l])/(2.0*e[l]);
                    r=sqrt((g*g)+1.0);
                    g=d[m]-d[l]+e[l]/(g+sign(r,g));
                    s=c=1.0;
                    p=0.0;
                    for (i=m-1;i>=l;i--) {
                        f=s*e[i];
                        b=c*e[i];
                        if (fabs(f) >= fabs(g)) {
                            c=g/f;
                            r=sqrt((c*c)+1.0);
                            e[i+1]=f*r;
                            c *= (s=1.0/r);
                        } else {
                            s=f/g;
                            r=sqrt((s*s)+1.0);
                            e[i+1]=g*r;
                            s *= (c=1.0/r);
                        }
                        g=d[i+1]-p;
                        r=(d[i]-g)*s+2.0*c*b;
                        p=s*r;
                        d[i+1]=g+p;
                        g=c*r-b;
                        // Next loop can be omitted if
                        // Eigenvectors are not wanted.
                        for (k=0;k<n;k++) {
                            f=(*this)(k,i+1);
                            (*this)(k,i+1)=s*(*this)(k,i)+c*f;
                            (*this)(k,i)=c*(*this)(k,i)-s*f;
                        }
                    }
                    d[l]=d[l]-p;
                    e[l]=g;
                    e[m]=0.0;
                } else {
                    i = 0;
                    // printf("l, iter, e/dd: %d %d %10.3g\n",
                    //         l,iter,fabs(e[m])/dd);
                }
            } while (m != l);
        }
    }

    /// Computes Eigenvectors and Eigenvalues of a symmetric matrix.
    /// Eigenvectors are stored in the columns of matrix @c u (which needs to be
    /// of the same size as this matrix), Eigenvalues in a buffer pointed to by
    /// @c d (which needs to be nRows() in size).
    int eigenSystem(McDMatrix<T>& u, T *d, McProgressInterface* progress=0) {
        const int r = nRows();
        const int c = nCols();

        int i, j;

        if (r != c) {
            fprintf(stderr, "McDMatrix::eigenSystem: Must be a square matrix.\n");
            return 1;
        }

        // e contains the off-diagonal elements.
        T *e = (T*) mcdmatrix_malloc(mcuint64(r)*sizeof(T));

        if (d==NULL || e==NULL) {
            fprintf(stderr, "McDMatrix::eigenSystem: NULL pointer argument.\n");
            return 1;
        }

        // u is a copy of the matrix, which will contain the Eigenvectors later.
        for (i=0; i<r; i++)
            for (j=0; j<r; j++)
                u(i,j) = (*this)(i,j);

        // Note: We had some problems with these methods during DTI computations.
        // It seems in rare cases the order of the Eigenvalues does not match the
        // order of the Eigenvectors. Unfortunately, we were not able to track
        // down the problem.
        u.tred2(d,e);
        u.tqli(d,e);

        mcdmatrix_free(e);

        return 0;
    }

    /// Compute singular value decomposition of matrix, i.e. compute u, w and v
    /// such that
    ///
    ///     this = u w v(trans)
    ///
    /// Matrix w is returned as diagonal vector only, since all its other
    /// elements are 0. Matrices @c u and @c v do not need to be initialized,
    /// but @c w needs to point to a buffer of nRows() elements in size.
    int SVD(McDMatrix<T>& u, T* w, McDMatrix<T>& v, int maxits=30) {
        int flag,i,its,j,jj,k,l=-1,nm=-1;
        T anorm,c,f,g,h,s,scale,x,y,z;

        int m = nrows;
        int n = ncols;

        T *rv1 = (T*) mcdmatrix_malloc(mcuint64(n)*sizeof(T));

        u = (*this);
        v.resize(n,n);

        g=scale=anorm=0.0;

        for (i=0;i<n;i++) {
            l=i+1;
            rv1[i]=scale*g;
            g=s=scale=0.0;
            if (i < m) {
                for (k=i;k<m;k++) scale += fabs(u[k][i]);
                if (scale) {
                    for (k=i;k<m;k++) {
                        u[k][i] /= scale;
                        s += u[k][i]*u[k][i];
                    }
                    f=u[i][i];
                    g = -sign(sqrt(s),f);
                    h=f*g-s;
                    u[i][i]=f-g;
                    for (j=l;j<n;j++) {
                        for (s=0.0,k=i;k<m;k++) s += u[k][i]*u[k][j];
                        f=s/h;
                        for (k=i;k<m;k++) u[k][j] += f*u[k][i];
                    }
                    for (k=i;k<m;k++) u[k][i] *= scale;
                }
            }
            w[i]=scale *g;
            g=s=scale=0.0;
            if (i < m && i != n-1) {
                for (k=l;k<n;k++) scale += fabs(u[i][k]);
                if (scale) {
                    for (k=l;k<n;k++) {
                        u[i][k] /= scale;
                        s += u[i][k]*u[i][k];
                    }
                    f=u[i][l];
                    g = -sign(sqrt(s),f);
                    h=f*g-s;
                    u[i][l]=f-g;
                    for (k=l;k<n;k++) rv1[k]=u[i][k]/h;
                    for (j=l;j<m;j++) {
                        for (s=0.0,k=l;k<n;k++) s += u[j][k]*u[i][k];
                        for (k=l;k<n;k++) u[j][k] += s*rv1[k];
                    }
                    for (k=l;k<n;k++) u[i][k] *= scale;
                }
            }
            anorm=fmax(anorm,(fabs(w[i])+fabs(rv1[i])));
        }
        for (i=n-1;i>=0;i--) {
            if (i < n-1) {
                if (g) {
                    for (j=l;j<n;j++)
                        v[j][i]=(u[i][j]/u[i][l])/g;
                    for (j=l;j<n;j++) {
                        for (s=0.0,k=l;k<n;k++) s += u[i][k]*v[k][j];
                        for (k=l;k<n;k++) v[k][j] += s*v[k][i];
                    }
                }
                for (j=l;j<n;j++) v[i][j]=v[j][i]=0.0;
            }
            v[i][i]=1.0;
            g=rv1[i];
            l=i;
        }
        for (i=imin(m-1,n-1);i>=0;i--) {
            l=i+1;
            g=w[i];
            for (j=l;j<n;j++) u[i][j]=0.0;
            if (g) {
                g=1.0f/g;
                for (j=l;j<n;j++) {
                    for (s=0.0,k=l;k<m;k++) s += u[k][i]*u[k][j];
                    f=(s/u[i][i])*g;
                    for (k=i;k<m;k++) u[k][j] += f*u[k][i];
                }
                for (j=i;j<m;j++) u[j][i] *= g;
            } else for (j=i;j<m;j++) u[j][i]=0.0;
            ++u[i][i];
        }

        for (k=n-1;k>=0;k--) {
            for (its=1; its<=maxits; its++) {
                flag=1;
                for (l=k;l>=0;l--) {
                    nm=l-1;
                    // assure a break in case l == 0
                    //   (generally rv1[0] = 0)
                    // otherwise there will be access to w[nm=-1]
                    // and u[j][nm=-1] in the following sections
                    if (l == 0 ||
                        (float)(fabs(rv1[l])+anorm) == (float)anorm) {
                        flag=0;
                        break;
                    }
                    if ((float)(fabs(w[nm])+anorm) == (float)anorm) {
                        break;
                    }
                }
                if (flag) {
                    c=0.0;
                    s=1.0;
                    for (i=l;i<=k;i++) {
                        f=s*rv1[i];
                        rv1[i]=c*rv1[i];
                        if ((float)(fabs(f)+anorm) == (float)anorm) break;
                        g=w[i];
                        h=pythag(f,g);
                        w[i]=h;
                        h=1.0f/h;
                        c=g*h;
                        s = -f*h;
                        for (j=0;j<m;j++) {
                            y=u[j][nm];
                            z=u[j][i];
                            u[j][nm]=y*c+z*s;
                            u[j][i]=z*c-y*s;
                        }
                    }
                }
                z=w[k];
                if (l == k) {
                   if (z < 0.0) {
                        w[k] = -z;
                        for (j=0;j<n;j++) v[j][k] = -v[j][k];
                    }
                    break;
                }
                if (its == maxits) {
                    printf("no convergence in %d svd iterations \n",
                           maxits);
                    mcdmatrix_free(rv1);
                    return 0;
                }
                x=w[l];
                nm=k-1;
                y=w[nm];
                g=rv1[nm];
                h=rv1[k];
                f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0f*h*y);
                g=pythag(f,1.0);
                f=((x-z)*(x+z)+h*((y/(f+sign(g,f)))-h))/x;
                c=s=1.0;
                for (j=l;j<=nm;j++) {
                    i=j+1;
                    g=rv1[i];
                    y=w[i];
                    h=s*g;
                    g=c*g;
                    z=pythag(f,h);
                    rv1[j]=z;
                    c=f/z;
                    s=h/z;
                    f=x*c+g*s;
                    g = g*c-x*s;
                    h=y*s;
                    y *= c;
                    for (jj=0;jj<n;jj++) {
                        x=v[jj][j];
                        z=v[jj][i];
                        v[jj][j]=x*c+z*s;
                        v[jj][i]=z*c-x*s;
                    }
                    z=pythag(f,h);
                    w[j]=z;
                    if (z) {
                        z=1.0f/z;
                        c=f*z;
                        s=h*z;
                    }
                    f=c*g+s*y;
                    x=c*y-s*g;
                    for (jj=0;jj<m;jj++) {
                        y=u[jj][j];
                        z=u[jj][i];
                        u[jj][j]=y*c+z*s;
                        u[jj][i]=z*c-y*s;
                    }
                }
                rv1[l]=0.0;
                rv1[k]=f;
                w[k]=x;
            }
        }
        mcdmatrix_free(rv1);
        return 1;
    }

    /** Moore-Penrose pseudo-inverse of a matrix (double or float).
    This method is using SVD.

    If the caller does not supply a threshold \param eps > 0 for singular
    value rejection, An estimation based on: max(rowdim(MP), coldim(MP)) * smax
    will be used, where smax is the maximum singular value.

    If the entries are all of the same magnitude q straight forward way:
      McDMatrix<double> DT(GS);
      DT.transpose();
      McDMatrix<double> Q(DT);
      Q *= GS;
      Q.inverse();
      Q *= DT;
    might also be used for the calculation of the pseudo inverse */
    McDMatrix<T> pseudoInverse(McDMatrix<T> MP, double eps = -1.0)
    {
        // McDMatrix::inverse modifies itself instead of returning a copy
        McDMatrix<T> u, v;
        int      i;
        T * w = (T *) mcdmatrix_malloc(mcuint64(MP.nCols()) * sizeof(T));

        // singular value decomposition
        if ( MP.SVD(u,w,v) ) {

            // now calculate the threshold for rejecting singular values
            if (eps < 0) { // otherwise use the one supplied
                int maximum = 0;
                for (i=1; i < MP.nCols(); i++) {
                    if ( w[i]>w[maximum] )
                        maximum = i;
                }
                int dmax = (MP.nCols() > MP.nRows() ? MP.nCols() : MP.nRows());
                eps = w[maximum] * dmax * 1.e-6;
                // printf("eps that is used in pinv: %g", eps);
            }

            McDMatrix<T> SigmaPlus(MP.nCols(), MP.nCols());
            SigmaPlus.fill(0);

            for (i=0; i < MP.nCols(); i++) { // A^+ is inverse of w and multiply again
                if ( w[i] > eps ) // should we make an interface for that?
                    SigmaPlus(i, i) = 1.0/w[i];
                // printf("singular values[%d] %g", i, w[i]);
            }

            u *= SigmaPlus;
            u *= v.transpose();

            mcdmatrix_free(w);
        }

        return u;
    }

    /** Computes PCA of samples represented by the columns of the matrix.
        \param mean average over all samples
        \param eigenVals eigenvalues of covariance matrix sorted
                         in decending order of magnitude
        \param modes eigenvectors of covariance matrix sorted
                     in decending order of magnitude of corresponding
                     eigenvalue
        \param weights expansion coefficients of samples into eigenvectors
    */
    void pca(McDArray<T>& mean, McDArray<T>& eigenVals,
             McDArray<McDArray<T> >& modes,
             McDArray<McDArray<T> >& weights,
             McProgressInterface* progress=0)
    {
        int i,j,k;

        McDMatrix<T>& trainingSet = (*this);

        // Number of elements in the training set
        int setSize = trainingSet.nCols();

        // Size of one element
        int elementSize = trainingSet.nRows();

        if (setSize<1 || elementSize<1) {
            mean.resize(0);
            eigenVals.resize(0);
            modes.resize(0);
            weights.resize(0);
            return;
        }

        // Compute mean
        mean.resize(elementSize); mean.fill(0);
        for (i=0; i<elementSize; i++) {
            for (j=0; j<setSize; j++)
                mean[i] += trainingSet(i,j);
            mean[i] /= setSize;
        }

        McDArray<int> modeOrder;

        // Trivial case: only one element in the set
        if (setSize==1) {
            modes.resize(0);
            eigenVals.resize(0);
            weights.resize(1); weights[0].resize(0);
            modeOrder.resize(0);
            return;
        }

        // Compute deviations from mean
        McDMatrix<T> devMean(elementSize, setSize);

        for (i=0; i<elementSize; i++) {
            for (j=0; j<setSize; j++)
                devMean(i,j) = trainingSet(i,j) - mean[i];
        }

        enum { SET_LARGE=0, SET_SMALL } pcaCase;

        // Compute covariance matrix
        McDMatrix<double> cov;

        if ( setSize<elementSize ) pcaCase = SET_SMALL;
        else pcaCase = SET_LARGE;

        int n = (pcaCase==SET_SMALL) ? setSize : elementSize;

        cov.resize(n,n);
        cov.fill(0.0);

        if ( pcaCase==SET_SMALL )
        {
            for (i=0; i<setSize; i++)
            {
                if ( progress ) 
                {
                    progress->setProgressInfo("Step 1/3: computing covariance matrix");
                    progress->setProgressValue(float(i)/((float)setSize-1.));
                    if ( progress->wasInterrupted() ) return;
                }

                for (j=i; j<setSize; j++) {
                    for (k=0; k<elementSize; k++)
                        cov(i,j) += double(devMean(k,i) * devMean(k,j));
                    cov(i,j) /= double(setSize);
                    cov(j,i) = cov(i,j);
                }
            }
        }
        else
        {
            for (i=0; i<elementSize; i++) {
                for (j=i; j<elementSize; j++) {
                    for (k=0; k<setSize; k++)
                        cov(i,j) += double(devMean(i,k) * devMean(j,k));
                    cov(i,j) /= double(setSize);
                    cov(j,i) = cov(i,j);
                }
            }
        }

        // Compute eigenvectors and eigenvalues of covariance matrix
        // in double precision
        McDMatrix<double> eigenVecs(n,n);
        McDArray<double> eigenValsD(n);

        cov.eigenSystem(eigenVecs, eigenValsD);

        // Sort eigenvalues (naive sorting in O(n*n) time)
        McBitfield visited(n);  visited.unsetAll();
        modeOrder.resize(n);

        for (i=0; i<n; i++) {
            double max = -1.0;
            int index = -1;
            for (j=0; j<n; j++) {
                if (visited[j]) continue;
                if (fabs(eigenValsD[j])>max) {
                    max = eigenValsD[j];
                    index = j;
                }
            }

            assert(index!=-1);
            visited.set(index);
            modeOrder[i] = index;
        }

        int nModes = (pcaCase==SET_SMALL) ? n-1 : n;

        // Copy eigenvalues in descending order
        eigenVals.resize(nModes);
        for (i=0; i<nModes; i++) {
            eigenVals[i] = eigenValsD[modeOrder[i]];
        }

        // Compute modes in descending order
        modes.resize(nModes);
        for (i=0; i<nModes; i++) {
            modes[i].resize(elementSize);
            modes[i].fill(0);
        }

        for (k=0; k<nModes; k++)
        {
            if ( progress ) 
            {
                progress->setProgressInfo("Step 2/3: computing modes");
                progress->setProgressValue(float(k)/((float)nModes-1.));
                if ( progress->wasInterrupted() ) return;
            }

            if ( pcaCase==SET_SMALL ) {
                for (i=0; i<elementSize; i++) {
                    for (j=0; j<setSize; j++) {
                        modes[k][i] += devMean(i,j)*eigenVecs(j,modeOrder[k]);
                    }
                }
            }
            else {
                for (i=0; i<elementSize; i++) {
                    modes[k][i] = eigenVecs(i,modeOrder[k]);
                }
            }

            // Normalize modes
            double norm = 0.0;
            for (i=0; i<elementSize; i++)
                norm += modes[k][i]*modes[k][i];
            if ( norm==0 ) continue;
            norm = sqrt(norm);

            for (i=0; i<elementSize; i++)
                modes[k][i] /= norm;
        }

        // Compute weights (representation as linear combination of modes)
        weights.resize(setSize);
        for (i=0; i<setSize; i++) { weights[i].resize(nModes); weights[i].fill(0); }

        for (k=0; k<setSize; k++)
        {
            if ( progress ) 
            {
                progress->setProgressInfo("Step 3/3: computing weights");
                progress->setProgressValue(float(k)/((float)setSize-1.));
                if ( progress->wasInterrupted() ) return;
            }

            for (i=0; i<nModes; i++) {
                for (j=0; j<elementSize; j++) {
                    weights[k][i] += modes[i][j]*devMean(j,k);
                }
            }
        }
    }


protected:
    int nrows;
    int ncols;
    T *data; // Pointer to internal buffer

    // some utility functions
    T fmax(T a, T b) {
        return (a > b ? a : b);
    }

    int imin(int a, int b) {
        return (a < b ? a : b);
    }

    T sqr(T a) { return a*a; }

    T pythag(T a, T b) {
        T absa,absb;
        absa=(T) fabs(a);
        absb=(T) fabs(b);
        if (absa > absb)
            return (T) absa*sqrt(1.0f+sqr(absb/absa));
        else
            return (T) (absb == 0.0 ? 0.0 : absb*sqrt(1.0+sqr(absa/absb)));
    }

public:
    void dumpMatrix(MC_ostream & os) const {
        if(!size()) return;

        int i,j;
        const T * p = dataPtr();
        T tmax = *p;
        T tmin = *p;
        p++;

        for(i=size()-1; i; i--){
            if(tmax < *p)
                tmax = *p;
            else if(tmin > *p)
                tmin = *p;
            p++;
        }

        if(tmin < 0 && tmax > 0){
            os << tmin << " <= z...a < 0 <= A...Z <= " << tmax << "\n\n";
            p = dataPtr();
            for(j=0; j<nRows(); j++){
                for(i=0; i<nCols(); i++){
                    if(*p>=0)
                        os << char(*p/tmax*('Z'-'A')+'A');
                    else
                        os << char(*p/tmin*('z'-'a')+'a');
                    p++;
                }
                os << "\n";
            }
        }  else {
            char minC,maxC;
            if(tmin >= 0){
                minC = 'A';
                maxC = 'Z';
            } else {
                minC = 'z';
                maxC = 'a';
            }

            os << tmin << " <= " << minC << "..." << maxC
               << " <= " << tmax << "\n\n";

            p = dataPtr();
            float factor = (tmax != tmin) ? (maxC-minC)/(tmax-tmin) : 0;
            for(j=0; j<nRows(); j++){
                for(i=0; i<nCols(); i++){
                    os << char((*p-tmin)*factor+minC);
                    p++;
                }
                os << "\n";
            }

        }
    }
};

/// @if EXCLUDETHIS

template<>
inline float McDMatrix<float>::conjug(const float& z){
    return z;
}

template<>
inline double McDMatrix<double>::conjug(const double& z){
    return z;
}

template<>
inline double McDMatrix<float>::realPart(const float& z){
    return z;
}

template<>
inline double McDMatrix<double>::realPart(const double& z){
    return z;
}

template<>
inline double McDMatrix<float>::imagPart(const float& z){
    return 0;
}

template<>
inline double McDMatrix<double>::imagPart(const double& z){
    return 0;
}


template<>
inline MC_complex<float> McDMatrix<MC_complex<float> >::conjug(const MC_complex<float>& z)
{
    return MC_conj(z);
}

template<>
inline MC_complex<double> McDMatrix<MC_complex<double> >::conjug(const MC_complex<double>& z)
{
    return MC_conj(z);
}

template<>
inline double McDMatrix<MC_complex<float> >::realPart(const MC_complex<float>& z)
{
    return MC_real(z);
}

template<>
inline double McDMatrix<MC_complex<double> >::realPart(const MC_complex<double>& z)
{
    return MC_real(z);
}

template<>
inline double McDMatrix<MC_complex<float> >::imagPart(const MC_complex<float>& z)
{
    return MC_imag(z);
}

template<>
inline double McDMatrix<MC_complex<double> >::imagPart(const MC_complex<double>& z)
{
    return MC_imag(z);
}


template<>
inline int McDMatrix<MC_complex<float> >::eigenSystem(McDMatrix<MC_complex<float> >& u,
                                                   MC_complex<float> *d,
                                                   McProgressInterface* progress)
{
    fprintf(stderr, "eigenSystem not implemented for complex<float>\n");
    return 0;
}

template<>
inline int McDMatrix<MC_complex<double> >::eigenSystem(McDMatrix<MC_complex<double> >& u,
                                                    MC_complex<double> *d,
                                                    McProgressInterface* progress)
{
    fprintf(stderr, "eigenSystem not implemented for complex<double>\n");
    return 0;
}

template<>
inline int McDMatrix<MC_complex<float> >::SVD(McDMatrix<MC_complex<float> >& u,
                                           MC_complex<float>* w,
                                           McDMatrix<MC_complex<float> >& v,
                                           int maxits)
{
    fprintf(stderr, "SVD not implemented for complex<float>\n");
    return 0;
}

template<>
inline int McDMatrix<MC_complex<double> >::SVD(McDMatrix<MC_complex<double> >& u,
                                            MC_complex<double>* w,
                                            McDMatrix<MC_complex<double> >& v,
                                            int maxits)
{
    fprintf(stderr, "SVD not implemented for complex<double>\n");
    return 0;
}

template<>
inline void McDMatrix<MC_complex<float> >::pca(McDArray<MC_complex<float> >& mean,
                                            McDArray<MC_complex<float> >& eigenVals,
                                            McDArray<McDArray<MC_complex<float> > >& modes,
                                            McDArray<McDArray<MC_complex<float> > >& weights,
                                            McProgressInterface* progress)
{
    fprintf(stderr, "pca not implemented for complex<float>\n");
}

template<>
inline void McDMatrix<MC_complex<double> >::pca(McDArray<MC_complex<double> >& mean,
                                             McDArray<MC_complex<double> >& eigenVals,
                                             McDArray<McDArray<MC_complex<double> > >& modes,
                                             McDArray<McDArray<MC_complex<double> > >& weights,
                                             McProgressInterface* progress)
{
    fprintf(stderr, "pca not implemented for complex<double>\n");
}

/// @endif

#endif

/// @}

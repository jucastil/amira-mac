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
#ifndef MC_SPARSE_MATRIX_H
#define MC_SPARSE_MATRIX_H

#include "McDArray.h"
#include "McSmallArray.h"
#include "McProgressInterface.h"

#if defined (HX_HAS_STDCOMPLEX)
#  include <complex>
#else
#  include <complex.h>
#endif

#include "McStdlib.h"
#include "McWinDLLApi.h"

/** A template class for sparse matrices.  The first template parameter
    should be one of float, double, complex<float> or complex<double>.
    The second parameter is a boolean value specifying whether the
    matrix is symmetric or not.  Symmetric matrices automatically
    use special algorithms and need less memory. */
template<class T, bool SYMMETRIC> class McSparseMatrix
{
protected:
    struct MatrixEntry{
	MatrixEntry() : value(T(0)), col(0){};

	MatrixEntry(const T& newVal, int column){
	    value = newVal;
	    col = column;
	}

	T value;
	int col;
    };

    ///
    McDArray<McSmallArray<MatrixEntry, 10> > data;

    ///
    int numCols;

public:
    /// Default Constructor
    McSparseMatrix() : numCols(0) {
	data.clear();
    }

    ///
    McSparseMatrix(int n) : numCols(n) {
	data.resize(n);
	for (int i=0; i<n; i++){
	    data[i].resize(1);
	    data[i][0] = MatrixEntry(T(0), i);
	}
    }

    ///
    McSparseMatrix(int rows, int columns) : numCols(columns) {
	if (SYMMETRIC)
	    assert(rows==columns);

	data.resize(rows);
    }

    /// Index operator.  Only for element reading.
    T operator()(int i, int j) const {
	assert(i>=0 && i<data.size() && j>=0 && j<numCols);
	for (int k=0; k<data[i].size(); k++)
	    if (data[i][k].col==j)
		return data[i][k].value;

	return T(0);
    }

    /// Multiplication with a scalar
    void operator*=(const T& scalar) {
	int i, j;
	for (i=0; i<data.size(); i++)
	    for (j=0; j<data[i].size(); j++)
		data[i][j].value *= scalar;
    }

    ///
    void init(const int n) {
	numCols = n;
	data.resize(n);
	for (int i=0; i<n; i++){
	    data[i].resize(1);
	    data[i][0] = MatrixEntry(T(0), i);
	}
    }

    ///
    void resize(int m, int n) {
	assert(m>=0 && n>=0);

	data.resize(m);
	int i, j;
	if (numCols>n)
	    for (i=0; i<m; i++)
		for (j=data[i].size()-1; j>=0; j--)
		    if (data[i][j].col>=n)
			data[i].remove(j);

	numCols = n;
    }

    ///
    void resizeRows(int n){
	if (SYMMETRIC)
	    assert(false);
	assert(n>=0);
	data.resize(n);
    }

    /// The number of rows of the matrix
    int nRows() const {
	return data.size();
    }

    /// The number of columns of the matrix
    int nCols() const {
	return numCols;
    }

    /// The number of elements
    int nElements() const {
	int nElem = 0;
	int i;
	for (i=0; i<nRows(); i++)
	    nElem += data[i].size();
	return nElem;
    }

    /// Quadratic matrix or not?
    bool isQuadratic() const {
	return nRows()==nCols();
    }

    /// Test the matrix for symmetry
    bool isSymmetric(float epsilon=1.e-6) {
        if ( !isQuadratic() ) return false;

        int i, j, n=data.size();

        for (i=0; i<data.size(); i++) {

            T diagElem = (*this)(i,i);

            for (j=0; j<data[i].size(); j++) {

                int col = data[i][j].col;
                if ( col<=i ) continue;

                T& e1 = data[i][j].value;
                T e2 = (*this)(col,i);

                double norm1 = sqrt( realPart(e1*conjug(e1)) );
                double norm2 = sqrt( realPart(e2*conjug(e2)) );

                T delta = e1-e2;
                double norm = sqrt( realPart(delta*conjug(delta)) );

                //double maxNorm = norm1>norm2 ? norm1 : norm2;
                double maxNorm = sqrt( realPart(diagElem*conjug(diagElem)) );
                if ( norm>epsilon*maxNorm ) return false;
            }
        }

        return true;
    }

    /// Create symmetric matrix by removing upper right part
    void makeSymmetric(McSparseMatrix<T,true>& sym) {

        sym.init( nRows() );

        int i, j;

        for (i=0; i<data.size(); i++) {
            for (j=0; j<data[i].size(); j++) {

                int col = data[i][j].col;
                if ( col>i ) continue;

                T& elem = data[i][j].value;

                sym.setEntry(i,col, elem);
            }
        }
    }

    /** Copy the lower left part into the upper right part.
        While the result is still symmetric from a mathematical point of view,
        the SYMMETRIC template parameter of the result is set to false.
        Hence, everything is prepared to make non-symmetric modifications.
        This function can be seen as the opposite to makeSymmetric().
    */
    void fillSymmetric(McSparseMatrix< T, false >& Result) const
    {
        Result.init(0);
        Result.resize(nRows(), nCols());

        for (int i=0; i<data.size(); i++) {
            for (int j=0; j<data[i].size(); j++) {
                const int col = data[i][j].col;
                if (col <= i) {
                    Result.setEntry(i, col, data[i][j].value);
                    if (col != i) {
                        Result.setEntry(col, i, data[i][j].value);
                    }
                } else {
                    assert(false); //Not symmetric in the first place
                }
            }
        }
    }

    ///Clears an entire row
    void clearRow(const int iRow)
    {
        mcrequire(iRow >= 0);
        mcrequire(iRow < nRows());

        data[iRow].clear();
    }

    ///
    void setEntry(int i, int j, const T& newValue) {
	for (int k=0; k<data[i].size(); k++)
	    if (data[i][k].col==j){
		data[i][k].value = newValue;
		return;
	    }

	data[i].append(MatrixEntry(newValue, j));
    }

    ///
    void addToEntry(int i, int j, const T& newValue) {
	for (int k=0; k<data[i].size(); k++)
	    if (data[i][k].col==j){
		data[i][k].value += newValue;
		return;
	    }

	data[i].append(MatrixEntry(newValue, j));
    }

    ///A helper class to iterate over a symmetric matrix during multiplication with itself
    struct SymmetricMatrixIter
    {
        SymmetricMatrixIter(const McSmallArray< MatrixEntry, 10 >& First, const McSmallArray< MatrixEntry, 10 >& Second)
                :FirstPart(First)
                ,SecondPart(Second)
                ,SubIndex(-1)
        {
            ActivePart = &FirstPart;
        }

        const McSmallArray< MatrixEntry, 10 >& FirstPart;
        const McSmallArray< MatrixEntry, 10 >& SecondPart;

        const MatrixEntry* next()
        {
            SubIndex++;

            //End of active part?
            if (ActivePart->size() <= SubIndex) {
                if (ActivePart == &SecondPart) {
                    return NULL;
                } else {
                    //Go to the second part
                    if (SecondPart.size() <= 1) return NULL;
                    ActivePart = &SecondPart;
                    SubIndex = 1; //We should use the diagonal only once, right?
                }
            }

            //Get the current element
            return &(*ActivePart)[SubIndex];
        }

    private:
        int SubIndex;
        const McSmallArray< MatrixEntry, 10 >* ActivePart;
    };

    ///Multiply a symmetric matrix with itself
    void squareSym(McSparseMatrix& Result) const
    {
        if (SYMMETRIC) {
            const int numRows = nRows();
            //const int numCols = nCols();

            //Create a lookup for the columns
            McDArray< McSmallArray< MatrixEntry, 10 > > ColLookup;
            ColLookup.remax(-1, numCols);
            for (int i=0; i<numRows; i++) {
                const McSmallArray< MatrixEntry, 10 >& Row = data[i];
                for (int k=Row.size()-1; k>=0; k--) {
                    const MatrixEntry& Entry = Row[k];

                    ColLookup[Entry.col].append(Entry);
                    ColLookup[Entry.col].last().col = i;
                }
            }

            //Multiply with itself
            for (int i=0; i<numRows; i++) {
                SymmetricMatrixIter RowIter(data[i], ColLookup[i]);
                const MatrixEntry* RowItem = RowIter.next();

                while (RowItem) {
                    SymmetricMatrixIter OtherRowIter(data[RowItem->col], ColLookup[RowItem->col]);
                    const MatrixEntry* OtherRowItem = OtherRowIter.next();

                    while (OtherRowItem) {
                        if (OtherRowItem->col <= i) { //Result is symmetric, too
                            Result.addToEntry(i, OtherRowItem->col, RowItem->value * OtherRowItem->value);
                        }
                        OtherRowItem = OtherRowIter.next();
                    }

                    RowItem = RowIter.next();
                }
            }
        }
    }

    ///Computes the transpose of the matrix
    void Transpose(McSparseMatrix& Result) const
    {
        const int numRows = nRows();
        Result.init(0);
        Result.resize(numCols, numRows);

        for (int i=0; i<numRows; i++) {
            const McSmallArray< MatrixEntry, 10 >& Row = data[i];
            for (int k=Row.size()-1; k>=0; k--) {
                const MatrixEntry& Entry = Row[k];
                Result.setEntry(Entry.col, i, Entry.value);
            }
        }
    }

    ///Multiplies this matrix with the given other matrix
    void multMat(McSparseMatrix& Other, McSparseMatrix< T, false >& Result) const
    {
        //The matrices have to be compatible
        mcrequire(nCols() == Other.nRows());

        const int numRows = nRows();

        Result.init(0);
        Result.resize(numRows, Other.nCols());

        for (int i=0; i<numRows; i++) {
            const McSmallArray< MatrixEntry, 10 >& Row = data[i];
            for (int k=Row.size()-1; k>=0; k--) {
                const int col = Row[k].col;
                const McSmallArray< MatrixEntry, 10 >& OtherRow = Other.data[col];

                for (int h=OtherRow.size()-1; h>=0; h--) {
                    Result.addToEntry(i, OtherRow[h].col, Row[k].value * OtherRow[h].value);
                }
            }
        }
    }

    ///Multiplies this matrix with the given other matrix and the result is known to be symmetric, i.e., A^T * A.
    bool multMatSymResult(McSparseMatrix& Other, McSparseMatrix< T, true >& Result) const
    {
        //The matrices have to be compatible
        mcrequire(numCols == Other.nRows() && nRows() == Other.nCols());

        const int numRows = nRows();

        Result.init(0);
        Result.resize(numRows, numRows);

        for (int i=0; i<numRows; i++) {
            const McSmallArray< MatrixEntry, 10 >& Row = data[i];
            for (int k=Row.size()-1; k>=0; k--) {
                const int col = Row[k].col;
                const McSmallArray< MatrixEntry, 10 >& OtherRow = Other.data[col];

                for (int h=OtherRow.size()-1; h>=0; h--) {
                    if (i >= OtherRow[h].col) { //Symmetric result
                        Result.addToEntry(i, OtherRow[h].col, Row[k].value * OtherRow[h].value);
                    }
                }
            }
        }

        return true;
    }

    ///Multiplies a matrix with its transposed self, i.e., A^T * A. The result is symmetric.
    void ATA(McSparseMatrix< T, true >& Result)
    {
        const int numRows = nRows();

        Result.init(numCols);

        for (int i=0; i<numCols; i++) {
            const McSmallArray< MatrixEntry, 10 >& TRow = Transpose[i];
            for (int k=0; k<TRow.size(); k++) {
                const int col = TRow[k].col;
                const McSmallArray< MatrixEntry, 10 >& Row = data[col];

                for (int h=0; h<Row.size(); h++) {
                    if (i <= Row[h].col) { //Symmetric result
                        Result.addToEntry(i, Row[h].col, TRow[k].value * Row[h].value);
                    }
                }
            }
        }
    }


    /// Multiply sparse matrix with vector.
    void multVec(const McDArray<T>& v, McDArray<T>& result) const {
	int i,j,k;

	assert(v.size()==nCols());
	result.resize(nRows());
	result.fill(T(0));

	if (SYMMETRIC){

	    for (i=0; i<nRows(); i++) {
		result[i]   += (*this)(i,i) * v[i];

		for (k=1; k<data[i].size(); k++) {
		    j = data[i][k].col;
		    const T& elemIJ = data[i][k].value;
		    result[j]   += elemIJ * v[i];
		    result[i]   += elemIJ * v[j];
		}
	    }
	} else {
	    for (i=0; i<nRows(); i++)
		for (j=0; j<data[i].size(); j++)
		    result[i] += data[i][j].value * v[data[i][j].col];

	}
    }

    /// Multiply real sparse matrix with complex vector.
    void multVecC(const McDArray< MC_complex<T> >& v,
		  McDArray< MC_complex<T> >& result) const {
	int i,j,k;

	assert(v.size()==nCols());
	result.resize(nRows());
	result.fill(MC_complex<T>(0.));

	if (SYMMETRIC){

	    for (i=0; i<nRows(); i++) {
		result[i]   += (*this)(i,i) * v[i];

		for (k=1; k<data[i].size(); k++) {
		    j = data[i][k].col;
		    const T& elemIJ = data[i][k].value;
		    result[j]   += elemIJ * v[i];
		    result[i]   += elemIJ * v[j];
		}
	    }
	} else {
	    for (i=0; i<nRows(); i++)
		for (j=0; j<data[i].size(); j++)
		    result[i] += data[i][j].value * v[data[i][j].col];

	}
    }

    /// Multiply sparse matrix with multiple vectors.
    void multVecM(const McDArray< McDArray<T> >& v,
		  McDArray< McDArray<T> >& result) const {
	int i,j,k,l;

	int nRhs = v.size();
	if (nRhs == 0) return;

	result.resize(nRhs);
	for (i=0; i<nRhs; i++) {
	    assert(v[i].size()==nCols());
	    result[i].resize(nRows());
	    result[i].fill(T(0));
	}
	if (SYMMETRIC){

	    for (i=0; i<nRows(); i++) {
		for (j=0; j<nRhs; j++)
		    result[j][i]   += (*this)(i,i) * v[j][i];

		for (k=1; k<data[i].size(); k++) {
		    j = data[i][k].col;
		    const T& elemIJ = data[i][k].value;
		    for (l=0; l<nRhs; l++) {
			result[l][j]   += elemIJ * v[l][i];
			result[l][i]   += elemIJ * v[l][j];
		    }
		}
	    }
	} else {
	    for (i=0; i<nRows(); i++)
		for (j=0; j<data[i].size(); j++)
		    for (l=0; l<nRhs; l++)
			result[l][i] += data[i][j].value * v[l][data[i][j].col];
	}
    }

    /// One SSOR step.
    void SSORIteration(float relaxFact, const McDArray<T>& rhs,
		       McDArray<T>& result) const {
	if (!SYMMETRIC){
	    printf("SSORIteration works only for symmetric matrices!!\n");
	    assert(false);
	}

	assert(rhs.size()==nCols());
	result.resize(nRows());
	result.fill(T(0));

	int i,j,k;

	for (i=0; i<nRows(); i++) {
	    result[i]   = rhs[i];

	    for (k=1; k<data[i].size(); k++) {
		j = data[i][k].col;       // j < i !!!
		const T& elemIJ = data[i][k].value;
		result[i]   -= elemIJ * result[j];
	    }

	    const T& diagI = data[i][0].value;
	    result[i]   *= T(relaxFact) / diagI;
	}

	for (i=nRows()-1; i>=0; i--) {
	    const T s = T(relaxFact) * result[i];

	    for (k=1; k<data[i].size(); k++) {
		j = data[i][k].col;       // j < i !!!
		const T& elemIJ = data[i][k].value;
		const T& diagJ  = data[j][0].value;
		result[j]   -= elemIJ / diagJ * s;
	    }
	}

	float fact = 2. - relaxFact;
	for (i=0; i<nRows(); i++)
	    result[i] *= fact;

    }

    /// One SSOR step, real matrix, complex vector.
    void SSORIterationC(float relaxFact,
			const McDArray< MC_complex<T> >& rhs,
			McDArray< MC_complex<T> >& result) const {
	if (!SYMMETRIC){
	    printf("SSORIteration works only for symmetric matrices!!\n");
	    assert(false);
	}

	assert(rhs.size()==nCols());
	result.resize(nRows());
	result.fill(MC_complex<T>(0));

	int i,j,k;

	for (i=0; i<nRows(); i++) {
	    result[i]   = rhs[i];

	    for (k=1; k<data[i].size(); k++) {
		j = data[i][k].col;       // j < i !!!
		const T& elemIJ = data[i][k].value;
		result[i]   -= elemIJ * result[j];
	    }

	    const T& diagI = data[i][0].value;
	    result[i]   *= T(relaxFact) / diagI;
	}

	for (i=nRows()-1; i>=0; i--) {
	    const MC_complex<T> s = T(relaxFact) * result[i];

	    for (k=1; k<data[i].size(); k++) {
		j = data[i][k].col;       // j < i !!!
		const T& elemIJ = data[i][k].value;
		const T& diagJ  = data[j][0].value;
		result[j]   -= elemIJ / diagJ * s;
	    }
	}

	float fact = 2. - relaxFact;
	for (i=0; i<nRows(); i++)
	    result[i] *= fact;

    }

    /// One SSOR step for multiple right hand sides.
    void SSORIterationM(float relaxFact,
			const McDArray< McDArray<T> >& rhs,
			McDArray< McDArray<T> >& result) const {
	if (!SYMMETRIC){
	    printf("SSORIteration works only for symmetric matrices!!\n");
	    assert(false);
	}

	int i,j,k,l;

	int nRhs = rhs.size();
	if (nRhs == 0) return;

	result.resize(nRhs);
	for (i=0; i<nRhs; i++) {
	    assert(rhs[i].size()==nCols());
	    result[i].resize(nRows());
	    result[i].fill(T(0));
	}

	for (i=0; i<nRows(); i++) {
	    for (l=0; l<nRhs; l++)
		result[l][i] = rhs[l][i];

	    for (k=1; k<data[i].size(); k++) {
		j = data[i][k].col;       // j < i !!!
		const T& elemIJ = data[i][k].value;
		for (l=0; l<nRhs; l++)
		    result[l][i] -= elemIJ * result[l][j];
	    }

	    const T& diagI = data[i][0].value;
	    for (l=0; l<nRhs; l++)
		result[l][i] *= T(relaxFact) / diagI;
	}

	McDArray <T> s(nRhs);
	for (i=nRows()-1; i>=0; i--) {
	    for (l=0; l<nRhs; l++)
		s[l] = T(relaxFact) * result[l][i];

	    for (k=1; k<data[i].size(); k++) {
		j = data[i][k].col;       // j < i !!!
		const T& elemIJ = data[i][k].value;
		const T& diagJ  = data[j][0].value;
		for (l=0; l<nRhs; l++)
		    result[l][j]   -= elemIJ / diagJ * s[l];
	    }
	}

	float fact = 2. - relaxFact;
	for (l=0; l<nRhs; l++) {
	    for (i=0; i<nRows(); i++)
		result[l][i] *= fact;
	}

    }

    /// One SOR iteration.
    void SORIteration(float relaxFact, const McDArray<T>& rhs,
		      const McDArray<T>& xOld, McDArray<T>& xNew) const {
	if (SYMMETRIC){
	    printf("SORIteration doesn't work for symmetric matrices!!\n");
	    assert(false);
	}

	assert(isQuadratic());

	assert(rhs.size()==nCols());
	xNew.resize(nRows());

	int i,j,k;

	for (i=0; i<nRows(); i++)
	    xNew[i] = rhs[i];

	for (i=0; i<nRows(); i++) {
	    for (k=0; k<data[i].size(); k++) {
		j = data[i][k].col;
		if (j != i) {
		    const T& elemIJ = data[i][k].value;
		    xNew[i]   -= elemIJ * xOld[j];
		}
	    }

	    const T& diagI = (*this)(i,i);
	    xNew[i]   *= T(relaxFact) / diagI;
	}

	float fact = 1. - relaxFact;
	for (i=0; i<nRows(); i++)
	    xNew[i] += fact * xOld[i];
    }

    /// One SOR iteration, real matrix, complex vector.
    void SORIterationC(float relaxFact, const McDArray< MC_complex<T> >& rhs,
		       const McDArray< MC_complex<T> >& xOld,
		       McDArray< MC_complex<T> >& xNew) const {
	if (SYMMETRIC){
	    printf("SORIteration doesn't work for symmetric matrices!!\n");
	    assert(false);
	}

	assert(isQuadratic());

	assert(rhs.size()==nCols());
	xNew.resize(nRows());

	int i,j,k;

	for (i=0; i<nRows(); i++)
	    xNew[i] = rhs[i];

	for (i=0; i<nRows(); i++) {
	    for (k=0; k<data[i].size(); k++) {
		j = data[i][k].col;
		if (j != i) {
		    const T& elemIJ = data[i][k].value;
		    xNew[i]   -= elemIJ * xOld[j];
		}
	    }

	    const T& diagI = (*this)(i,i);
	    xNew[i]   *= T(relaxFact) / diagI;
	}

	float fact = 1. - relaxFact;
	for (i=0; i<nRows(); i++)
	    xNew[i] += fact * xOld[i];
    }


    /// Iterative solver: SOR.
    void SOR(const McDArray<T>& rhs, McDArray<T>& result,
	     McDArray<T>& residuum,
	     int* maxIter, const double tolerance,
	     const double relaxFact,
	     McProgressInterface* progress=0) const {

	assert(isQuadratic());

	result.resize(nRows());
	residuum.resize(nRows());

	multVec(result,residuum);

	int i;
	for (i=0; i<nRows(); i++) {
	    residuum[i] = rhs[i] - residuum[i];
	}

	double normRhs = 0.;
	for (i=0; i<nRows(); i++) {
	    normRhs += realPart(rhs[i]*conjug(rhs[i]));
	}
	normRhs = sqrt(normRhs);

	double normRes = 0.;
	for (i=0; i<nRows(); i++) {
	    normRes += realPart(residuum[i]*conjug(residuum[i]));
	}
	normRes = sqrt(normRes);

 	if (progress && normRhs) {
	    float progressValue = log(normRes/normRhs) / log(tolerance);
	    progress->setProgressValue(progressValue);
	    progress->setProgressInfo("solving LES:  res = %g",
				      normRes/normRhs);
	}

	// main loop: SOR iteration
	McDArray<T> xNew(nRows());
	int iLoop;
	for (iLoop = 0;
	     iLoop < *maxIter && normRes > tolerance * normRhs;
	     iLoop++) {
	    //SORIteration(relaxFact, rhs, result, xNew);
	    SORIteration(relaxFact, rhs, result, xNew);
	    result = xNew;

	    multVec(result,residuum);
	    for (i=0; i<nRows(); i++) {
		residuum[i] = rhs[i] - residuum[i];
	    }

	    normRes = 0.;
	    for (i=0; i<nRows(); i++) {
		normRes += realPart(residuum[i]*conjug(residuum[i]));
	    }
	    normRes = sqrt(normRes);

	    if (progress) {
		if (iLoop%5 == 0) {
		    float progressValue = log(normRes/normRhs) / log(tolerance);
		    progress->setProgressValue(progressValue);
		}
		if (iLoop%20 == 0) {
		    progress->setProgressInfo("solving LES:  it, res:  %d  %g",
					      iLoop+1, normRes/normRhs);
		}
	    }
	}

	*maxIter = iLoop + 1;

    }

    /// Iterative solver: SOR, real matrix, complex vector.
    void SORC(const McDArray< MC_complex<T> >& rhs,
	      McDArray< MC_complex<T> >& result,
	      McDArray< MC_complex<T> >& residuum,
	      int* maxIter, const double tolerance,
	      const double relaxFact,
	      McProgressInterface* progress=0) const {

	assert(isQuadratic());

	result.resize(nRows());
	residuum.resize(nRows());

	multVecC(result,residuum);

	int i;
	for (i=0; i<nRows(); i++) {
	    residuum[i] = rhs[i] - residuum[i];
	}

	double normRhs = 0.;
	for (i=0; i<nRows(); i++) {
	    normRhs += MC_real(rhs[i]*MC_conj(rhs[i]));
	}
	normRhs = sqrt(normRhs);

	double normRes = 0.;
	for (i=0; i<nRows(); i++) {
	    normRes += MC_real(residuum[i]*MC_conj(residuum[i]));
	}
	normRes = sqrt(normRes);

 	if (progress && normRhs) {
	    float progressValue = log(normRes/normRhs) / log(tolerance);
	    progress->setProgressValue(progressValue);
	    progress->setProgressInfo("solving LES:  res = %g",
				      normRes/normRhs);
	}

	// main loop: SOR iteration
	McDArray< MC_complex<T> > xNew(nRows());
	int iLoop;
	for (iLoop = 0;
	     iLoop < *maxIter && normRes > tolerance * normRhs;
	     iLoop++) {
	    //SORIteration(relaxFact, rhs, result, xNew);
	    SORIterationC(relaxFact, rhs, result, xNew);
	    result = xNew;

	    multVecC(result,residuum);
	    for (i=0; i<nRows(); i++) {
		residuum[i] = rhs[i] - residuum[i];
	    }

	    normRes = 0.;
	    for (i=0; i<nRows(); i++) {
		normRes += MC_real(residuum[i]*MC_conj(residuum[i]));
	    }
	    normRes = sqrt(normRes);

	    if (progress) {
		if (iLoop%5 == 0) {
		    float progressValue = log(normRes/normRhs) / log(tolerance);
		    progress->setProgressValue(progressValue);
		}
		if (iLoop%20 == 0) {
		    progress->setProgressInfo("solving LES:  it, res:  %d  %g",
					      iLoop+1, normRes/normRhs);
                    if (progress->wasInterrupted()) break;
		}
	    }
	}

	*maxIter = iLoop + 1;

    }

    /// Iterative solver: preconditioned conjugate gradient method.
    void pcg(const McDArray<T>& rhs, McDArray<T>& result,
	     McDArray<T>& residuum,
	     int* maxIter, const double tolerance,
	     const double relaxFact,
	     McProgressInterface* progress=0,
	     char *progressText = 0) {

 	assert(SYMMETRIC);

	int i;

	int nUnknowns = nRows();

	McDArray<T> s(nUnknowns);
	McDArray<T> d(nUnknowns);
	McDArray<T> ad(nUnknowns);

	if (progress) {
	    progress->setProgressValue(0.);
	    if (progressText)
		progress->setProgressInfo("%s solving LES: res = 1",
					  progressText);
	    else
		progress->setProgressInfo("solving LES: res = 1");
	}

	residuum.resize(nUnknowns);
	residuum = rhs;
	double normRhs = 0.;
	for (i=0; i<nUnknowns; i++) {
	    normRhs += realPart(residuum[i]*conjug(residuum[i]));
	}
	normRhs = sqrt(normRhs);

	result.resize(nUnknowns);
	result.fill(T(0));

	// precondDiag(nEdges, residuum, s);
	SSORIteration(relaxFact, residuum, s);

	d = s;

	double rDotS = 0.;
	for (i=0; i<nUnknowns; i++)
	    rDotS += realPart(residuum[i] * conjug(s[i]));

	if (normRhs > 0.) {
	    double normRes = normRhs;

	    int iLoop;

	    // main loop: conjugate gradients iteration
	    for (iLoop = 0;
		 iLoop < *maxIter && normRes/normRhs > tolerance;
		 iLoop++) {
		multVec(d, ad);

		double dAd = 0.;
		for (i=0; i<nUnknowns; i++)
		    dAd += realPart(d[i] * conjug(ad[i]));

		T alpha(rDotS / dAd);

		for (i=0; i<nUnknowns; i++) {
		    result[i]   += alpha *  d[i];
		    residuum[i] -= alpha * ad[i];
		}

		// precondDiag(nEdges, residuum, s);
		SSORIteration(relaxFact, residuum, s);

		double rDotSNew = 0.;
		for (i=0; i<nUnknowns; i++)
		    rDotSNew += realPart(residuum[i] * conjug(s[i]));

		double beta = rDotSNew / rDotS;

		rDotS = rDotSNew;

		for (i=0; i<nUnknowns; i++) {
		    d[i] *= beta;
		    d[i] += s[i];
		}

 		normRes = 0;
 		for (i=0; i<nUnknowns; i++)
 		    normRes += realPart(residuum[i]*conjug(residuum[i]));
 		normRes = sqrt(normRes);

		if (progress) {
		    float progressValue = log(normRes/normRhs) / log(tolerance);
		    progress->setProgressValue(progressValue);
		    if (progressText)
			progress->
			    setProgressInfo("%s solving LES:  it, res:  %d  %g",
					    progressText, iLoop+1, normRes/normRhs);
		    else
			progress->setProgressInfo("solving LES:  it, res:  %d  %g",
						  iLoop+1, normRes/normRhs);
		    if (progress->wasInterrupted())
			break;
		}
	    }
	    // end of main loop

	    // return actual number of iterations
	    *maxIter = iLoop + 1;

// 	    if (normRes/normRhs > tolerance) {
// 		theMsg->printf("%s %g in %d iterations",
// 			       "Warning: didn't achieve attempted accuracy",
// 			       tolerance,iLoop+1);
// 		theMsg->printf("achieved accuracy: %g",normRes/normRhs);
// 	    }
	}
    }

    /// Preconditioned CG method for multiple right hand sides.
    void pcgM(const McDArray< McDArray<T> >& rhs,
	      McDArray< McDArray<T> >& result,
	      McDArray< McDArray<T> >& residuum,
	      int* maxIter, const double tolerance,
	      const double relaxFact,
	      McProgressInterface* progress=0,
	      char *progressText = 0) {

	assert(SYMMETRIC);

	int i, j;

	int nRhs = rhs.size();
	if (nRhs == 0)
	    return;

	int nUnknowns = nRows();

	McDArray< McDArray<T> > s(nRhs);
	McDArray< McDArray<T> > d(nRhs);
	McDArray< McDArray<T> > ad(nRhs);

	residuum.resize(nRhs);
	result.resize(nRhs);

	for (i=0; i<nRhs; i++) {
	    s[i].resize(nUnknowns);
	    d[i].resize(nUnknowns);
	    ad[i].resize(nUnknowns);
	    residuum[i].resize(nUnknowns);
	    result[i].resize(nUnknowns);
	}

	if (progress) {
	    progress->setProgressValue(0.);
	    if (progressText)
		progress->setProgressInfo("%s solving LES: res = 1",
					  progressText);
	    else
		progress->setProgressInfo("solving LES: res = 1");
	}

	for (i=0; i<nRhs; i++) {
	    residuum[i] = rhs[i];
	}

	McDArray<double> normRhs(nRhs);
	normRhs.fill(0.);
	double maxNormRhs = 0.;
	for (j=0; j<nRhs; j++) {
	    for (i=0; i<nUnknowns; i++) {
		normRhs[j] += realPart(residuum[j][i]*conjug(residuum[j][i]));
	    }
	    normRhs[j] = sqrt(normRhs[j]);
	    if (normRhs[j] > maxNormRhs)
		maxNormRhs = normRhs[j];
	}

	for (i=0; i<nRhs; i++) {
	    result[i].fill(T(0));
	}

	// precondDiag(nEdges, residuum, s);
	SSORIterationM(relaxFact, residuum, s);

	// d = s;   // geht das ??
	for (i=0; i<nRhs; i++) {
	    d[i] = s[i];
	}

	McDArray<double> rDotS(nRhs);
	rDotS.fill(0.);
	for (j=0; j<nRhs; j++) {
	    for (i=0; i<nUnknowns; i++)
		rDotS[j] += realPart(residuum[j][i] * conjug(s[j][i]));
	}

	if (maxNormRhs > 0.) {
	    McDArray<double> normRes = normRhs;
	    McDArray<double> relRes(nRhs);
	    relRes.fill(0.);
	    double maxRelRes = 0.;
	    for (i=0; i<nRhs; i++) {
		if (normRhs[i] > 0.)
		    relRes[i] = normRes[i] / normRhs[i];
		if (maxRelRes < relRes[i])
		    maxRelRes = relRes[i];
	    }


	    int iLoop;

	    // main loop: conjugate gradients iteration
	    for (iLoop = 0;
		 iLoop < *maxIter && maxRelRes > tolerance;
		 iLoop++) {
		multVecM(d, ad);

		McDArray<double> dAd(nRhs);
		dAd.fill(0.);
		for (j=0; j<nRhs; j++) {
		    for (i=0; i<nUnknowns; i++)
			dAd[j] += realPart(d[j][i] * conjug(ad[j][i]));
		}
		McDArray<double> alpha(nRhs);
		for (i=0; i<nRhs; i++) {
		    alpha[i]= rDotS[i] / dAd[i];
		}

		for (j=0; j<nRhs; j++) {
		    for (i=0; i<nUnknowns; i++) {
			result[j][i]   += alpha[j] *  d[j][i];
			residuum[j][i] -= alpha[j] * ad[j][i];
		    }
		}

		// precondDiag(nEdges, residuum, s);
		SSORIterationM(relaxFact, residuum, s);

		McDArray<double> rDotSNew(nRhs);
		rDotSNew.fill(0.);
		for (j=0; j<nRhs; j++) {
		    for (i=0; i<nUnknowns; i++)
			rDotSNew[j] += realPart(residuum[j][i] * conjug(s[j][i]));
		}
		McDArray<double> beta(nRhs);
		for (i=0; i<nRhs; i++) {
		    beta[i] = rDotSNew[i] / rDotS[i];
		}
		rDotS = rDotSNew;

		for (j=0; j<nRhs; j++) {
		    for (i=0; i<nUnknowns; i++) {
			d[j][i] *= beta[j];
			d[j][i] += s[j][i];
		    }
		}

 		normRes.fill(0.);
		for (j=0; j<nRhs; j++) {
		    for (i=0; i<nUnknowns; i++)
			normRes[j] += realPart(residuum[j][i]*conjug(residuum[j][i]));
		    normRes[j] = sqrt(normRes[j]);
		}
		maxRelRes = 0.;
		relRes.fill(0.);
		for (i=0; i<nRhs; i++) {
		    if (normRhs[i] > 0.)
			relRes[i] = normRes[i] / normRhs[i];
		    if (maxRelRes < relRes[i])
			maxRelRes = relRes[i];
		}

		if (progress) {
		    float progressValue = log(maxRelRes) / log(tolerance);
		    progress->setProgressValue(progressValue);
		    if (progressText)
			progress->
			    setProgressInfo("%s solving LES:  it, res:  %d  %g",
					    progressText, iLoop+1, maxRelRes);
		    else
			progress->setProgressInfo("solving LES:  it, res:  %d  %g",
						  iLoop+1, maxRelRes);
		    if (progress->wasInterrupted())
			break;
		}
	    }
	    // end of main loop

	    // return actual number of iterations
	    *maxIter = iLoop + 1;

// 	    if (normRes/normRhs > tolerance) {
// 		theMsg->printf("%s %g in %d iterations",
// 			       "Warning: didn't achieve attempted accuracy",
// 			       tolerance,iLoop+1);
// 		theMsg->printf("achieved accuracy: %g",normRes/normRhs);
// 	    }
	}
    }


    /// Preconditioned CG method for real matrix & complex vector.
    void pcgC(const McDArray< MC_complex<T> >& rhs, McDArray< MC_complex<T> >& result,
	      McDArray< MC_complex<T> >& residuum,
	      int* maxIter, const double tolerance,
	      const double relaxFact,
	      McProgressInterface* progress=0,
	      char *progressText = 0) {

	assert(SYMMETRIC);

	int i;

	int nUnknowns = nRows();

	McDArray< MC_complex<T> > s(nUnknowns);
	McDArray< MC_complex<T> > d(nUnknowns);
	McDArray< MC_complex<T> > ad(nUnknowns);

	if (progress) {
	    progress->setProgressValue(0.);
	    if (progressText)
		progress->setProgressInfo("%s solving LES: res = 1",
					  progressText);
	    else
		progress->setProgressInfo("solving LES: res = 1");
	}

	residuum.resize(nUnknowns);
	residuum = rhs;
	double normRhs = 0.;
	for (i=0; i<nUnknowns; i++) {
	    normRhs += MC_real(residuum[i]*MC_conj(residuum[i]));
	}
	normRhs = sqrt(normRhs);

	result.resize(nUnknowns);
	result.fill(MC_complex<T>(0));

	// precondDiag(nEdges, residuum, s);
	SSORIterationC(relaxFact, residuum, s);

	d = s;

	double rDotS = 0.;
	for (i=0; i<nUnknowns; i++)
	    rDotS += MC_real(residuum[i] * MC_conj(s[i]));

	if (normRhs > 0.) {
	    double normRes = normRhs;

	    int iLoop;

	    // main loop: conjugate gradients iteration
	    for (iLoop = 0;
		 iLoop < *maxIter && normRes/normRhs > tolerance;
		 iLoop++) {
		multVecC(d, ad);

		double dAd = 0.;
		for (i=0; i<nUnknowns; i++)
		    dAd += MC_real(d[i] * MC_conj(ad[i]));

		double alpha = rDotS / dAd;
		for (i=0; i<nUnknowns; i++) {
		    MC_complex<T> alphad = d[i];
		    alphad *= alpha;
		    result[i]   += alphad;
		    alphad = ad[i];
		    alphad *= alpha;
		    residuum[i] -= alphad;
		}

		// precondDiag(nEdges, residuum, s);
		SSORIterationC(relaxFact, residuum, s);

		double rDotSNew = 0.;
		for (i=0; i<nUnknowns; i++)
		    rDotSNew += MC_real(residuum[i] * MC_conj(s[i]));

		double beta = rDotSNew / rDotS;

		rDotS = rDotSNew;

		for (i=0; i<nUnknowns; i++) {
		    d[i] *= beta;
		    d[i] += s[i];
		}

 		normRes = 0;
 		for (i=0; i<nUnknowns; i++)
 		    normRes += MC_real(residuum[i]*MC_conj(residuum[i]));
 		normRes = sqrt(normRes);

		if (progress) {
		    float progressValue = log(normRes/normRhs) / log(tolerance);
		    progress->setProgressValue(progressValue);
		    if (progressText)
			progress->
			    setProgressInfo("%s solving LES:  it, res:  %d  %g",
					    progressText, iLoop+1, normRes/normRhs);
		    else
			progress->setProgressInfo("solving LES:  it, res:  %d  %g",
						  iLoop+1, normRes/normRhs);
		    if (progress->wasInterrupted())
			break;
		}
	    }
	    // end of main loop

	    // return actual number of iterations
	    *maxIter = iLoop + 1;

// 	    if (normRes/normRhs > tolerance) {
// 		theMsg->printf("%s %g in %d iterations",
// 			       "Warning: didn't achieve attempted accuracy",
// 			       tolerance,iLoop+1);
// 		theMsg->printf("achieved accuracy: %g",normRes/normRhs);
// 	    }
	}
    }


    /// another iterative solver for nonsymmetric matrices: BI-CGSTAB
    void BiCGSTAB(const McDArray<T>& rhs, McDArray<T>& result,
		  McDArray<T>& residuum,
		  int* maxIter, const double tolerance,
		  McProgressInterface* progress=0) const {

	int j;
	int countIter=0;
	const int N = rhs.size();

	const McDArray<T>& b = rhs;
	McDArray<T> xi = result;

	McDArray<T> tmp;
	multVec(xi, tmp);

	McDArray<T> ri(N);
	for (j=0; j<N; j++)
	    ri[j] = b[j] - tmp[j];

	double normRes = sqrt(realPart(dotProduct(ri, ri)));
	double normRhs = sqrt(realPart(dotProduct(rhs, rhs)));

	if (normRes <= tolerance * normRhs) {
	    residuum = ri;
	    *maxIter = 0;
	    return;
	}

	if (progress && normRhs) {
	    float progressValue = log(normRes/normRhs) / log(tolerance);
	    progress->setProgressValue(progressValue);
	    progress->setProgressInfo("solving LES:  res = %g",
				      normRes/normRhs);
	}

	McDArray<T> r0hat = ri;

startAgain:

	double normR0hat = sqrt(realPart(dotProduct(r0hat,r0hat)));
	double normRi = normR0hat;

	double alpha = 1;
	double omegai = 1;

	McDArray<T> pi(N);
	McDArray<T> vi(N);
	pi.fill(T(0));
	vi.fill(T(0));

	double rhoiMin1    = 1;

	double rhoi = realPart(dotProduct(ri, ri));

	while (countIter++<*maxIter) {

    	    if (fabs(rhoi) < 1.e-10 * normR0hat * normRi) {
		//printf("iter %d  rhoi: %g \n",i,rhoi);
		r0hat = ri;
		goto startAgain;
	    }

	    double beta = (rhoi / rhoiMin1)*(alpha / omegai);


	    // compute omegaiMin1*viMin1

	    for (j=0; j<N; j++)
		pi[j] = ri[j] + beta*(pi[j] - omegai*vi[j]);

	    multVec(pi, vi);

	    double denom = realPart(dotProduct(r0hat, vi));

	    alpha = rhoi / denom;

	    McDArray<T> s(N);

	    for (j=0; j<N; j++)
		s[j] = ri[j] - alpha*vi[j];

	    if (sqrt(realPart(dotProduct(s,s))) <= tolerance * normRhs) {
		for (j=0; j<N; j++)
		    xi[j] = xi[j] + alpha*pi[j];

		ri = s;
		break;
	    }

	    McDArray<T> t;
	    multVec(s, t);

	    omegai = realPart(dotProduct(t,s)) / realPart(dotProduct(t,t));

	    rhoiMin1 = rhoi;
	    rhoi = -omegai*realPart(dotProduct(r0hat,t));

	    for (j=0; j<N; j++)
		xi[j] = xi[j] + alpha*pi[j] + omegai*s[j];

	    for (j=0; j<N; j++)
		ri[j] = s[j] - omegai*t[j];

	    normRes = sqrt(realPart(dotProduct(ri, ri)));
	    normRi = normRes;

	    if (progress && normRhs) {
		if (countIter%5 == 0) {
		    float progressValue = log(normRes/normRhs) / log(tolerance);
		    progress->setProgressValue(progressValue);
		}
		if (countIter%20 == 0) {
		    progress->setProgressInfo("solving LES:  it, res:  %d  %g",
					      countIter, normRes/normRhs);
		}
	    }

	    if (normRes <= normRhs * tolerance)
		break;

	    ////////////////////////
	}

	*maxIter = countIter;

	residuum = ri;

	result = xi;

    }


    /// another iterative solver for nonsymmetric matrices: BI-CGSTAB
    void BiCGSTABC(const McDArray<MC_complex<T> >& rhs, McDArray<MC_complex<T> >& result,
		  McDArray<MC_complex<T> >& residuum,
		  int* maxIter, const double tolerance,
		  McProgressInterface* progress=0) const {

	int i, j;

	int countIter=0;

	const int N = rhs.size();

	const McDArray<MC_complex<T> >& b = rhs;
	McDArray<MC_complex<T> > xi = result;

	McDArray<MC_complex<T> > tmp;
	multVecC(xi, tmp);

	McDArray<MC_complex<T> > ri(N);
	for (j=0; j<N; j++)
	    ri[j] = b[j] - tmp[j];

	double normRes = sqrt(MC_real(dotProductC(ri, ri)));
	double normRhs = sqrt(MC_real(dotProductC(rhs, rhs)));

	if (normRes <= tolerance * normRhs) {
	    residuum = ri;
	    *maxIter = 0;
	    return;
	}

	if (progress && normRhs) {
	    float progressValue = log(normRes/normRhs) / log(tolerance);
	    progress->setProgressValue(progressValue);
            if (progress->wasInterrupted()) {return;}
	    progress->setProgressInfo("solving LES:  res = %g",
				      normRes/normRhs);
	}


	McDArray<MC_complex<T> > r0hat = ri;

startAgain:

	MC_complex<double> tmp2 = dotProductCRI(r0hat, r0hat);

	double normR0hatr = sqrt(MC_real(tmp2));
	double normR0hati = sqrt(MC_imag(tmp2));
	double normRi_r   = normR0hatr;
	double normRi_i   = normR0hati;

	double alphar = 1;
	double alphai = 1;
	double omegai_r = 1;
	double omegai_i = 1;

	McDArray<MC_complex<T> > pi(N);
	McDArray<MC_complex<T> > vi(N);
	pi.fill(MC_complex<T>(0));
	vi.fill(MC_complex<T>(0));

	double rhoiMin1r    = 1;
	double rhoiMin1i    = 1;

	tmp2 = dotProductCRI(r0hat, ri);
	double rhoi_r = MC_real(tmp2);
	double rhoi_i = MC_imag(tmp2);


	i=0;
	while (i++<*maxIter) {

	    if (fabs(rhoi_r) < 1.e-10 * normR0hatr * normRi_r ||
		fabs(rhoi_i) < 1.e-10 * normR0hati * normRi_i) {
		//printf("iter %d  rhoi: %g %g \n",i,rhoi_r,rhoi_i);
		r0hat = ri;
		goto startAgain;
	    }

	    countIter++;

	    double betar = (rhoi_r / rhoiMin1r)*(alphar / omegai_r);
	    double betai = (rhoi_i / rhoiMin1i)*(alphai / omegai_i);

	    // compute omegaiMin1*viMin1

	    for (j=0; j<N; j++)
		pi[j] = MC_complex<T>( MC_real(ri[j]) + betar*(MC_real(pi[j]) - omegai_r*MC_real(vi[j])) ,
				       MC_imag(ri[j]) + betai*(MC_imag(pi[j]) - omegai_i*MC_imag(vi[j])) );
	    multVecC(pi, vi);

	    tmp2 = dotProductCRI(r0hat, vi);
	    alphar = rhoi_r / MC_real(tmp2);
	    alphai = rhoi_i / MC_imag(tmp2);

	    McDArray<MC_complex<T> > s(N);

	    for (j=0; j<N; j++)
		s[j] = MC_complex<T>( MC_real(ri[j]) - alphar*MC_real(vi[j]),
				      MC_imag(ri[j]) - alphai*MC_imag(vi[j]) );

	    if (sqrt(MC_real(dotProductC(s,s))) <= tolerance * normRhs) {
		for (j=0; j<N; j++)
		    xi[j] = MC_complex<T>( MC_real(xi[j]) + alphar*MC_real(pi[j]),
			    		   MC_imag(xi[j]) + alphai*MC_imag(pi[j]) );
		ri = s;
		break;
	    }

	    McDArray<MC_complex<T> > t;
	    multVecC(s, t);

	    tmp2 = dotProductCRI(t,t);
	    double denomr = MC_real(tmp2);
            double denomi = MC_imag(tmp2);

	    tmp2 = dotProductCRI(t,s);
	    omegai_r = MC_real(tmp2) / denomr;
	    omegai_i = MC_imag(tmp2) / denomi;

	    rhoiMin1r   = rhoi_r;
	    rhoiMin1i   = rhoi_i;
	    tmp2 = dotProductCRI(r0hat, t);
	    rhoi_r = -omegai_r * MC_real(tmp2);
	    rhoi_i = -omegai_i * MC_imag(tmp2);

	    for (j=0; j<N; j++)
		xi[j] = MC_complex<T>( MC_real(xi[j]) + alphar*MC_real(pi[j]) + omegai_r*MC_real(s[j]),
				       MC_imag(xi[j]) + alphai*MC_imag(pi[j]) + omegai_i*MC_imag(s[j]) );

	    for (j=0; j<N; j++)
		ri[j] = MC_complex<T>( MC_real(s[j]) - omegai_r*MC_real(t[j]),
				       MC_imag(s[j]) - omegai_i*MC_imag(t[j]) );

	    tmp2 = dotProductCRI(ri,ri);
	    normRi_r = sqrt(MC_real(tmp2));
	    normRi_i = sqrt(MC_imag(tmp2));
	    normRes = sqrt(MC_real(tmp2) + MC_imag(tmp2));

	    if (progress && normRhs) {
		if (countIter%5 == 0) {
		    float progressValue = log(normRes/normRhs) / log(tolerance);
		    progress->setProgressValue(progressValue);
                    if (progress->wasInterrupted()) {return;}
		}
		if (countIter%20 == 0) {
		    progress->setProgressInfo("solving LES:  it, res:  %d  %g",
					      countIter, normRes/normRhs);
		}
	    }

	    if (normRes <= tolerance * normRhs)
		break;

	    ////////////////////////
	}

	*maxIter = countIter;

	residuum = ri;

	result = xi;

    }


    ///
    static T dotProduct(const McDArray<T>& a, const McDArray<T>& b){
	assert(a.size()==b.size());

	T sum = T(0);
	int i;

	for (i=0; i<a.size(); i++)
	    sum += a[i]*conjug(b[i]);

	return sum;
    }

    static MC_complex<T> dotProductC(const McDArray< MC_complex<T> >& a,
			 const McDArray< MC_complex<T> >& b){
	assert(a.size()==b.size());

	MC_complex<T> sum = MC_complex<T>(0);
	int i;

	for (i=0; i<a.size(); i++)
	    sum += a[i]*MC_conj(b[i]);

	return sum;
    }

    static MC_complex<double> dotProductCRI(const McDArray< MC_complex<T> >& a,
			 const McDArray< MC_complex<T> >& b){
	assert(a.size()==b.size());

	MC_complex<double> sum = MC_complex<double>(0);
	int i;

	for (i=0; i<a.size(); i++)
	    sum += MC_complex<double>( (double)MC_real(a[i])*MC_real(b[i]) , (double)MC_imag(a[i])*MC_imag(b[i]) );

	return sum;
    }

    /// complex conjugate, if T is complex, nothing if T is not
    static T conjug(const T& z){
	return z;
    }

    static double realPart(const T& z){
	return z;
    }

};

/// @if EXCLUDETHIS

template<>
inline MC_complex<float> McSparseMatrix<MC_complex<float> , false>::conjug(const MC_complex<float>& z)
{
    return MC_conj(z);
}

template<>
inline MC_complex<double> McSparseMatrix<MC_complex<double> , false>::conjug(const MC_complex<double>& z)
{
    return MC_conj(z);
}
template<>
inline MC_complex<float> McSparseMatrix<MC_complex<float> , true>::conjug(const MC_complex<float>& z)
{
    return MC_conj(z);
}

template<>
inline MC_complex<double> McSparseMatrix<MC_complex<double> , true>::conjug(const MC_complex<double>& z)
{
    return MC_conj(z);
}

template<>
inline double McSparseMatrix<MC_complex<float> , false>::realPart(const MC_complex<float>& z)
{
    return MC_real(z);
}

template<>
inline double McSparseMatrix<MC_complex<double> , false>::realPart(const MC_complex<double>& z)
{
    return MC_real(z);
}
template<>
inline double McSparseMatrix<MC_complex<float> , true>::realPart(const MC_complex<float>& z)
{
    return MC_real(z);
}

template<>
inline double McSparseMatrix<MC_complex<double> , true>::realPart(const MC_complex<double>& z)
{
    return MC_real(z);
}

/// @endif

#endif

/// @}

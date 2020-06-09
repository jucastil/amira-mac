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
#ifndef MC_BANDMATRIX_IMPL
#define MC_BANDMATRIX_IMPL

#include "McMath.h"

template<class T>
McBandMatrix<T>::McBandMatrix(int d, int  m1, int m2)
{
	mD1 = d;
	mD2 = 1 + m1 + m2;
	mM1 = m1;
	mM2 = m2;

	int i;	
	mData = new T*[d+ OFFSET];
	for (i= OFFSET ; i<d + OFFSET; i++) {
		mData[i] = new T[mD2+ OFFSET];
		memset(mData[i] + OFFSET, 0, mD2 * sizeof(T));
	}

	mDataUpper = new T*[d+ OFFSET];
	for (i= OFFSET ; i<d + OFFSET; i++) {
		mDataUpper[i] = new T[mD2+ OFFSET];
		memset(mDataUpper[i] + OFFSET, 0, mD2 * sizeof(T));
	}

}

template<class T>
McBandMatrix<T>::~McBandMatrix()
{
	for (int i= OFFSET ; i< mD1 + OFFSET; i++) {
		delete [] mData[i];
		delete [] mDataUpper[i];
	}
	delete [] mData;
	delete [] mDataUpper;
	delete [] mIndx;
}


/** sets one full row of matrix
\param i row number
\param row elements, must have size of band width
*/
template <class T>
void McBandMatrix<T>::setRow(int i,const McDArray<T> &row)
{
	assert(row.size() == mD2);

	memcpy(mData[i + OFFSET] + OFFSET, row.dataPtr(), sizeof(T) * mD2);
}

/** vector multiplication */
template <class T>
void McBandMatrix<T>::mult(const McDVector<T> &b, McDVector<T> &x)
{
	// void banmul(mData, mD1, mM1, mM2, x.dataPtr()- OFFSET, b.dataPtr() - OFFSET)
	banmul(mData, mD1, mM1, mM2, x.dataPtr()- OFFSET, b.dataPtr() - OFFSET);
}




template<class T>
void banmul(T **a, int n, int m1, int m2, T x[], T b[])
/*
Matrix multiply b = A · x, w here A is band diagonal with m1 rows below the diagonal and m2
rows above. The input vector x and output vector b are stored as x[1..n] and b[1..n],
respectively. The array a[1..n][1..m1+m2+1] stores A as follows: The diagonal elements
are in a[1..n][m1+1]. Subdiagonal elements are in a[j..n][1..m1] (with j > 1 appropriate
to the number of elements on each subdiagonal). Superdiagonal elements are in
a[1..j][m1+2..m1+m2+1] with j < n appropriate to the number of elements on each superdiagonal.
*/
{
	int i,j,k,tmploop;
	for (i=1;i<=n;i++) {
		k=i-m1-1;
		tmploop=MC_MIN2(m1+m2+1,n-k);
		b[i]=0.0;
		for (j=MC_MAX2(1,1-k);j<=tmploop;j++) b[i] += a[i][j]*x[j+k];
	}
}


#define SWAP(a,b) {dum=(a);(a)=(b);(b)=dum;}
#define TINY 1.0e-20


/*
Given an n × n band diagonal matrix A with m1 subdiagonal rows and m2 superdiagonal rows,
compactly stored in the array a[1..n][1..m1+m2+1] as described in the comment for routine
banmul, this routine constructs an LU decomposition of a rowwise permutation of A. The upper
triangular matrix replaces a, while the lower triangular matrix is returned in al[1..n][1..m1].
indx[1..n] is an output vector which records the row permutation e?ected by the partial
pivoting; d is output as ±1 depending on whether the number of row interchanges was even
or odd, respectively. This routine is used in combination with banbks to solve band-diagonal
sets of equations. */
template<class T>
void bandec(T **a, int n, int m1, int m2, T **al,
			int indx[], T *d)
{
	int i,j,k,l;
	int mm;
	T dum;
	mm=m1+m2+1;
	l=m1;
	for (i=1;i<=m1;i++) {// Rearrange the storage a bit.
		for (j=m1+2-i;j<=mm;j++) a[i][j-l]=a[i][j];
		l--;
		for (j=mm-l;j<=mm;j++) a[i][j]=0.0;
	}
	*d=1.0;
	l=m1;
	for (k=1;k<=n;k++) { //For each row...
		dum=a[k][1];
		i=k;
		if (l < n) l++;
		for (j=k+1;j<=l;j++) { //Find the pivot element.
			if (fabs(a[j][1]) > fabs(dum)) {
				dum=a[j][1];
				i=j;
			}
		}indx[k]=i;
		if (dum == 0.0) a[k][1]=TINY;
		/*
		Matrix is algorithmically singular, but proceed anyway with TINY pivot (desirable in
		some applications).*/
		if (i != k) { //Interchange rows.
			*d = -(*d);
			for (j=1;j<=mm;j++) SWAP(a[k][j],a[i][j])
		}
		for (i=k+1;i<=l;i++) { // Do the elimination.
			dum=a[i][1]/a[k][1];
			al[k][i-k]=dum;
			for (j=2;j<=mm;j++) a[i][j-1]=a[i][j]-dum*a[k][j];
			a[i][mm]=0.0;
		}
	}
}

/** solve linear system */
template <class T>
void McBandMatrix<T>::decompose()
{
	mIndx = new int[mD1 + OFFSET];

	float d;

	bandec(mData, mD1, mM1, mM2, mDataUpper, mIndx, &d);
	
}

#define SWAP(a,b) {dum=(a);(a)=(b);(b)=dum;}
template<class T>
void banbks(T **a, int n, int m1, int m2, T **al,
int indx[], T b[])
/*
Given the arrays a, al, and indx as returned from bandec, and given a right-hand side vector
b[1..n], solves the band diagonal linear equations A · x = b. The solution vector x overwrites
b[1..n]. The other input arrays are not modi?ed, and can be left in place for successive calls
with di?erent right-hand sides.
*/
{
	int i,k,l;
	int mm;
	T dum;
	mm=m1+m2+1;
	l=m1;
	for (k=1;k<=n;k++) { //Forward substitution, unscrambling the permuted rows
		 i=indx[k];   //as we go.
		if (i != k) SWAP(b[k],b[i])
			if (l < n) l++;
		for (i=k+1;i<=l;i++) b[i] -= al[k][i-k]*b[k];
	}
	l=1;
	for (i=n;i>=1;i--) { //Backsubstitution.
		dum=b[i];
		for (k=2;k<=l;k++) dum -= a[i][k]*b[k+i-1];
		b[i]=dum/a[i][1];
		if (l < mm) l++;
	}
}

template <class T>
void McBandMatrix<T>::solve(const McDVector<T> &b, McDVector<T> &x)
{	
	//  as required by banbks
	x = b;

	banbks(mData, mD1, mM1, mM2, mDataUpper, mIndx, x.dataPtr() - OFFSET);
}

#endif


/// @}

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
#ifndef MC_BANDMATRIX_H
#define MC_BANDMATRIX_H

#include "McDVector.h"
#include "McWinDLLApi.h"

/// in numerical recipes all indices start with one.
const int OFFSET = 1;

/** band matrices. Provides routines for matrix/vector multiplication
and solution of linear systems. */
template<class T>
class  McBandMatrix {

	public:

		/**
			\param d size of matrix
			\param m1 no bands left
			\param m2 no bands right
		*/
		McBandMatrix(int d, int m1, int m2);

		~McBandMatrix();

		/** sets one full row of matrix
			\param i row number
			\param row elements, must have size of band width
		*/
		void setRow(int i,const McDArray<T> &row);



		/** decompose matrix. Call before calling solve */
		void decompose();

		/** solve linear system */
		void solve(const McDVector<T> &b, McDVector<T> &x);

		/** vector multiplication */
		void mult(const McDVector<T> &b, McDVector<T> &x);

private:

	/// data in matrix
	T** mData;

	/// data for superdiagonal matrix after decomposition
	T** mDataUpper;

	/// permutation inforamtion
	int* mIndx;


	int mD1; //!> height
	int mD2; //!> width
	int mM1; //!> rows to the left/lower
	int mM2; //!> rows to the right/up

};

#include "McBandMatrix_impl.h"

#endif


/// @}

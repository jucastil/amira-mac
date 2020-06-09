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
#include "McDMatrix.h"

/** Multiplies from the left a (row) vector with a matrix. The result is a (row) vector. */
template<typename T>
McDVector<T> vectorMatrixProduct(const McDVector<T>& left, const McDMatrix<T>& right) {
    if(left.size() != right.nRows()) {
        std::cout << "ERROR: size mismatch" << std::endl;
        return left;
    }

    McDVector<T> res(right.nCols());
    res.fill(T(0));

    const T* dptr = right.dataPtr();
    const T* curPtr = left.dataPtr();

    for(unsigned int i = 0; i < (unsigned int)right.nRows(); i++) {
        T* resPtr = res.dataPtr();

        for(unsigned int j = 0; j < (unsigned int)right.nCols(); j++)
            *(resPtr++) += (*(curPtr)) * (*(dptr++));

        curPtr++;
    }

    return res;
}

/** Multiplies a (column) vector with a (row) vector. The result is a matrix. */
template<typename T>
McDMatrix<T> vectorVectorProduct(const McDVector<T>& left, const McDVector<T>& right) {
    McDMatrix<T> res(left.size(), right.size());
    T* resPtr = res.dataPtr();
    const T* leftPtr = left.dataPtr();

    for(unsigned int i = 0, sizeL = left.size(); i < sizeL; i++) {
        const T* rightPtr = right.dataPtr();

        for(unsigned int j = 0, sizeR = right.size(); j < sizeR; j++) {
            *(resPtr++) = (*leftPtr) * (*(rightPtr++));
        }
        leftPtr++;
    }

    return res;
}

/// @}

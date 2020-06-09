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

/// @addtogroup hxregistration hxregistration
/// @{
#ifndef MC_TENSOR_PROD_MATRIX_H
#define MC_TENSOR_PROD_MATRIX_H

#include <mclib/McDVector.h>
#include <mclib/McStdlib.h>

/** This class provides a dynamic two dimensional matrix of type T
    with tensor product structure, i.e.

    A = Id + a1 * |v1><v1| + a2 * |v2><v2| + a3 * |v3><v3| + ...

    A matrix of this type occurs e.g. as approximation of the Hessian
    matrix in a quasiNewton method.

    For very large matrix dimensions and a comparable small number of
    vectors vi it is more efficient in terms of memory and CPU time to 
    store the vectors vi and the factors ai.

    possible extensions: 
    - complex conjugation, if T is complex
    - factor a0 for unit matrix

*/

template<class T> class McTensorProductMatrix
{
public:
    /** Default constructor.*/
    McTensorProductMatrix<T>() : size(0)
    {
        entries.resize(0);
        factors.resize(0);
    }

    /** This constructor creates a matrix of size n. */
    McTensorProductMatrix<T>(int n) : size(n)
    {
        entries.resize(0);
        factors.resize(0);
    }

    /// Destructor.
    ~McTensorProductMatrix() 
    { 
    }

    /** Resize method. Resets matrix to a unit matrix! */
    void resize(int n)
    {
        if (n < 0) 
            n = 0;
        size = n;
        reset();
    }

    /** Resets matrix to a unit matrix */
    void reset()
    {
        entries.resize(0);
        factors.resize(0);
        mScale = 1;
    }

    /** Add vector vi and corresponding factor ai. Returns 1 on
        success, 0 if vector and matrix have different dimensions */
    int addEntry(McDVector<T> &vi, T& ai)
    {
        if (vi.size() != size)
            return 0;

        entries.append(vi);
        factors.append(ai);
        return 1;
    }

    /** Return actual number of vectors vi */
    int numEntries()
    {
        return entries.size();
    }

    /** Matrix-vector multiplication. Returns 1 on success, 
        0 if input vector and matrix have different dimensions */
    int multVec(McDVector<T> &input, McDVector<T> &output)
    {
        if (input.size() != size)
            return 0;
        
        if (entries.size() != factors.size())
            return 0;  // should not occur
        
        output = input; // initial multiplication with unit matrix
        output *= mScale; // use scaling factor


        // Caution: McDVector::dot already includes a complex conjugation!
        int i;
        McDVector<T> tmp;
        for (i=0; i<entries.size(); i++) {
            tmp     = entries[i];
            tmp    *= factors[i] * input.dot(entries[i]);
            output += tmp;
        }
        return 1;
    }
    

    /** Scale H0 in the QuasiNewton approximation.
        Scaling improves convergence.
    */
     McTensorProductMatrix<T>& scaleIdentity(T s)
     { 
     //   for (int i =0; i<size; i++) factors[i] *= s;
        mScale = s;
        return *this;
     }

protected:
    /// Matrix dimension.
    int size;

    /// Vectors vi
    McDArray < McDVector<T> > entries;
    
    /// Factors ai
    McDArray<T> factors;

    /// scale factor
    T mScale;
};

#endif

/// @}

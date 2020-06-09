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
#ifndef _MC_DVECTOR_H
#define _MC_DVECTOR_H

#include "McDArray.h"

#if defined (HX_HAS_STDCOMPLEX)
#  include <complex>
#else
#  include <complex.h>
#endif
#include "McStdlib.h"

template<class T>
class McDVector : public McDArray<T> {

  public:

    /// Constructors.
    McDVector() : McDArray<T>() {};

    explicit McDVector(const McDArray<T>& old) : McDArray<T>(old) {};

    McDVector(const McDVector& old) : McDArray<T>(old) {};

    McDVector(int size, int max=0) : McDArray<T>(size,max) {};



    /********************** Basic operations ****************************/

    /// Addition. Assigns v1+v2 to this McDVector.
    void addInto(const McDVector<T>& v1, const McDVector<T>& v2) {
        assert(v1.size()==v2.size());
        resize(v1.size());
        for (int i=0; i<this->thesize; i++)
            (*this)[i] = v1[i]+v2[i];
    }

    /// Addition.
    McDVector& operator+=(const McDVector<T>& v) {
        assert(v.size() == this->thesize);
        for (int i=0; i<this->thesize; i++)
            (*this)[i] += v[i];
        return *this;
    }


    /// add scaled vector
    void add(T lambda, const McDVector<T>& v) {
        assert(v.size() == this->thesize);
        for (int i=0; i<this->thesize; i++)
            (*this)[i] += lambda * v[i];
    }

    /// Subtraction. Assigns v1-v2 to this McDVector.
    void subtractInto(const McDVector<T>& v1, const McDVector<T>& v2) {
        assert(v1.size()==v2.size());
        this->resize(v1.size());
        for (int i=0; i<this->thesize; i++)
            (*this)[i] = v1[i]-v2[i];
    }

    /// Subtraction.
    McDVector& operator-=(const McDVector<T>& v) {
        assert(v.size() == this->thesize);
        for (int i=0; i<this->thesize; i++)
            (*this)[i] -= v[i];
        return *this;
    }




    /// Multiplication by scalar of type T.
    McDVector& operator*=(T d) {
        for (int i=0; i<this->thesize; i++)
            (*this)[i] *= d;
        return *this;
    }

    /// Division by scalar of type T
    McDVector& operator/=(T d) {
        for (int i=0; i<this->thesize; i++)
            (*this)[i] /= d;
        return *this;
    }

    /********************* Special operations **********************/
protected:
    /// Return complex conjugate. (Also see specialization for complex below.)
    static T conjug(const T& z) { return z; }

    /// Return MC_real part. (Also see specialization for complex below.)
    static double realPart(const T& z) {return z; }

    /// Return MC_imaginary part. (Also see specialization for complex below.)
    static double imagPart(const T& z) { return 0; }
public:
    /// max norm. (Also see specialization for complex below.)
    double maxNorm() const
    {
        double d;
        double result = 0;
        for( int i=0; i< this->thesize; i++ ) {
            d = fabs((*this)[i]);
            if (d>result)
                result = d;
        }
        return result;
    }

    /// Squared length
    double length2() const {
        double sum = 0;
        for (int i=0; i<this->thesize; i++) {
            const T& z = (*this)[i];
            sum += realPart(z*conjug(z));
        }
        return sum;
    }

    /// Length
    double length() const {
        return MC_sqrtf((*this).length2());
    }

    /// Sum of all elements
    double getSum() const {
        double sum = 0.0;

        for(unsigned int i = 0, size = this->thesize; i < size; i++)
            sum += (*this)[i];

        return sum;
    }

    /// Normalize vector to 1 and return length
    double normalize() {
        double len = length();
        if (len) {
            for (int i=0; i<this->thesize; i++)
                (*this)[i] /= len;
        }
        return len;
    }

    /// Scalar product
    T dot(const McDVector<T>& v) const {
        assert(this->thesize==v.size());
        T prod = T(0);
        for (int i=0; i<this->thesize; i++)
            prod += (*this)[i]*conjug(v[i]);
        return prod;
    }

//     /// equal with tolerance in length
//     bool equals (const McDVector<T>& v, float tolerance = 1e-6) const {
//         if ((*this - v).length2 () < (tolerance * tolerance)) {
//             return true;
//         }
//         return false;
//     }

    /// Print to file
    void print(const char *start = NULL, FILE *fp = stdout) {
        if (start) fprintf(fp,"%s",start);
        for (int i=0 ; i<this->thesize ; i++) {
            const T& z = (*this)[i];
            if (imagPart(z)==0)
                fprintf(fp,"%1g\t",realPart(z));
            else if (imagPart(z)<0)
                fprintf(fp,"%1g-%1gi\t",realPart(z),fabs(imagPart(z)));
            else
                fprintf(fp,"%1g+%1gi\t",realPart(z),fabs(imagPart(z)));
        }
        fprintf(fp,"\n");
    }
};


/// @if EXCLUDETHIS
// Specializations:

template<>
inline MC_complex<float> McDVector<MC_complex<float> >::conjug(const MC_complex<float>& z)
{
    return MC_conj(z);
}

template<>
inline MC_complex<double> McDVector<MC_complex<double> >::conjug(const MC_complex<double>& z)
{
    return MC_conj(z);
}

template<>
inline double McDVector<MC_complex<float> >::realPart(const MC_complex<float>& z)
{
    return MC_real(z);
}

template<>
inline double McDVector<MC_complex<double> >::realPart(const MC_complex<double>& z)
{
    return MC_real(z);
}

template<>
inline double McDVector<MC_complex<float> >::imagPart(const MC_complex<float>& z)
{
    return MC_imag(z);
}

template<>
inline double McDVector<MC_complex<double> >::imagPart(const MC_complex<double>& z)
{
    return MC_imag(z);
}

template<>
inline double McDVector< MC_complex<float> >::maxNorm() const
{
    double d;
    double result = 0;
    for( int i=0; i< this->thesize; i++ ) {
        d = MC_abs( (*this)[i] );
        if (d>result)
            result = d;
    }
    return result;
}

template<>
inline double McDVector< MC_complex<double> >::maxNorm() const
{
    double d;
    double result = 0;
    for( int i=0; i< this->thesize; i++ ) {
        d = MC_abs( (*this)[i] );
        if (d>result)
            result = d;
    }
    return result;
}

/// @endif

#endif

/// @}

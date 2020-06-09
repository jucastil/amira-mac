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
#ifndef MC_MAT3_EIGENANALYSIS_H
#define MC_MAT3_EIGENANALYSIS_H

#include <mclib/McVec2i.h>
#include <mclib/McMat3f.h>
#include <mclib/McMat3d.h>
#include <mclib/McVec3f.h>
#include <mclib/McVec3d.h>
#include <mclib/McMath.h>

#include <complex>
#include <cmath>

/**
    Computes Eigenvalues and Eigenvectors for 3x3 matrices.
*/
namespace McMat3_EigenAnalysis
{

/**
    Returns arg*arg.
*/
template<class T>
T sqr(const T& arg)
{
    return arg*arg;
}

/**
    Returns arg*arg*arg.
*/
template<class T>
T cube(const T& arg)
{
    return arg*arg*arg;
}

/**
    Solves the cubic equation x^3+ax^2+bx+c = 0 directly using
    Cardano's method, see
    http://en.wikipedia.org/wiki/Cubic_function#Cardano.27s_method.

    The equation has either 1 real and 2 complex solutions, or 3 real
    solutions. The storage of the result depends on the return value.
    The function returns the number of real solutions.

    If the return value is 1, x0 is the real solution, x1+ix2 and
    x1-ix2 are the two complex solutions. If 3 is returned, x0, x1, x2
    are the 3 real solutions.
*/
template<class T>
int solveCubic(T a, T b, T c, T& x0, T& x1, T& x2)
{
    T p = b - sqr(a)/3.0;
    T q = 2.0*cube(a)/27.0 - a*b/3 + c;

    T D = sqr(q/2.0)+cube(p/3.0);

    if (D>0)
    {
        T sqrtD = sqrt(D);

        T u = McCbrt(-q/2.0+sqrtD);
        T v = McCbrt(-q/2.0-sqrtD);

        T z1 = u+v;

        std::complex<T> e1(-0.5,+0.5*sqrt(3.0));
        std::complex<T> e2(-0.5,-0.5*sqrt(3.0));

        std::complex<T> z2 = u*e1 + v*e2;

        x0 = z1-a/3.0;
        std::complex<T> xc = z2-static_cast<T>(a/3.0);
        x1 = xc.real();
        x2 = xc.imag();

        return 1;
    } else if (D==0)
    {
        T z1  = 0.0;
        T z23 = 0.0;

        if (p != 0.0)
        {
            z1  = 3.0*q/p;
            z23 = -3.0*q/(2.0*p);
        }

        x0 = z1-a/3.0;
        x1 = x2 = z23-a/3.0;

        return 3;
    } else // D < 0
    {
        T argument = -q/2.0*cube(sqrt(-3/p));

        // an argument of exactly 1 gives an acos of nan. 
        // The might happen due to inaccuracies of floating point computation. So check it.
        T cosArg = argument >= 1.0 ? 0.0 : acos(argument)/3.0;
        T fac = sqrt(-4.0/3.0*p);

        T z1 =  fac*cos(cosArg);
        T z2 = -fac*cos(cosArg+M_PI/3.0);
        T z3 = -fac*cos(cosArg-M_PI/3.0);

        x0 = z1-a/3.0;
        x1 = z2-a/3.0;
        x2 = z3-a/3.0;

        return 3;
    }
}

/**
    Helper class to deduce Matrix and Vector types for a given
    primitive real type.
*/
template<class T>
struct Mat3
{
};

template<>
struct Mat3<float>
{
    typedef McMat3f MatType;
    typedef McVec3f VecType;
};

template<>
struct Mat3<double>
{
    typedef McMat3d MatType;
    typedef McVec3d VecType;
};

/**
    Computes characteristic polynom for eigenvalue computation
    of a 3x3 matrix. The characteristic polynom is of type
    x^3+ax^2+bx+c = 0.
*/
template<class T>
void charPolynom3(typename Mat3<T>::MatType m, T& a, T& b, T& c)
{
    // det (x*Id-m)
    a = -m[2][2]-m[1][1]-m[0][0];
    b =  m[1][1]*m[2][2]  +m[0][0]*m[2][2]  +m[0][0]*m[1][1]
        -m[1][2]*m[2][1]  -m[0][1]*m[1][0]  -m[0][2]*m[2][0];
    c = -m[0][0]*m[1][1]*m[2][2]  +m[0][0]*m[1][2]*m[2][1]
        +m[0][1]*m[1][0]*m[2][2]  -m[0][1]*m[1][2]*m[2][0]
        -m[0][2]*m[1][0]*m[2][1]  +m[0][2]*m[1][1]*m[2][0];
}

/**
    Computes |arg|^2
*/
template<class T>
T val2(T arg)
{
    return arg*arg;
}

/**
    Computes |arg|^2
*/
template<class T>
T val2(std::complex<T> arg)
{
    return arg.real()*arg.real()+arg.imag()*arg.imag();
}

/**
    Computes |length(d)|^2, where d is a 3 component vector.
*/
template<class T>
double length2(T* d)
{
    return val2(d[0]) + val2(d[1]) + val2(d[2]);
}


/**
    Helper class for deducing the primitive real type of either
    a complex or a plain real type.
*/
template<class T>
struct ValueTypeClass
{
    typedef T ValueType;
};

template<class T>
struct ValueTypeClass<std::complex<T> >
{
    typedef T ValueType;
};

template<class T>
McVec2i maxElement(T m[3][3],int upperLeft) {
    McVec2i maxIdx(upperLeft,upperLeft);
    double maxVal2 = val2(m[maxIdx[0]][maxIdx[1]]);

    for (int i=upperLeft;i<3;i++) {
        for (int j=upperLeft;j<3;j++) {
            double currentVal2 = val2(m[i][j]);
            if (currentVal2 > maxVal2) {
                maxIdx = McVec2i(i,j);
                maxVal2 = currentVal2;
            }
        }
    }
    return maxIdx;
}

template<class T>
void swapRows(T m[3][3], int i, int j) {
    for (int x=0;x<3;x++) {
        std::swap(m[i][x],m[j][x]);
    }
}

template<class T>
void swapColumns(T m[3][3], int i, int j) {
    for (int x=0;x<3;x++) {
        std::swap(m[x][i],m[x][j]);
    }
}

/**
    Computes a real/complex eigenvector of a matrix for eigenvalue 
    @c lambda.  It does some type of row and column pivoting.
*/
template<class T>
void computeEV(const typename Mat3<typename ValueTypeClass<T>::ValueType>::MatType& mf, T lambda, T* ev)
{
    T m[3][3] = { {mf[0][0],mf[0][1],mf[0][2]}
                 ,{mf[1][0],mf[1][1],mf[1][2]}
                 ,{mf[2][0],mf[2][1],mf[2][2]}};
    m[0][0] -= lambda;
    m[1][1] -= lambda;
    m[2][2] -= lambda;

    int idx[3] = {0,1,2};

    McVec2i maxIdx = maxElement(m,0);
    swapRows(m,0,maxIdx[0]);
    swapColumns(m,0,maxIdx[1]);
    std::swap(idx[0],idx[maxIdx[1]]);

    for (int i=1;i<3;i++)
    {
        m[i][1] -= m[0][1]*m[i][0]/m[0][0];
        m[i][2] -= m[0][2]*m[i][0]/m[0][0];
    }
    m[1][0] = 0.0;
    m[2][0] = 0.0;

    maxIdx = maxElement(m,1);
    swapRows(m,1,maxIdx[0]);
    swapColumns(m,1,maxIdx[1]);
    std::swap(idx[1],idx[maxIdx[1]]);

    // now choose the second element:
    ev[idx[2]] = 1.0f;
    ev[idx[1]] = -m[1][2]/m[1][1];
    ev[idx[0]] = -(m[0][1]*ev[idx[1]]+m[0][2])/m[0][0];
}

/**
    Computes Eigenvalues and Eigenvectors of a 3x3 Matrix. Such a
    matrix has either 3 real or 1 real and two complex Eigenvalues and
    Eigenvectors.

    Returns number of real solutions. Result encoding depends on the
    return value.  If 3, all Eigenvectors and Eigenvalues are real. If
    1, lambda0 and ev0 is the real Eigenvalue/-vector, and (lambda1 +
    i lambda2) and (ev1 + i ev2) and its complex conjugate are the
    complex Eigenvalues/-vectors.

    The Eigenvectors are only correct if the dimensionality of the
    Eigenspace is 1.
*/
template<class T>
int compEigen3x3(const typename Mat3<T>::MatType& m, T& lambda0, T& lambda1, T& lambda2, typename Mat3<T>::VecType& ev0, typename Mat3<T>::VecType& ev1, typename Mat3<T>::VecType& ev2)
{
    T a;
    T b;
    T c;

    charPolynom3(m,a,b,c);
    int nReals = solveCubic(a,b,c,lambda0,lambda1,lambda2);
    computeEV(m,lambda0,&ev0[0]);

    if (nReals == 3)
    {
        computeEV(m,lambda1,&ev1[0]);
        computeEV(m,lambda2,&ev2[0]);
    } else // nReals = 1
    {
        std::complex<T> ev[3];
        computeEV(m,std::complex<T>(lambda1,lambda2),ev);
        ev1[0] = ev[0].real();
        ev1[1] = ev[1].real();
        ev1[2] = ev[2].real();
        ev2[0] = ev[0].imag();
        ev2[1] = ev[1].imag();
        ev2[2] = ev[2].imag();
    }

    return nReals;
}

}

#endif


/// @}

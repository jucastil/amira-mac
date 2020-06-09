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
#ifndef MC_MAT2d
#define MC_MAT2d

#include "McWinDLLApi.h"
#include "McVec2d.h"

class MCLIB_API McMat2d
{

public:
    /**
        Initializes all entries with 0.
    */
    McMat2d()
    {
        for (int i=0; i<4; i++)
            mat[i] = 0;
    }

    McMat2d(double m00, double m01, double m10, double m11)
    {
        mat[0] = m00;
        mat[1] = m01;
        mat[2] = m10;
        mat[3] = m11;
    }

    McMat2d(double m[4])
    {
        for (int i=0; i<4; i++)
            mat[i] = m[i];
    }

    /**
        Initialize matrix with two column vectors.
    */
    McMat2d(McVec2d col1, McVec2d col2)
    {
        mat[0] = col1[0];
        mat[1] = col2[0];
        mat[2] = col1[1];
        mat[3] = col2[1];
    }

    /// return new matrix which is inverse to this
    McMat2d inverse() const
    {
        double newCoeffs[] = {mat[3], -mat[1], -mat[2], mat[0]};
        McMat2d ret(newCoeffs);
        ret *= 1.0 / det();
        return ret;
    }

    double det() const
    {
        return (mat[0]*mat[3] - mat[1]*mat[2]);
    }

    /// matrix trace
    double trace() const
    {
        return mat[0]+mat[3];
    }

    /**
        Computes the eigenvalues of the matrix. The imaginary parts of
        the eigenvalues are stored in the second vector components.
    */
    void calcComplexEigenValues(McVec2d& lambda1, McVec2d& lambda2) const;

    /**
        Computes the real eigenvectors. The eigenvalues must be real!
    */
    void calcEigenVectors(McVec2d lambda1, McVec2d lambda2, McVec2d& ev1 , McVec2d& ev2) const;

    const double* operator[](int row) const
    {
        return &mat[row*2];
    }

    void operator*=(double s)
    {
        for (int i=0; i<4; i++)
            mat[i]*=s;
    }

    McMat2d operator*(double s) const
    {
        double newMat[4];
        for (int i=0; i<4; i++)
            newMat[i] = mat[i]*s;

        return McMat2d(newMat);
    }

    McVec2d operator*(McVec2d v) const
    {
        return McVec2d(mat[0]*v[0]+mat[1]*v[1], mat[2]*v[0]+mat[3]*v[1]);
    }

    McMat2d operator*(McMat2d m) const
    {
        return McMat2d(mat[0]*m.mat[0]+mat[1]*m.mat[2], mat[0]*m.mat[1]+mat[1]*m.mat[3],
                       mat[2]*m.mat[0]+mat[3]*m.mat[2], mat[2]*m.mat[1]+mat[3]*m.mat[3]);
    }

    McMat2d operator-(McMat2d m) const
    {
        return McMat2d(mat[0]-m.mat[0], mat[1]-m.mat[1], mat[2]-m.mat[2], mat[3]-m.mat[3]);
    }

    McMat2d operator+(McMat2d m) const
    {
        return McMat2d(mat[0]+m.mat[0], mat[1]+m.mat[1], mat[2]+m.mat[2], mat[3]+m.mat[3]);
    }

    /// Multiplies a row vector from the left.
    void multVecMatrix(const McVec2d& src, McVec2d& dst) const
    {
        dst[0] = src[0]*mat[0]+src[1]*mat[2];
        dst[1] = src[0]*mat[1]+src[1]*mat[3];
    }

private:
    double mat[4];
};

#endif

/// @}

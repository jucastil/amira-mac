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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef _TRIANGLE_DISTORTION_H
#define _TRIANGLE_DISTORTION_H

#include <hxsurftools/HxSurfToolsWinDLLApi.h>

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <float.h>

class Surface;

/** Class for measuring distortion of 3d triangles. */

class HXSURFTOOLS_API TriangleDistortion {

  public:

    /// Default constructor.
    TriangleDistortion() 
    {
        mT1p1 = mT1p2 = mT1p3 = mT2p1 = mT2p2 = mT2p3 = McVec3f(0);
        ev[0] = ev[1] = 0;
        mAreaT1 = mAreaT2 = mAreaT12 = 0;
        initFlag = false;
    }

    /// Constructor with coordinates of triangles
    TriangleDistortion(const McVec3f& t1p1, const McVec3f& t1p2, const McVec3f& t1p3,
                       const McVec3f& t2p1, const McVec3f& t2p2, const McVec3f& t2p3) 
    {
        mT1p1 = t1p1;
        mT1p2 = t1p2;
        mT1p3 = t1p3;
        mT2p1 = t2p1;
        mT2p2 = t2p2;
        mT2p3 = t2p3;

        computeEigenValues();
    }

    /// Destructor.
    ~TriangleDistortion() {}

    /// Distortion metrics.
    enum { ANGLE_DISTORTION=0, AREA_DISTORTION, STRETCH_DISTORTION, NUM_DISTORTIONS };

    /// Computation for all triangles on the surfaces.
    void compute( Surface* surface1, Surface* surface2,
                  float* triangleDistortions,
                  int distortion , bool useAreaWeight=false);

    /// Angle distortion based on singular values
    inline double angle();

    /// Area distortion based on singular values
    inline double area(double scale=1.);

    /// Length distortion based on singular values
    inline double stretch();

    /// Area of triangle 1
    double areaT1() { if (!initFlag) return -1; return mAreaT1; }

    /// Area of triangle 2
    double areaT2() { if (!initFlag) return -1; return mAreaT2; }

    /// Sum of areas of triangles
    double areaT12() { if (!initFlag) return -1; return mAreaT12; }
    
  protected:

    /// Coordinates of the two triangles
    McVec3f mT1p1, mT1p2, mT1p3, mT2p1, mT2p2, mT2p3;

    /// Singular values
    double ev[2];

    /// Areas of the triangles (mAreaT12 is the sum)
    double mAreaT1, mAreaT2, mAreaT12;

    /// Indicates whether singular values and have been computed
    bool initFlag;

    /// Compute eigenvalues values of triangle-triangle mapping
    void computeEigenValues();
};

//--------------------------------------------------------------------

inline double TriangleDistortion::angle()
{
    if ( !initFlag ) return FLT_MAX;

    double quot = ev[0]/ev[1];

    return (quot + 1./quot - 2.);
}

//--------------------------------------------------------------------

inline double TriangleDistortion::area(double scale)
{
    if ( !initFlag ) return FLT_MAX;

    double prod = ev[0]*ev[1];

    double s = scale*scale;

    return (prod/s + s/prod - 2.);
}

//--------------------------------------------------------------------

inline double TriangleDistortion::stretch()
{
    if ( !initFlag ) return FLT_MAX;

    return (ev[0] + ev[1] + 1./ev[0] + 1./ev[1] - 4.);
}

//--------------------------------------------------------------------

#endif

/// @}

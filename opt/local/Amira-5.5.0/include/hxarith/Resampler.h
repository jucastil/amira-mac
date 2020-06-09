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

/// @addtogroup hxarith hxarith
/// @{
#ifndef _RESAMPLER_H
#define _RESAMPLER_H

#include <hxarith/HxArithWinDLLApi.h>
#include <mclib/McPrimType.h>

class HxSpatialData;
class HxField3;
class HxLattice3;
class McVec3f;
class HxData;
class McVec3i;

/** This class resamples a regular scalar field and produces a new
field of different x, y, and z resolution. */

class HXARITH_API Resampler {

public:

    /// Default constructor.
    Resampler() { phaseShift=0; }

    typedef enum {
        BOX = 0,
        TRIANGLE,
        BELL,
        B_SPLINE,
        LANCZOS,
        MITCHELL,
        MINIMUM,
        MAXIMUM
    } FilterType;

    ///Do the average
    void doAverage(const unsigned char* srcLabel, const unsigned char* srcProb,
                unsigned char* dstLabel, unsigned char* dstProb,
                const int* dsrc,
                const int* averageSize,
                HxField3* field = 0, HxLattice3* lattice = 0);

    ///Conveniance method
    void doAverage(HxData* src, const int* averageSize,
                   HxField3*& result);
    void doResample(HxSpatialData* inputDataSet, HxSpatialData*& outputResult,
                    const McVec3f& newRes, HxField3* inputReference,
                    const McVec3f& voxSize, FilterType _filterType,
                    unsigned int numThreads=1);

    ~Resampler() {};

    void setPhaseShift(float _phaseShift) {phaseShift = _phaseShift;};

    // This struct has to be public. Otherwise we can't use it below in
    // CLIST on SunOS.
    typedef struct {
        int pixel;
        float weight;
    } CONTRIB;

protected:

    void zoom3d(HxLattice3& src, HxLattice3& dst,
                const float fracddst[],
                float (*filterf)(float), float fwidth,
                unsigned int numThreads=1);

    void updateParameters(HxField3* field, HxLattice3* lattice);

    void setUniformCoords(HxLattice3*, const HxLattice3*,
                          const float* fracddst = 0);
    void setStackedCoords(HxLattice3*, const HxLattice3*,
                          const float* fracddst = 0);
    void setRectilinearCoords(HxLattice3*, const HxLattice3*,
                              const float* fracddst = 0);
    void setCurvilinearCoords(HxLattice3*, const HxLattice3*,
                              const float* fracddst = 0);

    typedef struct {
        int     n;   /* number of contributors */
        CONTRIB *p;  /* pointer to list of contributions */
    } CLIST;

    CLIST* filter_contrib(int dstSize, int size, float scale,
                          float (*filterf)(float), float fwidth);

    void zoom1d(int nDst, float fracnDst,
                float* dst, int nSrc, const float* src);

    FilterType filterType;

    float phaseShift;
};

#endif

/// @}

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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef BOOKSTEINWRAP_H
#define BOOKSTEINWRAP_H

#include <mclib/McData3D.h>
#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McBox3f.h>
#include <mclib/McBox3i.h>
#include <mclib/McListStack.h>
#include <mclib/McHashTable.h>
#include <mclib/McVec2f.h>
#include <mclib/McProgressInterface.h>

#include "Contour2D.h"
#include "GiSelection2D.h"
#include "GiSelection3D.h"
#include "HxGiWinDLLApi.h"

class HXSEGEDITOR_API BooksteinWrap {

public:
    enum {
        BASIS_XLOGX=0,
        BASIS_X3=1,
    };

    /** Constructor. If basis is -1 the xlogx basis is used unless the Tcl
        variable booksteinnThinPlate3D is set. If polyOrder is -1 the order
        of the constraint polynomial is determined from the value of the Tcl
        variable booksteinPolyOrder. The default is 0 (no constraints). */
    BooksteinWrap(GiSelection3D* rasterData,
                  McBox3f* bbox, int isoValue=128, int basis=-1, int polyOrder=-1);

    /// Destructor.
    ~BooksteinWrap();

    /** Computes the implicit function (explicitly) that interpolates
        between the boundaries of the selection (a certain material), and
        labels all those voxels of data where the value of the implicit
        function is greater than zero. */
    int wrap(McProgressInterface* progress=0, int vrbs=1,
        int maxDim=-1, double maxRcond=0.);

    int getImplicitFunction(McData3D<float>* implFunc,
            McProgressInterface* progress=0, int vrbs=1, int maxDim=-1,
            int optimize=1, float maxRcond=0.);

protected:

    int prepareEvaluation(McProgressInterface* progress, int maxDim);

    void createLineSet(const McDArray <McDArray<McVec3d>*>& conts);

    void showLoopIntersection(Contour2D::Loop& loop, McVec2f& p1, McVec2f& p2);

    int verbose;

    double rcondMax;

    int stopWorking;

    /// Input field
    GiSelection3D* data;

    /// Dimensions of selection field data
    int dims[3];

    /// .
    McVec3d origin, size, vs, lo;

    int useErosion;

    int isoVal;

    int basisFunction;

    int polyOrder;

    double minDist;

    double maxDist;

    /// Contour arrays where boundary constraints hold
    McDArray <McDArray<McVec3d>*> boundaries0;
    McDArray <McDArray<McVec3d>*> boundaries1;
    McDArray <McDArray<McVec3d>*> boundaries2;

    /// Contour arrays where normal constraints hold
    McDArray <McDArray<McVec3d>*> innerPoints0;
    McDArray <McDArray<McVec3d>*> innerPoints1;
    McDArray <McDArray<McVec3d>*> innerPoints2;

    /// .
    McDArray<McVec3d> allpoints;
    McDArray<double> b;

    /// Bounding box of object to be wrapped
    McBox3i wrapBox;

    /// .
    int voxelNum, cornerNum, flooded;

    /// .
    void freeMemory();

    /// Computes points where boundary and inner constraints hold
    void computeBoundaryAndInnerPoints();

    // Temporaries for computeBoundaryAndInnerPoints()
    GiSelection2D tmp1,tmp2,tmp3,tmp4;

    /// Computes contraints for one slice
    int checkSlice(int orientation, int slice, int ni, int nj, int offi, int offj);

    /// Compute morphological AND at i,j in binary image in 4-neighborhood
    inline int morphoAnd(int i, int j, int ni, int nj, GiSelection2D& binary) {
        if (binary.isSet(i+j*ni)==0)
            return 0;
        if (i>0 && binary.isSet(i-1 + j*ni)==0)
            return 0;
        if (j>0 && binary.isSet(i+(j-1)*ni)==0)
            return 0;
        if (i<ni-1 && binary.isSet(i+1+j*ni)==0)
            return 0;
        if (j<nj-1 && binary.isSet(i+(j+1)*ni)==0)
            return 0;
        return 1;
    }

    /// Setup and solve the resulting linear system
    int setupAndSolveSystem(McProgressInterface* progress);

    /// Evaluates thin-plate-spline function
    double thinPlateSpline(const McVec3d &p1, const McVec3d &p2);

    /// Evaluates superposition of basis functions at x.
    double interpolatingFunction(const McVec3d& x);

    int computeWrapBox();

    void wrapData3D(McProgressInterface* progress);

    void testface(McVec3i nv, McVec3i& c,
                  McVec3i c1, McVec3i c2, McVec3i c3, McVec3i c4,
                  McListStack<McVec3i>& activeVoxels,
                  McHashTable<McVec3i, double>& cornerValues);

    int goodSeed(int orientation, int ii, int jj,
                 double height, McVec3i& sv);

    void doFloodFill(McVec3i seedVoxel);

    int linesIntersect(McVec2f p1, McVec2f p2, McVec2f q1, McVec2f q2);

    inline int getSystemDim() {
        int i, systemDim = 0;
        for (i=0; i<boundaries0.size(); i++)
            systemDim += boundaries0[i]->size();
        for (i=0; i<boundaries1.size(); i++)
            systemDim += boundaries1[i]->size();
        for (i=0; i<boundaries2.size(); i++)
            systemDim += boundaries2[i]->size();
        return 2*systemDim;
    }
};

#endif

/// @}

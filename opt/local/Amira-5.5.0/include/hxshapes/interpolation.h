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

/// @addtogroup hxshapes hxshapes
/// @{
#ifndef INTERPOLATION
#define INTERPOLATION

#include "HxShapesWinDLLApi.h"
#include <mclib/McDArray.h>

class McMat4f;
class McVec3f;

// --------------------------------------------------------------------------
//    functions for interpolation and averaging of a point sequence
// --------------------------------------------------------------------------

/** linear interpolation of a point sequence
    @c co are the source coordinates to be interpolated
    @c result will contain the intepolated points
    @c interpolationPointNumber is the number of points which will
    be added between each consecutive source points co[i] and co[i+1]
    thus the size of result will be (v.size()-1)*interpolationPointNumber+v.size()
*/
bool HXSHAPES_API linearInterpolation(const McDArray<McVec3f>& co,
                         McDArray<McVec3f>& result,
                         int interpolationPointNumber);

/** cubic interpolation of a point sequence
    @c co are the source coordinates to be interpolated
    @c result will contain the intepolated points
    @c interpolationPointNumber is the number of points which will
    be added between each consecutive source points co[i] and co[i+1]
    thus the size of result will be (v.size()-1)*interpolationPointNumber+v.size()
*/
bool HXSHAPES_API cubInterpolation(const McDArray<McVec3f>& co,
                      McDArray<McVec3f>& result,
                      int interPolationPointNumber);

/** cubic spline interpolation of a point sequence
    @c co are the source coordinates to be interpolated
    @c result will contain the intepolated points
    @c interpolationPointNumber is the number of points which will
    be added between each consecutive source points co[i] and co[i+1]
    thus the size of result will be (v.size()-1)*interpolationPointNumber+v.size()
    first and last element of @c co can be border points which are 
    used for getting correct calculations of the spline edges
    if they are given @c leftEndGiven resp. @c rightEndGiven must be set
*/
bool HXSHAPES_API cubInterpolation2(McDArray<McVec3f>& co,
                       McDArray<McVec3f>& result,
                       int interPolationPointNumber,
                       bool leftEndGiven=false ,
                       bool rightEndGiven=false );

/** b Spline interpolation of a point sequence (in 2 or 3d)
    @c co are the source coordinates to be interpolated
    @c result will contain the intepolated points
    @c interpolationPointNumber is the number of points which will
    be added between each consecutive source points co[i] and co[i+1]
    thus the size of result will be (v.size()-1)*interpolationPointNumber+v.size()
    @c dim is the dimension of @c co (2-3)
*/
bool HXSHAPES_API bezierInterpolation(McDArray<McVec3f>& co, 
                         McDArray<McVec3f>& res,
                         int dim,
                         int interPolationPointNumber);

/** b-Spline interpolation of a point sequence
    @c co are the source coordinates to be interpolated
    @c result will contain the intepolated points
    @c interpolationPointNumber is the number of points which will
    be added between each consecutive source points co[i] and co[i+1]
    thus the size of result will be (v.size()-1)*interpolationPointNumber+v.size()
*/
bool HXSHAPES_API bSplineInterpolation(const McDArray<McVec3f>& co,
                          McDArray<McVec3f>& result,
                          int interpolationPointNumber);

/** non weighted averaging of a point sequence
    @c co are the source coordinates to be averaged
    @c result will contain the averaged points
    width of averaging is @c avDistance*2+1
*/

bool HXSHAPES_API averaging(const McDArray<McVec3f>& co,
               McDArray<McVec3f>& result,
               int avDistance=1) ;


// --------------------------------------------------------------------------
//    internal functions
// --------------------------------------------------------------------------

void _getInterpolationParams(const McDArray<McVec3f>& coords,int f1, 
                               McVec3f &p1, McVec3f &p2,
                               McVec3f &dp1, McVec3f &dp2);

void _bezierPoints     // compute Bezier points of a bezier spline curve 
(
 McDArray<McVec3f>& b, // weight points 
 McDArray<McVec3f>& d, // Bezier points 
 int    m,             // number of curve pieces 
 int    dim            // 2,3 for planar, spatial curve
);  

void _bezierSpline     // evaluation of a Bezier spline curve 
(
 float   t,            // parameter value t from [0,1] 
 int    m,             // number of curve pieces     
 int    dim,           // 2,3 for planar, spatial curve 
 McDArray<McVec3f>& b, // Bezier points               
 McVec3f& p            // coordinates of curve point   
);  

void _bSpline (McMat4f& M,
               McVec3f*& result,
               int n);

#endif

/// @}

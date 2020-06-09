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
#ifndef REG_TYPESANDMACROS
#define REG_TYPESANDMACROS

/// Class of image data.
typedef enum 
{
  /// Grey-level data.
  REG_DATACLASS_GREY,
  /// Binary (1 / 0) data.
  REG_DATACLASS_BINARY,
  /// (Segmented) label data.
  REG_DATACLASS_LABEL,
  /// Data type unknown.
  REG_DATACLASS_UNKNOWN
} RegDataClass;


typedef enum 
{
  REG_INTERPOLATOR_TRILINEAR,
  REG_INTERPOLATOR_NEARESTNEIGHBOUR
} RegInterpolator;

typedef enum 
{ 
    REG_STEEPEST_DESCENT = 0, 
    REG_CONJUGATE_GRADIENTS=1, 
    REG_QUASI_NEWTON=2 
} RegGradientStrategies;

#define ABS(A) ((A) >= 0 ? (A) : -(A))

template<class T> inline T hxmin( T a, T b ) {return a>b?b:a;}
template<class T> inline T hxmax( T a, T b ) {return a>b?a:b;}

#include <float.h>
#include <limits.h>
#ifndef MINFLOAT
#define MINFLOAT FLT_MIN
#endif
#ifndef MAXFLOAT
#define MAXFLOAT FLT_MAX
#endif

//marker for non-successful move operation in functional
#define REG_OUTSIDE -FLT_MAX

//the minimum number of processors for which threads are used
#define REG_MIN_THREADS 3

//correction for control grid placement: prevent points or voxels from "falling outside"
//also necessary because landmarks are usually placed outside the surface
#define REG_GRID_CORRECTION 0.01


typedef enum 
{
    REG_DIST = 0, 
    REG_DIST_CURVEDNESS = 1,
    REG_DIST_SHAPEINDEX = 2,
    REG_DIST_CURVEDNESS_SHAPEINDEX = 3,
    REG_DIST_NORMALS = 4, 
    REG_DIST_NORMALS_CURVEDNESS = 5,
    REG_DIST_NORMALS_SHAPEINDEX = 6,
    REG_DIST_NORMALS_CURVEDNESS_SHAPEINDEX = 7
} RegSurfMatchingMode;


typedef enum { 
    REG_NO_CONSTRAINTS = 0,
    REG_GRIDENERGY = 1,
    REG_JACOBIAN = 2,
    REG_GRIDENERGY_JACOBIAN = 3
} RegRegularizationTerms; 


#endif

/// @}

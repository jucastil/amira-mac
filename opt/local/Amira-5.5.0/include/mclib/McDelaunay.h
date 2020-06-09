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
#ifndef MC_DELAUNAY_H
#define MC_DELAUNAY_H

#include "McWinDLLApi.h"

#include "McVec3f.h"
#include "McVec2f.h"
#include "McDArray.h"

/** This class provides a 2D and 3D triangulator. It computes the
    delaunay triangulation from a set of 2D/3D points and gives a set
    of triangles/tetrahedra that form the delaunay triangulation of these points.
*/
class MCLIB_API McDelaunay
{
public:
    /** This provides a triangle. It contains the indices of its 3 points
	in the given point set */
    struct Triangle {
	/// indices of its 3 points in the given point set
	int t[3];
	/// Access method.
 	int& operator[](int idx) {return t[idx];}
    };

    /** This provides a tetrahedron. It contains the indices of its 4 points
	in the given point set */
    struct Tetrahedron {
	/// indices of its 4 points in the given point set
	int t[4];
	/// Access method.
	int& operator[](int idx) {return t[idx];}
    };

    /** 2D triangulator. On return @c triangles contains all triangles
	belonging to the 2D delaunay triangulation of the given points.
	Each triangle contains the indices of its 3 points.
    */
    int triangulate2D (McVec2f* points, int nPoints,
	McDArray<Triangle>& triangles);

    /** 3D triangulator. On return @c tetrahedra contains all tetrahedra
	belonging to the 3D delaunay triangulation of the given points.
	Each tetrahedra contains the indices of its 4 points.
    */
    int triangulate3D (McVec3f* points, int nPoints,
	McDArray<Tetrahedron>& tetrahedra);

    /// Write points and triangles to file in EPS file format.
    int writeEPS (const char* filename, McVec2f* points, int nPoints,
	McDArray<Triangle>& triangles);
};

#endif

/// @}

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

/// @addtogroup hxsurfremesh hxsurfremesh
/// @{
#ifndef _RmEdgePathParametrization_H
#define _RmEdgePathParametrization_H

#include <mclib/McDArray.h>
#include <mclib/McVec3f.h>
#include <mclib/McBitfield.h>

#include "hxsurfremeshAPI.h"
#include <hxsurfacepath/SurfaceEdgeNode.h>
#include <hxsurfacepath/SurfaceVertexNode.h>

/** This class defines a continuous path parametrization.
    The value of lambda is in the interval [0,1]. 
    If the path is closed, then points[0]==points.last() !!!
*/

class Surface;

class HXSURFREMESH_API RmEdgePathParametrization
{

public:

    /// Constructor
    RmEdgePathParametrization();

    /// Constructor
    ~RmEdgePathParametrization();

    /// Create path
    void create(Surface* surface, const McDArray<int>& p);

    /// Compute triangle/barycentric coordinates from parameter
    void findTriangle(float lambda, int& tri3d, McVec3f& bary) const;
    void findSurfaceEdgeNode(float lambda, SurfaceEdgeNode& epn) const;

    /// Compute parameter from triangle/barycentric coordinates 
    void getParam(int tri3d, const McVec3f& bary, float& lambda) const;
    void getParam(const SurfaceNode* epn, float& lambda) const;
    
    /// Assignment operator
    RmEdgePathParametrization& operator=(const RmEdgePathParametrization& other) {
        copyData(other);
        return (*this);
    }

protected:

    /// Pointer to surface
    Surface* surface;

    /// Indices of surface vertices
    McDArray<int> points;

    /// Indices of surface edges
    McDArray<int> edges;

    /// Cumulative curve-length
    McDArray<float> lengths;

    /// Keeps track of all triangles along the path
    McBitfield containsTriangle;

    /// Copy data
    void copyData(const RmEdgePathParametrization &source);
};

#endif

/// @}

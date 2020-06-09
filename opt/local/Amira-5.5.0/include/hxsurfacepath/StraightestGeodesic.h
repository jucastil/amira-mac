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

/// @addtogroup hxsurfacepath hxsurfacepath
/// @{
#ifndef _STRAIGHTEST_GEODESIC_H
#define _STRAIGHTEST_GEODESIC_H

#include "hxsurfacepathAPI.h"
#include "SurfaceNodeFactory.h"

#include <mclib/McVec3f.h>
#include <mclib/McVec2f.h>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>

class SurfaceNode;

/** This class computes the straightest geodesic from a given
    point/direction.  For more information see article by K. Polthier
    and M. Schmies: "Straightest Geodesics on Polyhedral Surfaces",
    in: Mathematical Visualization, Ed: H.C. Hege, K. Polthier,
    Springer Verlag, 1998, ISBN 3-540-63991-8, Pages 391.
*/
class HXSURFACEPATH_API StraightestGeodesic
{

public:

    /// Constructor.
    StraightestGeodesic() : nFactory(0) {}

    /// Initializes surface.
    void init(Surface* surface);

    /// Computes straightest geodesic from @c node in direction @c
    /// vec. Returns true length of path.
    float compute(SurfaceNode* node, const McVec3f& vec, float length,
                  McDArray<McHandle<SurfaceNode> >& path);

    /// Returns last node of straightest geodesic from @c node in
    /// direction @c vec. Returns true length of path.
    float compute(SurfaceNode* node, const McVec3f& vec, float length,
                  McHandle<SurfaceNode>& last);

    /// Returns local coordinates of @c other node in neighbourhood of
    /// @c node.
    static McVec2f findInLocalNeighbourhood(SurfaceNode* node,
                                            const McDArray<int>& points,
                                            const McDArray<McVec2f>& coords,
                                            const McVec2f& p,
                                            SurfaceNode* other);

protected:

    /// Surface node factory.
    SurfaceNodeFactory nFactory;

    /// Computes location of first surface node.
    SurfaceNode* initPath(SurfaceNode* node, const McVec3f& vec);

    /// Computes location of next node from previous two nodes.
    SurfaceNode* tracePath(SurfaceNode* current, SurfaceNode* last);

    /// 2D intersection in local neighbourhood.
    SurfaceNode* computeIntersection2D(const McVec2f& p, const McVec2f& q, 
                                       const McDArray<McVec2f>& coords, 
                                       const McDArray<int>& points,
                                       float cutoff);

    /// For debugging.
    void showNeighbourhood(const McDArray<McVec2f>& coords, 
                           const McVec2f& center, 
                           const McVec2f& direc);
};

#endif // _STRAIGHTEST_GEODESIC_H

/// @}

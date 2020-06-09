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
#ifndef SURFACE_INTERSECTOR_H
#define SURFACE_INTERSECTOR_H

#include <hxcore/HxCompModule.h>
#include <mclib/McVec3f.h>
#include <hxsurface/HxSurface.h>
#include "SurfaceNode.h"
#include <hxcore/HxPortDoIt.h>
#include "HxSurfacePathSet.h"

/** Intersects two surfaces and produces SurfacePaths for each of them
    on the lines of intersection
*/

class HXSURFACEPATH_API HxSurfaceIntersector : public HxCompModule
{
    HX_HEADER(HxSurfaceIntersector);
public:
    /// Constructor.
    HxSurfaceIntersector(void);

    /// Destructor.
    virtual ~HxSurfaceIntersector(void);

    /// Computes surface intersection.
    virtual void doIt ();

    /// Updates GUI.
    virtual void update();

    /// Second surface is connected here.
    HxConnection portData2;

    /// Compute buttons for LineSet or Surface Path.
    HxPortDoIt portDoIt;

private:
    /// Puts the pieces together.
    void smoothPathSet(HxSurfacePathSet* pathSet);

    /// Searches for a next node after the last node of path.
    void getNextNode(int* nextNode,McDArray<int>& path,HxSurfacePathSet* pathSet,   McDArray<McDArray<int> >& beginNodes,   McDArray<McDArray<int> >& endNodes);

    /// Looks for a path that was not used yet.
    void getPath(McDArray<int>& path,HxSurfacePathSet* pathSet);

    /// Returns true if the number of triangles is equal and the
    /// triangles have identical vertices, where identical means equal
    /// 3d coordinates.
    bool areSurfacesIdentical( const HxSurface * surf1,
                               const HxSurface * surf2 ) const;

    float m_machineEps;
};

#endif // SURFACE_INTERSECTOR_H

/// @}

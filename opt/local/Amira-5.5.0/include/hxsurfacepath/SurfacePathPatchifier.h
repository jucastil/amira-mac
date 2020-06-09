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
#ifndef _SURFACE_PATH_PATCHIFIER_H
#define _SURFACE_PATH_PATCHIFIER_H

#include "SurfacePathSet.h"
#include "hxsurfacepathAPI.h"

class McBitfield;
class HxSurface;

/** This class implements patchification of a surface along a surface
    path.  However, in order to be able to patchify the surface, the
    surface path needs to lie completely on edges of the surface.
    This is true for edge path.  In order to convert an arbitrary path
    into an edge path, the surface needs to be re-triangulated along
    the path using a PathTriangulatorMethod.
 */
class HXSURFACEPATH_API SurfacePathPatchifier {

public:

    /// Constructor.
    SurfacePathPatchifier(SurfacePathSet* ps)
    {
        pathSet = ps;
        if ( !pathSet )
            return;

        surface = pathSet->getSurface();
    }

    /// Patchify the surface.
    bool compute(bool orderByArea=true);

    /// Create material list for given hxsurface.
    static void createMaterials(HxSurface* surf);

protected:

    /// Input path set (modified after compute was called).
    SurfacePathSet* pathSet;

    /// Reference to the surface to be patchified.
    Surface* surface;

    /// Fill triangles starting from first.
    void fillTriangles(Surface* surface, 
                       int first, McDArray<int>& list,
                       const McBitfield& isBorderEdge);
};

#endif // _SURFACE_PATH_PATCHIFIER_H

/// @}

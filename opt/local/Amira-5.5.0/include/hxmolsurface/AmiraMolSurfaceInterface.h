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

/// @addtogroup hxmolsurface hxmolsurface
/// @{
#ifndef AMIRA_MOL_SURFACE_INTERFACE_H
#define AMIRA_MOL_SURFACE_INTERFACE_H

#include <mclib/McDArray.h>
#include <mclib/McVec2i.h>
#include <mclib/McVec3i.h>
#include <mclib/McVec3f.h>

#include <molsurface/MolSurfaceInterface.h>

#include "HxMolSurfaceWinDLLApi.h"

class HxMolSurface;

class HXMOLSURFACE_API AmiraMolSurfaceInterface : public MolSurfaceInterface {
    
public:  
    AmiraMolSurfaceInterface(HxMolSurface * molSurf);
    virtual ~AmiraMolSurfaceInterface();

    virtual McDArray<McVec3f> & getPoints();
    virtual McDArray<McVec3i> & getTrianglePoints();
    virtual McDArray<int>     & getNumAtomsPerMol();
    virtual McDArray<int>     & getTriToAtom();
    virtual McDArray<McVec2i> & getTriSidesToAtom();
    virtual McDArray<int>     & getPointToAtom();
    virtual McDArray<McVec3f> & getCriticalPoints();
    virtual McDArray<McVec3f> & getCriticalPointNormals();

    virtual void setNumSphericalConcavePatches(const int numSphericalConcavePatches);
    virtual void setProbeRadius(const float probeRadius);
    virtual void setSurfaceType(const int surfaceType);

    virtual void clearSurface();

    /// This function copies the trianglePoints into the HxSurface::Triangle 
    /// data structure.
    virtual void finishSurface();

private:
    HxMolSurface * molSurface;

    /// This array is used to temporarily store the triangles, i.e. its points. 
    /// It is later copied into the HxSurface::Triangle data structure by calling
    /// the function finishSurface.
    McDArray<McVec3i> trianglePoints;
}; 
#endif


/// @}

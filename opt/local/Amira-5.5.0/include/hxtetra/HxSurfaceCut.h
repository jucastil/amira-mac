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

/// @addtogroup hxtetra hxtetra
/// @{
#ifndef HX_SURFACE_CUT_H
#define HX_SURFACE_CUT_H

#include <mclib/McBitfield.h>
#include <mclib/McHashTable.h>
#include <hxcore/HxArbitraryCut.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxsurface/HxSurface.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/SoPrimitiveVertex.h>
#include <hxtetra/HxTetraWinDLLApi.h>

struct HxSurfaceCutVertex;

/**  */
class HXTETRA_API HxSurfaceCut : public HxArbitraryCut {
	
	HX_HEADER(HxSurfaceCut);
	
public:
    /// Constructor.
    HxSurfaceCut();
	
    /// Add or remove certain materials.
    HxPortButtonMenu portSelection;
	
	// Create surface button
	HxPortButtonList portBuildSurface;
	
    /// Update method.
    virtual void update();
	
    /// Compute method.
    virtual void compute();
	
    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
	
    /// Save network.
    virtual void savePorts(FILE* fp);
	
protected:
    virtual ~HxSurfaceCut();
	
    McBitfield materialFlags;
    McHandle<SoShapeKit> shapeKit;
	McDArray<int> mat2FaceMat;
	
    void intersect(HxSurface* surf);
    void findHoles(McHashTable<int,McDArray<HxSurfaceCutVertex*>*>& startPoints);
    HxSurfaceCutVertex* intersect(int ia, int ib, const float* z, const SbVec3f* c);
	static void triangleCB (void* data,SoCallbackAction *action, const SoPrimitiveVertex *v1, const SoPrimitiveVertex *v2, const SoPrimitiveVertex *v3);
	void buildHxSurface();
};

#endif


/// @}

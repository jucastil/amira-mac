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
#ifndef HX_GRID_CUT
#define HX_GRID_CUT

#include <hxtetra/HxTetraWinDLLApi.h>
#include <hxcore/HxArbitraryCut.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxTetraGrid.h>
#include <hxfield/HxTetraScalarField3.h>
#include <hxfield/TetraCut.h>

class SoShapeKit;
class SoMaterial;
class SoPrimitiveVertex;

/// Computes intersection of tetrahedral grid or field and cutting plane
class HXTETRA_API HxGridCut : public HxArbitraryCut {
	
	HX_HEADER(HxGridCut);
	
public:
    /// Constructor.
    HxGridCut();
	
    /// Compute method.
    virtual void compute();
	
    /// Update method.
    virtual void update();
	
    /// Parse method.
    int parse(Tcl_Interp*, int argc, char **argv);
	
    /// Colormap to be used.
    HxPortColormap portColormap;
	
    /// Gouraud or texture ?
    HxPortRadioBox portTexture;
	
    /// Modify list of displayed tetrahedra
    HxPortButtonMenu portSelection;
	
	// Create surface button
	HxPortButtonList portBuildSurface;
	
protected:
    HxGridCut(const McTypeInfo* type);
    void commonInit();
    ~HxGridCut();
	
    HxTetraGrid* grid;
    HxTetraScalarField3* field;
    SoShapeKit*	shape;
    SoMaterial* materialNode;
    TetraCut cut;
	McDArray<int> mat2FaceMat;
	
    void savePorts(FILE* fp);
    void computeIntersection();

	static void triangleCB (void* data,SoCallbackAction *action, const SoPrimitiveVertex *v1, const SoPrimitiveVertex *v2, const SoPrimitiveVertex *v3);
	void buildHxSurface();
};

class HxFieldCut : public HxGridCut {
	HX_HEADER(HxFieldCut);
public: HxFieldCut() : HxGridCut(HxTetraScalarField3::getClassTypeId()) { }
protected: ~HxFieldCut() { }
};

#endif // HX_GRID_CUT


/// @}

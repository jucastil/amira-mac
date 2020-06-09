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
#ifndef HX_GRID_BOUNDARY_H
#define HX_GRID_BOUNDARY_H

#include <hxtetra/HxTetraWinDLLApi.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxTetraGrid.h>
#include <hxsurface/HxTriBase.h>

/** Display the boundary faces of a tetrahedral grid. */

class HXTETRA_API HxGridBoundary : public HxTriBase {

  HX_HEADER(HxGridBoundary);

  public:
    /// Constructor.
    HxGridBoundary();

    /// Update the user interface.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Allows that modules can be connected to grids and scalar fields.
    virtual int autoConnect(HxObject* primary);

    /// Material menu (material A - material B).
    HxPortMultiMenu portMaterial;

    /// Color mode: 0=normal, 1=mixed, 2=twisted
    HxPortRadioBox portColorMode;

    /// Returns the grid being visualized.
    HxTetraGrid* getGrid() { return grid; }

    /// Overloaded method creates surface with multiple patches.
    virtual void createSurfaceData();

    /// Checks if a given triangle is selected or not.
    int isSelectedTri(int triNdx);

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Save state.
    virtual void savePorts(FILE* fp);

    /// Returns parameter bundle where groups should be stored.
    virtual HxParamBundle* selectinterface_bundle(int create=0);

    /** Redefine this method to add specific picking information.
    GridBoundary appends "originalIdx", "tetra0" and "tetra1" to arguments. 
    They are the indices of the tetrahedra adjacent to the picked triangle 
    "originalIdx" in the original grid, or "idx" in this skin surface. */
    virtual void gatherPickInfo(
        const SoPickedPoint* pickedPoint, 
        McHashTable<McString, McString>& cbArguments);

  protected:
    virtual ~HxGridBoundary();

    struct Triangle {
	McVec3i points;
	McVec3f normal;
	int originalIndex;
	unsigned int frontColor;
	unsigned int backColor;
    };

    int renderIdx;
    HxTetraGrid* grid;
    McDArray<Triangle> boundaryTriangles;
    int numTriangles;
    int numPoints;

    bool selectAllNew, selectAllNewInternal;
    bool hasSameMaterial;

    void setupSurface(int shouldInitBox);
    void setupColors();

    virtual void bufferNew();
    virtual void bufferClear();

    static void tetraColorsCB(SoSurface::Settings *);
    static void tetraVertexColorsCB(SoSurface::Settings *);
    static void tetraVertexIndicesCB(SoSurface::Settings *);
    static void renderSelectCB(void* userData);
    static void initTex(SoSurface::Settings *s);
    static void finishTex(SoSurface::Settings *s);
    static void computeNormalsCB(SoSurface::Settings *s);

    static SoSurface::RenderTemplate renderTable[];
    static SoSurface::RenderTemplate fancyRenderTable[];
};

#endif

/// @}

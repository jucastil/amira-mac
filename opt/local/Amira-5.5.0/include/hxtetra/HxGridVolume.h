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
#ifndef HX_GRID_VOLUME
#define HX_GRID_VOLUME

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#include <mclib/McBitfield.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxTetraGrid.h>
#include <hxsurface/HxTriBase.h>
#include <hxtetra/HxTetraWinDLLApi.h>

class HxViewerLegend;
class HxLoc3Tetra;
class SoEventCallback;

/** This class displays individual cless of a tetrahedral grid. */

class HXTETRA_API HxGridVolume : public HxTriBase {

  HX_HEADER(HxGridVolume);

  public:
    /// Constructor.
    HxGridVolume();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Allows that modules can be connected to grids and scalar fields.
    virtual int autoConnect(HxObject* primary);

    /// Material menu.
    HxPortMultiMenu portMaterial;

    // Color mode: 0=normal, 1=mixed, 2=twisted
    HxPortRadioBox portColorMode;

    /// Interaction in VR mode (0=query, 1=toggle patches, 2=toggle triangles.
    HxPortRadioBox portVRMode;
    enum { VR_NONE, VR_QUERY, VR_SELECT_MATERIALS, VR_SELECT_TETRAS };

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Returns the grid which is being visualized.
    HxTetraGrid* getGrid() const { return grid; }

    /// Checks if a given tetrahedron is selected or not.
    int isSelected(int tet) const { return tetSelection[tet]; }

    /// Selects a block of tetrahedrons so that they become visible.
    void selectTetra(int first, int num);

    /// Unselects or hides a block of tetrahedrons.
    void unselectTetra(int first, int num);

    /// Automatically displays all tetrahedra one after each other.
    void animate(int nFrames=-1);

    /// Checks if a given triangle is selected or not.
    int isSelectedTri(int tri) const { return triSelection[tri]; }

    /// Save state.
    virtual void savePorts(FILE* fp);

    /// Returns the number of elements (triangles, quads, tetrahedra, ...).
    virtual int selectinterface_getNum() const;

    /// Check whether element i is selected.
    virtual int selectinterface_isSelected(int i) const;

    /// Change selection bit of element i.
    virtual void selectinterface_select(int i, int mode = SET_BIT);

    /// Change selection bit of all elements (allocates bitfield if necessary).
    virtual void selectinterface_selectAll(int mode = SET_BIT);

    /// Returns selected elements in bitfield.
    virtual void selectinterface_getSelected(McBitfield& bitfield);

    /// Returns parameter bundle where groups should be stored.
    virtual HxParamBundle* selectinterface_bundle(int create=0);

    /** Redefine this method to add specific picking information.
    GridVolume appends "tetra0" and "tetra1" to arguments. They are the indices of
    the tetrahedra adjacent to the picked triangle "idx" */
    virtual void gatherPickInfo(
        const SoPickedPoint* pickedPt, 
        McHashTable<McString, McString>& cbArguments);

  protected:
    virtual ~HxGridVolume();
    
    McBitfield triHighlight;
    McBitfield triSelection;
    McBitfield tetHighlight;
    McBitfield tetSelection;

    bool clickToggles;

    HxTetraGrid* grid;
    McVec3f* coords;
    HxTetraGrid::Triangle* triangles;
    unsigned int renderIdx;
    int numTetras;
    int numPoints;
    int pickedTetra;
    int pickedVertex;
    HxLoc3Tetra* locTetra;
    int vrSelect;

    bool selectAllNew, selectAllNewInternal;
    bool hasSameMaterial;

    HxViewerLegend* pickLegend;

    void setupSurface(int shouldInitBox);
    void setupColors();

    virtual void bufferNew();
    virtual void bufferAdd();
    virtual void bufferRemove();
    virtual void bufferClear();
    virtual void bufferHide();
    virtual void viewerSelect();
    virtual void mouseClick(SoEventCallback*);

    /// Create a HxTetraGrid containing all selected tetrahedrons.
    virtual HxTetraGrid * createTetraGridFromSelection(void);

    void getSelectedTetra(ostream& out);
    int getNumSelectedTetras(void);
    void selectTetra(int first, int num, int state);
    void selectTetra(const char* abc);
    void selectBoundaryTets(int bc = 0);
    void setPickInfo(int iTet, int iTri, float v, float w, int is3d);
    int findVisibleTetra(int iTet, const McVec3f& origin,
        const McVec3f& dir, int& iFace, McVec3f& uvtMin);
    int intersectTriangle(const McVec3f&, const McVec3f&, int, McVec3f&);
    int selectConnectedRegion(int tetraIndex);
    int highlightConnectedRegion(int tetraIndex);

    static void coordsCB(int i, const float* coords[3], void* userData);
    static void renderCB(SoSurface::Settings *s);
    static void vertexIndicesCB(SoSurface::Settings *s);
    static void tetraVertexIndicesCB(SoSurface::Settings *s);
    static void vertexColorsCB(SoSurface::Settings *s);
    static void tetraColorsCB(SoSurface::Settings *s);
    static void tetraVertexColorsCB(SoSurface::Settings *s);
    static void fancyRenderCB(SoSurface::Settings *s);
    static void renderSelectCB(void*);
    static void initTex(SoSurface::Settings *s);
    static void finishTex(SoSurface::Settings *s);
    static void computeNormalsCB(SoSurface::Settings *s);

    static SoSurface::RenderTemplate renderTable[];
    static SoSurface::RenderTemplate fancyRenderTable[];

    static void postRenderCB(void *userData);
    static void trackerEventCB(void *userData, SoEventCallback* node);
    static void controllerEventCB(void *userData, SoEventCallback* node);
};

#endif

/// @}

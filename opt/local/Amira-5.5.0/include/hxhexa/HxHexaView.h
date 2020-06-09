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

/// @addtogroup hxhexa hxhexa
/// @{
#ifndef HX_HEXA_VIEW
#define HX_HEXA_VIEW

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#include <mclib/McBitfield.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxfield/HxHexaGrid.h>
#include <hxsurface/HxQuadBase.h>
#include <hxhexa/HxHexaWinDLLApi.h>

class HxLoc3Hexa;
class SoEventCallback;

/** This class displays individual cless of a hexahedral grid. */

class HXHEXA_API HxHexaView : public HxQuadBase {

  HX_HEADER(HxHexaView);

  public:
    /// Constructor.
    HxHexaView();

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

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Returns the grid which is being visualized.
    HxHexaGrid* getGrid() const { return grid; }

    /// Checks if a given hexahedron is selected or not.
    int isSelected(int hex) const { return hexSelection[hex]; }

    /// Selects a block of hexahedrons so that they become visible.
    void selectHexa(int first, int num);

    /// Unselects or hides a block of hexahedrons.
    void unselectHexa(int first, int num);

    /// Automatically displays all hexahedra one after each other.
    void animate(int nFrames=-1);

    /// Save state.
    virtual void savePorts(FILE* fp);

    /// Returns the number of elements (triangles, quads, tetrahedra, ...).
    virtual int selectinterface_getNum() const;

    /// Check whether element i is selected.
    virtual int selectinterface_isSelected(int i) const;

    /// Change selection bit of element i.
    virtual void selectinterface_select(int i, int mode = SET_BIT);

    /// Change selection bit of all elements (allocates bitfield if
    //necessary).
    virtual void selectinterface_selectAll(int mode = SET_BIT);

    /// Returns selected elements in bitfield.
    virtual void selectinterface_getSelected(McBitfield& bitfield);

    /// Returns parameter bundle where groups should be stored.
    virtual HxParamBundle* selectinterface_bundle(int create=0);

  protected:
    virtual ~HxHexaView();

    int handlePseudoColorHexa();
    void pseudoColorGouraudHexa(SoSurface* surface);
    void pseudoColorTextureHexa(SoSurface* surface);

    McBitfield faceHighlight;
    McBitfield faceSelection;
    McBitfield hexHighlight;
    McBitfield hexSelection;

    HxHexaGrid* grid;
    McVec3f* coords;
    HxHexaGrid::Face* faces;
    unsigned int renderIdx;
    int numHexas;
    int numPoints;
    int pickedHexa;
    HxLoc3Hexa* locHexa;

    void setupSurface(int shouldInitBox);
    void setupColors();

    virtual void bufferNew();
    virtual void bufferAdd();
    virtual void bufferRemove();
    virtual void bufferClear();
    virtual void bufferHide();
    virtual void viewerSelect();
    virtual void mouseClick(SoEventCallback*);

    void getSelectedHexa(ostream& out);
    void selectHexa(int first, int num, int state);
    void selectHexa(const char* abc);
    void pickHexa(int id);
    int findVisibleHexa(int, const McVec3f&, const McVec3f&);
    int intersectQuad(const McVec3f&, const McVec3f&, int, McVec3f&);

    static void coordsCB(int i, const float* coords[4], void* userData);
    static void renderCB(SoSurface::Settings *s);
    static void vertexIndicesCB(SoSurface::Settings *s);
    static void hexaVertexIndicesCB(SoSurface::Settings *s);
    static void vertexColorsCB(SoSurface::Settings *s);
    static void hexaColorsCB(SoSurface::Settings *s);
    static void hexaVertexColorsCB(SoSurface::Settings *s);
    static void fancyRenderCB(SoSurface::Settings *s);
    static void renderSelectCB(void* userData);
    static void initTex(SoSurface::Settings *s);
    static void finishTex(SoSurface::Settings *s);

    static SoSurface::RenderTemplate renderTable[];
    static SoSurface::RenderTemplate fancyRenderTable[];

    static void postRenderCB(void *userData);
    static void trackerEventCB(void *userData, SoEventCallback* node);
    static void controllerEventCB(void *userData, SoEventCallback* node);
};

#endif

/// @}

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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef HX_TRI_BASE_H
#define HX_TRI_BASE_H

#include <hxsurface/HxSurfaceWinDLLApi.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
#else
#include <iostream.h>
#endif

#include <hxcore/HxModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortButtonList.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/draggers/SoTabBoxDragger.h>

#include <hxcolor/HxPortColormap.h>
#include <hxsurface/SoSurface.h>
#include <hxsurface/HxPortDrawStyle.h>
#include <hxsurface/HxViewBase.h>
#include <hxsurface/SoTriSurface.h>

/** Base class for modules displaying a set of triangles. This class serves
    as a front end for the SoSurface graphics class. An instance of
    SoSurface as well as some other Open Inventor nodes are automatically
    created in the constructor. Derived classes initialize, show, and hide
    the SoSurface class as needed.

    HxViewBase provides a special-purpose port which allows the user to
    modify the draw style of the triangular surface in a easy and
    consistent way (all modules derived from HxViewBase exhibit a similar
    GUI). Moreover, this class provides a generic buffer-concept allowing
    the user to select triangles by means of an Open Inventor tab-box
    dragger. Triangles inside the tab-box are highlighted (see
    SoSurface). Highlighted triangles can be added to the buffer,
    i.e., selected, or removed from the buffer, i.e., deselected.

    Other features of HxViewBase include the following:


    @li Pseudo-coloring: An arbitrary 3D scalar field can be connected
    to @c portColorField. In this case vertex colors are computed for
	every vertex defined in @c soSurface->coords. Colors are taken from
	a colormap which is attached to @c portColormap. Thus the scalar
	field can be visualized on top of the surface geometry.

	Note, that the base class makes use of the procedural data
	interface provided by the scalar field (createLocation(), eval()).
	Derived classes can extend this behaviour, for example to handle
	scalar fields defined on the same set of triangles being
	displayed by SoSurface. In this case scalar values defined on
	vertices may be accessed direclty, or discontinuities can be
	handled properly.

    @li Surface export: The triangles defined in @c soSurface can be
	automatically converted into a new object of type HxSurface.
	Only selected (visible) triangles will be included into the surface.
	The base class creates surfaces with only a single patch. Derived
	classes may overwrite the method @c createSurfaceData() if more
	information about patches is available (see for example
	HxGridBoundary).

    @li Common Tcl-commands: Many parameters of the SoSurface node can be
	controlled via the Tcl-command interface. This includes line
	width, outline color, highlight color, specular color, shininess,
	alpha mode, normal binding, and more.


*/

class HXSURFACE_API HxTriBase : public HxViewBase {

  HX_HEADER(HxTriBase);

  public:
    /// Constructor for derived classes.
    HxTriBase(const McTypeInfo* dataType=0);

    /// Compute method.
    virtual void compute();

	/// Adds all selected triangles to the given HxSurface.
    /// If a transformation matrix is given, it is applied to all points
    /// before adding them to HxSurface.
	virtual void addToSurface(HxSurface& Surf, SbMatrix *transMat=0);

    ///// Create a HxSurface containing all selected triangles.
    //virtual void createSurfaceData();

    /// enable/disable selection of unvisible triangles on draw
    void selectVisibleOnly(bool b);

    /// return current state of the draw selection mode
    bool selectVisibleOnly(void) const { return(_selectVisibleOnly); }

    /// return Bitfield of currently visible triangles
    McBitfield  getVisibleTriangles(void);

    /// Highlights specified triangle.
    void highlightTriangle(int which, int state) {
    	soTriSurface->highlightTriangle(which, state);
    }

    /// Highlights all triangles.
    void highlightAllTriangles(int state) {
	    soTriSurface->highlightAllTriangles(state);
    }

    /// Selects specified triangle.
    void selectTriangle(int which, int state) {
	    soTriSurface->selectTriangle(which, state);
    }

    /// Selects specified triangles.
    void selectTriangles(const McBitfield & selection, int state) {
        int i, n = selection.nBits();
        for ( i=0; i<n; i++ ) {
            if ( selection[i] )
                soTriSurface->selectTriangle(i, state);
        }
    }

    /// Selects all triangles.
    void selectAllTriangles(int state) {
	    soTriSurface->selectAllTriangles(state);
    }

    /// Checks whether speciefied triangle is highlighted.
    int isHighlighted(int t) { return soTriSurface->isHighlighted(t); }

    /// Checks whether speciefied triangle is selected.
    int isSelected(int t) { return soTriSurface->isSelected(t); }

    virtual int parse(Tcl_Interp* t, int argc, char** argv);

  protected:
    virtual ~HxTriBase();

    /// select visible or unvisible triangles on draw
    bool _selectVisibleOnly;

    /// Highlights all triangles inside box.
    virtual void bufferNew();

    /// Fill the inRoi field of surface according to input.
    virtual void handleRoi();

    /// Shift-click deselects current triangle.
    virtual void mouseClick(SoEventCallback*);

  public:
    virtual void viewerSelect();
    void selectTriangles(const char* abc);
    McHandle<SoTriSurface> soTriSurface;
};

#endif

/// @}

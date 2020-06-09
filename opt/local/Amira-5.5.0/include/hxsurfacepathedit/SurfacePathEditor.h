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

/// @addtogroup hxsurfacepathedit hxsurfacepathedit
/// @{
#ifndef SURFACE_PATH_EDITOR_H
#define SURFACE_PATH_EDITOR_H

#include <hxsurfacepathedit/SurfaceVertexPathEditor.h>

class HxPortSeparator;
class HxPortInfo;
class HxPortRadioBox;
class HxPortFloatTextN;
class HxPortMultiMenu;

class SurfacePathEditor: public SurfaceVertexPathEditor
{
    MC_HEADER(SurfacePathEditor);

public:

    /// Constructor.
    SurfacePathEditor(HxSurfacePathSet* pathSet);

    /// Constructor.  Call setPathSet() after this constructor!
    SurfacePathEditor();

    /// Destructor.
    ~SurfacePathEditor();

    /// Calls SurfaceVertexPathEditor::init() and initializes the node type.
    virtual void init(void);

    /// Initialize ports.
    virtual void initButtons(HxSurfacePathEditor* edi);

    /// Check ports.
    virtual void checkButtons();

    /// Update method.
    virtual void update();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Returns true, if the editor can edit @c ps.  Apparently, this
    /// editor can edit all kinds of path sets.
    virtual bool canEditPathSet(HxSurfacePathSet* ps) { return true; }

protected:

    /// Smoothing and unsmoothing of surface path.
    enum { SMOOTH_PATH=0, SNAP_PATH_TO_EDGES };

    /// Retriangulation strategies.
    enum { REFINE=0, REFINE_CONFORMING};

    /// Tolerance modes.
    enum { WORLD_COORDINATES=0, RELATIVE_COORDINATES};

    /// GUI: seperates general ports from special ports.
    HxPortSeparator* portSeparator;

    /// GUI: path operations for smoothing and unsmoothing the surface path.
    HxPortButtonList* portPathOperations3;

    /// GUI: retriangulation-buttons.
    HxPortButtonList* portRetriangulate;

    /// GUI: epsilon that specifies the distance from a path node
    /// within which the clicked point will be regarded as being equal
    /// to a certain node.
    HxPortFloatTextN* portSnapEpsilon;

    /// GUI: snapping new points?
    HxPortRadioBox* portSnapEpsilonMode;

    /// Flags for constrained Delaunay refinement.
    static const char* refine;

    /// Flags for constrained conforming Delaunay refinement.
    static const char* refineConforming;

    /// Show all ports.
    virtual void  enableAll();

    /// Hide all ports.
    virtual void disableAll();

    /// Entangle paths.
    virtual void entangle();
};

#endif

/// @}

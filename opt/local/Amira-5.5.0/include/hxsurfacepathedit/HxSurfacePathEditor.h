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
#ifndef HX_SURFACE_PATH_EDITOR_H
#define HX_SURFACE_PATH_EDITOR_H

#include <hxcore/HxEditor.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxsurfacepathedit/hxsurfacepatheditAPI.h>

class SurfacePathEditorGUIBase;

/** The actual visible editor in Amira. */
class HXSURFACEPATHEDIT_API HxSurfacePathEditor: public HxEditor
{
    HX_HEADER(HxSurfacePathEditor);

public:

    /// Constructor.
    HxSurfacePathEditor(void);

    /// Destructor.
    ~HxSurfacePathEditor(void);

    /// Editor types.
    enum {GENERIC_PATH_SET=0,VERTEX_PATH_SET};


    /// Update function.
    virtual void update();

    /// For tcl commands.
    int parse(Tcl_Interp* t, int argc, char **argv);

private:

    /// Handler, that initializes buttons and handles function-calls.
    SurfacePathEditorGUIBase* theHandler;

public:

    /// Returns port of this HxEditor.  The EditorHandlers need this
    /// method to initialize buttons.
    McDArray<HxPort*>& getPorts(void);

private:

    /// Initialize ports here.
    virtual void startEditing(HxData *data);

    /// Remove selection callbacks here.
    virtual void stopEditing();

    /// Pointer to the HxSurfacePathset, that is edited.
    HxData* data;

    /// Check if ports exist.
    bool thePortWidgetsCreated;

    /// Editor type (-1 = undefined, user is prompted, 0 = Generic, 1 = Vertex).
    int theEditorType;

    HxPortMultiMenu* portEditorTypes;

    HxPortButtonList* portStartEditor;

public:
    void init(void);
};

#endif

/// @}

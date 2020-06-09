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
#ifndef SURFACE_PATH_EDITOR_GUI_BASE_H
#define SURFACE_PATH_EDITOR_GUI_BASE_H

#include <hxsurfacepathedit/SurfacePathEditorViewerBase.h>

class HxSurfacePathEditor;
class HxSurfacePathSet;

void editorCallBack(void* editData);

/** Base class that provides and abstract definition for methods,
    defining the GUI (ports) for the @c HxSurfacePathEditor.
    The @c HxSurfacePathEditor forwards its methods to @c SurfacePathEditorGUIBase.

    If you need a new editor for @c HxSurfacePathSet derive from this class and
    implement all pure virtual methods.

    For an example on how to do this, see @c SurfaceVertexPathEditor.
*/

class HXSURFACEPATHEDIT_API SurfacePathEditorGUIBase: public SurfacePathEditorViewerBase
{
    MC_HEADER(SurfacePathEditorGUIBase);
public:

    /// Constructor.
    SurfacePathEditorGUIBase(HxSurfacePathSet* pathSet);

    /// Default Constructor.  Call setPathSet(HxSurfacePathSet*) after
    /// this constructor!
    SurfacePathEditorGUIBase();

    /// Initializes ports of HxEditor object.
    virtual void initButtons(HxSurfacePathEditor* edi) = 0;

    /// Check ports and set sensitivities.
    virtual void checkButtons() = 0;

    /// Update method.
    virtual void update() = 0;

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv) = 0;

    /// Destructor.
    virtual ~SurfacePathEditorGUIBase();

    /// Initializes the class.  This method is called by HxSurfacePathEditor.
    virtual void init(void) {}

};

#endif

/// @}

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
#ifndef SURFACE_VERTEX_PATH_EDITOR_H
#define SURFACE_VERTEX_PATH_EDITOR_H

#include <Inventor/events/SoKeyboardEvent.h>

#include <hxsurfacepathedit/SurfacePathEditorGUIBase.h>

class HxSurfacePathEditor;
class HxSurfacePathSet;
class PathConnector;
class FreeHandDrawer;
class HxPortToggleList;
class HxPortButtonList;
class HxPortMultiMenu;
class HxPortInfo;
class HxPortSeparator;
class HxPortIntSlider;
class HxPortRadioBox;

class SurfaceVertexPathEditor: public SurfacePathEditorGUIBase
{

    MC_HEADER(SurfaceVertexPathEditor);

public:

    /// Constructor.
    SurfaceVertexPathEditor(HxSurfacePathSet* pathSet);

    /// Default Constructor. Call setPathSet() after this constructor!
    SurfaceVertexPathEditor();

    /// Destructor.
    virtual ~SurfaceVertexPathEditor();

    /// Initializes ports of HxEditor object.
    virtual void initButtons(HxSurfacePathEditor* edi);

    /// Checks ports.
    virtual void checkButtons();

    /// Update method.
    virtual void update();

    /// Update editor data.
    virtual void updateData();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Create all available connectors and store them in mConnectors.
    virtual void init(void);

    /// Keyboard callback.  This function checks whether the event was
    /// triggered by pressing a certain key.
    virtual int keyCB(const SoEvent *event);

    /// Mouse pick callback.  This function checks whether the event
    /// was triggered by pressing a certain mouse button.
    virtual void mousePickCB(SoEventCallback* evCB);

    /// Passes @c set to the base class and initializes the member
    /// variable freeHandDrawer.
    virtual void setPathSet(HxSurfacePathSet*set);

    /// Returns true if @c ps is a pure vertex path set.
    virtual bool canEditPathSet(HxSurfacePathSet* ps)
    {
        bool ret= ps->isPureSurfaceVertexPath();
        if ( !ret )
            theMsg->printf("Cannot attach a SurfaceVertexPathEditor to this SurfacePathSet, "
                           "because it does not only contain vertex-nodes.");

        return ret;
    }

protected:

    /// Set type of control points.
    void setControlPointType(int type) { mControlPointType = type; }

    /// Set path node connector.
    void setConnector(PathConnector* c) { mConnector = c; }

    /// Name of list that defines connectors for the handler (in rc-file).
    McString mConnectorListVar;

    /// Pointer to path connector for use in mouse click callback.
    PathConnector* mConnector;

    /// Path connectors.
    McDArray< PathConnector* > mConnectors;

    /// Initialize connectors.
    void initConnectors();

    /// Path node type.
    int mControlPointType;

    /// Save the last pressed key.
    SoKeyboardEvent::Key m_keyPressed;

    /// Basic editing operations.
    enum { UNDO=0, REDO, DELETE_PATHS, DELETE_VERTEX };

    /// Path operations (1).
    enum { CLOSE_PATH=0, OPEN_PATH, REVERSE_PATH };

    /// Path operations (2).
    enum { MERGE_PATHS=0, SPLIT_PATH, ENTANGLE, UNTANGLE };

    /// Surface operations.
    enum { IMPORT_CONTOURS=0, PATCHIFY_SURFACE };

    /// GUI: advanced options.
    HxPortToggleList* portAdvancedOptions;

    /// GUI: basic editing-buttons.
    HxPortButtonList* portAction;

    /// GUI: path operations (1).
    HxPortButtonList* portPathOperations1;

    /// GUI: path operations (2).
    HxPortButtonList* portPathOperations2;

    /// GUI: surface operations.
    HxPortButtonList* portSurfaceOperations;

    /// GUI: path connectors.
    HxPortMultiMenu* portConnector;

    /// GUI: node type: vertex, edge, or triangle?
    HxPortRadioBox* portControlPointType;

    /// GUI: info port.
    HxPortInfo* portInfo;

    /// GUI: hit port, shows hit geometries.
    HxPortInfo* portHitGeom;

    /// GUI: seperates general ports from special ports.
    HxPortSeparator* portSep;

    /// GUI: allow selecting a certain surface path from the whole set.
    HxPortIntSlider* portPathSelect;

    /// GUI: allow selecting a certain control point from the selected
    /// surface path.
    HxPortIntSlider* portCPSelect;

    /// GUI: select/deselect all path from a surface path set.
    HxPortButtonList* portPathSelectAll;

    /// Returns true if user wants to perform operation only on
    /// selected paths, false otherwise.
    bool askForSelection();

    /// Carries out delete operations.  Deletes single control points
    /// or whole paths.
    void deleteOperations(void);

    /// Enable of disable free hand drawing.
    void setFreeHandDraw(bool fhd);

    /// Show all ports.
    virtual void  enableAll();

    /// Hide all ports.
    virtual void disableAll();

    /// Store pointer to free hand drawer.
    FreeHandDrawer* freeHandDrawer;

    /// Store whether free hand drawing is enabled or disabled.
    bool dragActive;

    /// GUI: refine-buttons.
    HxPortButtonList* portFreeHandDraw;

    /// Keeps track of the previous value of portFreeHandDraw.
    bool freeHandDrawValue;

    /// Entangle paths.
    virtual void entangle();
};

#endif

/// @}

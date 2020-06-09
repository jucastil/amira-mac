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

/// @addtogroup hxcore hxcore
/// @{
#ifndef HX_VIEWERTOOL_H
#define HX_VIEWERTOOL_H

#include <hxcore/HxViewer.h>
#include <Inventor/events/SoEvents.h>

class QAction;
class QCursor;

/** Base class for tools which can be added into a viewer panel.
    AmiraDev developers without a Qt license may create their own
    tools and add them into a tool bar in a viewer panel by calling
    HxViewerPanelBase::registerTool(). If Qt is installed the
    QAction provided by the tool may also be added to other menus
    or custom buttons. */
class HXCORE_API HxViewerTool : public McHandable
{   
    
  public:

    /// keyboard modifiers
    enum ModifierKeys {
        NO_MODIFIER      = 0,
        SHIFT_MODIFIER   = 1 << 1,
        CONTROL_MODIFIER = 1 << 2,
        ALT_MODIFIER     = 1 << 3
    };

    /** Checks if the tool supports the specified viewer or not.
        This method is called for all tool registered with a viewer
        panel each time the active viewer of the panel changes.
        Tool buttons associated with tool not supporting the new
        active viewer will be automatically disabled (greyed out). */
    virtual bool supportsViewer(HxViewerBase* baseViewer);

    /** Returns an action pointer. The QAction object allows the
        tool to be easily added in tool bars or menus. */
    QAction* action();

    /** Reads an icon file and sets the tool icon. Returns true on
        success, false on error. */
    bool setIconFile(const char* filename);

    /// Sets the tool's keyboard short cut (e.g. "Ctrl+X")
    void setShortcut(const char* shortcut);

    /// Returns the tools keyboard shortcut.
    McString shortcut() const;

    /// Sets the tools tool tip text.
    void setToolTip(const char* toolTip);

    /// Returns the tools tool tip text.
    McString toolTip() const;
    
    /// Sets the text to be displayed when the tool is added to a menu.
    void setText(const char* text);

    /// Returns the tool's descriptive text set via setText().
    McString text() const;

    /** This method is called whenever the active viewer of a viewer
        panel the tool is registered with changes. Tools may overload
        this method in order to update their user interface, e.g.
        tool button or action state. The default implementation calls
        updateUI(). */
    virtual void onActiveViewerChanged(HxViewerBase* newActiveViewer,
        HxViewerBase* oldActiveViewer);

    /** This method might be called in order to update the GUI of
        the tool. The method is called for example if a viewer is
        registered, shown, or hidden in a viewer panel. */
    virtual void updateUI(HxViewerBase* activeViewer);

  protected:
    /// Constructor.
    HxViewerTool(const char* text, const char* iconFilename=0);
    virtual ~HxViewerTool();

    class HxViewerToolPrivate* d;
    friend class HxViewerPanelBase;
};

/** Base class for trigger or toggle tools. */
class HXCORE_API HxViewerTriggerTool : public HxViewerTool
{
  public:
    HxViewerTriggerTool(const char* text, const char* iconFilename=0);

    void setChecked(bool value);
    virtual void onSetChecked(HxViewerBase* viewer, bool value);

    void trigger();
    virtual void onTrigger(HxViewerBase* viewer, int modifiers);

    void setCheckable(bool value);
    bool isCheckable() const;
};

/** Base class for modal viewer tools. A modal tool is a tool which
    interpretes all mouse events in a viewer while it is active.
    In addition to the active modal tool there can be other tools
    organized in a stack which interprete events not handled by
    modal tools with higher priority. Usually the active modal tool
    reacts on left mouse button events, while other tools might
    react on other keys or mouse buttons.
    
    Modal tools will always be represented by checkable tool buttons
    in a tool bar. */
class HXCORE_API HxViewerModalTool : public HxViewerTool
{
  public:
    /// Constructor.
    HxViewerModalTool(const char* text, const char* iconFilename=0);

    /** Event processing routine. Derived tools need to implement
        this method and implement the desired interaction behaviour.
        If an event was not handled by a tool the method should
        return false. In this case other tools might be asked to
        process the event. */
    virtual bool processEvent(const SoEvent* e, HxViewer* viewer);

    /** Returns the tool's cursor. The cursor is set automatically
        when the tool is activated. If 0 is returned the cursor will
        be set by the respective HxViewer. The default implementation
        returns the cursor set using setCursor(). */
    virtual QCursor* cursor() const;

    /** Sets the tool's cursor. The default cursor will be an arrow
        shape cursor. The method may have no effect for tools which
        which reimplement the cursor() method. */
    void setCursor(const QCursor& cursor);

    /** Sets flag if tool should be activated by default in all
        supported viewers of a viewer panel, or only in the active
        viewer. This property is evaluated when a tool is activated
        via the tool buttons in the viewer panel. A tool may still be
        explicitely activated in one viewer only by calling
        HxViewerBase::activateTool() or in all supported viewers by
        calling HxViewerPanelBase::activateTool(). */
    void setActivateAllEnabled(bool value);

    /** Returns true if the tool should be activated by default in
        all supported viewers of a viewer panel. The default value
        is true. */
    bool activateAllEnabled() const;

    /** Returns true if the tool is a navigation or viewing tool.
        With the ESC key it is possible to switch between the last
        navigation or viewing tool and the last interaction tool.
        The default implementation returns false. */
    virtual bool isNavigationTool() const;

    /** This method sets a flag which indicates if a reference to the
        tool should be kept when deactivating the tool. If this is the
        case the tool can be activated again using the ESC key. The
        default value is true. */
    void setRememberAsLastToolEnabled(bool value);

    /** Returns true if it is OK to remember the tool as last tool
        when deactivating it. */
    bool rememberAsLastToolEnabled() const;

  protected:
    /// Destructor.
    virtual ~HxViewerModalTool();

    /** This method is called when the tool becomes the active tool
        in a viewer. The default implementation does nothing. */
    virtual void onActivate(HxViewerBase*, HxViewerModalTool* previousActiveTool);

    /** Alternative onActivate() method. This method is called by the
        default implementation of the onActivate() method described
        above. The previous active tool is simply omitted. */
    virtual void onActivate(HxViewerBase*);

    /** This method is called when the tool is removed from the
        top of the tool stack of a viewer. */
    virtual void onDeactivate(HxViewerBase*);

    /*  For internal use only. Called in HxViewerBase::activateTool(). Sets
        the master tool button to checked if there is a master tool, i.e., if
        the tool has been registered using HxViewerPanelBase::overwriteTool(). */
    void setChecked(bool value);

    // void grabEvents();
    // void releaseEvents();

    // const SoPickedPoint& getPickedPoint() const;
    // const SoPickedPointList& getPickedPointList() const;
    // bool sendToSceneGraph(SoEvent* e); // runHandleEventAction(), callHandleEventAction(), applyHandleEventAction()

  friend class HxViewerBase;
};

/*

- Default tools for rotate, zoom, pan?
- Default tool for interaction?
- Picking with SoEventCallback?

Status quo:
Viewer Mode: Interaction OR Viewing
- Interaction: Send events to scene graph -> SoHandleEventAction, SoHandleEventCallback, getPickedPoint(), SoRayPickAction
- Viewing: Rotate, Zoom, Pan, Seek

New requirements:
- Lasso Tool, MPR Rotate Tool, Volpick Tool (used in Neuron Editor to add a point)
- Pick Tools (Pick + Operation, e.g. Select, Delete, Bisect Edge, ...)
- Brush Tool, Nudge Tool, Blow Tool

- Shape Tools: Ideally shape tools should ALWAYS be pickable
  Examples: Overlay measure shapes, crosshair, special draggers, ...

Standard Tools:
HX_INTERACTION_TOOL
HX_3D_ROTATE_TOOL
HX_3D_ZOOM_TOOL
HX_3D_PAN_TOOL
HX_3D_SEEK_TOOL

*/

#endif


/// @}

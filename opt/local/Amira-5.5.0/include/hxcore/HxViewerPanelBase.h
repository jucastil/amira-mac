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
#ifndef HX_VIEWER_PANEL_BASE_H
#define HX_VIEWER_PANEL_BASE_H

#include <hxcore/HxAmiraWinDLLApi.h>
#include <hxcore/HxViewerTool.h>
#include <mclib/McHandle.h>

/** Base class of a viewer panel. This class is used as a base class
    of QxViewerPanel. It contains functionality not depending on Qt
    and thus allows AmiraDev developers without a Qt license to
    customize a viewer panel. In particular, tools can be added as
    tool buttons, or toolbars can be enabled or disabled.
*/

class HxViewerBase;
class QMainWindow;
class QAction;
class QToolBar;

class HXCORE_API HxViewerPanelPrivate
{
public:
    struct ToolInfo {
        QToolBar* toolBar;
        McHandle<HxViewerTool> tool;
        int toolIndex;
    };

    QMainWindow* mMainWindow;
    McDArray<ToolInfo*> mTools;
    McDArray<QToolBar*> mToolBars;
    McHandle<HxViewerModalTool> mDefaultTool;

    bool verticalSplit;
    bool selectionVisible;

    int nViewers; // desired number of viewers in current layout
    McDArray<HxViewerBase*> viewers;
    McDArray<int> viewerIds;

    HxViewerBase* activeViewer;

    QToolBar* toolBar(const char* name);
};

class HXCORE_API HxViewerPanelBase
{
public:
    /** Returns all viewers registered with this panel.
        TODO: replace this method by numViewers()/viewer(). */
    McDArray<HxViewerBase*>& getViewers() const;

    /** Sets the active viewer of the panel. */
    virtual void setActiveViewer(HxViewerBase* newActiveViewer) = 0;

    /** Returns the active viewer of the panel. */
    HxViewerBase* getActiveViewer();

    /** Registers a tool with the viewer panel. If toolBarTitle is set
        a tool button for the tool will be created in the tool bar with
        that title. If no such tool bar exists a new one will be created.
        If insertBeforeTool is set the tool button will be inserted before
        the tool button of the insertBeforeTool tool within the specified toolbar. 
        If insertBeforeTool is not set the tool button will be appended to the list 
        of existing tool buttons. 

        Once a tool is registered the tool's virtual method
        HxViewerTool::supportsViewer() is called whenever the active
        viewer of the panel changes. If a tool does not support the
        active viewer the tool action (and thus also the corresponding
        tool button) will be disabled. Otherwise it will be enabled. */
    virtual void registerTool(HxViewerTool* tool, const char* toolBarTitle=0, const char* insertToolBefore=0) = 0;

    /** Unregisters a tool. The specified tool will be released. If a
        tool button was created for the tool, the button will be removed
        again. */
    virtual void unregisterTool(HxViewerTool* tool) = 0;

    /** Convenience function in order to reset the 'last active tools
        cache' of all viewers, whereas those last active tool references
        will be set to zero where the specified tool \c tool matches.

        @see HxViewerBase::lastActiveTool()
        @see HxViewerBase::lastInteractionTool()
        @see HxViewerBase::lastNavigationTool()

        @param tool Tool which should be removed from 'last tools' references.
    */
    void removeFromLastActiveTools(HxViewerModalTool* tool);

    /** Activates the specified modal tool in all supported viewer
        of this panel. The tool's virtual method onActivate() will
        be called once for each viewer the tool is activated in. */
    void activateTool(HxViewerModalTool* tool);

    /** Overwrites an existing tool for a particular viewer. This method
        makes it possible to share the same tool button between different
        tools operating in different viewers. Assume an existing tool does
        not support a particular viewer. Instead you want to provide a new
        tool which should be used instead of the existing tool if that
        particular viewer is the active viewer. Then you need to call this
        method instead of registerTool(). */
    virtual void overwriteTool(HxViewerTool* existingTool, HxViewerTool* newTool,
        HxViewerBase* viewer);

    /** Returns the tool which should be actually used in a given viewer
        instead of the specified tool. If no overwrite tool has been set
        the tool itself will be returned. */
    HxViewerTool* toolForViewer(HxViewerTool* tool, HxViewerBase* viewer);

    /// Returns the number of tools registered with the viewer panel.
    unsigned int numTools() const;

    /// Returns the tool with the given index.
    HxViewerTool* getTool(unsigned int toolIdx) const;

    /** Searches for a tool with the given text. If toolBarTitle is
        specified, the tool must be in a tool bar with that title.
        Otherwise it can be in any tool bar or in no tool bar at all.
        Returns 0 if no such tool is found. */
    HxViewerTool* findTool(const char* text, const char* toolBarTitle=0) const;

    /** Returns the number of tool bars of the viewer panel. Only tool
        bars created and managed by the panel itself are counted. Tool
        bars created by yourself and added to the panel using standard
        Qt methods are not reported. */
    unsigned int numToolBars() const;

    /// Returns the tool bar with the given index.
    QToolBar* getToolBar(unsigned int toolBarIdx) const;

    /// Returns the title of the tool bar with the given index.
    McString getToolBarTitle(unsigned int toolBarIdx) const;

    /// Removes and deletes the tool bar with the given index.
    void removeToolBar(unsigned int toolBarIdx);

    /// Shows or hides the tool bar with the given index.
    void setToolBarVisible(unsigned int toolBarIdx, bool value);

    /// Returns true if the tool bar with the given index is visible.
    bool isToolBarVisible(unsigned int toolBarIdx) const;

    /** Returns the index of the tool bar with the given title, or -1
        if no such tool bar could be found. */
    int findToolBar(const char* toolBarTitle) const;

    virtual void updateToolBars(HxViewerBase* oldActiveViewer) = 0;

protected:
    HxViewerPanelBase();
    virtual ~HxViewerPanelBase();

    HxViewerPanelPrivate* d;
};

#endif

/// @}

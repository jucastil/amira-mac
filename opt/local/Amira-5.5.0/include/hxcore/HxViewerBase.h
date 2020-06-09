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
#ifndef HX_VIEWERBASE_H
#define HX_VIEWERBASE_H

#include <mclib/McString.h>
#include <mclib/McHandable.h>
#include <hxcore/HxAmiraWinDLLApi.h>

class QWidget;
class QToolBar;
class QxViewerPanel;
class HxViewerTool;
class HxViewerModalTool;
class HxViewerPanelBase;

/** Base class of a viewer which can be inserted into a viewer panel.
    A viewer panel, see QxViewerPanel, is a container widget which
    show one or more viewers together with a set of toolbars. Usually
    a viewer panel contains standard 3D viewers of type HxViewer.
    However, in some cases also other types of viewers might be needed.
    For example, the segmentation editor creates its own 2D MPR viewers
    for editing ROIs in image data sets. HxViewerBase serves as a common
    base class for all such viewers.
*/
class HXCORE_API HxViewerBase : public McHandable
{
public:
    /** Returns the Id of the viewer as specified in the constructor.
        The Id of the Amira main viewer is 0. The Id is used to access
        a viewer via the Tcl command <tt>viewer id</tt> or by calling
        theController->viewer(id). Currently the Id is only interpreted
        for viewers of type HxViewer. */
    int viewerId() const;

    virtual QWidget* getWidget () const { return 0; }
    virtual void show(bool raise = true);
    virtual void hide();
    virtual int isVisible();
   
    virtual bool setFullScreen(const bool enable) { return false; }
    virtual bool isFullScreen() const { return false; }

    virtual void render() { }
    virtual void snapshot(const char* filename=0);

    virtual void setPanel(QxViewerPanel* panel);
    virtual QxViewerPanel* getPanel() const;
    HxViewerPanelBase* getPanelBase() const;

    /** Returns the active modal tool in this viewer, or 0 if no
        active modal tool has been set. */
    HxViewerModalTool* activeTool() const;
    
    /** Returns the modal tool which was active in this viewer
        before the current active tool was activated. */
    HxViewerModalTool* lastActiveTool() const;

    /** Returns the navigation tool which was active in this viewer
        the last time before an interaction tool was activated. This tool
        is activated if the current tool is an interaction tool and the
        ESC key is pressed. */
    HxViewerModalTool* lastNavigationTool() const;

    /** Returns the interaction tool which was active in this viewer
        the last time before a navigation tool was activated. This tool
        is activated if the current tool is a navigation tool and the
        ESC key is pressed. */
    HxViewerModalTool* lastInteractionTool() const;

    /** Activates the specified modal tool in this viewer. If a
        tool is activated onDeactivate() will be called for the
        previous active tool and onActivate() will be called for
        the new active tool. Use HxViewerPanelBase::activateTool()
        in order to activate a tool in all supported viewers of
        a panel. */
    void activateTool(HxViewerModalTool* tool);

    /** Removes all references to the specified tool. The method checks
        if the specified tool is the last navigation tool or the last
        interaction tool. If so, those references are set to zero. Then
        it is no longer possible to activate the tool using the ESC key. */
    void removeFromLastActiveTools(HxViewerModalTool* tool);

    /**
     * To get the list of disabled tools for this viewer.
     * Internal use only.
     */
    const McDArray<HxViewerTool*>& getDisabledTools() const;

    /**
     * To enable/disable a tool for this viewer.
     * Internal use only.
     */
    void setToolEnabled(HxViewerTool* tool, bool enable);

    /**
     * To enable/disable all tools for this viewer.
     * Internal use only.
     */
    void setAllToolsEnabled(bool enable);

    //void pushTool(HxViewerTool* tool, HxViewerBase* viewer);
    //void popTool(HxViewerTool* tool, HxViewerBase* viewer);
    //const McDArray<HxViewerTool*>& getToolStack() const;

protected:
    /** Constructor. The viewer Id is currently only used for 
        standard 3D viewers of type HxViewer. */
    HxViewerBase(int id=0);
    
    /// Destructor.
    virtual ~HxViewerBase();

private:
    struct HxViewerBasePrivate* d;
    int viewerNum;
    QxViewerPanel* mViewerPanel;
};

#endif

/// @}

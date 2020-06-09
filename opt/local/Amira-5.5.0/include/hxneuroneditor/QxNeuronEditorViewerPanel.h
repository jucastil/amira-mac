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

/// @addtogroup hxneuroneditor hxneuroneditor
/// @{
#ifndef QX_NEURONEDITOR_VIEWER_PANEL_H
#define QX_NEURONEDITOR_VIEWER_PANEL_H

#include <hxcore/QxViewerPanel.h>

#include "hxneuroneditorAPI.h"


class HXNEURONEDITOR_API QxNeuronEditorViewerPanel : public QxViewerPanel
{
    Q_OBJECT

public:
    QxNeuronEditorViewerPanel(QWidget* parent, DecorationType decorationType);

    void registerViewer(HxViewerBase* viewer, int update = 1);

    /// Register the Toggle-Viewer to the panel and add a button to the "Layout" toolbar
    /// that toggles the visibility of the viewer.
    void registerToggleViewer(HxViewerBase* viewer, int update = 1);

    void reconfigure();
    void reconfigureToggleViewer();

    void setLayout(Layout layout);
    QxViewerPanel::Layout getLayout() const;

    int getNumVisibleViewers() const;

    /// Update the activation of tools contained in toolbars depending
    /// on the current viewer and the corresponding action of the
    /// current layout will be checked.
    void updateToolBars(HxViewerBase* oldActiveViewer);

    /// Find all registered tools from one toolbar named \a toolBarTitle.
    McDArray<HxViewerTool*> getToolsFromToolBar(const char* toolBarTitle) const;

public slots:
    /// Triggered if a tool button contained by the layout toolbar has
    /// been clicked in order to switch the layout.
    void changeLayout(QAction*);
    /// Triggered if the active viewer has been changed in order to
    /// highlight the active viewer.
    void highlightActiveViewer(int);

    /// Triggered if a splitter between the viewers has moved in order to
    /// update the layout respectively the visibility state of the Toggle-Viewer
    /// if a viewer was hidden in this way.
    void updateLayout(int, int);
    void updateToggleLayout(int, int);

protected:
    ~QxNeuronEditorViewerPanel();

private:
    /// Find all visible viewers, active viewer in priority.
    /// Note: In the case the Toggle-Viewer is visible it does not number
    /// among the returned visible viewers.
    McDArray<HxViewerBase*> getVisibleViewers();

    /// Adjust the number of visible viewers to \a numVisibleViewers.
    void updateVisibleViewers(const int numVisibleViewers);

    /// Shows the \a viewer if \a show is set. Otherwise, hides the \a viewer.
    void showViewer(HxViewerBase* viewer, bool show = true);

    /// Swaps the current active viewer if it is not the Toggle-Viewer.
    void switchActiveViewer();

    /// Swaps the current visible viewer of the layout (MPR-Viewer or 3D-Viewer).
    void switchLayoutViewer();

    /// Switches between the MPR-Viewer and the 3D-Viewer if only one viewer is shown.
    void changeViewerInSingleLayoutMode();

    QxViewerPanel::Layout mCurrentLayout;

    /// Reference to the registered Toggle-Viewer.
    /// Note: The viewer is not affected by ordinary layout changes. Its visibility can only
    /// change via button in the "Layout" toolbar or through splitter movements.
    HxViewerBase* mToggleViewer;

    /// Action for toggling the visibility of the Toggle-Viewer.
    QAction* mToggleViewerAction;
};

#endif

/// @}

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
#ifndef QX_VIEWER_PANEL_H
#define QX_VIEWER_PANEL_H

#include <QMainWindow>
#include <mclib/McDArray.h>
#include <mclib/McHandle.h>
#include "HxViewerBase.h"
#include "HxViewerPanelBase.h"
#include "HxAmiraWinDLLApi.h"
#include "HxViewerTool.h"

class HxViewer;
class HxViewerBase;
class QAction;
class QxMultiToolButton;


/** Container widget for viewers derived from HxViewerBase. This class
    contains up to four viewers which can be displayed in different layouts.
    It also provides one or more toolbars which provide viewer tools such
    as navigation, measurement, snapshot tools, or buttons to change the
    viewer layout.

    The main viewer panel is accessible via the global macro thePanel.
    This panel contains the four viewers with the ids 0, 1, 2, and 3.
    Additional viewers are usually created in separate viewer panels.
    Other components like the Amira segmentation editor or the Amira neuron
    editor use their own viewer panel objects filled a standard viewer
    of type HxViewer plus additional custom viewers.

    Tools and toolbars can be registered, accessed, changed by AmiraDev
    developers without using Qt via the HxViewerPanelBase base class.
*/
class HXCORE_API QxViewerPanel : public QMainWindow, public HxViewerPanelBase
{
    Q_OBJECT

  public:
    /// Enumeration type used in setLayout().
    enum Layout {
        /// Hides all viewers.
        NO_VIEWER,
        /// Shows the active viewer only.
        SINGLE_VIEWER,
        /// Shows two viewers side-by-side.
        TWO_VIEWERS_HORIZONTAL,
        /// Shows two viewers on top of each other.
        TWO_VIEWERS_VERTICAL,
        /// Shows four viewers in a 2x2 layout.
        FOUR_VIEWERS,
        /// Shows three viewers.
        THREE_VIEWERS
    };

    enum DecorationType {
        DECO_NONE = 0,
        DECO_TOOL_BUTTONS = 1,
        DECO_LAYOUT_BUTTONS = 1 << 1,
        DECO_FULLSCREEN_BUTTON = 1 << 2,
        DECO_LAYOUT_FOUR_VIEWERS = 1 << 3,
        DECO_ALL_BUTTONS = 0xff
    };

    /** Constructor. */
    QxViewerPanel(QWidget* parent, DecorationType decorationType);

    /** Recomputes the size and position of the child viewers. */
    void reconfigure();

    /** Changes the viewer layout. Internally, viewers are sorted alphabetically
        according to their Qt widget's object name. If only a subset of viewers
        should be shown, first the active viewer is selected. The remaining viewers
        are taken from the top of the sorted viewer list. */
    void setLayout(Layout layout);

    /** Returns the current viewer layout. */
    Layout getLayout() const;

    ///
    void setVerticalSplit(bool value);

    ///
    bool isVerticalSplit() const;

    ///
    void registerViewer(HxViewerBase* viewer, int update=1);

    ///
    void unregisterViewer(HxViewerBase* viewer);

    ///
    int updateViewerIds();

    /** Returns the active viewer or the first visible viewer if there is
        no active viewer. Tools like reset orientation or view all are
        usually applied to this viewer.
        \seealso HxViewerPanelBase::getActiveViewer() */
    HxViewer* getDefaultViewer();

    /// Set the first visible viewer as active
    void setDefaultViewer();

    void setActiveViewer(HxViewerBase* newActiveViewer);

    ///
    int getNumViewers() const;

    ///
    int getNumVisibleViewers() const;

    /** Checks if the given viewer is visible to the viewer panel. The method
        returns true even if the viewer is visible to the panel, but the
        panel itself is hidden. Viewers in fullscreen mode are also handled
        correctly. */
    bool isViewerVisible(HxViewerBase* viewer);

    ///
    void checkRemoteMode();

    /** Creates a screen snapshot of the whole viewer panel. */
    void snapshotPanel(QImage& image);

    /** Enables the seismic orientation toolbar. If this flag is set
        before a viewer panel is created, 6 orientation buttons are created
        instead of 3. Also, these buttons are called "View From Above",
        "View From Below", "View From West", "View From East", "View From
        South" and "View From North", while the 3 standard orientation buttons
        are called "View XY", "View XZ", and "View YZ". */
    static bool seismicToolbarEnabled;
    
    /** Returns the viewer IDs of the standard viewers contained in
        the panel. Only viewers of type HxViewer are considered. */
    const McDArray<int>& getViewerIds() const;

    // Methods overloaded from HxViewerPanelBase:
    void registerTool(HxViewerTool* tool, const char* toolBarTitle=0, const char* insertBeforeTool=0);
    void unregisterTool(HxViewerTool* tool);

    /**
     * To retrieve the list of registered tools.
     * Internal use only.
     */
    McDArray<HxViewerTool*> getAllTools() const;

    /** Cycles through available viewers. The currently active viewer
        is hidden, and the next viewer is shown and made active instead.
        The method is called if the "Single Viewer" layout button is
        pressed multiple times in a row. */
    void cycleViewers();

    /** For internal use only. Returns the fullscreen button contained
        in the layout menu. The state off this button is set or unset
        if fullscreen mode is enabled or disabled inside the method
        QxViewer::setFullScreen(). */
    QAction* getFullScreenAction() const;

    //hide extra toolbar
    void hideExtraToolBar();

    void openStereoDialog();

    /**
     * Internal use only.
     */
    void updateToolBars(HxViewerBase* oldActiveViewer);

    
    /** Snapshot method with more arguments. If @c numTilesX or
        @c numTilesY is bigger than one, tiled rendering is used.
        If @c offscreenWidth and @c offscreenHeight are bigger than
        0, offscreen rendering is used. If @c filename is null, the
        snapshot dialog is popped up and all parameters can be
        overwritten by the user. */
   void snapshot( const char * filename, int numTilesX, int numTilesY, float nrSamples = 1.0f,
                   int offscreenWidth=0, int offscreenHeight=0, bool alpha = false);

  public slots:
    void snapshot(const char* filename=0);
    void setFullScreen();
    void modalToolTriggered(bool checked);
    void triggerToolTriggered(bool checked);
    void slotViewingModeActivated(bool);
    void layoutChanged(QAction*);

signals:
    void activeViewerChanged(int newViewerID);

  protected:
    ~QxViewerPanel();

    virtual void showEvent(QShowEvent*);
    virtual void closeEvent(QCloseEvent *);

    void createViewingToolBar();
    void createOrientationToolBar();
    void createExtraToolBar();
    void createLayoutToolBar();

    class QxSeismicToolBar* mSeismicToolBar;

private:
    Layout         mCurrentLayout;
    DecorationType mDecorationType;

    QAction* wMeasureAction;
    QxMultiToolButton* wMeasureBtn;
    QAction* wLayout1Action;
    QAction* wLayout2VAction;
    QAction* wLayout2HAction;
    QAction* wLayout4Action;
    QAction* wFullScreenAction;

    McHandle<HxViewerModalTool> mInteractTool;
    McHandle<HxViewerModalTool> mTrackballTool;
    McHandle<HxViewerModalTool> mTranslateTool;
    McHandle<HxViewerModalTool> mZoomTool;

  public:
    static QxViewerPanel*& getThePanel();
    static bool sBlockNavigationTools;
    unsigned int reconfigureLock:8;

    friend class QxViewer;
    friend class HxViewerPanelBase;
};

#define thePanel QxViewerPanel::getThePanel()

#endif

/// @}

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

/// @addtogroup hxsegeditor hxsegeditor
/// @{
#ifndef GIQ_H
#define GIQ_H

#include <qobject.h>
#include <qpixmap.h>
#include <QGridLayout>
#include <QFrame>

#ifdef COMPILE_VISAGE
#include <vsvolren/VsData.h>
#endif

#include "Gi.h"
#include <hxcolor/HxColormap.h>
#include <hxcore/QxViewerPanel.h>
#include <mclib/McDArray.h>

class QCursor;
class QSplitter;
class QMenuBar;
class QMenu;
class GiQStatDialog;
class QGridLayout;
class GiQToolbox;
class QFrame;
class HxGiEditor;
class Gi3DDialog;
class Gi3DViewerBarBase;
class GiSetOrientationTool;
class GiResetOrientationTool;
class HxLattice;
class HxViewerBase;
class HxRegScalarField3;
class HxPreferences;

/// Motif version of general image editor.
class HXSEGEDITOR_API GiQ : public QObject, public Gi
{
    Q_OBJECT

  public:
    /** Constructor. This constructor is called if the segmentation
        editor should be integrated into the Amira main window. This
        is the standard case in Amira. */
    GiQ(HxGiEditor* editor);
    bool isStandardEditor() const { return mMode==GI_EDITOR; }

    /** Alternative constructor. This constructor is called if the
        segmentation editor should be placed in a separate widget.
        This widget will be created as a child of the specified
        parent widget. Menus will be added to the specified menu
        bar. The segmentation editor widget can be obtained via
        getWidget(). */
    GiQ(HxGiEditor* editor, QWidget* parent, QMenuBar* menuBar);
    bool isStandAlone() const { return mMode==GI_STANDALONE; }

    GiQ(HxGiEditor* editor, QWidget*& wGuiParent, QWidget*& wViewerParent);
    bool isSubApplication() const { return mMode==GI_SUBAPPLICATION; }

    /** Destructor. Deletes widgets and frees resources. The
        destructor is called from ~HxGiEditor(). */
    ~GiQ();

    void clear();

    /** Returns the segmentation editor's toolbox. The toolbox holds
        the GUI controls for all tools as well as the tissue list,
        see GiQTissueList. */
    GiQToolbox* getToolbox() const;

    /** Returns the widget containing the segmentation editor. This
        method returns 0 if the editor was integrated into the
        Amira main window and the main viewer panel widget. Only
        if the editor was explicitely created as child of a specific
        child widget, a non-zero pointer will be returned. */
    QWidget* getWidget() const;

    /** Returns the viewer panel containing the editor's viewers.
        The viewer panel may either be the Amira viewer panel (if
        the editor is intergrated into the amira main window), or a
        separate panel (if the viewer is created in its own widget). */
    QxViewerPanel* getPanel() const { return mPanel; }

    virtual void setVolume(const mculong* dims, McTypedPointer data, HxLabelLattice3* result);

    /** Set mouse cursor (get it from current tool) */
    virtual void updateCursor();

    int statusLine;

    virtual void redraw();

    virtual void updateUndoSensitivity();
    HxGiEditor* getEditor() { return editor; }

    /** Called when the slice number has changed. This method is
        called from Gi::setSlice() when the slice number has changed.
        The method updates the cross-hair position and redraws all
        viewers. It also updates the 3D wireframe display. */
    virtual void sliceNumberChanged(GiViewer* viewer);

    virtual void touchData(int selChanged, int lblchanged,
                           int orientation, int slice,
                           int automatic, int cleared);

    /// Overloaded method, also sets toggle its checkbox.
    virtual void set3dMode(bool onOff);

    /// Overloaded method, also sets toggle its checkbox.
    virtual void setZoomMode(bool onOff);

    /** This method initializes the range slider limits and the range
        slider histogram plus the range slider min max spin boxes.

        Returns an initial data window with rmin rmax.
    */
    void initRangeSliders(HxData*, float &rmin, float &rmax);

#ifdef COMPILE_VISAGE
    void initRangeSlider(VsData* data);
#endif

    // Sets colormap to be applied in 2D viewers, use 0 for standard gray ramp
    void setColormap(HxColormap* colormap);

    // Returns current 2D colormap or 0 if standard gray ramp is used
    HxColormap* getColormap() const;

    /// Enable and disable the segmentation menus
    void setMenuEnabled(bool onOff);

    /// Enable and disable menus and sub menus recursively, needed to switch on/off shortcuts as well
    void disableSubmenusRecursively(QMenu* pMenu, bool onOff);

    void updateMaterialVisibility();

    /// Initialize thing before attaching to a data set.
    void preInit(float vmin, float vmax, const McHistogram& histo);

    void preInitShowOnly();

    void setImageDataSet(HxData* data);

    virtual void setMaskingEnabled(bool value);
    virtual void setMaskingOverlay(bool value);

    virtual bool maskingEnabled() const;

    Gi3DDialog* get3DDialog() const { return dialog3d; }

    // Adds the "Segmentation" and "Selection" menus to the main menu bar
    void addMenu();

    // Removes the "Segmentation" and "Selection" menus from the main menu bar
    void removeMenu();

    // Selects a tool and updates the user interface
    virtual void setTool(int which);

    virtual bool getPickedVoxel(HxViewer* viewer, int x, int y, McVec3i& voxel, float& intensity);

    // Set a marker at intensity and delete previous one if existing
    void setToolDataWindowMarker(float intensity);

    // Remove marker if existing
    void clearToolDataWindowMarker();

    // Set tool data window
    void setToolDataWindow(float min, float max, bool redraw=true);

    // Get tool data window
    void getToolDataWindow(float& min, float& max);

    // Set tool data window slider tracking mode
    // If tracking is enabled (mode==true) the slider emits dataWindowChanged signals
    // while dragging and not only on mouse release
    void setToolDataWindowSliderTracking(bool mode);

    // check tracking mode of tool data window slider
    bool toolDataWindowSliderTracking();

    // Return the index of the first slice with a selection
    int firstSliceWithSelection (int currentSlice, int orientation);

    // Return the index of the previous slice with a selection
    int prevSliceWithSelection (int currentSlice, int orientation);

    // Return the index of the next slice with a selection
    int nextSliceWithSelection (int currentSlice, int orientation);

    // Return the index of the last slice with a selection
    int lastSliceWithSelection (int currentSlice, int orientation);

    /** Emits signal hiddenSelectionDetected(direction)
        where direction indicates whether a selection is
        located in front and/or behind of the current slice:
        -1 (in front - previous), 0 (both), 1 (behind - next). */
    void checkForHiddenSelection (void);

  signals:
    /** This signal is emitted after a material has been renamed.
        When the signal is emitted the name has already been updated
        in the material bundle of the label field being edited. */
    void materialRenamed(HxData* labelData, const char* oldName, const char* newName);

    /** This signal is emitted after a new material has been added. */
    void materialAdded(HxData* labelData);

    /** This signal is emitted after a material has been removed.
        When the method is called labels already have been renumbered
        and the material has been removed from the parameter bundle.
        iMaterial is the index of the removed material and name is
        its name. */
    void materialRemoved(HxData* labelData, int iMaterial, const char* matName);

    /** This signal is emitted after the color of a material has been
        changed. iMaterial is the index of the material with a new
        color. */
    void colorChanged(HxData* labelData, int iMaterial);

    /** This signal is emitted when the labels have been modified.
        The signal is not emitted when only the selection is changed. */
    void labelsChanged(HxData* labelData);

    /** This signal is emitted when the selection has changed. */
    void selectionChanged();

    /** This signal is emitted when a selection is not visible within a viewer.
        direction can be negative (previous slices), positive (next slices),
        or zreo (both directions. */
    void hiddenSelectionDetected(int direction);

  protected:
    HxGiEditor*         editor;
    QMenuBar*           mMenuBar;
    QSplitter*          mSplitter;

    enum Mode {
        GI_EDITOR,
        GI_STANDALONE,
        GI_SUBAPPLICATION
    };

    Mode mMode;

    QCursor* actCursor;
    QMenu* segmentationMenu;
    QMenu* orientationPopup;
    QMenu* activePopup;
    QMenu* greyImagePopup;
    QMenu* gradientImagePopup;
    QMenu* selectionMenu;
    QMenu* drawStylePopup;
    GiQStatDialog* statDialog;
    GiQToolbox* toolbox;
    Gi3DDialog* dialog3d;
    Gi3DViewerBarBase* vb3d;
    GiSetOrientationTool* mSetOrientation[3];
    GiResetOrientationTool* mResetOrientation;
    bool inNewLabelDataSA;
    McHandle<HxColormap> mColormap;

    void updateGeom3D();
    void setZoomFactor(float f);
    void commonInit(HxGiEditor*);
    void onActivate();
    void onDeactivate();

    QxViewerPanel::Layout oldLayout;
    QxViewerPanel::Layout newLayout;
    McDArray<HxViewerBase*> oldViewers;
    McDArray<HxViewerBase*> newViewers;
    McDArray<int> mMenuIds;

  public slots:
    /**
     *  To be notified that preferences changed.
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

    void readPreferences();

    void growSelection2D();
    void growSelection3D();
    void shrinkSelection2D();
    void shrinkSelection3D();
    void selectionFillVolume();
    void selectionFill();
    void selectionFillAll();
    void growSelectionAll2D();
    void shrinkSelectionAll2D();
    void smoothSelection2D();
    void smoothSelectionAllSlices();
    void selectionInvert2D();
    void selectionInvert3D();
    void selectionEllipse();
    void selectionInterpol();
    void selectionWrap();

    void showFirstSliceWithSelection();
    void showPrevSliceWithSelection();
    void showNextSliceWithSelection();
    void showLastSliceWithSelection();
    void createViewers();
    void onShow();
    void onHide();
    void redrawViewAll();

    // Reimplemented from Gi.h
    void setDataWindow(float min, float max, bool redraw=true);
    // called if dataWindow has been changed by the use of the slider
    void toolDataWindowSliderChanged(float min, float max);
    void setEnableMask(int state);
    void setShowMask(int state);
    void slotDataTouched(unsigned int);
    void slot2DColormapTouched(unsigned int);

    void changeViewerLayout();

  private slots:    
    void menuAction();
    void orientationChanged(QAction* action);
    void activeViewerChanged(QAction* action);
    void menuGreyImageChanged(QAction* action);
    void menuGradientImageChanged(QAction* action);
    void menuUndo();
    void menuClose();
    void menuRedo();
    void mapMenu();
    void menuFillHolesSlice();
    void menuFillHolesAllSlices();
    void menuRemoveIslands();
    void menuSmoothLabels();
    void menuRemoveSkin();
    void menuSnakes();
    void menuPluginFilter(QAction* action); // Generic function for mapping plugin menu entry
    // void menuLevelSets();
    void menuProjection();
    void menuStatistics();
    void menuUsersguide();
    void configureOrientationPopup();
    void configureActivePopup();
    void show3DSelection();
    void show3DSlices();
    void show3DVolren();
    void setImageDataSA(int); // triggered by sub-application image data combo box
    void setLabelDataSA(int); // triggered by sub-application label data combo box
    void newLabelDataSA(); // triggered by sub-application new label data button
    void slotObjectAddedSA(HxObject* object);
    void slotObjectRemovedSA(HxObject* object);
    void slotObjectRenamedSA(HxObject* object, const char* old_name);
    void setSelectionDrawStyle(int drawStyle, int opacity);

  private:
    QList<QAction*> mMenus;
    QAction* mUndoAction;
    QPixmap mGiLayout1, mGiLayout3;
    int undoID, dataID, orienID, activeID, fillHolesID, islandID, smoothID;
    int growID, shrinkID, fillID, smFilID, invertID, drawID, snakesID, ellipseID, interID, wrapID;
    bool mFlipX, mFlipY, mFlipZ;
    friend class GiQTissueList;

    // states of the tri state 'show 3D slices push button'
    enum {
        MPR_HIDDEN_3D        = 0, // 3D MPR is not visible
        MPR_OPAQUE_3D        = 1, // 3D MPR is opaque textured
        MPR_WIREFRAME_3D     = 2  // 3D MPR is drawn in wireframe mode e.g only slice frames and the crosshair are visible
    };

    // next button state indicator of show '3D slices push button'
    int m3DMPRNextState;

    bool mBlockHiddenSelectionCheck;
};

#endif

/// @}

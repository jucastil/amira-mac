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
#ifndef GI_H
#define GI_H

#ifdef _WIN32
#include <qwidget.h>
#include <windows.h>
#endif

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <mclib/McTypedData3D.h>
#include <mclib/McData3D.h>
#include <mclib/McVec3i.h>

#include <hxlatticex/HxLattice.h>
#include <hxfield/HxUniformLabelField3.h>
#include <hxfield/HxCoord3.h>

#include "GiFilter.h"
#include "HxGiWinDLLApi.h"

class GiViewer;
class GiVoxelGrid;
class GiFrameBuffer;
class GiSelection3D;
class GiAction;
class GiSnakesFilter;
class GiProjector;
class GiNeuronTreeShape;
class GiTool;
class GiPanTool;
class GiCrossHairTool;
class HxLabelLattice3;
class HxNeuronTree;
class HxViewer;

/// General image editor.
class HXSEGEDITOR_API Gi
{
  public:
    /// Voxel types
    enum VoxelType { BYTE, SIGNEDSHORT, UNSIGNEDSHORT, SIGNEDINT, UNSIGNEDINT, FLOAT, DOUBLE, RGB };

    /// Constructor.
    Gi();

    /// Destructor.
    virtual ~Gi();

    /// Set 8 Bit image volume.
    void setVolumeByte(const mculong* dims, int bytesPerLine,
        unsigned char* image, HxLabelLattice3* labelLat);

    /// Set 16 Bit image volume.
    void setVolumeShort(const mculong* dims, int bytesPerLine,
        short* image,  HxLabelLattice3* labelLat);

    /// Set unsigned short image volume.
    void setVolumeUnsignedShort(const mculong* dims, int bytesPerLine,
                        unsigned short* image, HxLabelLattice3* labelLat);

    /// Set 32 Bit image volume.
    void setVolumeInt(const mculong* dims, int bytesPerLine,
        int* image,  HxLabelLattice3* labelLat);

    /// Set unsigned int image volume.
    void setVolumeUnsignedInt(const mculong* dims, int bytesPerLine,
                        unsigned int* image, HxLabelLattice3* labelLat);

    /// Set float image volume.
    void setVolumeFloat(const mculong* dims, int bytesPerLine,
                        float* image, HxLabelLattice3* labelLat);

    /// Set double image volume.
    void setVolumeDouble(const mculong* dims, int bytesPerLine,
                        double* image, HxLabelLattice3* labelLat);

    /** Sets the window/level of the viewers. Pixel values smaller than
        vmin are mapped to black, and pixel values bigger than vmax
        are mapped to white. */
    virtual void setDataWindow(float vmin, float vmax, bool redraw=true) = 0;

    /** Returns the current window/level settings. */
    void getDataWindow(float& vmin, float& vmax) const;

    /** Sets the current masking window. If masking is enabled, pixels
        inside the masking window are displayed in blue. */
    virtual void setToolDataWindow(float vmin, float vmax, bool redraw=true) = 0;

    // see GiQ
    virtual void setToolDataWindowMarker(float value) = 0;
    virtual void clearToolDataWindowMarker() = 0;
    virtual void setToolDataWindowSliderTracking(bool mode) = 0;
    virtual bool toolDataWindowSliderTracking() = 0;

    /** Returns the current masking window. */
    void getToolDataWindow(float& vmin, float& vmax) const;

    /** Returns the grey-value intensity at the cursor position. This
        intensity is the same as the one displayed in the segmentation
        editor's info area in the lower left corner of the toolbox
        window. The value is used by tools like the Magic Wand in order
        to change the cursor shape. */
    float intensityAtCursor() const { return mIntensityAtCursor; }

    virtual void setMaskingEnabled(bool value) = 0;

    virtual bool maskingEnabled() const = 0;

    /// Read selection draw style and opacity from registry variable
    void readSelectionDrawStyle();

    /// Render and paste all viewers
    virtual void redraw();

    /** Render and paste all viewer if necessary, if a 2D box changed in v. box is in
        unzoomed coordinates here ! */
    void redraw(const McBox2i& change,GiViewer* v);

        /// Get orientation of current viewer
    int getCurrentOrientation();

        /// Get slice number in current viewer
    int getCurrentSlice();

    ///
    void getCurrentLabelSlice(unsigned char*& labels,
            int& bytesPerPixel, int& bytesPerLine);

    void getLabelSlice(int orientation, int slice,
                    unsigned char*& labels,int& bytesPerPixel, int& bytesPerLine);

    bool getMask(GiFrameBuffer* frameBuffer, McBitfield& mask);

    ///
    McVec3i getPoint3D(int x, int y, GiViewer* v = 0);

    /// Replace region under selection by selection.
    void replaceBySelection(int tissue, int do3D=0);

    /// Assign all selected pixels to label @c tissue.
    void storeSelection(int tissue, int do3D=0, int clearSelection=1);

    /** Assign all selected pixels of type @c tissue to an automatically
        determined background tissue. */
    void subtractSelection(int tissue, int do3D=0);

    /// Subtract 3D selection stored in bitfield.
    bool subtractSelection3D(const McBitfield& bit, int tissue);

    /// Clears selection in current slice or in all slices.
    void clearSelection(bool do3D=false, bool saveHistory=true);

    /// Inverts selection in current slice or in all slices.
    void invertSelection(int do3D=0);

    /** Selects all pixels with label @c t. If parameter @c replace is true,
        the selection is cleared before. */
    void selectTissue(int t, int replace, int do3D=0);

    bool tissueSelected(int t);

    /** Locks or unlocks the given tissue type. If a tissue has been locked
        it is not modified by @c storeSelection() and related methods.
        Interactive tools which directly modify the selection should also
        preserve locked tissues. Filters currently ignore locks. */
    void lockTissue(int tissue, int lock);

    /// Returns true if the given tissue type is locked.
    int isLocked(int tissue) { return lock[tissue & 0xff]; }

    /// Return pointer to lock array.
    const int* getLocks() const { return lock; }

    /// Returns pointer to volume of voxel labels.
    HxLabelLattice3* getLabelLattice() { return labelLattice; }

    /// Returns pointer to the editor's 3D selection object.
    GiSelection3D* getSelection3D() { return selection3D; }

    /// Returns voxel type of CT/MR image volume (byte/short/rgb).
    VoxelType getVoxelType() const { return voxelType; }

    /// Returns a reference to the CT/MR image volume.
    McTypedData3D& getImage3D() { return imageVolume; }

    /// Returns a reference to the gradient image volume.
    McTypedData3D& getGradientImage3D();

    /// Generates the defaults gradient image
    void generateGradientImage();

    /// Returns a reference to the CT/MR image volume.
    McData3D<unsigned char>& getLabelImage3D() { return labelVolume; }

    /// Returns number of slices of image volume being edited.
    int getNumSlices(int orientation=-1);

    /// Select a tool (0=Lasso, 1=Brush, 2=MagicWand, 3=PickRegion)
    virtual void setTool(int which);

    /// Returns a pointer to the active tool.
    GiTool* getActiveTool() const { return activeTool; }

    /// Returns the index of the active tool or -1 if no tool is active.
    int getActiveToolId() const { return index(allTools,activeTool); }

    /// Set mouse cursor (get it from current tool)
    virtual void updateCursor() { };

    /// Returns pointer to a filter (0=Smooth, 1=FillBone, 2=RemoveIslands)
    GiFilter* getFilter(int i) { return allFilters[i]; }

    /// Returns a reference to the array of available filters.
    const McDArray<GiFilter*> & getAllFilters() const { return allFilters; }

    /// Returns the first filter of the given type in the array.
    template<class T> T* findFilter() {
        for (mclong i=0;i<allFilters.size();++i) {
            T* f=dynamic_cast<T*>(allFilters[i]);
            if (f) {
                return f;
            }
        }
        return NULL;
    }

    /// List of all viewers - each one may display a different slice
    /// and orientation.
    McDArray<GiViewer*> allViewers;

    ///
    GiViewer* getCurrentViewer();

    ///
    void locateTissue(int tissue);

    /// The tissue is set by GiXToolbox.
    void setCurrentTissue(int tissue) { currentTissue = tissue; }

    /// Tools and filter may access this.
    int getCurrentTissue() const { return currentTissue; }

    /// The 3d mode is set by GiQToolbox (or by GiMagicWand).
    virtual void set3dMode(bool onOff);

    virtual void setZoomMode(bool onOff);

    /// Tools and filter may access this.
    bool get3dMode() const { return flag3d; }

    bool getZoomMode() const { return zoomAll; }

    /** Fill holes in selection. A seed point may be specified. If not,
    the whole border is the seed. If the erase flag is specified the selection
    is cleared. This makes only sense in conjunction with a seed point.*/
    void fillSelection(int sx=-1,int sy=-1, int clear=0);

    ///
    void interpolSelections();

    ///
    void interpolSelections(int from, int to, int orientation);

    ///
    void wrapSelections();

    ///
    int extrapolSelections(int up);

    ///
        GiTool* getTool(int which) {
                return (which >= 0 && which < allTools.size()) ? allTools[which] : NULL;
        }

        ///
        int  getNumTools (void) { return allTools.size(); }

    /** Adds an action to the undo stack. If @c addToMultiAction is
        true and the last action on the stack is a GiMultiAction
        the action is added to the multi action instead of being
        added to the stack by itself. */
    void addUndoAction(GiAction*, bool addToMultiAction=0);

    /** Any tool which modifies the selection or the labels should
        call this function to report the change. A value slice=-1
        indicates that multiple slices have been changed. */
    virtual void touchData(int selChanged, int lblChanged,
                           int orientation, int slice,
                           int automatic, int cleared);

    /** Convenience function to create undo action, that stores information
        for the current slice. The action is automatically added to the stack.*/
    void saveUndoInformationForSlice(int withSelection, int withLabels, GiViewer* viewer = 0);

    /// save the selection for a volume. Action added to the stack.
    void saveUndoInformationForVolume(int withSelection, int withLabels, GiViewer* viewer = 0);

    /** This method clears the undo stack. It should be called whenever the selection
        or label image is modified in a way that can not be undone.*/
    void clearUndo(int clearSliceFlags=1);

    ///
    void undo();

    ///
    void redo();

    ///
    int canUndo();

    ///
    int canRedo();

    ///
    void updateSelectionBoxes();

    /* Update selection in a certain subregion. If multiple viewers are present,
       selections in other viewers are updated if necessary.*/
    void updateSelectionBoxes(McBox2i& box,GiViewer* viewer);

    /// get zoom factor in ascii form, e.g. "1:2"
    const char* getZoomFactorText();

    ///
    void zoomIn();

    ///
    void zoomOut();

    ///
    virtual void setZoomFactor(float f);

    ///
    virtual void updateUndoSensitivity();

    ///
    virtual bool getPickedVoxel(HxViewer* viewer, int x, int y, McVec3i& voxel, float& intensity) = 0;

    /// Projects a box from one viewer into another
    void projectBox(GiViewer* v1, GiViewer* v2, const McBox2i& in, McBox2i& out);

    /// Call virtual init() method for all tools (used in HxGiEditor).
    void initTools();

    ///
    GiProjector* getProjector() {return projector;}

    ///
    HxNeuronTree* getNeuronTree() {return neuronTree;}

    /// Find all byte/short data sets in object pool, with given dims.
    static void findImageDataSets(const mculong* dims, McDArray<HxData*>& images);

    /** Set mapping between raw and physical intensity units. This method
        should be called after a new image data set has been set. It reads
        the attributes DataWindowScale and DataWindowBias from the parameter
        bundle of the image object. Afterwards intensity values can be
        converted via scale() and rescale(). */
    void setRescaleInterceptSlope(const HxParamBundle* parameters=0);

    /** Converts from raw units to physical units. \sa setRescaleIntercept() */
    float rescale(float value, float x=1.f) { return value*mRescaleSlope + x*mRescaleIntercept; }

    /** Converts from physical units to raw units. \sa setRescaleIntercept() */
    float scale(float value, float x=1.f) { return (value-x*mRescaleIntercept)/mRescaleSlope; }

    /// get slice and contiguous selection field for current slice
    void getSliceLattice(HxLattice3 *&lattice, unsigned char *&selection, int whichImage = 1);
    //void getSliceLattice(HxLattice3 *&lattice, GiSelection3D *selection, int whichImage = 1);

    /// update and redraw selection from one slice lattice
    void updateSliceLattice(HxLattice3 *&lattice, unsigned char *&selection);

    int getProjectionMode() const { return projectionMode; }

    void setProjectionMode(int mode){ projectionMode = mode; }

    // draw style for materials (hatched, dotted, ...)
    unsigned char drawStyle2D[257]; // may include INVISIBLE
    unsigned char defaultDrawStyle2D[257]; // stores visible styles only

    unsigned char materialDisplay3D[256];

    // material colors
    unsigned char labelColors[257][3];

    // Register an external filter
    void registerPlugin(GiFilter* filter) { allPluginFilters.append(filter); }

    // Making the picking translation of the GI available to external plugins
    SbVec3f getPickingTranslation();
    void resetPickingTranslation();

    GiCrossHairTool* crossHair;

    HxData* labelData;              // label data object being edited, will be touch()'ed
    HxParamBundle* materials;       // parameter bundle containing the material info
    HxLabelLattice3* labelLattice;  // the actual label data to be edited
    HxData* imageData;              // image data object being shown
    HxLattice* imageLattice;        // underlying image data used for segmentation

    int voxelPrecision; // number of digits used when printing the position
    int intensityPrecision; // number of digits used when printing intensity values

    virtual void sliceNumberChanged(GiViewer*);

  protected:

    // used by generateGradientImage
    void generateGradientByteImage();
    void generateGradientShortImage();
    void generateGradientUnsignedShortImage();
    void generateGradientUnsignedIntImage();
    void generateGradientIntImage();
    void generateGradientFloatImage();

    // DATA
    McDArray<GiAction*> undoStack;
    McDArray<GiAction*> redoStack;
    int undoStackSize;

    McDArray<GiFilter*>         allFilters;
    McDArray<GiFilter*>         allPluginFilters;
    McDArray<GiTool*>           allTools;
    GiTool*                     activeTool;
    GiPanTool*                  mPanTool;
    GiSnakesFilter*             snakes3DTool;
    VoxelType                   voxelType;
    float                       dataWindow[2];
    float                       toolDataWindow[2];
    int                         lock[256];
    int                         currentTissue;
    bool                        flag3d;
    bool                        zoomAll;
    int                         crossHairLock;
    McTypedData3D               imageVolume;
    McTypedData3D               gradientImageVolume;
    McHandle<HxRegScalarField3> defaultGradientImage;
    float                       mRescaleSlope;
    float                       mRescaleIntercept;
    float                       mIntensityAtCursor;

    McData3D<unsigned char>     labelVolume;
    GiSelection3D*              selection3D;
    GiViewer*                   lastCurrentViewer;

    static void crossHairCBs(GiCrossHairTool* crossHair, void* userData);
    virtual void crossHairCB(GiCrossHairTool* crossHair);

    virtual void setVolume(const mculong* dims, McTypedPointer data, HxLabelLattice3* result);


    // this for the maximum intensity projection mode, used in neuron or
    // angiography segmentation
    int projectionMode;
    GiProjector* projector;
    GiNeuronTreeShape* neuronTreeShape;
    HxNeuronTree* neuronTree;

    // Set in GiQ
    class QxViewerPanel* mPanel;

    // this could be done in the destructor. However to have
    // a better control of the order of destruction in case of
    // multiple inheritance, we do it here:
    void destroyMembers();

    friend class HxGiEditor;
};

#endif

/// @}

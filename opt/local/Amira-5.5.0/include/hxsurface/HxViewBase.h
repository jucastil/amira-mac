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

/// @addtogroup hxsurface hxsurface
/// @{
#ifndef HX_VIEW_BASE_H
#define HX_VIEW_BASE_H

#include <hxsurface/HxSurfaceWinDLLApi.h>

#ifdef NEWSTYLE_IOSTREAM
#include <iostream>
#else 
#include <iostream.h>
#endif

#include <hxcore/HxModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxGLPolyLine.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxSelectInterface.h>
#include <hxcore/HxDisplay.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoTextureCoordinateObject.h>
#include <Inventor/nodes/SoTexture2.h>
#include <Inventor/draggers/SoTabBoxDragger.h>

#include <hxcolor/HxPortColormap.h>
#include <hxcolor/HistogramProviderModuleIface.h>
#include <hxsurface/SoSurface.h>
#include <hxsurface/HxPortDrawStyle.h>
#include <hxsurface/HxSurface.h>

class HxViewBaseData;
class QxViewBaseNotifier;

/** Base class for modules displaying a set of triangles. This class serves
    as a front end for the SoSurface graphics class. An instance of
    SoSurface as well as some other Open Inventor nodes are automatically
    created in the constructor. Derived classes initialize, show, and hide
    the SoSurface class as needed.
    
    HxViewBase provides a special-purpose port which allows the user to
    modify the draw style of the triangular surface in a easy and
    consistent way (all modules derived from HxViewBase exhibit a similar
    GUI). Moreover, this class provides a generic buffer-concept allowing
    the user to select triangles by means of an Open Inventor tab-box
    dragger. Triangles inside the tab-box are highlighted (see
    SoSurface). Highlighted triangles can be added to the buffer,
    i.e., selected, or removed from the buffer, i.e., deselected.

    Other features of HxViewBase include the following:
    

    @li Pseudo-coloring: An arbitrary 3D scalar field can be connected
	to @c portColorField. In this case vertex colors are computed for
	every vertex defined in @c soSurface->coords. Colors are taken from
	a colormap which is attached to @c portColormap. Thus the scalar
	field can be visualized on top of the surface geometry.

	Note, that the base class makes use of the procedural data
	interface provided by the scalar field (createLocation(), eval()).
	Derived classes can extend this behaviour, for example to handle
	scalar fields defined on the same set of triangles being 
	displayed by SoSurface. In this case scalar values defined on
	vertices may be accessed direclty, or discontinuities can be
	handled properly.

    @li Surface export: The triangles defined in @c soSurface can be
	automatically converted into a new object of type HxSurface.
	Only selected (visible) triangles will be included into the surface.
	The base class creates surfaces with only a single patch. Derived
	classes may overwrite the method @c createSurfaceData() if more
	information about patches is available (see for example
	HxGridBoundary).

    @li Common Tcl-commands: Many parameters of the SoSurface node can be
	controlled via the Tcl-command interface. This includes line
	width, outline color, highlight color, specular color, shininess, 
	alpha mode, normal binding, and more.

    
*/

class HXSURFACE_API HxViewBase : public HxModule{

  MC_ABSTRACT_HEADER(HxViewBase);

  class HistogramProvider : public HistogramProviderModuleIface {
      public:
        HistogramProvider(HxViewBase* owner);

        virtual McHandle<McHistogram> getHistogram(unsigned int numBins, HxPortColormap* const colormap);
        virtual McHandle<McHistogram> getHistogramAsync(unsigned int numBins, HxPortColormap* const portColormap);
      private:
        HxViewBase* mOwner;
    };

  public:

    /// Constructor for derived classes.
    HxViewBase(McHandle<SoSurface>& surface, const McTypeInfo* dataType=0);

    /// Draw style: 0=outlined, 1=shaded, 2=lines, 3=points, 4=transparent
    HxPortDrawStyle portDrawStyle;

    /// Connection to field used for pseudo-coloring.
    HxConnection portColorField;

    /// Colormap applied to field.
    HxPortColormap portColormap;

    /// Texture projected on surface.
    HxConnection portTexture;

    /// Texture wrap mode used while mapping on surface.
    HxPortMultiMenu portTextureWrap;
    enum { WRAP_REPEAT=0, WRAP_CLAMP=1 };

    /// Colormap applied to field.
    HxConnection portRoi;

    /// Port used to select culling mode for the surface.
    HxPortRadioBox portCullingMode;

    /// Culling modes.
    enum CullingMode {
        /// No culling (render both faces).
        NO_CULLING=SoSurface::NO_CULLING,
        /// Cull back faces.
        BACK_FACE=SoSurface::BACK_FACE,
        /// Cull front faces.
        FRONT_FACE=SoSurface::FRONT_FACE
    };

    /// Set culling mode for the surface.
    void setCullingMode(CullingMode mode);

    /// Buffer: 0=add, 1=remove, 2=clear, 3=show/hide box, 4=draw
    HxPortButtonList portBuffer;
    enum { BUFFER_ADD=0, BUFFER_REMOVE=1,
           BUFFER_CLEAR=2, BUFFER_BOX=3, BUFFER_DRAW=4 };

    /// Shows and hides portColormap.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char** argv);

	/** Adds all selected triangles or quads to the given HxSurface.
        If a transformation matrix is given, it is applied to all points
        before adding them to HxSurface.
		@see createSurfaceData()
	*/
	virtual void addToSurface(HxSurface& Surf, SbMatrix *transMat=0);

    /** Creates a HxSurface containing all selected triangles or quads.

		Resulting surface will be put into the ObjectPool without a connection to this module.

		@see addToSurface()
	*/
    virtual void createSurfaceData();

    /// Enumeration type used in @c drawStyleChanged().
    enum DrawStyleParameters {
	    /// Alpha mode (opaque, constant alpha, fancy alpha).
	    ALPHA_MODE,
	    /// Sorting mode (sorting on or off).
	    SORTING_MODE,
	    /// Culling mode (both faces, front face, back face).
	    CULLING_MODE,
	    /// Normal binding (per triangle, per vertex, direct).
	    NORMAL_BINDING
    };

    /** This is called when SoSurface parameters have been changed via
	the <em> more options</em> menu of HxPortDrawStyle. */
    virtual void drawStyleChanged(DrawStyleParameters what);

    /// Modes for unsetting, setting, and toggling selection bits.
    enum BitMode {
	/// Bit should be unset.
	UNSET_BIT=0,
	/// Bit should be set.
	SET_BIT=1,
	/// Bit should be toggled.
	TOGGLE_BIT=2
    };

    /// Returns the number of elements (triangles, quads, tetrahedra, ...).
    virtual int selectinterface_getNum() const;

    /// Check whether element i is selected.
    virtual int selectinterface_isSelected(int i) const;

    /// Change selection bit of element i.
    virtual void selectinterface_select(int i, int mode = SET_BIT);

    /// Change selection bit of all elements.
    virtual void selectinterface_selectAll(int mode = SET_BIT);

    /// Returns selected elements in bitfield.
    virtual void selectinterface_getSelected(McBitfield& bitfield);

    /// Causes a redraw.
    virtual void selectinterface_touch();

    virtual HxParamBundle* selectinterface_bundle(int create);

  protected:
    /// Destructor.
    virtual ~HxViewBase();

    /// Automatically connects module to colorField's default color map.
    void autoSetColormap();

    /// Interpretes portBuffer and calls bufferAdd(), bufferRemove(), etc.
    void handleBuffer();

    /// Interpretes portDrawStyle and sets soSurface fields.
    virtual void handleDrawStyle();

    /// Fill the inRoi field of surface according to input.
    virtual void handleRoi();

    int handlePseudoColor(int autoColor=1);
    void pseudoColorGouraud(SoSurface* surface);
    void pseudoColorTexture(SoSurface* surface);
    bool handleTexture();

    int handlePseudoColorTetra();
    void pseudoColorGouraudTetra(SoSurface* surface);
    void pseudoColorTextureTetra(SoSurface* surface);

    int handlePseudoColorSurface();
    void pseudoColorGouraudSurface(SoSurface* surface);
    void pseudoColorTextureSurface(SoSurface* surface);
    void vectorColorGouraudSurface(SoSurface* surface);

    /// Selects all highlighted triangles (== adds them to buffer).
    virtual void bufferAdd();

    /// Unselects all highlighted triangles (== removes them from buffer).
    virtual void bufferRemove();

    /// Unselects all triangles.
    virtual void bufferClear();

    /// Unhighlights all triangles.
    virtual void bufferHide();

    /// Highlights all triangles inside box.
    virtual void bufferNew();

    /// Shift-click deselects current triangle.
    virtual void mouseClick(SoEventCallback*);

  public:
    /** Connection point for Qt signals and slots.
      */
    QxViewBaseNotifier* const mNotifier;

    /**
     *  To update the use of display lists
     */
    virtual void preferencesChanged(const HxPreferences& oldPreferences, const HxPreferences& newPreferences);

    void setLegend(const char* text);
    void addText(const McVec3f& pos, const char* text);
    void setTextSize(float size);
    void set3DTextMode(bool is3d);
    void clearText();

    void initBox(float box[6]);
    void showBox();
    void hideBox();

    void getSelectedTriangles(ostream& out);

    McHandle<SoSurface>& soSurface;
    McHandle<SoSeparator> soRoot;
    McHandle<SoMaterial> soMaterial;
    McHandle<SoDrawStyle> soDrawStyle;
    McHandle<SoEventCallback> soEvent;
    McHandle<SoTabBoxDragger> dragger;
    McHandle<SoTextureCoordinateObject> m_texProj; 
    McHandle<SoTexture2> m_texture;

    HxViewBaseData* viewBaseData;

    /// a pointer to polyLine
    HxGLPolyLine* getPolyLine() { return &polyLine; }

    void setPolygonOffsetMode(SoSurface::PolygonOffsetMode mode);
    SoSurface::PolygonOffsetMode getPolygonOffsetMode();

  protected:
    HxGLPolyLine polyLine;
    unsigned int isDragging;
    float maxScaleX, maxScaleY, maxScaleZ;
    float xMin, xMax, yMin, yMax, zMin, zMax;

    void constrainBox();
    virtual void viewerSelect();
    int getTransform(SbMatrix& mat);

    static void viewerSelectCB(void* userData);
    static void newBoxCB(void* userData, SoDragger* dragger);
    static void startDraggingCB(void* userData, SoDragger*);
    static void finishDraggingCB(void* userData, SoDragger* dragger);
    static void mouseClickCB(void* userData, SoEventCallback* soEvent);

    static int portTextureCheck(void* userData, HxObject* src);

    virtual void savePorts(FILE* fp);

    SoSurface::PolygonOffsetMode m_polygonOffsetMode;

  friend class HxPortDrawStyle;
  friend class SurfEditProjector;

  private:
    HistogramProvider mHistogramProvider;
};

#endif

/// @}

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
#ifndef GI3DDIALOG_H
#define GI3DDIALOG_H

#include <mclib/McHandle.h>
#include <mclib/McDArray.h>
#include <mclib/McVec3s.h>
#include <mclibthreaded/McMutex.h>

#include <Inventor/nodes/SoCallback.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoSeparator.h>
#include <hxcore/HxGLPolyLine.h>

#include <qobject.h>

#ifdef HAVE_VSVOLREN
#include <vsvolren/VsSlice.h>
#endif

class GiQ;
class QMenu;
class QAction;
class HxColormap;


class Gi3DDialog : public QObject
{ 
    Q_OBJECT

public:
    Gi3DDialog(GiQ* gi);
    ~Gi3DDialog();

    void dataChanged(int sel, int lbl);
    void sliceNumberChanged();
    void showGeom(bool state);

    void setSelectionVisible(bool value);
    bool selectionVisible() const;

    void setSlicesVisible(bool value);
    bool slicesVisible() const;

    void setVolrenVisible(bool value);
    bool volrenVisible() const;

    void setVolrenLevel(int level);
    int volrenLevel() const;

    void setLabelClipped(int labelIndex, bool value);
    void setUseLabelColor(int labelIndex, bool value);
    
    /** Moves all materials  > labelIdxToBeRemoved with index i to index i--
        Affected values are useLabelColor, labelColor, labelClipped. */
    void updateLabels(int labelIdxToBeRemoved);

    /** Returns for each material if this material is visible or not.
        The return value depends on the current render mode. If volume
        rendering is on by default all materials are visible. If volume
        rendering is off by default all materials are invisible. */
    void get3DVisibility(bool visibility[256]);

    /** Returns for each material if it's own color should be used. */
    void getUseLabelColor(bool coloring[256]);
    
    void updateLabelLattice();
    void updatePreferences();
    void touchVolren();
    void touch();

    void reset();

    void configure3DColormapMenu(QMenu* menu);

    bool getPickedPoint(HxViewer* viewer, int x, int y,
        McVec3f& pObject, McVec3i& voxel, float& intensity);
    
    
    void set2DColormap(HxColormap* cm);

    // set render mode of 3d mpr slices 
    // allowed values are as following:
    // mode == 0 wirefrime e.g only slice frames and the crosshair are visible
    // mode != 0 density (textured slice)
    void set2DRenderSettings(int mode = 1);

protected:
    class Gi3DDialogPrivate* d;

    GiQ* gi;
    int drawStyle;
    bool showgeom;
    bool showMaterial;
    bool mSelectionVisible;
    bool mSlicesVisible;
    bool mVolrenVisible;
    bool selectionUpToDate;
    bool materialsUpToDate;
    bool useLabelsInVolren;
    McMutex mutex;

    // current render mode of 3d mpr slices
#ifdef HAVE_VSVOLREN
    VsSlice::RenderMode mSliceRenderMode;
#endif

    /// Uniform coordinates
    /// Selection
    McDArray<McVec3s> points[6];
    /// Materials
    McDArray<McDArray<McVec3s> > mpoints[6];

    /// Stacked coordinates
    /// Selection
    McDArray<McVec3f> pointsf[6];
    McDArray<float> voxelsizezminus[6]; // point's z-size per vertex
    McDArray<float> voxelsizezplus[6]; // point's z-size per vertex
    /// Materials
    McDArray<McDArray<McVec3f> > mpointsf[6];
    McDArray<McDArray<float> > mvoxelsizezminus[6];
    McDArray<McDArray<float> > mvoxelsizezplus[6];
    
    McHandle<SoCallback> socallback;
    McHandle<SoSeparator> separator;

    void updateSelection();
    void updateMaterials();
    void initSlices();
    void renderSlices();
    void renderVolume();
    void render(SoGLRenderAction* renderAction);
    void getBoundingBox(SoGetBoundingBoxAction* renderAction);
    static void renderCallback(void* userData, SoAction* action);

    class SoCoordinate3* coordsNode;
    class SoPointSet* pointSet;

  protected slots:
    void cleanup();
    void set3DColormap(QAction* action);
    void set3DRenderSettings(QAction* action);
};

#endif // GI3DDIALOGBASE_H

/// @}

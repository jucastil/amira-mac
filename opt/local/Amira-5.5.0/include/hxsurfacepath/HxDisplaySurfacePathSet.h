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

/// @addtogroup hxsurfacepath hxsurfacepath
/// @{
#ifndef HX_DISPLAY_SURFACE_PATH_SET
#define HX_DISPLAY_SURFACE_PATH_SET

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoCube.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoVertexProperty.h>

#include "HxSurfacePathSet.h"
#include "hxsurfacepathAPI.h"

#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxModule.h>

class SoShape;

/// Class for selecting control points and paths.
class HXSURFACEPATH_API SelectionInfo
{
private:

    /// Active control point.
    int activeCP;

    /// Set of active paths.
    McDArray<int> activePaths;

    /// Pointer to path set.
    SurfacePathSet* pathSet;

public:

    /// Constructor.
    SelectionInfo();
    
    /// Constructor.
    SelectionInfo(SurfacePathSet* pS);

    /// Sets the surface path set.
    void setSurfacePathSet(SurfacePathSet* pS);

    /// Returns single active path.
    int getActivePath() const;

    /// Returns active control point.
    int getActiveCP() const;

    /// Checks if path is active.
    bool isPathActive(int path) const;

    /// Returns reference to active paths.
    const McDArray<int>& getActivePaths() const;

    /// Checks whether only single path is active.
    bool isInEditMode(void) const;

    /// Checks whether any path is active.
    bool noPathSelected(void) const;

    /// Checks whether control point @c CP lies on active path.
    bool isCPOnActivePath(int CP) const;

    /// Synchronizes state of selection with pathset.
    void synchronize();

    /// Sets active control point.
    void setActiveCP(int aCP);

    /// Sets single active path.
    void setSinglePathActive(int activePath);

    /// Add path to set of active paths.
    void addToActivePaths(int path);

    /// Sets all paths as inactive.
    void deselectAll(void);

    /// Sets given path as inactive.
    void deselectPath(int path);

    /// Assignment operator.
    SelectionInfo& operator=(const SelectionInfo& other);

    /// Compares values of other and this.
    bool equals(const SelectionInfo& other);
};


/// Display module for surface path sets.
class HXSURFACEPATH_API HxDisplaySurfacePathSet : public HxModule
{
    HX_HEADER(HxDisplaySurfacePathSet);

public:

    /// Constructor.
    HxDisplaySurfacePathSet(void);

    /// GUI: Size of the cubes representing ControlPoints.
    HxPortIntSlider portPointSize;

    /// GUI: Displayed size of the drawn contour.
    HxPortIntSlider portLineWidth;

    /// GUI: Shape for control point.
    HxPortMultiMenu portControlPointShape;

    /// Control point colors.
    HxPortColorList portCPColors;

    /// Path colors.
    HxPortColorList portPathColors;

    /// Display parameters.
    HxPortFloatTextN portDisplayParams;

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Tcl command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    /// Returns oiv line separator.
    SoSeparator* getLineSeparator() const { return lineSep; }

    /// Returns oiv control point separator.
    SoSeparator* getControlPointSeparator() const { return cpSep; }

    /// Returns current selection.
    const SelectionInfo& getSelection() const { return selection; }

    /// Returns current selection.
    SelectionInfo& getSelection() { return selection; }
    
    /// Maps segment index to path index.
    int computePathIndexFromInventorSegmentIndex(int segmentIndex);

protected:

    /// Destructor.
    ~HxDisplaySurfacePathSet(void);

private:
    
    /// Scene graph.
    McHandle<SoSeparator> scene;
    McHandle<SoSeparator> lineSep;
    McHandle<SoSeparator> cpSep;

    /// Inventor node: inactive control points.
    McHandle<SoCube> greyCube;
    McHandle<SoSphere> greySphere;

    /// Inventor node: active control points.
    McHandle<SoCube> greenCube;
    McHandle<SoSphere> greenSphere;

    /// Inventor node: control point on active paths.
    McHandle<SoCube> redCube;
    McHandle<SoSphere> redSphere;

    /// Inventor node: end control point on active path.
    McHandle<SoCube> blueCube;
    McHandle<SoSphere> blueSphere;

    /// Inventor nodes: different colors.
    McHandle<SoGroup> groupRed;
    McHandle<SoGroup> groupGreen;
    McHandle<SoGroup> groupBlue;
    McHandle<SoGroup> groupGrey;

    /// Inventor nodes: different materials.
    McHandle<SoMaterial> materialRed;
    McHandle<SoMaterial> materialGreen;
    McHandle<SoMaterial> materialBlue;
    McHandle<SoMaterial> materialGrey;

    /// Used for fast line access.
    McHandle<SoVertexProperty> property;
    McHandle<SoDrawStyle> drawStyle;

    /// Pointer to path object.
    HxSurfacePathSet* pathSet;

    /// Creates lines.
    int makeLines(float offsetRatio);

    /// Creates control points.
    int makeControlPoints();

    /// Sets line colors.
    void setLineColors();

    /// Sets line color for @c line.
    void setLineColor(const McColor& color, int line);

    /// Sets line width.
    void setLineWidth(int width);

    /// Sets shape size.
    void setShapeSize(int shapeSize);

    /// Stores selection info.
    SelectionInfo selection;
};


/** New class representing a control point that stores its own node index.
 */
class HXSURFACEPATH_API SoControlPointSeparator : public SoSeparator
{
    SO_NODE_HEADER( SoControlPointSeparator );

public:

    /// Initializes class.
    static void initClass();

    /// Oiv separator for control points.
    SoControlPointSeparator();
    
    /// Sets shape of control point.
    void setDetails(const McVec3f& point, SoShape* shape);

    /// Returns node index.
    int getNodeIndex() { return nodeIndex; }

    /// Sets nodeIndex to @c ind.
    void setNodeIndex(int ind) { nodeIndex=ind; }

private:

    /// Index (in SurfacePathSet.nodes) of the node, this Separator
    /// represents.
    int nodeIndex;
};

#endif // HX_DISPLAY_SURFACE_PATH_SET

/// @}

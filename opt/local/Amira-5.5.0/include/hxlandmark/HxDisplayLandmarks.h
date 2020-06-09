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

/// @addtogroup hxlandmark hxlandmark
/// @{
#ifndef HX_DISPLAY_LANDMARKS_H
#define HX_DISPLAY_LANDMARKS_H

#include <hxlandmark/HxLandmarkWinDLLApi.h>
#include <Inventor/draggers/SoDragPointDragger.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoComplexity.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/engines/SoCompose.h>
#include <mclib/McHandle.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcolor/HxPortColormap.h>
#include <hxlandmark/HxLandmarkSet.h>

class SoNode;
class SoComplexity;
class SoSeparator;
class SoShapeKit;
class SoWrapperKit;
class SoTransformManip;
class SoEventCallback;
class SoPickedPoint;
class HxLandmarkEditor;

/// Displays a landmark set.
class HXLANDMARK_API HxDisplayLandmarks : public HxModule {

    HX_HEADER(HxDisplayLandmarks);

public:
    /// Constructor.
    HxDisplayLandmarks();

    /// Update method shows/hides necessary ports.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Spatial data object defining size of projection box.
    HxConnection portBox;

    /// Defines the set to be displayed (0=all,1,2,...).
    HxPortMultiMenu portChooseSet;

    /// Display lines between corresponding markers (toggle 0).
    HxPortToggleList portMode;

    /// Draw style: 0=spheres or points, 1=projection markers
    HxPortToggleList portDrawStyle;

    /// Controls size of default markers.
    HxPortFloatSlider portSize;

    /// Let the user modify the size of default markers.
    HxPortButtonList portSizeChange;

    /// Controls complexity of default markers (which are drawn as spheres).
    HxPortFloatSlider portComplexity;

    /// set color for one landmark set
    void setColor(int set, float r, float g, float b); 

    /// set color for connecting lines
    void setLineColor(float r, float g, float b); 

    /// Tcl command interface.
    int parse(Tcl_Interp* t, int argc, char **argv);

    ///
    void attachManip(SoTransformManip* manip, int point, int set);

    ///
    void detachManip(SoTransformManip* manip, int point, int set);

    ///
    void deselectAll();

    /// Writes a command sequence initializing the ports to fp.
    virtual void savePorts(FILE* fp);

protected:
    ~HxDisplayLandmarks();

    struct {
        int set;
        int point;
    } selectedPoint;

    float box[6];
    int movingPoint;
    McColor colors[3]; //!> colors for 3 sets of landmarks
    McColor lineColor; //!> color for connecting lines
    int mLineWidth;
    float defaultSphereRadius;

    McHandle<SoSeparator> separator;
    McHandle<SoComplexity> complexity;
    McHandle<SoSeparator> sphereroots[3];
    McHandle<SoSeparator> circleroots[3];
    McHandle<SoSeparator> lineroot;
    McHandle<SoNode> philipsMarker;
    McHandle<SoNode> leibingerMarker;
    McHandle<SoNode> beekleyMarker;
    McHandle<SoNode> thermoMarker;
    McHandle<SoSphere> defaultSphere;
    McHandle<HxLandmarkSet> pointSet;
    McHandle<SoEventCallback> eventCallback;

    HxLandmarkEditor* findEditor();
    void select(const SoPickedPoint *pickedPoint);
    void deselect();
    SoNode* createLines(HxLandmarkSet *set);
    SoNode* buildSceneGraph(HxLandmarkSet*, int set);
    SoSeparator* getMarkerFromFile(const char *fileName);
    void createPointSet(SoGroup* root, HxLandmarkSet* landmarks, int which);
    void createCircles(HxLandmarkSet *set, int s);

    static void eventCB(void *that, SoEventCallback* node);

    void calcBBAndSphereRadius();
};

#endif

/// @}

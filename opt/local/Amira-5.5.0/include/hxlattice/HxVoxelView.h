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

/// @addtogroup hxlattice hxlattice
/// @{
#ifndef HX_VOXEL_VIEW
#define HX_VOXEL_VIEW

#include <mclib/McBitfield.h>
#include <mclib/McData3D.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxlattice/HxOrthoSlice.h>
#include <hxlattice/HxLatticeWinDLLApi.h>

class SoLineSet;
class SoShapeKit;
class SoDragger;
class SoTabBoxDragger;
class SoNode;
class SoEventCallback;

///
class HXLATTICE_API HxVoxelView : public HxModule {

  HX_HEADER(HxVoxelView);

  public:
    /// Constructor.
    HxVoxelView();

    /// Destructor.
    ~HxVoxelView();

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Automatically connect to secondary port.
    virtual int autoConnect(HxObject*);

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
    
    /// Pointer to volume (portData is ortho slice).
    HxTightConnection portSlice;

    /// Optional colormap defines color of extracted regions.
    HxPortColormap portColormap;

    /// Maximum number of slice to traverse in both directions.
    HxPortIntSlider portMaxDist;

    /// Possible styles are faces+contours, faces only, contours only
    HxPortMultiMenu portDrawStyle;

    /// selects different floodfill algorithms
    HxPortMultiMenu portFill;

    /// Clear selection.
    HxPortDoIt portAction;

    /// Set callback to be invoked for any selection
    void setSelectionNotifyCB(void (*f)(void*, HxVoxelView*), void*);
    
    virtual void saveUpdate(FILE* fp);

    struct Region {
	int seed[3];
	int numFaces;
      int numLines;
      int maxDist;
      int floodType;
      float posx,posy,posz;

	Region() { }

	Region(int i, int j, int k, int d, int t, float x, float y, float z) {
	    seed[0] = i;
	    seed[1] = j;
	    seed[2] = k;
	    numFaces = 0;
	    numLines = 0;
	    maxDist = d;
	    floodType = t;
	    posx = x;
	    posy = y;
	    posz = z;
	}
    };

    McDArray<Region> regions;

  protected:
    SoSeparator* sceneRoot;
    SoShapeKit*	shape;
    SoEventCallback* eventCB;
    McBitfield bitfield;
    HxOrthoSlice* slice;
    HxRegScalarField3* field;
    void* selectionNotifyUserData;
    void (*selectionNotifyCB)(void* userData, HxVoxelView*);
    
    unsigned char isLabelField();
    unsigned int getColor(float value);
    inline unsigned char aLine(bool a, bool b, bool c, bool d);

    void extractRegion(const SbVec3f&, int add, int fill, int maxDist);
    void removeRegion(int faceIndex);

    static void voxelPickCB(void *userData, SoEventCallback *eventCB);
    static int slicePickCB(const SbVec3f&, const SoMouseButtonEvent*, void*);

    SoLineSet*          contours;
    SoShapeKit*         conShape;
    
   
};
#endif

/// @}

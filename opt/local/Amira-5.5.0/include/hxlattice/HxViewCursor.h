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
#ifndef HX_VIEWCURSOR_H
#define HX_VIEWCURSOR_H


#include <Inventor/draggers/SoRotateDiscDragger.h> 
#include <Inventor/draggers/SoTransformBoxDragger.h> 


#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/SoTabPlaneDragger2.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hximview/QxLightBox.h>

#include <hxlattice/HxMapToTexture.h>

#include <hxlattice/HxLatticeWinDLLApi.h>


class TexturedRectangle;

class HXLATTICE_API HxViewCursor  : public HxOverlayModule{

    HX_HEADER(HxViewCursor);

    typedef SoTabPlaneDragger2 DraggerType;

private:

    /// two controlled oblique slices.
    TexturedRectangle* mSlice1;
    TexturedRectangle* mSlice2;

    /// draggers
    McHandle<DraggerType> mDragger;
    McHandle<SoRotateDiscDragger>  mRotateDragger;

    /// rotation angle
    float mAngle,mLastAngle;

    /// translation
    SbVec2f mTranslation;


    /// connected data
    HxField3* mField;

    /// called by draggerFinishCB to update ports
    void updateDraggerPorts(); 

    static void draggerCB(void *userData,SoDragger* dragger);
    static void draggerFinishCB(void *userData,SoDragger* dragger);

    /// apply current transforamtion to  slices 
    void updateSlices();
	
    // DATA
    McHandle<SoSeparator> mDraggerRoot;
    McHandle<SoTransform> xform;

    McHandle<SoTransform> ivTransform;
    McHandle<SoSeparator> cursorRoot;

    /// 2D viewer
    QxLightBox mViewer;

    /// Hide displayed geometries.
    virtual void removeOverlay();

public:

    HxViewCursor();

    ~HxViewCursor();

    /// show ObliqueSlices?
    HxPortToggleList portShowSlices;

    /// creates all color ports
    HxMapToTexture colorPorts;

    /// current translation of dragger in plane.
    HxPortFloatTextN portTranslation;

    /// angle
    HxPortFloatSlider portRotation;

	/// Associated Cylinder Slice
	HxConnection portCylinderSlice;

    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// save viewer geometry
    virtual void savePorts(FILE *fp);

    /// add offset to primary input data and truncate negative values.
    void addOffset(HxField3* field, int offset);


	/// creates slice objects
	void createImage(const char* name1=0, const char* name2=0);

    /// Automatically connects to a scalar field.
    int autoConnect(HxObject* primary);

    int virtual parse(Tcl_Interp* t, int argc, char **argv);
};


#endif

/// @}

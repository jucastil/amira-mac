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

/// @addtogroup hxneuro hxneuro
/// @{
#ifndef _HX_VOLUME_TRANSFORM_
#define _HX_VOLUME_TRANSFORM_

#include <Inventor/manips/SoTransformManip.h>
#include <Inventor/sensors/SoNodeSensor.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoEventCallback.h>

#include <mclib/McData3D.h>
#include <mclib/McMat4f.h>
#include <mclib/McHandle.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortColorList.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxsurface/HxSurface.h>
#include <hxfield/HxUniformScalarField3.h>

class HxGLPolyLine;

class HxVolumeEdit : public HxCompModule {

  HX_HEADER(HxVolumeEdit);

public:
    struct EditAction : public McHandable {
        template <class T>
            EditAction(T* f) {
            clearedPixels.resize(f->lattice.nNodes());
            clearedPixels.unsetAll();
        }
        McBitfield clearedPixels;
    };

    McDArray<McHandle<EditAction> > undoStack;
    McDArray<McHandle<EditAction> > redoStack;

    void executeAction(HxVolumeEdit::EditAction* ea);

    EditAction* createEditAction();

    /// Default constructor.
    HxVolumeEdit();

    /// Default destructor.
    ~HxVolumeEdit();
  
    /// Invokes actual computation.
    virtual void compute();

    /// Additionally saves the manipulator if present
    virtual void savePorts(FILE *fp);

    /// Invokes actual computation.
    virtual void update();

    /// Port manipulators
    HxPortMultiMenu portManip;

    /// Zero level port
    HxPortFloatTextN portZero;

    /// if editing a label field this is for selection if padding label
    HxPortMultiMenu portPaddingLabel;

    HxPortColorList portPaddingColor;

    /// 
    HxPortButtonList portCutAction;

    /// 
    HxPortButtonList portRestoreAction;
    
    ///
    HxPortButtonList portEditAction;

    HxPortRadioBox portChannel;

    /// A button which creates a result object if necessary
    HxPortDoIt portCheckResult;

    bool checkResult();

    int parse(Tcl_Interp* t, int argc, char **argv);

protected:

    //Make 
    void doIt();
    int drawExterior;
    int copyMode;
    HxGLPolyLine* polyLine;
    HxField3* thedata;
    SoNodeSensor* sensor;
    McMat4f rot;
    int x[2], y[2], z[2];		//bounding box after the scale and transformation
    int xp[2],yp[2],zp[2];		//bounding box in the coordinate system
    int x0, y0, z0;		//coordinates of point 0 after rotation before new coordinate system
    int x1, y1, z1;		//coordinates of point 1 after rotation before new coordinate system
    int x3, y3, z3;		//coordinates of point 3 after rotation before new coordinate system
    int x4, y4, z4;		//coordinates of point 4 after rotation before new coordinate system
    void* restoredata;

    void setSensitivity();
    void restore();
    void undo();
    void redo();
    void createMask();
    void pushUndo(EditAction* ea);

    void debug();

    void cut(bool in, int copy);

    void setManip(int which);

    static void viewerSelectCB(void* userData);

    void viewerSelect();

    McHandle<SoTransformManip> manip;
    McHandle<SoSeparator> separator;
    McHandle<SoCoordinate3> coords;
    McHandle<SoSeparator> shape;

    //Computes the points for one wall (4 points)
    //void computePoints(int x, int y, int z, int dir);

    static void trackerEventCB(void* userData, SoEventCallback* node);

    bool mIsScalarField;
};

#endif


/// @}

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

/// @addtogroup hxtensor hxtensor
/// @{
#ifndef HXTENSORDISPLAY
#define HXTENSORDISPLAY

#include <mclib/McDArray.h>
#include <mclib/McDMatrix.h>
#include <Inventor/SbLinear.h>
#include <Inventor/nodekits/SoShapeKit.h>

#include <hxcore/HxPlanarMod.h>
#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcolor/HxPortColormap.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>
#include "HxTensorWinDLLApi.h"


class SoMFVec3f;
class SoMFUInt32;
class HxScalarField3;

/** The module will display the eigenvalue with different glyph based methods. */
class HXTENSOR_API HxTensorDisplay : public HxOverlayModule {

  HX_HEADER(HxTensorDisplay);
  
  public:
    /** Constructor. */
    HxTensorDisplay();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    HxConnection portROI;
    HxPortRadioBox port2D3D;
    HxPortRadioBox portDisplay;
    HxPortToggleList portOptions;
    HxPortMultiMenu portOptions2;
    HxPortToggleList portScaleOptions;
    HxPortFloatSlider portComplexity;
    HxPortIntTextN portResolution;
    HxPortColormap portColormap;
    HxConnection portColorField;
    HxConnection portMask;
    HxConnection portShape;
    HxConnection portSurface; /// a surface is used to sample the positions
    HxPortText portExpr;
    HxPortFloatSlider portOffset;
    HxPortFloatSlider portScale;
    
    /** Do it button. */
    HxPortDoIt portAction;
    
    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
    
 public:
    /** Destructor. */
    ~HxTensorDisplay();

    /// Save ports.
    virtual void savePorts(FILE* fp);

    /** draw lines for each eigenvektor additionally to the current display module */
    int showLines; 
    
    /** size of point to be drawn */
    float pointSizeValue;
    
    /** steepness of the sigmoidal remapping function for negative eigenvalues */
    float sigmoidSteepness;
    
 private:
    McHandle<SoSeparator> scene;
    void sort(McDArray<double> &evals,McDMatrix<double> &evects);
    int firstTimeFlag; // a flag that is reset the first time update is called with data
    float volumeModeSkip; /// < this defines the resolution of the drawing 1.0 is every voxel
    
 protected:
    McHandle<HxPlanarMod> background;
    SbVec3f orig, norm, uVec, vVec;
    float diagonal;
    int getTransform(SbMatrix& mat);
};
#endif

/// @}

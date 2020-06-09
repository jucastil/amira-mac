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
#ifndef HX_CONTRAST_H
#define HX_CONTRAST_H

#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>

#include <hxfield/HxField3.h>

#include <Inventor/nodes/SoAnnotation.h>
#include <Inventor/nodes/SoVertexProperty.h> 

#include "HxLatticeWinDLLApi.h"

class HxViewer;
class HxContrastInterfaceBase;

/// This class modifies the data window (contrast settings) of an OrthoSlice
class HXLATTICE_API HxContrast : public HxOverlayModule
{
    HX_HEADER(HxContrast);

  public:

    /// Constructor
    HxContrast (void);

    /// Returns portModule as primary port.
    virtual int autoConnect(HxObject* primary);

    /// Update method.
    virtual void  update (void);

    /// Compute method
    virtual void  compute (void);

    /// Info to current Contrast Settings
    HxPortInfo  portInfo;

    /// Input fields for window center and window width
    HxPortFloatSlider  portCenter;
    HxPortFloatSlider  portWidth;

    /// Mode: 0 = hide window, 1 = show window
    HxPortToggleList  portDisplay;

    /// X and Y position of Window Graph (pixel values)
    /// (0, 0) is lower left, negative values relative to right and top.
    HxPortIntTextN  portPosition;

    /// Tcl command interface.
    virtual int  parse (Tcl_Interp *t, int argc, char **argv);

  protected:

    /// Destructor of Class HxContrast
    virtual  ~HxContrast (void);

    /// Open Inventor callback for mouse picking
    static int  eventCB (const SoEvent *, HxViewer *, void *);
    int  eventCallback (const SoEvent *);

    /// Set window center or window width
    void  setWindowCenter (float center);
    void  setWindowWidth (float width);

    /// Line color adjustment
    void  setLineColor (int  red, int  green, int  blue);

    /// Mouse sensitivity control
    void setMouseSensitivity (float  factor) {
        mouseSensitivity = factor > 1.0 ? 1.0 : factor < 0.1 ? 0.1 : factor;
        mouseSensitivity *= (0.01 * dataRange);
    }

    /// Contrast adjustment
    void mapData (void);
    
    /// Display information of data range and data window
    void  setInfoText (void);

    /// Mapping type of the connected module has changed
    void  setMappingType (int);

    /// Range for linear mapping has changed
    void setLinearRange (HxContrastInterfaceBase* orthoSlice);

    /// Range of the connected data might have changed
    void  setDataRange (HxField3  *);

  private:

    // useful constants
    enum {HIDE, SHOW};
    enum {CENTER, WIDTH};
    enum {X, Y};
    enum {R, G, B};

    // verbose or quiet mode
    short    verbose;

    // these enums must be modified with portMappingType from orthoslice
    enum {HISTOGRAM=0 , COLOR, NUM_MAPPINGS};
    char    *mappingType[NUM_MAPPINGS];
    int      mappingTypeId;

    // window parameters (class globals)
    float    windowCenter;
    float    windowWidth;
    float    windowHalf;

    // visible flag and position of window graph
    int      displayFlag;

    // contrast window graph settings
    float    graphScale;
    float    rampStart;
    float    rampEnd;

    float    lineColor[3];

    // data range settings
    float    dataMin;
    float    dataMax;
    float    dataRange;

    // mouse properties
    float    mouseSensitivity;

    // internal callback handling
    void  registerEventCallback (void);
    void  unregisterEventCallback (void);

    short  eventCallbackRegistered;
    short  contrastAdjustment;

    SbVec2s  lastPosition;

    // for drawing window graphs within the viewer
    McHandle<SoAnnotation>  annotation;
    McHandle<SoVertexProperty> vertices;

    void  updateWindowGraph();
};

#endif // HX_CONTRAST_H

/// @}

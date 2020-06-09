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

/// @addtogroup hxisl hxisl
/// @{
#ifndef HX_SEED_LINE_H
#define HX_SEED_LINE_H

#include <Inventor/nodekits/SoWrapperKit.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/manips/SoTransformBoxManip.h>
#include <Inventor/draggers/SoTransformBoxDragger.h>
#include <Inventor/draggers/SoTabBoxDragger.h>
#include <Inventor/engines/SoElapsedTime.h>

#include <hxcore/HxModule.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonMenu.h>

#include <hxisl/HxDisplayISL.h>
#include <hxisl/FieldLineSet.h>

#include <mclib/McHandle.h>

class HxSurface;

/// Add-on for HxDisplayISL, allows to distribute line seed on a surface.
class HxSeedSurface : public HxModule {

    HX_HEADER(HxSeedSurface);
  
public:
    /// Constructor.
    HxSeedSurface();

    /// Destructor.
    ~HxSeedSurface();

    /// Fixes num lines if seed mode is "at vertices".
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Connects primary module (ISL) to portDisplayISL.
    virtual int autoConnect(HxObject* primary);

    /// Connection to display ISL module.
    HxTightConnection portDisplayISL;

    /// Number of field lines.
    HxPortFloatSlider portNumLines;

    /// Length of field lines.
    HxPortFloatSlider portLength;

    /// Controls whether field lines extend forward or backward.
    HxPortFloatSlider portBalance;

    /// Provides menu for seed mode (vertices/surface).
    HxPortButtonMenu portDistribute;
    enum { AT_VERTICES=0, ON_SURFACE=1 };

    // This contains the "DoIt" button.
    HxPortDoIt portDoIt;

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Implements save network feature.
    void savePorts(FILE* fp);
    
  protected:
    HxDisplayISL* disl;    
    FieldLineSet* fieldLineSet;

    void pointMode(HxSurface*);
    void surfaceMode(HxSurface*, int nLines);
};

#endif

/// @}

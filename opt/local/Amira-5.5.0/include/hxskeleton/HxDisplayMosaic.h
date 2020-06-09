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

/// @addtogroup hxskeleton hxskeleton
/// @{
#ifndef HX_DISPLAY_MOSAIC_H
#define HX_DISPLAY_MOSAIC_H

#include "HxMosaic.h"
#include <hxcore/HxModule.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortDoIt.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodekits/SoShapeKit.h>

/// This module displays the bounding box of any spatial data object.
class HXSKELETON_API HxDisplayMosaic : public HxModule {

  HX_HEADER(HxDisplayMosaic);

  public:
    /// Constructor.
    HxDisplayMosaic();

    ///
    HxPortIntSlider portBrick;

    /// Toggles display of bbox values in the 3D viewer.
    HxPortToggleList portText;

    /// load block
    HxPortDoIt portAction;

    /// Compute method.
    virtual void compute();

    /// Tcl-comand interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    ///
    void setLineWidth (float width);

    /// Returns the line width of the bounding box or 0.0
    /// if no bounding box could be found.
    float getLineWidth();

  protected:
    virtual ~HxDisplayMosaic();

    McHandle<SoSeparator> oivRoot;
    McDArray<McHandle<SoShapeKit> > oivBoxes;

    void makeBox(int i, const float* b, SbMatrix* trans);
    void setNoBoxes (int size);
    void highlight (int n);

    float lineWidth;
};

#endif // HX_BOUNDING_BOX

/// @}

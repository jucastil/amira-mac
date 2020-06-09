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

/// @addtogroup hxtetra hxtetra
/// @{
#ifndef HX_SHOW_CONTOURS_H
#define HX_SHOW_CONTOURS_H

#include <hxtetra/HxTetraWinDLLApi.h>
#include <mclib/McDArray.h>
#include <hxcore/HxPlanarMod.h>
#include <hxcore/HxOverlayModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortText.h>
#include <hxcolor/HxPortColormap.h>

#include <Inventor/SbLinear.h>
#include <Inventor/nodekits/SoShapeKit.h>

class SoMFVec3f;
class SoMFUInt32;
class HxScalarField3;

/// This module draws contours of a label field on top of an arbitrary plane.

class HXTETRA_API HxShowContours : public HxOverlayModule {

  HX_HEADER(HxShowContours);

  public:
    /// Constructor.
    HxShowContours(GraphicalRepMgtType graphicalRepMgtType = MANAGED_BY_BACKGROUND_MOD);

    /// Update method shows/hides some ports.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Parameters: 0=resolution of sample grid, 1=line width.
    HxPortFloatTextN portParameters;

    /// Colormap to be used.
    //    HxPortColormap portColormap;

    /// Parse method
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    enum Parameters { RESOLUTION=0, LINEWIDTH=1 };

    enum Options { UPDATEMINMAX=0, RESAMPLE=1 };

  protected:
    // Destructor.
    virtual ~HxShowContours();

    // Inventor shape kit containing a line set node
    McHandle<SoShapeKit> shapeKit;

    // Scaled plane vectors
    SbVec3f orig, norm, uVec, vVec;

    // Array containing colors of all iso-values.
    McDArray<unsigned int> isoRGBA;

    // Inventor field containing all vertices.
    SoMFVec3f* vertex;
    int nMaxVertices, nVertices;

    // Inventor field containing all color tuples.
    SoMFUInt32* orderedRGBA;
    int nMaxOrderedRGBA, nOrderedRGBA;

    // Diagonal of data set's bounding box
    float diagonal;

    // Required for coord adjustment in case of transformations.
    SbMatrix mat;

  protected:
    void showContours();
    void doGeneric();
    int getTransform(SbMatrix& mat);

    /// Hide displayed geometries.
    virtual void removeOverlay();
};

#endif

/// @}

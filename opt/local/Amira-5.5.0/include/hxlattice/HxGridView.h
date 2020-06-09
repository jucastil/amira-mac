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
#ifndef HX_GRID_VIEW
#define HX_GRID_VIEW

#include <mclib/McHandle.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxRegVectorField3.h>
#include <hxfield/HxRegComplexVectorField3.h>

#include <Inventor/nodekits/SoShapeKit.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoQuadMesh.h>
#include <Inventor/nodes/SoVertexProperty.h>

/// This module display slices of a regular grid in wireframe.

class HxGridView : public HxModule {

  HX_HEADER(HxGridView);
  
  public:
    /// Constructor.
    HxGridView ();

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /// Saves ports and other settings
    virtual void savePorts(FILE* fp);

    /// Determines orientation of slice to be extracted (xy, xz, yz).
    HxPortRadioBox portOrientation;

    /// Whether to use coordinate information or the data.
    HxPortRadioBox portDataMode;

    /// Scale factor in coord + data value mode.
    HxPortFloatSlider portScale;

    /// Determines slice number.
    HxPortIntSlider portSliceNumber;

  protected:
    ~HxGridView();

    int lineMode;
    McHandle<SoShapeKit> shapeKit;
    McHandle<SoVertexProperty> vertexProperty;
    McHandle<SoIndexedLineSet> indexedLineSet;
    McHandle<SoQuadMesh> quadMesh;
};

#endif

/// @}

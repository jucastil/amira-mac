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

/// @addtogroup hxiso hxiso
/// @{
#ifndef HX_ISOHEXA_H
#define HX_ISOHEXA_H

#include <hxiso/HxIsoWinDLLApi.h>

#include <mclib/McVec3f.h>
#include <mclib/McDArray.h>
#include <hxsurface/HxTriBase.h>

#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxConnection.h>

class HxHexaScalarField3;
class HxHexaGrid;

/** This class implements isosurface algorithms for scalar fields
    on unstructured hexahedral grids. */

class HXISO_API HxIsoHexa : public HxTriBase {

  HX_HEADER(HxIsoHexa);

  public:
    /// Default constructor.
    HxIsoHexa();

    /// Updates user interface even when module is disabled.
    virtual void update();

    /// Invokes actual computation.
    virtual void compute();

    /// Threshold of the isosurface.
    HxPortFloatSlider portThreshold;

    /// check wether or not to average cell based fields.
    HxPortToggleList portAverage;

    /// Do it button.
    HxPortDoIt portAction;

    /// Tcl-commands interface.
    int parse(Tcl_Interp* t, int argc, char** argv);

    /// Save sate method.
    virtual void savePorts(FILE* fp);

  protected:
    virtual ~HxIsoHexa();

    HxHexaScalarField3* field;
    HxHexaGrid* grid;

    float threshold;
    float* scalarData;
    // Remember 8-bit table index of last voxel here.
    unsigned int index;

    // Was computeSurface() called after last parameter change?
    int surfaceUpToDate;

    void computeSurface();
    void computeSurfaceMC();
    void computeSurfacePerCell();

    unsigned int computeIndex(int* cellpoints);
    McVec3f computeIntersection(int* cellpoints, int e);

    McDArray<float> averagedData;
    void average(HxHexaScalarField3* field);
};

#endif


/// @}

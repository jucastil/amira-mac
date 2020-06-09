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

/// @addtogroup hxsurftools hxsurftools
/// @{
#ifndef HX_GET_CURVATURE_H
#define HX_GET_CURVATURE_H

#include <math.h>
#include <stdio.h>
#include <mclib/McBitfield.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxsurface/HxSurface.h>
#include <hxsurftools/HxSurfToolsWinDLLApi.h>

/// Computes linear superposition from multiple electromagnetic fields.
class HXSURFTOOLS_API HxGetCurvature : public HxCompModule {

  HX_HEADER(HxGetCurvature);

  public:
    /// Constructor.
    HxGetCurvature();

    /// Compute method.
    virtual void compute();

    /// Method: 0=on triangles, 1=on vertices
    HxPortRadioBox portMethod;

    /// Specifies nLoops and nLayers parameters.
    HxPortIntTextN portParam;

    /// Combo box specifying the result type.
    HxPortMultiMenu portOutput;

    /// Supported curvature result types.
    enum Mode {
        /// Max curvature.
        MODE_MAX=0,
        /// Inverse max curvatute.
        MODE_MAX_INV=1,
        /// Mean curvature.
        MODE_MEAN=2,
        /// Inverse mean curvature.
        MODE_MEAN_INV=3,
        /// Gauss curvature.
        MODE_GAUSS=4,
        /// Inverse Gauss curvature.
        MODE_GAUSS_INV=5,
        /// Both curvature values (complex field).
        MODE_BOTH=6,
        /// Both inverted curvature values (complex field).
        MODE_BOTH_INV=7,
        /// Max curvature vector (vector field).
        MODE_MAX_VECTOR=8,
        /// Both curvature vectors (complex vector field).
        MODE_BOTH_VECTORS=9,
        /// Shape Index
        MODE_SHAPEINDEX=10,
        /// Curvedness
        MODE_CURVEDNESS=11
    };

    /// Do it button.
    HxPortDoIt portAction;

    /// Parse method
    int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    ~HxGetCurvature();

    int canCreate;
    void doVectors(HxSurface*);
    void doVectors2(HxSurface*);
    void doCurvature(HxSurface*, int outputMode);
    void doCurvature2(HxSurface*, int outputMode);
    void fixOrientations(HxSurface*, McVec3f* vec);
    void fix(HxSurface*, McVec3f* vec, int n, McBitfield&);
    virtual int canCreateData(HxData* data, McString& createCmd);

  public:

    /// computes curvature encoded on triangles of surface
    static void getCurvature(Surface* surface, float* curvatures, McVec3f* vectors,
                             int mode, int nLayers, int nLoops);

    /// computes curvature encoded on vertices of surface
    static void getCurvature2(Surface* surface, float* curvatures, McVec3f* vectors,
                              int mode, int nAverage);
};

#endif

/// @}

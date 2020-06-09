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
#ifndef HX_SURFACEISOLINES_H
#define HX_SURFACEISOLINES_H

#include <hxsurftools/HxSurfToolsWinDLLApi.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcolor/HxPortColormap.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodekits/SoShapeKit.h>
#include <hxsurftools/HxSurfaceScalarField.h>
#include <hxsurftools/HxSurfaceVectorField.h>

#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoCoordinate3.h>


class HxSurfaceIsoGraph;
class HxSurface;
class HxLineSet;

/** This module draws contour lines of a tetrahedral scalar field on
    top of a planar slice. */
class HXSURFTOOLS_API HxSurfaceIsolines : public HxModule {

  HX_HEADER(HxSurfaceIsolines);

  public:
    /// Constructor.
    HxSurfaceIsolines();


    /// Update method shows/hides some ports.
    virtual void update();

    /// Compute method.
    virtual void compute();


    /// Indicates how isoline are defined, uniformly or explicitly.
    HxPortRadioBox portSpacing;

    /// Value of first and last isoline, total number of isolines.
    HxPortFloatTextN portUniform;
    
    /// Slider to choose an isovalue explicitly
    HxPortFloatSlider portIsovalue;
    /// Offsets to add from value selected in Slider.
    HxPortText portOffsets;

    /// Explicit definition of all isolines.
    HxPortText portExplicit;

    /// Parameters: 0=resolution of sample grid, 1=line width.
    HxPortFloatTextN portParameters;

    /// Options: 0=update min-max, 1=resample tetrahedral grid.
    HxPortToggleList portOptions;

    /// Colormap to be used.
    HxPortColormap portColormap;

    /// Parse method
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    enum Parameters { LINEWIDTH=0 };

    enum Options { UPDATEMINMAX=0 };

    HxLineSet* exportAsLineSet();
    void resetIsoGraphs (bool makeNew = true);
    void addToLineSet(HxLineSet* lineset);

    McDArray<HxSurfaceIsoGraph*> &getIsoGraphs () { return isoGraphs; };
    McDArray<float> getIsoValues () { return isoValues; };

  protected:
    virtual ~HxSurfaceIsolines();

    HxSurfaceField *field;
    HxSurface      *grid;
    SoShapeKit	   *shape;
    SoLineSet	   *lineSet;
    McDArray<float> isoValues;

    HxSurfaceField::Encoding       encoding;

    // Indicates if range should be reset if a new data object is attached.
    unsigned int resetRangeFlag:1;

    void computeIsolines();

    void determineIsoValues();

    void isolineOnNodes();

    void isolineOnTriangles();

    void isolineOnTriangleNodes();

    void resetRange(HxSurfaceField* field);


  private:

    void isoTri(const HxSurface::Triangle& tri, 
                int nDataVar, float* data[3]);

    int isoEdge(const HxSurface::Edge& edge, int t1, int t2, 
                float *data, int nDataVar);

    SbColor color;
    HxColormap *colormap;
    float minCoord, coordWidth;
    int nVertex, nColor;
    SoMaterial *material;
    SoCoordinate3 *coords;
    int usePortValues;
    McDArray<HxSurfaceIsoGraph*> isoGraphs;

};

#endif

/// @}

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
#ifndef HX_ScanConvertSurface2_H
#define HX_ScanConvertSurface2_H

#include <mclib/McProgressInterface.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>

#include <mclib/McVec2i.h>
#include <mclib/McVec3f.h>

#include "HxSurfToolsWinDLLApi.h"

class HxSurface;
class HxLabelLattice3;
class HxUniformLabelField3;
class HxStackedLabelField3;
class HxRegScalarField3;
class HxCoord3;

/** This class converts closed manifold surfaces to a uniform label field */

class HXSURFTOOLS_API ScanConvertSurface {
    
protected:
    McDArray<short> surfacePointLabels;
    McDArray<short> edgePointLabels;
    McDArray<int>   markEdges;
    McDArray<McVec3f> pointsOnEdges;
    McDArray<McVec2i> contourEdges;
    McDArray<float> intersectionPoints;
    McBitfield markPoints;
    McBitfield markTriangles;
    McProgressInterface * progressInterface;
    
public:
    bool interactive;
    bool isManifold;
    int material;
    
public:
    /// Constructor.
    ScanConvertSurface();
    /// Constructor.
    ~ScanConvertSurface();

    /** Set progress interface. */
    void setProgressInterface(McProgressInterface * progressInterface);

    /** label points depending on their coordinates 
        orient = 2: label surface points depending on their z-coordinates
        orient = 1: label points on edges depending on their y-coordinates 
        lattice: only necessary for z-computation in stacked label fields */
    void labelPointsByCoord(HxSurface* surface, int orient, int dim, 
                            float min, float max,
                            HxCoord3* coords = 0);
    
    /** find edges intersecting given slice 
        orient = 2: find surface edges intersecting slice z = z(k)
        orient = 1: find contour edges intersecting slice y = y(k) */
    void findIntersectingEdges(HxSurface* surface,
                               int orient, int k,
                               float coord);

    /** create contours for intersection of surface with slice
        z = z(k) */
    void createContours(HxSurface* surface, int mat);

    /** Function to scan-convert a surface to a label field, a
        pointer to which will be returned by the function. If you want
        to compute the voxel overlap with some label field (@c
        labelField2), make sure to take the dimension and bounding box
        of this label field. Otherwise, the bounding box and
        dimensions should be chosen according to the surface. In @c 
        volumeOverlap the number of overlapping voxels will be stored. */
    HxUniformLabelField3 * 
    scanConvertSurface(HxSurface* surface, int dims[3], float bb[6],
                       int & volumeOverlap,
                       HxUniformLabelField3 * labelField2=0);
    /** Same as above, but takes a pointer to the labels as input. 
        It is assumed, that @c labels points to a field of the correct size
        given by @c dims. Thus, this function allows to scan-convert a surface
        without creating an HxObject. 

        If the scan-conversion fails, false is returned, true otherwise. */
    bool 
    scanConvertSurface(HxSurface* surface,
                       unsigned char * labels,
                       int dims[3], float bb[6],
                       int & volumeOverlap,
                       HxUniformLabelField3 * labelField2=0);

    /** More general version of the above. Can handle stacked coordinates.
        It uses a HxCoord3 object instead of a fixed voxelsize to compute the z
        location of the label voxels.

        The result returned HxRegScalarField3 is either a HxUniformLabelField3
        or a HxStackedLabelField3 depending on the coordinate's type.
        If the scanconvertion fails 0 is returned.
    */
    HxRegScalarField3 * 
    scanConvertSurface(HxSurface* surface, HxCoord3 * coords,
                       int & volumeOverlap,
                       HxRegScalarField3 * labelField2=0);
};    

/** Amira module for scanconverting a surface into a labelfield. */

class HXSURFTOOLS_API HxScanConvertSurface : public HxCompModule {

    HX_HEADER(HxScanConvertSurface);
    
public:
    /// Constructor.
    HxScanConvertSurface();

    /// Optional reference field specifying bbox and dimensions.
    HxConnection portField;

    /// Bounding box of resulting field.
    HxPortFloatTextN portBBox;

    /// Dimensions of resulting field.
    HxPortIntTextN portDimensions;
    
    /// Material List: scan all or one specific material
    HxPortMultiMenu portMaterials;

    /// Options: compute volume overlap
    HxPortToggleList portOptions;

    /// DoIt button.
    HxPortDoIt portAction;
    
    /// Update method.
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// TCL parse method.
    int parse(Tcl_Interp* t, int argc, char **argv);

protected:

    void doIt(int interactive);
    
    ScanConvertSurface scanConverter;

    ~HxScanConvertSurface();

};

#endif

/// @}

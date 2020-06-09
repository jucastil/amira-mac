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
#ifndef _HX_GMClargeLabel_
#define _HX_GMClargeLabel_

#include <hxsurftools/HxSurfToolsWinDLLApi.h>

#include <mclib/McDArray.h>
#include <mclib/McBitfield.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxfield/HxCoord3.h>

class SoShapeKit;
class SoShapeHints;
class SoMaterialBinding;
class SoMaterial;
class SoNormalBinding;
class SoIndexedFaceSet;
class SoCoordinate3;
class SoNormal;
class HxUniformCoord3;
class HxStackedCoord3;
class HxSurface;
class Surface;

/// This class implements isosurface algorithms for regular scalar fields.

class HXSURFTOOLS_API HxGMC : public HxCompModule {

  HX_HEADER(HxGMC);

  public:
    /// Default constructor.
    HxGMC();

    /// Invokes actual computation.
    virtual void compute();

    /// Sets values of option port.
    virtual void update();

    /// Options: 0=none, 1=use weights, 2=constr smoothing, 3=unconstr sm.
    HxPortMultiMenu portSmoothing;

    /// Options: 0=subvoxel accuracy, 1=add border, 2=compact cubes.
    HxPortToggleList portOptions;
    enum { SUBVOXEL_ACCURACY=-1, ADD_BORDER=0, COMPACT_CUBES=1 };

    /// Border: 0=adjust coords, 1=extra material
    HxPortToggleList portBorder;
    enum { ADJUST_COORDS=0, EXTRA_MATERIAL=1 };

    /// Edges smaller than given threshold are removed (range 0...1)
    HxPortFloatTextN portMinEdgeLength;

    /// Material List: for individual reconstruction of labels
    HxPortMultiMenu portMaterialList;

    /// Material list for selecting a material for which a smooth
    /// surface should be generated
    HxPortMultiMenu portSmoothMaterial;

    /// Do it button.
    HxPortDoIt portAction;

    /// Parse method.
    int parse(Tcl_Interp* t, int argc, char **argv);

    inline int getV(int i, void* ptr);

  protected:
    //void addEmptyBorder(unsigned char* dest, unsigned char* src, const int* srcdims,int emptyId);

    void createPatches(Surface *surface);
    void removePatch(Surface* surface, int mat1, int mat2);
    void adjustCoordinates(Surface* surface, int, const int*, HxCoord3*, bool checkAllPoints);
    void rescaleUniform(HxSurface* surface, HxUniformCoord3*, const int*);
    void rescaleStacked(HxSurface* surface, HxStackedCoord3*, const int*);
    void removeExterior2(HxSurface* surface, int exterior2);
    void simplify(Surface* surface);
    void compactify(HxSurface* surface, const int* dims, int smoothMat);

    static void weldVertices(HxSurface* surface, McBitfield&, float minLength);

    void relabel(int oldLabel, int& newLabel, int* table, int tableInv[8]);

    unsigned short castPtr(void* ptr);

    ~HxGMC();

    void doIt(int interactive=1);

    int faceShiftPolicy;
    float adjustCoordsShift;
    int useMaterialList;
    int isLabelLattice;
    int isByte;

    // temporary storage for labels and weights if computed as part
    // of the gmc calculation
    void* myLabels;
    unsigned char* myWeights;

    virtual int canCreateData(HxData* data, McString& createCmd);
};


  inline int HxGMC::getV(int i, void* ptr)
{
    if (isByte)
        return ((unsigned char*) ptr)[i];
    else
        return ((short*) ptr)[i];
}

#endif

/// @}

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

/// @addtogroup hxvector hxvector
/// @{
#ifndef HX_STREAM_SURF_H
#define HX_STREAM_SURF_H

#include <hxvector/HxVectorWinDLLApi.h>
#include <mclib/McHandle.h>
#include <mclib/McODE3.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPort3DPointList.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxfield/HxVectorField3.h>
#include <hxsurface/HxSurface.h>
#include <hxcolor/HxPortColormap.h>

#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoDrawStyle.h>
#include <Inventor/nodes/SoLightModel.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoIndexedFaceSet.h>
#include <Inventor/nodes/SoIndexedLineSet.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoPackedColor.h>

/// This module displays a triangular grid.

class HXVECTOR_API HxStreamSurf : public HxCompModule {

  HX_HEADER(HxStreamSurf);
  
  public:
    /// Constructor.
    HxStreamSurf();

    /// Compute method.
    virtual void compute();

    /// Parse method.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    HxPortColormap portColormap;

    /// This defines the position of the seed.
    HxPort3DPointList portOrigin;

    /// Controls the resolution of the surface (exponent, 0=default).
    HxPortFloatSlider portResolution;

    /// Lengths: 0=forward 1=backward 2=width of seed line
    HxPortFloatTextN portLength;

    /** Action and seed control. Buttons: 0=Add to surface, 1=Clear surface,
	Seed: 0=binormal, 1=principal normal, 2=x, 3=y, 4=z */
    HxPortButtonMenu portAction;

    /// save port and other settings to file
    virtual void savePorts(FILE* fp);

  protected:
    ~HxStreamSurf();

    int nCoordIndex;
    int orientation;
    float tolerance;
    float center[3];
    float radius2;
    HxLocation3* loc;
    HxVectorField3* field;
    float toleranceSL;
    int doLineSet;
    int nCoords;

    McHandle<SoSeparator> shapeKit;
    McHandle<SoDrawStyle> drawStyle;
    McHandle<SoLightModel> lightModel;
    McHandle<SoMaterial> material;
    McHandle<SoCoordinate3> coordinate3;
    McHandle<SoPackedColor> packedColor;
    McHandle<SoIndexedFaceSet> indexedFaceSet;
    McHandle<SoIndexedLineSet> indexedLineSet;

    void initializeFront(McVec3f& origin, int& nPoints, int& isClosed);
    void propagate(int n, int isClosed);
    void addLine(int idx1, int idx2);
    void addTriangle(int idx1, int idx2, int idx3);

    void clearResult();
    void addToResult();

    int isOutside(McVec3f& r);
    static int tangent(const McVec3f& r, McVec3f& f, void* userData);
    static int torsion(const McVec3f& r, McVec3f& f, void* userData);

    struct Tracer {
	McODE3 ode;
	int stop;
	int indexOfLastPoint;
	int indexOfCurrentPoint;
	int indexOfTerminatedPoint;
    };
};

#endif

/// @}

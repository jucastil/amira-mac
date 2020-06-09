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
#ifndef HX_DISPLAYTETRAVECTORS_H
#define HX_DISPLAYTETRAVECTORS_H

#include <hxcore/HxModule.h>
#include <hxcore/HxTightConnection.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortMultiMenu.h>

#include <hxcolor/HxPortColormap.h>

#include <hxfield/HxTetraGrid.h>

#include <mclib/McBitfield.h>

#include <Inventor/SoType.h>

#include "HxTetraWinDLLApi.h"

class SoShapeKit;
class SoLineSet;
class SoIndexedLineSet;
class SoPointSet;
class SoCoordinate3;
class SoMaterial;
class SoMaterialBinding;
class SoPackedColor;
class SoDrawStyle;

class HxField3;
class HxGridVolume;
class HxGridBoundary;

/// Produces an arrow plot of a vector field defined on a tetrahedra grid
class HXTETRA_API HxDisplayTetraVectors : public HxModule {

  HX_HEADER(HxDisplayTetraVectors);

  public:
    /// Constructor.
    HxDisplayTetraVectors();

    // ???
    virtual void fire();

    /// Update method (show/hide ports).
    virtual void update();

    /// Compute method.
    virtual void compute();

    /// Autoconnect.
    virtual int autoConnect(HxObject* primary);

    /// Connection to grid volume module (used to select tetrahedra)
    HxTightConnection portModule;

    /// save port and other settings to file
    virtual void savePorts(FILE* fp);

    /// Tcl-command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:
    HxDisplayTetraVectors(SoType type); // for use by derived classes

    virtual ~HxDisplayTetraVectors();

    HxPortColormap	portColormap;
    HxPortFloatSlider   portScaleSize;
    HxPortToggleList	portMode;
    HxPortRadioBox	portShow;
    HxPortAnimatedFloat	portProjection;

    HxGridVolume*       gridVolume;
    HxGridBoundary*     gridBoundary;
    HxField3*		field;
    HxTetraGrid*	grid;
    HxTetraGrid*	gvGrid;
    McVec3f*            coords;
    HxTetraGrid::Triangle* triangles;
    float*              theData;
    int                 nTriangles;
    int                 nSelTriangles;
    McBitfield          triSelection;

    SoLineSet*  	lineSet;
    SoSeparator*	lineShape;
    SoMaterialBinding*  lineMatBinding;
    SoPackedColor*	lineColor;
    SoDrawStyle*	lineStyle;

    SoPointSet*	    	pointSet;
    SoShapeKit*	    	pointShape;

    int			nCoords;
    float		commonScale;
    SbBool		doNoScaling;
    SbBool		doDrawArrows;
    SbBool		doLogScale;
    SbVec3f		orig;
    float		diagonal;
    float		maxComponent;
    float               inputBox[6];
    float               sinPhi, cosPhi;

    void commonInit();
    int drawVectors();

    
    void render(const float* pos, float* vec, SbVec3f*& vertexPtr, SbVec3f*& pointPtr, unsigned int*& colorPtr);
};

#endif

/// @}

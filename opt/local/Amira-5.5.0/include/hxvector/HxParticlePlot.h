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
#ifndef PARTICLEPLOT_H
#define PARTICLEPLOT_H
 
#include <mclib/McHandle.h>
#include <Inventor/nodes/SoCone.h>
#include <Inventor/nodes/SoSeparator.h>

#include <anna/AnnaExpression.h>

#include <hxcore/HxThread.h>
#include <hxcore/HxModule.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxtime/HxPortTime.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxRoiInterface.h>

#include <hxcolor/HxPortColormap.h>
#include <hxlines/HxLineSet.h>
#include <hxisl/FieldLineSet.h>
#include <hxisl/ParticleSet.h>
#include <hxisl/Particle.h>

#include <hxvector/HxVectorWinDLLApi.h>

class HxLineSet;

/** Represents a display modul which can be applied to vector fields. */
class HXVECTOR_API HxParticlePlot : public HxModule {

    HX_HEADER(HxParticlePlot);

  public:
    /// Constructor.
    HxParticlePlot();

    /// Destructor.
    ~HxParticlePlot();

    /// Updates the display.
    virtual void update();

    /// Recomputes time point 0.
    virtual void compute();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
    void addCone(int whichSceneGraph, SbVec3f *where, SbVec3f *whichDirection, float scale);
    void savePorts(FILE *fp);

    bool validSceneGraph();
    void createMySceneGraph();
    void createMySceneGraphFromLineSet();

    FieldLineSet * fieldLineSet;
    ParticleSet* particles;
    HxVectorField3 * vectorField;
	HxScalarField3 * colorField;
	HxConnection portROI;
	HxConnection portShape;
	HxConnection portDistField;
	HxConnection portColorField;
    // HxConnection portLineSet;

    HxPortButtonMenu portDistribute;
	HxPortIntTextN portResolution;
	HxPortColormap portColormap;
    HxPortIntTextN portOptions;
    HxPortFloatTextN portOptions2;
	HxPortText portThreshold;
    HxPortTime portAnimate;
    SoNode *cone;   
	bool recomputeScene;
	float currentMaxMagnitude; /// < the maximum magnitude of the vector field
	float currentMagnitude;    /// < the magnitude of the last validPoint test
    float currentColorValue;
	HxPortDoIt        portDoIt;
 private:
    bool doRedistribute;
	bool validPoint(SbVec3f *where, HxLocation3 *locV, HxLocation3 *locC);
    bool validPointLineSet(SbVec3f *where, HxLocation3 *locColor);
	void prepareGeometry();
	HxLineSet *createLineSet();
	SoTransform *shapeTransform;

    /// Internal data structures to store the scenes.
//    McHandle<SoSeparator> scene;
    McDArray<McHandle<SoSeparator> > scenes;
	int stepstoblend; /// < the number of time steps we will use to blend out the objects
    
    AnnaExpression mExpr;
    bool mExprIsValid;

    McDArray<double> mVarVals;
};

#endif

/// @}

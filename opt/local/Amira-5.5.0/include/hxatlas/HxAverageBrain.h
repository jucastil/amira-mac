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

/// @addtogroup hxatlas hxatlas
/// @{
#ifndef HX_AVERAGE_H
#define HX_AVERAGE_H

#include "hxatlasAPI.h"
#include <Inventor/nodes/SoTransform.h>
#include <Inventor/nodes/SoCoordinate3.h>
#include <Inventor/nodes/SoLineSet.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoSeparator.h>
#include <mclib/McHandle.h>

#include <hxfield/HxUniformScalarField3.h>

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortOptionMenu.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>

#include <hxcore/HxPortButtonList.h>

class HxRegScalarField3;

/// Uses an analytic expression to compute a new field

class HXATLAS_API HxAverageBrain : public HxCompModule {

  HX_HEADER(HxAverageBrain);

  public:
    /// Constructor.
    HxAverageBrain();

    /// Compute method.
    virtual void compute();

    /// Update method.
    virtual void update();

    ///
    HxPortOptionMenu portMode;

    HxPortIntTextN portMaterial;

    ///
    HxPortText portTransform;

    ///
    HxPortText portFiles;
   
    /// Do it button.
    HxPortButtonList portChoose;
    
    ///
    HxPortDoIt portAction;
    
    /// Tcl command interface
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  protected:

    virtual int canCreateData(HxData* data, McString& createCmd);
    
    template <class T> void computeMoments(HxUniformScalarField3* templ);    
    void addGeom();

    template< class T> void computeIt( HxUniformScalarField3 *templ);

    virtual ~HxAverageBrain();
    void chooseTransform(int n,HxUniformScalarField3* field,
			 const char* transName);
    void getTransform(HxUniformScalarField3* templ,
		      HxUniformScalarField3* field,
		      SbMatrix& local0ToLocalI,
		      SbVec3f& stepVec);

    McDArray<const char*> transformNames;
   
    
    int n;
    float optimum ;
    int resolutionLevel;
    int stopWorking;
    int verbose;
    float defaultA; // default values for inputA, inputB, inputC,
    float defaultB; // if set() or move() fail
    
    McHandle<SoSeparator> sep;
    McHandle<SoLineSet> ls;
    McHandle<SoCoordinate3> coords;
    McHandle<SoMaterial> material;
    
    SbVec3f center;
    SbVec3f moments[3];
    float eigval[3];
    
   
};

#endif

/// @}

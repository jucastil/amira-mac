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

/// @addtogroup hxmoledit hxmoledit
/// @{
#ifndef HX_MolElectrostatics_H
#define HX_MolElectrostatics_H

#include <Inventor/draggers/SoDragger.h>

#include "HxMolEditWinDLLApi.h"
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortButtonMenu.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortInfo.h>

#include "MolBoxDragger.h"

class SbVec3f;
class HxUniformVectorField3;
class HxUniformScalarField3;
class HxSurfaceScalarField;
class HxSurfaceVectorField;
class SoSeparator;

class MolElectrostatics;
class HxMolecule;

/** This class implements the amira interface for the poisson solver
**/

class HXMOLEDIT_API HxMolElectrostatics : public HxCompModule {

    HX_HEADER(HxMolElectrostatics);
    
public:
    /// Constructor.
    HxMolElectrostatics();
  
    /// Destructor.
    virtual ~HxMolElectrostatics();

    
    /// Update method.
    virtual void update();
    
    /// Compute method.
    virtual void compute();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
    
    HxConnection portSurfaceField;
    
    HxConnection portSurface;
    
    HxPortDoIt portAction;

    HxPortFloatSlider portDielectrical;

    HxPortRadioBox portCalcType;

    HxPortRadioBox portOutputType;
    
    HxPortSeparator portSep1;

    HxPortText portChargeAttributeName;

    HxPortSeparator portSep2;

    PortFieldDimension portFieldDimension;

    /// This function does the actual computation.
    void doIt();
      
protected:

    MolBoxDragger box;

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);
    
    // creates a regular scalar field on a grid as specified by the
    // ports and the boxdragger which contains the potential for each grid point
    HxUniformScalarField3* createPotentialField() const;
    HxUniformVectorField3* createEField() const;
    HxSurfaceScalarField* createPotentialSurfaceField() const;
    HxSurfaceVectorField* createESurfaceField() const;

    MolElectrostatics * me;

    HxSurfaceScalarField * surfField;
    HxMolecule* mol;

};

#endif

/// @}

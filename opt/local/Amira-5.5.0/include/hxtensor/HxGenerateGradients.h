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

/// @addtogroup hxtensor hxtensor
/// @{
#ifndef HXGENERATEGRADIENTS
#define HXGENERATEGRADIENTS

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortText.h>
#include <hxcore/HxThread.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxRegComplexVectorField3.h>
#include <hxfield/HxRegSym2TensorField3.h>
#include <hxfield/HxRegVectorField3.h>
#include <hxfield/HxUniformVectorField3.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxLattice3.h>
#include <mclib/McDMatrix.h>
#include <mclib/McDArray.h>

#include <anna/AnnaExpression.h>

#include "HxTensorWinDLLApi.h"

#include <Inventor/elements/SoElements.h>
#include <Inventor/sensors/SoTimerSensor.h>

/** This module generates gradient weighted images from a symmetric
    second order tensor field. 
  */
class HXTENSOR_API HxGenerateGradients : public HxCompModule {

  HX_HEADER(HxGenerateGradients);
  
  public:
    /** Constructor. */
    HxGenerateGradients();

    /** Compute method. */
    virtual void compute();

    HxConnection portMask;
    HxPortFloatTextN portGradient;
    HxPortFloatTextN portBValue;
    HxPortRadioBox portMode;
    HxPortFloatTextN portScale;

    /** Port for selecting a material or a group of materials. */ 
    HxPortText portExpr;

    /** Do it button. */
    HxPortDoIt portAction;

    virtual void update();

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

  public:

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    /// Save ports.
    virtual void savePorts(FILE* fp);

    void createGradient(HxRegSym2TensorField3 *field,
                        HxRegScalarField3 *mask,
                        HxRegScalarField3 *output,
                        McVec3f gradient);

    // computes the bilinear form u^T B u
    template<typename T>
    static double bilinearForm(McDMatrix<T> B, McDArray<T> u);

  private:
    AnnaExpression mExpr;
};
#endif

/// @}

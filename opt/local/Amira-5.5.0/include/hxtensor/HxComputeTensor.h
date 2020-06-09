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
#ifndef HXCOMPUTETENSOR
#define HXCOMPUTETENSOR

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <mclib/McDMatrix.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>
#include "HxTensorWinDLLApi.h"

/** Class computing the tensor from the gradient data for DT-MRI.
    The implementation is based on the paper by Westin et al 2002. */
class HXTENSOR_API HxComputeTensor : public HxCompModule {

  HX_HEADER(HxComputeTensor);

  public:
    /** Constructor. */
    HxComputeTensor();

    /** Update method. */
    virtual void update();

    /** The result will be represented as a complex scalar field
    this is _not_ a complex vector field but merely a convienient
    way to store the 6 degrees of freedom in a symmetric 3x3 matrix.
    This implementation is using the Westin02 solution for calculating the tensor.
    The individual tensor components can be optained from the resulting
    6 element field (a complex vector field) by extracting single channels
    the channels are (in order): Dxx, Dxy, Dxz, Dyy, Dyz, Dzz. */
    virtual void compute();

    /** b value field */
    HxPortFloatTextN portB;

    /** sub sample */
    HxPortToggleList portToggle;

    /** size of the gaussian filter */
    HxPortIntTextN portSize;

    /** sigma of the (Gaussian) filter */
    HxPortFloatTextN portSigma;

    /** A list of commands to fill the gradient informations. */
    HxPortButtonList portButtons;

    /** Do it button. */
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);

    /** Add a seperator to mark the start of the gradient tables */
    HxPortSeparator portSeparator;

    /** Now the gradients */
    HxPortFloatTextN portG1;
    HxPortFloatTextN portG2;
    HxPortFloatTextN portG3;
    HxPortFloatTextN portG4;
    HxPortFloatTextN portG5;
    HxPortFloatTextN portG6;

    HxConnection portC1;
    HxConnection portC2;
    HxConnection portC3;
    HxConnection portC4;
    HxConnection portC5;
    HxConnection portC6;

  public:
    /** Destructor. */
    ~HxComputeTensor();

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    /// Save ports.
    virtual void savePorts(FILE* fp);

private:
    void readGradients();
    void attachData();
    void saveGradientsToData();


    McDMatrix<double> NormOuterProduct(McDMatrix<double> g);
    McDMatrix<double> pinv(McDMatrix<double> g, double eps=-1);
    McDArray<HxConnection *> portConnectionList;
    McDArray<HxPortFloatTextN *> portGradientList;
};

#endif



/// @}

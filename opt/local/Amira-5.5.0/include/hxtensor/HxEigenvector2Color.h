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
#ifndef HX_EIGENVECTOR2COLOR
#define HX_EIGENVECTOR2COLOR

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
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>
#include "HxTensorWinDLLApi.h"

/** Class that computes a color representation of the eigenvalue decomposition of 
    a tensor field. The choice of the parameters is described in the documentation. */
class HXTENSOR_API HxEigenvector2Color : public HxCompModule {

  HX_HEADER(HxEigenvector2Color);
  
  public:
    /** Constructor. */
    HxEigenvector2Color();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    /** creates the illustration of the color mapping to directions. */
    void createMap(float *);

    /** Connection to a LabelSet that can be used to extract the color repres. for a material. */
    HxConnection portMask;

    /** Connection to the Eigenvalues of the tensor. Is used to compute the FA as alpha. */
    HxConnection portEvals;

    /** Port for selecting a material or a group of materials. */ 
    HxPortText portExpr;

    /// exposure control value
    HxPortFloatSlider portExposure;
    
    /** Option port to switch off scaling by fractional anisotropy. */
    HxPortToggleList portOption;

    /** Do it button. */
    HxPortDoIt portAction;

    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);


    float scaleBall;

  public:
    /** Destructor. */
    ~HxEigenvector2Color();

    /// Check if given data object can be reconstructed.
    virtual int canCreateData(HxData* data, McString& createCmd);

    /// Save ports.
    virtual void savePorts(FILE* fp);

};
#endif

/// @}

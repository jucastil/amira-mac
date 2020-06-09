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

/// @addtogroup hxelasticslicereg hxelasticslicereg
/// @{
#ifndef HX_ELASTIC_SLICE_REG
#define HX_ELASTIC_SLICE_REG

#include <hxelasticslicereg/HxElasticSliceRegWinDLLApi.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxlatticex/HxLattice.h>

class HXELASTICSLICEREG_API HxElasticSliceReg:public HxCompModule {

    HX_HEADER(HxElasticSliceReg);

  public:
    /** Constructor. */
    HxElasticSliceReg();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    /** Input field for material parameters lambda and mu */
    HxPortFloatTextN portMaterialParams;

    /** Select fixed material parameters or auto-estimation */
    HxPortRadioBox portParamMethod;

    /** Number of iterations */
    HxPortIntTextN portIterations;

    /** Maximum displacement of pixel*/
    HxPortFloatTextN portMaxDisplacement;

    /** Do it button. */
    HxPortDoIt portAction;

    /** resets displacement vectors and material parameters */
    void reset();

    /** performs the actual registration */
    void doIt();

  public:
    /** Destructor. */
    ~HxElasticSliceReg();

  private:
    // Stencils
    float S1[3][3], S2[3][3], S3[3][3], S4[3][3];
    void calculateStencils();
    // For calculating D1ij, D2ij, D3ij and D4ij
    float dValue(int quadrant, mclong i, mclong j, mclong M, mclong N);
    // For calculating Moore-Penrose pseudo inverse of 2x2 matrix
    void calculateInverse(const float D1, const float D2, const float D3,
                          const float D4, float &Dinv1, float &Dinv2, float &Dinv3, float &Dinv4);

    void calculateError(float *f, float *g, float *u, float *v);

    float *u;
    float *v;
    mclong M;
    mclong N;

};
#endif

/// @}

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
#ifndef HXGENERATETENSORDATA
#define HXGENERATETENSORDATA

#include <hxcore/HxCompModule.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortIntSlider.h>
#include <hxcore/HxPortSeparator.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortInfo.h>
#include <hxfield/HxField3.h>
#include <hxfield/HxLattice3.h>
#include <hxfield/HxSym2TensorField3.h>
#include <mclib/McDMatrix.h>
#include "HxTensorWinDLLApi.h"

/** This class is generating analytical tensor fields based on
  * different formulas. You need to connect an Arithmetic module
  * to this module in order to sample the Tensor field to a resolution
  * that you need (use Arx, Ary, Arz, Aix, Aiy, Aiz). In random setting
  * the tensor will be computed based on 8 random tensor values (each
  * matrix entry between [-0.5,0.5]*scale) set to the 8 corners of the
  * boundingbox of a cube. Values are linearily interpolated between the
  * corners to produce a smooth interpolation between the corners.
  * Please note that this interpolation technique does not guarantee
  * a positive definite tensor.
  */
class HXTENSOR_API HxGenerateTensorData : public HxSym2TensorField3 {

  HX_HEADER(HxGenerateTensorData);
  
  public:
    /** Constructor. */
    HxGenerateTensorData();

    /** Update method. */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    /** You can switch between the Scharzschild and the Kerr metric a Moebius 
        strip, a spherical tensor field and a random tensor field. The random
        tensor field is defined by random matrices at the 8 corners of the bounding
        box. */
    HxPortMultiMenu portToggle;

    /** This port scales the distance from the center of the data cube. this
        is useful because Arithmetic can only sample fields from [-1,1],
        or the size of the entries for the random choice. */
    HxPortFloatSlider portScale;
    
    /** The mass, a parameter of the Schwarzschild and Kerr matrices. */
    HxPortFloatSlider portMass;
    
    /** The angular moment a. */
    HxPortFloatTextN portAngularMoment;
    
    /// Tcl command interface.
    virtual int parse(Tcl_Interp* t, int argc, char **argv);
    
    /// Creates location class for this field.
    virtual HxLocation3* createLocation();
    
    /// To be able to save this data set with its settings.
    virtual int saveCreation(FILE* fp, const char *path, int flags);
    
    /// This calculates the actual tensor (6 elements) for the current
    /// polar position it returns the tensor in cartesian coordinates.
    static void calculate(HxGenerateTensorData*, float, float, float, float *);
    
    /// Calculates the tensor interpolation for 8 given corner values.
    static void calculateRandom(HxGenerateTensorData* f, float x, float y, float z, float *res);
    
    /// Returns bounding box of field.
    virtual void getBoundingBox(float bbox[6]) const;
    
    /// Duplicates the current HxAnnaScalarField3 object
    virtual HxData *duplicate() const;
    
 public:
    /** Destructor. */
    ~HxGenerateTensorData();
    
    /// Save ports.
    virtual void savePorts(FILE* fp);
        
 protected:
    float myBoundingBox[6];
    HxLocation3 locationA;
    void copyData(const HxGenerateTensorData &source);
    virtual void computeRange(float& min, float &max, bool discardUndefinedValues=false);
    virtual void info();
    //This method will always return 1.
    static int eval(HxGenerateTensorData*, HxLocation3*, float*);
    /// corner values for the interpolation random setting
    McDMatrix<double> cornerValues;
    /** Used in the radial field */
    double eval1, eval2, eval3;
};
#endif

/// @}

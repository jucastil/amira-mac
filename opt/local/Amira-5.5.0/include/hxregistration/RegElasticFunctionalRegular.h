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

/// @addtogroup hxregistration hxregistration
/// @{
#ifndef REG_ELASTICFUNCTIONAL_REGULAR
#define REG_ELASTICFUNCTIONAL_REGULAR

#include <hxregistration/RegElasticFunctional.h>

class RegElasticFunctionalRegularThread;


///Class for regular grids: iteration through image is done by pointers using templates in order to differentiate between primitive data types. 
class RegElasticFunctionalRegular : public RegElasticFunctional 
{
public:
    RegElasticFunctionalRegular(McDArray<HxSpatialData*> &r, McDArray<HxSpatialData*> &m, 
        RegInterpolator i, RegParametricTransform *t,RegMetric *me, 
        RegOptimizerCallback* cb, 
        RegDataClass dM, HxLandmarkSet* lm = NULL, bool fP=false );
    
    virtual    ~RegElasticFunctionalRegular();

    /// Like evaluate(), but remember transformed and interpolated values from model
    virtual double evaluateAndCache();

	virtual double evaluateAndCacheWithRegularizer();
    
    /// Re-evaluate functional after change in subvolume VolumeOfInfluence[idx] 
    virtual double evaluateIncremental( int idx, float delta = 0 );

	virtual double evaluateIncrementalWithRegularizer ( int idx, float delta = 0 );
    
    /// Evaluate functional for the complete volume and return gradient
    virtual double evaluate( McDVector<double> &gradient, double step, int unconstrained=0 );
    
    /// Evaluate functional for the complete volume
    virtual double evaluate();

	virtual double evaluateWithRegularizer();

    ///Is called once for one resolution level. Prepares for Nearest Neigbour interpolation.
    virtual void resetEval();   

 
private:
    virtual void createThreads();

    McDArray <RegElasticFunctionalRegularThread*> myThreads;

    virtual void updateFixedControlPoints();
    
    ///For Label Difference calculation.
    mclong samples;

    ///Copies for gradient calculation.
    mclong _samples;

    //For CREATE_EVAL
    float BBoxMod[6];

    int modelDims[3];


    //For CREATE_LOCATION    
    unsigned char extent;

    /// Normalization factors 1.0/(dims[i]-1), i=0,1,2
    float fx, fy, fz; 
   
};

#endif



/// @}

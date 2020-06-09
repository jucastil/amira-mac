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
#ifndef REG_VOXEL_EVALUATOR
#define REG_VOXEL_EVALUATOR

#include <hxfield/HxFieldEvaluator.h>
#include <hxfield/HxLoc3Regular.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxregistration/RegTypesAndMacros.h>
#include "hxregistrationAPI.h"


/// Helper class. Is inherited by classes which want to evaluate images at certain positions.
class HXREGISTRATION_API RegVoxelEvaluator
{
public:
    RegVoxelEvaluator(HxRegScalarField3 *mo, 
        RegInterpolator i);

    virtual ~RegVoxelEvaluator(){ 
        if (evalMod)
            delete evalMod;
        if(locMod)
            delete locMod;  
    } 

    ///Is called once for one resolution level.
    virtual void resetEval();

    void getEvalMod(HxFieldEvaluator*& eval, HxLocation3*& lo) { eval = evalMod; lo = locMod;}

    void createEvalModel(HxFieldEvaluator*& eval, HxLocation3*& loc);
    
    ///Performs interpolation
    HxFieldEvaluator* evalMod;

    ///Needed for interpolation
    HxLocation3* locMod;
   

protected:
    
    void createEval(HxRegScalarField3 *obj, HxFieldEvaluator*& eval);
    
    RegInterpolator interpolator;
   
    ///The image which shall be registered with respect to the reference
    HxRegScalarField3 *model;
};

#endif


/// @}

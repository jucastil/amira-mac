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
#ifndef HX_OPTIMIZER
#define HX_OPTIMIZER

#include <mclib/McDVector.h>

#include "hxregistrationAPI.h"

class RegParametricTransform;
class RegOptimizerCallback;
class RegFunctional;

/// Generic optimizer.
class  HXREGISTRATION_API  HxOptimizer 
{
//  private: HX_HEADER( HxOptimizer );
public:
  /// Constructor
    HxOptimizer(RegOptimizerCallback *r) : computeObject(r),  level(0), 
            updateStepScaleVector(false), functional(NULL), transform(NULL), 
        resolutionLevel(0), numResolutionLevels(1), mCurrentOptimization(0), mNumOptimizations(0) {} 

    /// Destructor
    virtual ~HxOptimizer() {}

    void setUpdateStepScaleVector( bool v) { updateStepScaleVector = v; } 
    
    bool getUpdateStepScaleVector()  { return updateStepScaleVector; } 
    
    /// Set functional to optimize.
    void setFunctional(RegFunctional * f);  

    /// Interface: Optimize functional.
    virtual void optimize(double exploration = 1, double accuracy = 0 )  = 0; 

    /**Set level of optimization in appropriate manner, eg. in terms of 
    grid refinement or image resolution.*/
    virtual void setLevel(short l) { level = l;}

    ///The object implementing the compute method
    RegOptimizerCallback *computeObject;

    /** Set current resolution level and total number of levels
    *  (needed for setProgressValue()).
    */
    void setResolution(int currentLevel, int numLevels, int currentOptimization=-1, int numOptimizations=-1) {
        if (currentLevel == -1) {
            // don't change resolutionLevel, numResolutionLevels, mNumOptimizations
            // just increment mCurrentOptimization
            ++mCurrentOptimization;

        } else {
	    resolutionLevel = currentLevel+1;

            if (numLevels == -1) {
                // don't change numResolutionLevels
            } else
                numResolutionLevels = numLevels;

            if (currentOptimization==-1)
                mCurrentOptimization = resolutionLevel;
            else
                mCurrentOptimization = currentOptimization+1;

            if (numOptimizations == -1)
                mNumOptimizations = numResolutionLevels;
            else
                mNumOptimizations = numOptimizations;
        }
    }
    

protected:  
    ///Level of optimization in terms of grid refinement or image resolution.
    short level;

    //DEBUG:
    void makeComment(McDVector<double> pV, char *comment) { 
        sprintf( comment, "pV: (%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f)", 
        pV[0],pV[1],pV[2],pV[3], pV[4],pV[5],pV[6],pV[7],pV[8],
        pV[9],pV[10],pV[11],pV[12],pV[13], pV[14]);
    }
 
    /** This flag determines whether the vector of step sizes is updated.
    * For some optimization problems, such as 2-D projection to 3-D image
    * registration, the current parameter vector determines the optimum step
    * sizes for the transformation parameters. In such cases, this flag can be
    * set to "true" so that after each optimization step the functional is
    * queried for updated steppings.
    */
    bool updateStepScaleVector;

    /// Optimization functional.
    RegFunctional *functional;

    /// Transform 
    RegParametricTransform *transform;

    int resolutionLevel;
    int numResolutionLevels;
    int mCurrentOptimization;
    int mNumOptimizations;
};

#endif  
   
  





/// @}

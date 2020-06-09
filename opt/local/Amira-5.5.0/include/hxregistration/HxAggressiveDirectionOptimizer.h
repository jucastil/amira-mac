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
#ifndef HX_AGGRESSIVEDIRECTIONOPTIMIZER
#define HX_AGGRESSIVEDIRECTIONOPTIMIZER

#include <hxregistration/HxOptimizer.h>

/** Aggressive line search optimizer.
 * This class implements an algorithm that optimizes the target function by
 * successive line searches in estimated gradient directions. 
 *
 * First, the gradient of the target functional is computed. The length of this
 * vector is normalized to the current search step size. Next, the resulting
 * vector is added to the current parameter vector as long as this leads to
 * an improvement of the target function.
 *
 * The components of the search vector that are below a given fraction of 
 * the absolute maximum component are set to zero now.
 *
 * Next, the length of the search vector is successively reduced by a factor
 * of 2, making one step forward or backward at each resulting length.
 *
 * The search then starts again with that vector.
 *
 * The main purpose of this optimizer is to exploit the gradient information
 * once computed as long as possible. However, this leads to a large number
 * of updates of the parameter vector. This, in turn, usually consumes more 
 * time than is saved by the small number of gradient evaluations.
 * Because of the massive variation of the paramVector, this optimizer is the
 * choice in rather coarse resolutions. At least the original resolution level
 * should be registered using a simpler optimizer.
 */
class  HXREGISTRATION_API HxAggressiveDirectionOptimizer : public HxOptimizer 
{
    public:
    /** Change behaviour of optimizer here by changing directionThreshold
     * default*/      
    HxAggressiveDirectionOptimizer( RegOptimizerCallback *r, 
          double s = 0.5, int e = 0,  double d = 0.1, int dim = 3) : 
	    HxOptimizer(r), stepFactor(s), directionThreshold(d), 
	    extensiveSearch(e), mDimension(dim) {}

    virtual ~HxAggressiveDirectionOptimizer() {}

    /// Optimize functional.
    virtual void optimize( double exploration = 1, 
			   double accuracy = 0 ) ;

    
private:
    /// Factor by which the step size is reduced after each pass.  
    double stepFactor;
   
    /** Threshold for direction components.
    * Before searching in a certain directions, all components below this
    * fraction of the maximum absolute component are set to zero. 
    * Set this flag to 0 to disable thresholding; set it to 1 to remove all but
    * the most significant components.
    */
    double directionThreshold;
    
    /// Flag for the "extensive search" mode.
    int extensiveSearch;

    /// dimensionality (2D or 3D)
    int mDimension;
};

#endif
    

    

    

/// @}

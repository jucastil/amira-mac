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
#ifndef HX_BESTNEIGHBOUROPTIMIZER
#define HX_BESTNEIGHBOUROPTIMIZER

#include <hxregistration/HxOptimizer.h>

/** Best-neighbour-search optimizer.
 * This class implements a search technique introduced by Studholme et al.
 * By modifying each parameter of the search space by a certain step up- and
 * downwards, all "neighbours" of the current parameter vector are visited. For
 * each of these, the target function (functional) is evaluated. The search 
 * then continues from the parameter vector producing the maximum value. If no
 * further improvement is possible, the step size is decreased by a given 
 * factor until it reaches a lower bound.
 */
class  HXREGISTRATION_API  HxBestNeighbourOptimizer : public HxOptimizer 
{
//  private: HX_HEADER( HxBestNeighbourOptimizer );
  
    public:
    /// Constructor
    HxBestNeighbourOptimizer(RegOptimizerCallback *r, 
                             double s = 0.5, int dim = 3) : 
	    HxOptimizer(r), stepFactor(s), mDimension(dim) {}
    
    /// Destructor
    virtual ~HxBestNeighbourOptimizer() {}

    /// Interface: Optimize functional.
    virtual void optimize(  double exploration = 1, 
			   double accuracy = 0 );  

private:
    /** Search step factor.
    * This variable determines the factor by which to decrease the search step
    * size if no further improvement is possible at a certain resolution.
    * Reasonable values are in the range 0 < StepFactor < 1. For most cases,
    * a value of 0.5 has been found to provide optimum accuracy and performance.
    */
    double stepFactor;

    /// dimensionality: 2D or 3D
    int mDimension;
};

#endif
    

    

    

/// @}

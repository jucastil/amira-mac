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
#ifndef REG_AFFINEFUNCTIONAL_UNIFORM
#define REG_AFFINEFUNCTIONAL_UNIFORM

#include <hxregistration/RegAffineFunctional.h>

/// Functional subclass.
class RegAffineFunctionalUniform : public RegAffineFunctional 
{
public:
    ///Constructor
#ifdef REG_USE_HX_OPTIMIZE
    RegAffineFunctionalUniform(const McDArray<HxSpatialData*> &r, McDArray<HxSpatialData*> &m,
        RegInterpolator i, RegParametricTransform *t, RegMetric *me, RegOptimizerCallback* cb,
        int c, int dim) :
    RegAffineFunctional(r, m, i, t, me, cb, c, dim)
#else
    RegAffineFunctionalUniform(const McDArray<HxSpatialData*> &r, McDArray<HxSpatialData*> &m,
        RegInterpolator i, RegParametricTransform *t, RegMetric *me, RegOptimizerCallback* cb,
        int c, int dim, unsigned int numThreads) :
    RegAffineFunctional(r, m, i, t, me, cb, c, dim),
        mNumThreads(numThreads)
#endif
    {
#ifndef _OPENMP
        mNumThreads = 1;
#endif
    }

    ///Destructor
    virtual ~RegAffineFunctionalUniform() {}
    
    /// Evaluate functional
    //virtual double evaluate() ;
    
    /// should be replaced by gradient. Evaluate functional and return gradient
    //virtual double evaluate( McDVector<double> &gradient,  float step,
    //    int unconstrained=0); 

#ifdef REG_USE_HX_OPTIMIZE
void RegAffineFunctionalUniform::initTransform(RegParametricTransform*)
{
    RegAffineFunctional::initTransform(transform);
}
#endif
        
    ///Is called once for one resolution level. Prepares for interpolation.
    virtual void resetEval();   

private:
/** Compute functional value without volume clipping.
* This function iterates over all voxels of the reference image. For each of
* these, its position after applying the current coordinate transformation
* is determined. If it is inside the model image, the corresponding model
* voxel is retrieved (by interpolation or not).
* From the resulting sequence of voxel pairs, the voxel-based similarity 
* measure (metric) is calculated.
*@return The computed similarity measure as returned by the "metric" 
* subobject.
    */
    virtual double evaluateNoClip ();
      
    ///For Label Difference calculation.
    mclong samples;

    int modelDims[3];

    /* matrix including shift to lower left corner of bounding box
       and scaling with fx, fy, fz
    */
    SbMatrixd matTransScale;

    unsigned int mNumThreads;
};

#endif



/// @}

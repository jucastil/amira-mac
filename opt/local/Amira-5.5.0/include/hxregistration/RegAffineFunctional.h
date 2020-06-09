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
#ifndef REG_AFFINEFUNCTIONAL
#define REG_AFFINEFUNCTIONAL

#include <hxfield/HxCoord3.h>
#include <hxfield/HxLoc3Regular.h>
#include <hxregistration/RegFunctional.h>
#include <hxregistration/RegAffineTransform.h>
#include <hxregistration/RegVoxelEvaluator.h>
#include <Inventor/SbLinear.h>


/// Functional subclass.
class RegAffineFunctional : public RegFunctional 
{
public:
    ///Constructor
#ifdef REG_USE_HX_OPTIMIZE
    RegAffineFunctional(const McDArray<HxSpatialData*> &r, McDArray<HxSpatialData*> &m,
        RegInterpolator i, RegParametricTransform *t, RegMetric *me, RegOptimizerCallback* cb,
        int c, int dim) :
        RegFunctional(r, m, t, me, cb)
#else
    RegAffineFunctional(const McDArray<HxSpatialData*> &r, McDArray<HxSpatialData*> &m,
        RegInterpolator i, RegParametricTransform *t, RegMetric *me, RegOptimizerCallback* cb,
        int c, int dim) :
        RegFunctional(r, m, t, me, cb)
#endif
        , clipping(c), mDimension(dim) {
        mEval = new RegVoxelEvaluator(dynamic_cast<HxRegScalarField3 *>(m[0]), i);
    }

    ///Destructor
    virtual ~RegAffineFunctional() {
        if (mEval)
            delete mEval;
    }
    
    /// Evaluate functional
    virtual double evaluate() ;
    
    /// should be replaced by gradient. Evaluate functional and return gradient
    virtual double evaluate( McDVector<double> &gradient,  double step,
        int unconstrained=0); 

#ifdef REG_USE_HX_OPTIMIZE
void RegAffineFunctional::initTransform(RegParametricTransform*)
{
    RegFunctional::initTransform(transform);
}
#endif

    /// Set clipping mode.
    void setClipping(  int c) { clipping = c; }
    
    /// This functional uses mEval, but derived classes use their own interpolation.
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

    /** Compute functional value with volume clipping using multi-threading.
    * This function iterates over all voxels of the reference image that - after
    * applying the current coordinate transformation - are located inside the
    * mode image. This set of voxels is determined on-the-fly by an extension of
    * Liang and Barsky's "Parameterized Line-Clipping" technique.
    * From the resulting sequence of reference/model voxel pairs, the selected
    * voxel-based similarity measure (metric) is computed.
    *@param paramVector The current parameter vector describing the effective coordinate
    * transformation.
    *@return The computed similarity measure as returned by the "metric" 
    * subobject.
    */
    double evaluateFullClip () { 
        return 0;
    }
  
    /** Clipping algorithm to use.
    * A flag indicating whether exact volume clipping is
    * to be used (clipping==1) or not (clipping==0).
    */
    int clipping;

    int mDimension;

    RegVoxelEvaluator *mEval;
};

#endif



/// @}

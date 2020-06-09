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
#ifndef REG_FUNCTIONAL
#define REG_FUNCTIONAL


#include <hxcore/HxObjectPool.h>
#include <hxregistration/RegMetric.h>
#include <hxregistration/RegParametricTransform.h>
#include <hxregistration/RegTypesAndMacros.h>
#include <hxregistration/RegOptimizerCallback.h>
#include "hxregistrationAPI.h"


/** Functional that evaluates a voxel-based similarity measure.
* This class defines the type of functional that is optimized during
* voxel-based registration. It holds references to reference and model data
* and computes similarity as well as its gradient w.r.t. a given
* transformation.
* The metric to be optimized is given by a ructor parameter.
*
* This class, however, is still universal with respect to the registration
* transformation. Derived classes can therefore efficiently implement all
* transformation-dependent operations.
*/
class HXREGISTRATION_API RegFunctional
{
public:
/** Constructor.
* Init pointers to volume and transformation objects and initialize
* internal data structures.
*@param reference The reference (i.e. static) volume.
*@param model The model (i.e. transformed) volume.
*@param t A transformation . This object determines the type
* of transformation to be optimized. 
    */	
    ///Constructor
    RegFunctional(const McDArray<HxSpatialData*> &r, 
                  McDArray<HxSpatialData*> &mo, 
                  RegParametricTransform *t, RegMetric *me,
                  RegOptimizerCallback* cb): 
        metric(me), transform(t), reference(r), model(mo), computeObject(cb)
    { 
        modelSize = model[0]->getBoundingBoxSize(); 
    }
    
    ///Destructor
    virtual ~RegFunctional() { 
        if (metric)
            delete metric; 
        //DO NOT delete transform (original data)
    } 
    
    ///Different from evaluate() for elastic registration only.
    virtual double evaluateAndCache() { return this->evaluate(); }
    
    /**Different from evaluate() for elastic registration only.
    *@param delta Discretization step for approximatio of partial derivative
    */
    virtual double evaluateIncremental (int idx, double delta = 0 ) { return this->evaluate(); }
    
    /// Evaluate functional
    virtual double evaluate() = 0;
    
    /// replace with gradiet. Evaluate functional and return gradient
    virtual double evaluate(McDVector<double> &gradient, double step,
        int unconstrained=0) = 0;
    
        /** get gradient. This should replace the old evaluate for gradient.
    When all classes have implemented this method, make abstract */ 
    //why? when gradient really returns a bool value only, a second call 
    //to evaluate would be necessary to get the current metric result.
    virtual bool gradient( McDVector<double> &gradient) 
    { return true;}
    
    
    /** this defines the current grid size. Used for gradient computation */
    void setScale(double scale) { mDelta = scale; }
    
    McVec3f* getModelSize(){return &modelSize;}
    
    ///Is needed by optimizer: May differ for different resolution levels.
    RegParametricTransform* getTransform() {return transform;}
    
    /// inititialises the tranform 
    virtual void initTransform(RegParametricTransform* transform = NULL)
    { 
        if (transform) {
            McVec3f *mdSz = getModelSize(); 
            SbVec3d modSize((*mdSz)[0], (*mdSz)[1], (*mdSz)[2]);
            transform->computeParamStep(&modSize);
        }
     }

    ///Remove objects from object pool; original data must be preserved, only resampled images shall be removed.
    inline void removeObjects( /*int idx, */ 
                              const McDArray<HxSpatialData*> &ref, McDArray<HxSpatialData*> &mod) 
    { 
        /*
        if ( (ref[idx] != reference[idx]) && (mod[idx] != model[idx]) )
            //different address -> delete, it´s not the original data!
        {
            theObjectPool->removeObject(reference[idx]);
            theObjectPool->removeObject(model[idx]);
        }
        */

        // ignore idx; remove all objects from McDArray reference which are not
        // original data
        for (int idx1=0; idx1<reference.size(); idx1++) {
            bool isOriginal = false;
            for (int idx2=0; idx2<ref.size(); idx2++) {
                if (reference[idx1] == ref[idx2])
                    isOriginal = true;
            }
            if (!isOriginal) {
                theObjectPool->removeObject(reference[idx1]);
                reference[idx1] = NULL;
            }
        }

        // ignore idx; remove all objects from McDArray model which are not
        // original data
        for (int idx1=0; idx1<model.size(); idx1++) {
            bool isOriginal = false;
            for (int idx2=0; idx2<mod.size(); idx2++) {
                if (model[idx1] == mod[idx2])
                    isOriginal = true;
            }
            if (!isOriginal) {
                theObjectPool->removeObject(model[idx1]);
                model[idx1] = NULL;
            }
        }



    }


#ifdef REG_USE_HX_OPTIMIZE    
    void setDataLevel(int d) {dataLevel = d;}
#endif

    ///Is needed by HxAffineRegistration for computation of principal axes
    virtual void setTransform(RegParametricTransform *t) {transform = t;}
    
    

    McVec3f modelSize;

    ///The metric used to evaluate the current transform
    RegMetric *metric;
    
    ///The transform
    RegParametricTransform *transform;
    
    /// grid size
    double mDelta;

#ifdef REG_USE_HX_OPTIMIZE    
   int dataLevel;
#endif

protected:
    ///The reference image
    McDArray<HxSpatialData*> reference;

    ///The image which shall be registered with respect to the reference
    McDArray<HxSpatialData*> model;

    ///The object implementing the compute method
    RegOptimizerCallback *computeObject;
};

#endif


/// @}

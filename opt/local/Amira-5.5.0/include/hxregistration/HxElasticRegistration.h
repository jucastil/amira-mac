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
#ifndef HXELASTICREGISTRATION
#define HXELASTICREGISTRATION

#include <hxcore/HxCompModule.h>
#include <hxlandmark/HxLandmarkSet.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxConnection.h>

#include <hxregistration/HxVoxelRegistration.h>
#ifdef REG_USE_HX_OPTIMIZE
#include <hxregistration/RegElasticObjFunction.h>
#endif
#include <hxregistration/RegVoxelLinearSplineTransform.h>
#include <hxregistration/hxregistrationAPI.h>

/// Compute module elastic registration.
class HXREGISTRATION_API HxElasticRegistration : public HxVoxelRegistration
{
    
private: HX_HEADER( HxElasticRegistration );
         typedef HxVoxelRegistration inherited;
         
public:
    HxElasticRegistration();
    
    virtual ~HxElasticRegistration();
    
    virtual RegFunctional* createFunctional(McDArray<HxSpatialData*>  &ref, 
        McDArray<HxSpatialData*> &mod, int refinements = -1, int dataLevel = -1);
    
    virtual void compute();
    
    virtual void update();
    
    void showControlPoints();
    
    virtual bool applyTransform (RegParametricTransform *transform = NULL);
    
    void createVectorField();

    ///Use landmarks for validation.
    void validateLandmarks();

    void saveControlPoints();
    
    virtual int initRegistration ();
    
    virtual void doneRegistration (); 
    
    virtual int doneResolution(int level, int total);
    
    virtual void enterResolution(int level, int total, RegFunctional* f = NULL);

    void writeModel();
    
    
    /// Show and save results.
    HxPortButtonList portResult;      
    
    /// Maximal distance vor validation via landmarks.
    HxPortFloatTextN portAboveThresh;

    /// Output for validation via landmarks.
    HxPortInfo portStatistics;

    /// 2nd output for validation via landmarks.
    HxPortInfo portStatistics2;

    ///chose the type of interpolation for the warp
    //HxPortOptionMenu portWarpType;    

    HxConnection portControlPoints;
    
    HxPortIntTextN portInitialGridSize;
    
    HxPortIntTextN portRefineGrid;
    
    /**Values of weights for regularization measures:
    * jacobian constraint: Weighting of Jacobian constraint.
    * grid energy: Weighting of grid bending energy constraint.
    */
    HxPortFloatTextN portRegularization;

    /** Should consist of two sets (optional). The distance of corresponding landmarks serves 
    * as an optional penalty term in the optimization.
    * It is assumed that first set is that of the model. */
    HxConnection portLandmarks;
    
    
private:   
    virtual void createTransform();

    ///Needed for showCP, applyTransform befor registration has started
    void createInitialTransform();
    
    virtual void updateReference();

#ifdef REG_USE_HX_OPTIMIZE
    virtual void createObjFunction(RegTimer *timer = NULL) {mObjFunction = new
        RegElasticObjFunction(this, timer);}
    
    ///prolongations must be cast to McDArray< McDArray<int> > *.
    virtual int getProlongationsPerDataLevel();
#endif

    HxLandmarkSet *ControlPoints;

    int gridSize[3];

    HxLandmarkSet* landmarks;

    HxLandmarkSet* transformedLandmarks;

    ///Voxel size of original reference is needed for slightly extending the control grid
    float voxelSize[3];

    bool controlPointsShowing;
    
    int computeFinalGridSize(int axis);

    RegSplineTransform *warpTransform;
    
    /// This value determines how often the control point grid is refined at every level.
    McDArray<int> RefineGrid;
    
    /// Number of grid refinements at current level.
    short RefinedGridAtLevel;

    /// Number of grid refinements in total.
    short RefinedGridTotal;
    
    /// Number of finest Levels on which to use grid energy (quasi adaptive).
    short NTimesGridEnergy;
};

#endif

/// @}

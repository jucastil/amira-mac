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
#ifndef REG_CREATEDEFORMATION
#define REG_CREATEDEFORMATION

#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortInfo.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxConnection.h>
#include <hxfield/HxRegScalarField3.h>
#include <hxregistration/RegSplineTransform.h>

/// Compute module for applying a transformation computed by HxElasticRegistration.
class  HxApplyBSplineTransform : public HxCompModule
{
private: HX_HEADER( HxApplyBSplineTransform );
    
public:
    HxApplyBSplineTransform();

    virtual ~HxApplyBSplineTransform();

    /** Perform all the initialization steps: set grid size, initialize grid (inner distances)
    * set control points, define the interpolated space, calculate grid spacing from that
    * and finally, precompute B-Spline interpolants.*/
    void initWarpTransform();

    /// update method 
    virtual void update();
    
    /// compute method 
    virtual void compute(); 
    
    void applyTransform ();
    
    void createVectorField();

    void showDeformedGrid();

    void validateLandmarks();
    
    HxConnection portControlPoints;
        
    /// Secondary input connection to reference dataset (optional)
    HxConnection portReference;

    /** Defines desired resolution in x, y, and z direction (only if
    reference is not present). */
    HxPortIntTextN portRes;

    /// Apply deformation or create VectorField.
    HxPortButtonList portAction;

    /// Show and validate results.
    HxPortButtonList portResult;

    /// Maximal distance vor validation via landmarks.
    HxPortFloatTextN portAboveThresh;

    /// Output for validation via landmarks.
    HxPortInfo portStatistics;

    /// 2nd output for validation via landmarks.
    HxPortInfo portStatistics2;
    
    /** Should consist of two sets (optional). The distance of corresponding landmarks serves 
    * as an optional penalty term in the optimization.
    * It is assumed that first set is that of the model. */
    HxConnection portLandmarks;

       
protected:      

	/// 2 for 2D, 3 for 3D
	int mDimension;
    McDArray<HxRegScalarField3*> reference;
    
    HxRegScalarField3 *model;
    
    HxRegVectorField3 *vecField;

    HxLandmarkSet *ControlPoints;  
       
    ///Nearest neighbour for label fields, trilinear for others
    RegInterpolator interpolator;
    
    RegDataClass dataClassRef;
    
    RegDataClass dataClassMod;    
    
    RegSplineTransform *warpTransform;

    HxLandmarkSet* landmarks;

    HxLandmarkSet* transformedLandmarks;

};

#endif

/// @}

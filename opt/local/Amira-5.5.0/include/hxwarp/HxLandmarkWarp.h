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

/// @addtogroup hxwarp hxwarp
/// @{
#ifndef HX_LANDMARK_WARP_H
#define HX_LANDMARK_WARP_H

#include <hxwarp/HxWarpWinDLLApi.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortMultiMenu.h>
#include <hxcore/HxPortToggleList.h>
#include <hxcore/HxPortRadioBox.h>
#include <hxcore/HxConnection.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxPortFloatSlider.h>
#include <hxfield/HxUniformScalarField3.h>
#include <hxfield/HxUniformVectorField3.h>

class SbMatrix;

/** ... */
class HXWARP_API HxLandmarkWarp : public HxCompModule {

  HX_HEADER(HxLandmarkWarp);
  
  public:
    /** Constructor. */
    HxLandmarkWarp();

    /** Update method (port interface) */
    virtual void update();

    /** Compute method. */
    virtual void compute();

    ///
    HxConnection portImageData;

    /** Optional connection to define coordinate system. */
    HxConnection portMaster;

    /** Filter types: 0= 1->2  1= 2->1.. */
    HxPortRadioBox portDirection;

    /** Filter types: 0=Bookstein-Splines 1=flow 2=rigid.. */
    HxPortMultiMenu portMethod;

    /** Whether or not to premultiply with rigid transform. */
    HxPortToggleList portRigid;

    /** */
    HxPortToggleList portOptions;

    /** beta value (Flow-method) 0..1 */
    HxPortFloatSlider portParameter;

    /** Norm to be used, L1 or L2 */
    HxPortMultiMenu portNorm;

    /** Do it button. */
    HxPortDoIt portAction;

  protected:
    /** Destructor. */
    ~HxLandmarkWarp();

    HxUniformScalarField3* createOutputDataSet();
    HxUniformVectorField3* createOutputVectorDataSet();

    // if an output vector is supplied (!=0) we will return
    // as well the displacement field
    void RigidWarp( HxUniformScalarField3* input, 	
		   HxUniformScalarField3* output,		
		   SbMatrix* m,
		   HxUniformVectorField3* outputVector=0);

    void prepareLandmarks(McDArray<McVec3f>& p1,
			  McDArray<McVec3f>& p2,
			  SbMatrix& rigid);
};

#endif

/// @}

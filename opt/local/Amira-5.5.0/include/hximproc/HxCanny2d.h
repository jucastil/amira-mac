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

/// @addtogroup hximproc hximproc
/// @{
#ifndef HX_CANNY_2D
#define HX_CANNY_2D

#include <hxcore/HxObjectPool.h>
#include <hxcore/HxCompModule.h>
#include <hxcore/HxPortFloatTextN.h>
#include <hxcore/HxPortIntTextN.h>
#include <hxcore/HxPortButtonList.h>
#include <hxcore/HxPortDoIt.h>
#include <hxcore/HxConnection.h>

#include <hxfield/HxRegScalarField3.h>

#include "HxImprocWinDLLApi.h"

/** Canny edge detector: 
    1. Application of Gauss filter.
    2. Application of Sobel filter (gradient filter).
    3. Along the gradient direction (normal to edges), a non-maximal
       suppression (thinning) is performed.
    4. A so-called "hysteresis thresholding": Edges are connected
       w.r.t. to lower and upper bounds provided by the user.
*/
class HXIMPROC_API HxCanny2D : public HxCompModule 
{
    HX_HEADER(HxCanny2D);

public:
    ///Constructor
    HxCanny2D();

    ///Destructor
    virtual ~HxCanny2D(){};

    /// update method 
    virtual void update() {};  
    
    /// compute method 
    virtual void compute();

    void removeResult()
    {
        HxRegScalarField3 *result = (HxRegScalarField3 *) getResult();
        theObjectPool->removeObject(result);
    }

    /// Sigma for Gauss filter
    HxPortFloatTextN portSigma;

    /// Kernel size for Gauss filter
    HxPortIntTextN portKernelSize;

    /// Range for non maximal suppression of canny filter.
    HxPortIntTextN portSuppressionRange;

    /// Mask size determines to which degree holes between edges are filled..
    HxPortIntTextN portConnectEdgesMaskSize;
	
    /** Start connecting edges from all points with value >
        mConnectEdgesThresholdUpper ("guaranteed true edges"); Later on,
        mark points as edge, where value > mConnectEdgesThresholdLower AND
        point within mConnectEdgesMaskSize from a point with value >
        mConnectEdgesThresholdUpper.
    */
    HxPortFloatTextN portConnectEdgesThreshold;
	
    ///
    HxPortDoIt portAction;

protected:
     virtual int canCreateData(HxData* data, McString& createCmd);
};

#endif

/// @}
